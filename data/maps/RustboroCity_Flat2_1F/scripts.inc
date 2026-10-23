RustboroCity_Flat2_1F_MapScripts::
	.byte 0

RustboroCity_Flat2_1F_EventScript_OldWoman::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat2_1F_EventScript_OldWomanEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat2_1F_EventScript_OldWomanFreed
	msgbox RustboroCity_Flat2_1F_Text_OldWoman, MSGBOX_NPC
	end

RustboroCity_Flat2_1F_EventScript_OldWomanEnding::
	msgbox RustboroCity_Flat2_1F_Text_OldWomanEnding, MSGBOX_NPC
	end

RustboroCity_Flat2_1F_EventScript_OldWomanFreed::
	msgbox RustboroCity_Flat2_1F_Text_OldWomanFreed, MSGBOX_NPC
	end

RustboroCity_Flat2_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox RustboroCity_Flat2_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_Flat2_1F_Text_OldWoman:
	.string "DEVON's workers live in this building.\n"
	.string "Nobody's been to work in days. It's\l"
	.string "like one long Sunday.\p"
	.string "Except upstairs. Somebody up there is\n"
	.string "still keeping shift hours, rattling\l"
	.string "about at five in the morning.$"

RustboroCity_Flat2_1F_Text_OldWomanFreed:
	.string "The neighbours are being called in to\n"
	.string "answer questions about DEVON.\p"
	.string "Upstairs, somebody is still busy at\n"
	.string "something. I've stopped asking what.$"

RustboroCity_Flat2_1F_Text_OldWomanEnding:
	.string "DEVON's workers are going back, under\n"
	.string "a new sign. It's a Monday again.\p"
	.string "Upstairs is still busy at something.\n"
	.string "I hope they get some rest.$"

RustboroCity_Flat2_1F_Text_Skitty:
	.string "SKITTY: Gyaaaah!$"

