BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

@ Ten Gauntlets: the Gambler is now the Broker (broker-spec.md). One deal
@ per gauntlet from the next gauntlet's shop wave: an item or a Pokemon, at
@ 1.2x, the player's to keep (Pokemon are tagged OT "BROKER"). The vanilla
@ betting flow below is unreachable now.
@ VAR_TEMP_2 holds the gauntlet deal's status (BROKER_*), VAR_TEMP_3 whether
@ the Artisan Cave side quest's MASTER BALL is on offer (easter-eggs-spec.md,
@ #1). The MASTER BALL doesn't use up the gauntlet's deal.
BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	special FacilityBrokerCheck
	goto_if_eq VAR_RESULT, BROKER_RUN_ACTIVE, BattleFrontier_Lounge3_EventScript_Broker_RunActive
	copyvar VAR_TEMP_2, VAR_RESULT
	call_if_eq VAR_ARTISAN_QUEST_STEP, 3, BattleFrontier_Lounge3_EventScript_Broker_FlotsamSentYou
	call_if_eq VAR_ARTISAN_QUEST_STEP, 4, BattleFrontier_Lounge3_EventScript_Broker_CheckAlreadyHasBall
	call BattleFrontier_Lounge3_EventScript_Broker_CheckMasterBall
	specialvar VAR_RESULT, IsFrontierPOSDown
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge3_EventScript_Broker_POSDown
	goto_if_eq VAR_TEMP_2, BROKER_OK, BattleFrontier_Lounge3_EventScript_Broker_DealOpen
	goto_if_eq VAR_TEMP_3, TRUE, BattleFrontier_Lounge3_EventScript_Broker_OnlyMasterBall
	goto_if_eq VAR_TEMP_2, BROKER_DEAL_USED, BattleFrontier_Lounge3_EventScript_Broker_DealUsed
	goto BattleFrontier_Lounge3_EventScript_Broker_NothingLeft
	end

@ While the Frontier's system is down (IsFrontierPOSDown), the Broker's
@ regular deals are off too - only the MASTER BALL, so the player's FP can't
@ drain before they can afford it. Until FLOTSAM has sent the player (step 3,
@ which CheckMasterBall above turns into an offer), and again once the ball is
@ bought, he's just "busy".
BattleFrontier_Lounge3_EventScript_Broker_POSDown::
	goto_if_eq VAR_TEMP_3, FALSE, BattleFrontier_Lounge3_EventScript_Broker_POSDownNothing
	msgbox BattleFrontier_Lounge3_Text_BrokerPOSDown, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, BROKER_RUN_ACTIVE
	goto BattleFrontier_Lounge3_EventScript_Broker_Open
	end

BattleFrontier_Lounge3_EventScript_Broker_POSDownNothing::
	msgbox BattleFrontier_Lounge3_Text_BrokerPOSDownNothing, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_Broker_FlotsamSentYou::
	msgbox BattleFrontier_Lounge3_Text_BrokerFlotsamSentYou, MSGBOX_DEFAULT
	setvar VAR_ARTISAN_QUEST_STEP, 4
	return

@ Step 5 (FLOTSAM waits at the waterfall) follows buying the MASTER BALL -
@ or, if the player somehow already has one, just coming here for it.
BattleFrontier_Lounge3_EventScript_Broker_CheckAlreadyHasBall::
	checkitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge3_EventScript_Broker_MasterBallInHand
	checkpcitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge3_EventScript_Broker_MasterBallInHand
	return

BattleFrontier_Lounge3_EventScript_Broker_MasterBallInHand::
	setvar VAR_ARTISAN_QUEST_STEP, 5
	return

BattleFrontier_Lounge3_EventScript_Broker_CheckMasterBall::
	setvar VAR_TEMP_3, FALSE
	goto_if_lt VAR_ARTISAN_QUEST_STEP, 4, Common_EventScript_NopReturn
	goto_if_set FLAG_ARTISAN_LATI_CAUGHT, Common_EventScript_NopReturn
	checkitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NopReturn
	checkpcitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NopReturn
	setvar VAR_TEMP_3, TRUE
	return

