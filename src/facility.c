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

static const struct FacilityGauntletData sFacilityGauntlets[] =
{
    [FACILITY_GAUNTLET_1] = { sGauntlet1Pool, ARRAY_COUNT(sGauntlet1Pool), TRAINER_FACILITY_B1_BOSS_WINONA },
    [FACILITY_GAUNTLET_2] = { sGauntlet2Pool, ARRAY_COUNT(sGauntlet2Pool), TRAINER_FACILITY_B2_BOSS_JUAN },
    [FACILITY_GAUNTLET_3] = { sGauntlet3Pool, ARRAY_COUNT(sGauntlet3Pool), TRAINER_FACILITY_B3_BOSS_ROXANNE },
    [FACILITY_GAUNTLET_4] = { sGauntlet4Pool, ARRAY_COUNT(sGauntlet4Pool), TRAINER_FACILITY_B4_BOSS_ANABEL },
    [FACILITY_GAUNTLET_5] = { sGauntlet5Pool, ARRAY_COUNT(sGauntlet5Pool), TRAINER_FACILITY_B5_BOSS_TUCKER },
    [FACILITY_GAUNTLET_6] = { sGauntlet6Pool, ARRAY_COUNT(sGauntlet6Pool), TRAINER_FACILITY_B6_BOSS_NOLAND },
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

// The Factory hosts gauntlet 6, so it opens when gauntlet 5 is cleared.
void IsBattleFactoryUnlocked(void)
{
    gSpecialVar_Result = IsFacilityDoorUnlocked(FACILITY_DOOR_FACTORY)
        || (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << FACILITY_GAUNTLET_5)) != 0;
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

void GetFacilityRunGauntlet(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.gauntlet;
}

// specialvar-style: VAR_0x8004 = gauntlet. A cleared gauntlet can't be
// re-entered (CLAUDE.md, "Re-entry: none") - every attendant checks this
// before offering a run.
// specialvar: TRUE while the Artisan Cave quest is required and unfinished -
// gauntlet 3 cleared, no Latias/Latios caught yet (easter-eggs-spec.md). The
// Frontier's "POS is down": the shop, the Broker's deals, the move tutors and
// gauntlet 4's mat all close, so the 900 FP from clearing gauntlet 3 can only
// go on the quest (a LEAFEON, 300, and the Broker's MASTER BALL, 600) and the
// player can't spend themselves into a soft lock.
bool16 IsFrontierPOSDown(void)
{
    return GetGauntletsClearedCount() >= 3 && !FlagGet(FLAG_ARTISAN_LATI_CAUGHT);
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

void FacilityIsBossBattle(void)
{
    gSpecialVar_Result = (gSaveBlock3Ptr->facility.run.battleNum == 7);
}

void FacilityGetDrawnPoolIndex(void)
{
    u8 battleNum = gSaveBlock3Ptr->facility.run.battleNum;
    gSpecialVar_Result = gSaveBlock3Ptr->facility.run.drawnTeams[battleNum - 1];
}

// Flat across all ten gauntlets - not the "10/100 x gauntlet number" formula
// in battle-tower-design-v2.md, which hadn't been played against actual shop
// prices yet. Retuned again once shop-spec.md's economy section (and the
// tier-2 pricing ladder in that doc) was worked out against these numbers:
// a full clear (6 wins + boss) pays 900 FP, matching that doc exactly. u16
// gSaveBlock3Ptr->facility.progress.fp tops out at 65535 - even a player who
// clears every gauntlet without ever spending banks at most 300 (starting
// grant) + 9000 (ten full clears) = 9300, comfortably inside that ceiling
// with room to spare.
#define FACILITY_FP_PER_BATTLE 75
#define FACILITY_FP_PER_BOSS   450

void FacilityAwardBattleFP(void)
{
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FACILITY_FP_PER_BATTLE;
    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
}

// Ten Gauntlets: called right after a pool-battle win, before
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

void FacilityCompleteGauntlet(void)
{
    u8 gauntlet = gSaveBlock3Ptr->facility.run.gauntlet;
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FACILITY_FP_PER_BOSS;

    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
    gSaveBlock3Ptr->facility.progress.gauntletsCompleted |= (1 << gauntlet);
    gSaveBlock3Ptr->facility.run.active = FALSE;
    FacilityBrokerResolveLoans(TRUE);
}

void FacilityAbandonRun(void)
{
    // Covers both a loss and a deliberate quit - run-loop-spec.md treats them
    // identically (FP already banked from prior wins is kept, the streak
    // just ends). Nothing else needs resetting: gauntlet/battleNum/
    // drawnTeams are only ever read after checking active, so stale values
    // left behind are harmless.
    gSaveBlock3Ptr->facility.run.active = FALSE;
    FacilityBrokerResolveLoans(FALSE);
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
