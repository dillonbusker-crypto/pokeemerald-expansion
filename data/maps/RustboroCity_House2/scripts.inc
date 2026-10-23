RustboroCity_House2_MapScripts::
	.byte 0

RustboroCity_House2_EventScript_PokefanF::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_House2_EventScript_PokefanFEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_House2_EventScript_PokefanFFreed
	msgbox RustboroCity_House2_Text_PokefanF, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_PokefanFEnding::
	msgbox RustboroCity_House2_Text_PokefanFEnding, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_PokefanFFreed::
	msgbox RustboroCity_House2_Text_PokefanFFreed, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_LittleGirl::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_House2_EventScript_LittleGirlEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_House2_EventScript_LittleGirlFreed
	msgbox RustboroCity_House2_Text_LittleGirl, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_LittleGirlEnding::
	msgbox RustboroCity_House2_Text_LittleGirlEnding, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_LittleGirlFreed::
	msgbox RustboroCity_House2_Text_LittleGirlFreed, MSGBOX_NPC
	end

RustboroCity_House2_Text_PokefanF:
	.string "I used to say the TRAINER'S SCHOOL\n"
	.string "could turn you into a GYM LEADER.\p"
	.string "But ROXANNE left her GYM to work for\n"
	.string "the FRONTIER. I don't know what to\l"
	.string "tell my daughter about that.$"

RustboroCity_House2_Text_PokefanFFreed:
	.string "ROXANNE is back at the GYM!\p"
	.string "I told my daughter: even a GYM LEADER\n"
	.string "can lose her way and come home.\l"
	.string "It's a better lesson than the SCHOOL's.$"

RustboroCity_House2_Text_PokefanFEnding:
	.string "My daughter wants to be a GYM LEADER.\p"
	.string "I said yes before she finished the\n"
	.string "sentence.$"

RustboroCity_House2_Text_LittleGirl:
	.string "ROXANNE is my hero. She's not at the\n"
	.string "GYM, and Mom won't say where she's\l"
	.string "gone.\p"
	.string "I made her a drawing in case she\n"
	.string "comes back.$"

RustboroCity_House2_Text_LittleGirlFreed:
	.string "ROXANNE came back! I gave her my\n"
	.string "drawing!\p"
	.string "She really knows a lot about\n"
	.string "POKéMON. And she's strong, too!$"

RustboroCity_House2_Text_LittleGirlEnding:
	.string "I'm going to be as strong as\n"
	.string "ROXANNE and know as much as she does.\p"
	.string "I'm going to start with rocks.$"