BattleFrontier_Lounge3_EventScript_Broker_OnlyMasterBall::
	call_if_eq VAR_TEMP_2, BROKER_DEAL_USED, BattleFrontier_Lounge3_EventScript_Broker_OnlyMasterBallDealUsed
	call_if_eq VAR_TEMP_2, BROKER_NOTHING_LEFT, BattleFrontier_Lounge3_EventScript_Broker_OnlyMasterBallNothingLeft
	goto BattleFrontier_Lounge3_EventScript_Broker_Open
	end

BattleFrontier_Lounge3_EventScript_Broker_OnlyMasterBallDealUsed::
	msgbox BattleFrontier_Lounge3_Text_BrokerOnlyMasterBall, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge3_EventScript_Broker_OnlyMasterBallNothingLeft::
	msgbox BattleFrontier_Lounge3_Text_BrokerOnlyMasterBallNothingLeft, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge3_EventScript_Broker_DealOpen::
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_Broker_Greet
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_BrokerIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_Open
	end

BattleFrontier_Lounge3_EventScript_Broker_Greet:
	msgbox BattleFrontier_Lounge3_Text_BrokerGreet, MSGBOX_DEFAULT
BattleFrontier_Lounge3_EventScript_Broker_Open:
	special ShowFacilityFPWindow
BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf:
	message BattleFrontier_Lounge3_Text_BrokerWhichShelf
	waitmessage
	call_if_eq VAR_TEMP_2, BROKER_OK, BattleFrontier_Lounge3_EventScript_Broker_PushDealShelves
	call_if_eq VAR_TEMP_3, TRUE, BattleFrontier_Lounge3_EventScript_Broker_PushIllegalShelf
	dynmultipush BattleFrontier_Lounge3_Text_BrokerShelfNothing, 2
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge3_EventScript_Broker_Items
	case 1, BattleFrontier_Lounge3_EventScript_Broker_Mons
	case 3, BattleFrontier_Lounge3_EventScript_Broker_MasterBall
	goto BattleFrontier_Lounge3_EventScript_Broker_Goodbye
	end

BattleFrontier_Lounge3_EventScript_Broker_PushDealShelves::
	dynmultipush BattleFrontier_Lounge3_Text_BrokerShelfItem, 0
	dynmultipush BattleFrontier_Lounge3_Text_BrokerShelfMon, 1
	return

BattleFrontier_Lounge3_EventScript_Broker_PushIllegalShelf::
	dynmultipush BattleFrontier_Lounge3_Text_BrokerShelfIllegal, 3
	return

BattleFrontier_Lounge3_EventScript_Broker_MasterBall::
	msgbox BattleFrontier_Lounge3_Text_BrokerConfirmMasterBall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	setvar VAR_0x8008, 600
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_Lounge3_EventScript_Broker_NotEnoughFP
	checkitemspace ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge3_EventScript_Broker_BagFull
	setvar VAR_0x8004, 600
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	additem ITEM_MASTER_BALL
	setvar VAR_TEMP_3, FALSE
	call_if_eq VAR_ARTISAN_QUEST_STEP, 4, BattleFrontier_Lounge3_EventScript_Broker_MasterBallInHand
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_BrokerMasterBallDone, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, BROKER_OK, BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	goto BattleFrontier_Lounge3_EventScript_Broker_Goodbye
	end

BattleFrontier_Lounge3_EventScript_Broker_Items:
	special FacilityBrokerBuildItemMenu
	goto_if_eq VAR_RESULT, 0, BattleFrontier_Lounge3_EventScript_Broker_NoStock
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectRow
	buffernumberstring STR_VAR_2, VAR_0x8008
	msgbox BattleFrontier_Lounge3_Text_BrokerConfirmItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_Broker_Items
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_Lounge3_EventScript_Broker_NotEnoughFP
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge3_EventScript_Broker_BagFull
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	additem VAR_0x8009
	special FacilityBrokerMarkDealUsed
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_BrokerItemDone, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_Goodbye
	end

