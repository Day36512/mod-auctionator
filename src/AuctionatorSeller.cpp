#include "Auctionator.h"
#include "AuctionHouseMgr.h"
#include "AuctionatorSeller.h"
#include "Item.h"
#include "DatabaseEnv.h"
#include "PreparedStatement.h"
#include <random>
#include <optional>

AuctionatorSeller::AuctionatorSeller(Auctionator* natorParam, uint32 auctionHouseIdParam) {
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

float AuctionatorSeller::GetVanillaQualityMultiplier(uint32 quality) {
    switch (quality) {
    case 0: return nator->config->expansionQualityMultipliers.vanillaPoor;
    case 1: return nator->config->expansionQualityMultipliers.vanillaNormal;
    case 2: return nator->config->expansionQualityMultipliers.vanillaUncommon;
    case 3: return nator->config->expansionQualityMultipliers.vanillaRare;
    case 4: return nator->config->expansionQualityMultipliers.vanillaEpic;
    case 5: return nator->config->expansionQualityMultipliers.vanillaLegendary;
    default: return 1.0f;  // Default multiplier for unexpected quality values
    }
}

float AuctionatorSeller::GetTBCQualityMultiplier(uint32 quality) {
    switch (quality) {
    case 0: return nator->config->expansionQualityMultipliers.tbcPoor;
    case 1: return nator->config->expansionQualityMultipliers.tbcNormal;
    case 2: return nator->config->expansionQualityMultipliers.tbcUncommon;
    case 3: return nator->config->expansionQualityMultipliers.tbcRare;
    case 4: return nator->config->expansionQualityMultipliers.tbcEpic;
    case 5: return nator->config->expansionQualityMultipliers.tbcLegendary;
    default: return 1.0f;  // Default multiplier for unexpected quality values
    }
}

float AuctionatorSeller::GetWotLKQualityMultiplier(uint32 quality) {
    switch (quality) {
    case 0: return nator->config->expansionQualityMultipliers.wotlkPoor;
    case 1: return nator->config->expansionQualityMultipliers.wotlkNormal;
    case 2: return nator->config->expansionQualityMultipliers.wotlkUncommon;
    case 3: return nator->config->expansionQualityMultipliers.wotlkRare;
    case 4: return nator->config->expansionQualityMultipliers.wotlkEpic;
    case 5: return nator->config->expansionQualityMultipliers.wotlkLegendary;
    default: return 1.0f;  // Default multiplier for unexpected quality values
    }
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
    if (nator->config->sellerConfig.excludePoorQualityItems == 1) {
        additionalConditions += " AND it.quality != 0"; 
    }

    // Set the maximum number of items to query for. Changing this <might>
    // affect how random our auctoin listing are at the cost of memory/cpu
    // but it is something i need to test.
    uint32 queryLimit = nator->config->sellerConfig.queryLimit;

    // Get the name of the character database so we can do our join below.
    std::string characterDbName = CharacterDatabase.GetConnectionInfo()->database;

    std::string orderByClause = " ORDER BY RAND()"; // Default random order
    if (nator->config->sellerConfig.prioritizeTradeGoods == 1) {
        orderByClause = " ORDER BY CASE WHEN it.class = 7 THEN 0 ELSE 1 END, RAND()";
    }
    
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
            , it.ItemLevel
            , it.RequiredLevel
            , it.SellPrice
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
            )" + additionalConditions + orderByClause + R"(
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
        count++;
        Field* fields = result->Fetch();
        std::string itemName = fields[1].Get<std::string>();

        uint32 itemClass = fields[6].Get<uint32>();
        uint32 stackable = fields[3].Get<uint32>();
        uint32 stackSize;

        // Set stack size to 1000 for projectile class, otherwise calculate based on stackable value
        if (itemClass == 6) { // 6 is the class ID for projectiles
            stackSize = 1000;
        }
        else if (stackable >= 20) {
            std::uniform_int_distribution<> stackDist(1, 20);
            stackSize = stackDist(gen);
        }
        else {
            stackSize = stackable; // Use the stackable value directly
        }

        uint32 quality = fields[4].Get<uint32>();
        uint32 itemSubclass = fields[7].Get<uint32>();
        uint32 price = fields[2].Get<uint32>();
        uint32 marketPrice = fields[5].Get<uint32>();
        uint32 itemLevel = fields[8].Get<uint32>();
        if (itemLevel == 0 || itemLevel == 1) {
            itemLevel = fields[9].Get<uint32>(); // Use RequiredLevel as fallback

            // Adjust the expansion range based on RequiredLevel
            if (itemLevel <= 60) { // Vanilla
                itemLevel = 92; // Set a value within Vanilla range
            }
            else if (itemLevel <= 70) { // TBC
                itemLevel = 164; // Set a value within TBC range
            } // No change needed for WotLK, as 71+ already falls in this range
        }

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

        // Determine expansion-specific and quality-based multiplier
        float expansionQualityMultiplier = 1.0f;
        if (itemLevel >= 1 && itemLevel <= 92) { // Vanilla
            expansionQualityMultiplier = GetVanillaQualityMultiplier(quality);
        }
        else if (itemLevel >= 93 && itemLevel <= 164) { // TBC
            expansionQualityMultiplier = GetTBCQualityMultiplier(quality);
        }
        else if (itemLevel >= 165) { // WotLK
            expansionQualityMultiplier = GetWotLKQualityMultiplier(quality);
        }

        float finalPricePerItem = 0.0f;
        float fluctuationFactor = fluctuationDist(gen);

        // Use BuyPrice if available; otherwise, fallback to 4x SellPrice or 3x entry value
        uint32 itemId = fields[0].Get<uint32>(); // Assuming 'fields[0]' is the item's entry
        uint32 basePrice = (price > 0) ? price : (fields[10].Get<uint32>() > 0 ? 4 * fields[10].Get<uint32>() : 3 * itemId);

        if (marketPrice > 0) {
            finalPricePerItem = marketPrice * fluctuationFactor;
        }
        else {
            finalPricePerItem = static_cast<float>(basePrice) * qualityMultiplier *
                (classMultiplierOpt ? classMultiplierOpt.value() : 1.0f) *
                (subclassMultiplierOpt ? subclassMultiplierOpt.value() : 1.0f) *
                expansionQualityMultiplier * fluctuationFactor;
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
