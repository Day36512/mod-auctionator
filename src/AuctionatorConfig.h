
#ifndef AUCTIONATOR_CONFIG_H
#define AUCTIONATOR_CONFIG_H

#include "Common.h"

struct AuctionatorHouseConfig
{
public:
    uint32 enabled = 0;
    uint32 maxAuctions = 100;
};

struct AuctionatorBidderConfig
{
public:
    uint32 enabled;
    uint32 cycleMinutes;
    uint32 maxPerCycle;
};

struct AuctionatorPriceMultiplierConfig
{
public:
    // Quality multipliers
    float poor = 1.0f;
    float normal = 1.0f;
    float uncommon = 1.0f;
    float rare = 1.0f;
    float epic = 1.0f;
    float legendary = 1.0f;

    // Class multipliers
    float container = 1.0f;
    float weapon = 1.0f;
    float gem = 1.0f;
    float armor = 1.0f;
    float reagent = 1.0f;
    float projectile = 1.0f;
    float tradeGoods = 1.0f;
    float consumables = 1.0f;
    float recipe = 1.0f;
    float quiver = 1.0f;
    float key = 1.0f;
    float miscellaneous = 1.0f;
    float glyph = 1.0f;
};

struct AuctionatorSellerConfig
{
public:
    uint32 queryLimit = 1000;
    uint32 defaultPrice = 10000;
    uint32 auctionsPerRun = 100;
    float fluctuationMin = 0.94f;
    float fluctuationMax = 1.06f;
    uint32 excludePoorQualityItems = 0;
    uint32 prioritizeTradeGoods = 0;
    uint32 excludeVanillaItems = 0;
    uint32 excludeTBCItems = 0;
    uint32 excludeWotLKItems = 0;
};

struct AuctionatorExpansionQualityMultiplierConfig {
    float vanillaPoor = 1.0f;
    float vanillaNormal = 1.0f;
    float vanillaUncommon = 1.0f;
    float vanillaRare = 1.0f;
    float vanillaEpic = 1.0f;
    float vanillaLegendary = 1.0f;

    float tbcPoor = 1.0f;
    float tbcNormal = 1.0f;
    float tbcUncommon = 1.0f;
    float tbcRare = 1.0f;
    float tbcEpic = 1.0f;
    float tbcLegendary = 1.0f;

    float wotlkPoor = 1.0f;
    float wotlkNormal = 1.0f;
    float wotlkUncommon = 1.0f;
    float wotlkRare = 1.0f;
    float wotlkEpic = 1.0f;
    float wotlkLegendary = 1.0f;

};

class AuctionatorConfig
{
public:
    AuctionatorConfig()
        : isEnabled(false),
        characterId(0),
        characterGuid(0),
        auctionHouseId(7),
        hordeSeller(),
        allianceSeller(),
        neutralSeller(),
        allianceBidder(),
        hordeBidder(),
        neutralBidder(),
        sellerMultipliers(),
        bidderMultipliers(),
        sellerConfig(),
        expansionQualityMultipliers(),
        bidOnOwn(0),
        excludeGems(false),
        excludeEnchants(false),
        excludeTradeGoods(false),
        excludeGlyphs(false)
    {}
    bool isEnabled;
    uint32 characterId;
    uint32 characterGuid;
    uint32 auctionHouseId;

    AuctionatorHouseConfig hordeSeller;
    AuctionatorHouseConfig allianceSeller;
    AuctionatorHouseConfig neutralSeller;

    AuctionatorBidderConfig allianceBidder;
    AuctionatorBidderConfig hordeBidder;
    AuctionatorBidderConfig neutralBidder;

    AuctionatorPriceMultiplierConfig sellerMultipliers;
    AuctionatorPriceMultiplierConfig bidderMultipliers;

    AuctionatorSellerConfig sellerConfig;

    AuctionatorExpansionQualityMultiplierConfig expansionQualityMultipliers;

    uint32 bidOnOwn;

    // Dinkle New fields for excluding specific item types
    bool excludeGems;
    bool excludeEnchants;
    bool excludeTradeGoods;
    bool excludeGlyphs;
};
#endif // AUCTIONATOR_CONFIG_H