BattleFrontier_Lounge3_EventScript_Broker_Mons:
	special FacilityBrokerBuildMonMenu
	goto_if_eq VAR_RESULT, 0, BattleFrontier_Lounge3_EventScript_Broker_NoStock
	setvar VAR_0x8004, SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC
	special ShowScrollableMultichoice
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	copyvar VAR_0x8004, VAR_RESULT
	special FacilityShopSelectRow
	buffernumberstring STR_VAR_2, VAR_0x8008
	msgbox BattleFrontier_Lounge3_Text_BrokerConfirmMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_Broker_Mons
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_Lounge3_EventScript_Broker_NotEnoughFP
	special FacilityBrokerSellMon
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BattleFrontier_Lounge3_EventScript_Broker_NoRoom
	copyvar VAR_0x8004, VAR_0x8008
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_Lounge3_Text_BrokerMonReceived
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_BrokerMonDone, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_Goodbye
	end

BattleFrontier_Lounge3_EventScript_Broker_NoStock:
	msgbox BattleFrontier_Lounge3_Text_BrokerNoStock, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	end

BattleFrontier_Lounge3_EventScript_Broker_NotEnoughFP:
	msgbox BattleFrontier_Lounge3_Text_BrokerNotEnoughFP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	end

BattleFrontier_Lounge3_EventScript_Broker_BagFull:
	msgbox BattleFrontier_Lounge3_Text_BrokerBagFull, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	end

BattleFrontier_Lounge3_EventScript_Broker_NoRoom:
	msgbox BattleFrontier_Lounge3_Text_BrokerNoRoom, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_Broker_ChooseShelf
	end

BattleFrontier_Lounge3_EventScript_Broker_Goodbye:
	special CloseFacilityFPWindow
	special FacilityShopFreeMenuRows
	msgbox BattleFrontier_Lounge3_Text_BrokerGoodbye, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_Broker_RunActive:
	msgbox BattleFrontier_Lounge3_Text_BrokerRunActive, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_Broker_DealUsed:
	msgbox BattleFrontier_Lounge3_Text_BrokerDealUsed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_Broker_NothingLeft:
	msgbox BattleFrontier_Lounge3_Text_BrokerNothingLeft, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
	.string "…What's that you want?\p"
	.string "Can't you see we're kind of busy here?\n"
	.string "Can't your business wait till later?$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
	.string "…Huh?\n"
	.string "You look to me like a tough TRAINER.\p"
	.string "Heheh…\n"
	.string "Listen, I have this proposition.\p"
	.string "We have a little group going here,\n"
	.string "and we play a little game with what\l"
	.string "goes on in the BATTLE FRONTIER.\p"
	.string "The rules are really simple.\p"
	.string "First, we pick one of the facilities\n"
	.string "in the BATTLE FRONTIER.\p"
	.string "Then, we each pick a different TRAINER\n"
	.string "who's taking that facility's challenge,\l"
	.string "and bet with our Battle Points.\p"
	.string "The guy who bet on the TRAINER with\n"
	.string "the best record takes all the Battle\l"
	.string "Points in the pool.\p"
	.string "Sounds simple, huh?\n"
	.string "So, anyway…$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be challenging the BATTLE\l"
	.string "TOWER's SINGLE BATTLE ROOMS.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be challenging the BATTLE\l"
	.string "TOWER's DOUBLE BATTLE ROOMS.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be challenging the BATTLE\l"
	.string "TOWER's MULTI BATTLE ROOMS.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE\l"
	.string "DOME's SINGLE BATTLE Tourney.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE\l"
	.string "DOME's DOUBLE BATTLE Tourney.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE\l"
	.string "FACTORY's Battle Swap Single Tourney.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE\l"
	.string "FACTORY's Battle Swap Double Tourney.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be challenging the BATTLE\l"
	.string "PALACE's SINGLE BATTLE HALLS.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be challenging the BATTLE\l"
	.string "PALACE's DOUBLE BATTLE HALLS.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE\l"
	.string "ARENA's Set KO Tourney.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE PIKE's\l"
	.string "Battle Choice.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
	.string "What I'm looking for is a TRAINER who's\n"
	.string "going to be entering the BATTLE\l"
	.string "PYRAMID's Battle Quest.\p"
	.string "But so far, I haven't seen a TRAINER\n"
	.string "that has that winning quality.$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
	.string "I'll see to it that you benefit, too.\n"
	.string "So how about it?\l"
	.string "How about entering that event for me?$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
	.string "All right, that's perfect.\n"
	.string "So, uh… How about spotting me some\l"
	.string "of your Battle Points?\p"
	.string "Trust me, I'll show you my gratitude\n"
	.string "afterward.$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
	.string "Great, great!\n"
	.string "So, how much can you spot me?$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
	.string "Oh, no, no, no!\n"
	.string "You don't have enough Battle Points!\p"
	.string "I wish you wouldn't monkey around and\n"
	.string "waste everyone's time!$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
	.string "Heheh! Thanks much!\n"
	.string "So, off you go!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
	.string "Get to the BATTLE TOWER's\n"
	.string "SINGLE BATTLE ROOMS pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
	.string "Get to the BATTLE TOWER's\n"
	.string "DOUBLE BATTLE ROOMS pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
	.string "Get to the BATTLE TOWER's\n"
	.string "MULTI BATTLE ROOMS pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
	.string "Get to the BATTLE DOME's\n"
	.string "SINGLE BATTLE Tourney pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
	.string "Get to the BATTLE DOME's\n"
	.string "DOUBLE BATTLE Tourney pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
	.string "Get to the BATTLE FACTORY's\n"
	.string "Battle Swap Single Tourney pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
	.string "Get to the BATTLE FACTORY's\n"
	.string "Battle Swap Double Tourney pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
	.string "Get to the BATTLE PALACE's\n"
	.string "SINGLE BATTLE HALLS pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
	.string "Get to the BATTLE PALACE's\n"
	.string "DOUBLE BATTLE HALLS pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattleArena::
	.string "Get to the BATTLE ARENA's\n"
	.string "Set KO Tourney pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattlePike::
	.string "Get to the BATTLE PIKE's\n"
	.string "Battle Choice pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
	.string "Get to the BATTLE PYRAMID's\n"
	.string "Battle Quest pronto!\p"
	.string "It's a must-win situation!\n"
	.string "Don't blow your chance!\l"
	.string "Both of our futures depend on you!$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
	.string "Oh, it's you…\n"
	.string "Nice try…\p"
	.string "I hate to break it to you, but I can't\n"
	.string "return your Battle Points…\p"
	.string "I guess we'll have to let it motivate\n"
	.string "us to try harder next time!$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
	.string "Oh, yes!\n"
	.string "Hello there, champ!\p"
	.string "I knew you could!\n"
	.string "I knew you would!\l"
	.string "We're both big winners!\p"
	.string "I'll return your Battle Points and,\n"
	.string "of course, a little extra from me!$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
	.string "{PLAYER} obtained\n"
	.string "{STR_VAR_1} Battle Points.$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
	.string "If you're up for another challenge,\n"
	.string "please do think of me!$"

