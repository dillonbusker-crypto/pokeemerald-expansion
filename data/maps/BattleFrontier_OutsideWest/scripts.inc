BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

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
	specialvar VAR_RESULT, GetGauntletsClearedCount
	call_if_lt VAR_RESULT, 4, BattleFrontier_OutsideWest_EventScript_HideTucker
	call_if_lt VAR_RESULT, 5, BattleFrontier_OutsideWest_EventScript_HideNoland
	end

BattleFrontier_OutsideWest_EventScript_HideTucker::
	setflag FLAG_TEMP_1
	return

BattleFrontier_OutsideWest_EventScript_HideNoland::
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

BattleFrontier_OutsideWest_EventScript_Noland::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_OutsideWest_EventScript_NolandBeaten
	msgbox BattleFrontier_OutsideWest_Text_NolandBefore, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_NolandBeaten::
	msgbox BattleFrontier_OutsideWest_Text_NolandAfter, MSGBOX_DEFAULT
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

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Cleared5
	msgbox BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Cleared5:
	msgbox BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Text5, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Cleared6
	msgbox BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Cleared6:
	msgbox BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text6, MSGBOX_SIGN
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
	.string "I wanted to start gauntlet 1 the\n"
	.string "moment I got off the ferry from\l"
	.string "ROUTE 103…\p"
	.string "Urrrrp… Maybe after I lie down.$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "Nobody stumbles onto this island\n"
	.string "by accident.\p"
	.string "SCOTT invites you, you take the\n"
	.string "ferry, and then the Ten Gauntlets\l"
	.string "decide how good you really were.$"

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
	.string "Now it's a Doubles gauntlet where\n"
	.string "every team is built to a plan. I\l"
	.string "wonder who designs them all?$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "The BATTLE PIKE is still sealed…\n"
	.string "but I heard the PIKE QUEEN keeps a\l"
	.string "SEVIPER.\p"
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
	.string "Now it's ten gauntlets, and the\n"
	.string "BRAINS guard the end of them.\l"
	.string "SCOTT really doesn't do anything\l"
	.string "halfway.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "I've finally arrived at the BATTLE\n"
	.string "FRONTIER!\p"
	.string "I'm sure to grab attention with\n"
	.string "my looks and ability!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Munch, munch…\p"
	.string "Every one of these people has a\n"
	.string "locked team of six…\p"
	.string "Munch… I just have snacks…$"

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
	.string "ten gauntlets with my looks and\l"
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

BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Text5:
	.string "BATTLE FACTORY - GAUNTLET 6: THE\n"
	.string "ASSEMBLY LINE.\p"
	.string "Home of the FACTORY HEAD, NOLAND.$"

BattleFrontier_OutsideWest_EventScript_BattleFactorySign_Text0:
	.string "BATTLE FACTORY - GAUNTLET 6: THE\n"
	.string "ASSEMBLY LINE.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 5.$"

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text6:
	.string "BATTLE PIKE - GAUNTLET 7.\p"
	.string "Sealed. Still being prepared.$"

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_Text0:
	.string "BATTLE PIKE - GAUNTLET 7.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 6.$"

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

BattleFrontier_OutsideWest_Text_NolandBefore:
	.string "NOLAND is tinkering with a\n"
	.string "machine.\p"
	.string "Every team's built on one part.\n"
	.string "Figure out which, and you're\l"
	.string "halfway home.$"

BattleFrontier_OutsideWest_Text_NolandAfter:
	.string "You broke my best line. I'm\n"
	.string "rebuilding it better. Ha!\p"
	.string "Say... ever ask SCOTT why he never\n"
	.string "runs his own gauntlets? I did,\l"
	.string "once. He just laughed.$"
