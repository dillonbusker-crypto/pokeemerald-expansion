BattleFrontier_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_PokemonCenter_1F_OnFrame
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	setflag FLAG_TEMP_5
	call_if_eq VAR_BROKER_STORY_STATE, 2, BattleFrontier_PokemonCenter_1F_EventScript_SetupHideout
	call BattleFrontier_PokemonCenter_1F_EventScript_SetupEndgameAbra
	end

@ Ten Gauntlets: the endgame ABRA network (data/scripts/endgame_towns.inc).
@ The FRONTIER's ABRA waits by the counter once STEVEN has sent the player to
@ RUSTBORO (storyline.md).
BattleFrontier_PokemonCenter_1F_EventScript_SetupEndgameAbra::
	setflag FLAG_HIDE_FRONTIER_ENDGAME_ABRA
	goto_if_unset FLAG_ABRA_TO_RUSTBORO, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_FRONTIER_ENDGAME_ABRA
	return

BattleFrontier_PokemonCenter_1F_EventScript_EndgameAbra::
	setvar VAR_0x8004, ABRA_AT_FRONTIER
	goto EventScript_EndgameAbra

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
	@ Ten Gauntlets: Bad Dreams (storyline.md). While the event runs she has
	@ patients and asks for a CRESSELIA's feather; once DARKRAI is freed, and
	@ while gauntlet 7 is still open, she says so once per visit (FLAG_TEMP_7).
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_PokemonCenter_1F_EventScript_NurseBadDreams
	goto_if_unset FLAG_DARKRAI_FREED, BattleFrontier_PokemonCenter_1F_EventScript_NurseNormal
	goto_if_set FLAG_TEMP_7, BattleFrontier_PokemonCenter_1F_EventScript_NurseNormal
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ne VAR_RESULT, 6, BattleFrontier_PokemonCenter_1F_EventScript_NurseNormal
	setflag FLAG_TEMP_7
	lock
	faceplayer
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseWokeUp, MSGBOX_DEFAULT
	goto BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal

BattleFrontier_PokemonCenter_1F_EventScript_NurseBadDreams::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LUNAR_WING, BattleFrontier_PokemonCenter_1F_EventScript_NurseCurtains
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseDreamers, MSGBOX_DEFAULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseHaveCresselia, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_ne VAR_RESULT, SPECIES_CRESSELIA, BattleFrontier_PokemonCenter_1F_EventScript_NurseNotCresselia
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseThanksCresselia, MSGBOX_DEFAULT
	giveitem ITEM_LUNAR_WING
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_PokemonCenter_1F_EventScript_NurseBagFull
	setflag FLAG_RECEIVED_LUNAR_WING
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseWingGlows, MSGBOX_DEFAULT
	goto BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal

BattleFrontier_PokemonCenter_1F_EventScript_NurseNotCresselia::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseNotCresselia, MSGBOX_DEFAULT
	goto BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal

BattleFrontier_PokemonCenter_1F_EventScript_NurseBagFull::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseBagFull, MSGBOX_DEFAULT
	goto BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal

BattleFrontier_PokemonCenter_1F_EventScript_NurseCurtains::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseCurtains, MSGBOX_DEFAULT
	goto BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal

BattleFrontier_PokemonCenter_1F_EventScript_NurseNormal::
	@ Ten Gauntlets: after the siphon (states 11-14) she hints once, then heals as usual.
	goto_if_lt VAR_ENDGAME_STATE, 11, BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal
	goto_if_ge VAR_ENDGAME_STATE, 15, BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal
	goto_if_eq VAR_FRONTIER_JOY_HINTED, 1, BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal
	setvar VAR_FRONTIER_JOY_HINTED, 1
	lock
	faceplayer
	msgbox BattleFrontier_PokemonCenter_1F_Text_NurseCrownHint, MSGBOX_DEFAULT
BattleFrontier_PokemonCenter_1F_EventScript_NurseHeal::
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_SMUGGLER, BattleFrontier_PokemonCenter_1F_SchoolKid_Gossip0
	case GOSSIP_ANABEL, BattleFrontier_PokemonCenter_1F_SchoolKid_Gossip0
	msgbox BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
BattleFrontier_PokemonCenter_1F_SchoolKid_Gossip0::
	msgbox BattleFrontier_PokemonCenter_1F_SchoolKid_Text_Gossip0, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_SchoolKid_Text_Gossip0:
	.string "Remember the red and blue POKéMON I\n"
	.string "saw over the sea?\p"
	.string "I heard something crying out from\n"
	.string "that cave below the waterfall one\l"
	.string "night... And then nothing.\p"
	.string "I haven't seen them since.$"

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


BattleFrontier_PokemonCenter_1F_Text_NurseCrownHint:
	.string "NURSE JOY: The CROWN drained every\n"
	.string "chip on the island in one go. What\l"
	.string "power!\p"
	.string "It makes me think. I may be able to\n"
	.string "help you with it, but I need time\l"
	.string "to work it out.$"

BattleFrontier_PokemonCenter_1F_Text_NurseDreamers:
	.string "NURSE JOY: I finally have patients,\n"
	.string "and I can't wake a single one.\p"
	.string "They fell asleep on their feet, all\n"
	.string "dreaming the same dream.\p"
	.string "The old remedy is a CRESSELIA's\n"
	.string "feather: the LUNAR WING.\p"
	.string "If someone could bring me a\n"
	.string "CRESSELIA, even for a moment…$"

BattleFrontier_PokemonCenter_1F_Text_NurseHaveCresselia:
	.string "NURSE JOY: Do you have a CRESSELIA\n"
	.string "with you?$"

BattleFrontier_PokemonCenter_1F_Text_NurseWhich:
	.string "NURSE JOY: Which one?$"

BattleFrontier_PokemonCenter_1F_Text_NurseNotCresselia:
	.string "NURSE JOY: That's not a CRESSELIA.$"

BattleFrontier_PokemonCenter_1F_Text_NurseThanksCresselia:
	.string "NURSE JOY: A CRESSELIA! Thank you,\n"
	.string "CRESSELIA.\p"
	.string "Just one feather… There. That's all\n"
	.string "it takes.$"

BattleFrontier_PokemonCenter_1F_Text_NurseWingGlows:
	.string "NURSE JOY: They say it glows near\n"
	.string "the dreamers, and leads you to\l"
	.string "whatever is causing it.$"

BattleFrontier_PokemonCenter_1F_Text_NurseBagFull:
	.string "NURSE JOY: Your BAG is full. Make\n"
	.string "room, and ask me again.$"

BattleFrontier_PokemonCenter_1F_Text_NurseCurtains:
	.string "NURSE JOY: The dreamers all talk\n"
	.string "about curtains. The PIKE has\l"
	.string "curtains…$"

BattleFrontier_PokemonCenter_1F_Text_NurseWokeUp:
	.string "NURSE JOY: My patients all woke up!\n"
	.string "Was that you?$"

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
	.string "{PLAYER} asked whether this was all\n"
	.string "just a feud between the two of\l"
	.string "them.$"

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
