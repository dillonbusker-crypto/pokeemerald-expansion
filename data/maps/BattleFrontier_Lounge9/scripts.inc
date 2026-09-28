BattleFrontier_Lounge9_MapScripts::
	.byte 0

@ Ten Gauntlets: a support group for trainers of banned POKeMON
@ (easter-eggs-spec.md, #5). The empty seat in the middle is SMEARGLE's.

BattleFrontier_Lounge9_EventScript_Leader::
	msgbox BattleFrontier_Lounge9_Text_Leader, MSGBOX_NPC
	end

BattleFrontier_Lounge9_EventScript_Wobbuffet::
	msgbox BattleFrontier_Lounge9_Text_Wobbuffet, MSGBOX_NPC
	end

BattleFrontier_Lounge9_EventScript_Shedinja::
	msgbox BattleFrontier_Lounge9_Text_Shedinja, MSGBOX_NPC
	end

BattleFrontier_Lounge9_EventScript_Palafin::
	msgbox BattleFrontier_Lounge9_Text_Palafin, MSGBOX_NPC
	end

BattleFrontier_Lounge9_EventScript_Wishiwashi::
	msgbox BattleFrontier_Lounge9_Text_Wishiwashi, MSGBOX_NPC
	end

BattleFrontier_Lounge9_Text_Leader:
	.string "Welcome. We're all friends here.\n"
	.string "Nobody judges.\p"
	.string "...Did you bring a SMEARGLE? We're\n"
	.string "still waiting on our SMEARGLE\l"
	.string "member.$"

BattleFrontier_Lounge9_Text_Wobbuffet:
	.string "Shadow Tag, Encore, Counter... He\n"
	.string "only ever wanted to help.\p"
	.string "And they call HIM the problem?$"

BattleFrontier_Lounge9_Text_Shedinja:
	.string "One HP! One! How is that fair to\n"
	.string "anyone?\p"
	.string "...They said something about\n"
	.string "Wonder Guard.$"

BattleFrontier_Lounge9_Text_Palafin:
	.string "It was only 457 BST when I walked\n"
	.string "in!$"

BattleFrontier_Lounge9_Text_Wishiwashi:
	.string "It's small. It's so small.\p"
	.string "...Until it isn't.$"
