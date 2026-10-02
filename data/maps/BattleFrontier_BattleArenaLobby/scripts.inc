BattleFrontier_BattleArenaLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_2, 0, BattleFrontier_BattleArenaLobby_EventScript_CheckLocked
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 9, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

@ Ten Gauntlets: every non-Tower facility is locked until it's this
@ gauntlet's turn. IsBattleArenaUnlocked always reads FALSE right now -
@ nothing sets that bit yet, since the unlock schedule isn't designed. See
@ CLAUDE.md and shop-spec.md's unlock-schedule table.
BattleFrontier_BattleArenaLobby_EventScript_CheckLocked::
	setvar VAR_TEMP_2, 1
	special IsBattleArenaUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_CheckLocked_Done
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_NotOpenYet, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_BATTLE_FRONTIER_OUTSIDE_EAST, 1
	waitstate
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_CheckLocked_Done::
	end

BattleFrontier_BattleArenaLobby_Text_NotOpenYet:
	.string "This part of the BATTLE FRONTIER\n"
	.string "hasn't opened up yet.$"

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
	.string "Where the battling spirit of TRAINERS\n"
	.string "is put to the test!\p"
	.string "I welcome you to the BATTLE ARENA!\p"
	.string "I am your guide to the Set KO Tourney!$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
	.string "Now, do you wish to take\n"
	.string "the BATTLE ARENA challenge?$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
	.string "We await your challenge on\n"
	.string "another occasion!$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
	.string "In the BATTLE ARENA, we undertake\n"
	.string "the Set KO Tourney.\p"
	.string "All participants enter with a team of\n"
	.string "three POKéMON.\p"
	.string "The three POKéMON must be lined up in\n"
	.string "the order in which they are to appear.\p"
	.string "During battle, the POKéMON will appear\n"
	.string "one at a time in the preset order.\p"
	.string "Once a POKéMON enters battle, it must\n"
	.string "remain out until the match is decided.\p"
	.string "If a match remains undecided in\n"
	.string "three turns, it goes to judging.\p"
	.string "If you wish to interrupt your challenge,\n"
	.string "please save the game.\p"
	.string "If you don't save, you will not be able\n"
	.string "to continue with your challenge.\p"
	.string "If you pull off the feat of beating\n"
	.string "seven TRAINERS in succession,\l"
	.string "we will present you with Battle Points.$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
	.string "Before showing you to the BATTLE\n"
	.string "ARENA, you must save. Is that okay?$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
	.string "The BATTLE ARENA offers two levels\n"
	.string "of challenge, Level 50 and Open Level.\l"
	.string "Which is your choice?$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
	.string "Very well, now select your\n"
	.string "three POKéMON, please.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
	.string "My dear challenger!\p"
	.string "You do not have the three POKéMON\n"
	.string "required for entry.\p"
	.string "To qualify, you must bring three\n"
	.string "different kinds of POKéMON.\p"
	.string "They also must not hold the same\n"
	.string "kinds of items.\p"
	.string "EGGS{STR_VAR_1}.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsEnd:
	.string "When you have made your preparations,\n"
	.string "please do return.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
	.string "My dear challenger!\p"
	.string "You do not have the three POKéMON\n"
	.string "required for entry.\p"
	.string "To qualify, you must bring three\n"
	.string "different kinds of POKéMON.\p"
	.string "The three different POKéMON\n"
	.string "must all be Level 50 or lower.\p"
	.string "They also must not hold the same\n"
	.string "kinds of items.\p"
	.string "EGGS{STR_VAR_1}.$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
	.string "I shall now guide you to\n"
	.string "the BATTLE ARENA.$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
	.string "My dear challenger!\p"
	.string "You did not save the game before\n"
	.string "shutting down, did you?\p"
	.string "It is unfortunate, but that has\n"
	.string "resulted in your disqualification\l"
	.string "from your challenge.\p"
	.string "You may, of course, start with a fresh\n"
	.string "challenge.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
	.string "We congratulate you for your splendid\n"
	.string "string of wins over seven TRAINERS!$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
	.string "Your achievement will be recorded.\n"
	.string "Please wait while I save the game.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
	.string "In commemoration of your 7-win streak,\n"
	.string "we present you with this prize.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
	.string "Oh?\n"
	.string "Your BAG seems to be full.\p"
	.string "I urge you to clear space and\n"
	.string "return for your prize.$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
	.string "Thank you so much for participating!\p"
	.string "Please wait while I save the game.$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
	.string "We await your challenge on\n"
	.string "another occasion!$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
	.string "We have been looking forward to\n"
	.string "your arrival.\p"
	.string "Before I show you to the BATTLE\n"
	.string "ARENA, I must save the game.\l"
	.string "Please wait.$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
	.string "Shall I record your last BATTLE ARENA\n"
	.string "match on your FRONTIER PASS?$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
	.string "I lost on the REFEREE's decision…\p"
	.string "I don't think it was a good idea to only\n"
	.string "use defensive moves and not attack…$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
	.string "I won in judging!\p"
	.string "Landing hits consistently on\n"
	.string "the opponent's POKéMON worked!$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
	.string "Our match was declared a draw.\p"
	.string "When we ran out of time, both my\n"
	.string "POKéMON and the opponent's had about\l"
	.string "the same amount of HP left.$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
	.string "In the BATTLE ARENA, the order of\n"
	.string "POKéMON is totally important.\p"
	.string "For example, if your first POKéMON\n"
	.string "has certain type disadvantages,\l"
	.string "try making your second POKéMON one\l"
	.string "with moves that are super effective\l"
	.string "against the first one.\p"
	.string "I think that will be a good way of\n"
	.string "making an effective team.$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
	.string "The Set KO Tourney's rules are listed.$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
	.string "Which heading do you want to read?$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
	.string "The Set KO Tourney has special rules,\n"
	.string "unlike standard battles.\p"
	.string "First, one battle lasts only\n"
	.string "three turns.\p"
	.string "If the outcome is not decided after\n"
	.string "three turns, it goes to judging.\p"
	.string "The REFEREE will choose the winner\n"
	.string "based on how the POKéMON battled.\p"
	.string "Also, a POKéMON cannot be switched out\n"
	.string "until its battle's outcome is decided.$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
	.string "The first judging factor is “Mind.”\n"
	.string "This factor evaluates how aggressive\l"
	.string "the battlers were.\p"
	.string "The judging is based on how often\n"
	.string "the TRAINERS ordered the use of\l"
	.string "offensive moves.$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
	.string "The second judging factor is “Skill.”\n"
	.string "This factor evaluates how effectively\l"
	.string "POKéMON moves were used.\p"
	.string "If a move worked successfully,\n"
	.string "the Skill rating goes up.\p"
	.string "If a move failed, the Skill rating\n"
	.string "is lowered.\p"
	.string "If it was an offensive move, the Skill\n"
	.string "rating goes up if the move was “super\l"
	.string "effective” and goes down if it was\l"
	.string "“not very effective.”\p"
	.string "The Skill rating will not go up for\n"
	.string "moves such as PROTECT and DETECT.\p"
	.string "If the opponent used PROTECT or\n"
	.string "DETECT, and your POKéMON failed to\l"
	.string "hit with a move, its Skill rating will not\l"
	.string "go down.$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
	.string "The third judging factor is “Body.”\n"
	.string "This factor is based on how much HP\l"
	.string "remained at the end of a battle.\p"
	.string "The rating takes into account how much\n"
	.string "HP a POKéMON had at the start of\l"
	.string "battle, and what remained at the end.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
	.string "A victory snatched from the ARENA\n"
	.string "TYCOON, and a seven-TRAINER sweep!\p"
	.string "We congratulate you on your most\n"
	.string "splendid challenge!$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
	.string "My dear challenger, in recognition of\n"
	.string "your indefatigable spirit, please\l"
	.string "accept these Battle Point(s).$"

