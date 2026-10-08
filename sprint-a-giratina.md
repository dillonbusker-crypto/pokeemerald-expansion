# Sprint A: Giratina in Rustboro, "The Tear" (Phase 1 design)

Design only. Nothing is built. Read with `sprint-endgame-towns.md` (section 2A
and the decisions in section 1). Written 2026-10-08 on branch
`worktree-agent-ae0427905d4b54fd1`, based on `sprint/endgame-towns` at
`2ebbf4d7e3` (the Phase 0 reservations are in place: `FLAG_GIRATINA_CAUGHT`
0x281, `FLAG_HOOPA_TEAR_HINTED` 0x282, `VAR_GIRATINA_EVENT` 0x40F9, and
`TRAINER_ENDGAME_ROXANNE` 990).

**What I verified** (read from the repo, not run): every coordinate below
against `map.bin` collision (bits 10-11 of each 16-bit entry) and `map.json`;
a breadth-first search of the Rusturf Tunnel walkable path; the engine
facts quoted (flash radius, dynamic warps, `IsFrontierChippedMon`, the ABRA
scripts); every dialogue line's pixel width with the font table (max 193 px
of 208, `{PLAYER}` counted as seven letters).
**What I assumed** is listed in section 7.

---

## 0. The shape of it, in brief

1. **Gate:** `checktrainerflag TRAINER_ENDGAME_ROXANNE` (Roxanne beaten).
   Before it, no new line, object or option appears anywhere.
2. **The clue:** Roxanne's lead (C's text) points to Devon. The Devon 3F
   scientist (already in the room, at (17, 7)) briefs the player and offers
   an escort (YES/NO). Two Rustboro NPCs (the Pokemon Center's girl and the
   Trainers' School's lass) give clue lines. Hoopa gets a one-time hint.
3. **The way in:** fade, narration, `warp` to Rusturf Tunnel (4, 9), the
   same pattern as Wattson to New Mauville.
4. **The tunnel:** vanilla events hidden, wild encounters removed, dark
   (`setflashlevel 2`), three "wrongness" moments in the corridor, a
   sighting at the last chamber, then Giratina at (19, 18).
5. **The battle:** `setwildbattle SPECIES_GIRATINA, 60`. Caught: the Griseous
   Core, light returns. Anything else: Giratina stays.
6. **Every tunnel exit** is a dynamic warp to Rustboro (31, 9).

**Suggested line for Roxanne's lead (C's text, for the lead to align):**

```
ROXANNE: The stone under RUSTURF TUNNEL has rung wrong since the FACTORY
blast. Take it to DEVON's scientists on 3F: their needles and my ear should agree.
```

