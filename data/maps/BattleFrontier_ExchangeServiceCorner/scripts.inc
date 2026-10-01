BattleFrontier_ExchangeServiceCorner_MapScripts::
	.byte 0

@ ============================================================================
@ Ten Gauntlets shop - see shop-spec.md and shop-unlock-b2.md. Replaces the
@ vanilla Battle Points vendors with four FP-spending keepers.
@
@ Every keeper's list is now one dynamically-built menu
@ (SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC) instead of a chain of hand-paginated
@ pages - src/facility_shop.c's "Build" specials filter the master data by
@ unlock progress (and, for Pokemon, by gauntlet wave, then tier, then
@ optionally by type) and stage the result; FacilityShopSelectRow reads back
@ whichever row got picked. See that file's header comment for the full
@ rationale. This is what lets a keeper's stock grow across the remaining
@ unlocks without a new SCROLL_MULTI_TEN_GAUNTLETS_* menu id or a new
@ page-handling label each time.
@ ============================================================================

BattleFrontier_ExchangeServiceCorner_EventScript_ShopClosedMidRun::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ShopClosedMidRun, MSGBOX_DEFAULT
	release
	end

@ Ten Gauntlets: FacilityShopFreeMenuRows here (not deferred to the next
@ visit's Build call) matters more than it looks - see the comment on it in
@ include/facility_shop.h. Leaving the shop guarantees at least one map
@ transition before the player can come back, and every map transition
@ resets the whole heap's allocator bookkeeping (MoveSaveBlocks_ResetHeap(),
@ src/overworld.c) - a real, confirmed double-free bug if sMenuRows is still
@ holding a pointer when that happens.
BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbyeFP::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ThankYouVisitWithFP, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	special FacilityShopFreeMenuRows
	release
	end

@ ----------------------------------------------------------------------------
@ Keeper 1 - Consumables (berries)
@ ----------------------------------------------------------------------------

BattleFrontier_ExchangeServiceCorner_EventScript_ConsumablesKeeper::
	lock
	faceplayer
	specialvar VAR_RESULT, IsFacilityRunActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_ShopClosedMidRun
	specialvar VAR_RESULT, IsFrontierPOSDown
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_POSDown
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomeConsumables, MSGBOX_DEFAULT
	special ShowFacilityFPWindow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseConsumable
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseConsumable::
	special FacilityShopBuildConsumablesMenu
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ConsumablesGoodbye
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectRow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyConsumable
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ConsumablesGoodbye::
	special CloseFacilityShopDescriptionWindow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbyeFP
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyConsumable::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmPurchase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseConsumable
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPConsumable
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_BagFullConsumable
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	additem VAR_0x8009
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourItem, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseConsumable
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPConsumable::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughFP, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseConsumable
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BagFullConsumable::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseConsumable
	end

@ ----------------------------------------------------------------------------
@ Keeper 2 - Held items
@ ----------------------------------------------------------------------------

BattleFrontier_ExchangeServiceCorner_EventScript_HeldItemsKeeper::
	lock
	faceplayer
	specialvar VAR_RESULT, IsFacilityRunActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_ShopClosedMidRun
	specialvar VAR_RESULT, IsFrontierPOSDown
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_POSDown
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomeHeldItems, MSGBOX_DEFAULT
	special ShowFacilityFPWindow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHeldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHeldItem::
	special FacilityShopBuildHeldItemsMenu
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbyeFP
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectRow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyHeldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyHeldItem::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmPurchase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHeldItem
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPHeldItem
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_BagFullHeldItem
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	additem VAR_0x8009
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourItem, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHeldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPHeldItem::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughFP, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHeldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BagFullHeldItem::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHeldItem
	end

