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

@ Ten Gauntlets: permanent roadblock. This is a battle-only hack with no
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

@ Ten Gauntlets: OLDALE's townsfolk pass on the LITTLEROOT gossip from the
@ Birch arc (storyline.md; VAR_BIRCH_STORY_STATE 1-2 while DEVON is at the
@ lab, 3 on after). LITTLEROOT's own wanderers stay indoors through it.
OldaleTown_EventScript_Girl::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_ARREST, OldaleTown_Girl_Gossip0
	case GOSSIP_PALACE, OldaleTown_Girl_Gossip0
	case GOSSIP_RAID, OldaleTown_Girl_Gossip1
	case GOSSIP_TAKEN, OldaleTown_Girl_Gossip2
	case GOSSIP_STANDOFF, OldaleTown_Girl_Gossip2
	case GOSSIP_ALL_CLEAR, OldaleTown_Girl_Gossip2
	goto_if_ge VAR_BIRCH_STORY_STATE, 3, OldaleTown_EventScript_GirlAfterLab
	goto_if_ge VAR_BIRCH_STORY_STATE, 1, OldaleTown_EventScript_GirlDuringLab
	msgbox OldaleTown_Text_SavingMyProgress, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
OldaleTown_Girl_Gossip0::
	msgbox OldaleTown_Girl_Text_Gossip0, MSGBOX_NPC
	end

OldaleTown_Girl_Gossip1::
	msgbox OldaleTown_Girl_Text_Gossip1, MSGBOX_NPC
	end

OldaleTown_Girl_Gossip2::
	msgbox OldaleTown_Girl_Text_Gossip2, MSGBOX_NPC
	end

OldaleTown_Girl_Text_Gossip0:
	.string "The radio says the ELITE FOUR left\n"
	.string "the POKéMON LEAGUE, and nobody knows\l"
	.string "where they went!\p"
	.string "Mommy says not to worry. She's had the\n"
	.string "radio on all day.$"

OldaleTown_Girl_Text_Gossip1:
	.string "Big men in suits ran through OLDALE\n"
	.string "this morning, carrying boxes and\l"
	.string "boxes!\p"
	.string "My friend in LITTLEROOT says they\n"
	.string "came from the LAB again.$"

OldaleTown_Girl_Text_Gossip2:
	.string "My friend in LITTLEROOT says your\n"
	.string "house is all dark now.\p"
	.string "Where did your mom and dad go?$"

OldaleTown_EventScript_GirlDuringLab::
	msgbox OldaleTown_Text_GirlDuringLab, MSGBOX_NPC
	end

OldaleTown_EventScript_GirlAfterLab::
	msgbox OldaleTown_Text_GirlAfterLab, MSGBOX_NPC
	end

OldaleTown_EventScript_MartEmployee::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_RAID, OldaleTown_MartEmployee_Gossip0
	case GOSSIP_TAKEN, OldaleTown_MartEmployee_Gossip1
	case GOSSIP_STANDOFF, OldaleTown_MartEmployee_Gossip1
	case GOSSIP_ALL_CLEAR, OldaleTown_MartEmployee_Gossip1
	goto_if_ge VAR_BIRCH_STORY_STATE, 3, OldaleTown_EventScript_MartEmployeeAfterLab
	goto_if_ge VAR_BIRCH_STORY_STATE, 1, OldaleTown_EventScript_MartEmployeeDuringLab
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

@ Story gossip: the line for the current beat (GetStoryGossipStage).
OldaleTown_MartEmployee_Gossip0::
	msgbox OldaleTown_MartEmployee_Text_Gossip0, MSGBOX_DEFAULT
	release
	end

OldaleTown_MartEmployee_Gossip1::
	msgbox OldaleTown_MartEmployee_Text_Gossip1, MSGBOX_DEFAULT
	release
	end

