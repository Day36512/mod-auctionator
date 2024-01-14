#include "AuctionatorBidder.h"
#include "Auctionator.h"
#include "ObjectMgr.h"
#include <random>


AuctionatorBidder::AuctionatorBidder(uint32 auctionHouseIdParam, ObjectGuid buyer, AuctionatorConfig* auctionatorConfig)
{
    SetLogPrefix("[AuctionatorBidder] ");
    auctionHouseId = auctionHouseIdParam;
    buyerGuid = buyer;
    ahMgr = sAuctionMgr->GetAuctionsMapByHouseId(auctionHouseId);
    config = auctionatorConfig;
    bidOnOwn = config->bidOnOwn;
}

AuctionatorBidder::~AuctionatorBidder()
{

}

void AuctionatorBidder::SpendSomeCash()
{
    uint32 auctionatorPlayerGuid = buyerGuid.GetRawValue();

    std::string query = R"(
        SELECT
            ah.id
        FROM auctionhouse ah
        WHERE itemowner <> {} AND houseid = {};
    )";

    // for testing we may want to bid on our own auctions.
    // if we do we set the ownerToSkip to 0 so we will pick
    // up all auctions including our own.
    uint32 ownerToSkip = auctionatorPlayerGuid;
    if (bidOnOwn) {
        ownerToSkip = 0;
    }

    QueryResult result = CharacterDatabase.Query(query, ownerToSkip, auctionHouseId);

    if (!result) {
        logInfo("Can't see player auctions at ["
            + std::to_string(auctionHouseId) + "] not from ["
            + std::to_string(auctionatorPlayerGuid) + "], moving on.");
        return;
    }

    if (result->GetRowCount() == 0) {
        logInfo("No player auctions, taking my money elsewhere.");
        return;
    }

    // move our query results into a vector for easier manipulation
    std::vector<uint32> biddableAuctionIds;
    do {
        biddableAuctionIds.push_back(result->Fetch()->Get<uint32>());
    } while(result->NextRow());

    // shuffle our vector to try to inject some randomness
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(
        biddableAuctionIds.begin(),
        biddableAuctionIds.end(),
        std::default_random_engine(seed)
    );

    logInfo("Found " + std::to_string(biddableAuctionIds.size()) + " biddable auctions");

    uint32 purchasePerCycle = GetAuctionsPerCycle();
    uint32 counter = 0;
    uint32 total = biddableAuctionIds.size();

    while(purchasePerCycle > 0 && biddableAuctionIds.size() > 0) {
        counter++;
        AuctionEntry* auction = GetAuctionForPurchase(biddableAuctionIds);

        if (auction == nullptr) {
            return;
        }

        // get our item template for this item, we need some of these details for pricing and such.
        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(auction->item_template);

        logInfo("Considering auction: "
            + itemTemplate->Name1
            + " [AuctionId: " + std::to_string(auction->Id) + "]"
            + " [ItemId: " + std::to_string(itemTemplate->ItemId) + "]"
            + " <> " + std::to_string(counter) + " of "
            + std::to_string(total)
        );

        bool success = false;

        // If this item has a buyout price, let's try to buy it. Otherwise we will
        // see if it's worth bidding on.
        if (auction->buyout > 0) {
            success = BuyoutAuction(auction, itemTemplate);
        } else {
            success = BidOnAuction(auction, itemTemplate);
        }

        if (success) {
            purchasePerCycle--;
            logInfo("Purchase made, remaining: " + std::to_string(purchasePerCycle));
        }
    }
}

AuctionEntry* AuctionatorBidder::GetAuctionForPurchase(std::vector<uint32>& auctionIds)
{
    if (auctionIds.size() == 0) {
        return nullptr;
    }

    uint32 auctionId = auctionIds[0];
    auctionIds.erase(auctionIds.begin());

    logTrace("Auction removed, remaining items: " + std::to_string(auctionIds.size()));

    AuctionEntry* auction = ahMgr->GetAuction(auctionId);
    return auction;
}

bool AuctionatorBidder::BidOnAuction(AuctionEntry* auction, ItemTemplate const* itemTemplate)
{
    // Check if someone has already bid on this auction.
    if (auction->bid) {
        if (auction->bidder == buyerGuid) {
            logInfo("Skipping auction, I have already bid: "
                + std::to_string(auction->bid) + ".");
        }
        else {
            logInfo("Skipping auction, someone else has already bid "
                + std::to_string(auction->bid) + ".");
        }
        return false;
    }

    // Nobody has bidded on this auction, so let's grab its current bid value.
    uint32 currentPrice = auction->startbid;

    // Calculate the standard and increased buy prices.
    uint32 normalBuyPrice = CalculateBuyPrice(auction, itemTemplate, false);
    uint32 increasedBuyPrice = CalculateBuyPrice(auction, itemTemplate, true);

    // Decide if our bid is less than the max amount we want to pay.
    if (currentPrice > normalBuyPrice && currentPrice > increasedBuyPrice) {
        logInfo("Skipping auction ("
            + std::to_string(auction->Id) + "), current price of "
            + std::to_string(currentPrice) + " is higher than both normal ("
            + std::to_string(normalBuyPrice) + ") and increased price ("
            + std::to_string(increasedBuyPrice) + ")");
        return false;
    }

    // Calculate the bid price.
    uint32 bidPrice;
    if (currentPrice <= normalBuyPrice) {
        bidPrice = currentPrice + (normalBuyPrice - currentPrice) / 2;
    }
    else {
        // If current price is above normal but below increased price
        bidPrice = currentPrice + (increasedBuyPrice - currentPrice) / 2;
    }

    // Update the auction with the new bid.
    auction->bidder = buyerGuid;
    auction->bid = bidPrice;

    // Update the database.
    CharacterDatabase.Execute(R"(
        UPDATE
            auctionhouse
        SET
            buyguid = {},
            lastbid = {}.
        WHERE
            id = {}
    )",
        auction->bidder.GetCounter(),
        auction->bid,
        auction->Id);

    logInfo("Bid on auction of "
        + itemTemplate->Name1 + " ["
        + std::to_string(auction->Id) + "] for "
        + std::to_string(bidPrice) + " copper.");

    return true;
}

