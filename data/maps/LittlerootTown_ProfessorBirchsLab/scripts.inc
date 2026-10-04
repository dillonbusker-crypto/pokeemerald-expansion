LittlerootTown_ProfessorBirchsLab_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_ProfessorBirchsLab_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_ProfessorBirchsLab_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
	.byte 0

	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
	@ 1: Beat Elite Four, Dex upgrade ready
	@ 2: Received National Dex
	@ 3: Left lab after receiving National Dex
	@ 4: Entered lab after catching all Hoenn mons
	@ 5: Birch told player to choose Johto starter
	@ 6: Chose Johto starter

	@ State descriptions for VAR_BIRCH_LAB_STATE
	@ 1: Never occurs
	@ 2: Chose starter
	@ 3: Received starter in lab
	@ 4: Defeated rival on Route 103
	@ 5: Received pokedex

@ Ten Gauntlets: DEVON's men have stripped the lab bare since the raid (the
@ Crown is taken, storyline.md) - see StripBirchsLab in src/facility.c.
LittlerootTown_ProfessorBirchsLab_OnLoad:
	call_if_ge VAR_CROWN_STORY_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_StripLab
	end

LittlerootTown_ProfessorBirchsLab_EventScript_StripLab::
	special StripBirchsLab
	return

LittlerootTown_ProfessorBirchsLab_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	call LittlerootTown_ProfessorBirchsLab_EventScript_SetupBirchStory
	call LittlerootTown_ProfessorBirchsLab_EventScript_SetupCrownStory
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter::
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 5, 10
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
	goto LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout

LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout::
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout::
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 5, 10
	end

LittlerootTown_ProfessorBirchsLab_OnWarp:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
	.2byte 0

LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade::
	turnobject LOCALID_PLAYER, DIR_NORTH
	addobject LOCALID_BIRCHS_LAB_BIRCH
	addobject LOCALID_BIRCHS_LAB_RIVAL
	turnobject LOCALID_BIRCHS_LAB_RIVAL, DIR_NORTH
	setobjectxy LOCALID_BIRCHS_LAB_RIVAL, 5, 5
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
	turnobject LOCALID_BIRCHS_LAB_AIDE, DIR_EAST
	setobjectxy LOCALID_BIRCHS_LAB_AIDE, 10, 10
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject::
	addobject LOCALID_BIRCHS_LAB_RIVAL
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters::
	addobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
	addobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
	addobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
	addobject LOCALID_BIRCHS_LAB_RIVAL
	turnobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL, 8, 4
	turnobject LOCALID_BIRCHS_LAB_TOTODILE_BALL, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_TOTODILE_BALL, 9, 4
	turnobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_CHIKORITA_BALL, 10, 4
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
	turnobject LOCALID_BIRCHS_LAB_RIVAL, DIR_EAST
	setobjectxy LOCALID_BIRCHS_LAB_RIVAL, 5, 5
	end

LittlerootTown_ProfessorBirchsLab_OnFrame:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent
	map_script_2 VAR_BIRCH_LAB_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter
	map_script_2 VAR_TEMP_2, 0, LittlerootTown_ProfessorBirchsLab_EventScript_StoneScene
	map_script_2 VAR_TEMP_3, 1, LittlerootTown_ProfessorBirchsLab_EventScript_Confession
	.2byte 0

@ The starter is technically given prior to this on Route 101 by special ChooseStarter
@ This is just where the game tells you its yours and lets you nickname it
LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent::
	lockall
	bufferleadmonspeciesname STR_VAR_1
	message LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ThisOneIsSpecial, MSGBOX_DEFAULT
	closemessage
	msgbox LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_ROUTE_101_BOY
	setvar VAR_BIRCH_LAB_STATE, 3
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent::
	lockall
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex
	waitmovement 0
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex
	end

LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex::
	lockall
	delay 30
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes
	waitmovement 0
	delay 20
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 10
	playse SE_CLICK
	delay 20
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment
	playse SE_PC_ON
	waitse
	delay 20
	applymovement LOCALID_BIRCHS_LAB_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex
	waitmovement 0
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational
	waitmessage
	waitfanfare
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	setvar VAR_SCOTT_BF_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes:
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter::
	lockall
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_Aide::
	lock
	faceplayer
	goto_if_eq VAR_BIRCH_STORY_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_AideStayOut
	goto_if_ge VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter
	goto_if_set FLAG_BIRCH_AIDE_MET, LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork, MSGBOX_DEFAULT
	setflag FLAG_BIRCH_AIDE_MET
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Cyndaquil::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Totodile::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_TOTODILE, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Chikorita::
	release
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	showmonpic SPECIES_CHIKORITA, 10, 3
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil::
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CYNDAQUIL
	givemon SPECIES_CYNDAQUIL, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile::
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita::
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIKORITA
	givemon SPECIES_CHIKORITA, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC
	hidemonpic
	goto Common_EventScript_NoMoreRoomForPokemon
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC::
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
	removeobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita::
	hidemonpic
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter::
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter
	waitmessage
	waitfanfare
	return

