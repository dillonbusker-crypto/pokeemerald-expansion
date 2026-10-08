RusturfTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RusturfTunnel_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RusturfTunnel_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RusturfTunnel_OnWarp
	.byte 0

RusturfTunnel_OnWarp:
	map_script_2 VAR_TEMP_4, 0, RusturfTunnel_EventScript_FaceNorth
	.2byte 0

RusturfTunnel_EventScript_FaceNorth::
	setvar VAR_TEMP_4, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

RusturfTunnel_OnFrame:
	map_script_2 VAR_GIRATINA_EVENT, 1, RusturfTunnel_EventScript_FirstEntry
	map_script_2 VAR_RUSTURF_TUNNEL_STATE, 4, RusturfTunnel_EventScript_ClearTunnelScene
	map_script_2 VAR_RUSTURF_TUNNEL_STATE, 5, RusturfTunnel_EventScript_ClearTunnelScene
	.2byte 0

RusturfTunnel_OnTransition:
	call_if_eq VAR_RUSTURF_TUNNEL_STATE, 2, RusturfTunnel_EventScript_SetAquaGruntAndPeekoPos
	call_if_ge VAR_ENDGAME_STATE, 10, RusturfTunnel_EventScript_SetupEndgame
	end

RusturfTunnel_EventScript_SetAquaGruntAndPeekoPos::
	setobjectxyperm LOCALID_RUSTURF_TUNNEL_PEEKO, 13, 4
	setobjectxyperm LOCALID_RUSTURF_TUNNEL_GRUNT, 13, 5
	return

RusturfTunnel_EventScript_Wanda::
	lock
	faceplayer
	msgbox RusturfTunnel_Text_BoyfriendOnOtherSideOfRock, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RusturfTunnel_EventScript_WandasBoyfriend::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_1, RusturfTunnel_EventScript_AlreadySpokenTo
	setflag FLAG_TEMP_1
	msgbox RusturfTunnel_Text_WhyCantTheyKeepDigging, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RusturfTunnel_EventScript_AlreadySpokenTo::
	msgbox RusturfTunnel_Text_ToGetToVerdanturf, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RusturfTunnel_EventScript_ClearTunnelScene::
	lockall
	call_if_eq VAR_TEMP_1, 1, RusturfTunnel_EventScript_FaceWandasBoyfriend1
	call_if_eq VAR_TEMP_1, 2, RusturfTunnel_EventScript_FaceWandasBoyfriend2
	call_if_eq VAR_TEMP_1, 3, RusturfTunnel_EventScript_FaceWandasBoyfriend3
	call RusturfTunnel_EventScript_WandasBoyfriendNotice
	msgbox RusturfTunnel_Text_YouShatteredBoulderTakeHM, MSGBOX_DEFAULT
	call_if_eq VAR_TEMP_1, 2, RusturfTunnel_EventScript_WandasBoyfriendApproachPlayer
	call_if_eq VAR_TEMP_1, 3, RusturfTunnel_EventScript_WandasBoyfriendApproachPlayer
	giveitem ITEM_HM_STRENGTH
	setflag FLAG_RECEIVED_HM_STRENGTH
	msgbox RusturfTunnel_Text_ExplainStrength, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_1, 1, RusturfTunnel_EventScript_BoyfriendApproachWanda1
	call_if_eq VAR_TEMP_1, 2, RusturfTunnel_EventScript_BoyfriendApproachWanda2
	call_if_eq VAR_TEMP_1, 3, RusturfTunnel_EventScript_BoyfriendApproachWanda3
	msgbox RusturfTunnel_Text_WandaReunion, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_1, 1, RusturfTunnel_EventScript_WandaAndBoyfriendExit1
	call_if_eq VAR_TEMP_1, 2, RusturfTunnel_EventScript_WandaAndBoyfriendExit
	call_if_eq VAR_TEMP_1, 3, RusturfTunnel_EventScript_WandaAndBoyfriendExit
	call RusturfTunnel_EventScript_SetRusturfTunnelOpen
	releaseall
	end

RusturfTunnel_EventScript_BoyfriendApproachWanda1::
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PlayerWatchBoyfriend1
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_BoyfriendApproachWanda1
	waitmovement 0
	return

