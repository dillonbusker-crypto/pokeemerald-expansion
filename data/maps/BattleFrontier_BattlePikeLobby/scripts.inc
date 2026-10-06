BattleFrontier_BattlePikeLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame:
	map_script_2 VAR_TEMP_2, 0, BattleFrontier_BattlePikeLobby_EventScript_CheckLocked
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePikeLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving::
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen::
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	pike_savehelditems
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR, 6, 7
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor::
	applymovement LOCALID_PIKE_LOBBY_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor:
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker::
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin::
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain::
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitse
	return

@ Ten Gauntlets: locked until gauntlet 5 is cleared (IsBattlePikeUnlocked).
BattleFrontier_BattlePikeLobby_EventScript_CheckLocked::
	setvar VAR_TEMP_2, 1
	special IsBattlePikeUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_CheckLocked_Done
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_NotOpenYet, MSGBOX_DEFAULT
	closemessage
	warpsilent MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 0
	waitstate
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_CheckLocked_Done::
	end

BattleFrontier_BattlePikeLobby_Text_NotOpenYet:
	.string "This part of the BATTLE FRONTIER\n"
	.string "hasn't opened up yet.$"

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike:
	.string "Where the luck of TRAINERS\n"
	.string "is put to the test…\p"
	.string "Welcome to the BATTLE PIKE…\p"
	.string "I am your guide to the BATTLE PIKE…$"

BattleFrontier_BattlePikeLobby_Text_TakeChallenge:
	.string "Would you like to take the Battle\n"
	.string "Choice challenge?$"

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike:
	.string "Here we conduct an event we call\n"
	.string "the Battle Choice.\p"
	.string "The Battle Choice rules are very\n"
	.string "simple…\p"
	.string "Choose one of three paths and make\n"
	.string "your way to the goal room at the end\l"
	.string "of the BATTLE PIKE. It's that simple.\p"
	.string "However, what happens on the chosen\n"
	.string "path depends entirely on the luck\l"
	.string "of the challenger…\p"
	.string "If you reach the goal, you will be\n"
	.string "rewarded with Battle Points.\p"
	.string "If you want to interrupt your\n"
	.string "challenge, please have a word with\l"
	.string "our staff in the big rooms on the way.\p"
	.string "If you don't save before interrupting,\n"
	.string "you will be disqualified.$"

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou:
	.string "We look forward to seeing you\n"
	.string "on another occasion…$"

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode:
	.string "You have the choice of two courses,\n"
	.string "Level 50 and Open Level.\l"
	.string "Which will you challenge?$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50:
	.string "I beg your pardon, but…\p"
	.string "You do not have three eligible\n"
	.string "POKéMON for the Battle Choice event.\p"
	.string "You must have three different POKéMON\n"
	.string "of Level 50 or less to enter.\p"
	.string "They also must be holding different\n"
	.string "kinds of items.\p"
	.string "EGGS{STR_VAR_1}.$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd:
	.string "Please come see me when\n"
	.string "you are ready…$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen:
	.string "I beg your pardon, but…\p"
	.string "You do not have three eligible\n"
	.string "POKéMON for the Battle Choice event.\p"
	.string "You must have three different\n"
	.string "POKéMON to enter.\p"
	.string "They also must be holding different\n"
	.string "kinds of items.\p"
	.string "EGGS{STR_VAR_1}.$"

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons:
	.string "Please choose the three POKéMON\n"
	.string "you wish to enter in the challenge…$"

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge:
	.string "Before starting your Battle Choice\n"
	.string "challenge, I must save the game.\l"
	.string "Is that acceptable?$"

