MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MauvilleCity_OnFrame
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	@ Ten Gauntlets: only reached in the endgame (data/scripts/endgame_towns.inc).
	@ No WALLY fight, no vanilla SCOTT, and no WATTSON outside with the
	@ BASEMENT KEY.
	setflag FLAG_HIDE_MAUVILLE_CITY_WALLY
	setflag FLAG_HIDE_MAUVILLE_CITY_WALLYS_UNCLE
	setflag FLAG_HIDE_MAUVILLE_CITY_SCOTT
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	call MauvilleCity_EventScript_SetupEndgame
	call MauvilleCity_EventScript_SetupCalyrex
	end

MauvilleCity_OnFrame:
	map_script_2 VAR_TEMP_1, 1, MauvilleCity_EventScript_ArrivalScene
	map_script_2 VAR_TEMP_1, 2, MauvilleCity_EventScript_CenterScene
	.2byte 0

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_MAUVILLE_WALLY
	removeobject LOCALID_MAUVILLE_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_MAUVILLE_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_MAUVILLE_SCOTT, 12, 13
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
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

MauvilleCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "UNCLE: It's because of POKéMON that\n"
	.string "this boy's got more pep, I suppose…\l"
	.string "But he's become a bit too peppy…$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "WALLY: Aww, UNCLE, please?\p"
	.string "I want to challenge this GYM and see\n"
	.string "how much better I've become.\p"
	.string "Please? May I, please?$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "UNCLE: Now hold on, WALLY.\p"
	.string "Since you started living with POKéMON,\n"
	.string "you have grown quite a lot stronger.\p"
	.string "But don't you think you're pushing it\n"
	.string "to suddenly challenge a GYM?$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "WALLY: I'm not pushing it.\p"
	.string "If I combine forces with RALTS,\n"
	.string "we can beat anyone!$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "WALLY: Oh! Hi, {PLAYER}!\p"
	.string "I've gotten a lot stronger since\n"
	.string "we met.\p"
	.string "{PLAYER}, I want you and my UNCLE to\n"
	.string "understand that.\p"
	.string "{PLAYER}, please, will you have\n"
	.string "a battle with me?$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "WALLY: Oh… If you won't battle me,\n"
	.string "{PLAYER}, my UNCLE won't know that I've\l"
	.string "become really strong.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "UNCLE: {PLAYER}{KUN}, was it?\n"
	.string "On WALLY's behalf, can I ask you to\l"
	.string "battle with him just this once?\p"
	.string "I don't think he's going to listen to\n"
	.string "any reason the way he is now.$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "WALLY: {PLAYER}, please!\n"
	.string "Battle with me, please.$"

MauvilleCity_Text_WallyHereICome:
	.string "WALLY: {PLAYER}, thank you.\p"
	.string "Okay… Here I come!$"

MauvilleCity_Text_WallyDefeat:
	.string "WALLY: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "I lost…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "WALLY: UNCLE…\n"
	.string "I'll go back to VERDANTURF…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{PLAYER}, thank you.\n"
	.string "Being a TRAINER is tough, isn't it?\p"
	.string "It's not enough just to have POKéMON\n"
	.string "and make them battle. That isn't what\l"
	.string "being a real TRAINER is about.$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "UNCLE: WALLY, there's no need to be so\n"
	.string "down on yourself.\p"
	.string "Why, what's keeping you from becoming\n"
	.string "stronger and stronger?\p"
	.string "Come on, let's go home.\n"
	.string "Everyone's waiting for you.$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "UNCLE: {PLAYER}{KUN}, it just dawned on me\n"
	.string "that you must be the TRAINER who kept\l"
	.string "an eye out for WALLY when he caught\l"
	.string "his POKéMON.\p"
	.string "Why don't you visit us in VERDANTURF\n"
	.string "sometime?\l"
	.string "I'm sure WALLY would enjoy it.$"


MauvilleCity_Text_WallyPokenavCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "WALLY: Oh, hello, {PLAYER}!\p"
	.string "I just wanted to tell you that\n"
	.string "my uncle bought me a POKéNAV!\p"
	.string "Now I can get in touch with you\n"
	.string "anytime, {PLAYER}!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

