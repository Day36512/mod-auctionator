#include "Auctionator.h"
#include "AuctionHouseMgr.h"
#include "AuctionatorSeller.h"
#include "Item.h"
#include "DatabaseEnv.h"
#include "PreparedStatement.h"
#include <random>


AuctionatorSeller::AuctionatorSeller(Auctionator* natorParam, uint32 auctionHouseIdParam)
{
    SetLogPrefix("[AuctionatorSeller] ");
    nator = natorParam;
    auctionHouseId = auctionHouseIdParam;

    ahMgr = nator->GetAuctionMgr(auctionHouseId);
};

AuctionatorSeller::~AuctionatorSeller()
{
    // TODO: clean up
};

void AuctionatorSeller::LetsGetToIt(uint32 maxCount, uint32 houseId)
{
    // Check config settings
    bool excludeGems = nator->config->excludeGems;
    bool excludeEnchants = nator->config->excludeEnchants;
    bool excludeTradeGoods = nator->config->excludeTradeGoods;

    // Construct additional WHERE conditions based on config
    std::string additionalConditions = "";
    if (excludeGems) {
        additionalConditions += " AND it.bagFamily != 512";
    }
    if (excludeEnchants) {
        additionalConditions += " AND (it.class != 0 OR it.subclass != 6)";
    }
    if (excludeTradeGoods) {
        additionalConditions += " AND it.class != 7";
    }

    // Set the maximum number of items to query for. Changing this <might>
    // affect how random our auctoin listing are at the cost of memory/cpu
    // but it is something i need to test.
    uint32 queryLimit = nator->config->sellerConfig.queryLimit;

    // Get the name of the character database so we can do our join below.
    std::string characterDbName = CharacterDatabase.GetConnectionInfo()->database;

    // Construct the SQL query with the additional conditions
    std::string itemQuery = R"(
        SELECT
            it.entry
            , it.name
            , it.BuyPrice
            , it.stackable
            , it.quality
            , mp.average_price
            , it.class 
        FROM
            mod_auctionator_itemclass_config aicconf
            LEFT JOIN item_template it ON
                aicconf.class = it.class
                AND aicconf.subclass = it.subclass
                -- skip BoP
                AND it.bonding != 1
                AND it.bonding != 4
                AND (
                    it.bonding >= aicconf.bonding
                    OR it.bonding = 0
                )
            LEFT JOIN mod_auctionator_disabled_items dis on it.entry = dis.item
LEFT JOIN (
    SELECT
        count(ii.itemEntry) as itemCount
        , ii.itemEntry AS itemEntry
    FROM
        acore_characters.item_instance ii
        INNER JOIN {}.auctionhouse ah ON ii.guid = ah.itemguid
    WHERE ah.houseId = {}
    GROUP BY ii.itemEntry
) ic ON ic.itemEntry = it.entry
            LEFT JOIN
                (
                    SELECT
                        DISTINCT(mpp.entry),
                        mpa.average_price
                    FROM {}.mod_auctionator_market_price mpp
                    INNER JOIN (
                        SELECT
                            max(scan_datetime) AS scan,
                            entry
                        FROM {}.mod_auctionator_market_price
                        GROUP BY entry
                    ) mps ON mpp.entry = mps.entry
                    INNER JOIN
                        {}.mod_auctionator_market_price mpa
                        ON mpa.entry = mpp.entry
                        AND mpa.scan_datetime = mps.scan
                ) mp ON it.entry = mp.entry
        WHERE
            dis.item IS NULL
            AND it.entry <= 56000
            )" + additionalConditions + R"(
        ORDER BY RAND()
        LIMIT {}
        ;
    )";

    QueryResult result = WorldDatabase.Query(
        itemQuery,
        characterDbName,
        houseId,
        characterDbName,
        characterDbName,
        characterDbName,
        queryLimit
    );

    if (!result)
    {
        logDebug("No results for LetsGo item query");
        return;
    }

    // Dinkle: Randomize prices a bit.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> fluctuationDist(0.95, 1.05); // +/- a 5% fluctuation

    AuctionatorPriceMultiplierConfig multiplierConfig = nator->config->sellerMultipliers;
    uint32 count = 0;
    do
    {
        count++;
        Field* fields = result->Fetch();

        // TODO: refactor listing an item into a testable method
        std::string itemName = fields[1].Get<std::string>();

        uint32 stackSize = fields[3].Get<uint32>();
        if (stackSize > 20) {
            stackSize = 20;
        }

        // if (stackSize > 20) {
        //     std::random_device rd;
        //     std::mt19937 gen(rd());
        //     std::uniform_int_distribution<> dis(1, stackSize);
        //     stackSize = dis(gen);
        //     logDebug("Stack size: " + std::to_string(stackSize));
        // }

        uint32 quality = fields[4].Get<uint32>();
        float qualityMultiplier = Auctionator::GetQualityMultiplier(multiplierConfig, quality);

        // Dinkle: Fetch the item class 
        uint32 itemClass = fields[6].Get<uint32>(); 
        float classMultiplier = 1.0f; // Default multiplier

        // Dinkle: Determine the class multiplier
        switch (itemClass) {
        case 0: // Consumable
            classMultiplier = multiplierConfig.consumable;
            break;
        case 1: // Container
            classMultiplier = multiplierConfig.container;
            break;
        case 2: // Weapon
            classMultiplier = multiplierConfig.weapon;
            break;
        case 3: // Gem
            classMultiplier = multiplierConfig.gem;
            break;
        case 4: // Armor
            classMultiplier = multiplierConfig.armor;
            break;
        case 5: // Reagent
            classMultiplier = multiplierConfig.reagent;
            break;
        case 6: // Projectile
            classMultiplier = multiplierConfig.projectile;
            break;
        case 7: // Trade Goods
            classMultiplier = multiplierConfig.tradeGoods;
            break;
        case 9: // Recipe
            classMultiplier = multiplierConfig.recipe;
            break;
        case 11: // Quiver
            classMultiplier = multiplierConfig.quiver;
            break;
        case 13: // Key
            classMultiplier = multiplierConfig.key;
            break;
        case 15: // Miscellaneous
            classMultiplier = multiplierConfig.miscellaneous;
            break;
        case 16: // Glyph
            classMultiplier = multiplierConfig.glyph;
            break;
        default:
            classMultiplier = 1.0f; // Default multiplier if class is not listed
        }

        uint32 price = fields[2].Get<uint32>();
        uint32 marketPrice = fields[5].Get<uint32>();
        if (marketPrice > 0) {
            logDebug("Using Market over Template [" + itemName + "] " +
                std::to_string(marketPrice) + " <--> " + std::to_string(price));
            price = marketPrice;
        }

        if (price == 0) {
            price = 1000 * qualityMultiplier;
        }
        
        float combinedMultiplier = qualityMultiplier + classMultiplier;
        float fluctuationFactor = fluctuationDist(gen);
        uint32 finalPrice = uint32(price * stackSize * combinedMultiplier * fluctuationFactor);

        // Setup the auction item
        AuctionatorItem newItem = AuctionatorItem();
        newItem.itemId = fields[0].Get<uint32>();
        newItem.quantity = 1;
        newItem.buyout = finalPrice;
        newItem.time = 60 * 60 * 12;
        newItem.stackSize = stackSize;

        logDebug("Adding item: " + itemName
            + " with quantity of " + std::to_string(newItem.quantity)
            + " at price of " +  std::to_string(newItem.buyout)
            + " to house " + std::to_string(houseId)
        );


        nator->CreateAuction(newItem, houseId);
        if (count == maxCount) {
            break;
        }
    } while (result->NextRow());

    logInfo("Items added houseId("
        + std::to_string(houseId)
        + ") this run: " + std::to_string(count));

};