LittlerootTown_ProfessorBirchsLab_EventScript_Birch::
	lock
	faceplayer
	goto_if_ge VAR_CROWN_STORY_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_BirchAfterCrown
	goto_if_ge VAR_BIRCH_STORY_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_BirchEverythingFine
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting
	goto_if_unset FLAG_HAS_MATCH_CALL, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
	end

LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister::
	goto_if_unset FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380, ProfBirch_EventScript_RatePokedexOrRegister
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, ProfBirch_EventScript_RatePokedexOrRegister
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, ProfBirch_EventScript_RatePokedexOrRegister
	goto_if_eq VAR_BIRCH_LAB_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome, MSGBOX_DEFAULT
	release
	end

EventScript_RegisterProfBirch::
	msgbox MatchCall_Text_BirchRegisterCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MatchCall_Text_RegisteredBirch, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	setvar VAR_REGISTER_BIRCH_STATE, 2
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex::
	@ Ten Gauntlets: rival already ran here from Route 103 furious about the
	@ player's pre-built level 50 starter (see Route103's post-battle text) -
	@ this is where Birch actually answers her, and the player overhears the
	@ whole Ten Gauntlets / level 50 / L-menu explanation as a side effect.
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayDemandsAnswers
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanDemandsAnswers
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchExplainsLevelCap, MSGBOX_DEFAULT
	bufferleadmonspeciesname STR_VAR_1
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchExplainsLMenu, MSGBOX_DEFAULT
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex, MSGBOX_DEFAULT
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
	@ Ten Gauntlets: the PokeNav's auto-heal (a DEVON feature) is what heals
	@ the player between battles in the story (storyline.md), so they need one.
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchGivesPokenav, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokenav
	waitmessage
	waitfanfare
	waitbuttonpress
	setflag FLAG_SYS_POKENAV_GET
	@ Ten Gauntlets: Birch finishes (badges, SCOTT, the ticket) before the
	@ rival steps up for the last word, which sets up the rematch outside the
	@ Battle Tower (BattleFrontier_OutsideEast_EventScript_Rival).
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchOffersFrontierChallenge, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	closemessage
	applymovement LOCALID_BIRCHS_LAB_RIVAL, LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayAnnouncesFivePokemon
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanAnnouncesFivePokemon
	setvar VAR_BIRCH_LAB_STATE, 5
	@ Ten Gauntlets: the rival heads for the Frontier too (their rematch waits
	@ at the Battle Tower door) - gone from the lab from here on.
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_OLDALE_TOWN_STATE, 1
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
	setvar VAR_LITTLEROOT_TOWN_STATE, 3
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayDemandsAnswers::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayDemandsAnswers, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanDemandsAnswers::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanDemandsAnswers, MSGBOX_DEFAULT
	return

@ Ten Gauntlets: no longer hands over 5 POKé BALLS. The rival's last word in
@ the lab scene: it still doesn't count, and they'll see the player at the
@ Frontier for a real rematch. Nothing is given here - SCOTT hands over the
@ five starting POKeMON at his house.
LittlerootTown_ProfessorBirchsLab_EventScript_MayAnnouncesFivePokemon::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooReceivingPokemon, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanAnnouncesFivePokemon::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooReceivingPokemon, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex::
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
	goto_if_ge VAR_CROWN_STORY_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_NothingLeft
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Rival::
	lock
	faceplayer
	goto_if_ge VAR_CROWN_STORY_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_RivalAfterCrown
	goto_if_ge VAR_BIRCH_STORY_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_RivalHelping
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_PC::
	goto_if_ge VAR_CROWN_STORY_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_NothingLeft
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
	goto_if_ge VAR_CROWN_STORY_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_NothingLeft
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Book::
	goto_if_ge VAR_CROWN_STORY_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_NothingLeft
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ScottAboardSSTidalCall::
	lockall
	pokenavcall LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall
	waitmessage
	clearflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork:
	.string "Hunh? PROF. BIRCH?\p"
	.string "He's gone to meet the sponsor\n"
	.string "again. Ergo, he isn't here.\p"
	.string "He used to go out on fieldwork. I\n"
	.string "miss that.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork:
	.string "The PROF never used to be one for\n"
	.string "desk work. Now he won't leave that\l"
	.string "machine.\p"
	.string "I asked him once what it measures.\n"
	.string "He just said, “Please don't ask.”$"

LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo:
	.string "PROF. BIRCH used to study the\n"
	.string "habitats of wild POKéMON.\p"
	.string "These days it's all this bond\n"
	.string "research for our new sponsor. He\l"
	.string "barely sleeps.$"

LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon:
	.string "PROF. BIRCH: So, {PLAYER}{KUN}.\p"
	.string "I've heard so much about you from\n"
	.string "your father.\p"
	.string "I've heard that you don't have your\n"
	.string "own POKéMON yet.\p"
	.string "But the way you battled earlier,\n"
	.string "you pulled it off with aplomb!\p"
	.string "I guess you have your father's blood\n"
	.string "in your veins after all!\p"
	.string "Oh, yes. As thanks for rescuing me,\n"
	.string "I'd like you to have the POKéMON you\l"
	.string "used earlier.\p"
	.string "{PLAYER} received the {STR_VAR_1}!$"

