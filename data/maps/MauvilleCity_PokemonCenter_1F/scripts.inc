MauvilleCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx::
	special SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_MAUVILLE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

@ Ten Gauntlets: the townsfolk follow the story (GetStoryGossipStage).
MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_PokemonCenter_1F_EventScript_Woman1Ending
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_PokemonCenter_1F_EventScript_Woman1Freed
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman1Occupied, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1Freed::
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman1Freed, MSGBOX_NPC
	end

@ The old man's tale is told at the statue; she has seen it stand again.
MauvilleCity_PokemonCenter_1F_EventScript_Woman1Ending::
	goto_if_set FLAG_MAUVILLE_STATUE_RESTORED, MauvilleCity_PokemonCenter_1F_EventScript_Woman1EndingWhole
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman1Ending, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1EndingWhole::
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman1EndingWhole, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_PokemonCenter_1F_EventScript_Woman2Ending
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_PokemonCenter_1F_EventScript_Woman2Freed
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman2Occupied, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2Freed::
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman2Freed, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2Ending::
	msgbox MauvilleCity_PokemonCenter_1F_Text_Woman2Ending, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_PokemonCenter_1F_EventScript_YoungsterEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_PokemonCenter_1F_EventScript_YoungsterFreed
	msgbox MauvilleCity_PokemonCenter_1F_Text_YoungsterOccupied, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_YoungsterFreed::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YoungsterFreed, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_YoungsterEnding::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YoungsterEnding, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_Woman1Occupied:
	.string "That man over there keeps saying the\n"
	.string "lights will come back.\p"
	.string "With the grunts right outside! He's\n"
	.string "funny in a weird way. I'm glad\l"
	.string "somebody isn't afraid.$"

MauvilleCity_PokemonCenter_1F_Text_Woman1Freed:
	.string "That man said the lights would come\n"
	.string "back, and they did!\p"
	.string "Now he tells everyone about the stone\n"
	.string "on the lawn. Weird. But I've stopped\l"
	.string "doubting him.$"

MauvilleCity_PokemonCenter_1F_Text_Woman1Ending:
	.string "That man still talks about mending the\n"
	.string "broken stone on the lawn.\p"
	.string "Weird. But he's been right so far.$"

MauvilleCity_PokemonCenter_1F_Text_Woman1EndingWhole:
	.string "That man was right about the stone\n"
	.string "king. It stands whole on the lawn.\p"
	.string "I'm never doubting him again.$"

MauvilleCity_PokemonCenter_1F_Text_Woman2Occupied:
	.string "A grunt demanded that the nurse heal\n"
	.string "his POKéMON. She said no, politely.\p"
	.string "The CENTER was empty, and I've never\n"
	.string "been prouder of anyone.$"

MauvilleCity_PokemonCenter_1F_Text_Woman2Freed:
	.string "The grunts are gone, and the nurse\n"
	.string "still waves at the door.\p"
	.string "Nobody comes in. The POKéNAV heals\n"
	.string "everyone's POKéMON for them.$"

MauvilleCity_PokemonCenter_1F_Text_Woman2Ending:
	.string "The nurse had four patients this\n"
	.string "morning! DEVON switched the POKéNAV's\l"
	.string "auto-heal off “for review.”\p"
	.string "She cried. The good kind.$"

MauvilleCity_PokemonCenter_1F_Text_YoungsterOccupied:
	.string "I wanted to see the COLOSSEUM up\n"
	.string "there, but the lights keep flickering\l"
	.string "and the link rooms won't start.\p"
	.string "Dad says the grunts are drawing too\n"
	.string "much power from somewhere.$"

MauvilleCity_PokemonCenter_1F_Text_YoungsterFreed:
	.string "The lights are steady and the link\n"
	.string "rooms work again!\p"
	.string "I'm going to lose every COLOSSEUM\n"
	.string "battle, but I'll lose steadily.$"

MauvilleCity_PokemonCenter_1F_Text_YoungsterEnding:
	.string "People are battling upstairs again!\p"
	.string "I lost to a boy who has never left\n"
	.string "town. Best loss of my life.$"

