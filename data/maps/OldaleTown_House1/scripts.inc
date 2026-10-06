OldaleTown_House1_MapScripts::
	.byte 0

OldaleTown_House1_EventScript_Woman::
	msgbox OldaleTown_House1_Text_LeftPokemonGoesOutFirst, MSGBOX_NPC
	end

OldaleTown_House1_Text_LeftPokemonGoesOutFirst:
	.string "When a POKéMON battle starts, the one\n"
	.string "at the left of the list goes out first.\p"
	.string "So, when you get more POKéMON in your\n"
	.string "party, try switching around the order\l"
	.string "of your POKéMON.\p"
	.string "It could give you an advantage.$"

@ ============================================================================
@ Ten Gauntlets: the Paradox researcher. Show him a Paradox Pokemon he hasn't
@ seen and he pays a BOOSTER ENERGY, which the shop doesn't sell: one per
@ species, any time (OldaleCheckParadox, src/facility.c).
@ ============================================================================
OldaleTown_House1_EventScript_ParadoxResearcher::
	lock
	faceplayer
	msgbox OldaleTown_House1_Text_ResearcherIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OldaleTown_House1_EventScript_ResearcherNo
OldaleTown_House1_EventScript_ResearcherPick::
	msgbox OldaleTown_House1_Text_ResearcherWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, OldaleTown_House1_EventScript_ResearcherNo
	special OldaleCheckParadox
	goto_if_eq VAR_RESULT, 0, OldaleTown_House1_EventScript_ResearcherNotParadox
	goto_if_eq VAR_RESULT, 2, OldaleTown_House1_EventScript_ResearcherSeen
	msgbox OldaleTown_House1_Text_ResearcherNew, MSGBOX_DEFAULT
	giveitem ITEM_BOOSTER_ENERGY
	goto_if_eq VAR_RESULT, FALSE, OldaleTown_House1_EventScript_ResearcherBagFull
	special OldaleMarkParadoxShown
	special OldaleCheckParadox
	msgbox OldaleTown_House1_Text_ResearcherThanks, MSGBOX_DEFAULT
	release
	end

OldaleTown_House1_EventScript_ResearcherNotParadox::
	msgbox OldaleTown_House1_Text_ResearcherNotParadox, MSGBOX_DEFAULT
	release
	end

OldaleTown_House1_EventScript_ResearcherSeen::
	msgbox OldaleTown_House1_Text_ResearcherSeen, MSGBOX_DEFAULT
	release
	end

OldaleTown_House1_EventScript_ResearcherBagFull::
	msgbox OldaleTown_House1_Text_ResearcherBagFull, MSGBOX_DEFAULT
	release
	end

OldaleTown_House1_EventScript_ResearcherNo::
	msgbox OldaleTown_House1_Text_ResearcherNo, MSGBOX_DEFAULT
	release
	end

OldaleTown_House1_Text_ResearcherIntro:
	.string "I study POKéMON out of their own\n"
	.string "time. From the deep past, and from\l"
	.string "a future that hasn't happened yet.\p"
	.string "Twenty kinds, by my count, and I've\n"
	.string "only ever seen them in photographs.\p"
	.string "If you show me one I haven't seen,\n"
	.string "I'll pay you in BOOSTER ENERGY.\l"
	.string "It's the only thing they'll hold\l"
	.string "that I can't get anywhere else.\p"
	.string "Do you have one with you?$"

OldaleTown_House1_Text_ResearcherWhich:
	.string "Which one?$"

OldaleTown_House1_Text_ResearcherNew:
	.string "A {STR_VAR_1}! In the flesh!\p"
	.string "Hold still… Let me write this\n"
	.string "down… Marvelous.\p"
	.string "A deal is a deal.$"

OldaleTown_House1_Text_ResearcherThanks:
	.string "That's {STR_VAR_2} of the twenty.\p"
	.string "Bring me another kind, any time,\n"
	.string "and there's another one in it.$"

OldaleTown_House1_Text_ResearcherNotParadox:
	.string "Hm. That one belongs to the here\n"
	.string "and now. Not what I'm after.$"

OldaleTown_House1_Text_ResearcherSeen:
	.string "{STR_VAR_1}… I've already made my\n"
	.string "notes on that one.\p"
	.string "Bring me a kind I haven't seen.$"

OldaleTown_House1_Text_ResearcherBagFull:
	.string "Your BAG is full. Come back for it\n"
	.string "when you've made room.$"

OldaleTown_House1_Text_ResearcherNo:
	.string "The offer stands. Any time.$"
