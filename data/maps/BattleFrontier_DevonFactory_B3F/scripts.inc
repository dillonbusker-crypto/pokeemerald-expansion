BattleFrontier_DevonFactory_B3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_DevonFactory_B3F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_DevonFactory_B3F_OnFrame
	.byte 0

@ ============================================================================
@ Ten Gauntlets: the Pillar Chamber (storyline.md, "After gauntlet 8"). The
@ player and WALLACE come down the stairs together (B2F warps them in at
@ (2, 1)) and walk up to SCOTT at (8, 6), charging the CROWN at the PILLAR
@ with MEGA MEWTWO Y at (9, 6). MEWTWO beats WALLACE's PALKIA; the player
@ steps in, and SCOTT's battle - meant to be lost, with no white-out
@ (B_FLAG_NO_WHITEOUT) - follows. Then SCOTT leaves, STEVEN arrives, and the
@ story picks up outside the Battle Arena (state 5).
@ ============================================================================

BattleFrontier_DevonFactory_B3F_OnTransition:
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	goto_if_ne VAR_ENDGAME_STATE, 4, BattleFrontier_DevonFactory_B3F_EventScript_OnTransitionEnd
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	setvar VAR_TEMP_1, 1
BattleFrontier_DevonFactory_B3F_EventScript_OnTransitionEnd:
	end

BattleFrontier_DevonFactory_B3F_OnFrame:
	map_script_2 VAR_TEMP_1, 1, BattleFrontier_DevonFactory_B3F_EventScript_PillarScene
	.2byte 0

BattleFrontier_DevonFactory_B3F_EventScript_PillarScene::
	lockall
	setvar VAR_TEMP_1, 0
	@ Down from the stairs to (8, 9), WALLACE beside at (9, 9).
	applymovement LOCALID_PLAYER, BattleFrontier_DevonFactory_B3F_Movement_PlayerIn
	applymovement LOCALID_DEVON_FACTORY_PILLAR_WALLACE, BattleFrontier_DevonFactory_B3F_Movement_WallaceIn
	waitmovement 0
	@ The CROWN reaches full power.
	playse SE_M_EXPLOSION
	fadescreen FADE_TO_WHITE
	delay 20
	fadescreen FADE_FROM_WHITE
	call BattleFrontier_DevonFactory_B3F_EventScript_Shake
	waitse
	playmoncry SPECIES_MEWTWO_MEGA_Y, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_DEVON_FACTORY_SCOTT, Common_Movement_FaceDown
	applymovement LOCALID_DEVON_FACTORY_MEWTWO, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_B3F_Text_Scott1, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B3F_Text_Wallace1, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B3F_Text_Scott2, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B3F_Text_Wallace2, MSGBOX_DEFAULT
	closemessage
	@ PALKIA against MEWTWO.
	playse SE_BALL_OPEN
	clearflag FLAG_TEMP_4
	addobject LOCALID_DEVON_FACTORY_PALKIA
	waitse
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottTakeHimOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_FACTORY_PALKIA, BattleFrontier_DevonFactory_B3F_Movement_LungeUp
	waitmovement 0
	playse SE_M_EXPLOSION
	call BattleFrontier_DevonFactory_B3F_EventScript_Shake
	waitse
	msgbox BattleFrontier_DevonFactory_B3F_Text_MewtwoShrugsItOff, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_FACTORY_MEWTWO, BattleFrontier_DevonFactory_B3F_Movement_LungeDown
	waitmovement 0
	playse SE_M_PSYBEAM
	fadescreen FADE_TO_BLACK
	playmoncry SPECIES_PALKIA, CRY_MODE_FAINT
	waitmoncry
	removeobject LOCALID_DEVON_FACTORY_PALKIA
	fadescreen FADE_FROM_BLACK
	waitse
	applymovement LOCALID_DEVON_FACTORY_PILLAR_WALLACE, BattleFrontier_DevonFactory_B3F_Movement_WallacePushedBack
	call BattleFrontier_DevonFactory_B3F_EventScript_Shake
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_B3F_Text_WallaceLost, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottFinishHim, MSGBOX_DEFAULT
	closemessage
	@ The player steps in front of WALLACE, to (9, 9).
	applymovement LOCALID_PLAYER, BattleFrontier_DevonFactory_B3F_Movement_PlayerStepsIn
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_B3F_Text_PlayerSteppedIn, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottSquash, MSGBOX_DEFAULT
	closemessage
	@ SCOTT's battle: the player's team stays fainted on a loss, no white-out.
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
	setflag FLAG_ENDGAME_NO_WHITEOUT
	@ Bad Dreams: a player who freed DARKRAI fights the teams with MAGEARNA in its place.
	goto_if_set FLAG_DARKRAI_FREED, BattleFrontier_DevonFactory_B3F_EventScript_BattleScottNoDarkrai
	call_if_set FLAG_STEVEN_HAS_LATIOS, BattleFrontier_DevonFactory_B3F_EventScript_BattleScottLatias
	call_if_unset FLAG_STEVEN_HAS_LATIOS, BattleFrontier_DevonFactory_B3F_EventScript_BattleScottLatios
