# Gauntlet 2 Setup — Claude Code Prompt & Code

Two parts: a prompt to paste into Claude Code, and the replacement C function.

---

## PART 1 — Paste this into Claude Code

> Set up the gauntlet 2 boss fight for playtesting, same pattern as the Winona
> test. Read `gauntlet-02.md` for the full details.
>
> **Boss trainer.** Replace whichever sacrificial trainer we used for Winona
> with Tidewarden Juan, the gauntlet 2 boss. The six Pokémon, natures, EVs,
> abilities, items and movesets are all in `gauntlet-02.md` under "Boss —
> Tidewarden Juan". All at level 50 with 31 IVs.
>
> **This is a DOUBLE battle, not a single.** Gauntlet 2 is the first doubles
> facility. Make sure the trainer's double-battle field is set, and if the
> trainer you're replacing was a single-battle trainer, either pick a
> double-battle trainer instead or set the flag and confirm the overworld
> script still works. Tell me which approach you took.
>
> **AI flags:** same as Winona — full offensive intelligence, smart replacement
> choice, proactive switching, and omniscient. No ace flag. Also check whether
> this version of the expansion has a separate doubles-awareness AI flag and
> enable it if so.
>
> **Player team.** Replace the body of the counter-team function in
> `src/new_game.c` with the gauntlet 2 benchmark team — the code is in part 2
> of this file. Note the zeroSpeedIV field: this is a Trick Room team, so six
> Pokémon need their Speed IV set to 0 rather than 31, because under Trick Room
> slower moves first. Don't skip that, it inverts the whole strategy.
>
> **Keep** the exp-gain and obedience disables from last time.
>
> **Verify before building:** grep the actual species, move, item and ability
> constants rather than trusting the names I wrote. Check the abilityNum values
> against the species data — Gastrodon needs Storm Drain, Amoonguss needs
> Regenerator, Mudsdale needs Stamina, Pelipper needs Drizzle, Toxicroak needs
> Dry Skin. Several of those are second or hidden abilities and the numbering
> matters.
>
> Then rebuild and tell me what changed.

---

## PART 2 — Replacement counter-team function

Replace the existing `sBuilding1CounterTeam` array and
`GiveBuilding1CounterTeam` function in `src/new_game.c` with this. The call
site at the end of `NewGameInitData()` needs its name updated to match.

