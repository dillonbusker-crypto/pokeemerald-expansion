RustboroCity_Flat2_2F_MapScripts::
	.byte 0

RustboroCity_Flat2_2F_EventScript_OldMan::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat2_2F_EventScript_OldManEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat2_2F_EventScript_OldManFreed
	msgbox RustboroCity_Flat2_2F_Text_OldMan, MSGBOX_NPC
	end

RustboroCity_Flat2_2F_EventScript_OldManEnding::
	msgbox RustboroCity_Flat2_2F_Text_OldManEnding, MSGBOX_NPC
	end

RustboroCity_Flat2_2F_EventScript_OldManFreed::
	msgbox RustboroCity_Flat2_2F_Text_OldManFreed, MSGBOX_NPC
	end

RustboroCity_Flat2_2F_EventScript_NinjaBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_PREMIER_BALL_RUSTBORO, RustboroCity_Flat2_2F_EventScript_GavePremierBall
	msgbox RustboroCity_Flat2_2F_Text_MyDaddyMadeThisYouCanHaveIt, MSGBOX_DEFAULT
	giveitem ITEM_PREMIER_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_PREMIER_BALL_RUSTBORO
	release
	end

RustboroCity_Flat2_2F_EventScript_GavePremierBall::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_Flat2_2F_EventScript_GavePremierBallEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_Flat2_2F_EventScript_GavePremierBallFreed
	msgbox RustboroCity_Flat2_2F_Text_GavePremierBall, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_2F_EventScript_GavePremierBallEnding::
	msgbox RustboroCity_Flat2_2F_Text_GavePremierBallEnding, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_2F_EventScript_GavePremierBallFreed::
	msgbox RustboroCity_Flat2_2F_Text_GavePremierBallFreed, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat2_2F_Text_OldMan:
	.string "In the old days, DEVON was just a\n"
	.string "teeny, tiny company. A garage and a\l"
	.string "screwdriver.\p"
	.string "Now it's an empire with the ELITE\n"
	.string "FOUR for doormen.$"

RustboroCity_Flat2_2F_Text_OldManFreed:
	.string "I knew STONE when he was a young man\n"
	.string "with a screwdriver.\p"
	.string "I'd like to think confessing came\n"
	.string "easy because he was honest, once.$"

RustboroCity_Flat2_2F_Text_OldManEnding:
	.string "They put up a plaque for the old garage\n"
	.string "at DEVON. The first one.\p"
	.string "I cried at the unveiling. Don't look at\n"
	.string "me.$"

RustboroCity_Flat2_2F_Text_MyDaddyMadeThisYouCanHaveIt:
	.string "My daddy works at DEVON.\n"
	.string "My daddy made this in his spare time!\l"
	.string "But I can't use it, so you can have it.$"

RustboroCity_Flat2_2F_Text_GavePremierBall:
	.string "My daddy works at DEVON. He's home\n"
	.string "now, and he isn't smiling.\p"
	.string "When I grow up I'm going to work for\n"
	.string "DEVON, too. The nice kind.$"

RustboroCity_Flat2_2F_Text_GavePremierBallFreed:
	.string "Daddy got called in to answer\n"
	.string "questions. He says it's the right kind\l"
	.string "of boring.\p"
	.string "When I grow up I'm going to work for\n"
	.string "DEVON, too.$"

RustboroCity_Flat2_2F_Text_GavePremierBallEnding:
	.string "Daddy's back at work. He says the new\n"
	.string "boss has a rule against secrets.\p"
	.string "I think it's a good rule.$"

