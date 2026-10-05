LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveMomToMaysDoor
	call_if_unset FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_SetTwinPos
	call_if_eq VAR_LITTLEROOT_TOWN_STATE, 3, LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_MAY, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_OLDALE_RIVAL_STATE, 1, LittlerootTown_EventScript_MoveRivalFromOldale
	call_if_eq VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_EventScript_SetRivalLeftForRoute103
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_HideMapNamePopup
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_EventScript_LeftLabAfterDexUpgrade
	call LittlerootTown_EventScript_SetupBirchStory
	call LittlerootTown_EventScript_SetupCrownStory
	end

LittlerootTown_EventScript_LeftLabAfterDexUpgrade::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

LittlerootTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

LittlerootTown_EventScript_MoveRivalFromOldale::
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	return

LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
	return

LittlerootTown_EventScript_MoveMomToMaysDoor::
	setobjectxyperm LOCALID_LITTLEROOT_MOM, 14, 8
	return

LittlerootTown_EventScript_SetTwinPos::
	goto_if_eq VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_SetTwinGuardingRoutePos
	setobjectxyperm LOCALID_LITTLEROOT_TWIN, 10, 1
	setobjectmovementtype LOCALID_LITTLEROOT_TWIN, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_SetTwinGuardingRoutePos::
	setobjectxyperm LOCALID_LITTLEROOT_TWIN, 7, 2
	setobjectmovementtype LOCALID_LITTLEROOT_TWIN, MOVEMENT_TYPE_FACE_DOWN
	return

LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setobjectmovementtype LOCALID_LITTLEROOT_MOM, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetMomInFrontOfDoorMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetMomInFrontOfDoorFemale
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorMale::
	setobjectxyperm LOCALID_LITTLEROOT_MOM, 5, 9
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorFemale::
	setobjectxyperm LOCALID_LITTLEROOT_MOM, 14, 9
	return

LittlerootTown_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
	map_script_2 VAR_TEMP_3, 1, LittlerootTown_EventScript_CrownScott
	.2byte 0

LittlerootTown_EventScript_StepOffTruckMale::
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_StepOffTruckFemale::
	lockall
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_LITTLEROOT_MOM
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachDoor
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomEnterHouse
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideplayer
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_Movement_MomExitHouse:
	walk_down
	step_end

LittlerootTown_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

LittlerootTown_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

LittlerootTown_EventScript_BeginDexUpgradeScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_LITTLEROOT_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox LittlerootTown_Text_BirchSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	releaseall
	end

LittlerootTown_OnWarp:
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade
	.2byte 0

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade::
	addobject LOCALID_LITTLEROOT_BIRCH
	addobject LOCALID_LITTLEROOT_RIVAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale
	goto LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale::
	setobjectxy LOCALID_LITTLEROOT_RIVAL, 6, 10
	setobjectxy LOCALID_LITTLEROOT_BIRCH, 5, 10
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale::
	setobjectxy LOCALID_LITTLEROOT_RIVAL, 13, 10
	setobjectxy LOCALID_LITTLEROOT_BIRCH, 14, 10
	end

LittlerootTown_EventScript_FatMan::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_AFTER_LAB, LittlerootTown_FatMan_Gossip0
	case GOSSIP_SQUAD, LittlerootTown_FatMan_Gossip0
	case GOSSIP_ARREST, LittlerootTown_FatMan_Gossip0
	case GOSSIP_PALACE, LittlerootTown_FatMan_Gossip0
	case GOSSIP_TAKEN, LittlerootTown_FatMan_Gossip1
	case GOSSIP_STANDOFF, LittlerootTown_FatMan_Gossip1
	case GOSSIP_ALL_CLEAR, LittlerootTown_FatMan_Gossip1
	lock
	faceplayer
	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_DEFAULT
	release
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
LittlerootTown_FatMan_Gossip0::
	msgbox LittlerootTown_FatMan_Text_Gossip0, MSGBOX_NPC
	end

LittlerootTown_FatMan_Gossip1::
	msgbox LittlerootTown_FatMan_Text_Gossip1, MSGBOX_NPC
	end

LittlerootTown_FatMan_Text_Gossip0:
	.string "DEVON says PROF. BIRCH owed them\n"
	.string "money. I don't buy it.\p"
	.string "The man wears the same lab coat every\n"
	.string "day. He's not the type to borrow big.$"

LittlerootTown_FatMan_Text_Gossip1:
	.string "They took the PROFESSOR's machines,\n"
	.string "his books, everything.\p"
	.string "The power of science is staggering. So\n"
	.string "is the power of greed.$"

LittlerootTown_EventScript_Boy::
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_AFTER_LAB, LittlerootTown_Boy_Gossip0
	case GOSSIP_SQUAD, LittlerootTown_Boy_Gossip0
	case GOSSIP_ARREST, LittlerootTown_Boy_Gossip0
	case GOSSIP_PALACE, LittlerootTown_Boy_Gossip0
	case GOSSIP_TAKEN, LittlerootTown_Boy_Gossip1
	case GOSSIP_STANDOFF, LittlerootTown_Boy_Gossip1
	case GOSSIP_ALL_CLEAR, LittlerootTown_Boy_Gossip1
	lock
	faceplayer
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab, MSGBOX_DEFAULT
	release
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
LittlerootTown_Boy_Gossip0::
	msgbox LittlerootTown_Boy_Text_Gossip0, MSGBOX_NPC
	end

LittlerootTown_Boy_Gossip1::
	msgbox LittlerootTown_Boy_Text_Gossip1, MSGBOX_NPC
	end

LittlerootTown_Boy_Text_Gossip0:
	.string "I saw it! The CHAMPION, WALLACE,\n"
	.string "battling DEVON's men right outside\l"
	.string "the LAB!\p"
	.string "{RIVAL} came home after that. They\n"
	.string "help out at the LAB every day now.$"

LittlerootTown_Boy_Text_Gossip1:
	.string "{RIVAL} says the LAB got emptied out.\n"
	.string "Every machine, every book.\p"
	.string "And nobody's seen your mom and dad\n"
	.string "since. Are they okay?$"

LittlerootTown_EventScript_Twin::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	switch VAR_RESULT
	case GOSSIP_AFTER_LAB, LittlerootTown_Twin_Gossip0
	case GOSSIP_SQUAD, LittlerootTown_Twin_Gossip0
	case GOSSIP_ARREST, LittlerootTown_Twin_Gossip0
	case GOSSIP_PALACE, LittlerootTown_Twin_Gossip0
	case GOSSIP_TAKEN, LittlerootTown_Twin_Gossip1
	case GOSSIP_STANDOFF, LittlerootTown_Twin_Gossip1
	case GOSSIP_ALL_CLEAR, LittlerootTown_Twin_Gossip1
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_YouSavedBirch
	goto_if_ne VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_GoSaveBirch
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

