// ============================================================================
// Ten Buildings facility run loop. See run-loop-spec.md for the full design.
//
// Building 1 ("Little League", building-01.md) has its full twelve-team
// pool and boss. Building 2 ("The Second Slot", building-02.md) has 6 of
// its twelve pool teams for now (A1, A2, B4, B6, C7, D11) - the shuffle
// below operates on whatever poolSize the active building declares, so
// adding the remaining six later is a data change only.
// ============================================================================

#include "global.h"
#include "facility.h"
#include "assertf.h"
#include "event_data.h"
#include "frontier_util.h"
#include "pokemon.h"
#include "random.h"
#include "save.h"
#include "strings.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/trainers.h"

#define FACILITY_MAX_POOL_SIZE 12

struct FacilityBuildingData
{
    const u16 *pool;
    u8 poolSize;
    u16 boss;
};

static const u16 sBuilding1Pool[] =
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

static const u16 sBuilding2Pool[] =
{
    TRAINER_FACILITY_B2_A1_FAULT,
    TRAINER_FACILITY_B2_A2_UNDERTOW,
    TRAINER_FACILITY_B2_B4_SPORECLOUD,
    TRAINER_FACILITY_B2_B6_LIGHTNINGROD,
    TRAINER_FACILITY_B2_C7_OPENINGACT,
    TRAINER_FACILITY_B2_D11_INVERSION,
};

static const u16 sBuilding3Pool[] =
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

static const u16 sBuilding4Pool[] =
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

static const struct FacilityBuildingData sFacilityBuildings[] =
{
    [FACILITY_BUILDING_1] = { sBuilding1Pool, ARRAY_COUNT(sBuilding1Pool), TRAINER_FACILITY_B1_BOSS_HELIS },
    [FACILITY_BUILDING_2] = { sBuilding2Pool, ARRAY_COUNT(sBuilding2Pool), TRAINER_FACILITY_B2_BOSS_NERYS },
    [FACILITY_BUILDING_3] = { sBuilding3Pool, ARRAY_COUNT(sBuilding3Pool), TRAINER_FACILITY_B3_BOSS_KASRA },
    [FACILITY_BUILDING_4] = { sBuilding4Pool, ARRAY_COUNT(sBuilding4Pool), TRAINER_FACILITY_B4_BOSS_IYLA },
};

bool8 IsFacilityRunActive(void)
{
    return gSaveBlock3Ptr->facility.run.active;
}

// Ten Buildings trainers (TRAINER_FACILITY_* constants) live in the regular,
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
bool8 IsFacilityBattleTrainer(u16 trainerId)
{
    u32 i, j;

    for (i = 0; i < ARRAY_COUNT(sFacilityBuildings); i++)
    {
        const struct FacilityBuildingData *data = &sFacilityBuildings[i];

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
// start (see the six BattleFrontier_Battle*Lobby OnFrame checks). Nothing
// sets any of these bits yet - that's the unlock schedule, still
// undesigned - so gSaveBlock3Ptr->facility.progress.unlockedFacilityDoors
// stays 0 and every door below reads as locked. Tower needs no bit; its
// lobby has no lock check at all.
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

void IsBattleDomeUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_DOME);
}

void IsBattleFactoryUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_FACTORY);
}

void IsBattlePikeUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_PIKE);
}

void IsBattleArenaUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_ARENA);
}

void IsBattlePalaceUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_PALACE);
}

void IsBattlePyramidUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_PYRAMID);
}

void FacilityCheckEligible(void)
{
    gSpecialVar_Result = (gPartiesCount[B_TRAINER_PLAYER] == PARTY_SIZE);
}

// The Fisher-Yates draw below only guarantees the drawn *indices* are
// distinct - it can't catch the same trainer being listed twice in a
// building's pool data (an easy mistake once a pool grows to its full 12
// entries). That would be a programmer error, not a player-reachable state,
// so it's an assertf rather than something handled at runtime.
static void AssertPoolTrainersAreUnique(const struct FacilityBuildingData *data)
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
// refuse a rematch) for every trainer in the building's pool and its boss.
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
static void ClearPoolTrainerFlags(const struct FacilityBuildingData *data)
{
    u32 i;

    for (i = 0; i < data->poolSize; i++)
        FlagClear(TRAINER_FLAGS_START + data->pool[i]);
    FlagClear(TRAINER_FLAGS_START + data->boss);
}