@ ============================================================================
@ Ten Gauntlets: the Battle Arena is the sparring ground (storyline.md,
@ frontier-dialogue.md). The attendant sets up rematches against any boss
@ the player has beaten - free, no FP, nothing counts. The secret: once the
@ player has paid the Lounge 7 psychic to read the current gauntlet's boss
@ (VAR_PSYCHIC_READ_GAUNTLET == cleared + 1), a mock battle against that
@ boss's real team is on the menu too, for 100 FP each time.
@ Every match is fought under Frontier rules and never whites the player out
@ (FLAG_SPARRING_BATTLE, see src/battle_setup.c), with a full heal and the
@ held items restored either side of it. The boss's trainer flag is cleared
@ first so the battle isn't skipped; a mock win setting the next boss's flag
@ is harmless, since FacilityStartRun() clears it again for the real run.
@ ============================================================================
BattleFrontier_BattleArenaLobby_EventScript_Sparring::
	lock
	faceplayer
	specialvar VAR_TEMP_3, GetGauntletsClearedCount
	copyvar VAR_TEMP_5, VAR_TEMP_3
	addvar VAR_TEMP_5, 1
	setvar VAR_TEMP_4, 0
	call_if_eq VAR_PSYCHIC_READ_GAUNTLET, VAR_TEMP_5, BattleFrontier_BattleArenaLobby_EventScript_SparMockReady
	goto_if_ne VAR_TEMP_3, 0, BattleFrontier_BattleArenaLobby_EventScript_SparMenu
	goto_if_ne VAR_TEMP_4, 0, BattleFrontier_BattleArenaLobby_EventScript_SparMenu
	msgbox BattleFrontier_BattleArenaLobby_Text_SparNothingYet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_SparMockReady::
	setvar VAR_TEMP_4, 1
	return

