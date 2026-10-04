EverGrandeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_OnFrame
	.byte 0

EverGrandeCity_OnFrame:
	map_script_2 VAR_TEMP_2, 1, EverGrandeCity_EventScript_WallaceGoesIn
	.2byte 0

EverGrandeCity_OnTransition:
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call EverGrandeCity_EventScript_SetupEverGrandeStory
	end

EverGrandeCity_EventScript_VictoryRoadSign::
	msgbox EverGrandeCity_Text_EnteringVictoryRoad, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_CitySign::
	msgbox EverGrandeCity_Text_CitySign, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_PokemonLeagueSign::
	msgbox EverGrandeCity_Text_EnteringPokemonLeague, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_SetVisitedEverGrande::
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setvar VAR_TEMP_1, 1
	end

EverGrandeCity_Text_EnteringVictoryRoad:
	.string "ENTERING VICTORY ROAD$"

EverGrandeCity_Text_EnteringPokemonLeague:
	.string "ENTERING POKéMON LEAGUE\n"
	.string "CENTER GATE$"

EverGrandeCity_Text_CitySign:
	.string "EVER GRANDE CITY\p"
	.string "“The paradise of flowers, the sea,\n"
	.string "and POKéMON.”$"

@ ============================================================================
@ Ten Gauntlets: the Ever Grande trip, the end of the Broker's letter
@ (storyline.md; VAR_BROKER_STORY_STATE is explained in
@ BattleFrontier_OutsideWest). WALLACE's ABRA lands the player in front of the
@ POKEMON LEAGUE at (18, 8), where WALLACE waits (state 7) and leads the way
@ in. Another ABRA waits outside the POKEMON CENTER below, where a loss to
@ MAXIE and ARCHIE whites out to, to TELEPORT the player back up. Only the
@ Pokemon Center and the LEAGUE are open: VICTORY ROAD is closed at both
@ ends, and the current stops anyone surfing down the waterfall south of the
@ town. The rest of HOENN stays out of reach.
@ ============================================================================

EverGrandeCity_EventScript_SetupEverGrandeStory::
	setflag FLAG_HIDE_EVER_GRANDE_STORY_OUTSIDE_WALLACE
	setflag FLAG_HIDE_EVER_GRANDE_STORY_TOP_ABRA
	setflag FLAG_HIDE_EVER_GRANDE_STORY_LOWER_ABRA
	goto_if_lt VAR_BROKER_STORY_STATE, 7, Common_EventScript_NopReturn
	goto_if_ge VAR_BROKER_STORY_STATE, 11, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_TOP_ABRA
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_LOWER_ABRA
	goto_if_ne VAR_BROKER_STORY_STATE, 7, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_OUTSIDE_WALLACE
	setvar VAR_TEMP_2, 1
	return

EverGrandeCity_EventScript_WallaceGoesIn::
	lockall
	setvar VAR_TEMP_2, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_EVER_GRANDE_WALLACE, Common_Movement_FaceRight
	waitmovement 0
	msgbox EverGrandeCity_Text_WallaceWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EVER_GRANDE_WALLACE, EverGrandeCity_Movement_WallaceToDoor
	waitmovement 0
	opendoor 18, 5
	waitdooranim
	applymovement LOCALID_EVER_GRANDE_WALLACE, EverGrandeCity_Movement_WallaceIn
	waitmovement 0
	removeobject LOCALID_EVER_GRANDE_WALLACE
	closedoor 18, 5
	waitdooranim
	setvar VAR_BROKER_STORY_STATE, 8
	releaseall
	end

@ From (17, 7) to (18, 6), below the door.
EverGrandeCity_Movement_WallaceToDoor:
	walk_up
	walk_right
	face_up
	step_end

EverGrandeCity_Movement_WallaceIn:
	walk_up
	set_invisible
	step_end