MauvilleCity_Text_RegisteredWally:
	.string "Registered WALLY\n"
	.string "in the POKéNAV.$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "SCOTT: Hehe…\n"
	.string "I was watching that match!\p"
	.string "You're friends with that boy WALLY,\n"
	.string "aren't you?\p"
	.string "But you didn't hold anything back\n"
	.string "and beat him impressively.\p"
	.string "Yeah! That's what a real POKéMON\n"
	.string "battle is all about!\p"
	.string "I idolize TRAINERS like that!\p"
	.string "… … … … … …\n"
	.string "I'll be cheering for you!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "WATTSON: Oh, {PLAYER}{KUN}!\n"
	.string "You look like you have a lot of zip!\l"
	.string "That's a good thing, wahahahaha!\p"
	.string "Fine! I've decided!\n"
	.string "I need a favor, {PLAYER}{KUN}!\p"
	.string "MAUVILLE CITY has an underground\n"
	.string "sector called NEW MAUVILLE.\p"
	.string "{PLAYER}{KUN}, I'd like you to go there and\n"
	.string "switch off the GENERATOR.\p"
	.string "The GENERATOR has been running a bit\n"
	.string "haywire. It's getting unsafe.\p"
	.string "Here, this is the KEY to get into\n"
	.string "NEW MAUVILLE.$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "WATTSON: Don't you worry about it.\n"
	.string "It won't be a challenge to you.\p"
	.string "The entrance to NEW MAUVILLE is just\n"
	.string "a short SURF away from ROUTE 110.\p"
	.string "That's it, then, you have my trust!\n"
	.string "Wahahahaha!$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "WATTSON: Wahahahaha!\p"
	.string "I knew it, {PLAYER}{KUN}! I knew I'd made\n"
	.string "the right choice asking you!\p"
	.string "This is my thanks--a TM containing\n"
	.string "THUNDERBOLT!\p"
	.string "Go on, you've earned it!$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "WATTSON: Wahahahaha!\p"
	.string "It pleases me to no end to see\n"
	.string "the young step up and take charge!$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "You know, it's cool to have POKéMON\n"
	.string "battles and stuff…\p"
	.string "But if your POKéMON gets hurt,\n"
	.string "you have to nurse it back to health.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "The roads of this town stretch north\n"
	.string "and south, and east and west.\p"
	.string "Because of that, we get all sorts of\n"
	.string "people coming through.$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "Have you been to RYDEL'S CYCLES yet?\p"
	.string "RYDEL, the owner, is a very generous\n"
	.string "man.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "Even if you're riding a BIKE,\n"
	.string "wild POKéMON could jump you.$"

MauvilleCity_Text_CitySign:
	.string "MAUVILLE CITY\n"
	.string "“The bright and shiny city of fun!”$"

MauvilleCity_Text_GymSign:
	.string "MAUVILLE CITY POKéMON GYM\n"
	.string "LEADER: WATTSON\l"
	.string "“The cheerfully electrifying man!”$"

MauvilleCity_Text_BikeShopSign:
	.string "“Ride in gravel and shake up your\n"
	.string "soul!”\l"
	.string "RYDEL'S CYCLES$"

MauvilleCity_Text_GameCornerSign:
	.string "“The play spot for all!”\n"
	.string "MAUVILLE GAME CORNER$"

MauvilleCity_Text_ExplainTV:
	.string "Hi, do you check out TV at all?\p"
	.string "They've added a bunch of cool new\n"
	.string "shows recently.\p"
	.string "TV is so cool. I've seen my friends on\n"
	.string "TV just out of the blue.\p"
	.string "And, sometimes, they even put you on TV\n"
	.string "without telling you.\p"
	.string "I wish I would be on TV sometime.\p"
	.string "That's why I think you should check\n"
	.string "out TVs whenever you can.$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Hi, have you been checking out TVs?$"

@ Ten Gauntlets: the endgame ABRA network (data/scripts/endgame_towns.inc).
MauvilleCity_EventScript_EndgameAbra::
	setvar VAR_0x8004, ABRA_AT_MAUVILLE
	goto EventScript_EndgameAbra

