// ============================================================================
// Ten Gauntlets shop - see shop-spec.md and shop-unlock-b2.md.
//
// Keepers 1 (consumables), 2 (held items) and 3 (Mega Stones) are plain
// `additem` purchases,
// scripted the same way vanilla's own BP vendors are (see
// data/maps/BattleFrontier_ExchangeServiceCorner/scripts.inc) but spending
// FP instead of Battle Points. Keeper 4 (Pokemon) needs this file because it
// has to create a mon, not just hand over an item.
//
// Every sellable row - item or mon - carries an `unlockGauntlet` field: 0
// means available from game start, N means it doesn't show up until
// gSaveBlock3Ptr->facility.progress.gauntletsCompleted has bit (N - 1) set
// (IsShopEntryUnlocked() below). That bit is flipped by FacilityCompleteGauntlet()
// in src/facility.c the moment a gauntlet's boss falls - before the player
// can act again - so there's no separate "unlock trigger" to wire up here;
// the shop just reads the same bitmask the run loop already maintains, live,
// every time a keeper's menu opens. Nine more unlocks after this one are
// just nine more rows with an unlockGauntlet value, not nine more
// conditionals.
//
// Keeper 4 (Pokemon) additionally organizes its master tables by that same
// `unlockGauntlet` value, calling it a "wave": the player picks a gauntlet's
// wave first (FacilityShopBuildGauntletMenu), then a tier within it, so
// browsing one gauntlet's additions doesn't mean scrolling through every
// other gauntlet's too. That's one generic gauntlet-select screen shared by
// every gauntlet, not a new screen per gauntlet - a gauntlet's worth of new
// mons is still just new rows with that gauntlet's unlockGauntlet value.
//
// The list itself is generated at runtime instead of living as a
// SCROLL_MULTI_TEN_GAUNTLETS_MON_STANDARD_1..6-style static COMPOUND_STRING
// table (see include/constants/field_specials.h's SCROLL_MULTI_TEN_GAUNTLETS_
// DYNAMIC comment) - a static table meant every unlock needed hand-edited
// pagination (MAX_SCROLL_MULTI_LENGTH is 16, an artifact of that table's
// second dimension, not a real engine limit) kept in sync by hand across two
// files. Now the "Build" specials below filter the master tables by unlock
// and (for Pokemon) by wave/tier/type, and stage the result in sMenuRows -
// heap-allocated per visit, same lifetime as ShowScrollableMultichoice's own
// sScrollableMultichoice_ListMenuItem, so steady-state EWRAM use doesn't grow
// no matter how many rows a tier eventually holds. Name pointers come
// straight from GetSpeciesName()/GetItemName() (already-persistent strings,
// no copy needed); price is drawn by a per-row itemPrintFunc callback in
// field_specials.c, exactly the way vanilla's own Pokemart list draws Poke
// Dollar prices next to item names.
// ============================================================================

#include "global.h"
#include "random.h"
#include "facility_shop.h"
#include "battle_main.h"
#include "event_data.h"
#include "international_string_util.h"
#include "item.h"
#include "malloc.h"
#include "menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "text.h"
#include "window.h"
#include "facility.h"
#include "constants/region_map_sections.h"
#include "constants/items.h"
#include "constants/species.h"

struct FacilityShopMon
{
    u16 species;
    u16 price;
    u8 unlockGauntlet; // 0 = available from game start
};

struct FacilityShopItem
{
    u16 item;
    u16 price;
    u8 unlockGauntlet; // 0 = available from game start
    const u8 *description; // NULL if this row doesn't show one (Keeper 2's stock)
};

// After the Factory (storyline.md), its surge has fried DEVON's systems and
// the BROKER runs the shop for the cause: everything is free. A free row
// draws no price (FacilityShop's itemPrintFunc skips a price of 0).
static u16 ShopPrice(u16 price)
{
    return FlagGet(FLAG_FRONTIER_SHOP_FREE) ? 0 : price;
}

static bool8 IsShopEntryUnlocked(u8 unlockGauntlet)
{
    if (unlockGauntlet == 0)
        return TRUE;
    return (gSaveBlock3Ptr->facility.progress.gauntletsCompleted & (1 << (unlockGauntlet - 1))) != 0;
}

// ----------------------------------------------------------------------------
// Keeper 1 - Consumables. Confusion-berry descriptions name the exact
// natures to avoid (the ones that lower the relevant stat) rather than a
// vague "if the nature doesn't suit it" - shop-spec.md's own complaint about
// the vanilla wording.
// ----------------------------------------------------------------------------

static const u8 sDesc_Figy[] = _("Restores HP when low.\nAvoid on Bold, Modest,\nCalm or Timid natures -\nit'll confuse instead.");
static const u8 sDesc_Wiki[] = _("Restores HP when low.\nAvoid on Adamant,\nImpish, Careful or\nJolly - it'll confuse.");
static const u8 sDesc_Mago[] = _("Restores HP when low.\nAvoid on Brave,\nRelaxed, Quiet or\nSassy - it'll confuse.");
static const u8 sDesc_Aguav[] = _("Restores HP when low.\nAvoid on Naughty, Lax,\nNaive or Rash -\nit'll confuse instead.");
static const u8 sDesc_Iapapa[] = _("Restores HP when low.\nAvoid on Lonely, Mild,\nGentle or Hasty -\nit'll confuse instead.");
static const u8 sDesc_Liechi[] = _("Raises Attack one\nstage when HP drops\nbelow 25%.");
static const u8 sDesc_Petaya[] = _("Raises Sp. Atk one\nstage when HP drops\nbelow 25%.");
static const u8 sDesc_Sitrus[] = _("Restores 25% max HP\nonce HP drops to\nhalf or below.");
static const u8 sDesc_Lum[] = _("Cures any status\ncondition, once.");
static const u8 sDesc_Occa[] = _("Halves the damage\nfrom one super-\neffective Fire move.");
static const u8 sDesc_Passho[] = _("Halves the damage\nfrom one super-\neffective Water move.");
static const u8 sDesc_Wacan[] = _("Halves the damage\nfrom one super-\neffective Electric\nmove.");
static const u8 sDesc_Rindo[] = _("Halves the damage\nfrom one super-\neffective Grass move.");
static const u8 sDesc_Yache[] = _("Halves the damage\nfrom one super-\neffective Ice move.");
static const u8 sDesc_Chople[] = _("Halves the damage\nfrom one super-\neffective Fighting\nmove.");
static const u8 sDesc_Kebia[] = _("Halves the damage\nfrom one super-\neffective Poison move.");
static const u8 sDesc_Shuca[] = _("Halves the damage\nfrom one super-\neffective Ground\nmove.");
static const u8 sDesc_Coba[] = _("Halves the damage\nfrom one super-\neffective Flying move.");
static const u8 sDesc_Payapa[] = _("Halves the damage\nfrom one super-\neffective Psychic\nmove.");
static const u8 sDesc_Tanga[] = _("Halves the damage\nfrom one super-\neffective Bug move.");
static const u8 sDesc_Charti[] = _("Halves the damage\nfrom one super-\neffective Rock move.");
static const u8 sDesc_Kasib[] = _("Halves the damage\nfrom one super-\neffective Ghost move.");
static const u8 sDesc_Haban[] = _("Halves the damage\nfrom one super-\neffective Dragon\nmove.");
static const u8 sDesc_Colbur[] = _("Halves the damage\nfrom one super-\neffective Dark move.");
static const u8 sDesc_Babiri[] = _("Halves the damage\nfrom one super-\neffective Steel move.");
static const u8 sDesc_Roseli[] = _("Halves the damage\nfrom one super-\neffective Fairy move.");

static const struct FacilityShopItem sConsumables[] =
{
    { ITEM_FIGY_BERRY,   80,  0, sDesc_Figy },
    { ITEM_WIKI_BERRY,   80,  0, sDesc_Wiki },
    { ITEM_MAGO_BERRY,   80,  0, sDesc_Mago },
    { ITEM_AGUAV_BERRY,  80,  0, sDesc_Aguav },
    { ITEM_IAPAPA_BERRY, 80,  0, sDesc_Iapapa },
    { ITEM_LIECHI_BERRY, 100, 0, sDesc_Liechi },
    { ITEM_PETAYA_BERRY, 100, 0, sDesc_Petaya },
    // Unlocked clearing gauntlet 1 - shop-unlock-b2.md. Resist berries are
    // the conceptual step here: every purchase up to now made a Pokemon
    // generically better, a resist berry is a bet on a specific threat.
    { ITEM_SITRUS_BERRY, 180, 1, sDesc_Sitrus },
    { ITEM_LUM_BERRY,    160, 1, sDesc_Lum },
    { ITEM_OCCA_BERRY,   120, 1, sDesc_Occa },
    { ITEM_PASSHO_BERRY, 120, 1, sDesc_Passho },
    { ITEM_WACAN_BERRY,  120, 1, sDesc_Wacan },
    { ITEM_RINDO_BERRY,  120, 1, sDesc_Rindo },
    { ITEM_YACHE_BERRY,  120, 1, sDesc_Yache },
    { ITEM_CHOPLE_BERRY, 120, 1, sDesc_Chople },
    { ITEM_KEBIA_BERRY,  120, 1, sDesc_Kebia },
    { ITEM_SHUCA_BERRY,  120, 1, sDesc_Shuca },
    { ITEM_COBA_BERRY,   120, 1, sDesc_Coba },
    { ITEM_PAYAPA_BERRY, 120, 1, sDesc_Payapa },
    { ITEM_TANGA_BERRY,  120, 1, sDesc_Tanga },
    { ITEM_CHARTI_BERRY, 120, 1, sDesc_Charti },
    { ITEM_KASIB_BERRY,  120, 1, sDesc_Kasib },
    { ITEM_HABAN_BERRY,  120, 1, sDesc_Haban },
    { ITEM_COLBUR_BERRY, 120, 1, sDesc_Colbur },
    { ITEM_BABIRI_BERRY, 120, 1, sDesc_Babiri },
    { ITEM_ROSELI_BERRY, 120, 1, sDesc_Roseli },
};

// ----------------------------------------------------------------------------
// Keeper 2 - Held items. No description window for this keeper (not asked
// for, and every row here is a one-line "type +20%" effect already legible
// from the name).
// ----------------------------------------------------------------------------

