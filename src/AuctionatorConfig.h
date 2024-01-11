
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
    float potion = 1.0f;
    float elixir = 1.0f;
    float flask = 1.0f;
    float scroll = 1.0f;
    float foodDrink = 1.0f;
    float itemEnhancement = 1.0f;
    float bandage = 1.0f;
    float otherConsumable = 1.0f;
    float container = 1.0f;
    float weapon = 1.0f;
    float gem = 1.0f;
    float armor = 1.0f;
    float reagent = 1.0f;
    float projectile = 1.0f;
    float tradeGoods = 1.0f;
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
        uint32 defaultPrice = 100000;
        uint32 auctionsPerRun = 100;
};

class AuctionatorConfig
{
    private:

    public:
        AuctionatorConfig() {};
        bool isEnabled = false;
        uint32 characterId = 0;
        uint32 characterGuid = 0;
        uint32 auctionHouseId = 7;

        AuctionatorHouseConfig hordeSeller;
        AuctionatorHouseConfig allianceSeller;
        AuctionatorHouseConfig neutralSeller;

        AuctionatorBidderConfig allianceBidder;
        AuctionatorBidderConfig hordeBidder;
        AuctionatorBidderConfig neutralBidder;

        AuctionatorPriceMultiplierConfig sellerMultipliers;
        AuctionatorPriceMultiplierConfig bidderMultipliers;

        AuctionatorSellerConfig sellerConfig;

        uint32 bidOnOwn = 0;
        // Dinkle New fields for excluding specific item types
        bool excludeGems = false;
        bool excludeEnchants = false;
        bool excludeTradeGoods = false;
        bool excludeGlyphs = false;

};

#endif