BattleFrontier_BattleArenaLobby_EventScript_SparMenu::
	message BattleFrontier_BattleArenaLobby_Text_SparWelcome
	waitmessage
	call_if_ge VAR_TEMP_3, 1, BattleFrontier_BattleArenaLobby_EventScript_SparPush1
	call_if_ge VAR_TEMP_3, 2, BattleFrontier_BattleArenaLobby_EventScript_SparPush2
	call_if_ge VAR_TEMP_3, 3, BattleFrontier_BattleArenaLobby_EventScript_SparPush3
	call_if_ge VAR_TEMP_3, 4, BattleFrontier_BattleArenaLobby_EventScript_SparPush4
	call_if_ge VAR_TEMP_3, 5, BattleFrontier_BattleArenaLobby_EventScript_SparPush5
	call_if_ge VAR_TEMP_3, 6, BattleFrontier_BattleArenaLobby_EventScript_SparPush6
	call_if_ge VAR_TEMP_3, 7, BattleFrontier_BattleArenaLobby_EventScript_SparPush7
	call_if_ge VAR_TEMP_3, 8, BattleFrontier_BattleArenaLobby_EventScript_SparPush8
	call_if_eq VAR_TEMP_4, 1, BattleFrontier_BattleArenaLobby_EventScript_SparPushMock
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparCancel, 127
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_SparCheck1
	case 1, BattleFrontier_BattleArenaLobby_EventScript_SparCheck2
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SparCheck3
	case 3, BattleFrontier_BattleArenaLobby_EventScript_SparCheck4
	case 4, BattleFrontier_BattleArenaLobby_EventScript_SparCheck5
	case 5, BattleFrontier_BattleArenaLobby_EventScript_SparCheck6
	case 6, BattleFrontier_BattleArenaLobby_EventScript_SparCheck7
	case 7, BattleFrontier_BattleArenaLobby_EventScript_SparCheck8
	case 100, BattleFrontier_BattleArenaLobby_EventScript_SparMock
	goto BattleFrontier_BattleArenaLobby_EventScript_SparGoodbye
	end

BattleFrontier_BattleArenaLobby_EventScript_SparPush1::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss1, 0
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush2::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss2, 1
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush3::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss3, 2
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush4::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss4, 3
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush5::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss5, 4
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush6::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss6, 5
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush7::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss7, 6
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPush8::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparBoss8, 7
	return

BattleFrontier_BattleArenaLobby_EventScript_SparPushMock::
	dynmultipush BattleFrontier_BattleArenaLobby_Text_SparMockOption, 100
	return

BattleFrontier_BattleArenaLobby_EventScript_SparCheck1::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar1
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar1::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B1_BOSS_WINONA
	trainerbattle_single TRAINER_FACILITY_B1_BOSS_WINONA, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck2::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar2
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar2::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B2_BOSS_JUAN
	trainerbattle_double TRAINER_FACILITY_B2_BOSS_JUAN, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, Facility_Text_NotEnoughMons, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck3::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar3
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar3::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B3_BOSS_ROXANNE
	trainerbattle_single TRAINER_FACILITY_B3_BOSS_ROXANNE, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck4::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar4
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar4::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B4_BOSS_ANABEL
	trainerbattle_double TRAINER_FACILITY_B4_BOSS_ANABEL, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, Facility_Text_NotEnoughMons, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck5::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar5
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar5::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B5_BOSS_TUCKER
	trainerbattle_single TRAINER_FACILITY_B5_BOSS_TUCKER, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck6::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar6
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar6::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B6_BOSS_LUCY
	trainerbattle_double TRAINER_FACILITY_B6_BOSS_LUCY, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, Facility_Text_NotEnoughMons, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck7::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar7
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar7::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B7_BOSS_SPENSER
	trainerbattle_single TRAINER_FACILITY_B7_BOSS_SPENSER, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCheck8::
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattleArenaLobby_EventScript_Spar8
	end

