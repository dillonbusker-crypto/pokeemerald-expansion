NewMauville_Inside_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, NewMauville_Inside_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, NewMauville_Inside_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, NewMauville_Inside_OnLoad
	.byte 0

NewMauville_Inside_OnResume:
	call_if_eq VAR_TEMP_1, 1, NewMauville_Inside_EventScript_SetBarrierStateBlueButton
	call_if_eq VAR_TEMP_2, 1, NewMauville_Inside_EventScript_SetBarrierStateGreenButton
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, NewMauville_Inside_EventScript_TryRemoveVoltorb
	end

NewMauville_Inside_EventScript_TryRemoveVoltorb::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

NewMauville_Inside_OnTransition:
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	@ Ten Gauntlets: the VOLTORBs are switched off (and no wild encounters).
	setflag FLAG_HIDE_NEW_MAUVILLE_VOLTORB_1
	setflag FLAG_HIDE_NEW_MAUVILLE_VOLTORB_2
	setflag FLAG_HIDE_NEW_MAUVILLE_VOLTORB_3
	call NewMauville_Inside_EventScript_SetupEndgame
	end

NewMauville_Inside_EventScript_ShowVoltorb1::
	clearflag FLAG_HIDE_NEW_MAUVILLE_VOLTORB_1
	return

NewMauville_Inside_EventScript_ShowVoltorb2::
	clearflag FLAG_HIDE_NEW_MAUVILLE_VOLTORB_2
	return

NewMauville_Inside_EventScript_ShowVoltorb3::
	clearflag FLAG_HIDE_NEW_MAUVILLE_VOLTORB_3
	return

NewMauville_Inside_OnLoad:
	call_if_eq VAR_NEW_MAUVILLE_STATE, 2, NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	end

NewMauville_Inside_EventScript_BlueButton::
	lockall
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_2, 0
	playse SE_PIN
	call NewMauville_Inside_EventScript_SetBarrierStateBlueButton
	special DrawWholeMapView
	releaseall
	end

NewMauville_Inside_EventScript_GreenButton::
	lockall
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 1
	playse SE_PIN
	call NewMauville_Inside_EventScript_SetBarrierStateGreenButton
	special DrawWholeMapView
	releaseall
	end

NewMauville_Inside_EventScript_SetBarrierStateBlueButton::
	setmetatile 23, 34, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 23, 35, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 23, 36, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 23, 37, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 10, 16, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 10, 17, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 10, 18, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 10, 19, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 10, 0, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 10, 1, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 10, 2, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 10, 3, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 37, 33, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 37, 34, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 37, 35, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 37, 36, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 28, 22, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 28, 23, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 28, 24, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 28, 25, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 10, 24, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 10, 25, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 10, 26, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 10, 27, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 21, 2, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 21, 3, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 21, 4, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 21, 5, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 6, 11, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 13, 10, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 16, 22, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 4, 26, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 30, 38, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 2, 11, METATILE_BikeShop_Button_Green, FALSE
	setmetatile 17, 10, METATILE_BikeShop_Button_Green, FALSE
	setmetatile 25, 18, METATILE_BikeShop_Button_Green, FALSE
	setmetatile 18, 36, METATILE_BikeShop_Button_Green, FALSE
	return