LittlerootTown_ProfessorBirchsLab_Text_ThisOneIsSpecial:
	.string "PROF. BIRCH: Oh, and don't mind if\n"
	.string "that {STR_VAR_1} seems a little\l"
	.string "more... seasoned than you'd\l"
	.string "expect.\p"
	.string "It came to me from the BATTLE\n"
	.string "FRONTIER.\p"
	.string "I'll explain everything once\n"
	.string "you've been to see {RIVAL}.$"

LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon:
	.string "PROF. BIRCH: While you're at it, why not\n"
	.string "give a nickname to that {STR_VAR_1}?$"

LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival:
	.string "PROF. BIRCH: If you work at POKéMON\n"
	.string "and gain experience, I think you'll make\l"
	.string "an extremely good TRAINER.\p"
	.string "My kid, {RIVAL}, is also studying\n"
	.string "POKéMON while helping me out.\p"
	.string "{PLAYER}{KUN}, don't you think it might be\n"
	.string "a good idea to go see {RIVAL}?$"

LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou:
	.string "PROF. BIRCH: Great!\n"
	.string "{RIVAL} should be happy, too.\p"
	.string "Get {RIVAL} to teach you what it\n"
	.string "means to be a TRAINER.$"

LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay:
	.string "PROF. BIRCH: Oh, don't be that way.\n"
	.string "You should go meet my kid.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome:
	.string "PROF. BIRCH: {RIVAL}? Off at the\n"
	.string "FRONTIER, I think.\p"
	.string "...I do wish they'd stay home.$"

LittlerootTown_ProfessorBirchsLab_Text_MayDemandsAnswers:
	.string "MAY: Dad! {PLAYER}{KUN}'s POKéMON is\n"
	.string "level 50! Mine was level 5!\p"
	.string "Explain. Right now.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanDemandsAnswers:
	.string "BRENDAN: Dad! {PLAYER}'s POKéMON is\n"
	.string "level 50! Mine was level 5!\p"
	.string "You'd better have a good\n"
	.string "explanation.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchExplainsLevelCap:
	.string "PROF. BIRCH: Ha ha... so you found\n"
	.string "out the hard way. Sorry about\l"
	.string "that, {RIVAL}.\p"
	.string "That POKéMON was built for the\n"
	.string "BATTLE FRONTIER. SCOTT has rebuilt\l"
	.string "it into something new: the EIGHT\l"
	.string "GAUNTLETS.\p"
	.string "Eight gauntlets of battles, each\n"
	.string "one tougher than the last.\p"
	.string "Out there, every POKéMON battles\n"
	.string "at level 50. No more, no less.\l"
	.string "Nobody wins by grinding levels.\p"
	.string "You win with the team you build.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchExplainsLMenu:
	.string "PROF. BIRCH: So a TRAINER needs\n"
	.string "another way to improve their\l"
	.string "POKéMON. That's where your POKéNAV\l"
	.string "comes in.\p"
	.string "Press the L Button any time. You\n"
	.string "can edit stats, change natures and\l"
	.string "Hidden Power types, relearn moves,\l"
	.string "teach egg moves and TMs, and\l"
	.string "switch abilities.\p"
	.string "That {STR_VAR_1} of yours, {PLAYER}{KUN}?\n"
	.string "It came from the FRONTIER, and I\l"
	.string "finished building it with that\l"
	.string "very menu. That's why it was\l"
	.string "already level 50.$"

LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex:
	.string "PROF. BIRCH: Oh, and {PLAYER}{KUN}, take\n"
	.string "this, too.\p"
	.string "It keeps a record of every POKéMON\n"
	.string "you meet. You'll be meeting\l"
	.string "plenty.$"

LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex:
	.string "{PLAYER} received the POKéDEX!$"

LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex:
	.string "PROF. BIRCH: The POKéDEX is a high-tech\n"
	.string "tool that automatically makes a record\l"
	.string "of any POKéMON you meet or catch.\p"
	.string "My kid, {RIVAL}, goes everywhere\n"
	.string "with it.\p"
	.string "Whenever my kid catches a rare POKéMON\n"
	.string "and records its data in the POKéDEX,\l"
	.string "why, {RIVAL} looks for me while I'm out\l"
	.string "doing fieldwork, and shows me.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchOffersFrontierChallenge:
	.string "PROF. BIRCH: One more thing. Take\n"
	.string "a look in your BADGE case.\p"
	.string "I talked with every GYM LEADER in\n"
	.string "HOENN. A TRAINER headed for the\l"
	.string "FRONTIER shouldn't have to prove\l"
	.string "themselves eight times over first.\p"
	.string "So all eight BADGES are already\n"
	.string "yours. With them, any POKéMON will\l"
	.string "obey you, however strong it is.\p"
	.string "SCOTT runs the FRONTIER. Pay him a\n"
	.string "visit when you arrive. He has five\l"
	.string "more POKéMON waiting for you,\l"
	.string "built the same way.\p"
	.string "Here's your ticket. The ferry\n"
	.string "leaves from the dock on ROUTE 103.$"

LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait:
	.string "PROF. BIRCH: Oh... {PLAYER}{KUN}. How\n"
	.string "are the gauntlets?\p"
	.string "Good. That's good. Just... keep\n"
	.string "winning, all right?\p"
	.string "...Don't mind me. I haven't been\n"
	.string "sleeping much.$"

LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooReceivingPokemon:
	.string "MAY: Okay. Fine. I get it now.\p"
	.string "...It still doesn't count, though.\p"
	.string "Once I've built a real team, I'm\n"
	.string "coming to the FRONTIER, too.\p"
	.string "Then we have a real rematch,\n"
	.string "{PLAYER}{KUN}. Same level. No tricks.$"

LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext:
	.string "MAY: I wonder where I should go look\n"
	.string "for POKéMON next?$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooReceivingPokemon:
	.string "BRENDAN: ...Fine. I get it now.\p"
	.string "That still doesn't count, though.\p"
	.string "Once I've built a real team, I'm\n"
	.string "heading to the FRONTIER, too.\p"
	.string "Then we settle this for real,\n"
	.string "{PLAYER}. Same level. No tricks.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext:
	.string "BRENDAN: Where should I look for\n"
	.string "POKéMON next…$"

LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine:
	.string "It's a serious-looking machine. A\n"
	.string "sticker on the side reads:\l"
	.string "PROPERTY OF DEVON CORPORATION.$"

LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch:
	.string "It's a PC used for research.\n"
	.string "Better not mess around with it.$"

LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon:
	.string "It's crammed with books on POKéMON.$"

LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead:
	.string "It's a book that's too hard to read.$"

LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational:
	.string "PROF. BIRCH: Now…\p"
	.string "{PLAYER}{KUN} and {RIVAL}, I've had the two\n"
	.string "of you help me study POKéMON.\p"
	.string "Thanks to your help, new facts\n"
	.string "are coming to light.\p"
	.string "It appears that in the HOENN region,\n"
	.string "there are also POKéMON from other\l"
	.string "regions.\p"
	.string "It goes to show how rich and varied\n"
	.string "the natural environments of HOENN\l"
	.string "happen to be.\p"
	.string "That's why I think it's necessary for\n"
	.string "me to upgrade your POKéDEX to\l"
	.string "the NATIONAL Mode.\p"
	.string "Here, let me see your POKéDEX units.$"

LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool:
	.string "MAY: Eheheh!\p"
	.string "It's so cool that even my POKéDEX\n"
	.string "is getting updated!\p"
	.string "It's because you went out and caught\n"
	.string "so many POKéMON, {PLAYER}{KUN}!$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe:
	.string "BRENDAN: I went out all over HOENN\n"
	.string "and checked out POKéMON.\p"
	.string "You can thank me for getting\n"
	.string "the NATIONAL Mode POKéDEX.\p"
	.string "Yep, you're lucky, {PLAYER}!$"

LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone:
	.string "PROF. BIRCH: Okay, all done!$"

LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational:
	.string "{PLAYER}'s POKéDEX was upgraded\n"
	.string "to the NATIONAL Mode!$"

LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2:
	.string "PROF. BIRCH: But listen.\n"
	.string "You've become the CHAMPION,\l"
	.string "but your POKéMON journey isn't over.\p"
	.string "There is no end to the road\n"
	.string "that is POKéMON.\p"
	.string "Somewhere, there is a grassy patch\n"
	.string "that's waiting for you!$"

LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork:
	.string "MAY: I think I'll take a short break\n"
	.string "from fieldwork.\p"
	.string "I think I'll help the PROF here for\n"
	.string "a while.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork:
	.string "BRENDAN: For the time being,\n"
	.string "I'm taking a break from fieldwork.\p"
	.string "I'll be helping out the PROF here\n"
	.string "for a while.$"

LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon:
	.string "PROF. BIRCH: Oh, {PLAYER}{KUN}!\n"
	.string "Let's have a look at your POKéDEX.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Yes, there's no doubt about it.\p"
	.string "You really have completed the HOENN\n"
	.string "region's POKéDEX.\p"
	.string "That's more than just impressive.\p"
	.string "I have a gift for you.\p"
	.string "Consider it my show of appreciation\n"
	.string "for the fantastic work you've done.\p"
	.string "My gift is a rare POKéMON only found\n"
	.string "in another region!\p"
	.string "You can have any one of these\n"
	.string "three POKéMON!$"

LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon:
	.string "PROF. BIRCH: These are rare POKéMON\n"
	.string "only found in another region!\p"
	.string "You can have any one of these\n"
	.string "three POKéMON!$"

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil:
	.string "PROF. BIRCH: The FIRE POKéMON\n"
	.string "CYNDAQUIL caught your eye!\p"
	.string "You're as sharp as ever!\p"
	.string "So the CYNDAQUIL is your choice?$"

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile:
	.string "PROF. BIRCH: The WATER POKéMON\n"
	.string "TOTODILE is your choice!\p"
	.string "You know how to pick a good one.\p"
	.string "So, you'll take the TOTODILE?$"

LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita:
	.string "PROF. BIRCH: The GRASS POKéMON\n"
	.string "CHIKORITA is your choice!\p"
	.string "You sure know what you're doing.\p"
	.string "So, you'll take the CHIKORITA?$"

LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable:
	.string "PROF. BIRCH: Take your time before\n"
	.string "you decide.\p"
	.string "They're all invaluable POKéMON.$"

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_PickedFinePokemon:
	.string "PROF. BIRCH: I see!\n"
	.string "You picked a fine POKéMON!$"

LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter:
	.string "{PLAYER} received the {STR_VAR_1}\n"
	.string "from PROF. BIRCH!$"

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_NicknameJohtoStarter:
	.string "Want to give a nickname to\n"
	.string "the {STR_VAR_1} you received?$"

LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting:
	.string "PROF. BIRCH: Listen, {PLAYER}{KUN}.\n"
	.string "You've completed the HOENN POKéDEX,\l"
	.string "but your POKéMON journey isn't over.\p"
	.string "There is no end to the road\n"
	.string "that is POKéMON.\p"
	.string "Somewhere, there is a grassy patch\n"
	.string "that's waiting for you!$"

LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone:
	.string "You received the promised POKéMON.\n"
	.string "Better leave the others alone.$"

@ Unused
LittlerootTown_ProfessorBirchsLab_Text_DontHaveAnyRoomForPokemon:
	.string "Oh, you don't have any room for\n"
	.string "this POKéMON.$"

LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere:
	.string "MAY: {PLAYER}{KUN}, after this…\n"
	.string "What are you going to do?\p"
	.string "Are you going to keep battling\n"
	.string "and sharpening your skills?\p"
	.string "Or are you going to try filling\n"
	.string "the NATIONAL POKéDEX?\p"
	.string "I'm staying here to help the PROF.$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly:
	.string "BRENDAN: Rather than collecting\n"
	.string "POKéMON, I prefer slowly and \l"
	.string "steadily raising the one I chose.$"

LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier:
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\n"
	.string "Have you gone to that place,\l"
	.string "the BATTLE FRONTIER?$"

LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier:
	.string "BRENDAN: Hey, {PLAYER}!\n"
	.string "Have you gone out to that place,\l"
	.string "the BATTLE FRONTIER?$"

LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "SCOTT: Hi, hi, {PLAYER}!\n"
	.string "It's me, SCOTT.\p"
	.string "I'm aboard the S.S. TIDAL now.\n"
	.string "It feels great to be on the sea!\p"
	.string "By the way…\p"
	.string "There's this place that I'd like to\n"
	.string "invite you to for a visit.\p"
	.string "If you're interested, board a ferry\n"
	.string "at either SLATEPORT or LILYCOVE.\p"
	.string "I'll fill you in on the details when\n"
	.string "we meet. I'll be waiting!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

LittlerootTown_ProfessorBirchsLab_Text_BirchGivesPokenav:
	.string "PROF. BIRCH: And this came\n"
	.string "straight from DEVON: their newest\l"
	.string "POKéNAV.\p"
	.string "It heals your POKéMON after every\n"
	.string "battle, all on its own. Every\l"
	.string "TRAINER at the FRONTIER carries\l"
	.string "one.$"

LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokenav:
	.string "{PLAYER} received the POKéNAV!$"

@ Ten Gauntlets: Birch's lab arc, after gauntlet 5 (storyline.md;
@ VAR_BIRCH_STORY_STATE, see BattleFrontier_OutsideWest). At state 2,
@ PRESIDENT STONE faces BIRCH by the POKé BALL machine with two men in suits
@ behind him, and WALLACE stands a few tiles back at (5, 10). The scene
@ plays as soon as the player comes in: they always arrive on the left mat
@ tile (6, 12) and walk straight up to (6, 10), beside WALLACE. From state 4
@ the rival helps out in the lab.
LittlerootTown_ProfessorBirchsLab_EventScript_SetupBirchStory::
	setvar VAR_TEMP_2, 1
	@ STONE, his two men and WALLACE (FLAG_TEMP_1-4) are only here for the
	@ scene. Temp flags start clear on every visit, so hide them first.
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	goto_if_ge VAR_BIRCH_STORY_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_RivalAtLab
	goto_if_ne VAR_BIRCH_STORY_STATE, 2, Common_EventScript_NopReturn
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_4
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setobjectxyperm LOCALID_BIRCHS_LAB_BIRCH, 9, 6
	setobjectmovementtype LOCALID_BIRCHS_LAB_BIRCH, MOVEMENT_TYPE_FACE_DOWN
	setobjectxyperm LOCALID_BIRCHS_LAB_AIDE, 2, 10
	setobjectmovementtype LOCALID_BIRCHS_LAB_AIDE, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_TEMP_2, 0
	return