static const struct FacilityShopItem sHeldItems[] =
{
    { ITEM_LEFTOVERS,      150, 0, NULL },
    { ITEM_CHARCOAL,       60,  0, NULL },
    { ITEM_MYSTIC_WATER,   60,  0, NULL },
    { ITEM_MIRACLE_SEED,   60,  0, NULL },
    { ITEM_MAGNET,         60,  0, NULL },
    { ITEM_NEVER_MELT_ICE, 60,  0, NULL },
    { ITEM_BLACK_BELT,     60,  0, NULL },
    { ITEM_POISON_BARB,    60,  0, NULL },
    { ITEM_SOFT_SAND,      60,  0, NULL },
    { ITEM_SHARP_BEAK,     60,  0, NULL },
    { ITEM_TWISTED_SPOON,  60,  0, NULL },
    { ITEM_SILVER_POWDER,  60,  0, NULL },
    { ITEM_HARD_STONE,     60,  0, NULL },
    { ITEM_SPELL_TAG,      60,  0, NULL },
    { ITEM_DRAGON_FANG,    60,  0, NULL },
    { ITEM_BLACK_GLASSES,  60,  0, NULL },
    { ITEM_METAL_COAT,     60,  0, NULL },
    { ITEM_SILK_SCARF,     60,  0, NULL },
    { ITEM_FAIRY_FEATHER,  60,  0, NULL },
    // Unlocked clearing gauntlet 1. Moved here from gauntlet 3 on purpose -
    // gauntlet 2 is where Spore shows up in force, and the gauntlet that
    // teaches a threat should sell its answer. See shop-unlock-b2.md.
    { ITEM_SAFETY_GOGGLES, 250, 1, NULL },
    { ITEM_WHITE_HERB,     150, 1, NULL },
    { ITEM_BLACK_SLUDGE,   120, 1, NULL },
    // Unlocked clearing gauntlet 2 - shop-unlock-b3.md. The weather rocks and
    // terrain seeds are the signature purchase of this tier: the first items
    // that improve the *team* rather than one Pokemon. Eviolite is gated
    // here on purpose - NFE Pokemon have artificially low BST, so letting it
    // in earlier would systematically break the lower tiers' caps.
    { ITEM_DAMP_ROCK,     200, 2, NULL },
    { ITEM_HEAT_ROCK,     200, 2, NULL },
    { ITEM_SMOOTH_ROCK,   200, 2, NULL },
    { ITEM_ICY_ROCK,      200, 2, NULL },
    { ITEM_ELECTRIC_SEED, 150, 2, NULL },
    { ITEM_GRASSY_SEED,   150, 2, NULL },
    { ITEM_MISTY_SEED,    150, 2, NULL },
    { ITEM_PSYCHIC_SEED,  150, 2, NULL },
    { ITEM_EVIOLITE,      350, 2, NULL },
    { ITEM_FLAME_ORB,     200, 2, NULL },
    { ITEM_TOXIC_ORB,     200, 2, NULL },
    { ITEM_EXPERT_BELT,   250, 2, NULL },
    { ITEM_MUSCLE_BAND,   150, 2, NULL },
    { ITEM_WISE_GLASSES,  150, 2, NULL },
    // Unlocked clearing gauntlet 3 - shop-unlock-b4.md. Focus Sash is the
    // signature purchase and the one to watch in playtesting - held items are
    // reusable here, so it's a permanent guaranteed-survive every battle,
    // stronger than in official play where it's consumed once and gone.
    { ITEM_FOCUS_SASH,       400, 3, NULL },
    { ITEM_ASSAULT_VEST,     350, 3, NULL },
    { ITEM_LIFE_ORB,         350, 3, NULL },
    { ITEM_HEAVY_DUTY_BOOTS, 300, 3, NULL },
    // Unlocked clearing gauntlet 4 - gauntlet-05.md. Choice Scarf is the
    // signature purchase: the singles answer to every fast Mega in the
    // gauntlet. Clear Amulet waits for gauntlet 6 (doubles, where blanking
    // Intimidate actually teaches something).
    { ITEM_CHOICE_SCARF,     450, 4, NULL },
    { ITEM_CHOICE_BAND,      400, 4, NULL },
    { ITEM_CHOICE_SPECS,     400, 4, NULL },
    { ITEM_WEAKNESS_POLICY,  350, 4, NULL },
    { ITEM_ROCKY_HELMET,     300, 4, NULL },
    { ITEM_MENTAL_HERB,      200, 4, NULL },
    // Unlocked clearing gauntlet 5 - gauntlet-06.md. Doubles tools, nothing
    // that swings a game by itself. Clear Amulet is the signature purchase:
    // it blanks the Intimidate half of gauntlet 6's teams lean on.
    { ITEM_CLEAR_AMULET,       300, 5, NULL },
    { ITEM_LOADED_DICE,        300, 5, NULL },
    { ITEM_COVERT_CLOAK,       250, 5, NULL },
    { ITEM_ROOM_SERVICE,       250, 5, NULL },
    { ITEM_THROAT_SPRAY,       250, 5, NULL },
    { ITEM_EJECT_BUTTON,       250, 5, NULL },
    { ITEM_LIGHT_CLAY,         250, 5, NULL },
    { ITEM_TERRAIN_EXTENDER,   250, 5, NULL },
    { ITEM_MIRROR_HERB,        250, 5, NULL },
    { ITEM_EJECT_PACK,         200, 5, NULL },
    { ITEM_UTILITY_UMBRELLA,   200, 5, NULL },
    { ITEM_ABILITY_SHIELD,     200, 5, NULL },
    { ITEM_PUNCHING_GLOVE,     200, 5, NULL },
    { ITEM_RED_CARD,           150, 5, NULL },
    { ITEM_ADRENALINE_ORB,     150, 5, NULL },
    // Unlocked clearing gauntlet 6 - gauntlet-07.md (wave 6). Every remaining
    // competitive item. Luck items (King's Rock, Razor Fang, Quick Claw, Focus
    // Band, Bright Powder, Lax Incense, Berserk Gene) stay out, as do the
    // duplicate incenses and anything with no legal holder.
    // Booster Energy isn't sold: the researcher in OLDALE's first house gives
    // one per Paradox species shown (OldaleCheckParadox, src/facility.c).
    { ITEM_AIR_BALLOON,      250, 6, NULL },
    { ITEM_POWER_HERB,       250, 6, NULL },
    { ITEM_PROTECTIVE_PADS,  200, 6, NULL },
    { ITEM_BLUNDER_POLICY,   200, 6, NULL },
    { ITEM_SHED_SHELL,       200, 6, NULL },
    { ITEM_SCOPE_LENS,       200, 6, NULL },
    { ITEM_RAZOR_CLAW,       200, 6, NULL },
    { ITEM_METRONOME,        200, 6, NULL },
    { ITEM_WELLSPRING_MASK,  600, 6, NULL },
    { ITEM_CORNERSTONE_MASK, 600, 6, NULL },
    { ITEM_HEARTHFLAME_MASK, 800, 6, NULL },
    { ITEM_FLAME_PLATE,      250, 6, NULL },
    { ITEM_SPLASH_PLATE,     250, 6, NULL },
    { ITEM_ZAP_PLATE,        250, 6, NULL },
    { ITEM_MEADOW_PLATE,     250, 6, NULL },
    { ITEM_ICICLE_PLATE,     250, 6, NULL },
    { ITEM_FIST_PLATE,       250, 6, NULL },
    { ITEM_TOXIC_PLATE,      250, 6, NULL },
    { ITEM_EARTH_PLATE,      250, 6, NULL },
    { ITEM_SKY_PLATE,        250, 6, NULL },
    { ITEM_MIND_PLATE,       250, 6, NULL },
    { ITEM_INSECT_PLATE,     250, 6, NULL },
    { ITEM_STONE_PLATE,      250, 6, NULL },
    { ITEM_SPOOKY_PLATE,     250, 6, NULL },
    { ITEM_DRACO_PLATE,      250, 6, NULL },
    { ITEM_DREAD_PLATE,      250, 6, NULL },
    { ITEM_IRON_PLATE,       250, 6, NULL },
    { ITEM_PIXIE_PLATE,      250, 6, NULL },
    { ITEM_NORMAL_GEM,       150, 6, NULL },
    { ITEM_FIRE_GEM,         150, 6, NULL },
    { ITEM_WATER_GEM,        150, 6, NULL },
    { ITEM_ELECTRIC_GEM,     150, 6, NULL },
    { ITEM_GRASS_GEM,        150, 6, NULL },
    { ITEM_ICE_GEM,          150, 6, NULL },
    { ITEM_FIGHTING_GEM,     150, 6, NULL },
    { ITEM_POISON_GEM,       150, 6, NULL },
    { ITEM_GROUND_GEM,       150, 6, NULL },
    { ITEM_FLYING_GEM,       150, 6, NULL },
    { ITEM_PSYCHIC_GEM,      150, 6, NULL },
    { ITEM_BUG_GEM,          150, 6, NULL },
    { ITEM_ROCK_GEM,         150, 6, NULL },
    { ITEM_GHOST_GEM,        150, 6, NULL },
    { ITEM_DRAGON_GEM,       150, 6, NULL },
    { ITEM_DARK_GEM,         150, 6, NULL },
    { ITEM_STEEL_GEM,        150, 6, NULL },
    { ITEM_FAIRY_GEM,        150, 6, NULL },
    { ITEM_SALAC_BERRY,      200, 6, NULL },
    { ITEM_GANLON_BERRY,     200, 6, NULL },
    { ITEM_APICOT_BERRY,     200, 6, NULL },
    { ITEM_LANSAT_BERRY,     200, 6, NULL },
    { ITEM_STARF_BERRY,      200, 6, NULL },
    { ITEM_MICLE_BERRY,      200, 6, NULL },
    { ITEM_CUSTAP_BERRY,     200, 6, NULL },
    { ITEM_KEE_BERRY,        150, 6, NULL },
    { ITEM_MARANGA_BERRY,    150, 6, NULL },
    { ITEM_JABOCA_BERRY,     150, 6, NULL },
    { ITEM_ROWAP_BERRY,      150, 6, NULL },
    { ITEM_ENIGMA_BERRY,     150, 6, NULL },
    { ITEM_CHILAN_BERRY,     150, 6, NULL },
    { ITEM_CHERI_BERRY,      50, 6, NULL },
    { ITEM_CHESTO_BERRY,     50, 6, NULL },
    { ITEM_PECHA_BERRY,      50, 6, NULL },
    { ITEM_RAWST_BERRY,      50, 6, NULL },
    { ITEM_ASPEAR_BERRY,     50, 6, NULL },
    { ITEM_PERSIM_BERRY,     50, 6, NULL },
    { ITEM_ORAN_BERRY,       50, 6, NULL },
    { ITEM_LEPPA_BERRY,      100, 6, NULL },
    { ITEM_BERRY_JUICE,      100, 6, NULL },
    { ITEM_SHELL_BELL,       150, 6, NULL },
    { ITEM_BIG_ROOT,         150, 6, NULL },
    { ITEM_BINDING_BAND,     150, 6, NULL },
    { ITEM_GRIP_CLAW,        150, 6, NULL },
    { ITEM_ZOOM_LENS,        150, 6, NULL },
    { ITEM_DESTINY_KNOT,     150, 6, NULL },
    { ITEM_ABSORB_BULB,      150, 6, NULL },
    { ITEM_CELL_BATTERY,     150, 6, NULL },
    { ITEM_LUMINOUS_MOSS,    150, 6, NULL },
    { ITEM_SNOWBALL,         150, 6, NULL },
    { ITEM_IRON_BALL,        100, 6, NULL },
    { ITEM_LAGGING_TAIL,     100, 6, NULL },
    { ITEM_FULL_INCENSE,     100, 6, NULL },
    { ITEM_STICKY_BARB,      100, 6, NULL },
    { ITEM_FLOAT_STONE,      100, 6, NULL },
    { ITEM_DOUSE_DRIVE,      100, 6, NULL },
    { ITEM_SHOCK_DRIVE,      100, 6, NULL },
    { ITEM_BURN_DRIVE,       100, 6, NULL },
    { ITEM_CHILL_DRIVE,      100, 6, NULL },
    { ITEM_FIRE_MEMORY,      100, 6, NULL },
    { ITEM_WATER_MEMORY,     100, 6, NULL },
    { ITEM_ELECTRIC_MEMORY,  100, 6, NULL },
    { ITEM_GRASS_MEMORY,     100, 6, NULL },
    { ITEM_ICE_MEMORY,       100, 6, NULL },
    { ITEM_FIGHTING_MEMORY,  100, 6, NULL },
    { ITEM_POISON_MEMORY,    100, 6, NULL },
    { ITEM_GROUND_MEMORY,    100, 6, NULL },
    { ITEM_FLYING_MEMORY,    100, 6, NULL },
    { ITEM_PSYCHIC_MEMORY,   100, 6, NULL },
    { ITEM_BUG_MEMORY,       100, 6, NULL },
    { ITEM_ROCK_MEMORY,      100, 6, NULL },
    { ITEM_GHOST_MEMORY,     100, 6, NULL },
    { ITEM_DRAGON_MEMORY,    100, 6, NULL },
    { ITEM_DARK_MEMORY,      100, 6, NULL },
    { ITEM_STEEL_MEMORY,     100, 6, NULL },
    { ITEM_FAIRY_MEMORY,     100, 6, NULL },
    { ITEM_THICK_CLUB,       150, 6, NULL },
    { ITEM_LEEK,             150, 6, NULL },
    // Unlocked clearing gauntlet 7 - gauntlet-08.md (wave 7), the last wave.
    { ITEM_WIDE_LENS,        150, 7, NULL },
    { ITEM_RING_TARGET,      150, 7, NULL },
};

// ----------------------------------------------------------------------------
// Keeper 3 - Mega Stones. Opens clearing gauntlet 4, the same moment the
// gauntlet 4 attendant hands over the Mega Ring. Gen 6 Megas plus the
// Legends: Z-A Megas that play best in singles, all at or under 600 BST
// after evolving - see gauntlet-05.md's Bans and Keeper 3 sections for why
// each one is in, which were cut as outclassed, and which wait for later
// gauntlets (Gengar/Kangaskhan at 7, the doubles-leaning ones at 6). Every
// stone's base Pokemon is sold by Keeper 4 by the same wave. Plain items,
// bought through the same flow as Keeper 2's.
// ----------------------------------------------------------------------------

static const struct FacilityShopItem sMegaStones[] =
{
    // Premium - 600
    { ITEM_ALAKAZITE,     600, 4, NULL },
    { ITEM_SCIZORITE,     600, 4, NULL },
    { ITEM_HERACRONITE,   600, 4, NULL },
    { ITEM_PINSIRITE,     600, 4, NULL },
    { ITEM_MAWILITE,      600, 4, NULL },
    { ITEM_MEDICHAMITE,   600, 4, NULL },
    { ITEM_ALTARIANITE,   600, 4, NULL },
    { ITEM_LOPUNNITE,     600, 4, NULL },
    { ITEM_SABLENITE,     600, 4, NULL },
    { ITEM_CLEFABLITE,    600, 4, NULL },
    { ITEM_HAWLUCHANITE,  600, 4, NULL },
    { ITEM_RAICHUNITE_Y,  600, 4, NULL },
    { ITEM_ABSOLITE_Z,    600, 4, NULL },
    { ITEM_STARAPTITE,    600, 4, NULL },
    // Strong - 450
    { ITEM_MANECTITE,     450, 4, NULL },
    { ITEM_SLOWBRONITE,   450, 4, NULL },
    { ITEM_HOUNDOOMINITE, 450, 4, NULL },
    { ITEM_SHARPEDONITE,  450, 4, NULL },
    { ITEM_PIDGEOTITE,    450, 4, NULL },
    { ITEM_ABSOLITE,      450, 4, NULL },
    { ITEM_ABOMASITE,     450, 4, NULL },
    { ITEM_BARBARACITE,   450, 4, NULL },
    { ITEM_MALAMARITE,    450, 4, NULL },
    { ITEM_SKARMORITE,    450, 4, NULL },
    { ITEM_FROSLASSITE,   450, 4, NULL },
    { ITEM_DRAGALGITE,    450, 4, NULL },
    // Standard - 300
    { ITEM_BEEDRILLITE,   300, 4, NULL },
    { ITEM_VICTREEBELITE, 300, 4, NULL },
    // Unlocked clearing gauntlet 5 - gauntlet-06.md. The doubles-leaning
    // Megas held back from gauntlet 5.
    { ITEM_SCRAFTINITE,    600, 5, NULL },
    { ITEM_RAICHUNITE_X,   600, 5, NULL },
    { ITEM_TATSUGIRINITE,  450, 5, NULL },
    { ITEM_GOLURKITE,      450, 5, NULL },
    { ITEM_CRABOMINITE,    450, 5, NULL },
    { ITEM_SCOVILLAINITE,  450, 5, NULL },
    { ITEM_CAMERUPTITE,    450, 5, NULL },
    { ITEM_DRAMPANITE,     450, 5, NULL },
    { ITEM_CHIMECHITE,     300, 5, NULL },
    { ITEM_MEOWSTICITE,    300, 5, NULL },
    // Unlocked clearing gauntlet 6 - gauntlet-07.md (wave 6). Every remaining
    // stone, whatever its Mega's BST, except the doubles-leaning ones and the
    // legendary Megas (wave 7) and the story locks (Kangaskhanite, the Lati
    // stones, Mewtwonite).
    { ITEM_GARCHOMPITE,      1000, 6, NULL },
    { ITEM_GARCHOMPITE_Z,    1000, 6, NULL },
    { ITEM_SALAMENCITE,      1000, 6, NULL },
    { ITEM_METAGROSSITE,     1000, 6, NULL },
    { ITEM_TYRANITARITE,     1000, 6, NULL },
    { ITEM_DRAGONINITE,      1000, 6, NULL },
    { ITEM_BAXCALIBRITE,     1000, 6, NULL },
    { ITEM_GENGARITE,        1000, 6, NULL },
    { ITEM_BLAZIKENITE,      1000, 6, NULL },
    { ITEM_CHARIZARDITE_X,   750, 6, NULL },
    { ITEM_CHARIZARDITE_Y,   750, 6, NULL },
    { ITEM_GYARADOSITE,      750, 6, NULL },
    { ITEM_SWAMPERTITE,      750, 6, NULL },
    { ITEM_BLASTOISINITE,    750, 6, NULL },
    { ITEM_SCEPTILITE,       750, 6, NULL },
    { ITEM_GRENINJITE,       750, 6, NULL },
    { ITEM_GOLISOPITE,       750, 6, NULL },
    { ITEM_CHESNAUGHTITE,    750, 6, NULL },
    { ITEM_FERALIGITE,       750, 6, NULL },
    { ITEM_DELPHOXITE,       750, 6, NULL },
    { ITEM_EMBOARITE,        750, 6, NULL },
    { ITEM_LUCARIONITE,      750, 6, NULL },
    { ITEM_LUCARIONITE_Z,    750, 6, NULL },
    { ITEM_GLIMMORANITE,     750, 6, NULL },
    { ITEM_VENUSAURITE,      750, 6, NULL },
    { ITEM_MEGANIUMITE,      750, 6, NULL },
    { ITEM_STARMINITE,       750, 6, NULL },
    { ITEM_CHANDELURITE,     750, 6, NULL },
    { ITEM_GARDEVOIRITE,     750, 6, NULL },
    { ITEM_GALLADITE,        750, 6, NULL },
    { ITEM_AERODACTYLITE,    750, 6, NULL },
    { ITEM_EELEKTROSSITE,    750, 6, NULL },
    { ITEM_EXCADRITE,        750, 6, NULL },
    { ITEM_PYROARITE,        750, 6, NULL },
    { ITEM_BANETTITE,        300, 6, NULL },
    { ITEM_SCOLIPITE,        300, 6, NULL },
    { ITEM_FALINKSITE,       300, 6, NULL },
    // Unlocked clearing gauntlet 7 - gauntlet-08.md (wave 7), the last wave. The legendary
    // Megas and the doubles-leaning stones. Zygardite is never sold during the
    // gauntlets (Brandon's), nor are the story-locked stones.
    { ITEM_DARKRANITE,       1200, 7, NULL },
    { ITEM_MAGEARNITE,       1200, 7, NULL },
    { ITEM_ZERAORITE,        1200, 7, NULL },
    { ITEM_HEATRANITE,       1200, 7, NULL },
    { ITEM_DIANCITE,         1200, 7, NULL },
    { ITEM_FLOETTITE,        750, 7, NULL },
    { ITEM_AMPHAROSITE,      750, 7, NULL },
    { ITEM_AGGRONITE,        750, 7, NULL },
    { ITEM_STEELIXITE,       750, 7, NULL },
    { ITEM_AUDINITE,         300, 7, NULL },
    { ITEM_GLALITITE,        300, 7, NULL },
};

