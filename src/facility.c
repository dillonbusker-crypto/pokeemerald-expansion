// ============================================================================
// Ten Gauntlets facility run loop. See run-loop-spec.md for the full design.
//
// Gauntlet 1 ("Little League", gauntlet-01.md) has its full twelve-team
// pool and boss. Gauntlet 2 ("The Second Slot", gauntlet-02.md) has 6 of
// its twelve pool teams for now (A1, A2, B4, B6, C7, D11) - the shuffle
// below operates on whatever poolSize the active gauntlet declares, so
// adding the remaining six later is a data change only. Gauntlets 3 and 4
// use the Battle Tower's other two mats; gauntlet 5 ("The Main Event",
// gauntlet-05.md) is the first outside the Tower, run from the Battle Dome
// lobby with the same shared run-loop scripts; gauntlet 6 ("The Assembly
// Line", gauntlet-06.md) runs the same way from the Battle Factory lobby.
// ============================================================================

#include "global.h"
#include "facility.h"
#include "facility_shop.h"
#include "assertf.h"
#include "data.h"
#include "item.h"
#include "event_data.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "frontier_util.h"
#include "pokemon.h"
#include "random.h"
#include "save.h"
#include "strings.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/maps.h"
#include "constants/pokeball.h"
#include "constants/region_map_sections.h"
#include "constants/trainers.h"

#define FACILITY_MAX_POOL_SIZE 12

// Every trainer ID needs its own "defeated" flag below MAX_TRAINERS_COUNT -
// past it, the flag lands on a system flag and the ID is read as a battle
// partner. See the note above TRAINERS_COUNT_EMERALD in
// include/constants/opponents.h. Fails the build instead of failing silently.
STATIC_ASSERT(TRAINERS_COUNT <= MAX_TRAINERS_COUNT, TrainerIdsMustFitBelowMaxTrainersCount);

struct FacilityGauntletData
{
    const u16 *pool;
    u8 poolSize;
    u16 boss;
};

static const u16 sGauntlet1Pool[] =
{
    TRAINER_FACILITY_B1_01_EMBER,
    TRAINER_FACILITY_B1_02_BROOK,
    TRAINER_FACILITY_B1_03_FERN,
    TRAINER_FACILITY_B1_04_VOLT,
    TRAINER_FACILITY_B1_05_MARLO,
    TRAINER_FACILITY_B1_06_MIRA,
    TRAINER_FACILITY_B1_07_SABLE,
    TRAINER_FACILITY_B1_08_GALE,
    TRAINER_FACILITY_B1_09_CASS,
    TRAINER_FACILITY_B1_10_DEX,
    TRAINER_FACILITY_B1_11_QUARRY,
    TRAINER_FACILITY_B1_12_NYX,
};

static const u16 sGauntlet2Pool[] =
{
    TRAINER_FACILITY_B2_A1_FAULT,
    TRAINER_FACILITY_B2_A2_UNDERTOW,
    TRAINER_FACILITY_B2_B4_SPORECLOUD,
    TRAINER_FACILITY_B2_B6_LIGHTNINGROD,
    TRAINER_FACILITY_B2_C7_OPENINGACT,
    TRAINER_FACILITY_B2_D11_INVERSION,
};

static const u16 sGauntlet3Pool[] =
{
    TRAINER_FACILITY_B3_A1_DOWNPOUR,
    TRAINER_FACILITY_B3_A2_DELUGE,
    TRAINER_FACILITY_B3_A3_THUNDER,
    TRAINER_FACILITY_B3_B4_SOLARFLARE,
    TRAINER_FACILITY_B3_B5_HEATHAZE,
    TRAINER_FACILITY_B3_B6_SCORCHED,
    TRAINER_FACILITY_B3_C7_DUSTSTORM,
    TRAINER_FACILITY_B3_C8_ATTRITION,
    TRAINER_FACILITY_B3_C9_GRIT,
    TRAINER_FACILITY_B3_D10_WHITEOUT,
    TRAINER_FACILITY_B3_D11_OVERGROWTH,
    TRAINER_FACILITY_B3_D12_STATFIELD,
};

static const u16 sGauntlet4Pool[] =
{
    TRAINER_FACILITY_B4_A1_JETSTREAM,
    TRAINER_FACILITY_B4_A2_HEADWIND,
    TRAINER_FACILITY_B4_A3_CROSSWIND,
    TRAINER_FACILITY_B4_B4_STANDSTILL,
    TRAINER_FACILITY_B4_B5_DEADWEIGHT,
    TRAINER_FACILITY_B4_B6_SLOWBURN,
    TRAINER_FACILITY_B4_C7_VERDANT,
    TRAINER_FACILITY_B4_C8_MINDFIELD,
    TRAINER_FACILITY_B4_C9_LIVEWIRE,
    TRAINER_FACILITY_B4_D10_DRAGNET,
    TRAINER_FACILITY_B4_D11_STATCLING,
    TRAINER_FACILITY_B4_D12_CHECKMATE,
};

static const u16 sGauntlet5Pool[] =
{
    TRAINER_FACILITY_B5_A1_HEADLINER,
    TRAINER_FACILITY_B5_A2_SPOTLIGHT,
    TRAINER_FACILITY_B5_A3_QUICKDRAW,
    TRAINER_FACILITY_B5_B4_ASCENSION,
    TRAINER_FACILITY_B5_B5_CRESCENDO,
    TRAINER_FACILITY_B5_B6_BULWARK,
    TRAINER_FACILITY_B5_C7_LOCKEDIN,
    TRAINER_FACILITY_B5_C8_MOMENTUM,
    TRAINER_FACILITY_B5_C9_SLEIGHT,
    TRAINER_FACILITY_B5_D10_MINEFIELD,
    TRAINER_FACILITY_B5_D11_IRONWALL,
    TRAINER_FACILITY_B5_D12_PRESSURE,
};

