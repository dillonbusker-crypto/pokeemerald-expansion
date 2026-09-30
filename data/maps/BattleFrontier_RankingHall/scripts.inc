BattleFrontier_RankingHall_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_RankingHall_OnTransition
	.byte 0

@ Ten Gauntlets: STEVEN waits by the eleventh plaque once gauntlet 2 is
@ cleared, until the player has spoken to him (frontier-dialogue.md). Keyed
@ off the cleared count, not just the attendant's hint, so a save that
@ cleared gauntlet 2 before this existed still finds him.
BattleFrontier_RankingHall_OnTransition:
	setflag FLAG_TEMP_1
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_STEVEN_STORY_STATE, 3, BattleFrontier_RankingHall_EventScript_NoSteven
	goto_if_eq VAR_STEVEN_STORY_STATE, 2, BattleFrontier_RankingHall_EventScript_StevenBackAfterG4
	goto_if_lt VAR_RESULT, 2, BattleFrontier_RankingHall_EventScript_NoSteven
	clearflag FLAG_TEMP_1
	end

@ Back after gauntlet 4 (VAR_STEVEN_STORY_STATE 2 -> 3).
BattleFrontier_RankingHall_EventScript_StevenBackAfterG4:
	goto_if_lt VAR_RESULT, 4, BattleFrontier_RankingHall_EventScript_NoSteven
	clearflag FLAG_TEMP_1
BattleFrontier_RankingHall_EventScript_NoSteven:
	end

BattleFrontier_RankingHall_EventScript_Steven::
	lock
	faceplayer
	goto_if_eq VAR_STEVEN_STORY_STATE, 2, BattleFrontier_RankingHall_EventScript_StevenG4
	msgbox BattleFrontier_RankingHall_Text_StevenIntro, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenAsksBadges, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_ShowedBadges, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenCounterfeit, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenTakesRainBadge, MSGBOX_DEFAULT
	playse SE_PIN
	message BattleFrontier_RankingHall_Text_GaveRainBadge
	waitmessage
	waitbuttonpress
	clearflag FLAG_BADGE08_GET
	closemessage
	turnobject LOCALID_RANKING_HALL_STEVEN, DIR_EAST
	delay 30
	msgbox BattleFrontier_RankingHall_Text_StevenPlaque, MSGBOX_DEFAULT
	applymovement LOCALID_RANKING_HALL_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_RankingHall_Text_StevenGift, MSGBOX_DEFAULT
	giveitem ITEM_EVIOLITE
	msgbox BattleFrontier_RankingHall_Text_StevenFavor, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenAsksHelp, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_AgreedToHelp, MSGBOX_DEFAULT
	closemessage
	setvar VAR_STEVEN_STORY_STATE, 2
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_RANKING_HALL_STEVEN
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_RankingHall_EventScript_TowerSinglesRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 1's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 1, BattleFrontier_RankingHall_EventScript_TowerSinglesRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_TowerSinglesRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerSinglesRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_TowerSinglesRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerDoublesRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 2's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 2, BattleFrontier_RankingHall_EventScript_TowerDoublesRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_TowerDoublesRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerDoublesRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_TowerDoublesRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerMultisRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 3's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 3, BattleFrontier_RankingHall_EventScript_TowerMultisRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_TowerMultisRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerMultisRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_TowerMultisRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerLinkRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 4's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 4, BattleFrontier_RankingHall_EventScript_TowerLinkRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_TowerLinkRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_TowerLinkRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_TowerLinkRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_ArenaRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 8's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 8, BattleFrontier_RankingHall_EventScript_ArenaRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_ArenaRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_ArenaRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_ArenaRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PalaceRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 9's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 9, BattleFrontier_RankingHall_EventScript_PalaceRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_PalaceRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PalaceRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_PalaceRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_FactoryRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 6's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 6, BattleFrontier_RankingHall_EventScript_FactoryRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_FactoryRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_FactoryRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_FactoryRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_DomeRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 5's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 5, BattleFrontier_RankingHall_EventScript_DomeRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_DomeRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_DomeRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_DomeRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PikeRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 7's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 7, BattleFrontier_RankingHall_EventScript_PikeRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_PikeRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PikeRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_PikeRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PyramidRecords::
	@ Ten Gauntlets: a Hall of Ten plaque - gauntlet 10's boss, and the
	@ player's name once it's been beaten (frontier-dialogue.md, Part 5).
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 10, BattleFrontier_RankingHall_EventScript_PyramidRecords_Beaten
	msgbox BattleFrontier_RankingHall_EventScript_PyramidRecords_Text, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PyramidRecords_Beaten:
	msgbox BattleFrontier_RankingHall_EventScript_PyramidRecords_TextBeaten, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_ShowRecords::
	special ShowRankingHallRecordsWindow
	waitbuttonpress
	special ScrollRankingHallRecordsWindow
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_RankingHall_EventScript_Attendant::
	msgbox BattleFrontier_RankingHall_Text_ExplainRankingHall, MSGBOX_NPC
	end

