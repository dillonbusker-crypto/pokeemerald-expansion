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
@   13 four guards hold the corridors, each fought once, in order: MAGMA's
@      ADMINS (TABITHA, COURTNEY), then AQUA's (MATT, SHELLY).
@      VAR_NEW_MAUVILLE_ADMINS counts them (0-4), and a trigger just before
@      each starts the fight. The player uses the SCRAMBLER before each, so a
@      beaten guard stays beaten; each leaves, a charging coil heals the
@      party, and the held items come back (EventScript_RestoreStoryHeldItems),
@      win or white-out.
@      At the generator MAXIE and ARCHIE guard it together and are fought back
@      to back: both speak, the RIVAL runs in from off screen along row 5 to
@      stand behind the player, MAXIE is fought, the RIVAL patches the party
@      up, then ARCHIE. A trigger column at x 29 or a talk starts the
@      scene. A loss in either fight whites out to MAUVILLE's
@      POKEMON CENTER, and the whole pair is fought again: OnTransition
@      clears MAXIE's trainer flag in state 13 (ARCHIE's is only set together
@      with state 14).
@   14 the CROWN is supercharged; MAXIE and ARCHIE are gone
@ FLAG_TEMP_1-4 the admins (TABITHA, COURTNEY, MATT, SHELLY), 5 the RIVAL
@ (absent until the generator scene adds her/him), 6 MAXIE and ARCHIE at the
@ generator (shown together in state 13).
@ ============================================================================

NewMauville_Inside_EventScript_SetupEndgame::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	call Common_EventScript_SetupRivalGfxId
	goto_if_ne VAR_ENDGAME_STATE, 13, Common_EventScript_NopReturn
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	clearflag FLAG_TEMP_6
	@ A MAXIE win that wasn't followed by an ARCHIE win is forgotten: both
	@ are fought again.
	cleartrainerflag TRAINER_NEW_MAUVILLE_MAXIE
	checktrainerflag TRAINER_NEW_MAUVILLE_TABITHA
	call_if FALSE, NewMauville_Inside_EventScript_ShowTabitha
	checktrainerflag TRAINER_NEW_MAUVILLE_COURTNEY
	call_if FALSE, NewMauville_Inside_EventScript_ShowCourtney
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

NewMauville_Inside_EventScript_MattTrigger::
	lockall
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_MATT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto NewMauville_Inside_EventScript_MattFight

NewMauville_Inside_EventScript_Matt::
	lockall
	faceplayer
	goto_if_ne VAR_NEW_MAUVILLE_ADMINS, 2, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_MattFight

NewMauville_Inside_EventScript_MattFight::
	msgbox NewMauville_Inside_Text_Matt, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_MATT, NewMauville_Inside_Text_MattDefeat
	msgbox NewMauville_Inside_Text_MattAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 3
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
	goto_if_ne VAR_NEW_MAUVILLE_ADMINS, 3, NewMauville_Inside_EventScript_NotYet
	goto NewMauville_Inside_EventScript_ShellyFight

NewMauville_Inside_EventScript_ShellyFight::
	msgbox NewMauville_Inside_Text_Shelly, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_SHELLY, NewMauville_Inside_Text_ShellyDefeat
	msgbox NewMauville_Inside_Text_ShellyAfter, MSGBOX_DEFAULT
	setvar VAR_NEW_MAUVILLE_ADMINS, 4
	goto NewMauville_Inside_EventScript_GuardLeaves

NewMauville_Inside_EventScript_NotYet::
	msgbox NewMauville_Inside_Text_NotYet, MSGBOX_DEFAULT
	releaseall
	end

@ Shared by all four. VAR_LAST_TALKED is the guard just beaten.
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