@ Outside the LEAGUE: back to the FRONTIER, any time. Once MAXIE and ARCHIE
@ are beaten (state 10), it's the trip home and the event ends.
EverGrandeCity_EventScript_TopAbra::
	lock
	faceplayer
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox EverGrandeCity_Text_TopAbra, MSGBOX_YESNO
	waitmoncry
	goto_if_eq VAR_RESULT, NO, EverGrandeCity_EventScript_AbraNo
	msgbox EverGrandeCity_Text_AbraUsedTeleport, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_BROKER_STORY_STATE, 10, EverGrandeCity_EventScript_TripDone
	playse SE_M_TELEPORT
	warpteleport MAP_BATTLE_FRONTIER_OUTSIDE_EAST, 4, 53
	waitstate
	release
	end

EverGrandeCity_EventScript_TripDone::
	setvar VAR_BROKER_STORY_STATE, 11
	return

EverGrandeCity_EventScript_LowerAbra::
	lock
	faceplayer
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox EverGrandeCity_Text_LowerAbra, MSGBOX_YESNO
	waitmoncry
	goto_if_eq VAR_RESULT, NO, EverGrandeCity_EventScript_AbraNo
	msgbox EverGrandeCity_Text_AbraUsedTeleport, MSGBOX_DEFAULT
	closemessage
	playse SE_M_TELEPORT
	warpteleport MAP_EVER_GRANDE_CITY, 18, 8
	waitstate
	release
	end

EverGrandeCity_EventScript_AbraNo::
	release
	end

@ On the tile in front of either VICTORY ROAD entrance (top, (18, 28), and
@ bottom, (18, 42)): turned back the way they came.
EverGrandeCity_EventScript_VictoryRoadClosed::
	lockall
	specialvar VAR_RESULT, GetPlayerFacingDirection
	msgbox EverGrandeCity_Text_VictoryRoadClosed, MSGBOX_DEFAULT
	closemessage
	call EverGrandeCity_EventScript_StepBack
	releaseall
	end

@ Row 59, the last water above the waterfall: pushed back up.
EverGrandeCity_EventScript_WaterfallTooStrong::
	lockall
	specialvar VAR_RESULT, GetPlayerFacingDirection
	msgbox EverGrandeCity_Text_WaterfallTooStrong, MSGBOX_DEFAULT
	closemessage
	call EverGrandeCity_EventScript_StepBack
	releaseall
	end

EverGrandeCity_EventScript_StepBack::
	call_if_eq VAR_RESULT, DIR_NORTH, EverGrandeCity_EventScript_StepDown
	call_if_eq VAR_RESULT, DIR_SOUTH, EverGrandeCity_EventScript_StepUp
	call_if_eq VAR_RESULT, DIR_WEST, EverGrandeCity_EventScript_StepRight
	call_if_eq VAR_RESULT, DIR_EAST, EverGrandeCity_EventScript_StepLeft
	waitmovement 0
	return

EverGrandeCity_EventScript_StepDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	return

EverGrandeCity_EventScript_StepUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	return

EverGrandeCity_EventScript_StepRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	return

EverGrandeCity_EventScript_StepLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
	return

EverGrandeCity_Text_WallaceWaiting:
	.string "WALLACE: {PLAYER}! You made it.\p"
	.string "The LEAGUE staff say MAXIE and\n"
	.string "ARCHIE are still inside.\p"
	.string "Let's not keep them waiting.\n"
	.string "Come on!$"

EverGrandeCity_Text_TopAbra:
	.string "It's WALLACE's ABRA.\p"
	.string "It can TELEPORT you back to the\n"
	.string "FRONTIER. Go now?$"

EverGrandeCity_Text_LowerAbra:
	.string "It's WALLACE's ABRA.\p"
	.string "It can TELEPORT you up to the\n"
	.string "POKéMON LEAGUE. Go now?$"

EverGrandeCity_Text_AbraUsedTeleport:
	.string "ABRA used TELEPORT!$"

EverGrandeCity_Text_VictoryRoadClosed:
	.string "A sign has been posted:\p"
	.string "“VICTORY ROAD is closed until\n"
	.string "further notice.”$"

EverGrandeCity_Text_WaterfallTooStrong:
	.string "The current is too strong to go\n"
	.string "down the waterfall!$"
