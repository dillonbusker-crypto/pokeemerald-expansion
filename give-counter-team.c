// ============================================================================
// Test-team injector for Building 1 boss playtesting
//
// WHERE TO PUT THIS:
//   Paste into src/new_game.c, near the bottom of the file but ABOVE the
//   NewGameInitData() function. Then add one line at the very end of
//   NewGameInitData():
//
//       GiveBuilding1CounterTeam();
//
//   Rebuild with `make -j$(nproc)` and start a NEW GAME. The team appears in
//   your party immediately.
//
// REQUIRED INCLUDES at the top of new_game.c (add any that are missing):
//   #include "constants/items.h"
//   #include "constants/moves.h"
//   #include "constants/abilities.h"
//   #include "pokemon.h"
//
// TO REMOVE LATER: delete the call line. The function can stay harmlessly.
// ============================================================================

struct TestTeamMon
{
    u16 species;
    u16 heldItem;
    u8  abilityNum;   // 0 = first ability, 1 = second, 2 = hidden
    u8  nature;
    u8  evHP, evAtk, evDef, evSpeed, evSpAtk, evSpDef;
    u16 moves[4];
};

static const struct TestTeamMon sBuilding1CounterTeam[6] =
{
    {
        .species = SPECIES_SABLEYE,
        .heldItem = ITEM_LEFTOVERS,
        .abilityNum = 2,              // Prankster (hidden)
        .nature = NATURE_BOLD,
        .evHP = 252, .evAtk = 0, .evDef = 252, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 4,
        .moves = { MOVE_WILL_O_WISP, MOVE_TAUNT, MOVE_RECOVER, MOVE_FOUL_PLAY },
    },
    {
        .species = SPECIES_FERROSEED,
        .heldItem = ITEM_METAL_COAT,
        .abilityNum = 0,              // Iron Barbs
        .nature = NATURE_RELAXED,
        .evHP = 252, .evAtk = 0, .evDef = 252, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 4,
        .moves = { MOVE_GYRO_BALL, MOVE_SEED_BOMB, MOVE_PROTECT, MOVE_CURSE },
    },
    {
        .species = SPECIES_CHINCHOU,
        .heldItem = ITEM_MYSTIC_WATER,
        .abilityNum = 0,              // Volt Absorb
        .nature = NATURE_MODEST,
        .evHP = 252, .evAtk = 0, .evDef = 4, .evSpeed = 0, .evSpAtk = 252, .evSpDef = 0,
        .moves = { MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_CONFUSE_RAY },
    },
    {
        .species = SPECIES_PAWNIARD,
        .heldItem = ITEM_BLACK_GLASSES,
        .abilityNum = 0,              // Defiant
        .nature = NATURE_JOLLY,
        .evHP = 0, .evAtk = 252, .evDef = 4, .evSpeed = 252, .evSpAtk = 0, .evSpDef = 0,
        .moves = { MOVE_SUCKER_PUNCH, MOVE_KNOCK_OFF, MOVE_IRON_HEAD, MOVE_SWORDS_DANCE },
    },
    {
        .species = SPECIES_MARSHTOMP,
        .heldItem = ITEM_SOFT_SAND,
        .abilityNum = 0,              // Torrent
        .nature = NATURE_ADAMANT,
        .evHP = 252, .evAtk = 252, .evDef = 4, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 0,
        .moves = { MOVE_EARTHQUAKE, MOVE_WATERFALL, MOVE_ROCK_SLIDE, MOVE_PROTECT },
    },
    {
        .species = SPECIES_PARASECT,
        .heldItem = ITEM_MIRACLE_SEED,
        .abilityNum = 1,              // Dry Skin
        .nature = NATURE_ADAMANT,
        .evHP = 252, .evAtk = 252, .evDef = 4, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 0,
        .moves = { MOVE_SPORE, MOVE_SEED_BOMB, MOVE_X_SCISSOR, MOVE_LEECH_LIFE },
    },
};

void GiveBuilding1CounterTeam(void)
{
    u32 i, j;

    ZeroPlayerPartyMons();

    for (i = 0; i < 6; i++)
    {
        const struct TestTeamMon *src = &sBuilding1CounterTeam[i];
        struct Pokemon *mon = &gPlayerParty[i];
        u32 value;

        // Level 50, all IVs 31, correct nature
        CreateMonWithNature(mon, src->species, 50, 31, src->nature);

        value = src->abilityNum;
        SetMonData(mon, MON_DATA_ABILITY_NUM, &value);

        value = src->heldItem;
        SetMonData(mon, MON_DATA_HELD_ITEM, &value);

        value = src->evHP;    SetMonData(mon, MON_DATA_HP_EV, &value);
        value = src->evAtk;   SetMonData(mon, MON_DATA_ATK_EV, &value);
        value = src->evDef;   SetMonData(mon, MON_DATA_DEF_EV, &value);
        value = src->evSpeed; SetMonData(mon, MON_DATA_SPEED_EV, &value);
        value = src->evSpAtk; SetMonData(mon, MON_DATA_SPATK_EV, &value);
        value = src->evSpDef; SetMonData(mon, MON_DATA_SPDEF_EV, &value);

        for (j = 0; j < 4; j++)
            SetMonMoveSlot(mon, src->moves[j], j);

        CalculateMonStats(mon);
    }

    gPlayerPartyCount = 6;
}
