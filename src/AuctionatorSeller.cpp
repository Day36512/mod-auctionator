#include "Auctionator.h"
#include "AuctionHouseMgr.h"
#include "AuctionatorSeller.h"
#include "Item.h"
#include "DatabaseEnv.h"
#include "PreparedStatement.h"
#include <random>
#include <optional>

AuctionatorSeller::AuctionatorSeller(Auctionator * natorParam, uint32 auctionHouseIdParam) {
    SetLogPrefix("[AuctionatorSeller] ");
    nator = natorParam;
    auctionHouseId = auctionHouseIdParam;
    ahMgr = nator->GetAuctionMgr(auctionHouseId);
}

AuctionatorSeller::~AuctionatorSeller()
{
    // TODO: clean up
};

float AuctionatorSeller::GetQualityMultiplier(uint32 quality) {
    AuctionatorPriceMultiplierConfig multiplierConfig = nator->config->sellerMultipliers;
    switch (quality) {
    case 0: return multiplierConfig.poor;       // Poor
    case 1: return multiplierConfig.normal;     // Normal
    case 2: return multiplierConfig.uncommon;   // Uncommon
    case 3: return multiplierConfig.rare;       // Rare
    case 4: return multiplierConfig.epic;       // Epic
    case 5: return multiplierConfig.legendary;  // Legendary
    default: return 1.0f; // Default
    }
}

std::optional<float> AuctionatorSeller::GetClassMultiplier(uint32 itemClass) {
    AuctionatorPriceMultiplierConfig& multiplierConfig = nator->config->sellerMultipliers; 
    switch (itemClass) {
    case 1: return multiplierConfig.container;
    case 2: return multiplierConfig.weapon;
    case 3: return multiplierConfig.gem;
    case 4: return multiplierConfig.armor;
    case 5: return multiplierConfig.reagent;
    case 6: return multiplierConfig.projectile;
    case 7: return multiplierConfig.tradeGoods;
    case 9: return multiplierConfig.recipe;
    case 11: return multiplierConfig.quiver;
    case 13: return multiplierConfig.key;
    case 15: return multiplierConfig.miscellaneous;
    case 16: return multiplierConfig.glyph;
    default: return std::nullopt; // No specific class multiplier
    }
}

std::optional<float> AuctionatorSeller::GetSubclassMultiplier(uint32 itemClass, uint32 itemSubclass) {
    AuctionatorPriceMultiplierConfig& multiplierConfig = nator->config->sellerMultipliers; // Access sellerMultipliers directly
    if (itemClass == 0) { // Assuming 0 is for consumables
        switch (itemSubclass) {
        case 1: return multiplierConfig.potion;
        case 2: return multiplierConfig.elixir;
        case 3: return multiplierConfig.flask;
        case 4: return multiplierConfig.scroll;
        case 5: return multiplierConfig.foodDrink;
        case 6: return multiplierConfig.itemEnhancement;
        case 7: return multiplierConfig.bandage;
        case 8: return multiplierConfig.otherConsumable;
        default: return std::nullopt; // No specific subclass multiplier
        }
    }
    return std::nullopt; // No subclass multiplier for other classes
}

void AuctionatorSeller::LetsGetToIt(uint32 maxCount, uint32 houseId)
{
    // Check config settings
    bool excludeGems = nator->config->excludeGems;
    bool excludeEnchants = nator->config->excludeEnchants;
    bool excludeTradeGoods = nator->config->excludeTradeGoods;
    bool excludeGlyphs = nator->config->excludeGlyphs;
    
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
    if (excludeGlyphs) {
        additionalConditions += " AND it.class != 16";
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
            , it.subclass
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
    float fluctuationMin = nator->config->sellerConfig.fluctuationMin;
    float fluctuationMax = nator->config->sellerConfig.fluctuationMax;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> fluctuationDist(fluctuationMin, fluctuationMax);

    AuctionatorPriceMultiplierConfig multiplierConfig = nator->config->sellerMultipliers;
    uint32 count = 0;
    do
    {
        count++;
        Field* fields = result->Fetch();

        // TODO: refactor listing an item into a testable method
        std::string itemName = fields[1].Get<std::string>();

        // if (stackSize > 20) {
        //     std::random_device rd;
        //     std::mt19937 gen(rd());
        //     std::uniform_int_distribution<> dis(1, stackSize);
        //     stackSize = dis(gen);
        //     logDebug("Stack size: " + std::to_string(stackSize));
        // }

        uint32 quality = fields[4].Get<uint32>();
        uint32 itemClass = fields[6].Get<uint32>();
        uint32 itemSubclass = fields[7].Get<uint32>();
        uint32 price = fields[2].Get<uint32>();
        uint32 marketPrice = fields[5].Get<uint32>();

        float qualityMultiplier = GetQualityMultiplier(quality);
        auto classMultiplierOpt = GetClassMultiplier(itemClass);
        auto subclassMultiplierOpt = GetSubclassMultiplier(itemClass, itemSubclass);

        float combinedMultiplier = qualityMultiplier;
        if (classMultiplierOpt) {
            combinedMultiplier *= classMultiplierOpt.value();
        }
        if (subclassMultiplierOpt) {
            combinedMultiplier *= subclassMultiplierOpt.value();
        }

        float finalPricePerItem = 0.0f;
        float fluctuationFactor = fluctuationDist(gen);

        if (marketPrice > 0) {
            finalPricePerItem = marketPrice * fluctuationFactor;
        }
        else {
            finalPricePerItem = static_cast<float>(price) * combinedMultiplier * fluctuationFactor;
        }

        uint32 stackSize = fields[3].Get<uint32>();
        if (stackSize > 20) {
            stackSize = 20; // or any other logic for stack size
        }

        float totalPriceForStack = finalPricePerItem * static_cast<float>(stackSize);

        AuctionatorItem newItem = AuctionatorItem();
        newItem.itemId = fields[0].Get<uint32>();
        newItem.quantity = 1; // or any logic for quantity
        newItem.buyout = totalPriceForStack;
        newItem.time = 60 * 60 * 12; // or any other auction time
        newItem.stackSize = stackSize;

        // Logging and creating auction
        logDebug("Adding item: " + itemName
            + " with quantity of " + std::to_string(newItem.quantity)
            + " at total price of " + std::to_string(newItem.buyout)
            + " for a stack of " + std::to_string(stackSize)
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
}