// ----------------------------------------------------------------------------
// Keeper 4 - Pokemon. One master array per price tier, spanning every
// gauntlet's additions to that tier - not one array per gauntlet. Gauntlet
// 1's pool is unlockGauntlet 0; shop-unlock-b2.md's additions are
// unlockGauntlet 1. Azumarill, Medicham and Linoone were never on a real ban
// list in code (see FacilityCheckEligible/the trainer pool) - "banned" at
// tier 1 only ever meant "not in this list" - so they need no extra
// unbanning step beyond appearing here.
// ----------------------------------------------------------------------------

static const struct FacilityShopMon sPremiumMons[] =
{
    { SPECIES_SABLEYE,   250, 0 },
    { SPECIES_PARASECT,  250, 0 },
    { SPECIES_FERROSEED, 250, 0 },
    { SPECIES_BUTTERFREE,250, 0 },
    { SPECIES_MURKROW,   250, 0 },
    { SPECIES_MAWILE,    250, 0 },
    { SPECIES_ROSELIA,   250, 0 },
    { SPECIES_GABITE,    250, 0 },
    { SPECIES_AMOONGUSS,   250, 1 },
    { SPECIES_WHIMSICOTT,  250, 1 },
    { SPECIES_TOXAPEX,     250, 1 },
    { SPECIES_MIMIKYU,     250, 1 },
    { SPECIES_BRONZONG,    250, 1 },
    { SPECIES_INDEEDEE,    250, 1 },
    { SPECIES_GASTRODON,   250, 1 },
    { SPECIES_AZUMARILL,   250, 1 },
    { SPECIES_HITMONTOP,   250, 1 },
    { SPECIES_MANECTRIC,   250, 1 },
    { SPECIES_ARAQUANID,   250, 1 },
    { SPECIES_POLITOED,    250, 1 },
    // Exactly-500-BST additions, tiered by competitive strength like the
    // rest of this wave. Calyrex (legendary) and Minior (440 as bought,
    // 500 only once Shields Down breaks) are left out on purpose.
    { SPECIES_GENGAR,      250, 1 },
    { SPECIES_HAWLUCHA,    250, 1 },
    { SPECIES_KLEAVOR,     250, 1 },
    // Added after the gauntlets were built (OU, missed by the first pass).
    { SPECIES_ALOMOMOLA,   250, 1 },
    // Unlocked clearing gauntlet 2 - shop-unlock-b3.md.
    { SPECIES_VOLCARONA,      400, 2 },
    { SPECIES_FERROTHORN,     400, 2 },
    { SPECIES_GHOLDENGO,      400, 2 },
    { SPECIES_KINGAMBIT,      400, 2 },
    { SPECIES_HATTERENE,      400, 2 },
    { SPECIES_GRIMMSNARL,     400, 2 },
    { SPECIES_GLISCOR,        400, 2 },
    { SPECIES_EXCADRILL,      400, 2 },
    { SPECIES_CHANSEY,        400, 2 },
    { SPECIES_PORYGON2,       400, 2 },
    { SPECIES_RILLABOOM,      400, 2 },
    { SPECIES_MILOTIC,        400, 2 },
    { SPECIES_GARDEVOIR,      400, 2 },
    { SPECIES_MAGNEZONE,      400, 2 },
    { SPECIES_HIPPOWDON,      400, 2 },
    { SPECIES_NINETALES_ALOLA,400, 2 },
    { SPECIES_WEAVILE,        400, 2 },
    { SPECIES_AEGISLASH,      400, 2 },
    { SPECIES_ANNIHILAPE,     400, 2 },
    { SPECIES_TOGEKISS,       400, 2 },
    { SPECIES_KINGDRA,        400, 2 },
    { SPECIES_URSALUNA,       400, 2 },
    { SPECIES_SNEASLER,       400, 2 },
    { SPECIES_SERPERIOR,      400, 2 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 3's pool.
    { SPECIES_SKELEDIRGE,             400, 2 },
    { SPECIES_PRIMARINA,              400, 2 },
    { SPECIES_SLOWKING_GALAR,         400, 2 },
    // Added after the gauntlets were built (UUBL, missed by the first pass).
    { SPECIES_POLTEAGEIST,            400, 2 },
    // Unlocked clearing gauntlet 3 - shop-unlock-b4.md.
    { SPECIES_ARCANINE,       500, 3 },
    // Doubles staples gauntlet 4's CPU teams already used but the shop
    // never sold - see shop-unlock-b4.md.
    { SPECIES_INCINEROAR,      500, 3 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 4's pool.
    { SPECIES_CINDERACE,              500, 3 },
    { SPECIES_GRENINJA,               500, 3 },
    { SPECIES_MEOWSCARADA,            500, 3 },
    // Unlocked clearing gauntlet 4 - gauntlet-05.md. The 600-BST
    // pseudo-legendaries plus the singles-relevant Paradox / Ultra Beast /
    // Mythical picks; the Ubers-grade ones wait for gauntlet 7.
    { SPECIES_GARCHOMP,        850, 4 },
    { SPECIES_DRAGAPULT,       850, 4 },
    { SPECIES_DRAGONITE,       850, 4 },
    { SPECIES_TYRANITAR,       850, 4 },
    { SPECIES_METAGROSS,       850, 4 },
    { SPECIES_GREAT_TUSK,      850, 4 },
    { SPECIES_IRON_VALIANT,    850, 4 },
    { SPECIES_IRON_TREADS,     850, 4 },
    { SPECIES_IRON_MOTH,       850, 4 },
    { SPECIES_RAGING_BOLT,     850, 4 },
    { SPECIES_IRON_BOULDER,    850, 4 },
    { SPECIES_IRON_CROWN,      850, 4 },
    { SPECIES_KELDEO,          850, 4 },
    { SPECIES_VOLCANION,       850, 4 },
    { SPECIES_PECHARUNT,       850, 4 },
    { SPECIES_MEW,             850, 4 },
    { SPECIES_JIRACHI,         850, 4 },
    { SPECIES_CELESTEELA,      850, 4 },
    { SPECIES_BLACEPHALON,     850, 4 },
    { SPECIES_BUZZWOLE,        850, 4 },
    // Unlocked clearing gauntlet 5 - gauntlet-06.md. Doubles-relevant
    // Paradox / Ultra Beasts and the non-Uber sub-legendaries; the
    // Ubers-grade ones (Chi-Yu, Chien-Pao, Spectrier, Zapdos-Galar, Urshifu
    // Single Strike, Landorus / Enamorus Incarnate) wait. Ogerpon is Teal
    // only - no masks are sold.
    { SPECIES_IRON_HANDS,               850, 5 },
    { SPECIES_LANDORUS_THERIAN,         850, 5 },
    { SPECIES_HEATRAN,                  850, 5 },
    { SPECIES_URSHIFU_RAPID_STRIKE,     850, 5 },
    { SPECIES_TAPU_KOKO,                850, 5 },
    { SPECIES_TAPU_LELE,                850, 5 },
    { SPECIES_TAPU_FINI,                850, 5 },
    { SPECIES_TING_LU,                  850, 5 },
    { SPECIES_TORNADUS,                 850, 5 },
    { SPECIES_THUNDURUS,                850, 5 },
    { SPECIES_OGERPON,                  850, 5 },
    // Unlocked clearing gauntlet 6 - gauntlet-07.md (wave 6). The singles finale:
    // everything held back until now.
    { SPECIES_FLUTTER_MANE,           1400, 6 },
    { SPECIES_ROARING_MOON,           1400, 6 },
    { SPECIES_CHI_YU,                 1400, 6 },
    { SPECIES_CHIEN_PAO,              1400, 6 },
    { SPECIES_DARKRAI,                1400, 6 },
    { SPECIES_DEOXYS_ATTACK,          1400, 6 },
    { SPECIES_DEOXYS_SPEED,           1400, 6 },
    { SPECIES_SHAYMIN_SKY,            1400, 6 },
    { SPECIES_MAGEARNA,               1400, 6 },
    { SPECIES_MARSHADOW,              1400, 6 },
    { SPECIES_ZYGARDE_50,             1400, 6 },
    { SPECIES_SPECTRIER,              1400, 6 },
    { SPECIES_URSHIFU_SINGLE_STRIKE,  1400, 6 },
    // Added after the gauntlets were built: only 505 BST, but Ubers-grade
    // (Strong Jaw Fishious Rend), so it waits with the other Ubers.
    { SPECIES_DRACOVISH,              1400, 6 },
    // Endgame stock, unlocked clearing gauntlet 8 (storyline.md, the free
    // shop). Palafin stays on the gauntlets' permanent ban list; with all
    // eight cleared there's no gauntlet left for it to break.
    { SPECIES_PALAFIN,                1400, 8 },
};

static const struct FacilityShopMon sStrongMons[] =
{
    { SPECIES_HAUNTER,    200, 0 },
    { SPECIES_PAWNIARD,   200, 0 },
    { SPECIES_CROAGUNK,   200, 0 },
    { SPECIES_MIENFOO,    200, 0 },
    { SPECIES_SCRAGGY,    200, 0 },
    { SPECIES_GURDURR,    200, 0 },
    { SPECIES_METANG,     200, 0 },
    { SPECIES_PORYGON,    200, 0 },
    { SPECIES_SUDOWOODO,  200, 0 },
    { SPECIES_PUPITAR,    200, 0 },
    { SPECIES_KROKOROK,   200, 0 },
    { SPECIES_MIGHTYENA,  200, 0 },
    { SPECIES_MASQUERAIN, 200, 0 },
    { SPECIES_ARIADOS,    200, 0 },
    { SPECIES_MARSHTOMP,  200, 0 },
    { SPECIES_CHINCHOU,   200, 0 },
    { SPECIES_DUNSPARCE,  200, 0 },
    { SPECIES_DRIFLOON,   200, 0 },
    { SPECIES_VULLABY,    200, 0 },
    { SPECIES_NATU,       200, 0 },
    { SPECIES_SOLOSIS,    200, 0 },
    { SPECIES_MAREANIE,   200, 0 },
    { SPECIES_KLEFKI,        200, 1 },
    { SPECIES_TOGETIC,       200, 1 },
    { SPECIES_CLEFAIRY,      200, 1 },
    { SPECIES_JELLICENT,     200, 1 },
    { SPECIES_LANTURN,       200, 1 },
    { SPECIES_ORANGURU,      200, 1 },
    { SPECIES_CORVIKNIGHT,   200, 1 },
    { SPECIES_DUSCLOPS,      200, 1 },
    { SPECIES_CLODSIRE,      200, 1 },
    { SPECIES_SCRAFTY,       200, 1 },
    { SPECIES_HARIYAMA,      200, 1 },
    { SPECIES_CRAWDAUNT,     200, 1 },
    { SPECIES_BARRASKEWDA,   200, 1 },
    { SPECIES_SALAZZLE,      200, 1 },
    { SPECIES_HOUNDOOM,      200, 1 },
    { SPECIES_VIKAVOLT,      200, 1 },
    { SPECIES_MEDICHAM,      200, 1 },
    { SPECIES_MAROWAK_ALOLA, 200, 1 },
    { SPECIES_RAICHU_ALOLA,  200, 1 },
    { SPECIES_PELIPPER,      200, 1 },
    { SPECIES_TORKOAL,       200, 1 },
    { SPECIES_ABOMASNOW,     200, 1 },
    { SPECIES_GARGANACL,     200, 1 },
    { SPECIES_COPPERAJAH,    200, 1 },
    { SPECIES_GOLEM,         200, 1 },
    { SPECIES_MUDSDALE,      200, 1 },
    { SPECIES_PASSIMIAN,     200, 1 },
    { SPECIES_BISHARP,       200, 1 },
    // Exactly-500-BST additions - see the note in sPremiumMons. Scyther
    // was pulled forward from the gauntlet 3 wave; it's still an Eviolite
    // target once Eviolite unlocks there.
    { SPECIES_MUK_ALOLA,     200, 1 },
    { SPECIES_CLAWITZER,     200, 1 },
    { SPECIES_BARBARACLE,    200, 1 },
    { SPECIES_SCYTHER,       200, 1 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 2's pool.
    { SPECIES_KILOWATTREL,            200, 1 },
    // Added after the gauntlets were built (UU, missed by the first pass).
    { SPECIES_LOKIX,                  200, 1 },
    // Unlocked clearing gauntlet 2 - shop-unlock-b3.md.
    { SPECIES_NINETALES,     300, 2 },
    { SPECIES_GIGALITH,      300, 2 },
    { SPECIES_VENUSAUR,      300, 2 },
    { SPECIES_TANGROWTH,     300, 2 },
    { SPECIES_KROOKODILE,    300, 2 },
    { SPECIES_RHYPERIOR,     300, 2 },
    { SPECIES_FLYGON,        300, 2 },
    { SPECIES_MANDIBUZZ,     300, 2 },
    { SPECIES_MAMOSWINE,     300, 2 },
    { SPECIES_FROSLASS,      300, 2 },
    { SPECIES_SWAMPERT,      300, 2 },
    { SPECIES_GYARADOS,      300, 2 },
    { SPECIES_ROTOM_WASH,    300, 2 },
    { SPECIES_ROTOM_HEAT,    300, 2 },
    { SPECIES_ROTOM_MOW,     300, 2 },
    { SPECIES_GALLADE,       300, 2 },
    { SPECIES_CROBAT,        300, 2 },
    { SPECIES_HAXORUS,       300, 2 },
    { SPECIES_NOIVERN,       300, 2 },
    { SPECIES_HONCHKROW,     300, 2 },
    { SPECIES_PORYGON_Z,     300, 2 },
    { SPECIES_ELECTIVIRE,    300, 2 },
    { SPECIES_YANMEGA,       300, 2 },
    { SPECIES_DUSKNOIR,      300, 2 },
    { SPECIES_TOXICROAK,     300, 2 },
    { SPECIES_SEISMITOAD,    300, 2 },
    { SPECIES_KABUTOPS,      300, 2 },
    { SPECIES_LYCANROC,      300, 2 },
    { SPECIES_SANDACONDA,    300, 2 },
    { SPECIES_CETITAN,       300, 2 },
    { SPECIES_ARCTOZOLT,     300, 2 },
    { SPECIES_PINCURCHIN,    300, 2 },
    { SPECIES_WEEZING_GALAR, 300, 2 },
    { SPECIES_BLISSEY,       300, 2 },
    { SPECIES_SNORLAX,       300, 2 },
    { SPECIES_STARMIE,       300, 2 },
    { SPECIES_AERODACTYL,    300, 2 },
    { SPECIES_CLOYSTER,      300, 2 },
    { SPECIES_AMPHAROS,      300, 2 },
    { SPECIES_SYLVEON,       300, 2 },
    { SPECIES_ESPEON,        300, 2 },
    { SPECIES_UMBREON,       300, 2 },
    { SPECIES_VAPOREON,      300, 2 },
    { SPECIES_JOLTEON,       300, 2 },
    { SPECIES_FLAREON,       300, 2 },
    { SPECIES_LEAFEON,       300, 2 },
    { SPECIES_GLACEON,       300, 2 },
    { SPECIES_BRAVIARY,      300, 2 },
    { SPECIES_TINKATON,      300, 2 },
    { SPECIES_LUCARIO,       300, 2 },
    { SPECIES_CERULEDGE,     300, 2 },
    { SPECIES_HYDRAPPLE,     300, 2 },
    { SPECIES_GOLISOPOD,     300, 2 },
    { SPECIES_FERALIGATR,    300, 2 },
    // Eviolite targets, same tier/price as the rest of this wave -
    // shop-unlock-b3.md.
    { SPECIES_RHYDON,        300, 2 },
    { SPECIES_GLIGAR,        300, 2 },
    { SPECIES_MAGNETON,      300, 2 },
    { SPECIES_TYPE_NULL,     300, 2 },
    { SPECIES_DOUBLADE,      300, 2 },
    { SPECIES_SNEASEL,       300, 2 },
    { SPECIES_DURALUDON,     300, 2 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 3's pool.
    { SPECIES_INTELEON,               300, 2 },
    { SPECIES_QUAQUAVAL,              300, 2 },
    { SPECIES_DECIDUEYE,              300, 2 },
    { SPECIES_TYPHLOSION,             300, 2 },
    { SPECIES_SAMUROTT,               300, 2 },
    { SPECIES_EMBOAR,                 300, 2 },
    { SPECIES_CHESNAUGHT,             300, 2 },
    { SPECIES_DELPHOX,                300, 2 },
    { SPECIES_ZOROARK_HISUI,          300, 2 },
    { SPECIES_OVERQWIL,               300, 2 },
    // Unlocked clearing gauntlet 3 - shop-unlock-b4.md.
    { SPECIES_ARCHEOPS,      375, 3 },
    // Doubles staples - see the note in sPremiumMons.
    { SPECIES_TALONFLAME,      375, 3 },
    { SPECIES_TSAREENA,        375, 3 },
    { SPECIES_DONDOZO,         375, 3 },
    { SPECIES_CONKELDURR,      375, 3 },
    { SPECIES_GLIMMORA,        375, 3 },
    { SPECIES_FARIGIRAF,       375, 3 },
    { SPECIES_ARBOLIVA,        375, 3 },
    { SPECIES_FLORGES,       375, 3 },
    // Sub-legendaries judged safe for gauntlet 5's singles (see the
    // gauntlet 4 legendary draft) - the rest of the 551-599 legendary /
    // Paradox / UB band is held back on purpose.
    { SPECIES_ENTEI,         375, 3 },
    { SPECIES_RAIKOU,        375, 3 },
    { SPECIES_SUICUNE,       375, 3 },
    { SPECIES_ZAPDOS,        375, 3 },
    { SPECIES_MOLTRES,       375, 3 },
    { SPECIES_AZELF,         375, 3 },
    { SPECIES_TERRAKION,     375, 3 },
    { SPECIES_COBALION,      375, 3 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 4's pool.
    { SPECIES_MAUSHOLD,               375, 3 },
    { SPECIES_SINISTCHA_UNREMARKABLE, 375, 3 },
    { SPECIES_ARMAROUGE,              375, 3 },
    { SPECIES_BASCULEGION_M,          375, 3 },
    { SPECIES_TYPHLOSION_HISUI,       375, 3 },
    { SPECIES_SAMUROTT_HISUI,         375, 3 },
    // Added after the gauntlets were built (UU, missed by the first pass).
    { SPECIES_ARCANINE_HISUI,         375, 3 },
    // Unlocked clearing gauntlet 4 - gauntlet-05.md.
    { SPECIES_SALAMENCE,       700, 4 },
    { SPECIES_HYDREIGON,       700, 4 },
    { SPECIES_BAXCALIBUR,      700, 4 },
    { SPECIES_ARCHALUDON,      700, 4 },
    { SPECIES_KOMMO_O,         700, 4 },
    { SPECIES_IRON_LEAVES,     700, 4 },
    { SPECIES_SLITHER_WING,    700, 4 },
    { SPECIES_SANDY_SHOCKS,    700, 4 },
    { SPECIES_NIHILEGO,        700, 4 },
    { SPECIES_XURKITREE,       700, 4 },
    { SPECIES_VICTINI,         700, 4 },
    { SPECIES_CELEBI,          700, 4 },
    { SPECIES_MELOETTA,        700, 4 },
    { SPECIES_ZERAORA,         700, 4 },
    { SPECIES_MELMETAL,        700, 4 },
    { SPECIES_ZARUDE,          700, 4 },
    { SPECIES_MANAPHY,         700, 4 },
    { SPECIES_DEOXYS_DEFENSE,  700, 4 },
    { SPECIES_SHAYMIN,         700, 4 },
    { SPECIES_HOOPA,           700, 4 },
    // Unlocked clearing gauntlet 5 - gauntlet-06.md.
    { SPECIES_IRON_JUGULIS,             700, 5 },
    { SPECIES_STAKATAKA,                700, 5 },
    { SPECIES_TAPU_BULU,                700, 5 },
    { SPECIES_CRESSELIA,                700, 5 },
    { SPECIES_TORNADUS_THERIAN,         700, 5 },
    { SPECIES_THUNDURUS_THERIAN,        700, 5 },
    { SPECIES_REGIELEKI,                700, 5 },
    { SPECIES_REGIDRAGO,                700, 5 },
    { SPECIES_OKIDOGI,                  700, 5 },
    { SPECIES_MUNKIDORI,                700, 5 },
    { SPECIES_FEZANDIPITI,              700, 5 },
    { SPECIES_MOLTRES_GALAR,            700, 5 },
    { SPECIES_ENAMORUS_THERIAN,         700, 5 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 6's pool.
    { SPECIES_URSALUNA_BLOODMOON,     700, 5 },
    // Unlocked clearing gauntlet 6 - gauntlet-07.md (wave 6). The singles finale:
    // everything held back until now.
    { SPECIES_WALKING_WAKE,           1150, 6 },
    { SPECIES_GOUGING_FIRE,           1150, 6 },
    { SPECIES_IRON_BUNDLE,            1150, 6 },
    { SPECIES_KARTANA,                1150, 6 },
    { SPECIES_PHEROMOSA,              1150, 6 },
    { SPECIES_NAGANADEL,              1150, 6 },
    { SPECIES_GENESECT,               1150, 6 },
    { SPECIES_ZAPDOS_GALAR,           1150, 6 },
    { SPECIES_LANDORUS_INCARNATE,     1150, 6 },
    { SPECIES_ENAMORUS_INCARNATE,     1150, 6 },
    { SPECIES_DEOXYS_NORMAL,          1150, 6 },
    { SPECIES_NECROZMA,               1150, 6 },
    { SPECIES_DIANCIE,                1150, 6 },
    { SPECIES_HOUNDSTONE,             1150, 6 },
    { SPECIES_DARMANITAN_GALAR,       1150, 6 },
    // Unlocked clearing gauntlet 7 - gauntlet-08.md (wave 7), the last wave. Floette-Eternal,
    // for Floettite.
    { SPECIES_FLOETTE_ETERNAL,      1150, 7 },
};

static const struct FacilityShopMon sStandardMons[] =
{
    { SPECIES_COMBUSKEN,  150, 0 },
    { SPECIES_MONFERNO,   150, 0 },
    { SPECIES_FROGADIER,  150, 0 },
    { SPECIES_DEWOTT,     150, 0 },
    { SPECIES_QUILLADIN,  150, 0 },
    { SPECIES_GROVYLE,    150, 0 },
    { SPECIES_IVYSAUR,    150, 0 },
    { SPECIES_SERVINE,    150, 0 },
    { SPECIES_DARTRIX,    150, 0 },
    { SPECIES_THWACKEY,   150, 0 },
    { SPECIES_FLORAGATO,  150, 0 },
    { SPECIES_TORRACAT,   150, 0 },
    { SPECIES_RABOOT,     150, 0 },
    { SPECIES_CROCALOR,   150, 0 },
    { SPECIES_BRAIXEN,    150, 0 },
    { SPECIES_QUAXWELL,   150, 0 },
    { SPECIES_BRIONNE,    150, 0 },
    { SPECIES_DRIZZILE,   150, 0 },
    { SPECIES_CROCONAW,   150, 0 },
    { SPECIES_PRINPLUP,   150, 0 },
    { SPECIES_WARTORTLE,  150, 0 },
    { SPECIES_QUILAVA,    150, 0 },
    { SPECIES_CHARMELEON, 150, 0 },
    { SPECIES_PIGNITE,    150, 0 },
    { SPECIES_GROTLE,     150, 0 },
    { SPECIES_BAYLEEF,    150, 0 },
    { SPECIES_LUXIO,      150, 0 },
    { SPECIES_FLAAFFY,    150, 0 },
    { SPECIES_MAGNEMITE,  150, 0 },
    { SPECIES_MACHOKE,    150, 0 },
    { SPECIES_GRAVELER,   150, 0 },
    { SPECIES_FLETCHINDER,150, 0 },
    { SPECIES_STARAVIA,   150, 0 },
    { SPECIES_KADABRA,    150, 0 },
    { SPECIES_LAMPENT,    150, 0 },
    { SPECIES_MORGREM,    150, 0 },
    { SPECIES_WHIRLIPEDE, 150, 0 },
    { SPECIES_NIDORINO,   150, 0 },
    { SPECIES_NIDORINA,   150, 0 },
    { SPECIES_KOFFING,    150, 0 },
    { SPECIES_SKRELP,     150, 0 },
    { SPECIES_STUNKY,     150, 0 },
    { SPECIES_BOLDORE,    150, 0 },
    { SPECIES_ONIX,       150, 0 },
    { SPECIES_MUDBRAY,    150, 0 },
    { SPECIES_PALPITOAD,  150, 0 },
    { SPECIES_KRICKETUNE, 150, 0 },
    { SPECIES_BEEDRILL,   150, 0 },
    { SPECIES_YANMA,      150, 0 },
    { SPECIES_FURRET,     150, 0 },
    { SPECIES_RATICATE,   150, 0 },
    { SPECIES_LICKITUNG,  150, 0 },
    { SPECIES_CHATOT,     150, 0 },
    { SPECIES_WOOBAT,     150, 0 },
    { SPECIES_RUFFLET,    150, 0 },
    { SPECIES_PANCHAM,    150, 0 },
    { SPECIES_STUFFUL,    150, 0 },
    { SPECIES_TIMBURR,    150, 0 },
    { SPECIES_ZORUA,      150, 0 },
    { SPECIES_ESPURR,     150, 0 },
    { SPECIES_MUNNA,      150, 0 },
    { SPECIES_BRONZOR,    150, 0 },
    { SPECIES_DROWZEE,    150, 0 },
    { SPECIES_SPOINK,     150, 0 },
    { SPECIES_KIRLIA,     150, 0 },
    { SPECIES_NOSEPASS,   150, 0 },
    { SPECIES_CHARJABUG,  150, 0 },
    { SPECIES_JOLTIK,     150, 0 },
    { SPECIES_ELEKID,     150, 0 },
    { SPECIES_CORSOLA,    150, 0 },
    { SPECIES_STARYU,     150, 0 },
    { SPECIES_POLIWHIRL,  150, 0 },
    { SPECIES_FOONGUS,    150, 0 },
    { SPECIES_PONYTA,     150, 0 },
    { SPECIES_GROWLITHE,  150, 0 },
    { SPECIES_LARVESTA,   150, 0 },
    { SPECIES_PIDGEOTTO,  150, 0 },
    { SPECIES_TRANQUILL,  150, 0 },
    { SPECIES_CAMERUPT,   150, 1 },
    { SPECIES_TURTONATOR, 150, 1 },
    { SPECIES_MAGCARGO,   150, 1 },
    { SPECIES_SWANNA,     150, 1 },
    { SPECIES_EXPLOUD,    150, 1 },
    { SPECIES_ZEBSTRIKA,  150, 1 },
    { SPECIES_FROSMOTH,   150, 1 },
    { SPECIES_AMBIPOM,    150, 1 },
    { SPECIES_BEWEAR,     150, 1 },
    { SPECIES_DREDNAW,    150, 1 },
    { SPECIES_JUMPLUFF,   150, 1 },
    { SPECIES_COMFEY,     150, 1 },
    { SPECIES_LINOONE,    150, 1 },
    { SPECIES_SANDSLASH,  150, 1 },
    { SPECIES_LUDICOLO,   150, 1 },
    { SPECIES_NIDOKING,   150, 1 },
    { SPECIES_NIDOQUEEN,  150, 1 },
    { SPECIES_ALAKAZAM,   150, 1 },
    { SPECIES_MACHAMP,    150, 1 },
    { SPECIES_SCIZOR,     150, 1 },
    { SPECIES_SKARMORY,   150, 1 },
    { SPECIES_SLOWBRO,    150, 1 },
    { SPECIES_SLOWKING,   150, 1 },
    { SPECIES_WEEZING,    150, 1 },
    { SPECIES_MUK,        150, 1 },
    { SPECIES_HERACROSS,  150, 1 },
    { SPECIES_DONPHAN,    150, 1 },
    { SPECIES_URSARING,   150, 1 },
    { SPECIES_MILTANK,    150, 1 },
    { SPECIES_CLAYDOL,    150, 1 },
    { SPECIES_CRADILY,    150, 1 },
    { SPECIES_ARMALDO,    150, 1 },
    { SPECIES_REVAVROOM,  150, 1 },
    { SPECIES_FLAMIGO,    150, 1 },
    { SPECIES_ORTHWORM,   150, 1 },
    { SPECIES_TOXTRICITY, 150, 1 },
    // Exactly-500-BST additions - see the note in sPremiumMons. Stoutland
    // was pulled forward from the gauntlet 3 wave.
    { SPECIES_GOLDUCK,    150, 1 },
    { SPECIES_RAPIDASH,   150, 1 },
    { SPECIES_RAPIDASH_GALAR, 150, 1 },
    { SPECIES_PINSIR,     150, 1 },
    { SPECIES_WAILORD,    150, 1 },
    { SPECIES_DRAPION,    150, 1 },
    { SPECIES_LEAVANNY,   150, 1 },
    { SPECIES_CARBINK,    150, 1 },
    { SPECIES_STOUTLAND,  150, 1 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 2's pool.
    { SPECIES_BANETTE,                150, 1 },
    { SPECIES_GLALIE,                 150, 1 },
    { SPECIES_AUDINO,                 150, 1 },
    { SPECIES_FALINKS,                150, 1 },
    // Unlocked clearing gauntlet 2 - shop-unlock-b3.md.
    { SPECIES_VANILLUXE,  200, 2 },
    { SPECIES_FLOATZEL,   200, 2 },
    { SPECIES_OMASTAR,    200, 2 },
    { SPECIES_POLIWRATH,  200, 2 },
    { SPECIES_GOREBYSS,   200, 2 },
    { SPECIES_HUNTAIL,    200, 2 },
    { SPECIES_EXEGGUTOR,  200, 2 },
    { SPECIES_LILLIGANT,  200, 2 },
    { SPECIES_VICTREEBEL, 200, 2 },
    { SPECIES_SHIFTRY,    200, 2 },
    { SPECIES_SAWSBUCK,   200, 2 },
    { SPECIES_CHERRIM,    200, 2 },
    { SPECIES_CHARIZARD,  200, 2 },
    { SPECIES_MAGMORTAR,  200, 2 },
    { SPECIES_BLAZIKEN,   200, 2 },
    { SPECIES_BEARTIC,    200, 2 },
    { SPECIES_LAPRAS,     200, 2 },
    { SPECIES_WALREIN,    200, 2 },
    { SPECIES_SCEPTILE,   200, 2 },
    // Gauntlet 3's Scorched team used Solrock before the shop sold it.
    { SPECIES_SOLROCK,         200, 2 },
    { SPECIES_EELEKTROSS, 200, 2 },
    { SPECIES_TENTACRUEL, 200, 2 },
    { SPECIES_SIRFETCHD,  200, 2 },
    // Moved down from the gauntlet 7 draft (gauntlet-07.md): never sold, not too
    // strong - gauntlet 3's pool.
    { SPECIES_MEGANIUM,               200, 2 },
    { SPECIES_BLASTOISE,              200, 2 },
    { SPECIES_STEELIX,                200, 2 },
    { SPECIES_AGGRON,                 200, 2 },
    { SPECIES_CHANDELURE,             200, 2 },
    { SPECIES_PYROAR,                 200, 2 },
    { SPECIES_SCOLIPEDE,              200, 2 },
    // Unlocked clearing gauntlet 3 - shop-unlock-b4.md.
    { SPECIES_SILVALLY,   250, 3 },
    // Doubles staples - see the note in sPremiumMons. Indeedee-F is the
    // form with Follow Me; only the male was sold before.
    { SPECIES_COALOSSAL,       250, 3 },
    { SPECIES_MR_RIME,         250, 3 },
    { SPECIES_DRACOZOLT,       250, 3 },
    { SPECIES_GALVANTULA,      250, 3 },
    { SPECIES_INDEEDEE_F,      250, 3 },
    { SPECIES_ARTICUNO,   250, 3 },
    { SPECIES_REGIROCK,   250, 3 },
    { SPECIES_REGICE,     250, 3 },
    { SPECIES_REGISTEEL,  250, 3 },
    { SPECIES_UXIE,       250, 3 },
    { SPECIES_MESPRIT,    250, 3 },
    { SPECIES_VIRIZION,   250, 3 },
    // Unlocked clearing gauntlet 4 - gauntlet-05.md.
    { SPECIES_GOODRA,          550, 4 },
    { SPECIES_GOODRA_HISUI,    550, 4 },
    { SPECIES_SCREAM_TAIL,     550, 4 },
    { SPECIES_BRUTE_BONNET,    550, 4 },
    { SPECIES_IRON_THORNS,     550, 4 },
    { SPECIES_GUZZLORD,        550, 4 },
    // Unlocked clearing gauntlet 5 - gauntlet-06.md.
    { SPECIES_ARTICUNO_GALAR,           550, 5 },
    { SPECIES_GLASTRIER,                550, 5 },
    { SPECIES_WO_CHIEN,                 550, 5 },
    // Unlocked clearing gauntlet 6 - gauntlet-07.md (wave 6). The singles finale:
    // everything held back until now.
    { SPECIES_ESPATHRA,               900, 6 },
};

static const struct FacilityShopMon sBudgetMons[] =
{
    { SPECIES_SPINDA,     100, 0 },
    { SPECIES_DELCATTY,   100, 0 },
    { SPECIES_AIPOM,      100, 0 },
    { SPECIES_TEDDIURSA,  100, 0 },
    { SPECIES_LEDIAN,     100, 0 },
    { SPECIES_DUSTOX,     100, 0 },
    { SPECIES_BEAUTIFLY,  100, 0 },
    { SPECIES_PLUSLE,     100, 0 },
    { SPECIES_MINUN,      100, 0 },
    { SPECIES_PACHIRISU,  100, 0 },
    { SPECIES_GRIMER,     100, 0 },
    // Unlocked clearing gauntlet 4 - gauntlet-05.md. Base Pokemon for Mega
    // Stones that weren't sold yet, priced for what they are without the
    // stone (the stone carries the premium). Clefable also arrives here as
    // a regular Pokemon - it had never been sold, and gauntlet 5's CPU
    // teams use it.
    { SPECIES_LOPUNNY,         375, 4 },
    { SPECIES_ALTARIA,         375, 4 },
    { SPECIES_ABSOL,           375, 4 },
    { SPECIES_CLEFABLE,        375, 4 },
    { SPECIES_STARAPTOR,       375, 4 },
    { SPECIES_RAICHU,          375, 4 },
    { SPECIES_PIDGEOT,         250, 4 },
    { SPECIES_SHARPEDO,        250, 4 },
    { SPECIES_MALAMAR,         250, 4 },
    { SPECIES_DRAGALGE,        250, 4 },
    // Kangaskhan comes with the other Mega bases, but its stone is never
    // sold: the only Kangaskhanite is NORMAN's gift after gauntlet 5
    // (storyline.md), so the Broker and the trader can't offer one either.
    { SPECIES_KANGASKHAN,      250, 4 },
    // Unlocked clearing gauntlet 5 - gauntlet-06.md. Bases for the doubles
    // Mega Stones.
    { SPECIES_SCOVILLAIN,               375, 5 },
    { SPECIES_GOLURK,                   375, 5 },
    { SPECIES_TATSUGIRI,                375, 5 },
    { SPECIES_CRABOMINABLE,             250, 5 },
    { SPECIES_DRAMPA,                   250, 5 },
    { SPECIES_CHIMECHO,                 250, 5 },
    { SPECIES_MEOWSTIC,                 250, 5 },
};

static const struct FacilityShopMon *const sMonTiers[] =
{
    [FACILITY_SHOP_TIER_PREMIUM]  = sPremiumMons,
    [FACILITY_SHOP_TIER_STRONG]   = sStrongMons,
    [FACILITY_SHOP_TIER_STANDARD] = sStandardMons,
    [FACILITY_SHOP_TIER_BUDGET]   = sBudgetMons,
};

static const u16 sMonTierSizes[] =
{
    [FACILITY_SHOP_TIER_PREMIUM]  = ARRAY_COUNT(sPremiumMons),
    [FACILITY_SHOP_TIER_STRONG]   = ARRAY_COUNT(sStrongMons),
    [FACILITY_SHOP_TIER_STANDARD] = ARRAY_COUNT(sStandardMons),
    [FACILITY_SHOP_TIER_BUDGET]   = ARRAY_COUNT(sBudgetMons),
};

// GetSpeciesName() gives every form its base name ("Rotom" for all three
// Rotoms), so the shop names the forms it sells itself, Showdown-style. A
// default form keeps its plain name. Longest is Ursaluna-Bloodmoon (103 px),
// which is why the Pokemon lists' box is wider (field_specials.c).
static const struct
{
    u16 species;
    const u8 *name;
} sShopFormNames[] =
{
    { SPECIES_ARCANINE_HISUI,       COMPOUND_STRING("Arcanine-Hisui") },
    { SPECIES_ARTICUNO_GALAR,       COMPOUND_STRING("Articuno-Galar") },
    { SPECIES_DARMANITAN_GALAR,     COMPOUND_STRING("Darmanitan-Galar") },
    { SPECIES_DEOXYS_ATTACK,        COMPOUND_STRING("Deoxys-Attack") },
    { SPECIES_DEOXYS_DEFENSE,       COMPOUND_STRING("Deoxys-Defense") },
    { SPECIES_DEOXYS_SPEED,         COMPOUND_STRING("Deoxys-Speed") },
    { SPECIES_ENAMORUS_THERIAN,     COMPOUND_STRING("Enamorus-Therian") },
    { SPECIES_FLOETTE_ETERNAL,      COMPOUND_STRING("Floette-Eternal") },
    { SPECIES_GOODRA_HISUI,         COMPOUND_STRING("Goodra-Hisui") },
    { SPECIES_INDEEDEE_F,           COMPOUND_STRING("Indeedee-F") },
    { SPECIES_LANDORUS_THERIAN,     COMPOUND_STRING("Landorus-Therian") },
    { SPECIES_MAROWAK_ALOLA,        COMPOUND_STRING("Marowak-Alola") },
    { SPECIES_MOLTRES_GALAR,        COMPOUND_STRING("Moltres-Galar") },
    { SPECIES_MUK_ALOLA,            COMPOUND_STRING("Muk-Alola") },
    { SPECIES_NINETALES_ALOLA,      COMPOUND_STRING("Ninetales-Alola") },
    { SPECIES_RAICHU_ALOLA,         COMPOUND_STRING("Raichu-Alola") },
    { SPECIES_RAPIDASH_GALAR,       COMPOUND_STRING("Rapidash-Galar") },
    { SPECIES_ROTOM_HEAT,           COMPOUND_STRING("Rotom-Heat") },
    { SPECIES_ROTOM_MOW,            COMPOUND_STRING("Rotom-Mow") },
    { SPECIES_ROTOM_WASH,           COMPOUND_STRING("Rotom-Wash") },
    { SPECIES_SAMUROTT_HISUI,       COMPOUND_STRING("Samurott-Hisui") },
    { SPECIES_SHAYMIN_SKY,          COMPOUND_STRING("Shaymin-Sky") },
    { SPECIES_SLOWKING_GALAR,       COMPOUND_STRING("Slowking-Galar") },
    { SPECIES_THUNDURUS_THERIAN,    COMPOUND_STRING("Thundurus-Therian") },
    { SPECIES_TORNADUS_THERIAN,     COMPOUND_STRING("Tornadus-Therian") },
    { SPECIES_TYPHLOSION_HISUI,     COMPOUND_STRING("Typhlosion-Hisui") },
    { SPECIES_URSALUNA_BLOODMOON,   COMPOUND_STRING("Ursaluna-Bloodmoon") },
    // Both Urshifu are named: neither reads as "the normal one". Showdown's
    // full names don't fit the box.
    { SPECIES_URSHIFU_RAPID_STRIKE, COMPOUND_STRING("Urshifu-Rapid") },
    { SPECIES_URSHIFU_SINGLE_STRIKE, COMPOUND_STRING("Urshifu-Single") },
    { SPECIES_WEEZING_GALAR,        COMPOUND_STRING("Weezing-Galar") },
    { SPECIES_ZAPDOS_GALAR,         COMPOUND_STRING("Zapdos-Galar") },
    { SPECIES_ZOROARK_HISUI,        COMPOUND_STRING("Zoroark-Hisui") },
};

static const u8 *GetShopMonName(u16 species)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sShopFormNames); i++)
    {
        if (sShopFormNames[i].species == species)
            return sShopFormNames[i].name;
    }
    return GetSpeciesName(species);
}

// Above the default (index 0, primary) ability, a handful of these mons are
// on the list specifically *because* of a non-default ability - selling the
// default would quietly break the reason they're here. Named exceptions per
// shop-spec.md's own open question on this. Not a general ability audit of
// the whole roster; revisit per-species as future unlocks add mons whose
// default ability would be similarly wrong.
static const struct { u16 species; u8 abilityNum; } sAbilityOverrides[] =
{
    { SPECIES_AMOONGUSS, 2 }, // Regenerator, not Effect Spore
    { SPECIES_TOXAPEX,   2 }, // Regenerator, not Merciless
    { SPECIES_POLITOED,  2 }, // Drizzle, not Water Absorb - the point of selling it, see shop-unlock-b2.md
    { SPECIES_PELIPPER,  1 }, // Drizzle, not Keen Eye
    { SPECIES_TORKOAL,   1 }, // Drought, not White Smoke
    { SPECIES_SERPERIOR, 2 }, // Contrary, not Overgrow - Leaf Storm is the whole set
    { SPECIES_HYDRAPPLE, 1 }, // Regenerator, not Supersweet Syrup
    { SPECIES_SNEASLER,  1 }, // Unburden, not Pressure
    { SPECIES_ENTEI,     2 }, // Inner Focus - blocks Intimidate and flinch (B_UPDATED_INTIMIDATE)
    { SPECIES_RAIKOU,    2 }, // Inner Focus, as Entei
    { SPECIES_SUICUNE,   2 }, // Inner Focus, as Entei
    { SPECIES_ZAPDOS,    2 }, // Static, not Pressure
    { SPECIES_MOLTRES,   2 }, // Flame Body, not Pressure
    { SPECIES_INCINEROAR, 2 }, // Intimidate, not Blaze
    { SPECIES_TALONFLAME, 2 }, // Gale Wings, not Flame Body
    { SPECIES_TSAREENA,  1 }, // Queenly Majesty, not Leaf Guard
    { SPECIES_FARIGIRAF, 1 }, // Armor Tail, not Cud Chew
    { SPECIES_COALOSSAL, 1 }, // Flame Body, not Steam Engine
    { SPECIES_INDEEDEE_F, 2 }, // Psychic Surge - the reason to buy it
    { SPECIES_INDEEDEE_M, 2 }, // Psychic Surge, as Indeedee-F
    { SPECIES_GARCHOMP,  2 }, // Rough Skin, not Sand Veil
    { SPECIES_DRAGONITE, 2 }, // Multiscale, not Inner Focus
    { SPECIES_CLEFABLE,  1 }, // Magic Guard, not Cute Charm
    { SPECIES_DRAGALGE,  2 }, // Adaptability, not Poison Point
    { SPECIES_TATSUGIRI, 2 }, // Storm Drain, not Commander
    { SPECIES_MEOWSTIC,  2 }, // Prankster, not Keen Eye
    // The never-sold leftovers moved down from the gauntlet 7 draft
    // (gauntlet-07.md): the hidden ability is the reason to use these.
    { SPECIES_AUDINO,         1 }, // Regenerator, not Healer
    { SPECIES_FALINKS,        2 }, // Defiant, not Battle Armor
    { SPECIES_KILOWATTREL,    2 }, // Competitive, not Wind Power
    { SPECIES_SLOWKING_GALAR, 2 }, // Regenerator, not Curious Medicine
    { SPECIES_TYPHLOSION,     2 }, // Flash Fire, not Blaze
    { SPECIES_EMBOAR,         2 }, // Reckless, not Blaze
    { SPECIES_CHESNAUGHT,     2 }, // Bulletproof, not Overgrow
    { SPECIES_SKELEDIRGE,     2 }, // Unaware, not Blaze
    { SPECIES_QUAQUAVAL,      2 }, // Moxie, not Torrent
    { SPECIES_PRIMARINA,      2 }, // Liquid Voice, not Torrent
    { SPECIES_OVERQWIL,       2 }, // Intimidate, not Poison Point
    { SPECIES_SCOLIPEDE,      2 }, // Speed Boost, not Poison Point
    { SPECIES_CINDERACE,      2 }, // Libero, not Blaze
    { SPECIES_GRENINJA,       2 }, // Protean, not Torrent (never Battle Bond)
    { SPECIES_MEOWSCARADA,    2 }, // Protean, not Overgrow
    { SPECIES_BASCULEGION_M,  1 }, // Adaptability, not Swift Swim
    { SPECIES_SAMUROTT_HISUI, 2 }, // Sharpness, not Torrent
    // Gauntlet 7's wave (gauntlet-07.md).
    { SPECIES_LANDORUS_INCARNATE, 2 }, // Sheer Force, not Sand Force
    { SPECIES_ENAMORUS_INCARNATE, 2 }, // Contrary, not Cute Charm
    { SPECIES_ESPATHRA,       2 }, // Speed Boost - why it waited for gauntlet 7
    { SPECIES_HOUNDSTONE,     2 }, // Fluffy, not Sand Rush
};

static u8 GetShopMonAbilityNum(u16 species)
{
    u32 i;

    // Blaziken is sold from gauntlet 3 with Blaze. Speed Boost waits until
    // Blazikenite does (wave 6, gauntlet-07.md): a Blaziken bought once
    // gauntlet 6 is cleared gets it.
    if (species == SPECIES_BLAZIKEN)
        return GetGauntletsClearedCount() >= 6 ? 2 : 0;
    for (i = 0; i < ARRAY_COUNT(sAbilityOverrides); i++)
    {
        if (sAbilityOverrides[i].species == species)
            return sAbilityOverrides[i].abilityNum;
    }
    return 0;
}

// ----------------------------------------------------------------------------
// Dynamic menu staging. One keeper's list lives here at a time, heap-backed
// so it costs nothing while no shop menu is open - see the file header.
// ----------------------------------------------------------------------------

struct FacilityShopMenuRow
{
    u16 id;      // species or item constant, EXCEPT on the type-filter menu,
                 // where it's a Type constant (or FACILITY_SHOP_TYPE_ALL)
    u16 price;
    const u8 *name;
    const u8 *description; // may be NULL
};

#define FACILITY_SHOP_TYPE_ALL NUMBER_OF_MON_TYPES
#define FACILITY_SHOP_TYPE_FILTER_THRESHOLD 20

// Sentinel id for the "Sell a Pokemon" row on the gauntlet-select menu -
// keeps it out of the u8 wave range (0-9) the same way FACILITY_SHOP_TYPE_ALL
// keeps its sentinel out of the Type range.
#define FACILITY_SHOP_GAUNTLET_SELECT_SELL 0xFFFF
#define FACILITY_SHOP_GAUNTLET_SELECT_FREE 0xFFFE // Ten Gauntlets: "Free the Pokemon" (the siphon)

static EWRAM_DATA struct FacilityShopMenuRow *sMenuRows = NULL;
static EWRAM_DATA u16 sMenuRowCount = 0;
static EWRAM_DATA u8 sPendingMonTier = 0; // tier remembered between BuildMonTierList and SelectMonType
static EWRAM_DATA u8 sPendingGauntletWave = 0; // wave remembered between BuildBuildingMenu and BuildMonTierList

static void FreeMenuRows(void)
{
    if (sMenuRows != NULL)
    {
        Free(sMenuRows);
        sMenuRows = NULL;
    }
    sMenuRowCount = 0;
}

// See the comment on this in include/facility_shop.h - called from the
// keeper interaction's own "goodbye" script, not deferred to the next visit.
void FacilityShopFreeMenuRows(void)
{
    FreeMenuRows();
}

u16 FacilityShopGetMenuCount(void)
{
    return sMenuRowCount;
}

const u8 *FacilityShopGetMenuRowName(u16 index)
{
    if (index >= sMenuRowCount)
        return NULL;
    return sMenuRows[index].name;
}

u16 FacilityShopGetMenuRowPrice(u16 index)
{
    if (index >= sMenuRowCount)
        return 0;
    return sMenuRows[index].price;
}

const u8 *FacilityShopGetMenuRowDescription(u16 index)
{
    if (index >= sMenuRowCount)
        return NULL;
    return sMenuRows[index].description;
}

bool8 FacilityShopMenuHasDescriptions(void)
{
    u16 i;
    for (i = 0; i < sMenuRowCount; i++)
    {
        if (sMenuRows[i].description != NULL)
            return TRUE;
    }
    return FALSE;
}

void FacilityShopBuildConsumablesMenu(void)
{
    u16 i, count = 0;

    FreeMenuRows();
    for (i = 0; i < ARRAY_COUNT(sConsumables); i++)
    {
        if (IsShopEntryUnlocked(sConsumables[i].unlockGauntlet))
            count++;
    }

    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    for (i = 0, count = 0; i < ARRAY_COUNT(sConsumables); i++)
    {
        if (!IsShopEntryUnlocked(sConsumables[i].unlockGauntlet))
            continue;
        sMenuRows[count].id = sConsumables[i].item;
        sMenuRows[count].price = ShopPrice(sConsumables[i].price);
        sMenuRows[count].name = GetItemName(sConsumables[i].item);
        sMenuRows[count].description = sConsumables[i].description;
        count++;
    }
}

void FacilityShopBuildHeldItemsMenu(void)
{
    u16 i, count = 0;

    FreeMenuRows();
    for (i = 0; i < ARRAY_COUNT(sHeldItems); i++)
    {
        if (IsShopEntryUnlocked(sHeldItems[i].unlockGauntlet))
            count++;
    }

    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    for (i = 0, count = 0; i < ARRAY_COUNT(sHeldItems); i++)
    {
        if (!IsShopEntryUnlocked(sHeldItems[i].unlockGauntlet))
            continue;
        sMenuRows[count].id = sHeldItems[i].item;
        sMenuRows[count].price = ShopPrice(sHeldItems[i].price);
        sMenuRows[count].name = GetItemName(sHeldItems[i].item);
        sMenuRows[count].description = NULL;
        count++;
    }
}

// Keeper 3. gSpecialVar_Result = FALSE if no stone is unlocked yet (the
// keeper shows its "coming later" line instead of an empty list).
void FacilityShopBuildMegaStonesMenu(void)
{
    u16 i, count = 0;

    FreeMenuRows();
    for (i = 0; i < ARRAY_COUNT(sMegaStones); i++)
    {
        if (IsShopEntryUnlocked(sMegaStones[i].unlockGauntlet))
            count++;
    }

    gSpecialVar_Result = (count != 0);
    if (count == 0)
        return;

    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    for (i = 0, count = 0; i < ARRAY_COUNT(sMegaStones); i++)
    {
        if (!IsShopEntryUnlocked(sMegaStones[i].unlockGauntlet))
            continue;
        sMenuRows[count].id = sMegaStones[i].item;
        sMenuRows[count].price = ShopPrice(sMegaStones[i].price);
        sMenuRows[count].name = GetItemName(sMegaStones[i].item);
        sMenuRows[count].description = NULL;
        count++;
    }
}

// A mon is in the currently-browsed gauntlet submenu if its wave is the one
// the player picked on the gauntlet-select screen. IsShopEntryUnlocked is a
// belt-and-suspenders check - sPendingGauntletWave can't be set to a wave
// that isn't unlocked (FacilityShopBuildGauntletMenu only ever offers
// unlocked waves), but the check is one word and worth keeping honest.
static bool8 IsMonInPendingWave(const struct FacilityShopMon *mon)
{
    return mon->unlockGauntlet == sPendingGauntletWave && IsShopEntryUnlocked(mon->unlockGauntlet);
}

// Stages the final species list for the remembered tier/gauntlet wave,
// optionally restricted to one primary type. typeFilter ==
// FACILITY_SHOP_TYPE_ALL means no restriction.
static u16 StageMonTier(u8 tier, u8 typeFilter)
{
    const struct FacilityShopMon *pool = sMonTiers[tier];
    u16 size = sMonTierSizes[tier];
    u16 i, count = 0;

    FreeMenuRows();
    for (i = 0; i < size; i++)
    {
        if (!IsMonInPendingWave(&pool[i]))
            continue;
        if (typeFilter != FACILITY_SHOP_TYPE_ALL && GetSpeciesType(pool[i].species, 0) != typeFilter)
            continue;
        count++;
    }

    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    for (i = 0, count = 0; i < size; i++)
    {
        if (!IsMonInPendingWave(&pool[i]))
            continue;
        if (typeFilter != FACILITY_SHOP_TYPE_ALL && GetSpeciesType(pool[i].species, 0) != typeFilter)
            continue;
        sMenuRows[count].id = pool[i].species;
        sMenuRows[count].price = ShopPrice(pool[i].price);
        sMenuRows[count].name = GetShopMonName(pool[i].species);
        sMenuRows[count].description = NULL;
        count++;
    }
    return count;
}

static const u8 sText_TypeFilterAll[] = _("All");

// Stages the type-filter menu: one row per distinct primary type actually
// present among the tier's currently-browsed gauntlet wave, plus "All" up
// front.
static void StageMonTypeMenu(u8 tier)
{
    const struct FacilityShopMon *pool = sMonTiers[tier];
    u16 size = sMonTierSizes[tier];
    bool8 typePresent[NUMBER_OF_MON_TYPES] = {0};
    u16 i, count = 1; // slot 0 reserved for "All"

    for (i = 0; i < size; i++)
    {
        if (!IsMonInPendingWave(&pool[i]))
            continue;
        typePresent[GetSpeciesType(pool[i].species, 0)] = TRUE;
    }
    for (i = 0; i < NUMBER_OF_MON_TYPES; i++)
    {
        if (typePresent[i])
            count++;
    }

    FreeMenuRows();
    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    sMenuRows[0].id = FACILITY_SHOP_TYPE_ALL;
    sMenuRows[0].price = 0;
    sMenuRows[0].name = sText_TypeFilterAll;
    sMenuRows[0].description = NULL;
    for (i = 0, count = 1; i < NUMBER_OF_MON_TYPES; i++)
    {
        if (!typePresent[i])
            continue;
        sMenuRows[count].id = i;
        sMenuRows[count].price = 0;
        sMenuRows[count].name = gTypesInfo[i].name;
        sMenuRows[count].description = NULL;
        count++;
    }
}

// gSpecialVar_0x8009 = FACILITY_SHOP_TIER_* in. sPendingGauntletWave must
// already be set (FacilityShopSelectGauntletRow does this before the caller
// ever reaches the tier-select screen).
// gSpecialVar_Result = TRUE if this tier/wave combination has more mons than
// fit in one screenful of browsing and a type-filter menu was staged instead
// of the species list directly - the caller shows that menu and then calls
// FacilityShopSelectMonType with the chosen row before showing the (now
// staged) species list. FALSE means the species list is already staged and
// ready to show. Splitting the master tables by gauntlet wave first means
// this threshold rarely trips anymore - it's kept for the rare wave whose
// single tier is still a big pool on its own.
void FacilityShopBuildMonTierList(void)
{
    u8 tier = gSpecialVar_0x8009;
    u16 unlockedCount = 0;
    const struct FacilityShopMon *pool = sMonTiers[tier];
    u16 size = sMonTierSizes[tier];
    u16 i;

    sPendingMonTier = tier;
    for (i = 0; i < size; i++)
    {
        if (IsMonInPendingWave(&pool[i]))
            unlockedCount++;
    }

    if (unlockedCount > FACILITY_SHOP_TYPE_FILTER_THRESHOLD)
    {
        StageMonTypeMenu(tier);
        gSpecialVar_Result = TRUE;
    }
    else
    {
        StageMonTier(tier, FACILITY_SHOP_TYPE_ALL);
        gSpecialVar_Result = FALSE;
    }
}

// gSpecialVar_0x8004 = chosen row index into the just-shown type-filter menu.
// Re-stages the species list for the remembered tier, filtered to that type.
void FacilityShopSelectMonType(void)
{
    u16 index = gSpecialVar_0x8004;
    u8 typeFilter = sMenuRows[index].id;
    StageMonTier(sPendingMonTier, typeFilter);
}

// gSpecialVar_0x8004 = chosen row index into whichever list is currently
// staged (consumables, held items, or a Pokemon tier/type list).
// Out: gSpecialVar_0x8009 = species or item id, VAR_0x8008 = price,
// STR_VAR_1 = name (for the confirm message).
void FacilityShopSelectRow(void)
{
    u16 index = gSpecialVar_0x8004;
    gSpecialVar_0x8009 = sMenuRows[index].id;
    gSpecialVar_0x8008 = sMenuRows[index].price;
    StringCopy(gStringVar1, sMenuRows[index].name);
}

// ----------------------------------------------------------------------------
// Gauntlet-select menu - the screen above tier-select. One row per gauntlet
// whose shop wave (unlockGauntlet value) is unlocked and actually has a mon
// in some tier, plus "Sell a Pokemon". Adding a gauntlet's worth of new mons
// is exactly one more line in sGauntletWaveNames (and the unlockGauntlet
// values already on those rows do the rest) - no other change needed here.
// ----------------------------------------------------------------------------

// One name per shop wave. Wave N is the stock that unlocks on clearing
// gauntlet N, i.e. what the player buys *for* gauntlet N+1 - so wave 0 is
// "Gauntlet 1", and wave 8 is the endgame stock. All are listed up front: a
// wave with no name here never appears in the menu at all
// (FacilityShopBuildGauntletMenu only walks this table), which silently hid
// gauntlets 5 and 6's Pokemon while it stopped at 4.
static const u8 *const sGauntletWaveNames[] =
{
    COMPOUND_STRING("Gauntlet 1 Pokemon"),
    COMPOUND_STRING("Gauntlet 2 Pokemon"),
    COMPOUND_STRING("Gauntlet 3 Pokemon"),
    COMPOUND_STRING("Gauntlet 4 Pokemon"),
    COMPOUND_STRING("Gauntlet 5 Pokemon"),
    COMPOUND_STRING("Gauntlet 6 Pokemon"),
    COMPOUND_STRING("Gauntlet 7 Pokemon"),
    COMPOUND_STRING("Gauntlet 8 Pokemon"),
    COMPOUND_STRING("Endgame Pokemon"),
};

static const u8 sText_SellAPokemon[] = _("Sell a Pokemon");
static const u8 sText_FreeThePokemon[] = _("Free the Pokemon");

// Ten Gauntlets: the Frontier siphon (storyline.md) is offered once, after
// Rustboro (VAR_ENDGAME_STATE 10), while the player holds the uncharged Crown.
static bool8 ShouldOfferSiphon(void)
{
    return VarGet(VAR_ENDGAME_STATE) == 10 && CheckBagHasItem(ITEM_REPLICA_CROWN, 1);
}

// Guards against a wave number that's unlocked (in the IsShopEntryUnlocked
// sense) but was never actually given any Pokemon of its own - e.g. a future
// gauntlet whose shop-unlock wave is items-only at Keeper 4's counter.
// Showing a gauntlet option that opens onto an empty tier list would be a
// dead end, so it just doesn't appear.
static bool8 GauntletWaveHasAnyMon(u8 wave)
{
    u32 tier, i;

    for (tier = 0; tier < ARRAY_COUNT(sMonTiers); tier++)
    {
        for (i = 0; i < sMonTierSizes[tier]; i++)
        {
            if (sMonTiers[tier][i].unlockGauntlet == wave)
                return TRUE;
        }
    }
    return FALSE;
}

// The Pokemon keeper's first screen. Stages one row per unlocked gauntlet
// wave plus "Sell a Pokemon" - see FacilityShopSelectGauntletRow for what the
// caller does with the chosen row.
void FacilityShopBuildGauntletMenu(void)
{
    u16 i, count = 0;

    for (i = 0; i < ARRAY_COUNT(sGauntletWaveNames); i++)
    {
        if (IsShopEntryUnlocked(i) && GauntletWaveHasAnyMon(i))
            count++;
    }
    count++; // Sell a Pokemon
    if (ShouldOfferSiphon())
        count++; // Free the Pokemon

    FreeMenuRows();
    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;

    for (i = 0, count = 0; i < ARRAY_COUNT(sGauntletWaveNames); i++)
    {
        if (!IsShopEntryUnlocked(i) || !GauntletWaveHasAnyMon(i))
            continue;
        sMenuRows[count].id = i;
        sMenuRows[count].price = 0;
        sMenuRows[count].name = sGauntletWaveNames[i];
        sMenuRows[count].description = NULL;
        count++;
    }
    sMenuRows[count].id = FACILITY_SHOP_GAUNTLET_SELECT_SELL;
    sMenuRows[count].price = 0;
    sMenuRows[count].name = sText_SellAPokemon;
    sMenuRows[count].description = NULL;
    if (ShouldOfferSiphon())
    {
        count++;
        sMenuRows[count].id = FACILITY_SHOP_GAUNTLET_SELECT_FREE;
        sMenuRows[count].price = 0;
        sMenuRows[count].name = sText_FreeThePokemon;
        sMenuRows[count].description = NULL;
    }
}

// gSpecialVar_0x8004 = chosen row index into the just-shown gauntlet menu.
// gSpecialVar_Result = TRUE means the player picked "Sell a Pokemon" - the
// caller goes straight to the sell flow; 2 means "Free the Pokemon" (the
// siphon, only offered at VAR_ENDGAME_STATE 10). FALSE means sPendingGauntletWave is
// now set and the caller should show tier-select next.
void FacilityShopSelectGauntletRow(void)
{
    u16 index = gSpecialVar_0x8004;
    u16 id = sMenuRows[index].id;

    if (id == FACILITY_SHOP_GAUNTLET_SELECT_SELL)
    {
        gSpecialVar_Result = TRUE;
    }
    else if (id == FACILITY_SHOP_GAUNTLET_SELECT_FREE)
    {
        gSpecialVar_Result = 2;
    }
    else
    {
        sPendingGauntletWave = id;
        gSpecialVar_Result = FALSE;
    }
}

void FacilityShopGetFP(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->facility.progress.fp;
}

void FacilityShopTakeFP(void)
{
    if (gSaveBlock3Ptr->facility.progress.fp < gSpecialVar_0x8004)
        gSaveBlock3Ptr->facility.progress.fp = 0;
    else
        gSaveBlock3Ptr->facility.progress.fp -= gSpecialVar_0x8004;
}

void FacilityShopGiveFP(void)
{
    u32 fp = gSaveBlock3Ptr->facility.progress.fp + gSpecialVar_0x8004;
    gSaveBlock3Ptr->facility.progress.fp = (fp > 0xFFFF) ? 0xFFFF : fp;
}

// Level 50, neutral nature, 31 IVs, zero EVs, current level-up moveset,
// primary ability (named exceptions above) - the shop-spec.md defaults for
// a purchased Pokemon (its "Open questions for implementation" section,
// answered).
//
// No held item on the mon - the player buys their own from the shop.
// Shared by the Pokemon keeper and the Broker, so a Pokemon is built
// the same way whichever counter it came from.
static void CreateShopMon(struct Pokemon *mon, u16 species)
{
    struct PokemonTemplate template = {0};

    template.species = species;
    template.level = 50;
    template.gender = MON_GENDER_RANDOM;
    template.nature = NATURE_HARDY;
    template.origin = GIFTMON_ORIGIN;
    template.doNotUseDefaultAbility = TRUE;
    template.abilityNum = GetShopMonAbilityNum(template.species);
    template.ivs[STAT_HP] = 31;
    template.ivs[STAT_ATK] = 31;
    template.ivs[STAT_DEF] = 31;
    template.ivs[STAT_SPEED] = 31;
    template.ivs[STAT_SPATK] = 31;
    template.ivs[STAT_SPDEF] = 31;
    template.moves[0] = MOVE_DEFAULT;
    template.moves[1] = MOVE_DEFAULT;
    template.moves[2] = MOVE_DEFAULT;
    template.moves[3] = MOVE_DEFAULT;

    CreateMonFromTemplate(mon, &template);
}

void FacilityShopBuyMon(void)
{
    struct Pokemon mon;

    CreateShopMon(&mon, gSpecialVar_0x8009);
    gSpecialVar_Result = GiveCapturedMonToPlayer(&mon);
}

// Sell-back price lookup scans every tier regardless of unlock status -
// gauntletsCompleted bits only ever get set, never cleared, so a mon the
// player already owns was necessarily bought (or granted) while its row was
// unlocked; there's no path where a currently-owned mon's row could have
// since re-locked.
static bool8 FindMonTierPrice(u16 species, u16 *price)
{
    u32 tier, i;

    for (tier = 0; tier < ARRAY_COUNT(sMonTiers); tier++)
    {
        for (i = 0; i < sMonTierSizes[tier]; i++)
        {
            if (sMonTiers[tier][i].species == species)
            {
                *price = sMonTiers[tier][i].price;
                return TRUE;
            }
        }
    }
    return FALSE;
}

// Total owned = party + every box, not just the box the player happens to be
// looking at - a mon parked in storage still counts toward "don't sell down
// to nothing." Selling itself only ever touches the party (a boxed mon isn't
// offered here at all - see ChoosePartyMon in the sell script), so this is
// purely a "would this leave the player with too few Pokemon anywhere" check.
static u32 CountAllOwnedMons(void)
{
    u32 total = 0;
    u32 box, pos, i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct BoxPokemon *boxMon = &gParties[B_TRAINER_PLAYER][i].box;
        if (GetBoxMonData(boxMon, MON_DATA_SPECIES) != SPECIES_NONE)
            total++;
    }
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            struct BoxPokemon *boxMon = GetBoxedMonPtr(box, pos);
            if (GetBoxMonData(boxMon, MON_DATA_SPECIES) != SPECIES_NONE)
                total++;
        }
    }
    return total;
}

void FacilityShopSellMonPrompt(void)
{
    u16 slot = gSpecialVar_0x8004;
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][slot];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u16 price;

    if (!FindMonTierPrice(species, &price))
    {
        gSpecialVar_Result = SELL_MON_NOT_SELLABLE;
        return;
    }

    // Selling a mon deletes it outright (ZeroMonData in FacilityShopSellMon
    // below) - a held item would be lost right along with it, for real, with
    // no confirmation that mentions the item at all. Refusing outright is
    // safer than a "the item will be lost too" warning the player could
    // click through by habit.
    if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
    {
        gSpecialVar_Result = SELL_MON_HOLDING_ITEM;
        return;
    }

    // <= 6 (not < 6) so the player always has enough left for a full team of
    // six after the sale, even if every last one of them is in the party
    // right now - the whole point of this check is never being able to
    // soft-lock the run for lack of a fielded team.
    if (CountAllOwnedMons() <= 6)
    {
        gSpecialVar_Result = SELL_MON_NOT_ENOUGH_OWNED;
        return;
    }

    StringCopy(gStringVar1, GetShopMonName(species));
    gSpecialVar_0x8008 = price / 2;
    gSpecialVar_Result = SELL_MON_OK;
}

