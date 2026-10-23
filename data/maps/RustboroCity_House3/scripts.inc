RustboroCity_House3_MapScripts::
	.byte 0

RustboroCity_House3_EventScript_OldMan::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_House3_EventScript_OldManEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_House3_EventScript_OldManFreed
	msgbox RustboroCity_House3_Text_OldMan, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldManEnding::
	msgbox RustboroCity_House3_Text_OldManEnding, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldManFreed::
	msgbox RustboroCity_House3_Text_OldManFreed, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWoman::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_House3_EventScript_OldWomanEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_House3_EventScript_OldWomanFreed
	msgbox RustboroCity_House3_Text_OldWoman, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWomanEnding::
	msgbox RustboroCity_House3_Text_OldWomanEnding, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWomanFreed::
	msgbox RustboroCity_House3_Text_OldWomanFreed, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
RustboroCity_House3_EventScript_Pekachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_OldMan:
	.string "I name everything. My POKéNAV is\n"
	.string "“THIEF”.\p"
	.string "It stole the NURSE's job and the\n"
	.string "town's reason to stand in line.\l"
	.string "Perfectly suited, don't you think?$"

RustboroCity_House3_Text_OldManFreed:
	.string "STONE confessed to something. I've\n"
	.string "renamed my POKéNAV “SUSPECT”.\p"
	.string "It suits it.$"

RustboroCity_House3_Text_OldManEnding:
	.string "New management at DEVON means my\n"
	.string "POKéNAV needs a new name.\p"
	.string "“PROBATION”. We'll see how it\n"
	.string "behaves.$"

RustboroCity_House3_Text_OldWoman:
	.string "I have a name for the ELITE FOUR, too.\n"
	.string "“Those rude young people who can't go\l"
	.string "home.”\p"
	.string "They've sat on DEVON's doorstep for\n"
	.string "days. I bet nobody's fed them.$"

RustboroCity_House3_Text_OldWomanFreed:
	.string "Someone beat the ELITE FOUR on DEVON's\n"
	.string "doorstep. I had made them a pie, too.\p"
	.string "I'll give it to whoever won.$"

RustboroCity_House3_Text_OldWomanEnding:
	.string "I baked for the whole street today.\p"
	.string "When something ends, you bake.$"

RustboroCity_House3_Text_Pekachu:
	.string "PEKACHU: Peka!$"

