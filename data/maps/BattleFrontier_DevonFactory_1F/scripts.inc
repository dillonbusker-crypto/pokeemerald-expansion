BattleFrontier_DevonFactory_1F_MapScripts::
	.byte 0

@ Ten Gauntlets: the Battle Factory is Devon's facility (storyline.md, "After
@ gauntlet 8"). Four of the seven guards are on this floor. Their lines are
@ placeholders until the endgame fights are written.
BattleFrontier_DevonFactory_1F_EventScript_Lucy::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Lucy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_1F_EventScript_Spenser::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Spenser, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_1F_EventScript_Anabel::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Anabel, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_1F_EventScript_Tucker::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_1F_Text_Tucker, MSGBOX_DEFAULT
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

BattleFrontier_DevonFactory_1F_Text_Spenser:
	.string "Every POKéMON on this island passed\n"
	.string "through this lab.\p"
	.string "Don't ask an old man how he sleeps.\n"
	.string "He doesn't.$"

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

