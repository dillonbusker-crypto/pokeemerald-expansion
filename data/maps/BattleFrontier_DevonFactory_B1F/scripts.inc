BattleFrontier_DevonFactory_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_DevonFactory_B1F_OnTransition
	.byte 0

@ ============================================================================
@ Ten Gauntlets: the Holding Block (storyline.md, "After gauntlet 8"). GRETA
@ (by the door) and NOLAND (at the cell controls) are two of the five guards.
@ With both beaten, the controls open every cell: MOM, DAD and the BROKER
@ head for the exit, and HOOPA vanishes through one of its rings (it waits
@ for the player in the Arena later).
@ ============================================================================

BattleFrontier_DevonFactory_B1F_OnTransition:
	checktrainerflag TRAINER_FACTORY_GRETA
	call_if TRUE, BattleFrontier_DevonFactory_B1F_EventScript_HideGreta
	checktrainerflag TRAINER_FACTORY_NOLAND
	call_if TRUE, BattleFrontier_DevonFactory_B1F_EventScript_HideNoland
	call_if_set FLAG_ENDGAME_CELLS_OPENED, BattleFrontier_DevonFactory_B1F_EventScript_HideCaptives
	call_if_ge VAR_ENDGAME_STATE, 5, BattleFrontier_DevonFactory_B1F_EventScript_HideAll
	end

BattleFrontier_DevonFactory_B1F_EventScript_HideGreta::
	setflag FLAG_TEMP_1
	return

BattleFrontier_DevonFactory_B1F_EventScript_HideNoland::
	setflag FLAG_TEMP_2
	return

BattleFrontier_DevonFactory_B1F_EventScript_HideCaptives::
	setflag FLAG_TEMP_3
	return

BattleFrontier_DevonFactory_B1F_EventScript_HideAll::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	return

BattleFrontier_DevonFactory_B1F_EventScript_Greta::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Greta, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_FACTORY_GRETA, BattleFrontier_DevonFactory_B1F_Text_GretaDefeat
	msgbox BattleFrontier_DevonFactory_B1F_Text_GretaAfter, MSGBOX_DEFAULT
	goto DevonFactory_EventScript_BrainBeaten

BattleFrontier_DevonFactory_B1F_EventScript_Noland::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Noland, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_FACTORY_NOLAND, BattleFrontier_DevonFactory_B1F_Text_NolandDefeat
	msgbox BattleFrontier_DevonFactory_B1F_Text_NolandAfter, MSGBOX_DEFAULT
	goto DevonFactory_EventScript_BrainBeaten

BattleFrontier_DevonFactory_B1F_EventScript_Mom::
	msgbox BattleFrontier_DevonFactory_B1F_Text_Mom, MSGBOX_NPC
	end

BattleFrontier_DevonFactory_B1F_EventScript_Dad::
	msgbox BattleFrontier_DevonFactory_B1F_Text_Dad, MSGBOX_NPC
	end

BattleFrontier_DevonFactory_B1F_EventScript_Broker::
	msgbox BattleFrontier_DevonFactory_B1F_Text_Broker, MSGBOX_NPC
	end

BattleFrontier_DevonFactory_B1F_EventScript_Hoopa::
	lock
	playmoncry SPECIES_HOOPA, CRY_MODE_NORMAL
	msgbox BattleFrontier_DevonFactory_B1F_Text_HoopaCaged, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The controls at (5-7, 1). While GRETA or NOLAND still stands, they're
@ locked; with both beaten, every cell opens. The captives talk from their
@ cells, then everyone is gone under a fade.
BattleFrontier_DevonFactory_B1F_EventScript_CellControls::
	lockall
	goto_if_set FLAG_ENDGAME_CELLS_OPENED, BattleFrontier_DevonFactory_B1F_EventScript_CellsAlreadyOpen
	goto_if_lt VAR_ENDGAME_STATE, 4, BattleFrontier_DevonFactory_B1F_EventScript_CellsLocked
	checktrainerflag TRAINER_FACTORY_GRETA
	goto_if FALSE, BattleFrontier_DevonFactory_B1F_EventScript_CellsGuarded
	checktrainerflag TRAINER_FACTORY_NOLAND
	goto_if FALSE, BattleFrontier_DevonFactory_B1F_EventScript_CellsGuarded
	msgbox BattleFrontier_DevonFactory_B1F_Text_OpenCells, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_DevonFactory_B1F_EventScript_CellsEnd
	closemessage
	playse SE_UNLOCK
	waitse
	msgbox BattleFrontier_DevonFactory_B1F_Text_CellsOpened, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B1F_Text_FreedMom, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B1F_Text_FreedDad, MSGBOX_DEFAULT
	msgbox BattleFrontier_DevonFactory_B1F_Text_FreedBroker, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_HOOPA, CRY_MODE_ENCOUNTER
	msgbox BattleFrontier_DevonFactory_B1F_Text_FreedHoopa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	playse SE_M_TELEPORT
	removeobject LOCALID_DEVON_FACTORY_HOOPA
	waitse
	msgbox BattleFrontier_DevonFactory_B1F_Text_HoopaVanished, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_DEVON_FACTORY_MOM
	removeobject LOCALID_DEVON_FACTORY_DAD
	removeobject LOCALID_DEVON_FACTORY_BROKER
	setflag FLAG_ENDGAME_CELLS_OPENED
	fadescreen FADE_FROM_BLACK
	msgbox BattleFrontier_DevonFactory_B1F_Text_CaptivesLeft, MSGBOX_DEFAULT
