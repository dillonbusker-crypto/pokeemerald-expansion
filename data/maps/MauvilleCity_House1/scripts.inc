MauvilleCity_House1_MapScripts::
	.byte 0

@ Ten Gauntlets: no HM Rock Smash here. The Dude just talks (and still
@ refuses, whatever the story); the original gift script below is unreachable.
MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_House1_EventScript_RockSmashDudeEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_House1_EventScript_RockSmashDudeFreed
	msgbox MauvilleCity_House1_Text_TenGauntletsNoHM, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_RockSmashDudeFreed::
	msgbox MauvilleCity_House1_Text_NoHMFreed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_RockSmashDudeEnding::
	msgbox MauvilleCity_House1_Text_NoHMEnding, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_RockSmashDudeVanilla::
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_TenGauntletsNoHM:
	.string "Woohoo! ...Well, no. Not today.\p"
	.string "With all the trouble in town, I'm\n"
	.string "keeping my ROCK SMASHING to myself.\p"
	.string "Stay safe out there!$"

MauvilleCity_House1_Text_NoHMFreed:
	.string "Woohoo! ...No HM today, either.\p"
	.string "But the grunts are gone, and my ROCK\n"
	.string "SMASHING is back in my own hands.\p"
	.string "That stone on the lawn? Not for\n"
	.string "smashing. Not even I would dare.$"

MauvilleCity_House1_Text_NoHMEnding:
	.string "Woohoo! ...No HM here. Not today,\n"
	.string "not ever.\p"
	.string "But the grunts are gone, SCOTT is in\n"
	.string "handcuffs, and I smashed a boulder\l"
	.string "just because I could.\p"
	.string "Woohoo!$"

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Woohoo!\p"
	.string "I hear people call me the ROCK SMASH\n"
	.string "GUY, but I find that sort of degrading.\p"
	.string "I think I deserve a bit more respect,\n"
	.string "like maybe the ROCK SMASH DUDE.\p"
	.string "Woohoo!\p"
	.string "Anyways, your POKéMON look pretty\n"
	.string "strong.\p"
	.string "I like that!\n"
	.string "Here, take this HIDDEN MACHINE!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "That HM contains ROCK SMASH.\p"
	.string "If you come across large boulders\n"
	.string "that block your path…\p"
	.string "Well, use that HM move and smash\n"
	.string "them right out of your way!\p"
	.string "Yes, sir! Smash rocks aside, I say!\n"
	.string "Woohoo!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Oh, yes, if you smash a rock, a POKéMON\n"
	.string "could come flying out of hiding.\p"
	.string "Woohoo!$"

