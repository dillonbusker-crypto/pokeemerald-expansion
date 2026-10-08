BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_OutsideEast_OnFrame
	.byte 0

BattleFrontier_OutsideEast_OnFrame:
	map_script_2 VAR_BROKER_STORY_STATE, 3, BattleFrontier_OutsideEast_EventScript_CenterScott
	map_script_2 VAR_TEMP_7, 1, BattleFrontier_OutsideEast_EventScript_CrownRival
	map_script_2 VAR_TEMP_2, 1, BattleFrontier_OutsideEast_EventScript_PyramidWallaceScene
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_OutsideEast_EventScript_BaseScene
	.2byte 0

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
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	call BattleFrontier_OutsideEast_EventScript_ArmScottCaveWarning
	call BattleFrontier_OutsideEast_EventScript_SetupSteven
	call BattleFrontier_OutsideEast_EventScript_SetupBrokerStory
	call BattleFrontier_OutsideEast_EventScript_SetupRival
	call BattleFrontier_OutsideEast_EventScript_SetupCrownStory
	call BattleFrontier_OutsideEast_EventScript_SetupEndgame
	call BattleFrontier_OutsideEast_EventScript_SetupBadDreams
	setflag FLAG_TEMP_5
	call_if_eq VAR_NORMAN_STORY_STATE, 3, BattleFrontier_OutsideEast_EventScript_ShowNorman
	end

@ Ten Gauntlets: Bad Dreams (storyline.md). The twin sleeps where she stands
@ while the event runs: facing down, no looking around.
BattleFrontier_OutsideEast_EventScript_SetupBadDreams::
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	setobjectmovementtype LOCALID_FRONTIER_TWIN, MOVEMENT_TYPE_FACE_DOWN
	return

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
	goto_if_set FLAG_FRONTIER_RIVAL_REMATCH_DONE, BattleFrontier_OutsideEast_EventScript_SetupRivalPlaza
	specialvar VAR_RESULT, HasReceivedFrontierStartingGrants
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NopReturn
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, BattleFrontier_OutsideEast_EventScript_ShowRivalMay
	clearflag FLAG_TEMP_4
	return

BattleFrontier_OutsideEast_EventScript_ShowRivalMay::
	clearflag FLAG_TEMP_3
	return

@ Ten Gauntlets: after the rematch, the rival trains on the plaza in front of
@ the Battle Tower, with a new line after each gauntlet the player clears
@ (storyline.md). Once gauntlet 5 is cleared, the rival is at the Factory
@ door instead (BattleFrontier_OutsideWest), and after that, in LITTLEROOT.
BattleFrontier_OutsideEast_EventScript_SetupRivalPlaza::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, Common_EventScript_NopReturn
	setobjectxyperm LOCALID_FRONTIER_RIVAL_MAY, 13, 18
	setobjectxyperm LOCALID_FRONTIER_RIVAL_BRENDAN, 13, 18
	setobjectmovementtype LOCALID_FRONTIER_RIVAL_MAY, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_FRONTIER_RIVAL_BRENDAN, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, BattleFrontier_OutsideEast_EventScript_ShowRivalMay
	clearflag FLAG_TEMP_4
	return

BattleFrontier_OutsideEast_EventScript_RivalPlaza::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideEast_EventScript_RivalPlaza0
	case 1, BattleFrontier_OutsideEast_EventScript_RivalPlaza1
	case 2, BattleFrontier_OutsideEast_EventScript_RivalPlaza2
	case 3, BattleFrontier_OutsideEast_EventScript_RivalPlaza3
	msgbox BattleFrontier_OutsideEast_Text_RivalPlaza4, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RivalPlaza0::
	msgbox BattleFrontier_OutsideEast_Text_RivalPlaza0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RivalPlaza1::
	msgbox BattleFrontier_OutsideEast_Text_RivalPlaza1, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RivalPlaza2::
	msgbox BattleFrontier_OutsideEast_Text_RivalPlaza2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RivalPlaza3::
	msgbox BattleFrontier_OutsideEast_Text_RivalPlaza3, MSGBOX_DEFAULT
	release
	end

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
	goto_if_set FLAG_FRONTIER_RIVAL_REMATCH_DONE, BattleFrontier_OutsideEast_EventScript_RivalPlaza
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

@ Step 5: FLOTSAM turns on the player at the waterfall, with the SCRAMBLER
@ jamming both PokeNavs' auto-heal. It's a real battle (storyline.md): no heal
@ after a win - the player can visit Nurse Joy - and a loss is a real white-
@ out back to the Frontier's Pokemon Center. Frontier rules otherwise
@ (IsFrontierStoryTrainer()).
BattleFrontier_OutsideEast_EventScript_FlotsamBetrayal::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideEast_Text_FlotsamBetrayal, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_FRONTIER_FLOTSAM, BattleFrontier_OutsideEast_Text_FlotsamDefeated
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
	setflag FLAG_FRONTIER_FLORIST_ASKED
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
	lock
	faceplayer
	checkitem ITEM_SCRAMBLER
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideEast_EventScript_LookerAgain
	msgbox BattleFrontier_OutsideEast_Text_Looker, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_LookerScrambler, MSGBOX_DEFAULT
	giveitem ITEM_SCRAMBLER
	msgbox BattleFrontier_OutsideEast_Text_LookerScramblerAfter, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_LookerAgain::
	msgbox BattleFrontier_OutsideEast_Text_LookerAgain, MSGBOX_DEFAULT
	release
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
	goto_if_ge VAR_RESULT, 6, BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Cleared6
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Cleared6:
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text6, MSGBOX_SIGN
	end

@ Ten Gauntlets: the Arena hosts no gauntlet; it's the sparring ground.
BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 7, BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Cleared7
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text0, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Cleared7:
	msgbox BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text7, MSGBOX_SIGN
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
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_NORMAN, BattleFrontier_OutsideEast_RichBoy_Gossip0
	case GOSSIP_SYSTEM_DOWN, BattleFrontier_OutsideEast_RichBoy_Gossip1
	case GOSSIP_SMUGGLER, BattleFrontier_OutsideEast_RichBoy_Gossip2
	case GOSSIP_LAB, BattleFrontier_OutsideEast_RichBoy_Gossip3
	case GOSSIP_SQUAD, BattleFrontier_OutsideEast_RichBoy_Gossip4
	case GOSSIP_ARREST, BattleFrontier_OutsideEast_RichBoy_Gossip5
	case GOSSIP_RAID, BattleFrontier_OutsideEast_RichBoy_Gossip6
	case GOSSIP_TAKEN, BattleFrontier_OutsideEast_RichBoy_Gossip7
	case GOSSIP_STANDOFF, BattleFrontier_OutsideEast_RichBoy_Gossip8
	case GOSSIP_SIEGE, BattleFrontier_OutsideEast_RichBoy_Gossip9
	case GOSSIP_AFTERMATH, BattleFrontier_OutsideEast_RichBoy_Gossip10
	case GOSSIP_DEVON, BattleFrontier_OutsideEast_RichBoy_Gossip11
	case GOSSIP_DEVON_FREED, BattleFrontier_OutsideEast_RichBoy_Gossip12
	case GOSSIP_SIPHON, BattleFrontier_OutsideEast_RichBoy_Gossip13
	case GOSSIP_MAUVILLE, BattleFrontier_OutsideEast_RichBoy_Gossip14
	case GOSSIP_MAUVILLE_FREED, BattleFrontier_OutsideEast_RichBoy_Gossip15
	case GOSSIP_SKY_PILLAR, BattleFrontier_OutsideEast_RichBoy_Gossip16
	case GOSSIP_ENDING, BattleFrontier_OutsideEast_RichBoy_Gossip17
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
BattleFrontier_OutsideEast_RichBoy_Gossip0::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip0, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip1::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip1, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip2::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip2, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip3::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip3, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip4::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip4, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip5::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip5, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip6::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip6, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip7::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip7, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip8::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip8, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip9::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip9, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip9:
	.string "The CHAMPION blew the FACTORY's door\n"
	.string "clean off! WALLACE, with a PALKIA!\p"
	.string "I saw it. I'm telling everyone.\n"
	.string "Everyone.$"

BattleFrontier_OutsideEast_RichBoy_Gossip10::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip10, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip10:
	.string "SCOTT is gone. The BRAINS are gone.\n"
	.string "The shops are giving it all away!\p"
	.string "And they say WALLACE lost too.\n"
	.string "…What is going ON?$"

BattleFrontier_OutsideEast_RichBoy_Gossip11::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip11, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip12::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip12, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip11:
	.string "The ELITE FOUR are guarding DEVON\n"
	.string "CORPORATION. Not the LEAGUE, DEVON!\p"
	.string "I've run out of people to tell.$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip12:
	.string "Somebody beat the whole ELITE FOUR,\n"
	.string "one after another, inside DEVON!\p"
	.string "...It was you again, wasn't it?$"

BattleFrontier_OutsideEast_RichBoy_Gossip13::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip13, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip13:
	.string "The chips are OFF! Every POKéMON on\n"
	.string "this island can grow again!\p"
	.string "The CROWN is glowing, and MAUVILLE\n"
	.string "is next, I heard. I'm telling everyone!$"

BattleFrontier_OutsideEast_RichBoy_Gossip14::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip14, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip14:
	.string "TEAM AQUA and TEAM MAGMA are working\n"
	.string "together! They took all of MAUVILLE!\p"
	.string "“A new order,” they keep saying.\n"
	.string "And something about a generator.\l"
	.string "I heard it from a guy who heard it...$"

BattleFrontier_OutsideEast_RichBoy_Gossip15::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip15, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip15:
	.string "MAUVILLE is free! And SCOTT is headed\n"
	.string "for SKY PILLAR!\p"
	.string "And NURSE JOY's CHANSEY can take a\n"
	.string "POKéMON to level 100! ...You've been\l"
	.string "busy, haven't you?$"

BattleFrontier_OutsideEast_RichBoy_Gossip16::
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip16, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip16:
	.string "STEVEN, WALLACE, NORMAN and WATTSON\n"
	.string "are at SKY PILLAR! And all seven\l"
	.string "BRAINS jumped them!\p"
	.string "Somebody climbed up alone. I'd bet\n"
	.string "my allowance it was you.$"

BattleFrontier_OutsideEast_RichBoy_Gossip17::
	goto_if_set FLAG_GIRATINA_CAUGHT, BattleFrontier_OutsideEast_RichBoy_Gossip17Tear
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip17, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_RichBoy_Gossip17Tear::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Gossip17, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_RichBoy_Text_Tear, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_RichBoy_Text_Gossip17:
	.string "SCOTT was ARRESTED! And the CROWN\n"
	.string "was confiscated! The shops are still\l"
	.string "free!\p"
	.string "I told everyone. Everyone.\n"
	.string "...Thank you, by the way.$"

BattleFrontier_OutsideEast_RichBoy_Text_Tear:
	.string "Oh! And DEVON's needles all went\n"
	.string "still at once. Something under\l"
	.string "RUSTBORO finally calmed down!$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip0:
	.string "Did you see it? A man stormed the\n"
	.string "DOUBLES mat yelling about his kid!\p"
	.string "...Wait. You're the kid, aren't you?\n"
	.string "Sorry. I really can't help it.$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip1:
	.string "The shops are down! The fourth mat is\n"
	.string "down! Even the tutors' registers are\l"
	.string "down!\p"
	.string "And there's a shifty guy past the\n"
	.string "PALACE who doesn't look worried at all.\l"
	.string "I'm just saying.$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip2:
	.string "The International Police caught a\n"
	.string "smuggler sneaking off the island!\p"
	.string "And somebody made that odd tree by\n"
	.string "the waterfall run off. Was it you? ...It\l"
	.string "was you, wasn't it?$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip3:
	.string "{RIVAL} came tearing through here\n"
	.string "looking for you! Something about\l"
	.string "their dad!\p"
	.string "Then I swear the CHAMPION walked\n"
	.string "right past the guards. Nobody\l"
	.string "believes me.$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip4:
	.string "STEVEN STONE strolled across the\n"
	.string "plaza, cool as you like, with you right\l"
	.string "behind him.\p"
	.string "Very subtle. Nobody noticed. Except\n"
	.string "me. ...Sorry.$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip5:
	.string "They took the BROKER! SCOTT read out\n"
	.string "the charges himself, right in the\l"
	.string "courtyard!\p"
	.string "...I bought a resist berry off him once.\n"
	.string "Do you think they keep a list?$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip6:
	.string "The FACTORY HEAD and the ARENA\n"
	.string "TYCOON took the ferry to the mainland\l"
	.string "with a bunch of men in suits!\p"
	.string "Toward LITTLEROOT, I heard. Isn't\n"
	.string "that where you're from?$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip7:
	.string "STEVEN STONE just flew in, and he\n"
	.string "looks furious. He's waiting outside\l"
	.string "the FACTORY.\p"
	.string "Something's about to happen. I can\n"
	.string "feel it!$"

