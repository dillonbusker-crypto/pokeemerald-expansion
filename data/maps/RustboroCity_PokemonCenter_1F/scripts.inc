RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

@ Ten Gauntlets: the endgame ABRA network (data/scripts/endgame_towns.inc).
@ RUSTBORO's ABRA waits by the counter, and the others land the player
@ beside it.
RustboroCity_PokemonCenter_1F_EventScript_EndgameAbra::
	setvar VAR_0x8004, ABRA_AT_RUSTBORO
	goto EventScript_EndgameAbra

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_RUSTBORO_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonCenter_1F_EventScript_ManEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonCenter_1F_EventScript_ManFreed
	msgbox RustboroCity_PokemonCenter_1F_Text_Man, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_ManEnding::
	msgbox RustboroCity_PokemonCenter_1F_Text_ManEnding, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_ManFreed::
	msgbox RustboroCity_PokemonCenter_1F_Text_ManFreed, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonCenter_1F_EventScript_BoyEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonCenter_1F_EventScript_BoyFreed
	msgbox RustboroCity_PokemonCenter_1F_Text_Boy, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_BoyEnding::
	msgbox RustboroCity_PokemonCenter_1F_Text_BoyEnding, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_BoyFreed::
	msgbox RustboroCity_PokemonCenter_1F_Text_BoyFreed, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	checktrainerflag TRAINER_ENDGAME_ROXANNE
	goto_if FALSE, RustboroCity_PokemonCenter_1F_EventScript_GirlOld
	goto_if_set FLAG_GIRATINA_CAUGHT, RustboroCity_PokemonCenter_1F_EventScript_GirlTearClosed
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlTear, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GirlOld::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonCenter_1F_EventScript_GirlOldEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonCenter_1F_EventScript_GirlOldFreed
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlOld, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GirlOldEnding::
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlOldEnding, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GirlOldFreed::
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlOldFreed, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GirlTearClosed::
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlTearClosed, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_Man:
	.string "I used to come in every morning while\n"
	.string "my POKéMON healed, for the company.\p"
	.string "Now my POKéNAV heals it before\n"
	.string "breakfast. I come in anyway. The NURSE\l"
	.string "and I just look at each other.$"

RustboroCity_PokemonCenter_1F_Text_ManFreed:
	.string "They say the auto-heal runs on DEVON's\n"
	.string "servers. With STONE out of his chair,\l"
	.string "maybe it will stutter.\p"
	.string "I hate that I'm hoping so.$"

RustboroCity_PokemonCenter_1F_Text_ManEnding:
	.string "NURSE JOY had a patient this morning.\n"
	.string "A real one! A WURMPLE with a sore tail.\p"
	.string "I brought her tea. She cried a little.$"

RustboroCity_PokemonCenter_1F_Text_Boy:
	.string "Everyone's scared of the ELITE FOUR,\n"
	.string "so I hang around the CENTER.\p"
	.string "It's the one place they wouldn't\n"
	.string "bother with. There's nothing in here\l"
	.string "to take.$"

RustboroCity_PokemonCenter_1F_Text_BoyFreed:
	.string "I mostly stopped hiding in the CENTER.\p"
	.string "Mostly. The couch is very good.$"

RustboroCity_PokemonCenter_1F_Text_BoyEnding:
	.string "The CENTER is busy again, and I had\n"
	.string "to give up my couch.\p"
	.string "Worth it. The WURMPLE was really\n"
	.string "cute.$"

RustboroCity_PokemonCenter_1F_Text_GirlOld:
	.string "The man next door gave me an HM\n"
	.string "once, before everything went wrong.\p"
	.string "My POKéMON has been using CUT on the\n"
	.string "same tree for weeks, out of boredom.\l"
	.string "It's down to a stump.$"

RustboroCity_PokemonCenter_1F_Text_GirlOldFreed:
	.string "The tree is a stump, and it's still my\n"
	.string "POKéMON's favourite sparring partner.\p"
	.string "It's the one thing in town that stays\n"
	.string "where I put it.$"

RustboroCity_PokemonCenter_1F_Text_GirlOldEnding:
	.string "I took my POKéMON on a walk today,\n"
	.string "and for once it had nothing to CUT.\p"
	.string "We both felt a little lost. In a\n"
	.string "good way.$"


@ Ten Gauntlets: "The Tear" (sprint-a-giratina.md). The girl after ROXANNE's
@ rematch, then once GIRATINA is caught (FLAG_GIRATINA_CAUGHT).
RustboroCity_PokemonCenter_1F_Text_GirlTear:
	.string "My shadow was on the wrong side of\n"
	.string "me this morning. It pointed at the\l"
	.string "lamp instead of away from it.\p"
	.string "The floor tiles in here don't match\n"
	.string "the lights, either. Is that normal?$"

RustboroCity_PokemonCenter_1F_Text_GirlTearClosed:
	.string "My shadow behaves again!\p"
	.string "I almost miss it. It was the most\n"
	.string "interesting thing that ever\l"
	.string "happened to me.$"

@ ----------------------------------------------------------------------------
@ Ten Gauntlets: a WOBBUFFET has been queuing at the counter since the POKéNAV
@ emptied the POKéMON CENTERS. It is the whole line. Each talk plays the next
@ gag (VAR_RUSTBORO_WOBBUFFET, 0-3, cycles); after the credits the CENTER has
@ patients again and its number finally comes up.
@ ----------------------------------------------------------------------------
RustboroCity_PokemonCenter_1F_EventScript_Wobbuffet::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetEnding
	goto_if_eq VAR_RUSTBORO_WOBBUFFET, 1, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetCounter
	goto_if_eq VAR_RUSTBORO_WOBBUFFET, 2, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPoint
	goto_if_eq VAR_RUSTBORO_WOBBUFFET, 3, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetTicket
	@ 0: the salute.
	playmoncry SPECIES_WOBBUFFET, CRY_MODE_NORMAL
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetSalute, MSGBOX_DEFAULT
	waitmoncry
	setvar VAR_RUSTBORO_WOBBUFFET, 1
	release
	end