NewMauville_Inside_EventScript_SetBarrierStateGreenButton::
	setmetatile 23, 34, METATILE_BikeShop_Barrier_Blue_Top, TRUE
	setmetatile 23, 35, METATILE_BikeShop_Barrier_Blue_TopMid, TRUE
	setmetatile 23, 36, METATILE_BikeShop_Barrier_Blue_BottomMid, TRUE
	setmetatile 23, 37, METATILE_BikeShop_Barrier_Blue_Bottom, TRUE
	setmetatile 10, 16, METATILE_BikeShop_Barrier_Blue_Top, TRUE
	setmetatile 10, 17, METATILE_BikeShop_Barrier_Blue_TopMid, TRUE
	setmetatile 10, 18, METATILE_BikeShop_Barrier_Blue_BottomMid, TRUE
	setmetatile 10, 19, METATILE_BikeShop_Barrier_Blue_Bottom, TRUE
	setmetatile 10, 0, METATILE_BikeShop_Barrier_Blue_Top, TRUE
	setmetatile 10, 1, METATILE_BikeShop_Barrier_Blue_TopMid, TRUE
	setmetatile 10, 2, METATILE_BikeShop_Barrier_Blue_BottomMid, TRUE
	setmetatile 10, 3, METATILE_BikeShop_Barrier_Blue_Bottom, TRUE
	setmetatile 37, 33, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 37, 34, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 37, 35, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 37, 36, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 28, 22, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 28, 23, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 28, 24, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 28, 25, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 10, 24, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 10, 25, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 10, 26, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 10, 27, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 21, 2, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 21, 3, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 21, 4, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 21, 5, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 2, 11, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 17, 10, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 25, 18, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 18, 36, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 6, 11, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 13, 10, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 16, 22, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 4, 26, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 30, 38, METATILE_BikeShop_Button_Blue, FALSE
	return

NewMauville_Inside_EventScript_RedButton::
	lockall
	msgbox NewMauville_Inside_Text_SteppedOnSwitchGeneratorStopped, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 2
	releaseall
	end

NewMauville_Inside_EventScript_SetGeneratorOffMetatiles::
	setmetatile 33, 6, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 32, 2, METATILE_BikeShop_Generator_Off_Tile0, TRUE
	setmetatile 33, 2, METATILE_BikeShop_Generator_Off_Tile1, TRUE
	setmetatile 34, 2, METATILE_BikeShop_Generator_Off_Tile2, TRUE
	setmetatile 35, 2, METATILE_BikeShop_Generator_Off_Tile3, TRUE
	setmetatile 32, 3, METATILE_BikeShop_Generator_Off_Tile4, TRUE
	setmetatile 33, 3, METATILE_BikeShop_Generator_Off_Tile5, TRUE
	setmetatile 34, 3, METATILE_BikeShop_Generator_Off_Tile6, TRUE
	setmetatile 35, 3, METATILE_BikeShop_Generator_Off_Tile7, TRUE
	special DrawWholeMapView
	return

NewMauville_Inside_EventScript_Generator::
	lockall
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, NewMauville_Inside_EventScript_GeneratorOff
	msgbox NewMauville_Inside_Text_GeneratorRadiatingHeat, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_EventScript_GeneratorOff::
	msgbox NewMauville_Inside_Text_GeneratorQuietedDown, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_EventScript_Voltorb1::
	lock
	faceplayer
	setwildbattle SPECIES_VOLTORB, 25
	waitse
	playmoncry SPECIES_VOLTORB, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedVoltorb1
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_DefeatedVoltorb1
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_DefeatedVoltorb1
	setflag FLAG_DEFEATED_VOLTORB_1_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_DefeatedVoltorb1::
	setflag FLAG_DEFEATED_VOLTORB_1_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_Voltorb2::
	lock
	faceplayer
	setwildbattle SPECIES_VOLTORB, 25
	waitse
	playmoncry SPECIES_VOLTORB, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedVoltorb2
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_DefeatedVoltorb2
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_DefeatedVoltorb2
	setflag FLAG_DEFEATED_VOLTORB_2_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_DefeatedVoltorb2::
	setflag FLAG_DEFEATED_VOLTORB_2_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_Voltorb3::
	lock
	faceplayer
	setwildbattle SPECIES_VOLTORB, 25
	waitse
	playmoncry SPECIES_VOLTORB, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedVoltorb3
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_DefeatedVoltorb3
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_DefeatedVoltorb3
	setflag FLAG_DEFEATED_VOLTORB_3_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_DefeatedVoltorb3::
	setflag FLAG_DEFEATED_VOLTORB_3_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_Text_GeneratorRadiatingHeat:
	.string "The generator is radiating heat that\n"
	.string "can be felt even at a distance.\p"
	.string "It looks like it should be turned off\n"
	.string "as soon as possible.$"