void FacilityShopSellMon(void)
{
    u16 slot = gSpecialVar_0x8004;

    ZeroMonData(&gParties[B_TRAINER_PLAYER][slot]);
    CompactPartySlots();
    CalculatePlayerPartyCount();

    gSpecialVar_0x8004 = gSpecialVar_0x8008;
    FacilityShopGiveFP();
}

// Small persistent FP balance popup for the shop, shown for the duration of
// a keeper interaction - same idea, same corner and size, as vanilla's own
// ShowBattlePointsWindow/UpdateBattlePointsWindow/CloseBattlePointsWindow
// in src/field_specials.c, just for FP instead of Battle Points.
static const u8 sText_FP[] = _("FP");
static EWRAM_DATA u8 sFacilityFPWindowId = 0;

void UpdateFacilityFPWindow(void)
{
    u8 string[32];
    u32 x;

    StringCopy(ConvertIntToDecimalStringN(string, gSaveBlock3Ptr->facility.progress.fp, STR_CONV_MODE_RIGHT_ALIGN, 4), sText_FP);
    x = GetStringRightAlignXOffset(FONT_NORMAL, string, 48);
    AddTextPrinterParameterized(sFacilityFPWindowId, FONT_NORMAL, string, x, 1, 0, NULL);
}

void ShowFacilityFPWindow(void)
{
    static const struct WindowTemplate sFacilityFP_WindowTemplate =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 6,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 8,
    };

    sFacilityFPWindowId = AddWindow(&sFacilityFP_WindowTemplate);
    SetStandardWindowBorderStyle(sFacilityFPWindowId, FALSE);
    UpdateFacilityFPWindow();
    CopyWindowToVram(sFacilityFPWindowId, COPYWIN_GFX);
}