@ Story gossip: the line for the current beat (GetStoryGossipStage).
LittlerootTown_Twin_Gossip0::
	msgbox LittlerootTown_Twin_Text_Gossip0, MSGBOX_DEFAULT
	release
	end

LittlerootTown_Twin_Gossip1::
	msgbox LittlerootTown_Twin_Text_Gossip1, MSGBOX_DEFAULT
	release
	end

LittlerootTown_Twin_Text_Gossip0:
	.string "Mommy let me play outside again! The\n"
	.string "scary men in suits are gone.\p"
	.string "The CHAMPION chased them away! He's\n"
	.string "my favorite now.$"

LittlerootTown_Twin_Text_Gossip1:
	.string "Mommy says I have to stay close to\n"
	.string "home again.\p"
	.string "Your house is so quiet now. Where did\n"
	.string "everyone go?$"

LittlerootTown_EventScript_GoSaveBirch::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	release
	end

LittlerootTown_EventScript_YouSavedBirch::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_YouSavedBirch, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoodLuck::
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_DangerousWithoutPokemon::
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinPushPlayerFromRoute
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_Movement_TwinApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

LittlerootTown_Movement_TwinPushPlayerFromRoute:
	walk_down
	step_end

LittlerootTown_Movement_TwinReturnLeft:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_faster_down
	step_end

LittlerootTown_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LittlerootTown_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_Movement_TwinApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

LittlerootTown_Movement_TwinReturnRight:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_EventScript_GoSaveBirchTrigger::
	lockall
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	releaseall
	end

LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BirchsLabSign::
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BrendansHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_BirchsHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_BirchsHouseSignFemale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_BirchsHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_BirchsHouseSignMale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_GiveRunningShoesTrigger0::
	lockall
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_LITTLEROOT_MOM, 10, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger1::
	lockall
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_LITTLEROOT_MOM, 11, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger3::
	lockall
	setvar VAR_0x8008, 3
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger4::
	lockall
	setvar VAR_0x8008, 4
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger5::
	lockall
	setvar VAR_0x8008, 5
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomNoticePlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomNoticePlayerFemale
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	msgbox LittlerootTown_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomApproachPlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomApproachPlayerFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomReturnHomeMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomReturnHomeFemale
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SetHomeDoorCoordsFemale::
	setvar VAR_0x8009, 14
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_MomNoticePlayerMale::
	applymovement LOCALID_LITTLEROOT_MOM, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LittlerootTown_EventScript_MomNoticePlayerFemale::
	applymovement LOCALID_LITTLEROOT_MOM, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerMale5
	return

LittlerootTown_EventScript_MomApproachPlayerFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerFemale5
	return

LittlerootTown_EventScript_MomApproachPlayer0::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayer0
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayer1::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayer1
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale2::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale3::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale4::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale5::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale2::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale3::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale4::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale5::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeMale5
	return

LittlerootTown_EventScript_MomReturnHomeFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeFemale5
	return

LittlerootTown_EventScript_MomReturnHome0::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHome0
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHome1::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHome1
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale2::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale3::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale4::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale5::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale2::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale3::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale4::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale5::
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_Movement_MomApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayerMale2:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale4:
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale5:
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale2:
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale3:
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale4:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale5:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomReturnHome0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHome1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHomeMale2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale4:
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale5:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale2:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale3:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale5:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomExitThroughDoor:
	walk_up
	step_end

LittlerootTown_EventScript_Mom::
	lock
	faceplayer
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	applymovement LOCALID_LITTLEROOT_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetReceivedRunningShoes::
	removeobject LOCALID_LITTLEROOT_MOM
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	release
	end

LittlerootTown_EventScript_GiveRunningShoes::
	msgbox LittlerootTown_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_Text_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox LittlerootTown_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_MomExplainsLMenu, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

LittlerootTown_Text_OurNewHomeLetsGoInside:
	.string "MOM: {PLAYER}, we're here, honey!\p"
	.string "It must be tiring riding with our things\n"
	.string "in the moving truck.\p"
	.string "Well, this is LITTLEROOT TOWN.\p"
	.string "How do you like it?\n"
	.string "This is our new home!\p"
	.string "It has a quaint feel, but it seems to be\n"
	.string "an easy place to live, don't you think?\p"
	.string "And, you get your own room, {PLAYER}!\n"
	.string "Let's go inside.$"

LittlerootTown_Text_WaitPlayer:
	.string "MOM: Wait, {PLAYER}!$"

LittlerootTown_Text_WearTheseRunningShoes:
	.string "MOM: {PLAYER}! {PLAYER}! Did you\n"
	.string "introduce yourself to PROF. BIRCH?\p"
	.string "Oh! What an adorable POKéMON!\n"
	.string "You got it from PROF. BIRCH. How nice!\p"
	.string "You're your father's child, all right.\n"
	.string "You look good together with POKéMON!\p"
	.string "Here, honey! If you're going out on an\n"
	.string "adventure, wear these RUNNING SHOES.\p"
	.string "They'll put a zip in your step!$"

LittlerootTown_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

LittlerootTown_Text_ExplainRunningShoes:
	.string "MOM: {PLAYER}, those shoes came with\n"
	.string "instructions.\p"
	.string "“Press the B Button while wearing these\n"
	.string "RUNNING SHOES to run extra-fast!\p"
	.string "“Slip on these RUNNING SHOES and race\n"
	.string "in the great outdoors!”$"

LittlerootTown_Text_MomExplainsLMenu:
	.string "MOM: Oh, and PROF. BIRCH called ahead\n"
	.string "and told me everything: the level\l"
	.string "cap, and that menu of his.\p"
	.string "Honestly, don't let it worry you. He's\n"
	.string "a bit much, but he knows what he's\l"
	.string "doing.\p"
	.string "Just remember, dear: press the L Button\n"
	.string "any time you want to look at your\l"
	.string "POKéMON's details or make changes.\p"
	.string "It's all right there whenever you\n"
	.string "need it.$"

LittlerootTown_Text_ComeHomeIfAnythingHappens:
	.string "... ... ... ... ... ...\p"
	.string "To think that you have your very\n"
	.string "own POKéMON now...\p"
	.string "And the BATTLE FRONTIER, too. These\n"
	.string "EIGHT GAUNTLETS... The PROFESSOR\l"
	.string "seems to think they'd suit you\l"
	.string "perfectly.\p"
	.string "...Your father is going to be\n"
	.string "upset. He had such plans for your\l"
	.string "first adventure.\p"
	.string "Well. Never mind that now. If\n"
	.string "anything happens, you can always\l"
	.string "come home.\p"
	.string "Go on, go get them, honey!$"

LittlerootTown_Text_CanUsePCToStoreItems:
	.string "If you use a PC, you can store items\n"
	.string "and POKéMON.\p"
	.string "The power of science is staggering!$"