RusturfTunnel_EventScript_BoyfriendApproachWanda2::
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PlayerWatchBoyfriend
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_BoyfriendApproachWanda
	waitmovement 0
	applymovement LOCALID_RUSTURF_TUNNEL_WANDA, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

RusturfTunnel_EventScript_BoyfriendApproachWanda3::
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PlayerWatchBoyfriend
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_BoyfriendApproachWanda
	waitmovement 0
	applymovement LOCALID_RUSTURF_TUNNEL_WANDA, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

RusturfTunnel_EventScript_FaceWandasBoyfriend1::
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

RusturfTunnel_EventScript_FaceWandasBoyfriend2::
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_BoyfriendFaceRight
	waitmovement 0
	return

RusturfTunnel_EventScript_FaceWandasBoyfriend3::
	return

RusturfTunnel_EventScript_WandasBoyfriendApproachPlayer::
	closemessage
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_WandasBoyfriendApproachPlayer
	waitmovement 0
	return

RusturfTunnel_EventScript_WandaAndBoyfriendExit1::
	applymovement LOCALID_RUSTURF_TUNNEL_WANDA, RusturfTunnel_Movement_WandaExit1
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_WandasBoyfriendExit1
	waitmovement 0
	return

RusturfTunnel_EventScript_WandaAndBoyfriendExit::
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PlayerWatchWandaExit
	applymovement LOCALID_RUSTURF_TUNNEL_WANDA, RusturfTunnel_Movement_WandaExit
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, RusturfTunnel_Movement_WandasBoyfriendExit
	waitmovement 0
	return

RusturfTunnel_EventScript_WandasBoyfriendNotice::
	playse SE_PIN
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RUSTURF_TUNNEL_WANDAS_BF, Common_Movement_Delay48
	waitmovement 0
	return

RusturfTunnel_Movement_WandaExit1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_WandaExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_PlayerWatchWandaExit:
	delay_8
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

RusturfTunnel_Movement_Unused1:
	walk_left
	walk_in_place_faster_right
	step_end

RusturfTunnel_Movement_Unused2:
	walk_down
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	step_end

RusturfTunnel_Movement_Unused3:
	walk_up
	walk_in_place_faster_down
	delay_8
	walk_in_place_faster_right
	step_end

RusturfTunnel_Movement_PlayerWatchBoyfriend1:
	walk_left
	walk_in_place_faster_right
	step_end

RusturfTunnel_Movement_PlayerWatchBoyfriend:
	walk_right
	walk_in_place_faster_left
	step_end

RusturfTunnel_Movement_BoyfriendFaceRight:
	walk_up
	walk_in_place_faster_right
	step_end

RusturfTunnel_Movement_WandasBoyfriendExit1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_WandasBoyfriendExit:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_WandasBoyfriendApproachPlayer:
	walk_right
	step_end

RusturfTunnel_Movement_BoyfriendApproachWanda1:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_fast_up
	walk_fast_right
	step_end

RusturfTunnel_Movement_BoyfriendApproachWanda:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_fast_right
	walk_in_place_faster_up
	step_end

RusturfTunnel_EventScript_TunnelBlockagePos1::
	setvar VAR_TEMP_1, 1
	end

RusturfTunnel_EventScript_TunnelBlockagePos2::
	setvar VAR_TEMP_1, 2
	end

RusturfTunnel_EventScript_TunnelBlockagePos3::
	setvar VAR_TEMP_1, 3
	end

RusturfTunnel_EventScript_AquaGruntBackUp::
	lockall
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	msgbox RusturfTunnel_Text_ComeAndGetSome, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RUSTURF_TUNNEL_GRUNT, RusturfTunnel_Movement_GruntAndPeekoBackUp
	applymovement LOCALID_RUSTURF_TUNNEL_PEEKO, RusturfTunnel_Movement_GruntAndPeekoBackUp
	waitmovement 0
	copyobjectxytoperm LOCALID_RUSTURF_TUNNEL_GRUNT
	copyobjectxytoperm LOCALID_RUSTURF_TUNNEL_PEEKO
	setvar VAR_RUSTURF_TUNNEL_STATE, 3
	releaseall
	end

