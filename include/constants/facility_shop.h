#ifndef GUARD_CONSTANTS_FACILITY_SHOP_H
#define GUARD_CONSTANTS_FACILITY_SHOP_H

// Ten Gauntlets shop (shop-spec.md). Split out from include/facility_shop.h
// so scripts can see these too - data/event_scripts.s only pulls in
// constants/*.h headers.

enum
{
    FACILITY_SHOP_TIER_PREMIUM,
    FACILITY_SHOP_TIER_STRONG,
    FACILITY_SHOP_TIER_STANDARD,
    FACILITY_SHOP_TIER_BUDGET,
};

// FacilityShopSellMonPrompt()'s result - SELL_MON_OK means the confirm
// prompt should show; everything else is a reason to refuse with its own
// message instead of the generic "can't sell that" one.
enum
{
    SELL_MON_OK,
    SELL_MON_NOT_SELLABLE,
    SELL_MON_HOLDING_ITEM,
    SELL_MON_NOT_ENOUGH_OWNED,
};

// FacilityShopSellMonPrompt() also refuses the Broker's loaners.
#define SELL_MON_BROKER_LOAN (SELL_MON_NOT_ENOUGH_OWNED + 1)

// The Broker (broker-spec.md). FacilityBrokerCheck()'s result.
enum
{
    BROKER_OK,
    BROKER_RUN_ACTIVE,
    BROKER_DEAL_USED,
    BROKER_NOTHING_LEFT,
};

// FacilityBrokerGetLoanOutcome()'s result, after a run ends.
enum
{
    BROKER_LOAN_NONE,
    BROKER_LOAN_KEPT,
    BROKER_LOAN_COLLECTED,
};

#endif // GUARD_CONSTANTS_FACILITY_SHOP_H
