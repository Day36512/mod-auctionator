#ifndef AUCTIONATORSELLER_H
#define AUCTIONATORSELLER_H

#include "Auctionator.h"
#include "AuctionHouseMgr.h"
#include <optional>

class AuctionatorSeller : public AuctionatorBase {
private:
    Auctionator* nator;
    uint32 auctionHouseId;
    AuctionHouseObject* ahMgr;

    float GetQualityMultiplier(uint32 quality);
    std::optional<float> GetClassMultiplier(uint32 itemClass);

    float GetVanillaQualityMultiplier(uint32 quality);
    float GetTBCQualityMultiplier(uint32 quality);
    float GetWotLKQualityMultiplier(uint32 quality);

public:
    AuctionatorSeller(Auctionator* natorParam, uint32 auctionHouseIdParam);
    ~AuctionatorSeller();
    void LetsGetToIt(uint32 maxCount, uint32 houseId);
};

#endif  // AUCTIONATORSELLER_H
