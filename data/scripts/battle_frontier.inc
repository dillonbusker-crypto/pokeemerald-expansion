BattleFrontier_ShowCaughtBannedSpecies::
	goto_if_eq VAR_0x8005, 0, BattleFrontier_ShowCaughtBannedSpeciesEnd
	msgbox BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ShowCaughtBannedSpeciesEnd
	callnative ShowBattleFrontierCaughtBannedSpecies
	waitstate
BattleFrontier_ShowCaughtBannedSpeciesEnd:
	return


BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies:
	.string "Do you want to see the list of\n"
	.string "POKéMON species you can't bring?$"

@ Ten Gauntlets: the PokeNav's auto-heal (Devon) put Pokemon Centers out of
@ business (storyline.md). The first white-out gets Nurse Joy's delight.
EventScript_FrontierFirstPatient::
	msgbox Text_FrontierFirstPatient, MSGBOX_DEFAULT
	setflag FLAG_FRONTIER_FIRST_PATIENT
	return

Text_FrontierFirstPatient:
	.string "Oh! A patient! You're the first\n"
	.string "one we've had in a long time!\p"
	.string "Ever since those PokéNavs started\n"
	.string "healing everyone, nobody comes in\l"
	.string "anymore...$"