BattleFrontier_DevonFactory_B3F_EventScript_ScottBattleDone::
	clearflag FLAG_ENDGAME_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_DevonFactory_B3F_EventScript_ScottBeaten
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottLeaves, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_OPEN
	removeobject LOCALID_DEVON_FACTORY_MEWTWO
	waitse
	applymovement LOCALID_DEVON_FACTORY_SCOTT, BattleFrontier_DevonFactory_B3F_Movement_ScottOut
	waitmovement 0
	removeobject LOCALID_DEVON_FACTORY_SCOTT
	@ STEVEN, from the stairs to (8, 9), beside the player.
	delay 30
	clearflag FLAG_TEMP_5
	addobject LOCALID_DEVON_FACTORY_PILLAR_STEVEN
	applymovement LOCALID_DEVON_FACTORY_PILLAR_STEVEN, BattleFrontier_DevonFactory_B3F_Movement_StevenIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_B3F_Text_Steven, MSGBOX_DEFAULT
	closemessage
	@ JOY sees to the team, and everyone regroups outside the Arena.
	fadescreen FADE_TO_BLACK
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	special HealPlayerParty
	setvar VAR_ENDGAME_STATE, 5
	warp MAP_BATTLE_FRONTIER_OUTSIDE_EAST, 39, 31
	waitstate
	releaseall
	end

@ He has the Lati the player didn't catch: FLAG_STEVEN_HAS_LATIOS means the
@ player's is a LATIOS.
BattleFrontier_DevonFactory_B3F_EventScript_BattleScottLatias::
	trainerbattle_no_intro TRAINER_FACTORY_SCOTT_LATIAS, BattleFrontier_DevonFactory_B3F_Text_ScottDefeat
	return

BattleFrontier_DevonFactory_B3F_EventScript_BattleScottLatios::
	trainerbattle_no_intro TRAINER_FACTORY_SCOTT_LATIOS, BattleFrontier_DevonFactory_B3F_Text_ScottDefeat
	return

@ DARKRAI is gone from SCOTT's team: he says so, then the same fight with
@ five. Falls back into the common tail above.
BattleFrontier_DevonFactory_B3F_EventScript_BattleScottNoDarkrai::
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottNoDarkrai, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_STEVEN_HAS_LATIOS, BattleFrontier_DevonFactory_B3F_EventScript_BattleScottNoDarkraiLatias
	call_if_unset FLAG_STEVEN_HAS_LATIOS, BattleFrontier_DevonFactory_B3F_EventScript_BattleScottNoDarkraiLatios
	goto BattleFrontier_DevonFactory_B3F_EventScript_ScottBattleDone

BattleFrontier_DevonFactory_B3F_EventScript_BattleScottNoDarkraiLatias::
	trainerbattle_no_intro TRAINER_FACTORY_SCOTT_NO_DARKRAI_LATIAS, BattleFrontier_DevonFactory_B3F_Text_ScottDefeat
	return

BattleFrontier_DevonFactory_B3F_EventScript_BattleScottNoDarkraiLatios::
	trainerbattle_no_intro TRAINER_FACTORY_SCOTT_NO_DARKRAI_LATIOS, BattleFrontier_DevonFactory_B3F_Text_ScottDefeat
	return

BattleFrontier_DevonFactory_B3F_EventScript_ScottBeaten::
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottBeaten, MSGBOX_DEFAULT
	return

BattleFrontier_DevonFactory_B3F_EventScript_Shake::
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12 @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	return

@ (2, 1) down to (2, 9), then right to (8, 9).
BattleFrontier_DevonFactory_B3F_Movement_PlayerIn:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

@ (3, 2) down to (3, 10), right to (9, 10), up to (9, 9).
BattleFrontier_DevonFactory_B3F_Movement_WallaceIn:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	face_up
	step_end

BattleFrontier_DevonFactory_B3F_Movement_LungeUp:
	walk_fast_up
	walk_fast_down
	face_up
	step_end

BattleFrontier_DevonFactory_B3F_Movement_LungeDown:
	walk_fast_down
	walk_fast_up
	face_down
	step_end

@ (9, 9) back to (9, 11): a tile clear of the player, who steps in at (9, 9).
BattleFrontier_DevonFactory_B3F_Movement_WallacePushedBack:
	lock_facing_direction
	walk_fast_down
	walk_fast_down
	unlock_facing_direction
	step_end

BattleFrontier_DevonFactory_B3F_Movement_PlayerStepsIn:
	walk_right
	face_up
	step_end

@ (8, 6) left to (2, 6), then up the stairs.
BattleFrontier_DevonFactory_B3F_Movement_ScottOut:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ (2, 2) down to (2, 9), right to (8, 9).
BattleFrontier_DevonFactory_B3F_Movement_StevenIn:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_right
	step_end

