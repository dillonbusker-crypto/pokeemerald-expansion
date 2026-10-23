BattleFrontier_Lounge8_MapScripts::
	.byte 0

BattleFrontier_Lounge8_EventScript_Man::
	msgbox BattleFrontier_Lounge8_Text_WhatATrainerNeeds, MSGBOX_NPC
	end

BattleFrontier_Lounge8_EventScript_Woman::
	msgbox BattleFrontier_Lounge8_Text_KnowAboutFrontierBrains, MSGBOX_NPC
	end

BattleFrontier_Lounge8_EventScript_NinjaBoy::
	msgbox BattleFrontier_Lounge8_Text_ToldMeIHaveTalentForBattling, MSGBOX_NPC
	end

BattleFrontier_Lounge8_Text_WhatATrainerNeeds:
	.string "What a trainer needs...\p"
	.string "Knowledge... Strategy... Luck...\n"
	.string "Guts... Spirit... Bravery... And\l"
	.string "ability...\p"
	.string "Well, I'm all set in every way!\n"
	.string "I'll clear all eight gauntlets!\p"
	.string "Huh? Six POKéMON? At level 50? Hm.$"

BattleFrontier_Lounge8_Text_KnowAboutFrontierBrains:
	.string "BRAINS?\p"
	.string "They used to run the seven\n"
	.string "facilities here. Now five of them\l"
	.string "guard the end of the Eight\l"
	.string "Gauntlets, from gauntlet 4 on.\p"
	.string "The first three are guarded by\n"
	.string "SCOTT's WARDENS... and get this,\l"
	.string "they're GYM LEADERS! WINONA, JUAN\l"
	.string "and ROXANNE.\p"
	.string "I wonder what SCOTT offered them\n"
	.string "to leave their GYMS?$"

BattleFrontier_Lounge8_Text_ToldMeIHaveTalentForBattling:
	.string "At the BATTLE TOWER, an older girl\n"
	.string "told me that I have a lot of talent\l"
	.string "for battling!\p"
	.string "I like POKéMON CONTESTS more!\p"
	.string "But I'm no good at CONTESTS!\p"
	.string "I guess having talent and liking\n"
	.string "something aren't the same.$"


@ ----------------------------------------------------------------------------
@ Ten Gauntlets: the old woman who hears the one that made the world. She has
@ heard its hum all her life, and the AZURE FLUTE has been in her shawl all
@ along. She asks to be shown a Pokemon (ChoosePartyMon): anything but
@ GIRATINA she blesses in the name of mighty ARCEUS (flavour only). Shown
@ GIRATINA (either forme) she takes it for the KING OF THE UNDERWORLD, blows
@ the flute, and the player is carried to NAVEL ROCK's summit, where ARCEUS
@ waits (NavelRock_Top; level 60, catchable). VAR_ARCEUS_EVENT: 0 not blown,
@ 1 blown (she plays again on request), 2 ARCEUS caught. Her opening line
@ follows the Tear (VAR_GIRATINA_EVENT, FLAG_GIRATINA_CAUGHT).
@ ----------------------------------------------------------------------------
BattleFrontier_Lounge8_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_eq VAR_ARCEUS_EVENT, 2, BattleFrontier_Lounge8_EventScript_OldWomanDone
	goto_if_eq VAR_ARCEUS_EVENT, 1, BattleFrontier_Lounge8_EventScript_OldWomanAgain
	goto_if_set FLAG_GIRATINA_CAUGHT, BattleFrontier_Lounge8_EventScript_OldWomanReek
	goto_if_ge VAR_GIRATINA_EVENT, 1, BattleFrontier_Lounge8_EventScript_OldWomanTorn
	msgbox BattleFrontier_Lounge8_Text_OldWomanHum, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge8_EventScript_OldWomanShow
	end

BattleFrontier_Lounge8_EventScript_OldWomanTorn::
	msgbox BattleFrontier_Lounge8_Text_OldWomanTorn, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge8_EventScript_OldWomanShow
	end

BattleFrontier_Lounge8_EventScript_OldWomanReek::
	msgbox BattleFrontier_Lounge8_Text_OldWomanReek, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge8_EventScript_OldWomanShow
	end

@ "Show me one": the chosen slot's species decides. GIRATINA (either forme)
@ is the flute; an EGG or anything else gets a blessing.
BattleFrontier_Lounge8_EventScript_OldWomanShow::
	msgbox BattleFrontier_Lounge8_Text_OldWomanShowMe, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, BattleFrontier_Lounge8_EventScript_OldWomanNotNow
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_GIRATINA, BattleFrontier_Lounge8_EventScript_OldWomanGiratina
	goto_if_eq VAR_RESULT, SPECIES_GIRATINA_ORIGIN, BattleFrontier_Lounge8_EventScript_OldWomanGiratina
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge8_EventScript_OldWomanBlessEgg
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	msgbox BattleFrontier_Lounge8_Text_OldWomanBless, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_EventScript_OldWomanBlessEgg::
	msgbox BattleFrontier_Lounge8_Text_OldWomanBlessEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_EventScript_OldWomanNotNow::
	msgbox BattleFrontier_Lounge8_Text_OldWomanNotNow, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_EventScript_OldWomanGiratina::
	msgbox BattleFrontier_Lounge8_Text_OldWomanGiratina1, MSGBOX_DEFAULT
	msgbox BattleFrontier_Lounge8_Text_OldWomanGiratina2, MSGBOX_DEFAULT
	msgbox BattleFrontier_Lounge8_Text_OldWomanFlute, MSGBOX_DEFAULT
	setvar VAR_ARCEUS_EVENT, 1
	goto BattleFrontier_Lounge8_EventScript_OldWomanBlows
	end