(The scientist's briefing echoes it: "ROXANNE says the stone under it rings
wrong, too.")

---

## 1. `VAR_GIRATINA_EVENT` (0x40F9), the state machine

The var only moves forward. `FLAG_GIRATINA_CAUGHT` is the public "done" gate
(the other maps test the flag, not the var). Nothing here is set by C: the
gate for "Roxanne beaten" is the trainer flag itself.

| Value | Meaning | Set by | What it shows |
|---|---|---|---|
| 0 | Nothing happened yet | initial | Roxanne unbeaten: nothing changes anywhere. Roxanne beaten: clue lines, Hoopa hint, scientist's briefing are available |
| 1 | Briefed | the scientist's first talk (before the YES/NO, so declining still counts) | The scientist now offers the short "still leaning east" escort. The next arrival in the tunnel plays the entry narration |
| 2 | Entered once | `RusturfTunnel_OnFrame` (entry narration) | Wrongness trigger 1 (the shadow) is armed |
| 3 | Shadow seen | trigger at x = 7 | Wrongness trigger 2 (footprints) armed |
| 4 | Footprints seen | trigger at x = 16 | Wrongness trigger 3 (backwards writing) armed |
| 5 | Writing seen | trigger at x = 27 | The sighting trigger at the last chamber is armed |
| 6 | Giratina sighted | trigger at (21, 16) | Talking to Giratina plays its first contact text |
| 7 | Fought at least once, not caught | Giratina's script (first contact) | Talking to Giratina plays the short "hangs where it was" text |
| 8 | Caught, Core given | Giratina's script | Scientist and NPCs use their "closed" lines; the escort is gone |

Each wrongness trigger plays once, ever (the next value arms the next one),
so retries after a loss or a run show no repeat narration. `FLAG_GIRATINA_CAUGHT`
is set together with value 8, and it is also the hide flag of Giratina's
object.

**Not state-machine, derived:** the clue NPCs' three phases are just
(Roxanne flag clear / Roxanne flag set and Giratina not caught / Giratina
caught). The Hoopa hint uses `FLAG_HOOPA_TEAR_HINTED` (once) and the same two
tests.

---

## 2. Every script change, by map

Files outside the plan's "Owns" list that Phase 2 needs to touch are marked
**ASK**. Everything else is inside the owned set.

### 2.1 Numbers used and requested

| What | Value |
|---|---|
| `VAR_GIRATINA_EVENT` | reserved, as above |
| `FLAG_GIRATINA_CAUGHT` | reserved; also Giratina's object hide flag |
| `FLAG_HOOPA_TEAR_HINTED` | reserved |
| `VAR_TEMP_4` (tunnel) | Rusturf's `OnWarp` "face north once" (same trick as the Pike). Vanilla's tunnel uses `VAR_TEMP_1` only |
| **ASK: one new flag** `FLAG_HIDE_RUSTURF_TUNNEL_MIKE` | **0x285** (first of the spare flags). Hiker Mike has no hide flag today (`"flag": "0"`). See 2.2 and section 7 for the no-new-flag fallback |

No `FLAG_TEMP_9/A/B/E/10+` anywhere. No `FLAG_TEMP_*` at all in the tunnel.

### 2.2 `data/maps/RusturfTunnel/` (map.json and scripts.inc)

Everything that changes from vanilla is gated on `VAR_ENDGAME_STATE >= 10`
(the town's liberation) except the three exit warps, which can't be
conditional (see "Exits").

**`map.json`**

- **Objects.** Add Giratina:
  `local_id LOCALID_RUSTURF_TUNNEL_GIRATINA`,
  `graphics_id OBJ_EVENT_GFX_SPECIES(GIRATINA)` (a 64x64 overworld sprite,
  like Lugia's), at **(19, 18)**, `MOVEMENT_TYPE_FACE_UP`,
  `script RusturfTunnel_EventScript_Giratina`, `flag FLAG_GIRATINA_CAUGHT`.
  Change Hiker Mike's `"flag": "0"` to `FLAG_HIDE_RUSTURF_TUNNEL_MIKE`
  (ASK).
- **Coord events** (all `type trigger`, `elevation 3`; none on a tile that a
  vanilla event uses: vanilla's are (23, 4), (25, 4), (25, 5), (9, 4),
  (9, 5)):

  | Tiles | var | value | script |
  |---|---|---|---|
  | (7, 4), (7, 5) | `VAR_GIRATINA_EVENT` | 2 | `RusturfTunnel_EventScript_Shadow` |
  | (16, 4), (16, 5) | `VAR_GIRATINA_EVENT` | 3 | `RusturfTunnel_EventScript_Prints` |
  | (27, 4), (27, 5) | `VAR_GIRATINA_EVENT` | 4 | `RusturfTunnel_EventScript_Writing` |
  | (21, 16) | `VAR_GIRATINA_EVENT` | 5 | `RusturfTunnel_EventScript_Sighting` |

  The corridor is two tiles tall (rows 4 and 5) at x = 7, 16 and 27, so a
  pair of tiles covers the width. (21, 16) is the only way into the last
  chamber (checked below), so one tile is enough.
- **Exits.** The three warp events at (4, 10), (29, 16) and (18, 20) change
  to `"dest_map": "MAP_DYNAMIC", "dest_warp_id": "WARP_ID_DYNAMIC"` (the
  Lilycove elevator does this). Their destination is whatever
  `setdynamicwarp` last stored, set in the tunnel's OnTransition (below) to
  Rustboro (31, 9). This is unconditional, like New Mauville's exit was:
  Route 116 and Verdanturf cannot be reached in the endgame, so no live
  path changes. The Route 116 / Verdanturf warps that point *into* the
  tunnel are untouched.

**`scripts.inc`**

- `RusturfTunnel_MapScripts`: add
  `map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RusturfTunnel_OnWarp`.
- `RusturfTunnel_OnTransition` (modified): keep the vanilla line, then
  `call_if_ge VAR_ENDGAME_STATE, 10, RusturfTunnel_EventScript_SetupEndgame`.
- **New** `RusturfTunnel_EventScript_SetupEndgame`:
  ```
  setflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
  setflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
  setflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
  setflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
  setflag FLAG_HIDE_RUSTURF_TUNNEL_BRINEY
  setflag FLAG_HIDE_RUSTURF_TUNNEL_ROCK_1
  setflag FLAG_HIDE_RUSTURF_TUNNEL_ROCK_2
  setflag FLAG_HIDE_RUSTURF_TUNNEL_MIKE        @ ASK
  setdynamicwarp MAP_RUSTBORO_CITY, 31, 9
  goto_if_set FLAG_GIRATINA_CAUGHT, Common_EventScript_NopReturn
  setflashlevel 2
  return
  ```
  Setting a hide flag in OnTransition works because objects spawn after the
  transition script (this is how every other endgame map hides things).
  Five of these flags are already set at New Game
  (`data/scripts/new_game.inc`); setting them again is harmless and covers
  any save that cleared them. The two rocks are **not** set by New Game, so
  they genuinely need this. No wild-encounter call is needed in the script
  (see `wild_encounters.json` below).
- `RusturfTunnel_OnFrame` (modified): add, **first** in the table,
  `map_script_2 VAR_GIRATINA_EVENT, 1, RusturfTunnel_EventScript_FirstEntry`.
  Vanilla's two entries (`VAR_RUSTURF_TUNNEL_STATE` 4 and 5) stay and never
  fire (that var stays 0).
- **New** `RusturfTunnel_OnWarp`:
  `map_script_2 VAR_TEMP_4, 0, RusturfTunnel_EventScript_FaceNorth`;
  `FaceNorth` does `setvar VAR_TEMP_4, 1`, `turnobject LOCALID_PLAYER,
  DIR_NORTH`, `end` (the Pike lair's pattern).
- **New** `RusturfTunnel_EventScript_FirstEntry`: `lockall`, the entry
  narration (`Text_Enter`), `setvar VAR_GIRATINA_EVENT, 2`, `releaseall`.
- **New** `RusturfTunnel_EventScript_Shadow` / `_Prints` / `_Writing`:
  each `lockall`, its message, `setvar VAR_GIRATINA_EVENT, 3 / 4 / 5`,
  `releaseall`, `end`.
- **New** `RusturfTunnel_EventScript_Sighting`: `lockall`,
  `playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER`, `waitmoncry`,
  `Text_Sighting`, `setvar VAR_GIRATINA_EVENT, 6`, `releaseall`.
- **New** `RusturfTunnel_EventScript_Giratina` (the object). Same shape as
  the Pike's Darkrai script:
  ```
  lock
  faceplayer
  checkitemspace ITEM_GRISEOUS_CORE            @ always room for the reward
  goto_if_eq VAR_RESULT, FALSE, ..._GiratinaBagFull
  goto_if_ge VAR_GIRATINA_EVENT, 7, ..._GiratinaAgain
  msgbox Text_GiratinaFirst, MSGBOX_DEFAULT
  setvar VAR_GIRATINA_EVENT, 7
  goto ..._GiratinaBattle
  ..._GiratinaAgain:  msgbox Text_GiratinaAgain ; (falls into Battle)
  ..._GiratinaBattle:
  closemessage
  playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
  waitmoncry
  setwildbattle SPECIES_GIRATINA, 60
  dowildbattle
  specialvar VAR_RESULT, GetBattleOutcome
  goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ..._GiratinaCaught
  msgbox Text_GiratinaStays, MSGBOX_DEFAULT     @ won, ran, teleported: it stays
  release
  end
  ```
  A loss never returns to the script (the engine white-outs to Rustboro's
  Pokemon Center, whose OnTransition sets the respawn on every ABRA arrival).
- **New** `RusturfTunnel_EventScript_GiratinaCaught`:
  `setflag FLAG_GIRATINA_CAUGHT`, `setvar VAR_GIRATINA_EVENT, 8`,
  `removeobject LOCALID_RUSTURF_TUNNEL_GIRATINA`, `animateflash 0`,
  `setflashlevel 0` (the dark lifts), `Text_Caught`,
  `giveitem ITEM_GRISEOUS_CORE`, `Text_Core`, `release`, `end`.
- **New** `RusturfTunnel_EventScript_GiratinaBagFull`:
  `Text_BagFull`, `release`, `end`.
- **Left alone:** the two items ((3, 1) Poke Ball, (30, 2) Max Ether) stay
  as optional loot; the vanilla scripts (Wanda, boyfriend, grunt, Peeko,
  Mike, `ClearTunnelScene`, the `TunnelBlockagePos*` setvars on (23, 4),
  (25, 4), (25, 5)) are untouched and never reachable. The tunnel's music
  (`MUS_PETALBURG_WOODS`) and fog weather are unchanged (section 7).

**Hidden vanilla objects** (all hidden by the flags in `SetupEndgame`):

| Object | Tile | Hide flag | Already set at New Game? |
|---|---|---|---|
| Wanda | (25, 4) | `FLAG_HIDE_RUSTURF_TUNNEL_WANDA` | yes |
| Wanda's boyfriend | (23, 5) | `..._WANDAS_BOYFRIEND` | yes |
| Aqua grunt | (14, 5) | `..._AQUA_GRUNT` | yes |
| Peeko | (14, 4) | `..._PEEKO` | yes |
| Mr. Briney | (5, 4) | `..._BRINEY` | yes |
| Rock Smash rock | (24, 5) | `FLAG_HIDE_RUSTURF_TUNNEL_ROCK_1` | **no** |
| Rock Smash rock | (24, 4) | `FLAG_HIDE_RUSTURF_TUNNEL_ROCK_2` | **no** |
| Hiker Mike (trainer) | (32, 13) | `FLAG_HIDE_RUSTURF_TUNNEL_MIKE` (new, ASK) | n/a, new |

Mike matters: he faces left from (32, 13) and the route passes (29, 13),
three tiles into his line of sight. Hiding the rocks does **not** trigger
the vanilla HM Strength scene: that scene is gated on
`VAR_RUSTURF_TUNNEL_STATE` 4 or 5, and `TryUpdateRusturfTunnelState` (the
only thing that sets those from the rock flags) is called only from the
Rock Smash field-move script, which HMs being banned never reaches.

### 2.3 `data/maps/RustboroCity_DevonCorp_3F/scripts.inc`

- `RustboroCity_DevonCorp_3F_EventScript_Scientist` (modified; today it is a
  `MSGBOX_NPC` showing `Text_ScientistAfter`). The map.json object (17, 7)
  keeps the same script label. New logic:
  ```
  lock
  faceplayer
  checktrainerflag TRAINER_ENDGAME_ROXANNE
  goto_if FALSE, ..._ScientistCrown            @ the old line, unchanged
  goto_if_set FLAG_GIRATINA_CAUGHT, ..._ScientistTearClosed
  goto_if_ge VAR_GIRATINA_EVENT, 1, ..._ScientistTearAgain
  msgbox Text_TearBrief1 / Brief2 / Brief3
  setvar VAR_GIRATINA_EVENT, 1
  msgbox Text_TearAsk, MSGBOX_YESNO
  goto_if_eq VAR_RESULT, NO, ..._ScientistTearNotYet
  goto ..._ScientistTearLead
  ```
  `..._ScientistCrown` is the old `Text_ScientistAfter` + `release`.
  `..._ScientistTearAgain` shows `Text_TearAskAgain` (YES/NO), NO goes to
  `NotYet`. `..._ScientistTearNotYet`: `Text_TearNotYet`, `release`.
  `..._ScientistTearClosed`: `Text_TearClosed`, `release`.
- **New** `..._ScientistTearLead` (the Wattson pattern from
  `MauvilleCity_EventScript_LeadToNewMauville`):
  ```
  closemessage
  fadescreen FADE_TO_BLACK
  msgbox Text_TearLed, MSGBOX_DEFAULT
  closemessage
  warp MAP_RUSTURF_TUNNEL, 4, 9
  waitstate
  releaseall
  end
  ```
- No map.json change. No other 3F script changes. The scientist is never
  hidden (no hide flag on that object); Stone and the 3F map are unchanged.

### 2.4 `data/maps/RustboroCity_PokemonCenter_1F/scripts.inc`

- `RustboroCity_PokemonCenter_1F_EventScript_Girl` (the girl at (10, 6);
  today `MSGBOX_NPC` of the HM Cut line) becomes:
  ```
  checktrainerflag TRAINER_ENDGAME_ROXANNE
  goto_if FALSE, ..._GirlOld                   @ vanilla line, unchanged
  goto_if_set FLAG_GIRATINA_CAUGHT, ..._GirlTearClosed
  msgbox ..._Text_GirlTear, MSGBOX_NPC
  end
  ```
  (`..._GirlOld` and `..._GirlTearClosed` are `msgbox ..., MSGBOX_NPC` + `end`.)
  She stands beside the ABRA's landing tile (12, 5), so the player passes her
  on every arrival.

### 2.5 `data/maps/RustboroCity_PokemonSchool/scripts.inc`

- `RustboroCity_PokemonSchool_EventScript_Lass` (the lass at (10, 8)):
  same three-phase shape as the girl, `_Text_LassTear` and
  `_Text_LassTearClosed`.

### 2.6 `data/maps/BattleFrontier_BattleArenaLobby/scripts.inc`

- `..._EventScript_Hoopa` (modified): after `waitmoncry`, before the ring
  count, add `call BattleFrontier_BattleArenaLobby_EventScript_TearHint`.
- **New** `..._EventScript_TearHint`:
  ```
  goto_if_set FLAG_HOOPA_TEAR_HINTED, Common_EventScript_NopReturn
  goto_if_set FLAG_GIRATINA_CAUGHT, Common_EventScript_NopReturn
  checktrainerflag TRAINER_ENDGAME_ROXANNE
  goto_if FALSE, Common_EventScript_NopReturn
  msgbox ..._Text_HoopaTear, MSGBOX_DEFAULT
  setflag FLAG_HOOPA_TEAR_HINTED
  return
  ```
  It runs before the "rings left" test on purpose: if the player has already
  spent both rings, the hint still shows on the first talk. The ring list
  itself is not touched (twelve rings, no thirteenth entry: the hint says
  the thirteenth won't open).

### 2.7 `src/facility.c`

`IsFrontierChippedMon`: extend the unchipped list by one,
`&& metLocation != MAPSEC_RUSTURF_TUNNEL`. A Pokemon caught in the tunnel
gets `MAPSEC_RUSTURF_TUNNEL` as its met location because the tunnel map's
`region_map_section` is `MAPSEC_RUSTURF_TUNNEL` (verified in map.json).
B adds `MAPSEC_MAUVILLE_CITY` to the same expression: a one-line merge
conflict at most, as the plan says. Giratina is available from state 10, a
state before the siphon (11) turns chips off for everything, so the line
does real work.

### 2.8 **ASK** `src/data/wild_encounters.json`

Delete the `MAP_RUSTURF_TUNNEL` block (Whismur at level 6-7, rate 10), as
Phase 4 did for New Mauville (commit `bfb7c2228a`). Without it a dark,
fogged corridor throws Whismur at the player every few steps. It is the
only wild-encounter switch this project uses (`WE_FLAG_NO_ENCOUNTER` is 0).
Nothing in `src/` refers to `gRusturfTunnel`.

### 2.9 Not touched

`RustboroCity` (the town's map, its sealed exits, its scripts): no change.
Its sealed-exit triggers at the town edge stay as they are; the tunnel's
exits land the player inside the walls. `include/constants/flags.h` changes
only for the Mike flag (ASK).

---

## 3. The map path, verified

Object and warp positions in map.json are **tile** coordinates; I read
`data/layouts/RusturfTunnel/map.bin` (36 x 24, `LAYOUT_RUSTURF_TUNNEL`,
collision = bits 10-11, none of the objects is part of the grid) and ran a
BFS with the objects ignored (they are all hidden or non-blocking after the
changes above). `#` = blocked, `.` = floor, `W` = warp, `C` = vanilla
coord event, `O` = object.

```
    012345678901234567890123456789012345
  0 ####################################
  1 ###O.....###########################
  2 ###......#####################O#####
  3 ########.###################...#####
  4 ####.O...C....O........COO....######
  5 ####.....C....O........OOC.....#####
  6 ####.#######################....####
  7 ###.....####################.....###
  8 ###.....####################......##
  9 ###.....####################......##
 10 ###.W..######################.######
 11 #############################..#####
 12 #############################...####
 13 #######################...#.....O###
 14 ######################..........####
 15 ##################..#...........####
 16 ##################....#......W..####
 17 ##################....##############
 18 #################....###############
 19 #################....###############
 20 #################.W.################
```

**Warp-in tile:** (4, 9). It is floor, directly above the west exit warp at
(4, 10); `OnWarp` turns the player north. (One tile above the exit, so the
first step down is not an accidental exit.)

**Walkable path to Giratina** (rocks hidden; 51 steps from (4, 9) to the tile
beside Giratina):

| Leg | Steps | Passes |
|---|---|---|
| (4, 9) north to (4, 5) | U4 | the small west room, then the corridor |
| east along row 5 to (28, 5) | R24 | trigger columns at x = 7, 16, 27; over (23, 5), (24, 5), (25, 5) where the boyfriend, rock and Wanda were |
| south to (28, 9) | D4 | into the east cavern |
| (29, 9) | R1 | |
| south to (29, 15) | D6 | past Mike's old row (13), past the east exit warp (29, 16) just below |
| west along row 15 to (21, 15) | L8 | |
| south to (21, 17) | D2 | trigger (21, 16) on the way |
| (20, 17), then (20, 18) | L1 D1 | |

Compressed: `U4 R24 D4 R1 D6 L8 D2 L1 D1`, then face west. (BFS output for the
tile *at* Giratina is 52 steps; the 51-step figure stops one tile short.)

**The last chamber** is rows 15-20, x = 17-21. Its only entrance is
(21, 15) down to (21, 16): (20, 15) and (22, 16) are blocked, and rows 17-20
are walled on the east, so the single trigger tile at (21, 16) cannot be
bypassed.

**Giratina's tile:** (19, 18) (floor; neighbors (18, 18), (20, 18), (19, 17),
(19, 19) are all floor). The player talks from (20, 18) facing west or
(19, 17) facing south. The south exit (18, 20) stays reachable around it
via (18, 18)-(18, 19).

**Exit tiles and where they lead.** All three warp events go to Rustboro via
the dynamic warp: **Rustboro (31, 9)**.

| Warp event | Tile | Vanilla leads to | Endgame leads to |
|---|---|---|---|
| 0 | (4, 10) | Route 116 | Rustboro (31, 9) |
| 1 | (29, 16) | Verdanturf Town | Rustboro (31, 9) |
| 2 | (18, 20) | Route 116 | Rustboro (31, 9) |

Rustboro (31, 9) was checked on `RustboroCity/map.bin`: floor, in the
town's north-east plaza beside the tunnel sign at (30, 8). Vanilla's
`VAR_RUSTBORO_CITY_STATE` triggers at (30, 9) and (31, 10) don't fire (that
var stays 0 in the endgame, per `RustboroCity_OnTransition`). The plaza
connects to the rest of the town; the sealed east edge (x = 39) is eight
tiles away.

**Other tiles named in this doc** (all checked as floor or as the object):

| Map | Tile |
|---|---|
| `RustboroCity_DevonCorp_3F` | scientist (17, 7), faces west; player talks from (16, 7) (stone is at (17, 5)) |
| `RustboroCity_PokemonCenter_1F` | girl (10, 6), faces east into a wall; player talks from (10, 5) facing south. The ABRA lands the player at (12, 5) |
| `RustboroCity_PokemonSchool` | lass (10, 8), flanked by walls at (10, 7) and (10, 9); player talks from (9, 8) or (11, 8) |
| `BattleFrontier_BattleArenaLobby` | Hoopa (11, 9); player talks from (11, 10) facing north |

**Darkness.** `setflashlevel 2` is radius 64 px on a 240 x 160 screen,
about four tiles; the same level as the Pike lair. The map header has
`requires_flash: false`, so `SetDefaultFlashLevel` clears to 0 on load and
the OnTransition value wins; a warp into any other map clears it again
(`gMapHeader.cave` is false there), so the exits need nothing. The level is
saved in the save block, so a save inside the tunnel stays dark on load
(the Pike lair relies on the same behavior).

---

## 4. All the dialogue, drafted in full

Rules: the player never speaks (narration, or NPCs echo). Every line below
is at most 193 px (limit 208, `{PLAYER}` as seven letters) and in the repo's
`.string` format, so it can be pasted. Pages use `\p`; the longer pages
scroll with `\l`, as the existing endgame scenes do. Tone: short, grounded,
a little wry; NPC names in capitals, places and Pokemon in capitals.

### 4.1 Rustboro Pokemon Center, the girl (phase 2, then phase 3)

```
RustboroCity_PokemonCenter_1F_Text_GirlTear:
	.string "My shadow was on the wrong side of\n"
	.string "me this morning. It pointed at the\l"
	.string "lamp instead of away from it.\p"
	.string "The floor tiles in here don't match\n"
	.string "the lights, either. Is that normal?$"

RustboroCity_PokemonCenter_1F_Text_GirlTearClosed:
	.string "My shadow behaves again!\p"
	.string "I almost miss it. It was the most\n"
	.string "interesting thing that ever\l"
	.string "happened to me.$"
```

### 4.2 Trainers' School, the lass

```
RustboroCity_PokemonSchool_Text_LassTear:
	.string "My big brother says RUSTURF TUNNEL\n"
	.string "goes upward now.\p"
	.string "It runs under a mountain! A tunnel\n"
	.string "can't go up and still come out the\l"
	.string "other side.\p"
	.string "He says he isn't joking. He looked\n"
	.string "a little green.$"

RustboroCity_PokemonSchool_Text_LassTearClosed:
	.string "My brother says RUSTURF TUNNEL goes\n"
	.string "down again, like a tunnel should.\p"
	.string "He seems a little disappointed.$"
```

### 4.3 Hoopa's hint (once, after Roxanne, until Giratina is caught)

```
BattleFrontier_BattleArenaLobby_Text_HoopaTear:
	.string "HOOPA reaches for a ring that isn't\n"
	.string "on its list. It buckles and snaps\l"
	.string "shut.\p"
	.string "HOOPA flinches and shakes its head.\n"
	.string "Something on the other side is\l"
	.string "angry.\p"
	.string "HOOPA points in the direction of\n"
	.string "RUSTBORO, and won't try again.$"
```

### 4.4 The Devon 3F scientist

The briefing (three messages, then the question):

```
RustboroCity_DevonCorp_3F_Text_TearBrief1:
	.string "{PLAYER}, good. You need to see\n"
	.string "these readings.\p"
	.string "Every ring HOOPA opens leaves a\n"
	.string "scar in space. The FACTORY blast\l"
	.string "left a bigger one.\p"
	.string "They should have healed by now.\n"
	.string "They haven't. They're growing.$"

RustboroCity_DevonCorp_3F_Text_TearBrief2:
	.string "The needles all lean the same way:\n"
	.string "east, toward RUSTURF TUNNEL.\p"
	.string "ROXANNE says the stone under it\n"
	.string "rings wrong, too. Two instruments\l"
	.string "that never met, agreeing.\p"
	.string "Something has come through the tear\n"
	.string "there. Something large, and still.$"

RustboroCity_DevonCorp_3F_Text_TearBrief3:
	.string "RUSTBORO's gates are sealed, but\n"
	.string "DEVON keeps a service shaft under\l"
	.string "the plant. It comes out in that\l"
	.string "tunnel.\p"
	.string "I can take you as far as the first\n"
	.string "bend, and no farther.$"

RustboroCity_DevonCorp_3F_Text_TearAsk:
	.string "Shall I take you to RUSTURF\n"
	.string "TUNNEL?$"
```

Later visits, a "no", the fade narration, and the closing line:

```
RustboroCity_DevonCorp_3F_Text_TearAskAgain:
	.string "The needles are still leaning east.\p"
	.string "Shall I take you to RUSTURF\n"
	.string "TUNNEL?$"

RustboroCity_DevonCorp_3F_Text_TearNotYet:
	.string "Of course. Come back when you're\n"
	.string "ready. The needles aren't going\l"
	.string "anywhere.$"

RustboroCity_DevonCorp_3F_Text_TearLed:
	.string "The scientist led {PLAYER} down a\n"
	.string "service shaft that is on no map.\p"
	.string "It ended in raw stone: RUSTURF\n"
	.string "TUNNEL.$"

RustboroCity_DevonCorp_3F_Text_TearClosed:
	.string "The needles went still all at once,\n"
	.string "about the time that tunnel stopped\l"
	.string "being strange.\p"
	.string "Whatever was in there, it's yours\n"
	.string "now. Keep that CORE close.\p"
	.string "I'd give a year's salary to read\n"
	.string "what it does to a POKéMON.$"
```

### 4.5 Rusturf Tunnel

Entry (first arrival only, `VAR_GIRATINA_EVENT` 1 to 2):

```
RusturfTunnel_Text_Enter:
	.string "The scientist stopped at the first\n"
	.string "bend and raised his lamp. It\l"
	.string "guttered out. His instruments went\l"
	.string "dead a moment later.\p"
	.string "“This is as far as I go,” he said.\n"
	.string "“Follow the tunnel east. Any way\l"
	.string "out will bring you back under\l"
	.string "RUSTBORO. Don't ask me how.”\p"
	.string "Then his footsteps were gone, and\n"
	.string "{PLAYER} was alone in the dark.\p"
	.string "Somewhere ahead, something was\n"
	.string "breathing, slowly.$"
```

The three wrongness moments, in walking order:

```
RusturfTunnel_Text_Shadow:
	.string "{PLAYER}'s shadow doesn't fall\n"
	.string "behind. It stretches ahead, long\l"
	.string "and thin, as if it knows the way.\p"
	.string "When {PLAYER} stops, it takes one\n"
	.string "more step.$"

RusturfTunnel_Text_Prints:
	.string "There are footprints in the dust.\n"
	.string "Small, fresh, the same tread as\l"
	.string "{PLAYER}'s own boots.\p"
	.string "They lead the way {PLAYER} is\n"
	.string "going. And they look newer the\l"
	.string "farther they go.$"

RusturfTunnel_Text_Writing:
	.string "Scratched into the rock, about\n"
	.string "eye height:\p"
	.string "“.KCAB OG”\p"
	.string "The letters are cut from right to\n"
	.string "left. The scratches are still\l"
	.string "bright.$"
```

(The shadow ties to the girl's clue, the tunnel that "goes upward" to the
lass's, and the backwards line is the "line said backwards". If the owner
would rather have an object that is back where it started, the Poke Ball
at (3, 1) is the obvious candidate; I kept this to text so nothing in the
map moves.)

The sighting and Giratina:

```
RusturfTunnel_Text_Sighting:
	.string "The tunnel opens into a narrow\n"
	.string "chamber. The dark is thicker here.\p"
	.string "Above the floor, where nothing\n"
	.string "should hang, something does: long\l"
	.string "and black, with golden spikes\l"
	.string "folded like broken wings.\p"
	.string "It casts no shadow. The stone\n"
	.string "around it is bent, like a glass\l"
	.string "seen through water.\p"
	.string "One red eye opens.$"

RusturfTunnel_Text_GiratinaFirst:
	.string "GIRATINA's eye holds {PLAYER}.\n"
	.string "The walls flex like skin.\p"
	.string "A voice with no sound fills the\n"
	.string "chamber.\p"
	.string "GIRATINA: …Another hand… in my\n"
	.string "world…\p"
	.string "Every door you tear lets my dark\n"
	.string "leak out.\p"
	.string "I was cast out once. I will not be\n"
	.string "cast out again.$"

RusturfTunnel_Text_GiratinaAgain:
	.string "GIRATINA hangs where it was, the\n"
	.string "red eye fixed on {PLAYER}.\p"
	.string "The tear hasn't closed. The dark\n"
	.string "still leaks out of it, cold.$"

RusturfTunnel_Text_GiratinaStays:
	.string "GIRATINA doesn't follow. The dark\n"
	.string "folds around it and goes still.\p"
	.string "It hasn't left. The tear hasn't\n"
	.string "closed.$"

RusturfTunnel_Text_BagFull:
	.string "GIRATINA waits in the dark. But\n"
	.string "{PLAYER}'s BAG is full.\p"
	.string "Whatever it leaves behind will need\n"
	.string "room. Make some first.$"
```

The catch and the Griseous Core (the item message comes from `giveitem`
between the two texts):

```
RusturfTunnel_Text_Caught:
	.string "The ball clicked shut.\p"
	.string "The dark let go of the chamber all\n"
	.string "at once. The walls stopped\l"
	.string "breathing.\p"
	.string "The tunnel brightened, and it was\n"
	.string "only a tunnel again.\p"
	.string "Something small rolled across the\n"
	.string "floor to {PLAYER}'s feet.$"

RusturfTunnel_Text_Core:
	.string "The GRISEOUS CORE is warm. It hums,\n"
	.string "the way GIRATINA's cry did.\p"
	.string "Held by GIRATINA, it will remember\n"
	.string "the world behind the world, the one\l"
	.string "it was born in.$"
```

Giratina speaks once, as telepathy (the "GIRATINA:" line, introduced by
"a voice with no sound"), as the plan allows; every other beat is narration.

---

## 5. Gossip (for the lead to add at integration)

One line, for a gossip NPC, after Giratina is caught (a pre-event version
isn't needed: the event is optional):

```
	.string "DEVON's needles all went still at\n"
	.string "once. Something under RUSTBORO\l"
	.string "finally calmed down, they say.$"
```

Per D9 this is an extra line in the existing gossip NPCs gated on
`FLAG_GIRATINA_CAUGHT`, not a new `GetStoryGossipStage` beat.

---

## 6. The harness plan: scenario 33 (`harness-giratina.c`)

Base: copy `~/decomps/headless-harness/harness-badD.c` (the newest copy,
scenarios 20-31) to `harness-giratina.c`, set `#define HARNESS_SCENARIO 33`
and `STORY_VAR VAR_GIRATINA_EVENT` for scenario 33, add 33 to the
`TxtWatch()` condition (as 29 and 31 have). Use a scratch folder, delete it
after. A New Game run, never the owner's save. **Plan once, run once** (the
memory note): the collision, trigger tiles and timing are all above.

### Additions the harness needs (small)

- `OP_PRESS_B` (answers a YES/NO with NO; the overworld Mash only presses A).
- Two battle-input flags in the style of `sLoseNext`: `sRunNext` (on the
  battle menu press RIGHT, DOWN, A) and `sBallNext` (before the battle,
  `gBagPosition.pocket = POCKET_POKE_BALLS`, cursor on the Master Ball; in
  the menu RIGHT, A, A, A). **This is untested**: no scenario has caught
  anything yet (the handoff notes Hoopa's catch was never run). If the bag
  keystrokes don't land in one planned attempt, fall back to checking the
  catch branch by running `RusturfTunnel_EventScript_GiratinaCaught`
  directly with a Giratina given by the harness, and say so in the report.
- New checks (numbers 3300 up), a `Setup` case per phase.

### Setup (New Game, then `OP_SETUP`)

`SetupCommon()`; `VarSet(VAR_ENDGAME_STATE, 10)`; `FlagSet(FLAG_ABRA_TO_RUSTBORO)`;
`GiveStrong(1, ITEM_NONE)` (Mewtwo with Flamethrower: hits Ghost/Dragon, PP
refilled); `AddBagItem(ITEM_MASTER_BALL, 1)`; `VarSet(VAR_GIRATINA_EVENT, 0)`.
Roxanne's flag is **clear** (setup 330) or **set**
(`FlagSet(TRAINER_FLAGS_START + TRAINER_ENDGAME_ROXANNE)`, setup 331). Setup
332 = hold the player at 1 HP and require `B_OUTCOME_LOST` for the next
battle (the memory note for must-lose fights). Setup 334 = state 18 for the
post-credits part (and clear the Giratina flags again).

### Part A: Roxanne unbeaten (state 10, var 0)

Everything must be invisible.

| Step | Check |
|---|---|
| `WARP_XY` Center (10, 5), face south, A | 3300: the vanilla "CUT down skinny trees" line, not "shadow" |
| `WARP_XY` School (9, 8), face east, A | 3301: the vanilla confusion line, not "upward" |
| `WARP_XY` Devon 3F (16, 7), face east, A | 3302: the old "Charge the CROWN" line; `VAR_GIRATINA_EVENT` still 0; still on 3F |
| `WARP_XY` Arena lobby (11, 10), face north, A | 3303: Hoopa's offer text, no "angry"; `FLAG_HOOPA_TEAR_HINTED` clear |

### Part B: Roxanne beaten (setup 331)

| Step | Check |
|---|---|
| Center girl, School lass | 3310: "shadow"; 3311: "upward" |
| Hoopa, twice | 3312: first talk has "angry" and sets the flag; the second (after `TXTRESET`) has the offer and no "angry" |
| Scientist (16, 7), A, mash to the question, `OP_PRESS_B` | 3313: "readings" and "ROXANNE" shown, var = 1, still on 3F, the "Come back" line |
| Scientist again (var 1, so the short offer), A, YES | 3314: map = Rusturf Tunnel, player (4, 9) facing north, `GetFlashLevel() == 2`, var = 2 after the entry text ("lamp") |
| `WALK` N4, E3 (to (7, 5)) | 3315: Briney hidden; mash to var 3; text has "shadow" |
| `WALK` E9 (to (16, 5)) | 3316: grunt and Peeko hidden; mash to var 4; text "footprints" |
| `WALK` E11 (to (27, 5)) | 3317: player x = 27 proves the way through; boyfriend, Wanda, both rocks hidden; mash to var 5; text "KCAB" |
| `WALK` E1, S4, E1, S6 (to (29, 15)); `WALK` W8 | 3318: at (29, 15) no battle has started and Mike (32, 13) is hidden |
| `WALK` S1 onto (21, 16) | 3319: sighting text, var = 6, Giratina present at (19, 18) (`ObjAt(OBJ_EVENT_GFX_SPECIES(GIRATINA))`), flash 2 |

Then four battles, talking from (20, 18) facing west:

| Battle | How | Checks |
|---|---|---|
| B1: lose | setup 332, `WALK` S1, W1, S1, face west, A, mash | 3320: first-contact text ("cast out"); outcome `B_OUTCOME_LOST`; white-out to Rustboro's Pokemon Center, party healed, items back; var = 7; flag clear; `GetFlashLevel() == 0` |
| Re-escort | `WARP_XY` Devon 3F (16, 7), A | 3321: the short offer ("still leaning east"), not the briefing; YES; in the tunnel at (4, 9), var still 7, no "lamp" text, flash 2. Then `WARP_XY` to (20, 18) as a shortcut (the full walk was tested once) |
| B2: knock out | A, mash (HP hack) | 3322: text "hangs where it was" then "doesn't follow"; Giratina still there; flag clear; no Core; var 7 |
| B3: run | `sRunNext` | 3323: `B_OUTCOME_RAN`; Giratina still there; flag clear |
| B4: catch | Master Ball | 3324: `FLAG_GIRATINA_CAUGHT`, var = 8, Core in bag, Giratina object gone, flash 0, Giratina in the party at level 60 with met location `MAPSEC_RUSTURF_TUNNEL`, `!IsFrontierChippedMon()` |

Exits (all three, short warps next to each):

| Step | Check |
|---|---|
| `WARP_XY` (4, 9), `WALK` S1 | 3325: map = Rustboro, (31, 9), flash 0 |
| `WARP_XY` (29, 15), `WALK` S1 | 3326: same |
| `WARP_XY` (18, 19), `WALK` S1 | 3327: same |

### Part C: caught

| Step | Check |
|---|---|
| Girl, lass | 3330: "behaves again"; 3331: "down again" |
| Scientist | 3332: "went still", no escort offered |
| Hoopa | 3333: no hint (flag was cleared in setup; Giratina caught suppresses it) |

### Part D: after the credits (setup 334: state 18, Roxanne beaten, var 0)

| Step | Check |
|---|---|
| `WARP_XY` Frontier Pokemon Center (12, 5), face east, A, mash (ABRA; Rustboro is first) | 3340: in Rustboro's Center at (12, 5) |
| `WARP_XY` Devon 3F (16, 7), A, YES | 3341: briefing shown, in the tunnel, flash 2 |

This is the ABRA-after-credits claim (section 7) turned into a check.

Failure paths covered: everything invisible before Roxanne (A); no repeat
narration on retries (B1-B3); a loss returns cleanly (B1); a run and a
knock-out leave Giratina (B2, B3); the bag-full guard is not run (needs a
full bag; say so in the report, or add a one-line setup that fills the bag).

---

## 7. Open questions and risks

### The post-credits ABRA finding: it still works

Read in `data/scripts/endgame_towns.inc`, `BattleFrontier_OutsideEast`,
`BattleFrontier_PokemonCenter_1F`, `RustboroCity_PokemonCenter_1F`:

- `FLAG_ABRA_TO_RUSTBORO` is set once (Steven, state 7) and **never
  cleared** anywhere.
- The ABRA menu (`EventScript_EndgameAbra`) depends only on the `FLAG_ABRA_TO_*`
  flags, not on `VAR_ENDGAME_STATE`. The Frontier's ABRA is shown by that flag
  alone (`SetupEndgameAbra`); Rustboro's Center ABRA has no hide flag.
- After the credits (state 18) `EndgameClear` continues the game at
  `HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST`, outside; nothing seals the
  Frontier's Pokemon Center.
- Rustboro's scripts only key on states 7 (allies) and 9 (Juan); the
  sealed-exit triggers are unconditional; Devon 1F-3F key only on trainer
  flags (the Elite Four stay beaten) and state 8/9 scenes that have passed.

So the event stays open after the credits, and gets harness check 3340-3341.
I have not run it. (D4 in the sprint plan says the same of the Gym.)

### Needs the lead's call

1. **A new hide flag for Hiker Mike** (`FLAG_HIDE_RUSTURF_TUNNEL_MIKE`,
   0x285). He is the only vanilla object with no hide flag, and the route
   crosses his sight line. *No-new-flag fallback:* give his object a local id
   and `settrainerflag TRAINER_MIKE_2` in `SetupEndgame`, so he never
   challenges; he'd stay in his corner with his vanilla post-battle line
   (harmless, off-tone).
2. **`wild_encounters.json`** (2.8) is outside "Owns". It is the same one
   deletion New Mauville got.
3. **Exits as `MAP_DYNAMIC` warps** (2.2) overwrite the tunnel's vanilla
   warps for good. The alternative that keeps vanilla (conditional exits)
   would need coord-event scripts on the three exit tiles; I judged it not
   worth it because nothing can reach Route 116 or Verdanturf in the endgame,
   and the vanilla story is to be stripped. The exit has no narration; the
   map-name popup ("RUSTBORO CITY") is the only cue that the tunnel let go.
4. **Experience farming.** Because Giratina stays after a knock-out or run,
   a strong team can knock it out repeatedly: Giratina's Experience yield is
   high, and the story rule allows Experience in the endgame. The Hoopa
   legends have the same property (they "flee" and the ring reopens). If it
   matters, a simple cap (for example, no Experience after the first
   knock-out) is a Phase 2 decision.
5. **Origin Forme in gauntlet battles.** The Core is a normal held item
   (`FORM_CHANGE_ITEM_HOLD`); I did not check whether any facility rule
   (the shop's species list, forms) lets Giratina-Origin in. Not this
   sprint's problem unless the lead wants it.

### Risks / assumptions I could not verify without running

- **Dynamic warp coordinates.** I read `ScrCmd_setdynamicwarp`,
  `SetDynamicWarpWithCoords` and `SetWarpDestinationToDynamicWarp`, and the
  Celadon/Lilycove precedent; with three arguments (`setdynamicwarp MAP,
  x, y`) the warp id is none and the coordinates are used. Harness checks
  3325-3327 cover it.
- **Darkness on screen.** Radius 64 px (level 2) is what the Pike lair uses
  and the Pike's darkness itself has not been looked at (the handoff says so).
  The tunnel's `WEATHER_FOG_HORIZONTAL` over the dark circle is unseen; if
  it looks bad, set `setweather WEATHER_NONE` in `SetupEndgame`.
- **Music.** The tunnel plays `MUS_PETALBURG_WOODS`, which is cozy. A
  different track for the endgame is a one-line `playbgm` change if the
  owner wants it.
- **The catch path in the harness** is untried (above).
- **Widths** used `{PLAYER}` = "BRENDAN"; a longer player name would be
  wider. Same assumption as `textwidth.py`.
- **Wrongness is text-only.** The shadow "takes one more step" is words, not
  a sprite effect. No object moves, so there is nothing to desync.
- **Difficulty.** Level 60 Giratina against the player's team has not been
  tuned; the catch rate is 3 (Master Ball and the 99 Ultra Balls in the base
  are the player's tools).