BattleFrontier_DevonFactory_B3F_EventScript_Pillar::
	msgbox BattleFrontier_DevonFactory_B3F_Text_Pillar, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_EventScript_PillarMachinery::
	msgbox BattleFrontier_DevonFactory_B3F_Text_PillarMachinery, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_EventScript_ScottPC::
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottPC, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_EventScript_CrownBlueprints::
	msgbox BattleFrontier_DevonFactory_B3F_Text_CrownBlueprints, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_Text_Pillar:
	.string "The MEGA PILLAR.\p"
	.string "It thrums with the bonds of\n"
	.string "thousands of trainers.$"

BattleFrontier_DevonFactory_B3F_Text_PillarMachinery:
	.string "Cables as thick as an arm run from\n"
	.string "the machine into the PILLAR.$"

BattleFrontier_DevonFactory_B3F_Text_ScottPC:
	.string "SCOTT's PC. A single file is open:\p"
	.string "“CROWN - FINAL STAGE.”$"

BattleFrontier_DevonFactory_B3F_Text_CrownBlueprints:
	.string "Blueprints for the CROWN, covered\n"
	.string "in DEVON's logo.$"

BattleFrontier_DevonFactory_B3F_Text_Scott1:
	.string "SCOTT: You're too late. Both of you.\p"
	.string "The CROWN is charged. Every bond\n"
	.string "this island ever made, in one hand.\p"
	.string "Unlimited, permanent MEGA\n"
	.string "EVOLUTION. No KEY STONE. No\l"
	.string "partner. No limits.\p"
	.string "Why? You'll hear all of it soon\n"
	.string "enough. When it no longer matters.$"

BattleFrontier_DevonFactory_B3F_Text_Wallace1:
	.string "WALLACE: This ends here, SCOTT.$"

BattleFrontier_DevonFactory_B3F_Text_Scott2:
	.string "SCOTT: Does it? I did this to\n"
	.string "STEVEN. I'll gladly do it to you.$"

BattleFrontier_DevonFactory_B3F_Text_Wallace2:
	.string "WALLACE: I'm the CHAMPION of HOENN.\n"
	.string "It's my duty to try, whatever the\l"
	.string "odds.\p"
	.string "Go, PALKIA!$"

BattleFrontier_DevonFactory_B3F_Text_ScottTakeHimOut:
	.string "SCOTT: MEWTWO. Take him out.\p"
	.string "WALLACE: PALKIA, Spacial Rend!$"

BattleFrontier_DevonFactory_B3F_Text_MewtwoShrugsItOff:
	.string "MEGA MEWTWO Y shrugged it off!\p"
	.string "SCOTT: MEWTWO, Psystrike.$"

BattleFrontier_DevonFactory_B3F_Text_WallaceLost:
	.string "WALLACE: PALKIA… I lost.\p"
	.string "I've failed as CHAMPION…$"

BattleFrontier_DevonFactory_B3F_Text_ScottFinishHim:
	.string "SCOTT: MEWTWO. Finish him.$"

BattleFrontier_DevonFactory_B3F_Text_PlayerSteppedIn:
	.string "{PLAYER} stepped in front of\n"
	.string "WALLACE!$"

BattleFrontier_DevonFactory_B3F_Text_ScottSquash:
	.string "SCOTT: You? Out of the way.\p"
	.string "…No? I told your father once that\n"
	.string "I'd squash him.\p"
	.string "I don't need you anymore, kid.\n"
	.string "MEWTWO, squash them.$"

BattleFrontier_DevonFactory_B3F_Text_ScottNoDarkrai:
	.string "SCOTT: Someone cut my DARKRAI loose\n"
	.string "while I was away.\p"
	.string "It doesn't matter.$"

BattleFrontier_DevonFactory_B3F_Text_ScottDefeat:
	.string "…Interesting.$"

BattleFrontier_DevonFactory_B3F_Text_ScottBeaten:
	.string "SCOTT: Impressive. It changes\n"
	.string "nothing.$"

BattleFrontier_DevonFactory_B3F_Text_ScottLeaves:
	.string "SCOTT: This is wasting my time.\p"
	.string "I have places to be. When I'm done,\n"
	.string "I'll be the most powerful trainer\l"
	.string "who ever lived.$"

BattleFrontier_DevonFactory_B3F_Text_Steven:
	.string "STEVEN: WALLACE! {PLAYER}!\p"
	.string "SCOTT walked right past me on the\n"
	.string "stairs, with his BRAINS behind him.\l"
	.string "I'm too late, aren't I?\p"
	.string "There's more. The ELITE FOUR are\n"
	.string "guarding DEVON, for some reason.\l"
	.string "We need to find out why.\p"
	.string "But first, let's get you both out\n"
	.string "of here.$"