BattleFrontier_Lounge8_EventScript_OldWomanAgain::
	msgbox BattleFrontier_Lounge8_Text_OldWomanAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge8_EventScript_OldWomanPatient
	goto BattleFrontier_Lounge8_EventScript_OldWomanBlows
	end

BattleFrontier_Lounge8_EventScript_OldWomanPatient::
	msgbox BattleFrontier_Lounge8_Text_OldWomanPatient, MSGBOX_DEFAULT
	release
	end

@ The flute: the player hears nothing, the room goes white, NAVEL ROCK's
@ summit (12, 18), at the foot of the path up to ARCEUS.
BattleFrontier_Lounge8_EventScript_OldWomanBlows::
	msgbox BattleFrontier_Lounge8_Text_OldWomanBlows, MSGBOX_DEFAULT
	closemessage
	warpwhitefade MAP_NAVEL_ROCK_TOP, 12, 18
	waitstate
	release
	end

BattleFrontier_Lounge8_EventScript_OldWomanDone::
	msgbox BattleFrontier_Lounge8_Text_OldWomanDone, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_Text_OldWomanHum:
	.string "Hush. Do you hear it?\p"
	.string "…No. Nobody does but me.\p"
	.string "A hum, like a flute with no one\n"
	.string "playing it. Every night, since I\l"
	.string "was a girl.\p"
	.string "It made this world, dear. The land,\n"
	.string "the sea, the two great beasts who\l"
	.string "squabble over them.\p"
	.string "It made the one it had to banish,\n"
	.string "too. It still listens.\p"
	.string "And I listen back.$"

BattleFrontier_Lounge8_Text_OldWomanTorn:
	.string "The hum has changed, child. It's\n"
	.string "sharper now. Frightened, almost.\p"
	.string "Something has clawed its way up\n"
	.string "from underneath. Something that was\l"
	.string "put down there on purpose.\p"
	.string "If you ever meet it… bring it to me.\n"
	.string "I'll know what to do.\p"
	.string "I have always known.$"

BattleFrontier_Lounge8_Text_OldWomanReek:
	.string "You smell of the underworld.\n"
	.string "Cold, and old, and angry.\p"
	.string "You've caught it, haven't you?\p"
	.string "Then show it to me. Here, now. I\n"
	.string "must see it with my own eyes.$"

BattleFrontier_Lounge8_Text_OldWomanShowMe:
	.string "Show me one you carry, dear. Any\n"
	.string "one. Let me see it.$"

BattleFrontier_Lounge8_Text_OldWomanBless:
	.string "The old woman laid a hand on\n"
	.string "{STR_VAR_1}.\p"
	.string "In the name of mighty ARCEUS, who\n"
	.string "shaped the land and the sea and you,\l"
	.string "little one: be blessed.\p"
	.string "{STR_VAR_1} looked blessed.\n"
	.string "Probably.$"

BattleFrontier_Lounge8_Text_OldWomanBlessEgg:
	.string "An EGG. Well, bless it, then. It\n"
	.string "can't object.\p"
	.string "In the name of mighty ARCEUS: be\n"
	.string "blessed, whatever you turn out to be.$"

BattleFrontier_Lounge8_Text_OldWomanNotNow:
	.string "Another time, then. It isn't going\n"
	.string "anywhere. Neither am I.$"

BattleFrontier_Lounge8_Text_OldWomanGiratina1:
	.string "…\p"
	.string "…!!!\p"
	.string "The KING OF THE UNDERWORLD! The\n"
	.string "BANISHED ONE! In my parlour!\p"
	.string "You've brought it to my door in a\n"
	.string "BALL, like a pet!$"

BattleFrontier_Lounge8_Text_OldWomanGiratina2:
	.string "Stand back, child. I know what must\n"
	.string "be done.\p"
	.string "It must be exorcised. Sent back to\n"
	.string "its maker, to answer for itself.\p"
	.string "I have known this since I was seven\n"
	.string "years old.$"

BattleFrontier_Lounge8_Text_OldWomanFlute:
	.string "The old woman drew a flute from her\n"
	.string "shawl. It was blue as deep water,\l"
	.string "and older than the house.\p"
	.string "I've had this all along, dear.\p"
	.string "All I ever needed was a reason.$"

BattleFrontier_Lounge8_Text_OldWomanBlows:
	.string "She set it to her lips and blew.\p"
	.string "{PLAYER} heard nothing at all.\p"
	.string "The room went white.$"

BattleFrontier_Lounge8_Text_OldWomanAgain:
	.string "It heard me. It is waiting for you\n"
	.string "on the rock above the sea, where\l"
	.string "the rainbow bird used to roost.\p"
	.string "Shall I play again?$"

BattleFrontier_Lounge8_Text_OldWomanPatient:
	.string "It is patient, dear.\p"
	.string "It has all the time there is.$"

BattleFrontier_Lounge8_Text_OldWomanDone:
	.string "The hum has stopped.\p"
	.string "Sixty years, and it has stopped. I\n"
	.string "don't know what to do with the\l"
	.string "quiet.\p"
	.string "…The BANISHED ONE is still in your\n"
	.string "BALL, isn't it. Right alongside its\l"
	.string "maker.\p"
	.string "Well. Let them argue it out.\n"
	.string "I've earned my rest.$"