LittlerootTown_Text_BirchSpendsDaysInLab:
	.string "PROF. BIRCH used to be out in the\n"
	.string "tall grass every day.\p"
	.string "Lately he just locks himself in\n"
	.string "his LAB. And a man in fancy\l"
	.string "clothes keeps coming to visit...$"

LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Um, um, um!\p"
	.string "If you go outside and go in the grass,\n"
	.string "wild POKéMON will jump out!$"

LittlerootTown_Text_DangerousIfYouDontHavePokemon:
	.string "It's dangerous if you don't have\n"
	.string "your own POKéMON.$"

LittlerootTown_Text_CanYouGoSeeWhatsHappening:
	.string "Um, hi!\p"
	.string "There are scary POKéMON outside!\n"
	.string "I can hear their cries!\p"
	.string "I want to go see what's going on,\n"
	.string "but I don't have any POKéMON…\p"
	.string "Can you go see what's happening\n"
	.string "for me?$"

LittlerootTown_Text_YouSavedBirch:
	.string "You saved PROF. BIRCH!\n"
	.string "I'm so glad!$"

LittlerootTown_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_Text_TownSign:
	.string "LITTLEROOT TOWN\n"
	.string "“A town that can't be shaded any hue.”$"

LittlerootTown_Text_ProfBirchsLab:
	.string "PROF. BIRCH'S POKéMON LAB$"

LittlerootTown_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

LittlerootTown_Text_ProfBirchsHouse:
	.string "PROF. BIRCH'S HOUSE$"

LittlerootTown_Text_BirchSomethingToShowYouAtLab:
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

@ Ten Gauntlets: Birch's lab arc, after gauntlet 5 (storyline.md;
@ VAR_BIRCH_STORY_STATE, see BattleFrontier_OutsideWest). Outside the lab:
@ state 1, a man in a suit blocks the door with WALLACE and the rival in front
@ of him (walking up plays the scene: three more of DEVON's men rush in, and
@ the player and the rival tag-team two of them); state 2, WALLACE is inside,
@ DEVON's men have fled and the rival waits; state 3, WALLACE and the rival face each
@ other by the door (talking to either plays the debrief). From state 4 the
@ rival is in the lab, and until the family scene (state 5) the way out to
@ ROUTE 101 sends the player home first.
LittlerootTown_EventScript_SetupBirchStory::
	setflag FLAG_TEMP_1
	setflag FLAG_HIDE_BIRCH_STORY_LITTLEROOT_WALLACE
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	call LittlerootTown_EventScript_HideWanderersForLab
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_2, 1
	switch VAR_BIRCH_STORY_STATE
	case 1, LittlerootTown_EventScript_SetupLabDoor
	case 2, LittlerootTown_EventScript_SetupWallaceInside
	case 3, LittlerootTown_EventScript_SetupLabDebrief
	case 4, LittlerootTown_EventScript_ArmGoHomeFirst
	return

@ The town's three wanderers (the twin, the boy and the fat man) stay
@ indoors for the whole arc, states 1-5, so nobody walks into the scenes.
@ Their gossip about it moved to OLDALE's townsfolk. The fat man's hide flag
@ is vanilla's, cleared for good after the opening, so clearing it again
@ afterwards puts him back as he was.
LittlerootTown_EventScript_HideWanderersForLab::
	goto_if_eq VAR_BIRCH_STORY_STATE, 0, Common_EventScript_NopReturn
	goto_if_ge VAR_BIRCH_STORY_STATE, 6, LittlerootTown_EventScript_ShowFatManAfterLab
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	setflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	return

LittlerootTown_EventScript_ShowFatManAfterLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	return

LittlerootTown_EventScript_SetupLabDoor::
	clearflag FLAG_TEMP_1
	clearflag FLAG_HIDE_BIRCH_STORY_LITTLEROOT_WALLACE
	clearflag FLAG_TEMP_3
	setvar VAR_TEMP_1, 0
	return

LittlerootTown_EventScript_SetupWallaceInside::
	clearflag FLAG_TEMP_3
	setobjectxyperm LOCALID_LITTLEROOT_LAB_RIVAL, 6, 18
	setobjectmovementtype LOCALID_LITTLEROOT_LAB_RIVAL, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_SetupLabDebrief::
	clearflag FLAG_HIDE_BIRCH_STORY_LITTLEROOT_WALLACE
	clearflag FLAG_TEMP_3
	setobjectxyperm LOCALID_LITTLEROOT_WALLACE, 6, 18
	setobjectmovementtype LOCALID_LITTLEROOT_WALLACE, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_LITTLEROOT_LAB_RIVAL, 8, 18
	setobjectmovementtype LOCALID_LITTLEROOT_LAB_RIVAL, MOVEMENT_TYPE_FACE_LEFT
	return

LittlerootTown_EventScript_ArmGoHomeFirst::
	setvar VAR_TEMP_2, 0
	return

LittlerootTown_EventScript_LabDoorScene::
	lockall
	setvar VAR_TEMP_1, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 4, LittlerootTown_EventScript_LabDoorFaceRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	goto LittlerootTown_EventScript_LabDoorTalk

LittlerootTown_EventScript_LabDoorFaceRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
LittlerootTown_EventScript_LabDoorTalk::
	waitmovement 0
	msgbox LittlerootTown_Text_LabDoor1, MSGBOX_DEFAULT
	closemessage
	@ The player hurries to the rival's side at (5, 19) first, so the camera
	@ has settled before the reinforcements appear: the engine removes an
	@ object far outside the view whenever the camera moves
	@ (RemoveObjectEventIfOutsideView). Then three more of DEVON's men rush
	@ in from row 12, just above the screen: one to WALLACE's right, two
	@ down the west edge to face the rival (5, 18) and the player.
	call LittlerootTown_EventScript_LabPlayerToRival
	waitmovement 0
	clearflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_6
	addobject LOCALID_LITTLEROOT_AGENT_A
	addobject LOCALID_LITTLEROOT_AGENT_B
	addobject LOCALID_LITTLEROOT_AGENT_C
	applymovement LOCALID_LITTLEROOT_AGENT_A, LittlerootTown_Movement_AgentAIn
	applymovement LOCALID_LITTLEROOT_AGENT_B, LittlerootTown_Movement_AgentBIn
	applymovement LOCALID_LITTLEROOT_AGENT_C, LittlerootTown_Movement_AgentCIn
	waitmovement 0
	applymovement LOCALID_LITTLEROOT_LAB_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_LITTLEROOT_WALLACE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox LittlerootTown_Text_LabWallaceTakesTwo, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_LabRivalTagTeam, MSGBOX_DEFAULT
	closemessage
	special SaveFacilityHeldItems
