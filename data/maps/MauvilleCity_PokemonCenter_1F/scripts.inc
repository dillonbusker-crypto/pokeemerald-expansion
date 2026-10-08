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

MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings:
	.string "That man over there, he says weird\n"
	.string "things!\p"
	.string "He's funny in a weird way.\n"
	.string "I doubt I'll forget about him!$"

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner:
	.string "When I accessed the RECORD CORNER,\n"
	.string "the data for what's hot in DEWFORD\l"
	.string "got updated.\p"
	.string "Now that bit of data is the same\n"
	.string "as my friend's!$"

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun:
	.string "A RECORD CORNER opened upstairs in\n"
	.string "the POKéMON CENTER.\p"
	.string "I don't know what it's about, but it\n"
	.string "sounds fun. I'll go check it out!$"

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
