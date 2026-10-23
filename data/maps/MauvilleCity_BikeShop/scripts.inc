MauvilleCity_BikeShop_MapScripts::
	.byte 0

@ Ten Gauntlets: no BIKE is ever handed out (the climb to SKY PILLAR is on
@ foot). RYDEL just talks; the original gift script below is unreachable.
MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_BikeShop_EventScript_RydelEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_BikeShop_EventScript_RydelFreed
	msgbox MauvilleCity_BikeShop_Text_RydelOccupied, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_RydelFreed::
	msgbox MauvilleCity_BikeShop_Text_RydelFreed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_RydelEnding::
	msgbox MauvilleCity_BikeShop_Text_RydelEnding, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_RydelVanilla::
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

@ Ten Gauntlets: RYDEL's assistant is the third of MAUVILLE's hidden helpers.
@ He rewired a charging coil from NEW MAUVILLE's old lines; once per game it
@ lifts one party POKéMON to level 65 (RaiseMonToLevel).
MauvilleCity_BikeShop_EventScript_Assistant::
	lock
	faceplayer
	goto_if_set FLAG_MAUVILLE_RAISE_3, MauvilleCity_BikeShop_EventScript_AssistantUsed
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_BikeShop_EventScript_AssistantIntroEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_BikeShop_EventScript_AssistantIntroFreed
	msgbox MauvilleCity_BikeShop_Text_AssistantIntroOccupied, MSGBOX_DEFAULT
	goto MauvilleCity_BikeShop_EventScript_AssistantOffer
	end

MauvilleCity_BikeShop_EventScript_AssistantIntroFreed::
	msgbox MauvilleCity_BikeShop_Text_AssistantIntroFreed, MSGBOX_DEFAULT
	goto MauvilleCity_BikeShop_EventScript_AssistantOffer
	end

MauvilleCity_BikeShop_EventScript_AssistantIntroEnding::
	msgbox MauvilleCity_BikeShop_Text_AssistantIntroEnding, MSGBOX_DEFAULT
	goto MauvilleCity_BikeShop_EventScript_AssistantOffer
	end

MauvilleCity_BikeShop_EventScript_AssistantOffer::
	msgbox MauvilleCity_BikeShop_Text_AssistantOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_AssistantNotNow
MauvilleCity_BikeShop_EventScript_AssistantPick::
	msgbox MauvilleCity_BikeShop_Text_AssistantWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, MauvilleCity_BikeShop_EventScript_AssistantNotNow
	setvar VAR_0x8005, 65
	special RaiseMonToLevel
	goto_if_eq VAR_RESULT, 1, MauvilleCity_BikeShop_EventScript_AssistantEgg
	goto_if_eq VAR_RESULT, 2, MauvilleCity_BikeShop_EventScript_AssistantTooStrong
	setflag FLAG_MAUVILLE_RAISE_3
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	playfanfare MUS_LEVEL_UP
	message MauvilleCity_BikeShop_Text_AssistantGrew
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox MauvilleCity_BikeShop_Text_AssistantDone, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_AssistantEgg::
	msgbox MauvilleCity_BikeShop_Text_AssistantEgg, MSGBOX_DEFAULT
	goto MauvilleCity_BikeShop_EventScript_AssistantPick
	end

MauvilleCity_BikeShop_EventScript_AssistantTooStrong::
	msgbox MauvilleCity_BikeShop_Text_AssistantTooStrong, MSGBOX_DEFAULT
	goto MauvilleCity_BikeShop_EventScript_AssistantPick
	end

MauvilleCity_BikeShop_EventScript_AssistantNotNow::
	msgbox MauvilleCity_BikeShop_Text_AssistantNotNow, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_AssistantUsed::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_BikeShop_EventScript_AssistantUsedEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_BikeShop_EventScript_AssistantUsedFreed
	msgbox MauvilleCity_BikeShop_Text_AssistantUsedOccupied, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_AssistantUsedFreed::
	msgbox MauvilleCity_BikeShop_Text_AssistantUsedFreed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_AssistantUsedEnding::
	msgbox MauvilleCity_BikeShop_Text_AssistantUsedEnding, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelOccupied:
	.string "Well, well, a customer! ...No. I can\n"
	.string "see you aren't here for a BIKE.\p"
	.string "Nobody rides in a town where grunts\n"
	.string "block the roads. My BIKES gather dust,\l"
	.string "and I've nothing left to fix!\p"
	.string "But chin up! The wind will be back!$"