LittlerootTown_EventScript_LabTagBattle::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_ne VAR_RESULT, 0, LittlerootTown_EventScript_LabTagBattleStart
	special LoadPlayerParty
	msgbox LittlerootTown_Text_LabTagPickTeam, MSGBOX_DEFAULT
	closemessage
	goto LittlerootTown_EventScript_LabTagBattle

@ A story fight, not part of a run: no white-out on a loss, the team is
@ healed and its held items put back either way, and a loss just means
@ trying again.
LittlerootTown_EventScript_LabTagBattleStart::
	call LittlerootTown_EventScript_LabTagBattleWithRival
	special RestoreFacilityHeldItems
	special HealPlayerParty
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LittlerootTown_EventScript_LabTagWon
	msgbox LittlerootTown_Text_LabTagLost, MSGBOX_DEFAULT
	closemessage
	goto LittlerootTown_EventScript_LabTagBattle

LittlerootTown_EventScript_LabTagWon::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox LittlerootTown_Text_LabAgentsFallBack, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_SUIT, LittlerootTown_Movement_SuitFlees
	applymovement LOCALID_LITTLEROOT_AGENT_A, LittlerootTown_Movement_AgentAFlees
	applymovement LOCALID_LITTLEROOT_AGENT_B, LittlerootTown_Movement_AgentBFlees
	applymovement LOCALID_LITTLEROOT_AGENT_C, LittlerootTown_Movement_AgentCFlees
	waitmovement 0
	removeobject LOCALID_LITTLEROOT_SUIT
	removeobject LOCALID_LITTLEROOT_AGENT_A
	removeobject LOCALID_LITTLEROOT_AGENT_B
	removeobject LOCALID_LITTLEROOT_AGENT_C
	applymovement LOCALID_LITTLEROOT_LAB_RIVAL, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_LITTLEROOT_WALLACE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox LittlerootTown_Text_LabDoor2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_WALLACE, LittlerootTown_Movement_WallaceToDoor
	waitmovement 0
	opendoor 7, 16
	waitdooranim
	applymovement LOCALID_LITTLEROOT_WALLACE, LittlerootTown_Movement_WallaceIntoLab
	waitmovement 0
	removeobject LOCALID_LITTLEROOT_WALLACE
	closedoor 7, 16
	waitdooranim
	setvar VAR_BIRCH_STORY_STATE, 2
	releaseall
	end

@ The player joins the rival from wherever the scene started: one of the
@ tiles at x 4 (rows 17-19) or x 10 (rows 16-19).
LittlerootTown_EventScript_LabPlayerToRival::
	goto_if_eq VAR_0x8004, 4, LittlerootTown_EventScript_LabPlayerFromLeft
	switch VAR_0x8005
	case 16, LittlerootTown_EventScript_LabPlayerFromRight16
	case 17, LittlerootTown_EventScript_LabPlayerFromRight17
	case 18, LittlerootTown_EventScript_LabPlayerFromRight18
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromRight19
	return

LittlerootTown_EventScript_LabPlayerFromRight16::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromRight16
	return

LittlerootTown_EventScript_LabPlayerFromRight17::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromRight17
	return

LittlerootTown_EventScript_LabPlayerFromRight18::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromRight18
	return

LittlerootTown_EventScript_LabPlayerFromLeft::
	switch VAR_0x8005
	case 17, LittlerootTown_EventScript_LabPlayerFromLeft17
	case 18, LittlerootTown_EventScript_LabPlayerFromLeft18
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromLeft19
	return

LittlerootTown_EventScript_LabPlayerFromLeft17::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromLeft17
	return

LittlerootTown_EventScript_LabPlayerFromLeft18::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerFromLeft18
	return

@ MAY brings the same trio whatever the starter; BRENDAN's half follows his
@ starter, as in the Tower rematch (VAR_STARTER_MON: 1 water, 2 grass,
@ otherwise fire).
LittlerootTown_EventScript_LabTagBattleWithRival::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_LabTagWithBrendan
	multi_2_vs_2 TRAINER_LITTLEROOT_DEVON_AGENT_1, LittlerootTown_Text_Agent1Defeat, TRAINER_LITTLEROOT_DEVON_AGENT_2, LittlerootTown_Text_Agent2Defeat, PARTNER_RIVAL_MAY
	return

LittlerootTown_EventScript_LabTagWithBrendan::
	switch VAR_STARTER_MON
	case 1, LittlerootTown_EventScript_LabTagWithBrendanWater
	case 2, LittlerootTown_EventScript_LabTagWithBrendanGrass
	multi_2_vs_2 TRAINER_LITTLEROOT_DEVON_AGENT_1, LittlerootTown_Text_Agent1Defeat, TRAINER_LITTLEROOT_DEVON_AGENT_2, LittlerootTown_Text_Agent2Defeat, PARTNER_RIVAL_BRENDAN_FIRE
	return

LittlerootTown_EventScript_LabTagWithBrendanWater::
	multi_2_vs_2 TRAINER_LITTLEROOT_DEVON_AGENT_1, LittlerootTown_Text_Agent1Defeat, TRAINER_LITTLEROOT_DEVON_AGENT_2, LittlerootTown_Text_Agent2Defeat, PARTNER_RIVAL_BRENDAN_WATER
	return

LittlerootTown_EventScript_LabTagWithBrendanGrass::
	multi_2_vs_2 TRAINER_LITTLEROOT_DEVON_AGENT_1, LittlerootTown_Text_Agent1Defeat, TRAINER_LITTLEROOT_DEVON_AGENT_2, LittlerootTown_Text_Agent2Defeat, PARTNER_RIVAL_BRENDAN_GRASS
	return

LittlerootTown_Movement_PlayerFromLeft17:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	face_left
	step_end

LittlerootTown_Movement_PlayerFromLeft18:
	walk_fast_down
	walk_fast_right
	face_left
	step_end

LittlerootTown_Movement_PlayerFromLeft19:
	walk_fast_right
	face_left
	step_end

LittlerootTown_Movement_PlayerFromRight16:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_left
	step_end

LittlerootTown_Movement_PlayerFromRight17:
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_left
	step_end

LittlerootTown_Movement_PlayerFromRight18:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_left
	step_end

LittlerootTown_Movement_PlayerFromRight19:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_left
	step_end

@ A: from (11, 12) down the x 11 column to WALLACE's right, (8, 18).
LittlerootTown_Movement_AgentAIn:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_left
	step_end

@ B: from (1, 12) down the x 1 column, then round to face the rival from (4, 18).
LittlerootTown_Movement_AgentBIn:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_right
	walk_fast_right
	face_right
	step_end

@ C: from (0, 12) down the x 0 column a step behind B, to face the player from (4, 19).
LittlerootTown_Movement_AgentCIn:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	face_right
	step_end

@ They flee the way they came, back to row 12, just off the top of the
@ screen; the first man takes the x 10 column.
LittlerootTown_Movement_SuitFlees:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LittlerootTown_Movement_AgentAFlees:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LittlerootTown_Movement_AgentBFlees:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LittlerootTown_Movement_AgentCFlees:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LittlerootTown_Movement_WallaceToDoor:
	walk_fast_up
	step_end