void CloseFacilityFPWindow(void)
{
    ClearStdWindowAndFrameToTransparent(sFacilityFPWindowId, TRUE);
    RemoveWindow(sFacilityFPWindowId);
}

// Item/mon description sidebar, Consumables keeper only (the only keeper
// with per-row descriptions - FacilityShopMenuHasDescriptions() is what
// field_specials.c checks before calling any of these three, so the other
// keepers never touch this window). Same geometry as the vanilla Move Tutor
// description box (ShowBattleFrontierTutorWindow in src/field_specials.c),
// placed left of the item list the same way.
static EWRAM_DATA u8 sFacilityShopDescWindowId = 0;

void ShowFacilityShopDescriptionWindow(void)
{
    static const struct WindowTemplate sFacilityShopDesc_WindowTemplate =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 7,
        .width = 12,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 20,
    };

    sFacilityShopDescWindowId = AddWindow(&sFacilityShopDesc_WindowTemplate);
    SetStandardWindowBorderStyle(sFacilityShopDescWindowId, FALSE);
}

void UpdateFacilityShopDescriptionWindow(void)
{
    u16 index = gSpecialVar_0x8004;
    const u8 *description = FacilityShopGetMenuRowDescription(index);

    FillWindowPixelRect(sFacilityShopDescWindowId, PIXEL_FILL(1), 0, 0, 96, 48);
    if (description != NULL)
        AddTextPrinterParameterized(sFacilityShopDescWindowId, FONT_NORMAL, description, 0, 1, 0, NULL);
    CopyWindowToVram(sFacilityShopDescWindowId, COPYWIN_GFX);
}

