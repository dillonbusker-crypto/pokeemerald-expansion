RustboroCity_Flat2_3F_MapScripts::
	.byte 0

RustboroCity_Flat2_3F_EventScript_DevonEmployee::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat2_3F_EventScript_DevonEmployeeEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat2_3F_EventScript_DevonEmployeeFreed
	msgbox RustboroCity_Flat2_3F_Text_DevonEmployee, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_EventScript_DevonEmployeeEnding::
	msgbox RustboroCity_Flat2_3F_Text_DevonEmployeeEnding, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_EventScript_DevonEmployeeFreed::
	msgbox RustboroCity_Flat2_3F_Text_DevonEmployeeFreed, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_RAISE_2, RustboroCity_Flat2_3F_EventScript_WomanUsed
	msgbox RustboroCity_Flat2_3F_Text_WomanOffer, MSGBOX_DEFAULT
	msgbox RustboroCity_Flat2_3F_Text_WomanAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat2_3F_EventScript_WomanNotNow
RustboroCity_Flat2_3F_EventScript_WomanPick::
	msgbox RustboroCity_Flat2_3F_Text_WomanWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, RustboroCity_Flat2_3F_EventScript_WomanNotNow
	setvar VAR_0x8005, 55
	special RaiseMonToLevel
	goto_if_eq VAR_RESULT, 1, RustboroCity_Flat2_3F_EventScript_WomanEgg
	goto_if_eq VAR_RESULT, 2, RustboroCity_Flat2_3F_EventScript_WomanTooStrong
	setflag FLAG_RUSTBORO_RAISE_2
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	playfanfare MUS_LEVEL_UP
	message RustboroCity_Flat2_3F_Text_WomanGrew
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox RustboroCity_Flat2_3F_Text_WomanDone, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_3F_EventScript_WomanEgg::
	msgbox RustboroCity_Flat2_3F_Text_WomanEgg, MSGBOX_DEFAULT
	goto RustboroCity_Flat2_3F_EventScript_WomanPick
	end

RustboroCity_Flat2_3F_EventScript_WomanTooStrong::
	msgbox RustboroCity_Flat2_3F_Text_WomanTooStrong, MSGBOX_DEFAULT
	goto RustboroCity_Flat2_3F_EventScript_WomanPick
	end

RustboroCity_Flat2_3F_EventScript_WomanNotNow::
	msgbox RustboroCity_Flat2_3F_Text_WomanNotNow, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_3F_EventScript_WomanUsed::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat2_3F_EventScript_WomanUsedEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat2_3F_EventScript_WomanUsedFreed
	msgbox RustboroCity_Flat2_3F_Text_WomanUsed, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_3F_EventScript_WomanUsedEnding::
	msgbox RustboroCity_Flat2_3F_Text_WomanUsedEnding, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_3F_EventScript_WomanUsedFreed::
	msgbox RustboroCity_Flat2_3F_Text_WomanUsedFreed, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_3F_Text_DevonEmployee:
	.string "Our PRESIDENT likes to collect rare\n"
	.string "stones. I thought it was a hobby.\p"
	.string "With the ELITE FOUR in the lobby, I've\n"
	.string "started to wonder what he was\l"
	.string "collecting them for.$"

RustboroCity_Flat2_3F_Text_DevonEmployeeFreed:
	.string "I won't repeat what STONE confessed.\n"
	.string "I'm a DEVON man.\p"
	.string "But the stones… Everyone knew he kept\n"
	.string "a vault of them. I never asked how\l"
	.string "many.$"

RustboroCity_Flat2_3F_Text_DevonEmployeeEnding:
	.string "The new management are cataloguing the\n"
	.string "PRESIDENT's stone collection. I helped.\p"
	.string "Some of them hum.$"

RustboroCity_Flat2_3F_Text_WomanOffer:
	.string "Oh! A visitor. Forgive the sheets,\n"
	.string "I'm still on my old shift hours.\p"
	.string "I was a nurse at the POKéMON CENTER,\n"
	.string "until the POKéNAV took the work.\l"
	.string "They gave me a certificate.\p"
	.string "I kept one thing: the full recovery\n"
	.string "course we ran for POKéMON coming off\l"
	.string "a long illness. Rest, feeding, drills.\p"
	.string "It brings one up to LV. 55. No\n"
	.string "further. And I have the supplies for\l"
	.string "one patient.$"

RustboroCity_Flat2_3F_Text_WomanAsk:
	.string "Shall I look after one of yours?$"

RustboroCity_Flat2_3F_Text_WomanWhich:
	.string "Which POKéMON is the patient?$"

RustboroCity_Flat2_3F_Text_WomanNotNow:
	.string "Of course. The sheets are fresh\n"
	.string "whenever you need them.$"

RustboroCity_Flat2_3F_Text_WomanEgg:
	.string "An EGG is perfectly well, dear.\n"
	.string "Nothing to treat. Choose another.$"

RustboroCity_Flat2_3F_Text_WomanTooStrong:
	.string "That one is stronger than my course can\n"
	.string "make it. Choose another.$"

RustboroCity_Flat2_3F_Text_WomanGrew:
	.string "The full course ran through the night.\p"
	.string "{STR_VAR_1} grew to LV. 55!$"

RustboroCity_Flat2_3F_Text_WomanDone:
	.string "There. Good as new, and then some.\n"
	.string "That was my last set of supplies.\l"
	.string "I enjoyed it.$"

RustboroCity_Flat2_3F_Text_WomanUsed:
	.string "I'm out of supplies, but I keep the\n"
	.string "sheets folded. Habit. Someone might\l"
	.string "need them.$"

RustboroCity_Flat2_3F_Text_WomanUsedFreed:
	.string "People talk about the CENTERS opening\n"
	.string "up again. I'm keeping the sheets\l"
	.string "folded, just in case.$"

RustboroCity_Flat2_3F_Text_WomanUsedEnding:
	.string "They've asked me back to the CENTER,\n"
	.string "part time. I said I'd think about it.\p"
	.string "I've already started packing.$"

