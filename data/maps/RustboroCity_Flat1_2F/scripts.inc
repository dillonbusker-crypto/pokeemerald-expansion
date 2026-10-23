RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat1_2F_EventScript_WaldasDadEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat1_2F_EventScript_WaldasDadFreed
	msgbox RustboroCity_Flat1_2F_Text_WaldasDad, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadEnding::
	msgbox RustboroCity_Flat1_2F_Text_WaldasDadEnding, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFreed::
	msgbox RustboroCity_Flat1_2F_Text_WaldasDadFreed, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat1_2F_EventScript_WaldasMomEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat1_2F_EventScript_WaldasMomFreed
	msgbox RustboroCity_Flat1_2F_Text_WaldasMom, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_WaldasMomEnding::
	msgbox RustboroCity_Flat1_2F_Text_WaldasMomEnding, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_WaldasMomFreed::
	msgbox RustboroCity_Flat1_2F_Text_WaldasMomFreed, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_WaldasMom:
	.string "Having my husband home all day means\n"
	.string "three meals to plan, not one.\p"
	.string "I'm not complaining. Okay, I'm\n"
	.string "complaining a little.$"

RustboroCity_Flat1_2F_Text_WaldasMomFreed:
	.string "He got a letter. STONE's enquiry wants\n"
	.string "every researcher's notes.\p"
	.string "He writes them at the table all night.\n"
	.string "At least he's eating my cooking again.$"

RustboroCity_Flat1_2F_Text_WaldasMomEnding:
	.string "He's back at work. I make exactly one\n"
	.string "dinner a day, and I've never been\l"
	.string "happier.$"

RustboroCity_Flat1_2F_Text_WaldasDad:
	.string "Oh, hello! Welcome to the PEPPER\n"
	.string "household.\p"
	.string "I'm one of DEVON's researchers. Was.\n"
	.string "They sent us home with the ELITE FOUR\l"
	.string "in the lobby.\p"
	.string "I told my wife it's an inspection.\n"
	.string "WALDA laughs more with me home,\l"
	.string "so there's that.$"

RustboroCity_Flat1_2F_Text_WaldasDadFreed:
	.string "I worked on the auto-heal in the\n"
	.string "POKéNAV. The one that emptied the\l"
	.string "POKéMON CENTERS.\p"
	.string "I thought I was making life easier.\n"
	.string "I'll apologise to the NURSES myself.\p"
	.string "STONE has confessed. I'm still waiting\n"
	.string "for someone to ask for mine.$"

RustboroCity_Flat1_2F_Text_WaldasDadEnding:
	.string "I'm back at DEVON. The auto-heal is on\n"
	.string "my desk, in pieces.\p"
	.string "I'm going to rebuild it so it sends\n"
	.string "people to the CENTER, not away from it.$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "It's a POKéMON plush DOLL!$"

