BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_ScottExplainsBattleRules, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_ScottExplainsShop, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_ScottExplainsWhereToStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

@ Ten Gauntlets: the facility guide is now the gauntlet guide - no menu,
@ just where the player's next gauntlet is. The vanilla facility menu below
@ (ChooseFacilityToLearnAbout) is unreferenced now.
BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_GauntletGuideIntro, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetGauntletsClearedCount
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_NextGauntlet1
	case 1, BattleFrontier_ReceptionGate_EventScript_NextGauntlet2
	case 2, BattleFrontier_ReceptionGate_EventScript_NextGauntlet3
	case 3, BattleFrontier_ReceptionGate_EventScript_NextGauntlet4
	case 4, BattleFrontier_ReceptionGate_EventScript_NextGauntlet5
	case 5, BattleFrontier_ReceptionGate_EventScript_NextGauntlet6
	case 10, BattleFrontier_ReceptionGate_EventScript_AllGauntletsCleared
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntletNotReady, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

@ Ten Gauntlets: the rules guide walks through the Ten Gauntlets rules in
@ order. The vanilla rules menu below (ChooseRuleToLearnAbout) is
@ unreferenced now.
BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_RulesGuideIntro, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_RulesTeam, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_RulesBattles, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_RulesItems, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_RulesLosing, MSGBOX_DEFAULT
	release
	end
BattleFrontier_ReceptionGate_EventScript_NextGauntlet1::
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntlet1, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_NextGauntlet2::
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntlet2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_NextGauntlet3::
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntlet3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_NextGauntlet4::
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntlet4, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_NextGauntlet5::
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntlet5, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_NextGauntlet6::
	msgbox BattleFrontier_ReceptionGate_Text_NextGauntlet6, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_AllGauntletsCleared::
	msgbox BattleFrontier_ReceptionGate_Text_AllGauntletsCleared, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

@ Ten Gauntlets: the FRONTIER PASS guide is now the FP and roster guide.
@ The vanilla FRONTIER PASS menu below is unreferenced now.
BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_FPGuideIntro, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_FPGuideEarning, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_FPGuideRoster, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_FPGuideTools, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "Is it your first time here?\n"
	.string "Please step this way!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "The front lines of POKéMON\n"
	.string "battling! Welcome to the BATTLE\l"
	.string "FRONTIER, home of the Ten\l"
	.string "Gauntlets!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "For a first-time visitor, we issue\n"
	.string "the FRONTIER PASS.\p"
	.string "It's for use at all the facilities\n"
	.string "in the BATTLE FRONTIER.\p"
	.string "Here you are!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "{PLAYER} obtained\n"
	.string "the FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "{PLAYER} placed the TRAINER CARD\n"
	.string "in the FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "Ten gauntlets, and only one way\n"
	.string "through: forward. Good luck!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "???: Well, if it isn't {PLAYER}{KUN}!\n"
	.string "You came out here!$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "GUIDE: Oh! MR. SCOTT, sir!\n"
	.string "Good day to you, sir!$"

@ Ten Gauntlets: this whole speech used to be one giant string with 15 \p
@ pages. msgbox expands its text into the fixed 1000-byte gStringVar4
@ buffer (StringExpandPlaceholders, src/field_message_box.c) regardless of
@ length - that one string ran to ~1950 raw characters and silently
@ overflowed it, corrupting nearby memory and eventually crashing with a
@ "jumped to invalid address" fault well after the fact. Split into four
@ separate msgbox calls (see ScottScene above), each comfortably under the
@ limit - same pattern already used for Birch's equally long explanation in
@ LittlerootTown_ProfessorBirchsLab.
BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "SCOTT: It's great to see you here,\n"
	.string "it really is!\p"
	.string "Let me tell you how things work\n"
	.string "around here, because this circuit\l"
	.string "isn't like anything you've faced\l"
	.string "before.\p"
	.string "Forget GYMS and BADGES. Here,\n"
	.string "there are ten gauntlets, and\l"
	.string "battling your way through them is\l"
	.string "the whole game.\p"
	.string "Each gauntlet throws six trainers\n"
	.string "at you, drawn at random from a\l"
	.string "pool of twelve. Beat all six, and\l"
	.string "that gauntlet's boss is waiting\l"
	.string "for you.\p"
	.string "Beat the boss, and the gauntlet's\n"
	.string "cleared - for good. There's no\l"
	.string "going back in for a rematch, so\l"
	.string "bring your best team every time.$"

