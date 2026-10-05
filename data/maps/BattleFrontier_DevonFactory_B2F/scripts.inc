BattleFrontier_DevonFactory_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BattleFrontier_DevonFactory_B2F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_DevonFactory_B2F_OnTransition
	.byte 0

@ ============================================================================
@ Ten Gauntlets: the Generator Hall (storyline.md, "After gauntlet 8"). The
@ stairs down to the PILLAR are sealed until all five guards are beaten and
@ the Holding Block's cells are open. Five red lights (metatile 0x224) sit
@ beside the door, one per guard; each beaten guard's goes dark (the plain
@ wall face, 0x221). Once everything is done, WALLACE waits by the stairs,
@ and walking up to them takes the two of them down together.
@ ============================================================================

BattleFrontier_DevonFactory_B2F_OnLoad:
	specialvar VAR_RESULT, GetFactoryBrainsBeaten
	call_if_ge VAR_RESULT, 1, BattleFrontier_DevonFactory_B2F_EventScript_LightOff1
	call_if_ge VAR_RESULT, 2, BattleFrontier_DevonFactory_B2F_EventScript_LightOff2
	call_if_ge VAR_RESULT, 3, BattleFrontier_DevonFactory_B2F_EventScript_LightOff3
	call_if_ge VAR_RESULT, 4, BattleFrontier_DevonFactory_B2F_EventScript_LightOff4
	call_if_ge VAR_RESULT, 5, BattleFrontier_DevonFactory_B2F_EventScript_LightOff5
	end

BattleFrontier_DevonFactory_B2F_EventScript_LightOff1::
	setmetatile 10, 1, 0x221, TRUE
	return

BattleFrontier_DevonFactory_B2F_EventScript_LightOff2::
	setmetatile 11, 1, 0x221, TRUE
	return

BattleFrontier_DevonFactory_B2F_EventScript_LightOff3::
	setmetatile 15, 1, 0x221, TRUE
	return

BattleFrontier_DevonFactory_B2F_EventScript_LightOff4::
	setmetatile 16, 1, 0x221, TRUE
	return

BattleFrontier_DevonFactory_B2F_EventScript_LightOff5::
	setmetatile 17, 1, 0x221, TRUE
	return

BattleFrontier_DevonFactory_B2F_OnTransition:
	setflag FLAG_TEMP_1
	call BattleFrontier_DevonFactory_B2F_EventScript_CheckStairsOpen
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_DevonFactory_B2F_EventScript_OnTransitionEnd
	clearflag FLAG_TEMP_1
BattleFrontier_DevonFactory_B2F_EventScript_OnTransitionEnd:
	end

@ VAR_RESULT = TRUE once the stairs can open: all five guards beaten and the
@ cells open, during the Factory (state 4).
BattleFrontier_DevonFactory_B2F_EventScript_CheckStairsOpen::
	setvar VAR_RESULT, FALSE
	goto_if_ne VAR_ENDGAME_STATE, 4, Common_EventScript_NopReturn
	goto_if_unset FLAG_ENDGAME_CELLS_OPENED, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetFactoryBrainsBeaten
	goto_if_lt VAR_RESULT, 5, BattleFrontier_DevonFactory_B2F_EventScript_StairsNotReady
	setvar VAR_RESULT, TRUE
	return

BattleFrontier_DevonFactory_B2F_EventScript_StairsNotReady::
	setvar VAR_RESULT, FALSE
	return

@ The coord event on (13, 2), below the stairs at (13, 1).
BattleFrontier_DevonFactory_B2F_EventScript_PillarDoorSealed::
	lockall
	call BattleFrontier_DevonFactory_B2F_EventScript_CheckStairsOpen
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_DevonFactory_B2F_EventScript_GoDown
	goto_if_ge VAR_ENDGAME_STATE, 5, BattleFrontier_DevonFactory_B2F_EventScript_NothingLeft
	specialvar VAR_RESULT, GetFactoryBrainsBeaten
	goto_if_lt VAR_RESULT, 5, BattleFrontier_DevonFactory_B2F_EventScript_LightsStillOn
	msgbox BattleFrontier_DevonFactory_B2F_Text_CaptivesFirst, MSGBOX_DEFAULT
	goto BattleFrontier_DevonFactory_B2F_EventScript_StepBack