RusturfTunnel_Movement_GruntAndPeekoBackUp:
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

RusturfTunnel_EventScript_Peeko::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox RusturfTunnel_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RusturfTunnel_EventScript_Grunt::
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox RusturfTunnel_Text_GruntIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_RUSTURF_TUNNEL, RusturfTunnel_Text_GruntDefeat
	msgbox RusturfTunnel_Text_GruntTakePackage, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_PARTS
	closemessage
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PushPlayerAsideForGrunt
	applymovement LOCALID_RUSTURF_TUNNEL_GRUNT, RusturfTunnel_Movement_GruntEscape
	waitmovement 0
	removeobject LOCALID_RUSTURF_TUNNEL_GRUNT
	delay 50
	addobject LOCALID_RUSTURF_TUNNEL_BRINEY
	applymovement LOCALID_RUSTURF_TUNNEL_BRINEY, RusturfTunnel_Movement_BrineyApproachPeeko1
	waitmovement 0
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PlayerMoveAsideForBriney
	applymovement LOCALID_RUSTURF_TUNNEL_BRINEY, RusturfTunnel_Movement_BrineyApproachPeeko2
	waitmovement 0
	msgbox RusturfTunnel_Text_PeekoGladToSeeYouSafe, MSGBOX_DEFAULT
	applymovement LOCALID_RUSTURF_TUNNEL_BRINEY, Common_Movement_FacePlayer
	waitmovement 0
	message RusturfTunnel_Text_ThankYouLetsGoHomePeeko
	waitmessage
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	waitbuttonpress
	waitmoncry
	closemessage
	applymovement LOCALID_PLAYER, RusturfTunnel_Movement_PlayerWatchBrineyExit
	applymovement LOCALID_RUSTURF_TUNNEL_BRINEY, RusturfTunnel_Movement_BrineyExit
	applymovement LOCALID_RUSTURF_TUNNEL_PEEKO, RusturfTunnel_Movement_PeekoExit
	waitmovement 0
	removeobject LOCALID_RUSTURF_TUNNEL_BRINEY
	removeobject LOCALID_RUSTURF_TUNNEL_PEEKO
	clearflag FLAG_DEVON_GOODS_STOLEN
	setflag FLAG_RECOVERED_DEVON_GOODS
	setvar VAR_RUSTBORO_CITY_STATE, 4
	setvar VAR_BRINEY_HOUSE_STATE, 1
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	release
	end

RusturfTunnel_Movement_PushPlayerAsideForGrunt:
	face_down
	lock_facing_direction
	walk_up
	unlock_facing_direction
	walk_in_place_faster_left
	step_end

RusturfTunnel_Movement_PlayerMoveAsideForBriney:
	walk_down
	walk_in_place_faster_up
	step_end

RusturfTunnel_Movement_GruntEscape:
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

RusturfTunnel_Movement_BrineyApproachPeeko1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RusturfTunnel_Movement_BrineyExit:
	walk_left
	walk_left
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

RusturfTunnel_Movement_PlayerWatchBrineyExit:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_left
	step_end

RusturfTunnel_Movement_BrineyApproachPeeko2:
	delay_16
	walk_right
	step_end

RusturfTunnel_Movement_PeekoExit:
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

RusturfTunnel_EventScript_Mike::
	trainerbattle_single TRAINER_MIKE_2, RusturfTunnel_Text_MikeIntro, RusturfTunnel_Text_MikeDefeat
	msgbox RusturfTunnel_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

RusturfTunnel_Text_ComeAndGetSome:
	.string "What, are you coming?\n"
	.string "Come and get some, then!$"

RusturfTunnel_Text_Peeko:
	.string "PEEKO: Pii pihyoh!$"

RusturfTunnel_Text_GruntIntro:
	.string "Grah, keelhaul it all!\p"
	.string "That hostage POKéMON turned out to\n"
	.string "be worthless!\p"
	.string "And to think I made a getaway…\n"
	.string "In this tunnel to nowhere!\p"
	.string "Hey! You!\n"
	.string "So you want to battle me?$"

