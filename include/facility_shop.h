#ifndef GUARD_FACILITY_SHOP_H
#define GUARD_FACILITY_SHOP_H

#include "constants/facility_shop.h"

// Ten Gauntlets shop, replacing the vanilla Battle Points vendors in the
// Exchange Service Corner. See shop-spec.md and shop-unlock-b2.md. Currency
// is FP (gSaveBlock3Ptr->facility.progress.fp), not Battle Points or money.
//
// FP get/take/give all follow the same gSpecialVar_0x8004-as-amount
// convention the vanilla BP vendor specials use
// (TakeFrontierBattlePoints() in src/field_specials.c) - scripts do
// `setvar VAR_0x8004, <amount>` before calling.
void FacilityShopGetFP(void);
void FacilityShopTakeFP(void);
void FacilityShopGiveFP(void);

// ----------------------------------------------------------------------------
// Dynamic menu staging (src/facility_shop.c's file header has the full
// rationale). Each "Build" special filters its master data by unlock
// progress and stages the result; the calling script then shows
// SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC and reads the chosen row with
// FacilityShopSelectRow. field_specials.c reads the staged rows directly
// through the four getters below while the list is on screen (name/price
// per visible row, description for the sidebar).
// ----------------------------------------------------------------------------

void FacilityShopBuildConsumablesMenu(void);
void FacilityShopBuildHeldItemsMenu(void);
// gSpecialVar_Result = FALSE if no Mega Stone is unlocked yet.
void FacilityShopBuildMegaStonesMenu(void);

// The Pokemon keeper's first screen - one row per unlocked gauntlet's shop
// wave plus "Sell a Pokemon". gSpecialVar_0x8004 = chosen row index in;
// FacilityShopSelectGauntletRow's gSpecialVar_Result = TRUE means the player
// picked Sell (go straight to the sell flow), FALSE means the wave to browse
// is now remembered internally and the caller should show tier-select next.
void FacilityShopBuildGauntletMenu(void);
void FacilityShopSelectGauntletRow(void);

// gSpecialVar_0x8009 = FACILITY_SHOP_TIER_* in. gSpecialVar_Result = TRUE if
// a type-filter menu was staged instead of the species list (too many
// unlocked mons in this tier to browse flat) - show that menu, feed the
// chosen row to FacilityShopSelectMonType, then show the list again. FALSE
// means the species list is already staged and ready to show.
void FacilityShopBuildMonTierList(void);
// gSpecialVar_0x8004 = chosen row index from the type-filter menu.
void FacilityShopSelectMonType(void);

// gSpecialVar_0x8004 = chosen row index into whichever list is currently
// staged. Out: gSpecialVar_0x8009 = species/item id, VAR_0x8008 = price,
// STR_VAR_1 = name (for the confirm message).
void FacilityShopSelectRow(void);

u16 FacilityShopGetMenuCount(void);
const u8 *FacilityShopGetMenuRowName(u16 index);
u16 FacilityShopGetMenuRowPrice(u16 index);
const u8 *FacilityShopGetMenuRowDescription(u16 index);
bool8 FacilityShopMenuHasDescriptions(void);

// Buys the species currently in gSpecialVar_0x8009 for VAR_0x8008 FP,
// already confirmed by the caller. Gives it to the party if there's room,
// otherwise the PC (same as any other gift mon) - see MON_GIVEN_TO_PARTY /
// MON_GIVEN_TO_PC / MON_CANT_GIVE in gSpecialVar_Result.
void FacilityShopBuyMon(void);

// Sell-back flow. gSpecialVar_0x8004 = party slot, from `special
// ChoosePartyMon`. FacilityShopSellMonPrompt looks the slot's species up in
// the master tier tables (any tier, any unlock state - see the comment on
// FindMonTierPrice in src/facility_shop.c) and sets VAR_0x8008 = 50% sell
// price, STR_VAR_1 = species name, gSpecialVar_Result = FALSE if the species
// isn't in any tier (nothing to offer - the mon can't be sold here).
// FacilityShopSellMon then actually removes the mon and pays out, once the
// caller has confirmed.
void FacilityShopSellMonPrompt(void);
void FacilityShopSellMon(void);

// FP balance popup. Show it once when a keeper is greeted, Update it after
// every FacilityShopTakeFP/GiveFP so it doesn't go stale mid-visit, Close it
// on the way out (BattleFrontier_ExchangeServiceCorner_EventScript_
// ClerkGoodbyeFP in data/maps/BattleFrontier_ExchangeServiceCorner/
// scripts.inc does all three).
void ShowFacilityFPWindow(void);
void UpdateFacilityFPWindow(void);
void CloseFacilityFPWindow(void);

// Item/mon description sidebar - Consumables keeper only, see
// FacilityShopMenuHasDescriptions(). Show once when the keeper is greeted,
// Update it (gSpecialVar_0x8004 = selected row) every time the cursor moves,
// Close it on the way out - mirrors the FP window's three-special shape.
void ShowFacilityShopDescriptionWindow(void);
void UpdateFacilityShopDescriptionWindow(void);
void CloseFacilityShopDescriptionWindow(void);

// Called on the way out of any keeper interaction (see ClerkGoodbyeFP in
// data/maps/BattleFrontier_ExchangeServiceCorner/scripts.inc) so sMenuRows
// never survives idle between visits. It has to be freed before the player
// can possibly leave, not deferred to the next visit's Build call - walking
// away and back triggers at least one map transition, and every map
// transition calls MoveSaveBlocks_ResetHeap() (src/overworld.c), which wipes
// the entire heap's allocator bookkeeping back to one free block. A pointer
// left dangling in sMenuRows across that reset looks fine until freed, then
// trips malloc.c's double-free assertion on an unrelated later allocation -
// this was a real, confirmed bug, not hypothetical.
void FacilityShopFreeMenuRows(void);

// ----------------------------------------------------------------------------
// The Broker (Lounge 3) - see broker-spec.md. Sells one piece of the next
// gauntlet's shop wave per gauntlet: an item outright at 1.5x, or a Pokemon
// on loan at half price. A loaner is kept if the player clears that
// gauntlet and collected (held item returned) if a run of it ends without
// clearing it.
// ----------------------------------------------------------------------------

// gSpecialVar_Result = BROKER_OK / _RUN_ACTIVE / _DEAL_USED / _NOTHING_LEFT.
void FacilityBrokerCheck(void);
// Stage three random picks from the next wave (fixed per gauntlet - seeded
// from the gauntlet and the player's trainer ID). gSpecialVar_Result = rows
// staged. The caller then uses the shop's own dynamic menu and
// FacilityShopSelectRow, exactly like a keeper.
void FacilityBrokerBuildItemMenu(void);
void FacilityBrokerBuildMonMenu(void);
// Marks this gauntlet's deal as spent.
void FacilityBrokerMarkDealUsed(void);
// Loans the species in gSpecialVar_0x8009. gSpecialVar_Result =
// MON_GIVEN_TO_PARTY / MON_GIVEN_TO_PC / MON_CANT_GIVE; marks the deal spent
// unless MON_CANT_GIVE.
void FacilityBrokerLoanMon(void);
// Called by FacilityCompleteGauntlet (kept == TRUE) and FacilityAbandonRun
// (kept == FALSE) in src/facility.c.
void FacilityBrokerResolveLoans(bool8 kept);
// After a run ends: gSpecialVar_Result = BROKER_LOAN_NONE / _KEPT /
// _COLLECTED, gStringVar1 = the loaner's species name.
void FacilityBrokerGetLoanOutcome(void);

#endif // GUARD_FACILITY_SHOP_H
