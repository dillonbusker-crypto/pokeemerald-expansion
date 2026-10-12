IslandCave_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, IslandCave_OnResume
	map_script MAP_SCRIPT_ON_LOAD, IslandCave_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, IslandCave_OnTransition
	.byte 0

IslandCave_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, IslandCave_EventScript_TryRemoveRegice
	end

IslandCave_EventScript_TryRemoveRegice::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

IslandCave_OnLoad:
	call_if_unset FLAG_SYS_BRAILLE_REGICE_COMPLETED, IslandCave_EventScript_HideRegiEntrance
	end

IslandCave_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

IslandCave_OnTransition:
	setflag FLAG_LANDMARK_ISLAND_CAVE
	call IslandCave_EventScript_ClearSteps
	call_if_unset FLAG_DEFEATED_REGICE, IslandCave_EventScript_ShowRegice
	call IslandCave_EventScript_SetupHoopaTrip
	end

IslandCave_EventScript_ShowRegice::
	clearflag FLAG_HIDE_REGICE
	return

IslandCave_EventScript_OpenRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 8, 19, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 19, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 9, 20, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	playse SE_BANG
	setflag FLAG_SYS_BRAILLE_REGICE_COMPLETED
	end

IslandCave_EventScript_CaveEntranceMiddle::
	lockall
	call_if_set FLAG_TEMP_REGICE_PUZZLE_FAILED, IslandCave_EventScript_ClearSteps
	goto_if_set FLAG_SYS_BRAILLE_REGICE_COMPLETED, IslandCave_EventScript_BigHoleInWall
	braillemessage IslandCave_Braille_RunLapAroundWall
	setflag FLAG_TEMP_REGICE_PUZZLE_STARTED
	special ShouldDoBrailleRegicePuzzle
	goto IslandCave_EventScript_CloseBrailleMsg
	end

IslandCave_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

IslandCave_EventScript_CaveEntranceSide::
	lockall
	call_if_set FLAG_TEMP_REGICE_PUZZLE_FAILED, IslandCave_EventScript_ClearSteps
	braillemessage IslandCave_Braille_RunLapAroundWall
	goto_if_set FLAG_SYS_BRAILLE_REGICE_COMPLETED, IslandCave_EventScript_CloseBrailleMsg
	setflag FLAG_TEMP_REGICE_PUZZLE_STARTED
	special ShouldDoBrailleRegicePuzzle
	goto IslandCave_EventScript_CloseBrailleMsg
	end

IslandCave_EventScript_CloseBrailleMsg::
	waitbuttonpress
	closebraillemessage
	releaseall
	end

IslandCave_EventScript_ClearSteps::
	setvar VAR_REGICE_STEPS_1, 0
	setvar VAR_REGICE_STEPS_2, 0
	setvar VAR_REGICE_STEPS_3, 0
	clearflag FLAG_TEMP_REGICE_PUZZLE_FAILED
	return

IslandCave_EventScript_Regice::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGICE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGICE, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, IslandCave_EventScript_DefeatedRegice
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, IslandCave_EventScript_RanFromRegice
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, IslandCave_EventScript_RanFromRegice
	setflag FLAG_DEFEATED_REGICE
	release
	end

IslandCave_EventScript_DefeatedRegice::
	setflag FLAG_DEFEATED_REGICE
	goto Common_EventScript_RemoveStaticPokemon
	end

IslandCave_EventScript_RanFromRegice::
	setvar VAR_0x8004, SPECIES_REGICE
	goto Common_EventScript_LegendaryFlewAway
	end

@ ============================================================================
@ Ten Gauntlets: HOOPA's rings (storyline.md). HOOPA in the Arena sends the
@ player here, to the sealed chamber, with VAR_HOOPA_TARGET set to the
@ legendary they chose. Regice is hidden; the legendary (OBJ_EVENT_GFX_VAR_0)
@ waits at (8, 7) and HOOPA blocks the way out at (8, 11). The legendary is
@ level 60 and, met here, isn't chipped (IsFrontierChippedMon), so it grows.
@ Caught: the ring is used up. Knocked out or escaped: it flees, and the
@ player can come back for it. Either way HOOPA takes them back.
@ ============================================================================