static const u16 sGauntlet6Pool[] =
{
    TRAINER_FACILITY_B6_A1_MONSOON,
    TRAINER_FACILITY_B6_A2_SOLSTICE,
    TRAINER_FACILITY_B6_A3_WHITEOUT,
    TRAINER_FACILITY_B6_B4_LIVEWIRE,
    TRAINER_FACILITY_B6_B5_MINDSCAPE,
    TRAINER_FACILITY_B6_B6_OVERGROWTH,
    TRAINER_FACILITY_B6_C7_STANDING,
    TRAINER_FACILITY_B6_C8_NIGHTSHIFT,
    TRAINER_FACILITY_B6_C9_SLOWBURN,
    TRAINER_FACILITY_B6_D10_BLITZ,
    TRAINER_FACILITY_B6_D11_HEAVYWEIGHT,
    TRAINER_FACILITY_B6_D12_CHORUS,
};

static const u16 sGauntlet7Pool[] =
{
    TRAINER_FACILITY_B7_A1_SANDSTORM,
    TRAINER_FACILITY_B7_A2_DROUGHT,
    TRAINER_FACILITY_B7_A3_DOWNPOUR,
    TRAINER_FACILITY_B7_B4_RUIN,
    TRAINER_FACILITY_B7_B5_PARADOX,
    TRAINER_FACILITY_B7_B6_NOBRAKES,
    TRAINER_FACILITY_B7_C7_STEELHEART,
    TRAINER_FACILITY_B7_C8_MOMENTUM,
    TRAINER_FACILITY_B7_C9_DRAGONFIRE,
    TRAINER_FACILITY_B7_D10_NOEXIT,
    TRAINER_FACILITY_B7_D11_STONEWALL,
    TRAINER_FACILITY_B7_D12_MINDGAMES,
};

static const u16 sGauntlet8Pool[] =
{
    TRAINER_FACILITY_B8_A1_SUNSTROKE,
    TRAINER_FACILITY_B8_A2_TORRENT,
    TRAINER_FACILITY_B8_A3_SANDBLAST,
    TRAINER_FACILITY_B8_B4_GRANDSLAM,
    TRAINER_FACILITY_B8_B5_STATICROOM,
    TRAINER_FACILITY_B8_B6_HEAVYMETAL,
    TRAINER_FACILITY_B8_C7_GALEFORCE,
    TRAINER_FACILITY_B8_C8_LIVEWIRE,
    TRAINER_FACILITY_B8_C9_DARKHEART,
    TRAINER_FACILITY_B8_D10_BEDROCK,
    TRAINER_FACILITY_B8_D11_PERISHTRAP,
    TRAINER_FACILITY_B8_D12_FAIRYRING,
};

static const struct FacilityGauntletData sFacilityGauntlets[] =
{
    [FACILITY_GAUNTLET_1] = { sGauntlet1Pool, ARRAY_COUNT(sGauntlet1Pool), TRAINER_FACILITY_B1_BOSS_WINONA },
    [FACILITY_GAUNTLET_2] = { sGauntlet2Pool, ARRAY_COUNT(sGauntlet2Pool), TRAINER_FACILITY_B2_BOSS_JUAN },
    [FACILITY_GAUNTLET_3] = { sGauntlet3Pool, ARRAY_COUNT(sGauntlet3Pool), TRAINER_FACILITY_B3_BOSS_ROXANNE },
    [FACILITY_GAUNTLET_4] = { sGauntlet4Pool, ARRAY_COUNT(sGauntlet4Pool), TRAINER_FACILITY_B4_BOSS_ANABEL },
    [FACILITY_GAUNTLET_5] = { sGauntlet5Pool, ARRAY_COUNT(sGauntlet5Pool), TRAINER_FACILITY_B5_BOSS_TUCKER },
    [FACILITY_GAUNTLET_6] = { sGauntlet6Pool, ARRAY_COUNT(sGauntlet6Pool), TRAINER_FACILITY_B6_BOSS_LUCY },
    [FACILITY_GAUNTLET_7] = { sGauntlet7Pool, ARRAY_COUNT(sGauntlet7Pool), TRAINER_FACILITY_B7_BOSS_SPENSER },
    [FACILITY_GAUNTLET_8] = { sGauntlet8Pool, ARRAY_COUNT(sGauntlet8Pool), TRAINER_FACILITY_B8_BOSS_BRANDON },
};

bool8 IsFacilityRunActive(void)
{
    return gSaveBlock3Ptr->facility.run.active;
}

// Ten Gauntlets trainers (TRAINER_FACILITY_* constants) live in the regular,
// modern gTrainers[] table - the trainers.party "Competitive Format" the
// project relies on for exact fixed movesets doesn't generate the legacy,
// separate gFacilityTrainers/gBattleFrontierTrainers array (a much smaller,
// hand-authored table, FRONTIER_TRAINERS_COUNT entries) that the *real*
// Battle Frontier's trainerId-indexed lookups assume BATTLE_TYPE_FRONTIER
// implies. TRAINER_FACILITY_B2_A1_FAULT is id 855, so any of those lookups
// treats it as a record-mixing/apprentice slot index and reads garbage -
// this is what caused the "opponent needs a valid name" crash in
// battle_message.c when the game needed to print this trainer's name
// mid-battle. See battle_message.c's BATTLE_TYPE_FRONTIER checks, which
// this is used to route our own trainers around.
// Story battles outside a run - the rival's rematch and NORMAN in front of
// the Battle Tower (frontier-dialogue.md), FLOTSAM at the waterfall - are fought under Frontier
// rules (Set style, no bag), so they carry the same battle type as a run and
// need the same routing below.
bool8 IsFrontierStoryTrainer(u16 trainerId)
{
    return trainerId >= TRAINER_FRONTIER_RIVAL_MAY_FIRE && trainerId <= TRAINER_FRONTIER_FLOTSAM;
}

