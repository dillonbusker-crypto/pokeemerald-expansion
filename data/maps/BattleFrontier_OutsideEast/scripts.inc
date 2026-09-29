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
	call_if_ge VAR_ARTISAN_QUEST_STEP, 5, BattleFrontier_OutsideEast_EventScript_HideFlotsam
	call_if_unset FLAG_ARTISAN_LATI_CAUGHT, BattleFrontier_OutsideEast_EventScript_HideLooker
	setflag FLAG_TEMP_6
	call_if_eq VAR_ARTISAN_QUEST_STEP, 5, BattleFrontier_OutsideEast_EventScript_ShowFlotsamAtWaterfall
	call BattleFrontier_OutsideEast_EventScript_RemoveHMs
	call BattleFrontier_OutsideEast_EventScript_SetupRival
	setflag FLAG_TEMP_5
	call_if_eq VAR_NORMAN_STORY_STATE, 3, BattleFrontier_OutsideEast_EventScript_ShowNorman
	end

BattleFrontier_OutsideEast_EventScript_ShowNorman::
	clearflag FLAG_TEMP_5
	return

@ Ten Gauntlets: the rival blocks the Battle Tower door, demanding a fair
@ rematch for ROUTE 103, from the moment SCOTT has handed over the starting
@ team until the player beats them. MAY for a male player, BRENDAN for a
@ female one.
BattleFrontier_OutsideEast_EventScript_SetupRival::
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	goto_if_set FLAG_FRONTIER_RIVAL_REMATCH_DONE, Common_EventScript_NopReturn
	specialvar VAR_RESULT, HasReceivedFrontierStartingGrants
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, BattleFrontier_OutsideEast_EventScript_ShowRivalMay
	clearflag FLAG_TEMP_4
	return

BattleFrontier_OutsideEast_EventScript_ShowRivalMay::
	clearflag FLAG_TEMP_3
	return