IslandCave_EventScript_SetupHoopaTrip::
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	goto_if_eq VAR_HOOPA_TARGET, 0, Common_EventScript_NopReturn
	setflag FLAG_HIDE_REGICE
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_6
	call_if_eq VAR_HOOPA_TARGET, SPECIES_MIRAIDON, IslandCave_EventScript_GfxMiraidon
	call_if_eq VAR_HOOPA_TARGET, SPECIES_XERNEAS, IslandCave_EventScript_GfxXerneas
	call_if_eq VAR_HOOPA_TARGET, SPECIES_YVELTAL, IslandCave_EventScript_GfxYveltal
	call_if_eq VAR_HOOPA_TARGET, SPECIES_ZACIAN, IslandCave_EventScript_GfxZacian
	call_if_eq VAR_HOOPA_TARGET, SPECIES_HO_OH, IslandCave_EventScript_GfxHoOh
	call_if_eq VAR_HOOPA_TARGET, SPECIES_LUGIA, IslandCave_EventScript_GfxLugia
	call_if_eq VAR_HOOPA_TARGET, SPECIES_RESHIRAM, IslandCave_EventScript_GfxReshiram
	call_if_eq VAR_HOOPA_TARGET, SPECIES_ZEKROM, IslandCave_EventScript_GfxZekrom
	call_if_eq VAR_HOOPA_TARGET, SPECIES_SOLGALEO, IslandCave_EventScript_GfxSolgaleo
	call_if_eq VAR_HOOPA_TARGET, SPECIES_LUNALA, IslandCave_EventScript_GfxLunala
	call_if_eq VAR_HOOPA_TARGET, SPECIES_NECROZMA_DUSK_MANE, IslandCave_EventScript_GfxNecrozmaDuskMane
	call_if_eq VAR_HOOPA_TARGET, SPECIES_NECROZMA_DAWN_WINGS, IslandCave_EventScript_GfxNecrozmaDawnWings
	return

IslandCave_EventScript_GfxMiraidon::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(MIRAIDON), warn=FALSE
	return

IslandCave_EventScript_GfxXerneas::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(XERNEAS), warn=FALSE
	return

IslandCave_EventScript_GfxYveltal::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(YVELTAL), warn=FALSE
	return

IslandCave_EventScript_GfxZacian::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(ZACIAN), warn=FALSE
	return

IslandCave_EventScript_GfxHoOh::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(HO_OH), warn=FALSE
	return

IslandCave_EventScript_GfxLugia::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(LUGIA), warn=FALSE
	return

IslandCave_EventScript_GfxReshiram::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(RESHIRAM), warn=FALSE
	return

IslandCave_EventScript_GfxZekrom::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(ZEKROM), warn=FALSE
	return

IslandCave_EventScript_GfxSolgaleo::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(SOLGALEO), warn=FALSE
	return

IslandCave_EventScript_GfxLunala::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(LUNALA), warn=FALSE
	return

IslandCave_EventScript_GfxNecrozmaDuskMane::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(NECROZMA_DUSK_MANE), warn=FALSE
	return

IslandCave_EventScript_GfxNecrozmaDawnWings::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(NECROZMA_DAWN_WINGS), warn=FALSE
	return

