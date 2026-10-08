#include "global.h"
#include "event_data.h"
#include "facility.h"
#include "test/test.h"
#include "constants/region_map_sections.h"

// Ten Gauntlets: STEVEN hands back the Lati he took after gauntlet 4
// (GiveStevenLatiBack builds a fresh one). Both Lati in Artisan Cave are
// forced shiny, so the one he returns must be too. Ten tries each, so a
// lucky shiny roll can't pass it.
TEST("Ten Gauntlets: STEVEN gives the Lati back shiny")
{
    u32 i, species = 0;

    PARAMETRIZE { species = SPECIES_LATIAS; FlagClear(FLAG_STEVEN_HAS_LATIOS); }
    PARAMETRIZE { species = SPECIES_LATIOS; FlagSet(FLAG_STEVEN_HAS_LATIOS); }
    for (i = 0; i < 10; i++)
    {
        ZeroPlayerPartyMons();
        GiveStevenLatiBack();
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES), species);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_MET_LOCATION), MAPSEC_ARTISAN_CAVE);
        EXPECT(IsMonShiny(&gParties[B_TRAINER_PLAYER][0]));
    }
}