BattleFrontier_OutsideEast_RichBoy_Text_Gossip8:
	.string "STEVEN lost! STEVEN STONE, beaten\n"
	.string "outside the FACTORY, in front of\l"
	.string "everyone!\p"
	.string "And SCOTT just told him to get lost.\n"
	.string "...I'm not even going to say anything\l"
	.string "this time.$"

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
	@ Ten Gauntlets: Bad Dreams (storyline.md). Asleep during the event, awake
	@ once DARKRAI is freed (while gauntlet 7 is still open).
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideEast_Twin_Asleep
	goto_if_unset FLAG_DARKRAI_FREED, BattleFrontier_OutsideEast_Twin_Normal
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_eq VAR_RESULT, 6, BattleFrontier_OutsideEast_Twin_Awake
BattleFrontier_OutsideEast_Twin_Normal::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Twin_Asleep::
	lock
	msgbox BattleFrontier_OutsideEast_Twin_Text_Asleep, MSGBOX_DEFAULT
	checkitem ITEM_LUNAR_WING
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideEast_Twin_WingGlows
	release
	end

BattleFrontier_OutsideEast_Twin_WingGlows::
	msgbox BattleFrontier_OutsideEast_Twin_Text_WingGlows, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_Twin_Awake::
	msgbox BattleFrontier_OutsideEast_Twin_Text_Awake, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Twin_Text_Asleep:
	.string "…Mmm… daddy, there's a shadow…\n"
	.string "it has one blue eye… it's behind\l"
	.string "the curtain… Zzz…$"

BattleFrontier_OutsideEast_Twin_Text_WingGlows:
	.string "The LUNAR WING glows faintly.$"

BattleFrontier_OutsideEast_Twin_Text_Awake:
	.string "I had a scary dream and daddy\n"
	.string "couldn't wake me up!\p"
	.string "Then it just went away. I slept so\n"
	.string "well last night!$"

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
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_NORMAN, BattleFrontier_OutsideEast_TriathleteM_Gossip0
	case GOSSIP_SYSTEM_DOWN, BattleFrontier_OutsideEast_TriathleteM_Gossip1
	case GOSSIP_SMUGGLER, BattleFrontier_OutsideEast_TriathleteM_Gossip2
	case GOSSIP_AFTER_LAB, BattleFrontier_OutsideEast_TriathleteM_Gossip3
	case GOSSIP_ARREST, BattleFrontier_OutsideEast_TriathleteM_Gossip4
	case GOSSIP_PALACE, BattleFrontier_OutsideEast_TriathleteM_GossipPalace
	case GOSSIP_RAID, BattleFrontier_OutsideEast_TriathleteM_Gossip5
	case GOSSIP_TAKEN, BattleFrontier_OutsideEast_TriathleteM_Gossip5
	case GOSSIP_STANDOFF, BattleFrontier_OutsideEast_TriathleteM_Gossip6
	case GOSSIP_SIEGE, BattleFrontier_OutsideEast_TriathleteM_Gossip7
	case GOSSIP_AFTERMATH, BattleFrontier_OutsideEast_TriathleteM_Gossip8
	case GOSSIP_DEVON, BattleFrontier_OutsideEast_TriathleteM_Gossip8
	case GOSSIP_DEVON_FREED, BattleFrontier_OutsideEast_TriathleteM_Gossip8
	case GOSSIP_SIPHON, BattleFrontier_OutsideEast_TriathleteM_Gossip9
	case GOSSIP_MAUVILLE, BattleFrontier_OutsideEast_TriathleteM_Gossip9
	case GOSSIP_MAUVILLE_FREED, BattleFrontier_OutsideEast_TriathleteM_Gossip9
	case GOSSIP_SKY_PILLAR, BattleFrontier_OutsideEast_TriathleteM_Gossip10
	case GOSSIP_ENDING, BattleFrontier_OutsideEast_TriathleteM_Gossip11
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
BattleFrontier_OutsideEast_TriathleteM_Gossip0::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip0, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Gossip1::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip1, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Gossip2::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip2, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Gossip3::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip3, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Gossip4::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip4, MSGBOX_NPC
	end

@ GOSSIP_PALACE: the arrest line, or the dream while Bad Dreams runs.
BattleFrontier_OutsideEast_TriathleteM_GossipPalace::
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideEast_TriathleteM_Gossip4
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_BadDreams, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Text_BadDreams:
	.string "Everyone on the island is dreaming\n"
	.string "the same dream. A shadow, a blue\l"
	.string "eye, a hall of curtains.\p"
	.string "Some of them can't wake up. I've\n"
	.string "moved my laps to the early morning,\l"
	.string "before I get drowsy.$"

BattleFrontier_OutsideEast_TriathleteM_Gossip5::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip5, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Gossip6::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip6, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Gossip7::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip7, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip7:
	.string "That heat is coming off the FACTORY.\n"
	.string "Whatever SCOTT's doing, it's pulling\l"
	.string "in everything.\p"
	.string "I've stopped running laps. It's too\n"
	.string "hot.$"

BattleFrontier_OutsideEast_TriathleteM_Gossip8::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip8, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip8:
	.string "They say SCOTT walked out of the\n"
	.string "FACTORY and left, BRAINS and all.\p"
	.string "His MEWTWO beat the CHAMPION's\n"
	.string "PALKIA. I'm glad I missed that one.$"

BattleFrontier_OutsideEast_TriathleteM_Gossip9::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip9, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip9:
	.string "The chips are off! My POKéMON gain\n"
	.string "EXP on my morning laps again!\p"
	.string "I've doubled my laps. MAUVILLE is on\n"
	.string "the news, but I'll worry after my\l"
	.string "cooldown.\p"
	.string "Heard they knocked over MAUVILLE's\n"
	.string "old stone king in the fighting.\p"
	.string "WATTSON built the town around it.\n"
	.string "Bet he's not happy.$"

BattleFrontier_OutsideEast_TriathleteM_Gossip10::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip10, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip10:
	.string "All seven BRAINS ambushed STEVEN at\n"
	.string "SKY PILLAR? Seven! I couldn't beat\l"
	.string "one of them.$"

BattleFrontier_OutsideEast_TriathleteM_Gossip11::
	msgbox BattleFrontier_OutsideEast_TriathleteM_Text_Gossip11, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip11:
	.string "They arrested SCOTT. Clean sweep.\n"
	.string "And the shops are still free.\p"
	.string "Personal best this week, too. Best week\n"
	.string "of my life.$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip0:
	.string "Did you hear the shouting? A GYM\n"
	.string "LEADER chewed SCOTT out at his own\l"
	.string "house!\p"
	.string "And SCOTT just smiled through all of\n"
	.string "it. I've never once seen that man lose\l"
	.string "his cool.$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip1:
	.string "The whole island's system crashed, and\n"
	.string "SCOTT hasn't even come out of his\l"
	.string "house.\p"
	.string "You'd think the man in charge would\n"
	.string "want to be seen fixing it.$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip2:
	.string "I saw the FACTORY HEAD and the ARENA\n"
	.string "TYCOON heading down toward that cave\l"
	.string "below the waterfall.\p"
	.string "SCOTT's own people. Whatever's down\n"
	.string "there, he wants it.$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip3:
	.string "Gauntlet 6 went down, and came back\n"
	.string "up the moment SCOTT made one phone\l"
	.string "call.\p"
	.string "One call. That's how much pull he has\n"
	.string "with DEVON.$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip4:
	.string "SCOTT arrested the BROKER himself.\n"
	.string "Then he packed a bag and took the\l"
	.string "ferry out.\p"
	.string "Feedback from high-profile trainers,\n"
	.string "he said. What could matter more to him\l"
	.string "than his own FRONTIER?$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip5:
	.string "SCOTT's house is dark, and the\n"
	.string "FACTORY HEAD and the ARENA TYCOON\l"
	.string "left on the ferry in a hurry.\p"
	.string "Something big is going on, and none of\n"
	.string "us are supposed to know.$"

BattleFrontier_OutsideEast_TriathleteM_Text_Gossip6:
	.string "...I finally saw SCOTT battle.\p"
	.string "His MEWTWO Mega Evolved without a KEY\n"
	.string "STONE, and STEVEN STONE's DIALGA\l"
	.string "went down to a single attack.\p"
	.string "I always wanted to see him battle. Now\n"
	.string "I wish I hadn't.$"

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
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_STEVEN, BattleFrontier_OutsideEast_Gentleman_Gossip0
	case GOSSIP_ANABEL, BattleFrontier_OutsideEast_Gentleman_Gossip1
	case GOSSIP_LAB, BattleFrontier_OutsideEast_Gentleman_Gossip2
	case GOSSIP_ARREST, BattleFrontier_OutsideEast_Gentleman_Gossip3
	case GOSSIP_PALACE, BattleFrontier_OutsideEast_Gentleman_GossipPalace
	case GOSSIP_STANDOFF, BattleFrontier_OutsideEast_Gentleman_Gossip5
	case GOSSIP_SIEGE, BattleFrontier_OutsideEast_Gentleman_Gossip6
	case GOSSIP_AFTERMATH, BattleFrontier_OutsideEast_Gentleman_Gossip7
	case GOSSIP_DEVON, BattleFrontier_OutsideEast_Gentleman_Gossip8
	case GOSSIP_DEVON_FREED, BattleFrontier_OutsideEast_Gentleman_Gossip9
	case GOSSIP_SIPHON, BattleFrontier_OutsideEast_Gentleman_Gossip10
	case GOSSIP_MAUVILLE, BattleFrontier_OutsideEast_Gentleman_Gossip11
	case GOSSIP_MAUVILLE_FREED, BattleFrontier_OutsideEast_Gentleman_Gossip12
	case GOSSIP_SKY_PILLAR, BattleFrontier_OutsideEast_Gentleman_Gossip13
	case GOSSIP_ENDING, BattleFrontier_OutsideEast_Gentleman_Gossip14
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
BattleFrontier_OutsideEast_Gentleman_Gossip0::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip0, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Gossip1::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip1, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Gossip2::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip2, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Gossip3::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip3, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Gossip4::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip4, MSGBOX_NPC
	end

@ GOSSIP_PALACE: the trench coat line, or the dream while Bad Dreams runs.
BattleFrontier_OutsideEast_Gentleman_GossipPalace::
	specialvar VAR_RESULT, IsBadDreamsActive
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideEast_Gentleman_Gossip4
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_BadDreams, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_BadDreams:
	.string "Odd. Half the island is asleep on\n"
	.string "its feet, and every one of them\l"
	.string "mumbles the same dream.\p"
	.string "A shadow, one blue eye, and rows of\n"
	.string "curtains. I haven't slept a wink\l"
	.string "since I heard it.$"

BattleFrontier_OutsideEast_Gentleman_Gossip5::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip5, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Gossip6::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip6, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip6:
	.string "This sunlight… It's the FACTORY.\n"
	.string "I can feel it in my old bones.\p"
	.string "The eighth gauntlet is cleared, and\n"
	.string "this is what follows.$"

BattleFrontier_OutsideEast_Gentleman_Gossip7::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip7, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip7:
	.string "SCOTT is gone, and the island is\n"
	.string "quiet. Too quiet.\p"
	.string "A strange POKéMON has taken up in\n"
	.string "the ARENA. It plays with rings.$"

BattleFrontier_OutsideEast_Gentleman_Gossip8::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip8, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Gossip9::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip9, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip8:
	.string "The ELITE FOUR, guarding DEVON…\n"
	.string "SCOTT's reach is longer than I feared.\p"
	.string "Be careful, young one.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip9:
	.string "DEVON free, and the ELITE FOUR\n"
	.string "humbled. I hear you carry something\l"
	.string "back from RUSTBORO.\p"
	.string "Guard it well, young one.$"

BattleFrontier_OutsideEast_Gentleman_Gossip10::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip10, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip10:
	.string "The chips lie silent. Every POKéMON\n"
	.string "on this island may grow again.\p"
	.string "But the energy has gone into the\n"
	.string "CROWN, I fear. Be wary of MAUVILLE,\l"
	.string "young one.$"

BattleFrontier_OutsideEast_Gentleman_Gossip11::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip11, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip11:
	.string "AQUA and MAGMA, side by side.\n"
	.string "Two old enemies, one “new order.”\p"
	.string "That is no friendship, young one.\n"
	.string "It is a pact waiting to break.$"

BattleFrontier_OutsideEast_Gentleman_Gossip12::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip12, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip12:
	.string "MAUVILLE is free, and SCOTT is bound\n"
	.string "for SKY PILLAR.\p"
	.string "The NURSE's CHANSEY can now lift a\n"
	.string "POKéMON to level 100. A fine gift,\l"
	.string "young one. Use it well.\p"
	.string "I hear the GYM LEADERS of RUSTBORO\n"
	.string "and MAUVILLE are battling again.\p"
	.string "They hold nothing back, but they do\n"
	.string "tell winners what troubles them.$"

BattleFrontier_OutsideEast_Gentleman_Gossip13::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip13, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip13:
	.string "STEVEN, WALLACE, NORMAN and WATTSON\n"
	.string "hold SKY PILLAR against all seven\l"
	.string "BRAINS.\p"
	.string "And the climb is yours alone. I would\n"
	.string "go with you, if my knees allowed.$"