LittlerootTown_ProfessorBirchsLab_EventScript_RivalAtLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 5, 10
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
	return

LittlerootTown_ProfessorBirchsLab_EventScript_StoneScene::
	lockall
	setvar VAR_TEMP_2, 1
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerToWallace
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_StoneScene1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_STONE, Common_Movement_FaceDown
	applymovement LOCALID_BIRCHS_LAB_SUIT_1, Common_Movement_FaceDown
	applymovement LOCALID_BIRCHS_LAB_SUIT_2, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_BIRCHS_LAB_STONE, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_StoneScene2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_STONE, Common_Movement_FaceUp
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_StoneScene3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_SUIT_2, LittlerootTown_ProfessorBirchsLab_Movement_LeaveFromRight
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ExitSound
	removeobject LOCALID_BIRCHS_LAB_SUIT_2
	applymovement LOCALID_BIRCHS_LAB_STONE, LittlerootTown_ProfessorBirchsLab_Movement_StoneLeaves
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ExitSound
	removeobject LOCALID_BIRCHS_LAB_STONE
	applymovement LOCALID_BIRCHS_LAB_SUIT_1, LittlerootTown_ProfessorBirchsLab_Movement_LeaveFromLeft
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ExitSound
	removeobject LOCALID_BIRCHS_LAB_SUIT_1
	delay 20
	applymovement LOCALID_BIRCHS_LAB_WALLACE, LittlerootTown_ProfessorBirchsLab_Movement_WallaceToBirch
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_StoneScene4, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_WALLACE, LittlerootTown_ProfessorBirchsLab_Movement_WallaceLeaves
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ExitSound
	removeobject LOCALID_BIRCHS_LAB_WALLACE
	setvar VAR_BIRCH_STORY_STATE, 3
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_ExitSound::
	playse SE_EXIT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_AideStayOut::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_AideStayOut, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_BirchEverythingFine::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchEverythingFine, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_RivalHelping::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_RivalHelping, MSGBOX_DEFAULT
	release
	end

@ From the mat (6, 12) to (6, 10), beside WALLACE at (5, 10).
LittlerootTown_ProfessorBirchsLab_Movement_PlayerToWallace:
	walk_up
	walk_up
	face_up
	step_end

@ Out down the x 10 column, along row 11 below the player, onto the mat.
LittlerootTown_ProfessorBirchsLab_Movement_LeaveFromRight:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_StoneLeaves:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_LeaveFromLeft:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_WallaceToBirch:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	face_up
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_WallaceLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

LittlerootTown_ProfessorBirchsLab_Text_StoneScene1:
	.string "PROF. BIRCH: We had a deal! Better\n"
	.string "equipment for my lab, and in\l"
	.string "return I'd send the kids to SCOTT.\p"
	.string "PRESIDENT STONE: The deal also\n"
	.string "included finding out whether the\l"
	.string "CROWN will actually work,\l"
	.string "PROFESSOR.\p"
	.string "PROF. BIRCH: It's never been done\n"
	.string "before! A few weeks isn't nearly\l"
	.string "enough to know for sure.\p"
	.string "PRESIDENT STONE: I can buy you\n"
	.string "more time. But not much.\p"
	.string "That child is progressing far\n"
	.string "faster than any of us imag...$"

LittlerootTown_ProfessorBirchsLab_Text_StoneScene2:
	.string "PRESIDENT STONE: Well. It seems we\n"
	.string "have visitors.\p"
	.string "And quite an important one, too.$"

LittlerootTown_ProfessorBirchsLab_Text_StoneScene3:
	.string "PRESIDENT STONE: Do remember our\n"
	.string "confidentiality agreement,\l"
	.string "PROFESSOR.\p"
	.string "It would be such a shame if\n"
	.string "anything were to happen to this\l"
	.string "precious laboratory of yours.$"

LittlerootTown_ProfessorBirchsLab_Text_StoneScene4:
	.string "WALLACE: PROFESSOR, are you all\n"
	.string "right? What is going on here?\p"
	.string "PROF. BIRCH: I'm fine. Really, I'm\n"
	.string "fine.\p"
	.string "All I can tell you is that I\n"
	.string "agreed to help DEVON with some\l"
	.string "research into Mega Evolution. In\l"
	.string "exchange, they upgraded my\l"
	.string "equipment.\p"
	.string "I'm afraid I can't say much more\n"
	.string "than that.\p"
	.string "But it's nothing to worry about.\n"
	.string "What they want simply isn't\l"
	.string "possible.\p"
	.string "I just need some time to prove it,\n"
	.string "and then they'll get off my back.\p"
	.string "WALLACE: Be careful, PROFESSOR.\n"
	.string "And keep me in the loop.$"

LittlerootTown_ProfessorBirchsLab_Text_AideStayOut:
	.string "The PROFESSOR told me to stay out\n"
	.string "of it...$"

