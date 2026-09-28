BattleFrontier_Lounge4_MapScripts::
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman::
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook::
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_Lounge4_EventScript_Man_Cleared6
	goto_if_ge VAR_RESULT, 5, BattleFrontier_Lounge4_EventScript_Man_Cleared5
	goto_if_ge VAR_RESULT, 4, BattleFrontier_Lounge4_EventScript_Man_Cleared4
	goto_if_ge VAR_RESULT, 3, BattleFrontier_Lounge4_EventScript_Man_Cleared3
	goto_if_ge VAR_RESULT, 2, BattleFrontier_Lounge4_EventScript_Man_Cleared2
	goto_if_ge VAR_RESULT, 1, BattleFrontier_Lounge4_EventScript_Man_Cleared1
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_EventScript_Man_Cleared6:
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text6, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_EventScript_Man_Cleared5:
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text5, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_EventScript_Man_Cleared4:
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text4, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_EventScript_Man_Cleared3:
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_EventScript_Man_Cleared2:
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_EventScript_Man_Cleared1:
	msgbox BattleFrontier_Lounge4_EventScript_Man_Text1, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring:
	.string "I wonder if they'll be airing\n"
	.string "interviews with the FRONTIER\l"
	.string "BRAINS today?$"

BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere:
	.string "If I opened a restaurant here,\n"
	.string "it'd make money for sure.\p"
	.string "Somebody's already running a\n"
	.string "business out of one of those\l"
	.string "houses on the far east side, past\l"
	.string "the ARENA…\p"
	.string "Whatever he's selling, it isn't\n"
	.string "food. And the customers always\l"
	.string "leave looking over their\l"
	.string "shoulders.$"

BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles:
	.string "Whew…\p"
	.string "I need to take a breather after\n"
	.string "some intense battles…\p"
	.string "But even now, I never take a break\n"
	.string "from plotting strategy and combos.$"

BattleFrontier_Lounge4_EventScript_Man_Text6:
	.string "Whew... I'm out of advice.\p"
	.string "You've gone further than I ever\n"
	.string "did.$"

BattleFrontier_Lounge4_EventScript_Man_Text5:
	.string "Whew... I need a breather after\n"
	.string "some intense battles. But I never\l"
	.string "stop plotting strategy.\p"
	.string "Here's one for your next gauntlet:\p"
	.string "“Every one of those teams is a\n"
	.string "chain. Break the link it can't\l"
	.string "replace.”$"

BattleFrontier_Lounge4_EventScript_Man_Text4:
	.string "Whew... I need a breather after\n"
	.string "some intense battles. But I never\l"
	.string "stop plotting strategy.\p"
	.string "Here's one for your next gauntlet:\p"
	.string "“A setup sweeper is only as good\n"
	.string "as its setup turn. Take the turn\l"
	.string "away, or be faster than it.”$"

BattleFrontier_Lounge4_EventScript_Man_Text3:
	.string "Whew... I need a breather after\n"
	.string "some intense battles. But I never\l"
	.string "stop plotting strategy.\p"
	.string "Here's one for your next gauntlet:\p"
	.string "“Speed isn't something you have.\n"
	.string "It's something you set.”$"

BattleFrontier_Lounge4_EventScript_Man_Text2:
	.string "Whew... I need a breather after\n"
	.string "some intense battles. But I never\l"
	.string "stop plotting strategy.\p"
	.string "Here's one for your next gauntlet:\p"
	.string "“The best answer to a weather team\n"
	.string "isn't to resist it. It's to take\l"
	.string "the weather away.”$"

BattleFrontier_Lounge4_EventScript_Man_Text1:
	.string "Whew... I need a breather after\n"
	.string "some intense battles. But I never\l"
	.string "stop plotting strategy.\p"
	.string "Here's one for your next gauntlet:\p"
	.string "“In Doubles, the move that hits\n"
	.string "both sides is worth more than the\l"
	.string "one that hits hardest.”$"

BattleFrontier_Lounge4_EventScript_Man_Text0:
	.string "Whew... I need a breather after\n"
	.string "some intense battles. But I never\l"
	.string "stop plotting strategy.\p"
	.string "Here's one for your next gauntlet:\p"
	.string "“A Dragon Dance sweeper only needs\n"
	.string "one free turn. Don't give it one.”$"