RusturfTunnel_Text_GruntDefeat:
	.string "Urrrggh! My career in crime comes to\n"
	.string "a dead end!$"

RusturfTunnel_Text_GruntTakePackage:
	.string "This is plain not right…\p"
	.string "The BOSS told me this would be a\n"
	.string "slick-and-easy job to pull.\p"
	.string "All I had to do was steal some package\n"
	.string "from DEVON.\p"
	.string "Tch!\n"
	.string "You want it back that badly, take it!$"

RusturfTunnel_Text_PeekoGladToSeeYouSafe:
	.string "PEEKO!\n"
	.string "Am I glad to see you're safe!$"

RusturfTunnel_Text_ThankYouLetsGoHomePeeko:
	.string "PEEKO owes her life to you!\p"
	.string "They call me MR. BRINEY.\n"
	.string "And, you are?\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Ah, so you are {PLAYER}{KUN}!\n"
	.string "I sincerely thank you!\p"
	.string "Now, if there's anything that troubles\n"
	.string "you, don't hesitate to tell me!\p"
	.string "You can usually find me in my cottage\n"
	.string "by the sea near PETALBURG WOODS.\p"
	.string "Come, PEEKO, we should make our way\n"
	.string "home.\p"
	.string "PEEKO: Pihyoh!$"

RusturfTunnel_Text_WhyCantTheyKeepDigging:
	.string "… …\p"
	.string "Why can't they keep digging?\n"
	.string "Is the bedrock too hard?\p"
	.string "My beloved awaits me in VERDANTURF\n"
	.string "TOWN just beyond here…\p"
	.string "If RUSTBORO and VERDANTURF were\n"
	.string "joined by this tunnel, I could visit\l"
	.string "her every day…\p"
	.string "But this…\n"
	.string "What am I to do?$"

RusturfTunnel_Text_ToGetToVerdanturf:
	.string "To get from RUSTBORO to VERDANTURF,\n"
	.string "you need to go to DEWFORD, then pass\l"
	.string "through SLATEPORT and MAUVILLE…$"

RusturfTunnel_Text_YouShatteredBoulderTakeHM:
	.string "Wow! You shattered that boulder\n"
	.string "blocking the way.\p"
	.string "To show you how much I appreciate it,\n"
	.string "I'd like you to have this HM.$"

RusturfTunnel_Text_ExplainStrength:
	.string "That HM contains STRENGTH.\p"
	.string "If a muscular POKéMON were to learn\n"
	.string "that, it would be able to move even\l"
	.string "large boulders.$"

RusturfTunnel_Text_WandaReunion:
	.string "WANDA!\n"
	.string "Now I can see you anytime!\p"
	.string "WANDA: That's…wonderful.\p"
	.string "Please, take some rest at my home.$"

RusturfTunnel_Text_BoyfriendOnOtherSideOfRock:
	.string "On the other side of this rock…\n"
	.string "My boyfriend is there.\p"
	.string "He… He's not just digging the tunnel\n"
	.string "to come see me.\p"
	.string "He works his hands raw and rough\n"
	.string "for the benefit of everyone.$"

RusturfTunnel_Text_MikeIntro:
	.string "What do you call a wild man up in the\n"
	.string "mountains? A mountain man, right?\p"
	.string "So why don't they call a POKéMON in\n"
	.string "the mountains a mountain POKéMON?$"

RusturfTunnel_Text_MikeDefeat:
	.string "My POKéMON…\n"
	.string "Ran out of power…$"

RusturfTunnel_Text_MikePostBattle:
	.string "They halted development here to\n"
	.string "protect POKéMON, right?\l"
	.string "There's a feel-good story!$"


