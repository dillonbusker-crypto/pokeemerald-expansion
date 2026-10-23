RustboroCity_PokemonSchool_MapScripts::
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonSchool_EventScript_GameboyKid1Ending
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonSchool_EventScript_GameboyKid1Freed
	msgbox RustboroCity_PokemonSchool_Text_GameboyKid1, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1Ending::
	msgbox RustboroCity_PokemonSchool_Text_GameboyKid1Ending, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1Freed::
	msgbox RustboroCity_PokemonSchool_Text_GameboyKid1Freed, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonSchool_EventScript_GameboyKid2Ending
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonSchool_EventScript_GameboyKid2Freed
	msgbox RustboroCity_PokemonSchool_Text_GameboyKid2, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2Ending::
	msgbox RustboroCity_PokemonSchool_Text_GameboyKid2Ending, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2Freed::
	msgbox RustboroCity_PokemonSchool_Text_GameboyKid2Freed, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonSchool_EventScript_RichBoyEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonSchool_EventScript_RichBoyFreed
	msgbox RustboroCity_PokemonSchool_Text_RichBoy, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoyEnding::
	msgbox RustboroCity_PokemonSchool_Text_RichBoyEnding, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoyFreed::
	msgbox RustboroCity_PokemonSchool_Text_RichBoyFreed, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	checktrainerflag TRAINER_ENDGAME_ROXANNE
	goto_if FALSE, RustboroCity_PokemonSchool_EventScript_LassOld
	goto_if_set FLAG_GIRATINA_CAUGHT, RustboroCity_PokemonSchool_EventScript_LassTearClosed
	msgbox RustboroCity_PokemonSchool_Text_LassTear, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_LassOld::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonSchool_EventScript_LassOldEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonSchool_EventScript_LassOldFreed
	msgbox RustboroCity_PokemonSchool_Text_LassOld, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_LassOldEnding::
	msgbox RustboroCity_PokemonSchool_Text_LassOldEnding, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_LassOldFreed::
	msgbox RustboroCity_PokemonSchool_Text_LassOldFreed, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_LassTearClosed::
	msgbox RustboroCity_PokemonSchool_Text_LassTearClosed, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonSchool_EventScript_SchoolKidMEnding
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonSchool_EventScript_SchoolKidMFreed
	msgbox RustboroCity_PokemonSchool_Text_SchoolKidM, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidMEnding::
	msgbox RustboroCity_PokemonSchool_Text_SchoolKidMEnding, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidMFreed::
	msgbox RustboroCity_PokemonSchool_Text_SchoolKidMFreed, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_TeacherLesson
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_QUICK_CLAW
	goto RustboroCity_PokemonSchool_EventScript_TeacherLesson

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherLesson::
	faceplayer
	goto_if_set FLAG_RUSTBORO_RAISE_3, RustboroCity_PokemonSchool_EventScript_TeacherLessonUsed
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonOffer, MSGBOX_DEFAULT
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_PokemonSchool_EventScript_TeacherLessonNotNow
RustboroCity_PokemonSchool_EventScript_TeacherLessonPick::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonWhich, MSGBOX_DEFAULT
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, RustboroCity_PokemonSchool_EventScript_TeacherLessonNotNow
	setvar VAR_0x8005, 55
	special RaiseMonToLevel
	goto_if_eq VAR_RESULT, 1, RustboroCity_PokemonSchool_EventScript_TeacherLessonEgg
	goto_if_eq VAR_RESULT, 2, RustboroCity_PokemonSchool_EventScript_TeacherLessonTooStrong
	setflag FLAG_RUSTBORO_RAISE_3
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	playfanfare MUS_LEVEL_UP
	message RustboroCity_PokemonSchool_Text_TeacherLessonGrew
	waitmessage
	waitfanfare
	waitbuttonpress
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonDone, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherFinish

RustboroCity_PokemonSchool_EventScript_TeacherLessonEgg::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonEgg, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherLessonPick
	end

RustboroCity_PokemonSchool_EventScript_TeacherLessonTooStrong::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonTooStrong, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherLessonPick
	end

RustboroCity_PokemonSchool_EventScript_TeacherLessonNotNow::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonNotNow, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherFinish

RustboroCity_PokemonSchool_EventScript_TeacherLessonUsed::
	specialvar VAR_RESULT, GetStoryGossipStage
	goto_if_ge VAR_RESULT, GOSSIP_ENDING, RustboroCity_PokemonSchool_EventScript_TeacherLessonUsedEnding
	goto_if_ge VAR_RESULT, GOSSIP_SIPHON, RustboroCity_PokemonSchool_EventScript_TeacherLessonUsedSiphon
	goto_if_ge VAR_RESULT, GOSSIP_DEVON_FREED, RustboroCity_PokemonSchool_EventScript_TeacherLessonUsedFreed
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonUsed, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherFinish

RustboroCity_PokemonSchool_EventScript_TeacherLessonUsedEnding::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonUsedEnding, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherFinish

RustboroCity_PokemonSchool_EventScript_TeacherLessonUsedSiphon::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonUsedSiphon, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherFinish

RustboroCity_PokemonSchool_EventScript_TeacherLessonUsedFreed::
	msgbox RustboroCity_PokemonSchool_Text_TeacherLessonUsedFreed, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_TeacherFinish

RustboroCity_PokemonSchool_EventScript_TeacherFinish::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
	.string "The blackboard lists status changes\n"
	.string "that may affect POKéMON in battle.$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
	.string "Which topic do you want to read?$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
	.string "If a POKéMON is poisoned, it will\n"
	.string "steadily lose HP.\p"
	.string "The effects of poison remain after\n"
	.string "a battle.\p"
	.string "A poisoned POKéMON's HP will drop\n"
	.string "while it is traveling.\p"
	.string "Heal a poisoning using an ANTIDOTE.$"

RustboroCity_PokemonSchool_Text_ExplainParalysis:
	.string "If a POKéMON becomes paralyzed,\n"
	.string "its SPEED drops.\p"
	.string "It may also not be able to move while\n"
	.string "it is in battle.\p"
	.string "Paralysis remains after battle.\n"
	.string "Cure it using a PARLYZ HEAL.$"

RustboroCity_PokemonSchool_Text_ExplainSleep:
	.string "If a POKéMON falls asleep, it will be\n"
	.string "unable to attack.\p"
	.string "A POKéMON may wake up on its own,\n"
	.string "but if a battle ends while it is\l"
	.string "sleeping, it will stay asleep.\p"
	.string "Wake it up using an AWAKENING.$"

RustboroCity_PokemonSchool_Text_ExplainBurn:
	.string "A burn reduces ATTACK power, and it\n"
	.string "steadily reduces the victim's HP.\p"
	.string "A burn lingers after battle.\n"
	.string "Cure a burn using a BURN HEAL.$"

RustboroCity_PokemonSchool_Text_ExplainFreeze:
	.string "If a POKéMON is frozen, it becomes\n"
	.string "completely helpless.\p"
	.string "It will remain frozen after battle.\n"
	.string "Thaw it out using an ICE HEAL.$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
	.string "Students who skipped their studies\n"
	.string "used to get a taste of my QUICK CLAW.\p"
	.string "But the desks are empty these days.\n"
	.string "There's no one left to confiscate\l"
	.string "from. Here, you take it.$"

RustboroCity_PokemonSchool_Text_TeacherLessonOffer:
	.string "EXP, battles, badges… I taught them\n"
	.string "all of it. Then it stopped working.\p"
	.string "I don't know what to teach any more.\n"
	.string "But I still have one lesson: my night\l"
	.string "class. The one nobody attends.\p"
	.string "One POKéMON, every drill in the book,\n"
	.string "in a single sitting. It graduates at\l"
	.string "LV. 55. I only have time for one.$"

RustboroCity_PokemonSchool_Text_TeacherLessonAsk:
	.string "Would you like to enrol a POKéMON?$"

RustboroCity_PokemonSchool_Text_TeacherLessonWhich:
	.string "Which POKéMON will be attending?$"

RustboroCity_PokemonSchool_Text_TeacherLessonNotNow:
	.string "The door is open whenever you're\n"
	.string "ready. It's not as if the room is\l"
	.string "full.$"

RustboroCity_PokemonSchool_Text_TeacherLessonEgg:
	.string "An EGG can't sit a lesson. It can't\n"
	.string "even sit up. Choose another.$"

