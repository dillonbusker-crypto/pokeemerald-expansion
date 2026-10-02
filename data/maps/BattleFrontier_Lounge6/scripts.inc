BattleFrontier_Lounge6_MapScripts::
	.byte 0

@ Ten Gauntlets: the Broker's cousin. A blind trade, once per gauntlet, for
@ 200 FP - one of the player's party Pokemon for a random Pokemon from the next
@ gauntlet's shop wave (FacilityTraderTrade(), src/facility_shop.c).
@ VAR_TRADER_LAST_GAUNTLET holds the gauntlet she last traded for. She won't
@ take the Latias/Latios (STEVEN needs it), a LEAFEON (the florist's quest
@ needs one) or an Egg, doesn't trade mid-run (the team is locked), and closes
@ while the island's POS is down (it costs FP). The vanilla Meowth trade
@ scripts below are unreferenced now.
BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_ge VAR_BROKER_STORY_STATE, 5, BattleFrontier_Lounge6_EventScript_TraderLayingLow
	specialvar VAR_RESULT, IsFacilityRunActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge6_EventScript_TraderMidRun
	specialvar VAR_RESULT, IsFrontierPOSDown
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge6_EventScript_TraderPOSDown
	specialvar VAR_TEMP_1, GetGauntletsClearedCount
	addvar VAR_TEMP_1, 1
	goto_if_eq VAR_TRADER_LAST_GAUNTLET, VAR_TEMP_1, BattleFrontier_Lounge6_EventScript_TraderAlreadyTraded
	specialvar VAR_RESULT, FacilityTraderHasStock
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge6_EventScript_TraderNothingLeft
	special ShowFacilityFPWindow
	msgbox BattleFrontier_Lounge6_Text_TraderOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge6_EventScript_TraderDecline
	setvar VAR_0x8008, 200
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, VAR_0x8008, BattleFrontier_Lounge6_EventScript_TraderNoFP
	msgbox BattleFrontier_Lounge6_Text_TraderWhichOne, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, BattleFrontier_Lounge6_EventScript_TraderDecline
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge6_EventScript_TraderNoEgg
	goto_if_eq VAR_RESULT, SPECIES_LATIAS, BattleFrontier_Lounge6_EventScript_TraderNoLati
	goto_if_eq VAR_RESULT, SPECIES_LATIOS, BattleFrontier_Lounge6_EventScript_TraderNoLati
	goto_if_eq VAR_RESULT, SPECIES_LEAFEON, BattleFrontier_Lounge6_EventScript_TraderNoLeafeon
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	msgbox BattleFrontier_Lounge6_Text_TraderConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge6_EventScript_TraderDecline
	special FacilityTraderTrade
	goto_if_eq VAR_RESULT, SPECIES_NONE, BattleFrontier_Lounge6_EventScript_TraderNothingLeft
	setvar VAR_0x8004, 200
	special FacilityShopTakeFP
	special UpdateFacilityFPWindow
	copyvar VAR_TRADER_LAST_GAUNTLET, VAR_TEMP_1
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_Lounge6_Text_TraderTraded
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox BattleFrontier_Lounge6_Text_TraderAfter, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_Lounge6_EventScript_TraderPOSDown::
	msgbox BattleFrontier_Lounge6_Text_TraderPOSDown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TraderNoFP::
	msgbox BattleFrontier_Lounge6_Text_TraderNoFP, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_Lounge6_EventScript_TraderNoLeafeon::
	msgbox BattleFrontier_Lounge6_Text_TraderNoLeafeon, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_Lounge6_EventScript_TraderMidRun::
	msgbox BattleFrontier_Lounge6_Text_TraderMidRun, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TraderAlreadyTraded::
	msgbox BattleFrontier_Lounge6_Text_TraderAlreadyTraded, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TraderNothingLeft::
	msgbox BattleFrontier_Lounge6_Text_TraderNothingLeft, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TraderDecline::
	msgbox BattleFrontier_Lounge6_Text_TraderDecline, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_Lounge6_EventScript_TraderNoEgg::
	msgbox BattleFrontier_Lounge6_Text_TraderNoEgg, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_Lounge6_EventScript_TraderNoLati::
	msgbox BattleFrontier_Lounge6_Text_TraderNoLati, MSGBOX_DEFAULT
	special CloseFacilityFPWindow
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "My POKéMON is a {STR_VAR_2}.\n"
	.string "Do you know it?\l"
	.string "It's quite cute and rather nice.\p"
	.string "This little one, I could trade with\n"
	.string "pride!\p"
	.string "Would you like to trade me a {STR_VAR_1}\n"
	.string "for my {STR_VAR_2}?$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
	.string "Oh, it's adorable!\n"
	.string "Thank you!\l"
	.string "I promise I'll be good to it!\p"
	.string "Oh! I hope you'll be good to\n"
	.string "my {STR_VAR_2}, too!$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
	.string "Oh, I'm sorry!\n"
	.string "I don't intend to trade for anything\l"
	.string "but a {STR_VAR_1}.$"