BattleFrontier_OutsideEast_Gentleman_Gossip14::
	msgbox BattleFrontier_OutsideEast_Gentleman_Text_Gossip14, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Gentleman_Text_Gossip14:
	.string "SCOTT in handcuffs, and the CROWN in\n"
	.string "the hands of the police.\l"
	.string "HOENN breathes again.\p"
	.string "The shops stay free, and the island is\n"
	.string "at peace. Well done, young one.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip0:
	.string "I saw a man in a fine suit outside the\n"
	.string "old BATTLE FACTORY, studying its walls\l"
	.string "like a geologist.\p"
	.string "Unless I'm mistaken, that was STEVEN\n"
	.string "STONE. The former CHAMPION, here? How\l"
	.string "curious.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip1:
	.string "Someone finally beat ANABEL and took\n"
	.string "the whole TOWER, they say.\p"
	.string "And STEVEN STONE is back. I saw him up\n"
	.string "on the ledge above the PYRAMID,\l"
	.string "watching the plaza.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip2:
	.string "Only gauntlet 6 went down this time.\n"
	.string "Every shop is still running.\p"
	.string "A system that fails one door at a time\n"
	.string "isn't failing. Someone is choosing.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip3:
	.string "The ELITE FOUR have left the POKéMON\n"
	.string "LEAGUE, I hear. All four, at once.\p"
	.string "Gauntlets, BRAINS, and now the LEAGUE\n"
	.string "itself... The ground is shifting under\l"
	.string "all of HOENN.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip4:
	.string "A man in a trench coat has been hiding\n"
	.string "in the bushes near the FACTORY for\l"
	.string "days.\p"
	.string "He thinks nobody notices. Everybody\n"
	.string "notices.$"

BattleFrontier_OutsideEast_Gentleman_Text_Gossip5:
	.string "A MEGA EVOLUTION that never ends...\n"
	.string "They say SCOTT's MEWTWO is still Mega\l"
	.string "Evolved.\p"
	.string "Whatever is waiting after the eighth\n"
	.string "gauntlet, I don't think I want to see\l"
	.string "it anymore.$"

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
	.string "THE HALL OF EIGHT\p"
	.string "Eight gauntlets. Eight bosses. And\n"
	.string "the trainers who beat them.$"

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
	.string "eight gauntlets.\p"
	.string "And if my dream comes true...\p"
	.string "I... I'm going to ask MIMI next\n"
	.string "door if she will be friends with\l"
	.string "me!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "The BATTLE PYRAMID's sealed tight.\n"
	.string "They say it's the eighth gauntlet,\l"
	.string "the very last one.\p"
	.string "I'm going to be waiting right here\n"
	.string "the day it opens.$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "I thrive in darkness... Yes...\p"
	.string "The PYRAMID KING waits in the dark\n"
	.string "of the eighth gauntlet... Few have\l"
	.string "seen him.\p"
	.string "Yet everyone who reaches gauntlet\n"
	.string "7 dreams of him...$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "I didn't sleep for a week, but\n"
	.string "then I put together the ultimate\l"
	.string "team!\p"
	.string "...You can't skip ahead here,\n"
	.string "though. So I'm starting at\l"
	.string "gauntlet 1 like everyone else.$"

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
	.string "My daddy says a witch lives in a\n"
	.string "house way out west, past the\l"
	.string "BATTLE DOME!\p"
	.string "She can see the future! Isn't that\n"
	.string "spooky?$"

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
	.string "HALL OF EIGHT!\p"
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
	.string "Eight gauntlets, and the FRONTIER\n"
	.string "BRAINS waiting at the end of\l"
	.string "them...\p"
	.string "SCOTT never does anything without\n"
	.string "a reason. What's waiting after the\l"
	.string "eighth, I wonder?$"

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

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text6:
	.string "BATTLE PALACE - GAUNTLET 7: THE\n"
	.string "OPEN COURT.\p"
	.string "Home of the PALACE MAVEN, SPENSER.$"

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_Text0:
	.string "BATTLE PALACE - GAUNTLET 7: THE\n"
	.string "OPEN COURT.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 6.$"

BattleFrontier_OutsideEast_EventScript_BattleArenaSign_Text0:
	.string "BATTLE ARENA - THE SPARRING\n"
	.string "GROUND.\p"
	.string "Rematch the bosses you've already\n"
	.string "beaten.$"

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text7:
	.string "BATTLE PYRAMID - GAUNTLET 8: THE\n"
	.string "SUMMIT.\p"
	.string "Home of the PYRAMID KING, BRANDON.$"

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_Text0:
	.string "BATTLE PYRAMID - GAUNTLET 8: THE\n"
	.string "SUMMIT.\p"
	.string "Sealed. Opens for those who clear\n"
	.string "gauntlet 7.$"

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
	.string "...And one more thing. This\n"
	.string "FRONTIER is a crazy place. Spend\l"
	.string "some time talking to the locals.\p"
	.string "You'd be amazed what people around\n"
	.string "here know. I'll be watching!$"

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
	.string "...And one more thing. This\n"
	.string "FRONTIER is a crazy place. Spend\l"
	.string "some time talking to the locals.\p"
	.string "You'd be amazed what people around\n"
	.string "here know. I'll be watching!$"

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
	.string "And don't think you can just\n"
	.string "auto-heal after this one, kid. See\l"
	.string "this? It's a SCRAMBLER. Your\l"
	.string "POKéNAV's jammed. Mine too... but\l"
	.string "who's counting?$"

BattleFrontier_OutsideEast_Text_FlotsamDefeated:
	.string "No... NO! Not to a kid!$"



BattleFrontier_OutsideEast_Text_FlotsamSore:
	.string "FLOTSAM: I can't believe I lost to\n"
	.string "a kid...\p"
	.string "Heh. Doesn't matter anyway. SCOTT\n"
	.string "bans HMs on the FRONTIER. Without\l"
	.string "SURF, you'll never get down to\l"
	.string "that cave.\p"
	.string "...Unless that fancy L menu of\n"
	.string "yours can teach it some other\l"
	.string "way.\p"
	.string "...Forget I said that. I'm out of\n"
	.string "here!$"

BattleFrontier_OutsideEast_Text_FlotsamDroppedFP:
	.string "FLOTSAM dropped something in his\n"
	.string "hurry...$"

BattleFrontier_OutsideEast_Text_FoundFlotsamFP:
	.string "{PLAYER} found 300 FP!$"

BattleFrontier_OutsideEast_Text_FloristBefore:
	.string "I really want a LEAFEON to help\n"
	.string "with my flowers... but I'm not\l"
	.string "strong enough to earn one.\p"
	.string "You look strong. Maybe you could\n"
	.string "help me?\p"
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

BattleFrontier_OutsideEast_Text_LookerScrambler:
	.string "LOOKER: We also found this on him.\n"
	.string "A device that jams the auto-heal\l"
	.string "of every POKéNAV nearby. A\l"
	.string "SCRAMBLER, he called it.\p"
	.string "I have never seen anything like\n"
	.string "it. Someone who knows machines\l"
	.string "ought to take a look... someone\l"
	.string "like STEVEN STONE.\p"
	.string "...You have met STEVEN? Outside\n"
	.string "the old BATTLE FACTORY?\l"
	.string "Magnifique! Then you shall show it\l"
	.string "to him for me.$"

BattleFrontier_OutsideEast_Text_LookerScramblerAfter:
	.string "LOOKER: Keep it safe. And if\n"
	.string "STEVEN learns anything... you know\l"
	.string "where to find me.$"

BattleFrontier_OutsideEast_Text_LookerAgain:
	.string "LOOKER: FLOTSAM is in custody. But\n"
	.string "the one who beat him... I still\l"
	.string "wonder.\p"
	.string "...Carry on.$"

@ Ten Gauntlets: after the Lati is caught, the next time the player steps up
@ to the Battle Tower door, SCOTT walks in from off-screen: he's heard about a
@ ruckus in Artisan Cave and is sending his men in (storyline.md). That points
@ the player back to the cave, LOOKER and the SCRAMBLER - and the men in suits
@ only appear once this scene has played (ArtisanCave_B1F).
BattleFrontier_OutsideEast_EventScript_ArmScottCaveWarning::
	setflag FLAG_TEMP_7
	setvar VAR_TEMP_6, 1
	goto_if_unset FLAG_ARTISAN_LATI_CAUGHT, Common_EventScript_NopReturn
	goto_if_set FLAG_SCOTT_CAVE_WARNING, Common_EventScript_NopReturn
	setvar VAR_TEMP_6, 0
	return

BattleFrontier_OutsideEast_EventScript_ScottCaveWarning::
	setvar VAR_TEMP_6, 1
	@ Re-check, in case the trigger was armed by a save from an older build.
	goto_if_unset FLAG_ARTISAN_LATI_CAUGHT, BattleFrontier_OutsideEast_EventScript_ScottCaveWarningEnd
	goto_if_set FLAG_SCOTT_CAVE_WARNING, BattleFrontier_OutsideEast_EventScript_ScottCaveWarningEnd
	lockall
	clearflag FLAG_TEMP_7
	addobject LOCALID_FRONTIER_SCOTT
	applymovement LOCALID_FRONTIER_SCOTT, BattleFrontier_OutsideEast_Movement_ScottWalksUp
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_WEST
	msgbox BattleFrontier_OutsideEast_Text_ScottCaveWarning, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_SCOTT, BattleFrontier_OutsideEast_Movement_ScottWalksAway
	waitmovement 0
	removeobject LOCALID_FRONTIER_SCOTT
	setflag FLAG_SCOTT_CAVE_WARNING
	releaseall
	end

BattleFrontier_OutsideEast_EventScript_ScottCaveWarningEnd:
	end

@ From (8, 15), just off-screen, to (15, 15), beside the player at the door.
BattleFrontier_OutsideEast_Movement_ScottWalksUp:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

BattleFrontier_OutsideEast_Movement_ScottWalksAway:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

BattleFrontier_OutsideEast_Text_ScottCaveWarning:
	.string "SCOTT: Ah, {PLAYER}. Glad I caught\n"
	.string "you.\p"
	.string "Strange news today. I've had\n"
	.string "reports of a ruckus in ARTISAN\l"
	.string "CAVE. A battle... and something\l"
	.string "flying off into the dark.\p"
	.string "That cave is FRONTIER property.\n"
	.string "I'm sending some of my men in to\l"
	.string "investigate.\p"
	.string "...You wouldn't know anything\n"
	.string "about that, would you?\p"
	.string "No? Of course not. Good luck in\n"
	.string "there, {PLAYER}.$"

BattleFrontier_OutsideEast_Text_RivalPlaza0:
	.string "{RIVAL}: Oh, it's you. Don't mind\n"
	.string "me. I'm training.\p"
	.string "Gauntlet 1 is next on my list, and\n"
	.string "this time I'm going in prepared.$"

BattleFrontier_OutsideEast_Text_RivalPlaza1:
	.string "{RIVAL}: Guess who cleared\n"
	.string "gauntlet 1?\p"
	.string "WINONA's ALTARIA nearly had me,\n"
	.string "but I pulled through. ...Don't\l"
	.string "look so surprised!$"

BattleFrontier_OutsideEast_Text_RivalPlaza2:
	.string "{RIVAL}: Gauntlet 2 is a\n"
	.string "nightmare. Doubles, and JUAN's\l"
	.string "team just won't go down.\p"
	.string "That's three losses now. ...Don't\n"
	.string "say it. I'll figure it out.$"

BattleFrontier_OutsideEast_Text_RivalPlaza3:
	.string "{RIVAL}: I called home to check in\n"
	.string "with Dad yesterday. Something's\l"
	.string "off with him.\p"
	.string "He kept asking whether anyone had\n"
	.string "followed me here. And who I'd been\l"
	.string "talking to.\p"
	.string "Who would follow me? He's never\n"
	.string "been this paranoid.$"

BattleFrontier_OutsideEast_Text_RivalPlaza4:
	.string "{RIVAL}: Still stuck on gauntlet\n"
	.string "2. Every time I think I've cracked\l"
	.string "it, JUAN finds a new way to wash\l"
	.string "me out.\p"
	.string "And Dad's stopped picking up the\n"
	.string "phone at night. I keep telling\l"
	.string "myself it's nothing.$"

@ ============================================================================
@ Ten Gauntlets: STEVEN (storyline.md). After gauntlet 2 he waits outside the
@ Battle Factory (BattleFrontier_OutsideWest), Devon's sealed control room;
@ after gauntlet 4, on the ledge above the Pyramid at (65, 5) here in Outside
@ East. Both objects run BattleFrontier_Steven_EventScript_Steven, which
@ acts on VAR_LAST_TALKED. VAR_STEVEN_STORY_STATE: 0 none, 1 attendant's
@ hint, 2 met after gauntlet 2, 3 met after gauntlet 4.
@ ============================================================================

BattleFrontier_Steven_EventScript_Steven::
	lock
	faceplayer
	goto_if_eq VAR_BROKER_STORY_STATE, 5, BattleFrontier_Steven_EventScript_StevenLetter
	goto_if_eq VAR_STEVEN_STORY_STATE, 2, BattleFrontier_Steven_EventScript_StevenG4
	msgbox BattleFrontier_Steven_Text_StevenIntro, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_StevenAsksBadges, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_ShowedBadges, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_StevenCounterfeit, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_StevenTakesRainBadge, MSGBOX_DEFAULT
	playse SE_PIN
	message BattleFrontier_Steven_Text_GaveRainBadge
	waitmessage
	waitbuttonpress
	clearflag FLAG_BADGE08_GET
	closemessage
	turnobject VAR_LAST_TALKED, DIR_NORTH
	delay 30
	msgbox BattleFrontier_Steven_Text_StevenFactory, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_Steven_Text_StevenGift, MSGBOX_DEFAULT
	giveitem ITEM_EVIOLITE
	msgbox BattleFrontier_Steven_Text_StevenAsksHelp, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_AgreedToHelp, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_StevenFavor, MSGBOX_DEFAULT
	closemessage
	setvar VAR_STEVEN_STORY_STATE, 2
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_Steven_Text_StevenIntro:
	.string "STEVEN: Ah, there you are. That\n"
	.string "was quite a battle against JUAN.\p"
	.string "I'm STEVEN. A friend of mine,\n"
	.string "WALLACE, asked me to come here\l"
	.string "quietly.\p"
	.string "JUAN was his teacher. WALLACE\n"
	.string "wants to know why he walked away\l"
	.string "from the SOOTOPOLIS GYM to guard a\l"
	.string "mat on this island.\p"
	.string "JUAN wouldn't tell me much. Only\n"
	.string "that SCOTT made him an offer he\l"
	.string "couldn't refuse...\p"
	.string "And that I'd understand, if I\n"
	.string "asked him again after the eighth\l"
	.string "gauntlet.$"