LittlerootTown_Movement_WallaceIntoLab:
	walk_fast_up
	set_invisible
	step_end

LittlerootTown_EventScript_LabSuit::
	lock
	faceplayer
	goto_if_ge VAR_BIRCH_STORY_STATE, 2, LittlerootTown_EventScript_LabSuitAside
	msgbox LittlerootTown_Text_LabSuitNoEntry, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_LabSuitAside::
	msgbox LittlerootTown_Text_LabSuitAside, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_LabWallace::
	lock
	goto_if_eq VAR_BIRCH_STORY_STATE, 3, LittlerootTown_EventScript_LabDebrief
	faceplayer
	msgbox LittlerootTown_Text_LabWallaceWait, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_LabRival::
	lock
	goto_if_ge VAR_CROWN_STORY_STATE, 2, LittlerootTown_EventScript_CrownRival
	goto_if_eq VAR_BIRCH_STORY_STATE, 3, LittlerootTown_EventScript_LabDebrief
	faceplayer
	goto_if_ge VAR_BIRCH_STORY_STATE, 4, LittlerootTown_EventScript_LabRivalSeeFolks
	msgbox LittlerootTown_Text_LabRivalWaiting, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_LabRivalSeeFolks::
	msgbox LittlerootTown_Text_LabRivalSeeFolks, MSGBOX_DEFAULT
	release
	end

@ WALLACE reports back to STEVEN and flies off (the same bird the vanilla
@ rival and STEVEN fly away on), then the rival stays behind.
LittlerootTown_EventScript_LabDebrief::
	applymovement LOCALID_LITTLEROOT_WALLACE, Common_Movement_FacePlayer
	applymovement LOCALID_LITTLEROOT_LAB_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LittlerootTown_Text_LabDebriefWallace, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_LITTLEROOT_WALLACE
	waitfieldeffect FLDEFF_NPCFLY_OUT
	applymovement LOCALID_LITTLEROOT_LAB_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LittlerootTown_Text_LabDebriefRival, MSGBOX_DEFAULT
	@ Taking a break from the FRONTIER, the rival hands over the FP they'd
	@ saved up.
	msgbox LittlerootTown_Text_LabRivalGivesFP, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1000
	special FacilityShopGiveFP
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_Text_LabReceivedRivalFP
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox LittlerootTown_Text_LabRivalKeepGoing, MSGBOX_DEFAULT
	setvar VAR_BIRCH_STORY_STATE, 4
	setvar VAR_TEMP_2, 0
	release
	end

LittlerootTown_EventScript_GoHomeFirst::
	lockall
	goto_if_eq VAR_CROWN_STORY_STATE, 5, LittlerootTown_EventScript_CrownGoHomeFirst
	msgbox LittlerootTown_Text_GoHomeFirst, MSGBOX_DEFAULT
LittlerootTown_EventScript_GoHomeFirstStepBack:
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown
	waitmovement 0
	releaseall
	end

LittlerootTown_Text_LabDoor1:
	.string "WALLACE: I'll ask you once more.\n"
	.string "What is going on in there?\p"
	.string "MAN IN SUIT: And I'll tell you\n"
	.string "once more. It's none of your\l"
	.string "business.\p"
	.string "WALLACE: Do you know who I am? I'm\n"
	.string "the POKéMON LEAGUE CHAMPION.\p"
	.string "One phone call, and I'd have\n"
	.string "PRESIDENT STONE himself on the\l"
	.string "line.\p"
	.string "MAN IN SUIT: Call him all you\n"
	.string "like. The PRESIDENT is... busy at\l"
	.string "the moment.\p"
	.string "WALLACE: Then I suppose I'll have\n"
	.string "to find another way to make you\l"
	.string "move.\p"
	.string "MAN IN SUIT: Another way? Ha!\n"
	.string "Bring it on, CHAMPION.\p"
	.string "Boys!$"

LittlerootTown_Text_LabWallaceTakesTwo:
	.string "WALLACE: Four of DEVON's finest.\n"
	.string "How flattering.\p"
	.string "I'll handle these two.\n"
	.string "{PLAYER}, {RIVAL}... can you two\l"
	.string "take the others?$"

LittlerootTown_Text_LabRivalTagTeam:
	.string "{RIVAL}: You bet we can!\p"
	.string "{PLAYER}, let's do this. Together!$"

LittlerootTown_Text_LabTagPickTeam:
	.string "{RIVAL}: {PLAYER}! Pick your\n"
	.string "POKéMON, quick!$"

LittlerootTown_Text_LabTagLost:
	.string "{RIVAL}: Ugh... They're tough.\p"
	.string "Come on, {PLAYER}! One more time!$"

LittlerootTown_Text_Agent1Defeat:
	.string "This wasn't in the briefing...$"

LittlerootTown_Text_Agent2Defeat:
	.string "The PRESIDENT won't like this.$"

LittlerootTown_Text_LabAgentsFallBack:
	.string "MAN IN SUIT: ...Tch. Fine.\p"
	.string "This changes nothing. The\n"
	.string "PROFESSOR is overdue on his loans,\l"
	.string "and DEVON wants what it's owed.\p"
	.string "Fall back!$"

LittlerootTown_Text_LabDoor2:
	.string "{RIVAL}: Loans? Dad never said a\n"
	.string "word about any loan! This is a\l"
	.string "load of garbage!\p"
	.string "WALLACE: Then let's find out what's\n"
	.string "really going on.$"

LittlerootTown_Text_LabSuitNoEntry:
	.string "MAN IN SUIT: Nobody goes in.\n"
	.string "PRESIDENT's orders.$"

LittlerootTown_Text_LabSuitAside:
	.string "MAN IN SUIT: ...Go on, then. Not\n"
	.string "like I can stop the CHAMPION.$"

LittlerootTown_Text_LabWallaceWait:
	.string "WALLACE: Stay close, {PLAYER}.$"

LittlerootTown_Text_LabRivalWaiting:
	.string "{RIVAL}: Go on, {PLAYER}! I'll keep\n"
	.string "watch out here, in case they come\l"
	.string "back.\p"
	.string "Just make sure Dad's okay.$"

LittlerootTown_Text_LabRivalSeeFolks:
	.string "{RIVAL}: While you're here, go and\n"
	.string "say hi to your mom and dad.\p"
	.string "I'll be at the lab.$"

LittlerootTown_Text_LabDebriefWallace:
	.string "WALLACE: There's more to this\n"
	.string "story than the PROFESSOR is\l"
	.string "letting on. I'm certain of it.\p"
	.string "And PRESIDENT STONE, here, in\n"
	.string "person...\p"
	.string "STEVEN needs to hear about this.\n"
	.string "Something is going on with his\l"
	.string "father.\p"
	.string "I'll report back to him right\n"
	.string "away.\p"
	.string "{PLAYER}, {RIVAL}. Look after each\n"
	.string "other.$"

