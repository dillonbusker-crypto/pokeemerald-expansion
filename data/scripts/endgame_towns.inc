@ ============================================================================
@ Ten Gauntlets: the towns of the endgame (storyline.md) - RUSTBORO, MAUVILLE
@ and SKY PILLAR. The player only ever reaches them by ABRA, and they're cut
@ off from the rest of Hoenn: the exits turn the player back, the GYMS are
@ locked (GetEndgameSealedDoorScript, src/facility.c), and the vanilla story
@ events there are switched off in each map's own scripts.
@ ============================================================================

@ An ABRA of the network. The map's ABRA sets VAR_0x8004 to where it is
@ (ABRA_AT_*), and the menu lists every other place it can go: the FRONTIER
@ always, the rest once their FLAG_ABRA_TO_* is set by the story.
EventScript_EndgameAbra::
	lock
	faceplayer
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox EventScript_EndgameAbra_Text_WhereTo, MSGBOX_DEFAULT
	waitmoncry
	call_if_ne VAR_0x8004, ABRA_AT_FRONTIER, EventScript_EndgameAbra_PushFrontier
	goto_if_unset FLAG_ABRA_TO_RUSTBORO, EventScript_EndgameAbra_SkipRustboro
	call_if_ne VAR_0x8004, ABRA_AT_RUSTBORO, EventScript_EndgameAbra_PushRustboro
EventScript_EndgameAbra_SkipRustboro:
	goto_if_unset FLAG_ABRA_TO_MAUVILLE, EventScript_EndgameAbra_SkipMauville
	call_if_ne VAR_0x8004, ABRA_AT_MAUVILLE, EventScript_EndgameAbra_PushMauville
EventScript_EndgameAbra_SkipMauville:
	goto_if_unset FLAG_ABRA_TO_SKY_PILLAR, EventScript_EndgameAbra_SkipSkyPillar
	call_if_ne VAR_0x8004, ABRA_AT_SKY_PILLAR, EventScript_EndgameAbra_PushSkyPillar
EventScript_EndgameAbra_SkipSkyPillar:
	dynmultipush EventScript_EndgameAbra_Text_Cancel, ABRA_CANCEL
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case ABRA_AT_FRONTIER, EventScript_EndgameAbra_GoFrontier
	case ABRA_AT_RUSTBORO, EventScript_EndgameAbra_GoRustboro
	case ABRA_AT_MAUVILLE, EventScript_EndgameAbra_GoMauville
	case ABRA_AT_SKY_PILLAR, EventScript_EndgameAbra_GoSkyPillar
	release
	end

EventScript_EndgameAbra_PushFrontier::
	dynmultipush EventScript_EndgameAbra_Text_Frontier, ABRA_AT_FRONTIER
	return

EventScript_EndgameAbra_PushRustboro::
	dynmultipush EventScript_EndgameAbra_Text_Rustboro, ABRA_AT_RUSTBORO
	return

EventScript_EndgameAbra_PushMauville::
	dynmultipush EventScript_EndgameAbra_Text_Mauville, ABRA_AT_MAUVILLE
	return

EventScript_EndgameAbra_PushSkyPillar::
	dynmultipush EventScript_EndgameAbra_Text_SkyPillar, ABRA_AT_SKY_PILLAR
	return

EventScript_EndgameAbra_Teleport::
	msgbox EventScript_EndgameAbra_Text_UsedTeleport, MSGBOX_DEFAULT
	closemessage
	playse SE_M_TELEPORT
	return

@ Arrivals: in front of the Devon Factory, and beside each town's ABRA.
EventScript_EndgameAbra_GoFrontier::
	call EventScript_EndgameAbra_Teleport
	warpteleport MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 15, 39
	waitstate
	release
	end

EventScript_EndgameAbra_GoRustboro::
	call EventScript_EndgameAbra_Teleport
	warpteleport MAP_RUSTBORO_CITY, 16, 39
	waitstate
	release
	end

EventScript_EndgameAbra_GoMauville::
	call EventScript_EndgameAbra_Teleport
	warpteleport MAP_MAUVILLE_CITY, 22, 6
	waitstate
	release
	end

EventScript_EndgameAbra_GoSkyPillar::
	call EventScript_EndgameAbra_Teleport
	warpteleport MAP_SKY_PILLAR_OUTSIDE, 13, 9
	waitstate
	release
	end

@ On every way out of an endgame town: a word, then a step back the way the
@ player came.
EventScript_EndgameSealedExit::
	lockall
	specialvar VAR_RESULT, GetPlayerFacingDirection
	msgbox EventScript_EndgameSealedExit_Text, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_RESULT, DIR_NORTH, EventScript_EndgameSealedExit_StepDown
	call_if_eq VAR_RESULT, DIR_SOUTH, EventScript_EndgameSealedExit_StepUp
	call_if_eq VAR_RESULT, DIR_WEST, EventScript_EndgameSealedExit_StepRight
	call_if_eq VAR_RESULT, DIR_EAST, EventScript_EndgameSealedExit_StepLeft
	waitmovement 0
	releaseall
	end

EventScript_EndgameSealedExit_StepDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	return

EventScript_EndgameSealedExit_StepUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	return

EventScript_EndgameSealedExit_StepRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	return

EventScript_EndgameSealedExit_StepLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	return

@ Locked doors (GetEndgameSealedDoorScript): the player bumps the GYM door.
EventScript_EndgameSealedGym::
	msgbox EventScript_EndgameSealedGym_Text, MSGBOX_SIGN
	end

EventScript_EndgameAbra_Text_WhereTo:
	.string "It's WALLACE's ABRA.\n"
	.string "Where should it TELEPORT you?$"

EventScript_EndgameAbra_Text_Frontier:
	.string "BATTLE FRONTIER$"

EventScript_EndgameAbra_Text_Rustboro:
	.string "RUSTBORO CITY$"

EventScript_EndgameAbra_Text_Mauville:
	.string "MAUVILLE CITY$"

EventScript_EndgameAbra_Text_SkyPillar:
	.string "SKY PILLAR$"

EventScript_EndgameAbra_Text_Cancel:
	.string "CANCEL$"

EventScript_EndgameAbra_Text_UsedTeleport:
	.string "ABRA used TELEPORT!$"

EventScript_EndgameSealedExit_Text:
	.string "Now isn't the time to wander off.\p"
	.string "{PLAYER} needs to stay focused on\n"
	.string "the task at hand.$"

EventScript_EndgameSealedGym_Text:
	.string "The GYM's doors are locked.\p"
	.string "A notice reads: “Closed until\n"
	.string "further notice.”$"