BattleFrontier_DevonFactory_B1F_EventScript_CellsEnd::
	releaseall
	end

BattleFrontier_DevonFactory_B1F_EventScript_CellsAlreadyOpen::
	msgbox BattleFrontier_DevonFactory_B1F_Text_CellsAlreadyOpen, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_DevonFactory_B1F_EventScript_CellsLocked::
	msgbox BattleFrontier_DevonFactory_B1F_Text_CellControls, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_DevonFactory_B1F_EventScript_CellsGuarded::
	msgbox BattleFrontier_DevonFactory_B1F_Text_CellsGuarded, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_DevonFactory_B1F_EventScript_Confiscated::
	msgbox BattleFrontier_DevonFactory_B1F_Text_Confiscated, MSGBOX_SIGN
	end

BattleFrontier_DevonFactory_B1F_Text_Greta:
	.string "Visiting hours are over, kid.$"

BattleFrontier_DevonFactory_B1F_Text_Noland:
	.string "Your folks are fine. For now.\n"
	.string "Don't make me change that.$"

BattleFrontier_DevonFactory_B1F_Text_Mom:
	.string "{PLAYER}! Oh, thank goodness!\n"
	.string "Your father's been pacing for hours.$"

BattleFrontier_DevonFactory_B1F_Text_Dad:
	.string "{PLAYER}. Don't worry about us.\n"
	.string "Finish what you came here to do.$"

BattleFrontier_DevonFactory_B1F_Text_Broker:
	.string "My best customer! Get me out of\n"
	.string "here and I'll make it worth your\l"
	.string "while.$"

BattleFrontier_DevonFactory_B1F_Text_CellControls:
	.string "CELL CONTROLS\p"
	.string "All doors: LOCKED.$"

BattleFrontier_DevonFactory_B1F_Text_Confiscated:
	.string "Confiscated belongings. One crate\n"
	.string "is labeled BROKER. It's full of…\l"
	.string "more crates.$"

BattleFrontier_DevonFactory_B1F_Text_GretaDefeat:
	.string "Ha! Now THAT's a fight!$"

BattleFrontier_DevonFactory_B1F_Text_GretaAfter:
	.string "GRETA: You've got guts, kid. I'll\n"
	.string "give you that. And this: my piece of\l"
	.string "the PILLAR key.\p"
	.string "Doesn't change anything. SCOTT\n"
	.string "already has what he wants.$"

BattleFrontier_DevonFactory_B1F_Text_NolandDefeat:
	.string "Every machine breaks down\n"
	.string "eventually, huh.$"

BattleFrontier_DevonFactory_B1F_Text_NolandAfter:
	.string "NOLAND: Fine. Here's my piece of the\n"
	.string "key. The cell controls are yours.\p"
	.string "Go see SCOTT. See where it gets\n"
	.string "you.$"

BattleFrontier_DevonFactory_B1F_Text_HoopaCaged:
	.string "A POKéMON is shut in the cell. It\n"
	.string "watches {PLAYER} curiously.$"

BattleFrontier_DevonFactory_B1F_Text_CellsGuarded:
	.string "CELL CONTROLS\n"
	.string "All doors: LOCKED.\p"
	.string "There's no getting near the\n"
	.string "controls while the guards are here.$"

BattleFrontier_DevonFactory_B1F_Text_OpenCells:
	.string "CELL CONTROLS\n"
	.string "All doors: LOCKED.\p"
	.string "Open every cell?$"

BattleFrontier_DevonFactory_B1F_Text_CellsOpened:
	.string "Every cell door slid open!$"

BattleFrontier_DevonFactory_B1F_Text_FreedMom:
	.string "MOM: {PLAYER}! Oh, I knew you'd\n"
	.string "come!$"

BattleFrontier_DevonFactory_B1F_Text_FreedDad:
	.string "DAD: {PLAYER}. SCOTT is below us,\n"
	.string "at that PILLAR of his.\p"
	.string "Don't worry about us. We'll find\n"
	.string "our own way out. Go!$"

BattleFrontier_DevonFactory_B1F_Text_FreedBroker:
	.string "BROKER: My best customer! I'll\n"
	.string "make this worth your while.\p"
	.string "Come and find me once you're out\n"
	.string "of here.$"

BattleFrontier_DevonFactory_B1F_Text_FreedHoopa:
	.string "The POKéMON in the last cell is\n"
	.string "free! It's a HOOPA!$"

BattleFrontier_DevonFactory_B1F_Text_HoopaVanished:
	.string "HOOPA vanished into one of its\n"
	.string "rings!$"

BattleFrontier_DevonFactory_B1F_Text_CaptivesLeft:
	.string "MOM, DAD and the BROKER hurried off\n"
	.string "toward the exit.$"

BattleFrontier_DevonFactory_B1F_Text_CellsAlreadyOpen:
	.string "CELL CONTROLS\n"
	.string "All doors: OPEN.$"
