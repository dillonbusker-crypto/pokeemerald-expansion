BattleFrontier_ScottsHouse_MapScripts::
	.byte 0

@ Ten Gauntlets: SCOTT is the host of the Ten Gauntlets. First visit, he
@ hands over the starting team (five Pokemon, 300 FP and the HMs - see
@ GiveFrontierStartingMon() in src/new_game.c), one Pokemon at a time. After
@ that, he has one line per number of gauntlets cleared. The vanilla branches
@ below (Battle Points gift, Symbol berries, Shields) are unreferenced now.
BattleFrontier_ScottsHouse_EventScript_Scott::
	lock
	faceplayer
	specialvar VAR_RESULT, HasReceivedFrontierStartingGrants
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_GiveStartingTeam
	specialvar VAR_RESULT, GetGauntletsClearedCount
	switch VAR_RESULT
	case 0, BattleFrontier_ScottsHouse_EventScript_Progress0
	case 1, BattleFrontier_ScottsHouse_EventScript_Progress1
	case 2, BattleFrontier_ScottsHouse_EventScript_Progress2
	case 3, BattleFrontier_ScottsHouse_EventScript_Progress3
	case 4, BattleFrontier_ScottsHouse_EventScript_Progress4
	case 5, BattleFrontier_ScottsHouse_EventScript_Progress5
	case 10, BattleFrontier_ScottsHouse_EventScript_Progress10
	msgbox BattleFrontier_ScottsHouse_Text_Progress6Plus, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GiveStartingTeam::
	msgbox BattleFrontier_ScottsHouse_Text_HereIsYourTeam, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
BattleFrontier_ScottsHouse_EventScript_GiveStartingMonLoop::
	special GiveFrontierStartingMon
	playfanfare MUS_OBTAIN_ITEM
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, BattleFrontier_ScottsHouse_EventScript_StartingMonToPC
	message BattleFrontier_ScottsHouse_Text_ReceivedMon
	goto BattleFrontier_ScottsHouse_EventScript_StartingMonNext
BattleFrontier_ScottsHouse_EventScript_StartingMonToPC::
	message BattleFrontier_ScottsHouse_Text_ReceivedMonToPC
BattleFrontier_ScottsHouse_EventScript_StartingMonNext::
	waitmessage
	waitfanfare
	waitbuttonpress
	addvar VAR_0x8004, 1
	goto_if_lt VAR_0x8004, 5, BattleFrontier_ScottsHouse_EventScript_GiveStartingMonLoop
	special GiveFrontierStartingFPAndHMs
	msgbox BattleFrontier_ScottsHouse_Text_HereIsFPAndHMs, MSGBOX_DEFAULT
	msgbox BattleFrontier_ScottsHouse_Text_NowYouHaveSix, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress0::
	msgbox BattleFrontier_ScottsHouse_Text_Progress0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress1::
	msgbox BattleFrontier_ScottsHouse_Text_Progress1, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress2::
	msgbox BattleFrontier_ScottsHouse_Text_Progress2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress3::
	msgbox BattleFrontier_ScottsHouse_Text_Progress3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress4::
	msgbox BattleFrontier_ScottsHouse_Text_Progress4, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress5::
	msgbox BattleFrontier_ScottsHouse_Text_Progress5, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_Progress10::
	msgbox BattleFrontier_ScottsHouse_Text_Progress10, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_Text_HereIsYourTeam:
	.string "SCOTT: There you are, {PLAYER}{KUN}!\p"
	.string "Every challenger needs six POKéMON\n"
	.string "to enter a gauntlet, and you've\l"
	.string "only brought one.\p"
	.string "So I put together a few of my own\n"
	.string "favorites to round you out.\p"
	.string "They're no champions, but they're\n"
	.string "honest workers. Look after them!$"

BattleFrontier_ScottsHouse_Text_ReceivedMon:
	.string "{PLAYER} received {STR_VAR_1}!$"