void CloseFacilityShopDescriptionWindow(void)
{
    ClearStdWindowAndFrameToTransparent(sFacilityShopDescWindowId, TRUE);
    RemoveWindow(sFacilityShopDescWindowId);
}

// ============================================================================
// The Broker - Lounge 3. See broker-spec.md.
//
// Stock is the NEXT gauntlet's shop wave: the player has cleared N
// gauntlets, the shop shows waves 0..N, and the Broker sells from wave N+1.
// Three items and three Pokemon are picked from it with a small generator
// seeded from N and the player's trainer ID, so the picks never change on a
// reload - only when the next wave becomes his stock.
//
// Pokemon he sells are the player's to keep, tagged Original Trainer
// "BROKER" with the in-game-trade met location (so they count as chipped -
// see IsFrontierChippedMon() in src/facility.c).
// ============================================================================

#define BROKER_STOCK_PER_SHELF 3
#define BROKER_MAX_CANDIDATES  256

static const u8 sText_BrokerOTName[] = _("BROKER");


static u8 BrokerNextWave(void)
{
    return GetGauntletsClearedCount() + 1;
}

void FacilityBrokerCheck(void)
{
    u8 cleared = GetGauntletsClearedCount();

    if (IsFacilityRunActive())
        gSpecialVar_Result = BROKER_RUN_ACTIVE;
    else if (cleared >= 8) // all eight gauntlets cleared
        gSpecialVar_Result = BROKER_NOTHING_LEFT;
    else if (gSaveBlock3Ptr->facility.progress.brokerDealsUsed & (1 << cleared))
        gSpecialVar_Result = BROKER_DEAL_USED;
    else
        gSpecialVar_Result = BROKER_OK;
}

