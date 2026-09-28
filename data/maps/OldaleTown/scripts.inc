OldaleTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_OnTransition
	.byte 0

OldaleTown_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_OLDALE_TOWN
	call_if_unset FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_BlockWestEntrance
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployee
	call_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_SetOldaleState
	end

@ This script seems pointless because nothing uses VAR_OLDALE_TOWN_STATE
OldaleTown_EventScript_SetOldaleState::
	setvar VAR_OLDALE_TOWN_STATE, 1
	return

OldaleTown_EventScript_BlockWestEntrance::
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 1, 11
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_FACE_LEFT
	return

OldaleTown_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_OLDALE_MART_EMPLOYEE, 13, 14
	setobjectmovementtype LOCALID_OLDALE_MART_EMPLOYEE, MOVEMENT_TYPE_FACE_DOWN
	return

@ Ten Buildings: permanent roadblock. This is a battle-only hack with no
@ story - Route 102 onward (the rest of the vanilla region) is never meant
@ to be reachable. Two HIKERs cover both tiles of the path west (see
@ OldaleTown_EventScript_BlockWestEntrance above for vanilla's OWN
@ temporary version of this same block, which lifts once
@ FLAG_ADVENTURE_STARTED is set - these don't depend on that flag and
@ never lift.
@
@ This was originally OBJ_EVENT_GFX_SNORLAX, matching the classic "sleeping
@ Snorlax blocks the road" gag, but that graphic's info pointer is compiled
@ out for Emerald builds (see the #if IS_FRLG block in
@ src/data/object_events/object_event_graphics_info_pointers.h) - it rendered
@ invisible even though its collision still worked. HIKER is a normal,
@ always-available Emerald graphic that reads fine as "the trail's closed".
OldaleTown_EventScript_Route102Roadblock::
	msgbox OldaleTown_Text_TrailClosed, MSGBOX_NPC
	end

OldaleTown_EventScript_TownSign::
	msgbox OldaleTown_Text_TownSign, MSGBOX_SIGN
	end

OldaleTown_EventScript_Girl::
	msgbox OldaleTown_Text_SavingMyProgress, MSGBOX_NPC
	end

OldaleTown_EventScript_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_ExplainPotion
	goto_if_set FLAG_TEMP_1, OldaleTown_EventScript_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, OldaleTown_EventScript_GoToMartSouth
	case DIR_NORTH, OldaleTown_EventScript_GoToMartNorth
	case DIR_EAST, OldaleTown_EventScript_GoToMartEast
	end

OldaleTown_EventScript_GoToMartSouth::
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, OldaleTown_Movement_EmployeeSouth
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerSouth
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_GoToMartNorth::
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, OldaleTown_Movement_EmployeeNorth
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerNorth
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_GoToMartEast::
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerEast
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, OldaleTown_Movement_EmployeeEast
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_ExplainPokemonMart::
	msgbox OldaleTown_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, OldaleTown_EventScript_BagIsFull
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_POTION_OLDALE
	fadedefaultbgm
	release
	end

OldaleTown_EventScript_ExplainPotion::
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

OldaleTown_Movement_EmployeeEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_EmployeeSouth:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_EmployeeNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_Unknown1:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_PlayerEast:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_PlayerSouth:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_PlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_Unknown2:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_EventScript_FootprintsMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_NotBlockingPath
	msgbox OldaleTown_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

OldaleTown_EventScript_BlockedPath::
	lockall
	applymovement LOCALID_PLAYER, OldaleTown_Movement_PlayerStepBack
	applymovement LOCALID_FOOTPRINTS_MAN, OldaleTown_Movement_BackUp
	waitmovement 0
	msgbox OldaleTown_Text_WaitDontComeInHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, OldaleTown_Movement_ReturnToOriginalPosition
	waitmovement 0
	releaseall
	end

OldaleTown_EventScript_NotBlockingPath::
	msgbox OldaleTown_Text_FinishedSketchingFootprints, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_Rival::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger1::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger2::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger3::
	lockall
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_ShowRivalMessage::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, OldaleTown_EventScript_ShowMayMessage
	goto_if_eq VAR_RESULT, FEMALE, OldaleTown_EventScript_ShowBrendanMessage
	end

OldaleTown_EventScript_ShowMayMessage::
	msgbox OldaleTown_Text_MayLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_ShowBrendanMessage::
	msgbox OldaleTown_Text_BrendanLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_RivalFinish::
	closemessage
	call_if_eq VAR_0x8009, 0, OldaleTown_EventScript_DoExitMovement1
	call_if_eq VAR_0x8009, 1, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_OLDALE_RIVAL
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	releaseall
	end

OldaleTown_EventScript_DoExitMovement1::
	goto_if_ne VAR_FACING, DIR_SOUTH, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_EventScript_DoExitMovement2::
	applymovement LOCALID_PLAYER, OldaleTown_Movement_WatchRivalExit
	applymovement LOCALID_OLDALE_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer2:
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer3:
	face_left
	step_end

OldaleTown_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_PlayerStepBack:
	delay_8
	walk_right
	step_end

OldaleTown_Movement_BackUp:
	walk_fast_up
	walk_in_place_faster_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

OldaleTown_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

OldaleTown_Text_SavingMyProgress:
	.string "I want to take a rest, so I'm saving my\n"
	.string "progress.$"

OldaleTown_Text_TrailClosed:
	.string "HIKER: Whoa there!\p"
	.string "This trail's closed - rockslide up\n"
	.string "ahead. Not getting through this way\l"
	.string "anytime soon.$"

OldaleTown_Text_IWorkAtPokemonMart:
	.string "Hi!\n"
	.string "I work at a POKéMON MART.\p"
	.string "Can I get you to come with me?$"

OldaleTown_Text_ThisIsAPokemonMart:
	.string "This is a POKéMON MART.\n"
	.string "Just look for our blue roof.\p"
	.string "We sell a variety of goods including\n"
	.string "POKé BALLS for catching POKéMON.\p"
	.string "Here, I'd like you to have this as\n"
	.string "a promotional item.$"

OldaleTown_Text_PotionExplanation:
	.string "A POTION can be used anytime, so it's\n"
	.string "even more useful than a POKéMON CENTER\l"
	.string "in certain situations.$"

OldaleTown_Text_WaitDontComeInHere:
	.string "Aaaaah! Wait!\n"
	.string "Please don't come in here.\p"
	.string "I just discovered the footprints of\n"
	.string "a rare POKéMON!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

OldaleTown_Text_DiscoveredFootprints:
	.string "I just discovered the footprints of\n"
	.string "a rare POKéMON!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

OldaleTown_Text_FinishedSketchingFootprints:
	.string "I finished sketching the footprints of\n"
	.string "a rare POKéMON.\p"
	.string "But it turns out they were only my\n"
	.string "own footprints…$"

OldaleTown_Text_MayLetsGoBack:
	.string "MAY: {PLAYER}{KUN}!\n"
	.string "Over here!\l"
	.string "Let's hurry home!$"

OldaleTown_Text_BrendanLetsGoBack:
	.string "BRENDAN: I'm heading back to my dad's\n"
	.string "LAB now.\l"
	.string "{PLAYER}, you should hustle back, too.$"

OldaleTown_Text_TownSign:
	.string "OLDALE TOWN\n"
	.string "“Where things start off scarce.”$"