BattleFrontier_RankingHall_EventScript_DomePikeFactoryRecordsSign::
	msgbox BattleFrontier_RankingHall_Text_DomePikeFactoryRecords, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PalaceArenaPyramidRecordsSIgn::
	msgbox BattleFrontier_RankingHall_Text_PalaceArenaPyramidRecords, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_NinjaBoy::
	lock
	faceplayer
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 1, BattleFrontier_RankingHall_EventScript_NinjaBoy_Cleared1
	msgbox BattleFrontier_RankingHall_EventScript_NinjaBoy_Text0, MSGBOX_DEFAULT
	release
	end

BattleFrontier_RankingHall_EventScript_NinjaBoy_Cleared1:
	msgbox BattleFrontier_RankingHall_EventScript_NinjaBoy_Text1, MSGBOX_DEFAULT
	release
	end

BattleFrontier_RankingHall_EventScript_NinjaBoyNameOnList::
	msgbox BattleFrontier_RankingHall_Text_WowThatsSuper, MSGBOX_DEFAULT
	release
	end

BattleFrontier_RankingHall_EventScript_Boy::
	msgbox BattleFrontier_RankingHall_Text_MyNamesNotUpThere, MSGBOX_NPC
	end

BattleFrontier_RankingHall_Text_ExplainRankingHall:
	.string "Welcome to the HALL OF TEN.\p"
	.string "There's one plaque for each\n"
	.string "gauntlet's boss, and once they've\l"
	.string "fallen, the name of the trainer\l"
	.string "who beat them.$"

BattleFrontier_RankingHall_Text_DomePikeFactoryRecords:
	.string "THE HALL OF TEN\p"
	.string "Gauntlets 5 to 7: the BATTLE DOME,\n"
	.string "the BATTLE FACTORY and the BATTLE\l"
	.string "PIKE.$"

BattleFrontier_RankingHall_Text_PalaceArenaPyramidRecords:
	.string "THE HALL OF TEN\p"
	.string "Gauntlets 8 to 10: the BATTLE\n"
	.string "ARENA, the BATTLE PALACE and the\l"
	.string "BATTLE PYRAMID.$"

BattleFrontier_RankingHall_Text_IsYourNameOnThisList:
	.string "Hi, is your name on this list?$"

BattleFrontier_RankingHall_Text_WowThatsSuper:
	.string "Wow, that's super!\n"
	.string "I'll have to try harder, too!$"

BattleFrontier_RankingHall_Text_WorkHarderIfYouSawFriendsName:
	.string "Oh, is that right?\p"
	.string "If you saw your friend's name up here,\n"
	.string "I bet it would make you work harder!$"

BattleFrontier_RankingHall_Text_MyNamesNotUpThere:
	.string "Hmm… No plaques with my name on\n"
	.string "them yet.\p"
	.string "Well, I'm still on gauntlet 1…$"

