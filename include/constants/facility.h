#ifndef GUARD_CONSTANTS_FACILITY_H
#define GUARD_CONSTANTS_FACILITY_H

// Ten Buildings facility run loop (run-loop-spec.md). Split out from
// include/facility.h so scripts can see these too - data/event_scripts.s
// only pulls in constants/*.h headers, and setvar's own .if-based warning
// check needs FACILITY_BUILDING_* to resolve to a literal constant at
// assemble time.
//
// Building index, matching gSaveBlock3Ptr->facility.run.building (0-9) and
// the bit position in facility.progress.buildingsCompleted.
#define FACILITY_BUILDING_1 0
#define FACILITY_BUILDING_2 1
#define FACILITY_BUILDING_3 2
#define FACILITY_BUILDING_4 3

#endif // GUARD_CONSTANTS_FACILITY_H