BattleFrontier_DevonFactory_B2F_EventScript_NothingLeft::
	msgbox BattleFrontier_DevonFactory_B2F_Text_NothingLeft, MSGBOX_DEFAULT
	goto BattleFrontier_DevonFactory_B2F_EventScript_StepBack

BattleFrontier_DevonFactory_B2F_EventScript_LightsStillOn::
	msgbox BattleFrontier_DevonFactory_B2F_Text_PillarDoorSealed, MSGBOX_DEFAULT
BattleFrontier_DevonFactory_B2F_EventScript_StepBack::
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_DevonFactory_B2F_Movement_StepBack
	waitmovement 0
	releaseall
	end

BattleFrontier_DevonFactory_B2F_EventScript_StairsWallace::
	lockall
	applymovement LOCALID_DEVON_FACTORY_STAIRS_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_B2F_Text_StairsWallaceTalk, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_DevonFactory_B2F_EventScript_GoDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_DEVON_FACTORY_STAIRS_WALLACE, Common_Movement_FaceRight
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_B2F_Text_StairsWallace, MSGBOX_DEFAULT
	closemessage
	playse SE_UNLOCK
	waitse
	warp MAP_BATTLE_FRONTIER_DEVON_FACTORY_B3F, 0
	waitstate
	releaseall
	end

BattleFrontier_DevonFactory_B2F_Movement_StepBack:
	walk_down
	step_end

BattleFrontier_DevonFactory_B2F_EventScript_LockLights::
	msgbox BattleFrontier_DevonFactory_B2F_Text_LockLights, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B2F_EventScript_GeneratorUnit::
	msgbox BattleFrontier_DevonFactory_B2F_Text_GeneratorUnit, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B2F_EventScript_Generator::
	msgbox BattleFrontier_DevonFactory_B2F_Text_Generator, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B2F_Text_LockLights:
	.string "Red lights glow beside the door.\n"
	.string "One for each lock.$"

BattleFrontier_DevonFactory_B2F_Text_GeneratorUnit:
	.string "A DEVON generator. The readout\n"
	.string "says: OUTPUT TO PILLAR.$"

BattleFrontier_DevonFactory_B2F_Text_Generator:
	.string "The generator hums. The floor\n"
	.string "trembles under it.$"

BattleFrontier_DevonFactory_B2F_Text_PillarDoorSealed:
	.string "The door won't budge. Red lights\n"
	.string "still glow beside it.$"

BattleFrontier_DevonFactory_B2F_Text_CaptivesFirst:
	.string "The lights are out, but the door\n"
	.string "won't open yet.\p"
	.string "{PLAYER} decided to free the\n"
	.string "captives in the HOLDING BLOCK\l"
	.string "first.$"

BattleFrontier_DevonFactory_B2F_Text_StairsWallaceTalk:
	.string "WALLACE: SPENSER and BRANDON won't\n"
	.string "trouble anyone for a while.\p"
	.string "The lights are out. SCOTT is down\n"
	.string "those stairs.$"

BattleFrontier_DevonFactory_B2F_Text_StairsWallace:
	.string "WALLACE: {PLAYER}! SPENSER and\n"
	.string "BRANDON won't trouble anyone for\l"
	.string "a while.\p"
	.string "Every light is out, and your family\n"
	.string "is safe. Well done.\p"
	.string "SCOTT is down there. Let's end this,\n"
	.string "together.$"

BattleFrontier_DevonFactory_B2F_Text_NothingLeft:
	.string "The door has sealed itself again.\n"
	.string "SCOTT is long gone.$"
