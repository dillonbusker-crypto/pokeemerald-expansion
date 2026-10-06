RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition:
	call RustboroCity_DevonCorp_3F_EventScript_SetupEndgame
	call_if_eq VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
	end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos::
	setobjectxyperm LOCALID_DEVON_CORP_3F_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_CORP_3F_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast::
	turnobject LOCALID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame:
	map_script_2 VAR_ENDGAME_STATE, 8, RustboroCity_DevonCorp_3F_EventScript_StoneScene
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk:
	delay_16
	walk_in_place_faster_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor::
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls::
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor:
	.string "I'm MR. STONE, the PRESIDENT of\n"
	.string "the DEVON CORPORATION.\p"
	.string "I'd just got word about you!\p"
	.string "You saved our staff not just once,\n"
	.string "but twice!\p"
	.string "I have a favor to ask of an amazing\n"
	.string "person like you.\p"
	.string "I understand that you're delivering\n"
	.string "a package to SLATEPORT's SHIPYARD.\p"
	.string "Well, on the way, could you stop off in\n"
	.string "DEWFORD TOWN?\p"
	.string "I was hoping that you'd deliver a\n"
	.string "LETTER to STEVEN in DEWFORD.$"

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis:
	.string "MR. STONE: Now, you should know that\n"
	.string "I am a great PRESIDENT.\p"
	.string "So, I'd never be so cheap as to ask\n"
	.string "a favor for nothing in return.\p"
	.string "That's why I want you to have this!$"

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
	.string "{PLAYER} received a POKéNAV.$"

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp:
	.string "MR. STONE: That device…\p"
	.string "It's a POKéMON NAVIGATOR, or POKéNAV\n"
	.string "for short.\p"
	.string "It's an indispensable tool for any\n"
	.string "TRAINER on an adventure.\p"
	.string "It has a map of the HOENN region.\p"
	.string "You can check the locations of\n"
	.string "DEWFORD and SLATEPORT easily!\p"
	.string "By the way, I've heard that sinister\n"
	.string "criminals--MAGMA and AQUA, I believe--\l"
	.string "have been making trouble far and wide.\p"
	.string "I think it would be best if you rested\n"
	.string "up before you go on your way.$"

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare:
	.string "MR. STONE: Well, then, {PLAYER}{KUN},\n"
	.string "go with caution and care!$"

RustboroCity_DevonCorp_3F_Text_CountingOnYou:
	.string "MR. STONE: I'm counting on you!$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter:
	.string "MR. STONE: You delivered my LETTER?\n"
	.string "Thank you kindly!\p"
	.string "This is my way of thanking you.\n"
	.string "It should help you, a TRAINER.$"

RustboroCity_DevonCorp_3F_Text_ExplainExpShare:
	.string "MR. STONE: A POKéMON holding that\n"
	.string "EXP. SHARE will be given some of the\l"
	.string "EXP Points from battle.\p"
	.string "It will get EXP Points even if it didn't\n"
	.string "actually battle.\p"
	.string "I would say EXP. SHARE is quite useful\n"
	.string "for raising weak POKéMON.$"

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends:
	.string "MR. STONE: Since my youth, I've immersed\n"
	.string "myself in work.\p"
	.string "Consequently, I'm not familiar with\n"
	.string "trends and that sort of thing.\p"
	.string "But do young people all want to be\n"
	.string "TRAINERS in the POKéMON LEAGUE?$"

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere:
	.string "This is the DEVON CORPORATION's\n"
	.string "third floor.\p"
	.string "Our PRESIDENT's OFFICE is on\n"
	.string "this floor.\p"
	.string "Anyway, I can't tell you how much I'm\n"
	.string "grateful for what you've done.\p"
	.string "Um… By the way, that parcel\n"
	.string "you got back for us…\p"
	.string "Could I get you to deliver that to\n"
	.string "the SHIPYARD in SLATEPORT?\p"
	.string "It would be awful if those robbers\n"
	.string "tried to take it again.\p"
	.string "Uh… Hehehe, so, uh, could I count\n"
	.string "on you to do that for me?\p"
	.string "Oh, that's right.\n"
	.string "Could you wait here a second?$"

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe:
	.string "Our PRESIDENT would like to have\n"
	.string "a word with you.\p"
	.string "Please come with me.$"

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead:
	.string "Please, go ahead.$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard:
	.string "If you visit the SHIPYARD in SLATEPORT,\n"
	.string "you should go see CAPT. STERN.$"

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular:
	.string "DEVON's new products, the REPEAT BALL\n"
	.string "and TIMER BALL, have become hugely\l"
	.string "popular among TRAINERS.$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay:
	.string "It's a collection of rare rocks and\n"
	.string "stones assembled by the PRESIDENT.$"

