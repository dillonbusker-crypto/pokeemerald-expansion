#include "global.h"
#include "clock.h"
#include "new_game.h"
#include "random.h"
#include "clock.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
#include "trainer_hill.h"
#include "trainer_tower.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "constants/tms_hms.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "string_util.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "mystery_gift.h"
#include "union_room_chat.h"
#include "constants/map_groups.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "difficulty.h"
#include "follower_npc.h"

extern const u8 EventScript_ResetAllMapFlags[];
extern const u8 EventScript_ResetAllMapFlagsFrlg[];

static void ClearFrontierRecord(void);
static void WarpToTruck(void);
static void ResetMiniGamesRecords(void);
static void ResetItemFlags(void);
static void ResetDexNav(void);

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 16) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

// L=A isnt set here for some reason.
static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_MID;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock1Ptr->dexCaught, 0, sizeof(gSaveBlock1Ptr->dexCaught));
    memset(&gSaveBlock1Ptr->dexSeen, 0, sizeof(gSaveBlock1Ptr->dexSeen));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToTruck(void)
{
    if (IS_FRLG)
        SetWarpDestination(MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), WARP_ID_NONE, 6, 6);
    else
        SetWarpDestination(MAP_GROUP(MAP_INSIDE_OF_TRUCK), MAP_NUM(MAP_INSIDE_OF_TRUCK), WARP_ID_NONE, -1, -1);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

// ============================================================================
// Test-team injector for Gauntlet 2 boss playtesting.
//
// Throwaway harness, not the real facility: gives the player the benchmark
// counter-team from gauntlet-02.md so Tidewarden Nerys (placed on Youngster
// Calvin's Route 102 encounter, see src/data/trainers.party) can be tested
// for tuning. Delete the call in NewGameInitData() below to remove it later;
// this function can stay harmlessly.
//
// This is a Trick Room team: every mon's Speed IV is floored to 0 (on top of
// a minimizing nature) rather than the usual 31, because Trick Room makes
// slower move first. Getting this wrong silently inverts the whole strategy.
//
// Uses CreateMonFromTemplate() (include/pokemon.h) - see the gauntlet 1
// counter-team comment (git history) for why, over the CreateMonWithNature()
// call in the original design-doc snippet, which doesn't exist in this
// checkout.
// ============================================================================

#define IVS_ZERO_SPEED { [STAT_HP] = 31, [STAT_ATK] = 31, [STAT_DEF] = 31, [STAT_SPEED] = 0, [STAT_SPATK] = 31, [STAT_SPDEF] = 31 }

static const struct PokemonTemplate sGauntlet2CounterTeam[] =
{
    {
        .species = SPECIES_BRONZONG,
        .heldItem = ITEM_SITRUS_BERRY,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_RELAXED,
        .abilityNum = 0, // Levitate
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_DEF] = 252, [STAT_SPDEF] = 4 },
        .ivs = IVS_ZERO_SPEED,
        .moves = { MOVE_TRICK_ROOM, MOVE_GYRO_BALL, MOVE_ZEN_HEADBUTT, MOVE_PROTECT },
    },
    {
        .species = SPECIES_GASTRODON,
        .heldItem = ITEM_PASSHO_BERRY,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_QUIET,
        .abilityNum = 1, // Storm Drain
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_SPATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_ZERO_SPEED,
        .moves = { MOVE_MUDDY_WATER, MOVE_EARTH_POWER, MOVE_RECOVER, MOVE_PROTECT },
    },
    {
        .species = SPECIES_LANTURN,
        .heldItem = ITEM_WACAN_BERRY,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_QUIET,
        .abilityNum = 0, // Volt Absorb
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_SPATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_ZERO_SPEED,
        .moves = { MOVE_THUNDER, MOVE_ICE_BEAM, MOVE_SURF, MOVE_PROTECT },
    },
    {
        .species = SPECIES_AMOONGUSS,
        .heldItem = ITEM_LEFTOVERS,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_RELAXED,
        .abilityNum = 2, // Regenerator (hidden)
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_DEF] = 252, [STAT_SPDEF] = 4 },
        .ivs = IVS_ZERO_SPEED,
        .moves = { MOVE_SPORE, MOVE_RAGE_POWDER, MOVE_SLUDGE_BOMB, MOVE_PROTECT },
    },
    {
        .species = SPECIES_VIKAVOLT,
        .heldItem = ITEM_MAGNET,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_QUIET,
        .abilityNum = 0, // Levitate
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_SPATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_ZERO_SPEED,
        .moves = { MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_PROTECT },
    },
    {
        .species = SPECIES_MUDSDALE,
        .heldItem = ITEM_MYSTIC_WATER,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_BRAVE,
        .abilityNum = 1, // Stamina
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_ATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_ZERO_SPEED,
        .moves = { MOVE_HIGH_HORSEPOWER, MOVE_HEAVY_SLAM, MOVE_ROCK_SLIDE, MOVE_PROTECT },
    },
};

