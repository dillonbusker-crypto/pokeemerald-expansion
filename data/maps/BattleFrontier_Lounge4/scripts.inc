BattleFrontier_Lounge4_MapScripts::
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman::
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook::
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man::
	msgbox BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles, MSGBOX_NPC
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

