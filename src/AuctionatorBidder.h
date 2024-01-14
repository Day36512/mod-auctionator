#ifndef AUCTIONATORBIDDER_H
#define AUCTIONATORBIDDER_H

#include "Auctionator.h"
#include "AuctionatorBase.h"
#include "ObjectMgr.h"

class AuctionatorBidder : AuctionatorBase
{
private:
    uint32 auctionHouseId;
    AuctionHouseObject* ahMgr;
    ObjectGuid buyerGuid;
    AuctionatorConfig* config;
    uint32 bidOnOwn = 0;
    uint32 GetAuctionsPerCycle();

public:
    AuctionatorBidder(uint32 auctionHouseIdParam, ObjectGuid buyer, AuctionatorConfig* auctionatorConfig);
    ~AuctionatorBidder();
    void SpendSomeCash();
    AuctionEntry* GetAuctionForPurchase(std::vector<uint32>& biddableAuctionIds);

    bool BidOnAuction(AuctionEntry* auction, ItemTemplate const* itemTemplate);
    bool BuyoutAuction(AuctionEntry* auction, ItemTemplate const* itemTemplate);

    // Updated function signature with an additional parameter
    uint32 CalculateBuyPrice(AuctionEntry* auction, ItemTemplate const* item, bool includeIncrease);
};

#endif  //AUCTIONATORBIDDER_H
