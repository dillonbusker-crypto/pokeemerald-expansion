BattleFrontier_Mart_MapScripts::
	.byte 0

@ Ten Gauntlets: the shelves are bare - men in suits bought up the stock
@ (storyline.md). The vanilla pokemart list below is unreferenced now.
BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	msgbox BattleFrontier_Mart_Text_BoughtOut, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_FRONTIER_MART_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
	.string "We came here to chaperon our\n"
	.string "grandson.\p"
	.string "We took him to a fortune-teller\n"
	.string "out west, past the BATTLE DOME.\l"
	.string "She told him every POKéMON the\l"
	.string "boss would use!\p"
	.string "200 FP, mind you. But he says it\n"
	.string "was worth every point.$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
	.string "Dear, what do you think of this?\n"
	.string "Wouldn't this make a nice gift?\p"
	.string "It's…PRO…TE…IN?\n"
	.string "It sounds delicious, doesn't it?$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
	.string "I came in to buy POTIONS out of\n"
	.string "habit. BAG items don't even work\l"
	.string "during a run.\p"
	.string "...Doesn't matter. The shelves are\n"
	.string "empty anyway.$"

BattleFrontier_Mart_Text_BoughtOut:
	.string "Welcome... I'm sorry, but we have\n"
	.string "nothing to sell.\p"
	.string "Some men in suits came in and\n"
	.string "bought up all our stock. We\l"
	.string "haven't had a delivery since.\p"
	.string "If you need something, try the\n"
	.string "EXCHANGE SERVICE CORNER.\p"
	.string "...Though I hear some of our\n"
	.string "missing deliveries turn up in the\l"
	.string "hands of a man who sells things\l"
	.string "before anyone else has them.\p"
	.string "I didn't tell you that.$"
