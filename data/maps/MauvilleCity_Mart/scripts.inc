MauvilleCity_Mart_MapScripts::
	.byte 0

MauvilleCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_X_ACCURACY
	pokemartlistend

@ Ten Gauntlets: the townsfolk follow the story (GetStoryGossipStage).
MauvilleCity_Mart_EventScript_ExpertM::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_Mart_EventScript_ExpertMEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_Mart_EventScript_ExpertMFreed
	msgbox MauvilleCity_Mart_Text_ExpertMOccupied, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_ExpertMFreed::
	msgbox MauvilleCity_Mart_Text_ExpertMFreed, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_ExpertMEnding::
	msgbox MauvilleCity_Mart_Text_ExpertMEnding, MSGBOX_NPC
	end

@ The man is the one vague hint at MAUVILLE's hidden helpers: while any of
@ them is unused he adds a second remark.
MauvilleCity_Mart_EventScript_Man::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_Mart_EventScript_ManEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_Mart_EventScript_ManFreed
	msgbox MauvilleCity_Mart_Text_ManOccupied, MSGBOX_DEFAULT
	goto MauvilleCity_Mart_EventScript_ManHint
	end

MauvilleCity_Mart_EventScript_ManFreed::
	msgbox MauvilleCity_Mart_Text_ManFreed, MSGBOX_DEFAULT
	goto MauvilleCity_Mart_EventScript_ManHint
	end

MauvilleCity_Mart_EventScript_ManEnding::
	msgbox MauvilleCity_Mart_Text_ManEnding, MSGBOX_DEFAULT
	goto MauvilleCity_Mart_EventScript_ManHint
	end

MauvilleCity_Mart_EventScript_ManHint::
	goto_if_unset FLAG_MAUVILLE_RAISE_1, MauvilleCity_Mart_EventScript_ManHintTell
	goto_if_unset FLAG_MAUVILLE_RAISE_2, MauvilleCity_Mart_EventScript_ManHintTell
	goto_if_unset FLAG_MAUVILLE_RAISE_3, MauvilleCity_Mart_EventScript_ManHintTell
	release
	end

MauvilleCity_Mart_EventScript_ManHintTell::
	msgbox MauvilleCity_Mart_Text_ManHint, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Mart_Text_ExpertMOccupied:
	.string "Stat-boosting items: X ATTACK,\n"
	.string "X DEFEND… The grunts bought the shelf\l"
	.string "bare this morning.\p"
	.string "They've stood outside ever since,\n"
	.string "waiting for orders. Something big.$"

MauvilleCity_Mart_Text_ExpertMFreed:
	.string "The shelves are full again! X ATTACK,\n"
	.string "X DEFEND, and all the rest.\p"
	.string "The grunts left a mountain of boosts\n"
	.string "behind. The clerk won't take returns.$"

MauvilleCity_Mart_Text_ExpertMEnding:
	.string "A temporary boost is only worth it if\n"
	.string "you survive to use it.\p"
	.string "The whole town did. Care for an\n"
	.string "X ATTACK?$"

MauvilleCity_Mart_Text_ManOccupied:
	.string "Use a move, or use an item…\n"
	.string "The TRAINER's decisions decide it all.\p"
	.string "The grunts decided to take a whole\n"
	.string "town. I wonder who decided that\l"
	.string "for them.$"

MauvilleCity_Mart_Text_ManFreed:
	.string "Use a move, or use an item…\n"
	.string "The TRAINER's decisions decide it all.\p"
	.string "This town decided to wait for you.\n"
	.string "It worked.$"

MauvilleCity_Mart_Text_ManEnding:
	.string "Use a move, or use an item…\n"
	.string "I know the best decision now: stay\l"
	.string "close to a TRAINER who wins.$"

MauvilleCity_Mart_Text_ManHint:
	.string "By the way, I hear a few folks in\n"
	.string "town can bring a POKéMON up to speed,\l"
	.string "if you ask nicely.\p"
	.string "I won't say who. Talk to everyone.$"

