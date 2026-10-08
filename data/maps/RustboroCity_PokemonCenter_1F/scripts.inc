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
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	checktrainerflag TRAINER_ENDGAME_ROXANNE
	goto_if FALSE, RustboroCity_PokemonCenter_1F_EventScript_GirlOld
	goto_if_set FLAG_GIRATINA_CAUGHT, RustboroCity_PokemonCenter_1F_EventScript_GirlTearClosed
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlTear, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GirlOld::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GirlTearClosed::
	msgbox RustboroCity_PokemonCenter_1F_Text_GirlTearClosed, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "My POKéMON has a NAIVE nature, and my\n"
	.string "friend's has a JOLLY nature.\p"
	.string "It's fascinating how POKéMON have\n"
	.string "personalities!$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Just like people, there are male and\n"
	.string "female POKéMON.\p"
	.string "But no one seems to have any idea how\n"
	.string "they're different.$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "The man next door gave me an HM!\p"
	.string "I used it to teach my POKéMON how to\n"
	.string "CUT down skinny trees.$"


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