BattleFrontier_BattlePikeLobby_Text_StepThisWay:
	.string "Please step this way…$"

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults:
	.string "Your challenge has ended…\p"
	.string "I shall record your results.\n"
	.string "Please wait…$"

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance:
	.string "You have completed the challenge…\p"
	.string "I must say… You seem to possess luck\n"
	.string "in abundance…$"

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults:
	.string "I shall record your results.\n"
	.string "Please wait…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints2:
	.string "To commemorate your completion of\n"
	.string "the Battle Choice challenge, we award\l"
	.string "you these Battle Point(s)…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit:
	.string "You appear to have reached the limit\n"
	.string "for Battle Points…\p"
	.string "Please exchange some Battle Points\n"
	.string "for prizes, then return…$"

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting:
	.string "I beg your pardon, but…\p"
	.string "You failed to save before you quit\n"
	.string "your challenge the last time.\p"
	.string "Because of that, your challenge so far\n"
	.string "has been disqualified. I am sorry…$"

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen:
	.string "Congratulations…\p"
	.string "You have snatched victory from the\n"
	.string "PIKE QUEEN and cleared the event…$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints:
	.string "In recognition of your amazing luck,\n"
	.string "we award you these Battle Point(s)…$"

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal:
	.string "Arrgh! I blew my chance!\n"
	.string "I was one room away from the goal!\p"
	.string "In this place, you'd better watch out\n"
	.string "for poison, freezing, and so on.$"

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer:
	.string "I've completed the challenge 10 times\n"
	.string "now, but I've never had to battle\l"
	.string "a TRAINER once.$"

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere:
	.string "Listen! Listen!\p"
	.string "Don't you think that the special\n"
	.string "abilities of POKéMON will be useful\l"
	.string "here?$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose:
	.string "What is this weird place?\n"
	.string "I can't figure it out at all!\p"
	.string "I've taken the challenge a bunch\n"
	.string "of times, but all I ever do is run into\l"
	.string "TRAINERS whichever path I choose.$"

BattleFrontier_BattlePikeLobby_Text_RulesAreListed:
	.string "The Battle Choice's rules are listed.$"

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading:
	.string "Which heading do you want to read?$"

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules:
	.string "The BAG and POKéNAV may not be used\n"
	.string "during a Battle Choice challenge.$"

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules:
	.string "During a Battle Choice challenge,\n"
	.string "any BERRY or HERB held by POKéMON\l"
	.string "will be effective only once.$"

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules:
	.string "During a Battle Choice challenge,\n"
	.string "the sequence of POKéMON cannot be\l"
	.string "changed.\p"
	.string "The sequence must be set before\n"
	.string "starting your challenge.$"

@ ============================================================================
@ Ten Gauntlets: gauntlet 6 ("The Crossroads", gauntlet-06.md), boss PIKE
@ QUEEN LUCY. It ran in the Battle Factory until the trim to eight gauntlets
@ made the Factory Devon's control room (storyline.md). The Pike is only the
@ location (no rooms or paths): its attendant runs gauntlet 6 through the
@ shared run-loop scripts in data/maps/BattleFrontier_BattleTowerLobby/
@ scripts.inc. The Pike opens when gauntlet 5 is cleared
@ (IsBattlePikeUnlocked() in src/facility.c).
@ ============================================================================

BattleFrontier_BattlePikeLobby_EventScript_FacilityAttendantB6::
	lock
	faceplayer
	setvar VAR_0x8004, FACILITY_GAUNTLET_6
	special IsFacilityRunActiveForGauntlet
	goto_if_eq VAR_RESULT, TRUE, Facility_ResumeRun
	special IsFacilityRunActiveForDifferentGauntlet
	goto_if_eq VAR_RESULT, TRUE, Facility_BusyElsewhere
	special IsFacilityGauntletCompleted
	goto_if_eq VAR_RESULT, TRUE, Facility_AlreadyCleared
	goto_if_lt VAR_BIRCH_STORY_STATE, 6, BattleFrontier_BattlePikeLobby_EventScript_B6SystemDown
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
BattleFrontier_BattlePikeLobby_EventScript_B6SystemDown::
	msgbox BattleFrontier_BattlePikeLobby_Text_B6SystemDown, MSGBOX_DEFAULT
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
	trainerbattle_double TRAINER_FACILITY_B6_BOSS_LUCY, Facility_B6_Text_BossIntro, Facility_B6_Text_BossDefeat, Facility_Text_NotEnoughMons, Facility_AfterBossBattle
	end

Facility_B6_Text_AskEnter:
	.string "Welcome to gauntlet 6, THE\n"
	.string "CROSSROADS!\p"
	.string "This is a Doubles gauntlet - six\n"
	.string "battles, then a boss. Your whole\l"
	.string "party of six enters, and it's\l"
	.string "locked once you begin.\p"
	.string "Every team here takes one of four\n"
	.string "roads. Ready to start?$"

Facility_B6_Text_BossIntro:
	.string "LUCY: ...I am LUCY. The PIKE\n"
	.string "QUEEN.\p"
	.string "My POKéMON won't overpower you.\n"
	.string "They'll wear you down.\p"
	.string "Burned. Paralyzed. Asleep.\n"
	.string "Trapped.\p"
	.string "...Then gone.$"

Facility_B6_Text_BossDefeat:
	.string "...You slipped every trap. Go.$"