BattleFrontier_ScottsHouse_Text_ReceivedMonToPC:
	.string "{PLAYER} received {STR_VAR_1}!\n"
	.string "It was sent to the PC.$"

BattleFrontier_ScottsHouse_Text_HereIsFPAndHMs:
	.string "SCOTT: And a little something to\n"
	.string "spend - 300 FP, plus a set of HMs.\p"
	.string "When you can afford better POKéMON,\n"
	.string "the EXCHANGE CORNER will take these\l"
	.string "off your hands. No hard feelings.$"

BattleFrontier_ScottsHouse_Text_NowYouHaveSix:
	.string "Now you've got six. The BATTLE\n"
	.string "TOWER is waiting. Go show me I was\l"
	.string "right about you!$"

BattleFrontier_ScottsHouse_Text_Progress0:
	.string "SCOTT: The BATTLE TOWER's first\n"
	.string "mat is where everyone starts. Six\l"
	.string "battles, then WARDEN HELIS.\p"
	.string "Seven facilities used to test\n"
	.string "seven different skills. I wanted\l"
	.string "one ladder that tests all of them,\l"
	.string "in order.\p"
	.string "That's the Ten Gauntlets.$"

BattleFrontier_ScottsHouse_Text_Progress1:
	.string "SCOTT: You got past HELIS! I knew\n"
	.string "it!\p"
	.string "The next mat is DOUBLES. Two\n"
	.string "POKéMON on each side changes\l"
	.string "everything you think you know.\l"
	.string "Don't get comfortable.$"

BattleFrontier_ScottsHouse_Text_Progress2:
	.string "SCOTT: Two gauntlets down!\p"
	.string "The third mat is about the sky\n"
	.string "itself. Rain, sun, sand, snow...\l"
	.string "In there, the weather is a weapon.$"

BattleFrontier_ScottsHouse_Text_Progress3:
	.string "SCOTT: Three! Now it gets serious.\p"
	.string "The last TOWER mat belongs to\n"
	.string "ANABEL. She's the first of my\l"
	.string "FRONTIER BRAINS, and she doesn't\l"
	.string "lose often.$"

BattleFrontier_ScottsHouse_Text_Progress4:
	.string "SCOTT: You beat ANABEL! Heheh...\n"
	.string "I'll admit, I didn't see that\l"
	.string "coming so soon.\p"
	.string "The BATTLE DOME is open to you\n"
	.string "now. TUCKER loves an audience.\l"
	.string "Give him one worth remembering.$"

BattleFrontier_ScottsHouse_Text_Progress5:
	.string "SCOTT: The DOME ACE himself,\n"
	.string "beaten!\p"
	.string "Next is the BATTLE FACTORY. NOLAND\n"
	.string "builds every team on that line to\l"
	.string "a plan. Find the plan, break it.$"

BattleFrontier_ScottsHouse_Text_Progress6Plus:
	.string "SCOTT: Heheh... You're further\n"
	.string "along than anyone I've ever\l"
	.string "brought here.\p"
	.string "The rest of the FRONTIER is still\n"
	.string "being prepared for you. When the\l"
	.string "next door opens, you'll be the\l"
	.string "first to know.$"

BattleFrontier_ScottsHouse_Text_Progress10:
	.string "SCOTT: All ten gauntlets... All\n"
	.string "seven of my BRAINS...\p"
	.string "I built this place to find one\n"
	.string "trainer who could do that. And now\l"
	.string "that I've found you... Heheh.\p"
	.string "There's something after the tenth\n"
	.string "that I haven't told anyone about.\l"
	.string "Not yet.$"

