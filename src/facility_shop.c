// ============================================================================
// Ten Buildings shop - see shop-spec.md and shop-unlock-b2.md.
//
// Keepers 1 (consumables) and 2 (held items) are plain `additem` purchases,
// scripted the same way vanilla's own BP vendors are (see
// data/maps/BattleFrontier_ExchangeServiceCorner/scripts.inc) but spending
// FP instead of Battle Points. Keeper 4 (Pokemon) needs this file because it
// has to create a mon, not just hand over an item.
//
// Every sellable row - item or mon - carries an `unlockBuilding` field: 0
// means available from game start, N means it doesn't show up until
// gSaveBlock3Ptr->facility.progress.buildingsCompleted has bit (N - 1) set
// (IsShopEntryUnlocked() below). That bit is flipped by FacilityCompleteBuilding()
// in src/facility.c the moment a building's boss falls - before the player
// can act again - so there's no separate "unlock trigger" to wire up here;
// the shop just reads the same bitmask the run loop already maintains, live,
// every time a keeper's menu opens. Nine more unlocks after this one are
// just nine more rows with an unlockBuilding value, not nine more
// conditionals.
//
// Keeper 4 (Pokemon) additionally organizes its master tables by that same
// `unlockBuilding` value, calling it a "wave": the player picks a building's
// wave first (FacilityShopBuildBuildingMenu), then a tier within it, so
// browsing one building's additions doesn't mean scrolling through every
// other building's too. That's one generic building-select screen shared by
// every building, not a new screen per building - a building's worth of new
// mons is still just new rows with that building's unlockBuilding value.
//
// The list itself is generated at runtime instead of living as a
// SCROLL_MULTI_TEN_BUILDINGS_MON_STANDARD_1..6-style static COMPOUND_STRING
// table (see include/constants/field_specials.h's SCROLL_MULTI_TEN_BUILDINGS_
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
#include "constants/items.h"
#include "constants/species.h"

struct FacilityShopMon
{
    u16 species;
    u16 price;
    u8 unlockBuilding; // 0 = available from game start
};

struct FacilityShopItem
{
    u16 item;
    u16 price;
    u8 unlockBuilding; // 0 = available from game start
    const u8 *description; // NULL if this row doesn't show one (Keeper 2's stock)
};

static bool8 IsShopEntryUnlocked(u8 unlockBuilding)
{
    if (unlockBuilding == 0)
        return TRUE;
    return (gSaveBlock3Ptr->facility.progress.buildingsCompleted & (1 << (unlockBuilding - 1))) != 0;
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
    // Unlocked clearing building 1 - shop-unlock-b2.md. Resist berries are
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
    // Unlocked clearing building 1. Moved here from building 3 on purpose -
    // building 2 is where Spore shows up in force, and the building that
    // teaches a threat should sell its answer. See shop-unlock-b2.md.
    { ITEM_SAFETY_GOGGLES, 250, 1, NULL },
    // Unlocked clearing building 2 - shop-unlock-b3.md. The weather rocks and
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
    // Unlocked clearing building 3 - shop-unlock-b4.md. Focus Sash is the
    // signature purchase and the one to watch in playtesting - held items are
    // reusable here, so it's a permanent guaranteed-survive every battle,
    // stronger than in official play where it's consumed once and gone.
    { ITEM_FOCUS_SASH,       400, 3, NULL },
    { ITEM_ASSAULT_VEST,     350, 3, NULL },
    { ITEM_LIFE_ORB,         350, 3, NULL },
    { ITEM_HEAVY_DUTY_BOOTS, 300, 3, NULL },
};

