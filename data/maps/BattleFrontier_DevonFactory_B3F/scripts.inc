BattleFrontier_DevonFactory_B3F_MapScripts::
	.byte 0

@ Ten Gauntlets: the Pillar Chamber, with SCOTT's office. SCOTT's speech and
@ the battle he can't lose play out here (storyline.md), and later the
@ siphon that sets FLAG_CROWN_CHARGED.
BattleFrontier_DevonFactory_B3F_EventScript_Scott::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B3F_Text_Scott, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B3F_EventScript_Pillar::
	msgbox BattleFrontier_DevonFactory_B3F_Text_Pillar, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_EventScript_PillarMachinery::
	msgbox BattleFrontier_DevonFactory_B3F_Text_PillarMachinery, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_EventScript_ScottPC::
	msgbox BattleFrontier_DevonFactory_B3F_Text_ScottPC, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_EventScript_CrownBlueprints::
	msgbox BattleFrontier_DevonFactory_B3F_Text_CrownBlueprints, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B3F_Text_Scott:
	.string "So you made it all the way down\n"
	.string "here. Of course you did.\p"
	.string "I always did have an eye for talent.$"

BattleFrontier_DevonFactory_B3F_Text_Pillar:
	.string "The MEGA PILLAR.\p"
	.string "It thrums with the bonds of\n"
	.string "thousands of trainers.$"

BattleFrontier_DevonFactory_B3F_Text_PillarMachinery:
	.string "Cables as thick as an arm run from\n"
	.string "the machine into the PILLAR.$"

BattleFrontier_DevonFactory_B3F_Text_ScottPC:
	.string "SCOTT's PC. A single file is open:\p"
	.string "“CROWN - FINAL STAGE.”$"

BattleFrontier_DevonFactory_B3F_Text_CrownBlueprints:
	.string "Blueprints for the CROWN, covered\n"
	.string "in DEVON's logo.$"

