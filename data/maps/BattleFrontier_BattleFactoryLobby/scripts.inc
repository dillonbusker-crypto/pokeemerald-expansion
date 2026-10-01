BattleFrontier_BattleFactoryLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame:
	map_script_2 VAR_TEMP_2, 0, BattleFrontier_BattleFactoryLobby_EventScript_CheckLocked
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle::
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
	msgbox BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults_Text, MSGBOX_SIGN
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_Cleared
	msgbox BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_Text, MSGBOX_SIGN
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_Cleared:
	msgbox BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_TextCleared, MSGBOX_SIGN
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
	msgbox BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard_Text, MSGBOX_SIGN
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
	releaseall
	end

@ Ten Gauntlets: every non-Tower facility is locked until it's this
@ gauntlet's turn. IsBattleFactoryUnlocked always reads FALSE right now -
@ nothing sets that bit yet, since the unlock schedule isn't designed. See
@ CLAUDE.md and shop-spec.md's unlock-schedule table.
BattleFrontier_BattleFactoryLobby_EventScript_CheckLocked::
	setvar VAR_TEMP_2, 1
	special IsBattleFactoryUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_CheckLocked_Done
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_NotOpenYet, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 2
	waitstate
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_CheckLocked_Done::
	end

BattleFrontier_BattleFactoryLobby_Text_NotOpenYet:
	.string "This part of the BATTLE FRONTIER\n"
	.string "hasn't opened up yet.$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
	.string "Where the intelligence of TRAINERS\n"
	.string "is put to the test!\p"
	.string "Welcome to the BATTLE FACTORY!\p"
	.string "I am your guide to the Battle Swap\n"
	.string "Single Tournament.$"

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
	.string "Would you like to take the Battle\n"
	.string "Swap Single challenge?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
	.string "The Battle Swap Single Tournament\n"
	.string "is a SINGLE BATTLE competition using\l"
	.string "only rental POKéMON.\p"
	.string "First, you will be loaned three\n"
	.string "POKéMON specifically for this event.\p"
	.string "Using the supplied rental POKéMON,\n"
	.string "you must conduct a SINGLE BATTLE.\p"
	.string "If you win, you are permitted to trade\n"
	.string "one of your rental POKéMON.\p"
	.string "Repeat this cycle of battling and\n"
	.string "trading--if you win seven times in\l"
	.string "a row, you will earn Battle Points.\p"
	.string "If you want to interrupt your\n"
	.string "challenge, please save the game.\p"
	.string "If you don't save, you will be\n"
	.string "disqualified from your challenge.$"

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
	.string "We look forward to your next visit.$"

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
	.string "Which level do you wish to challenge?\n"
	.string "Level 50 or Open Level?$"

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
	.string "Before you begin your challenge,\n"
	.string "I need to save the game. Is that okay?$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
	.string "Okay, I will hold your POKéMON for\n"
	.string "safekeeping while you compete.$"

BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
	.string "Please step this way.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
	.string "Thank you for participating!\p"
	.string "I will return your POKéMON in exchange\n"
	.string "for our rental POKéMON.\p"
	.string "I must also save the event results.\n"
	.string "Please wait.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
	.string "I will return your POKéMON in exchange\n"
	.string "for our rental POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
	.string "Congratulations! You've won seven\n"
	.string "straight Battle Swap matches!$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
	.string "In recognition of your 7-win streak,\n"
	.string "we award you these Battle Point(s).$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
	.string "Oh, oh, oh!\p"
	.string "Your Battle Points are maxed.\p"
	.string "Please come back after using\n"
	.string "some Battle Points.$"

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
	.string "We've been waiting for you!\p"
	.string "Before we resume your challenge,\n"
	.string "I must save the game.$"

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
	.string "I'm sorry to say this, but you didn't\n"
	.string "save before you quit playing last time.\p"
	.string "As a result, you have been disqualified\n"
	.string "from your challenge.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
	.string "We'll return your personal POKéMON.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
	.string "Where the intelligence of TRAINERS\n"
	.string "is put to the test!\p"
	.string "Welcome to the BATTLE FACTORY!\p"
	.string "I am your guide to the Battle Swap\n"
	.string "Double Tournament.$"

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
	.string "Would you like to take the Battle\n"
	.string "Swap Double challenge?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
	.string "The Battle Swap Double Tournament\n"
	.string "is a DOUBLE BATTLE competition using\l"
	.string "only rental POKéMON.\p"
	.string "First, you will be loaned three\n"
	.string "POKéMON specifically for this event.\p"
	.string "Using the supplied rental POKéMON,\n"
	.string "you must conduct a DOUBLE BATTLE.\p"
	.string "If you win, you are permitted to trade\n"
	.string "one of your rental POKéMON.\p"
	.string "Repeat this cycle of battling and\n"
	.string "trading--if you win seven times in\l"
	.string "a row, you will earn Battle Points.\p"
	.string "If you want to interrupt your\n"
	.string "challenge, please save the game.\p"
	.string "If you don't save before interrupting,\n"
	.string "you will be disqualified.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
	.string "Congratulations for defeating\n"
	.string "the FACTORY HEAD and winning\l"
	.string "seven matches in a row!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
	.string "In recognition of your wealth of\n"
	.string "knowledge and keen intelligence,\l"
	.string "we award you these Battle Point(s).$"

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
	.string "Let me exchange your POKéMON\n"
	.string "for our rental POKéMON.\p"
	.string "I need to save the battle data,\n"
	.string "so please wait.$"

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
	.string "Would you like to record your last\n"
	.string "BATTLE FACTORY match on your\l"
	.string "FRONTIER PASS?$"

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
	.string "Hi! You, there!\p"
	.string "Every team in here is built around\n"
	.string "one plan: weather, terrain, TRICK\l"
	.string "ROOM, or raw power.\p"
	.string "Spot the plan on turn one, and\n"
	.string "you're halfway there.$"

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
	.string "I brought my Singles team to a\n"
	.string "Doubles gauntlet…\p"
	.string "Spread moves hit both of my\n"
	.string "POKéMON. Every single turn.$"

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
	.string "Their PELIPPER set up rain, and I\n"
	.string "just kept attacking…\p"
	.string "I should have taken the weather\n"
	.string "away first.$"

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
	.string "I hear the FACTORY HEAD's team\n"
	.string "runs on sunshine.\p"
	.string "…I'm going to go stand in the rain\n"
	.string "for a while.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
	.string "Like, I'm really tough, but I get bored\n"
	.string "really easily, so I just kept swapping\l"
	.string "and battling over and over.\p"
	.string "So anyway, when I kept entering\n"
	.string "Battle Swap events, I noticed they\l"
	.string "varied the rental POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
	.string "The Battle Swap rules are listed.$"

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
	.string "Which heading do you want to read?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
	.string "In a Battle Swap event, you may use\n"
	.string "only three POKéMON.\p"
	.string "Whether you are renting or swapping,\n"
	.string "your team may not have two or more\l"
	.string "of the same POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
	.string "You may swap POKéMON only with\n"
	.string "the TRAINER you have just defeated.\p"
	.string "You may swap for only those POKéMON\n"
	.string "used by the beaten TRAINER.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
	.string "After every battle you win, you may\n"
	.string "swap for one of your defeated\l"
	.string "opponent's POKéMON.\p"
	.string "You will not be able to swap POKéMON\n"
	.string "with the seventh TRAINER in the event.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
	.string "There are two key points to be aware\n"
	.string "of when swapping POKéMON.\p"
	.string "First, when swapping, you can't check\n"
	.string "the stats of the POKéMON you are\l"
	.string "about to receive.\p"
	.string "Second, the POKéMON on your team\n"
	.string "are lined up in sequence, depending on\l"
	.string "the order in which you rented them.\p"
	.string "This sequence remains unchanged\n"
	.string "even when swaps are made.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
	.string "In the Open Level, the rental POKéMON\n"
	.string "and the opposing TRAINERS' POKéMON\l"
	.string "are all Level 100.$"