bool8 IsFacilityBattleTrainer(u16 trainerId)
{
    u32 i, j;

    if (IsFrontierStoryTrainer(trainerId))
        return TRUE;

    for (i = 0; i < ARRAY_COUNT(sFacilityGauntlets); i++)
    {
        const struct FacilityGauntletData *data = &sFacilityGauntlets[i];

        if (data->pool == NULL)
            continue;
        if (trainerId == data->boss)
            return TRUE;
        for (j = 0; j < data->poolSize; j++)
        {
            if (trainerId == data->pool[j])
                return TRUE;
        }
    }
    return FALSE;
}

// Every real Battle Frontier facility except the Tower is locked at game
// start (see the six BattleFrontier_Battle*Lobby OnFrame checks). The Tower
// needs no bit; its lobby has no lock check at all.
//
// A facility that hosts a gauntlet opens when the gauntlet before it is
// cleared, read straight from gauntletsCompleted - the same bitmask the
// Tower mats use (IsDoublesMatUnlocked() etc.), so there's no second piece
// of state a script could forget to set. The door bits in
// gSaveBlock3Ptr->facility.progress.unlockedFacilityDoors are still honored
// as an extra way in (nothing sets them yet), for any door that ever needs
// opening outside the gauntlet order.
#define FACILITY_DOOR_DOME    (1 << 0)
#define FACILITY_DOOR_FACTORY (1 << 1)
#define FACILITY_DOOR_PIKE    (1 << 2)
#define FACILITY_DOOR_ARENA   (1 << 3)
#define FACILITY_DOOR_PALACE  (1 << 4)
#define FACILITY_DOOR_PYRAMID (1 << 5)

static bool8 IsFacilityDoorUnlocked(u8 door)
{
    return (gSaveBlock3Ptr->facility.progress.unlockedFacilityDoors & door) != 0;
}

// The Dome hosts gauntlet 5, so it opens when gauntlet 4 is cleared.
void IsBattleDomeUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_DOME)
        || (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_4)) != 0;
}

// The Factory hosts no gauntlet: it's Devon's control room, home of the
// Mega Pillar (storyline.md), sealed until the endgame opens its door bit.
void IsBattleFactoryUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_FACTORY);
}

// special: WALLACE's PALKIA blasts the Factory door open after gauntlet 8.
void SetBattleFactoryUnlocked(void)
{
    gSaveBlock3Ptr->facility.progress.unlockedFacilityDoors |= FACILITY_DOOR_FACTORY;
}

// The Pike hosts gauntlet 6, so it opens when gauntlet 5 is cleared.
void IsBattlePikeUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_PIKE)
        || (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_5)) != 0;
}

// The Arena hosts no gauntlet: it's the sparring ground (storyline.md), open
// from the start. Its attendant turns the player away until there's a boss
// to spar against.
void IsBattleArenaUnlocked(void)
{
    gSpecialVar_Result = TRUE;
}

// The Palace hosts gauntlet 7, so it opens when gauntlet 6 is cleared.
void IsBattlePalaceUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_PALACE)
        || (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_6)) != 0;
}

// The Pyramid hosts gauntlet 8, the last, so it opens when gauntlet 7 is cleared.
void IsBattlePyramidUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_PYRAMID)
        || (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_7)) != 0;
}

bool32 IsFacilityLobbyDoorLocked(u32 mapGroup, u32 mapNum)
{
    u16 savedResult = gSpecialVar_Result;
    bool32 locked;

    switch (mapNum | (mapGroup << 8))
    {
    case MAP_BATTLE_FRONTIER_BATTLE_DOME_LOBBY:
        IsBattleDomeUnlocked();
        break;
    case MAP_BATTLE_FRONTIER_DEVON_FACTORY_1F:
        IsBattleFactoryUnlocked();
        break;
    case MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY:
        IsBattlePikeUnlocked();
        break;
    case MAP_BATTLE_FRONTIER_BATTLE_ARENA_LOBBY:
        IsBattleArenaUnlocked();
        break;
    case MAP_BATTLE_FRONTIER_BATTLE_PALACE_LOBBY:
        IsBattlePalaceUnlocked();
        break;
    case MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY:
        IsBattlePyramidUnlocked();
        break;
    default:
        return FALSE;
    }
    locked = !gSpecialVar_Result;
    gSpecialVar_Result = savedResult;
    return locked;
}

// ============================================================================
// The Crown is taken, the event after gauntlet 7 (storyline.md;
// VAR_CROWN_STORY_STATE is explained in LittlerootTown's scripts).
// ============================================================================

// TRUE while the player's own front door in LITTLEROOT is locked: from the
// rival's news (state 2) until BIRCH has confessed (state 5). Walking into
// it runs LittlerootTown_EventScript_HomeDoorLocked (TryDoorWarp). The house
// map that's home depends on the player's gender; the other is the rival's.
bool32 IsStoryLockedHomeDoor(u32 mapGroup, u32 mapNum)
{
    u32 home = (gSaveBlock2Ptr->playerGender == MALE) ? MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F
                                                      : MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F;
    u32 state = VarGet(VAR_CROWN_STORY_STATE);

    return (mapNum | (mapGroup << 8)) == home && state >= 2 && state < 5;
}

