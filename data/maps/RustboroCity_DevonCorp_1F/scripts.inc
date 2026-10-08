RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call RustboroCity_DevonCorp_1F_EventScript_SetupEndgame
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

@ ============================================================================
@ Ten Gauntlets: Rustboro, Devon Corporation (storyline.md; the states are
@ explained in RustboroCity's scripts). The staff are gone, and the ELITE FOUR
@ hold the building: SIDNEY in the lobby and PHOEBE on the stairs here,
@ GLACIA and DRAKE on 2F. Each is fought once, in order, and leaves. The
@ player uses the SCRAMBLER before each (DevonFactory_EventScript_UseScrambler):
@ no heal between them, a loss whites out to RUSTBORO's POKEMON CENTER, and
@ whoever is beaten stays beaten.
@ ============================================================================

RustboroCity_DevonCorp_1F_EventScript_SetupEndgame::
	setflag FLAG_TEMP_1
	checktrainerflag TRAINER_DEVON_SIDNEY
	call_if TRUE, RustboroCity_DevonCorp_1F_EventScript_HideSidney
	checktrainerflag TRAINER_DEVON_PHOEBE
	call_if TRUE, RustboroCity_DevonCorp_1F_EventScript_HidePhoebe
	return

RustboroCity_DevonCorp_1F_EventScript_HideSidney::
	setflag FLAG_TEMP_2
	return

RustboroCity_DevonCorp_1F_EventScript_HidePhoebe::
	setflag FLAG_TEMP_3
	return

RustboroCity_DevonCorp_1F_EventScript_Sidney::
	lock
	faceplayer
	msgbox RustboroCity_DevonCorp_1F_Text_Sidney, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_DEVON_SIDNEY, RustboroCity_DevonCorp_1F_Text_SidneyDefeat
	msgbox RustboroCity_DevonCorp_1F_Text_SidneyAfter, MSGBOX_DEFAULT
	goto DevonCorp_EventScript_EliteFourLeaves

RustboroCity_DevonCorp_1F_EventScript_Phoebe::
	lock
	faceplayer
	checktrainerflag TRAINER_DEVON_SIDNEY
	goto_if FALSE, RustboroCity_DevonCorp_1F_EventScript_PhoebeNotYet
	msgbox RustboroCity_DevonCorp_1F_Text_Phoebe, MSGBOX_DEFAULT
	call DevonFactory_EventScript_UseScrambler
	trainerbattle_no_intro TRAINER_DEVON_PHOEBE, RustboroCity_DevonCorp_1F_Text_PhoebeDefeat
	msgbox RustboroCity_DevonCorp_1F_Text_PhoebeAfter, MSGBOX_DEFAULT
	goto DevonCorp_EventScript_EliteFourLeaves

RustboroCity_DevonCorp_1F_EventScript_PhoebeNotYet::
	msgbox RustboroCity_DevonCorp_1F_Text_PhoebeNotYet, MSGBOX_DEFAULT
	release
	end

@ Shared by all four. The held items they use up come back, win or white-out
@ (EventScript_RestoreStoryHeldItems), as after any story fight.
@ VAR_LAST_TALKED is still the member just beaten.
DevonCorp_EventScript_EliteFourLeaves::
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_DEVON_CORP_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_DEVON_CORP_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "Hello and welcome to the DEVON\n"
	.string "CORPORATION.\p"
	.string "We're proud producers of items and\n"
	.string "medicine that enhance your life.$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "One of our research staff stupidly\n"
	.string "got robbed of an important parcel.$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "Hey, those RUNNING SHOES!\n"
	.string "They're one of our products!\p"
	.string "It makes me happy when I see someone\n"
	.string "using something we made.$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "That stolen parcel…\p"
	.string "Well, sure it's important, but it's not\n"
	.string "anything that anyone can use.\p"
	.string "In my estimation, that robber must not\n"
	.string "have been very bright.$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "It sounds like they've recovered\n"
	.string "the ripped-off DEVON GOODS.$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "I'm sorry, only authorized people\n"
	.string "are allowed to enter here.$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "It's beyond stupid.\n"
	.string "How could we get robbed?$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "Hi, there!\n"
	.string "You're always welcome here!$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "Samples of rocks and metal are\n"
	.string "displayed in the glass case.\p"
	.string "There's a panel with some writing\n"
	.string "on it…\p"
	.string "“DEVON CORPORATION got its start as\n"
	.string "a producer of stones from quarries.\p"
	.string "“The company also produced iron from\n"
	.string "filings in the sand.\p"
	.string "“From that humble start as a producer\n"
	.string "of raw materials, DEVON developed.\p"
	.string "“DEVON is now a manufacturer of a wide\n"
	.string "range of industrial products.”$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "Prototypes and test products fill\n"
	.string "the glass display case.\p"
	.string "There's a panel with a description…\p"
	.string "“In addition to industrial products,\n"
	.string "DEVON now markets sundries and\l"
	.string "pharmaceuticals for better lifestyles.\p"
	.string "“Recently, DEVON has begun marketing\n"
	.string "tools for POKéMON TRAINERS, including\l"
	.string "POKé BALLS and POKéNAV systems.”$"

RustboroCity_DevonCorp_1F_Text_Sidney:
	.string "SIDNEY: Well, look who it is.\p"
	.string "SCOTT beat all four of us, kid. Then\n"
	.string "he made us an offer.\p"
	.string "MEGAS that never wear off, and the\n"
	.string "LEAGUE all to ourselves once he's\l"
	.string "in charge.\p"
	.string "All we've gotta do is stand here.\n"
	.string "Nothing personal. Let's go!$"

RustboroCity_DevonCorp_1F_Text_SidneyDefeat:
	.string "Ha! Now that's what I call a\n"
	.string "battle!$"

RustboroCity_DevonCorp_1F_Text_SidneyAfter:
	.string "SIDNEY: I lost fair and square.\n"
	.string "I'm done guarding doors.\p"
	.string "PHOEBE's on the stairs. Good luck.$"

RustboroCity_DevonCorp_1F_Text_PhoebeNotYet:
	.string "PHOEBE: Not so fast.\p"
	.string "We do this the LEAGUE's way. SIDNEY\n"
	.string "first, then me.$"

RustboroCity_DevonCorp_1F_Text_Phoebe:
	.string "PHOEBE: You got past SIDNEY.\p"
	.string "SCOTT's CROWN bound my BANETTE's\n"
	.string "MEGA EVOLUTION for good.\p"
	.string "It said it never wanted to change\n"
	.string "back. I believed it.\p"
	.string "Show me if our bond is any less\n"
	.string "than yours!$"

RustboroCity_DevonCorp_1F_Text_PhoebeDefeat:
	.string "Oh, darn.\n"
	.string "I've gone and lost.$"

RustboroCity_DevonCorp_1F_Text_PhoebeAfter:
	.string "PHOEBE: The stairs are yours.\p"
	.string "GLACIA is upstairs. She won't go\n"
	.string "easy on you.$"
