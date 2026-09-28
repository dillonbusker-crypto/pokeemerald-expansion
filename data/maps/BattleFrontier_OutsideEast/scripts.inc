BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 8, BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Cleared8
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Cleared8:
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text8, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 7, BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Cleared7
	msgbox BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Cleared7:
	msgbox BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Text7, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 9, BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Cleared9
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Cleared9:
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text9, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 4, BattleFrontier_OutsideEast_EventScript_TriathleteF_Cleared4
	msgbox BattleFrontier_OutsideEast_EventScript_TriathleteF_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF_Cleared4:
	msgbox BattleFrontier_OutsideEast_EventScript_TriathleteF_Text4, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, BattleFrontier_OutsideEast_EventScript_Man2_Cleared5
	msgbox BattleFrontier_OutsideEast_EventScript_Man2_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Man2_Cleared5:
	msgbox BattleFrontier_OutsideEast_EventScript_Man2_Text5, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_FRONTIER_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 3, BattleFrontier_OutsideEast_EventScript_Man3_Cleared3
	msgbox BattleFrontier_OutsideEast_EventScript_Man3_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Man3_Cleared3:
	msgbox BattleFrontier_OutsideEast_EventScript_Man3_Text3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 3, BattleFrontier_OutsideEast_EventScript_Woman1_Cleared3
	msgbox BattleFrontier_OutsideEast_EventScript_Woman1_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman1_Cleared3:
	msgbox BattleFrontier_OutsideEast_EventScript_Woman1_Text3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 3, BattleFrontier_OutsideEast_EventScript_Woman2_Cleared3
	msgbox BattleFrontier_OutsideEast_EventScript_Woman2_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman2_Cleared3:
	msgbox BattleFrontier_OutsideEast_EventScript_Woman2_Text3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "BATTLE TOWER - GAUNTLETS 1 TO 4.\p"
	.string "Every challenger starts here!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "This is the BATTLE PALACE!\n"
	.string "Keep your eyes on POKéMON battles!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "This is the BATTLE ARENA!\n"
	.string "Let the toughest teams gather!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "This is the BATTLE PYRAMID!\n"
	.string "Advance through the Battle Quest!$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "THE HALL OF TEN\p"
	.string "Ten gauntlets. Ten bosses. And the\n"
	.string "trainers who beat them.$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "FRONTIER POINT EXCHANGE SERVICE\n"
	.string "CORNER\p"
	.string "POKéMON, items and MEGA STONES for\n"
	.string "FP!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "Wow! It's huge!\p"
	.string "The BATTLE TOWER holds four whole\n"
	.string "gauntlets, one mat each. Everyone\l"
	.string "starts there!$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "My grand ambition is to clear all\n"
	.string "ten gauntlets.\p"
	.string "And if my dream comes true…\p"
	.string "I… I'm going to ask MIMI next door\n"
	.string "if she will be friends with me!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "The BATTLE PYRAMID's sealed tight.\n"
	.string "They say it's the tenth gauntlet,\l"
	.string "the very last one.\p"
	.string "I'm going to be waiting right here\n"
	.string "the day it opens.$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "I thrive in darkness… Yes…\p"
	.string "The PYRAMID KING waits in the dark\n"
	.string "of the tenth gauntlet… Few have\l"
	.string "seen him.\p"
	.string "Yet everyone who reaches gauntlet\n"
	.string "9 dreams of him…$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "I didn't sleep for a week, but\n"
	.string "then I put together the ultimate\l"
	.string "team!\p"
	.string "…The ARENA's still sealed, though.\n"
	.string "So I'm starting at gauntlet 1 like\l"
	.string "everyone else.$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "Did SCOTT invite you here, too?\p"
	.string "He really does know how to spot\n"
	.string "talented trainers, but… I've never\l"
	.string "once seen him battle.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "ZIGG!\n"
	.string "I believe in you, little buddy!\p"
	.string "I'll make my little ZIGG any favorite\n"
	.string "tasty treats you like if you win!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "ZIGZAGOON looks vacant…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "People call me a busybody, but I\n"
	.string "can't help it.\p"
	.string "Your hat's crooked! Your lead's\n"
	.string "wrong! And you haven't bought a\l"
	.string "single resist berry!\p"
	.string "…Sorry. I really can't help it.$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "I may not look that impressive\n"
	.string "now, but I once beat a GYM LEADER.\p"
	.string "There's no LEAGUE here, though.\n"
	.string "Only gauntlets. And nobody hands\l"
	.string "out badges.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "I'm fast on my BIKE, and that goes for\n"
	.string "the way I battle, too.\p"
	.string "I win matches in the blink of\n"
	.string "an eye!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "I'm better than my daddy\n"
	.string "at POKéMON.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "Go on, my baby sweetie!\n"
	.string "Go rack up some wins for Daddy!\p"
	.string "You're just like your mother,\n"
	.string "so you'll be dominating!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "It wasn't easy getting here,\n"
	.string "but I'd heard about this knockout\l"
	.string "pretty girl at the BATTLE ARENA.\p"
	.string "Instead of her, do you know what\n"
	.string "I found?\p"
	.string "A whole teeming mob of sweaty,\n"
	.string "stinky, and primitive martial artists!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "I sometimes see this really\n"
	.string "important-looking old man going\l"
	.string "into the PALACE, even though it's\l"
	.string "sealed.\p"
	.string "His POKéMON look… legendary.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "Do you know it? The legend of the\n"
	.string "BATTLE PYRAMID?\p"
	.string "When a trainer clears nine\n"
	.string "gauntlets, the PYRAMID KING\l"
	.string "himself shall appear!\p"
	.string "…I just made that up. Or did I?$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "Man! Oh man!\n"
	.string "I've never lost once before!\p"
	.string "But I got wiped out with no saving\n"
	.string "grace at all!\p"
	.string "And then I'm told I don't have any\n"
	.string "talent?! Man!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "This guy ran into a horribly tough\n"
	.string "TRAINER while he was on the BATTLE\l"
	.string "TOWER challenge.\p"
	.string "Now look at him…\p"
	.string "You need to be cautious if you ever\n"
	.string "decide to go to the BATTLE TOWER.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "Yes!\n"
	.string "I've finally got enough Battle Points!\p"
	.string "I guess I'll trade for another giant\n"
	.string "plush DOLL!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "Oh, yeah, okay! So this is the\n"
	.string "HALL OF TEN!\p"
	.string "Beat a gauntlet's boss and your\n"
	.string "name goes up on its plaque. I'm\l"
	.string "going to be the reason one of\l"
	.string "those changes!$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "Doubles is made for us, darling!\n"
	.string "You use Fake Out, and I'll use\l"
	.string "Protect!$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "Ooh, darling, you are so\n"
	.string "wonderful!\p"
	.string "…That's not how Protect works at\n"
	.string "all, but I love you.\p"
	.string "Let's go take on the Doubles mat\n"
	.string "right this instant! Everything\l"
	.string "will topple like dominoes!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "Ten gauntlets, and the FRONTIER\n"
	.string "BRAINS waiting at the end of them…\p"
	.string "SCOTT never does anything without\n"
	.string "a reason. What's waiting after the\l"
	.string "tenth, I wonder?$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Excuse me, young one.\n"
	.string "Have you good eyesight?\p"
	.string "There is an odd tree past here, and to\n"
	.string "my tired eyes it seems to wiggle.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Excuse me, young one.\n"
	.string "Have you a good memory?\p"
	.string "I have this feeling there once was\n"
	.string "an odd tree past here.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "I…\n"
	.string "I saw it!\p"
	.string "There was a sticky sort of a POKéMON\n"
	.string "with a long tail up ahead!\p"
	.string "It was hiding under a boulder, and\n"
	.string "it kept staring at me!$"