MauvilleCity_BikeShop_Text_RydelFreed:
	.string "The grunts are gone, and all the wind\n"
	.string "in MAUVILLE came back with them!\p"
	.string "SCOTT is headed for SKY PILLAR? No\n"
	.string "BIKE for you, I'm afraid. That climb is\l"
	.string "for your own two legs!\p"
	.string "May the wind be at your back anyway!$"

MauvilleCity_BikeShop_Text_RydelEnding:
	.string "The shop is quiet, and it's the good\n"
	.string "kind of quiet now.\p"
	.string "I've oiled every chain twice. Nothing\n"
	.string "left to fix! Best problem I've ever had.\p"
	.string "May the wind always be at your back!$"

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Well, well, what have we here?\n"
	.string "A most energetic customer!\p"
	.string "Me? You may call me RYDEL.\n"
	.string "I'm the owner of this cycle shop.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "RYDEL: Your RUNNING SHOES…\n"
	.string "They're awfully filthy.\p"
	.string "Did you come from far away?$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "RYDEL: Is that right?\p"
	.string "Then, I guess you have no need for\n"
	.string "any of my BIKES.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Hm, hm… … … … …\p"
	.string "You're saying that you came all this\n"
	.string "way from LITTLEROOT?\p"
	.string "My goodness!\n"
	.string "That's ridiculously far!\p"
	.string "If you had one of my BIKES, you could\n"
	.string "go anywhere easily while feeling the\l"
	.string "gentle caress of the wind!\p"
	.string "I'll tell you what!\n"
	.string "I'll give you a BIKE!\p"
	.string "Oh, wait a second!\p"
	.string "I forgot to tell you that there are\n"
	.string "two kinds of BIKES!\p"
	.string "They are the MACH BIKE and\n"
	.string "the ACRO BIKE!\p"
	.string "The MACH BIKE is for cyclists who want\n"
	.string "to feel the wind with their bodies!\p"
	.string "And an ACRO BIKE is for those who\n"
	.string "prefer technical rides!\p"
	.string "I'm a real sweetheart, so you can\n"
	.string "have whichever one you like!\p"
	.string "Which one will you choose?$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} chose the MACH BIKE.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} chose the ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "RYDEL: If you get the urge to switch\n"
	.string "BIKES, just come see me!$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "RYDEL: Oh? Were you thinking about\n"
	.string "switching BIKES?$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "RYDEL: Okay, no problem!\n"
	.string "I'll switch BIKES for you!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{PLAYER} got the MACH BIKE exchanged\n"
	.string "for an ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{PLAYER} got the ACRO BIKE exchanged\n"
	.string "for a MACH BIKE.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "RYDEL: Good, good!\n"
	.string "I'm happy that you like it!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "Oh? What happened to that BIKE\n"
	.string "I gave you?\p"
	.string "Oh, I get it, you stored it using your PC.\p"
	.string "Well, take it out of PC storage,\n"
	.string "and I'll be happy to exchange it!\p"
	.string "May the wind always be at your back\n"
	.string "on your adventure!$"

MauvilleCity_BikeShop_Text_AssistantIntroOccupied:
	.string "Don't tell RYDEL. Nobody's buying\n"
	.string "BIKES, so I've been tinkering.$"

MauvilleCity_BikeShop_Text_AssistantIntroFreed:
	.string "The grunts are gone, and RYDEL still\n"
	.string "thinks I'm oiling chains.\p"
	.string "Don't tell him I'm tinkering.$"

MauvilleCity_BikeShop_Text_AssistantIntroEnding:
	.string "Nothing to fix and nobody to sell to,\n"
	.string "so I've been tinkering all week.$"

