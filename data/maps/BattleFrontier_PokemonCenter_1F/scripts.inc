BattleFrontier_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_PokemonCenter_1F_OnFrame
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	setflag FLAG_TEMP_5
	call_if_eq VAR_BROKER_STORY_STATE, 2, BattleFrontier_PokemonCenter_1F_EventScript_SetupHideout
	end

BattleFrontier_PokemonCenter_1F_OnFrame:
	map_script_2 VAR_BROKER_STORY_STATE, 2, BattleFrontier_PokemonCenter_1F_EventScript_Hideout
	.2byte 0

@ Ten Gauntlets: the Broker's letter (storyline.md; VAR_BROKER_STORY_STATE
@ is explained in BattleFrontier_OutsideWest). STEVEN brings the player here
@ from the Pike: the regulars are out, and the nurse overhears everything,
@ which is why she won't help SCOTT later.
BattleFrontier_PokemonCenter_1F_EventScript_SetupHideout::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	return

@ The player comes in at (7, 8) with STEVEN a step ahead; they walk up to
@ the counter, STEVEN at (6, 4), the player at (7, 4).
BattleFrontier_PokemonCenter_1F_EventScript_Hideout::
	lockall
	applymovement LOCALID_FRONTIER_PC_STEVEN, BattleFrontier_PokemonCenter_1F_Movement_StevenToCounter
	applymovement LOCALID_PLAYER, BattleFrontier_PokemonCenter_1F_Movement_PlayerToCounter
	waitmovement 0
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutNurseGreets, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenThanks, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutNurseNoTrouble, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_PC_STEVEN, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenHeard, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutPlayerAsks, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenWedge, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenBelieveMe, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, BattleFrontier_PokemonCenter_1F_EventScript_HideoutBelieves
	call_if_ne VAR_RESULT, YES, BattleFrontier_PokemonCenter_1F_EventScript_HideoutDoubts
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenFather, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenCrown, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenJustBusiness, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutPlayerPushesBack, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenDenial, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenUnknowns, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenGoodbye, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_FRONTIER_PC_STEVEN
	setvar VAR_BROKER_STORY_STATE, 3
	fadescreen FADE_FROM_BLACK
	releaseall
	end

BattleFrontier_PokemonCenter_1F_EventScript_HideoutBelieves::
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenRelieved, MSGBOX_DEFAULT
	return

BattleFrontier_PokemonCenter_1F_EventScript_HideoutDoubts::
	msgbox BattleFrontier_PokemonCenter_1F_Text_HideoutStevenShrugs, MSGBOX_DEFAULT
	return

BattleFrontier_PokemonCenter_1F_Movement_StevenToCounter:
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_PokemonCenter_1F_Movement_PlayerToCounter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FRONTIER_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Man::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Picnicker::
	msgbox BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox BattleFrontier_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon:
	.string "I saw two POKéMON flying low over\n"
	.string "the southern sea... a red one and\l"
	.string "a blue one, fast as jets!\p"
	.string "Where do you think they were\n"
	.string "going?$"

BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena:
	.string "The nurse here told me an old\n"
	.string "colleague of hers retired to the\l"
	.string "little house on the far west edge,\l"
	.string "past the BATTLE DOME.\p"
	.string "Says she sells a SECOND WIND now.\n"
	.string "One more try at a battle you lost.\l"
	.string "Can you believe it?$"

BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge:
	.string "Giggle… I'm going through every\n"
	.string "gauntlet with just this baby!\p"
	.string "…What do you mean, six?$"

BattleFrontier_PokemonCenter_1F_Text_Skitty:
	.string "SKITTY: Mya myaaah!$"