@ Ten Gauntlets: the Artisan Cave side quest (easter-eggs-spec.md, #1).
@ VAR_ARTISAN_QUEST_STEP: 0 none, 1 FLOTSAM's pitch, 2 odd tree gone,
@ 3 FLOTSAM named the Broker, 4 Broker reacted, 5 MASTER BALL bought (FLOTSAM
@ blocks the waterfall), 6 FLOTSAM beaten, 7 Latios/Latias caught.
@ FLOTSAM stands on the dead-end path above the odd tree until step 5, then on
@ the tree's old spot (the only way down to the water) until he's beaten.
@ LOOKER takes his first spot once a Lati is caught.
BattleFrontier_OutsideEast_EventScript_ShowFlotsamAtWaterfall::
	clearflag FLAG_TEMP_6
	return

@ SCOTT bans HMs on the Frontier - takes back the ones older saves got.
BattleFrontier_OutsideEast_EventScript_RemoveHMs::
	special RemoveFrontierHMs
	return

BattleFrontier_OutsideEast_EventScript_HideFlotsam::
	setflag FLAG_TEMP_1
	return

BattleFrontier_OutsideEast_EventScript_HideLooker::
	setflag FLAG_TEMP_2
	return

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

@ Fought under Frontier rules: the battle itself gets the Frontier battle
@ type (IsFrontierRivalTrainer() in src/battle_setup.c - Set style, no bag),
@ and held items used up in it come back afterwards, same as in a run.
BattleFrontier_OutsideEast_EventScript_Rival::
	lock
	faceplayer
	special SaveFacilityHeldItems
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, BattleFrontier_OutsideEast_EventScript_RivalMay
	goto BattleFrontier_OutsideEast_EventScript_RivalBrendan
	end

BattleFrontier_OutsideEast_EventScript_RivalMay::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	msgbox BattleFrontier_OutsideEast_Text_MayRematch, MSGBOX_DEFAULT
	closemessage
	switch VAR_STARTER_MON
	case 1, BattleFrontier_OutsideEast_EventScript_MayBattleWater
	case 2, BattleFrontier_OutsideEast_EventScript_MayBattleGrass
	goto BattleFrontier_OutsideEast_EventScript_MayBattleFire
	end

BattleFrontier_OutsideEast_EventScript_MayBattleFire::
	trainerbattle_earlyrival TRAINER_FRONTIER_RIVAL_MAY_FIRE, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_MayDefeated, BattleFrontier_OutsideEast_Text_MayWon
	goto BattleFrontier_OutsideEast_EventScript_MayAfterBattle
	end

BattleFrontier_OutsideEast_EventScript_MayBattleWater::
	trainerbattle_earlyrival TRAINER_FRONTIER_RIVAL_MAY_WATER, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_MayDefeated, BattleFrontier_OutsideEast_Text_MayWon
	goto BattleFrontier_OutsideEast_EventScript_MayAfterBattle
	end

BattleFrontier_OutsideEast_EventScript_MayBattleGrass::
	trainerbattle_earlyrival TRAINER_FRONTIER_RIVAL_MAY_GRASS, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_MayDefeated, BattleFrontier_OutsideEast_Text_MayWon
	goto BattleFrontier_OutsideEast_EventScript_MayAfterBattle
	end

BattleFrontier_OutsideEast_EventScript_MayAfterBattle::
	copyvar VAR_TEMP_5, VAR_RESULT
	special RestoreFacilityHeldItems
	goto_if_eq VAR_TEMP_5, TRUE, BattleFrontier_OutsideEast_EventScript_MayPlayerLost
	msgbox BattleFrontier_OutsideEast_Text_MayStormsOff, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8008, LOCALID_FRONTIER_RIVAL_MAY
	goto BattleFrontier_OutsideEast_EventScript_RivalStormOff
	end

BattleFrontier_OutsideEast_EventScript_MayPlayerLost::
	msgbox BattleFrontier_OutsideEast_Text_MayAgain, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RivalBrendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	msgbox BattleFrontier_OutsideEast_Text_BrendanRematch, MSGBOX_DEFAULT
	closemessage
	switch VAR_STARTER_MON
	case 1, BattleFrontier_OutsideEast_EventScript_BrendanBattleWater
	case 2, BattleFrontier_OutsideEast_EventScript_BrendanBattleGrass
	goto BattleFrontier_OutsideEast_EventScript_BrendanBattleFire
	end

BattleFrontier_OutsideEast_EventScript_BrendanBattleFire::
	trainerbattle_earlyrival TRAINER_FRONTIER_RIVAL_BRENDAN_FIRE, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_BrendanDefeated, BattleFrontier_OutsideEast_Text_BrendanWon
	goto BattleFrontier_OutsideEast_EventScript_BrendanAfterBattle
	end

BattleFrontier_OutsideEast_EventScript_BrendanBattleWater::
	trainerbattle_earlyrival TRAINER_FRONTIER_RIVAL_BRENDAN_WATER, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_BrendanDefeated, BattleFrontier_OutsideEast_Text_BrendanWon
	goto BattleFrontier_OutsideEast_EventScript_BrendanAfterBattle
	end

BattleFrontier_OutsideEast_EventScript_BrendanBattleGrass::
	trainerbattle_earlyrival TRAINER_FRONTIER_RIVAL_BRENDAN_GRASS, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_BrendanDefeated, BattleFrontier_OutsideEast_Text_BrendanWon
	goto BattleFrontier_OutsideEast_EventScript_BrendanAfterBattle
	end

BattleFrontier_OutsideEast_EventScript_BrendanAfterBattle::
	copyvar VAR_TEMP_5, VAR_RESULT
	special RestoreFacilityHeldItems
	goto_if_eq VAR_TEMP_5, TRUE, BattleFrontier_OutsideEast_EventScript_BrendanPlayerLost
	msgbox BattleFrontier_OutsideEast_Text_BrendanStormsOff, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8008, LOCALID_FRONTIER_RIVAL_BRENDAN
	goto BattleFrontier_OutsideEast_EventScript_RivalStormOff
	end

BattleFrontier_OutsideEast_EventScript_BrendanPlayerLost::
	msgbox BattleFrontier_OutsideEast_Text_BrendanAgain, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 = the rival's local ID. They walk off along the row, away from
@ whichever side the player is talking from, so they never walk through them.
BattleFrontier_OutsideEast_EventScript_RivalStormOff::
	setflag FLAG_FRONTIER_RIVAL_REMATCH_DONE
	special HealPlayerParty
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, BattleFrontier_OutsideEast_EventScript_RivalStormOffRight
	applymovement VAR_0x8008, BattleFrontier_OutsideEast_Movement_RivalStormOffLeft
	goto BattleFrontier_OutsideEast_EventScript_RivalGone
	end

BattleFrontier_OutsideEast_EventScript_RivalStormOffRight::
	applymovement VAR_0x8008, BattleFrontier_OutsideEast_Movement_RivalStormOffRight
BattleFrontier_OutsideEast_EventScript_RivalGone::
	waitmovement 0
	removeobject VAR_0x8008
	fadedefaultbgm
	release
	end

BattleFrontier_OutsideEast_Movement_RivalStormOffLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

BattleFrontier_OutsideEast_Movement_RivalStormOffRight:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

@ Ten Gauntlets: NORMAN blocks the Battle Tower after the scene at SCOTT's
@ house (VAR_NORMAN_STORY_STATE 3), and won't let the player on to gauntlet 2
@ until they beat him. Frontier rules like the rival's rematch; a loss heals
@ and lets the player try again. See frontier-dialogue.md.
BattleFrontier_OutsideEast_EventScript_Norman::
	lock
	faceplayer
	special SaveFacilityHeldItems
	msgbox BattleFrontier_OutsideEast_Text_NormanChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_earlyrival TRAINER_FRONTIER_NORMAN, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_NormanDefeated, BattleFrontier_OutsideEast_Text_NormanWon
	copyvar VAR_TEMP_5, VAR_RESULT
	special RestoreFacilityHeldItems
	goto_if_eq VAR_TEMP_5, TRUE, BattleFrontier_OutsideEast_EventScript_NormanPlayerLost
	special HealPlayerParty
	msgbox BattleFrontier_OutsideEast_Text_NormanWarning, MSGBOX_DEFAULT
	setvar VAR_0x8004, 300
	special FacilityShopGiveFP
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_OutsideEast_Text_ReceivedNormanFP
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox BattleFrontier_OutsideEast_Text_NormanGoingHome, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NORMAN_STORY_STATE, 4
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, BattleFrontier_OutsideEast_EventScript_NormanLeavesRight
	applymovement LOCALID_FRONTIER_NORMAN, BattleFrontier_OutsideEast_Movement_NormanLeavesLeft
	goto BattleFrontier_OutsideEast_EventScript_NormanGone
	end

BattleFrontier_OutsideEast_EventScript_NormanLeavesRight::
	applymovement LOCALID_FRONTIER_NORMAN, BattleFrontier_OutsideEast_Movement_NormanLeavesRight
BattleFrontier_OutsideEast_EventScript_NormanGone::
	waitmovement 0
	removeobject LOCALID_FRONTIER_NORMAN
	release
	end

BattleFrontier_OutsideEast_EventScript_NormanPlayerLost::
	msgbox BattleFrontier_OutsideEast_Text_NormanAgain, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_Movement_NormanLeavesLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

BattleFrontier_OutsideEast_Movement_NormanLeavesRight:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

BattleFrontier_OutsideEast_EventScript_Flotsam::
	lock
	faceplayer
	goto_if_ge VAR_ARTISAN_QUEST_STEP, 3, BattleFrontier_OutsideEast_EventScript_FlotsamFindBroker
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_FlotsamParanoid
	goto_if_eq VAR_ARTISAN_QUEST_STEP, 1, BattleFrontier_OutsideEast_EventScript_FlotsamFigureItOut
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 3, BattleFrontier_OutsideEast_EventScript_FlotsamPitch
	msgbox BattleFrontier_OutsideEast_Text_FlotsamNobody, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FlotsamPitch::
	msgbox BattleFrontier_OutsideEast_Text_FlotsamPitch, MSGBOX_DEFAULT
	setvar VAR_ARTISAN_QUEST_STEP, 1
	release
	end

BattleFrontier_OutsideEast_EventScript_FlotsamFigureItOut::
	msgbox BattleFrontier_OutsideEast_Text_FlotsamWaterIt, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FlotsamParanoid::
	msgbox BattleFrontier_OutsideEast_Text_FlotsamScared, MSGBOX_DEFAULT
	setvar VAR_ARTISAN_QUEST_STEP, 3
	release
	end

BattleFrontier_OutsideEast_EventScript_FlotsamFindBroker::
	msgbox BattleFrontier_OutsideEast_Text_FlotsamDoneHelping, MSGBOX_DEFAULT
	release
	end

@ Step 5: FLOTSAM turns on the player at the waterfall. Frontier rules
@ (IsFrontierStoryTrainer()); a loss heals and lets the player try again.
BattleFrontier_OutsideEast_EventScript_FlotsamBetrayal::
	lock
	faceplayer
	special SaveFacilityHeldItems
	msgbox BattleFrontier_OutsideEast_Text_FlotsamBetrayal, MSGBOX_DEFAULT
	closemessage
	trainerbattle_earlyrival TRAINER_FRONTIER_FLOTSAM, RIVAL_BATTLE_HEAL_AFTER, BattleFrontier_OutsideEast_Text_FlotsamDefeated, BattleFrontier_OutsideEast_Text_FlotsamWon
	copyvar VAR_TEMP_5, VAR_RESULT
	special RestoreFacilityHeldItems
	goto_if_eq VAR_TEMP_5, TRUE, BattleFrontier_OutsideEast_EventScript_FlotsamPlayerLost
	special HealPlayerParty
	msgbox BattleFrontier_OutsideEast_Text_FlotsamSore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_FLOTSAM_WATERFALL, BattleFrontier_OutsideEast_Movement_FlotsamFlees
	waitmovement 0
	removeobject LOCALID_FRONTIER_FLOTSAM_WATERFALL
	setvar VAR_ARTISAN_QUEST_STEP, 6
	msgbox BattleFrontier_OutsideEast_Text_FlotsamDroppedFP, MSGBOX_DEFAULT
	setvar VAR_0x8004, 300
	special FacilityShopGiveFP
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_OutsideEast_Text_FoundFlotsamFP
	waitmessage
	waitfanfare
	waitbuttonpress
	release
	end

BattleFrontier_OutsideEast_EventScript_FlotsamPlayerLost::
	msgbox BattleFrontier_OutsideEast_Text_FlotsamAgain, MSGBOX_DEFAULT
	release
	end

@ He leaps up the cliff behind him, away from the player.
BattleFrontier_OutsideEast_Movement_FlotsamFlees:
	jump_in_place_down
	jump_2_up
	jump_2_up
	set_invisible
	step_end

@ Ten Gauntlets: the florist (easter-eggs-spec.md, #1) trades the WAILMER PAIL
@ for a LEAFEON - the way past the odd tree. Replaces the vanilla Rich Boy.
BattleFrontier_OutsideEast_EventScript_Florist::
	lock
	faceplayer
	goto_if_set FLAG_FRONTIER_FLORIST_TRADED, BattleFrontier_OutsideEast_EventScript_FloristThanks
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 3, BattleFrontier_OutsideEast_EventScript_FloristAsk
	msgbox BattleFrontier_OutsideEast_Text_FloristBefore, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FloristAsk::
	msgbox BattleFrontier_OutsideEast_Text_FloristWantsLeafeon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_FloristNoLeafeon
	msgbox BattleFrontier_OutsideEast_Text_FloristShowMe, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, BattleFrontier_OutsideEast_EventScript_FloristNoLeafeon
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_ne VAR_RESULT, SPECIES_LEAFEON, BattleFrontier_OutsideEast_EventScript_FloristNotLeafeon
	getpartysize
	goto_if_lt VAR_RESULT, 2, BattleFrontier_OutsideEast_EventScript_FloristOnlyMon
	msgbox BattleFrontier_OutsideEast_Text_FloristOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_FloristNoLeafeon
	special FrontierFloristTakeMon
	msgbox BattleFrontier_OutsideEast_Text_FloristTakesLeafeon, MSGBOX_DEFAULT
	giveitem ITEM_WAILMER_PAIL
	setflag FLAG_FRONTIER_FLORIST_TRADED
	msgbox BattleFrontier_OutsideEast_Text_FloristThanks, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FloristNoLeafeon::
	msgbox BattleFrontier_OutsideEast_Text_FloristNoLeafeon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FloristNotLeafeon::
	msgbox BattleFrontier_OutsideEast_Text_FloristNotLeafeon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FloristOnlyMon::
	msgbox BattleFrontier_OutsideEast_Text_FloristOnlyMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_FloristThanks::
	msgbox BattleFrontier_OutsideEast_Text_FloristThanks, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Looker::
	msgbox BattleFrontier_OutsideEast_Text_Looker, MSGBOX_NPC
	end

@ Ten Gauntlets: the Frontier Brains loiter outside their own facilities
@ (easter-eggs-spec.md, #8). ANABEL is gauntlet 4's boss.
BattleFrontier_OutsideEast_EventScript_Anabel::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 4, BattleFrontier_OutsideEast_EventScript_AnabelBeaten
	msgbox BattleFrontier_OutsideEast_Text_AnabelBefore, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_AnabelBeaten::
	msgbox BattleFrontier_OutsideEast_Text_AnabelAfter, MSGBOX_DEFAULT
	release
	end

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
	checkitem ITEM_WAILMER_PAIL
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideEast_EventScript_SudowoodoEnd
	msgbox BattleFrontier_OutsideEast_Text_UseWailmerPail, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, BattleFrontier_OutsideEast_EventScript_WaterSudowoodo
BattleFrontier_OutsideEast_EventScript_SudowoodoEnd:
	release
	end

@ Also run by src/item_use.c when the WAILMER PAIL is used from the bag.
BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoFlee
	waitmovement 0
	removeobject LOCALID_FRONTIER_SUDOWOODO
	setflag FLAG_DEFEATED_SUDOWOODO
	call_if_lt VAR_ARTISAN_QUEST_STEP, 2, BattleFrontier_OutsideEast_EventScript_SudowoodoFled
	msgbox BattleFrontier_OutsideEast_Text_SudowoodoFled, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_SudowoodoFled::
	setvar VAR_ARTISAN_QUEST_STEP, 2
	return

BattleFrontier_OutsideEast_Movement_SudowoodoFlee:
	jump_in_place_down
	jump_2_up
	jump_2_up
	step_end

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
	goto BattleFrontier_OutsideEast_EventScript_OldWomanShiftyMan
	end

BattleFrontier_OutsideEast_EventScript_OldWomanShiftyMan::
	goto_if_set FLAG_ARTISAN_LATI_CAUGHT, BattleFrontier_OutsideEast_EventScript_OldWomanEnd
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_lt VAR_RESULT, 3, BattleFrontier_OutsideEast_EventScript_OldWomanEnd
	msgbox BattleFrontier_OutsideEast_Text_ShiftyMan, MSGBOX_DEFAULT
BattleFrontier_OutsideEast_EventScript_OldWomanEnd:
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	goto BattleFrontier_OutsideEast_EventScript_OldWomanShiftyMan
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
	.string "That ledge up there drops down\n"
	.string "from a cave. You can hop off it,\l"
	.string "but nobody's ever climbed up.\p"
	.string "...I swear I heard something\n"
	.string "singing in there, though. Two\l"
	.string "voices.$"

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
	.string "Then I met WARDEN WINONA. I got\n"
	.string "wiped out with no saving grace at\l"
	.string "all!$"

BattleFrontier_OutsideEast_EventScript_Woman1_Text3:
	.string "He's on gauntlet 3 now. He did\n"
	.string "great until the weather turned.\p"
	.string "Please don't mention sandstorms\n"
	.string "around him.$"

BattleFrontier_OutsideEast_EventScript_Woman1_Text0:
	.string "He'd never lost once. Then he met\n"
	.string "WARDEN WINONA on the first mat.\p"
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

BattleFrontier_OutsideEast_Text_UseWailmerPail:
	.string "It's an odd tree...\p"
	.string "Water it with the WAILMER PAIL?$"

BattleFrontier_OutsideEast_Text_SudowoodoFled:
	.string "{PLAYER} watered the odd tree. It\n"
	.string "shrieked... it was a SUDOWOODO!\p"
	.string "It fled for good.$"

BattleFrontier_OutsideEast_Text_ShiftyMan:
	.string "...And lately there's been a\n"
	.string "shifty-looking man skulking down\l"
	.string "the path to it. Up to no good, I'd\l"
	.string "wager.$"

BattleFrontier_OutsideEast_Text_FlotsamNobody:
	.string "Huh? What am I doing? None of your\n"
	.string "business, kid.\p"
	.string "...Tell you what. Beat a few of\n"
	.string "the FRONTIER's bosses, and maybe\l"
	.string "I'll loop you in. Only if you're\l"
	.string "up for it.$"

BattleFrontier_OutsideEast_Text_FlotsamPitch:
	.string "Well, well, well. Three bosses on\n"
	.string "your resume.\p"
	.string "Maybe you're good enough to help\n"
	.string "me out after all.\p"
	.string "Look down the waterfall, toward\n"
	.string "the west. There's a cave.\p"
	.string "I was going to keep the spoils all\n"
	.string "to myself... but technically,\l"
	.string "there's enough to share.\p"
	.string "Problem is, this tree down here\n"
	.string "just won't budge. And the florist\l"
	.string "in town refuses to talk to me.\p"
	.string "Figure that out, and I'll consider\n"
	.string "us in business.$"


BattleFrontier_OutsideEast_Text_FlotsamWaterIt:
	.string "That tree's still standing on the\n"
	.string "only way down to the water.\p"
	.string "The florist in town knows how to\n"
	.string "move it. She just won't tell ME.$"

BattleFrontier_OutsideEast_Text_FlotsamScared:
	.string "You got rid of the tree? ...People\n"
	.string "SAW you!\p"
	.string "They're watching. I can feel it.\n"
	.string "Somebody's always watching on this\l"
	.string "island...\p"
	.string "Forget it. I'm getting cold feet.\n"
	.string "I'm out. You should probably quit\l"
	.string "too.\p"
	.string "...But if you're feeling lucky, go\n"
	.string "see the BROKER. He's been doing\l"
	.string "this a lot longer than me.\p"
	.string "I haven't met with him in a long\n"
	.string "time, though. No idea where he's\l"
	.string "set up shop these days.$"

BattleFrontier_OutsideEast_Text_FlotsamDoneHelping:
	.string "I told you, I'm out.\p"
	.string "If you want in, find the BROKER. I\n"
	.string "don't know where he is anymore.$"

BattleFrontier_OutsideEast_Text_Looker:
	.string "I am LOOKER, of the International\n"
	.string "Police!\p"
	.string "We caught this FLOTSAM trying to\n"
	.string "slip off the FRONTIER. Illegal\l"
	.string "sales... tampering with protected\l"
	.string "POKéMON...\p"
	.string "Every one of his POKéMON had been\n"
	.string "wiped out. An easy capture, for\l"
	.string "once!\p"
	.string "...But someone beat him first. Who\n"
	.string "could have been strong enough, I\l"
	.string "wonder?\p"
	.string "...You would not happen to know,\n"
	.string "would you? ...No? Hmm. Very well.\l"
	.string "Carry on.$"

BattleFrontier_OutsideEast_Text_AnabelBefore:
	.string "The last mat is mine.\p"
	.string "Take your time on the first three.\n"
	.string "I'll know when you're ready.$"

BattleFrontier_OutsideEast_Text_AnabelAfter:
	.string "You've got the TOWER. Now let's\n"
	.string "see what the rest of them make of\l"
	.string "you.\p"
	.string "...Has SCOTT ever told you who\n"
	.string "taught all of us?$"

BattleFrontier_OutsideEast_Text_MayRematch:
	.string "MAY: There you are, {PLAYER}{KUN}!\p"
	.string "I told you I'd come. I built a\n"
	.string "real team this time, with the same\l"
	.string "tools you've got.\p"
	.string "Level 50, same as yours. Same\n"
	.string "rules. No tricks.\p"
	.string "Route 103 doesn't count. You're\n"
	.string "not setting foot in that TOWER\l"
	.string "until we settle this!$"

BattleFrontier_OutsideEast_Text_MayDefeated:
	.string "...No. No way.\p"
	.string "I lost. For real this time.$"

BattleFrontier_OutsideEast_Text_MayWon:
	.string "Ha! NOW that's a real battle!$"

BattleFrontier_OutsideEast_Text_MayAgain:
	.string "MAY: See? Not so easy when it's\n"
	.string "fair!\p"
	.string "I healed your team. I'm not\n"
	.string "letting you blame a technicality.\p"
	.string "Whenever you're ready... we go\n"
	.string "again!$"

BattleFrontier_OutsideEast_Text_MayStormsOff:
	.string "MAY: ...Fine. FINE. You won.\p"
	.string "Don't get comfortable! Those\n"
	.string "gauntlets are going to chew you\l"
	.string "up...\p"
	.string "And I'll be watching when they do!$"

BattleFrontier_OutsideEast_Text_BrendanRematch:
	.string "BRENDAN: There you are, {PLAYER}!\p"
	.string "I told you I'd come. I built a\n"
	.string "real team this time, with the same\l"
	.string "tools you've got.\p"
	.string "Level 50, same as yours. Same\n"
	.string "rules. No tricks.\p"
	.string "Route 103 doesn't count. You're\n"
	.string "not setting foot in that TOWER\l"
	.string "until we settle this!$"

BattleFrontier_OutsideEast_Text_BrendanDefeated:
	.string "...No. No way.\p"
	.string "I lost. For real this time.$"

BattleFrontier_OutsideEast_Text_BrendanWon:
	.string "Ha! NOW that's a real battle!$"

BattleFrontier_OutsideEast_Text_BrendanAgain:
	.string "BRENDAN: See? Not so easy when\n"
	.string "it's fair!\p"
	.string "I healed your team. I'm not\n"
	.string "letting you blame a technicality.\p"
	.string "Whenever you're ready... we go\n"
	.string "again!$"

BattleFrontier_OutsideEast_Text_BrendanStormsOff:
	.string "BRENDAN: ...Fine. FINE. You won.\p"
	.string "Don't get comfortable! Those\n"
	.string "gauntlets are going to chew you\l"
	.string "up...\p"
	.string "And I'll be watching when they do!$"

BattleFrontier_OutsideEast_Text_NormanChallenge:
	.string "NORMAN: {PLAYER}.\p"
	.string "I owe you an honest word. All I\n"
	.string "ever wanted was for you to have\l"
	.string "the adventure of a lifetime. Eight\l"
	.string "GYMS, the open road... the way I\l"
	.string "had it.\p"
	.string "But if this is the path you've\n"
	.string "chosen, then I'll support it. On\l"
	.string "one condition.\p"
	.string "I won't let you go any further\n"
	.string "until I know you can protect\l"
	.string "yourself.\p"
	.string "They fight two on two in there. So\n"
	.string "will we. Show me, {PLAYER}!$"

BattleFrontier_OutsideEast_Text_NormanDefeated:
	.string "...Hah. You've grown.$"

BattleFrontier_OutsideEast_Text_NormanWon:
	.string "Not yet. You're not ready yet.$"

BattleFrontier_OutsideEast_Text_NormanAgain:
	.string "NORMAN: Your team's healed.\p"
	.string "Think about what went wrong. Then\n"
	.string "come back and show me again. I'll\l"
	.string "be right here.$"

BattleFrontier_OutsideEast_Text_NormanWarning:
	.string "NORMAN: ...You can protect\n"
	.string "yourself. I can see that now.\p"
	.string "But listen to me, {PLAYER}. Watch\n"
	.string "out for SCOTT.\p"
	.string "I've heard rumors about him.\n"
	.string "Strange ones. Something about all\l"
	.string "of this just isn't right.\p"
	.string "Keep your eyes open.\p"
	.string "...Oh, and here. Consider it a\n"
	.string "reward. I, ah... borrowed it from\l"
	.string "SCOTT's wallet on my way out.$"

BattleFrontier_OutsideEast_Text_ReceivedNormanFP:
	.string "{PLAYER} received 300 FP!$"

BattleFrontier_OutsideEast_Text_NormanGoingHome:
	.string "NORMAN: Don't tell your mother.\p"
	.string "I'm heading home to LITTLEROOT.\n"
	.string "Come and see us when you can.$"

BattleFrontier_OutsideEast_Text_FlotsamBetrayal:
	.string "FLOTSAM: Well, look who it is. And\n"
	.string "with a MASTER BALL, too...\p"
	.string "Yeah, I had a change of heart.\n"
	.string "I've been thinking. Why share?\p"
	.string "I'm done being a small-timer. I'll\n"
	.string "risk it all.\p"
	.string "Here's the plan: I beat you, I\n"
	.string "take that MASTER BALL, and I go\l"
	.string "claim the prize in that cave. All\l"
	.string "for myself.\p"
	.string "Nothing personal, kid!$"

BattleFrontier_OutsideEast_Text_FlotsamDefeated:
	.string "No... NO! Not to a kid!$"

BattleFrontier_OutsideEast_Text_FlotsamWon:
	.string "Heh. The MASTER BALL's as good as\n"
	.string "mine.$"

BattleFrontier_OutsideEast_Text_FlotsamAgain:
	.string "FLOTSAM: Your POKéMON look healthy\n"
	.string "enough to lose again.\p"
	.string "Come back whenever you want to\n"
	.string "hand over that MASTER BALL!$"

BattleFrontier_OutsideEast_Text_FlotsamSore:
	.string "FLOTSAM: I can't believe I lost to\n"
	.string "a kid...\p"
	.string "Heh. Doesn't matter anyway. SCOTT\n"
	.string "bans HMs on the FRONTIER. Without\l"
	.string "SURF, you'll never get down to\l"
	.string "that cave.\p"
	.string "...Wait a second. Are you the one\n"
	.string "who's got that fancy L menu?\p"
	.string "...Whatever. I'm out of here!$"

BattleFrontier_OutsideEast_Text_FlotsamDroppedFP:
	.string "FLOTSAM dropped something in his\n"
	.string "hurry...$"

BattleFrontier_OutsideEast_Text_FoundFlotsamFP:
	.string "{PLAYER} found 300 FP!$"

BattleFrontier_OutsideEast_Text_FloristBefore:
	.string "I really want a LEAFEON to help\n"
	.string "with my flowers... but I'm not\l"
	.string "strong enough to beat the TOWER's\l"
	.string "third boss.\p"
	.string "You look strong. Maybe if you\n"
	.string "could beat it, you could help me?\p"
	.string "...Oh, never mind me. I'm getting\n"
	.string "ahead of myself.$"

BattleFrontier_OutsideEast_Text_FloristWantsLeafeon:
	.string "A LEAFEON would be perfect for my\n"
	.string "flowers.\p"
	.string "But the EXCHANGE CORNER only sells\n"
	.string "them once you've cleared gauntlet\l"
	.string "2, and I'm just not strong enough.\p"
	.string "...Do you have a LEAFEON?$"

BattleFrontier_OutsideEast_Text_FloristShowMe:
	.string "Really? Let me see!$"

BattleFrontier_OutsideEast_Text_FloristNotLeafeon:
	.string "Oh... that isn't a LEAFEON.$"

BattleFrontier_OutsideEast_Text_FloristOnlyMon:
	.string "I couldn't take your only POKéMON!$"

BattleFrontier_OutsideEast_Text_FloristNoLeafeon:
	.string "Oh... If you ever get a LEAFEON,\n"
	.string "please come and see me!$"

BattleFrontier_OutsideEast_Text_FloristOffer:
	.string "Oh, it's beautiful!\p"
	.string "I'll trade you your LEAFEON for a\n"
	.string "very special item, if you're\l"
	.string "willing.$"

BattleFrontier_OutsideEast_Text_FloristTakesLeafeon:
	.string "Thank you so much! Here, this is\n"
	.string "for you.$"

BattleFrontier_OutsideEast_Text_FloristThanks:
	.string "LEAFEON is doing wonders for my\n"
	.string "flowers!\p"
	.string "That WAILMER PAIL has watered a\n"
	.string "lot of odd things in its time... I\l"
	.string "hear there's a tree down by the\l"
	.string "water that could use a drink.$"
