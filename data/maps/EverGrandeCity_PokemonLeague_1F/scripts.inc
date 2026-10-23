EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_PokemonLeague_1F_OnFrame
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnFrame:
	map_script_2 VAR_TEMP_2, 1, EverGrandeCity_PokemonLeague_1F_EventScript_MaxieArchieScene
	.2byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	call EverGrandeCity_PokemonLeague_1F_EventScript_SetupEverGrandeStory
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_LEAGUE_GUARD_1, 9, 2
	setobjectxyperm LOCALID_LEAGUE_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LEAGUE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

@ Ten Gauntlets: no POKéMART sells to the player anywhere (the only shop is
@ the Frontier's). The LEAGUE's counter is closed. The vanilla list below is
@ unreferenced.
EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	lock
	faceplayer
	msgbox EverGrandeCity_PokemonLeague_1F_Text_ClerkClosed, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PokemonLeague_1F_Text_ClerkClosed:
	.string "Welcome… I'm afraid the counter is\n"
	.string "closed.\p"
	.string "With the ELITE FOUR gone, the LEAGUE\n"
	.string "hasn't ordered stock in weeks. I'm\l"
	.string "only here to mind the register.$"

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	pokemartlistend

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	@ Ten Gauntlets: the ELITE FOUR have left (storyline.md), so the guards
	@ never let anyone through.
	goto EverGrandeCity_PokemonLeague_1F_EventScript_EliteFourGone
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_LEAGUE_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_LEAGUE_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_LEAGUE_GUARD_1
	copyobjectxytoperm LOCALID_LEAGUE_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"

@ ============================================================================
@ Ten Gauntlets: the Ever Grande trip, the end of the Broker's letter
@ (storyline.md; VAR_BROKER_STORY_STATE is explained in
@ BattleFrontier_OutsideWest). MAXIE and ARCHIE wait in the lobby for a
@ meeting that isn't here. At state 8, WALLACE has just gone in ahead of the
@ player (who arrives on the left mat, (9, 11)); the scene plays straight
@ away and goes into the tag battle. A loss whites out to the POKEMON CENTER
@ below (state 9: they're all still here, and talking to WALLACE starts the
@ fight again). Beaten, MAXIE and ARCHIE vanish behind a flash bang, and
@ WALLACE goes after them (state 10).
@ ============================================================================

EverGrandeCity_PokemonLeague_1F_EventScript_SetupEverGrandeStory::
	setflag FLAG_HIDE_EVER_GRANDE_STORY_WALLACE
	setflag FLAG_HIDE_EVER_GRANDE_STORY_MAXIE
	setflag FLAG_HIDE_EVER_GRANDE_STORY_ARCHIE
	goto_if_lt VAR_BROKER_STORY_STATE, 8, Common_EventScript_NopReturn
	goto_if_gt VAR_BROKER_STORY_STATE, 9, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_WALLACE
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_MAXIE
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_ARCHIE
	goto_if_eq VAR_BROKER_STORY_STATE, 9, EverGrandeCity_PokemonLeague_1F_EventScript_SetupRematch
	setvar VAR_TEMP_2, 1
	return

EverGrandeCity_PokemonLeague_1F_EventScript_SetupRematch::
	setobjectxyperm LOCALID_LEAGUE_WALLACE, 10, 7
	setobjectmovementtype LOCALID_LEAGUE_MAXIE, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_LEAGUE_ARCHIE, MOVEMENT_TYPE_FACE_DOWN
	return

EverGrandeCity_PokemonLeague_1F_EventScript_EliteFourGone::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_EliteFourGone, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_MaxieArchieScene::
	lockall
	setvar VAR_TEMP_2, 0
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_PlayerIn
	applymovement LOCALID_LEAGUE_WALLACE, EverGrandeCity_PokemonLeague_1F_Movement_WallaceIn
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_Scene1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LEAGUE_MAXIE, Common_Movement_FaceDown
	applymovement LOCALID_LEAGUE_ARCHIE, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LEAGUE_MAXIE, Common_Movement_ExclamationMark
	applymovement LOCALID_LEAGUE_ARCHIE, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_Scene2, MSGBOX_DEFAULT
	closemessage
	playse SE_PC_OFF
	msgbox EverGrandeCity_PokemonLeague_1F_Text_UsedScrambler, MSGBOX_DEFAULT
	waitse
	msgbox EverGrandeCity_PokemonLeague_1F_Text_Scene3, MSGBOX_DEFAULT
	closemessage
	setvar VAR_BROKER_STORY_STATE, 9
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TagBattle

@ State 9: talking to WALLACE (or to MAXIE and ARCHIE, who point at him)
@ starts the fight again.
EverGrandeCity_PokemonLeague_1F_EventScript_Wallace::
	lock
	faceplayer
	goto_if_ne VAR_BROKER_STORY_STATE, 9, EverGrandeCity_PokemonLeague_1F_EventScript_WallaceEnd
	msgbox EverGrandeCity_PokemonLeague_1F_Text_WallaceRetry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EverGrandeCity_PokemonLeague_1F_EventScript_WallaceNotYet
	closemessage
	applymovement LOCALID_LEAGUE_WALLACE, Common_Movement_FaceUp
	waitmovement 0
	playse SE_PC_OFF
	msgbox EverGrandeCity_PokemonLeague_1F_Text_UsedScrambler, MSGBOX_DEFAULT
	waitse
	closemessage
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TagBattle

EverGrandeCity_PokemonLeague_1F_EventScript_WallaceNotYet::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_WallaceNotYet, MSGBOX_DEFAULT
EverGrandeCity_PokemonLeague_1F_EventScript_WallaceEnd::
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_MaxieArchie::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_BackForMore, MSGBOX_NPC
	end

@ The player brings three POKEMON and WALLACE the other three. No heal (the
@ SCRAMBLER); a loss whites out to the POKEMON CENTER below, and the held
@ items come back either way (EventScript_RestoreStoryHeldItems).
EverGrandeCity_PokemonLeague_1F_EventScript_TagBattle::
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
EverGrandeCity_PokemonLeague_1F_EventScript_ChooseTeam::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_ne VAR_RESULT, 0, EverGrandeCity_PokemonLeague_1F_EventScript_TagBattleStart
	special LoadPlayerParty
	msgbox EverGrandeCity_PokemonLeague_1F_Text_PickTeam, MSGBOX_DEFAULT
	closemessage
	goto EverGrandeCity_PokemonLeague_1F_EventScript_ChooseTeam

EverGrandeCity_PokemonLeague_1F_EventScript_TagBattleStart::
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY
	multi_2_vs_2 TRAINER_EVER_GRANDE_MAXIE, EverGrandeCity_PokemonLeague_1F_Text_MaxieDefeat, TRAINER_EVER_GRANDE_ARCHIE, EverGrandeCity_PokemonLeague_1F_Text_ArchieDefeat, PARTNER_WALLACE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, EverGrandeCity_PokemonLeague_1F_EventScript_TagBattleWon
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate
	end

EverGrandeCity_PokemonLeague_1F_EventScript_TagBattleWon::
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	applymovement LOCALID_LEAGUE_WALLACE, Common_Movement_FaceUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_Beaten, MSGBOX_DEFAULT
	closemessage
	@ The flash bang.
	playse SE_M_SELF_DESTRUCT
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_LEAGUE_MAXIE
	removeobject LOCALID_LEAGUE_ARCHIE
	delay 30
	fadescreen FADE_FROM_WHITE
	waitse
	applymovement LOCALID_LEAGUE_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_WallaceChases, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LEAGUE_WALLACE, EverGrandeCity_PokemonLeague_1F_Movement_WallaceOut
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_LEAGUE_WALLACE
	setvar VAR_BROKER_STORY_STATE, 10
	releaseall
	end

@ From the mat (9, 11) up to (9, 7), two tiles below MAXIE at (9, 5).
EverGrandeCity_PokemonLeague_1F_Movement_PlayerIn:
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

@ From (10, 10) up to (10, 7), beside the player, below ARCHIE.
EverGrandeCity_PokemonLeague_1F_Movement_WallaceIn:
	walk_up
	walk_up
	walk_up
	face_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_WallaceOut:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	set_invisible
	step_end

EverGrandeCity_PokemonLeague_1F_Text_EliteFourGone:
	.string "We can't let anyone through.\p"
	.string "The ELITE FOUR aren't here.\n"
	.string "Nobody knows where they've gone...$"

EverGrandeCity_PokemonLeague_1F_Text_Scene1:
	.string "ARCHIE: Bah! I thought this was\n"
	.string "supposed to be the meeting place!\p"
	.string "MAXIE: Perhaps he meant the ELITE\n"
	.string "FOUR would be at the meeting...\p"
	.string "Not that the meeting would be at\n"
	.string "the ELITE FOUR.\p"
	.string "ARCHIE: Then why didn't he just\n"
	.string "say so?!$"

EverGrandeCity_PokemonLeague_1F_Text_Scene2:
	.string "MAXIE: ...The CHAMPION.\p"
	.string "This is all just a\n"
	.string "misunderstanding. We were just\l"
	.string "leaving.\p"
	.string "WALLACE: Not so fast.\n"
	.string "Who were you meeting?\p"
	.string "ARCHIE: That's none of your\n"
	.string "business, CHAMPION.\p"
	.string "WALLACE: It's very much my\n"
	.string "business. The ELITE FOUR are at\l"
	.string "this so-called meeting.\p"
	.string "Speak up, now. Or else.\p"
	.string "ARCHIE: Or else what? Gahahaha!\p"
	.string "We can handle you easy, CHAMPION.\n"
	.string "And what's this puny kid gonna do\l"
	.string "about it?\p"
	.string "WALLACE: {PLAYER}. The SCRAMBLER.$"

EverGrandeCity_PokemonLeague_1F_Text_UsedScrambler:
	.string "{PLAYER} used the SCRAMBLER!\p"
	.string "Every POKéNAV nearby went dark.$"

EverGrandeCity_PokemonLeague_1F_Text_Scene3:
	.string "MAXIE: A SCRAMBLER...? No healing\n"
	.string "for anyone, then.\p"
	.string "ARCHIE: Fine by me! Bring it on!\p"
	.string "WALLACE: {PLAYER}, choose three\n"
	.string "POKéMON. I'll handle the rest.$"

EverGrandeCity_PokemonLeague_1F_Text_PickTeam:
	.string "WALLACE: {PLAYER}! Choose your\n"
	.string "POKéMON!$"

EverGrandeCity_PokemonLeague_1F_Text_MaxieDefeat:
	.string "MAXIE: This was not... in my\n"
	.string "calculations.$"

EverGrandeCity_PokemonLeague_1F_Text_ArchieDefeat:
	.string "ARCHIE: Gwah! Blown out of the\n"
	.string "water!$"

EverGrandeCity_PokemonLeague_1F_Text_Beaten:
	.string "ARCHIE: MAXIE... We can't let him\n"
	.string "take us in. Not now!\p"
	.string "MAXIE: Agreed. Close your eyes.\p"
	.string "MAXIE threw something!$"

EverGrandeCity_PokemonLeague_1F_Text_WallaceChases:
	.string "WALLACE: ...! They're gone!\p"
	.string "A flash bang... They planned for\n"
	.string "this.\p"
	.string "I'm going after them. They can't\n"
	.string "have gone far.\p"
	.string "{PLAYER}, get back to the FRONTIER\n"
	.string "before SCOTT notices you're gone.\l"
	.string "My ABRA is waiting outside.\p"
	.string "Thank you. I couldn't have done\n"
	.string "this alone.$"

EverGrandeCity_PokemonLeague_1F_Text_WallaceRetry:
	.string "WALLACE: Ready to try again,\n"
	.string "{PLAYER}?$"

EverGrandeCity_PokemonLeague_1F_Text_WallaceNotYet:
	.string "WALLACE: Take a moment, then. They\n"
	.string "aren't going anywhere.$"

EverGrandeCity_PokemonLeague_1F_Text_BackForMore:
	.string "ARCHIE: Back for more, kid?\n"
	.string "Gahahaha!$"
