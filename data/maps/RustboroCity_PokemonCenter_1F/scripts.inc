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