// The endgame towns (storyline.md) are cut off from the rest of Hoenn by
// their exits; inside them, only the GYMS stay shut, each until its town is
// freed (VAR_ENDGAME_STATE reaches openState), and then open for good.
// TryDoorWarp runs the returned script instead of warping.
static const struct { u16 map; const u8 *script; u16 openState; } sEndgameSealedDoors[] =
{
    { MAP_RUSTBORO_CITY_GYM, EventScript_EndgameSealedGym, 10 },  // the Elite Four, Stone and Juan are done
    { MAP_MAUVILLE_CITY_GYM, EventScript_EndgameSealedGym, 15 },  // New Mauville is done
};

const u8 *GetEndgameSealedDoorScript(u32 mapGroup, u32 mapNum)
{
    u32 i, map = mapNum | (mapGroup << 8);

    for (i = 0; i < ARRAY_COUNT(sEndgameSealedDoors); i++)
    {
        if (sEndgameSealedDoors[i].map == map)
            return VarGet(VAR_ENDGAME_STATE) >= sEndgameSealedDoors[i].openState
                 ? NULL : sEndgameSealedDoors[i].script;
    }
    return NULL;
}

// DEVON's men stripped BIRCH's lab bare: every piece of furniture goes, and
// only the walls and the door mat are left. The lab is 13x13; rows 0-1 are
// the back wall, row 2 the floor in its shadow. Called from the lab's
// ON_LOAD script once the raid has happened.
#define METATILE_Lab_WallTop      0x208
#define METATILE_Lab_WallBottom   0x20A
#define METATILE_Lab_FloorShadow  0x23E
#define METATILE_Lab_Floor        0x202

void StripBirchsLab(void)
{
    s32 x, y;

    for (y = 0; y < 13; y++)
    {
        for (x = 0; x < 13; x++)
        {
            u32 metatile;

            if (y == 12 && (x == 6 || x == 7))
                continue;
            if (y == 0)
                metatile = METATILE_Lab_WallTop | MAPGRID_COLLISION_MASK;
            else if (y == 1)
                metatile = METATILE_Lab_WallBottom | MAPGRID_COLLISION_MASK;
            else if (y == 2)
                metatile = METATILE_Lab_FloorShadow;
            else
                metatile = METATILE_Lab_Floor;
            MapGridSetMetatileIdAt(x + MAP_OFFSET, y + MAP_OFFSET, metatile);
        }
    }
}

// STEVEN gives back the Latias or Latios he took after gauntlet 4
// (FLAG_STEVEN_HAS_LATIOS says which), holding its Mega Stone. It's the one
// caught wild in Artisan Cave, so it keeps that met location - the one
// Pokemon without a chip (IsFrontierChippedMon) - and the Broker's MASTER
// BALL it was caught in. The original was released from the party when
// STEVEN took it, so this builds a fresh one. VAR_RESULT = MON_GIVEN_TO_*.
void GiveStevenLatiBack(void)
{
    struct Pokemon mon;
    bool32 latios = FlagGet(FLAG_STEVEN_HAS_LATIOS);
    u16 species = latios ? SPECIES_LATIOS : SPECIES_LATIAS;
    u16 item = latios ? ITEM_LATIOSITE : ITEM_LATIASITE;
    u8 metLocation = MAPSEC_ARTISAN_CAVE;
    u8 ball = BALL_MASTER;

    CreateRandomMon(&mon, species, 50);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    SetMonData(&mon, MON_DATA_MET_LOCATION, &metLocation);
    SetMonData(&mon, MON_DATA_POKEBALL, &ball);
    gSpecialVar_Result = GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
}

void FacilityCheckEligible(void)
{
    gSpecialVar_Result = (gPartiesCount[B_TRAINER_PLAYER] == PARTY_SIZE);
}

// The Fisher-Yates draw below only guarantees the drawn *indices* are
// distinct - it can't catch the same trainer being listed twice in a
// gauntlet's pool data (an easy mistake once a pool grows to its full 12
// entries). That would be a programmer error, not a player-reachable state,
// so it's an assertf rather than something handled at runtime.
static void AssertPoolTrainersAreUnique(const struct FacilityGauntletData *data)
{
    u32 i, j;

    for (i = 0; i < data->poolSize; i++)
    {
        assertf(data->pool[i] != data->boss, "facility pool trainer duplicates the boss");
        for (j = i + 1; j < data->poolSize; j++)
            assertf(data->pool[i] != data->pool[j], "facility pool has a duplicate trainer");
    }
}

// Clears the "already defeated" flag (the same one vanilla NPCs use to
// refuse a rematch) for every trainer in the gauntlet's pool and its boss.
// Without this, beating a trainer in one run leaves them permanently flagged
// defeated, so the *next* run that draws them skips the battle entirely and
// routes into BattleSetup_GetScriptAddrAfterBattle()'s no-custom-return-
// script fallback (EventScript_TestSignpostMsg) instead of
// Facility_AfterPoolBattle - which is a real softlock, since that fallback
// script ends without releasing the field script lock.
//
// This runs once per FacilityStartRun(), not mid-run, so it can't be used to
// dodge a fight against a trainer you already beat in the run you're
// currently on: the run's draw is a Fisher-Yates permutation of the pool
// (see AssertPoolTrainersAreUnique above for why that means no repeats
// within a run) and battleNum only ever advances forward
// (FacilityAdvanceBattleNum), so a trainer's flag never even gets set again
// until after the run that beat them has ended.
static void ClearPoolTrainerFlags(const struct FacilityGauntletData *data)
{
    u32 i;

    for (i = 0; i < data->poolSize; i++)
        FlagClear(TRAINER_FLAGS_START + data->pool[i]);
    FlagClear(TRAINER_FLAGS_START + data->boss);
}