void FacilityBrokerMarkDealUsed(void)
{
    gSaveBlock3Ptr->facility.progress.brokerDealsUsed |= (1 << GetGauntletsClearedCount());
}

static u32 BrokerRandom(u32 *state)
{
    *state = *state * 1103515245 + 12345;
    return (*state >> 16) & 0x7FFF;
}

// Picks up to BROKER_STOCK_PER_SHELF distinct entries out of `count`
// candidates, deterministically for this gauntlet and this player.
static u8 BrokerPick(u16 count, u8 shelf, u16 *picked)
{
    u32 state = (u32)BrokerNextWave() * 7919 + shelf * 104729 + READ_OTID_FROM_SAVE;
    u8 n = 0;

    while (n < BROKER_STOCK_PER_SHELF && n < count)
    {
        u16 idx = BrokerRandom(&state) % count;
        u8 j;
        bool8 dup = FALSE;

        for (j = 0; j < n; j++)
        {
            if (picked[j] == idx)
                dup = TRUE;
        }
        if (!dup)
            picked[n++] = idx;
    }
    return n;
}

// The Broker's markup (broker-spec.md): 1.2x the shop price, rounded to the
// nearest 10 FP - for items and Pokemon alike.
static u16 BrokerPrice(u16 shopPrice)
{
    return ((shopPrice * 6 / 5) + 5) / 10 * 10;
}