NewMauville_Inside_Text_GeneratorQuietedDown:
	.string "The generator quieted down.$"

NewMauville_Inside_Text_SteppedOnSwitchGeneratorStopped:
	.string "{PLAYER} stepped on the switch.\p"
	.string "Click…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "The generator appears to have\n"
	.string "stopped…$"

@ ============================================================================
@ Ten Gauntlets: New Mauville (storyline.md; VAR_ENDGAME_STATE is explained in
@ BattleFrontier_OutsideEast). The VOLTORBs, the wild encounters, the locked
@ door and the red switch are switched off; the buttons and barriers still
@ work as in vanilla.
@   13 five guards hold the corridors, each fought once, in order: MAGMA's
@      ADMINS and then MAXIE (TABITHA, COURTNEY, MAXIE), then AQUA's (MATT,
@      SHELLY). VAR_NEW_MAUVILLE_ADMINS counts them (0-5), and a trigger just
@      before each starts the fight. The player uses the SCRAMBLER before
@      each, so a beaten guard stays beaten; each leaves, a charging coil
@      heals the party, and the held items come back
@      (EventScript_RestoreStoryHeldItems), win or white-out.
@      At the generator ARCHIE is fought alone, with the beaten MAXIE standing
@      beside him (a second MAXIE object, LOCALID_NEW_MAUVILLE_MAXIE_BEATEN,
@      shown once MAXIE's trainer flag is set). A loss whites out to
@      MAUVILLE's POKEMON CENTER and only ARCHIE is fought again: state 14 is
@      set after his win.
@   14 the CROWN is supercharged; MAXIE and ARCHIE are gone
@ FLAG_TEMP_1-4 the admins, 5 MAXIE in the corridor, 6 ARCHIE, 7 MAXIE at the
@ generator.
@ ============================================================================

NewMauville_Inside_EventScript_SetupEndgame::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	goto_if_ne VAR_ENDGAME_STATE, 13, Common_EventScript_NopReturn
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	clearflag FLAG_TEMP_6
	checktrainerflag TRAINER_NEW_MAUVILLE_TABITHA
	call_if FALSE, NewMauville_Inside_EventScript_ShowTabitha
	checktrainerflag TRAINER_NEW_MAUVILLE_COURTNEY
	call_if FALSE, NewMauville_Inside_EventScript_ShowCourtney
	checktrainerflag TRAINER_NEW_MAUVILLE_MAXIE
	call_if FALSE, NewMauville_Inside_EventScript_ShowMaxie
	call_if TRUE, NewMauville_Inside_EventScript_ShowMaxieBeaten
	checktrainerflag TRAINER_NEW_MAUVILLE_MATT
	call_if FALSE, NewMauville_Inside_EventScript_ShowMatt
	checktrainerflag TRAINER_NEW_MAUVILLE_SHELLY
	call_if FALSE, NewMauville_Inside_EventScript_ShowShelly
	return

NewMauville_Inside_EventScript_ShowTabitha::
	clearflag FLAG_TEMP_1
	return

NewMauville_Inside_EventScript_ShowCourtney::
	clearflag FLAG_TEMP_2
	return

NewMauville_Inside_EventScript_ShowMaxie::
	clearflag FLAG_TEMP_5
	return

NewMauville_Inside_EventScript_ShowMaxieBeaten::
	clearflag FLAG_TEMP_7
	return

NewMauville_Inside_EventScript_ShowMatt::
	clearflag FLAG_TEMP_3
	return

NewMauville_Inside_EventScript_ShowShelly::
	clearflag FLAG_TEMP_4
	return

@ Each guard is on a one-tile-wide stretch (SHELLY's is two wide, so two
@ triggers), and the trigger is the tile just before. The fight scripts
@ start from either the trigger or a talk.
NewMauville_Inside_EventScript_TabithaTrigger::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_TABITHA
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto NewMauville_Inside_EventScript_TabithaFight

NewMauville_Inside_EventScript_Tabitha::
	lockall
	faceplayer
	goto NewMauville_Inside_EventScript_TabithaFight

NewMauville_Inside_EventScript_TabithaFight::
	msgbox NewMauville_Inside_Text_Tabitha, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_TABITHA, NewMauville_Inside_Text_TabithaDefeat
	msgbox NewMauville_Inside_Text_TabithaAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 1
	goto NewMauville_Inside_EventScript_GuardLeaves

NewMauville_Inside_EventScript_CourtneyTrigger::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_COURTNEY
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto NewMauville_Inside_EventScript_CourtneyFight

NewMauville_Inside_EventScript_Courtney::
	lockall
	faceplayer
	goto_if_ne VAR_NEW_MAUVILLE_ADMINS, 1, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_CourtneyFight

NewMauville_Inside_EventScript_CourtneyFight::
	msgbox NewMauville_Inside_Text_Courtney, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_COURTNEY, NewMauville_Inside_Text_CourtneyDefeat
	msgbox NewMauville_Inside_Text_CourtneyAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 2
	goto NewMauville_Inside_EventScript_GuardLeaves

@ MAXIE holds the stretch at (4, 9), MAGMA's last. Beaten, he leaves for the
@ generator: the second MAXIE object there is shown (FLAG_TEMP_7), and on every
@ later visit SetupEndgame shows it from his trainer flag.
NewMauville_Inside_EventScript_MaxieTrigger::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_MAXIE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto NewMauville_Inside_EventScript_MaxieFight

NewMauville_Inside_EventScript_Maxie::
	lockall
	faceplayer
	goto_if_ne VAR_NEW_MAUVILLE_ADMINS, 2, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_MaxieFight

NewMauville_Inside_EventScript_MaxieFight::
	msgbox NewMauville_Inside_Text_Maxie, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_MAXIE, NewMauville_Inside_Text_MaxieDefeat
	msgbox NewMauville_Inside_Text_MaxieAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 3
	clearflag FLAG_TEMP_7
	goto NewMauville_Inside_EventScript_GuardLeaves

NewMauville_Inside_EventScript_MattTrigger::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_MATT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto NewMauville_Inside_EventScript_MattFight

NewMauville_Inside_EventScript_Matt::
	lockall
	faceplayer
	goto_if_ne VAR_NEW_MAUVILLE_ADMINS, 3, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_MattFight

NewMauville_Inside_EventScript_MattFight::
	msgbox NewMauville_Inside_Text_Matt, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_MATT, NewMauville_Inside_Text_MattDefeat
	msgbox NewMauville_Inside_Text_MattAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 4
	goto NewMauville_Inside_EventScript_GuardLeaves

@ SHELLY stands at (21, 5); on the upper lane the trigger brings her up beside
@ the player first.
NewMauville_Inside_EventScript_ShellyTrigger4::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_SHELLY
	applymovement LOCALID_NEW_MAUVILLE_SHELLY, Common_Movement_WalkUp
	waitmovement 0
	goto NewMauville_Inside_EventScript_ShellyTrigger

NewMauville_Inside_EventScript_ShellyTrigger5::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_SHELLY
	goto NewMauville_Inside_EventScript_ShellyTrigger

NewMauville_Inside_EventScript_ShellyTrigger::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto NewMauville_Inside_EventScript_ShellyFight

NewMauville_Inside_EventScript_Shelly::
	lockall
	faceplayer
	goto_if_ne VAR_NEW_MAUVILLE_ADMINS, 4, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_ShellyFight

NewMauville_Inside_EventScript_ShellyFight::
	msgbox NewMauville_Inside_Text_Shelly, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_SHELLY, NewMauville_Inside_Text_ShellyDefeat
	msgbox NewMauville_Inside_Text_ShellyAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 5
	goto NewMauville_Inside_EventScript_GuardLeaves

NewMauville_Inside_EventScript_NotYet::
	msgbox NewMauville_Inside_Text_NotYet, MSGBOX_DEFAULT
	releaseall
	end

@ Shared by all five. VAR_LAST_TALKED is the guard just beaten.
NewMauville_Inside_EventScript_GuardLeaves::
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	special HealPlayerParty
	fadescreen FADE_FROM_BLACK
	msgbox NewMauville_Inside_Text_Healed, MSGBOX_DEFAULT
	releaseall
	end

@ The beaten MAXIE and ARCHIE stand at (33, 5) and (34, 5). Walking into the
@ room (x 29) or talking to either starts the same scene: ARCHIE's battle.
NewMauville_Inside_EventScript_GeneratorLeadersTrigger::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_NEW_MAUVILLE_MAXIE_BEATEN, Common_Movement_FaceLeft
	applymovement LOCALID_NEW_MAUVILLE_ARCHIE, Common_Movement_FaceLeft
	waitmovement 0
	goto NewMauville_Inside_EventScript_GeneratorLeadersScene

NewMauville_Inside_EventScript_GeneratorLeaders::
	lockall
	goto_if_ne VAR_ENDGAME_STATE, 13, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_GeneratorLeadersScene

NewMauville_Inside_EventScript_GeneratorLeadersScene::
	msgbox NewMauville_Inside_Text_MaxieAtGenerator, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_Archie1, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_Archie2, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_ARCHIE
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_ARCHIE, NewMauville_Inside_Text_ArchieDefeat
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	msgbox NewMauville_Inside_Text_LeadersBeaten, MSGBOX_DEFAULT
	closemessage
	@ The CROWN, held up to the generator.
	playse SE_M_THUNDERBOLT2
	fadescreen FADE_TO_WHITE
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 16 @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_FROM_WHITE
	playfanfare MUS_OBTAIN_ITEM
	msgbox NewMauville_Inside_Text_Supercharged, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	setvar VAR_ENDGAME_STATE, 14
	@ Scott takes the PRIMALS back through the CROWN.
	playse SE_BALL_OPEN
	delay 8
	playse SE_BALL_OPEN
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	msgbox NewMauville_Inside_Text_BallsEmpty, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_MaxieBitter, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_ArchieBitter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NEW_MAUVILLE_MAXIE_BEATEN
	removeobject LOCALID_NEW_MAUVILLE_ARCHIE
	fadescreen FADE_FROM_BLACK
	msgbox NewMauville_Inside_Text_LeadersGone, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_Text_NotYet:
	.string "…Not yet. Whoever stands in front\n"
	.string "of the generator isn't ready to\l"
	.string "talk.$"

NewMauville_Inside_Text_Healed:
	.string "A charging coil nearby hummed.\n"
	.string "{PLAYER}'s POKéMON were restored.$"

NewMauville_Inside_Text_Tabitha:
	.string "TABITHA: Hehehe! So you're the kid\n"
	.string "SCOTT warned us about.\p"
	.string "MAGMA works with AQUA now, and the\n"
	.string "generator under MAUVILLE is ours\l"
	.string "to guard.\p"
	.string "MAGMA holds this half, AQUA the\n"
	.string "other. I'm the first!$"

NewMauville_Inside_Text_TabithaDefeat:
	.string "Hehehe… Hahahaha!\n"
	.string "That was something!$"

NewMauville_Inside_Text_TabithaAfter:
	.string "TABITHA: Hehehe… Fine, I'm out.\p"
	.string "COURTNEY is down the corridor.\n"
	.string "She won't be as much fun about it.$"

NewMauville_Inside_Text_Courtney:
	.string "COURTNEY: …Ah. So you got past\n"
	.string "TABITHA.\p"
	.string "…Then I have to do this myself.\n"
	.string "…Hm. Target acquired.$"

NewMauville_Inside_Text_CourtneyDefeat:
	.string "…Ah…\n"
	.string "…I calculated wrong.$"

NewMauville_Inside_Text_CourtneyAfter:
	.string "COURTNEY: …Ah. You're strong.\p"
	.string "…MAXIE himself holds the next\n"
	.string "stretch. …He's not like us.\p"
	.string "…Be careful. …That's all.$"

NewMauville_Inside_Text_Maxie:
	.string "MAXIE: So. You've come through\n"
	.string "TABITHA and COURTNEY.\p"
	.string "SCOTT warned us you would.\p"
	.string "He also gave me what I always\n"
	.string "wanted. GROUDON, for good.\p"
	.string "All I have to do is guard this\n"
	.string "generator. I don't intend to lose\l"
	.string "it twice.$"

NewMauville_Inside_Text_MaxieDefeat:
	.string "Impossible… GROUDON's power…$"

NewMauville_Inside_Text_MaxieAfter:
	.string "MAXIE: …So that's that.\p"
	.string "AQUA holds the rest of the way.\n"
	.string "MATT, SHELLY, and ARCHIE at the\l"
	.string "generator.\p"
	.string "I'll be there. I want to see\n"
	.string "ARCHIE's face when you do to him\l"
	.string "what you just did to me.$"

NewMauville_Inside_Text_Matt:
	.string "MATT: Hah! So you're the one who\n"
	.string "walked through MAGMA's lot. Even\l"
	.string "MAXIE!\p"
	.string "That's their problem. TEAM AQUA's\n"
	.string "finest stands in your way now!$"

NewMauville_Inside_Text_MattDefeat:
	.string "Gwaaah!\n"
	.string "Washed away!$"

NewMauville_Inside_Text_MattAfter:
	.string "MATT: Grr… Go on, then.\p"
	.string "SHELLY is just ahead. She hates\n"
	.string "losing even more than I do.$"

NewMauville_Inside_Text_Shelly:
	.string "SHELLY: Ahahaha! You came all this\n"
	.string "way?\p"
	.string "I'm the last wall before the\n"
	.string "generator. Let's see what you're\l"
	.string "made of!$"

NewMauville_Inside_Text_ShellyDefeat:
	.string "Ahahaha… Swept away by the tide!$"

NewMauville_Inside_Text_ShellyAfter:
	.string "SHELLY: Fine, fine. I lost.\p"
	.string "The generator's through the door\n"
	.string "ahead. ARCHIE is waiting.\p"
	.string "And MAXIE, for whatever that's\n"
	.string "worth now. Don't come crying to me.$"

NewMauville_Inside_Text_MaxieAtGenerator:
	.string "MAXIE: …It's here, ARCHIE.\p"
	.string "As I said. Through all four of them,\n"
	.string "and through me.$"

NewMauville_Inside_Text_Archie1:
	.string "ARCHIE: Hah! So MAXIE lost. I won't.\p"
	.string "SCOTT gave us what we always\n"
	.string "wanted, kid. GROUDON and KYOGRE,\l"
	.string "for good.\p"
	.string "All I have to do is guard this\n"
	.string "generator.$"

NewMauville_Inside_Text_Archie2:
	.string "ARCHIE: Nobody touches it.\n"
	.string "KYOGRE and I will see to that!$"

NewMauville_Inside_Text_ArchieDefeat:
	.string "No… Not even KYOGRE…$"

NewMauville_Inside_Text_LeadersBeaten:
	.string "MAXIE and ARCHIE were both beaten.\p"
	.string "{PLAYER} held the REPLICA CROWN up\n"
	.string "to the generator.$"

NewMauville_Inside_Text_Supercharged:
	.string "The CROWN drank in the current!\p"
	.string "It can now make all six party\n"
	.string "POKéMON permanent MEGAS!$"

NewMauville_Inside_Text_BallsEmpty:
	.string "Light flared from MAXIE's and\n"
	.string "ARCHIE's POKé BALLS, then died.\p"
	.string "The BALLS were empty.$"

NewMauville_Inside_Text_MaxieBitter:
	.string "MAXIE: …GROUDON. Gone, through the\n"
	.string "CROWN, just as SCOTT said he would\l"
	.string "take it if we failed.$"

NewMauville_Inside_Text_ArchieBitter:
	.string "ARCHIE: And KYOGRE with it. Hmph.\p"
	.string "Listen, kid. SCOTT's headed for\n"
	.string "SKY PILLAR. If you want him,\l"
	.string "that's where he'll be.$"

NewMauville_Inside_Text_LeadersGone:
	.string "MAXIE and ARCHIE walked out of the\n"
	.string "generator hall without a word.$"