@ ============================================================================
@ Ten Gauntlets: Mauville and New Mauville (storyline.md; VAR_ENDGAME_STATE is
@ explained in BattleFrontier_OutsideEast). The ABRA lands the player at
@ (22, 6), above the POKEMON CENTER's door.
@   12 TEAM AQUA and TEAM MAGMA hold the town. WATTSON rushes up; STEVEN and
@      WALLACE stay to clear it, and WATTSON leads the player to NEW MAUVILLE
@      (state 13). A white-out anywhere from here on lands in the CENTER.
@   13 WATTSON waits by the CENTER's door, ready to lead the player back down
@   14 MAXIE and ARCHIE are beaten: the player comes out of the CENTER (New
@      Mauville's exit warp), the teams have left, and WATTSON, STEVEN and
@      WALLACE wait outside (state 15 after the scene)
@   15 WATTSON stays in town; STEVEN and WALLACE are at the FRONTIER
@ FLAG_TEMP_1 WATTSON, 2 STEVEN, 3 WALLACE, 4 the grunts.
@ ============================================================================

MauvilleCity_EventScript_SetupEndgame::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	goto_if_lt VAR_ENDGAME_STATE, 12, Common_EventScript_NopReturn
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call_if_le VAR_ENDGAME_STATE, 13, MauvilleCity_EventScript_ShowGrunts
	call_if_eq VAR_ENDGAME_STATE, 12, MauvilleCity_EventScript_SetupArrivalScene
	call_if_eq VAR_ENDGAME_STATE, 13, MauvilleCity_EventScript_ShowWattsonAtCenter
	call_if_eq VAR_ENDGAME_STATE, 14, MauvilleCity_EventScript_SetupCenterScene
	call_if_eq VAR_ENDGAME_STATE, 15, MauvilleCity_EventScript_ShowWattsonAtCenter
	return

MauvilleCity_EventScript_ShowGrunts::
	clearflag FLAG_TEMP_4
	return

@ WATTSON starts at (22, 10) and runs up to (22, 7); STEVEN and WALLACE are
@ already beside it, at (21, 7) and (23, 7).
MauvilleCity_EventScript_SetupArrivalScene::
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	setvar VAR_TEMP_1, 1
	return

MauvilleCity_EventScript_ShowWattsonAtCenter::
	clearflag FLAG_TEMP_1
	setobjectxyperm LOCALID_MAUVILLE_ENDGAME_WATTSON, 21, 8
	setobjectmovementtype LOCALID_MAUVILLE_ENDGAME_WATTSON, MOVEMENT_TYPE_FACE_RIGHT
	return

@ The player steps out of the CENTER to (22, 6). STEVEN (22, 7) and WALLACE
@ (23, 7) wait right below.
MauvilleCity_EventScript_SetupCenterScene::
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	setobjectxyperm LOCALID_MAUVILLE_ENDGAME_WATTSON, 21, 8
	setobjectmovementtype LOCALID_MAUVILLE_ENDGAME_WATTSON, MOVEMENT_TYPE_FACE_UP
	setobjectxyperm LOCALID_MAUVILLE_ENDGAME_STEVEN, 22, 7
	setobjectxyperm LOCALID_MAUVILLE_ENDGAME_WALLACE, 23, 7
	setvar VAR_TEMP_1, 2
	return

MauvilleCity_EventScript_ArrivalScene::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MAUVILLE_ENDGAME_WATTSON, MauvilleCity_Movement_WattsonRushesUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAUVILLE_ENDGAME_WATTSON, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox MauvilleCity_Text_ArrivalWattson1, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_ArrivalWattson2, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_ArrivalSteven1, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_ArrivalWattson3, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_ArrivalSteven2, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_ArrivalWallace, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAUVILLE_ENDGAME_STEVEN
	removeobject LOCALID_MAUVILLE_ENDGAME_WALLACE
	fadescreen FADE_FROM_BLACK
	msgbox MauvilleCity_Text_ArrivalLedAway, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_ArrivalWattson4, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_LeadToNewMauville
	end

MauvilleCity_Movement_WattsonRushesUp:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

@ Shared by the first trip and every return after a white-out or a walk back
@ up. The door is always open in the endgame (NewMauville_Entrance).
MauvilleCity_EventScript_LeadToNewMauville::
	closemessage
	fadescreen FADE_TO_BLACK
	msgbox MauvilleCity_Text_LedDown, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEW_MAUVILLE_STATE, 1
	setvar VAR_ENDGAME_STATE, 13
	warp MAP_NEW_MAUVILLE_ENTRANCE, 4, 5
	waitstate
	releaseall
	end

MauvilleCity_EventScript_EndgameWattson::
	lock
	faceplayer
	goto_if_eq VAR_ENDGAME_STATE, 13, MauvilleCity_EventScript_WattsonBackDown
	msgbox MauvilleCity_Text_WattsonStays, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WattsonBackDown::
	msgbox MauvilleCity_Text_WattsonReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_WattsonNotYet
	goto MauvilleCity_EventScript_LeadToNewMauville
	end

MauvilleCity_EventScript_WattsonNotYet::
	msgbox MauvilleCity_Text_WattsonNotYet, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CenterScene::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_CenterWattson1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_ENDGAME_WATTSON, Common_Movement_FaceRight
	waitmovement 0
	msgbox MauvilleCity_Text_CenterWattson2, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CenterSteven, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CenterWallace, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ENDGAME_STATE, 15
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAUVILLE_ENDGAME_STEVEN
	removeobject LOCALID_MAUVILLE_ENDGAME_WALLACE
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox MauvilleCity_Text_CenterWattson3, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_EventScript_EndgameAllies::
	msgbox MauvilleCity_Text_AlliesBusy, MSGBOX_NPC
	end

MauvilleCity_EventScript_EndgameGruntAqua::
	msgbox MauvilleCity_Text_GruntAqua, MSGBOX_NPC
	end

MauvilleCity_EventScript_EndgameGruntMagma::
	msgbox MauvilleCity_Text_GruntMagma, MSGBOX_NPC
	end

MauvilleCity_Text_GruntAqua:
	.string "A new order is here, kid.\p"
	.string "TEAM AQUA and TEAM MAGMA are on the\n"
	.string "same side now. Don't get in the way.$"

MauvilleCity_Text_GruntMagma:
	.string "HOENN has a new leader, and it\n"
	.string "isn't the LEAGUE.\p"
	.string "Move along, and keep your POKéMON\n"
	.string "to yourself.$"

MauvilleCity_Text_AlliesBusy:
	.string "We'll clear the town. Go on.$"

MauvilleCity_Text_ArrivalWattson1:
	.string "WATTSON: Wahah-- no. No laughing\n"
	.string "today.\p"
	.string "MAUVILLE has been taken, STEVEN!\n"
	.string "TEAM AQUA and TEAM MAGMA marched\l"
	.string "in together at dawn.$"

MauvilleCity_Text_ArrivalWattson2:
	.string "WATTSON: They say a new order is\n"
	.string "here. That HOENN has a new leader,\l"
	.string "a man called SCOTT.\p"
	.string "AQUA and MAGMA, working side by\n"
	.string "side! I never thought I'd see it.$"

MauvilleCity_Text_ArrivalSteven1:
	.string "STEVEN: They aren't here for the\n"
	.string "town. They're guarding something.\p"
	.string "WATTSON, what lies under MAUVILLE?$"

MauvilleCity_Text_ArrivalWattson3:
	.string "WATTSON: NEW MAUVILLE. My old\n"
	.string "generator, beneath ROUTE 110.\p"
	.string "It's been dead for years, but a\n"
	.string "generator that size can be woken.$"

MauvilleCity_Text_ArrivalSteven2:
	.string "STEVEN: A backup power source for\n"
	.string "SCOTT's CROWN, in case the FACTORY\l"
	.string "ever runs dry.\p"
	.string "That's what the teams are here to\n"
	.string "protect.$"

MauvilleCity_Text_ArrivalWallace:
	.string "WALLACE: Then that's where you\n"
	.string "strike, {PLAYER}.\p"
	.string "STEVEN and I will clear the town.\n"
	.string "Quietly, and with great style.\p"
	.string "WATTSON will see you through.$"

MauvilleCity_Text_ArrivalLedAway:
	.string "STEVEN and WALLACE drew the\n"
	.string "grunts away from the streets.$"

MauvilleCity_Text_ArrivalWattson4:
	.string "WATTSON: I know the way down to the\n"
	.string "generator. Follow me!\p"
	.string "Down to the water, and across to\n"
	.string "NEW MAUVILLE!$"

MauvilleCity_Text_LedDown:
	.string "WATTSON led {PLAYER} down to the\n"
	.string "water and across to NEW MAUVILLE.$"

MauvilleCity_Text_WattsonReady:
	.string "WATTSON: The generator's waiting.\n"
	.string "Shall I lead you back down?$"

MauvilleCity_Text_WattsonNotYet:
	.string "WATTSON: Take your time. I'll be\n"
	.string "right here.$"

MauvilleCity_Text_WattsonStays:
	.string "WATTSON: I'll stay and get MAUVILLE\n"
	.string "back on its feet.\p"
	.string "If SCOTT is still out there, I'll\n"
	.string "be ready when you call.$"

MauvilleCity_Text_CenterWattson1:
	.string "WATTSON: You're back! And the\n"
	.string "grunts cleared out the moment the\l"
	.string "generator went quiet.$"

MauvilleCity_Text_CenterWattson2:
	.string "WATTSON: Wahahahah! The lights of\n"
	.string "MAUVILLE are on again.\p"
	.string "Thank you, {PLAYER}. This town is in\n"
	.string "your debt.$"

MauvilleCity_Text_CenterSteven:
	.string "STEVEN: Well done. The CROWN holds\n"
	.string "all the power it can now: six\l"
	.string "permanent MEGAS.\p"
	.string "And HOOPA's third ring should be\n"
	.string "ready.$"

MauvilleCity_Text_CenterWallace:
	.string "WALLACE: Take the ABRA home to the\n"
	.string "FRONTIER, {PLAYER}.\p"
	.string "STEVEN and I will fly ahead. We'll\n"
	.string "meet you there.$"

MauvilleCity_Text_CenterWattson3:
	.string "WATTSON: STEVEN and WALLACE are\n"
	.string "off. I'll stay and mind the town.\p"
	.string "Go on, {PLAYER}. The ABRA's by the\n"
	.string "POKéMON CENTER.$"

@ ============================================================================
@ Ten Gauntlets: CALYREX, "The True King" (sprint-b-calyrex.md).
@ VAR_CALYREX_EVENT: 0 nothing, 1 the old man's legend heard, 2 the statue
@ restored, 3 CALYREX has asked for a steed, 4 caught. Gated on the GYM
@ rematch (TRAINER_ENDGAME_WATTSON). FLAG_TEMP_6 rubble, 7 statue, 8 CALYREX.
@ ============================================================================

MauvilleCity_EventScript_SetupCalyrex::
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	goto_if_lt VAR_ENDGAME_STATE, 15, Common_EventScript_NopReturn
	goto_if_ge VAR_CALYREX_EVENT, 2, MauvilleCity_EventScript_ShowRestoredStatue
	clearflag FLAG_TEMP_6
	return

MauvilleCity_EventScript_ShowRestoredStatue::
	clearflag FLAG_TEMP_7
	call_if_lt VAR_CALYREX_EVENT, 4, MauvilleCity_EventScript_ShowCalyrex
	return

MauvilleCity_EventScript_ShowCalyrex::
	clearflag FLAG_TEMP_8
	return

@ The rubble. Not beaten WATTSON: nothing. Beaten: a hint, and once the legend
@ is heard (state 1) the restoration.
MauvilleCity_EventScript_StatueRubble::
	lockall
	goto_if_not_defeated TRAINER_ENDGAME_WATTSON, MauvilleCity_EventScript_RubbleBare
	goto_if_eq VAR_CALYREX_EVENT, 1, MauvilleCity_EventScript_RestoreStatue
	msgbox MauvilleCity_Text_RubbleCracked, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_EventScript_RubbleBare::
	msgbox MauvilleCity_Text_RubbleBare, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_EventScript_RestoreStatue::
	msgbox MauvilleCity_Text_RestorePrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_RestoreLater
	msgbox MauvilleCity_Text_StatueMends, MSGBOX_DEFAULT
	closemessage
	playse SE_M_TELEPORT
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_MAUVILLE_STATUE_RUBBLE
	addobject LOCALID_MAUVILLE_STATUE
	setflag FLAG_MAUVILLE_STATUE_RESTORED
	setvar VAR_CALYREX_EVENT, 2
	fadescreen FADE_FROM_WHITE
	delay 30
	msgbox MauvilleCity_Text_WindRises, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	addobject LOCALID_MAUVILLE_CALYREX
	fadescreen FADE_FROM_WHITE
	applymovement LOCALID_MAUVILLE_CALYREX, Common_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_CALYREX, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox MauvilleCity_Text_CalyrexAppears, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_CalyrexSpeaks
	end

MauvilleCity_EventScript_RestoreLater::
	msgbox MauvilleCity_Text_RestoreLater, MSGBOX_DEFAULT
	releaseall
	end

@ The restored statue, in every state from 2 on.
MauvilleCity_EventScript_StatueWhole::
	lockall
	msgbox MauvilleCity_Text_StatueWhole, MSGBOX_DEFAULT
	releaseall
	end

@ CALYREX. State 2: its first words (a reset mid-scene lands here). State 3:
@ the steed check.
MauvilleCity_EventScript_Calyrex::
	lock
	faceplayer
	goto_if_eq VAR_CALYREX_EVENT, 2, MauvilleCity_EventScript_CalyrexSpeaks
	goto MauvilleCity_EventScript_CalyrexSteedCheck
	end

MauvilleCity_EventScript_CalyrexSpeaks::
	msgbox MauvilleCity_Text_CalyrexVoice, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexCrown1, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexCrown2, MSGBOX_DEFAULT
	setvar VAR_CALYREX_EVENT, 3
	msgbox MauvilleCity_Text_CalyrexSteed, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_CalyrexSteedCheck
	end

MauvilleCity_EventScript_CalyrexSteedCheck::
	checkspecies SPECIES_GLASTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_EventScript_CalyrexHasSteed
	checkspecies SPECIES_SPECTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_EventScript_CalyrexHasSteed
	msgbox MauvilleCity_Text_CalyrexNoSteed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexHasSteed::
	msgbox MauvilleCity_Text_CalyrexSees, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_CalyrexWaits
	@ Checked before the fight, so the REINS always fit.
	checkitemspace ITEM_REINS_OF_UNITY
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_EventScript_CalyrexBagFull
	closemessage
	playmoncry SPECIES_CALYREX, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CALYREX, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MauvilleCity_EventScript_CalyrexCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MauvilleCity_EventScript_CalyrexStands
	msgbox MauvilleCity_Text_CalyrexRan, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexWaits::
	msgbox MauvilleCity_Text_CalyrexWaits, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexBagFull::
	msgbox MauvilleCity_Text_CalyrexBagFull, MSGBOX_DEFAULT
	release
	end

@ Knocked out: it stays, at full strength next time. Same for a run.
MauvilleCity_EventScript_CalyrexStands::
	msgbox MauvilleCity_Text_CalyrexStands, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexCaught::
	setflag FLAG_CALYREX_CAUGHT
	setvar VAR_CALYREX_EVENT, 4
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_MAUVILLE_CALYREX
	fadescreen FADE_FROM_WHITE
	msgbox MauvilleCity_Text_CalyrexCaught, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexThanks, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexReins, MSGBOX_DEFAULT
	giveitem ITEM_REINS_OF_UNITY
	msgbox MauvilleCity_Text_CalyrexReinsHow, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_StatueBlooms, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Text_RubbleBare:
	.string "A heap of broken stone lies in the\n"
	.string "grass, scorched and trampled.$"

MauvilleCity_Text_RubbleCracked:
	.string "A statue lies in pieces in the grass.\n"
	.string "Its crown is cracked clean through.\p"
	.string "Whoever he was, he was somebody\n"
	.string "once. Someone in town might\l"
	.string "remember.$"

MauvilleCity_Text_RestorePrompt:
	.string "The broken crown has a clean seam,\n"
	.string "as if it were waiting for a mate.\p"
	.string "Hold the REPLICA CROWN to the break?$"

MauvilleCity_Text_RestoreLater:
	.string "{PLAYER} lowered the CROWN. The\n"
	.string "stone lay still.$"

MauvilleCity_Text_StatueMends:
	.string "{PLAYER} held the REPLICA CROWN to\n"
	.string "the break in the stone.\p"
	.string "Its light ran into the crack like\n"
	.string "rain into a dry field.\p"
	.string "The pieces ground together. The\n"
	.string "crown closed, and the statue stood\l"
	.string "whole.$"

MauvilleCity_Text_WindRises:
	.string "A warm wind crossed the lawn,\n"
	.string "though the air had been still.$"

MauvilleCity_Text_CalyrexAppears:
	.string "At the statue's side, where there\n"
	.string "had been nothing, a small king\l"
	.string "stood. CALYREX.$"

MauvilleCity_Text_CalyrexVoice:
	.string "A voice settled into {PLAYER}'s\n"
	.string "mind, soft and old. It had no\l"
	.string "mouth to speak it.\p"
	.string "“I felt my likeness mend. Someone\n"
	.string "remembered me, after so many\l"
	.string "seasons.”$"

MauvilleCity_Text_CalyrexCrown1:
	.string "“You carry a crown.”\p"
	.string "“No. Look closer, and it is not.”\p"
	.string "“That is no crown. It is a chain.”$"

MauvilleCity_Text_CalyrexCrown2:
	.string "“Thousands of bonds are wound into\n"
	.string "it. None were given. All were\l"
	.string "taken.\p"
	.string "“It lent its light to mend my\n"
	.string "stone, and for that I thank you.\p"
	.string "“But a crown is a weight carried\n"
	.string "for others. A chain only binds.”$"

MauvilleCity_Text_CalyrexSteed:
	.string "“I am faint. The harvest forgot me,\n"
	.string "and I forgot how to rise.\p"
	.string "“A king does not walk alone. Show\n"
	.string "me the steed you trust: the white\l"
	.string "steed of frost, or the dark steed\l"
	.string "of shade.”$"

MauvilleCity_Text_CalyrexNoSteed:
	.string "“You have no steed with you.\n"
	.string "Without one, I cannot rise, and\l"
	.string "you cannot be measured.\p"
	.string "“The old teller of tales, in the\n"
	.string "house of healing, remembers where\l"
	.string "such steeds are kept.”$"

MauvilleCity_Text_CalyrexSees:
	.string "“A steed walks with you. I know\n"
	.string "that stride.\p"
	.string "“Then let me see how you ride, and\n"
	.string "what you do with a chain in your\l"
	.string "hand.”$"

MauvilleCity_Text_CalyrexReady:
	.string "“Are you ready to be measured?”$"

MauvilleCity_Text_CalyrexWaits:
	.string "“Then ready yourself, {PLAYER}.\n"
	.string "I am in no hurry.”$"

MauvilleCity_Text_CalyrexBagFull:
	.string "CALYREX waits, but {PLAYER}'s BAG is\n"
	.string "full.\p"
	.string "Whatever the king gives will need\n"
	.string "room. Make some first.$"

MauvilleCity_Text_CalyrexStands:
	.string "CALYREX swayed, then rose again as\n"
	.string "if the grass itself held it up.\p"
	.string "“Not yet, {PLAYER}. Come back when\n"
	.string "you are ready.”$"

MauvilleCity_Text_CalyrexRan:
	.string "“You turn from the trial. I will\n"
	.string "wait. Kings are good at it.”$"

MauvilleCity_Text_CalyrexCaught:
	.string "The ball closed on CALYREX without\n"
	.string "a struggle, calm and unhurried.\p"
	.string "It had not been bound. It had\n"
	.string "chosen.$"

MauvilleCity_Text_CalyrexThanks:
	.string "“I will ride with you, {PLAYER}.\p"
	.string "“I judged the chain. I should have\n"
	.string "judged the hand that held it.\p"
	.string "“You stood the trial, and you\n"
	.string "never asked me to bow.”$"

MauvilleCity_Text_CalyrexReins:
	.string "“Take the REINS. They bind a king\n"
	.string "to his steed in trust, not in\l"
	.string "chains.”$"

MauvilleCity_Text_CalyrexReinsHow:
	.string "“Use them on me and my steed, and\n"
	.string "we are one. Use them again, and we\l"
	.string "part.”$"

MauvilleCity_Text_StatueBlooms:
	.string "The stone king stood whole on the\n"
	.string "lawn. Around its feet, wildflowers\l"
	.string "had opened in the bare grass.$"

MauvilleCity_Text_StatueWhole:
	.string "A stone king stands on the lawn,\n"
	.string "his crown whole. Wildflowers have\l"
	.string "opened around the base.$"