BattleFrontier_Steven_Text_StevenAsksBadges:
	.string "STEVEN: I have a favor to ask. May\n"
	.string "I see your BADGE case?$"

BattleFrontier_Steven_Text_ShowedBadges:
	.string "{PLAYER} showed STEVEN the BADGE\n"
	.string "case.$"

BattleFrontier_Steven_Text_StevenCounterfeit:
	.string "STEVEN: ...\p"
	.string "These aren't GYM BADGES. The\n"
	.string "weight is wrong. The metal is\l"
	.string "wrong.\p"
	.string "I've handled nearly every stone in\n"
	.string "HOENN, and these didn't come from\l"
	.string "any of them.\p"
	.string "Your father called them fakes?\n"
	.string "Then he was right. They're\l"
	.string "counterfeit.\p"
	.string "But whoever made them knew exactly\n"
	.string "what they were doing. There's\l"
	.string "something set into the alloy...\l"
	.string "I've only ever seen it in one\l"
	.string "place. It looks like a shard of...\p"
	.string "...No. Not until I'm sure.$"

BattleFrontier_Steven_Text_StevenGift:
	.string "STEVEN: I've kept you long enough.\n"
	.string "Here... for the gauntlets ahead.\l"
	.string "It's a stone, of sorts. I think\l"
	.string "you'll find it useful.$"

BattleFrontier_Steven_Text_StevenFavor:
	.string "STEVEN: Keep beating these\n"
	.string "gauntlets, {PLAYER}. The closer you\l"
	.string "get to the top, the more SCOTT\l"
	.string "will have to show his hand.\p"
	.string "I'll be around.$"

@ Ten Gauntlets: STEVEN after gauntlet 4 (storyline.md). He confirms the
@ shards, swaps the counterfeit badges for real ones (FLAG_REAL_BADGES, which
@ lets Experience flow - see FrontierStoryAllowsExp()), looks at the
@ SCRAMBLER, and tests the one Pokemon without a chip: the Latias or Latios
@ from Artisan Cave, which must lead the party. It battles a wild ARON with
@ no Bag, switching or running (FLAG_FIGHT_ONLY_BATTLE) and gains Experience.
@ Then he takes it for safekeeping - a Pokemon growing past 50 on SCOTT's
@ island would give the game away - and gives a METAGROSS @ METAGROSSITE,
@ borrowed from the Broker to test (it doesn't grow either: it's chipped). The trade isn't a choice.
BattleFrontier_Steven_EventScript_StevenG4::
	goto_if_set FLAG_REAL_BADGES, BattleFrontier_Steven_EventScript_StevenG4Test
	msgbox BattleFrontier_Steven_Text_StevenG4Confirm, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message BattleFrontier_Steven_Text_GotRealBadges
	waitmessage
	waitfanfare
	waitbuttonpress
	setflag FLAG_BADGE08_GET
	setflag FLAG_REAL_BADGES
	checkitem ITEM_SCRAMBLER
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_Steven_EventScript_StevenSeesScrambler
	msgbox BattleFrontier_Steven_Text_StevenNoticesLati, MSGBOX_DEFAULT
BattleFrontier_Steven_EventScript_StevenG4Test::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_LATIAS, BattleFrontier_Steven_EventScript_StevenG4Battle
	goto_if_eq VAR_RESULT, SPECIES_LATIOS, BattleFrontier_Steven_EventScript_StevenG4Battle
	msgbox BattleFrontier_Steven_Text_StevenLatiInFront, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Steven_EventScript_StevenG4Battle::
	copyvar VAR_TEMP_1, VAR_RESULT
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox BattleFrontier_Steven_Text_StevenTestBattle, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	setflag FLAG_FIGHT_ONLY_BATTLE
	setwildbattle SPECIES_ARON, 10
	dowildbattle
	clearflag FLAG_FIGHT_ONLY_BATTLE
	msgbox BattleFrontier_Steven_Text_StevenTestResult, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_StevenTrade, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	call_if_eq VAR_RESULT, SPECIES_LATIOS, BattleFrontier_Steven_EventScript_StevenKeepsLatios
	special FrontierFloristTakeMon
	message BattleFrontier_Steven_Text_HandedOverLati
	waitmessage
	waitbuttonpress
	givemon SPECIES_METAGROSS, 50, ITEM_METAGROSSITE
	special FacilityTagLastPartyMonBroker
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_Steven_Text_ReceivedMetagross
	waitmessage
	waitfanfare
	waitbuttonpress
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox BattleFrontier_Steven_Text_StevenG4Goodbye, MSGBOX_DEFAULT
	closemessage
	setvar VAR_STEVEN_STORY_STATE, 3
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_Steven_EventScript_StevenKeepsLatios::
	setflag FLAG_STEVEN_HAS_LATIOS
	return

BattleFrontier_Steven_EventScript_StevenSeesScrambler::
	msgbox BattleFrontier_Steven_Text_StevenScrambler, MSGBOX_DEFAULT
	return

BattleFrontier_Steven_Text_StevenTakesRainBadge:
	.string "STEVEN: May I borrow one of these?\n"
	.string "I'd like to study it properly.\p"
	.string "This one. The RAIN BADGE... JUAN's\n"
	.string "own badge, from SOOTOPOLIS.\l"
	.string "Fitting.$"

BattleFrontier_Steven_Text_GaveRainBadge:
	.string "{PLAYER} handed the RAIN BADGE to\n"
	.string "STEVEN.$"

BattleFrontier_Steven_Text_StevenAsksHelp:
	.string "STEVEN: {PLAYER}... I could use\n"
	.string "someone on the inside. Someone\l"
	.string "SCOTT is watching, who can keep an\l"
	.string "eye on him in return.\p"
	.string "Will you work with me?$"

BattleFrontier_Steven_Text_AgreedToHelp:
	.string "{PLAYER} agreed to work with\n"
	.string "STEVEN.$"

BattleFrontier_Steven_Text_StevenG4Confirm:
	.string "STEVEN: {PLAYER}. I was right.\p"
	.string "There are KEY STONE shards in the\n"
	.string "alloy. And while I carried your\l"
	.string "RAIN BADGE, my own POKéMON stopped\l"
	.string "gaining Experience. Not one point.\p"
	.string "Those badges are feeding on your\n"
	.string "POKéMON's growth.\p"
	.string "So they're going. WALLACE pulled\n"
	.string "some strings with the GYMS.\l"
	.string "Here... the real ones.$"

BattleFrontier_Steven_Text_GotRealBadges:
	.string "{PLAYER}'s BADGES were replaced\n"
	.string "with real ones!$"

BattleFrontier_Steven_Text_StevenScrambler:
	.string "{PLAYER} showed STEVEN the\n"
	.string "SCRAMBLER from LOOKER.\p"
	.string "STEVEN: A SCRAMBLER... It jams the\n"
	.string "POKéNAV's auto-heal.\p"
	.string "That's DEVON technology. I'd know\n"
	.string "it anywhere. I'll look into how\l"
	.string "FLOTSAM got his hands on one.$"

BattleFrontier_Steven_Text_StevenNoticesLati:
	.string "STEVEN: Now... your LATIAS or\n"
	.string "LATIOS. It came from the wild, not\l"
	.string "from SCOTT.\p"
	.string "I want to test something.$"

BattleFrontier_Steven_Text_StevenLatiInFront:
	.string "STEVEN: Put your LATIAS or LATIOS\n"
	.string "at the front of your party, then\l"
	.string "come and see me.$"

BattleFrontier_Steven_Text_StevenTestBattle:
	.string "STEVEN: I caught this ARON on my\n"
	.string "way here. Battle it with your\l"
	.string "{STR_VAR_1}, and don't hold back.\p"
	.string "Let me patch your team up first.$"

BattleFrontier_Steven_Text_StevenTestResult:
	.string "STEVEN: Did you see? It gained\n"
	.string "Experience!\p"
	.string "So it was the badges. With them\n"
	.string "gone, your {STR_VAR_1} can grow. It\l"
	.string "was caught in the wild, so nothing\l"
	.string "else is holding it back.\p"
	.string "But I don't think the badges are\n"
	.string "the whole story. Something's wrong\l"
	.string "with the POKéMON from the FRONTIER\l"
	.string "shop too.\p"
	.string "I borrowed a METAGROSS from the\n"
	.string "BROKER to check. It didn't gain a\l"
	.string "single point, even while I wasn't\l"
	.string "carrying the badges.\p"
	.string "WALLACE and I will find out why.$"

BattleFrontier_Steven_Text_StevenTrade:
	.string "STEVEN: For now, that METAGROSS\n"
	.string "will be more use to you than it is\l"
	.string "to me.\p"
	.string "And your {STR_VAR_1} worries me. A\n"
	.string "POKéMON climbing past level 50 on\l"
	.string "SCOTT's island is exactly what\l"
	.string "would make him suspicious.\p"
	.string "It seems SCOTT has taken a special\n"
	.string "interest in you, {PLAYER}. In you,\l"
	.string "and in how far you get through his\l"
	.string "gauntlets.\p"
	.string "So for now, keep progressing. Keep\n"
	.string "beating the gauntlets as if\l"
	.string "nothing has changed, and we'll see\l"
	.string "what he does next.\p"
	.string "I'll hold on to your {STR_VAR_1}\n"
	.string "for the time being. Take\l"
	.string "METAGROSS, along with its MEGA\l"
	.string "STONE.$"

BattleFrontier_Steven_Text_HandedOverLati:
	.string "{PLAYER} handed the {STR_VAR_1} over\n"
	.string "to STEVEN.$"

BattleFrontier_Steven_Text_ReceivedMetagross:
	.string "{PLAYER} received a METAGROSS\n"
	.string "holding a METAGROSSITE!$"

BattleFrontier_Steven_Text_StevenG4Goodbye:
	.string "STEVEN: With that MEGA RING,\n"
	.string "METAGROSS can Mega Evolve. Use it\l"
	.string "well.\p"
	.string "Keep climbing, {PLAYER}. I'll look\n"
	.string "after your {STR_VAR_1} until the\l"
	.string "time is right.$"

BattleFrontier_OutsideEast_EventScript_SetupSteven::
	setflag FLAG_TEMP_8
	call_if_eq VAR_BROKER_STORY_STATE, 5, BattleFrontier_OutsideEast_EventScript_ShowLedgeSteven
	goto_if_ne VAR_STEVEN_STORY_STATE, 2, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_lt VAR_RESULT, 4, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_8
	return

BattleFrontier_Steven_Text_StevenFactory:
	.string "STEVEN: And this building... The\n"
	.string "BATTLE FACTORY, it used to be. Now\l"
	.string "it's “DEVON staff only.”\p"
	.string "What would DEVON want with a\n"
	.string "battle facility?\p"
	.string "And look at the stonework. That's\n"
	.string "MEGA STONE ore in these walls.\l"
	.string "Raw, unpolished... and a great\l"
	.string "deal of it.$"

@ ============================================================================
@ Ten Gauntlets: the Broker's letter, after gauntlet 6 (storyline.md;
@ VAR_BROKER_STORY_STATE is explained in BattleFrontier_OutsideWest).
@ SCOTT, NOLAND, GRETA and a guard wait outside the Pokemon Center (state 3),
@ then the same four surround the Broker in the courtyard outside his house
@ (state 4), with SCOTT on the left. STEVEN waits on the ledge above the
@ Pyramid for the LETTER (state 5), and WALLACE meets the player on the way
@ back (state 6). LOOKER leaves his spot for the Factory from state 6
@ (BattleFrontier_OutsideWest).
@ ============================================================================

BattleFrontier_OutsideEast_EventScript_SetupBrokerStory::
	setflag FLAG_HIDE_BROKER_STORY_SCOTT
	setflag FLAG_HIDE_BROKER_STORY_NOLAND
	setflag FLAG_HIDE_BROKER_STORY_GRETA
	setflag FLAG_HIDE_BROKER_STORY_GUARD
	setflag FLAG_HIDE_BROKER_STORY_BROKER
	setflag FLAG_HIDE_BROKER_STORY_WALLACE
	setflag FLAG_HIDE_EVER_GRANDE_STORY_FRONTIER_ABRA
	call_if_ge VAR_BROKER_STORY_STATE, 6, BattleFrontier_OutsideEast_EventScript_HideLooker
	call_if_ge VAR_BROKER_STORY_STATE, 7, BattleFrontier_OutsideEast_EventScript_ShowWallaceAbra
	call_if_eq VAR_BROKER_STORY_STATE, 3, BattleFrontier_OutsideEast_EventScript_ShowCenterSquad
	call_if_eq VAR_BROKER_STORY_STATE, 4, BattleFrontier_OutsideEast_EventScript_ShowArrest
	return