// ----------------------------------------------------------------------------
// Keeper 4 - Pokemon. One master array per price tier, spanning every
// building's additions to that tier - not one array per building. Building
// 1's pool is unlockBuilding 0; shop-unlock-b2.md's additions are
// unlockBuilding 1. Azumarill, Medicham and Linoone were never on a real ban
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
    // Unlocked clearing building 2 - shop-unlock-b3.md.
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
    // Unlocked clearing building 3 - shop-unlock-b4.md.
    { SPECIES_ARCANINE,       500, 3 },
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
    // was pulled forward from the building 3 wave; it's still an Eviolite
    // target once Eviolite unlocks there.
    { SPECIES_MUK_ALOLA,     200, 1 },
    { SPECIES_CLAWITZER,     200, 1 },
    { SPECIES_BARBARACLE,    200, 1 },
    { SPECIES_SCYTHER,       200, 1 },
    // Unlocked clearing building 2 - shop-unlock-b3.md.
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
    // Eviolite targets, same tier/price as the rest of this wave -
    // shop-unlock-b3.md.
    { SPECIES_RHYDON,        300, 2 },
    { SPECIES_GLIGAR,        300, 2 },
    { SPECIES_MAGNETON,      300, 2 },
    { SPECIES_TYPE_NULL,     300, 2 },
    { SPECIES_DOUBLADE,      300, 2 },
    { SPECIES_SNEASEL,       300, 2 },
    // Unlocked clearing building 3 - shop-unlock-b4.md.
    { SPECIES_ARCHEOPS,      375, 3 },
    { SPECIES_FLORGES,       375, 3 },
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
    // was pulled forward from the building 3 wave.
    { SPECIES_GOLDUCK,    150, 1 },
    { SPECIES_RAPIDASH,   150, 1 },
    { SPECIES_RAPIDASH_GALAR, 150, 1 },
    { SPECIES_PINSIR,     150, 1 },
    { SPECIES_WAILORD,    150, 1 },
    { SPECIES_DRAPION,    150, 1 },
    { SPECIES_LEAVANNY,   150, 1 },
    { SPECIES_CARBINK,    150, 1 },
    { SPECIES_STOUTLAND,  150, 1 },
    // Unlocked clearing building 2 - shop-unlock-b3.md.
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
    // Unlocked clearing building 3 - shop-unlock-b4.md.
    { SPECIES_SILVALLY,   250, 3 },
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
};

static u8 GetShopMonAbilityNum(u16 species)
{
    u32 i;
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

// Sentinel id for the "Sell a Pokemon" row on the building-select menu -
// keeps it out of the u8 wave range (0-9) the same way FACILITY_SHOP_TYPE_ALL
// keeps its sentinel out of the Type range.
#define FACILITY_SHOP_BUILDING_SELECT_SELL 0xFFFF

static EWRAM_DATA struct FacilityShopMenuRow *sMenuRows = NULL;
static EWRAM_DATA u16 sMenuRowCount = 0;
static EWRAM_DATA u8 sPendingMonTier = 0; // tier remembered between BuildMonTierList and SelectMonType
static EWRAM_DATA u8 sPendingBuildingWave = 0; // wave remembered between BuildBuildingMenu and BuildMonTierList

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
        if (IsShopEntryUnlocked(sConsumables[i].unlockBuilding))
            count++;
    }

    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    for (i = 0, count = 0; i < ARRAY_COUNT(sConsumables); i++)
    {
        if (!IsShopEntryUnlocked(sConsumables[i].unlockBuilding))
            continue;
        sMenuRows[count].id = sConsumables[i].item;
        sMenuRows[count].price = sConsumables[i].price;
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
        if (IsShopEntryUnlocked(sHeldItems[i].unlockBuilding))
            count++;
    }

    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;
    for (i = 0, count = 0; i < ARRAY_COUNT(sHeldItems); i++)
    {
        if (!IsShopEntryUnlocked(sHeldItems[i].unlockBuilding))
            continue;
        sMenuRows[count].id = sHeldItems[i].item;
        sMenuRows[count].price = sHeldItems[i].price;
        sMenuRows[count].name = GetItemName(sHeldItems[i].item);
        sMenuRows[count].description = NULL;
        count++;
    }
}

// A mon is in the currently-browsed building submenu if its wave is the one
// the player picked on the building-select screen. IsShopEntryUnlocked is a
// belt-and-suspenders check - sPendingBuildingWave can't be set to a wave
// that isn't unlocked (FacilityShopBuildBuildingMenu only ever offers
// unlocked waves), but the check is one word and worth keeping honest.
static bool8 IsMonInPendingWave(const struct FacilityShopMon *mon)
{
    return mon->unlockBuilding == sPendingBuildingWave && IsShopEntryUnlocked(mon->unlockBuilding);
}

// Stages the final species list for the remembered tier/building wave,
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
        sMenuRows[count].price = pool[i].price;
        sMenuRows[count].name = GetSpeciesName(pool[i].species);
        sMenuRows[count].description = NULL;
        count++;
    }
    return count;
}

static const u8 sText_TypeFilterAll[] = _("All");

// Stages the type-filter menu: one row per distinct primary type actually
// present among the tier's currently-browsed building wave, plus "All" up
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

