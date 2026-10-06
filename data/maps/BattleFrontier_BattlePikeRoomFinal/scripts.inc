BattleFrontier_BattlePikeRoomFinal_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePikeRoomFinal_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeRoomFinal_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeRoomFinal_OnWarp
	.byte 0

BattleFrontier_BattlePikeRoomFinal_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePikeRoomFinal_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattlePikeRoomFinal_EventScript_EnterRoom::
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoomFinal_EventScript_BadDreamsEnter
	delay 16
	applymovement LOCALID_PIKE_FINAL_ROOM_ATTENDANT, BattleFrontier_BattlePikeRoomFinal_Movement_AttendantApproachPlayer
	waitmovement 0
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	lockall
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_CongratsThisWayPlease, MSGBOX_DEFAULT
	closemessage
	releaseall
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 5, 6
	waitstate
	end

BattleFrontier_BattlePikeRoomFinal_Movement_AttendantApproachPlayer:
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomFinal_OnWarp:
	map_script_2 VAR_TEMP_4, 0, BattleFrontier_BattlePikeRoomFinal_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePikeRoomFinal_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_4, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeRoomFinal_Text_CongratsThisWayPlease:
	.string "Congratulations…\n"
	.string "Now, this way, please…$"


@ ============================================================================
@ Ten Gauntlets: Bad Dreams (storyline.md, "During gauntlet 7"). This is
@ DARKRAI's lair: the Pike lobby's attendant lets the player in while
@ IsBadDreamsActive() and they carry the LUNAR WING. Nothing else reaches
@ this room (the Pike's own rooms went unused when gauntlet 6 moved to the
@ lobby attendant), so the vanilla flow above runs only outside the window.
@ The room is lit by a small flash radius. DARKRAI is the object at (2, 4)
@ (VAR_OBJ_GFX_ID_0, hidden by FLAG_DARKRAI_FREED); the way out is the bottom
@ row.
@ ============================================================================

BattleFrontier_BattlePikeRoomFinal_OnTransition:
	clearflag FLAG_BATTLE_NO_CATCHING
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoomFinal_EventScript_SetUpLair
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_LINK_RECEPTIONIST, warn=FALSE
	end

BattleFrontier_BattlePikeRoomFinal_EventScript_SetUpLair::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(DARKRAI), warn=FALSE
	setflashlevel 2
	end

BattleFrontier_BattlePikeRoomFinal_EventScript_BadDreamsEnter::
	setvar VAR_TEMP_0, 1
	lockall
	delay 16
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_Enter, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ The bottom row leads back to the lobby. Asks first, so a step back isn't a
@ surprise; works whether or not DARKRAI is still here.
BattleFrontier_BattlePikeRoomFinal_EventScript_BadDreamsExit::
	lockall
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_LeaveAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, BattleFrontier_BattlePikeRoomFinal_EventScript_Leave
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomFinal_Movement_StepBack
	waitmovement 0
	releaseall
	end

BattleFrontier_BattlePikeRoomFinal_EventScript_Leave::
	playse SE_PIKE_CURTAIN_OPEN
	waitse
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 5, 6
	waitstate
	end

BattleFrontier_BattlePikeRoomFinal_Movement_StepBack:
	walk_up
	step_end

BattleFrontier_BattlePikeRoomFinal_EventScript_Darkrai::
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattlePikeRoomFinal_EventScript_NotDarkrai
	lock
	faceplayer
	checkitemspace ITEM_DARKRANITE
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattlePikeRoomFinal_EventScript_BagFull
	goto_if_eq VAR_TEMP_1, 1, BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiAgain
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_Collar, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 1
	goto BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiBattle

BattleFrontier_BattlePikeRoomFinal_EventScript_NotDarkrai::
	end

@ Checked before the fight, so there is always room for the DARKRANITE.
BattleFrontier_BattlePikeRoomFinal_EventScript_BagFull::
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_BagFull, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiAgain::
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_Again, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiBattle

BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiBattle::
	closemessage
	playmoncry SPECIES_DARKRAI, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_DARKRAI, 60
	special SetBadDreamsDarkraiMoves
	setflag FLAG_BATTLE_NO_CATCHING
	dowildbattle
	clearflag FLAG_BATTLE_NO_CATCHING
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiFreed
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_Backed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeRoomFinal_EventScript_DarkraiFreed::
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_Shattered, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_PIKE_FINAL_ROOM_ATTENDANT
	setflag FLAG_DARKRAI_FREED
	fadescreen FADE_FROM_WHITE
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_Gone, MSGBOX_DEFAULT
	giveitem ITEM_DARKRANITE
	msgbox BattleFrontier_BattlePikeRoomFinal_Text_SleepEasy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattlePikeRoomFinal_Text_Enter:
	.string "The curtains fall shut behind\n"
	.string "{PLAYER}.\p"
	.string "It's cold in here, and dark. Far\n"
	.string "ahead, something breathes, slowly.\p"
	.string "The way out is back down, through\n"
	.string "the curtains.$"

BattleFrontier_BattlePikeRoomFinal_Text_Collar:
	.string "A shadow hangs in the air, one\n"
	.string "blue eye open. DARKRAI.\p"
	.string "A collar of cold light is clamped\n"
	.string "around its neck.\p"
	.string "It's a chip, like the ones in the\n"
	.string "FRONTIER's POKéMON. Cut from a\l"
	.string "shard of MEGA STONE.\p"
	.string "SCOTT must have done this. He\n"
	.string "leashed it here in the empty PIKE,\l"
	.string "to feed on the island while he's\l"
	.string "away.\p"
	.string "The eye narrows. The collar flares.$"

BattleFrontier_BattlePikeRoomFinal_Text_Again:
	.string "DARKRAI is still here, the collar\n"
	.string "still burning. The eye narrows.$"

BattleFrontier_BattlePikeRoomFinal_Text_BagFull:
	.string "DARKRAI waits in the dark. But\n"
	.string "{PLAYER}'s BAG is full.\p"
	.string "Whatever that collar leaves behind\n"
	.string "will need room. Make some first.$"

BattleFrontier_BattlePikeRoomFinal_Text_Backed:
	.string "DARKRAI doesn't follow. The collar's\n"
	.string "light pulses in the dark, patient.$"

BattleFrontier_BattlePikeRoomFinal_Text_Shattered:
	.string "The collar shattered!$"

BattleFrontier_BattlePikeRoomFinal_Text_Gone:
	.string "DARKRAI melted into the dark and\n"
	.string "was gone.\p"
	.string "Where it hung, the collar's last\n"
	.string "shard lies on the floor.$"

BattleFrontier_BattlePikeRoomFinal_Text_SleepEasy:
	.string "Out in the FRONTIER, the sleepers\n"
	.string "are stirring.\p"
	.string "The island will sleep easy tonight.$"

BattleFrontier_BattlePikeRoomFinal_Text_LeaveAsk:
	.string "Go back out through the curtains?$"
