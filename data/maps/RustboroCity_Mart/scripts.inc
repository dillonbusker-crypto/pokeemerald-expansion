RustboroCity_Mart_MapScripts::
	.byte 0

RustboroCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_unset FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_PokemartBasic
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_PokemartExpanded
	end

RustboroCity_Mart_EventScript_PokemartBasic::
	pokemart RustboroCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
RustboroCity_Mart_Pokemart_Basic:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	pokemartlistend

RustboroCity_Mart_EventScript_PokemartExpanded::
	pokemart RustboroCity_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
RustboroCity_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	pokemartlistend

RustboroCity_Mart_EventScript_PokefanF::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Mart_EventScript_PokefanFEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Mart_EventScript_PokefanFFreed
	msgbox RustboroCity_Mart_Text_PokefanF, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_PokefanFEnding::
	msgbox RustboroCity_Mart_Text_PokefanFEnding, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_PokefanFFreed::
	msgbox RustboroCity_Mart_Text_PokefanFFreed, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_Boy::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Mart_EventScript_BoyEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Mart_EventScript_BoyFreed
	msgbox RustboroCity_Mart_Text_Boy, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BoyEnding::
	msgbox RustboroCity_Mart_Text_BoyEnding, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BoyFreed::
	msgbox RustboroCity_Mart_Text_BoyFreed, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BugCatcher::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Mart_EventScript_BugCatcherEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Mart_EventScript_BugCatcherFreed
	msgbox RustboroCity_Mart_Text_BugCatcher, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BugCatcherEnding::
	msgbox RustboroCity_Mart_Text_BugCatcherEnding, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BugCatcherFreed::
	msgbox RustboroCity_Mart_Text_BugCatcherFreed, MSGBOX_NPC
	end

RustboroCity_Mart_Text_PokefanF:
	.string "No deliveries since the ELITE FOUR\n"
	.string "took DEVON. The trucks start there.\p"
	.string "The clerk is rationing ANTIDOTES, so\n"
	.string "I'm buying PARLYZ HEALS before they\l"
	.string "go too.$"

RustboroCity_Mart_Text_PokefanFFreed:
	.string "The trucks are running again, slowly.\n"
	.string "Same shelf, new boxes.\p"
	.string "Whatever happened at DEVON, I'm\n"
	.string "buying ANTIDOTES like it's a holiday.$"

RustboroCity_Mart_Text_PokefanFEnding:
	.string "The shelves are full! I bought an\n"
	.string "ANTIDOTE I don't need, just to carry\l"
	.string "it home.$"

RustboroCity_Mart_Text_Boy:
	.string "I keep buying POTIONS, even though the\n"
	.string "POKéNAV heals my team for free.\p"
	.string "It feels wrong to walk out of here\n"
	.string "with nothing.$"

RustboroCity_Mart_Text_BoyFreed:
	.string "They say the free healing is DEVON's\n"
	.string "doing. Maybe I'll keep my POTIONS\l"
	.string "stocked, just in case.$"

RustboroCity_Mart_Text_BoyEnding:
	.string "I used a SUPER POTION on a real\n"
	.string "emergency today! First time in a year.\p"
	.string "Dad cheered. I think he missed the\n"
	.string "sound of the lid popping.$"

RustboroCity_Mart_Text_BugCatcher:
	.string "I'm getting an ESCAPE ROPE, just in\n"
	.string "case.\p"
	.string "In case of what? Everything. The ELITE\n"
	.string "FOUR, the shut roads, whatever's\l"
	.string "next.$"

RustboroCity_Mart_Text_BugCatcherFreed:
	.string "I heard the tunnel isn't where it\n"
	.string "used to be.\p"
	.string "An ESCAPE ROPE can't help if the\n"
	.string "entrance moves.$"

RustboroCity_Mart_Text_BugCatcherEnding:
	.string "I took my ESCAPE ROPE back. Never\n"
	.string "needed it.\p"
	.string "The clerk wouldn't refund it, so now I\n"
	.string "have a story and a rope.$"

