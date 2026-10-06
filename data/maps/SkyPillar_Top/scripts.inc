SkyPillar_Top_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_Top_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Top_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SkyPillar_Top_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyPillar_Top_OnFrame
	.byte 0

SkyPillar_Top_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SkyPillar_Top_EventScript_TryRemoveRayquaza
	end

SkyPillar_Top_EventScript_TryRemoveRayquaza::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SkyPillar_Top_OnTransition:
	@ Ten Gauntlets: no wild RAYQUAZA here, whatever way the player came in
	@ (see SkyPillar_Outside_OnTransition), and the smooth floor always. The
	@ vanilla awakening trigger is switched off.
	setvar VAR_SKY_PILLAR_STATE, 2
	setflag FLAG_DEFEATED_RAYQUAZA
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	setmaplayoutindex LAYOUT_SKY_PILLAR_TOP_CLEAN
	@ The final scene (VAR_ENDGAME_STATE 17): TEMP_1 hides SCOTT's RAYQUAZA,
	@ TEMP_2 SCOTT, TEMP_3 STEVEN and LOOKER. SCOTT waits at the top from
	@ state 17 on; the catch scene plays until FLAG_SKY_PILLAR_RAYQUAZA_CAUGHT
	@ is set, and never again after a loss.
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	call_if_eq VAR_ENDGAME_STATE, 17, SkyPillar_Top_EventScript_SetupFinalScene
	end

SkyPillar_Top_EventScript_SetupFinalScene::
	clearflag FLAG_TEMP_2
	call_if_unset FLAG_SKY_PILLAR_RAYQUAZA_CAUGHT, SkyPillar_Top_EventScript_SetupCatchScene
	return

SkyPillar_Top_EventScript_SetupCatchScene::
	clearflag FLAG_TEMP_1
	setvar VAR_TEMP_1, 1
	return

SkyPillar_Top_EventScript_SetCleanLayout::
	setmaplayoutindex LAYOUT_SKY_PILLAR_TOP_CLEAN
	setobjectmovementtype LOCALID_RAYQUAZA_SLEEPING, MOVEMENT_TYPE_FACE_DOWN
	return

SkyPillar_Top_EventScript_TryShowRayquaza::
	call_if_unset FLAG_DEFEATED_RAYQUAZA, SkyPillar_Top_EventScript_ShowRayquaza
	return

SkyPillar_Top_EventScript_ShowRayquaza::
	clearflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL
	return

SkyPillar_Top_OnWarp:
	map_script_2 VAR_SKY_PILLAR_STATE, 0, SkyPillar_Top_EventScript_RayquazaFaceDown
	.2byte 0

SkyPillar_Top_EventScript_RayquazaFaceDown::
	turnobject LOCALID_RAYQUAZA_SLEEPING, DIR_SOUTH
	end

SkyPillar_Top_EventScript_Rayquaza::
	lockall
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RAYQUAZA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SkyPillar_Top_EventScript_DefeatedRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SkyPillar_Top_EventScript_RanFromRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SkyPillar_Top_EventScript_RanFromRayquaza
	setflag FLAG_DEFEATED_RAYQUAZA
	releaseall
	end

SkyPillar_Top_EventScript_DefeatedRayquaza::
	setflag FLAG_DEFEATED_RAYQUAZA
	goto SkyPillar_Top_EventScript_DefeatedRayquaza2
	end

SkyPillar_Top_EventScript_RanFromRayquaza::
	setvar VAR_0x8004, SPECIES_RAYQUAZA
	goto SkyPillar_Top_EventScript_RanFromRayquaza2
	end

SkyPillar_Top_EventScript_DefeatedRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Top_EventScript_RanFromRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	releaseall
	end

SkyPillar_Top_EventScript_AwakenRayquaza::
	lockall
	fadeoutbgm 1
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaStir
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_RAYQUAZA_SLEEPING
	msgbox SkyPillar_Top_Text_RayquazaFlewOff, MSGBOX_DEFAULT
	closemessage
	delay 20
	fadeinbgm 1
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	releaseall
	end