// gSpecialVar_0x8009 = FACILITY_SHOP_TIER_* in. sPendingBuildingWave must
// already be set (FacilityShopSelectBuildingRow does this before the caller
// ever reaches the tier-select screen).
// gSpecialVar_Result = TRUE if this tier/wave combination has more mons than
// fit in one screenful of browsing and a type-filter menu was staged instead
// of the species list directly - the caller shows that menu and then calls
// FacilityShopSelectMonType with the chosen row before showing the (now
// staged) species list. FALSE means the species list is already staged and
// ready to show. Splitting the master tables by building wave first means
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
// Building-select menu - the screen above tier-select. One row per building
// whose shop wave (unlockBuilding value) is unlocked and actually has a mon
// in some tier, plus "Sell a Pokemon". Adding a building's worth of new mons
// is exactly one more line in sBuildingWaveNames (and the unlockBuilding
// values already on those rows do the rest) - no other change needed here.
// ----------------------------------------------------------------------------

static const u8 *const sBuildingWaveNames[] =
{
    COMPOUND_STRING("Building 1 Pokemon"),
    COMPOUND_STRING("Building 2 Pokemon"),
    COMPOUND_STRING("Building 3 Pokemon"),
    COMPOUND_STRING("Building 4 Pokemon"),
};

static const u8 sText_SellAPokemon[] = _("Sell a Pokemon");

// Guards against a wave number that's unlocked (in the IsShopEntryUnlocked
// sense) but was never actually given any Pokemon of its own - e.g. a future
// building whose shop-unlock wave is items-only at Keeper 4's counter.
// Showing a building option that opens onto an empty tier list would be a
// dead end, so it just doesn't appear.
static bool8 BuildingWaveHasAnyMon(u8 wave)
{
    u32 tier, i;

    for (tier = 0; tier < ARRAY_COUNT(sMonTiers); tier++)
    {
        for (i = 0; i < sMonTierSizes[tier]; i++)
        {
            if (sMonTiers[tier][i].unlockBuilding == wave)
                return TRUE;
        }
    }
    return FALSE;
}

// The Pokemon keeper's first screen. Stages one row per unlocked building
// wave plus "Sell a Pokemon" - see FacilityShopSelectBuildingRow for what the
// caller does with the chosen row.
void FacilityShopBuildBuildingMenu(void)
{
    u16 i, count = 0;

    for (i = 0; i < ARRAY_COUNT(sBuildingWaveNames); i++)
    {
        if (IsShopEntryUnlocked(i) && BuildingWaveHasAnyMon(i))
            count++;
    }
    count++; // Sell a Pokemon

    FreeMenuRows();
    sMenuRows = Alloc(count * sizeof(struct FacilityShopMenuRow));
    sMenuRowCount = count;

    for (i = 0, count = 0; i < ARRAY_COUNT(sBuildingWaveNames); i++)
    {
        if (!IsShopEntryUnlocked(i) || !BuildingWaveHasAnyMon(i))
            continue;
        sMenuRows[count].id = i;
        sMenuRows[count].price = 0;
        sMenuRows[count].name = sBuildingWaveNames[i];
        sMenuRows[count].description = NULL;
        count++;
    }
    sMenuRows[count].id = FACILITY_SHOP_BUILDING_SELECT_SELL;
    sMenuRows[count].price = 0;
    sMenuRows[count].name = sText_SellAPokemon;
    sMenuRows[count].description = NULL;
}

// gSpecialVar_0x8004 = chosen row index into the just-shown building menu.
// gSpecialVar_Result = TRUE means the player picked "Sell a Pokemon" - the
// caller goes straight to the sell flow. FALSE means sPendingBuildingWave is
// now set and the caller should show tier-select next.
void FacilityShopSelectBuildingRow(void)
{
    u16 index = gSpecialVar_0x8004;
    u16 id = sMenuRows[index].id;

    if (id == FACILITY_SHOP_BUILDING_SELECT_SELL)
    {
        gSpecialVar_Result = TRUE;
    }
    else
    {
        sPendingBuildingWave = id;
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
void FacilityShopBuyMon(void)
{
    struct PokemonTemplate template = {0};
    struct Pokemon mon;

    template.species = gSpecialVar_0x8009;
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

    CreateMonFromTemplate(&mon, &template);
    gSpecialVar_Result = GiveCapturedMonToPlayer(&mon);
}

// Sell-back price lookup scans every tier regardless of unlock status -
// buildingsCompleted bits only ever get set, never cleared, so a mon the
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
    u32 total = gPartiesCount[B_TRAINER_PLAYER];
    u32 i;

    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
        total += CountMonsInBox(i);

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

    StringCopy(gStringVar1, GetSpeciesName(species));
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
