#ifndef GUARD_FACILITY_H
#define GUARD_FACILITY_H

#include "constants/facility.h"

// The shared "is a run active" check. Every mid-run restriction (L-menu, PC,
// shop) and the BATTLE_TYPE_BATTLE_TOWER-on-facility-battles hook in
// src/battle_setup.c go through this single function - see run-loop-spec.md.
bool8 IsFacilityRunActive(void);

// Is trainerId one of ours (a building's pool or boss)? See the comment on
// this function's definition in src/facility.c for why battle_message.c
// needs this to route our trainers around the real Battle Frontier's
// trainerId-indexed lookups.
bool8 IsFacilityBattleTrainer(u16 trainerId);

void FacilityCheckEligible(void);
// gSpecialVar_0x8004 = FACILITY_BUILDING_* to start a run for.
void FacilityStartRun(void);
void FacilityIsBossBattle(void);
void FacilityGetDrawnPoolIndex(void);
void FacilityAwardBattleFP(void);
// gStringVar1 = ordinal ("1st".."6th") for the pool battle just won,
// gSpecialVar_0x8008 = FP just awarded, gSpecialVar_Result = TRUE on the 6th
// win (boss up next). Call before FacilityAdvanceBattleNum.
void FacilityGetBattleWonInfo(void);
void FacilityAdvanceBattleNum(void);
void FacilityCompleteBuilding(void);
void FacilityAbandonRun(void);

// Quiet save (no message-box popup) - used after a loss.
void FacilitySilentSave(void);

// gSpecialVar_0x8004/0x8005 = the two party slots to swap. For the
// post-battle "rearrange party" option - see run-loop-spec.md's "Party
// reordering between battles".
void FacilitySwapPartyMonSlots(void);

// gSpecialVar_Result = gSaveBlock3Ptr->facility.run.building. Only
// meaningful while IsFacilityRunActive() - used by the Battle Tower
// Lobby's shared Facility_DoBattle to route to the right building's
// battle-label switch when more than one mat can start a run.
void GetFacilityRunBuilding(void);

// gSpecialVar_0x8004 = FACILITY_BUILDING_* this mat represents in.
// IsFacilityRunActiveForBuilding: TRUE if a run is active AND it's for
// that building (resume here). IsFacilityRunActiveForDifferentBuilding:
// TRUE if a run is active for some *other* building (busy elsewhere -
// only one run can be active at a time, see run-loop-spec.md).
void IsFacilityRunActiveForBuilding(void);
void IsFacilityRunActiveForDifferentBuilding(void);

// The Doubles mat is locked until building 1 is cleared. The Multis mat
// (building 3) unlocks clearing building 2, and the Link Multis mat
// (building 4) unlocks clearing building 3.
void IsDoublesMatUnlocked(void);
void IsMultisMatUnlocked(void);
void IsLinkMultisMatUnlocked(void);

// Every non-Tower facility is locked at game start - see the FACILITY_DOOR_*
// comment in src/facility.c. Each of these is a `special` (not `specialvar`)
// called from its lobby map's OnFrame check, e.g.
// `special IsBattleDomeUnlocked` then `goto_if_eq VAR_RESULT, FALSE, ...`.
void IsBattleDomeUnlocked(void);
void IsBattleFactoryUnlocked(void);
void IsBattlePikeUnlocked(void);
void IsBattleArenaUnlocked(void);
void IsBattlePalaceUnlocked(void);
void IsBattlePyramidUnlocked(void);

#endif // GUARD_FACILITY_H
