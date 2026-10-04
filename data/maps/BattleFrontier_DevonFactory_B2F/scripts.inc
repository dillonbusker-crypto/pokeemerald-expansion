BattleFrontier_DevonFactory_B2F_MapScripts::
	.byte 0

@ Ten Gauntlets: the Generator Hall. The stairs down to the PILLAR are sealed
@ until all seven guards are beaten; each beaten guard should turn one of
@ the seven red lights (metatile 0x224 on the wall face) off. Until that's
@ scripted the door simply stays sealed.
BattleFrontier_DevonFactory_B2F_EventScript_Brandon::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B2F_Text_Brandon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B2F_EventScript_PillarDoorSealed::
	lockall
	msgbox BattleFrontier_DevonFactory_B2F_Text_PillarDoorSealed, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, BattleFrontier_DevonFactory_B2F_Movement_StepBack
	waitmovement 0
	releaseall
	end

BattleFrontier_DevonFactory_B2F_Movement_StepBack:
	walk_down
	step_end

BattleFrontier_DevonFactory_B2F_EventScript_LockLights::
	msgbox BattleFrontier_DevonFactory_B2F_Text_LockLights, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B2F_EventScript_GeneratorUnit::
	msgbox BattleFrontier_DevonFactory_B2F_Text_GeneratorUnit, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B2F_EventScript_Generator::
	msgbox BattleFrontier_DevonFactory_B2F_Text_Generator, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B2F_Text_Brandon:
	.string "Beyond this door lies the PILLAR!\p"
	.string "Seven locks seal it, and I am one\n"
	.string "of them. Come, then!$"

BattleFrontier_DevonFactory_B2F_Text_LockLights:
	.string "Seven red lights glow beside the\n"
	.string "door. One for each lock.$"

BattleFrontier_DevonFactory_B2F_Text_GeneratorUnit:
	.string "A DEVON generator. The readout\n"
	.string "says: OUTPUT TO PILLAR.$"

BattleFrontier_DevonFactory_B2F_Text_Generator:
	.string "The generator hums. The floor\n"
	.string "trembles under it.$"

BattleFrontier_DevonFactory_B2F_Text_PillarDoorSealed:
	.string "The door won't budge.\n"
	.string "Seven red lights glow beside it.$"

