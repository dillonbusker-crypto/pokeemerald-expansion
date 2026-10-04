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
#define FACILITY_GAUNTLET_8 7

// Story beats for townsfolk gossip, returned by GetStoryGossipStage()
// (src/facility.c). In story order; NPCs that gossip switch on these.
#define GOSSIP_ARRIVAL       0  // no gauntlet cleared yet
#define GOSSIP_NORMAN        1  // gauntlet 1: NORMAN stormed the TOWER
#define GOSSIP_STEVEN        2  // gauntlet 2: STEVEN seen on the island
#define GOSSIP_SYSTEM_DOWN   3  // gauntlet 3, LATI not caught: the island's system is down
#define GOSSIP_SMUGGLER      4  // LATI caught: FLOTSAM arrested, a cry in the cave
#define GOSSIP_ANABEL        5  // gauntlet 4: ANABEL beaten, the cave closed
#define GOSSIP_LAB           6  // gauntlet 5, BIRCH arc: DEVON at the lab, gauntlet 6 down
#define GOSSIP_AFTER_LAB     7  // BIRCH arc over: gauntlet 6 back up
#define GOSSIP_SQUAD         8  // gauntlet 6, before the arrest: SCOTT's squad marching
#define GOSSIP_ARREST        9  // the BROKER arrested, the ELITE FOUR missing
#define GOSSIP_PALACE        10 // back from EVER GRANDE: SCOTT out of town
#define GOSSIP_RAID          11 // gauntlet 7: the lab raided
#define GOSSIP_TAKEN         12 // BIRCH has confessed: the parents gone
#define GOSSIP_STANDOFF      13 // STEVEN beaten by SCOTT's MEWTWO
#define GOSSIP_ALL_CLEAR     14 // gauntlet 8 cleared

#endif // GUARD_CONSTANTS_FACILITY_H