@ Ten Gauntlets: the old man tells the legend of the KING OF BOUNTIFUL
@ HARVEST once WATTSON is beaten (sprint-b-calyrex.md). Whichever of the five
@ MAUVILLE men he is, this goes first; everything else is the vanilla script.
MauvilleCity_PokemonCenter_1F_EventScript_OldMan::
	goto_if_not_defeated TRAINER_ENDGAME_WATTSON, MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	lock
	faceplayer
	switch VAR_CALYREX_EVENT
	case 0, MauvilleCity_PokemonCenter_1F_EventScript_OldManTell
	case 1, MauvilleCity_PokemonCenter_1F_EventScript_OldManRetell
	case 2, MauvilleCity_PokemonCenter_1F_EventScript_OldManRetell
	case 3, MauvilleCity_PokemonCenter_1F_EventScript_OldManSteed
	case 4, MauvilleCity_PokemonCenter_1F_EventScript_OldManEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManTell::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManIntro, MSGBOX_DEFAULT
	setvar VAR_CALYREX_EVENT, 1
	goto MauvilleCity_PokemonCenter_1F_EventScript_OldManTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManRetell::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	goto MauvilleCity_PokemonCenter_1F_EventScript_OldManTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManTale1, MSGBOX_DEFAULT
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManTale2, MSGBOX_DEFAULT
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManTale3, MSGBOX_DEFAULT
	release
	end

@ State 3: the king needs a steed.
MauvilleCity_PokemonCenter_1F_EventScript_OldManSteed::
	checkspecies SPECIES_GLASTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_OldManSteedGo
	checkspecies SPECIES_SPECTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_OldManSteedGo
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManSteedHint, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManSteedGo::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManSteedGo, MSGBOX_DEFAULT
	release
	end

@ State 4: the end of the tale, which says how to use the REINS. NO is the
@ vanilla man.
MauvilleCity_PokemonCenter_1F_EventScript_OldManEnd::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManEndAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManEpilogue, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_OldManIntro:
	.string "Trainer! You came from the GYM, did\n"
	.string "you? Then you've heard WATTSON's\l"
	.string "favorite story: the stone on the\l"
	.string "lawn.\p"
	.string "He built a whole town around a king\n"
	.string "and never learned the king's name.\p"
	.string "Sit. I'll tell you. Hardly anyone\n"
	.string "asks anymore.$"

MauvilleCity_PokemonCenter_1F_Text_OldManTale1:
	.string "Long ago, before MAUVILLE, before\n"
	.string "any road, a king ruled a land of\l"
	.string "fields.\p"
	.string "They called him the KING OF\n"
	.string "BOUNTIFUL HARVEST. Where he walked,\l"
	.string "the grain stood tall and the\l"
	.string "flowers opened.\p"
	.string "He rode a great steed, white as\n"
	.string "frost or dark as shade. No storm or\l"
	.string "army stood against the two of them.$"

MauvilleCity_PokemonCenter_1F_Text_OldManTale2:
	.string "But a king lives by being\n"
	.string "remembered. The harvests came and\l"
	.string "came, and the people forgot whom to\l"
	.string "thank.\p"
	.string "The crops still grew. The king grew\n"
	.string "faint, and faded, steed and all.\p"
	.string "The people carved his likeness in\n"
	.string "stone, to say they were sorry.\p"
	.string "That's the stone on the lawn.\n"
	.string "A crown cracks when its king is\l"
	.string "forgotten.$"

MauvilleCity_PokemonCenter_1F_Text_OldManTale3:
	.string "They say it mends the same way:\n"
	.string "when a crown is held to the break\l"
	.string "by someone who remembers.\p"
	.string "Funny. I hear you carry a crown of\n"
	.string "your own. It couldn't hurt to try.$"

MauvilleCity_PokemonCenter_1F_Text_OldManAgain:
	.string "Shall I tell the tale of the KING\n"
	.string "OF BOUNTIFUL HARVEST again?$"

MauvilleCity_PokemonCenter_1F_Text_OldManSteedHint:
	.string "A king without his steed is half a\n"
	.string "harvest.\p"
	.string "The steed of frost, GLASTRIER, and\n"
	.string "the steed of shade, SPECTRIER, are\l"
	.string "sold on the island, at the exchange\l"
	.string "counter.\p"
	.string "Bring either, and the king will see\n"
	.string "you.$"

MauvilleCity_PokemonCenter_1F_Text_OldManSteedGo:
	.string "Ah, there's a steed at your side.\n"
	.string "The king is waiting on the lawn.$"

MauvilleCity_PokemonCenter_1F_Text_OldManEndAsk:
	.string "Shall I tell how the tale ends?$"

MauvilleCity_PokemonCenter_1F_Text_OldManEpilogue:
	.string "So the king rides again. Not as\n"
	.string "anyone's prisoner. That's the right\l"
	.string "end for a harvest king.\p"
	.string "About those REINS: use them from\n"
	.string "your BAG on the king and his steed,\l"
	.string "and the two become one. Use them\l"
	.string "again to part them.\p"
	.string "Keep a spot free in your party,\n"
	.string "mind. The steed needs somewhere to\l"
	.string "stand.$"