LittlerootTown_Text_LabDebriefRival:
	.string "{RIVAL}: {PLAYER}... that felt good\n"
	.string "back there. Winning, I mean. With\l"
	.string "you.\p"
	.string "I haven't won much lately. I never\n"
	.string "made it past gauntlet 2. JUAN\l"
	.string "washes me out every single time.\p"
	.string "Honestly? I'm getting cold feet\n"
	.string "about the FRONTIER.\p"
	.string "And after today, Dad needs someone\n"
	.string "here more than I need another loss.\p"
	.string "So I'm staying in LITTLEROOT for a\n"
	.string "while, to help out at the lab.$"

LittlerootTown_Text_LabRivalGivesFP:
	.string "{RIVAL}: Here. I won't be needing\n"
	.string "these anymore.\p"
	.string "It's every FP I saved up. Spend it\n"
	.string "on something good.$"

LittlerootTown_Text_LabReceivedRivalFP:
	.string "{PLAYER} received 1,000 FP!$"

LittlerootTown_Text_LabRivalKeepGoing:
	.string "{RIVAL}: You keep going, okay?\n"
	.string "Somebody has to show those\l"
	.string "gauntlets how it's done.$"

LittlerootTown_Text_GoHomeFirst:
	.string "{PLAYER} decided to go home and see\n"
	.string "MOM and DAD first.$"


@ ============================================================================
@ Ten Gauntlets: the Crown is taken, after gauntlet 7 (storyline.md).
@ VAR_CROWN_STORY_STATE: 0 none, 1 gauntlet 7 cleared (the rival waits
@ outside the Palace), 2 the rival's news and STEVEN's call done (NOLAND and
@ GRETA guard the lab door), 3 they've warned the player off, 4 both beaten
@ (the lab is open: BIRCH alone in the stripped lab), 5 BIRCH has confessed
@ (the player's house unlocks; the way out to ROUTE 101 sends them home
@ first), 6 the house found empty (SCOTT waits outside it), 7 SCOTT's deal
@ and STEVEN's vow done (the standoff outside the Factory), 8 STEVEN beaten
@ (he waits by the Factory with the Lati), 9 done.
@ Gauntlet 8 (the Pyramid) stays closed until 9. The scenes are at the
@ Palace (BattleFrontier_OutsideEast), here, in the lab and the player's
@ house, and outside the Factory (BattleFrontier_OutsideWest).
@ ============================================================================

@ States 2-4: NOLAND and GRETA block the lab door until beaten, and the rival
@ waits beside it at (5, 18), where they stood for the Birch arc. States 2-6:
@ the town's wanderers stay indoors, as in the Birch arc. State 6: SCOTT,
@ NOLAND and GRETA wait below the player's front door, and the scene plays
@ when the player steps out of it.
LittlerootTown_EventScript_SetupCrownStory::
	setflag FLAG_HIDE_CROWN_STORY_NOLAND
	setflag FLAG_HIDE_CROWN_STORY_GRETA
	setflag FLAG_HIDE_CROWN_STORY_LITTLEROOT_SCOTT
	setflag FLAG_HIDE_CROWN_STORY_LITTLEROOT_STEVEN
	goto_if_lt VAR_CROWN_STORY_STATE, 2, Common_EventScript_NopReturn
	goto_if_ge VAR_CROWN_STORY_STATE, 7, Common_EventScript_NopReturn
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	setflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	call_if_lt VAR_CROWN_STORY_STATE, 4, LittlerootTown_EventScript_ShowCrownGuards
	call_if_lt VAR_CROWN_STORY_STATE, 5, LittlerootTown_EventScript_ShowCrownRival
	call_if_eq VAR_CROWN_STORY_STATE, 5, LittlerootTown_EventScript_ArmGoHomeFirst
	call_if_eq VAR_CROWN_STORY_STATE, 6, LittlerootTown_EventScript_SetupCrownScott
	return

LittlerootTown_EventScript_ShowCrownGuards::
	clearflag FLAG_HIDE_CROWN_STORY_NOLAND
	clearflag FLAG_HIDE_CROWN_STORY_GRETA
	return

LittlerootTown_EventScript_ShowCrownRival::
	clearflag FLAG_TEMP_3
	setobjectxyperm LOCALID_LITTLEROOT_LAB_RIVAL, 5, 18
	setobjectmovementtype LOCALID_LITTLEROOT_LAB_RIVAL, MOVEMENT_TYPE_FACE_RIGHT
	return

@ The player's house is BRENDAN's for a boy, MAY's for a girl. SCOTT stands
@ two tiles below its door, NOLAND and GRETA behind him; STEVEN hides round
@ the side of the house, out of sight until SCOTT leaves. The scene only
@ plays when the player has just come out of the door (still on it until the
@ step down).
LittlerootTown_EventScript_SetupCrownScott::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlaceCrownScottMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlaceCrownScottFemale
	clearflag FLAG_HIDE_CROWN_STORY_LITTLEROOT_SCOTT
	clearflag FLAG_HIDE_CROWN_STORY_NOLAND
	clearflag FLAG_HIDE_CROWN_STORY_GRETA
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, VAR_0x8006, Common_EventScript_NopReturn
	goto_if_ne VAR_0x8005, 8, Common_EventScript_NopReturn
	setvar VAR_TEMP_3, 1
	return

LittlerootTown_EventScript_PlaceCrownScottMale::
	setvar VAR_0x8006, 5
	setobjectxyperm LOCALID_LITTLEROOT_SCOTT, 5, 11
	setobjectxyperm LOCALID_LITTLEROOT_NOLAND, 4, 12
	setobjectxyperm LOCALID_LITTLEROOT_GRETA, 6, 12
	setobjectxyperm LOCALID_LITTLEROOT_STEVEN, 8, 6
	call LittlerootTown_EventScript_CrownSquadFaceUp
	return

LittlerootTown_EventScript_PlaceCrownScottFemale::
	setvar VAR_0x8006, 14
	setobjectxyperm LOCALID_LITTLEROOT_SCOTT, 14, 11
	setobjectxyperm LOCALID_LITTLEROOT_NOLAND, 13, 12
	setobjectxyperm LOCALID_LITTLEROOT_GRETA, 15, 12
	setobjectxyperm LOCALID_LITTLEROOT_STEVEN, 11, 6
	call LittlerootTown_EventScript_CrownSquadFaceUp
	return