@ ============================================================================
@ Ten Gauntlets: Rustboro, Devon Corporation (storyline.md; the states are
@ explained in RustboroCity's scripts). Vanilla's first visit (the LETTER and
@ the POKENAV) and STONE's EXP. SHARE are switched off. Past DRAKE (state 8),
@ the player walks up to STONE's desk; STEVEN and WALLACE catch up, STONE
@ confesses, and his scientist re-engineers the REPLICA CROWN (state 9).
@ STEVEN stays with his father until the player has left RUSTBORO (state 10).
@ ============================================================================

RustboroCity_DevonCorp_3F_EventScript_SetupEndgame::
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	call_if_eq VAR_ENDGAME_STATE, 9, RustboroCity_DevonCorp_3F_EventScript_ShowSteven
	return

RustboroCity_DevonCorp_3F_EventScript_ShowSteven::
	clearflag FLAG_TEMP_1
	setobjectxyperm LOCALID_DEVON_CORP_3F_STEVEN, 13, 4
	return

@ The player comes up the stairs to (2, 2) and walks to (14, 5), across the
@ desk from STONE at (17, 5). STEVEN and WALLACE follow to (13, 4) and
@ (13, 6); the scientist comes round from (17, 7) to (14, 6).
RustboroCity_DevonCorp_3F_EventScript_StoneScene::
	lockall
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerToDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_Stone1, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_TEMP_1
	addobject LOCALID_DEVON_CORP_3F_STEVEN
	applymovement LOCALID_DEVON_CORP_3F_STEVEN, RustboroCity_DevonCorp_3F_Movement_StevenToDesk
	delay 32
	clearflag FLAG_TEMP_2
	addobject LOCALID_DEVON_CORP_3F_WALLACE
	applymovement LOCALID_DEVON_CORP_3F_WALLACE, RustboroCity_DevonCorp_3F_Movement_WallaceToDesk
	waitmovement LOCALID_DEVON_CORP_3F_STEVEN
	waitmovement LOCALID_DEVON_CORP_3F_WALLACE
	msgbox RustboroCity_DevonCorp_3F_Text_Steven1, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_Stone2, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_Steven2, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_Stone3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_SCIENTIST, RustboroCity_DevonCorp_3F_Movement_ScientistToPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_Scientist1, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_Wallace1, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_Scientist2, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_SELECT
	delay 20
	playse SE_SELECT
	delay 20
	playse SE_REPEL
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox RustboroCity_DevonCorp_3F_Text_Scientist3, MSGBOX_DEFAULT
	giveitem ITEM_REPLICA_CROWN
	msgbox RustboroCity_DevonCorp_3F_Text_Scientist4, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_SCIENTIST, RustboroCity_DevonCorp_3F_Movement_ScientistBack
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_Steven3, MSGBOX_DEFAULT
	msgbox RustboroCity_DevonCorp_3F_Text_Wallace2, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_DEVON_CORP_3F_WALLACE
	setvar VAR_ENDGAME_STATE, 9
	fadescreen FADE_FROM_BLACK
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_PlayerToDesk:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_Movement_StevenToDesk:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_Movement_WallaceToDesk:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_Movement_ScientistToPlayer:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

RustboroCity_DevonCorp_3F_Movement_ScientistBack:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_EventScript_EndgameStone::
	lock
	msgbox RustboroCity_DevonCorp_3F_Text_StoneAfter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Steven::
	msgbox RustboroCity_DevonCorp_3F_Text_StevenAfter, MSGBOX_NPC
	end

RustboroCity_DevonCorp_3F_EventScript_Scientist::
	msgbox RustboroCity_DevonCorp_3F_Text_ScientistAfter, MSGBOX_NPC
	end

RustboroCity_DevonCorp_3F_Text_Stone1:
	.string "MR. STONE: So. You're the one who\n"
	.string "got past the ELITE FOUR.\p"
	.string "I suppose you've come for answers.$"

RustboroCity_DevonCorp_3F_Text_Steven1:
	.string "STEVEN: Father.$"

RustboroCity_DevonCorp_3F_Text_Stone2:
	.string "MR. STONE: STEVEN…\p"
	.string "All I ever wanted was for DEVON to\n"
	.string "lead the world in technology.\p"
	.string "SCOTT came to me with the BOND\n"
	.string "HARNESS. He swore it was for the\l"
	.string "FRONTIER, and I believed him.\p"
	.string "When BIRCH tried to back out, I\n"
	.string "pressed him to meet our deadlines.\p"
	.string "I crossed lines I never should\n"
	.string "have. I see that now.$"

RustboroCity_DevonCorp_3F_Text_Steven2:
	.string "STEVEN: SCOTT has the CROWN.\n"
	.string "Is there anything left that can\l"
	.string "stand against it?$"

RustboroCity_DevonCorp_3F_Text_Stone3:
	.string "MR. STONE: …There is one thing.\p"
	.string "I never trusted SCOTT completely.\n"
	.string "So I had a second CROWN built, in\l"
	.string "secret. A failsafe.\p"
	.string "But it has no power, and I haven't\n"
	.string "the faintest idea how to use it.$"

RustboroCity_DevonCorp_3F_Text_Scientist1:
	.string "If I may, PRESIDENT.\p"
	.string "The chips in the FRONTIER's POKéMON\n"
	.string "are made from MEGA STONE shards.\p"
	.string "I could re-engineer the replica to\n"
	.string "draw its charge from those chips.$"

RustboroCity_DevonCorp_3F_Text_Wallace1:
	.string "WALLACE: And the chips themselves?$"

RustboroCity_DevonCorp_3F_Text_Scientist2:
	.string "Drained dry. They'd stop working\n"
	.string "altogether.\p"
	.string "Every POKéMON at the FRONTIER could\n"
	.string "grow again. Give me a moment!$"

RustboroCity_DevonCorp_3F_Text_Scientist3:
	.string "There. It's done.\n"
	.string "This belongs with you.$"

RustboroCity_DevonCorp_3F_Text_Scientist4:
	.string "It's empty for now. Charge it from\n"
	.string "the chips at the FRONTIER, and it\l"
	.string "can make a MEGA EVOLUTION last.$"

RustboroCity_DevonCorp_3F_Text_Steven3:
	.string "STEVEN: I'll stay here with my father\n"
	.string "for a while. We have a lot to talk\l"
	.string "about.\p"
	.string "Take the CROWN back to the FRONTIER.\n"
	.string "I'll join you there.$"

RustboroCity_DevonCorp_3F_Text_Wallace2:
	.string "WALLACE: I'll head down first. JUAN\n"
	.string "is waiting outside.\p"
	.string "He has something to say to you.$"

RustboroCity_DevonCorp_3F_Text_StoneAfter:
	.string "MR. STONE: I'll answer for what I've\n"
	.string "done. But first, stop SCOTT.$"

RustboroCity_DevonCorp_3F_Text_StevenAfter:
	.string "STEVEN: Go on. JUAN is waiting\n"
	.string "outside, and the CROWN needs its\l"
	.string "charge.$"

RustboroCity_DevonCorp_3F_Text_ScientistAfter:
	.string "Charge the CROWN from the chips at\n"
	.string "the FRONTIER. After that, it can make\l"
	.string "a MEGA EVOLUTION last.$"
