#include "global.h"
#include "event_data.h"
#include "test/battle.h"

// Ten Gauntlets: the Artisan Cave Latios/Latias battle (storyline.md). Fight
// and Run are refused (FLAG_CATCH_ONLY_BATTLE), the encounter is forced
// shiny (P_FLAG_FORCE_SHINY - a test can set only one flag, so Shiny() here),
// and the player catches it with a MASTER BALL.
WILD_BATTLE_TEST("Ten Gauntlets: Master Ball catches the Artisan Cave Latios")
{
    GIVEN {
        FLAG_SET(FLAG_CATCH_ONLY_BATTLE);
        PLAYER(SPECIES_WOBBUFFET) { Level(50); }
        OPPONENT(SPECIES_LATIOS) { Level(50); Shiny(TRUE); }
    } WHEN {
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_SPECIAL, B_ANIM_BALL_THROW, player);
    } THEN {
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_CAUGHT);
    }
}

// Control: the same catch without the catch-only rule.
WILD_BATTLE_TEST("Ten Gauntlets: Master Ball catch control, no catch-only flag")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(50); }
        OPPONENT(SPECIES_LATIOS) { Level(50); Shiny(TRUE); }
    } WHEN {
        TURN { USE_ITEM(player, ITEM_MASTER_BALL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_SPECIAL, B_ANIM_BALL_THROW, player);
    } THEN {
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_CAUGHT);
    }
}

// STEVEN's gauntlet 4 test (FLAG_FIGHT_ONLY_BATTLE): the player can only
// fight, and the wild ARON's own turns must still go through.
WILD_BATTLE_TEST("Ten Gauntlets: fight-only battle against a wild Aron finishes")
{
    GIVEN {
        FLAG_SET(FLAG_FIGHT_ONLY_BATTLE);
        PLAYER(SPECIES_LATIAS) { Level(50); }
        OPPONENT(SPECIES_ARON) { Level(10); }
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHIC); } // Sturdy holds on at 1 HP
        TURN { MOVE(player, MOVE_PSYCHIC); }
    } SCENE {
        MESSAGE("The wild Aron endured the hit!");
        MESSAGE("The wild Aron fainted!");
    } THEN {
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_WON);
    }
}