BattleFrontier_Lounge3_Text_NotInterested::
	.string "Not interested?! You shouldn't be\n"
	.string "so afraid to take a chance!$"

BattleFrontier_Lounge3_Text_Oh::
	.string "Oh…$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
	.string "I bought a POKéMON off him a whole\n"
	.string "gauntlet early.\p"
	.string "It still says BROKER on its\n"
	.string "papers. Gives me the creeps.$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
	.string "I bought a CHOICE SCARF off him a\n"
	.string "whole gauntlet early.\p"
	.string "I still don't know where he gets\n"
	.string "them.$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
	.string "Giggle! His prices are steep, but\n"
	.string "I got my POKéMON before anyone\l"
	.string "else could!$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
	.string "That man in the corner… I don't\n"
	.string "trust him one bit.$"

BattleFrontier_Lounge3_Text_BrokerIntro:
	.string "Psst. Over here.\p"
	.string "The EXCHANGE CORNER won't stock\n"
	.string "the good stuff until you've\l"
	.string "cleared the next gauntlet. Me? I\l"
	.string "know a guy on the delivery crew.\p"
	.string "One deal per gauntlet. An item or\n"
	.string "a POKéMON, yours to keep. Full\l"
	.string "price, plus my cut.\p"
	.string "...And you didn't hear any of this\n"
	.string "from me.$"

BattleFrontier_Lounge3_Text_BrokerGreet:
	.string "Psst. Back for something special?$"

BattleFrontier_Lounge3_Text_BrokerWhichShelf:
	.string "So, what'll it be?$"

BattleFrontier_Lounge3_Text_BrokerShelfItem:
	.string "An item$"

