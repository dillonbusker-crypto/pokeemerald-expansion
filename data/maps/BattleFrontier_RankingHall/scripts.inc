BattleFrontier_RankingHall_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_RankingHall_OnTransition
	.byte 0

@ Ten Gauntlets: STEVEN waits by the eleventh plaque once gauntlet 2 is
@ cleared, until the player has spoken to him (frontier-dialogue.md). Keyed
@ off the cleared count, not just the attendant's hint, so a save that
@ cleared gauntlet 2 before this existed still finds him.
BattleFrontier_RankingHall_OnTransition:
	setflag FLAG_TEMP_1
	goto_if_ge VAR_STEVEN_STORY_STATE, 2, BattleFrontier_RankingHall_EventScript_NoSteven
	specialvar VAR_RESULT, GetGauntletsClearedCount
	goto_if_lt VAR_RESULT, 2, BattleFrontier_RankingHall_EventScript_NoSteven
	clearflag FLAG_TEMP_1
BattleFrontier_RankingHall_EventScript_NoSteven:
	end

BattleFrontier_RankingHall_EventScript_Steven::
	lock
	faceplayer
	msgbox BattleFrontier_RankingHall_Text_StevenIntro, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenAsksBadges, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_ShowedBadges, MSGBOX_DEFAULT
	msgbox BattleFrontier_RankingHall_Text_StevenCounterfeit, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_RANKING_HALL_STEVEN, DIR_EAST
	delay 30
	msgbox BattleFrontier_RankingHall_Text_StevenPlaque, MSGBOX_DEFAULT
	applymovement LOCALID_RANKING_HALL_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_RankingHall_Text_StevenGift, MSGBOX_DEFAULT
	giveitem ITEM_EVIOLITE
	msgbox BattleFrontier_RankingHall_Text_StevenFavor, MSGBOX_DEFAULT
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