BattleFrontier_RankingHall_EventScript_TowerSinglesRecords_Text:
	.string "GAUNTLET 1 - LITTLE LEAGUE.\p"
	.string "Boss: WARDEN WINONA.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_TowerSinglesRecords_TextBeaten:
	.string "GAUNTLET 1 - LITTLE LEAGUE.\p"
	.string "Boss: WARDEN WINONA.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_TowerDoublesRecords_Text:
	.string "GAUNTLET 2 - THE SECOND SLOT.\p"
	.string "Boss: TIDEWARDEN JUAN.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_TowerDoublesRecords_TextBeaten:
	.string "GAUNTLET 2 - THE SECOND SLOT.\p"
	.string "Boss: TIDEWARDEN JUAN.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_TowerMultisRecords_Text:
	.string "GAUNTLET 3 - THE CHANGING SKY.\p"
	.string "Boss: DUNEWARDEN ROXANNE.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_TowerMultisRecords_TextBeaten:
	.string "GAUNTLET 3 - THE CHANGING SKY.\p"
	.string "Boss: DUNEWARDEN ROXANNE.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_TowerLinkRecords_Text:
	.string "GAUNTLET 4 - THE TURN ORDER.\p"
	.string "Boss: SALON MAIDEN ANABEL.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_TowerLinkRecords_TextBeaten:
	.string "GAUNTLET 4 - THE TURN ORDER.\p"
	.string "Boss: SALON MAIDEN ANABEL.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_DomeRecords_Text:
	.string "GAUNTLET 5 - THE MAIN EVENT.\p"
	.string "Boss: DOME ACE TUCKER.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_DomeRecords_TextBeaten:
	.string "GAUNTLET 5 - THE MAIN EVENT.\p"
	.string "Boss: DOME ACE TUCKER.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_FactoryRecords_Text:
	.string "GAUNTLET 6 - THE ASSEMBLY LINE.\p"
	.string "Boss: FACTORY HEAD NOLAND.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_FactoryRecords_TextBeaten:
	.string "GAUNTLET 6 - THE ASSEMBLY LINE.\p"
	.string "Boss: FACTORY HEAD NOLAND.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_PikeRecords_Text:
	.string "GAUNTLET 7 - BATTLE PIKE.\p"
	.string "Boss: PIKE QUEEN LUCY.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_PikeRecords_TextBeaten:
	.string "GAUNTLET 7 - BATTLE PIKE.\p"
	.string "Boss: PIKE QUEEN LUCY.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_ArenaRecords_Text:
	.string "GAUNTLET 8 - BATTLE ARENA.\p"
	.string "Boss: ARENA TYCOON GRETA.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_ArenaRecords_TextBeaten:
	.string "GAUNTLET 8 - BATTLE ARENA.\p"
	.string "Boss: ARENA TYCOON GRETA.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_PalaceRecords_Text:
	.string "GAUNTLET 9 - BATTLE PALACE.\p"
	.string "Boss: PALACE MAVEN SPENSER.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_PalaceRecords_TextBeaten:
	.string "GAUNTLET 9 - BATTLE PALACE.\p"
	.string "Boss: PALACE MAVEN SPENSER.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_PyramidRecords_Text:
	.string "GAUNTLET 10 - BATTLE PYRAMID.\p"
	.string "Boss: PYRAMID KING BRANDON.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_EventScript_PyramidRecords_TextBeaten:
	.string "GAUNTLET 10 - BATTLE PYRAMID.\p"
	.string "Boss: PYRAMID KING BRANDON.\p"
	.string "Defeated by {PLAYER}.$"

BattleFrontier_RankingHall_EventScript_NinjaBoy_Text1:
	.string "Hey! That plaque has your name on\n"
	.string "it!\p"
	.string "Wow, that's super! I'll have to\n"
	.string "try harder, too!$"