BattleFrontier_OutsideEast_EventScript_ShowCenterSquad::
	clearflag FLAG_HIDE_BROKER_STORY_SCOTT
	clearflag FLAG_HIDE_BROKER_STORY_NOLAND
	clearflag FLAG_HIDE_BROKER_STORY_GRETA
	clearflag FLAG_HIDE_BROKER_STORY_GUARD
	return

BattleFrontier_OutsideEast_EventScript_ShowArrest::
	call BattleFrontier_OutsideEast_EventScript_MoveSquadToCourtyard
	clearflag FLAG_HIDE_BROKER_STORY_SCOTT
	clearflag FLAG_HIDE_BROKER_STORY_NOLAND
	clearflag FLAG_HIDE_BROKER_STORY_GRETA
	clearflag FLAG_HIDE_BROKER_STORY_GUARD
	clearflag FLAG_HIDE_BROKER_STORY_BROKER
	return

@ Round the Broker at (64, 34): SCOTT left, NOLAND above, GRETA right, the
@ guard below.
BattleFrontier_OutsideEast_EventScript_MoveSquadToCourtyard::
	setobjectxyperm LOCALID_FRONTIER_BROKER_SCOTT, 63, 34
	setobjectmovementtype LOCALID_FRONTIER_BROKER_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_FRONTIER_BROKER_NOLAND, 64, 33
	setobjectmovementtype LOCALID_FRONTIER_BROKER_NOLAND, MOVEMENT_TYPE_FACE_DOWN
	setobjectxyperm LOCALID_FRONTIER_BROKER_GRETA, 65, 34
	setobjectmovementtype LOCALID_FRONTIER_BROKER_GRETA, MOVEMENT_TYPE_FACE_LEFT
	setobjectxyperm LOCALID_FRONTIER_BROKER_GUARD, 64, 35
	setobjectmovementtype LOCALID_FRONTIER_BROKER_GUARD, MOVEMENT_TYPE_FACE_UP
	return

BattleFrontier_OutsideEast_EventScript_ShowLedgeSteven::
	clearflag FLAG_TEMP_8
	return

@ The player steps out of the Pokemon Center to (3, 52). Off to the right,
@ SCOTT gives the order, and all four walk off east. The courtyard scene is
@ on this same map, so the squad is moved there now; it appears once the
@ player gets close.
BattleFrontier_OutsideEast_EventScript_CenterScott::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_CenterScott, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_BROKER_NOLAND, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_FRONTIER_BROKER_GRETA, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_FRONTIER_BROKER_GUARD, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_FRONTIER_BROKER_SCOTT, BattleFrontier_OutsideEast_Movement_SquadLeaves
	applymovement LOCALID_FRONTIER_BROKER_NOLAND, BattleFrontier_OutsideEast_Movement_SquadLeaves
	applymovement LOCALID_FRONTIER_BROKER_GRETA, BattleFrontier_OutsideEast_Movement_SquadLeaves
	applymovement LOCALID_FRONTIER_BROKER_GUARD, BattleFrontier_OutsideEast_Movement_SquadLeaves
	waitmovement 0
	removeobject LOCALID_FRONTIER_BROKER_SCOTT
	removeobject LOCALID_FRONTIER_BROKER_NOLAND
	removeobject LOCALID_FRONTIER_BROKER_GRETA
	removeobject LOCALID_FRONTIER_BROKER_GUARD
	setvar VAR_BROKER_STORY_STATE, 4
	call BattleFrontier_OutsideEast_EventScript_ShowArrest
	releaseall
	end

BattleFrontier_OutsideEast_Movement_SquadLeaves:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

@ Triggered one tile left of the flower at the courtyard's mouth (61, 34),
@ or the tile below it. The guards lead the Broker out along row 35, right
@ past the player, then north up the plaza, out of sight. The walk pauses
@ with the Broker just below the player, at (61, 35).
BattleFrontier_OutsideEast_EventScript_BrokerArrest::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8005, 35, BattleFrontier_OutsideEast_EventScript_ArrestStepUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_ArrestScott1, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestBroker1, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestScott2, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestBroker2, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestScott3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_BROKER_SCOTT, BattleFrontier_OutsideEast_Movement_ScottStepsAside
	waitmovement 0
	applymovement LOCALID_FRONTIER_BROKER_GUARD, BattleFrontier_OutsideEast_Movement_GuardOut1
	applymovement LOCALID_FRONTIER_BROKER, BattleFrontier_OutsideEast_Movement_BrokerOut1
	applymovement LOCALID_FRONTIER_BROKER_NOLAND, BattleFrontier_OutsideEast_Movement_NolandOut1
	applymovement LOCALID_FRONTIER_BROKER_GRETA, BattleFrontier_OutsideEast_Movement_GretaOut1
	waitmovement 0
	applymovement LOCALID_FRONTIER_BROKER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_BrokerDropped, MSGBOX_DEFAULT
	additem ITEM_LETTER
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_OutsideEast_Text_ReceivedLetter
	waitmessage
	waitfanfare
	waitbuttonpress
	closemessage
	applymovement LOCALID_FRONTIER_BROKER_GUARD, BattleFrontier_OutsideEast_Movement_GuardOut2
	applymovement LOCALID_FRONTIER_BROKER, BattleFrontier_OutsideEast_Movement_BrokerOut2
	applymovement LOCALID_FRONTIER_BROKER_NOLAND, BattleFrontier_OutsideEast_Movement_NolandOut2
	applymovement LOCALID_FRONTIER_BROKER_GRETA, BattleFrontier_OutsideEast_Movement_GretaOut2
	waitmovement 0
	removeobject LOCALID_FRONTIER_BROKER_GUARD
	removeobject LOCALID_FRONTIER_BROKER
	removeobject LOCALID_FRONTIER_BROKER_NOLAND
	removeobject LOCALID_FRONTIER_BROKER_GRETA
	applymovement LOCALID_FRONTIER_BROKER_SCOTT, BattleFrontier_OutsideEast_Movement_ScottToPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_ArrestScottExplains, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestPlayerAsks, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestScottKanto, MSGBOX_DEFAULT
	closemessage
	@ He knows someone bought that MASTER BALL, and what happened in
	@ Artisan Cave. He lets it go: he needs the player to keep winning.
	delay 60
	msgbox BattleFrontier_OutsideEast_Text_ArrestScottLook, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_ArrestScottCongrats, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_BROKER_SCOTT, BattleFrontier_OutsideEast_Movement_ScottLeaves
	waitmovement 0
	removeobject LOCALID_FRONTIER_BROKER_SCOTT
	setvar VAR_BROKER_STORY_STATE, 5
	call BattleFrontier_OutsideEast_EventScript_ShowLedgeSteven
	releaseall
	end

BattleFrontier_OutsideEast_EventScript_ArrestStepUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	return

BattleFrontier_OutsideEast_Movement_ScottStepsAside:
	walk_up
	face_down
	step_end

@ Four steps each: the guard to (60, 35), the Broker to (61, 35), NOLAND to
@ (62, 35), GRETA (a step behind) to (63, 35).
BattleFrontier_OutsideEast_Movement_GuardOut1:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

BattleFrontier_OutsideEast_Movement_BrokerOut1:
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

BattleFrontier_OutsideEast_Movement_NolandOut1:
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

BattleFrontier_OutsideEast_Movement_GretaOut1:
	delay_16
	walk_left
	walk_down
	walk_left
	step_end

@ Then each to (60, 35) and up the plaza to (60, 26), out of sight.
BattleFrontier_OutsideEast_Movement_GuardOut2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideEast_Movement_BrokerOut2:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideEast_Movement_NolandOut2:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideEast_Movement_GretaOut2:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ From (63, 33) to (62, 34), beside the player.
BattleFrontier_OutsideEast_Movement_ScottToPlayer:
	walk_down
	walk_left
	face_left
	step_end

BattleFrontier_OutsideEast_Movement_ScottLeaves:
	walk_down
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ STEVEN on the ledge (state 5). He flies off on the bird WALLACE uses in
@ LITTLEROOT.
BattleFrontier_Steven_EventScript_StevenLetter::
	msgbox BattleFrontier_Steven_Text_LetterPlayerTells, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_LetterShocked, MSGBOX_DEFAULT
	removeitem ITEM_LETTER
	msgbox BattleFrontier_Steven_Text_LetterHandedOver, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_LetterReads, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_LetterBonding, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_LetterPlayerThinks, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_LetterHypothesis, MSGBOX_DEFAULT
	msgbox BattleFrontier_Steven_Text_LetterLooker, MSGBOX_DEFAULT
	playfanfare MUS_REGISTER_MATCH_CALL
	message BattleFrontier_Steven_Text_LetterGotNumber
	waitmessage
	waitfanfare
	waitbuttonpress
	setflag FLAG_STEVEN_POKENAV_NUMBER
	msgbox BattleFrontier_Steven_Text_LetterGoodbye, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setvar VAR_BROKER_STORY_STATE, 6
	release
	end

@ The ledge is one tile wide here, so leaving STEVEN's spot always crosses
@ (60, 5). WALLACE comes along it from the west.
BattleFrontier_OutsideEast_EventScript_LedgeWallace::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	clearflag FLAG_HIDE_BROKER_STORY_WALLACE
	addobject LOCALID_FRONTIER_LEDGE_WALLACE
	applymovement LOCALID_FRONTIER_LEDGE_WALLACE, BattleFrontier_OutsideEast_Movement_WallaceAlongLedge
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_LedgeWallace, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_LedgePlayerTells, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_LedgeWallaceBye, MSGBOX_DEFAULT
	closemessage
	@ The LEAGUE office calls him: the ELITE FOUR are gone, and MAXIE and
	@ ARCHIE turned up right after.
	playse SE_POKENAV_CALL
	waitse
	delay 10
	playse SE_POKENAV_CALL
	waitse
	msgbox BattleFrontier_OutsideEast_Text_LedgeWallaceRings, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_LedgeWallaceOnCall, MSGBOX_DEFAULT
	closemessage
	playse SE_POKENAV_HANG_UP
	waitse
	msgbox BattleFrontier_OutsideEast_Text_LedgeWallaceAsksHelp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_LEDGE_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_FRONTIER_LEDGE_WALLACE
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setvar VAR_BROKER_STORY_STATE, 7
	releaseall
	end

BattleFrontier_OutsideEast_Movement_WallaceAlongLedge:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

BattleFrontier_OutsideEast_Text_CenterScott:
	.string "SCOTT: We finally traced the\n"
	.string "missing MASTER BALL.\p"
	.string "Move out.$"

BattleFrontier_OutsideEast_Text_ArrestScott1:
	.string "SCOTT: This little shindig of yours\n"
	.string "has gone on long enough.\p"
	.string "You're being detained by FRONTIER\n"
	.string "security. Illegally selling\l"
	.string "FRONTIER property. Holding a\l"
	.string "MASTER BALL.\p"
	.string "And before they take you away,\n"
	.string "you'll be coughing up that MASTER\l"
	.string "BALL.$"

BattleFrontier_OutsideEast_Text_ArrestBroker1:
	.string "BROKER: Don't have it anymore.\n"
	.string "Somebody bought it off me.$"

BattleFrontier_OutsideEast_Text_ArrestScott2:
	.string "SCOTT: Did you really think I\n"
	.string "wouldn't notice one of my MASTER\l"
	.string "BALLS missing from that shipment?$"

BattleFrontier_OutsideEast_Text_ArrestBroker2:
	.string "BROKER: Business is business.$"

BattleFrontier_OutsideEast_Text_ArrestScott3:
	.string "SCOTT: Take him away.$"

BattleFrontier_OutsideEast_Text_BrokerDropped:
	.string "The BROKER dropped something at\n"
	.string "{PLAYER}'s feet.$"

BattleFrontier_OutsideEast_Text_ReceivedLetter:
	.string "{PLAYER} received a LETTER to\n"
	.string "STEVEN!$"

BattleFrontier_OutsideEast_Text_ArrestScottExplains:
	.string "SCOTT: Sorry you had to see that,\n"
	.string "{PLAYER}.\p"
	.string "That man's been working this island\n"
	.string "as “the BROKER.” Selling FRONTIER\l"
	.string "stock under the table and taking a\l"
	.string "cut.\p"
	.string "Turns out he had old connections\n"
	.string "to TEAM AQUA, too.$"

BattleFrontier_OutsideEast_Text_ArrestPlayerAsks:
	.string "{PLAYER} asked SCOTT about the\n"
	.string "MASTER BALLS.$"

BattleFrontier_OutsideEast_Text_ArrestScottKanto:
	.string "SCOTT: Oh, those! I had a supply\n"
	.string "brought in from KANTO. Prizes for\l"
	.string "the FRONTIER shop, someday.\l"
	.string "Heheh...$"

BattleFrontier_OutsideEast_Text_ArrestScottLook:
	.string "SCOTT: ......\p"
	.string "...Anyway!$"

BattleFrontier_OutsideEast_Text_ArrestScottCongrats:
	.string "SCOTT: Congratulations on gauntlet\n"
	.string "6! From here on, the gauntlets get\l"
	.string "very serious.\p"
	.string "I'll be out of town for a little\n"
	.string "while. I'm meeting some very\l"
	.string "high-profile trainers, to get\l"
	.string "their feedback on my next FRONTIER\l"
	.string "addition.\p"
	.string "Good luck, {PLAYER}!$"

BattleFrontier_Steven_Text_LetterPlayerTells:
	.string "{PLAYER} told STEVEN about the\n"
	.string "BROKER.$"

BattleFrontier_Steven_Text_LetterShocked:
	.string "STEVEN: SCOTT arrested him? The\n"
	.string "BROKER?\p"
	.string "...He's an old friend. He was\n"
	.string "looking into something for me.\p"
	.string "He dropped a letter? For me?$"