OldaleTown_MartEmployee_Text_Gossip0:
	.string "Those men in suits came back to PROF.\n"
	.string "BIRCH's LAB, and this time they\l"
	.string "brought a truck.\p"
	.string "Our delivery boy says they carried out\n"
	.string "every machine in the place.$"

OldaleTown_MartEmployee_Text_Gossip1:
	.string "PROF. BIRCH's LAB is empty. Our\n"
	.string "delivery boy says the PROFESSOR just\l"
	.string "sits in there.\p"
	.string "We've been sending sandwiches over.$"

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

OldaleTown_EventScript_MartEmployeeDuringLab::
	msgbox OldaleTown_Text_MartEmployeeDuringLab, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_MartEmployeeAfterLab::
	msgbox OldaleTown_Text_MartEmployeeAfterLab, MSGBOX_DEFAULT
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
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_ARREST, OldaleTown_FootprintsMan_Gossip0
	case GOSSIP_PALACE, OldaleTown_FootprintsMan_Gossip0
	goto_if_ge VAR_BIRCH_STORY_STATE, 3, OldaleTown_EventScript_FootprintsManAfterLab
	goto_if_ge VAR_BIRCH_STORY_STATE, 1, OldaleTown_EventScript_FootprintsManDuringLab
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_NotBlockingPath
	msgbox OldaleTown_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
OldaleTown_FootprintsMan_Gossip0::
	msgbox OldaleTown_FootprintsMan_Text_Gossip0, MSGBOX_DEFAULT
	release
	end

OldaleTown_FootprintsMan_Text_Gossip0:
	.string "WALLACE flew over again! Right over\n"
	.string "OLDALE, headed north, fast.\p"
	.string "And now the radio says the ELITE FOUR\n"
	.string "are missing. A CHAMPION's footprints\l"
	.string "are never boring.$"

OldaleTown_EventScript_FootprintsManDuringLab::
	msgbox OldaleTown_Text_FootprintsManDuringLab, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_FootprintsManAfterLab::
	msgbox OldaleTown_Text_FootprintsManAfterLab, MSGBOX_DEFAULT
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
	.string "Honestly, nobody buys POTIONS\n"
	.string "anymore. Not since those DEVON\l"
	.string "POKéNAVs started healing POKéMON\l"
	.string "after every battle.\p"
	.string "Here, have one on the house.$"

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

OldaleTown_Text_GirlDuringLab:
	.string "There are men in suits at PROF.\n"
	.string "BIRCH's LAB, down in LITTLEROOT!\p"
	.string "Mommy says I'm not allowed to go\n"
	.string "anywhere near there.$"

OldaleTown_Text_GirlAfterLab:
	.string "My friend in LITTLEROOT saw a man\n"
	.string "in a really fancy suit come out of\l"
	.string "the LAB, with two big men behind\l"
	.string "him.\p"
	.string "Then they all just left. Like it\n"
	.string "was nothing!$"

OldaleTown_Text_MartEmployeeDuringLab:
	.string "There's a fellow in a suit standing\n"
	.string "guard at PROF. BIRCH's LAB. He\l"
	.string "wouldn't even let our delivery boy\l"
	.string "through.\p"
	.string "DEVON, I heard. What would a\n"
	.string "company like that want with the\l"
	.string "PROFESSOR?$"

OldaleTown_Text_MartEmployeeAfterLab:
	.string "PROF. BIRCH says it was all a\n"
	.string "misunderstanding, and everything's\l"
	.string "sorted.\p"
	.string "...He didn't look sorted to our\n"
	.string "delivery boy.$"

OldaleTown_Text_FootprintsManDuringLab:
	.string "Somebody said the CHAMPION went\n"
	.string "down to LITTLEROOT! WALLACE!\p"
	.string "Now those are footprints I'd like\n"
	.string "to study.$"

OldaleTown_Text_FootprintsManAfterLab:
	.string "I saw WALLACE fly right over\n"
	.string "OLDALE! Right over the houses!\p"
	.string "Nobody believes me.$"
