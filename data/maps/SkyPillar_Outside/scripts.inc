SkyPillar_Outside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Outside_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SkyPillar_Outside_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SkyPillar_Outside_OnFrame
	.byte 0

SkyPillar_Outside_OnTransition:
	@ Ten Gauntlets: only reached in the endgame (data/scripts/endgame_towns.inc).
	@ RAYQUAZA never woke and flew to SOOTOPOLIS: no WALLACE here, and
	@ VAR_SKY_PILLAR_STATE 2 gives the cracked floors (the bike) without the
	@ awakening, which needs state 0. FLAG_DEFEATED_RAYQUAZA keeps the wild
	@ RAYQUAZA off the top floor; SCOTT's scene places its own.
	setflag FLAG_HIDE_SKY_PILLAR_WALLACE
	setvar VAR_SKY_PILLAR_STATE, 2
	setflag FLAG_DEFEATED_RAYQUAZA
	setflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA
	setflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL
	@ Ten Gauntlets: the endgame (VAR_ENDGAME_STATE, data/maps/BattleFrontier_
	@ OutsideEast/scripts.inc). TEMP_1 hides the allies, TEMP_2 the BRAINS and
	@ TEMP_3 NURSE JOY. State 16: the allies wait. From 17: JOY is here, and
	@ she's where the player wakes up after losing to SCOTT.
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	call_if_eq VAR_ENDGAME_STATE, 16, SkyPillar_Outside_EventScript_ShowAllies
	call_if_ge VAR_ENDGAME_STATE, 17, SkyPillar_Outside_EventScript_JoyHere
	call_if_eq VAR_SOOTOPOLIS_CITY_STATE, 3, SkyPillar_Outside_EventScript_HideMapNamePopup
	call_if_ge VAR_SOOTOPOLIS_CITY_STATE, 4, SkyPillar_Outside_EventScript_CheckSetAbnormalWeather
	end

SkyPillar_Outside_EventScript_ShowAllies::
	clearflag FLAG_TEMP_1
	return

SkyPillar_Outside_EventScript_JoyHere::
	clearflag FLAG_TEMP_3
	setrespawn HEAL_LOCATION_SKY_PILLAR_OUTSIDE
	return

SkyPillar_Outside_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

SkyPillar_Outside_EventScript_CheckSetAbnormalWeather::
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	return

SkyPillar_Outside_OnLoad:
	@ Ten Gauntlets: the door is always open (the vanilla game waits for
	@ WALLACE to open it).
	call SkyPillar_Outside_EventScript_OpenDoor
	end

SkyPillar_Outside_EventScript_OpenDoor::
	setmetatile 14, 4, METATILE_Pacifidlog_SkyPillar_DoorOpen_Top, FALSE
	setmetatile 14, 5, METATILE_Pacifidlog_SkyPillar_DoorOpen_Bottom, FALSE
	return

SkyPillar_Outside_OnFrame:
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 3, SkyPillar_Outside_EventScript_WallaceScene
	map_script_2 VAR_ENDGAME_STATE, 16, SkyPillar_Outside_EventScript_AmbushScene
	.2byte 0

SkyPillar_Outside_EventScript_WallaceScene::
	lockall
	applymovement LOCALID_SKY_PILLAR_WALLACE, SkyPillar_Outside_Movement_WallaceApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SkyPillar_Outside_Text_OpenedDoorToSkyPillar, MSGBOX_DEFAULT
	closemessage
	delay 30
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	delay 40
	msgbox SkyPillar_Outside_Text_EarthquakeNotMomentToWaste, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SkyPillar_Outside_Movement_PlayerClimbSkyPillar
	applymovement LOCALID_SKY_PILLAR_WALLACE, SkyPillar_Outside_Movement_WallaceClimbSkyPillar
	waitmovement 0
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 3   @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 5   @ shake delay
	special ShakeCamera
	waitstate
	delay 20
	applymovement LOCALID_SKY_PILLAR_WALLACE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 10
	applymovement LOCALID_SKY_PILLAR_WALLACE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 20
	applymovement LOCALID_SKY_PILLAR_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	msgbox SkyPillar_Outside_Text_SituationGettingWorse, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SYS_WEATHER_CTRL
	setweather WEATHER_ABNORMAL
	doweather
	special WaitWeather
	delay 30
	msgbox SkyPillar_Outside_Text_GotToGoBackForSootopolis, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenswapbuffers FADE_TO_BLACK
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SOOTOPOLIS_CITY_STATE, 4
	removeobject LOCALID_SKY_PILLAR_WALLACE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Outside_Movement_WallaceApproachPlayer:
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
	step_end