RustboroCity_PokemonSchool_Text_TeacherLessonTooStrong:
	.string "That one is past LV. 55 already. It\n"
	.string "could teach my class. Choose another.$"

RustboroCity_PokemonSchool_Text_TeacherLessonGrew:
	.string "The lesson ran late into the night.\p"
	.string "{STR_VAR_1} grew to LV. 55!$"

RustboroCity_PokemonSchool_Text_TeacherLessonDone:
	.string "Top marks. There's nothing left I can\n"
	.string "teach it. Not that there was much\l"
	.string "when I started.$"

RustboroCity_PokemonSchool_Text_TeacherLessonUsed:
	.string "That was my last good lesson. The rest\n"
	.string "is waiting for someone to tell me what\l"
	.string "to teach.$"

RustboroCity_PokemonSchool_Text_TeacherLessonUsedFreed:
	.string "They tell me the ELITE FOUR are gone.\n"
	.string "Maybe I'll find my syllabus yet.$"

RustboroCity_PokemonSchool_Text_TeacherLessonUsedSiphon:
	.string "They say the FRONTIER's POKéMON can\n"
	.string "grow again. EXP matters once more!\p"
	.string "I'm dusting off my old lesson plans.$"

RustboroCity_PokemonSchool_Text_TeacherLessonUsedEnding:
	.string "A new syllabus arrived from the new\n"
	.string "DEVON. Nothing about badges.\p"
	.string "The first chapter is “bond”. I think\n"
	.string "I can teach that.$"

RustboroCity_PokemonSchool_Text_GameboyKid1:
	.string "I'm trading POKéMON with my friend\n"
	.string "right now.\p"
	.string "The teacher doesn't mind. Nobody's\n"
	.string "told him what to teach, so he lets\l"
	.string "us.$"

RustboroCity_PokemonSchool_Text_GameboyKid1Freed:
	.string "I'm trading POKéMON with my friend.\p"
	.string "My cousin says the FRONTIER gives\n"
	.string "everything away now. Even POKéMON!\l"
	.string "That's cheating, right?$"

RustboroCity_PokemonSchool_Text_GameboyKid1Ending:
	.string "I'm trading POKéMON with my friend\n"
	.string "right now.\p"
	.string "We're trading back what we swapped\n"
	.string "during the DEVON scare. Some things\l"
	.string "you shouldn't give away.$"

RustboroCity_PokemonSchool_Text_GameboyKid2:
	.string "I always wanted a SEEDOT.\p"
	.string "The man in the house across the way\n"
	.string "won't trade me his. He says he's too\l"
	.string "attached.$"

RustboroCity_PokemonSchool_Text_GameboyKid2Freed:
	.string "He still won't trade me his SEEDOT.\p"
	.string "I respect that. I'll just look at it\n"
	.string "a lot.$"

RustboroCity_PokemonSchool_Text_GameboyKid2Ending:
	.string "He still won't trade me his SEEDOT.\n"
	.string "But he lets me visit it.\p"
	.string "I think that's a fair deal.$"

RustboroCity_PokemonSchool_Text_RichBoy:
	.string "My father owns DEVON shares.\n"
	.string "I'm told not to mention it this week.\p"
	.string "POKéMON can hold items, but they don't\n"
	.string "know what to do with money.\l"
	.string "Neither does Father, lately.$"

RustboroCity_PokemonSchool_Text_RichBoyFreed:
	.string "My father sold his DEVON shares the day\n"
	.string "before the news. He calls it luck.\p"
	.string "I'm learning what that word means.$"

RustboroCity_PokemonSchool_Text_RichBoyEnding:
	.string "Father bought DEVON shares back at the\n"
	.string "new price. He says it's for the\l"
	.string "children.\p"
	.string "I'm the child. I'm still not sure\n"
	.string "what I did.$"

RustboroCity_PokemonSchool_Text_LassOld:
	.string "Everyone at school keeps talking\n"
	.string "about the ELITE FOUR.\p"
	.string "Our teacher says, “We'll take that up\n"
	.string "tomorrow.” It has been tomorrow for\l"
	.string "a week.$"

RustboroCity_PokemonSchool_Text_LassOldFreed:
	.string "The ELITE FOUR are gone. Our teacher\n"
	.string "says, “We'll take that up tomorrow.”\p"
	.string "I think he means it this time.$"

