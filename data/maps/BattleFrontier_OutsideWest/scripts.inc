BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_OutsideWest_OnFrame
	.byte 0

BattleFrontier_OutsideWest_OnFrame:
	map_script_2 VAR_TEMP_7, 1, BattleFrontier_OutsideWest_EventScript_PikeSteven
	.2byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	@ Ten Gauntlets: nothing is granted on arrival anymore - SCOTT hands the
	@ starting team over at his house (data/maps/BattleFrontier_ScottsHouse/
	@ scripts.inc), after his welcome at the Reception Gate sends the player
	@ there.
	@ Ten Gauntlets: the Frontier Brains only show up once their facility is
	@ open (easter-eggs-spec.md, #8), and the Ditto's true form stays hidden
	@ until it gives itself away (#4).
	setflag FLAG_TEMP_3
	special RemoveFrontierHMs
	@ White-outs (the SCRAMBLER's story battles) land at the Frontier's
	@ Pokemon Center, never back home in LITTLEROOT.
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	call BattleFrontier_OutsideWest_EventScript_ArmCaveClosedCheck
	specialvar VAR_RESULT, GetGauntletsClearedCount
	call_if_lt VAR_RESULT, 4, BattleFrontier_OutsideWest_EventScript_HideTucker
	call_if_lt VAR_RESULT, 5, BattleFrontier_OutsideWest_EventScript_HideLucy
	call BattleFrontier_OutsideWest_EventScript_SetupPikeStory
	call BattleFrontier_OutsideWest_EventScript_SetupSteven
	call BattleFrontier_OutsideWest_EventScript_SetupBrokerStory
	call BattleFrontier_OutsideWest_EventScript_SetupCrownStory
	call BattleFrontier_OutsideWest_EventScript_SetupFactoryJoy
	call BattleFrontier_OutsideWest_EventScript_SetupEndgame
	end

BattleFrontier_OutsideWest_EventScript_HideTucker::
	setflag FLAG_TEMP_1
	return

BattleFrontier_OutsideWest_EventScript_HideLucy::
	setflag FLAG_TEMP_2
	return

BattleFrontier_OutsideWest_EventScript_Woman1SawDitto::
	msgbox BattleFrontier_OutsideWest_Text_DittoBanned, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Tucker::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, BattleFrontier_OutsideWest_EventScript_TuckerBeaten
	msgbox BattleFrontier_OutsideWest_Text_TuckerBefore, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_TuckerBeaten::
	msgbox BattleFrontier_OutsideWest_Text_TuckerAfter, MSGBOX_DEFAULT
	release
	end

@ PIKE QUEEN LUCY waits outside the Pike, gauntlet 6's building, once it's
@ open (easter-eggs-spec.md, #8). NOLAND used to stand by the Factory; he's
@ SCOTT's henchman now (storyline.md).
BattleFrontier_OutsideWest_EventScript_Lucy::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_OutsideWest_EventScript_LucyBeaten
	msgbox BattleFrontier_OutsideWest_Text_LucyBefore, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_LucyBeaten::
	msgbox BattleFrontier_OutsideWest_Text_LucyAfter, MSGBOX_DEFAULT
	release
	end

@ The first talk gets the ferry attendant's greeting, word for word. The
@ second gives the game away: it turns back into a DITTO and bounces off,
@ away from the player. VAR_TEMP_1 counts talks this visit; VAR_TEMP_2 lets
@ the woman nearby comment on it until the player leaves the area.
BattleFrontier_OutsideWest_EventScript_DittoDisguise::
	lock
	faceplayer
	goto_if_eq VAR_TEMP_1, 1, BattleFrontier_OutsideWest_EventScript_DittoReveal
	setvar VAR_TEMP_1, 1
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_DittoReveal::
	msgbox BattleFrontier_OutsideWest_Text_DittoGivesItselfAway, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_TEMP_3
	addobject LOCALID_FRONTIER_DITTO
	removeobject LOCALID_FRONTIER_DITTO_DISGUISE
	setflag FLAG_FRONTIER_DITTO_REVEALED
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	waitmoncry
	setvar VAR_TEMP_2, 1
	specialvar VAR_RESULT, GetPlayerFacingDirection
	switch VAR_RESULT
	case DIR_NORTH, BattleFrontier_OutsideWest_EventScript_DittoBounceNorth
	case DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_DittoBounceSouth
	case DIR_WEST, BattleFrontier_OutsideWest_EventScript_DittoBounceWest
	applymovement LOCALID_FRONTIER_DITTO, BattleFrontier_OutsideWest_Movement_DittoBounceEast
	goto BattleFrontier_OutsideWest_EventScript_DittoGone
	end

BattleFrontier_OutsideWest_EventScript_DittoBounceNorth::
	applymovement LOCALID_FRONTIER_DITTO, BattleFrontier_OutsideWest_Movement_DittoBounceNorth
	goto BattleFrontier_OutsideWest_EventScript_DittoGone
	end

BattleFrontier_OutsideWest_EventScript_DittoBounceSouth::
	applymovement LOCALID_FRONTIER_DITTO, BattleFrontier_OutsideWest_Movement_DittoBounceSouth
	goto BattleFrontier_OutsideWest_EventScript_DittoGone
	end

BattleFrontier_OutsideWest_EventScript_DittoBounceWest::
	applymovement LOCALID_FRONTIER_DITTO, BattleFrontier_OutsideWest_Movement_DittoBounceWest
	goto BattleFrontier_OutsideWest_EventScript_DittoGone
	end

BattleFrontier_OutsideWest_EventScript_DittoGone::
	waitmovement 0
	removeobject LOCALID_FRONTIER_DITTO
	release
	end

BattleFrontier_OutsideWest_Movement_DittoBounceNorth:
	jump_in_place_down
	jump_2_up
	jump_2_up
	jump_2_up
	step_end

BattleFrontier_OutsideWest_Movement_DittoBounceSouth:
	jump_in_place_down
	jump_2_down
	jump_2_down
	jump_2_down
	step_end

BattleFrontier_OutsideWest_Movement_DittoBounceWest:
	jump_in_place_down
	jump_2_left
	jump_2_left
	jump_2_left
	step_end

BattleFrontier_OutsideWest_Movement_DittoBounceEast:
	jump_in_place_down
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

@ Ten Gauntlets: Slateport/Lilycove removed from this menu on purpose - see
@ the comment on MultichoiceList_SSTidalBattleFrontier in
@ src/data/script_menu.h. Route 103 is the only real destination for now,
@ mirroring how the player got here in the first place.
BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 1, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToRoute103
	case 1, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

@ Ten Gauntlets: the only real destination the ferry menu offers right now -
@ back the way the player came in, Route 103's own dock (see the comment on
@ Route103_EventScript_FerryAttendant, data/maps/Route103/scripts.inc). (20, 9)
@ lands just west of that dock's SS Tidal object, mirroring where the player
@ would have stood to board it in the first place.
BattleFrontier_OutsideWest_EventScript_FerryToRoute103::
	msgbox BattleFrontier_OutsideWest_Text_Route103ItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_ROUTE103, 20, 9
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FRONTIER_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_FRONTIER_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 4, BattleFrontier_OutsideWest_EventScript_BattleDomeSign_Cleared4
	msgbox BattleFrontier_OutsideWest_EventScript_BattleDomeSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign_Cleared4:
	msgbox BattleFrontier_OutsideWest_EventScript_BattleDomeSign_Text4, MSGBOX_SIGN
	end

@ Ten Gauntlets: the Factory is Devon's control room (storyline.md).
BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Cleared5
	msgbox BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Cleared5:
	msgbox BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text5, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_Boy1_Cleared1
	msgbox BattleFrontier_OutsideWest_EventScript_Boy1_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy1_Cleared1:
	msgbox BattleFrontier_OutsideWest_EventScript_Boy1_Text1, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FRONTIER_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_SYSTEM_DOWN, BattleFrontier_OutsideWest_Man1_Gossip0
	case GOSSIP_LAB, BattleFrontier_OutsideWest_Man1_Gossip1
	case GOSSIP_AFTER_LAB, BattleFrontier_OutsideWest_Man1_Gossip2
	case GOSSIP_PALACE, BattleFrontier_OutsideWest_Man1_Gossip3
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
BattleFrontier_OutsideWest_Man1_Gossip0::
	msgbox BattleFrontier_OutsideWest_Man1_Text_Gossip0, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man1_Gossip1::
	msgbox BattleFrontier_OutsideWest_Man1_Text_Gossip1, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man1_Gossip2::
	msgbox BattleFrontier_OutsideWest_Man1_Text_Gossip2, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man1_Gossip3::
	msgbox BattleFrontier_OutsideWest_Man1_Text_Gossip3, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man1_Text_Gossip0:
	.string "No shop, no tutors, no fourth mat. The\n"
	.string "whole island's system is down.\p"
	.string "DEVON runs all of it, they say. You'd\n"
	.string "think they could afford a backup.$"

BattleFrontier_OutsideWest_Man1_Text_Gossip1:
	.string "Gauntlet 6 is down. Only gauntlet 6.\n"
	.string "The DEVON technicians just shrug.\p"
	.string "Funny. Everything else on the island\n"
	.string "runs fine.$"

BattleFrontier_OutsideWest_Man1_Text_Gossip2:
	.string "Gauntlet 6 is back up. Word is SCOTT\n"
	.string "called DEVON's president himself and\l"
	.string "gave him an earful.$"

BattleFrontier_OutsideWest_Man1_Text_Gossip3:
	.string "The PALACE is finally open, and SCOTT\n"
	.string "has gone off the island, right when it\l"
	.string "gets interesting.\p"
	.string "Who's running the place while he's\n"
	.string "away? DEVON, I suppose.$"

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_FRONTIER_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, BattleFrontier_OutsideWest_EventScript_ExpertM_Cleared5
	goto_if_ge VAR_RESULT, 4, BattleFrontier_OutsideWest_EventScript_ExpertM_Cleared4
	msgbox BattleFrontier_OutsideWest_EventScript_ExpertM_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_ExpertM_Cleared5:
	msgbox BattleFrontier_OutsideWest_EventScript_ExpertM_Text5, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_ExpertM_Cleared4:
	msgbox BattleFrontier_OutsideWest_EventScript_ExpertM_Text4, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_STEVEN, BattleFrontier_OutsideWest_Man2_Gossip0
	case GOSSIP_ANABEL, BattleFrontier_OutsideWest_Man2_Gossip1
	case GOSSIP_STANDOFF, BattleFrontier_OutsideWest_Man2_Gossip2
	case GOSSIP_SIEGE, BattleFrontier_OutsideWest_Man2_Gossip3
	case GOSSIP_AFTERMATH, BattleFrontier_OutsideWest_Man2_Gossip4
	case GOSSIP_DEVON, BattleFrontier_OutsideWest_Man2_Gossip4
	case GOSSIP_DEVON_FREED, BattleFrontier_OutsideWest_Man2_Gossip4
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
BattleFrontier_OutsideWest_Man2_Gossip0::
	msgbox BattleFrontier_OutsideWest_Man2_Text_Gossip0, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man2_Gossip1::
	msgbox BattleFrontier_OutsideWest_Man2_Text_Gossip1, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man2_Gossip2::
	msgbox BattleFrontier_OutsideWest_Man2_Text_Gossip2, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man2_Gossip3::
	msgbox BattleFrontier_OutsideWest_Man2_Text_Gossip3, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man2_Text_Gossip3:
	.string "I saw the CHAMPION's PALKIA tear the\n"
	.string "FACTORY door open.\p"
	.string "The FRONTIER's never seen anything\n"
	.string "like it. Neither have I.$"

BattleFrontier_OutsideWest_Man2_Gossip4::
	msgbox BattleFrontier_OutsideWest_Man2_Text_Gossip4, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Man2_Text_Gossip4:
	.string "The FACTORY's empty now. SCOTT's\n"
	.string "gone, and everyone's breathing again.\p"
	.string "For now, anyway.$"

BattleFrontier_OutsideWest_Man2_Text_Gossip0:
	.string "STEVEN STONE beat the old FRONTIER\n"
	.string "faster than anyone, back in the day.\p"
	.string "Now he's here again, poking at the\n"
	.string "FACTORY's walls. What's he after?$"

BattleFrontier_OutsideWest_Man2_Text_Gossip1:
	.string "ANABEL held the TOWER for years\n"
	.string "without losing. Somebody finally took\l"
	.string "it from her.\p"
	.string "...You, was it? Huh.$"

BattleFrontier_OutsideWest_Man2_Text_Gossip2:
	.string "The old FRONTIER never had anything\n"
	.string "like that MEWTWO.\p"
	.string "SCOTT was always the one watching.\n"
	.string "Now everyone's watching him. And\l"
	.string "everyone's scared.$"

BattleFrontier_OutsideWest_EventScript_Woman1::
	lock
	faceplayer
	goto_if_eq VAR_TEMP_2, 1, BattleFrontier_OutsideWest_EventScript_Woman1SawDitto
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 2, BattleFrontier_OutsideWest_EventScript_Woman1_Cleared2
	msgbox BattleFrontier_OutsideWest_EventScript_Woman1_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Woman1_Cleared2:
	msgbox BattleFrontier_OutsideWest_EventScript_Woman1_Text2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "This is the BATTLE DOME!\n"
	.string "Your path to the invincible superstar!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "This is the BATTLE FACTORY!\n"
	.string "Seek out the toughest POKéMON!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "This is the BATTLE PIKE!\n"
	.string "Choose one of three paths!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "This is the BATTLE TOWER.\p"
	.string "TRAINERS bring their best-raised\n"
	.string "POKéMON for elimination-style matches.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "Hello! The ferry sails back to\n"
	.string "ROUTE 103.\p"
	.string "May I see your TICKET?$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "{PLAYER} doesn't have the TICKET…\p"
	.string "I'm terribly sorry.\p"
	.string "You must have a TICKET to board\n"
	.string "the ferry.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "{PLAYER} flashed the TICKET.\p"
	.string "Perfect! That's all you need!\p"
	.string "And where would you like to go?$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "SLATEPORT CITY it is, then!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "LILYCOVE CITY it is, then!$"

BattleFrontier_OutsideWest_Text_Route103ItIs:
	.string "ROUTE 103 it is, then!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "Please sail with us another time!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "Please board the ferry and wait for\n"
	.string "departure.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "Then, where would you like to go?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "I'm the best out of all my friends.\n"
	.string "But here…\l"
	.string "I've been useless!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "I want to go to the BATTLE TOWER,\n"
	.string "but I can't find it even though I have\l"
	.string "a map of the BATTLE FRONTIER.\p"
	.string "This place is just too big!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "A fortune-teller out west, past\n"
	.string "the BATTLE DOME, told me I'd get\l"
	.string "seasick on the ferry.\p"
	.string "Urrrrp... She was right. They say\n"
	.string "she can see who's waiting at the\l"
	.string "end of your gauntlet, too.$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "Nobody stumbles onto this island\n"
	.string "by accident.\p"
	.string "SCOTT invites you, you take the\n"
	.string "ferry, and then the Eight\l"
	.string "Gauntlets decide how good you\l"
	.string "really were.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "Hey, bro… Do we even have six\n"
	.string "POKéMON?$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "Uh… The lady at the EXCHANGE\n"
	.string "CORNER sells them, bro. For FP.\p"
	.string "We have… zero FP.\p"
	.string "We're gonna need a bigger plan,\n"
	.string "bro.$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "That's the BATTLE FACTORY. It used\n"
	.string "to rent POKéMON out.\p"
	.string "Now it's locked up tight. DEVON\n"
	.string "staff only. I see people in suits\l"
	.string "going in and out at all hours.$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "The BATTLE PIKE holds gauntlet\n"
	.string "6... and I heard the PIKE QUEEN\l"
	.string "keeps a SEVIPER.\p"
	.string "I'm s-scared already, and I\n"
	.string "haven't even cleared gauntlet 3!$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "Let's play rock, paper, scissors!\n"
	.string "Winner picks which mat I start\l"
	.string "today! One, two, three!\p"
	.string "… … … … … …$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "Yay! I won! I'll go take on the\n"
	.string "Doubles mat today!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "Oh, no… I lost. Not lucky today.\p"
	.string "Doubles can wait until tomorrow.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "I believe I'm the only person here\n"
	.string "who, for some unknown reason,\l"
	.string "would choose fishing over\l"
	.string "battling.\p"
	.string "Huh? You can't catch anything\n"
	.string "here? That's disappointing…\p"
	.string "Though I hear there's someone way\n"
	.string "over on the east side, out past\l"
	.string "the ARENA, who'll sell you things\l"
	.string "before the shop even has them.\p"
	.string "Sounds fishy to me. And I'd know.$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "Today, I'm going to keep battling\n"
	.string "until I clear a gauntlet. Just\l"
	.string "one!\p"
	.string "Then the next… then the next…$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "Off to the BATTLE DOME? In there,\n"
	.string "one POKéMON on every team changes\l"
	.string "form mid-battle.\p"
	.string "Deciding which of yours does, and\n"
	.string "when, is the whole art.$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "Grandpa, over here!\n"
	.string "The BATTLE DOME is here!\l"
	.string "Go get 'em, Grandpa!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "Ah, so this here is the BATTLE DOME?\n"
	.string "I won't let GENTLEMEN beat me!\p"
	.string "But where is the entrance?$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "There used to be seven facilities\n"
	.string "here, each with its own FRONTIER\l"
	.string "BRAIN.\p"
	.string "Now it's eight gauntlets, and the\n"
	.string "BRAINS guard the end of them.\l"
	.string "SCOTT really doesn't do anything\l"
	.string "halfway.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "I've finally arrived at the BATTLE\n"
	.string "FRONTIER!\p"
	.string "I'm sure to grab attention with\n"
	.string "my looks and ability!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Munch, munch...\p"
	.string "There's an old nurse in the little\n"
	.string "house on the far west edge, just\l"
	.string "past the BATTLE DOME.\p"
	.string "She sells something she calls a\n"
	.string "SECOND WIND. Lose a battle in a\l"
	.string "gauntlet, and you get one more\l"
	.string "try. Munch...$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "Crunch, munch…\p"
	.string "I tried snacking in the TOWER\n"
	.string "lobby, and an attendant told me\l"
	.string "the no-items rule applies to me\l"
	.string "too.\p"
	.string "Crunch, munch…$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string "Huh? Will you listen to yourself?\n"
	.string "That's nothing!\p"
	.string "When TUCKER's SALAMENCE Mega\n"
	.string "Evolved, TUCKER looked right at me\l"
	.string "and sparks flew!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "Whaaaaaat?! Pfft!\p"
	.string "That only happened because I\n"
	.string "happened to be sitting next to\l"
	.string "you!\p"
	.string "The DOME ACE looked our way\n"
	.string "because my cheering was so loud!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "Oh, shush! Keep that racket down!\p"
	.string "You fair-weather fans should stick\n"
	.string "to cheering for some TOWER warden!\p"
	.string "The DOME ACE, TUCKER, is mine! The\n"
	.string "only idol for me!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "Those people squabbling over\n"
	.string "there… They were famous trainers\l"
	.string "once.\p"
	.string "Then the DOME ACE, TUCKER, beat\n"
	.string "them so thoroughly at the BATTLE\l"
	.string "DOME that they became his fans\l"
	.string "instead.\p"
	.string "Now they cheer for him every day.$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "I heard there's a POKéMON with a\n"
	.string "paintbrush for a tail that's\l"
	.string "banned from every gauntlet! Why\l"
	.string "would anyone ban something so\l"
	.string "cute? I have to find it!\p"
	.string "They say they used to live in a\n"
	.string "cave on the west side... the one\l"
	.string "you can only reach by water.\p"
	.string "But they're all gone now.\n"
	.string "Something else moved in.$"

BattleFrontier_OutsideWest_EventScript_Boy1_Text1:
	.string "I finally beat WARDEN WINONA! Then\n"
	.string "I walked onto the Doubles mat.\p"
	.string "Spread moves. Nobody back home\n"
	.string "ever used spread moves.$"

BattleFrontier_OutsideWest_EventScript_Boy1_Text0:
	.string "I was the best out of all my\n"
	.string "friends back home. Here? WARDEN\l"
	.string "WINONA's ALTARIA swept my whole\l"
	.string "team.\p"
	.string "I didn't even know you could do\n"
	.string "that.$"

BattleFrontier_OutsideWest_EventScript_ExpertM_Text5:
	.string "I found a MEGA RING. Then I found\n"
	.string "out what Mega LOPUNNY does to a\l"
	.string "team with no priority.\p"
	.string "Ahem. I'm regrouping.$"

BattleFrontier_OutsideWest_EventScript_ExpertM_Text4:
	.string "The DOME's open! They say every\n"
	.string "trainer inside can Mega Evolve.\l"
	.string "Hmph. So can I, once I find a MEGA\l"
	.string "RING.$"

BattleFrontier_OutsideWest_EventScript_ExpertM_Text0:
	.string "So this is the BATTLE DOME? Sealed\n"
	.string "tight.\p"
	.string "They say every trainer inside can\n"
	.string "Mega Evolve. When those doors\l"
	.string "open, I'll be ready.$"

BattleFrontier_OutsideWest_EventScript_Woman1_Text2:
	.string "…Gauntlet 2 was Doubles. Nobody\n"
	.string "told me about Doubles.\p"
	.string "My looks did not help at all.$"

BattleFrontier_OutsideWest_EventScript_Woman1_Text0:
	.string "I've finally arrived at the BATTLE\n"
	.string "FRONTIER! I'm going to clear all\l"
	.string "eight gauntlets with my looks and\l"
	.string "ability alone!$"

BattleFrontier_OutsideWest_EventScript_BattleDomeSign_Text4:
	.string "BATTLE DOME - GAUNTLET 5: THE MAIN\n"
	.string "EVENT.\p"
	.string "Home of the DOME ACE, TUCKER.$"

BattleFrontier_OutsideWest_EventScript_BattleDomeSign_Text0:
	.string "BATTLE DOME - GAUNTLET 5: THE MAIN\n"
	.string "EVENT.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 4.$"

BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Text0:
	.string "BATTLE FACTORY.\p"
	.string "DEVON CORPORATION. AUTHORIZED\n"
	.string "STAFF ONLY.$"

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text5:
	.string "BATTLE PIKE - GAUNTLET 6: THE\n"
	.string "CROSSROADS.\p"
	.string "Home of the PIKE QUEEN, LUCY.$"

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text0:
	.string "BATTLE PIKE - GAUNTLET 6: THE\n"
	.string "CROSSROADS.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 5.$"

BattleFrontier_OutsideWest_Text_DittoGivesItselfAway:
	.string "...\p"
	.string "......\p"
	.string "...Ditto!$"

BattleFrontier_OutsideWest_Text_DittoBanned:
	.string "Did you see that? A DITTO!\p"
	.string "Banned from every gauntlet.\n"
	.string "...Can't imagine why.$"

BattleFrontier_OutsideWest_Text_TuckerBefore:
	.string "TUCKER is practicing his bows.\p"
	.string "Oh! Audience of one? I'll take it.\p"
	.string "See you in the main event!$"

BattleFrontier_OutsideWest_Text_TuckerAfter:
	.string "Encore, encore! ...No? Fair\n"
	.string "enough. You stole the show.\p"
	.string "...You know who taught me to put\n"
	.string "on a show? Ask SCOTT sometime.\l"
	.string "Watch what face he makes.$"



@ Ten Gauntlets: the tile in front of Artisan Cave's west entrance. While the
@ Latis are waiting (FLOTSAM beaten, none caught), the player can't walk in
@ without a MASTER BALL in the bag - inside, the Lati battle is catch-only and
@ the exits are blocked, so going in without one is a soft lock. Only blocks
@ walking north, into the door: coming out, a push "back" would walk the
@ player straight into the door again.
@ The tile in front of the cave mouth only turns the player away once the
@ cave is closed: after gauntlet 4, FRONTIER staff have closed it for good.
BattleFrontier_OutsideWest_EventScript_ArmCaveClosedCheck::
	setvar VAR_TEMP_3, 1
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 4, BattleFrontier_OutsideWest_EventScript_ArmCaveClosed
	return

BattleFrontier_OutsideWest_EventScript_ArmCaveClosed::
	setvar VAR_TEMP_3, 0
	return

BattleFrontier_OutsideWest_EventScript_CaveClosed::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_ne VAR_RESULT, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CaveClosedEnd
	lockall
	msgbox BattleFrontier_OutsideWest_Text_CaveClosed, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
BattleFrontier_OutsideWest_EventScript_CaveClosedEnd:
	end

BattleFrontier_OutsideWest_Text_CaveClosed:
	.string "A sign is posted over the\n"
	.string "entrance:\p"
	.string "“FRONTIER staff has closed the\n"
	.string "cave.”$"

@ Ten Gauntlets: Birch's lab arc, after gauntlet 5 (storyline.md).
@ VAR_BIRCH_STORY_STATE: 0 none, 1 the Pike door scene, 2 the lab door,
@ 3 inside the lab, 4 Wallace flies off and the rival stays, 5 the family
@ scene, 6 SCOTT at the Pike.
@ The rival blocks the Pike's doorstep (42, 28) once gauntlet 5 is cleared.
@ The little plaza in front of it is only reachable from the north (x 39-40)
@ or up the lane from the south (x 40-42), so the five tiles where those
@ enter it trigger the scene. Each walks the player to (42, 30); the rival
@ steps round them and runs off down the lane (x 42), the way WALLACE comes
@ in. At state 5, SCOTT comes up the same lane to meet the player on the
@ doorstep.
BattleFrontier_OutsideWest_EventScript_SetupPikeStory::
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_HIDE_BIRCH_STORY_PIKE_WALLACE
	setflag FLAG_TEMP_7
	setvar VAR_TEMP_4, 1
	setvar VAR_TEMP_5, 1
	call_if_eq VAR_BIRCH_STORY_STATE, 5, BattleFrontier_OutsideWest_EventScript_ArmPikeScott
	goto_if_ne VAR_BIRCH_STORY_STATE, 0, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_lt VAR_RESULT, 5, Common_EventScript_NopReturn
	setvar VAR_TEMP_4, 0
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, BattleFrontier_OutsideWest_EventScript_ShowPikeMay
	clearflag FLAG_TEMP_5
	return

BattleFrontier_OutsideWest_EventScript_ShowPikeMay::
	clearflag FLAG_TEMP_4
	return

BattleFrontier_OutsideWest_EventScript_ArmPikeScott::
	setvar VAR_TEMP_5, 0
	return

BattleFrontier_OutsideWest_EventScript_PikeRival::
	msgbox BattleFrontier_OutsideWest_Text_PikeRivalGoHome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_PikeRivalSceneA::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_PlayerFromA
	goto BattleFrontier_OutsideWest_EventScript_PikeRivalScene

BattleFrontier_OutsideWest_EventScript_PikeRivalSceneB::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_PlayerFromB
	goto BattleFrontier_OutsideWest_EventScript_PikeRivalScene

BattleFrontier_OutsideWest_EventScript_PikeRivalSceneC::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_PlayerFromC
	goto BattleFrontier_OutsideWest_EventScript_PikeRivalScene

BattleFrontier_OutsideWest_EventScript_PikeRivalSceneD::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_PlayerFromD
	goto BattleFrontier_OutsideWest_EventScript_PikeRivalScene

BattleFrontier_OutsideWest_EventScript_PikeRivalSceneE::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_PlayerFromE
	goto BattleFrontier_OutsideWest_EventScript_PikeRivalScene

BattleFrontier_OutsideWest_EventScript_PikeRivalScene::
	waitmovement 0
	setvar VAR_TEMP_4, 1
	checkplayergender
	setvar VAR_0x8004, LOCALID_FRONTIER_PIKE_MAY
	call_if_eq VAR_RESULT, FEMALE, BattleFrontier_OutsideWest_EventScript_PikeRivalIsBrendan
	playse SE_PIN
	applymovement VAR_0x8004, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_PikeRivalDistress, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8004, BattleFrontier_OutsideWest_Movement_RivalRunsOff
	waitmovement 0
	removeobject VAR_0x8004
	setvar VAR_BIRCH_STORY_STATE, 1
	delay 30
	clearflag FLAG_HIDE_BIRCH_STORY_PIKE_WALLACE
	addobject LOCALID_FRONTIER_WALLACE
	applymovement LOCALID_FRONTIER_WALLACE, BattleFrontier_OutsideWest_Movement_WallaceIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_PikeWallace, MSGBOX_DEFAULT
	closemessage
	@ He slipped past the guards, so he leaves the quick way: flying off on
	@ the same bird he uses in LITTLEROOT.
	applymovement LOCALID_FRONTIER_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_FRONTIER_WALLACE
	waitfieldeffect FLDEFF_NPCFLY_OUT
	releaseall
	end

BattleFrontier_OutsideWest_EventScript_PikeRivalIsBrendan::
	setvar VAR_0x8004, LOCALID_FRONTIER_PIKE_BRENDAN
	return

BattleFrontier_OutsideWest_EventScript_PikeScott::
	lockall
	setvar VAR_TEMP_5, 1
	clearflag FLAG_TEMP_7
	addobject LOCALID_FRONTIER_PIKE_SCOTT
	applymovement LOCALID_FRONTIER_PIKE_SCOTT, BattleFrontier_OutsideWest_Movement_ScottIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_PikeScott, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_PIKE_SCOTT, BattleFrontier_OutsideWest_Movement_ScottOut
	waitmovement 0
	removeobject LOCALID_FRONTIER_PIKE_SCOTT
	setvar VAR_BIRCH_STORY_STATE, 6
	releaseall
	end

@ Every start ends at (42, 30), two tiles below the rival, facing up.
BattleFrontier_OutsideWest_Movement_PlayerFromA:
	walk_right
	walk_right
	walk_right
	walk_down
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_PlayerFromB:
	walk_right
	walk_right
	walk_down
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_PlayerFromC:
	walk_right
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_PlayerFromD:
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_PlayerFromE:
	walk_up
	face_up
	step_end

@ Round the player at (42, 30), then down the lane, out of sight at (42, 38).
BattleFrontier_OutsideWest_Movement_RivalRunsOff:
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

BattleFrontier_OutsideWest_Movement_WallaceIn:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideWest_Movement_ScottIn:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideWest_Movement_ScottOut:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

BattleFrontier_OutsideWest_Text_PikeRivalDistress:
	.string "{RIVAL}: {PLAYER}! There you are!\n"
	.string "I've been looking everywhere for\l"
	.string "you!\p"
	.string "Mom just called. Some men from\n"
	.string "DEVON showed up at the lab, and\l"
	.string "they won't let Dad leave.\p"
	.string "She says they're holding him\n"
	.string "there. Like a hostage!\p"
	.string "I have to get home. Right now!$"

BattleFrontier_OutsideWest_Text_PikeRivalGoHome:
	.string "{RIVAL}: I have to get home!$"

BattleFrontier_OutsideWest_Text_PikeWallace:
	.string "WALLACE: Forgive me. I couldn't\n"
	.string "help overhearing.\p"
	.string "I'm WALLACE. I believe STEVEN has\n"
	.string "mentioned me. He asked me to check\l"
	.string "in on you.\p"
	.string "I slipped past the guards to get\n"
	.string "here. They run a tight ship on\l"
	.string "this island, so I can't stay long\l"
	.string "before someone notices.\p"
	.string "But DEVON's men holding a\n"
	.string "PROFESSOR in his own lab... That's\l"
	.string "no small matter.\p"
	.string "I'm going to LITTLEROOT to see\n"
	.string "what's going on.$"

BattleFrontier_OutsideWest_Text_PikeScott:
	.string "SCOTT: {PLAYER}! Hold on a moment.\p"
	.string "I heard about the business at\n"
	.string "PROF. BIRCH's lab. PRESIDENT STONE\l"
	.string "was way out of line.\p"
	.string "I called him myself and handled\n"
	.string "it. Your gauntlet should be back\l"
	.string "up and running.\p"
	.string "There's something else. My men\n"
	.string "have spotted STEVEN lurking around\l"
	.string "the FRONTIER.\p"
	.string "STEVEN and I don't have the best\n"
	.string "relationship. He's always been out\l"
	.string "to get me.\p"
	.string "When the FRONTIER first opened, he\n"
	.string "wasn't a fan. He told me there's\l"
	.string "more to POKéMON than battling and\l"
	.string "mini-games.\p"
	.string "Then he beat the whole FRONTIER\n"
	.string "faster than anyone before him,\l"
	.string "just to prove his point.\p"
	.string "I built the EIGHT GAUNTLETS to\n"
	.string "improve on the experience. But\l"
	.string "there's still bad blood between\l"
	.string "us.\p"
	.string "So if STEVEN ever approaches you,\n"
	.string "be aware. He may say things about\l"
	.string "me that aren't true.\p"
	.string "Well! Good luck in there, {PLAYER}.$"

BattleFrontier_OutsideWest_Text_LucyBefore:
	.string "LUCY is staring at the PIKE's\n"
	.string "door.\p"
	.string "...Every team in there takes one\n"
	.string "of four roads. Read yours early.\p"
	.string "...That's all.$"

BattleFrontier_OutsideWest_Text_LucyAfter:
	.string "LUCY: ...You beat me.\p"
	.string "SCOTT asked about you afterwards.\n"
	.string "More than once.\p"
	.string "...I'd watch that.$"

@ Ten Gauntlets: STEVEN waits outside the Battle Factory once gauntlet 2 is
@ cleared, until the player has spoken to him (the script is
@ BattleFrontier_Steven_EventScript_Steven, in Outside East). Keyed off the
@ cleared count, not just the attendant's hint, so a save that cleared
@ gauntlet 2 before this existed still finds him.
BattleFrontier_OutsideWest_EventScript_SetupSteven::
	setflag FLAG_TEMP_8
	goto_if_ge VAR_STEVEN_STORY_STATE, 2, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_lt VAR_RESULT, 2, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_8
	return

@ ============================================================================
@ Ten Gauntlets: the Broker's letter, after gauntlet 6 (storyline.md).
@ VAR_BROKER_STORY_STATE: 0 none, 1 gauntlet 6 cleared (STEVEN waits outside
@ the Pike), 2 following STEVEN to the Pokemon Center, 3 the Center scene
@ done (SCOTT and his men outside it), 4 SCOTT headed for the Broker's, 5 the
@ Broker arrested and the LETTER in hand (STEVEN on the ledge above the
@ Pyramid), 6 the LETTER delivered (WALLACE waits on the way back), 7 WALLACE
@ asked for help (his ABRA waits by the Pokemon Center; he waits outside the
@ POKEMON LEAGUE), 8 he's gone in (the scene plays in the lobby), 9 the scene
@ done, MAXIE and ARCHIE still to beat (talk to WALLACE), 10 beaten (the
@ ABRA brings the player home), 11 done.
@ Gauntlet 7 (the Palace) stays closed until 11. The scenes after the Pike
@ are in the Pokemon Center, Outside East and EVER GRANDE CITY.
@ ============================================================================

@ Clearing gauntlet 6 starts the arc the next time the player is out here
@ (always the Pike's doorstep, in practice). Only on exactly six cleared, so
@ a save already past gauntlet 7 never sees it. STEVEN only walks up when
@ the player has just come out of the Pike (on its door tile until the
@ step down), and SCOTT's house is locked while he's away: from the moment
@ he leaves for the Broker's until gauntlet 7 is cleared.
BattleFrontier_OutsideWest_EventScript_SetupBrokerStory::
	setflag FLAG_HIDE_BROKER_STORY_PIKE_STEVEN
	setflag FLAG_HIDE_BROKER_STORY_FACTORY_LOOKER
	setvar VAR_TEMP_6, 1
	call_if_ge VAR_BROKER_STORY_STATE, 6, BattleFrontier_OutsideWest_EventScript_ShowFactoryLooker
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ne VAR_RESULT, 6, Common_EventScript_NopReturn
	call_if_eq VAR_BROKER_STORY_STATE, 0, BattleFrontier_OutsideWest_EventScript_BrokerStoryStart
	call_if_ge VAR_BROKER_STORY_STATE, 4, BattleFrontier_OutsideWest_EventScript_LockScottsHouse
	goto_if_ne VAR_BROKER_STORY_STATE, 1, Common_EventScript_NopReturn
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 42, Common_EventScript_NopReturn
	goto_if_ne VAR_0x8005, 27, Common_EventScript_NopReturn
	setvar VAR_TEMP_7, 1
	return

BattleFrontier_OutsideWest_EventScript_BrokerStoryStart::
	setvar VAR_BROKER_STORY_STATE, 1
	return

BattleFrontier_OutsideWest_EventScript_LockScottsHouse::
	setvar VAR_TEMP_6, 0
	return

BattleFrontier_OutsideWest_EventScript_ShowFactoryLooker::
	clearflag FLAG_HIDE_BROKER_STORY_FACTORY_LOOKER
	return

@ STEVEN comes up the lane (the way WALLACE and SCOTT came for the Birch arc)
@ to the player on the Pike's doorstep, then leads them back down it. The
@ walk to the Pokemon Center crosses into Outside East, so it fades out and
@ picks up inside.
BattleFrontier_OutsideWest_EventScript_PikeSteven::
	lockall
	setvar VAR_TEMP_7, 0
	clearflag FLAG_HIDE_BROKER_STORY_PIKE_STEVEN
	addobject LOCALID_FRONTIER_PIKE_STEVEN
	applymovement LOCALID_FRONTIER_PIKE_STEVEN, BattleFrontier_OutsideWest_Movement_PikeStevenIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_PikeSteven, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_PIKE_STEVEN, BattleFrontier_OutsideWest_Movement_PikeStevenOut
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_PikePlayerFollows
	waitmovement 0
	setvar VAR_BROKER_STORY_STATE, 2
	warp MAP_BATTLE_FRONTIER_POKEMON_CENTER_1F, 7, 8
	waitstate
	releaseall
	end

@ Up the lane to (42, 29), just below the player.
BattleFrontier_OutsideWest_Movement_PikeStevenIn:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideWest_Movement_PikeStevenOut:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

BattleFrontier_OutsideWest_Movement_PikePlayerFollows:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ The trigger sits on the tile below the door; stepping onto it from any
@ side bounces the player back the way they came, so the door can't be
@ reached while SCOTT is away.
BattleFrontier_OutsideWest_EventScript_ScottsHouseLocked::
	lockall
	specialvar VAR_RESULT, GetPlayerFacingDirection
	msgbox BattleFrontier_OutsideWest_Text_ScottsHouseLocked, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_RESULT, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_LockedStepDown
	call_if_eq VAR_RESULT, DIR_WEST, BattleFrontier_OutsideWest_EventScript_LockedStepRight
	call_if_eq VAR_RESULT, DIR_EAST, BattleFrontier_OutsideWest_EventScript_LockedStepLeft
	waitmovement 0
	releaseall
	end

BattleFrontier_OutsideWest_EventScript_LockedStepDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	return

BattleFrontier_OutsideWest_EventScript_LockedStepRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	return

BattleFrontier_OutsideWest_EventScript_LockedStepLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	return

@ LOOKER watches the Factory from across the plaza, where STEVEN asked him to
@ find out where the Broker was taken.
BattleFrontier_OutsideWest_EventScript_FactoryLooker::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FactoryLooker, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_Text_PikeSteven:
	.string "STEVEN: {PLAYER}. Congratulations\n"
	.string "on LUCY.\p"
	.string "We need to talk. But not here.\p"
	.string "SCOTT's men have been tracking me\n"
	.string "around the island. I'd rather not\l"
	.string "give them a show.\p"
	.string "Follow me. And try to look like\n"
	.string "you're just out for a walk.$"

BattleFrontier_OutsideWest_Text_ScottsHouseLocked:
	.string "The door is locked.$"

BattleFrontier_OutsideWest_Text_FactoryLooker:
	.string "LOOKER: Shh! {PLAYER}! Not so loud!\n"
	.string "I am on a stakeout!\p"
	.string "STEVEN asked me to find out where\n"
	.string "they took the one they call the\l"
	.string "BROKER.\p"
	.string "And I have found it! They marched\n"
	.string "him straight through the doors of\l"
	.string "the BATTLE FACTORY.\p"
	.string "“DEVON staff only.” Hmph. Nobody\n"
	.string "has come out since.\p"
	.string "I will keep watching. You keep\n"
	.string "winning, yes? And act natural!$"

@ ============================================================================
@ TESTING ONLY - remove before release. The man on the ferry dock hands out a
@ level 100 MIRAIDON, as many times as asked, to speed through playtests.
@ To undo: point his object in map.json back at
@ BattleFrontier_OutsideWest_EventScript_Man3 and delete this block.
@ ============================================================================
BattleFrontier_OutsideWest_EventScript_TestMiraidon::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_TestMiraidonOffer, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, BattleFrontier_OutsideWest_EventScript_TestMiraidonEnd
	givemon SPECIES_MIRAIDON, 100
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BattleFrontier_OutsideWest_EventScript_TestMiraidonNoRoom
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_OutsideWest_Text_TestMiraidonReceived
	waitmessage
	waitfanfare
	waitbuttonpress
BattleFrontier_OutsideWest_EventScript_TestMiraidonEnd:
	release
	end

BattleFrontier_OutsideWest_EventScript_TestMiraidonNoRoom::
	msgbox BattleFrontier_OutsideWest_Text_TestMiraidonNoRoom, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_Text_TestMiraidonOffer:
	.string "TEST: Want a level 100 MIRAIDON?$"

BattleFrontier_OutsideWest_Text_TestMiraidonReceived:
	.string "{PLAYER} received a MIRAIDON!$"

BattleFrontier_OutsideWest_Text_TestMiraidonNoRoom:
	.string "TEST: No room in your party or PC.$"

@ ============================================================================
@ Ten Gauntlets: a facility that isn't open yet keeps its door shut - walking
@ into it does nothing (IsFacilityLobbyDoorLocked, src/facility.c, checked in
@ TryDoorWarp). Inspecting the door says why. Once it opens, these do nothing.
@ ============================================================================

BattleFrontier_OutsideWest_EventScript_DomeDoor::
	special IsBattleDomeUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideWest_EventScript_DomeDoorOpen
	msgbox BattleFrontier_OutsideWest_Text_DomeDoorLocked, MSGBOX_SIGN
BattleFrontier_OutsideWest_EventScript_DomeDoorOpen:
	end

BattleFrontier_OutsideWest_EventScript_FactoryDoor::
	special IsBattleFactoryUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideWest_EventScript_FactoryDoorOpen
	msgbox BattleFrontier_OutsideWest_Text_FactoryDoorLocked, MSGBOX_SIGN
BattleFrontier_OutsideWest_EventScript_FactoryDoorOpen:
	end

BattleFrontier_OutsideWest_EventScript_PikeDoor::
	special IsBattlePikeUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideWest_EventScript_PikeDoorOpen
	msgbox BattleFrontier_OutsideWest_Text_PikeDoorLocked, MSGBOX_SIGN
BattleFrontier_OutsideWest_EventScript_PikeDoorOpen:
	end

BattleFrontier_OutsideWest_Text_DomeDoorLocked:
	.string "The doors are shut. The BATTLE\n"
	.string "DOME isn't open yet.$"

BattleFrontier_OutsideWest_Text_FactoryDoorLocked:
	.string "The doors are locked. A sign reads:\p"
	.string "“DEVON PERSONNEL ONLY.”$"

BattleFrontier_OutsideWest_Text_PikeDoorLocked:
	.string "The doors are shut. The BATTLE\n"
	.string "PIKE isn't open yet.$"

@ ============================================================================
@ Ten Gauntlets: the Crown is taken, after gauntlet 7 (storyline.md;
@ VAR_CROWN_STORY_STATE is explained in LittlerootTown). State 7: on the row
@ below the Factory's doors, SCOTT (7, 39) and his MEWTWO (8, 39) face STEVEN
@ (14, 39) and his DIALGA (12, 39). Walking up the courtyard (row 42) plays
@ the standoff. State 8: STEVEN stays, beaten, to hand back the Lati.
@ ============================================================================

BattleFrontier_OutsideWest_EventScript_SetupCrownStory::
	setflag FLAG_HIDE_CROWN_STORY_FACTORY_SCOTT
	setflag FLAG_HIDE_CROWN_STORY_MEWTWO
	setflag FLAG_HIDE_CROWN_STORY_MEGA_MEWTWO
	setflag FLAG_HIDE_CROWN_STORY_DIALGA
	setflag FLAG_HIDE_CROWN_STORY_FACTORY_STEVEN
	setvar VAR_TEMP_8, 1
	goto_if_eq VAR_CROWN_STORY_STATE, 8, BattleFrontier_OutsideWest_EventScript_ShowBeatenSteven
	goto_if_ne VAR_CROWN_STORY_STATE, 7, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_CROWN_STORY_FACTORY_SCOTT
	clearflag FLAG_HIDE_CROWN_STORY_MEWTWO
	clearflag FLAG_HIDE_CROWN_STORY_DIALGA
	clearflag FLAG_HIDE_CROWN_STORY_FACTORY_STEVEN
	setvar VAR_TEMP_8, 0
	return

BattleFrontier_OutsideWest_EventScript_ShowBeatenSteven::
	clearflag FLAG_HIDE_CROWN_STORY_FACTORY_STEVEN
	setobjectmovementtype LOCALID_FRONTIER_CROWN_STEVEN, MOVEMENT_TYPE_FACE_DOWN
	return

@ The player comes up the courtyard to (11, 41), below the gap between the
@ two POKéMON. The CROWN Mega Evolves MEWTWO with no KEY STONE (a second
@ object, swapped in under a white flash). Each attack is a lunge into the
@ gap and back, with the screen shaking.
BattleFrontier_OutsideWest_EventScript_CrownStandoff::
	lockall
	setvar VAR_TEMP_8, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 9, BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom9
	call_if_eq VAR_0x8004, 10, BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom10
	call_if_eq VAR_0x8004, 11, BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom11
	call_if_eq VAR_0x8004, 12, BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom12
	call_if_eq VAR_0x8004, 13, BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom13
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_Standoff1, MSGBOX_DEFAULT
	closemessage
	@ The CROWN.
	playse SE_M_DETECT
	msgbox BattleFrontier_OutsideWest_Text_ScottRaisesCrown, MSGBOX_DEFAULT
	closemessage
	waitse
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_FRONTIER_CROWN_MEWTWO
	clearflag FLAG_HIDE_CROWN_STORY_MEGA_MEWTWO
	addobject LOCALID_FRONTIER_CROWN_MEGA_MEWTWO
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_MEWTWO_MEGA_Y, CRY_MODE_ENCOUNTER
	msgbox BattleFrontier_OutsideWest_Text_MewtwoMegaEvolved, MSGBOX_DEFAULT
	waitmoncry
	msgbox BattleFrontier_OutsideWest_Text_Standoff2, MSGBOX_DEFAULT
	closemessage
	@ Roar of Time.
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_FRONTIER_CROWN_DIALGA, BattleFrontier_OutsideWest_Movement_LungeLeft
	waitmovement 0
	playse SE_M_HYPER_BEAM
	call BattleFrontier_OutsideWest_EventScript_CrownShake
	waitse
	msgbox BattleFrontier_OutsideWest_Text_MewtwoHangsOn, MSGBOX_DEFAULT
	closemessage
	@ Aura Sphere.
	applymovement LOCALID_FRONTIER_CROWN_MEGA_MEWTWO, BattleFrontier_OutsideWest_Movement_LungeRight
	waitmovement 0
	playse SE_M_EXPLOSION
	call BattleFrontier_OutsideWest_EventScript_CrownShake
	waitse
	playmoncry SPECIES_DIALGA, CRY_MODE_FAINT
	waitmoncry
	removeobject LOCALID_FRONTIER_CROWN_DIALGA
	msgbox BattleFrontier_OutsideWest_Text_DialgaFainted, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_OPEN
	removeobject LOCALID_FRONTIER_CROWN_MEGA_MEWTWO
	waitse
	msgbox BattleFrontier_OutsideWest_Text_Standoff3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_CROWN_SCOTT, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_ScottRemindsPlayer, MSGBOX_DEFAULT
	closemessage
	@ SCOTT goes into the Factory, where the CROWN is.
	applymovement LOCALID_FRONTIER_CROWN_SCOTT, BattleFrontier_OutsideWest_Movement_ScottToFactoryDoor
	waitmovement 0
	opendoor 11, 38
	waitdooranim
	applymovement LOCALID_FRONTIER_CROWN_SCOTT, BattleFrontier_OutsideWest_Movement_ScottIntoFactory
	waitmovement 0
	removeobject LOCALID_FRONTIER_CROWN_SCOTT
	closedoor 11, 38
	waitdooranim
	setvar VAR_CROWN_STORY_STATE, 8
	releaseall
	end

BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom9::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_CrownFrom9
	return

BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom10::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_CrownFrom10
	return

BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom11::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_CrownFrom11
	return

BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom12::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_CrownFrom12
	return

BattleFrontier_OutsideWest_EventScript_CrownPlayerFrom13::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_CrownFrom13
	return

BattleFrontier_OutsideWest_EventScript_CrownShake::
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12 @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	return

@ STEVEN, beaten, by the Factory (state 8). SCOTT already knows about the
@ Lati, so there's no use hiding it any more: STEVEN gives it back with its
@ Mega Stone (GiveStevenLatiBack in src/facility.c). With SCOTT's new
@ counterfeits on, it won't grow until the New Mauville overclock. Then he
@ leaves, on foot: his team is down.
BattleFrontier_OutsideWest_EventScript_CrownSteven::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_StevenFailed, MSGBOX_DEFAULT
	special GiveStevenLatiBack
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BattleFrontier_OutsideWest_EventScript_StevenNoRoom
	copyvar VAR_0x8006, VAR_RESULT
	setvar VAR_0x8004, SPECIES_LATIAS
	call_if_set FLAG_STEVEN_HAS_LATIOS, BattleFrontier_OutsideWest_EventScript_StevenLatiIsLatios
	bufferspeciesname STR_VAR_1, VAR_0x8004
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_OutsideWest_Text_ReceivedLati
	waitmessage
	waitfanfare
	waitbuttonpress
	call_if_eq VAR_0x8006, MON_GIVEN_TO_PC, BattleFrontier_OutsideWest_EventScript_LatiSentToPC
	msgbox BattleFrontier_OutsideWest_Text_StevenGoodbye, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CROWN_STORY_STATE, 9
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_OutsideWest_EventScript_StevenLatiIsLatios::
	setvar VAR_0x8004, SPECIES_LATIOS
	return

BattleFrontier_OutsideWest_EventScript_LatiSentToPC::
	msgbox BattleFrontier_OutsideWest_Text_LatiSentToPC, MSGBOX_DEFAULT
	return

BattleFrontier_OutsideWest_EventScript_StevenNoRoom::
	msgbox BattleFrontier_OutsideWest_Text_StevenNoRoom, MSGBOX_DEFAULT
	release
	end

@ Every start on row 42 ends at (11, 41), facing up.
BattleFrontier_OutsideWest_Movement_CrownFrom9:
	walk_right
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_CrownFrom10:
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_CrownFrom11:
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_CrownFrom12:
	walk_left
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_CrownFrom13:
	walk_left
	walk_left
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_LungeLeft:
	lock_facing_direction
	walk_faster_left
	delay_8
	walk_right
	unlock_facing_direction
	step_end

BattleFrontier_OutsideWest_Movement_LungeRight:
	lock_facing_direction
	walk_faster_right
	delay_8
	walk_left
	unlock_facing_direction
	step_end

@ From (7, 39) along to (11, 39), below the doors, then in.
BattleFrontier_OutsideWest_Movement_ScottToFactoryDoor:
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_ScottIntoFactory:
	walk_up
	set_invisible
	step_end

BattleFrontier_OutsideWest_Text_Standoff1:
	.string "STEVEN: It's over, SCOTT.\p"
	.string "I heard every word in LITTLEROOT.\n"
	.string "Taking a child's parents as\l"
	.string "hostages...\p"
	.string "Release them. And the BROKER. Now.\p"
	.string "SCOTT: Over? Heheh...\p"
	.string "STEVEN. You always did like the\n"
	.string "sound of your own voice.\p"
	.string "Let me show you something.$"

BattleFrontier_OutsideWest_Text_ScottRaisesCrown:
	.string "SCOTT raised the CROWN!$"

BattleFrontier_OutsideWest_Text_MewtwoMegaEvolved:
	.string "MEWTWO Mega Evolved into\n"
	.string "MEGA MEWTWO Y!$"

BattleFrontier_OutsideWest_Text_Standoff2:
	.string "STEVEN: That's impossible...\p"
	.string "There's no KEY STONE. And you've\n"
	.string "never bonded with a POKéMON in\l"
	.string "your life!\p"
	.string "SCOTT: I don't need a bond.\n"
	.string "I have thousands of them.\p"
	.string "The CROWN isn't at full power yet.\n"
	.string "For now, it can only hold one MEGA\l"
	.string "EVOLUTION. Permanently.\p"
	.string "One is all I need for you.\p"
	.string "STEVEN: We'll see about that.\n"
	.string "DIALGA, Roar of Time!$"

BattleFrontier_OutsideWest_Text_MewtwoHangsOn:
	.string "MEGA MEWTWO Y hung on with 1 HP!\p"
	.string "SCOTT: MEWTWO, Aura Sphere!$"

BattleFrontier_OutsideWest_Text_DialgaFainted:
	.string "DIALGA fainted!$"

BattleFrontier_OutsideWest_Text_Standoff3:
	.string "STEVEN: ...I can't believe it.\n"
	.string "I lost.\p"
	.string "SCOTT: You really thought I wasn't\n"
	.string "prepared to face even you?\p"
	.string "Get lost, STEVEN.$"

BattleFrontier_OutsideWest_Text_ScottRemindsPlayer:
	.string "SCOTT: {PLAYER}. Remember our\n"
	.string "arrangement.\p"
	.string "I can tell this little stunt wasn't\n"
	.string "your idea. That's the only reason\l"
	.string "the deal still stands.\p"
	.string "Gauntlet 8. Don't keep me waiting.$"

BattleFrontier_OutsideWest_Text_StevenFailed:
	.string "STEVEN: I failed, {PLAYER}.\p"
	.string "I'm sorry. I thought I was strong\n"
	.string "enough.\p"
	.string "Your family is in SCOTT's hands now.\n"
	.string "As long as they are, the best thing\l"
	.string "you can do for them is what he\l"
	.string "wants.\p"
	.string "Win gauntlet 8.\p"
	.string "And take this back. SCOTT already\n"
	.string "knows about it, so there's no use\l"
	.string "hiding it any longer.$"

BattleFrontier_OutsideWest_Text_ReceivedLati:
	.string "{PLAYER} received {STR_VAR_1}\n"
	.string "back from STEVEN!$"

BattleFrontier_OutsideWest_Text_LatiSentToPC:
	.string "{STR_VAR_1} was sent to the PC.$"

BattleFrontier_OutsideWest_Text_StevenGoodbye:
	.string "STEVEN: It's holding its MEGA\n"
	.string "STONE. You'll need everything you\l"
	.string "have for THE SUMMIT.\p"
	.string "With SCOTT's new badges on you, it\n"
	.string "won't grow. But it's free of his\l"
	.string "chips, and it's yours.\p"
	.string "...I'll be in touch.$"

BattleFrontier_OutsideWest_Text_StevenNoRoom:
	.string "STEVEN: Your party and your PC are\n"
	.string "both full. Make some room, and\l"
	.string "come back to me.$"

@ ============================================================================
@ Ten Gauntlets: while the player fights through the Devon Factory (endgame
@ states 3-4, storyline.md), NURSE JOY waits beside its door as a quick heal.
@ She won't heal SCOTT's side, but she helps the player; a white-out still
@ lands at her POKEMON CENTER. Once SCOTT is gone she's back at her counter.
@ ============================================================================
BattleFrontier_OutsideWest_EventScript_SetupFactoryJoy::
	setflag FLAG_HIDE_FACTORY_JOY
	special IsBattleFactoryUnlocked
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_SetupFactoryJoyEnd
	goto_if_ge VAR_ENDGAME_STATE, 5, BattleFrontier_OutsideWest_EventScript_SetupFactoryJoyEnd
	clearflag FLAG_HIDE_FACTORY_JOY
BattleFrontier_OutsideWest_EventScript_SetupFactoryJoyEnd:
	return

BattleFrontier_OutsideWest_EventScript_FactoryJoy::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FactoryJoy, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox BattleFrontier_OutsideWest_Text_FactoryJoyDone, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_Text_FactoryJoy:
	.string "SCOTT's people won't get a single\n"
	.string "heal from me. You're another story.\p"
	.string "Let me see your team.$"

BattleFrontier_OutsideWest_Text_FactoryJoyDone:
	.string "All better! Come back any time you\n"
	.string "need me. I'll be right here.\p"
	.string "And if you fall in there, you'll wake\n"
	.string "up at my CENTER. Someone will be\l"
	.string "at the counter.$"

@ ============================================================================
@ Ten Gauntlets: the endgame after gauntlet 8 (storyline.md; VAR_ENDGAME_STATE
@ is explained in BattleFrontier_OutsideEast). The Brains who loiter out here
@ are in the Factory, then gone with SCOTT. State 2: WALLACE waits at the
@ Factory door, PALKIA out in front of him at (11, 40); walking up the
@ courtyard (row 43) plays the scene that blasts the door open. The harsh
@ sunlight shows in states 1-4 (see BattleFrontier_OutsideEast).
@ ============================================================================

BattleFrontier_OutsideWest_EventScript_SetupEndgame::
	setflag FLAG_HIDE_ENDGAME_DOOR_WALLACE
	setflag FLAG_HIDE_ENDGAME_DOOR_PALKIA
	setvar VAR_TEMP_9, 1
	goto_if_eq VAR_ENDGAME_STATE, 0, Common_EventScript_NopReturn
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	call_if_lt VAR_ENDGAME_STATE, 5, BattleFrontier_OutsideWest_EventScript_EndgameSunlight
	goto_if_ne VAR_ENDGAME_STATE, 2, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_ENDGAME_DOOR_WALLACE
	clearflag FLAG_HIDE_ENDGAME_DOOR_PALKIA
	setvar VAR_TEMP_9, 0
	return

BattleFrontier_OutsideWest_EventScript_EndgameSunlight::
	setweather WEATHER_DROUGHT
	return

BattleFrontier_OutsideWest_EventScript_DoorWallace::
	msgbox BattleFrontier_OutsideWest_Text_DoorWallaceWaiting, MSGBOX_NPC
	end

@ The player comes up the courtyard to (11, 42), below PALKIA. The blast is a
@ lunge at the door, a white flash and a shake; the door is open from then on
@ (SetBattleFactoryUnlocked). NURSE JOY walks up from the south to (11, 43),
@ then takes her post beside the door at (13, 38). WALLACE goes in first.
BattleFrontier_OutsideWest_EventScript_FactoryDoorScene::
	lockall
	setvar VAR_TEMP_9, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 9, BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom9
	call_if_eq VAR_0x8004, 10, BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom10
	call_if_eq VAR_0x8004, 11, BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom11
	call_if_eq VAR_0x8004, 12, BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom12
	call_if_eq VAR_0x8004, 13, BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom13
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_DoorWallace1, MSGBOX_DEFAULT
	closemessage
	@ Spacial Rend.
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_FRONTIER_ENDGAME_DOOR_PALKIA, BattleFrontier_OutsideWest_Movement_PalkiaLungeUp
	waitmovement 0
	playse SE_M_EXPLOSION
	fadescreen FADE_TO_WHITE
	special SetBattleFactoryUnlocked
	fadescreen FADE_FROM_WHITE
	call BattleFrontier_OutsideWest_EventScript_CrownShake
	waitse
	opendoor 11, 38
	waitdooranim
	msgbox BattleFrontier_OutsideWest_Text_DoorBlasted, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_OPEN
	removeobject LOCALID_FRONTIER_ENDGAME_DOOR_PALKIA
	setflag FLAG_HIDE_ENDGAME_DOOR_PALKIA
	waitse
	msgbox BattleFrontier_OutsideWest_Text_DoorWallace2, MSGBOX_DEFAULT
	closemessage
	@ NURSE JOY.
	clearflag FLAG_HIDE_FACTORY_JOY
	setobjectxyperm LOCALID_FRONTIER_FACTORY_JOY, 11, 47
	setobjectmovementtype LOCALID_FRONTIER_FACTORY_JOY, MOVEMENT_TYPE_FACE_UP
	addobject LOCALID_FRONTIER_FACTORY_JOY
	applymovement LOCALID_FRONTIER_FACTORY_JOY, BattleFrontier_OutsideWest_Movement_JoyUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_DoorJoy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_FACTORY_JOY, BattleFrontier_OutsideWest_Movement_JoyToPost
	waitmovement 0
	setobjectxyperm LOCALID_FRONTIER_FACTORY_JOY, 13, 38
	setobjectmovementtype LOCALID_FRONTIER_FACTORY_JOY, MOVEMENT_TYPE_FACE_DOWN
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	@ WALLACE goes in first.
	applymovement LOCALID_FRONTIER_ENDGAME_DOOR_WALLACE, Common_Movement_FaceLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_DoorWallace3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_ENDGAME_DOOR_WALLACE, BattleFrontier_OutsideWest_Movement_WallaceIntoFactory
	waitmovement 0
	removeobject LOCALID_FRONTIER_ENDGAME_DOOR_WALLACE
	setflag FLAG_HIDE_ENDGAME_DOOR_WALLACE
	closedoor 11, 38
	waitdooranim
	setvar VAR_ENDGAME_STATE, 3
	releaseall
	end

BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom9::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_DoorFrom9
	return

BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom10::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_DoorFrom10
	return

BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom11::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_DoorFrom11
	return

BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom12::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_DoorFrom12
	return

BattleFrontier_OutsideWest_EventScript_DoorPlayerFrom13::
	applymovement LOCALID_PLAYER, BattleFrontier_OutsideWest_Movement_DoorFrom13
	return

@ Every start on row 43 ends at (11, 42), facing up.
BattleFrontier_OutsideWest_Movement_DoorFrom9:
	walk_right
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_DoorFrom10:
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_DoorFrom11:
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_DoorFrom12:
	walk_left
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_DoorFrom13:
	walk_left
	walk_left
	walk_up
	face_up
	step_end

BattleFrontier_OutsideWest_Movement_PalkiaLungeUp:
	walk_fast_up
	walk_fast_down
	face_up
	step_end

@ From (11, 47) up to (11, 43), below the player.
BattleFrontier_OutsideWest_Movement_JoyUp:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ From (11, 43) round the player to her post at (13, 38).
BattleFrontier_OutsideWest_Movement_JoyToPost:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

@ From (12, 41) to the door at (11, 38).
BattleFrontier_OutsideWest_Movement_WallaceIntoFactory:
	walk_up
	walk_left
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideWest_Text_DoorWallaceWaiting:
	.string "WALLACE: SCOTT sealed this door\n"
	.string "from the inside. Come here,\l"
	.string "{PLAYER}.$"

BattleFrontier_OutsideWest_Text_DoorWallace1:
	.string "WALLACE: SCOTT has sealed the door\n"
	.string "from the inside.\p"
	.string "No matter. Stand back, {PLAYER}.\p"
	.string "PALKIA! Spacial Rend!$"

BattleFrontier_OutsideWest_Text_DoorBlasted:
	.string "The FACTORY's door was blasted\n"
	.string "open!$"

BattleFrontier_OutsideWest_Text_DoorWallace2:
	.string "WALLACE: That will do. Good work,\n"
	.string "PALKIA.$"

BattleFrontier_OutsideWest_Text_DoorJoy:
	.string "NURSE JOY: {PLAYER}! WALLACE!\p"
	.string "Whatever SCOTT is up to in there,\n"
	.string "it can't be good.\p"
	.string "I want to help the cause. I'll stand\n"
	.string "right outside the FACTORY.\p"
	.string "Come to me whenever your team needs\n"
	.string "healing!$"

BattleFrontier_OutsideWest_Text_DoorWallace3:
	.string "WALLACE: Thank you, NURSE JOY.\p"
	.string "I'll go in first, {PLAYER}.\n"
	.string "Stay close behind me.$"