@ Endgame setup: the vanilla people and rocks stay hidden (most are already
@ hidden from New Game; the two rocks and Hiker Mike are not), the exits all lead
@ to RUSTBORO, no fog over the dark, and the tunnel is dark until GIRATINA is
@ caught.
RusturfTunnel_EventScript_SetupEndgame::
	setflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	setflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	setflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
	setflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
	setflag FLAG_HIDE_RUSTURF_TUNNEL_BRINEY
	setflag FLAG_HIDE_RUSTURF_TUNNEL_ROCK_1
	setflag FLAG_HIDE_RUSTURF_TUNNEL_ROCK_2
	setflag FLAG_HIDE_RUSTURF_TUNNEL_MIKE
	setdynamicwarp MAP_RUSTBORO_CITY, 31, 9
	setweather WEATHER_NONE
	goto_if_set FLAG_GIRATINA_CAUGHT, Common_EventScript_NopReturn
	setflashlevel 2
	return

RusturfTunnel_EventScript_FirstEntry::
	lockall
	msgbox RusturfTunnel_Text_Enter, MSGBOX_DEFAULT
	setvar VAR_GIRATINA_EVENT, 2
	releaseall
	end

RusturfTunnel_EventScript_Shadow::
	lockall
	msgbox RusturfTunnel_Text_Shadow, MSGBOX_DEFAULT
	setvar VAR_GIRATINA_EVENT, 3
	releaseall
	end

RusturfTunnel_EventScript_Prints::
	lockall
	msgbox RusturfTunnel_Text_Prints, MSGBOX_DEFAULT
	setvar VAR_GIRATINA_EVENT, 4
	releaseall
	end

RusturfTunnel_EventScript_Writing::
	lockall
	msgbox RusturfTunnel_Text_Writing, MSGBOX_DEFAULT
	setvar VAR_GIRATINA_EVENT, 5
	releaseall
	end

RusturfTunnel_EventScript_Sighting::
	lockall
	playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox RusturfTunnel_Text_Sighting, MSGBOX_DEFAULT
	setvar VAR_GIRATINA_EVENT, 6
	releaseall
	end

@ GIRATINA. Checked before the fight, so there is always room for the
@ GRISEOUS CORE. Anything but a catch leaves it here to try again.
RusturfTunnel_EventScript_Giratina::
	lock
	faceplayer
	checkitemspace ITEM_GRISEOUS_CORE
	goto_if_eq VAR_RESULT, FALSE, RusturfTunnel_EventScript_GiratinaBagFull
	goto_if_ge VAR_GIRATINA_EVENT, 7, RusturfTunnel_EventScript_GiratinaAgain
	msgbox RusturfTunnel_Text_GiratinaFirst, MSGBOX_DEFAULT
	setvar VAR_GIRATINA_EVENT, 7
	goto RusturfTunnel_EventScript_GiratinaBattle

RusturfTunnel_EventScript_GiratinaAgain::
	msgbox RusturfTunnel_Text_GiratinaAgain, MSGBOX_DEFAULT
RusturfTunnel_EventScript_GiratinaBattle::
	closemessage
	playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_GIRATINA, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RusturfTunnel_EventScript_GiratinaCaught
	msgbox RusturfTunnel_Text_GiratinaStays, MSGBOX_DEFAULT
	release
	end

RusturfTunnel_EventScript_GiratinaCaught::
	setflag FLAG_GIRATINA_CAUGHT
	setvar VAR_GIRATINA_EVENT, 8
	removeobject LOCALID_RUSTURF_TUNNEL_GIRATINA
	animateflash 0
	setflashlevel 0
	msgbox RusturfTunnel_Text_Caught, MSGBOX_DEFAULT
	giveitem ITEM_GRISEOUS_CORE
	msgbox RusturfTunnel_Text_Core, MSGBOX_DEFAULT
	release
	end

RusturfTunnel_EventScript_GiratinaBagFull::
	msgbox RusturfTunnel_Text_BagFull, MSGBOX_DEFAULT
	release
	end

@ ============================================================================
@ Ten Gauntlets: "The Tear" (sprint-a-giratina.md). After ROXANNE's rematch, the
@ DEVON 3F scientist leads the player here; GIRATINA waits in the last chamber.
@ VAR_GIRATINA_EVENT (0x40F9), forward only:
@   0 nothing yet     1 briefed by the scientist   2 entered once (Text_Enter)
@   3 shadow seen     4 footprints seen            5 writing seen
@   6 GIRATINA sighted  7 fought, not caught       8 caught, GRISEOUS CORE given
@ FLAG_GIRATINA_CAUGHT is set with 8 and hides GIRATINA's object. The tunnel is
@ dark (setflashlevel 2) until then; every exit is a dynamic warp to RUSTBORO.
@ ============================================================================