bool AuctionatorBidder::BuyoutAuction(AuctionEntry* auction, ItemTemplate const* itemTemplate)
{
    // Calculate the normal and 20% increased buy prices.
    uint32 normalPrice = CalculateBuyPrice(auction, itemTemplate, false);
    uint32 increasedPrice = CalculateBuyPrice(auction, itemTemplate, true);

    // Determine if the buyout price is acceptable (less than or equal to normal or increased price).
    if (auction->buyout > normalPrice && auction->buyout > increasedPrice) {
        logInfo("Skipping buyout, price ("
            + std::to_string(auction->buyout) + ") is higher than normal and 20% increased prices ("
            + std::to_string(normalPrice) + " and " + std::to_string(increasedPrice) + ")");
        return false;
    }

    // Proceed with the buyout as usual.
    auto trans = CharacterDatabase.BeginTransaction();
    auction->bidder = buyerGuid;
    auction->bid = auction->buyout;

    sAuctionMgr->SendAuctionSuccessfulMail(auction, trans);
    auction->DeleteFromDB(trans);

    logInfo("Purchased auction of "
        + itemTemplate->Name1 + " ["
        + std::to_string(auction->Id) + "]"
        + "x" + std::to_string(auction->itemCount) + " for "
        + std::to_string(auction->buyout) + " copper."
    );

    sAuctionMgr->RemoveAItem(auction->item_guid);
    ahMgr->RemoveAuction(auction);

    CharacterDatabase.CommitTransaction(trans);

    return true;
}

uint32 AuctionatorBidder::GetAuctionsPerCycle()
{
    switch(auctionHouseId) {
        case AUCTIONHOUSE_ALLIANCE:
            return config->allianceBidder.maxPerCycle;
            break;
        case AUCTIONHOUSE_HORDE:
            return config->hordeBidder.maxPerCycle;
            break;
        case AUCTIONHOUSE_NEUTRAL:
            return config->neutralBidder.maxPerCycle;
            break;
        default:
            return 0;
    }
}

uint32 AuctionatorBidder::CalculateBuyPrice(AuctionEntry* auction, ItemTemplate const* item, bool includeIncrease)
{
    // Get the market price for this item.
    uint32 marketPrice = 0;
    std::string query = R"(
        SELECT
            entry
            , average_price
            , scan_datetime
        FROM mod_auctionator_market_price
        WHERE entry = {}
        ORDER BY scan_datetime DESC
        LIMIT 1
    )";
    QueryResult result = CharacterDatabase.Query(query, item->ItemId);

    if (result) {
        marketPrice = result->Fetch()[1].Get<uint32>();
    }

    // Get the stack size of the item.
    uint32 stackSize = 1;
    if (item->GetMaxStackSize() > 1 && auction->itemCount > 1) {
        stackSize = auction->itemCount;
    }

    // Get the quality multiplier configuration.
    AuctionatorPriceMultiplierConfig multiplierConfig = config->bidderMultipliers;
    uint32 quality = item->Quality;
    float qualityMultiplier = Auctionator::GetQualityMultiplier(multiplierConfig, quality);

    // Determine the price to use.
    uint32 price = 0;
    if (marketPrice > 0) {
        price = marketPrice;
        logInfo("Using Market over Template for bid eval [" + item->Name1 + "] " +
            std::to_string(marketPrice) + " with multiplier of " + std::to_string(qualityMultiplier) + "x");
    }
    else if (item->BuyPrice > 0) {
        price = item->BuyPrice;
    }
    else if (item->SellPrice > 0) {
        price = item->SellPrice * 4; // Using SellPrice x 4 when BuyPrice is not available
    }
    else {
        price = item->ItemId * 3; // Using entry x 3 as a fallback
    }

    // Calculate the base price for this item stack.
    uint32 basePrice = uint32(stackSize * price * qualityMultiplier);

    // Apply a 20% increase if specified
    if (includeIncrease) {
        return static_cast<uint32>(basePrice * 1.20);
    }

    return basePrice;
}