BattleFrontier_BattleArenaLobby_EventScript_Spar8::
	call BattleFrontier_BattleArenaLobby_EventScript_SparPrep
	cleartrainerflag TRAINER_FACILITY_B8_BOSS_BRANDON
	trainerbattle_double TRAINER_FACILITY_B8_BOSS_BRANDON, BattleFrontier_BattleArenaLobby_Text_SparIntro, BattleFrontier_BattleArenaLobby_Text_SparDefeat, Facility_Text_NotEnoughMons, BattleFrontier_BattleArenaLobby_EventScript_AfterSpar
	end

@ The mock battle: the current gauntlet's boss (gauntlet cleared + 1).
BattleFrontier_BattleArenaLobby_EventScript_SparMock::
	specialvar VAR_RESULT, FacilityPsychicGetBoss
	special FacilityCheckEligible
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix
	special ShowFacilityFPWindow
	msgbox BattleFrontier_BattleArenaLobby_Text_SparMockOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_BattleArenaLobby_EventScript_SparMockDeclined
	setvar VAR_0x8008, 100
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_BattleArenaLobby_EventScript_SparNoFP
	setvar VAR_0x8004, 100
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	playse SE_SHOP
	special CloseFacilityFPWindow
	msgbox BattleFrontier_BattleArenaLobby_Text_SparReady, MSGBOX_DEFAULT
	closemessage
	switch VAR_TEMP_3
	case 0, BattleFrontier_BattleArenaLobby_EventScript_Spar1
	case 1, BattleFrontier_BattleArenaLobby_EventScript_Spar2
	case 2, BattleFrontier_BattleArenaLobby_EventScript_Spar3
	case 3, BattleFrontier_BattleArenaLobby_EventScript_Spar4
	case 4, BattleFrontier_BattleArenaLobby_EventScript_Spar5
	case 5, BattleFrontier_BattleArenaLobby_EventScript_Spar6
	case 6, BattleFrontier_BattleArenaLobby_EventScript_Spar7
	case 7, BattleFrontier_BattleArenaLobby_EventScript_Spar8
	goto BattleFrontier_BattleArenaLobby_EventScript_SparGoodbye
	end

BattleFrontier_BattleArenaLobby_EventScript_SparMockDeclined::
	special CloseFacilityFPWindow
	goto BattleFrontier_BattleArenaLobby_EventScript_SparGoodbye
	end

BattleFrontier_BattleArenaLobby_EventScript_SparNoFP::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparNoFP, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_SparNeedSix::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparNeedSix, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_SparGoodbye::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparGoodbye, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_SparPrep::
	special SaveFacilityHeldItems
	special HealPlayerParty
	setflag FLAG_SPARRING_BATTLE
	return

BattleFrontier_BattleArenaLobby_EventScript_AfterSpar::
	clearflag FLAG_SPARRING_BATTLE
	special HealPlayerParty
	special RestoreFacilityHeldItems
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_BattleArenaLobby_EventScript_SparWon
	msgbox BattleFrontier_BattleArenaLobby_Text_SparLost, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SparWon::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparWon, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SparBoard::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparBoard, MSGBOX_SIGN
	end

BattleFrontier_BattleArenaLobby_EventScript_SparRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparRules, MSGBOX_SIGN
	end

BattleFrontier_BattleArenaLobby_EventScript_SparWoman::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparWoman, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_SparMan::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparMan, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_SparCamper::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparCamper, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_SparYoungster::
	msgbox BattleFrontier_BattleArenaLobby_Text_SparYoungster, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_Text_SparBoss1:
	.string "WARDEN WINONA$"

BattleFrontier_BattleArenaLobby_Text_SparBoss2:
	.string "TIDEWARDEN JUAN$"

