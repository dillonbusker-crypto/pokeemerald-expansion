NavelRock_Top_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NavelRock_Top_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, NavelRock_Top_OnResume
	.byte 0

@ Ten Gauntlets: the summit is reached only by the old woman's AZURE FLUTE
@ (BattleFrontier_Lounge8), and ARCEUS stands where HO-OH roosted. HO-OH
@ never shows and his trigger (VAR_TEMP_1) never fires; the ladder down
@ leads back to the old woman's house (map.json). The vanilla HO-OH scripts
@ below are unreferenced.
NavelRock_Top_OnTransition:
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_HO_OH
	end

@ ARCEUS at (12, 8), at the head of the path; level 60, catchable, never
@ chipped (MAPSEC_NAVEL_ROCK). Caught: gone (FLAG_ARCEUS_CAUGHT),
@ VAR_ARCEUS_EVENT 2, and the light carries the player back to the house.
@ Knocked out or run from: it stays.
NavelRock_Top_EventScript_Arceus::
	lock
	faceplayer
	msgbox NavelRock_Top_Text_ArceusBefore, MSGBOX_DEFAULT
	msgbox NavelRock_Top_Text_ArceusChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NavelRock_Top_EventScript_ArceusStepBack
	closemessage
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_ARCEUS, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, NavelRock_Top_EventScript_ArceusCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NavelRock_Top_EventScript_ArceusStands
	msgbox NavelRock_Top_Text_ArceusLetGo, MSGBOX_DEFAULT
	release
	end

NavelRock_Top_EventScript_ArceusStepBack::
	msgbox NavelRock_Top_Text_ArceusStepBack, MSGBOX_DEFAULT
	release
	end

NavelRock_Top_EventScript_ArceusStands::
	msgbox NavelRock_Top_Text_ArceusStands, MSGBOX_DEFAULT
	release
	end

NavelRock_Top_EventScript_ArceusCaught::
	setflag FLAG_ARCEUS_CAUGHT
	setvar VAR_ARCEUS_EVENT, 2
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_NAVEL_ROCK_ARCEUS
	fadescreen FADE_FROM_WHITE
	msgbox NavelRock_Top_Text_ArceusCaught, MSGBOX_DEFAULT
	closemessage
	warpwhitefade MAP_BATTLE_FRONTIER_LOUNGE8, 1, 5
	waitstate
	release
	end

NavelRock_Top_Text_ArceusBefore:
	.string "It did not move.\n"
	.string "It did not need to.\p"
	.string "{PLAYER} felt very small.$"

NavelRock_Top_Text_ArceusChallenge:
	.string "Challenge it?$"

NavelRock_Top_Text_ArceusStepBack:
	.string "{PLAYER} stepped back.\p"
	.string "It watched. It had been watching\n"
	.string "since before there were eyes.$"

NavelRock_Top_Text_ArceusStands:
	.string "It rose into the light, and came\n"
	.string "down again, whole.\p"
	.string "It is not finished with {PLAYER}.$"

NavelRock_Top_Text_ArceusLetGo:
	.string "It let {PLAYER} go.\p"
	.string "It did not need to chase.$"

NavelRock_Top_Text_ArceusCaught:
	.string "The light folded in on itself and\n"
	.string "was gone.\p"
	.string "Far below, {PLAYER} thought, an old\n"
	.string "woman's hum had just stopped.\p"
	.string "The light rose again, gently this\n"
	.string "time, and carried {PLAYER} home.$"

NavelRock_Top_EventScript_HideHoOh::
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_HO_OH
	return

NavelRock_Top_EventScript_TryShowHoOh::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_DEFEATED_HO_OH, Common_EventScript_NopReturn
	setvar VAR_TEMP_1, 0
	clearflag FLAG_HIDE_HO_OH
	return

NavelRock_Top_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, NavelRock_Top_EventScript_TryRemoveHoOh
	end

NavelRock_Top_EventScript_TryRemoveHoOh::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_NAVEL_ROCK_HO_OH
	return

NavelRock_Top_EventScript_HoOh::
	lockall
	setvar VAR_TEMP_1, 1
	special SpawnCameraObject
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_NAVEL_ROCK_HO_OH, NavelRock_Top_Movement_HoOhAppear
	applymovement LOCALID_CAMERA, NavelRock_Top_Movement_CameraPanUp
	waitmovement 0
	delay 50
	setweather WEATHER_NONE
	doweather
	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	delay 60
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_CAMERA, NavelRock_Top_Movement_CameraPanDown
	applymovement LOCALID_NAVEL_ROCK_HO_OH, NavelRock_Top_Movement_HoOhApproach
	waitmovement 0
	special RemoveCameraObject
	seteventmon SPECIES_HO_OH, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_LAST_TALKED, LOCALID_NAVEL_ROCK_HO_OH
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NavelRock_Top_EventScript_DefeatedHoOh
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NavelRock_Top_EventScript_RanFromHoOh
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NavelRock_Top_EventScript_RanFromHoOh
	setflag FLAG_CAUGHT_HO_OH
	releaseall
	end

NavelRock_Top_EventScript_DefeatedHoOh::
	setflag FLAG_DEFEATED_HO_OH
	setvar VAR_0x8004, SPECIES_HO_OH
	goto Common_EventScript_LegendaryFlewAway
	end

NavelRock_Top_EventScript_RanFromHoOh::
	setvar VAR_0x8004, SPECIES_HO_OH
	goto Common_EventScript_LegendaryFlewAway
	end

NavelRock_Top_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	step_end

NavelRock_Top_Movement_CameraPanDown:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

NavelRock_Top_Movement_HoOhApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	delay_16
	delay_16
	step_end

NavelRock_Top_Movement_HoOhAppear:
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	step_end