@ 1: the player tries to squeeze past, and bounces off (COUNTER).
RustboroCity_PokemonCenter_1F_EventScript_WobbuffetCounter::
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetSqueeze, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushNorth
	call_if_eq VAR_FACING, DIR_SOUTH, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushSouth
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushWest
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushEast
	playse SE_WALL_HIT
	applymovement LOCALID_RUSTBORO_PC_WOBBUFFET, RustboroCity_PokemonCenter_1F_Movement_WobbuffetBrace
	waitmovement 0
	call_if_eq VAR_FACING, DIR_NORTH, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceNorth
	call_if_eq VAR_FACING, DIR_SOUTH, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceSouth
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceWest
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceEast
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetCounter, MSGBOX_DEFAULT
	setvar VAR_RUSTBORO_WOBBUFFET, 2
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushNorth::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_PushNorth
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushSouth::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_PushSouth
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushWest::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_PushWest
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPushEast::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_PushEast
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceNorth::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_BounceNorth
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceSouth::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_BounceSouth
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceWest::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_BounceWest
	waitmovement 0
	return

RustboroCity_PokemonCenter_1F_EventScript_WobbuffetBounceEast::
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_PokemonCenter_1F_Movement_BounceEast
	waitmovement 0
	return

@ 2: the player points at the empty counter.
RustboroCity_PokemonCenter_1F_EventScript_WobbuffetPoint::
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetPoint1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RUSTBORO_PC_WOBBUFFET, RustboroCity_PokemonCenter_1F_Movement_WobbuffetLookUp
	waitmovement 0
	delay 30
	applymovement LOCALID_RUSTBORO_PC_WOBBUFFET, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetPoint2, MSGBOX_DEFAULT
	setvar VAR_RUSTBORO_WOBBUFFET, 3
	release
	end

@ 3: the ticket.
RustboroCity_PokemonCenter_1F_EventScript_WobbuffetTicket::
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetTicket, MSGBOX_DEFAULT
	setvar VAR_RUSTBORO_WOBBUFFET, 0
	release
	end

@ After the credits: its number comes up.
RustboroCity_PokemonCenter_1F_EventScript_WobbuffetEnding::
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetEnding1, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_WOBBUFFET, CRY_MODE_NORMAL
	applymovement LOCALID_RUSTBORO_PC_WOBBUFFET, RustboroCity_PokemonCenter_1F_Movement_WobbuffetBrace
	waitmovement 0
	waitmoncry
	msgbox RustboroCity_PokemonCenter_1F_Text_WobbuffetEnding2, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonCenter_1F_Movement_WobbuffetBrace:
	walk_in_place_fast_up
	walk_in_place_fast_up
	face_player
	step_end

RustboroCity_PokemonCenter_1F_Movement_WobbuffetLookUp:
	face_up
	step_end

RustboroCity_PokemonCenter_1F_Movement_PushNorth:
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

RustboroCity_PokemonCenter_1F_Movement_PushSouth:
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

RustboroCity_PokemonCenter_1F_Movement_PushWest:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

RustboroCity_PokemonCenter_1F_Movement_PushEast:
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

RustboroCity_PokemonCenter_1F_Movement_BounceNorth:
	jump_in_place_up
	step_end

RustboroCity_PokemonCenter_1F_Movement_BounceSouth:
	jump_in_place_down
	step_end

RustboroCity_PokemonCenter_1F_Movement_BounceWest:
	jump_in_place_left
	step_end

RustboroCity_PokemonCenter_1F_Movement_BounceEast:
	jump_in_place_right
	step_end

RustboroCity_PokemonCenter_1F_Text_WobbuffetSalute:
	.string "WOBBUFFET: Woooob!\p"
	.string "It saluted. It is standing in line\n"
	.string "for the counter.\p"
	.string "It is the whole line.$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetSqueeze:
	.string "WOBBUFFET: Wob.\p"
	.string "It is still in line. {PLAYER} tried\n"
	.string "to squeeze past.$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetCounter:
	.string "WOBBUFFET used COUNTER!\p"
	.string "{PLAYER} bounced off.\p"
	.string "WOBBUFFET: Wooob.\n"
	.string "It has not lost its place.$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetPoint1:
	.string "WOBBUFFET: Wob?\p"
	.string "{PLAYER} pointed at the counter.\n"
	.string "There is nobody waiting at it.$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetPoint2:
	.string "WOBBUFFET looked at the counter.\p"
	.string "WOBBUFFET looked at {PLAYER}.\p"
	.string "WOBBUFFET did not move. It was here\n"
	.string "first.$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetTicket:
	.string "WOBBUFFET: …Wob.\p"
	.string "It is holding a numbered ticket from\n"
	.string "the dispenser.\p"
	.string "The number is 1. The sign above the\n"
	.string "counter says NOW SERVING: 1.\p"
	.string "It has been saying that since the\n"
	.string "POKéNAV came out.$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetEnding1:
	.string "The CENTER has patients again, and a\n"
	.string "real line.\p"
	.string "WOBBUFFET is at the front of it. It\n"
	.string "was always at the front of it.\p"
	.string "NURSE JOY: Number 1? Number 1,\n"
	.string "please!$"

RustboroCity_PokemonCenter_1F_Text_WobbuffetEnding2:
	.string "WOBBUFFET: WOOOOOOOB!\p"
	.string "It wept. NURSE JOY wept. The man\n"
	.string "behind it checked his ticket and\l"
	.string "wept too. His number is 2.$"