IslandCave_EventScript_HoopaLegendary::
	lock
	faceplayer
	copyvar VAR_0x8004, VAR_HOOPA_TARGET
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	waitmoncry
	call_if_eq VAR_HOOPA_TARGET, SPECIES_MIRAIDON, IslandCave_EventScript_BattleMiraidon
	call_if_eq VAR_HOOPA_TARGET, SPECIES_XERNEAS, IslandCave_EventScript_BattleXerneas
	call_if_eq VAR_HOOPA_TARGET, SPECIES_YVELTAL, IslandCave_EventScript_BattleYveltal
	call_if_eq VAR_HOOPA_TARGET, SPECIES_ZACIAN, IslandCave_EventScript_BattleZacian
	call_if_eq VAR_HOOPA_TARGET, SPECIES_HO_OH, IslandCave_EventScript_BattleHoOh
	call_if_eq VAR_HOOPA_TARGET, SPECIES_LUGIA, IslandCave_EventScript_BattleLugia
	call_if_eq VAR_HOOPA_TARGET, SPECIES_RESHIRAM, IslandCave_EventScript_BattleReshiram
	call_if_eq VAR_HOOPA_TARGET, SPECIES_ZEKROM, IslandCave_EventScript_BattleZekrom
	call_if_eq VAR_HOOPA_TARGET, SPECIES_SOLGALEO, IslandCave_EventScript_BattleSolgaleo
	call_if_eq VAR_HOOPA_TARGET, SPECIES_LUNALA, IslandCave_EventScript_BattleLunala
	call_if_eq VAR_HOOPA_TARGET, SPECIES_NECROZMA_DUSK_MANE, IslandCave_EventScript_BattleNecrozmaDuskMane
	call_if_eq VAR_HOOPA_TARGET, SPECIES_NECROZMA_DAWN_WINGS, IslandCave_EventScript_BattleNecrozmaDawnWings
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, IslandCave_EventScript_HoopaCaught
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ISLAND_CAVE_LEGENDARY
	fadescreen FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_HOOPA_TARGET
	msgbox IslandCave_Text_LegendaryFled, MSGBOX_DEFAULT
	goto IslandCave_EventScript_HoopaTakesBack

IslandCave_EventScript_BattleMiraidon::
	setwildbattle SPECIES_MIRAIDON, 60
	return

IslandCave_EventScript_BattleXerneas::
	setwildbattle SPECIES_XERNEAS, 60
	return

IslandCave_EventScript_BattleYveltal::
	setwildbattle SPECIES_YVELTAL, 60
	return

IslandCave_EventScript_BattleZacian::
	setwildbattle SPECIES_ZACIAN, 60, ITEM_RUSTED_SWORD
	return

IslandCave_EventScript_BattleHoOh::
	setwildbattle SPECIES_HO_OH, 60
	return

IslandCave_EventScript_BattleLugia::
	setwildbattle SPECIES_LUGIA, 60
	return

IslandCave_EventScript_BattleReshiram::
	setwildbattle SPECIES_RESHIRAM, 60
	return

IslandCave_EventScript_BattleZekrom::
	setwildbattle SPECIES_ZEKROM, 60
	return

IslandCave_EventScript_BattleSolgaleo::
	setwildbattle SPECIES_SOLGALEO, 60
	return

IslandCave_EventScript_BattleLunala::
	setwildbattle SPECIES_LUNALA, 60
	return

IslandCave_EventScript_BattleNecrozmaDuskMane::
	setwildbattle SPECIES_NECROZMA_DUSK_MANE, 60
	return

IslandCave_EventScript_BattleNecrozmaDawnWings::
	setwildbattle SPECIES_NECROZMA_DAWN_WINGS, 60
	return