void FacilityStartRun(void)
{
    u8 building = gSpecialVar_0x8004;
    const struct FacilityBuildingData *buildingData = &sFacilityBuildings[building];
    u8 pool[FACILITY_MAX_POOL_SIZE];
    u8 poolSize = buildingData->poolSize;
    u32 i;

    AssertPoolTrainersAreUnique(buildingData);
    ClearPoolTrainerFlags(buildingData);

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

    gSaveBlock3Ptr->facility.run.building = building;
    gSaveBlock3Ptr->facility.run.battleNum = 1;
    gSaveBlock3Ptr->facility.run.active = TRUE;

    SaveFacilityHeldItems();
}

void GetFacilityRunBuilding(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.building;
}

void IsFacilityRunActiveForBuilding(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.active
        && gSaveBlock3Ptr->facility.run.building == gSpecialVar_0x8004;
}

void IsFacilityRunActiveForDifferentBuilding(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.active
        && gSaveBlock3Ptr->facility.run.building != gSpecialVar_0x8004;
}

void IsDoublesMatUnlocked(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.buildingsCompleted & (1 << FACILITY_BUILDING_1)) != 0;
}

// Building 3 (Multis mat) unlocks clearing building 2, building 4 (Link
// Multis mat) unlocks clearing building 3 - same one-building-ahead gating
// IsDoublesMatUnlocked already uses for building 2.
void IsMultisMatUnlocked(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.buildingsCompleted & (1 << FACILITY_BUILDING_2)) != 0;
}

void IsLinkMultisMatUnlocked(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.progress.buildingsCompleted & (1 << FACILITY_BUILDING_3)) != 0;
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

// Flat across all ten buildings - not the "10/100 x building number" formula
// in battle-tower-design-v2.md, which hadn't been played against actual shop
// prices yet. Retuned again once shop-spec.md's economy section (and the
// tier-2 pricing ladder in that doc) was worked out against these numbers:
// a full clear (6 wins + boss) pays 900 FP, matching that doc exactly. u16
// gSaveBlock3Ptr->facility.progress.fp tops out at 65535 - even a player who
// clears every building without ever spending banks at most 300 (starting
// grant) + 9000 (ten full clears) = 9300, comfortably inside that ceiling
// with room to spare.
#define FACILITY_FP_PER_BATTLE 75
#define FACILITY_FP_PER_BOSS   450

void FacilityAwardBattleFP(void)
{
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FACILITY_FP_PER_BATTLE;
    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
}

// Ten Buildings: called right after a pool-battle win, before
// FacilityAdvanceBattleNum bumps battleNum past it - gStringVar1 gets the
// ordinal ("1st".."6th") for the battle just won, gSpecialVar_0x8008 gets
// the FP just awarded (kept in sync with FACILITY_FP_PER_BATTLE rather than
// hardcoding "75" in the message text), and gSpecialVar_Result is TRUE only
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
    gSpecialVar_0x8008 = FACILITY_FP_PER_BATTLE;
    gSpecialVar_Result = (battleNum == 6);
}

void FacilityAdvanceBattleNum(void)
{
    gSaveBlock3Ptr->facility.run.battleNum++;
}

void FacilityCompleteBuilding(void)
{
    u8 building = gSaveBlock3Ptr->facility.run.building;
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FACILITY_FP_PER_BOSS;

    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
    gSaveBlock3Ptr->facility.progress.buildingsCompleted |= (1 << building);
    gSaveBlock3Ptr->facility.run.active = FALSE;
}

void FacilityAbandonRun(void)
{
    // Covers both a loss and a deliberate quit - run-loop-spec.md treats them
    // identically (FP already banked from prior wins is kept, the streak
    // just ends). Nothing else needs resetting: building/battleNum/
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
// Buildings battle uses) reads gParties[B_TRAINER_PLAYER][] directly, so a
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