MauvilleCity_BikeShop_Text_AssistantOffer:
	.string "I salvaged a charging coil from the\n"
	.string "old NEW MAUVILLE lines, the kind that\l"
	.string "heals a whole team.\p"
	.string "Then I rewired it. Now it doesn't just\n"
	.string "heal. It makes a POKéMON grow.\p"
	.string "One POKéMON, one go. The wire won't\n"
	.string "last. Want to try it?$"

MauvilleCity_BikeShop_Text_AssistantWhich:
	.string "Which POKéMON do I clip onto the coil?$"

MauvilleCity_BikeShop_Text_AssistantNotNow:
	.string "Okay. The coil will keep. Just don't\n"
	.string "touch the red wire.$"

MauvilleCity_BikeShop_Text_AssistantEgg:
	.string "That's an EGG! The coil would scramble\n"
	.string "it. Pick another.$"

MauvilleCity_BikeShop_Text_AssistantTooStrong:
	.string "That one is already charged past what\n"
	.string "this coil can do. Pick another.$"

MauvilleCity_BikeShop_Text_AssistantGrew:
	.string "{STR_VAR_1} was clipped on and\n"
	.string "grew to LV. 65!$"

MauvilleCity_BikeShop_Text_AssistantDone:
	.string "Whoa. It worked! ...And the coil is\n"
	.string "toast. Smells like toast, too.$"

MauvilleCity_BikeShop_Text_AssistantUsedOccupied:
	.string "The coil is fried. Don't tell RYDEL I\n"
	.string "fried it. Or that it worked.$"

MauvilleCity_BikeShop_Text_AssistantUsedFreed:
	.string "NEW MAUVILLE is quiet now, so no more\n"
	.string "spare lines to salvage. The coil was\l"
	.string "one of a kind.$"

MauvilleCity_BikeShop_Text_AssistantUsedEnding:
	.string "RYDEL found the burnt coil. He says\n"
	.string "it's the best thing anyone has ever\l"
	.string "done in his shop.$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "I'm learning about BIKES while\n"
	.string "I work here.\p"
	.string "If you need advice on how to ride your\n"
	.string "BIKE, there're a couple handbooks in\l"
	.string "the back.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "It's a handbook on the MACH BIKE.\p"
	.string "Which page do you want to read?$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "A BIKE moves in the direction that\n"
	.string "the + Control Pad is pressed.\p"
	.string "It will speed up once it gets rolling.\p"
	.string "To stop, release the + Control Pad.\n"
	.string "The BIKE will slow to a stop.\p"
	.string "Want to read a different page?$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "A MACH BIKE is speedy, but it can't\n"
	.string "stop very quickly.\p"
	.string "It gets a little tricky to get around\n"
	.string "a corner.\p"
	.string "Release the + Control Pad a little\n"
	.string "before the corner and slow down.\p"
	.string "Want to read a different page?$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "There are small sandy slopes\n"
	.string "throughout the HOENN region.\p"
	.string "The loose, crumbly sand makes it\n"
	.string "impossible to climb normally.\p"
	.string "But if you have a MACH BIKE, you can\n"
	.string "zip up a sandy slope.\p"
	.string "Want to read a different page?$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "It's a handbook on the ACRO BIKE.\p"
	.string "Which page do you want to read?$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Press the B Button while riding,\n"
	.string "and the front wheel lifts up.\p"
	.string "You can zip around with the front\n"
	.string "wheel up using the + Control Pad.\p"
	.string "This technique is called a wheelie.\p"
	.string "Want to read a different page?$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Keeping the B Button pressed,\n"
	.string "your BIKE can hop on the spot.\p"
	.string "This technique is called a bunny hop.\p"
	.string "You can ride while hopping, too.\p"
	.string "Want to read a different page?$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Press the B Button and the + Control\n"
	.string "Pad at the same time to jump.\p"
	.string "Press the + Control Pad to the side\n"
	.string "to jump sideways.\p"
	.string "Press it backwards to make the BIKE\n"
	.string "change directions while jumping.\p"
	.string "Want to read a different page?$"