```c
// ============================================================================
// Gauntlet 2 benchmark counter-team (anti-rain, Trick Room based)
//
// NOTE: zeroSpeedIV. This team wins by being SLOWER than the boss under
// Trick Room. Brave/Quiet/Relaxed natures lower Speed, but the IV must also
// be floored to 0 or these Pokemon are still too fast. Getting this wrong
// silently inverts the entire strategy.
// ============================================================================

struct TestTeamMon
{
    u16 species;
    u16 heldItem;
    u8  abilityNum;    // 0 = first, 1 = second, 2 = hidden — VERIFY THESE
    u8  nature;
    u8  zeroSpeedIV;   // TRUE = Speed IV 0 for Trick Room
    u8  evHP, evAtk, evDef, evSpeed, evSpAtk, evSpDef;
    u16 moves[4];
};

static const struct TestTeamMon sBuilding2CounterTeam[6] =
{
    {
        .species = SPECIES_BRONZONG,
        .heldItem = ITEM_SITRUS_BERRY,
        .abilityNum = 0,              // Levitate
        .nature = NATURE_RELAXED,
        .zeroSpeedIV = TRUE,
        .evHP = 252, .evAtk = 0, .evDef = 252, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 4,
        .moves = { MOVE_TRICK_ROOM, MOVE_GYRO_BALL, MOVE_ZEN_HEADBUTT, MOVE_PROTECT },
    },
    {
        .species = SPECIES_GASTRODON,
        .heldItem = ITEM_PASSHO_BERRY,
        .abilityNum = 1,              // Storm Drain
        .nature = NATURE_QUIET,
        .zeroSpeedIV = TRUE,
        .evHP = 252, .evAtk = 0, .evDef = 4, .evSpeed = 0, .evSpAtk = 252, .evSpDef = 0,
        .moves = { MOVE_MUDDY_WATER, MOVE_EARTH_POWER, MOVE_RECOVER, MOVE_PROTECT },
    },
    {
        .species = SPECIES_LANTURN,
        .heldItem = ITEM_WACAN_BERRY,
        .abilityNum = 0,              // Volt Absorb
        .nature = NATURE_QUIET,
        .zeroSpeedIV = TRUE,
        .evHP = 252, .evAtk = 0, .evDef = 4, .evSpeed = 0, .evSpAtk = 252, .evSpDef = 0,
        .moves = { MOVE_THUNDER, MOVE_ICE_BEAM, MOVE_SURF, MOVE_PROTECT },
    },
    {
        .species = SPECIES_AMOONGUSS,
        .heldItem = ITEM_LEFTOVERS,
        .abilityNum = 2,              // Regenerator (hidden)
        .nature = NATURE_RELAXED,
        .zeroSpeedIV = TRUE,
        .evHP = 252, .evAtk = 0, .evDef = 252, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 4,
        .moves = { MOVE_SPORE, MOVE_RAGE_POWDER, MOVE_SLUDGE_BOMB, MOVE_PROTECT },
    },
    {
        .species = SPECIES_VIKAVOLT,
        .heldItem = ITEM_MAGNET,
        .abilityNum = 0,              // Levitate
        .nature = NATURE_QUIET,
        .zeroSpeedIV = TRUE,
        .evHP = 252, .evAtk = 0, .evDef = 4, .evSpeed = 0, .evSpAtk = 252, .evSpDef = 0,
        .moves = { MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_PROTECT },
    },
    {
        .species = SPECIES_MUDSDALE,
        .heldItem = ITEM_MYSTIC_WATER,
        .abilityNum = 1,              // Stamina
        .nature = NATURE_BRAVE,
        .zeroSpeedIV = TRUE,
        .evHP = 252, .evAtk = 252, .evDef = 4, .evSpeed = 0, .evSpAtk = 0, .evSpDef = 0,
        .moves = { MOVE_HIGH_HORSEPOWER, MOVE_HEAVY_SLAM, MOVE_ROCK_SLIDE, MOVE_PROTECT },
    },
};

void GiveBuilding2CounterTeam(void)
{
    u32 i, j;

    ZeroPlayerPartyMons();

    for (i = 0; i < 6; i++)
    {
        const struct TestTeamMon *src = &sBuilding2CounterTeam[i];
        struct Pokemon *mon = &gPlayerParty[i];
        u32 value;

        CreateMonWithNature(mon, src->species, 50, 31, src->nature);

        if (src->zeroSpeedIV)
        {
            value = 0;
            SetMonData(mon, MON_DATA_SPEED_IV, &value);
        }

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
```

---

## Things likely to need fixing

**Ability numbers.** Second and hidden abilities are where this breaks. Storm
Drain, Regenerator, Stamina, Drizzle and Dry Skin are all non-default slots.
If Gastrodon comes out with Sticky Hold, the whole counter-strategy collapses
and it won't be obvious why.

**Double battle wiring.** This is the first doubles fight in the project. The
trainer's double-battle field has to be set, and some overworld trainer scripts
assume single battles. If it fights as a single, that's the cause.

**Speed IVs.** Check in-game via the summary screen or debug menu that the
counter-team is genuinely slow. If Trick Room isn't reversing the matchup, this
is the first thing to check.

**Move names.** `MOVE_HIGH_HORSEPOWER`, `MOVE_RAGE_POWDER`, `MOVE_MUDDY_WATER`
and `MOVE_TRICK_ROOM` should all exist, but grep before trusting.