SkyPillar_Outside_Movement_WallaceClimbSkyPillar:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SkyPillar_Outside_Movement_PlayerClimbSkyPillar:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

@ ============================================================================
@ Ten Gauntlets: the ambush (storyline.md, "Sky Pillar"). The ABRA lands the
@ player at (13, 9) with STEVEN, WALLACE, NORMAN and WATTSON by the door. All
@ seven BRAINS come up from the south, the four step forward to hold them off
@ (the fight is off-screen) and the player climbs alone: state 17.
@ ============================================================================

SkyPillar_Outside_EventScript_AmbushScene::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SkyPillar_Outside_Text_Steven1, MSGBOX_DEFAULT
	msgbox SkyPillar_Outside_Text_Norman1, MSGBOX_DEFAULT
	msgbox SkyPillar_Outside_Text_Wattson1, MSGBOX_DEFAULT
	msgbox SkyPillar_Outside_Text_Wallace1, MSGBOX_DEFAULT
	closemessage
	@ The BRAINS, from the south.
	playse SE_PIN
	applymovement LOCALID_SKY_PILLAR_STEVEN, Common_Movement_ExclamationMark
	applymovement LOCALID_SKY_PILLAR_ALLY_WALLACE, Common_Movement_ExclamationMark
	applymovement LOCALID_SKY_PILLAR_NORMAN, Common_Movement_ExclamationMark
	applymovement LOCALID_SKY_PILLAR_WATTSON, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	clearflag FLAG_TEMP_2
	addobject LOCALID_SKY_PILLAR_ANABEL
	addobject LOCALID_SKY_PILLAR_TUCKER
	addobject LOCALID_SKY_PILLAR_LUCY
	addobject LOCALID_SKY_PILLAR_SPENSER
	addobject LOCALID_SKY_PILLAR_BRANDON
	addobject LOCALID_SKY_PILLAR_NOLAND
	addobject LOCALID_SKY_PILLAR_GRETA
	applymovement LOCALID_SKY_PILLAR_ANABEL, Common_Movement_WalkUp
	applymovement LOCALID_SKY_PILLAR_TUCKER, Common_Movement_WalkUp
	applymovement LOCALID_SKY_PILLAR_LUCY, Common_Movement_WalkUp
	applymovement LOCALID_SKY_PILLAR_SPENSER, Common_Movement_WalkUp
	waitmovement 0
	applymovement LOCALID_SKY_PILLAR_BRANDON, Common_Movement_WalkUp
	applymovement LOCALID_SKY_PILLAR_NOLAND, Common_Movement_WalkUp
	applymovement LOCALID_SKY_PILLAR_GRETA, Common_Movement_WalkUp
	waitmovement 0
	msgbox SkyPillar_Outside_Text_Anabel, MSGBOX_DEFAULT
	msgbox SkyPillar_Outside_Text_Tucker, MSGBOX_DEFAULT
	msgbox SkyPillar_Outside_Text_Brandon, MSGBOX_DEFAULT
	closemessage
	@ The four step forward.
	applymovement LOCALID_SKY_PILLAR_STEVEN, SkyPillar_Outside_Movement_StevenForward
	applymovement LOCALID_SKY_PILLAR_ALLY_WALLACE, SkyPillar_Outside_Movement_WallaceForward
	applymovement LOCALID_SKY_PILLAR_NORMAN, SkyPillar_Outside_Movement_NormanForward
	applymovement LOCALID_SKY_PILLAR_WATTSON, SkyPillar_Outside_Movement_WattsonForward
	waitmovement 0
	msgbox SkyPillar_Outside_Text_Steven2, MSGBOX_DEFAULT
	msgbox SkyPillar_Outside_Text_Norman2, MSGBOX_DEFAULT
	closemessage
	@ The player climbs alone.
	applymovement LOCALID_PLAYER, SkyPillar_Outside_Movement_PlayerRunsUp
	waitmovement 0
	playse SE_M_EXPLOSION
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12 @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	msgbox SkyPillar_Outside_Text_BehindYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ENDGAME_STATE, 17
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SKY_PILLAR_STEVEN
	removeobject LOCALID_SKY_PILLAR_ALLY_WALLACE
	removeobject LOCALID_SKY_PILLAR_NORMAN
	removeobject LOCALID_SKY_PILLAR_WATTSON
	removeobject LOCALID_SKY_PILLAR_ANABEL
	removeobject LOCALID_SKY_PILLAR_TUCKER
	removeobject LOCALID_SKY_PILLAR_LUCY
	removeobject LOCALID_SKY_PILLAR_SPENSER
	removeobject LOCALID_SKY_PILLAR_BRANDON
	removeobject LOCALID_SKY_PILLAR_NOLAND
	removeobject LOCALID_SKY_PILLAR_GRETA
	@ NURSE JOY tagged along: she's the white-out respawn from now on.
	call SkyPillar_Outside_EventScript_JoyHere
	addobject LOCALID_SKY_PILLAR_JOY
	delay 40
	fadescreen FADE_FROM_BLACK
	msgbox SkyPillar_Outside_Text_JoyArrives, MSGBOX_DEFAULT
	releaseall
	end

