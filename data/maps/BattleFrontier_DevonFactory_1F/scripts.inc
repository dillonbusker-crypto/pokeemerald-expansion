BattleFrontier_DevonFactory_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_DevonFactory_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_DevonFactory_1F_OnFrame
	.byte 0

@ ============================================================================
@ Ten Gauntlets: the Battle Factory is Devon's facility (storyline.md, "After
@ gauntlet 8"; VAR_ENDGAME_STATE is explained in BattleFrontier_OutsideEast).
@ State 3: WALLACE waits in the lobby, and SPENSER and BRANDON rush him as the
@ player comes in; he takes them on, off-screen. Three of the five guards
@ are on this floor - ANABEL, LUCY and TUCKER - each fought once, with no
@ heal (the SCRAMBLER). Each hands over a piece of the PILLAR key and leaves.
@ ============================================================================

BattleFrontier_DevonFactory_1F_OnTransition:
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	call_if_eq VAR_ENDGAME_STATE, 3, BattleFrontier_DevonFactory_1F_EventScript_SetupLobby
	checktrainerflag TRAINER_FACTORY_ANABEL
	call_if TRUE, BattleFrontier_DevonFactory_1F_EventScript_HideAnabel
	checktrainerflag TRAINER_FACTORY_LUCY
	call_if TRUE, BattleFrontier_DevonFactory_1F_EventScript_HideLucy
	checktrainerflag TRAINER_FACTORY_TUCKER
	call_if TRUE, BattleFrontier_DevonFactory_1F_EventScript_HideTucker
	call_if_ge VAR_ENDGAME_STATE, 5, BattleFrontier_DevonFactory_1F_EventScript_HideGuards
	end

BattleFrontier_DevonFactory_1F_OnFrame:
	map_script_2 VAR_TEMP_1, 1, BattleFrontier_DevonFactory_1F_EventScript_LobbyScene
	.2byte 0

BattleFrontier_DevonFactory_1F_EventScript_SetupLobby::
	clearflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_6
	setvar VAR_TEMP_1, 1
	return

BattleFrontier_DevonFactory_1F_EventScript_HideAnabel::
	setflag FLAG_TEMP_1
	return

BattleFrontier_DevonFactory_1F_EventScript_HideLucy::
	setflag FLAG_TEMP_2
	return

BattleFrontier_DevonFactory_1F_EventScript_HideTucker::
	setflag FLAG_TEMP_3
	return

BattleFrontier_DevonFactory_1F_EventScript_HideGuards::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	return

@ The player comes in at (17, 29) or (18, 29) and steps up a tile. WALLACE is
@ at (17, 26); SPENSER and BRANDON come down from the reception room to
@ (16, 24) and (18, 24).
BattleFrontier_DevonFactory_1F_EventScript_LobbyScene::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	applymovement LOCALID_DEVON_FACTORY_SPENSER, BattleFrontier_DevonFactory_1F_Movement_GuardDown
	applymovement LOCALID_DEVON_FACTORY_BRANDON, BattleFrontier_DevonFactory_1F_Movement_GuardDown
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_1F_Text_LobbySpenser, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_1F_Text_LobbyBrandon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_FACTORY_LOBBY_WALLACE, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_1F_Text_LobbyWallace1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_FACTORY_LOBBY_WALLACE, Common_Movement_FaceUp
	waitmovement 0
	msgbox BattleFrontier_DevonFactory_1F_Text_LobbyWallace2, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_DEVON_FACTORY_LOBBY_WALLACE
	removeobject LOCALID_DEVON_FACTORY_SPENSER
	removeobject LOCALID_DEVON_FACTORY_BRANDON
	setvar VAR_ENDGAME_STATE, 4
	fadescreen FADE_FROM_BLACK
	msgbox BattleFrontier_DevonFactory_1F_Text_LobbyLedAway, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_DevonFactory_1F_Movement_GuardDown:
	walk_down
	walk_down
	walk_down
	face_down
	step_end

BattleFrontier_DevonFactory_1F_EventScript_Anabel::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Anabel, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_FACTORY_ANABEL, BattleFrontier_DevonFactory_1F_Text_AnabelDefeat
	msgbox BattleFrontier_DevonFactory_1F_Text_AnabelAfter, MSGBOX_DEFAULT
	goto DevonFactory_EventScript_BrainBeaten

BattleFrontier_DevonFactory_1F_EventScript_Lucy::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Lucy, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_FACTORY_LUCY, BattleFrontier_DevonFactory_1F_Text_LucyDefeat
	msgbox BattleFrontier_DevonFactory_1F_Text_LucyAfter, MSGBOX_DEFAULT
	goto DevonFactory_EventScript_BrainBeaten

BattleFrontier_DevonFactory_1F_EventScript_Tucker::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Tucker, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_FACTORY_TUCKER, BattleFrontier_DevonFactory_1F_Text_TuckerDefeat
	msgbox BattleFrontier_DevonFactory_1F_Text_TuckerAfter, MSGBOX_DEFAULT
	goto DevonFactory_EventScript_BrainBeaten