BattleFrontier_RankingHall_EventScript_NinjaBoy_Text0:
	.string "Is your name on any of these\n"
	.string "plaques?\p"
	.string "…Not yet? If you saw a friend's\n"
	.string "name up here, I bet it would make\l"
	.string "you work harder!$"

@ Ten Gauntlets: the eleventh plaque, past the other ten
@ (easter-eggs-spec.md, #3).
BattleFrontier_RankingHall_EventScript_EleventhPlaque::
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_ge VAR_RESULT, 10, BattleFrontier_RankingHall_EventScript_EleventhPlaqueScott
	msgbox BattleFrontier_RankingHall_Text_EleventhPlaque, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_EleventhPlaqueScott::
	msgbox BattleFrontier_RankingHall_Text_EleventhPlaqueScott, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_Text_EleventhPlaque:
	.string "GAUNTLET ?? - ??????$"

BattleFrontier_RankingHall_Text_EleventhPlaqueScott:
	.string "SCOTT.\p"
	.string "- Undefeated -$"

BattleFrontier_RankingHall_Text_StevenIntro:
	.string "STEVEN: Ah, there you are. That\n"
	.string "was quite a battle against JUAN.\p"
	.string "I'm STEVEN. A friend of mine,\n"
	.string "WALLACE, asked me to come here\l"
	.string "quietly.\p"
	.string "JUAN was his teacher. WALLACE\n"
	.string "wants to know why he walked away\l"
	.string "from the SOOTOPOLIS GYM to guard a\l"
	.string "mat on this island.\p"
	.string "JUAN wouldn't tell me much. Only\n"
	.string "that SCOTT made him an offer he\l"
	.string "couldn't refuse...\p"
	.string "And that I'd understand, if I\n"
	.string "asked him again after the tenth\l"
	.string "gauntlet.$"

BattleFrontier_RankingHall_Text_StevenAsksBadges:
	.string "STEVEN: I have a favor to ask. May\n"
	.string "I see your BADGE case?$"

BattleFrontier_RankingHall_Text_ShowedBadges:
	.string "{PLAYER} showed STEVEN the BADGE\n"
	.string "case.$"

BattleFrontier_RankingHall_Text_StevenCounterfeit:
	.string "STEVEN: ...\p"
	.string "These aren't GYM BADGES. The\n"
	.string "weight is wrong. The metal is\l"
	.string "wrong.\p"
	.string "I've handled nearly every stone in\n"
	.string "HOENN, and these didn't come from\l"
	.string "any of them.\p"
	.string "Your father was right. They're\n"
	.string "counterfeit.\p"
	.string "But whoever made them knew exactly\n"
	.string "what they were doing. There's\l"
	.string "something set into the alloy...\l"
	.string "I've only ever seen it in one\l"
	.string "place. It looks like a shard of...\p"
	.string "...No. Not until I'm sure.$"

BattleFrontier_RankingHall_Text_StevenPlaque:
	.string "STEVEN: And this plaque. The other\n"
	.string "ten are brass.\p"
	.string "This one is MEGA STONE ore.\p"
	.string "Who mounts a plaque made of MEGA\n"
	.string "STONE ore at the head of a hall...\l"
	.string "and leaves it blank?$"

BattleFrontier_RankingHall_Text_StevenGift:
	.string "STEVEN: I've kept you long enough.\n"
	.string "Here... for the gauntlets ahead.\l"
	.string "It's a stone, of sorts. I think\l"
	.string "you'll find it useful.$"

BattleFrontier_RankingHall_Text_StevenFavor:
	.string "STEVEN: Keep beating these\n"
	.string "gauntlets, {PLAYER}. The closer you\l"
	.string "get to the top, the more SCOTT\l"
	.string "will have to show his hand.\p"
	.string "I'll be around.$"

@ Ten Gauntlets: STEVEN after gauntlet 4 (storyline.md). He confirms the
@ shards, swaps the counterfeit badges for real ones (FLAG_REAL_BADGES, which
@ lets Experience flow - see FrontierStoryAllowsExp()), looks at the
@ SCRAMBLER, and tests the one Pokemon without a chip: the Latias or Latios
@ from Artisan Cave, which must lead the party. It battles a wild ARON with
@ no Bag, switching or running (FLAG_FIGHT_ONLY_BATTLE) and gains Experience.
@ Then he takes it for safekeeping - a Pokemon growing past 50 on SCOTT's
@ island would give the game away - and gives a METAGROSS @ METAGROSSITE,
@ bought from the Broker. The trade isn't a choice.
BattleFrontier_RankingHall_EventScript_StevenG4::
	goto_if_set FLAG_REAL_BADGES, BattleFrontier_RankingHall_EventScript_StevenG4Test
	msgbox BattleFrontier_RankingHall_Text_StevenG4Confirm, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	message BattleFrontier_RankingHall_Text_GotRealBadges
	waitmessage
	waitfanfare
	waitbuttonpress
	setflag FLAG_BADGE08_GET
	setflag FLAG_REAL_BADGES
	checkitem ITEM_SCRAMBLER
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_RankingHall_EventScript_StevenSeesScrambler
	msgbox BattleFrontier_RankingHall_Text_StevenNoticesLati, MSGBOX_DEFAULT
BattleFrontier_RankingHall_EventScript_StevenG4Test::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_LATIAS, BattleFrontier_RankingHall_EventScript_StevenG4Battle
	goto_if_eq VAR_RESULT, SPECIES_LATIOS, BattleFrontier_RankingHall_EventScript_StevenG4Battle
	msgbox BattleFrontier_RankingHall_Text_StevenLatiInFront, MSGBOX_DEFAULT
	release
	end

BattleFrontier_RankingHall_EventScript_StevenG4Battle::
	copyvar VAR_TEMP_1, VAR_RESULT
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox BattleFrontier_RankingHall_Text_StevenTestBattle, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	setflag FLAG_FIGHT_ONLY_BATTLE
	setwildbattle SPECIES_ARON, 10
	dowildbattle
	clearflag FLAG_FIGHT_ONLY_BATTLE
	msgbox BattleFrontier_RankingHall_Text_StevenTestResult, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenTrade, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	call_if_eq VAR_RESULT, SPECIES_LATIOS, BattleFrontier_RankingHall_EventScript_StevenKeepsLatios
	special FrontierFloristTakeMon
	message BattleFrontier_RankingHall_Text_HandedOverLati
	waitmessage
	waitbuttonpress
	givemon SPECIES_METAGROSS, 50, ITEM_METAGROSSITE
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_RankingHall_Text_ReceivedMetagross
	waitmessage
	waitfanfare
	waitbuttonpress
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox BattleFrontier_RankingHall_Text_StevenG4Goodbye, MSGBOX_DEFAULT
	closemessage
	setvar VAR_STEVEN_STORY_STATE, 3
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_RANKING_HALL_STEVEN
	fadescreen FADE_FROM_BLACK
	release
	end

BattleFrontier_RankingHall_EventScript_StevenKeepsLatios::
	setflag FLAG_STEVEN_HAS_LATIOS
	return

BattleFrontier_RankingHall_EventScript_StevenSeesScrambler::
	msgbox BattleFrontier_RankingHall_Text_StevenScrambler, MSGBOX_DEFAULT
	return

BattleFrontier_RankingHall_Text_StevenTakesRainBadge:
	.string "STEVEN: May I borrow one of these?\n"
	.string "I'd like to study it properly.\p"
	.string "This one. The RAIN BADGE... JUAN's\n"
	.string "own badge, from SOOTOPOLIS.\l"
	.string "Fitting.$"

BattleFrontier_RankingHall_Text_GaveRainBadge:
	.string "{PLAYER} handed the RAIN BADGE to\n"
	.string "STEVEN.$"

BattleFrontier_RankingHall_Text_StevenAsksHelp:
	.string "STEVEN: {PLAYER}... I could use\n"
	.string "someone on the inside. Someone\l"
	.string "SCOTT is watching, who can keep an\l"
	.string "eye on him in return.\p"
	.string "Will you work with me?$"

BattleFrontier_RankingHall_Text_AgreedToHelp:
	.string "{PLAYER} agreed to work with\n"
	.string "STEVEN.$"

BattleFrontier_RankingHall_Text_StevenG4Confirm:
	.string "STEVEN: {PLAYER}. I was right.\p"
	.string "There are KEY STONE shards in the\n"
	.string "alloy. And while I carried your\l"
	.string "RAIN BADGE, my own POKéMON stopped\l"
	.string "gaining Experience. Not one point.\p"
	.string "Those badges are feeding on your\n"
	.string "POKéMON's growth.\p"
	.string "So they're going. WALLACE pulled\n"
	.string "some strings with the GYMS.\l"
	.string "Here... the real ones.$"

BattleFrontier_RankingHall_Text_GotRealBadges:
	.string "{PLAYER}'s BADGES were replaced\n"
	.string "with real ones!$"

BattleFrontier_RankingHall_Text_StevenScrambler:
	.string "STEVEN: And LOOKER's device... a\n"
	.string "SCRAMBLER. It jams the PokéNav's\l"
	.string "auto-heal.\p"
	.string "That's DEVON technology. I'd know\n"
	.string "it anywhere. I'll look into how\l"
	.string "FLOTSAM got his hands on one.$"

BattleFrontier_RankingHall_Text_StevenNoticesLati:
	.string "STEVEN: Now... your LATIAS or\n"
	.string "LATIOS. It came from the wild, not\l"
	.string "from SCOTT.\p"
	.string "I want to test something.$"

BattleFrontier_RankingHall_Text_StevenLatiInFront:
	.string "STEVEN: Put your LATIAS or LATIOS\n"
	.string "at the front of your party, then\l"
	.string "come and see me.$"

BattleFrontier_RankingHall_Text_StevenTestBattle:
	.string "STEVEN: I caught this ARON on my\n"
	.string "way here. Battle it with your\l"
	.string "{STR_VAR_1}, and don't hold back.\p"
	.string "Let me patch your team up first.$"

BattleFrontier_RankingHall_Text_StevenTestResult:
	.string "STEVEN: Did you see? It gained\n"
	.string "Experience!\p"
	.string "The badges were holding it back.\n"
	.string "And yet the rest of your POKéMON\l"
	.string "still won't grow, even with real\l"
	.string "badges...\p"
	.string "Something else is holding them\n"
	.string "back. WALLACE and I will find out\l"
	.string "what.$"

BattleFrontier_RankingHall_Text_StevenTrade:
	.string "STEVEN: But this worries me. A\n"
	.string "POKéMON climbing past level 50 on\l"
	.string "SCOTT's island is exactly what\l"
	.string "would make him suspicious.\p"
	.string "You need to keep beating the\n"
	.string "gauntlets as if nothing has\l"
	.string "changed.\p"
	.string "So I'll keep your {STR_VAR_1}\n"
	.string "somewhere safe. In exchange, take\l"
	.string "this. My own edge, for you.\p"
	.string "I bought it from the BROKER, so\n"
	.string "nothing leads back to SCOTT's\l"
	.string "shop.$"

BattleFrontier_RankingHall_Text_HandedOverLati:
	.string "{PLAYER} handed the {STR_VAR_1} over\n"
	.string "to STEVEN.$"

BattleFrontier_RankingHall_Text_ReceivedMetagross:
	.string "{PLAYER} received a METAGROSS\n"
	.string "holding a METAGROSSITE!$"

BattleFrontier_RankingHall_Text_StevenG4Goodbye:
	.string "STEVEN: With that MEGA RING,\n"
	.string "METAGROSS can Mega Evolve. Use it\l"
	.string "well.\p"
	.string "Keep climbing, {PLAYER}. I'll look\n"
	.string "after your {STR_VAR_1} until the\l"
	.string "time is right.$"