BattleFrontier_ReceptionGate_Text_ScottExplainsBattleRules:
	.string "You'll get a full heal between every\n"
	.string "single battle, and held items come\l"
	.string "right back, too. But whatever's in your\l"
	.string "BAG stays there. Once you're in, it's\l"
	.string "just you and your team.\p"
	.string "Win, and you'll earn FP. Lose, and you\n"
	.string "keep whatever FP you've already banked -\l"
	.string "a bad run only costs you the streak,\l"
	.string "never your progress.\p"
	.string "Oh, and MEGA EVOLUTION is alive and well\n"
	.string "in this format. TERASTALLIZING,\l"
	.string "Z-MOVES, DYNAMAXING - none of that\l"
	.string "exists here. Just POKéMON, movesets,\l"
	.string "and MEGAS.$"

BattleFrontier_ReceptionGate_Text_ScottExplainsShop:
	.string "Spend that FP right here with us,\n"
	.string "at the EXCHANGE SERVICE CORNER\l"
	.string "just outside. Four keepers, four\l"
	.string "specialties - Consumables, Held\l"
	.string "Items, MEGA STONES, and POKéMON.\p"
	.string "Everything you buy there is yours\n"
	.string "for good, no renting. And if a\l"
	.string "POKéMON isn't working out for you,\l"
	.string "that same keeper will buy it back\l"
	.string "for half what you paid.\p"
	.string "Right now you're only seeing\n"
	.string "what's on the shelves for gauntlet\l"
	.string "one. Clear more gauntlets, and\l"
	.string "better stock comes out from the\l"
	.string "back.$"