SkyPillar_Outside_Movement_StevenForward:
	walk_down
	walk_down
	walk_down
	step_end

SkyPillar_Outside_Movement_WallaceForward:
	walk_down
	walk_down
	walk_down
	step_end

SkyPillar_Outside_Movement_NormanForward:
	walk_down
	walk_down
	walk_down
	step_end

SkyPillar_Outside_Movement_WattsonForward:
	delay_16
	walk_down
	walk_down
	walk_left
	step_end

@ (13, 9) up to (13, 6), beside the door.
SkyPillar_Outside_Movement_PlayerRunsUp:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

@ NURSE JOY (VAR_ENDGAME_STATE 17 on): heals the team, and is where the
@ player wakes up after losing to SCOTT (HEAL_LOCATION_SKY_PILLAR_OUTSIDE).
SkyPillar_Outside_EventScript_Joy::
	lock
	faceplayer
	msgbox SkyPillar_Outside_Text_JoyHeal, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SkyPillar_Outside_Text_JoyHealed, MSGBOX_DEFAULT
	release
	end

SkyPillar_Outside_Text_Steven1:
	.string "STEVEN: {PLAYER}. Good, you're here.\p"
	.string "SCOTT is at the top of the PILLAR.\n"
	.string "He went up with a BALL he's been\l"
	.string "saving, and RAYQUAZA is up there.\p"
	.string "We end this today, all of us.$"

SkyPillar_Outside_Text_Norman1:
	.string "NORMAN: SCOTT told me once he'd\n"
	.string "squash me, and then he took your\l"
	.string "mother and me off the board.\p"
	.string "I've waited a long time to stand\n"
	.string "across from that man.$"

SkyPillar_Outside_Text_Wattson1:
	.string "WATTSON: Wahahahah! NEW MAUVILLE\n"
	.string "is still humming, and I've got a\l"
	.string "full charge saved up for him!$"

SkyPillar_Outside_Text_Wallace1:
	.string "WALLACE: SCOTT has already beaten\n"
	.string "me once. I do not intend to let him\l"
	.string "do it twice.\p"
	.string "We climb together. Come.$"