BattleFrontier_Lounge6_Text_WellThatsFineToo:
	.string "Oh, you won't?\n"
	.string "Well, that's fine, too.\l"
	.string "Please come visit us again.$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
	.string "Giggle!\n"
	.string "A SKITTY is so much cuter than I had\l"
	.string "imagined. I'm delighted!$"

BattleFrontier_Lounge6_Text_TraderOffer:
	.string "Hello! You might know my cousin.\n"
	.string "He... sells things. Before anyone\l"
	.string "else has them. Family business,\l"
	.string "you could say.\p"
	.string "I've got a POKéMON here from\n"
	.string "further up the gauntlets. I won't\l"
	.string "tell you which one... that's half\l"
	.string "the fun!\p"
	.string "Trade me one of yours for it? 200\n"
	.string "FP, and just once per gauntlet.$"

BattleFrontier_Lounge6_Text_TraderWhichOne:
	.string "Which POKéMON will you trade?$"

BattleFrontier_Lounge6_Text_TraderConfirm:
	.string "Your {STR_VAR_1}? No peeking at\n"
	.string "mine, now. Deal?$"

BattleFrontier_Lounge6_Text_TraderTraded:
	.string "{PLAYER} traded {STR_VAR_1}... and\n"
	.string "received a {STR_VAR_2}!$"

BattleFrontier_Lounge6_Text_TraderAfter:
	.string "Surprise! I hope you'll be good to\n"
	.string "it. Come back after your next\l"
	.string "gauntlet, and I'll have something\l"
	.string "new.$"

BattleFrontier_Lounge6_Text_TraderMidRun:
	.string "Not in the middle of a run, dear!\n"
	.string "Your team's locked in.$"

BattleFrontier_Lounge6_Text_TraderAlreadyTraded:
	.string "We've already traded this\n"
	.string "gauntlet. Come back once you've\l"
	.string "cleared it, and I'll have\l"
	.string "something new.$"

BattleFrontier_Lounge6_Text_TraderNothingLeft:
	.string "You've gone further than anything\n"
	.string "I could offer you. I've nothing\l"
	.string "left to trade!$"

BattleFrontier_Lounge6_Text_TraderDecline:
	.string "Oh, that's all right. Come back if\n"
	.string "you change your mind.$"

BattleFrontier_Lounge6_Text_TraderNoEgg:
	.string "An EGG? No, no. I only trade\n"
	.string "POKéMON.$"

BattleFrontier_Lounge6_Text_TraderNoLati:
	.string "Oh, not that one. That one's far\n"
	.string "too special. Someone's counting on\l"
	.string "it... I can tell.$"

BattleFrontier_Lounge6_Text_TraderPOSDown:
	.string "Nothing's moving on this island\n"
	.string "with the system down. My cousin\l"
	.string "says the same.\p"
	.string "Come back when things are running\n"
	.string "again.$"

BattleFrontier_Lounge6_Text_TraderNoFP:
	.string "Oh dear. You'll need 200 FP for a\n"
	.string "trade.$"

BattleFrontier_Lounge6_Text_TraderNoLeafeon:
	.string "A LEAFEON? No, no. Someone in town\n"
	.string "has been hoping for one of those.\l"
	.string "I couldn't.$"

@ Ten Gauntlets: after her cousin the Broker's arrest (gauntlet 6,
@ storyline.md), she stops trading.
BattleFrontier_Lounge6_EventScript_TraderLayingLow::
	msgbox BattleFrontier_Lounge6_Text_TraderLayingLow, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_TraderLayingLow:
	.string "...Oh. It's you.\p"
	.string "You heard about my cousin, didn't\n"
	.string "you? SCOTT's people took him.\p"
	.string "I'm keeping my head down for a\n"
	.string "while. No more trades. Sorry.$"