BattleFrontier_PokemonCenter_1F_Text_HideoutNurseGreets:
	.string "NURSE JOY: Oh, STEVEN! And you've\n"
	.string "brought a friend.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenThanks:
	.string "STEVEN: Thank you for letting us\n"
	.string "use the CENTER, JOY. I owe you\l"
	.string "one.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutNurseNoTrouble:
	.string "NURSE JOY: Oh, it's no trouble at\n"
	.string "all. Nobody really comes here\l"
	.string "anymore, anyway.\p"
	.string "Take all the time you need.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenHeard:
	.string "STEVEN: WALLACE told me what\n"
	.string "happened at PROF. BIRCH's lab.\p"
	.string "Men in suits, holding a professor\n"
	.string "in his own lab... This is getting\l"
	.string "out of hand, {PLAYER}.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutPlayerAsks:
	.string "{PLAYER} told STEVEN what SCOTT had\n"
	.string "said outside the PIKE: the bad\l"
	.string "blood between them, and that\l"
	.string "STEVEN might say things that\l"
	.string "aren't true.\p"
	.string "Is this all just a feud between\n"
	.string "the two of them?$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenWedge:
	.string "STEVEN: ...He said that? He's\n"
	.string "trying to drive a wedge between\l"
	.string "us.\p"
	.string "And he'd only bother if he already\n"
	.string "knew you've been meeting with me.\p"
	.string "SCOTT and I never got along. I\n"
	.string "won't pretend we did.\p"
	.string "But this is about much more than\n"
	.string "an old disagreement. Counterfeit\l"
	.string "badges. POKéMON that can't grow.\l"
	.string "A professor held in his own lab.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenBelieveMe:
	.string "STEVEN: {PLAYER}... do you\n"
	.string "believe me?$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenRelieved:
	.string "STEVEN: ...Thank you. I'm glad\n"
	.string "you're still on my side.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenShrugs:
	.string "STEVEN: ...That's fair. I can't\n"
	.string "make you trust me.\p"
	.string "You'll find out soon enough who\n"
	.string "deserves it.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenFather:
	.string "STEVEN: WALLACE also told me my\n"
	.string "father was at that lab.\p"
	.string "So I went to DEVON and asked him\n"
	.string "myself. He kept it short.\p"
	.string "DEVON has PROF. BIRCH researching\n"
	.string "Mega Evolution, and its limits.\p"
	.string "DEVON supplies the technology that\n"
	.string "runs the FRONTIER's systems. He\l"
	.string "can shut things off if things get\l"
	.string "messy, he said.\p"
	.string "That's what happened to your\n"
	.string "gauntlet.\p"
	.string "He says SCOTT wants to bring a new\n"
	.string "battle mechanic to the FRONTIER.\l"
	.string "The research is for that. And\l"
	.string "SCOTT keeps strict deadlines.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenCrown:
	.string "STEVEN: WALLACE heard him say\n"
	.string "something at the lab. “The\l"
	.string "CROWN.” So I asked about it.\p"
	.string "He wouldn't tell me what it is.\n"
	.string "Only that it's “cutting edge,”\l"
	.string "and a big win for the company.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenJustBusiness:
	.string "STEVEN: My father isn't a bad\n"
	.string "person. I have to believe that.\p"
	.string "Whatever happened at the lab...\n"
	.string "I'm hoping it was just business.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutPlayerPushesBack:
	.string "{PLAYER} reminded STEVEN what\n"
	.string "WALLACE saw: his father, warning\l"
	.string "PROF. BIRCH that it would be a\l"
	.string "shame if anything happened to his\l"
	.string "lab.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenDenial:
	.string "STEVEN: ...I know.\p"
	.string "I know what it sounded like. He's\n"
	.string "still my father.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenUnknowns:
	.string "STEVEN: Here's what I still can't\n"
	.string "work out.\p"
	.string "The badges were holding back your\n"
	.string "POKéMON's Experience. I proved that\l"
	.string "much.\p"
	.string "But the FRONTIER's own POKéMON\n"
	.string "still don't grow, badges or not.\l"
	.string "Why? And where does it all go?\p"
	.string "Only time will tell. But it all\n"
	.string "seems to hinge on you, {PLAYER},\l"
	.string "and how far you get through these\l"
	.string "gauntlets.$"

BattleFrontier_PokemonCenter_1F_Text_HideoutStevenGoodbye:
	.string "STEVEN: I should go. I'll take the\n"
	.string "back way out.\p"
	.string "If you need me, you know where to\n"
	.string "find me. The ledge above the\l"
	.string "PYRAMID.$"