LittlerootTown_ProfessorBirchsLab_Text_BirchEverythingFine:
	.string "PROF. BIRCH: Oh, {PLAYER}! Don't\n"
	.string "you worry about all that.\l"
	.string "Everything's fine, honestly.\p"
	.string "Just a business matter.\p"
	.string "More importantly, how are the\n"
	.string "gauntlets treating you? I do hope\l"
	.string "you're having fun out there!$"

LittlerootTown_ProfessorBirchsLab_Text_RivalHelping:
	.string "{RIVAL}: Dad says everything's\n"
	.string "fine. He keeps saying it, anyway.\p"
	.string "I'm sticking around to help out\n"
	.string "until I'm sure.$"

@ ============================================================================
@ Ten Gauntlets: the Crown is taken, after gauntlet 7 (storyline.md;
@ VAR_CROWN_STORY_STATE is explained in LittlerootTown). From the raid on,
@ the lab is bare (OnLoad) and the aide is gone. At state 4 BIRCH stands
@ alone in the middle, and the confession plays as soon as the player comes
@ in (always on the left mat tile, (6, 12)): they walk up to him, the rival
@ runs in beside them, and STEVEN walks in partway through. From state 5,
@ BIRCH and the rival stay in the empty lab.
@ ============================================================================

LittlerootTown_ProfessorBirchsLab_EventScript_SetupCrownStory::
	clearflag FLAG_HIDE_CROWN_STORY_LAB_AIDE
	goto_if_lt VAR_CROWN_STORY_STATE, 2, Common_EventScript_NopReturn
	setflag FLAG_HIDE_CROWN_STORY_LAB_AIDE
	goto_if_lt VAR_CROWN_STORY_STATE, 4, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setobjectxyperm LOCALID_BIRCHS_LAB_BIRCH, 6, 6
	setobjectmovementtype LOCALID_BIRCHS_LAB_BIRCH, MOVEMENT_TYPE_FACE_DOWN
	goto_if_ge VAR_CROWN_STORY_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_CrownRivalStays
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 7, 12
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_FACE_UP
	setvar VAR_TEMP_3, 1
	return

LittlerootTown_ProfessorBirchsLab_EventScript_CrownRivalStays::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 7, 6
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_FACE_LEFT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_Confession::
	lockall
	setvar VAR_TEMP_3, 0
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerToBirch
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession1, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	addobject LOCALID_BIRCHS_LAB_RIVAL
	applymovement LOCALID_BIRCHS_LAB_RIVAL, LittlerootTown_ProfessorBirchsLab_Movement_RivalRunsIn
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession2, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	clearflag FLAG_TEMP_5
	addobject LOCALID_BIRCHS_LAB_STEVEN
	applymovement LOCALID_BIRCHS_LAB_STEVEN, LittlerootTown_ProfessorBirchsLab_Movement_StevenWalksIn
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession4, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_FaceRight
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession5, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_FaceDown
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession6, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_STEVEN, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Confession7, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCHS_LAB_STEVEN, LittlerootTown_ProfessorBirchsLab_Movement_StevenLeaves
	waitmovement 0
	call LittlerootTown_ProfessorBirchsLab_EventScript_ExitSound
	removeobject LOCALID_BIRCHS_LAB_STEVEN
	setvar VAR_CROWN_STORY_STATE, 5
	releaseall
	end

LittlerootTown_ProfessorBirchsLab_EventScript_BirchAfterCrown::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchAfterCrown, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_RivalAfterCrown::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_RivalAfterCrown, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_NothingLeft::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_NothingLeft, MSGBOX_SIGN
	end

@ From the mat (6, 12) up to (6, 7), just below BIRCH at (6, 6).
LittlerootTown_ProfessorBirchsLab_Movement_PlayerToBirch:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

@ From the right mat tile (7, 12) up to (7, 7), beside the player.
LittlerootTown_ProfessorBirchsLab_Movement_RivalRunsIn:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_up
	step_end

@ From the left mat tile (6, 12) round to (5, 7), on the player's other side.
LittlerootTown_ProfessorBirchsLab_Movement_StevenWalksIn:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	face_right
	step_end

LittlerootTown_ProfessorBirchsLab_Movement_StevenLeaves:
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	set_invisible
	step_end

LittlerootTown_ProfessorBirchsLab_Text_Confession1:
	.string "PROF. BIRCH: {PLAYER}...\p"
	.string "They took everything. The\n"
	.string "machines, the books, my research.\l"
	.string "Every last bit of it.\p"
	.string "After all I did for DEVON and\n"
	.string "SCOTT... After every threat, I did\l"
	.string "exactly what they asked.\p"
	.string "And in return, they ransacked my\n"
	.string "lab.$"

LittlerootTown_ProfessorBirchsLab_Text_Confession2:
	.string "{RIVAL}: Dad! Are you okay?!\p"
	.string "PROF. BIRCH: Yes... I'm all right.\n"
	.string "Thanks to {PLAYER}.\p"
	.string "I don't know what they had planned\n"
	.string "for me. Probably the worst.\p"
	.string "...I need to come clean. To both\n"
	.string "of you.\p"
	.string "I've been researching the\n"
	.string "possibility of permanent MEGA\l"
	.string "EVOLUTION. POKéMON that stay Mega\l"
	.string "Evolved, for good.\p"
	.string "SCOTT came to me with the idea. A\n"
	.string "new mechanic, to trial at the\l"
	.string "FRONTIER. At first, I agreed to\l"
	.string "help.\p"
	.string "DEVON delivered a device they\n"
	.string "called the CROWN.\p"
	.string "They claimed it could turn bond\n"
	.string "energy into Mega energy. And with\l"
	.string "enough of it concentrated, a MEGA\l"
	.string "EVOLUTION could be made permanent.$"

