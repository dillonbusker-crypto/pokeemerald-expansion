#ifndef GUARD_CONSTANTS_MOVE_RELEARNER_H
#define GUARD_CONSTANTS_MOVE_RELEARNER_H

// Max number of moves shown by the move relearner.
// Was 60 ("Increased from 25 to 60 so Mew can display all TMs/HMs") - sized
// for vanilla's 50 TMs + 8 HMs (58) with a little headroom. That comment
// stopped being true the moment this project's TM roster grew to 166 (see
// include/constants/tms_hms.h's FOREACH_TM) - GetRelearnerTMMoves()
// (src/move_relearner.c) writes one entry per TM/HM a species can still
// learn into sMoveRelearnerStruct->movesToLearn[MAX_RELEARNER_MOVES] with no
// bounds check at all, so any reasonably TM-versatile species (Mew being the
// extreme case, but far from the only one against a 166-move pool) could
// write past a 60-slot buffer and corrupt whatever heap-allocated memory
// came after it - a real heap-corruption bug found this way (garbled/crashed
// much later, at an unrelated menu that happened to touch the heap next).
// Raised to NUM_ALL_MACHINES (include/item.h) - the hard ceiling
// GetRelearnerTMMoves()'s own loop can never exceed, since it writes at most
// one entry per TM/HM that exists - so this is provably enough no matter how
// many machines a species can learn. A "combined legal pool" mode (level-up
// + egg + TM/HM + tutor in one list, needing this raised even further to
// 150) used to live here for a custom move editor tool - removed after a
// separate, never-fully-diagnosed heap corruption issue (see l_menu.c and
// data/scripts/debug.inc's Debug_EventScript_RelearnLevelUpMove for that
// history) - unrelated to this fix, but the same failure signature.
#define MAX_RELEARNER_MOVES 174

// Move Relearner menu change constants
enum MoveRelearnerStates
{
    MOVE_RELEARNER_LEVEL_UP_MOVES,
    MOVE_RELEARNER_EGG_MOVES,
    MOVE_RELEARNER_TM_MOVES,
    MOVE_RELEARNER_TUTOR_MOVES,
    MOVE_RELEARNER_COUNT,
};

enum RelearnMode
{
    RELEARN_MODE_NONE = 0,
    RELEARN_MODE_SCRIPT = 1,                     // Relearning moves through an event script
    // These two must stay 2 and 3, they are tied to the summary screen pages
    RELEARN_MODE_PSS_PAGE_BATTLE_MOVES = 2,      // Relearning moves through the summary screen's battle moves page
    RELEARN_MODE_PSS_PAGE_CONTEST_MOVES = 3,     // Relearning moves through the summary screen's contest moves page (defaults to contest page on relearner screen)
};

#endif // GUARD_CONSTANTS_MOVE_RELEARNER_H