BattleFrontier_Lounge3_Text_BrokerShelfMon:
	.string "A POKéMON$"

BattleFrontier_Lounge3_Text_BrokerShelfNothing:
	.string "Nothing$"

BattleFrontier_Lounge3_Text_BrokerConfirmItem:
	.string "The {STR_VAR_1}? That'll be\n"
	.string "{STR_VAR_2} FP, my cut included.\l"
	.string "Deal?$"

BattleFrontier_Lounge3_Text_BrokerConfirmMon:
	.string "{STR_VAR_1}, for {STR_VAR_2} FP, my\n"
	.string "cut included. It's yours to keep.\p"
	.string "Deal?$"

BattleFrontier_Lounge3_Text_BrokerItemDone:
	.string "Pleasure doing business. Now\n"
	.string "scram, before somebody sees us.$"

BattleFrontier_Lounge3_Text_BrokerMonReceived:
	.string "{PLAYER} received {STR_VAR_1}!$"

BattleFrontier_Lounge3_Text_BrokerMonDone:
	.string "It's all yours. Try not to tell\n"
	.string "anyone where you got it.$"

BattleFrontier_Lounge3_Text_BrokerNoStock:
	.string "Nothing on that shelf this time.\n"
	.string "Try the other one.$"

BattleFrontier_Lounge3_Text_BrokerNotEnoughFP:
	.string "You can't afford it. I don't do\n"
	.string "credit.$"

BattleFrontier_Lounge3_Text_BrokerBagFull:
	.string "Your BAG's full. Come back with\n"
	.string "some room.$"

BattleFrontier_Lounge3_Text_BrokerNoRoom:
	.string "You've got nowhere to put it.\n"
	.string "Clear some space first.$"

BattleFrontier_Lounge3_Text_BrokerGoodbye:
	.string "Remember: you didn't hear it from\n"
	.string "me.$"

BattleFrontier_Lounge3_Text_BrokerRunActive:
	.string "Not while you're mid-run. Too many\n"
	.string "eyes on you. Come back after.$"

BattleFrontier_Lounge3_Text_BrokerDealUsed:
	.string "I said one deal. Come back when\n"
	.string "the next gauntlet's open. I'll\l"
	.string "have new stock by then.$"

BattleFrontier_Lounge3_Text_BrokerNothingLeft:
	.string "You've cleared every gauntlet?\n"
	.string "…Then there's nothing left I can\l"
	.string "get you.\p"
	.string "Retirement, maybe.$"

BattleFrontier_Lounge3_Text_BrokerFlotsamSentYou:
	.string "...FLOTSAM sent you? That kid\n"
	.string "never could keep his mouth shut.\p"
	.string "Fine. For a friend of a friend,\n"
	.string "I've got something special under\l"
	.string "the counter.$"

BattleFrontier_Lounge3_Text_BrokerOnlyMasterBall:
	.string "You already made your deal this\n"
	.string "gauntlet. ...But that's not why\l"
	.string "you're here, is it?$"

BattleFrontier_Lounge3_Text_BrokerShelfIllegal:
	.string "Illegal item$"

BattleFrontier_Lounge3_Text_BrokerConfirmMasterBall:
	.string "A MASTER BALL. 600 FP.\p"
	.string "Where'd I get it? Where do you\n"
	.string "think?\p"
	.string "Deal?$"

BattleFrontier_Lounge3_Text_BrokerMasterBallDone:
	.string "Pleasure. ...And if anyone asks,\n"
	.string "you found it.$"

BattleFrontier_Lounge3_Text_BrokerOnlyMasterBallNothingLeft:
	.string "You've cleared every gauntlet?\n"
	.string "Then there's nothing left I can\l"
	.string "get you...\p"
	.string "...Except the one thing you came\n"
	.string "for.$"

BattleFrontier_Lounge3_Text_BrokerPOSDown:
	.string "Supply lines are dead. The whole\n"
	.string "island's system went down, and my\l"
	.string "guy on the delivery crew can't\l"
	.string "move a thing.\p"
	.string "...All I've got is what's under\n"
	.string "the counter.$"

BattleFrontier_Lounge3_Text_BrokerPOSDownNothing:
	.string "Not now, kid. I'm busy.\p"
	.string "Come back when you've actually got\n"
	.string "business with me.$"