IslandCave_EventScript_HoopaCaught::
	call_if_eq VAR_HOOPA_TARGET, SPECIES_MIRAIDON, IslandCave_EventScript_CaughtMiraidon
	call_if_eq VAR_HOOPA_TARGET, SPECIES_XERNEAS, IslandCave_EventScript_CaughtXerneas
	call_if_eq VAR_HOOPA_TARGET, SPECIES_YVELTAL, IslandCave_EventScript_CaughtYveltal
	call_if_eq VAR_HOOPA_TARGET, SPECIES_ZACIAN, IslandCave_EventScript_CaughtZacian
	call_if_eq VAR_HOOPA_TARGET, SPECIES_HO_OH, IslandCave_EventScript_CaughtHoOh
	call_if_eq VAR_HOOPA_TARGET, SPECIES_LUGIA, IslandCave_EventScript_CaughtLugia
	call_if_eq VAR_HOOPA_TARGET, SPECIES_RESHIRAM, IslandCave_EventScript_CaughtReshiram
	call_if_eq VAR_HOOPA_TARGET, SPECIES_ZEKROM, IslandCave_EventScript_CaughtZekrom
	call_if_eq VAR_HOOPA_TARGET, SPECIES_SOLGALEO, IslandCave_EventScript_CaughtSolgaleo
	call_if_eq VAR_HOOPA_TARGET, SPECIES_LUNALA, IslandCave_EventScript_CaughtLunala
	call_if_eq VAR_HOOPA_TARGET, SPECIES_NECROZMA_DUSK_MANE, IslandCave_EventScript_CaughtNecrozmaDuskMane
	call_if_eq VAR_HOOPA_TARGET, SPECIES_NECROZMA_DAWN_WINGS, IslandCave_EventScript_CaughtNecrozmaDawnWings
	addvar VAR_HOOPA_CATCHES, 1
	copyvar VAR_HOOPA_REST_STATE, VAR_ENDGAME_STATE
	msgbox IslandCave_Text_HoopaRecharge, MSGBOX_DEFAULT
	goto IslandCave_EventScript_HoopaTakesBack

IslandCave_EventScript_CaughtMiraidon::
	setflag FLAG_HOOPA_CAUGHT_MIRAIDON
	return

IslandCave_EventScript_CaughtXerneas::
	setflag FLAG_HOOPA_CAUGHT_XERNEAS
	return

IslandCave_EventScript_CaughtYveltal::
	setflag FLAG_HOOPA_CAUGHT_YVELTAL
	return

IslandCave_EventScript_CaughtZacian::
	setflag FLAG_HOOPA_CAUGHT_ZACIAN
	return

IslandCave_EventScript_CaughtHoOh::
	setflag FLAG_HOOPA_CAUGHT_HO_OH
	return

IslandCave_EventScript_CaughtLugia::
	setflag FLAG_HOOPA_CAUGHT_LUGIA
	return

IslandCave_EventScript_CaughtReshiram::
	setflag FLAG_HOOPA_CAUGHT_RESHIRAM
	return

IslandCave_EventScript_CaughtZekrom::
	setflag FLAG_HOOPA_CAUGHT_ZEKROM
	return

IslandCave_EventScript_CaughtSolgaleo::
	setflag FLAG_HOOPA_CAUGHT_SOLGALEO
	return

IslandCave_EventScript_CaughtLunala::
	setflag FLAG_HOOPA_CAUGHT_LUNALA
	return

IslandCave_EventScript_CaughtNecrozmaDuskMane::
	setflag FLAG_HOOPA_CAUGHT_NECROZMA_DUSK_MANE
	return

IslandCave_EventScript_CaughtNecrozmaDawnWings::
	setflag FLAG_HOOPA_CAUGHT_NECROZMA_DAWN_WINGS
	return

IslandCave_EventScript_CaveHoopa::
	lock
	faceplayer
	playmoncry SPECIES_HOOPA, CRY_MODE_NORMAL
	waitmoncry
	msgbox IslandCave_Text_HoopaGoBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, IslandCave_EventScript_HoopaTakesBack
	release
	end

IslandCave_EventScript_HoopaTakesBack::
	closemessage
	setvar VAR_HOOPA_TARGET, 0
	playse SE_M_TELEPORT
	warpteleport MAP_BATTLE_FRONTIER_BATTLE_ARENA_LOBBY, 11, 10
	waitstate
	release
	end

IslandCave_Text_LegendaryFled:
	.string "{STR_VAR_1} fled!\p"
	.string "HOOPA can open the ring again\n"
	.string "another time.$"

IslandCave_Text_HoopaRecharge:
	.string "HOOPA looks tired. Its rings will\n"
	.string "need time to recharge.$"

IslandCave_Text_HoopaGoBack:
	.string "HOOPA is guarding the way out.\n"
	.string "Go back through the ring?$"
