# Sprint C: the Gym rematches (Roxanne in Rustboro, Wattson in Mauville)

**Phase 2: built and tested** (2026-10-08). The lead's decisions: the
state-15 Wattson line removed from `MauvilleCity` (approved), Sky Pillar
left alone, **Miraidon** as Wattson's box-art legendary (not Zekrom), puzzle
off, heal kept. Results: the build is clean, widths fit (widest 198 px),
`test/battle/ten_gauntlets_enemy_mega.c` passes 4/4, and harness scenario 35
(`harness-gyms.c`) passes 17/17. Correction to section 6: Brandon's gauntlet
8 team already lists `Zygarde-Complete @ Zygardite` (doubles, level 50);
Roxanne's is the first singles one and the first with a test.

The original Phase 1 design follows. Workstream C of `sprint-endgame-towns.md`
(section 2C). The teams are in `endgame-teams.md`, "Gym rematches (Roxanne 60,
Wattson 65)". Everything below was checked against the code and map data on
`sprint/endgame-towns` (base `2ebbf4d7e3`). Where I assumed something instead
of checking it, the text says so.

---

## 0. Summary

| | Rustboro (Roxanne) | Mauville (Wattson) |
|---|---|---|
| Opens at | `VAR_ENDGAME_STATE` >= 10 | `VAR_ENDGAME_STATE` >= 15 |
| Sealed before | "The GYM's doors are locked" (unchanged text) | same |
| Interior | all five vanilla people hidden, Roxanne at (5, 2) | all six vanilla people hidden, Wattson at (5, 2), **puzzle switched off** |
| Path | 22 steps from the door mat, verified | 17 steps from the door mat, verified |
| Battle | `TRAINER_ENDGAME_ROXANNE` (990), singles, 6 at level 60 | `TRAINER_ENDGAME_WATTSON` (991), singles, 6 at level 65 |
| Win | party healed, then the lead to Devon's scientist | party healed, then the lead to the statue |
| Loss | white-out to Rustboro's Center, retry any time | white-out to Mauville's Center, retry any time |
| Unlock for A / B | `checktrainerflag TRAINER_ENDGAME_ROXANNE` | `checktrainerflag TRAINER_ENDGAME_WATTSON` |

No new flags, vars or trainer IDs. The vanilla Gym people are hidden with
`FLAG_TEMP_1` (not one of the aliased temp flags in `project-guide.md`'s trap:
9, A, B, E, 10 and up), set in each Gym's new `ON_TRANSITION`, the same
pattern `MauvilleCity` and `DevonCorp_1F` already use.

**Singles.** Both battles are singles (`Double Battle: No`), like the Elite
Four and New Mauville. D1 reads as a normal trainer battle; the vanilla
rematches were doubles, but nothing in the plan wants that and the teams are
built for 1v1.

---

## 1. Doors

### Today

`src/facility.c`, `sEndgameSealedDoors[]`: both Gyms are in the table
**unconditionally**, so `GetEndgameSealedDoorScript()` always returns
`EventScript_EndgameSealedGym` and `TryDoorWarp()`
(`src/field_control_avatar.c`) never lets the player in. The towns are only
reachable in the endgame, so "always" has meant "the whole endgame".

### Change

Give each entry the state at which it opens, and have the function return
`NULL` from then on:

```c
static const struct { u16 map; const u8 *script; u16 openState; } sEndgameSealedDoors[] =
{
    { MAP_RUSTBORO_CITY_GYM, EventScript_EndgameSealedGym, 10 },  // the Elite Four, Stone and Juan are done
    { MAP_MAUVILLE_CITY_GYM, EventScript_EndgameSealedGym, 15 },  // New Mauville is done
};

const u8 *GetEndgameSealedDoorScript(u32 mapGroup, u32 mapNum)
{
    u32 i, map = mapNum | (mapGroup << 8);

    for (i = 0; i < ARRAY_COUNT(sEndgameSealedDoors); i++)
    {
        if (sEndgameSealedDoors[i].map == map)
            return VarGet(VAR_ENDGAME_STATE) >= sEndgameSealedDoors[i].openState
                 ? NULL : sEndgameSealedDoors[i].script;
    }
    return NULL;
}
```