@ ----------------------------------------------------------------------------
@ Keeper 3 - Mega Stones. Opens clearing gauntlet 4 (gauntlet-05.md). Until
@ then FacilityShopBuildMegaStonesMenu finds nothing unlocked and the keeper
@ just says "not yet", so the counter reads as closed rather than broken.
@ Same purchase flow as Keeper 2 otherwise.
@
@ Also a safety net for the Mega Ring: the gauntlet 4 attendant gives it
@ (Facility_B4_GauntletComplete), but if a save ever reaches this counter
@ with stones unlocked and no ring, the keeper hands one over - stones are
@ useless without it (CanMegaEvolve() in src/battle_util.c).
@ ----------------------------------------------------------------------------

BattleFrontier_ExchangeServiceCorner_EventScript_MegaStoneKeeper::
	lock
	faceplayer
	specialvar VAR_RESULT, IsFacilityRunActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_ShopClosedMidRun
	specialvar VAR_RESULT, IsFrontierPOSDown
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_POSDown
	special FacilityShopBuildMegaStonesMenu
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_MegaStonesComingLater
	checkitem ITEM_MEGA_RING
	call_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_GiveMissingMegaRing
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomeMegaStones, MSGBOX_DEFAULT
	special ShowFacilityFPWindow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMegaStone
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MegaStonesComingLater::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_MegaStonesComingLater, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_GiveMissingMegaRing::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_YouNeedAMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	return

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMegaStone::
	special FacilityShopBuildMegaStonesMenu
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbyeFP
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectRow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyMegaStone
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyMegaStone::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmPurchase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMegaStone
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPMegaStone
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_BagFullMegaStone
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	additem VAR_0x8009
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourItem, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMegaStone
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPMegaStone::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughFP, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMegaStone
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BagFullMegaStone::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMegaStone
	end

@ ----------------------------------------------------------------------------
@ Keeper 4 - Pokemon. Choose a gauntlet's wave first, then a tier within it,
@ or sell one back from the party for FP. A tier with more mons in that one
@ wave than fit comfortably in one browse gets a type-filter menu first
@ (FacilityShopBuildMonTierList decides which, based on the live count for
@ that wave), otherwise the species list shows directly.
@ ----------------------------------------------------------------------------

BattleFrontier_ExchangeServiceCorner_EventScript_PokemonKeeper::
	lock
	faceplayer
	specialvar VAR_RESULT, IsFacilityRunActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_ShopClosedMidRun
	specialvar VAR_RESULT, IsFrontierPOSDown
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_PokemonKeeperPOSDown
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePokemon, MSGBOX_DEFAULT
	special ShowFacilityFPWindow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet::
	special FacilityShopBuildGauntletMenu
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbyeFP
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectGauntletRow
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonToSell
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonTier
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonTier::
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_MON_TIER_SELECT
	special ShowScrollableMultichoice
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_GoPremium
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_GoStrong
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_GoStandard
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_GoBudget
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

BattleFrontier_ExchangeServiceCorner_EventScript_GoPremium::
	setvar VAR_0x8009, FACILITY_SHOP_TIER_PREMIUM
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfTier
	end

BattleFrontier_ExchangeServiceCorner_EventScript_GoStrong::
	setvar VAR_0x8009, FACILITY_SHOP_TIER_STRONG
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfTier
	end

BattleFrontier_ExchangeServiceCorner_EventScript_GoStandard::
	setvar VAR_0x8009, FACILITY_SHOP_TIER_STANDARD
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfTier
	end

BattleFrontier_ExchangeServiceCorner_EventScript_GoBudget::
	setvar VAR_0x8009, FACILITY_SHOP_TIER_BUDGET
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfTier
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfTier::
	special FacilityShopBuildMonTierList
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonType
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonType::
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonTier
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectMonType
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList::
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonTier
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectRow
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyMon
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ConfirmBuyMon::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmPurchase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPForMon
	special FacilityShopBuyMon
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BattleFrontier_ExchangeServiceCorner_EventScript_NoRoomForMon
	copyvar VAR_TEMP_1, VAR_RESULT
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	playse SE_SHOP
	goto_if_eq VAR_TEMP_1, MON_GIVEN_TO_PC, BattleFrontier_ExchangeServiceCorner_EventScript_GotMonToPC
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourMon, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	end