LittlerootTown_EventScript_CrownSquadFaceUp::
	setobjectmovementtype LOCALID_LITTLEROOT_SCOTT, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_LITTLEROOT_NOLAND, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_LITTLEROOT_GRETA, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_CrownRival::
	faceplayer
	goto_if_eq VAR_CROWN_STORY_STATE, 4, LittlerootTown_EventScript_CrownRivalLabOpen
	msgbox LittlerootTown_Text_CrownRivalBlocked, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_CrownRivalLabOpen::
	msgbox LittlerootTown_Text_CrownRivalLabOpen, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_CrownGoHomeFirst::
	msgbox LittlerootTown_Text_CrownGoHomeFirst, MSGBOX_DEFAULT
	goto LittlerootTown_EventScript_GoHomeFirstStepBack

@ Walking into the player's own front door, states 2-4 (TryDoorWarp, see
@ IsStoryLockedHomeDoor in src/facility.c).
LittlerootTown_EventScript_HomeDoorLocked::
	lockall
	msgbox LittlerootTown_Text_HomeDoorLocked, MSGBOX_DEFAULT
	releaseall
	end

@ NOLAND (7, 17) and GRETA (8, 17) stand shoulder to shoulder in front of the
@ lab door. The first talk is their warning (state 3); after that, they offer
@ the fight. A loss on either battle whites out to OLDALE, and both have to be
@ beaten again.
LittlerootTown_EventScript_CrownGuards::
	lock
	applymovement LOCALID_LITTLEROOT_NOLAND, Common_Movement_FacePlayer
	applymovement LOCALID_LITTLEROOT_GRETA, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_ge VAR_CROWN_STORY_STATE, 3, LittlerootTown_EventScript_CrownGuardsWarning
	msgbox LittlerootTown_Text_CrownGuardsFirst, MSGBOX_DEFAULT
	setvar VAR_CROWN_STORY_STATE, 3
	release
	end

LittlerootTown_EventScript_CrownGuardsWarning::
	msgbox LittlerootTown_Text_CrownGuardsLastWarning, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_EventScript_CrownGuardsFight
	msgbox LittlerootTown_Text_CrownGuardsNo, MSGBOX_DEFAULT
	release
	end

@ The player squares up at (7, 18), below NOLAND, wherever they talked from:
@ (7, 18) itself, below GRETA at (8, 18), or beside her at (9, 17). No heal
@ between the two battles - the SCRAMBLER is on - and the held items come
@ back afterwards, win or white-out (EventScript_RestoreStoryHeldItems).
LittlerootTown_EventScript_CrownGuardsFight::
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 8, LittlerootTown_EventScript_CrownPlayerFromBelowGreta
	call_if_eq VAR_0x8004, 9, LittlerootTown_EventScript_CrownPlayerFromBesideGreta
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_LITTLEROOT_NOLAND, Common_Movement_FaceDown
	applymovement LOCALID_LITTLEROOT_GRETA, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PC_OFF
	msgbox LittlerootTown_Text_CrownUsedScrambler, MSGBOX_DEFAULT
	waitse
	msgbox LittlerootTown_Text_CrownGuardsGuts, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	trainerbattle_no_intro TRAINER_LITTLEROOT_GRETA, LittlerootTown_Text_CrownGretaDefeat
	msgbox LittlerootTown_Text_CrownNolandNext, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_LITTLEROOT_NOLAND, LittlerootTown_Text_CrownNolandDefeat
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	msgbox LittlerootTown_Text_CrownGuardsBeaten, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_GRETA, LittlerootTown_Movement_GretaLeavesLab
	applymovement LOCALID_LITTLEROOT_NOLAND, LittlerootTown_Movement_NolandLeavesLab
	waitmovement 0
	removeobject LOCALID_LITTLEROOT_GRETA
	removeobject LOCALID_LITTLEROOT_NOLAND
	setvar VAR_CROWN_STORY_STATE, 4
	release
	end

LittlerootTown_EventScript_CrownPlayerFromBelowGreta::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_CrownFromBelowGreta
	waitmovement 0
	return

LittlerootTown_EventScript_CrownPlayerFromBesideGreta::
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_CrownFromBesideGreta
	waitmovement 0
	return

LittlerootTown_Movement_CrownFromBelowGreta:
	walk_left
	step_end

LittlerootTown_Movement_CrownFromBesideGreta:
	walk_down
	walk_left
	walk_left
	step_end

@ Off along row 17 to the east, out of sight past x 14.
LittlerootTown_Movement_GretaLeavesLab:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LittlerootTown_Movement_NolandLeavesLab:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

@ State 6: the player steps out of their empty house. SCOTT steps up to them
@ for the deal and takes the real badges (FLAG_REAL_BADGES, so even the Lati
@ stops growing - FrontierStoryAllowsExp()), then leaves with NOLAND and
@ GRETA, out of sight to the side. STEVEN comes round the house: he heard
@ everything, and flies off to end it.
LittlerootTown_EventScript_CrownScott::
	lockall
	setvar VAR_TEMP_3, 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_Text_CrownScott1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_SCOTT, Common_Movement_WalkUp
	waitmovement 0
	msgbox LittlerootTown_Text_CrownScott2, MSGBOX_DEFAULT
	playse SE_PIN
	message LittlerootTown_Text_CrownBadgesSwapped
	waitmessage
	waitse
	waitbuttonpress
	clearflag FLAG_REAL_BADGES
	msgbox LittlerootTown_Text_CrownScott3, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_CrownSquadLeavesEast
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_CrownSquadLeavesWest
	waitmovement 0
	removeobject LOCALID_LITTLEROOT_SCOTT
	removeobject LOCALID_LITTLEROOT_NOLAND
	removeobject LOCALID_LITTLEROOT_GRETA
	delay 40
	clearflag FLAG_HIDE_CROWN_STORY_LITTLEROOT_STEVEN
	addobject LOCALID_LITTLEROOT_STEVEN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_CrownStevenFromEast
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_CrownStevenFromWest
	waitmovement 0
	msgbox LittlerootTown_Text_CrownSteven, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LITTLEROOT_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_LITTLEROOT_STEVEN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setvar VAR_CROWN_STORY_STATE, 7
	releaseall
	end

LittlerootTown_EventScript_CrownSquadLeavesEast::
	applymovement LOCALID_LITTLEROOT_SCOTT, LittlerootTown_Movement_CrownScottEast
	applymovement LOCALID_LITTLEROOT_NOLAND, LittlerootTown_Movement_CrownNolandEast
	applymovement LOCALID_LITTLEROOT_GRETA, LittlerootTown_Movement_CrownGretaEast
	return

LittlerootTown_EventScript_CrownSquadLeavesWest::
	applymovement LOCALID_LITTLEROOT_SCOTT, LittlerootTown_Movement_CrownScottWest
	applymovement LOCALID_LITTLEROOT_NOLAND, LittlerootTown_Movement_CrownNolandWest
	applymovement LOCALID_LITTLEROOT_GRETA, LittlerootTown_Movement_CrownGretaWest
	return

LittlerootTown_EventScript_CrownStevenFromEast::
	applymovement LOCALID_LITTLEROOT_STEVEN, LittlerootTown_Movement_CrownStevenFromEast
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	return

