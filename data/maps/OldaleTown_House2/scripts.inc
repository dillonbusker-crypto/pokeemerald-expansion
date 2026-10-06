OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_NORMAN, OldaleTown_House2_Woman_Gossip0
	case GOSSIP_STEVEN, OldaleTown_House2_Woman_Gossip1
	case GOSSIP_SYSTEM_DOWN, OldaleTown_House2_Woman_Gossip2
	case GOSSIP_SMUGGLER, OldaleTown_House2_Woman_Gossip3
	case GOSSIP_ANABEL, OldaleTown_House2_Woman_Gossip4
	case GOSSIP_ARREST, OldaleTown_House2_Woman_Gossip5
	case GOSSIP_PALACE, OldaleTown_House2_Woman_Gossip5
	case GOSSIP_RAID, OldaleTown_House2_Woman_Gossip6
	case GOSSIP_TAKEN, OldaleTown_House2_Woman_Gossip6
	case GOSSIP_STANDOFF, OldaleTown_House2_Woman_Gossip7
	case GOSSIP_SIEGE, OldaleTown_House2_Woman_Gossip8
	case GOSSIP_AFTERMATH, OldaleTown_House2_Woman_Gossip9
	case GOSSIP_DEVON, OldaleTown_House2_Woman_Gossip10
	case GOSSIP_DEVON_FREED, OldaleTown_House2_Woman_Gossip11
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
OldaleTown_House2_Woman_Gossip0::
	msgbox OldaleTown_House2_Woman_Text_Gossip0, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip1::
	msgbox OldaleTown_House2_Woman_Text_Gossip1, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip2::
	msgbox OldaleTown_House2_Woman_Text_Gossip2, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip3::
	msgbox OldaleTown_House2_Woman_Text_Gossip3, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip4::
	msgbox OldaleTown_House2_Woman_Text_Gossip4, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip5::
	msgbox OldaleTown_House2_Woman_Text_Gossip5, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip6::
	msgbox OldaleTown_House2_Woman_Text_Gossip6, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip7::
	msgbox OldaleTown_House2_Woman_Text_Gossip7, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip8::
	msgbox OldaleTown_House2_Woman_Text_Gossip8, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Text_Gossip8:
	.string "My grandson says the FRONTIER is\n"
	.string "baking in the sun, and the CHAMPION\l"
	.string "is there!\p"
	.string "I told him to stay indoors.$"

OldaleTown_House2_Woman_Gossip9::
	msgbox OldaleTown_House2_Woman_Text_Gossip9, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Text_Gossip9:
	.string "My grandson says the man who owns\n"
	.string "the FRONTIER is gone, and the shops\l"
	.string "are free now!\p"
	.string "He's not coming home after all.\n"
	.string "He's shopping.$"

OldaleTown_House2_Woman_Gossip10::
	msgbox OldaleTown_House2_Woman_Text_Gossip10, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Gossip11::
	msgbox OldaleTown_House2_Woman_Text_Gossip11, MSGBOX_NPC
	end

OldaleTown_House2_Woman_Text_Gossip10:
	.string "Now my grandson says the ELITE FOUR\n"
	.string "are guarding DEVON CORPORATION.\p"
	.string "I told him to stay put. He's still\n"
	.string "shopping.$"

OldaleTown_House2_Woman_Text_Gossip11:
	.string "My grandson says some child beat\n"
	.string "the whole ELITE FOUR at DEVON.\p"
	.string "He wants to be a TRAINER now.\n"
	.string "I've told him to finish his soup.$"

OldaleTown_House2_Woman_Text_Gossip0:
	.string "My grandson called from the FRONTIER!\p"
	.string "He says a GYM LEADER barged into the\n"
	.string "BATTLE TOWER, shouting for the man\l"
	.string "who runs the place. My, my.$"

OldaleTown_House2_Woman_Text_Gossip1:
	.string "My grandson says STEVEN STONE is on\n"
	.string "that island! The former CHAMPION!\p"
	.string "He asked for an autograph, and STEVEN\n"
	.string "said he was only there to look at the\l"
	.string "walls.$"

OldaleTown_House2_Woman_Text_Gossip2:
	.string "My grandson says every shop on that\n"
	.string "island has gone dark. He can't spend a\l"
	.string "single point.\p"
	.string "At least he's eating the care\n"
	.string "packages I send.$"

OldaleTown_House2_Woman_Text_Gossip3:
	.string "My grandson says the International\n"
	.string "Police caught a smuggler sneaking off\l"
	.string "the island!\p"
	.string "He says it's the most exciting thing\n"
	.string "that's happened there all year.$"

OldaleTown_House2_Woman_Text_Gossip4:
	.string "My grandson says someone beat the\n"
	.string "SALON MAIDEN, ANABEL. Nobody does\l"
	.string "that!\p"
	.string "A kid from LITTLEROOT, he says. ...Was\n"
	.string "it you?$"

OldaleTown_House2_Woman_Text_Gossip5:
	.string "My grandson says SCOTT himself\n"
	.string "arrested a man who sold things under\l"
	.string "the table.\p"
	.string "And the radio says the ELITE FOUR\n"
	.string "have gone missing. What is the world\l"
	.string "coming to?$"

OldaleTown_House2_Woman_Text_Gossip6:
	.string "Oh, it's dreadful. Men in suits tore\n"
	.string "PROF. BIRCH's LAB apart, they say.\p"
	.string "I told my grandson to stay on that\n"
	.string "island, where it's safe.$"

OldaleTown_House2_Woman_Text_Gossip7:
	.string "My grandson called in a panic. STEVEN\n"
	.string "STONE lost a battle to the man who\l"
	.string "owns the FRONTIER!\p"
	.string "He says that man's MEWTWO is still\n"
	.string "Mega Evolved. He wants to come home. I\l"
	.string "told him yes.$"

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "My grandson went off to the BATTLE\n"
	.string "FRONTIER.\p"
	.string "He says his POKéMON haven't grown\n"
	.string "one bit since he got there. He\l"
	.string "says that's normal there. Is it?$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "If the POKéMON with you become\n"
	.string "stronger, you'll be able to go farther\l"
	.string "away from here.$"