BattleFrontier_BattleArenaLobby_Text_SparBoss3:
	.string "DUNEWARDEN ROXANNE$"

BattleFrontier_BattleArenaLobby_Text_SparBoss4:
	.string "SALON MAIDEN ANABEL$"

BattleFrontier_BattleArenaLobby_Text_SparBoss5:
	.string "DOME ACE TUCKER$"

BattleFrontier_BattleArenaLobby_Text_SparBoss6:
	.string "PIKE QUEEN LUCY$"

BattleFrontier_BattleArenaLobby_Text_SparBoss7:
	.string "PALACE MAVEN SPENSER$"

BattleFrontier_BattleArenaLobby_Text_SparBoss8:
	.string "PYRAMID KING BRANDON$"

BattleFrontier_BattleArenaLobby_Text_SparMockOption:
	.string "MOCK BATTLE$"

BattleFrontier_BattleArenaLobby_Text_SparCancel:
	.string "CANCEL$"

BattleFrontier_BattleArenaLobby_Text_SparNothingYet:
	.string "Welcome to the sparring ground!\p"
	.string "I set up rematches against the\n"
	.string "bosses you've already beaten. No\l"
	.string "FP, no streak. Just practice.\p"
	.string "Come back once you've beaten one!$"

BattleFrontier_BattleArenaLobby_Text_SparWelcome:
	.string "Welcome to the sparring ground!\n"
	.string "Who would you like to spar\l"
	.string "against?$"

BattleFrontier_BattleArenaLobby_Text_SparReady:
	.string "All right! Your team's healed, and\n"
	.string "you'll get your items back after.\l"
	.string "No FP, nothing counts.\p"
	.string "Begin!$"

BattleFrontier_BattleArenaLobby_Text_SparIntro:
	.string "The sparring match begins!$"

BattleFrontier_BattleArenaLobby_Text_SparDefeat:
	.string "A good match.$"

BattleFrontier_BattleArenaLobby_Text_SparWon:
	.string "Nicely done! Come back any time.$"

BattleFrontier_BattleArenaLobby_Text_SparLost:
	.string "Shake it off. That's what\n"
	.string "sparring's for. Come back any\l"
	.string "time.$"

BattleFrontier_BattleArenaLobby_Text_SparNeedSix:
	.string "You'll need a full party of six,\n"
	.string "same as a real gauntlet.$"

BattleFrontier_BattleArenaLobby_Text_SparGoodbye:
	.string "Come back any time!$"

BattleFrontier_BattleArenaLobby_Text_SparNoFP:
	.string "Sorry, you don't have enough FP.$"

BattleFrontier_BattleArenaLobby_Text_SparMockOffer:
	.string "A mock battle? Against {STR_VAR_1}?\p"
	.string "You'd need to know that team\n"
	.string "inside and out... Every POKéMON,\l"
	.string "every item.\p"
	.string "...You do? Well, then I can set it\n"
	.string "up. Same team, same moves.\p"
	.string "The setup costs 100 FP. All right?$"

BattleFrontier_BattleArenaLobby_Text_SparBoard:
	.string "THE SPARRING GROUND\p"
	.string "Rematch any boss you've beaten. No\n"
	.string "FP. No streak. No hard feelings.$"

BattleFrontier_BattleArenaLobby_Text_SparRules:
	.string "SPARRING RULES\p"
	.string "A full party of six, all at level\n"
	.string "50. A full heal before and after.\p"
	.string "Held items come back. Nothing you\n"
	.string "win here counts.$"

BattleFrontier_BattleArenaLobby_Text_SparWoman:
	.string "I come here to spar against the\n"
	.string "bosses I've already beaten.\p"
	.string "Winning twice feels even better!$"

BattleFrontier_BattleArenaLobby_Text_SparMan:
	.string "No FP for sparring. Believe me, I\n"
	.string "checked.$"

BattleFrontier_BattleArenaLobby_Text_SparCamper:
	.string "The ARENA TYCOON? GRETA? She's\n"
	.string "hardly ever around these days.\p"
	.string "I heard she works for SCOTT\n"
	.string "directly now.$"

BattleFrontier_BattleArenaLobby_Text_SparYoungster:
	.string "The attendant can set up a match\n"
	.string "against any team she knows.\p"
	.string "She knows every boss you've\n"
	.string "beaten... I wonder if there's any\l"
	.string "other way she could know a team?$"