BattleFrontier_ReceptionGate_Text_ScottExplainsWhereToStart:
	.string "As for where to start - the BATTLE\n"
	.string "TOWER holds the first four\l"
	.string "gauntlets. The other doors are\l"
	.string "locked up tight. Clear what's in\l"
	.string "front of you, and they'll open up\l"
	.string "one at a time.\p"
	.string "But before you go anywhere near\n"
	.string "the TOWER, come by my house. It's\l"
	.string "at the north end of the plaza,\l"
	.string "past the BATTLE PIKE.\p"
	.string "One POKéMON won't get you through\n"
	.string "the door of gauntlet one - I've\l"
	.string "got something for you. See you\l"
	.string "there, {PLAYER}{KUN}!$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "I'm your guide to the various facilities\n"
	.string "here in the BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "Which would you like to learn about?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "It is the gigantic tower considered\n"
	.string "to be the BATTLE FRONTIER's symbol.\p"
	.string "There are four kinds of BATTLE ROOMS\n"
	.string "in the tower for SINGLE, DOUBLE, MULTI,\l"
	.string "and LINK MULTI BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "The BATTLE DOME is the large building\n"
	.string "shaped like a huge egg.\p"
	.string "Events named Battle Tourneys are held\n"
	.string "in this facility.\p"
	.string "The Battle Tourneys are offered in\n"
	.string "two courses--for SINGLE and DOUBLE\l"
	.string "BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "The BATTLE PALACE is the red building\n"
	.string "on the right of the BATTLE FRONTIER.\p"
	.string "There are two kinds of BATTLE HALLS\n"
	.string "for SINGLE and DOUBLE BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "The BATTLE ARENA is the dojo-like\n"
	.string "building at the center-right of\l"
	.string "the BATTLE FRONTIER.\p"
	.string "An event called the Set KO Tourney\n"
	.string "takes place at the BATTLE ARENA.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "The BATTLE FACTORY is the large\n"
	.string "building that is the closest to us.\p"
	.string "An event called the Battle Swap\n"
	.string "is conducted there.\p"
	.string "The Battle Swap event is offered in\n"
	.string "two courses for SINGLE and DOUBLE\l"
	.string "BATTLES.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "The BATTLE PIKE is the building shaped\n"
	.string "like a POKéMON at the center-left of\l"
	.string "the BATTLE FRONTIER.\p"
	.string "An event called the Battle Choice\n"
	.string "is conducted there.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "The BATTLE PYRAMID is the enormous\n"
	.string "pyramid.\p"
	.string "An event called the Battle Quest\n"
	.string "is conducted there.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "The RANKING HALL is located near\n"
	.string "the BATTLE TOWER.\p"
	.string "There, you may see the most fantastic\n"
	.string "records left by the TRAINERS that\l"
	.string "took on the many challenges of\l"
	.string "the BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "The EXCHANGE SERVICE CORNER is near\n"
	.string "the BATTLE TOWER.\p"
	.string "The Battle Points you have earned in\n"
	.string "the BATTLE FRONTIER may be exchanged\l"
	.string "for fabulous prizes there.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "I'm your guide to the basic rules that\n"
	.string "are common to all the challenges\l"
	.string "offered by the facilities in the BATTLE\l"
	.string "FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "What would you like to learn about?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "All the challenges at the BATTLE\n"
	.string "FRONTIER's facilities come in\l"
	.string "two courses--Level 50 and Open Level.$"

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "The Level 50 course is open to POKéMON\n"
	.string "up to and including Level 50.\p"
	.string "Please keep in mind, however, that\n"
	.string "no TRAINER you face will have any\l"
	.string "POKéMON below Level 50.\p"
	.string "This course is the entry level for\n"
	.string "battles at the BATTLE FRONTIER.\p"
	.string "To begin, we hope you will challenge\n"
	.string "this course.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "The Open Level course places no limit\n"
	.string "on the levels of POKéMON entering\l"
	.string "challenges.\p"
	.string "The levels of your opponents will\n"
	.string "be adjusted to match the levels of\l"
	.string "your POKéMON.\p"
	.string "However, no TRAINER you face will\n"
	.string "have any POKéMON below Level 60.$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "Virtually any kind of POKéMON may take\n"
	.string "on the challenges at all facilities.\p"
	.string "EGGS and certain kinds of POKéMON,\n"
	.string "however, are not permitted.\p"
	.string "The numbers of POKéMON required for\n"
	.string "challenges will depend on the facility.\p"
	.string "At all facilities, however, two or more\n"
	.string "of the same kind of POKéMON are not\l"
	.string "permitted.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "When entering a challenge at a BATTLE\n"
	.string "FRONTIER facility, POKéMON may not\l"
	.string "be holding the same kind of item.\p"
	.string "Please make sure that all POKéMON\n"
	.string "entering a challenge are holding\l"
	.string "different items.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "I'm your guide to the FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "Which would you like to learn about?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "There are seven facilities at\n"
	.string "the BATTLE FRONTIER.\p"
	.string "TRAINERS who gain recognition for\n"
	.string "their abilities may be rewarded with\l"
	.string "symbols from each of the facilities.\p"
	.string "To earn a symbol, TRAINERS may need\n"
	.string "to defeat other TRAINERS in a row,\l"
	.string "and may need to win events repeatedly.\p"
	.string "It's certainly not easy to win symbols.\n"
	.string "I wish you the best of luck!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "It is possible to record one battle\n"
	.string "on your FRONTIER PASS.\p"
	.string "You may record a battle you had with\n"
	.string "a friend or friends.\p"
	.string "Or you may record a battle conducted\n"
	.string "at the BATTLE FRONTIER excluding\l"
	.string "matches at the BATTLE PIKE or\l"
	.string "the BATTLE PYRAMID.\p"
	.string "You may choose to record your match\n"
	.string "at the end of a battle.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "Battle Points are rewards given to\n"
	.string "TRAINERS who battled outstandingly\l"
	.string "at the BATTLE FRONTIER.\p"
	.string "You may trade in your Battle Points\n"
	.string "for prizes at the EXCHANGE SERVICE\l"
	.string "CORNER.$"

BattleFrontier_ReceptionGate_Text_GauntletGuideIntro:
	.string "I'm your guide to the Ten\n"
	.string "Gauntlets!\p"
	.string "The BATTLE TOWER holds the first\n"
	.string "four, one on each mat. After that,\l"
	.string "each of the other facilities holds\l"
	.string "one: the DOME, the FACTORY, the\l"
	.string "PIKE, the ARENA, the PALACE and\l"
	.string "the PYRAMID.\p"
	.string "Singles and Doubles take turns,\n"
	.string "and each gauntlet opens once you\l"
	.string "clear the one before it.$"

BattleFrontier_ReceptionGate_Text_NextGauntlet1:
	.string "Your first gauntlet is LITTLE\n"
	.string "LEAGUE, on the BATTLE TOWER's\l"
	.string "first mat. Singles.\p"
	.string "The TOWER is the big building on\n"
	.string "the east side of the FRONTIER.$"

BattleFrontier_ReceptionGate_Text_NextGauntlet2:
	.string "Next up is THE SECOND SLOT, on the\n"
	.string "BATTLE TOWER's second mat. It's\l"
	.string "Doubles!$"

