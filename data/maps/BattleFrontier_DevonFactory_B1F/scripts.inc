BattleFrontier_DevonFactory_B1F_MapScripts::
	.byte 0

@ Ten Gauntlets: the Holding Block. GRETA and NOLAND guard MOM, DAD and the
@ BROKER; they leave as the player rescues them (to be scripted).
BattleFrontier_DevonFactory_B1F_EventScript_Greta::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Greta, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B1F_EventScript_Noland::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Noland, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B1F_EventScript_Mom::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Mom, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B1F_EventScript_Dad::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Dad, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B1F_EventScript_Broker::
	lock
	faceplayer
	msgbox BattleFrontier_DevonFactory_B1F_Text_Broker, MSGBOX_DEFAULT
	release
	end

BattleFrontier_DevonFactory_B1F_EventScript_CellControls::
	msgbox BattleFrontier_DevonFactory_B1F_Text_CellControls, MSGBOX_SIGN
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