@ Rayquaza has unusual movement frames
@ See comments, or sAnimTable_Rayquaza
SkyPillar_Top_Movement_RayquazaStir:
	delay_16
	walk_in_place_fast_left  @ Coiled, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left  @ Coiled, mouth open
	delay_16
	walk_in_place_right  @ Normal, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

SkyPillar_Top_Movement_RayquazaFlyOff:
	delay_16
	walk_in_place_down  @ Coiled, asleep
	delay_8
	walk_in_place_right  @ Normal, awake
	delay_8
	walk_faster_up  @ Fly up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SkyPillar_Top_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

SkyPillar_Top_Movement_CameraPanDown:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

SkyPillar_Top_Text_RayquazaFlewOff:
	.string "The awakened RAYQUAZA flew off…$"


@ ============================================================================
@ Ten Gauntlets: SCOTT at the top of SKY PILLAR (storyline.md, "Sky Pillar" and
@ "The final battle"). VAR_ENDGAME_STATE 17 on arrival: the player is walked
@ up the path to (14, 10), SCOTT throws a MASTER BALL at RAYQUAZA and catches
@ it, switches on the SCRAMBLER and fights (TRAINER_SKY_PILLAR_SCOTT_*; a loss
@ whites out to NURSE JOY, SkyPillar_Outside). After a loss the catch never
@ replays (FLAG_SKY_PILLAR_RAYQUAZA_CAUGHT): SCOTT waits and the battle starts
@ again on talk. A win: LOOKER and STEVEN arrive, SCOTT is arrested, state 18,
@ then the credits (EndgameClear: a plain save, no Hall of Fame, and the game
@ continues at the BATTLE FRONTIER).
@ ============================================================================

SkyPillar_Top_OnFrame:
	map_script_2 VAR_TEMP_1, 1, SkyPillar_Top_EventScript_CatchScene
	.2byte 0

SkyPillar_Top_EventScript_CatchScene::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_PLAYER, SkyPillar_Top_Movement_PlayerWalksUp
	waitmovement 0
	applymovement LOCALID_SKY_PILLAR_TOP_SCOTT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SkyPillar_Top_Text_ScottRayquaza, MSGBOX_DEFAULT
	closemessage
	@ The MASTER BALL.
	playse SE_BALL_THROW
	delay 30
	playse SE_BALL_OPEN
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_SKY_PILLAR_TOP_RAYQUAZA
	delay 10
	fadescreen FADE_FROM_WHITE
	waitse
	delay 20
	playse SE_BALL
	delay 40
	playse SE_BALL
	delay 40
	playse SE_BALL
	delay 40
	playse SE_SUCCESS
	playfanfare MUS_CAUGHT
	message SkyPillar_Top_Text_ScottCaught
	waitmessage
	waitfanfare
	waitbuttonpress
	setflag FLAG_SKY_PILLAR_RAYQUAZA_CAUGHT
	applymovement LOCALID_SKY_PILLAR_TOP_SCOTT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SkyPillar_Top_Text_ScottTurns, MSGBOX_DEFAULT
	@ Bad Dreams: he's a POKéMON short, and says so (once; not after a loss).
	call_if_set FLAG_DARKRAI_FREED, SkyPillar_Top_EventScript_ScottOneShort
	goto SkyPillar_Top_EventScript_ScottBattle
	end

@ After a loss: SCOTT waits where he was.
SkyPillar_Top_EventScript_Scott::
	lockall
	faceplayer
	msgbox SkyPillar_Top_Text_ScottAgain, MSGBOX_DEFAULT
	goto SkyPillar_Top_EventScript_ScottBattle
	end