LittlerootTown_ProfessorBirchsLab_Text_Confession3:
	.string "PROF. BIRCH: ...STEVEN.\p"
	.string "STEVEN: Please, Professor. Go on.\n"
	.string "I think I need to hear this too.$"

LittlerootTown_ProfessorBirchsLab_Text_Confession4:
	.string "PROF. BIRCH: In the spirit of\n"
	.string "pushing the limits of POKéMON, I\l"
	.string "agreed to tune the CROWN to bond\l"
	.string "energy.\p"
	.string "I told them it would need a great\n"
	.string "deal of it. They said they'd\l"
	.string "handle that part.\p"
	.string "Not long after, the EIGHT\n"
	.string "GAUNTLETS opened, and trainers\l"
	.string "came from all over.\p"
	.string "A few weeks in, SCOTT and\n"
	.string "PRESIDENT STONE paid me another\l"
	.string "visit.\p"
	.string "They were harvesting bond energy\n"
	.string "at the FRONTIER, they said, but it\l"
	.string "was “moving slower than expected.”\p"
	.string "They needed someone to push the\n"
	.string "limits hard.\p"
	.string "So they handed me the counterfeit\n"
	.string "badges. “Give these to NORMAN's\l"
	.string "kid when they're ready. A kid like\l"
	.string "NORMAN's shows real promise.”\p"
	.string "The badges would speed up the\n"
	.string "harvest. I pushed back.\p"
	.string "That's when the threats began.$"

LittlerootTown_ProfessorBirchsLab_Text_Confession5:
	.string "PROF. BIRCH: {RIVAL}... They\n"
	.string "threatened you.\p"
	.string "So I gave you both the badges, and\n"
	.string "I sent you off to the FRONTIER.$"

LittlerootTown_ProfessorBirchsLab_Text_Confession6:
	.string "PROF. BIRCH: And there's more I\n"
	.string "kept from you.\p"
	.string "{PLAYER}, your first POKéMON came\n"
	.string "from SCOTT. Every FRONTIER POKéMON\l"
	.string "carries a chip of shard material.\l"
	.string "Yours too.\p"
	.string "The chips are real. That's why\n"
	.string "your POKéMON never grow.\p"
	.string "And the menu I gave you... I built\n"
	.string "it so trainers could put the power\l"
	.string "back by hand, and never notice\l"
	.string "their POKéMON had stopped growing.\p"
	.string "Today, NOLAND and GRETA came asking\n"
	.string "for an update.\p"
	.string "I had found a way to make it work.\n"
	.string "But it needs an enormous amount of\l"
	.string "power.\p"
	.string "I shared my research. They called\n"
	.string "SCOTT with the news...\p"
	.string "Then they told me my job was done,\n"
	.string "and that they'd “handle me later.”\p"
	.string "They knocked me out, and took\n"
	.string "everything. The CROWN included.\p"
	.string "I'm so sorry. Both of you.\p"
	.string "{RIVAL}: It's okay, Dad.\p"
	.string "We're working with STEVEN and\n"
	.string "WALLACE. We're going to make this\l"
	.string "right.$"

LittlerootTown_ProfessorBirchsLab_Text_Confession7:
	.string "STEVEN: It all makes sense now.\p"
	.string "An enormous amount of power...\n"
	.string "There's only one place on that\l"
	.string "island that could supply it.\p"
	.string "The FACTORY. MEGA STONE ore in the\n"
	.string "walls, and whatever DEVON has built\l"
	.string "inside.\p"
	.string "A permanent MEGA EVOLUTION... The\n"
	.string "raw power of a MEGA, and the item\l"
	.string "slot free on top of it.\p"
	.string "SCOTT means to keep that power for\n"
	.string "himself.\p"
	.string "{PLAYER}, go and check on your\n"
	.string "family. I'll stay close.$"

LittlerootTown_ProfessorBirchsLab_Text_BirchAfterCrown:
	.string "PROF. BIRCH: Empty, isn't it?\n"
	.string "Years of work, gone in an\l"
	.string "afternoon.\p"
	.string "But you're both safe. That's what\n"
	.string "matters.\p"
	.string "Be careful, {PLAYER}.$"

LittlerootTown_ProfessorBirchsLab_Text_RivalAfterCrown:
	.string "{RIVAL}: I'm staying with Dad.\p"
	.string "{PLAYER}... Whatever SCOTT is\n"
	.string "planning, stop him. For all of us.$"

LittlerootTown_ProfessorBirchsLab_Text_NothingLeft:
	.string "There's nothing left here.$"
