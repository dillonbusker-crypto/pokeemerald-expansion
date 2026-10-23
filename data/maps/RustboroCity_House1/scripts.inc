RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_House1_EventScript_TraderEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_House1_EventScript_TraderFreed
	msgbox RustboroCity_House1_Text_Trader, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TraderEnding::
	msgbox RustboroCity_House1_Text_TraderEnding, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TraderFreed::
	msgbox RustboroCity_House1_Text_TraderFreed, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_House1_EventScript_HikerEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_House1_EventScript_HikerFreed
	msgbox RustboroCity_House1_Text_Hiker, MSGBOX_NPC
	end

RustboroCity_House1_EventScript_HikerEnding::
	msgbox RustboroCity_House1_Text_HikerEnding, MSGBOX_NPC
	end

RustboroCity_House1_EventScript_HikerFreed::
	msgbox RustboroCity_House1_Text_HikerFreed, MSGBOX_NPC
	end

RustboroCity_House1_Text_Trader:
	.string "Huh? My POKéMON is cute?\n"
	.string "Sure, I knew that.\p"
	.string "I almost traded it once. Not now.\n"
	.string "In a town like this, my SEEDOT is the\l"
	.string "only thing not worried about the\l"
	.string "ELITE FOUR.$"

RustboroCity_House1_Text_TraderFreed:
	.string "My SEEDOT is still cute. I knew that.\p"
	.string "STONE confessing made me think about\n"
	.string "what I'd trade away. Not my SEEDOT,\l"
	.string "for one.$"

RustboroCity_House1_Text_TraderEnding:
	.string "Any POKéMON can be cute if you raise it\n"
	.string "with care and kindness.\p"
	.string "I've always said so. I hear it's on a\n"
	.string "poster at DEVON now. I like to think\l"
	.string "I started that.$"

RustboroCity_House1_Text_Hiker:
	.string "In all sorts of places, there are all\n"
	.string "sorts of POKéMON and people.\p"
	.string "I slipped into town just before the\n"
	.string "roads shut. Now I'm a guest of\l"
	.string "whatever happens at DEVON.$"

RustboroCity_House1_Text_HikerFreed:
	.string "The roads are open, but I'm staying a\n"
	.string "while. The tunnel feels odd, like\l"
	.string "walking uphill on level ground.\p"
	.string "I'll leave when it stops.$"

RustboroCity_House1_Text_HikerEnding:
	.string "I'm off to see the rest of HOENN.\n"
	.string "MAUVILLE, the FRONTIER, all of it.\p"
	.string "There are all sorts of places out there.\n"
	.string "I'm going to find every one.$"