#undef IVS_ZERO_SPEED

void GiveGauntlet2CounterTeam(void)
{
    u32 i;

    ZeroPlayerPartyMons();
    for (i = 0; i < ARRAY_COUNT(sGauntlet2CounterTeam); i++)
        CreateMonFromTemplate(&gParties[B_TRAINER_PLAYER][i], &sGauntlet2CounterTeam[i]);

    gPartiesCount[B_TRAINER_PLAYER] = ARRAY_COUNT(sGauntlet2CounterTeam);
}

// ============================================================================
// Ten Gauntlets: the five Pokémon that round out the player's starting
// roster on arrival at the Frontier, plus a starting FP grant. See CLAUDE.md.
//
// Gauntlet 1 requires a full party of six to enter (FacilityCheckEligible()
// in src/facility.c), but FP is only earned by winning battles inside a
// gauntlet - a player who's only ever received their starter (see
// CB2_GiveStarter() in src/battle_setup.c) has no way to reach eligibility at
// all. These five, plus the FP grant below, close that gap.
//
// All five are drawn from gauntlet-01.md's pool, same as the starter -
// deliberately NOT Sableye, Parasect or Ferroseed, since those three are the
// answer to gauntlet 1's boss and handing them over for free would
// trivialize it. No held items on any of them either, same reasoning as the
// starter: the player buys their own.
//
// Handed over by SCOTT the first time the player visits his house (see
// data/maps/BattleFrontier_ScottsHouse/scripts.inc) - his welcome at the
// Reception Gate sends the player there. Guarded by
// gSaveBlock3Ptr->facility.progress.startingGrantsGiven so it only ever
// happens once.
// ============================================================================

#define FRONTIER_STARTING_FP 300 // easy to retune once the shop exists

#define IVS_31 { [STAT_HP] = 31, [STAT_ATK] = 31, [STAT_DEF] = 31, [STAT_SPEED] = 31, [STAT_SPATK] = 31, [STAT_SPDEF] = 31 }

static const struct PokemonTemplate sFrontierStartingFive[] =
{
    {
        .species = SPECIES_FURRET,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_JOLLY,
        .abilityNum = 2, // Frisk
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_ATK] = 252, [STAT_DEF] = 4, [STAT_SPEED] = 252 },
        .ivs = IVS_31,
        .moves = { MOVE_DOUBLE_EDGE, MOVE_COIL, MOVE_KNOCK_OFF, MOVE_U_TURN },
    },
    {
        .species = SPECIES_CHINCHOU,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_MODEST,
        .abilityNum = 0, // Volt Absorb
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_DEF] = 4, [STAT_SPATK] = 252 },
        .ivs = IVS_31,
        .moves = { MOVE_SURF, MOVE_THUNDERBOLT, MOVE_ICE_BEAM, MOVE_CONFUSE_RAY },
    },
    {
        .species = SPECIES_GRAVELER,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_ADAMANT,
        .abilityNum = 1, // Sturdy
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_ATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_31,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCK_BLAST, MOVE_STEALTH_ROCK, MOVE_EXPLOSION },
    },
    {
        .species = SPECIES_MURKROW,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_JOLLY,
        .abilityNum = 2, // Prankster
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_ATK] = 252, [STAT_DEF] = 4, [STAT_SPEED] = 252 },
        .ivs = IVS_31,
        .moves = { MOVE_BRAVE_BIRD, MOVE_SUCKER_PUNCH, MOVE_THUNDER_WAVE, MOVE_TAUNT },
    },
    {
        .species = SPECIES_ROSELIA,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_TIMID,
        .abilityNum = 0, // Natural Cure
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_SPATK] = 252, [STAT_DEF] = 4, [STAT_SPEED] = 252 },
        .ivs = IVS_31,
        .moves = { MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_SLEEP_POWDER, MOVE_SYNTHESIS },
    },
};

#undef IVS_31