LittlerootTown_EventScript_CrownStevenFromWest::
	applymovement LOCALID_LITTLEROOT_STEVEN, LittlerootTown_Movement_CrownStevenFromWest
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	return

@ A boy's house: the player at (5, 9), SCOTT steps up to (5, 10). They leave
@ east, out of sight past x 12; STEVEN comes down the east side of the house
@ from (8, 6) to (6, 9), beside the player. A girl's house is the mirror
@ image, around (14, 9).
LittlerootTown_Movement_CrownScottEast:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_CrownNolandEast:
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

LittlerootTown_Movement_CrownGretaEast:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_CrownScottWest:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_CrownNolandWest:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_CrownGretaWest:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_CrownStevenFromEast:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	face_left
	step_end

LittlerootTown_Movement_CrownStevenFromWest:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	face_right
	step_end

LittlerootTown_Text_CrownRivalBlocked:
	.string "{RIVAL}: They won't let anyone near\n"
	.string "the lab. Not even me.\p"
	.string "NOLAND and GRETA... I couldn't do\n"
	.string "a thing against them.\p"
	.string "{PLAYER}, you're Dad's only hope.$"

LittlerootTown_Text_CrownRivalLabOpen:
	.string "{RIVAL}: You did it! The door's\n"
	.string "clear!\p"
	.string "Go! I'm right behind you!$"

LittlerootTown_Text_CrownGoHomeFirst:
	.string "{PLAYER} decided to check on MOM\n"
	.string "and DAD before leaving.$"

LittlerootTown_Text_HomeDoorLocked:
	.string "The door is locked.\p"
	.string "MOM and DAD must have locked it\n"
	.string "because of all the commotion.$"

LittlerootTown_Text_CrownGuardsFirst:
	.string "GRETA: Well, well, well. If you're\n"
	.string "here, that settles it.\p"
	.string "You're on STEVEN and WALLACE's\n"
	.string "team.\p"
	.string "Oh, don't look so surprised. We\n"
	.string "aren't stupid.\p"
	.string "We know you've been meeting STEVEN.\n"
	.string "And we know you caught that LATI.\p"
	.string "And that little trip to EVER GRANDE\n"
	.string "with WALLACE? MAXIE and ARCHIE told\l"
	.string "us all about it.\p"
	.string "SCOTT is not happy about all your\n"
	.string "meddling.\p"
	.string "NOLAND: Look, kid. This is none of\n"
	.string "your business.\p"
	.string "BIRCH didn't keep his promises. He\n"
	.string "knew the consequences, and the\l"
	.string "consequences fell on him.\p"
	.string "We're under strict orders to keep\n"
	.string "him under house arrest.\p"
	.string "Get lost.$"

LittlerootTown_Text_CrownGuardsLastWarning:
	.string "NOLAND: This is your last warning,\n"
	.string "kid.\p"
	.string "Do you want trouble?$"

LittlerootTown_Text_CrownGuardsNo:
	.string "NOLAND: Smart. Now beat it.$"

LittlerootTown_Text_CrownUsedScrambler:
	.string "{PLAYER} used the SCRAMBLER!\p"
	.string "Every POKéNAV nearby went dark.$"

LittlerootTown_Text_CrownGuardsGuts:
	.string "GRETA: Ha! Pulling that thing on\n"
	.string "us? The kid's got guts.\p"
	.string "I almost like it.\p"
	.string "NOLAND: Then let's see how far guts\n"
	.string "get you.\p"
	.string "No auto-heal for any of us now.\n"
	.string "You'll have to beat us both, back\l"
	.string "to back, if you want to walk out\l"
	.string "of here.\p"
	.string "GRETA: Me first!$"

LittlerootTown_Text_CrownGretaDefeat:
	.string "GRETA: Grr... Not bad, kid!$"

LittlerootTown_Text_CrownNolandNext:
	.string "NOLAND: My turn. And don't expect\n"
	.string "a breather.$"

LittlerootTown_Text_CrownNolandDefeat:
	.string "NOLAND: ...You've got to be\n"
	.string "kidding me.$"

LittlerootTown_Text_CrownGuardsBeaten:
	.string "NOLAND: ...Unbelievable.\n"
	.string "Beaten by a kid. Twice over.\p"
	.string "GRETA: Doesn't matter.\p"
	.string "It's too late anyway. SCOTT already\n"
	.string "got what he wanted.\p"
	.string "NOLAND: Let's go.$"

LittlerootTown_Text_CrownScott1:
	.string "SCOTT: Ah, {PLAYER}. There you are.\p"
	.string "I'll admit it. I thought things\n"
	.string "might get messy today.$"

LittlerootTown_Text_CrownScott2:
	.string "SCOTT: You've been busy, haven't\n"
	.string "you?\p"
	.string "After your fourth gauntlet, the\n"
	.string "charging slowed down. Hardly a\l"
	.string "trickle.\p"
	.string "That's when I knew you'd swapped\n"
	.string "your badges.\p"
	.string "And then my men kept spotting\n"
	.string "STEVEN on my island. Secret\l"
	.string "meetings, here and there...\p"
	.string "Heheh. I'm not angry. I'm\n"
	.string "practical.\p"
	.string "Thanks to BIRCH's research, we\n"
	.string "need even more bond energy than\l"
	.string "we thought.\p"
	.string "So you'll be wearing these. New and\n"
	.string "improved. Built for maximum\l"
	.string "harvest.$"

LittlerootTown_Text_CrownBadgesSwapped:
	.string "SCOTT swapped {PLAYER}'s BADGES for\n"
	.string "a new set of counterfeits!$"

LittlerootTown_Text_CrownScott3:
	.string "{PLAYER} asked SCOTT why he wants\n"
	.string "permanent MEGAS so badly.\p"
	.string "SCOTT: ...\p"
	.string "Some of us never got a partner.\p"
	.string "So I'll take all of them.\p"
	.string "Here's the deal, {PLAYER}. Beat\n"
	.string "gauntlet 8 wearing those badges.\p"
	.string "Oh, and in case you were wondering\n"
	.string "where your parents are...\p"
	.string "They're my guests. Insurance.\p"
	.string "Any funny business, swapping those\n"
	.string "badges, running to STEVEN, and you\l"
	.string "won't see them again.\p"
	.string "Heheh. Good luck in there.$"

LittlerootTown_Text_CrownSteven:
	.string "STEVEN: {PLAYER}.\p"
	.string "I heard everything. Every word.\p"
	.string "Taking your parents... SCOTT has\n"
	.string "crossed the line. And now I have\l"
	.string "proof.\p"
	.string "I'm going to the FACTORY. I'm\n"
	.string "going to end this, now.\p"
	.string "Stay out of sight. If SCOTT is\n"
	.string "watching you, this can't look like\l"
	.string "your doing.$"