void FacilityStartRun(void)
{
    u8 gauntlet = gSpecialVar_0x8004;
    const struct FacilityGauntletData *gauntletData = &sFacilityGauntlets[gauntlet];
    u8 pool[FACILITY_MAX_POOL_SIZE];
    u8 poolSize = gauntletData->poolSize;
    u32 i;

    AssertPoolTrainersAreUnique(gauntletData);
    ClearPoolTrainerFlags(gauntletData);

    for (i = 0; i < poolSize; i++)
        pool[i] = i;

    // Fisher-Yates - shuffled fresh every run, per run-loop-spec.md ("the
    // draw should be re-rolled per run... or players will learn the
    // sequence").
    for (i = poolSize; i > 1; i--)
    {
        u32 j = Random() % i;
        u8 temp = pool[i - 1];
        pool[i - 1] = pool[j];
        pool[j] = temp;
    }

    for (i = 0; i < 6 && i < poolSize; i++)
        gSaveBlock3Ptr->facility.run.drawnTeams[i] = pool[i];

    gSaveBlock3Ptr->facility.run.gauntlet = gauntlet;
    gSaveBlock3Ptr->facility.run.battleNum = 1;
    gSaveBlock3Ptr->facility.run.active = TRUE;

    SaveFacilityHeldItems();
}

// specialvar: how many gauntlets are cleared (0-10). Gauntlets clear strictly
// in order, so this is also "the highest gauntlet cleared". Every
// progress-reactive NPC line in the Frontier keys off this - see
// frontier-dialogue.md, Part 2.
u16 GetGauntletsClearedCount(void)
{
    u16 bits = gSaveBlock3Ptr->facility.progress.gauntletsCompleted;
    u16 count = 0;

    while (bits)
    {
        count += bits & 1;
        bits >>= 1;
    }
    return count;
}

// specialvar: where the story is, for townsfolk gossip (GOSSIP_*, in
// include/constants/facility.h). Each event's own state var decides the
// beat inside it; a save that cleared a gauntlet before its event existed
// (state 0) counts as past the event.
u16 GetStoryGossipStage(void)
{
    u16 cleared = GetGauntletsClearedCount();
    u16 birch = VarGet(VAR_BIRCH_STORY_STATE);
    u16 broker = VarGet(VAR_BROKER_STORY_STATE);
    u16 crown = VarGet(VAR_CROWN_STORY_STATE);

    if (cleared >= 8)
    {
        u16 endgame = VarGet(VAR_ENDGAME_STATE);

        if (endgame <= 4)
            return GOSSIP_SIEGE;
        if (endgame <= 6)
            return GOSSIP_AFTERMATH;
        if (endgame <= 9)
            return GOSSIP_DEVON;
        if (endgame == 10)
            return GOSSIP_DEVON_FREED;
        if (endgame <= 12)
            return GOSSIP_SIPHON;
        if (endgame <= 14)
            return GOSSIP_MAUVILLE;
        if (endgame == 15)
            return GOSSIP_MAUVILLE_FREED;
        if (endgame <= 17)
            return GOSSIP_SKY_PILLAR;
        return GOSSIP_ENDING;
    }
    if (cleared == 7)
    {
        if (crown >= 1 && crown <= 4)
            return GOSSIP_RAID;
        if (crown >= 5 && crown <= 7)
            return GOSSIP_TAKEN;
        return GOSSIP_STANDOFF;
    }
    if (cleared == 6)
    {
        if (broker >= 1 && broker <= 4)
            return GOSSIP_SQUAD;
        if (broker >= 5 && broker <= 10)
            return GOSSIP_ARREST;
        return GOSSIP_PALACE;
    }
    if (cleared == 5)
        return (birch >= 1 && birch <= 5) ? GOSSIP_LAB : GOSSIP_AFTER_LAB;
    if (cleared == 4)
        return GOSSIP_ANABEL;
    if (cleared == 3)
        return FlagGet(FLAG_ARTISAN_LATI_CAUGHT) ? GOSSIP_SMUGGLER : GOSSIP_SYSTEM_DOWN;
    if (cleared == 2)
        return GOSSIP_STEVEN;
    if (cleared == 1)
        return GOSSIP_NORMAN;
    return GOSSIP_ARRIVAL;
}

void GetFacilityRunGauntlet(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.gauntlet;
}

// specialvar-style: VAR_0x8004 = gauntlet. A cleared gauntlet can't be
// re-entered (CLAUDE.md, "Re-entry: none") - every attendant checks this
// before offering a run.
// specialvar: TRUE while the Artisan Cave quest is required and unfinished -
// gauntlet 3 cleared, and the player hasn't yet collected the SCRAMBLER from
// LOOKER (who only appears once a Latias/Latios is caught), so the quest only
// ends once they've picked it up (easter-eggs-spec.md, storyline.md). The
// Frontier's "POS is down": the shop, the Broker's deals, the move tutors and
// gauntlet 4's mat all close, so the 900 FP from clearing gauntlet 3 can only
// go on the quest (a LEAFEON, 300, and the Broker's MASTER BALL, 600) and the
// player can't spend themselves into a soft lock.
// The story's Experience rule (storyline.md). The counterfeit badges take
// every Pokemon's growth, so nothing gains Experience until STEVEN swaps them
// for real ones after gauntlet 4 (FLAG_REAL_BADGES). Even then, every Pokemon
// that came from the Frontier - the shop, SCOTT, BIRCH's starter - carries a
// shard chip, and stays frozen. The only one without a chip is the Latias or
// Latios caught wild in Artisan Cave, which is exactly how STEVEN proves it.
// (The New Mauville overclock will lift the chip rule later.)
bool32 FrontierStoryAllowsExp(void)
{
    return FlagGet(FLAG_REAL_BADGES);
}

