#include "global.h"
#include "test/battle.h"

// Ten Gauntlets: permanent Megas (the Replica Crown, storyline.md). A Mega
// that starts a battle as one stays a Mega: it doesn't revert on fainting or
// at the end of the battle, and it can't Mega Evolve again. A Pokemon that
// Mega Evolves during the battle still reverts as usual (the engine's own
// tests in test/battle/form_change/mega_evolution.c cover that).

SINGLE_BATTLE_TEST("Ten Gauntlets: a permanent Mega stays a Mega after the battle")
{
    GIVEN {
        PLAYER(SPECIES_CHARIZARD_MEGA_X) { Item(ITEM_LEFTOVERS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_CHARIZARD_MEGA_X);
    }
}

SINGLE_BATTLE_TEST("Ten Gauntlets: a permanent Mega stays a Mega after fainting")
{
    GIVEN {
        PLAYER(SPECIES_VENUSAUR_MEGA) { HP(1); Item(ITEM_LEFTOVERS); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); SEND_OUT(player, 1); }
        TURN { USE_ITEM(player, ITEM_REVIVE, 0); }
        TURN { SWITCH(player, 0); }
    } THEN {
        EXPECT_EQ(player->species, SPECIES_VENUSAUR_MEGA);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_VENUSAUR_MEGA);
    }
}

SINGLE_BATTLE_TEST("Ten Gauntlets: a permanent Mega can't Mega Evolve again")
{
    GIVEN {
        PLAYER(SPECIES_CHARIZARD_MEGA_X) { Item(ITEM_CHARIZARDITE_Y); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
    } THEN {
        EXPECT_EQ(player->species, SPECIES_CHARIZARD_MEGA_X);
    }
}

// A permanent Mega doesn't use up the trainer's Mega Evolution for the battle.
SINGLE_BATTLE_TEST("Ten Gauntlets: a permanent Mega leaves the battle's Mega Evolution free")
{
    GIVEN {
        PLAYER(SPECIES_CHARIZARD_MEGA_X) { Item(ITEM_LEFTOVERS); }
        PLAYER(SPECIES_VENUSAUR) { Item(ITEM_VENUSAURITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { SWITCH(player, 1); }
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), SPECIES_CHARIZARD_MEGA_X);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), SPECIES_VENUSAUR);
    }
}

// The Replica Crown turns a permanent Mega back with its FORM_CHANGE_FAINT
// target, so every Mega needs one that isn't itself a Mega.
TEST("Ten Gauntlets: every Mega has a base form the Replica Crown can return it to")
{
    u32 megas = 0;
    for (enum Species species = 1; species < NUM_SPECIES; species++)
    {
        if (!IsSpeciesEnabled(species) || !gSpeciesInfo[species].isMegaEvolution)
            continue;
        megas++;
        struct Pokemon mon;
        CreateMon(&mon, species, 50, 0, OTID_STRUCT_PLAYER_ID);
        enum Species base = GetFormChangeTargetSpecies(&mon, FORM_CHANGE_FAINT);
        if (base == species || gSpeciesInfo[base].isMegaEvolution)
            Test_ExitWithResult(TEST_RESULT_FAIL, __LINE__, "%s:%d: species %d has no base form", gTestRunnerState.test->filename, __LINE__, species);
    }
    EXPECT_GT(megas, 0);
}