@ ============================================================================
@ Ten Gauntlets: gauntlet 6 ("The Assembly Line", gauntlet-06.md). Same
@ pattern as the Battle Dome's gauntlet 5: the Factory is only the location
@ (no rentals or swapping), and its Doubles attendant runs gauntlet 6
@ through the shared run-loop scripts in data/maps/BattleFrontier_
@ BattleTowerLobby/scripts.inc. The Factory opens when gauntlet 5 is
@ cleared (IsBattleFactoryUnlocked() in src/facility.c), so the lobby's
@ OnFrame check already turns the player away before then.
@
@ The vanilla Singles/Doubles attendant flows above are unreferenced now -
@ map.json points the two attendants at the scripts below instead.
@ ============================================================================

BattleFrontier_BattleFactoryLobby_EventScript_FacilityAttendantB6::
	lock
	faceplayer
	setvar VAR_0x8004, FACILITY_GAUNTLET_6
	special IsFacilityRunActiveForGauntlet
	goto_if_eq VAR_RESULT, TRUE, Facility_ResumeRun
	special IsFacilityRunActiveForDifferentGauntlet
	goto_if_eq VAR_RESULT, TRUE, Facility_BusyElsewhere
	special IsFacilityGauntletCompleted
	goto_if_eq VAR_RESULT, TRUE, Facility_AlreadyCleared
	goto_if_lt VAR_BIRCH_STORY_STATE, 6, BattleFrontier_BattleFactoryLobby_EventScript_B6SystemDown
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, Facility_NotEligible
	msgbox Facility_B6_Text_AskEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Facility_Decline
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Facility_Decline
	setvar VAR_0x8004, FACILITY_GAUNTLET_6
	special FacilityStartRun
	call Common_EventScript_SaveGame
	goto Facility_DoBattle
	end

@ Ten Gauntlets: Birch's lab arc (storyline.md). DEVON's technology runs the
@ Frontier's systems, and PRESIDENT STONE has paused gauntlet 6 until SCOTT
@ "handles it" (VAR_BIRCH_STORY_STATE 6). The shops stay open.
BattleFrontier_BattleFactoryLobby_EventScript_B6SystemDown::
	msgbox BattleFrontier_BattleFactoryLobby_Text_B6SystemDown, MSGBOX_DEFAULT
	release
	end

@ The vanilla Singles challenge would run the real Battle Factory's rental
@ logic, outside the Ten Gauntlets run loop - so this attendant just turns
@ the player away.
BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendantClosed::
	lock
	faceplayer
	msgbox BattleFrontier_BattleFactoryLobby_Text_SinglesClosed, MSGBOX_DEFAULT
	release
	end

Facility_DoBattle_B6:
	switch VAR_RESULT
	case 0, Facility_B6_Battle_MONSOON
	case 1, Facility_B6_Battle_SOLSTICE
	case 2, Facility_B6_Battle_WHITEOUT
	case 3, Facility_B6_Battle_LIVEWIRE
	case 4, Facility_B6_Battle_MINDSCAPE
	case 5, Facility_B6_Battle_OVERGROWTH
	case 6, Facility_B6_Battle_STANDING
	case 7, Facility_B6_Battle_NIGHTSHIFT
	case 8, Facility_B6_Battle_SLOWBURN
	case 9, Facility_B6_Battle_BLITZ
	case 10, Facility_B6_Battle_HEAVYWEIGHT
	case 11, Facility_B6_Battle_CHORUS
	end