SkyPillar_Outside_Text_Anabel:
	.string "ANABEL: I'm afraid nobody climbs.\p"
	.string "SCOTT trained every one of us.\n"
	.string "We would hate to disappoint him.$"

SkyPillar_Outside_Text_Tucker:
	.string "TUCKER: All seven of us, and not\n"
	.string "one POKéMON of ours is chipped.\p"
	.string "Fancy a battle in the open air?$"

SkyPillar_Outside_Text_Brandon:
	.string "BRANDON: The door is behind you,\n"
	.string "kid. So are we.\p"
	.string "LUCY, SPENSER, NOLAND, GRETA:\n"
	.string "close the way up!$"

SkyPillar_Outside_Text_Steven2:
	.string "STEVEN: Seven of them. Four of us.\n"
	.string "Those odds will do.\p"
	.string "WALLACE, NORMAN, WATTSON. We hold\n"
	.string "this line.\p"
	.string "{PLAYER}! Go! The door is open!$"

SkyPillar_Outside_Text_Norman2:
	.string "NORMAN: Go on, {PLAYER}.\n"
	.string "Finish it. We'll be right behind\l"
	.string "you.$"

SkyPillar_Outside_Text_BehindYou:
	.string "{PLAYER} ran for the PILLAR as\n"
	.string "the first POKé BALLS flew behind.\p"
	.string "Shouts, roars and the crash of\n"
	.string "attacks echoed off the stone…$"

SkyPillar_Outside_Text_JoyArrives:
	.string "The entrance is quiet now.\p"
	.string "NURSE JOY: I followed you all the\n"
	.string "way up here.\p"
	.string "I can't battle, but I can patch up\n"
	.string "your team. Talk to me any time.\p"
	.string "Now go. The stairs are clear.$"

SkyPillar_Outside_Text_JoyHeal:
	.string "NURSE JOY: You look like you've\n"
	.string "been through it. Let me see your\l"
	.string "POKéMON.$"

SkyPillar_Outside_Text_JoyHealed:
	.string "NURSE JOY: All better!\p"
	.string "SCOTT is waiting at the top.\n"
	.string "I'll be right here.$"

SkyPillar_Outside_EventScript_Wallace::
	end

SkyPillar_Outside_EventScript_ClosedDoor::
	msgbox SkyPillar_Outside_Text_DoorIsClosed, MSGBOX_SIGN
	end

SkyPillar_Outside_Text_DoorIsClosed:
	.string "The door is closed.$"

SkyPillar_Outside_Text_OpenedDoorToSkyPillar:
	.string "WALLACE: Oh, my, I'm terribly sorry!\p"
	.string "In my haste, I didn't notice that\n"
	.string "I'd left you behind!\p"
	.string "I've opened the locked door of\n"
	.string "the SKY PILLAR.\p"
	.string "{PLAYER}{KUN}, let's be on our way!$"

SkyPillar_Outside_Text_EarthquakeNotMomentToWaste:
	.string "WALLACE: It's an earthquake!\p"
	.string "There's not a moment to waste!\n"
	.string "We've got to hurry!$"

SkyPillar_Outside_Text_SituationGettingWorse:
	.string "WALLACE: Hmm…\n"
	.string "The situation is getting worse…$"

SkyPillar_Outside_Text_GotToGoBackForSootopolis:
	.string "WALLACE: This isn't good…\p"
	.string "The weather distortion is spreading\n"
	.string "even here…\p"
	.string "{PLAYER}{KUN}.\p"
	.string "RAYQUAZA should be farther up\n"
	.string "from here.\p"
	.string "I'm worried about SOOTOPOLIS.\n"
	.string "I've got to go back.\p"
	.string "Everything is in your hands now.\n"
	.string "Don't fail us!$"

@ Ten Gauntlets: the endgame ABRA network (data/scripts/endgame_towns.inc).
SkyPillar_Outside_EventScript_EndgameAbra::
	setvar VAR_0x8004, ABRA_AT_SKY_PILLAR
	goto EventScript_EndgameAbra