// Scott hands these over one at a time in his house (data/maps/
// BattleFrontier_ScottsHouse/scripts.inc), so each gets its own "received"
// message instead of all five silently appearing on arrival.
// gSpecialVar_0x8004 = index into sFrontierStartingFive (0-4). Out:
// gStringVar1 = species name, gSpecialVar_Result = MON_GIVEN_TO_PARTY /
// MON_GIVEN_TO_PC / MON_CANT_GIVE - the player normally only has their
// starter at this point, so all five fit in the party, but anything that
// doesn't goes to the PC like any other gift Pokemon.
void GiveFrontierStartingMon(void)
{
    struct Pokemon mon;
    u16 index = gSpecialVar_0x8004;

    if (index >= ARRAY_COUNT(sFrontierStartingFive))
    {
        gSpecialVar_Result = MON_CANT_GIVE;
        return;
    }
    CreateMonFromTemplate(&mon, &sFrontierStartingFive[index]);
    StringCopy(gStringVar1, GetSpeciesName(sFrontierStartingFive[index].species));
    gSpecialVar_Result = GiveCapturedMonToPlayer(&mon);
}

// The rest of Scott's welcome gift: starting FP and the HMs. Marks the
// whole grant as given - the script calls this last, after all five
// Pokemon, and checks HasReceivedFrontierStartingGrants() before starting,
// so none of it can ever happen twice.
void GiveFrontierStartingFPAndHMs(void)
{
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + FRONTIER_STARTING_FP;

    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;

    // Ten Gauntlets: with the Move Editor retired (see l_menu.c), the L-menu's
    // Move Relearner only ever offers a species' own level-up learnset - the
    // player's other way to round out a moveset is TMs. The TM/HM bag pocket
    // (BAG_TMHM_COUNT, include/constants/global.h) can only hold 64 distinct
    // item types within SaveBlock1's fixed sector budget - nowhere near
    // Emerald Imperium's 166-move TM list this project uses (see
    // include/constants/tms_hms.h's FOREACH_TM) - so TMs are no longer bag
    // items the player carries. They're taught directly via the L-menu's
    // "Teach TM" tool (data/scripts/debug.inc, Debug_EventScript_TeachTM),
    // which drills down by move type and calls the same CanTeachMoveBoxMon
    // special every vanilla Move Tutor uses. HMs stay as real bag items -
    // only 8 of them, nowhere near the pocket cap.
#define GRANT_HM(id) AddBagItem(ITEM_HM_##id, 99);
    FOREACH_HM(GRANT_HM)
#undef GRANT_HM

    gSaveBlock3Ptr->facility.progress.startingGrantsGiven = TRUE;
}

// specialvar: TRUE once Scott has handed over the starting team.
u16 HasReceivedFrontierStartingGrants(void)
{
    return gSaveBlock3Ptr->facility.progress.startingGrantsGiven;
}

void NewGameInitData(void)
{
#if IS_FRLG
    u8 rivalName[PLAYER_NAME_LENGTH + 1];
#endif
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();

#if IS_FRLG
    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
#endif
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearSav3();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    DeactivateAllRoamers();
    gSaveBlock1Ptr->registeredItem = ITEM_NONE;
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    UpdateDailySeed();
    WarpToTruck();
    if (IS_FRLG)
        RunScriptImmediately(EventScript_ResetAllMapFlagsFrlg);
    else
        RunScriptImmediately(EventScript_ResetAllMapFlags);
#if IS_FRLG
        StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
#endif
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetTrainerTowerResults();
    ResetContestLinkResults();
    SetCurrentDifficultyLevel(DIFFICULTY_NORMAL);
    ResetItemFlags();
    ResetDexNav();
    ClearFollowerNPCData();
    // GiveGauntlet2CounterTeam() call removed here: the real starter flow
    // (CB2_GiveStarter in src/battle_setup.c) now gives the player's first
    // mon, and this test harness handing out a full 6-mon team before Birch's
    // lab would both skip starter selection and make the eligibility check
    // in FacilityCheckEligible() trivially true from turn one. The function
    // itself is left in place, per its own header comment, as a harmless
    // throwaway that can still be called manually for boss-tuning tests.
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlock3Ptr->itemFlags, 0, sizeof(gSaveBlock3Ptr->itemFlags));
#endif
}

static void ResetDexNav(void)
{
#if USE_DEXNAV_SEARCH_LEVELS == TRUE
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));
#endif
    gSaveBlock3Ptr->dexNavChain = 0;
}