@ MAXIE and ARCHIE stand at (33, 5) and (34, 5). Walking into the room (x 29)
@ or talking to either starts the same scene: both fights, back to back.
NewMauville_Inside_EventScript_GeneratorLeadersTrigger::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_NEW_MAUVILLE_MAXIE, Common_Movement_FaceLeft
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
	closemessage
	@ The RIVAL runs in along row 5 from off screen. From the x 29 trigger
	@ the RIVAL stops right behind the player; from a talk (any tile beside
	@ the leaders) the RIVAL stops at (31, 5).
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 29, NewMauville_Inside_EventScript_RivalRunsIn
	call_if_ne VAR_0x8004, 29, NewMauville_Inside_EventScript_RivalRunsInFar
	msgbox NewMauville_Inside_Text_RivalArrives, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_MaxieOrder, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_ArchieNoBreak, MSGBOX_DEFAULT
	msgbox NewMauville_Inside_Text_RivalGo, MSGBOX_DEFAULT
	@ MAXIE first. A loss ends the script here (white-out).
	call DevonFactory_EventScript_UseScrambler
	setvar VAR_LAST_TALKED, LOCALID_NEW_MAUVILLE_MAXIE
	trainerbattle_no_intro TRAINER_NEW_MAUVILLE_MAXIE, NewMauville_Inside_Text_MaxieDefeat
	msgbox NewMauville_Inside_Text_MaxieAfter, MSGBOX_DEFAULT
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	@ The RIVAL patches the party up.
	closemessage
	fadescreen FADE_TO_BLACK
	special HealPlayerParty
	fadescreen FADE_FROM_BLACK
	msgbox NewMauville_Inside_Text_RivalHealed, MSGBOX_DEFAULT
	@ Then ARCHIE.
	msgbox NewMauville_Inside_Text_ArchieNext, MSGBOX_DEFAULT
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
	msgbox NewMauville_Inside_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NEW_MAUVILLE_MAXIE
	removeobject LOCALID_NEW_MAUVILLE_ARCHIE
	removeobject LOCALID_NEW_MAUVILLE_RIVAL
	setflag FLAG_TEMP_5
	fadescreen FADE_FROM_BLACK
	msgbox NewMauville_Inside_Text_LeadersGone, MSGBOX_DEFAULT
	releaseall
	end

@ The RIVAL object is added to the map only here. It spawns at (20, 5), off
@ screen west of the barrier (column x 21 is down by now), runs east along
@ row 5 to (28, 5), then steps to the player's row (4-8) and ends one tile
@ left of the player, facing right.
NewMauville_Inside_EventScript_RivalRunsIn::
	setobjectxyperm LOCALID_NEW_MAUVILLE_RIVAL, 20, 5
	clearflag FLAG_TEMP_5
	addobject LOCALID_NEW_MAUVILLE_RIVAL
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, NewMauville_Inside_Movement_RivalRunsIn
	waitmovement 0
	call_if_eq VAR_0x8005, 4, NewMauville_Inside_EventScript_RivalToRow4
	call_if_eq VAR_0x8005, 5, NewMauville_Inside_EventScript_RivalToRow5
	call_if_eq VAR_0x8005, 6, NewMauville_Inside_EventScript_RivalToRow6
	call_if_eq VAR_0x8005, 7, NewMauville_Inside_EventScript_RivalToRow7
	call_if_eq VAR_0x8005, 8, NewMauville_Inside_EventScript_RivalToRow8
	return

NewMauville_Inside_EventScript_RivalToRow4::
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, NewMauville_Inside_Movement_RivalToRow4
	waitmovement 0
	return

NewMauville_Inside_EventScript_RivalToRow5::
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, Common_Movement_FaceRight
	waitmovement 0
	return

NewMauville_Inside_EventScript_RivalToRow6::
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, NewMauville_Inside_Movement_RivalToRow6
	waitmovement 0
	return

NewMauville_Inside_EventScript_RivalToRow7::
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, NewMauville_Inside_Movement_RivalToRow7
	waitmovement 0
	return

NewMauville_Inside_EventScript_RivalToRow8::
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, NewMauville_Inside_Movement_RivalToRow8
	waitmovement 0
	return

@ From a talk the player stands at (32, 5), (35, 5), (33, 6) or (34, 6): the
@ RIVAL runs the whole of row 5 and stops at (31, 5), facing right.
NewMauville_Inside_EventScript_RivalRunsInFar::
	setobjectxyperm LOCALID_NEW_MAUVILLE_RIVAL, 20, 5
	clearflag FLAG_TEMP_5
	addobject LOCALID_NEW_MAUVILLE_RIVAL
	applymovement LOCALID_NEW_MAUVILLE_RIVAL, NewMauville_Inside_Movement_RivalRunsInFar
	waitmovement 0
	return