Facility_B6_Battle_MONSOON:
	trainerbattle_double TRAINER_FACILITY_B6_A1_MONSOON, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_SOLSTICE:
	trainerbattle_double TRAINER_FACILITY_B6_A2_SOLSTICE, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_WHITEOUT:
	trainerbattle_double TRAINER_FACILITY_B6_A3_WHITEOUT, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_LIVEWIRE:
	trainerbattle_double TRAINER_FACILITY_B6_B4_LIVEWIRE, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_MINDSCAPE:
	trainerbattle_double TRAINER_FACILITY_B6_B5_MINDSCAPE, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_OVERGROWTH:
	trainerbattle_double TRAINER_FACILITY_B6_B6_OVERGROWTH, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_STANDING:
	trainerbattle_double TRAINER_FACILITY_B6_C7_STANDING, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_NIGHTSHIFT:
	trainerbattle_double TRAINER_FACILITY_B6_C8_NIGHTSHIFT, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_SLOWBURN:
	trainerbattle_double TRAINER_FACILITY_B6_C9_SLOWBURN, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_BLITZ:
	trainerbattle_double TRAINER_FACILITY_B6_D10_BLITZ, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_HEAVYWEIGHT:
	trainerbattle_double TRAINER_FACILITY_B6_D11_HEAVYWEIGHT, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_B6_Battle_CHORUS:
	trainerbattle_double TRAINER_FACILITY_B6_D12_CHORUS, Facility_Text_Intro, Facility_Text_Defeat, Facility_Text_NotEnoughMons, Facility_AfterPoolBattle
	end

Facility_Battle_Boss_B6:
	trainerbattle_double TRAINER_FACILITY_B6_BOSS_NOLAND, Facility_B6_Text_BossIntro, Facility_B6_Text_BossDefeat, Facility_Text_NotEnoughMons, Facility_AfterBossBattle
	end

Facility_B6_Text_AskEnter:
	.string "Welcome to gauntlet 6, THE\n"
	.string "ASSEMBLY LINE!\p"
	.string "This is a Doubles gauntlet - six\n"
	.string "battles, then a boss. Your whole\l"
	.string "party of six enters, and it's\l"
	.string "locked once you begin.\p"
	.string "Every team here is built to a\n"
	.string "plan. Ready to start?$"

Facility_B6_Text_BossIntro:
	.string "Hey there! I'm NOLAND, the FACTORY\n"
	.string "HEAD.\p"
	.string "Every team off this line runs on\n"
	.string "one part. Mine runs on the sun.\p"
	.string "Find the part and break it.\n"
	.string "Simple, right? Ha!$"

Facility_B6_Text_BossDefeat:
	.string "Ha! You found the part that\n"
	.string "mattered. Nice work!$"

BattleFrontier_BattleFactoryLobby_Text_SinglesClosed:
	.string "The Singles challenge isn't running\n"
	.string "right now. Please see my colleague\l"
	.string "for the Assembly Line.$"

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults_Text:
	.string "The Singles challenge isn't\n"
	.string "running right now.$"

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_Text:
	.string "GAUNTLET 6 - THE ASSEMBLY LINE.\p"
	.string "Doubles. Boss: FACTORY HEAD\n"
	.string "NOLAND.\p"
	.string "Not yet cleared.$"

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_TextCleared:
	.string "GAUNTLET 6 - THE ASSEMBLY LINE.\p"
	.string "Doubles. Boss: FACTORY HEAD\n"
	.string "NOLAND.\p"
	.string "Cleared by {PLAYER}!$"

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard_Text:
	.string "THE ASSEMBLY LINE\p"
	.string "Every team off this line is built\n"
	.string "to one of four plans: WEATHER,\l"
	.string "TERRAIN, TRICK ROOM, or RAW POWER.\p"
	.string "Find the part the plan runs on,\n"
	.string "and break it.$"

BattleFrontier_BattleFactoryLobby_Text_B6SystemDown:
	.string "I'm sorry. The ASSEMBLY LINE is\n"
	.string "closed for now.\p"
	.string "The system's gone down again. Only\n"
	.string "this gauntlet, oddly enough. The\l"
	.string "shops are still running.\p"
	.string "DEVON's technicians run everything\n"
	.string "on the island, and they say\l"
	.string "they're looking into it. Nobody\l"
	.string "can tell me when it'll be back up.$"