RustboroCity_PokemonSchool_Text_LassOldEnding:
	.string "We had a real lesson today. Nothing\n"
	.string "about badges, nothing about scores.\p"
	.string "I understood all of it. That's never\n"
	.string "happened before.$"

RustboroCity_PokemonSchool_Text_SchoolKidM:
	.string "A POKéMON holding a BERRY will heal\n"
	.string "itself…\p"
	.string "I'm trying to take notes, but the\n"
	.string "teacher doesn't know what to teach.\l"
	.string "So I'm writing down what he doesn't\l"
	.string "say. There's more of it.$"

RustboroCity_PokemonSchool_Text_SchoolKidMFreed:
	.string "My notes are mostly arrows now.\n"
	.string "Arrows from DEVON to everything.$"

RustboroCity_PokemonSchool_Text_SchoolKidMEnding:
	.string "My notes are getting longer again.\n"
	.string "The teacher is saying things!\p"
	.string "Boy, it sure is hard taking notes\n"
	.string "down…$"

RustboroCity_PokemonSchool_Text_StudentsNotes:
	.string "It's this student's notebook…\p"
	.string "POKéMON are to be caught using\n"
	.string "POKé BALLS.\p"
	.string "Up to six POKéMON can accompany\n"
	.string "a TRAINER.\p"
	.string "A TRAINER is someone who catches\n"
	.string "POKéMON, raises them, and battles\l"
	.string "with them.\p"
	.string "A TRAINER's mission is to defeat\n"
	.string "the strong TRAINERS who await\l"
	.string "challengers in POKéMON GYMS.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
	.string "Hello? Didn't we meet before?\n"
	.string "I think back in PETALBURG CITY.\p"
	.string "Let me introduce myself.\n"
	.string "My name's SCOTT.\p"
	.string "I've been traveling everywhere in\n"
	.string "search of outstanding TRAINERS.\p"
	.string "More specifically, I'm looking for\n"
	.string "POKéMON battle experts.\p"
	.string "So, what brings you to this SCHOOL?\n"
	.string "Are you a TRAINER, too?\p"
	.string "The first thing you should do is to\n"
	.string "have a POKéMON learn the move CUT.\p"
	.string "If I remember correctly, someone in\n"
	.string "this town has CUT.$"

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
	.string "SCOTT: Hmm…\p"
	.string "The talent levels of the students here\n"
	.string "are unknown. The potential's there.$"

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
	.string "SCOTT: Oh, what's that?\p"
	.string "It's a STONE BADGE, isn't it?\n"
	.string "That's pretty impressive, I'd say.\p"
	.string "But, you know, I would've loved to see\n"
	.string "you in battle.\p"
	.string "It's hard to tell what you're like as\n"
	.string "a TRAINER from a LEAGUE BADGE.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
	.string "Hello? Didn't we meet before?\n"
	.string "I think back in PETALBURG CITY.\p"
	.string "Let me introduce myself.\n"
	.string "My name's SCOTT.\p"
	.string "I've been traveling everywhere in\n"
	.string "search of outstanding TRAINERS.\p"
	.string "More specifically, I'm looking for\n"
	.string "POKéMON battle experts.\p"
	.string "Oh, what's that?\n"
	.string "It's a STONE BADGE, isn't it?\p"
	.string "That's pretty impressive, I'd say, for\n"
	.string "a starting TRAINER like yourself.\p"
	.string "But, you know, I would've loved to see\n"
	.string "you in battle.\p"
	.string "It's hard to tell what you're like as\n"
	.string "a TRAINER from a LEAGUE BADGE.$"


@ Ten Gauntlets: "The Tear" (sprint-a-giratina.md). The lass after ROXANNE's
@ rematch, then once GIRATINA is caught.
RustboroCity_PokemonSchool_Text_LassTear:
	.string "My big brother says RUSTURF TUNNEL\n"
	.string "goes upward now.\p"
	.string "It runs under a mountain! A tunnel\n"
	.string "can't go up and still come out the\l"
	.string "other side.\p"
	.string "He says he isn't joking. He looked\n"
	.string "a little green.$"

RustboroCity_PokemonSchool_Text_LassTearClosed:
	.string "My brother says RUSTURF TUNNEL goes\n"
	.string "down again, like a tunnel should.\p"
	.string "He seems a little disappointed.$"