@ (20, 5) to (28, 5).
NewMauville_Inside_Movement_RivalRunsIn:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

@ (20, 5) to (31, 5).
NewMauville_Inside_Movement_RivalRunsInFar:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_right
	step_end

@ From (28, 5) to the player's row, beside the player at (29, y).
NewMauville_Inside_Movement_RivalToRow4:
	walk_fast_up
	face_right
	step_end

NewMauville_Inside_Movement_RivalToRow6:
	walk_fast_down
	face_right
	step_end

NewMauville_Inside_Movement_RivalToRow7:
	walk_fast_down
	walk_fast_down
	face_right
	step_end

NewMauville_Inside_Movement_RivalToRow8:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	face_right
	step_end

@ Only reachable if the scene is cut short; the RIVAL is normally gone.
NewMauville_Inside_EventScript_Rival::
	lock
	faceplayer
	msgbox NewMauville_Inside_Text_RivalTalk, MSGBOX_DEFAULT
	release
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
	.string "…The way beyond is AQUA's. MATT,\n"
	.string "then SHELLY. …They're loud.\l"
	.string "…But not weak.\p"
	.string "…Be careful. …That's all.$"

NewMauville_Inside_Text_MaxieDefeat:
	.string "Impossible… GROUDON's power…$"

NewMauville_Inside_Text_MaxieAfter:
	.string "MAXIE: …Hmph.\p"
	.string "ARCHIE. Show this child what\n"
	.string "KYOGRE is for.$"

NewMauville_Inside_Text_Matt:
	.string "MATT: Hah! So you're the one who\n"
	.string "walked through MAGMA's lot. Both\l"
	.string "TABITHA and COURTNEY!\p"
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
	.string "ahead. MAXIE and ARCHIE are\l"
	.string "waiting, the pair of them.\p"
	.string "Don't come crying to me.$"

NewMauville_Inside_Text_MaxieAtGenerator:
	.string "MAXIE: So. You've come through\n"
	.string "TABITHA, COURTNEY, MATT and SHELLY.\p"
	.string "SCOTT said you would. He also told\n"
	.string "me what to do about it.\p"
	.string "And he gave me what I always\n"
	.string "wanted. GROUDON is mine for good.$"

NewMauville_Inside_Text_Archie1:
	.string "ARCHIE: Hah! Two of us, one\n"
	.string "generator, kid!\p"
	.string "KYOGRE is mine for keeps. Neither\n"
	.string "of us is handing ours back!$"

NewMauville_Inside_Text_RivalArrives:
	.string "{RIVAL}: {PLAYER}!… Phew… I found\n"
	.string "the way down!\p"
	.string "I'm not leaving you alone with\n"
	.string "these two.$"

NewMauville_Inside_Text_MaxieOrder:
	.string "MAXIE: Your friend may watch, child.\p"
	.string "This is done one at a time, and I\n"
	.string "am first.$"

NewMauville_Inside_Text_ArchieNoBreak:
	.string "ARCHIE: And the moment he's done,\n"
	.string "it's me. No break in between, kid!$"

NewMauville_Inside_Text_RivalGo:
	.string "{RIVAL}: Go, {PLAYER}! The second the\n"
	.string "first one is down, I'll patch\l"
	.string "everyone up!$"

NewMauville_Inside_Text_RivalHealed:
	.string "{RIVAL} patched up {PLAYER}'s\n"
	.string "POKéMON.\p"
	.string "{RIVAL}: That's everyone.\n"
	.string "One more, {PLAYER}!$"

NewMauville_Inside_Text_ArchieNext:
	.string "ARCHIE: My turn. Let's see how long\n"
	.string "you last against the sea, kid!$"

NewMauville_Inside_Text_RivalTalk:
	.string "{RIVAL}: I'm right behind you,\n"
	.string "{PLAYER}. Go!$"

NewMauville_Inside_Text_RivalAfter:
	.string "{RIVAL}: It's over… I'll wait for you\n"
	.string "up top.\p"
	.string "Don't be long, okay?$"

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