@ Shared by all five guards (B1F's GRETA and NOLAND too). No heal between
@ fights - the SCRAMBLER - and a loss whites out to the FRONTIER's POKEMON
@ CENTER; the held items come back either way
@ (EventScript_RestoreStoryHeldItems).
DevonFactory_EventScript_UseScrambler::
	closemessage
	playse SE_PC_OFF
	msgbox DevonFactory_Text_UsedScrambler, MSGBOX_DEFAULT
	waitse
	closemessage
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
	return

@ The guard hands over a piece of the PILLAR key and leaves (VAR_LAST_TALKED
@ is still the guard). A light on B2F goes out for each piece.
DevonFactory_EventScript_BrainBeaten::
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	playfanfare MUS_OBTAIN_ITEM
	message DevonFactory_Text_ReceivedKeyPiece
	waitmessage
	waitfanfare
	waitbuttonpress
	specialvar VAR_RESULT, GetFactoryBrainsBeaten
	buffernumberstring STR_VAR_1, VAR_RESULT
	goto_if_ge VAR_RESULT, 5, DevonFactory_EventScript_AllKeyPieces
	msgbox DevonFactory_Text_KeyPieceCount, MSGBOX_DEFAULT
	goto DevonFactory_EventScript_BrainLeaves

DevonFactory_EventScript_AllKeyPieces::
	msgbox DevonFactory_Text_AllKeyPieces, MSGBOX_DEFAULT
DevonFactory_EventScript_BrainLeaves::
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_DevonFactory_1F_EventScript_Reception::
	msgbox BattleFrontier_DevonFactory_1F_Text_Reception, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_DisplayCase::
	msgbox BattleFrontier_DevonFactory_1F_Text_DisplayCase, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_VisitorLog::
	msgbox BattleFrontier_DevonFactory_1F_Text_VisitorLog, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_SecurityPC::
	msgbox BattleFrontier_DevonFactory_1F_Text_SecurityPC, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_Monitors::
	msgbox BattleFrontier_DevonFactory_1F_Text_Monitors, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_GauntletSystems::
	msgbox BattleFrontier_DevonFactory_1F_Text_GauntletSystems, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_HarvestLog::
	msgbox BattleFrontier_DevonFactory_1F_Text_HarvestLog, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_AutoHeal::
	msgbox BattleFrontier_DevonFactory_1F_Text_AutoHeal, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_Servers::
	msgbox BattleFrontier_DevonFactory_1F_Text_Servers, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_ImplantStation::
	msgbox BattleFrontier_DevonFactory_1F_Text_ImplantStation, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_BallTray::
	msgbox BattleFrontier_DevonFactory_1F_Text_BallTray, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_ChipTray::
	msgbox BattleFrontier_DevonFactory_1F_Text_ChipTray, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_BirchCrates::
	msgbox BattleFrontier_DevonFactory_1F_Text_BirchCrates, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_MasterBallCrates::
	msgbox BattleFrontier_DevonFactory_1F_Text_MasterBallCrates, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_EventScript_OreCrates::
	msgbox BattleFrontier_DevonFactory_1F_Text_OreCrates, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_1F_Text_Lucy:
	.string "…This room runs the whole island.\p"
	.string "The gauntlets, the doors, every\n"
	.string "POKéNAV. Touch nothing.$"

BattleFrontier_DevonFactory_1F_Text_Anabel:
	.string "I watched every battle you fought\n"
	.string "from these screens.\p"
	.string "Every win you were proud of, I saw\n"
	.string "it fill the PILLAR.$"

BattleFrontier_DevonFactory_1F_Text_Tucker:
	.string "MASTER BALLS! Crates of them!\n"
	.string "SCOTT's private collection.\p"
	.string "Dazzling, isn't it? Shame you'll\n"
	.string "never get near them!$"

BattleFrontier_DevonFactory_1F_Text_Reception:
	.string "DEVON CORPORATION\n"
	.string "FRONTIER SYSTEMS DIVISION\p"
	.string "All visitors must be escorted.$"

BattleFrontier_DevonFactory_1F_Text_DisplayCase:
	.string "A glass case. The label reads:\n"
	.string "“BOND HARNESS - PROTOTYPE 1.”\p"
	.string "The case is empty.$"

BattleFrontier_DevonFactory_1F_Text_VisitorLog:
	.string "A visitor log on the screen.\p"
	.string "SCOTT. PRESIDENT STONE. PROF. BIRCH.\n"
	.string "PROF. BIRCH. PROF. BIRCH…$"

BattleFrontier_DevonFactory_1F_Text_SecurityPC:
	.string "SECURITY: Frontier gate scanners.\p"
	.string "Every challenger has passed with\n"
	.string "counterfeit badges. 100% compliance.$"

BattleFrontier_DevonFactory_1F_Text_Monitors:
	.string "Dozens of screens show the\n"
	.string "FRONTIER's battle rooms.\p"
	.string "One screen is labeled {PLAYER}.$"

BattleFrontier_DevonFactory_1F_Text_GauntletSystems:
	.string "ISLAND SYSTEMS\p"
	.string "GAUNTLET 6: RESUMED.\n"
	.string "Last override: PRESIDENT STONE.$"

BattleFrontier_DevonFactory_1F_Text_HarvestLog:
	.string "BOND HARVEST - TOP CONTRIBUTORS\p"
	.string "1. {PLAYER}\p"
	.string "The rest of the list is a long way\n"
	.string "behind.$"

BattleFrontier_DevonFactory_1F_Text_AutoHeal:
	.string "POKéNAV AUTO-HEAL: ONLINE.\p"
	.string "Warning: SCRAMBLER interference\n"
	.string "detected on this island.$"

BattleFrontier_DevonFactory_1F_Text_Servers:
	.string "A DEVON server hums. Its lights\n"
	.string "blink in time with the PILLAR below.$"

BattleFrontier_DevonFactory_1F_Text_ImplantStation:
	.string "IMPLANT STATION\p"
	.string "Shard chip seated in 0.4 seconds.\n"
	.string "The POKéMON feels nothing.$"

BattleFrontier_DevonFactory_1F_Text_BallTray:
	.string "Rows of POKé BALLS, each one\n"
	.string "tagged: AWAITING IMPLANT.$"

BattleFrontier_DevonFactory_1F_Text_ChipTray:
	.string "A tray of tiny shards, the same\n"
	.string "metal as the counterfeit badges.$"

BattleFrontier_DevonFactory_1F_Text_BirchCrates:
	.string "Crates stamped LITTLEROOT LAB.\p"
	.string "PROF. BIRCH's equipment, taken in\n"
	.string "the raid.$"

BattleFrontier_DevonFactory_1F_Text_MasterBallCrates:
	.string "Crates of MASTER BALLS. The shipping\n"
	.string "labels say KANTO.$"

BattleFrontier_DevonFactory_1F_Text_OreCrates:
	.string "Crates of raw MEGA STONE ore, dug\n"
	.string "out from under the island.$"

BattleFrontier_DevonFactory_1F_Text_AnabelDefeat:
	.string "I read you perfectly. And it still\n"
	.string "wasn't enough.$"

BattleFrontier_DevonFactory_1F_Text_AnabelAfter:
	.string "ANABEL: SCOTT gave each of us a\n"
	.string "piece of the PILLAR key.\p"
	.string "Take mine. I won't need it where\n"
	.string "I'm going.$"

BattleFrontier_DevonFactory_1F_Text_LucyDefeat:
	.string "…Tch.$"

BattleFrontier_DevonFactory_1F_Text_LucyAfter:
	.string "LUCY: …Take it. The key piece.\n"
	.string "Before I change my mind.$"

BattleFrontier_DevonFactory_1F_Text_TuckerDefeat:
	.string "What a performance! I've never been\n"
	.string "upstaged like that!$"

BattleFrontier_DevonFactory_1F_Text_TuckerAfter:
	.string "TUCKER: A deal's a deal. Here: my\n"
	.string "piece of the PILLAR key.\p"
	.string "Enjoy the show downstairs. I hear\n"
	.string "SCOTT never loses!$"

BattleFrontier_DevonFactory_1F_Text_LobbySpenser:
	.string "SPENSER: Hohoho! The CHAMPION\n"
	.string "himself, come knocking.$"

BattleFrontier_DevonFactory_1F_Text_LobbyBrandon:
	.string "BRANDON: SCOTT said you might!\n"
	.string "You go no further, WALLACE!$"

BattleFrontier_DevonFactory_1F_Text_LobbyWallace1:
	.string "WALLACE: {PLAYER}, I'll handle these\n"
	.string "two chumps. Go on ahead.\p"
	.string "SCOTT will have his BRAINS guarding\n"
	.string "the way down. Free the captives, and\l"
	.string "find SCOTT.$"

BattleFrontier_DevonFactory_1F_Text_LobbyWallace2:
	.string "WALLACE: Now then. Which of you\n"
	.string "would like to go first?$"

BattleFrontier_DevonFactory_1F_Text_LobbyLedAway:
	.string "WALLACE led SPENSER and BRANDON off\n"
	.string "to battle.$"

DevonFactory_Text_UsedScrambler:
	.string "{PLAYER} used the SCRAMBLER!\p"
	.string "Every POKéNAV nearby went dark.$"

DevonFactory_Text_ReceivedKeyPiece:
	.string "{PLAYER} received a piece of the\n"
	.string "PILLAR key!$"

DevonFactory_Text_KeyPieceCount:
	.string "{PLAYER} has {STR_VAR_1} of the five\n"
	.string "pieces.$"

DevonFactory_Text_AllKeyPieces:
	.string "{PLAYER} has all five pieces of the\n"
	.string "PILLAR key!$"