SkyPillar_Top_EventScript_ScottBattle::
	@ The SCRAMBLER, as in the Factory: no heal between battles, and the held
	@ items come back (EventScript_RestoreStoryHeldItems) after a loss too.
	closemessage
	playse SE_PC_OFF
	msgbox SkyPillar_Top_Text_ScottScrambler, MSGBOX_DEFAULT
	waitse
	closemessage
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
	@ He has the Lati the player didn't catch: FLAG_STEVEN_HAS_LATIOS means the
	@ player's is a LATIOS. A loss is a normal white-out (to NURSE JOY), so
	@ nothing below this runs then.
	@ Bad Dreams: a player who freed DARKRAI fights the five-Pokemon teams.
	goto_if_set FLAG_DARKRAI_FREED, SkyPillar_Top_EventScript_BattleScottNoDarkrai
	call_if_set FLAG_STEVEN_HAS_LATIOS, SkyPillar_Top_EventScript_BattleScottLatias
	call_if_unset FLAG_STEVEN_HAS_LATIOS, SkyPillar_Top_EventScript_BattleScottLatios
SkyPillar_Top_EventScript_ScottBattleDone::
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	msgbox SkyPillar_Top_Text_ScottBeaten, MSGBOX_DEFAULT
	closemessage
	@ LOOKER and STEVEN come up the stairs.
	clearflag FLAG_TEMP_3
	addobject LOCALID_SKY_PILLAR_TOP_STEVEN
	addobject LOCALID_SKY_PILLAR_TOP_LOOKER
	applymovement LOCALID_SKY_PILLAR_TOP_STEVEN, SkyPillar_Top_Movement_StevenIn
	applymovement LOCALID_SKY_PILLAR_TOP_LOOKER, SkyPillar_Top_Movement_LookerIn
	waitmovement 0
	msgbox SkyPillar_Top_Text_StevenArrives, MSGBOX_DEFAULT
	msgbox SkyPillar_Top_Text_LookerArrests, MSGBOX_DEFAULT
	msgbox SkyPillar_Top_Text_ScottSilent, MSGBOX_DEFAULT
	msgbox SkyPillar_Top_Text_LookerCrown, MSGBOX_DEFAULT
	msgbox SkyPillar_Top_Text_StevenEnd, MSGBOX_DEFAULT
	closemessage
	@ The ending: the state is set before the save the credits start with.
	setvar VAR_ENDGAME_STATE, 18
	fadescreenspeed FADE_TO_BLACK, 24
	special EndgameClear
	waitstate
	end

SkyPillar_Top_EventScript_BattleScottLatias::
	trainerbattle_no_intro TRAINER_SKY_PILLAR_SCOTT_LATIAS, SkyPillar_Top_Text_ScottDefeat
	return

SkyPillar_Top_EventScript_BattleScottLatios::
	trainerbattle_no_intro TRAINER_SKY_PILLAR_SCOTT_LATIOS, SkyPillar_Top_Text_ScottDefeat
	return

SkyPillar_Top_EventScript_ScottOneShort::
	msgbox SkyPillar_Top_Text_ScottOneShort, MSGBOX_DEFAULT
	return

@ Falls back into the common tail above (ScottBattleDone).
SkyPillar_Top_EventScript_BattleScottNoDarkrai::
	call_if_set FLAG_STEVEN_HAS_LATIOS, SkyPillar_Top_EventScript_BattleScottNoDarkraiLatias
	call_if_unset FLAG_STEVEN_HAS_LATIOS, SkyPillar_Top_EventScript_BattleScottNoDarkraiLatios
	goto SkyPillar_Top_EventScript_ScottBattleDone

SkyPillar_Top_EventScript_BattleScottNoDarkraiLatias::
	trainerbattle_no_intro TRAINER_SKY_PILLAR_SCOTT_NO_DARKRAI_LATIAS, SkyPillar_Top_Text_ScottDefeatFive
	return

SkyPillar_Top_EventScript_BattleScottNoDarkraiLatios::
	trainerbattle_no_intro TRAINER_SKY_PILLAR_SCOTT_NO_DARKRAI_LATIOS, SkyPillar_Top_Text_ScottDefeatFive
	return

@ The stairs let the player out at (16, 15): left to (12, 15), up to (12, 11),
@ right to (14, 11) and up to (14, 10), below SCOTT at (14, 8).
SkyPillar_Top_Movement_PlayerWalksUp:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