BattleFrontier_OutsideEast_EventScript_TriathleteF_Text4:
	.string "Speed is everything! …At least it\n"
	.string "was, until gauntlet 4. Everyone in\l"
	.string "there learned to change the speed\l"
	.string "order.\p"
	.string "I'm still upset about it.$"

BattleFrontier_OutsideEast_EventScript_TriathleteF_Text0:
	.string "I'm fast on my BIKE, and that goes\n"
	.string "for the way I battle, too. I win\l"
	.string "matches in the blink of an eye!$"

BattleFrontier_OutsideEast_EventScript_Man2_Text5:
	.string "Go on, my baby sweetie! Daddy\n"
	.string "bought you a MEGA STONE, so go\l"
	.string "rack up some wins for Daddy!$"

BattleFrontier_OutsideEast_EventScript_Man2_Text0:
	.string "Go on, my baby sweetie! Go rack up\n"
	.string "some wins for Daddy!$"

BattleFrontier_OutsideEast_EventScript_Man3_Text3:
	.string "Man! I made it to gauntlet 3!\p"
	.string "…Then the sandstorm started. Don't\n"
	.string "talk to me about sandstorms.$"

BattleFrontier_OutsideEast_EventScript_Man3_Text0:
	.string "Man! Oh man! I'd never lost once\n"
	.string "before!\p"
	.string "Then I met WARDEN HELIS. I got\n"
	.string "wiped out with no saving grace at\l"
	.string "all!$"

BattleFrontier_OutsideEast_EventScript_Woman1_Text3:
	.string "He's on gauntlet 3 now. He did\n"
	.string "great until the weather turned.\p"
	.string "Please don't mention sandstorms\n"
	.string "around him.$"

BattleFrontier_OutsideEast_EventScript_Woman1_Text0:
	.string "He'd never lost once. Then he met\n"
	.string "WARDEN HELIS on the first mat.\p"
	.string "It was one ALTARIA. ONE!\p"
	.string "Watch out for that one if you're\n"
	.string "headed to the TOWER.$"

BattleFrontier_OutsideEast_EventScript_Woman2_Text3:
	.string "Yes! I've finally got enough FP!\p"
	.string "A CHOICE SCARF, or a new POKéMON…\n"
	.string "A CHOICE SCARF, or a new POKéMON…$"

BattleFrontier_OutsideEast_EventScript_Woman2_Text0:
	.string "Yes! I've finally got enough FP!\p"
	.string "A resist berry, or save up for a\n"
	.string "new POKéMON… A resist berry, or a\l"
	.string "new POKéMON…$"

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text8:
	.string "BATTLE PALACE - GAUNTLET 9.\p"
	.string "Sealed. Still being prepared.$"

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text0:
	.string "BATTLE PALACE - GAUNTLET 9.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 8.$"

BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Text7:
	.string "BATTLE ARENA - GAUNTLET 8.\p"
	.string "Sealed. Still being prepared.$"

BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Text0:
	.string "BATTLE ARENA - GAUNTLET 8.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 7.$"

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text9:
	.string "BATTLE PYRAMID - GAUNTLET 10.\p"
	.string "Sealed. Still being prepared.$"

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text0:
	.string "BATTLE PYRAMID - GAUNTLET 10.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 9.$"