- `field_control_avatar.c` is unchanged: it already calls the function twice
  (test, then run) and falls through to the normal warp on `NULL`.
- Below the threshold (including state 0, the whole non-endgame game) the
  Gym stays sealed exactly as today, so no vanilla behaviour changes.
- **Stays open for good**: states 16, 17 and 18 (after the credits) are all
  >= the threshold (D4). There is no way to re-seal.
- The sealed text is unchanged. Comments to update: the table's header in
  `facility.c` ("only the GYMS stay shut" becomes "until their town is
  freed") and the first paragraph of `data/scripts/endgame_towns.inc`.
- State meanings used: Rustboro 10 is set at the end of `RustboroCity_
  EventScript_JuanScene` (Juan's apology); Mauville 15 is set at the end of
  `MauvilleCity_EventScript_CenterScene`.

---

## 2. Rustboro Gym

### Map facts (checked in `data/layouts/RustboroCity_Gym/map.bin` and `map.json`)

Layout 11x20. Warps at (5, 19) and (6, 19) to Rustboro (27, 19). Vanilla
people: Roxanne (5, 2) facing down, Josh (5, 13), Tommy (3, 9), Marc (1, 6),
the Gym guide (3, 18). Statues (bg events) at (2, 18) and (8, 18) stay.

The maze is made of blocked tiles, so only the trainers' sight lines matter
once they are gone. Breadth-first search over the collision bits (2 bytes a
tile, bits 10-11) with every person removed:

```
(5,18) N x10 -> (5,8)   W x3 -> (2,8)   N x4 -> (2,4)   E x2 -> (4,4)
N x1 -> (4,3)           E x1 -> (5,3)   [in front of Roxanne at (5,2)]
```

From the arrival tile (5, 19) that is 22 steps, ending east-facing at (5, 3);
face north and press A. Column 5 is clear of walls from y 18 down to y 8
(Josh's tile (5, 13) is plain floor under him). (4, 2) is also walkable beside
her, so a player who approaches from the left also reaches her.

### Hiding the people

- `map.json`: the five vanilla objects (Josh, Tommy, Marc, the guide; Roxanne
  stays) get `"flag": "FLAG_TEMP_1"` instead of `"0"`. In the vanilla game the
  flag is never set, so nothing changes outside the endgame.
- `scripts.inc`: add an `ON_TRANSITION`:

```
RustboroCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_Gym_OnTransition
	.byte 0

RustboroCity_Gym_OnTransition:
	call_if_ge VAR_ENDGAME_STATE, 10, RustboroCity_Gym_EventScript_SetupEndgame
	end

@ Ten Gauntlets: the Gym only opens in the endgame (state 10, GetEndgameSealedDoorScript).
@ TEMP_1 hides JOSH, TOMMY, MARC and the guide; ROXANNE is alone. The respawn is
@ set here too, so a save made inside the Gym still whites out to the Center.
RustboroCity_Gym_EventScript_SetupEndgame::
	setflag FLAG_TEMP_1
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	return
```

(`HEAL_LOCATION_RUSTBORO_CITY` is the constant the Center's own transition
uses.)

### Roxanne's script

`RustboroCity_Gym_EventScript_Roxanne` gets one new first line; the vanilla
body below it is untouched:

```
RustboroCity_Gym_EventScript_Roxanne::
	goto_if_ge VAR_ENDGAME_STATE, 10, RustboroCity_Gym_EventScript_EndgameRoxanne
	trainerbattle_single TRAINER_ROXANNE_1, ...   @ vanilla, unchanged
```

New labels (modelled on the Elite Four's scripts in `RustboroCity_DevonCorp_1F`
and the held-item handling in `NewMauville_Inside`):

```
RustboroCity_Gym_EventScript_EndgameRoxanne::
	lock
	faceplayer
	checktrainerflag TRAINER_ENDGAME_ROXANNE
	goto_if TRUE, RustboroCity_Gym_EventScript_EndgameRoxanneLead
	msgbox RustboroCity_Gym_Text_EndgameRoxanneIntro, MSGBOX_DEFAULT
	call RustboroCity_Gym_EventScript_SaveHeldItems
	trainerbattle_no_intro TRAINER_ENDGAME_ROXANNE, RustboroCity_Gym_Text_EndgameRoxanneDefeat
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	special HealPlayerParty
	msgbox RustboroCity_Gym_Text_EndgameRoxanneAfter, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_EndgameRoxanneLead::
	msgbox RustboroCity_Gym_Text_EndgameRoxanneRepeat, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_SaveHeldItems::
	closemessage
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
	return
```

- `checktrainerflag` sets the comparison result, so it is followed by
  `goto_if TRUE` (the project trap).
- A loss: `trainerbattle_no_intro` whites out; `EventScript_AfterWhiteOutHeal`
  already restores the saved held items (`call_if_set
  FLAG_STORY_HELD_ITEMS_SAVED`) and heals at the Center. The trainer flag is
  not set, so talking again starts the fight again.
- A win sets the trainer flag (A's gate) and the script heals the party
  (`HealPlayerParty`, as the New Mauville admins do) so the player can go
  straight to the scientist and the tunnel. The heal is in the narration line.
- No badge, no TM, no vanilla rewards: the player holds the badge flags from
  the start, and the lead is the reward (D8).
- The save/restore script is local to the map (like `NewMauville_Inside_
  EventScript_SaveHeldItems`) so the Gym does not depend on Devon's maps.

### Dialogue

`ROXANNE: ...` is her voice from the Frontier ("I'm still teaching. Just a
harder lesson"), the ambush ("SCOTT said you'd come") and Wallace's "gone
home to think about what they've done". The lines work at any state from 10
up (no mention of the siphon, Mauville or Sky Pillar).

```
RustboroCity_Gym_Text_EndgameRoxanneIntro:
	.string "ROXANNE: …I wondered whether you\n"
	.string "would come, {PLAYER}.\p"
	.string "After DEVON, I went home and did\n"
	.string "nothing but think.\p"
	.string "SCOTT offered me a promise, and I\n"
	.string "mistook it for ambition.\p"
	.string "You have never seen my full strength,\n"
	.string "not at the TOWER, not outside DEVON.\p"
	.string "A GYM LEADER owes every TRAINER the\n"
	.string "whole lesson. So here it is.\p"
	.string "Stone is patient, and stone does not\n"
	.string "give way. Show me what you are!$"

RustboroCity_Gym_Text_EndgameRoxanneDefeat:
	.string "Not a crack. Not even a chip…\p"
	.string "So this is what you have built.$"

RustboroCity_Gym_Text_EndgameRoxanneAfter:
	.string "ROXANNE: Thank you, {PLAYER}. I needed\n"
	.string "to see that for myself.\p"
	.string "ROXANNE had {PLAYER}'s POKéMON\n"
	.string "restored to full health.\p"
	.string "ROXANNE: Now, something I cannot\n"
	.string "set down.\p"
	.string "Rock keeps a record of everything\n"
	.string "that has pressed on it. I read those\l"
	.string "records for a living.\p"
	.string "Lately the stone of RUSTURF TUNNEL\n"
	.string "reads wrong. Layers that run into\l"
	.string "nothing. A draft with no source.\p"
	.string "I fear space itself is tearing there.\p"
	.string "The scientist on DEVON's top floor\n"
	.string "measures such things. Please go and\l"
	.string "see him.\p"
	.string "I would trust your eyes over mine.$"

RustboroCity_Gym_Text_EndgameRoxanneRepeat:
	.string "ROXANNE: Please speak with the\n"
	.string "scientist on DEVON's top floor.\p"
	.string "The stone of RUSTURF TUNNEL is not\n"
	.string "right. I would rather be wrong, but\l"
	.string "I do not think I am.$"
```

(The "restored to full health" line is a narration, not Roxanne speaking, so
it carries no name prefix; `{PLAYER}` is named, never made to speak.)

---

## 3. Mauville Gym

### Map facts (checked in `data/layouts/MauvilleCity_Gym/map.bin`, `map.json`, `src/field_specials.c`)

Layout 10x21. Warps at (4, 20) and (5, 20) to Mauville (8, 5). Vanilla people:
Wattson (5, 2) facing down (hide flag `FLAG_HIDE_MAUVILLE_GYM_WATTSON`, which
is clear unless the vanilla Petalburg story sets it), Shawn (7, 8), Angelo
(7, 10), Ben (5, 10), Kirk (1, 13), Vivian (1, 16), the guide (7, 20).
Statues at (3, 18) and (6, 18) stay. Four **floor switches**, each a
`coord_event` trigger on VAR_TEMP_0 = 0: (0, 15) = switch 1, (4, 12) = 2,
(3, 9) = 3, (8, 9) = 4.

### How the barriers work (every state)

- Pressing a switch other than the last one pressed calls
  `MauvilleGymSetDefaultBarriers`, which **flips every beam in x 0-8, y 5-16**
  (On to Off, Off to On, impassable bits and poles included), then toggles
  `FLAG_MAUVILLE_GYM_BARRIERS_STATE`. Pressing the same switch twice does
  nothing. `MauvilleCity`'s transition resets the flag and
  `VAR_MAUVILLE_GYM_STATE` to 0 on every visit, so **every entry starts in
  the default configuration**.
- So there are only **two** barrier configurations, A (default) and B (every
  beam flipped). I simulated both from the real code and map data: flipping A
  gives B exactly equal to what `MauvilleCity_Gym_EventScript_SetAltBarriers`
  hard-codes on a reload, and flipping twice returns to A.
- **A (default):** green beams block rows 7 (x 4-5) and 11 (x 1-2) and row 14
  (x 4-5); the red ones at rows 10-11 (x 4-5, 7-8) are off. No walkable route
  from the door to Wattson (89 reachable tiles, Wattson's room not among
  them).
- **B (flipped):** the row 6-7 beams (x 4-5) and the row 11 beams at x 1-2
  open; the red ones at rows 10-11 close; the vertical pole at (6, 8-10)
  opens. Wattson is reachable.
- All four switches are reachable from the door in both configurations.
  Exhaustive search over (tile, configuration, last switch): 837 reachable
  states, none of them a dead end. So **the vanilla puzzle is always
  solvable**; the shortest way is 25 steps and one press of switch 3 at
  (3, 9).

### Decision: switch the puzzle off in the endgame

Wattson tells the player he did it (see his line). Reasons:

1. With the Gym guide and every trainer gone, nothing hints at the switches,
   and the straight route up column 4 **crosses switch 2 at (4, 12)**, which
   would re-close the red beams at (4, 11) behind a player who has just
   opened the way. A first-time visitor would be confused.
2. It gives a guaranteed path (below) with no state dependence, no soft-lock
   risk and a trivial harness check.
3. The vanilla puzzle is left intact for anything that is not the endgame.

(If the owner prefers the puzzle, the analysis above shows it is safe to
leave: skip the four gates and the OnLoad line below and keep only the
hiding. Nothing else depends on it.)

Mechanism, reusing the vanilla deactivation:

```
MauvilleCity_Gym_OnLoad:
	goto_if_ge VAR_ENDGAME_STATE, 15, MauvilleCity_Gym_EventScript_DeactivatePuzzle   @ NEW first line
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DeactivatePuzzle
	...
```

`MauvilleGymDeactivatePuzzle` presses all four switches (graphics) and turns
every beam Off. Simulated result: all of rows 6-7, 10-11 and 13-14 are
walkable; only the decorative poles at (6, 8), (3, 11) stay solid.

And each of the four switch scripts (`MauvilleCity_Gym_EventScript_Switch1`
to `Switch4`) gets one gate right after `lockall`, **before** the existing
`FLAG_DEFEATED_MAUVILLE_GYM` line, so walking over a switch can no longer
flip the beams back on:

```
	goto_if_ge VAR_ENDGAME_STATE, 15, MauvilleCity_Gym_EventScript_SwitchDoNothing
```

(`SwitchDoNothing` is `releaseall; end`, which matches the `lockall`.) I chose
this over setting `FLAG_DEFEATED_MAUVILLE_GYM` in the endgame because that
flag means "Wattson was beaten" to anyone reading the script later; the
trainer flag is the real record.

### Verified path

With the puzzle off (configuration D, simulated from the real code):

```
door mat (4,20) -> N x17 along column 4 -> (4,3) -> E x1 -> (5,3)
```

That is 18 steps (17 north, 1 east), ending east-facing in front of Wattson
at (5, 2); face north and press A.
Every tile on column 4 from y 19 to y 3 is walkable in D, including (4, 12)
(switch 2, now inert), (4, 11), (4, 7) and (4, 6) (the former beams). Wattson's
tile (5, 2) and the approach (5, 3) are floor at elevation 0, as in vanilla.

### Hiding the people

- `map.json`: Shawn, Angelo, Ben, Kirk, Vivian and the guide get
  `"flag": "FLAG_TEMP_1"`. Wattson keeps `FLAG_HIDE_MAUVILLE_GYM_WATTSON`.
- `scripts.inc`: add `map_script MAP_SCRIPT_ON_TRANSITION,
  MauvilleCity_Gym_OnTransition` beside the existing `ON_LOAD`:

```
MauvilleCity_Gym_OnTransition:
	call_if_ge VAR_ENDGAME_STATE, 15, MauvilleCity_Gym_EventScript_SetupEndgame
	end

MauvilleCity_Gym_EventScript_SetupEndgame::
	setflag FLAG_TEMP_1
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	return
```

`ON_TRANSITION` runs before `ON_LOAD`, so the flag is set before objects are
placed. (Mauville's own transition already sets the respawn at state 12+; the
line here covers a save made inside the Gym.)

### Wattson's script

Same shape as Roxanne's:

```
MauvilleCity_Gym_EventScript_Wattson::
	goto_if_ge VAR_ENDGAME_STATE, 15, MauvilleCity_Gym_EventScript_EndgameWattson   @ NEW
	trainerbattle_single TRAINER_WATTSON_1, ...   @ vanilla, unchanged

MauvilleCity_Gym_EventScript_EndgameWattson::
	lock
	faceplayer
	checktrainerflag TRAINER_ENDGAME_WATTSON
	goto_if TRUE, MauvilleCity_Gym_EventScript_EndgameWattsonLead
	msgbox MauvilleCity_Gym_Text_EndgameWattsonIntro, MSGBOX_DEFAULT
	call MauvilleCity_Gym_EventScript_SaveHeldItems
	trainerbattle_no_intro TRAINER_ENDGAME_WATTSON, MauvilleCity_Gym_Text_EndgameWattsonDefeat
	special RestoreFacilityHeldItems
	clearflag FLAG_STORY_HELD_ITEMS_SAVED
	special HealPlayerParty
	msgbox MauvilleCity_Gym_Text_EndgameWattsonAfter, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_EndgameWattsonLead::
	msgbox MauvilleCity_Gym_Text_EndgameWattsonRepeat, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_SaveHeldItems::
	closemessage
	setflag FLAG_STORY_HELD_ITEMS_SAVED
	special SaveFacilityHeldItems
	return
```

### Dialogue

Wattson's voice is from the endgame scenes: "Wahahahah! The lights of
MAUVILLE are on again." Also state-neutral (no Scott, no Sky Pillar).

```
MauvilleCity_Gym_Text_EndgameWattsonIntro:
	.string "WATTSON: Wahahahah! There you are,\n"
	.string "{PLAYER}!\p"
	.string "MAUVILLE's lights are on, and the\n"
	.string "whole town is humming. We did that\l"
	.string "together, you and I.\p"
	.string "I switched off the GYM's puzzles.\n"
	.string "You've been through enough\l"
	.string "obstacles!\p"
	.string "But my POKéMON? Fully charged! I've\n"
	.string "been itching for a proper battle\l"
	.string "since the day those teams marched in!\p"
	.string "Show me your sparks, {PLAYER}!$"

MauvilleCity_Gym_Text_EndgameWattsonDefeat:
	.string "Wahahahah! Bzzt!\p"
	.string "Overloaded! And I loved every\n"
	.string "volt of it!$"

MauvilleCity_Gym_Text_EndgameWattsonAfter:
	.string "WATTSON: What a jolt! My old\n"
	.string "circuits haven't buzzed like that\l"
	.string "in years.\p"
	.string "WATTSON topped up {PLAYER}'s\n"
	.string "POKéMON.\p"
	.string "WATTSON: Now, an old coot has a\n"
	.string "favor to ask.\p"
	.string "When I built MAUVILLE, I built it\n"
	.string "around a statue. A crowned POKéMON,\l"
	.string "carved long before my time.\p"
	.string "AQUA and MAGMA toppled it during\n"
	.string "their little occupation. It lies in\l"
	.string "pieces in the plaza.\p"
	.string "I haven't the heart to look at it.\n"
	.string "Would you, {PLAYER}? Young eyes\l"
	.string "notice things.$"

MauvilleCity_Gym_Text_EndgameWattsonRepeat:
	.string "WATTSON: The statue in the plaza,\n"
	.string "{PLAYER}. A crowned POKéMON deserves\l"
	.string "better than rubble!\p"
	.string "Have a look when you can.$"
```

---

## 4. Everything that changes, by file

| File | Change |
|---|---|
| `src/facility.c` | `sEndgameSealedDoors` gets `openState`; `GetEndgameSealedDoorScript` returns NULL from that state (section 1) |
| `data/scripts/endgame_towns.inc` | header comment only |
| `data/maps/RustboroCity_Gym/scripts.inc` | `ON_TRANSITION` + `SetupEndgame`; one gate line in `...EventScript_Roxanne`; `EndgameRoxanne`, `...Lead`, `SaveHeldItems`; four texts |
| `data/maps/RustboroCity_Gym/map.json` | `"flag": "FLAG_TEMP_1"` on Josh, Tommy, Marc, the guide |
| `data/maps/MauvilleCity_Gym/scripts.inc` | `ON_TRANSITION` + `SetupEndgame`; first line of `OnLoad`; gate line in `Switch1`-`Switch4`; one gate line in `...EventScript_Wattson`; `EndgameWattson`, `...Lead`, `SaveHeldItems`; four texts |
| `data/maps/MauvilleCity_Gym/map.json` | `"flag": "FLAG_TEMP_1"` on Shawn, Angelo, Ben, Kirk, Vivian, the guide |
| `src/data/trainers.party` | replace the two placeholder parties (990, 991) with the teams in `endgame-teams.md`; keep the header lines (`Class: Leader`, `Pic`, `Music`, `Double Battle: No`, the AI line) |
| `test/battle/ten_gauntlets_enemy_mega.c` (new) | the Mega Zygarde test (section 6) |
| `~/decomps/headless-harness/harness-gyms.c` | scenario 35 (section 5) |

`include/constants/opponents.h` already has 990 and 991 (`TRAINERS_COUNT_EMERALD`
is 992). **AI line (copied from the New Mauville trainers):** `Check Bad Move /
Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart
Switching / Omniscient`, already on the placeholders.

**Needs the lead (outside my lane): `data/maps/MauvilleCity/scripts.inc`,
`MauvilleCity_EventScript_SetupEndgame`.** At state 15 the outside Wattson is
still shown by the Center (`call_if_eq VAR_ENDGAME_STATE, 15,
MauvilleCity_EventScript_ShowWattsonAtCenter`) saying "I'll stay and mind the
town". From state 15 he is in his Gym, so on every town load at 15 there would
be two Wattsons. The fix is to delete that one `call_if_eq` line: the Center
scene itself runs at state 14 (it sets 15 at its end), so it still plays out
with him in place, and he is gone from the street on the next load. This is
B's file; the line is `MauvilleCity/scripts.inc` line 711. Scenario 23 may
check the state-15 Wattson (it re-runs in Phase 3).

---

## 5. Harness plan: scenario 35 (`harness-gyms.c`)

New Game, `STORY_VAR` = `VAR_ENDGAME_STATE`, fast text, battle style Set,
`HARNESS_GOD_MODE` off for the must-lose battles. The party has a move nothing
is immune to (Nature's Madness, PP refilled); the HP hack weakens foes in the
won battles and holds the player at 1 HP in the lost ones, which must end in
`B_OUTCOME_LOST`. Doors, walks and checks (numbers are `OP_CHECK` ids):

| # | Step | Check |
|---|---|---|
| 1 | Setup state 9; `WARP_XY(RUSTBORO_CITY, 27, 20)`; `WALK(NORTH, 1)`; mash | 350: still `MAP_RUSTBORO_CITY`, `PY() == 20` (sealed) |
| 2 | Setup state 10; same warp and step | 351: `MAP_RUSTBORO_CITY_GYM` |
| 3 | wait idle | 352: only the player and Roxanne exist as objects (count active objects = 2); `FLAG_TEMP_1` set |
| 4 | from the arrival tile: `WALK(N,11) W3 N4 E2 N1 E1`, `FACE(N)`; log position | 353: `PX() == 5 && PY() == 3` |
| 5 | **Loss.** Setup "lose next"; `PRESS_A`; mash until idle | 354: `MAP_RUSTBORO_CITY_POKEMON_CENTER_1F`, party healed, `FLAG_STORY_HELD_ITEMS_SAVED` clear, held items back, trainer flag **not** set |
| 6 | **Win.** Setup "win"; `WARP_XY(MAP_RUSTBORO_CITY_GYM, 5, 3)`; `FACE(N)`; `PRESS_A`; mash until idle | 355: trainer flag `TRAINER_ENDGAME_ROXANNE` set, party full HP, items back, Roxanne still at (5, 2) |
| 7 | `PRESS_A` again, mash | 356: no battle started (battle counter unchanged); the lead line printed (log the text; read it in the log) |
| 8 | Setup state 18; door again | 357: still opens (D4) |
| 9 | Setup state 14; `WARP_XY(MAUVILLE_CITY, 8, 6)`; `WALK(N,1)` | 358: still `MAP_MAUVILLE_CITY`, `PY() == 6` |
| 10 | Setup state 15; same | 359: `MAP_MAUVILLE_CITY_GYM` |
| 11 | wait idle | 360: only the player and Wattson exist; the switch tiles read `METATILE_MauvilleGym_PressedSwitch`, and (4, 7) reads `METATILE_MauvilleGym_GreenBeamH3_Off` (puzzle off) |
| 12 | from the door mat (4, 20): `WALK(N,17)`, `WALK(E,1)`, `FACE(N)` | 361: `PX() == 5 && PY() == 3`; `VAR_MAUVILLE_GYM_STATE == 0` and (4, 11) still passable (the walk crossed switch 2 at (4, 12) without re-closing the beams) |
| 13 | **Loss**, as step 5 | 362: `MAP_MAUVILLE_CITY_POKEMON_CENTER_1F`, healed, items back, trainer flag clear |
| 14 | **Win**, as step 6 (`WARP_XY(MAP_MAUVILLE_CITY_GYM, 5, 3)`) | 363: `TRAINER_ENDGAME_WATTSON` set, full HP |
| 15 | talk again | 364: no battle, the lead line printed |
| 16 | state 15: `WARP_XY(MAUVILLE_CITY, 22, 8)` (only if the lead approves the `MauvilleCity` edit) | 365: no Wattson object by the Center |
| 17 | state 18: Mauville door again | 366: still opens |

Plan notes (the "plan first" rule):

- Tiles checked against collision: the Rustboro route above; the Mauville
  column 4 (puzzle off); (27, 20) and (8, 6) are walkable (3-elevation tiles
  next to the door tiles `1CD`); the door tiles themselves are the only
  things the "sealed" steps bump.
- Door steps use `WALK(NORTH, 1)` from one tile below, as scenario 11 does
  (113: `PY() == 20`).
- After a white-out, `WARP_XY` straight to (5, 3) in each Gym for the retry:
  the walk was proved once, and the warp re-runs the Gym's `ON_TRANSITION`.
- The unlock check for A and B is the trainer flag after steps 6 and 14:
  `FlagGet(TRAINER_FLAGS_START + TRAINER_ENDGAME_ROXANNE)` etc.
- No team is battled for real (the owner's rule): the teams are checked by
  building and reading the generated `src/data/trainers.h`; the harness only
  needs the battles to start and end.
- Shop dependence: none.

---

## 6. Verifying Mega Zygarde (Phase 2)

No trainer yet Mega Evolves from a listed `Zygarde-Complete`. The form table
(`sZygardeCompleteFormChangeTable`) has `FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM`
-> `SPECIES_ZYGARDE_MEGA` with `ITEM_ZYGARDITE`, behind
`P_GEN_9_MEGA_EVOLUTIONS` (which follows `P_MEGA_EVOLUTIONS`, on in this
build as Mega Heatran etc. work).

New file `test/battle/ten_gauntlets_enemy_mega.c`, formats copied from
`ten_gauntlets_perma_mega.c` and `test/battle/ai/gimmick_mega.c`:

1. **Scripted:** `SINGLE_BATTLE_TEST`: `OPPONENT(SPECIES_ZYGARDE_COMPLETE)
   { Item(ITEM_ZYGARDITE); }`, `TURN { MOVE(opponent, MOVE_CELEBRATE, gimmick:
   GIMMICK_MEGA); }`, `SCENE { ANIMATION(ANIM_TYPE_GENERAL,
   B_ANIM_MEGA_EVOLUTION, opponent); }`, `THEN { EXPECT_EQ(opponent->species,
   SPECIES_ZYGARDE_MEGA); EXPECT_EQ(opponent->ability, ABILITY_AURA_BREAK); }`.
2. **The AI really does it:** `AI_SINGLE_BATTLE_TEST` with the same flags as
   the existing "AI uses Mega Evolution" test plus the Gym leaders' set
   (`AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT |
   AI_FLAG_OMNISCIENT`), `OPPONENT(SPECIES_ZYGARDE_COMPLETE) {
   Item(ITEM_ZYGARDITE); Moves(MOVE_EARTH_POWER); }`, `TURN { EXPECT_MOVE(
   opponent, MOVE_EARTH_POWER, gimmick: GIMMICK_MEGA); }`, species check.
3. **Not as the first Pokémon:** Zygarde in slot 6, switched in after a faint
   (Roxanne's real order): Mega Evolves on its first turn out.
4. **Power Construct doesn't interfere:** with the Complete form holding the
   stone, no extra form change or message appears before the Mega one.

If any fails, report before changing the set (e.g. the fallback would be
listing `Zygarde-Mega` directly, as the Elite Four's permanent Megas are).
The build check also applies: read the generated `trainers.h` entry for 990
and confirm `.species = SPECIES_ZYGARDE_COMPLETE`, `.heldItem =
ITEM_ZYGARDITE`, and that the party-file name `Zygarde-Complete` is accepted
by `trainerproc` (I assumed the `Groudon-Primal` naming pattern; not tried).

`make check` stays at 15 known failures (new tests only add passes).

---

## 7. Gossip suggestion (for the lead, D9)

One line for a gossip NPC at `GOSSIP_MAUVILLE_FREED` (20) and later, widths
checked:

```
	.string "The old GYM LEADERS in RUSTBORO and\n"
	.string "MAUVILLE are battling again.\p"
	.string "They hold nothing back. But they\n"
	.string "do tell winners what's troubling\l"
	.string "them.$"
```

---

## 8. Open questions

1. **The second Wattson at state 15** (section 4): the one-line edit to
   `MauvilleCity/scripts.inc` is B's file. Needs your go.
2. **Wattson at Sky Pillar (states 16-17).** The ambush scene has him there, but
   the Gym (open from 15) would still show him at home if the player ABRAs
   back mid-ambush. I left it: the player must detour deliberately, and
   closing the Gym again at 16-17 would add a second sealed text and a
   re-closing the owner may not want (D4 says the Gyms stay open). Cheap to
   add if you want it.
3. **Zekrom or Miraidon.** The set is in `endgame-teams.md` with a Miraidon
   swap beneath it. Note this build's Zekrom learnset is thin (no Close
   Combat, Earthquake or Swords Dance), so its set is Dragon Dance / Bolt
   Strike / Outrage / Roost, all legal.
4. **Puzzle off vs on** (section 3): I recommend off; the on-analysis is
   complete if you disagree.
5. **The heal after the win** is my addition (the New Mauville admins heal);
   remove the `HealPlayerParty` and the narration if you want none.
6. **Learnset quirks** found while checking: this build's Zygarde has no
   Thousand Arrows, Core Enforcer or Thousand Waves, and Rotom-Wash has no
   Hydro Pump or Scald (the earlier Rotom exception was Noland's form-change
   case), so neither appears on these teams.
7. **Mega Zygarde's strength.** 216 Sp. Atk and 216 HP at level 60 is a lot
   for a first Gym rematch; difficulty is untuned like the rest. If it is too
   much, the dial is Roxanne's level (D2) or dropping Focus Blast for
   Protect.
8. `FLAG_TEMP_1` is free in both Gym maps (neither uses temp flags today);
   confirmed by search.