// After gauntlet 8, HOOPA's rings lead to the legendaries, in ISLAND CAVE's
// sealed chamber (reached no other way): caught wild, so no chip either.
// The Frontier siphon (endgame part 3) drains every chip for the CROWN's
// charge, and from then on nothing is chipped.
bool32 IsFrontierChippedMon(struct Pokemon *mon)
{
    u32 metLocation = GetMonData(mon, MON_DATA_MET_LOCATION);

    if (FlagGet(FLAG_FRONTIER_CHIPS_OFF))
        return FALSE;
    // Never chipped: the two caves, GIRATINA's tunnel and CALYREX's MAUVILLE
    return metLocation != MAPSEC_ARTISAN_CAVE && metLocation != MAPSEC_ISLAND_CAVE
        && metLocation != MAPSEC_RUSTURF_TUNNEL && metLocation != MAPSEC_MAUVILLE_CITY;
}

// How many permanent Megas the REPLICA CROWN can hold in the party at once
// (storyline.md): one once the siphon charges it (VAR_ENDGAME_STATE 11),
// all six once New Mauville's generator supercharges it (state 14).
u32 GetReplicaCrownLimit(void)
{
    u32 state = VarGet(VAR_ENDGAME_STATE);

    if (state >= 14)
        return PARTY_SIZE;
    if (state >= 11)
        return 1;
    return 0;
}

// Ten Gauntlets: the Chansey's Transfer EXP (storyline.md, Mauville). The
// supercharged CROWN pours the Experience of every CHANSEY in the Pokemon
// Centers into one Pokemon: it goes to level 100, once per game
// (FLAG_CHANSEY_TRANSFER_EXP_USED, set by the script on success).
// In: gSpecialVar_0x8004 = party slot. Out: gSpecialVar_Result = 0 done,
// 1 an Egg, 2 already level 100.
void TransferExpToLevel100(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);

    if (species == SPECIES_EGG)
    {
        gSpecialVar_Result = 1;
        return;
    }
    if (GetMonData(mon, MON_DATA_LEVEL) >= MAX_LEVEL)
    {
        gSpecialVar_Result = 2;
        return;
    }
    SetMonData(mon, MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[species].growthRate][MAX_LEVEL]);
    CalculateMonStats(mon);
    gSpecialVar_Result = 0;
}

// Ten Gauntlets: the researcher in OLDALE's first house pays one BOOSTER
// ENERGY for each Paradox species the player shows him (the shop doesn't
// sell it). The shown species are a 32-bit mask across VAR_PARADOX_SHOWN_LO/HI,
// bit i = the i-th species with isParadox set, in species-id order (20 of
// them). In: gSpecialVar_0x8004 = party slot. Out: gSpecialVar_Result = 0 not
// a Paradox (or an Egg), 1 a Paradox he hasn't seen, 2 one he has; the
// species name in gStringVar1, and how many he's seen in gStringVar2.
static s32 ParadoxIndex(u16 species)
{
    u32 s, i = 0;

    for (s = 1; s < NUM_SPECIES; s++)
    {
        if (!gSpeciesInfo[s].isParadox)
            continue;
        if (s == species)
            return i;
        i++;
    }
    return -1;
}

static u32 ParadoxShownMask(void)
{
    return VarGet(VAR_PARADOX_SHOWN_LO) | ((u32)VarGet(VAR_PARADOX_SHOWN_HI) << 16);
}

void OldaleCheckParadox(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
    s32 index = (species == SPECIES_EGG) ? -1 : ParadoxIndex(species);
    u32 mask = ParadoxShownMask(), seen = 0, i;

    for (i = 0; i < 32; i++)
        seen += (mask >> i) & 1;
    ConvertIntToDecimalStringN(gStringVar2, seen, STR_CONV_MODE_LEFT_ALIGN, 2);
    if (index < 0)
    {
        gSpecialVar_Result = 0;
        return;
    }
    StringCopy(gStringVar1, GetSpeciesName(species));
    gSpecialVar_Result = (mask & (1u << index)) ? 2 : 1;
}

// Ten Gauntlets: Bad Dreams (storyline.md). specialvar: TRUE while the event
// can run - gauntlet 6 cleared and the Broker's letter done (gauntlet 7 is
// open), gauntlet 7 not yet cleared (SCOTT is still away), and DARKRAI not
// freed yet. The sleepers, NURSE JOY's offer and the PIKE all check this.
u16 IsBadDreamsActive(void)
{
    return GetGauntletsClearedCount() == 6
        && VarGet(VAR_BROKER_STORY_STATE) >= 11
        && !FlagGet(FLAG_DARKRAI_FREED);
}

// Called once the BOOSTER ENERGY is in the bag.
void OldaleMarkParadoxShown(void)
{
    s32 index = ParadoxIndex(GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES));
    u32 mask;

    if (index < 0)
        return;
    mask = ParadoxShownMask() | (1u << index);
    VarSet(VAR_PARADOX_SHOWN_LO, mask & 0xFFFF);
    VarSet(VAR_PARADOX_SHOWN_HI, mask >> 16);
}

// How many of the party are permanent Megas right now.
u32 CountPermanentMegasInParty(void)
{
    u32 i, n = 0;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (gSpeciesInfo[GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES)].isMegaEvolution)
            n++;
    }
    return n;
}

// The endgame after gauntlet 8 (storyline.md; VAR_ENDGAME_STATE is explained
// in BattleFrontier_OutsideEast). special: VAR_RESULT = how many of the five
// Brains guarding the Factory are beaten. Each one hands over a piece of the
// PILLAR key and turns off one of the red lights on B2F.
static const u16 sFactoryBrains[] =
{
    TRAINER_FACTORY_ANABEL,
    TRAINER_FACTORY_TUCKER,
    TRAINER_FACTORY_LUCY,
    TRAINER_FACTORY_GRETA,
    TRAINER_FACTORY_NOLAND,
};