BattleFrontier_BattlePikeLobby_Text_B6SystemDown:
	.string "I'm sorry. THE CROSSROADS is\n"
	.string "closed for now.\p"
	.string "The system's gone down again. Only\n"
	.string "this gauntlet, oddly enough. The\l"
	.string "shops are still running.\p"
	.string "DEVON's technicians run everything\n"
	.string "on the island, and they say\l"
	.string "they're looking into it. Nobody\l"
	.string "can tell me when it'll be back up.$"

BattleFrontier_BattlePikeLobby_EventScript_G6Plaque::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_BattlePikeLobby_EventScript_G6PlaqueCleared
	msgbox BattleFrontier_BattlePikeLobby_Text_G6Plaque, MSGBOX_SIGN
	end

BattleFrontier_BattlePikeLobby_EventScript_G6PlaqueCleared::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6PlaqueCleared, MSGBOX_SIGN
	end

BattleFrontier_BattlePikeLobby_EventScript_G6Rules::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6Rules, MSGBOX_SIGN
	end

BattleFrontier_BattlePikeLobby_EventScript_G6Hiker::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6Hiker, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_G6Twin::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6Twin, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_G6Beauty::
	@ Ten Gauntlets: Bad Dreams (storyline.md). Asleep during the event, awake
	@ once DARKRAI is freed (while gauntlet 7 is still open).
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_G6Beauty_Asleep
	goto_if_unset FLAG_DARKRAI_FREED, BattleFrontier_BattlePikeLobby_G6Beauty_Normal
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_eq VAR_RESULT, 6, BattleFrontier_BattlePikeLobby_G6Beauty_Awake
BattleFrontier_BattlePikeLobby_G6Beauty_Normal::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6Beauty, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_G6Beauty_Asleep::
	lock
	msgbox BattleFrontier_BattlePikeLobby_Text_G6BeautyAsleep, MSGBOX_DEFAULT
	checkitem ITEM_LUNAR_WING
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_G6Beauty_WingGlows
	release
	end

BattleFrontier_BattlePikeLobby_G6Beauty_WingGlows::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6BeautyWingGlows, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeLobby_G6Beauty_Awake::
	msgbox BattleFrontier_BattlePikeLobby_Text_G6BeautyAwake, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_Text_G6BeautyAsleep:
	.string "…Zzz… I keep opening the curtains…\n"
	.string "and the blue eye is still there…\p"
	.string "…Zzz…$"

BattleFrontier_BattlePikeLobby_Text_G6BeautyWingGlows:
	.string "The LUNAR WING glows faintly.$"

BattleFrontier_BattlePikeLobby_Text_G6BeautyAwake:
	.string "I dreamed of an endless hall of\n"
	.string "curtains for weeks. Last night it\l"
	.string "just stopped.\p"
	.string "I feel wonderful!$"

BattleFrontier_BattlePikeLobby_Text_G6Plaque:
	.string "GAUNTLET 6 - THE CROSSROADS.\p"
	.string "Doubles. Boss: PIKE QUEEN LUCY.\p"
	.string "Not yet cleared.$"

BattleFrontier_BattlePikeLobby_Text_G6PlaqueCleared:
	.string "GAUNTLET 6 - THE CROSSROADS.\p"
	.string "Doubles. Boss: PIKE QUEEN LUCY.\p"
	.string "Cleared by {PLAYER}!$"

BattleFrontier_BattlePikeLobby_Text_G6Rules:
	.string "THE CROSSROADS\p"
	.string "Every team here takes one of four\n"
	.string "roads: WEATHER, TERRAIN, TRICK\l"
	.string "ROOM, or RAW POWER.\p"
	.string "Read the road on turn one, and cut\n"
	.string "it off.$"

BattleFrontier_BattlePikeLobby_Text_G6Hiker:
	.string "Hi! You, there!\p"
	.string "Every team in here takes one of\n"
	.string "four roads: weather, terrain,\l"
	.string "TRICK ROOM, or raw power.\p"
	.string "Spot the road on turn one, and\n"
	.string "you're halfway there.$"

BattleFrontier_BattlePikeLobby_Text_G6Twin:
	.string "I brought my Singles team to a\n"
	.string "Doubles gauntlet...\p"
	.string "Spread moves hit both of my\n"
	.string "POKéMON. Every single turn.$"

BattleFrontier_BattlePikeLobby_Text_G6Beauty:
	.string "Their PELIPPER set up rain, and I\n"
	.string "just kept attacking...\p"
	.string "I should have taken the weather\n"
	.string "away first.$"
