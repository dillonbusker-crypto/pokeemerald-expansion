#include "global.h"
#include "test/battle.h"

// Ten Gauntlets: ROXANNE's endgame rematch (TRAINER_ENDGAME_ROXANNE) lists
// Zygarde-Complete holding Zygardite, her one Mega. No other trainer Mega
// Evolves from the Complete form, so these check that the opponent's Zygarde
// does, keeps Mega Zygarde's ability, and stays a Mega after switching.

SINGLE_BATTLE_TEST("Ten Gauntlets: an enemy Zygarde-Complete Mega Evolves with Zygardite")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ZYGARDE_COMPLETE) { Item(ITEM_ZYGARDITE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_POWER_CONSTRUCT);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, opponent);
    } THEN {
        EXPECT_EQ(opponent->species, SPECIES_ZYGARDE_MEGA);
        EXPECT_EQ(opponent->ability, ABILITY_AURA_BREAK);
    }
}

SINGLE_BATTLE_TEST("Ten Gauntlets: an enemy Mega Zygarde stays a Mega after switching out and back")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ZYGARDE_COMPLETE) { Item(ITEM_ZYGARDITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
        TURN { SWITCH(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, opponent);
    } THEN {
        EXPECT_EQ(opponent->species, SPECIES_ZYGARDE_MEGA);
        EXPECT_EQ(opponent->ability, ABILITY_AURA_BREAK);
    }
}

// The Gym leaders' AI (minus the switching flags, which a one-Pokemon test
// doesn't need) chooses to Mega Evolve on its own.
AI_SINGLE_BATTLE_TEST("Ten Gauntlets: the AI Mega Evolves its Zygarde-Complete")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ZYGARDE_COMPLETE) { Item(ITEM_ZYGARDITE); Moves(MOVE_EARTH_POWER); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_EARTH_POWER, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, opponent);
    } THEN {
        EXPECT_EQ(opponent->species, SPECIES_ZYGARDE_MEGA);
    }
}

// ROXANNE's Zygarde comes in last, after a faint: it Mega Evolves on its
// first turn out.
AI_SINGLE_BATTLE_TEST("Ten Gauntlets: the AI Mega Evolves a Zygarde-Complete sent out after a faint")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Speed(1); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_ZYGARDE_COMPLETE) { Item(ITEM_ZYGARDITE); Speed(50); Moves(MOVE_EARTH_POWER); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); EXPECT_SEND_OUT(opponent, 1); }
        TURN { EXPECT_MOVE(opponent, MOVE_EARTH_POWER, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, opponent);
    } THEN {
        EXPECT_EQ(opponent->species, SPECIES_ZYGARDE_MEGA);
    }
}