BattleFrontier_ScottsHouse_EventScript_CheckGiveItems::
	goto_if_unset FLAG_SCOTT_GIVES_BATTLE_POINTS, BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier
	goto_if_unset FLAG_COLLECTED_ALL_SILVER_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols
	goto_if_unset FLAG_COLLECTED_ALL_GOLD_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveShield::
	goto_if_unset FLAG_RECEIVED_SILVER_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield
	goto_if_unset FLAG_RECEIVED_GOLD_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols::
	goto_if_unset FLAG_SYS_TOWER_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols, MSGBOX_DEFAULT
	giveitem ITEM_LANSAT_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_SILVER_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols::
	goto_if_unset FLAG_SYS_TOWER_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_DOME_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PALACE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_ARENA_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_FACTORY_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PIKE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	goto_if_unset FLAG_SYS_PYRAMID_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols, MSGBOX_DEFAULT
	giveitem ITEM_STARF_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull
	setflag FLAG_COLLECTED_ALL_GOLD_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_BerryPocketFull::
	msgbox BattleFrontier_ScottsHouse_Text_BerryPocketStuffed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenBerry::
	msgbox BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_RandomComment::
	random 3
	goto_if_eq VAR_RESULT, 1, BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment
	goto_if_eq VAR_RESULT, 2, BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment
	msgbox BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment::
	msgbox BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment::
	msgbox BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveSilverShield::
	msgbox BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_SILVER_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_SILVER_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_NoRoomForShield::
	msgbox BattleFrontier_ScottsHouse_Text_ComeBackForThisLater, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenShield::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment
	end

BattleFrontier_ScottsHouse_EventScript_GiveGoldShield::
	msgbox BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow, MSGBOX_DEFAULT
	givedecoration DECOR_GOLD_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield
	setflag FLAG_RECEIVED_GOLD_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield
	end

BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingGreatThings, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier::
	msgbox BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	closemessage
	delay 30
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest
	msgbox BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing, MSGBOX_DEFAULT
	goto_if_eq VAR_SCOTT_STATE, 13, BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints
	goto_if_ge VAR_SCOTT_STATE, 9, BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints
	goto_if_ge VAR_SCOTT_STATE, 6, BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints
	goto BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint
	end

BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints::
	buffernumberstring STR_VAR_1, 4
	setvar VAR_0x8004, 4
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints::
	buffernumberstring STR_VAR_1, 3
	setvar VAR_0x8004, 3
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints::
	buffernumberstring STR_VAR_1, 2
	setvar VAR_0x8004, 2
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint::
	buffernumberstring STR_VAR_1, 1
	setvar VAR_0x8004, 1
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints
	end

BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints::
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	msgbox BattleFrontier_ScottsHouse_Text_ExplainBattlePoints, MSGBOX_DEFAULT
	setflag FLAG_SCOTT_GIVES_BATTLE_POINTS
	setflag FLAG_TEMP_2
	release
	end

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayNorth::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwaySouth::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayEast::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_ScottFaceAwayWest::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier:
	.string "SCOTT: Well, hello and welcome!\n"
	.string "Heheh… Sorry about the cramped space.\p"
	.string "Anyway, {PLAYER}{KUN}, let me formally\n"
	.string "welcome you to the BATTLE FRONTIER.\p"
	.string "This is my dream come true.\n"
	.string "It took me years and years, but I've\l"
	.string "finally given shape to my dream.$"

BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal:
	.string "On reflection, it was a terribly long\n"
	.string "journey…\p"
	.string "I left home alone on a quest to find\n"
	.string "strong TRAINERS.\p"
	.string "No one can imagine how much effort\n"
	.string "or time it took to make this real.$"

BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing:
	.string "But that's all in the past.\n"
	.string "No point dwelling on that!\p"
	.string "All I want for you is to enjoy battling\n"
	.string "to your heart's content here.\p"
	.string "{PLAYER}{KUN}, I want you to have this\n"
	.string "as a memento for all the time our\l"
	.string "paths crossed on our journeys.$"

BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints:
	.string "{PLAYER} obtained\n"
	.string "{STR_VAR_1} Battle Point(s).$"

BattleFrontier_ScottsHouse_Text_ExplainBattlePoints:
	.string "SCOTT: You can check your Battle\n"
	.string "Points on your FRONTIER PASS.\p"
	.string "The more success you have here at\n"
	.string "the BATTLE FRONTIER, the more Battle\l"
	.string "Points you will collect.\p"
	.string "Use your Battle Points the way you\n"
	.string "see fit, like trading them for items.$"