BattleFrontier_ExchangeServiceCorner_EventScript_GotMonToPC::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_SentMonToPC, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NoRoomForMon::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_NoRoomForMon, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NotEnoughFPForMon::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughFP, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonOfList
	end

@ Ten Gauntlets: FacilityShopFreeMenuRows before ChoosePartyMon, not just on
@ the way out via ClerkGoodbyeFP - see the comment on it in
@ include/facility_shop.h. ChoosePartyMon is a full-screen party menu swap,
@ and returning from ANY full-screen menu to the field runs
@ ResetMirageTowerAndSaveBlockPtrs() -> MoveSaveBlocks_ResetHeap()
@ (src/overworld.c), which resets the whole heap - the same heap reset that
@ used to only get blamed on map transitions. If the player browsed a tier's
@ species list before deciding to sell instead, sMenuRows would already be
@ staged, and selling would silently invalidate it mid-interaction, before
@ ClerkGoodbyeFP ever runs.
@
@ Sell lives on the gauntlet-select screen now (it isn't tied to any one
@ gauntlet's wave), so every exit from this flow returns to ChooseMonBuilding,
@ not ChooseMonTier.
BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonToSell::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, 1, BattleFrontier_ExchangeServiceCorner_EventScript_CantSellLastMon
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WhichMonToSell, MSGBOX_DEFAULT
	special FacilityShopFreeMenuRows
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	special FacilityShopSellMonPrompt
	switch VAR_RESULT
	case SELL_MON_NOT_SELLABLE, BattleFrontier_ExchangeServiceCorner_EventScript_CantSellMon
	case SELL_MON_HOLDING_ITEM, BattleFrontier_ExchangeServiceCorner_EventScript_CantSellHoldingItem
	case SELL_MON_NOT_ENOUGH_OWNED, BattleFrontier_ExchangeServiceCorner_EventScript_CantSellNotEnoughOwned
	buffernumberstring STR_VAR_2, VAR_0x8008
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmSell, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	special FacilityShopSellMon
	special UpdateFacilityFPWindow
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_SoldMon, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CantSellLastMon::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_CantSellLastMon, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CantSellMon::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_CantSellThatMon, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CantSellHoldingItem::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_CantSellHoldingItem, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CantSellNotEnoughOwned::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_CantSellNotEnoughOwned, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseMonGauntlet
	end

@ ----------------------------------------------------------------------------
@ Ambient NPCs, unrelated to the shop. Their old lines referenced the vanilla
@ doll/BP shop this replaces, so they've been swapped for generic flavor.
@ ----------------------------------------------------------------------------

BattleFrontier_ExchangeServiceCorner_EventScript_Man::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ManFlavor, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Sailor::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokefanF::
	lock
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_RichBoy::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_RichBoyFlavor, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Girl::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_MoreFPForClearingGauntlets, MSGBOX_NPC
	end

@ ----------------------------------------------------------------------------
@ Text
@ ----------------------------------------------------------------------------

BattleFrontier_ExchangeServiceCorner_Text_ShopClosedMidRun:
	.string "Come back once your current run is\n"
	.string "over - I can't do business with you\l"
	.string "mid-challenge.$"

BattleFrontier_ExchangeServiceCorner_Text_WelcomeConsumables:
	.string "Welcome to the EXCHANGE SERVICE\n"
	.string "CORNER.\p"
	.string "I deal in berries - the kind that\n"
	.string "activate on their own once a POKéMON\l"
	.string "is hurt badly enough.\p"
	.string "Careful which one you pick, though -\n"
	.string "some of these confuse a POKéMON whose\l"
	.string "nature doesn't suit them.$"

BattleFrontier_ExchangeServiceCorner_Text_WelcomeHeldItems:
	.string "Welcome to the EXCHANGE SERVICE\n"
	.string "CORNER.\p"
	.string "Everything I sell is a hold item -\n"
	.string "yours to keep, and it comes back after\l"
	.string "every battle, win or lose.$"

BattleFrontier_ExchangeServiceCorner_Text_MegaStonesComingLater:
	.string "This counter's for MEGA STONES,\n"
	.string "but I haven't got a thing to sell\l"
	.string "you yet.\p"
	.string "Come back once you've made it\n"
	.string "further through the gauntlets. I\l"
	.string "hear this counter fills up fast\l"
	.string "after the TOWER.$"

BattleFrontier_ExchangeServiceCorner_Text_WelcomeMegaStones:
	.string "Welcome to the MEGA STONE counter.\p"
	.string "Give a POKéMON its own stone and it\n"
	.string "can Mega Evolve - once per battle.$"

BattleFrontier_ExchangeServiceCorner_Text_YouNeedAMegaRing:
	.string "Hold on - you don't have a MEGA RING?\n"
	.string "These stones are no use without one.\l"
	.string "Here, take this.$"

BattleFrontier_ExchangeServiceCorner_Text_WelcomePokemon:
	.string "Welcome!\p"
	.string "I can sell you a POKéMON outright, or\n"
	.string "buy one back off of you for half what\l"
	.string "it's worth.\p"
	.string "Take your pick.$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmPurchase:
	.string "You've chosen the {STR_VAR_1}.\n"
	.string "Is that correct?$"

BattleFrontier_ExchangeServiceCorner_Text_HereIsYourItem:
	.string "Here is your item!$"

BattleFrontier_ExchangeServiceCorner_Text_HereIsYourMon:
	.string "Here's your {STR_VAR_1}!$"

BattleFrontier_ExchangeServiceCorner_Text_SentMonToPC:
	.string "Your party's full, so I've sent your\n"
	.string "{STR_VAR_1} to your PC instead.$"

BattleFrontier_ExchangeServiceCorner_Text_NoRoomForMon:
	.string "I'm so sorry…\n"
	.string "You haven't got room for it anywhere,\l"
	.string "not even in your PC…$"

BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughFP:
	.string "I'm so sorry…\n"
	.string "You don't have enough FP…$"

BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt:
	.string "I'm so sorry…\n"
	.string "You don't have space to hold it…$"

BattleFrontier_ExchangeServiceCorner_Text_ThankYouVisitWithFP:
	.string "Thank you very much.\p"
	.string "Please visit us again once you've\n"
	.string "earned more FP.$"

BattleFrontier_ExchangeServiceCorner_Text_WhichMonToSell:
	.string "Which POKéMON would you like to\n"
	.string "sell back?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmSell:
	.string "I'll give you {STR_VAR_2} FP for your\n"
	.string "{STR_VAR_1}. Is that all right?$"

BattleFrontier_ExchangeServiceCorner_Text_SoldMon:
	.string "Pleasure doing business with you!$"

BattleFrontier_ExchangeServiceCorner_Text_CantSellLastMon:
	.string "I can't take your last POKéMON off\n"
	.string "your hands - you'd have nothing left\l"
	.string "to battle with!$"

BattleFrontier_ExchangeServiceCorner_Text_CantSellThatMon:
	.string "I'm so sorry…\n"
	.string "That's not one I know how to price…$"

BattleFrontier_ExchangeServiceCorner_Text_CantSellHoldingItem:
	.string "Whoa, hold on! That POKéMON's holding\n"
	.string "an item - if I buy it, the item goes\l"
	.string "with it, gone for good.\p"
	.string "Take the item off first, then come\n"
	.string "back if you still want to sell.$"

BattleFrontier_ExchangeServiceCorner_Text_CantSellNotEnoughOwned:
	.string "I can't buy that one off you - you\n"
	.string "don't have enough POKéMON to spare.\p"
	.string "Come back once you've got more than\n"
	.string "six to your name, between your party\l"
	.string "and your boxes.$"

BattleFrontier_ExchangeServiceCorner_Text_ManFlavor:
	.string "This whole corner used to be nothing\n"
	.string "but dolls and cushions.\p"
	.string "Berries, hold items, POKéMON for FP…\n"
	.string "Now that's more like it.$"

BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher:
	.string "Leftovers, a resist berry, a\n"
	.string "CHOICE SCARF… The right item is\l"
	.string "worth more than a new POKéMON\l"
	.string "sometimes.\p"
	.string "Just buy them here, all right? Not\n"
	.string "from that shady type who hangs\l"
	.string "around the houses out past the\l"
	.string "ARENA, on the far east side.\p"
	.string "Nobody knows where he gets his\n"
	.string "stuff!$"

BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant:
	.string "Leave it to your mommy!\p"
	.string "If it's anything you want, I'll go\n"
	.string "through anything to get it, honey!$"

BattleFrontier_ExchangeServiceCorner_Text_RichBoyFlavor:
	.string "Do you know how much FP I've spent in\n"
	.string "here already?\p"
	.string "Neither do I! Ha ha ha!$"

BattleFrontier_ExchangeServiceCorner_Text_MoreFPForClearingGauntlets:
	.string "Did you know?\p"
	.string "Every battle you win is worth the\n"
	.string "same FP, win or lose the run\l"
	.string "later. It's clearing a whole\l"
	.string "gauntlet that really pays out.$"

@ ----------------------------------------------------------------------------
@ Ten Gauntlets: the Frontier's "POS is down" while the Artisan Cave quest is
@ required and unfinished (IsFrontierPOSDown, easter-eggs-spec.md). Nothing is
@ for sale, so the 900 FP from gauntlet 3 can only go on the quest. The
@ Pokemon keeper is the exception: one LEAFEON once the florist has asked for
@ one, then - once FLOTSAM is beaten (step 6) - the four POKeMON that learn
@ SURF by level-up, so a player without one can still reach the cave.
@ ----------------------------------------------------------------------------
BattleFrontier_ExchangeServiceCorner_EventScript_POSDown::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_POSDown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokemonKeeperPOSDown::
	goto_if_ge VAR_ARTISAN_QUEST_STEP, 6, BattleFrontier_ExchangeServiceCorner_EventScript_SurfStock
	goto_if_set FLAG_FRONTIER_FLORIST_TRADED, BattleFrontier_ExchangeServiceCorner_EventScript_POSDown
	goto_if_set FLAG_FRONTIER_FLORIST_ASKED, BattleFrontier_ExchangeServiceCorner_EventScript_OfferLeafeon
	msgbox BattleFrontier_ExchangeServiceCorner_Text_POSDownLeafeon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_OfferLeafeon::
	special ShowFacilityFPWindow
	msgbox BattleFrontier_ExchangeServiceCorner_Text_OfferLeafeon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye
	setvar VAR_0x8008, 300
	setvar VAR_0x8009, SPECIES_LEAFEON
	bufferspeciesname STR_VAR_1, VAR_0x8009
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownBuy
	end

BattleFrontier_ExchangeServiceCorner_EventScript_SurfStock::
	special ShowFacilityFPWindow
	message BattleFrontier_ExchangeServiceCorner_Text_SurfStock
	waitmessage
	dynmultipush BattleFrontier_ExchangeServiceCorner_Text_StockSlowbro, 0
	dynmultipush BattleFrontier_ExchangeServiceCorner_Text_StockSlowking, 1
	dynmultipush BattleFrontier_ExchangeServiceCorner_Text_StockTentacruel, 2
	dynmultipush BattleFrontier_ExchangeServiceCorner_Text_StockMilotic, 3
	dynmultipush BattleFrontier_ExchangeServiceCorner_Text_StockNothing, 4
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_StockSlowbro
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_StockSlowking
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_StockTentacruel
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_StockMilotic
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_StockSlowbro::
	setvar VAR_0x8008, 150
	setvar VAR_0x8009, SPECIES_SLOWBRO
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownConfirm
	end

BattleFrontier_ExchangeServiceCorner_EventScript_StockSlowking::
	setvar VAR_0x8008, 150
	setvar VAR_0x8009, SPECIES_SLOWKING
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownConfirm
	end

BattleFrontier_ExchangeServiceCorner_EventScript_StockTentacruel::
	setvar VAR_0x8008, 200
	setvar VAR_0x8009, SPECIES_TENTACRUEL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownConfirm
	end

BattleFrontier_ExchangeServiceCorner_EventScript_StockMilotic::
	setvar VAR_0x8008, 400
	setvar VAR_0x8009, SPECIES_MILOTIC
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownConfirm
	end

@ Every message below prints {STR_VAR_1}, so the species name has to be
@ buffered here - the normal shop menu does it when a row is picked, but this
@ path doesn't go through that menu (it showed a stale name otherwise).
BattleFrontier_ExchangeServiceCorner_EventScript_POSDownConfirm::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmPurchase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye
@ VAR_0x8008 = price, VAR_0x8009 = species.
BattleFrontier_ExchangeServiceCorner_EventScript_POSDownBuy::
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_POSDownNoFP
	special FacilityShopBuyMon
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BattleFrontier_ExchangeServiceCorner_EventScript_POSDownNoRoom
	copyvar VAR_TEMP_1, VAR_RESULT
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	playse SE_SHOP
	goto_if_eq VAR_TEMP_1, MON_GIVEN_TO_PC, BattleFrontier_ExchangeServiceCorner_EventScript_POSDownToPC
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourMon, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_POSDownToPC::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_SentMonToPC, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_POSDownNoFP::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughFP, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_POSDownNoRoom::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_NoRoomForMon, MSGBOX_DEFAULT
BattleFrontier_ExchangeServiceCorner_EventScript_POSDownGoodbye::
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_Text_POSDown:
	.string "I'm so sorry! Our POS system is\n"
	.string "down, along with the rest of the\l"
	.string "island's. We can't sell anything\l"
	.string "right now.$"

BattleFrontier_ExchangeServiceCorner_Text_POSDownLeafeon:
	.string "I'm so sorry! Our POS system is\n"
	.string "down. We can't sell anything right\l"
	.string "now.\p"
	.string "...Well, except for some reason\n"
	.string "this one LEAFEON keeps showing up\l"
	.string "as available. You probably don't\l"
	.string "want it, though.$"

BattleFrontier_ExchangeServiceCorner_Text_OfferLeafeon:
	.string "The system's still down... but\n"
	.string "that LEAFEON is somehow still\l"
	.string "showing up. I can sell you that\l"
	.string "one, for 300 FP.\p"
	.string "Would you like it?$"

BattleFrontier_ExchangeServiceCorner_Text_SurfStock:
	.string "Good news! Part of the system came\n"
	.string "back up. I can sell just these few\l"
	.string "WATER POKéMON for now.$"

BattleFrontier_ExchangeServiceCorner_Text_StockSlowbro:
	.string "SLOWBRO 150 FP$"

BattleFrontier_ExchangeServiceCorner_Text_StockSlowking:
	.string "SLOWKING 150 FP$"

BattleFrontier_ExchangeServiceCorner_Text_StockTentacruel:
	.string "TENTACRUEL 200 FP$"

BattleFrontier_ExchangeServiceCorner_Text_StockMilotic:
	.string "MILOTIC 400 FP$"

BattleFrontier_ExchangeServiceCorner_Text_StockNothing:
	.string "Nothing$"
