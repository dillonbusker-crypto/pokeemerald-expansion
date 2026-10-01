#ifndef GUARD_CONSTANTS_FACILITY_H
#define GUARD_CONSTANTS_FACILITY_H

// Ten Gauntlets facility run loop (run-loop-spec.md). Split out from
// include/facility.h so scripts can see these too - data/event_scripts.s
// only pulls in constants/*.h headers, and setvar's own .if-based warning
// check needs FACILITY_GAUNTLET_* to resolve to a literal constant at
// assemble time.
//
// Gauntlet index, matching gSaveBlock3Ptr->facility.run.gauntlet (0-9) and
// the bit position in facility.progress.gauntletsCompleted.
#define FACILITY_GAUNTLET_1 0
#define FACILITY_GAUNTLET_2 1
#define FACILITY_GAUNTLET_3 2
#define FACILITY_GAUNTLET_4 3
#define FACILITY_GAUNTLET_5 4
#define FACILITY_GAUNTLET_6 5
#define FACILITY_GAUNTLET_7 6

#endif // GUARD_CONSTANTS_FACILITY_H