BattleFrontier_ScottsHouse_Text_ExpectingGreatThings:
	.string "I'm expecting great things from you!$"

BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers:
	.string "SCOTT: Every TRAINER is an individual.\n"
	.string "They all lead lives of their own.\p"
	.string "But when they're in a battle,\n"
	.string "it doesn't matter who they are.\p"
	.string "They're all the same!\p"
	.string "I love the purity of battle,\n"
	.string "where everyone is equal.\p"
	.string "That's why I go everywhere seeking\n"
	.string "TRAINERS who are serious about\l"
	.string "battling, and invite them here.$"

BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain:
	.string "SCOTT: Have you met any of\n"
	.string "the FRONTIER BRAINS?\p"
	.string "Better yet, have you obtained any\n"
	.string "symbols from them?\p"
	.string "I handpicked the FRONTIER BRAINS\n"
	.string "as the toughest TRAINERS anywhere.\p"
	.string "But I'm sure that seeing how tough\n"
	.string "you are will startle even them!$"

BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier:
	.string "SCOTT: You don't just train for battle,\n"
	.string "right?\p"
	.string "I think I remember you working on\n"
	.string "a POKéDEX as well.\p"
	.string "Well, guess what?\p"
	.string "You may run into wild POKéMON in\n"
	.string "the BATTLE FRONTIER somewhere…\l"
	.string "Fufufu!$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols:
	.string "SCOTT: Are you enjoying things in\n"
	.string "the BATTLE FRONTIER?\p"
	.string "…Wait a second…\n"
	.string "Oh!\p"
	.string "Your FRONTIER PASS!\n"
	.string "You've collected the full set\l"
	.string "of silver symbols!\p"
	.string "That's more than impressive!\n"
	.string "You are tough, just as I suspected!\p"
	.string "Normally, I wouldn't do something\n"
	.string "like this, but this is a special time!\p"
	.string "I want you to have this.\n"
	.string "I'm sure you can put it to proper use.$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols:
	.string "SCOTT: I hope you're enjoying\n"
	.string "everything in the BATTLE FRONTIER.\p"
	.string "…Wait a second…\n"
	.string "Oh, my disbelieving eyes!\p"
	.string "Your FRONTIER PASS!\n"
	.string "You've gathered up the full set\l"
	.string "of gold symbols!\p"
	.string "That's more than stupendous!\n"
	.string "You're incredible, just as I suspected!\p"
	.string "… … … … … …\p"
	.string "{PLAYER}, you've got to accept this!\p"
	.string "I think you will be able to\n"
	.string "appreciate the value of my gift!$"

BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere:
	.string "I must say I have the gift of knowing\n"
	.string "a good TRAINER when I see one.\p"
	.string "I'm so glad I had the foresight to\n"
	.string "bring you here!$"

BattleFrontier_ScottsHouse_Text_BerryPocketStuffed:
	.string "Your BERRY POCKET seems to\n"
	.string "be stuffed.$"

BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow:
	.string "SCOTT: Oh, I heard about you!\n"
	.string "How you ruled the BATTLE TOWER!\l"
	.string "You beat over 50 TRAINERS in a row?\p"
	.string "That's fantastic!\n"
	.string "I want you to have this!$"

BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow:
	.string "SCOTT: Oh, my! I heard about you!\n"
	.string "How you overwhelmed the BATTLE TOWER!\l"
	.string "You beat over 100 TRAINERS in a row?\p"
	.string "That's ridiculously spectacular!\n"
	.string "You've got to have this!$"

BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings:
	.string "I'll be expecting to hear even greater\n"
	.string "things about you now!$"

BattleFrontier_ScottsHouse_Text_ComeBackForThisLater:
	.string "Oops, well, if you have too much\n"
	.string "stuff, come back for this later.$"

