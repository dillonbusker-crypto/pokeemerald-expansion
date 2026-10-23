MauvilleCity_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CableClub_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, CableClub_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, CableClub_OnTransition
	.byte 0

@ The below 3 are unused and leftover from RS
MauvilleCity_PokemonCenter_2F_EventScript_Colosseum::
	call CableClub_EventScript_Colosseum
	end

MauvilleCity_PokemonCenter_2F_EventScript_TradeCenter::
	call CableClub_EventScript_TradeCenter
	end

MauvilleCity_PokemonCenter_2F_EventScript_RecordCorner::
	call CableClub_EventScript_RecordCorner
	end

@ Ten Gauntlets: follows the story (GetStoryGossipStage).
MauvilleCity_PokemonCenter_2F_EventScript_Youngster::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, MauvilleCity_PokemonCenter_2F_EventScript_YoungsterEnding
	goto_if_ge VAR_RESULT, GOSSIP_MAUVILLE_FREED, MauvilleCity_PokemonCenter_2F_EventScript_YoungsterFreed
	msgbox MauvilleCity_PokemonCenter_2F_Text_YoungsterOccupied, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_2F_EventScript_YoungsterFreed::
	msgbox MauvilleCity_PokemonCenter_2F_Text_YoungsterFreed, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_2F_EventScript_YoungsterEnding::
	msgbox MauvilleCity_PokemonCenter_2F_Text_YoungsterEnding, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_2F_Text_YoungsterOccupied:
	.string "Nobody has used the COLOSSEUM since\n"
	.string "the teams came to town.\p"
	.string "Even the record on the wall went dark\n"
	.string "when the lights started to flicker.$"

MauvilleCity_PokemonCenter_2F_Text_YoungsterFreed:
	.string "The record wall lit up again!\p"
	.string "My name is on it, in the “lost”\n"
	.string "column. Better on the wall than off it.$"

MauvilleCity_PokemonCenter_2F_Text_YoungsterEnding:
	.string "WATTSON posted a notice: free\n"
	.string "COLOSSEUM day for everyone.\p"
	.string "I'll take losing in public, thanks.$"