void GetFactoryBrainsBeaten(void)
{
    u32 i;

    gSpecialVar_Result = 0;
    for (i = 0; i < ARRAY_COUNT(sFactoryBrains); i++)
    {
        if (FlagGet(TRAINER_FLAGS_START + sFactoryBrains[i]))
            gSpecialVar_Result++;
    }
}

// special: VAR_RESULT = HOOPA's rings the player can still use. One opens at
// the Arena base after the Factory, one after DEVON (JUAN's apology) and one
// after New Mauville (the teams leave the city). Only a catch uses a ring up.
void GetHoopaRingsLeft(void)
{
    u32 rings = 0;

    if (VarGet(VAR_ENDGAME_STATE) >= 6)
        rings++;
    if (VarGet(VAR_ENDGAME_STATE) >= 10)
        rings++;
    if (VarGet(VAR_ENDGAME_STATE) >= 15)
        rings++;
    if (rings > VarGet(VAR_HOOPA_CATCHES))
        gSpecialVar_Result = rings - VarGet(VAR_HOOPA_CATCHES);
    else
        gSpecialVar_Result = 0;
}

bool16 IsFrontierPOSDown(void)
{
    return GetGauntletsClearedCount() >= 3 && !CheckBagHasItem(ITEM_SCRAMBLER, 1);
}

void IsFacilityGauntletCompleted(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << gSpecialVar_0x8004)) != 0;
}

void IsFacilityRunActiveForGauntlet(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.active
        && gSaveBlock3Ptr->facility.run.gauntlet == gSpecialVar_0x8004;
}

void IsFacilityRunActiveForDifferentGauntlet(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.active
        && gSaveBlock3Ptr->facility.run.gauntlet != gSpecialVar_0x8004;
}

void IsDoublesMatUnlocked(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_1)) != 0;
}

// Gauntlet 3 (Multis mat) unlocks clearing gauntlet 2, gauntlet 4 (Link
// Multis mat) unlocks clearing gauntlet 3 - same one-gauntlet-ahead gating
// IsDoublesMatUnlocked already uses for gauntlet 2.
void IsMultisMatUnlocked(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_2)) != 0;
}

void IsLinkMultisMatUnlocked(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_3)) != 0;
}

// The psychic in Lounge 7 reads the current gauntlet's boss (the next one
// the player hasn't cleared). specialvar: the gauntlet number (1-10), or 0 if
// every built gauntlet is cleared. Also buffers the boss's name into
// gStringVar1.
u16 FacilityPsychicGetBoss(void)
{
    u16 gauntlet = GetGauntletsClearedCount();

    if (gauntlet >= ARRAY_COUNT(sFacilityGauntlets))
        return 0;
    StringCopy(gStringVar1, GetTrainerNameFromId(sFacilityGauntlets[gauntlet].boss));
    return gauntlet + 1;
}

// gSpecialVar_0x8004 = party slot. gSpecialVar_Result = FALSE past the end of
// the boss's party; otherwise TRUE, with the Pokemon's species, held item and
// ability buffered into gStringVar1-3 (gSpecialVar_0x8005 = FALSE if the
// party data leaves the ability to the species default).
void FacilityPsychicGetBossMon(void)
{
    u16 gauntlet = GetGauntletsClearedCount();
    const struct Trainer *boss;
    const struct TrainerMon *mon;

    gSpecialVar_Result = FALSE;
    if (gauntlet >= ARRAY_COUNT(sFacilityGauntlets))
        return;
    boss = GetTrainerStructFromId(sFacilityGauntlets[gauntlet].boss);
    if (gSpecialVar_0x8004 >= boss->partySize)
        return;
    mon = &boss->party[gSpecialVar_0x8004];
    StringCopy(gStringVar1, GetSpeciesName(mon->species));
    if (mon->heldItem != ITEM_NONE)
        StringCopy(gStringVar2, GetItemName(mon->heldItem));
    else
        StringCopy(gStringVar2, COMPOUND_STRING("nothing"));
    gSpecialVar_0x8005 = (mon->ability != ABILITY_NONE);
    if (gSpecialVar_0x8005)
        StringCopy(gStringVar3, gAbilitiesInfo[mon->ability].name);
    gSpecialVar_Result = TRUE;
}

void FacilityIsBossBattle(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.run.battleNum == 7);
}

void FacilityGetDrawnPoolIndex(void)
{
    u8 battleNum = gSaveBlock3Ptr->facility.run.battleNum;
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.drawnTeams[battleNum - 1];
}

// Rewards scale up as the shop gets pricier. Gauntlets 1-2 pay 75 a win and
// 450 for the boss (900 for a full clear), gauntlet 3 pays 100 and 600
// (1200), and from gauntlet 4 each gauntlet pays 50 more a win than the last,
// with the boss worth six wins: gauntlet 4 pays 150 and 900, 5 pays 200 and
// 1200, 6 pays 250 and 1500, 7 pays 300 and 1800, 8 pays 350 and 2100. Even a
// player who never spends banks at most 300 (starting grant) + 900*2 + 1200
// + 1800 + 2400 + 3000 + 3600 + 4200 = 18300 FP, plus a little from the
// story, well inside the u16 ceiling of
// gSaveBlock3Ptr->facility.progress.fp.
static u16 FacilityBattleFP(u8 gauntlet)
{
    if (gauntlet >= FACILITY_GAUNTLET_4)
        return 150 + 50 * (gauntlet - FACILITY_GAUNTLET_4);
    if (gauntlet == FACILITY_GAUNTLET_3)
        return 100;
    return 75;
}