void FacilityBrokerBuildItemMenu(void)
{
    static const struct FacilityShopItem *const sShelves[] = { sConsumables, sHeldItems, sMegaStones };
    static const u16 sShelfSizes[] = { ARRAY_COUNT(sConsumables), ARRAY_COUNT(sHeldItems), ARRAY_COUNT(sMegaStones) };
    const struct FacilityShopItem *candidates[BROKER_MAX_CANDIDATES];
    u16 picked[BROKER_STOCK_PER_SHELF];
    u8 wave = BrokerNextWave();
    bool8 hasMegaRing = CheckBagHasItem(ITEM_MEGA_RING, 1);
    u16 count = 0;
    u32 shelf, i;
    u8 n;

    for (shelf = 0; shelf < ARRAY_COUNT(sShelves); shelf++)
    {
        // No Mega Stones until the player can actually use one.
        if (sShelves[shelf] == sMegaStones && !hasMegaRing)
            continue;
        for (i = 0; i < sShelfSizes[shelf] && count < BROKER_MAX_CANDIDATES; i++)
        {
            if (sShelves[shelf][i].unlockGauntlet == wave)
                candidates[count++] = &sShelves[shelf][i];
        }
    }

    FreeMenuRows();
    n = BrokerPick(count, 0, picked);
    gSpecialVar_Result = n;
    if (n == 0)
        return;
    sMenuRows = Alloc(n * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = n;
    for (i = 0; i < n; i++)
    {
        sMenuRows[i].id = candidates[picked[i]]->item;
        sMenuRows[i].price = BrokerPrice(candidates[picked[i]]->price);
        sMenuRows[i].name = GetItemName(candidates[picked[i]]->item);
        sMenuRows[i].description = NULL;
    }
}

void FacilityBrokerBuildMonMenu(void)
{
    const struct FacilityShopMon *candidates[BROKER_MAX_CANDIDATES];
    u16 picked[BROKER_STOCK_PER_SHELF];
    u8 wave = BrokerNextWave();
    u16 count = 0;
    u32 tier, i;
    u8 n;

    for (tier = 0; tier < ARRAY_COUNT(sMonTiers); tier++)
    {
        for (i = 0; i < sMonTierSizes[tier] && count < BROKER_MAX_CANDIDATES; i++)
        {
            // No Metagross on gauntlet 4 - STEVEN gives the player one right
            // after it, and they mustn't see it coming. The normal shop
            // still sells it from gauntlet 5 on.
            if (wave == FACILITY_GAUNTLET_4 + 1 && sMonTiers[tier][i].species == SPECIES_METAGROSS)
                continue;
            if (sMonTiers[tier][i].unlockGauntlet == wave)
                candidates[count++] = &sMonTiers[tier][i];
        }
    }

    FreeMenuRows();
    n = BrokerPick(count, 1, picked);
    gSpecialVar_Result = n;
    if (n == 0)
        return;
    sMenuRows = Alloc(n * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = n;
    for (i = 0; i < n; i++)
    {
        sMenuRows[i].id = candidates[picked[i]]->species;
        sMenuRows[i].price = BrokerPrice(candidates[picked[i]]->price);
        sMenuRows[i].name = GetShopMonName(candidates[picked[i]]->species);
        sMenuRows[i].description = NULL;
    }
}

void FacilityBrokerSellMon(void)
{
    struct Pokemon mon;
    u8 metLocation = METLOC_IN_GAME_TRADE;
    u8 otGender = MALE;
    u32 i;

    CreateShopMon(&mon, gSpecialVar_0x8009);
    SetMonData(&mon, MON_DATA_OT_NAME, sText_BrokerOTName);
    SetMonData(&mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(&mon, MON_DATA_MET_LOCATION, &metLocation);

    // Not GiveCapturedMonToPlayer(): it stamps the player's name over the
    // OT, erasing the "BROKER" tag. Same party-then-PC placement, minus the
    // re-stamp.
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_NONE)
            break;
    }
    if (i < PARTY_SIZE)
    {
        CopyMon(&gParties[B_TRAINER_PLAYER][i], &mon, sizeof(mon));
        gPartiesCount[B_TRAINER_PLAYER] = i + 1;
        gSpecialVar_Result = MON_GIVEN_TO_PARTY;
    }
    else
    {
        gSpecialVar_Result = CopyMonToPC(&mon);
    }
    if (gSpecialVar_Result != MON_CANT_GIVE)
        FacilityBrokerMarkDealUsed();
}

// STEVEN's METAGROSS (after gauntlet 4) was borrowed from the Broker, so it
// carries his tag too. Called right after givemon: retags the last Pokemon in
// the party. There's always room - STEVEN takes the Lati first.
void FacilityTagLastPartyMonBroker(void)
{
    u8 metLocation = METLOC_IN_GAME_TRADE;
    u8 otGender = MALE;
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][CalculatePlayerPartyCount() - 1];

    SetMonData(mon, MON_DATA_OT_NAME, sText_BrokerOTName);
    SetMonData(mon, MON_DATA_OT_GENDER, &otGender);
    SetMonData(mon, MON_DATA_MET_LOCATION, &metLocation);
}

// ============================================================================
// The Lounge 6 trader, the Broker's cousin (frontier-dialogue.md). Once per
// gauntlet, for 200 FP, she trades one of the player's party Pokemon for a
// random Pokemon from the next gauntlet's shop wave - the same stock the Broker draws from - and the
// player doesn't know which until it's done. The traded-away Pokemon's held
// item goes back to the bag. The new one is built like any shop Pokemon.
// ============================================================================
static u16 CollectTraderCandidates(const struct FacilityShopMon **candidates)
{
    u8 wave = BrokerNextWave();
    u16 count = 0;
    u32 tier, i;

    for (tier = 0; tier < ARRAY_COUNT(sMonTiers); tier++)
    {
        for (i = 0; i < sMonTierSizes[tier] && count < BROKER_MAX_CANDIDATES; i++)
        {
            // No Metagross while the player is on gauntlet 4: STEVEN gives
            // them one (with its Mega Stone) right after it.
            if (wave == FACILITY_GAUNTLET_4 + 1 && sMonTiers[tier][i].species == SPECIES_METAGROSS)
                continue;
            if (sMonTiers[tier][i].unlockGauntlet == wave)
                candidates[count++] = &sMonTiers[tier][i];
        }
    }
    return count;
}

// specialvar: TRUE if the next gauntlet's wave has any Pokemon to trade for.
u16 FacilityTraderHasStock(void)
{
    const struct FacilityShopMon *candidates[BROKER_MAX_CANDIDATES];
    return CollectTraderCandidates(candidates) != 0;
}

// gSpecialVar_0x8004 = party slot. Replaces that Pokemon in place (party size
// unchanged). gStringVar1 = the traded-away Pokemon's nickname, gStringVar2 =
// the new species' name. gSpecialVar_Result = the new species, or
// SPECIES_NONE if there was nothing to trade for.
void FacilityTraderTrade(void)
{
    const struct FacilityShopMon *candidates[BROKER_MAX_CANDIDATES];
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    u16 count = CollectTraderCandidates(candidates);
    u16 species, item;

    gSpecialVar_Result = SPECIES_NONE;
    if (count == 0)
        return;
    species = candidates[Random() % count]->species;
    item = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (item != ITEM_NONE)
        AddBagItem(item, 1);
    GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
    StringGet_Nickname(gStringVar1);
    StringCopy(gStringVar2, GetShopMonName(species));
    CreateShopMon(mon, species);
    gSpecialVar_Result = species;
}
