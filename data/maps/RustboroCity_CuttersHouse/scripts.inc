RustboroCity_CuttersHouse_MapScripts::
	.byte 0

@ Ten Gauntlets: no HM Cut here. The Cutter just talks about the island; the
@ original gift script below is unreachable.
RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	msgbox RustboroCity_CuttersHouse_Text_TenGauntletsNoHM, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_CutterVanilla::
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_CuttersHouse_EventScript_LassEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_CuttersHouse_EventScript_LassFreed
	msgbox RustboroCity_CuttersHouse_Text_Lass, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_EventScript_LassEnding::
	msgbox RustboroCity_CuttersHouse_Text_LassEnding, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_EventScript_LassFreed::
	msgbox RustboroCity_CuttersHouse_Text_LassFreed, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_TenGauntletsNoHM:
	.string "I used to hand out HIDDEN MACHINES to\n"
	.string "any TRAINER with a spark.\p"
	.string "But everyone's off at that island\n"
	.string "now. I'm just waiting for the day\l"
	.string "they all come home.$"

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "That determined expression…\n"
	.string "That limber way you move…\l"
	.string "And your well-trained POKéMON…\p"
	.string "You're obviously a skilled TRAINER!\p"
	.string "No, wait, don't say a word.\n"
	.string "I can tell just by looking at you.\p"
	.string "I'm sure that you can put this\n"
	.string "HIDDEN MACHINE to good use.\p"
	.string "No need to be modest or shy.\n"
	.string "Go on, take it!$"

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "That HIDDEN MACHINE, or HM for\n"
	.string "short, is CUT.\p"
	.string "An HM move is one that can be used\n"
	.string "by POKéMON outside of battle.\p"
	.string "Any POKéMON that's learned CUT can\n"
	.string "chop down thin trees if the TRAINER\l"
	.string "has earned the STONE BADGE.\p"
	.string "And, unlike a TM, an HM can be used\n"
	.string "more than once.$"

RustboroCity_CuttersHouse_Text_Lass:
	.string "When they expanded RUSTBORO, my dad\n"
	.string "cleared the trees with CUT.\p"
	.string "Now he just watches the door. He's\n"
	.string "waiting for everyone to come home\l"
	.string "from the island.$"

RustboroCity_CuttersHouse_Text_LassFreed:
	.string "Dad polished his old CUT sign this\n"
	.string "morning. The roads are open.\p"
	.string "He says trainers might come back now.\n"
	.string "He won't say it out loud, in case it\l"
	.string "jinxes it.$"

RustboroCity_CuttersHouse_Text_LassEnding:
	.string "Someone asked about CUT today!\n"
	.string "Dad cried a little.\p"
	.string "He taught them for an hour, for free.\n"
	.string "The HM can wait, he said. The lesson\l"
	.string "couldn't.$"

