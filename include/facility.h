#ifndef GUARD_FACILITY_H
#define GUARD_FACILITY_H

#include "constants/facility.h"

struct Pokemon;

// The shared "is a run active" check. Every mid-run restriction (L-menu, PC,
// shop) and the BATTLE_TYPE_BATTLE_TOWER-on-facility-battles hook in
// src/battle_setup.c go through this single function - see run-loop-spec.md.
bool8 IsFacilityRunActive(void);

// Is trainerId one of ours (a gauntlet's pool or boss)? See the comment on
// this function's definition in src/facility.c for why battle_message.c
// needs this to route our trainers around the real Battle Frontier's
// trainerId-indexed lookups.
bool8 IsFacilityBattleTrainer(u16 trainerId);
bool8 IsFrontierStoryTrainer(u16 trainerId);

void FacilityCheckEligible(void);
// gSpecialVar_0x8004 = FACILITY_GAUNTLET_* to start a run for.
void FacilityStartRun(void);
void FacilityIsBossBattle(void);
// The Lounge 7 psychic's boss reading - see src/facility.c.
u16 FacilityPsychicGetBoss(void);
void FacilityPsychicGetBossMon(void);
void FacilityGetDrawnPoolIndex(void);
void FacilityAwardBattleFP(void);
// gStringVar1 = ordinal ("1st".."6th") for the pool battle just won,
// gSpecialVar_0x8008 = FP just awarded, gSpecialVar_Result = TRUE on the 6th
// win (boss up next). Call before FacilityAdvanceBattleNum.
void FacilityGetBattleWonInfo(void);
void FacilityAdvanceBattleNum(void);
void FacilityCompleteGauntlet(void);
void FacilityAbandonRun(void);

// Quiet save (no message-box popup) - used after a loss.
void FacilitySilentSave(void);

// gSpecialVar_0x8004/0x8005 = the two party slots to swap. For the
// post-battle "rearrange party" option - see run-loop-spec.md's "Party
// reordering between battles".
void FacilitySwapPartyMonSlots(void);

// gSpecialVar_Result = gSaveBlock3Ptr->facility.run.gauntlet. Only
// meaningful while IsFacilityRunActive() - used by the Battle Tower
// Lobby's shared Facility_DoBattle to route to the right gauntlet's
// battle-label switch when more than one mat can start a run.
void GetFacilityRunGauntlet(void);

// specialvar: number of gauntlets cleared (0-10). See frontier-dialogue.md.
u16 GetGauntletsClearedCount(void);
u16 GetStoryGossipStage(void);
// specialvar: TRUE while the required Artisan Cave quest locks the shop.
bool16 IsFrontierPOSDown(void);
// The story's Experience rule - see src/facility.c.
bool32 FrontierStoryAllowsExp(void);
// The optional endgame fights at level 100 once Transfer EXP has been used.
void LiftOptionalEndgameTrainerParty(u16 trainerId, struct Pokemon *party);
bool32 IsFrontierChippedMon(struct Pokemon *mon);
bool32 IsFrontierChippedBoxMon(struct BoxPokemon *boxMon);

// gSpecialVar_0x8004 = FACILITY_GAUNTLET_* this mat represents in.
// IsFacilityRunActiveForGauntlet: TRUE if a run is active AND it's for
// that gauntlet (resume here). IsFacilityRunActiveForDifferentGauntlet:
// TRUE if a run is active for some *other* gauntlet (busy elsewhere -
// only one run can be active at a time, see run-loop-spec.md).
void IsFacilityRunActiveForGauntlet(void);
void IsFacilityRunActiveForDifferentGauntlet(void);

// The Doubles mat is locked until gauntlet 1 is cleared. The Multis mat
// (gauntlet 3) unlocks clearing gauntlet 2, and the Link Multis mat
// (gauntlet 4) unlocks clearing gauntlet 3.
void IsDoublesMatUnlocked(void);
void IsMultisMatUnlocked(void);
void IsLinkMultisMatUnlocked(void);

// Every non-Tower facility is locked at game start - see the FACILITY_DOOR_*
// comment in src/facility.c. Each of these is a `special` (not `specialvar`)
// called from its lobby map's OnFrame check, e.g.
// `special IsBattleDomeUnlocked` then `goto_if_eq VAR_RESULT, FALSE, ...`.
void IsBattleDomeUnlocked(void);
void IsBattleFactoryUnlocked(void);
void SetBattleFactoryUnlocked(void);
void IsBattlePikeUnlocked(void);
void IsBattleArenaUnlocked(void);
void IsBattlePalaceUnlocked(void);
void IsBattlePyramidUnlocked(void);

// TRUE when a door leads into a facility lobby that isn't open yet, so the
// door stays shut (TryDoorWarp in src/field_control_avatar.c). The door's
// sign event on the outside map explains why.
bool32 IsFacilityLobbyDoorLocked(u32 mapGroup, u32 mapNum);

// The Crown is taken, after gauntlet 7 (storyline.md). The player's front
// door is locked until BIRCH's confession (TryDoorWarp runs
// LittlerootTown_EventScript_HomeDoorLocked instead); StripBirchsLab and
// GiveStevenLatiBack are specials - see src/facility.c.
bool32 IsStoryLockedHomeDoor(u32 mapGroup, u32 mapNum);
// The endgame towns' locked doors (the GYMS): the script to run instead of
// warping, or NULL (TryDoorWarp).
const u8 *GetEndgameSealedDoorScript(u32 mapGroup, u32 mapNum);
// The REPLICA CROWN's limit on permanent Megas in the party, and the count
// (src/facility.c; used by ItemUseCB_ReplicaCrown).
u32 GetReplicaCrownLimit(void);
void TransferExpToLevel100(void);
void RaiseMonToLevel(void);
// The level every chipped Pokemon catches up to when the siphon frees it,
// and the level the shop sells at from then on (SiphonLiftChippedLevels).
#define FRONTIER_SIPHON_LEVEL 60
void SiphonLiftChippedLevels(void);
// The Paradox researcher in OLDALE (src/facility.c).
void OldaleCheckParadox(void);
u16 IsBadDreamsActive(void);
void OldaleMarkParadoxShown(void);
u32 CountPermanentMegasInParty(void);
bool32 IsReplicaCrownFull(void);
// special: VAR_0x8008 = VAR_0x8004 wins' FP for the current gauntlet (src/facility.c).
void FacilityGetWinsPrice(void);
void StripBirchsLab(void);
void GiveStevenLatiBack(void);
void GetFactoryBrainsBeaten(void);
void GetHoopaRingsLeft(void);
void SetBadDreamsDarkraiMoves(void);

#endif // GUARD_FACILITY_H
