ArtisanCave_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, ArtisanCave_B1F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, ArtisanCave_B1F_OnTransition
	.byte 0

ArtisanCave_B1F_OnTransition:
	setflag FLAG_LANDMARK_ARTISAN_CAVE
	call_if_set FLAG_ARTISAN_LATI_CAUGHT, ArtisanCave_B1F_EventScript_HideLatis
	call_if_lt VAR_ARTISAN_QUEST_STEP, 6, ArtisanCave_B1F_EventScript_HideLatis
	@ The exits (the west entrance, and the ladder toward the east one) are
	@ blocked until the player has battled a Lati - only while the Latis are
	@ actually here, so nobody arriving early can be trapped.
	setvar VAR_TEMP_4, 1
	goto_if_set FLAG_ARTISAN_LATI_CAUGHT, ArtisanCave_B1F_EventScript_TransitionEnd
	goto_if_lt VAR_ARTISAN_QUEST_STEP, 6, ArtisanCave_B1F_EventScript_TransitionEnd
	setvar VAR_TEMP_4, 0
ArtisanCave_B1F_EventScript_TransitionEnd:
	end

@ Ten Gauntlets: the Artisan Cave side quest (easter-eggs-spec.md, #1).
@ Latios and Latias wait just inside the west entrance, once FLOTSAM has
@ been beaten at the waterfall (quest step 6). Either one is a
@ level 50 wild battle; catching one sends the other off for good. A
@ fainted one only disappears until the player next enters the cave, since
@ their hide flags are temporary ones. Both are shiny - P_FLAG_FORCE_SHINY
@ is a temp flag, so it can't outlive the battle even on a whiteout. It
@ must be set before setwildbattle, which rolls the Pokemon immediately.
ArtisanCave_B1F_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, ArtisanCave_B1F_EventScript_TryRemoveLati
	end

ArtisanCave_B1F_EventScript_TryRemoveLati::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ArtisanCave_B1F_EventScript_RemoveLati
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ArtisanCave_B1F_EventScript_RemoveLati
	return

ArtisanCave_B1F_EventScript_RemoveLati::
	removeobject VAR_LAST_TALKED
	return

ArtisanCave_B1F_EventScript_HideLatis::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	return

ArtisanCave_B1F_EventScript_Latios::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LATIOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag P_FLAG_FORCE_SHINY
	setwildbattle SPECIES_LATIOS, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_CATCH_ONLY_BATTLE
	dowildbattle
	clearflag FLAG_CATCH_ONLY_BATTLE
	setvar VAR_TEMP_4, 1
	clearflag P_FLAG_FORCE_SHINY
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ArtisanCave_B1F_EventScript_CaughtLatios
	release
	end

ArtisanCave_B1F_EventScript_CaughtLatios::
	setflag FLAG_ARTISAN_LATI_CAUGHT
	setvar VAR_ARTISAN_QUEST_STEP, 7
	playmoncry SPECIES_LATIAS, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_ARTISAN_LATIAS, ArtisanCave_B1F_Movement_FlyOff
	waitmovement 0
	removeobject LOCALID_ARTISAN_LATIAS
	msgbox ArtisanCave_B1F_Text_LatiasFlewOff, MSGBOX_DEFAULT
	release
	end

ArtisanCave_B1F_EventScript_Latias::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LATIAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag P_FLAG_FORCE_SHINY
	setwildbattle SPECIES_LATIAS, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_CATCH_ONLY_BATTLE
	dowildbattle
	clearflag FLAG_CATCH_ONLY_BATTLE
	setvar VAR_TEMP_4, 1
	clearflag P_FLAG_FORCE_SHINY
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ArtisanCave_B1F_EventScript_CaughtLatias
	release
	end

ArtisanCave_B1F_EventScript_CaughtLatias::
	setflag FLAG_ARTISAN_LATI_CAUGHT
	setvar VAR_ARTISAN_QUEST_STEP, 7
	playmoncry SPECIES_LATIOS, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_ARTISAN_LATIOS, ArtisanCave_B1F_Movement_FlyOff
	waitmovement 0
	removeobject LOCALID_ARTISAN_LATIOS
	msgbox ArtisanCave_B1F_Text_LatiosFlewOff, MSGBOX_DEFAULT
	release
	end

ArtisanCave_B1F_Movement_FlyOff:
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	step_end

ArtisanCave_B1F_Text_LatiasFlewOff:
	.string "LATIAS let out a cry and flew off\n"
	.string "deep into the cave...$"

ArtisanCave_B1F_Text_LatiosFlewOff:
	.string "LATIOS let out a cry and flew off\n"
	.string "deep into the cave...$"

ArtisanCave_B1F_EventScript_StayInCave::
	lockall
	msgbox ArtisanCave_B1F_Text_StayInCave, MSGBOX_DEFAULT
	closemessage
	specialvar VAR_RESULT, GetPlayerFacingDirection
	switch VAR_RESULT
	case DIR_NORTH, ArtisanCave_B1F_EventScript_StepBackDown
	case DIR_WEST, ArtisanCave_B1F_EventScript_StepBackRight
	case DIR_EAST, ArtisanCave_B1F_EventScript_StepBackLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	goto ArtisanCave_B1F_EventScript_StayInCaveEnd
	end

ArtisanCave_B1F_EventScript_StepBackDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	goto ArtisanCave_B1F_EventScript_StayInCaveEnd
	end

ArtisanCave_B1F_EventScript_StepBackRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	goto ArtisanCave_B1F_EventScript_StayInCaveEnd
	end

ArtisanCave_B1F_EventScript_StepBackLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
ArtisanCave_B1F_EventScript_StayInCaveEnd::
	waitmovement 0
	releaseall
	end

ArtisanCave_B1F_Text_StayInCave:
	.string "I should probably stay in the\n"
	.string "cave.$"