SkyPillar_Top_Movement_StevenIn:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	face_up
	step_end

SkyPillar_Top_Movement_LookerIn:
	delay_16
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	face_up
	step_end

SkyPillar_Top_Text_ScottRayquaza:
	.string "SCOTT: RAYQUAZA. The sky's own\n"
	.string "weapon, asleep at the top of the\l"
	.string "world, and I'm the only one who\l"
	.string "ever climbed up to take it.\p"
	.string "The BALL in my house wasn't a\n"
	.string "replica, you know. It held MEWTWO.\p"
	.string "This one's from the same shipment\n"
	.string "out of KANTO.$"

SkyPillar_Top_Text_ScottCaught:
	.string "SCOTT caught RAYQUAZA!$"

SkyPillar_Top_Text_ScottTurns:
	.string "SCOTT: Hm. Hoenn's sky, in my\n"
	.string "hand.\p"
	.string "ARCHIE and MAXIE crawled back to\n"
	.string "tell me what happened in NEW\l"
	.string "MAUVILLE. Their PRIMALS were mine\l"
	.string "to take back, and I took them.\p"
	.string "I never needed a partner. I needed\n"
	.string "the strongest ones there are.\p"
	.string "Power doesn't need balance, kid.\n"
	.string "It needs to be bigger than yours.$"

SkyPillar_Top_Text_ScottOneShort:
	.string "SCOTT: I'm one short, thanks to\n"
	.string "whoever freed my DARKRAI.\p"
	.string "Five is plenty.$"

SkyPillar_Top_Text_ScottAgain:
	.string "SCOTT: Back for more?\p"
	.string "Fine. I don't tire of this.$"

SkyPillar_Top_Text_ScottScrambler:
	.string "SCOTT switched on the SCRAMBLER!\p"
	.string "Every POKéNAV nearby went dark.\p"
	.string "SCOTT: This is life or death.$"

SkyPillar_Top_Text_ScottDefeat:
	.string "…Six of the strongest POKéMON\n"
	.string "there are.$"

SkyPillar_Top_Text_ScottDefeatFive:
	.string "…Five of the strongest POKéMON\n"
	.string "there are.$"

SkyPillar_Top_Text_ScottBeaten:
	.string "SCOTT: …How?\p"
	.string "Every one of mine was stronger\n"
	.string "than yours. I made sure of it.\p"
	.string "I've watched teams my whole life.\n"
	.string "I thought I understood what made\l"
	.string "one win.\p"
	.string "I never understood a single one.$"

SkyPillar_Top_Text_StevenArrives:
	.string "STEVEN: It's over, SCOTT.\p"
	.string "{PLAYER}, are you all right?\n"
	.string "The BRAINS stood down the moment\l"
	.string "they felt RAYQUAZA's BALL go\l"
	.string "quiet. WALLACE, NORMAN and\l"
	.string "WATTSON are fine.$"

SkyPillar_Top_Text_LookerArrests:
	.string "LOOKER: I am LOOKER, of the\n"
	.string "International Police!\p"
	.string "SCOTT, Founder of the BATTLE\n"
	.string "FRONTIER. Kidnapping. Tampering\l"
	.string "with protected POKéMON. Seizing\l"
	.string "a whole region's trainers.\p"
	.string "You are under arrest!$"

SkyPillar_Top_Text_ScottSilent:
	.string "SCOTT didn't answer. He looked at\n"
	.string "his empty hands as if he'd never\l"
	.string "seen them before.$"

SkyPillar_Top_Text_LookerCrown:
	.string "LOOKER: And this is SCOTT's real\n"
	.string "CROWN. Evidence. It's confiscated.\p"
	.string "The REPLICA CROWN {PLAYER} carries\n"
	.string "was made to free the island, not\l"
	.string "to rule it. {PLAYER} keeps that.$"

SkyPillar_Top_Text_StevenEnd:
	.string "STEVEN: Let's go home.\p"
	.string "Everyone's waiting at the\n"
	.string "FRONTIER.$"