static u16 FacilityBossFP(u8 gauntlet)
{
    if (gauntlet >= FACILITY_GAUNTLET_4)
        return 6 * FacilityBattleFP(gauntlet);
    if (gauntlet == FACILITY_GAUNTLET_3)
        return 600;
    return 450;
}

// Prices that scale with the rewards: the SECOND WIND and the trader cost two
// wins' FP, the psychic one, always for the gauntlet the player is on now
// (the next one not yet cleared; gauntlet 8 once all eight are).
// gSpecialVar_0x8004 = how many wins' worth. Sets VAR_0x8008 to the price and
// gStringVar3 to it, for the message.
void FacilityGetWinsPrice(void)
{
    u8 gauntlet = GetGauntletsClearedCount();

    if (gauntlet > FACILITY_GAUNTLET_8)
        gauntlet = FACILITY_GAUNTLET_8;
    gSpecialVar_0x8008 = FacilityBattleFP(gauntlet) * gSpecialVar_0x8004;
    ConvertIntToDecimalStringN(gStringVar3, gSpecialVar_0x8008, STR_CONV_MODE_LEFT_ALIGN, 5);
}

void FacilityAwardBattleFP(void)
{
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FacilityBattleFP(gSaveBlock3Ptr->facility.run.gauntlet);
    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
}

// Ten Gauntlets: called right after a pool-battle win, before
// FacilityAdvanceBattleNum bumps battleNum past it - gStringVar1 gets the
// ordinal ("1st".."6th") for the battle just won, gSpecialVar_0x8008 gets
// the FP just awarded (from FacilityBattleFP() rather than a number
// hardcoded in the message text), and gSpecialVar_Result is TRUE only
// on the 6th win, when the boss is up next - matches the literal 7 in
// FacilityIsBossBattle() above (battleNum reaches 7 once this 6th win is
// counted).
void FacilityGetBattleWonInfo(void)
{
    static const u8 sText_4th[] = _("4th");
    static const u8 sText_5th[] = _("5th");
    static const u8 sText_6th[] = _("6th");
    static const u8 *const sOrdinals[] = {
        gText_1st, gText_2nd, gText_3rd, sText_4th, sText_5th, sText_6th,
    };
    u8 battleNum = gSaveBlock3Ptr->facility.run.battleNum;

    StringCopy(gStringVar1, sOrdinals[battleNum - 1]);
    gSpecialVar_0x8008 = FacilityBattleFP(gSaveBlock3Ptr->facility.run.gauntlet);
    gSpecialVar_Result = (battleNum == 6);
}

void FacilityAdvanceBattleNum(void)
{
    gSaveBlock3Ptr->facility.run.battleNum++;
}

void FacilityCompleteGauntlet(void)
{
    u8 gauntlet = gSaveBlock3Ptr->facility.run.gauntlet;
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FacilityBossFP(gauntlet);

    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
    gSaveBlock3Ptr->facility.progress.gauntletsCompleted |= (1 << gauntlet);
    gSaveBlock3Ptr->facility.run.active = FALSE;
}

void FacilityAbandonRun(void)
{
    // Covers both a loss and a deliberate quit - run-loop-spec.md treats them
    // identically (FP already banked from prior wins is kept, the streak
    // just ends). Nothing else needs resetting: gauntlet/battleNum/
    // drawnTeams are only ever read after checking active, so stale values
    // left behind are harmless.
    gSaveBlock3Ptr->facility.run.active = FALSE;
}

// Quiet save - no "Saving... don't turn off the power" popup. Used after a
// loss, where the outcome is already communicated by the battle itself and
// the extra popup just adds friction. Common_EventScript_SaveGame (special
// SaveGame) is the vanilla message-box-driven save used everywhere else in
// this run loop; this is the same TrySavingData() call vanilla's own
// message-free saves (e.g. SaveGameFrontier() in src/frontier_util.c) use
// underneath it.
void FacilitySilentSave(void)
{
    TrySavingData(SAVE_NORMAL);
}

// Reorders two party slots in place - a real swap of the Pokemon data
// itself, not the gBattlePartyCurrentOrder indirection SwitchPartyMonSlots()
// (src/party_menu.c) uses for the vanilla Frontier's own mid-challenge
// reorder feature. That indirection is only honored by the Frontier's own
// battle setup path; plain trainerbattle_single/_double (what every Ten
// Gauntlets battle uses) reads gParties[B_TRAINER_PLAYER][] directly, so a
// real swap is the only one guaranteed to actually change lead order here.
void FacilitySwapPartyMonSlots(void)
{
    struct Pokemon temp;
    u8 slotA = gSpecialVar_0x8004;
    u8 slotB = gSpecialVar_0x8005;

    temp = gParties[B_TRAINER_PLAYER][slotA];
    gParties[B_TRAINER_PLAYER][slotA] = gParties[B_TRAINER_PLAYER][slotB];
    gParties[B_TRAINER_PLAYER][slotB] = temp;
}

// Bad Dreams: the wild DARKRAI that setwildbattle just made (enemy party slot
// 0) gets a fixed set with no sleep moves. Called between setwildbattle and
// dowildbattle.
void SetBadDreamsDarkraiMoves(void)
{
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];

    SetMonMoveSlot(mon, MOVE_DARK_PULSE, 0);
    SetMonMoveSlot(mon, MOVE_SLUDGE_BOMB, 1);
    SetMonMoveSlot(mon, MOVE_FOCUS_BLAST, 2);
    SetMonMoveSlot(mon, MOVE_NASTY_PLOT, 3);
}
