#ifndef GUARD_CONSTANTS_FIELD_SPECIALS_H
#define GUARD_CONSTANTS_FIELD_SPECIALS_H

// PC Locations
enum PCLocation
{
    PC_LOCATION_OTHER,
    PC_LOCATION_BRENDANS_HOUSE,
    PC_LOCATION_MAYS_HOUSE,
    PC_LOCATION_PLAYER_HOUSE_FRLG
};

// SS Tidal Locations
enum SSTidalLocation
{
    SS_TIDAL_LOCATION_CURRENTS,
    SS_TIDAL_LOCATION_SLATEPORT,
    SS_TIDAL_LOCATION_LILYCOVE,
    SS_TIDAL_LOCATION_ROUTE124,
    SS_TIDAL_LOCATION_ROUTE131,
};

enum SSTidalState
{
    SS_TIDAL_BOARD_SLATEPORT = 1,
    SS_TIDAL_DEPART_SLATEPORT,
    SS_TIDAL_HALFWAY_LILYCOVE,
    SS_TIDAL_LAND_LILYCOVE,
    SS_TIDAL_BOARD_LILYCOVE,
    SS_TIDAL_DEPART_LILYCOVE,
    SS_TIDAL_HALFWAY_SLATEPORT,
    SS_TIDAL_LAND_SLATEPORT,
    SS_TIDAL_EXIT_CURRENTS_RIGHT,
    SS_TIDAL_EXIT_CURRENTS_LEFT,
};

#define SS_TIDAL_MAX_STEPS 205

// Scrollable Multichoice Menus
// Ten Gauntlets: the four vanilla Exchange Corner BP vendors (decor x2,
// vitamins, hold items) that used to live right after
// SCROLL_MULTI_POKEMON_FAN_CLUB_RATER are gone - replaced by the
// SCROLL_MULTI_TEN_GAUNTLETS_* menus below. Their data lived in
// src/data/battle_frontier/battle_frontier_exchange_corner.h, now deleted.
enum ScrollMulti
{
    SCROLL_MULTI_NONE,
    SCROLL_MULTI_GLASS_WORKSHOP_VENDOR,
    SCROLL_MULTI_POKEMON_FAN_CLUB_RATER,
    SCROLL_MULTI_BERRY_POWDER_VENDOR,
    SCROLL_MULTI_BF_RECEPTIONIST,
    SCROLL_MULTI_BF_MOVE_TUTOR_1,
    SCROLL_MULTI_BF_MOVE_TUTOR_2,
    SCROLL_MULTI_SS_TIDAL_DESTINATION,
    SCROLL_MULTI_BATTLE_TENT_RULES,
    SCROLL_MULTI_BADGES,
    SCROLL_MULTI_SILPHCO_FLOORS,
    // Ten Gauntlets shop (shop-spec.md), Exchange Service Corner keepers.
    // SCROLL_MULTI_TEN_GAUNTLETS_MON_TIER_SELECT and _POST_BATTLE are small,
    // fixed-content menus and stay static. Everything else - consumables,
    // held items, every Pokemon tier and its optional type filter - is one
    // dynamically-built list, staged by src/facility_shop.c and read via
    // FacilityShopGetMenuCount/Name/Price/Description() instead of a
    // per-menu COMPOUND_STRING table. This is what lets the shop grow by
    // nine more unlocks without a new enum value or a new
    // ShowScrollableMultichoice case each time - see shop-spec.md and
    // shop-unlock-b2.md.
    SCROLL_MULTI_TEN_GAUNTLETS_MON_TIER_SELECT,
    SCROLL_MULTI_TEN_GAUNTLETS_DYNAMIC,
    SCROLL_MULTI_TEN_GAUNTLETS_POST_BATTLE,
};

#define MAX_SCROLL_MULTI_ON_SCREEN 6
#define MAX_SCROLL_MULTI_LENGTH 16

// Dept Store Floor Numbers
enum DeptStoreFloorNumber
{
    DEPT_STORE_FLOORNUM_B4F,
    DEPT_STORE_FLOORNUM_B3F,
    DEPT_STORE_FLOORNUM_B2F,
    DEPT_STORE_FLOORNUM_B1F,
    DEPT_STORE_FLOORNUM_1F,
    DEPT_STORE_FLOORNUM_2F,
    DEPT_STORE_FLOORNUM_3F,
    DEPT_STORE_FLOORNUM_4F,
    DEPT_STORE_FLOORNUM_5F,
    DEPT_STORE_FLOORNUM_6F,
    DEPT_STORE_FLOORNUM_7F,
    DEPT_STORE_FLOORNUM_8F,
    DEPT_STORE_FLOORNUM_9F,
    DEPT_STORE_FLOORNUM_10F,
    DEPT_STORE_FLOORNUM_11F,
    DEPT_STORE_FLOORNUM_ROOFTOP,
};

// Lilycove Pokémon Trainer Fan Club
#define NUM_TRAINER_FAN_CLUB_MEMBERS  8

#define FANCLUB_GOT_FIRST_FANS 7
#define FANCLUB_MEMBER1        8
#define FANCLUB_MEMBER2        9
#define FANCLUB_MEMBER3        10
#define FANCLUB_MEMBER4        11
#define FANCLUB_MEMBER5        12
#define FANCLUB_MEMBER6        13
#define FANCLUB_MEMBER7        14
#define FANCLUB_MEMBER8        15

#define FANCOUNTER_DEFEATED_DRAKE    0
#define FANCOUNTER_BATTLED_AT_BASE   1
#define FANCOUNTER_FINISHED_CONTEST  2
#define FANCOUNTER_USED_BATTLE_TOWER 3

// Return values for DoDeoxysRockInteraction
enum DeoxysRockResult
{
    DEOXYS_ROCK_FAILED,
    DEOXYS_ROCK_PROGRESSED,
    DEOXYS_ROCK_SOLVED,
    DEOXYS_ROCK_COMPLETE,
};

enum {
    OPEN_PARTY_SCREEN,
    NO_PARTY_SCREEN
};

enum {
    CURRENT_POSITION,
    TEMPLATE_POSITION
};

// Ten Gauntlets: TeachTMMove()'s result (src/field_specials.c), read by
// Debug_EventScript_TeachTM (data/scripts/debug.inc). TEACH_TM_NEEDS_REPLACE
// means the mon already has 4 moves - the script then shows its own
// dynmultichoice slot picker and calls ReplaceTMMoveSlot() directly, rather
// than routing through CanTeachMoveBoxMon/ShowSelectMovePokemonSummaryScreen
// like every other move-teaching path in this project. That summary-screen
// swap is exactly what 3-for-3 crash repros traced back to (a heap-corrupting
// bug never pinned down through code review, despite it being shared,
// heavily-used vanilla machinery) - so Teach TM's replace case avoids it
// entirely instead, using only primitives already proven safe elsewhere
// (dynmultichoice, direct SetBoxMonData/GiveMoveToBoxMon calls).
enum TeachTMResult
{
    TEACH_TM_LEARNED,
    TEACH_TM_ALREADY_KNOWS,
    TEACH_TM_CANNOT_LEARN,
    TEACH_TM_NEEDS_REPLACE,
};

#endif // GUARD_CONSTANTS_FIELD_SPECIALS_H