BattleFrontier_Steven_Text_LetterHandedOver:
	.string "{PLAYER} handed STEVEN the LETTER.$"

BattleFrontier_Steven_Text_LetterReads:
	.string "STEVEN: “STEVEN. If you're reading\n"
	.string "this, they finally got me.\p"
	.string "You asked why your METAGROSS\n"
	.string "wouldn't grow. I went digging.\p"
	.string "Every POKéMON that comes through\n"
	.string "the FRONTIER has a chip implanted\l"
	.string "in it. Every one. That's why they\l"
	.string "never gain any Experience.\p"
	.string "And they always seemed so sad, no\n"
	.string "matter how many trainers they\l"
	.string "battled for.\p"
	.string "Thought you should know.\n"
	.string "- The BROKER”$"

BattleFrontier_Steven_Text_LetterBonding:
	.string "STEVEN: Chips...\p"
	.string "{PLAYER}. Your POKéMON. Do they\n"
	.string "seem to bond with you?$"

BattleFrontier_Steven_Text_LetterPlayerThinks:
	.string "{PLAYER} thought about it. Their\n"
	.string "POKéMON fight hard... but they only\l"
	.string "ever seem focused on battling.$"

BattleFrontier_Steven_Text_LetterHypothesis:
	.string "STEVEN: I was afraid of that.\p"
	.string "When a trainer and a POKéMON work\n"
	.string "together, it creates bond energy.\l"
	.string "It's the power behind growth, and\l"
	.string "behind evolution.\p"
	.string "If those chips are made of the same\n"
	.string "shards as the badges, they're a\l"
	.string "second channel. Quieter.\p"
	.string "They're stealing the bond between\n"
	.string "the FRONTIER's POKéMON and their\l"
	.string "trainers.\p"
	.string "And if it's being stolen... it's\n"
	.string "going somewhere.$"

BattleFrontier_Steven_Text_LetterLooker:
	.string "STEVEN: I'll have LOOKER find out\n"
	.string "where they've taken the BROKER.\p"
	.string "And here. My POKéNAV number. If I\n"
	.string "find anything, you'll hear from\l"
	.string "me.$"

BattleFrontier_Steven_Text_LetterGotNumber:
	.string "{PLAYER} got STEVEN's POKéNAV\n"
	.string "number!$"

BattleFrontier_Steven_Text_LetterGoodbye:
	.string "STEVEN: I'm going to find out if\n"
	.string "those chips can be disabled.\p"
	.string "I'll be in touch, {PLAYER}.$"

BattleFrontier_OutsideEast_Text_LedgeWallace:
	.string "WALLACE: {PLAYER}! Well met.\p"
	.string "I slipped past SCOTT's security\n"
	.string "again. Have you seen STEVEN?$"

BattleFrontier_OutsideEast_Text_LedgePlayerTells:
	.string "{PLAYER} told WALLACE that STEVEN\n"
	.string "had just flown off.$"

BattleFrontier_OutsideEast_Text_LedgeWallaceBye:
	.string "WALLACE: Ha! Always on the move,\n"
	.string "that one.$"

BattleFrontier_OutsideEast_Text_LedgeWallaceRings:
	.string "...Beep beep beep!\n"
	.string "WALLACE's POKéNAV is ringing!$"

BattleFrontier_OutsideEast_Text_LedgeWallaceOnCall:
	.string "WALLACE: WALLACE here.\p"
	.string "...The ELITE FOUR? All four of\n"
	.string "them?\p"
	.string "...\p"
	.string "...MAXIE and ARCHIE? At the\n"
	.string "LEAGUE?\p"
	.string "I see. I'm on my way.$"

BattleFrontier_OutsideEast_Text_LedgeWallaceAsksHelp:
	.string "WALLACE: That was the POKéMON\n"
	.string "LEAGUE office.\p"
	.string "The ELITE FOUR have left their\n"
	.string "posts. Nobody knows where they've\l"
	.string "gone.\p"
	.string "And shortly after they left, MAXIE\n"
	.string "and ARCHIE showed up at the\l"
	.string "LEAGUE, stirring up trouble.\p"
	.string "I'm going to need your help with\n"
	.string "this, {PLAYER}.\p"
	.string "We'll be quick, so SCOTT doesn't\n"
	.string "notice you're gone.\p"
	.string "My ABRA will be waiting by the\n"
	.string "POKéMON CENTER. It knows TELEPORT,\l"
	.string "and the way to EVER GRANDE CITY.\p"
	.string "I'll fly ahead. Meet me outside the\n"
	.string "POKéMON LEAGUE.$"

@ ============================================================================
@ Ten Gauntlets: a facility that isn't open yet keeps its door shut - walking
@ into it does nothing (IsFacilityLobbyDoorLocked, src/facility.c, checked in
@ TryDoorWarp). Inspecting the door says why. Once it opens, these do nothing.
@ ============================================================================

BattleFrontier_OutsideEast_EventScript_PalaceDoor::
	special IsBattlePalaceUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideEast_EventScript_PalaceDoorOpen
	msgbox BattleFrontier_OutsideEast_Text_PalaceDoorLocked, MSGBOX_SIGN
BattleFrontier_OutsideEast_EventScript_PalaceDoorOpen:
	end

BattleFrontier_OutsideEast_EventScript_PyramidDoor::
	special IsBattlePyramidUnlocked
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_OutsideEast_EventScript_PyramidDoorOpen
	msgbox BattleFrontier_OutsideEast_Text_PyramidDoorLocked, MSGBOX_SIGN
BattleFrontier_OutsideEast_EventScript_PyramidDoorOpen:
	end

BattleFrontier_OutsideEast_Text_PalaceDoorLocked:
	.string "The doors are shut. The BATTLE\n"
	.string "PALACE isn't open yet.$"

BattleFrontier_OutsideEast_Text_PyramidDoorLocked:
	.string "The doors are shut. The BATTLE\n"
	.string "PYRAMID isn't open yet.$"

@ ============================================================================
@ Ten Gauntlets: the Crown is taken, after gauntlet 7 (storyline.md;
@ VAR_CROWN_STORY_STATE is explained in LittlerootTown). Clearing gauntlet 7
@ starts it the next time the player is out here (always the Palace's
@ doorstep, in practice): the rival runs up with the news from LITTLEROOT,
@ then STEVEN calls. Only on exactly seven cleared, so a save already past
@ gauntlet 8 never sees it. The rival is the plaza's own rival object, moved
@ off-screen to the west of the Palace to run in along row 58.
@ ============================================================================

BattleFrontier_OutsideEast_EventScript_SetupCrownStory::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ne VAR_RESULT, 7, Common_EventScript_NopReturn
	call_if_eq VAR_CROWN_STORY_STATE, 0, BattleFrontier_OutsideEast_EventScript_CrownStoryStart
	goto_if_ne VAR_CROWN_STORY_STATE, 1, Common_EventScript_NopReturn
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 45, Common_EventScript_NopReturn
	goto_if_ne VAR_0x8005, 56, Common_EventScript_NopReturn
	setobjectxyperm LOCALID_FRONTIER_RIVAL_MAY, 36, 58
	setobjectxyperm LOCALID_FRONTIER_RIVAL_BRENDAN, 36, 58
	setvar VAR_TEMP_7, 1
	return

BattleFrontier_OutsideEast_EventScript_CrownStoryStart::
	setvar VAR_CROWN_STORY_STATE, 1
	return

@ The player has stepped down off the Palace door to (45, 57). The rival runs
@ in below them, to (45, 58), and back out the same way.
BattleFrontier_OutsideEast_EventScript_CrownRival::
	lockall
	setvar VAR_TEMP_7, 0
	setvar VAR_0x8004, LOCALID_FRONTIER_RIVAL_MAY
	checkplayergender
	call_if_eq VAR_RESULT, MALE, BattleFrontier_OutsideEast_EventScript_CrownShowMay
	call_if_eq VAR_RESULT, FEMALE, BattleFrontier_OutsideEast_EventScript_CrownShowBrendan
	addobject VAR_0x8004
	applymovement VAR_0x8004, BattleFrontier_OutsideEast_Movement_CrownRivalIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_CrownRival, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8004, BattleFrontier_OutsideEast_Movement_CrownRivalOut
	waitmovement 0
	removeobject VAR_0x8004
	delay 40
	@ STEVEN calls. The player's POKéNAV has no Match Call, so the call is
	@ played out here.
	playse SE_POKENAV_CALL
	waitse
	delay 10
	playse SE_POKENAV_CALL
	waitse
	msgbox BattleFrontier_OutsideEast_Text_CrownPokenavRings, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_CrownStevenCall, MSGBOX_DEFAULT
	closemessage
	playse SE_POKENAV_HANG_UP
	waitse
	msgbox BattleFrontier_OutsideEast_Text_CrownClick, MSGBOX_DEFAULT
	setvar VAR_CROWN_STORY_STATE, 2
	releaseall
	end

BattleFrontier_OutsideEast_EventScript_CrownShowMay::
	clearflag FLAG_TEMP_3
	return

BattleFrontier_OutsideEast_EventScript_CrownShowBrendan::
	setvar VAR_0x8004, LOCALID_FRONTIER_RIVAL_BRENDAN
	clearflag FLAG_TEMP_4
	return

BattleFrontier_OutsideEast_Movement_CrownRivalIn:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_up
	step_end

BattleFrontier_OutsideEast_Movement_CrownRivalOut:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

BattleFrontier_OutsideEast_Text_CrownRival:
	.string "{RIVAL}: {PLAYER}! Thank goodness!\p"
	.string "NOLAND and GRETA stormed into the\n"
	.string "lab with a bunch of men in suits!\p"
	.string "They took everything. The machines,\n"
	.string "the books, Dad's research... all\l"
	.string "of it.\p"
	.string "I tried to fight them off, but\n"
	.string "they destroyed me. I had to run.\p"
	.string "Dad's still in there, {PLAYER}.\n"
	.string "He's in serious trouble!\p"
	.string "Get STEVEN and WALLACE. Get\n"
	.string "anyone! We need help, now!\p"
	.string "I'm heading back. Hurry!$"

BattleFrontier_OutsideEast_Text_CrownPokenavRings:
	.string "...Beep beep beep!\n"
	.string "{PLAYER}'s POKéNAV is ringing!$"

BattleFrontier_OutsideEast_Text_CrownStevenCall:
	.string "STEVEN: {PLAYER}, it's STEVEN.\n"
	.string "I just heard about LITTLEROOT.\p"
	.string "I'm sorry. I'm tied up right now\n"
	.string "with LOOKER, working out how to\l"
	.string "get the BROKER out of the FACTORY.\l"
	.string "I can't get there until later.\p"
	.string "And WALLACE is in EVER GRANDE CITY,\n"
	.string "trying to find out what happened\l"
	.string "to the ELITE FOUR.\p"
	.string "This one is up to you, {PLAYER}.\p"
	.string "But you've beaten seven gauntlets.\n"
	.string "You're ready for whatever is\l"
	.string "waiting there.\p"
	.string "Go. I'll get there as soon as I\n"
	.string "can.$"

BattleFrontier_OutsideEast_Text_CrownClick:
	.string "Click!$"

@ ============================================================================
@ Ten Gauntlets: the Ever Grande trip, the end of the Broker's letter
@ (storyline.md; VAR_BROKER_STORY_STATE is explained in
@ BattleFrontier_OutsideWest). From state 7 until the player is back (11),
@ WALLACE's ABRA waits by the Pokemon Center to TELEPORT them to EVER GRANDE
@ CITY; the ABRA there brings them back to (4, 53), beside it.
@ ============================================================================

BattleFrontier_OutsideEast_EventScript_ShowWallaceAbra::
	goto_if_ge VAR_BROKER_STORY_STATE, 11, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_EVER_GRANDE_STORY_FRONTIER_ABRA
	return

BattleFrontier_OutsideEast_EventScript_WallaceAbra::
	lock
	faceplayer
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_WallaceAbra, MSGBOX_YESNO
	waitmoncry
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_WallaceAbraNo
	msgbox BattleFrontier_OutsideEast_Text_AbraUsedTeleport, MSGBOX_DEFAULT
	closemessage
	playse SE_M_TELEPORT
	warpteleport MAP_EVER_GRANDE_CITY, 18, 8
	waitstate
	release
	end

BattleFrontier_OutsideEast_EventScript_WallaceAbraNo::
	release
	end

BattleFrontier_OutsideEast_Text_WallaceAbra:
	.string "It's WALLACE's ABRA.\p"
	.string "It can TELEPORT you to EVER GRANDE\n"
	.string "CITY. Go now?$"

BattleFrontier_OutsideEast_Text_AbraUsedTeleport:
	.string "ABRA used TELEPORT!$"

