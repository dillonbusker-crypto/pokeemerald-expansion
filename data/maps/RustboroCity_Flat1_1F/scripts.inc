RustboroCity_Flat1_1F_MapScripts::
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat1_1F_EventScript_ManEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat1_1F_EventScript_ManFreed
	msgbox RustboroCity_Flat1_1F_Text_Man, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_ManEnding::
	msgbox RustboroCity_Flat1_1F_Text_ManEnding, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_ManFreed::
	msgbox RustboroCity_Flat1_1F_Text_ManFreed, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat1_1F_EventScript_WomanEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat1_1F_EventScript_WomanFreed
	msgbox RustboroCity_Flat1_1F_Text_Woman, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_WomanEnding::
	msgbox RustboroCity_Flat1_1F_Text_WomanEnding, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_WomanFreed::
	msgbox RustboroCity_Flat1_1F_Text_WomanFreed, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_Text_Man:
	.string "Every POKéMON has an ABILITY, my\n"
	.string "upstairs neighbour likes to say.\p"
	.string "He's one of DEVON's researchers.\n"
	.string "He hasn't been downstairs since the\l"
	.string "ELITE FOUR arrived.$"

RustboroCity_Flat1_1F_Text_ManFreed:
	.string "My neighbour upstairs got a letter.\n"
	.string "STONE's enquiry wants every\l"
	.string "researcher's notes.\p"
	.string "He says he'll write them all, if it\n"
	.string "takes the winter.$"

RustboroCity_Flat1_1F_Text_ManEnding:
	.string "My neighbour is back at DEVON, and\n"
	.string "he's whistling on the stairs again.\p"
	.string "Every POKéMON has an ABILITY. His is\n"
	.string "cheering up the stairwell.$"

RustboroCity_Flat1_1F_Text_Woman:
	.string "POKéMON are such strange creatures.\n"
	.string "People are stranger.\p"
	.string "A company that makes gadgets for\n"
	.string "everyone, and now the ELITE FOUR\l"
	.string "guard its door.$"

RustboroCity_Flat1_1F_Text_WomanFreed:
	.string "POKéMON are such strange creatures.\p"
	.string "But PRESIDENT STONE confessing? That\n"
	.string "was the strangest thing of all.$"

RustboroCity_Flat1_1F_Text_WomanEnding:
	.string "POKéMON are such strange creatures.\n"
	.string "People are trying to be better ones.\p"
	.string "There's a notice on the door: “New\n"
	.string "management. Same neighbours.”$"