BattleFrontier_ReceptionGate_Text_NextGauntlet3:
	.string "Next up is THE CHANGING SKY, on\n"
	.string "the BATTLE TOWER's third mat.\l"
	.string "Singles, and the weather matters\l"
	.string "in there.$"

BattleFrontier_ReceptionGate_Text_NextGauntlet4:
	.string "Next up is THE TURN ORDER, the\n"
	.string "BATTLE TOWER's last mat. Doubles.\l"
	.string "The SALON MAIDEN, ANABEL, is\l"
	.string "waiting at the end.$"

BattleFrontier_ReceptionGate_Text_NextGauntlet5:
	.string "Next up is THE MAIN EVENT, at the\n"
	.string "BATTLE DOME. Singles, and the DOME\l"
	.string "ACE, TUCKER, is waiting at the\l"
	.string "end.\p"
	.string "The DOME is the big round building\n"
	.string "on the west side of the FRONTIER.$"

BattleFrontier_ReceptionGate_Text_NextGauntlet6:
	.string "Next up is THE ASSEMBLY LINE, at\n"
	.string "the BATTLE FACTORY. Doubles, with\l"
	.string "the FACTORY HEAD, NOLAND, at the\l"
	.string "end.\p"
	.string "The FACTORY is on the west side of\n"
	.string "the FRONTIER.$"

BattleFrontier_ReceptionGate_Text_NextGauntletNotReady:
	.string "You've come further than anyone!\n"
	.string "The next gauntlet is still being\l"
	.string "prepared. Please check back soon.$"

BattleFrontier_ReceptionGate_Text_AllGauntletsCleared:
	.string "You've cleared all ten gauntlets…\p"
	.string "I've never said that to anyone\n"
	.string "before. Congratulations!$"

BattleFrontier_ReceptionGate_Text_RulesGuideIntro:
	.string "I'm your guide to the rules of the\n"
	.string "Ten Gauntlets. Here's everything\l"
	.string "you need to know!$"

BattleFrontier_ReceptionGate_Text_RulesTeam:
	.string "Your whole party of six enters,\n"
	.string "and every POKéMON battles at level\l"
	.string "50.\p"
	.string "Once a run begins, your team is\n"
	.string "locked in until it ends.$"

BattleFrontier_ReceptionGate_Text_RulesBattles:
	.string "Each gauntlet is six battles,\n"
	.string "drawn at random from twelve, then\l"
	.string "its boss.\p"
	.string "You're fully healed after every\n"
	.string "battle.$"

BattleFrontier_ReceptionGate_Text_RulesItems:
	.string "Items in your BAG can't be used\n"
	.string "during a run. Held items can, and\l"
	.string "they come back after every battle.\p"
	.string "No two POKéMON on a team may hold\n"
	.string "the same item. That goes for your\l"
	.string "opponents, too.$"

BattleFrontier_ReceptionGate_Text_RulesLosing:
	.string "If you lose, the run ends, but you\n"
	.string "keep your team and every FP you've\l"
	.string "earned.\p"
	.string "Beat the boss and the gauntlet is\n"
	.string "cleared for good. There's no going\l"
	.string "back in, only forward!$"

BattleFrontier_ReceptionGate_Text_FPGuideIntro:
	.string "I'm your guide to FP and your\n"
	.string "roster!$"

BattleFrontier_ReceptionGate_Text_FPGuideEarning:
	.string "FP, FRONTIER POINTS, are earned\n"
	.string "for every battle you win, and\l"
	.string "clearing a gauntlet pays out much\l"
	.string "more.\p"
	.string "You keep everything you've earned,\n"
	.string "even if you lose.$"

BattleFrontier_ReceptionGate_Text_FPGuideRoster:
	.string "Spend FP at the EXCHANGE SERVICE\n"
	.string "CORNER on POKéMON, held items and\l"
	.string "MEGA STONES. Everything you buy is\l"
	.string "yours for good.\p"
	.string "If a POKéMON isn't working out,\n"
	.string "the keeper will buy it back for\l"
	.string "half what it cost.$"

BattleFrontier_ReceptionGate_Text_FPGuideTools:
	.string "Press the L BUTTON outside a run\n"
	.string "to open your trainer tools.\p"
	.string "You can change a POKéMON's stats,\n"
	.string "nature, HIDDEN POWER, ability and\l"
	.string "moves, so every POKéMON you buy\l"
	.string "can be built exactly how you like.$"