@ ============================================================================
@ Ten Gauntlets: the endgame after gauntlet 8 (storyline.md). VAR_ENDGAME_STATE:
@   0 not started
@   1 gauntlet 8 cleared: WALLACE waits by the Pyramid
@   2 WALLACE has swapped the badges for real ones and run to the Factory door
@     (BattleFrontier_OutsideWest)
@   3 PALKIA has blasted the door open; WALLACE waits in the lobby
@     (BattleFrontier_DevonFactory_1F)
@   4 inside: SPENSER and BRANDON took WALLACE on; the five guards and the
@     cells (the stairs to the PILLAR open once all are done)
@   5 SCOTT has the CROWN and is gone; the scene outside the Arena is next
@   6 the Arena is the base: the BROKER's free shop, HOOPA, STEVEN waiting
@   7 STEVEN has sent the player to RUSTBORO (storyline.md, Rustboro)
@   8-10 Rustboro (RustboroCity's scripts): the ambush, the CROWN, JUAN
@  11 the siphon is done: the CROWN is charged, the chips are off; STEVEN
@     waits outside the Arena (endgame part 3)
@  12 STEVEN has sent the player to MAUVILLE (FLAG_ABRA_TO_MAUVILLE)
@  13 WATTSON has led the player into NEW MAUVILLE (MauvilleCity's scripts)
@  14 MAXIE and ARCHIE beaten: the CROWN is supercharged (six Megas)
@  15 the teams have left MAUVILLE; HOOPA's third ring; the CHANSEY outside
@     the Arena; STEVEN waits outside the Arena
@  16 STEVEN has sent the player to SKY PILLAR (FLAG_ABRA_TO_SKY_PILLAR)
@  17 the BRAINS' ambush: the player climbs alone (SkyPillar_Outside)
@  18 SCOTT beaten and arrested: the ending (SkyPillar_Top)
@ The Factory's radiance shows as harsh sunlight on the outdoor maps in states
@ 1-4. Outdoor maps only: drought turns into sun in any battle fought on the
@ map, and no battle is ever fought out here.
@ ============================================================================

BattleFrontier_OutsideEast_EventScript_SetupEndgame::
	setflag FLAG_HIDE_ENDGAME_PYRAMID_WALLACE
	setflag FLAG_HIDE_ENDGAME_BASE_ALLIES
	setflag FLAG_HIDE_ENDGAME_BASE_PARENTS
	setflag FLAG_HIDE_ENDGAME_BASE_DAD
	setflag FLAG_HIDE_ENDGAME_BASE_JOY
	clearflag FLAG_HIDE_FRONTIER_BRAINS_AWAY
	call_if_eq VAR_ENDGAME_STATE, 0, BattleFrontier_OutsideEast_EventScript_TryStartEndgame
	goto_if_eq VAR_ENDGAME_STATE, 0, Common_EventScript_NopReturn
	setflag FLAG_HIDE_FRONTIER_BRAINS_AWAY
	call_if_lt VAR_ENDGAME_STATE, 5, BattleFrontier_OutsideEast_EventScript_EndgameSunlight
	call_if_eq VAR_ENDGAME_STATE, 1, BattleFrontier_OutsideEast_EventScript_SetupPyramidWallace
	goto_if_lt VAR_ENDGAME_STATE, 5, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_ENDGAME_BASE_PARENTS
	clearflag FLAG_HIDE_ENDGAME_BASE_DAD
	call_if_eq VAR_ENDGAME_STATE, 5, BattleFrontier_OutsideEast_EventScript_SetupBaseScene
	call_if_eq VAR_ENDGAME_STATE, 6, BattleFrontier_OutsideEast_EventScript_ShowBaseAllies
	@ Endgame part 3: STEVEN and WALLACE wait here in states 10, 11, 15 and 18 (they
	@ are in the towns in 7-9, 12-14 and 16-17); DAD goes with them to SKY PILLAR
	@ (16-17); NURSE JOY and her CHANSEY arrive in state 15.
	call_if_eq VAR_ENDGAME_STATE, 10, BattleFrontier_OutsideEast_EventScript_ShowBaseAllies
	call_if_eq VAR_ENDGAME_STATE, 11, BattleFrontier_OutsideEast_EventScript_ShowBaseAllies
	call_if_eq VAR_ENDGAME_STATE, 15, BattleFrontier_OutsideEast_EventScript_ShowBaseAllies
	call_if_eq VAR_ENDGAME_STATE, 18, BattleFrontier_OutsideEast_EventScript_ShowBaseAllies
	call_if_eq VAR_ENDGAME_STATE, 16, BattleFrontier_OutsideEast_EventScript_HideBaseDad
	call_if_eq VAR_ENDGAME_STATE, 17, BattleFrontier_OutsideEast_EventScript_HideBaseDad
	call_if_ge VAR_ENDGAME_STATE, 15, BattleFrontier_OutsideEast_EventScript_ShowBaseJoy
	return

BattleFrontier_OutsideEast_EventScript_HideBaseDad::
	setflag FLAG_HIDE_ENDGAME_BASE_DAD
	return

BattleFrontier_OutsideEast_EventScript_ShowBaseJoy::
	clearflag FLAG_HIDE_ENDGAME_BASE_JOY
	return

BattleFrontier_OutsideEast_EventScript_TryStartEndgame::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_lt VAR_RESULT, 8, Common_EventScript_NopReturn
	setvar VAR_ENDGAME_STATE, 1
	return

BattleFrontier_OutsideEast_EventScript_EndgameSunlight::
	setweather WEATHER_DROUGHT
	return

@ WALLACE waits below the Pyramid at (58, 18). Coming out of the door, the
@ player steps down to (58, 15) and he walks up to meet them; anyone who
@ arrives some other way can just talk to him.
BattleFrontier_OutsideEast_EventScript_SetupPyramidWallace::
	clearflag FLAG_HIDE_ENDGAME_PYRAMID_WALLACE
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 58, Common_EventScript_NopReturn
	goto_if_ne VAR_0x8005, 14, Common_EventScript_NopReturn
	setvar VAR_TEMP_2, 1
	return

BattleFrontier_OutsideEast_EventScript_PyramidWallaceScene::
	lockall
	setvar VAR_TEMP_2, 0
	applymovement LOCALID_FRONTIER_ENDGAME_PYRAMID_WALLACE, BattleFrontier_OutsideEast_Movement_WallaceToPyramid
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	goto BattleFrontier_OutsideEast_EventScript_PyramidWallaceTalk

BattleFrontier_OutsideEast_EventScript_PyramidWallace::
	lockall
	applymovement LOCALID_FRONTIER_ENDGAME_PYRAMID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
BattleFrontier_OutsideEast_EventScript_PyramidWallaceTalk::
	msgbox BattleFrontier_OutsideEast_Text_PyramidWallace1, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	message BattleFrontier_OutsideEast_Text_PyramidBadgesSwapped
	waitmessage
	waitse
	waitbuttonpress
	setflag FLAG_REAL_BADGES
	msgbox BattleFrontier_OutsideEast_Text_PyramidWallace2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_ENDGAME_PYRAMID_WALLACE, BattleFrontier_OutsideEast_Movement_WallaceRunsOff
	waitmovement 0
	removeobject LOCALID_FRONTIER_ENDGAME_PYRAMID_WALLACE
	setvar VAR_ENDGAME_STATE, 2
	releaseall
	end

BattleFrontier_OutsideEast_Movement_WallaceToPyramid:
	walk_up
	walk_up
	step_end

BattleFrontier_OutsideEast_Movement_WallaceRunsOff:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ State 5: the player arrives at (39, 31) from the Pillar Chamber, below the
@ Arena door, with STEVEN and WALLACE to the right and MOM and DAD to the
@ left. JOY healed the team before the warp.
BattleFrontier_OutsideEast_EventScript_SetupBaseScene::
	call BattleFrontier_OutsideEast_EventScript_ShowBaseAllies
	setvar VAR_TEMP_3, 1
	return

BattleFrontier_OutsideEast_EventScript_ShowBaseAllies::
	clearflag FLAG_HIDE_ENDGAME_BASE_ALLIES
	return

BattleFrontier_OutsideEast_EventScript_BaseScene::
	lockall
	setvar VAR_TEMP_3, 0
	msgbox BattleFrontier_OutsideEast_Text_BaseSteven1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_BaseMom, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_BaseDad, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideEast_Text_BaseSteven2, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_BaseWallace, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FRONTIER_SHOP_FREE
	setvar VAR_ENDGAME_STATE, 6
	releaseall
	end

@ STEVEN asks if the player is ready for DEVON. Yes sends them to RUSTBORO by
@ the ABRA in the POKEMON CENTER (state 7); STEVEN and WALLACE fly ahead.
@ Endgame part 3: he is back from state 10 (see the state table below).
BattleFrontier_OutsideEast_EventScript_BaseSteven::
	lock
	faceplayer
	goto_if_eq VAR_ENDGAME_STATE, 10, BattleFrontier_OutsideEast_EventScript_BaseStevenSiphon
	goto_if_eq VAR_ENDGAME_STATE, 11, BattleFrontier_OutsideEast_EventScript_BaseStevenMauville
	goto_if_eq VAR_ENDGAME_STATE, 15, BattleFrontier_OutsideEast_EventScript_BaseStevenSkyPillar
	goto_if_eq VAR_ENDGAME_STATE, 18, BattleFrontier_OutsideEast_EventScript_BaseStevenEnd
	goto_if_ge VAR_ENDGAME_STATE, 7, BattleFrontier_OutsideEast_EventScript_BaseStevenGone
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_BaseStevenNotYet
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenGo, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ABRA_TO_RUSTBORO
	setvar VAR_ENDGAME_STATE, 7
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_STEVEN
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_WALLACE
	setflag FLAG_HIDE_ENDGAME_BASE_ALLIES
	waitse
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_OutsideEast_EventScript_BaseStevenNotYet::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenNotYet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_BaseStevenGone::
	release
	end

@ State 10: back from RUSTBORO, the CROWN uncharged.
BattleFrontier_OutsideEast_EventScript_BaseStevenSiphon::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenSiphon, MSGBOX_DEFAULT
	release
	end

@ State 11: the siphon is done. STEVEN and WALLACE remember NEW MAUVILLE, then
@ STEVEN asks if the player is ready (VAR_TEMP_4: already explained this visit).
BattleFrontier_OutsideEast_EventScript_BaseStevenMauville::
	goto_if_eq VAR_TEMP_4, 1, BattleFrontier_OutsideEast_EventScript_BaseStevenMauvilleAsk
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenPower, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_BaseWallaceLevels, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenMauvilleIdea, MSGBOX_DEFAULT
	setvar VAR_TEMP_4, 1
BattleFrontier_OutsideEast_EventScript_BaseStevenMauvilleAsk::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenReadyMauville, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_BaseStevenMauvilleNotYet
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenGoMauville, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ABRA_TO_MAUVILLE
	setvar VAR_ENDGAME_STATE, 12
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_STEVEN
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_WALLACE
	setflag FLAG_HIDE_ENDGAME_BASE_ALLIES
	waitse
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_OutsideEast_EventScript_BaseStevenMauvilleNotYet::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenMauvilleNotYet, MSGBOX_DEFAULT
	release
	end

@ State 15: back from MAUVILLE. NURSE JOY's CHANSEY is outside (below); STEVEN
@ asks if the player is ready for SKY PILLAR. DAD goes with them.
BattleFrontier_OutsideEast_EventScript_BaseStevenSkyPillar::
	goto_if_eq VAR_TEMP_4, 1, BattleFrontier_OutsideEast_EventScript_BaseStevenSkyPillarAsk
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenChansey, MSGBOX_DEFAULT
	setvar VAR_TEMP_4, 1
BattleFrontier_OutsideEast_EventScript_BaseStevenSkyPillarAsk::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenReadySkyPillar, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_BaseStevenSkyPillarNotYet
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenGoSkyPillar, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ABRA_TO_SKY_PILLAR
	setvar VAR_ENDGAME_STATE, 16
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_STEVEN
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_WALLACE
	removeobject LOCALID_FRONTIER_ENDGAME_BASE_DAD
	setflag FLAG_HIDE_ENDGAME_BASE_ALLIES
	setflag FLAG_HIDE_ENDGAME_BASE_DAD
	waitse
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_OutsideEast_EventScript_BaseStevenSkyPillarNotYet::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenSkyPillarNotYet, MSGBOX_DEFAULT
	release
	end

@ State 18: it's over.
BattleFrontier_OutsideEast_EventScript_BaseStevenEnd::
	msgbox BattleFrontier_OutsideEast_Text_BaseStevenEnd, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_BaseWallace::
	goto_if_eq VAR_ENDGAME_STATE, 10, BattleFrontier_OutsideEast_EventScript_BaseWallaceSiphon
	goto_if_eq VAR_ENDGAME_STATE, 11, BattleFrontier_OutsideEast_EventScript_BaseWallaceLevels
	goto_if_eq VAR_ENDGAME_STATE, 15, BattleFrontier_OutsideEast_EventScript_BaseWallaceChansey
	goto_if_eq VAR_ENDGAME_STATE, 18, BattleFrontier_OutsideEast_EventScript_BaseWallaceEnd
	msgbox BattleFrontier_OutsideEast_Text_BaseWallaceTalk, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseWallaceSiphon::
	msgbox BattleFrontier_OutsideEast_Text_BaseWallaceSiphon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseWallaceLevels::
	msgbox BattleFrontier_OutsideEast_Text_BaseWallaceLevels, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseWallaceChansey::
	msgbox BattleFrontier_OutsideEast_Text_BaseWallaceChansey, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseWallaceEnd::
	msgbox BattleFrontier_OutsideEast_Text_BaseWallaceEnd, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseMom::
	goto_if_eq VAR_ENDGAME_STATE, 18, BattleFrontier_OutsideEast_EventScript_BaseMomEnd
	goto_if_ge VAR_ENDGAME_STATE, 16, BattleFrontier_OutsideEast_EventScript_BaseMomSkyPillar
	msgbox BattleFrontier_OutsideEast_Text_BaseMomTalk, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseMomSkyPillar::
	msgbox BattleFrontier_OutsideEast_Text_BaseMomSkyPillar, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseMomEnd::
	msgbox BattleFrontier_OutsideEast_Text_BaseMomEnd, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseDad::
	goto_if_eq VAR_ENDGAME_STATE, 18, BattleFrontier_OutsideEast_EventScript_BaseDadEnd
	msgbox BattleFrontier_OutsideEast_Text_BaseDadTalk, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BaseDadEnd::
	msgbox BattleFrontier_OutsideEast_Text_BaseDadEnd, MSGBOX_NPC
	end

@ ----------------------------------------------------------------------------
@ Endgame part 3: NURSE JOY and her CHANSEY (state 15 on). JOY explains Transfer
@ EXP; the player picks one Pokemon and it goes to level 100, once only
@ (FLAG_CHANSEY_TRANSFER_EXP_USED).
@ ----------------------------------------------------------------------------
BattleFrontier_OutsideEast_EventScript_JoyChansey::
	lock
	faceplayer
	goto_if_set FLAG_CHANSEY_TRANSFER_EXP_USED, BattleFrontier_OutsideEast_EventScript_JoyChanseyUsed
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyExplain, MSGBOX_DEFAULT
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideEast_EventScript_JoyChanseyNotNow
BattleFrontier_OutsideEast_EventScript_JoyChanseyPick::
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, BattleFrontier_OutsideEast_EventScript_JoyChanseyNotNow
	special TransferExpToLevel100
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideEast_EventScript_JoyChanseyEgg
	goto_if_eq VAR_RESULT, 2, BattleFrontier_OutsideEast_EventScript_JoyChanseyAlready100
	setflag FLAG_CHANSEY_TRANSFER_EXP_USED
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	playfanfare MUS_LEVEL_UP
	message BattleFrontier_OutsideEast_Text_JoyChanseyGrew
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyDone, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_JoyChanseyEgg::
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyEgg, MSGBOX_DEFAULT
	goto BattleFrontier_OutsideEast_EventScript_JoyChanseyPick
	end

BattleFrontier_OutsideEast_EventScript_JoyChanseyAlready100::
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyAlready100, MSGBOX_DEFAULT
	goto BattleFrontier_OutsideEast_EventScript_JoyChanseyPick
	end

BattleFrontier_OutsideEast_EventScript_JoyChanseyNotNow::
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyNotNow, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_JoyChanseyUsed::
	msgbox BattleFrontier_OutsideEast_Text_JoyChanseyUsed, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Chansey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ChanseyCry, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_Text_PyramidWallace1:
	.string "WALLACE: {PLAYER}! There you are.\p"
	.string "Feel that heat? That isn't the sun.\n"
	.string "It's pouring off the FACTORY.\p"
	.string "SCOTT is pulling in every scrap of\n"
	.string "energy this island has.\p"
	.string "I found the ELITE FOUR, too. They're\n"
	.string "guarding DEVON CORPORATION, in\l"
	.string "RUSTBORO. That will have to wait.\p"
	.string "STEVEN… Losing to that MEWTWO took\n"
	.string "a chip out of his confidence.\p"
	.string "He's regrouping. He'll meet us at\n"
	.string "DEVON later.\p"
	.string "One more thing. Those are SCOTT's\n"
	.string "counterfeit BADGES again, aren't\l"
	.string "they? Hand them over.$"

BattleFrontier_OutsideEast_Text_PyramidBadgesSwapped:
	.string "WALLACE took the counterfeit BADGES\n"
	.string "and gave {PLAYER} real ones.$"

BattleFrontier_OutsideEast_Text_PyramidWallace2:
	.string "WALLACE: There. Your wins won't feed\n"
	.string "SCOTT's machine anymore.\p"
	.string "Now come on. We need to get into\n"
	.string "the FACTORY. Now!$"

BattleFrontier_OutsideEast_Text_BaseSteven1:
	.string "STEVEN: Easy. Catch your breath.\n"
	.string "NURSE JOY has seen to your team.\p"
	.string "SCOTT is gone, and the BRAINS left\n"
	.string "the island with him.\p"
	.string "We'll use the BATTLE ARENA as our\n"
	.string "base for the time being.$"

BattleFrontier_OutsideEast_Text_BaseMom:
	.string "MOM: {PLAYER}! You're all right!\p"
	.string "When they told us what you did down\n"
	.string "there… Oh, come here.$"

BattleFrontier_OutsideEast_Text_BaseDad:
	.string "DAD: You stood between WALLACE and\n"
	.string "that MEWTWO.\p"
	.string "SCOTT always said he'd squash me.\n"
	.string "He never once thought about you.\p"
	.string "That was his mistake.$"

BattleFrontier_OutsideEast_Text_BaseSteven2:
	.string "STEVEN: The BROKER is in the\n"
	.string "EXCHANGE SERVICE CORNER, with the\l"
	.string "four shopkeepers. Go and see him.\p"
	.string "And there's a POKéMON in the ARENA\n"
	.string "that wants to meet you.\p"
	.string "When you're ready to move on DEVON,\n"
	.string "come and find me. I'll be here.$"

BattleFrontier_OutsideEast_Text_BaseWallace:
	.string "WALLACE: …Thank you, {PLAYER}.\n"
	.string "I won't forget it.$"

BattleFrontier_OutsideEast_Text_BaseStevenReady:
	.string "STEVEN: The ELITE FOUR are guarding\n"
	.string "DEVON, for some reason. We need to\l"
	.string "find out why.\p"
	.string "Are you ready to go to RUSTBORO?$"

BattleFrontier_OutsideEast_Text_BaseStevenGo:
	.string "STEVEN: Then WALLACE and I will meet\n"
	.string "you there.\p"
	.string "The ABRA at the POKéMON CENTER can\n"
	.string "TELEPORT you to RUSTBORO.\p"
	.string "See you at DEVON.$"

BattleFrontier_OutsideEast_Text_BaseStevenNotYet:
	.string "STEVEN: Take your time. The shop is\n"
	.string "free now, so use it.$"

BattleFrontier_OutsideEast_Text_BaseWallaceTalk:
	.string "WALLACE: PALKIA will be fine. My\n"
	.string "pride may take a little longer.$"

BattleFrontier_OutsideEast_Text_BaseMomTalk:
	.string "MOM: We'll stay right here. Go and\n"
	.string "do what you have to do.$"

BattleFrontier_OutsideEast_Text_BaseDadTalk:
	.string "DAD: Whatever SCOTT is planning,\n"
	.string "you've stood up to him once\l"
	.string "already. Remember that.$"

@ ----------------------------------------------------------------------------
@ Endgame part 3: the base after the siphon (states 10, 11, 15, 18).
@ ----------------------------------------------------------------------------

BattleFrontier_OutsideEast_Text_BaseStevenSiphon:
	.string "STEVEN: Back from RUSTBORO. Good.\p"
	.string "The scientist said the CROWN will\n"
	.string "charge from the chips in the\l"
	.string "FRONTIER's POKéMON.\p"
	.string "The POKéMON keeper in the EXCHANGE\n"
	.string "SERVICE CORNER can do it. Ask him\l"
	.string "to free the POKéMON.$"

BattleFrontier_OutsideEast_Text_BaseWallaceSiphon:
	.string "WALLACE: The CROWN is in your hands\n"
	.string "now. Put it to work.$"

BattleFrontier_OutsideEast_Text_BaseStevenPower:
	.string "STEVEN: It worked. Every POKéMON\n"
	.string "here is free of its chip.\p"
	.string "But the CROWN can only make one\n"
	.string "POKéMON a permanent MEGA for now.\p"
	.string "To stand toe to toe with SCOTT,\n"
	.string "we'll need a power source as big\l"
	.string "as the FACTORY's.$"

BattleFrontier_OutsideEast_Text_BaseWallaceLevels:
	.string "WALLACE: And your POKéMON won't\n"
	.string "reach level 100 before SCOTT is\l"
	.string "long gone.\p"
	.string "We need something bigger.$"

BattleFrontier_OutsideEast_Text_BaseStevenMauvilleIdea:
	.string "STEVEN: Something bigger…\p"
	.string "WALLACE, are you thinking what I'm\n"
	.string "thinking? NEW MAUVILLE.\p"
	.string "The generator under MAUVILLE.\n"
	.string "Nothing else in HOENN comes close.\p"
	.string "NURSE JOY says she might be able to\n"
	.string "help too, but she needs time.$"

BattleFrontier_OutsideEast_Text_BaseStevenReadyMauville:
	.string "STEVEN: We'll go ahead to MAUVILLE.\p"
	.string "Are you ready to follow us?$"

BattleFrontier_OutsideEast_Text_BaseStevenGoMauville:
	.string "STEVEN: Then WALLACE and I will see\n"
	.string "you there.\p"
	.string "The ABRA at the POKéMON CENTER can\n"
	.string "TELEPORT you to MAUVILLE.$"

BattleFrontier_OutsideEast_Text_BaseStevenMauvilleNotYet:
	.string "STEVEN: Take your time. HOOPA's\n"
	.string "rings are open, if you want to\l"
	.string "catch something first.$"

BattleFrontier_OutsideEast_Text_BaseStevenChansey:
	.string "STEVEN: You're back. WATTSON's\n"
	.string "generator did it.\p"
	.string "NURSE JOY has found a way to use it,\n"
	.string "too. She's waiting with a CHANSEY\l"
	.string "just below. Go and see her.\p"
	.string "After that, SCOTT is at SKY PILLAR.\n"
	.string "NORMAN, WATTSON, WALLACE and I mean\l"
	.string "to take him down together.$"

BattleFrontier_OutsideEast_Text_BaseWallaceChansey:
	.string "WALLACE: That CHANSEY has more\n"
	.string "power than it looks.$"

BattleFrontier_OutsideEast_Text_BaseStevenReadySkyPillar:
	.string "STEVEN: Are you ready for SKY\n"
	.string "PILLAR?$"

BattleFrontier_OutsideEast_Text_BaseStevenGoSkyPillar:
	.string "STEVEN: Then we'll go ahead.\p"
	.string "WALLACE, NORMAN, WATTSON and I will\n"
	.string "be waiting for you at the tower.\p"
	.string "The ABRA at the POKéMON CENTER can\n"
	.string "TELEPORT you to SKY PILLAR.$"

BattleFrontier_OutsideEast_Text_BaseStevenSkyPillarNotYet:
	.string "STEVEN: Take your time. We'll wait\n"
	.string "for you at SKY PILLAR.$"

BattleFrontier_OutsideEast_Text_BaseStevenEnd:
	.string "STEVEN: It's over, {PLAYER}.\p"
	.string "SCOTT is in custody, and the CROWN\n"
	.string "is locked away for good.\p"
	.string "HOENN owes you more than it knows.$"

BattleFrontier_OutsideEast_Text_BaseWallaceEnd:
	.string "WALLACE: It's over. And you did it,\n"
	.string "{PLAYER}.\p"
	.string "The FRONTIER is yours again.$"

BattleFrontier_OutsideEast_Text_BaseMomSkyPillar:
	.string "MOM: NORMAN went with STEVEN and\n"
	.string "the others. I told him to be\l"
	.string "careful. He didn't listen.\p"
	.string "You be careful too.$"

BattleFrontier_OutsideEast_Text_BaseMomEnd:
	.string "MOM: It's over. Oh, {PLAYER}, we're\n"
	.string "going home.$"

BattleFrontier_OutsideEast_Text_BaseDadEnd:
	.string "DAD: It's over. SCOTT never\n"
	.string "squashed anyone after all.\p"
	.string "I'm proud of you, {PLAYER}.$"

BattleFrontier_OutsideEast_Text_JoyChanseyExplain:
	.string "NURSE JOY: I've been working on it.\p"
	.string "The supercharged CROWN can draw in\n"
	.string "the EXPERIENCE of every CHANSEY in\l"
	.string "HOENN's POKéMON CENTERS.\p"
	.string "I taught this one a new move:\n"
	.string "TRANSFER EXP.\p"
	.string "One POKéMON will rise to level\n"
	.string "100. Only one, and only once.$"

BattleFrontier_OutsideEast_Text_JoyChanseyAsk:
	.string "NURSE JOY: Shall we do it now?$"

BattleFrontier_OutsideEast_Text_JoyChanseyWhich:
	.string "NURSE JOY: Which POKéMON?$"

BattleFrontier_OutsideEast_Text_JoyChanseyEgg:
	.string "NURSE JOY: That's an EGG. It has\n"
	.string "nothing to take it in with.\p"
	.string "Choose another POKéMON.$"

BattleFrontier_OutsideEast_Text_JoyChanseyAlready100:
	.string "NURSE JOY: That one is already\n"
	.string "level 100. Choose another.$"

BattleFrontier_OutsideEast_Text_JoyChanseyNotNow:
	.string "NURSE JOY: Take your time. I'll be\n"
	.string "right here.$"

BattleFrontier_OutsideEast_Text_JoyChanseyGrew:
	.string "CHANSEY used TRANSFER EXP!\p"
	.string "{STR_VAR_1} grew to LV. 100!$"

BattleFrontier_OutsideEast_Text_JoyChanseyDone:
	.string "NURSE JOY: There. CHANSEY and I\n"
	.string "gave everything we had.\p"
	.string "Go and put it to good use.$"

BattleFrontier_OutsideEast_Text_JoyChanseyUsed:
	.string "NURSE JOY: CHANSEY is spent. That\n"
	.string "was all the EXPERIENCE it could\l"
	.string "give.\p"
	.string "Go and finish this, {PLAYER}.$"

BattleFrontier_OutsideEast_Text_ChanseyCry:
	.string "CHANSEY: Chan! Chansey!$"