RusturfTunnel_Text_Enter:
	.string "The scientist stopped at the first\n"
	.string "bend and raised his lamp. It\l"
	.string "guttered out. His instruments went\l"
	.string "dead a moment later.\p"
	.string "“This is as far as I go,” he said.\n"
	.string "“Follow the tunnel east. Any way\l"
	.string "out will bring you back under\l"
	.string "RUSTBORO. Don't ask me how.”\p"
	.string "Then his footsteps were gone, and\n"
	.string "{PLAYER} was alone in the dark.\p"
	.string "Somewhere ahead, something was\n"
	.string "breathing, slowly.$"

RusturfTunnel_Text_Shadow:
	.string "{PLAYER}'s shadow didn't fall\n"
	.string "behind. It stretched ahead, long\l"
	.string "and thin, as if it knew the way.\p"
	.string "When {PLAYER} stopped, it took one\n"
	.string "more step.$"

RusturfTunnel_Text_Prints:
	.string "There were footprints in the dust.\n"
	.string "Small, fresh, the same tread as\l"
	.string "{PLAYER}'s own boots.\p"
	.string "They led the way {PLAYER} was\n"
	.string "going. And they looked newer the\l"
	.string "farther they went.$"

RusturfTunnel_Text_Writing:
	.string "Something was scratched into the\n"
	.string "rock, about eye height:\p"
	.string "“.KCAB OG”\p"
	.string "The letters were cut from right to\n"
	.string "left. The scratches were still\l"
	.string "bright.$"

RusturfTunnel_Text_Sighting:
	.string "The tunnel opened into a narrow\n"
	.string "chamber. The dark was thicker here.\p"
	.string "Above the floor, where nothing\n"
	.string "should hang, something did: long\l"
	.string "and black, with golden spikes\l"
	.string "folded like broken wings.\p"
	.string "It cast no shadow. The stone\n"
	.string "around it was bent, like a glass\l"
	.string "seen through water.\p"
	.string "One red eye opened.$"

RusturfTunnel_Text_GiratinaFirst:
	.string "GIRATINA's eye held {PLAYER}.\n"
	.string "The walls flexed like skin.\p"
	.string "A voice with no sound filled the\n"
	.string "chamber.\p"
	.string "GIRATINA: …Another hand… in my\n"
	.string "world…\p"
	.string "Every door you tear lets my dark\n"
	.string "leak out.\p"
	.string "I was cast out once. I will not be\n"
	.string "cast out again.$"

RusturfTunnel_Text_GiratinaAgain:
	.string "GIRATINA hung where it had been,\n"
	.string "its red eye fixed on {PLAYER}.\p"
	.string "The tear hadn't closed. The dark\n"
	.string "still leaked out of it, cold.$"

RusturfTunnel_Text_GiratinaStays:
	.string "GIRATINA didn't follow. The dark\n"
	.string "folded around it and went still.\p"
	.string "It hadn't left. The tear hadn't\n"
	.string "closed.$"

RusturfTunnel_Text_BagFull:
	.string "GIRATINA waited in the dark. But\n"
	.string "{PLAYER}'s BAG was full.\p"
	.string "Whatever it left behind would need\n"
	.string "room. Better to make some first.$"

RusturfTunnel_Text_Caught:
	.string "The ball clicked shut.\p"
	.string "The dark let go of the chamber all\n"
	.string "at once. The walls stopped\l"
	.string "breathing.\p"
	.string "The tunnel brightened, and it was\n"
	.string "only a tunnel again.\p"
	.string "Something small rolled across the\n"
	.string "floor to {PLAYER}'s feet.$"

RusturfTunnel_Text_Core:
	.string "The GRISEOUS CORE was warm. It\n"
	.string "hummed, the way GIRATINA's cry had.\p"
	.string "Held by GIRATINA, it would remember\n"
	.string "the world behind the world, the one\l"
	.string "it was born in.$"
