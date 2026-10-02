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
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

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
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

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
	.string "enough. You earned the crown.\p"
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
	setflag FLAG_TEMP_6
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
	clearflag FLAG_TEMP_6
	addobject LOCALID_FRONTIER_WALLACE
	applymovement LOCALID_FRONTIER_WALLACE, BattleFrontier_OutsideWest_Movement_WallaceIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_PikeWallace, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_WALLACE, BattleFrontier_OutsideWest_Movement_WallaceOut
	waitmovement 0
	removeobject LOCALID_FRONTIER_WALLACE
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

BattleFrontier_OutsideWest_Movement_WallaceOut:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
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
@ Pyramid), 6 the LETTER delivered (WALLACE waits on the way back), 7 done.
@ Gauntlet 7 (the Palace) stays closed until 6. The scenes after the Pike
@ are in the Pokemon Center and Outside East.
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
