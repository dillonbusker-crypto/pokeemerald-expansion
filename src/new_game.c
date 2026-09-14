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
// Test-team injector for Building 1 boss playtesting.
//
// Throwaway harness, not the real facility: gives the player the benchmark
// counter-team from building-01.md so Warden Helis (placed on Youngster
// Calvin's Route 102 encounter, see src/data/trainers.party) can be tested
// for tuning. Delete the call in NewGameInitData() below to remove it later;
// this function can stay harmlessly.
//
// Adapted from give-counter-team.c to the actual API in this checkout:
// CreateMonWithNature() does not exist here, so this uses CreateMonFromTemplate()
// (include/pokemon.h) instead, which fills in nature/ability/IVs/EVs/moves from
// a single struct PokemonTemplate.
// ============================================================================

#define IVS_ALL_31 { [STAT_HP] = 31, [STAT_ATK] = 31, [STAT_DEF] = 31, [STAT_SPEED] = 31, [STAT_SPATK] = 31, [STAT_SPDEF] = 31 }

static const struct PokemonTemplate sBuilding1CounterTeam[] =
{
    {
        .species = SPECIES_SABLEYE,
        .heldItem = ITEM_LEFTOVERS,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_BOLD,
        .abilityNum = 2, // Prankster (hidden ability)
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_DEF] = 252, [STAT_SPDEF] = 4 },
        .ivs = IVS_ALL_31,
        .moves = { MOVE_WILL_O_WISP, MOVE_TAUNT, MOVE_RECOVER, MOVE_FOUL_PLAY },
    },
    {
        .species = SPECIES_FERROSEED,
        .heldItem = ITEM_METAL_COAT,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_RELAXED,
        .abilityNum = 0, // Iron Barbs
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_DEF] = 252, [STAT_SPDEF] = 4 },
        .ivs = IVS_ALL_31,
        .moves = { MOVE_GYRO_BALL, MOVE_SEED_BOMB, MOVE_PROTECT, MOVE_CURSE },
    },
    {
        .species = SPECIES_CHINCHOU,
        .heldItem = ITEM_MYSTIC_WATER,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_MODEST,
        .abilityNum = 0, // Volt Absorb
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_DEF] = 4, [STAT_SPATK] = 252 },
        .ivs = IVS_ALL_31,
        .moves = { MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_CONFUSE_RAY },
    },
    {
        .species = SPECIES_PAWNIARD,
        .heldItem = ITEM_BLACK_GLASSES,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_JOLLY,
        .abilityNum = 0, // Defiant
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_ATK] = 252, [STAT_DEF] = 4, [STAT_SPEED] = 252 },
        .ivs = IVS_ALL_31,
        .moves = { MOVE_SUCKER_PUNCH, MOVE_KNOCK_OFF, MOVE_IRON_HEAD, MOVE_SWORDS_DANCE },
    },
    {
        .species = SPECIES_MARSHTOMP,
        .heldItem = ITEM_SOFT_SAND,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_ADAMANT,
        .abilityNum = 0, // Torrent
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_ATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_ALL_31,
        .moves = { MOVE_EARTHQUAKE, MOVE_WATERFALL, MOVE_ROCK_SLIDE, MOVE_PROTECT },
    },
    {
        .species = SPECIES_PARASECT,
        .heldItem = ITEM_MIRACLE_SEED,
        .level = 50,
        .gender = MON_GENDER_RANDOM,
        .nature = NATURE_ADAMANT,
        .abilityNum = 1, // Dry Skin
        .doNotUseDefaultAbility = TRUE,
        .origin = GIFTMON_ORIGIN,
        .evs = { [STAT_HP] = 252, [STAT_ATK] = 252, [STAT_DEF] = 4 },
        .ivs = IVS_ALL_31,
        .moves = { MOVE_SPORE, MOVE_SEED_BOMB, MOVE_X_SCISSOR, MOVE_LEECH_LIFE },
    },
};

#undef IVS_ALL_31

void GiveBuilding1CounterTeam(void)
{
    u32 i;

    ZeroPlayerPartyMons();
    for (i = 0; i < ARRAY_COUNT(sBuilding1CounterTeam); i++)
        CreateMonFromTemplate(&gParties[B_TRAINER_PLAYER][i], &sBuilding1CounterTeam[i]);

    gPartiesCount[B_TRAINER_PLAYER] = ARRAY_COUNT(sBuilding1CounterTeam);
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
    GiveBuilding1CounterTeam();
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
