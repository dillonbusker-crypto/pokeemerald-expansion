# Sprint B: Calyrex in Mauville, "The True King" (Phase 1 design)

Design only, 2026-10-08. Nothing in `src/`, `include/` or `data/` has been
changed. Everything here was read against the sprint branch
(`sprint/endgame-towns` at `2ebbf4d7e3`, "Sprint phase 0"), including the
reserved flags (`FLAG_CALYREX_CAUGHT` 0x283, `FLAG_MAUVILLE_STATUE_RESTORED`
0x284), `VAR_CALYREX_EVENT` 0x40FA and `TRAINER_ENDGAME_WATTSON` 991.

Read with `sprint-endgame-towns.md` (section 2B and decisions D3, D5, D7, D9).

---

## 0. The design in one screen

- **Where:** the lawn east of Mauville's Pokemon Center. The statue is an
  object at **(29, 6)** on `MauvilleCity`; the player examines it from (29, 7).
  Calyrex appears at (28, 7). All of these tiles are plain grass (`mt001`),
  walkable, no events, no objects, no collision (section 4).
- **How it is drawn:** objects, no metatile edits. Rubble is
  `OBJ_EVENT_GFX_BREAKABLE_ROCK`, the restored statue is
  `OBJ_EVENT_GFX_TRICK_HOUSE_STATUE`, Calyrex is `OBJ_EVENT_GFX_SPECIES(CALYREX)`.
  Three object entries appended to `MauvilleCity/map.json`, shown and hidden
  with `FLAG_TEMP_6/7/8` (free in Mauville; not aliased).
- **The gate:** `checktrainerflag TRAINER_ENDGAME_WATTSON` (the Gym rematch
  trainer flag), read live. Before it: the statue is plain rubble and the old man
  is vanilla. No state needs setting when Wattson falls.
- **The storyteller:** the Center's old man, through a **wrapper script** that
  only intercepts once Wattson is beaten, then falls through to the vanilla
  `MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan`. Important finding:
  that man is **not always the Storyteller** (section 3.2), so the wrapper has to
  work for all five types.
- **The restoration (my pick):** **the Replica Crown restores the statue.**
  Neither FP nor a New Mauville stone survives the evidence (section 1.3). The
  Crown already holds New Mauville's generator charge (state 14), so this is
  the "stone from the generator" idea with the trip removed, and it is the
  first thing Calyrex then calls a chain.
- **The steed and the fight:** Calyrex asks to see a Glastrier or Spectrier in
  the party. With one: a YES/NO, then `setwildbattle SPECIES_CALYREX, 60`,
  catchable. Without: a Calyrex line plus the old man's hint. Caught: the
  Reins of Unity, flags set, object gone. KO or run: Calyrex stays, retry.
- **The fusion** is the engine's own (`ItemUseCB_Fusion`, `src/party_menu.c`):
  Bag, Key Items, Reins, then Calyrex, then the steed. It removes the steed from
  the party into the PC struct's fusion storage. Never used in this project;
  section 6 lists what to test.
- **Code outside map files:** two lines in `src/facility.c` (the chip
  exception). Nothing else in `src/`.

---

## 1. State machine, and the three decisions

### 1.1 `VAR_CALYREX_EVENT`

| Value | Meaning | Set by | What the world shows |
|---|---|---|---|
| 0 | Nothing done | start | Rubble object (from `VAR_ENDGAME_STATE` 15). Wattson not beaten: "plain rubble", old man vanilla. Wattson beaten: "cracked crown, someone might remember" and the old man starts the legend on the next talk |
| 1 | Legend heard | old man's first telling | Rubble offers the restoration (YES/NO). Old man offers to retell |
| 2 | Statue restored, Calyrex stands by it but has not spoken | the restoration scene (also sets `FLAG_MAUVILLE_STATUE_RESTORED`) | Restored-statue object plus Calyrex. Normally the scene runs straight on to state 3; state 2 is only seen if the game is reset mid-scene |
| 3 | Calyrex has spoken and asked for a steed | Calyrex's first speech | Talk to Calyrex: no steed gives the NoSteed line; a steed gives YES/NO, then the fight. Old man: steed hint, or "go on" |
| 4 | Caught, Reins given (also `FLAG_CALYREX_CAUGHT`) | the catch scene | Statue stays restored, Calyrex object gone. Old man offers the ending of the tale |

The reserved flags: `FLAG_MAUVILLE_STATUE_RESTORED` is set in the same
breath as state 2 and `FLAG_CALYREX_CAUGHT` with state 4. **The scripts branch
on the var only**; the flags are mirrors for the lead's gossip, the harness and
any later system.

No state is "unlocked": the Wattson gate is read live
(`goto_if_not_defeated TRAINER_ENDGAME_WATTSON`).

Visibility rule (written in `OnTransition`, section 3.1):

| Object | Hide flag | Shown when |
|---|---|---|
| Rubble | `FLAG_TEMP_6` | `VAR_ENDGAME_STATE >= 15` and `VAR_CALYREX_EVENT < 2` |
| Restored statue | `FLAG_TEMP_7` | `VAR_ENDGAME_STATE >= 15` and `VAR_CALYREX_EVENT >= 2` |
| Calyrex | `FLAG_TEMP_8` | `VAR_ENDGAME_STATE >= 15` and `VAR_CALYREX_EVENT` is 2 or 3 |

Temp flags are cleared on every warp and camera transition
(`ClearTempFieldEventData`, `src/overworld.c`), then `OnTransition` runs, so
the script must set all three hides every load and clear the right ones.
After a wild battle the map is not reloaded, so in-script `addobject` and
`removeobject` carry the change.

### 1.2 Stays open after the credits

Nothing in the design reads `VAR_ENDGAME_STATE` above "at least 15". At 16, 17
and 18 the statue, the old man and Calyrex all work the same. The only
dependency outside my files is that the player can reach Mauville
(`FLAG_ABRA_TO_MAUVILLE` is never cleared) and that Wattson's trainer flag
stays set. Workstream A is checking the ABRA network after state 18.

### 1.3 The restoration choice: the Replica Crown

The two options in the plan both fail on evidence:

- **Pay FP: FP is a dead currency by state 15.**
  `FLAG_FRONTIER_SHOP_FREE` is set at the Arena base (`src/facility_shop.c`
  line 84 returns price 0), and FP only comes from gauntlet wins (900 per clear,
  `shop-spec.md`) plus a few story gifts of 300. Re-entry after a clear is not
  allowed. So the player's balance at state 15 is whatever they left over, with
  no way to earn more. A price either costs nothing in practice or **soft-locks
  a player who spent down to zero**, which D5 says optional content must never
  do.
- **A stone from New Mauville's generator room: the player cannot get there.**
  Wattson leads the player down only at state 13
  (`MauvilleCity_EventScript_EndgameWattson`), the entrance is on sealed Route
  110 water, and from state 14 the exit leads back to the Center. Reopening it
  means editing `MauvilleCity`'s endgame scene, `NewMauville_Entrance` and
  `NewMauville_Inside`, all of which the lead asked me not to disturb.

**Pick: the Replica Crown does it.** The Crown was supercharged at that very
generator (state 14, `GetReplicaCrownLimit`); the old man's tale says "a
crown is mended by a crown held to it by someone who remembers"; the player
holds the Crown to the break. Why this is the right shape:

1. **No new systems and no soft-lock.** The Crown is a key item the player
   always has. The gate is knowledge (hear the legend) plus Wattson.
2. **It is the plot.** The counterfeit Crown does the mending, so Calyrex,
   who has just been mended by it, is the one who can say what it really is:
   "That is no crown. It is a chain."
3. **It gives the old man a job.** He is the only place the player learns that
   the Crown is the key.

**Fallback if the lead or owner insists on FP:** change only the YES branch of
`MauvilleCity_EventScript_RestoreStatue` to

```
	special FacilityShopGetFP
	goto_if_lt VAR_RESULT, 300, MauvilleCity_EventScript_RestoreTooPoor
	setvar VAR_0x8004, 300
	special FacilityShopTakeFP
```

plus one extra text. I advise against it for the reason above. If it is used,
put a floor under it (a clamp to what the player has, or free if they have under
the price).

---

## 2. The statue: placement and drawing

Chosen spot, **(29, 6)**, the middle of the grass lawn between the Pokemon
Center (door at (22, 5)) and the Bike Shop. It is four tiles from the ABRA at
(25, 6), so a player stepping out of the Center or off the ABRA sees it at once.

```
        26 27 28 29 30 31 32          '.' walkable grass, 'o' object slot
   5     .  .  .  .  .  .  .          S  statue/rubble  (29, 6)
   6     .  .  .  S  .  .  .          C  Calyrex       (28, 7)
   7     .  .  C  p  .  .  .          p  player examines from (29, 7)
   8     road (mt101)
```

Why here and not elsewhere: the middle of the town (x 15-17, y 5-9) is the
N-S path crossing the road and carries a woman NPC and a grunt slot; x 21-25
is the arrival area and the Center scenes (Wattson at (21, 8), Steven (21, 7),
Wallace (23, 7), the Aqua grunt at (24, 10), the ABRA); x 13-19 y 0-4 is the
sealed route exit. The lawn at x 26-32, y 5-7 has only the ABRA to its west and
two grunt slots (27, 7) and (31, 8) hidden from state 14 by `FLAG_TEMP_4`.

Alternative the lead may prefer: the one-tile alcove at (29, 3)-(29, 4) just
north of the lawn (a gap in the trees, collision-free, no events). Moving the
statue to (29, 4) and standing at (29, 5) makes a little shrine; change `y` in
three map entries and nothing else. I kept the open lawn because it has four
approach tiles and no way to be blocked.

### Objects added to `data/maps/MauvilleCity/map.json`

Append, do not insert: local IDs are generated as index + 1 (`mapjson.cpp`), so
appending leaves every existing `LOCALID_*` unchanged. There are 24 objects
now, so these become 25, 26, 27 (the cap is 64 templates and 16 spawned
objects; at state 15 the lawn spawns at most about 12).

| local_id | graphics_id | x, y | movement | script | flag |
|---|---|---|---|---|---|
| `LOCALID_MAUVILLE_STATUE_RUBBLE` | `OBJ_EVENT_GFX_BREAKABLE_ROCK` | 29, 6 | `MOVEMENT_TYPE_LOOK_AROUND` | `MauvilleCity_EventScript_StatueRubble` | `FLAG_TEMP_6` |
| `LOCALID_MAUVILLE_STATUE` | `OBJ_EVENT_GFX_TRICK_HOUSE_STATUE` | 29, 6 | `MOVEMENT_TYPE_LOOK_AROUND` | `MauvilleCity_EventScript_StatueWhole` | `FLAG_TEMP_7` |
| `LOCALID_MAUVILLE_CALYREX` | `OBJ_EVENT_GFX_SPECIES(CALYREX)` | 28, 7 | `MOVEMENT_TYPE_FACE_RIGHT` | `MauvilleCity_EventScript_Calyrex` | `FLAG_TEMP_8` |

(elevation 3, range 0, `TRAINER_TYPE_NONE`, `"0"` trainer id, like every
other object on the map.)

The rubble and the statue share a tile; only one is ever shown, so there is no
collision overlap. Both graphics were checked: the Rock Smash rock is a 16x16
inanimate sprite (palette `NPC_1`), the statue a 16x32 gray figure (palette
`NPC_4`), already used by Mossdeep Gym. **They are stand-ins**: a toppled
statue drawn as a rock is a stretch, and a standing statue is a small gray
person. If the owner wants real art later it is one `graphics_id` per row.

---

## 3. Every script change, by map and label

Files touched in Phase 2: `data/maps/MauvilleCity/map.json`,
`data/maps/MauvilleCity/scripts.inc`,
`data/maps/MauvilleCity_PokemonCenter_1F/map.json`,
`data/maps/MauvilleCity_PokemonCenter_1F/scripts.inc`, `src/facility.c` (two
lines). Nothing else. No new flags, vars, constants, specials or items.

### 3.1 `MauvilleCity/scripts.inc`

**`MauvilleCity_OnTransition`**: one added line after
`call MauvilleCity_EventScript_SetupEndgame`:

```
	call MauvilleCity_EventScript_SetupCalyrex
```

All new labels go in one block appended at the end of the file, under a header
comment, so the endgame scenes above it are untouched.

```
@ ============================================================================
@ Ten Gauntlets: CALYREX, "The True King" (sprint-b-calyrex.md).
@ VAR_CALYREX_EVENT: 0 nothing, 1 the old man's legend heard, 2 the statue
@ restored, 3 CALYREX has asked for a steed, 4 caught. Gated on the GYM
@ rematch (TRAINER_ENDGAME_WATTSON). FLAG_TEMP_6 rubble, 7 statue, 8 CALYREX.
@ ============================================================================

MauvilleCity_EventScript_SetupCalyrex::
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	goto_if_lt VAR_ENDGAME_STATE, 15, Common_EventScript_NopReturn
	goto_if_ge VAR_CALYREX_EVENT, 2, MauvilleCity_EventScript_ShowRestoredStatue
	clearflag FLAG_TEMP_6
	return

MauvilleCity_EventScript_ShowRestoredStatue::
	clearflag FLAG_TEMP_7
	call_if_lt VAR_CALYREX_EVENT, 4, MauvilleCity_EventScript_ShowCalyrex
	return

MauvilleCity_EventScript_ShowCalyrex::
	clearflag FLAG_TEMP_8
	return

@ The rubble. Not beaten WATTSON: nothing. Beaten: a hint, and once the legend
@ is heard (state 1) the restoration.
MauvilleCity_EventScript_StatueRubble::
	lockall
	goto_if_not_defeated TRAINER_ENDGAME_WATTSON, MauvilleCity_EventScript_RubbleBare
	goto_if_eq VAR_CALYREX_EVENT, 1, MauvilleCity_EventScript_RestoreStatue
	msgbox MauvilleCity_Text_RubbleCracked, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_EventScript_RubbleBare::
	msgbox MauvilleCity_Text_RubbleBare, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_EventScript_RestoreStatue::
	msgbox MauvilleCity_Text_RestorePrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_RestoreLater
	msgbox MauvilleCity_Text_StatueMends, MSGBOX_DEFAULT
	closemessage
	playse SE_M_TELEPORT
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_MAUVILLE_STATUE_RUBBLE
	addobject LOCALID_MAUVILLE_STATUE
	setflag FLAG_MAUVILLE_STATUE_RESTORED
	setvar VAR_CALYREX_EVENT, 2
	fadescreen FADE_FROM_WHITE
	delay 30
	msgbox MauvilleCity_Text_WindRises, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	addobject LOCALID_MAUVILLE_CALYREX
	fadescreen FADE_FROM_WHITE
	applymovement LOCALID_MAUVILLE_CALYREX, Common_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_CALYREX, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox MauvilleCity_Text_CalyrexAppears, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_CalyrexSpeaks
	end

MauvilleCity_EventScript_RestoreLater::
	msgbox MauvilleCity_Text_RestoreLater, MSGBOX_DEFAULT
	releaseall
	end

@ The restored statue, in every state from 2 on.
MauvilleCity_EventScript_StatueWhole::
	lockall
	msgbox MauvilleCity_Text_StatueWhole, MSGBOX_DEFAULT
	releaseall
	end

@ CALYREX. State 2: its first words (a reset mid-scene lands here). State 3:
@ the steed check.
MauvilleCity_EventScript_Calyrex::
	lock
	faceplayer
	goto_if_eq VAR_CALYREX_EVENT, 2, MauvilleCity_EventScript_CalyrexSpeaks
	goto MauvilleCity_EventScript_CalyrexSteedCheck
	end

MauvilleCity_EventScript_CalyrexSpeaks::
	msgbox MauvilleCity_Text_CalyrexVoice, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexCrown1, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexCrown2, MSGBOX_DEFAULT
	setvar VAR_CALYREX_EVENT, 3
	msgbox MauvilleCity_Text_CalyrexSteed, MSGBOX_DEFAULT
	goto MauvilleCity_EventScript_CalyrexSteedCheck
	end

MauvilleCity_EventScript_CalyrexSteedCheck::
	checkspecies SPECIES_GLASTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_EventScript_CalyrexHasSteed
	checkspecies SPECIES_SPECTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_EventScript_CalyrexHasSteed
	msgbox MauvilleCity_Text_CalyrexNoSteed, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexHasSteed::
	msgbox MauvilleCity_Text_CalyrexSees, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_CalyrexWaits
	@ Checked before the fight, so the REINS always fit (as with DARKRAI's item).
	checkitemspace ITEM_REINS_OF_UNITY
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_EventScript_CalyrexBagFull
	closemessage
	playmoncry SPECIES_CALYREX, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CALYREX, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MauvilleCity_EventScript_CalyrexCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MauvilleCity_EventScript_CalyrexStands
	msgbox MauvilleCity_Text_CalyrexRan, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexWaits::
	msgbox MauvilleCity_Text_CalyrexWaits, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexBagFull::
	msgbox MauvilleCity_Text_CalyrexBagFull, MSGBOX_DEFAULT
	release
	end

@ Knocked out: it stays, at full strength next time. Same for a run.
MauvilleCity_EventScript_CalyrexStands::
	msgbox MauvilleCity_Text_CalyrexStands, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CalyrexCaught::
	setflag FLAG_CALYREX_CAUGHT
	setvar VAR_CALYREX_EVENT, 4
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_MAUVILLE_CALYREX
	fadescreen FADE_FROM_WHITE
	msgbox MauvilleCity_Text_CalyrexCaught, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexThanks, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_CalyrexReins, MSGBOX_DEFAULT
	giveitem ITEM_REINS_OF_UNITY
	msgbox MauvilleCity_Text_CalyrexReinsHow, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_StatueBlooms, MSGBOX_DEFAULT
	release
	end
```

Notes on the script above:

- Outcomes. `B_OUTCOME_CAUGHT` and `B_OUTCOME_WON` are handled; **everything
  else** (ran, teleported, the wild mon fled) is the run line and leaves
  Calyrex there. A loss (`B_OUTCOME_LOST`) never returns to the script: it
  whites out to Mauville's Center (`setrespawn` is set from state 12), and the
  event is where it was.
- `dowildbattle` (as the Island Cave's Hoopa legends do) rather than
  `BattleSetup_StartLegendaryBattle`. Either works; the legendary start adds a
  blur transition and the legend music. Optional polish, noted in section 9.
- Nothing hides Calyrex after a KO or run: `removeobject` is only in the catch
  path, so the object remains and `OnTransition` keeps showing it at states 2-3.
- Rubble at state 2+ is never shown, so `StatueRubble` has no branch for it.
- The statue never clears `FLAG_TEMP_6` while restored, because
  `OnTransition` only clears it for states 0 and 1.

### 3.2 `MauvilleCity_PokemonCenter_1F`

**Finding that changes the plan:** the old man is not always the Storyteller.
`SetMauvilleOldMan` (`src/mauville_old_man.c`) picks one of five men from the
last digit of the player's trainer ID (Bard, Hipster, Trader, Storyteller,
Giddy), and `SetMauvilleOldManObjEventGfx` gives all of them `OBJ_EVENT_GFX_BARD`.
So only about one New Game in five has an actual Storyteller, and the sprite is
the Bard's whichever it is. The legend must therefore be added in front of
**all five**, not inside the Storyteller script.

**Approach: a wrapper, with no edit to `data/scripts/mauville_man.inc`.**
`MauvilleCity_PokemonCenter_1F/map.json`: the old man's object (the one with
`OBJ_EVENT_GFX_VAR_0` at (2, 3)) changes its `script` from
`MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan` to
`MauvilleCity_PokemonCenter_1F_EventScript_OldMan`. The new script jumps to the
vanilla one on every path except the new ones, so the Bard's songs, the
Storyteller's records, the Trader and the rest still work exactly as before
(`OnTransition` is unchanged and still sets his graphics).

```
@ Ten Gauntlets: the old man tells the legend of the KING OF BOUNTIFUL
@ HARVEST once WATTSON is beaten (sprint-b-calyrex.md). Whichever of the five
@ MAUVILLE men he is, this goes first; everything else is the vanilla script.
MauvilleCity_PokemonCenter_1F_EventScript_OldMan::
	goto_if_not_defeated TRAINER_ENDGAME_WATTSON, MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	lock
	faceplayer
	switch VAR_CALYREX_EVENT
	case 0, MauvilleCity_PokemonCenter_1F_EventScript_OldManTell
	case 1, MauvilleCity_PokemonCenter_1F_EventScript_OldManRetell
	case 2, MauvilleCity_PokemonCenter_1F_EventScript_OldManRetell
	case 3, MauvilleCity_PokemonCenter_1F_EventScript_OldManSteed
	case 4, MauvilleCity_PokemonCenter_1F_EventScript_OldManEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManTell::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManIntro, MSGBOX_DEFAULT
	setvar VAR_CALYREX_EVENT, 1
	goto MauvilleCity_PokemonCenter_1F_EventScript_OldManTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManRetell::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	goto MauvilleCity_PokemonCenter_1F_EventScript_OldManTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManTale1, MSGBOX_DEFAULT
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManTale2, MSGBOX_DEFAULT
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManTale3, MSGBOX_DEFAULT
	release
	end

@ State 3: the king needs a steed.
MauvilleCity_PokemonCenter_1F_EventScript_OldManSteed::
	checkspecies SPECIES_GLASTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_OldManSteedGo
	checkspecies SPECIES_SPECTRIER
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_OldManSteedGo
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManSteedHint, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_OldManSteedGo::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManSteedGo, MSGBOX_DEFAULT
	release
	end

@ State 4: the end of the tale, which says how to use the REINS. NO is the
@ vanilla man.
MauvilleCity_PokemonCenter_1F_EventScript_OldManEnd::
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManEndAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan
	msgbox MauvilleCity_PokemonCenter_1F_Text_OldManEpilogue, MSGBOX_DEFAULT
	release
	end
```

Design points:

- **First telling is automatic** (state 0 plays the intro and the whole tale
  with no yes/no), so a player can never decline their way past the one
  clue. Later talks offer the retelling and let NO fall through to the vanilla
  man, who is why `OldManRetell` and `OldManEnd` end in `MauvilleOldMan`.
- States 3 does not fall through to the vanilla man (the hint is the whole
  point). It is the only state where he blocks his vanilla self, and it ends as
  soon as Calyrex is caught.
- The old man's talk at state 1-2 needs no steed check; the steed hint is
  state 3 only, because the player does not know they need one until Calyrex
  says so.
- The man wanders left and right on row 3 (x 1-3, `MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT`,
  range 1). Harness note in section 8.

### 3.3 `src/facility.c` (two lines)

`IsFrontierChippedMon` (line 628). Insert after the blank line that follows
`u32 metLocation = GetMonData(...)` and **before** the `if
(FlagGet(FLAG_FRONTIER_CHIPS_OFF))` line:

```
    if (metLocation == MAPSEC_MAUVILLE_CITY)
        return FALSE;
```

Reasoning: workstream A is editing the `return` line below
(`metLocation != MAPSEC_ARTISAN_CAVE && metLocation != MAPSEC_ISLAND_CAVE` plus
Rusturf Tunnel). Putting mine in separate lines **above** it, with an unchanged
line between, merges cleanly with A's change instead of conflicting on the same
line. The strictly "one line" version is
`&& metLocation != MAPSEC_MAUVILLE_CITY` appended to that return, which will
conflict with A's edit by one line at the merge.

Honest note: this has no effect in practice. Chips are off from state 11
(`FLAG_FRONTIER_CHIPS_OFF`), and the event only opens at 15, so a caught
Calyrex is unchipped either way. It keeps the rule honest (D5), as the plan says.

### 3.4 What I did not touch

`MauvilleCity` endgame scene labels (`SetupEndgame`, `ArrivalScene`,
`CenterScene`, the Wattson and grunt scripts), the Gym, `NewMauville_*`,
`data/scripts/endgame_towns.inc`, `include/*`, the gossip functions (section 7).

---

## 4. Map check

Method: read `data/layouts/MauvilleCity/map.bin` (40 x 20, 2 bytes per tile,
collision bits 10-11, elevation bits 12-15) and
`data/layouts/PokemonCenter_1F` for the Center, and every event in the two
`map.json` files. The renderer (`factory/render_lib.py`, `LAYOUT_MAUVILLE_CITY`)
shows the lawn as plain grass.

### MauvilleCity, every tile I use

| Tile | Role | Metatile | Collision | Elevation | Events there |
|---|---|---|---|---|---|
| (29, 6) | statue / rubble | `mt001` (grass, behavior 0) | 0 | 3 | none; no object, warp, trigger or sign |
| (29, 7) | player examines (facing up) | `mt001` | 0 | 3 | none |
| (28, 6), (30, 6), (29, 5) | other examine tiles | `mt001` | 0 | 3 | none |
| (28, 7) | Calyrex appears | `mt001` | 0 | 3 | none; the nearest object is the Magma grunt at (27, 7), hidden by `FLAG_TEMP_4` from state 14 |
| (22, 7) to (28, 7) | the walk from the Center for the harness | `mt108`, `mt10a`, `mt001` | 0 | 3 | Steven (21, 7), Wallace (23, 7): hidden by `FLAG_TEMP_2/3` from state 14. Nothing else on row 7 |
| (29, 3), (29, 4) | the alcove (alternative site) | `mt001` | 0 | 3 | none; (29, 2) is blocked, so a dead-end |

Rows 5 to 7 are `mt001` collision 0 elevation 3 for x = 26 to 32; row 8 is the
road (`mt101`), row 9 (`mt111`/`mt05e`). I printed these tiles from the file.

Event overlap: `bg_events` are at (23, 5), (24, 5), (11, 6), (24, 14), (25, 14), (19, 7),
(33, 6), (11, 15); warps at (8, 5), (22, 5), (35, 5), (23, 14), (32, 14),
(8, 13), (19, 14); the only `coord_events` are the 50-odd sealed-exit triggers
along the map edge (y 0 and 19, x 0 and 39). **None is within five tiles of the
statue.**

Flags the map already uses: `FLAG_TEMP_1` Wattson, `_2` Steven, `_3` Wallace,
`_4` the grunts (plus `VAR_TEMP_1` for the two scenes and `VAR_TEMP_F` for the
sealed exits). `FLAG_TEMP_6/7/8` are free here. Checked elsewhere in the tree:
`FLAG_TEMP_5` is read by the League lighting (`src/field_specials.c:5691`), so
I skipped it; nothing in `src/` touches 6, 7 or 8. `9/A/B/E/10+` are the aliased
engine flags and are not used. (The Island Cave uses 5 and 6 on its own map.)

### MauvilleCity_PokemonCenter_1F

The old man is at (2, 3) with `WANDER_LEFT_AND_RIGHT`, range x 1, y 0: he walks
x 1-3 on row 3. Collision on rows 2 to 4, x 0-3 is all 0 (`mt218/219/279/27a`,
`mt220/226/234/202`, row 4 `mt202`), so he can be reached from (x, 4) below,
(x, 2) above, or the sides. No events nearby (no coord or bg events on the map;
the exit warps are at (6, 8) and (7, 8), the stairs at (1, 6)). The Center is
the endgame respawn point, so the old man is where a defeated player lands.

---

## 5. All dialogue

Rules followed: the player never speaks (they are narrated or the NPC speaks to
them); Calyrex speaks only through telepathy, shown as curly-quoted lines
introduced by narration; no `--` or `...`; Pokemon, items and places in
capitals, like the other endgame scenes. Every line was measured with the
`textwidth.py` font table (`{PLAYER}` as BRENDAN): **widest segment 195 px of
208, none over.** Phase 2 must recheck the real diff.

Text goes in the same files as the scripts (map texts in `MauvilleCity`, the
old man's in the Center).

### The rubble and the statue (`MauvilleCity`)

```
MauvilleCity_Text_RubbleBare:
	.string "A heap of broken stone lies in the\n"
	.string "grass, scorched and trampled.$"

MauvilleCity_Text_RubbleCracked:
	.string "A statue lies in pieces in the grass.\n"
	.string "Its crown is cracked clean through.\p"
	.string "Whoever he was, he was somebody\n"
	.string "once. Someone in town might\l"
	.string "remember.$"

MauvilleCity_Text_RestorePrompt:
	.string "The broken crown has a clean seam,\n"
	.string "as if it were waiting for a mate.\p"
	.string "Hold the REPLICA CROWN to the break?$"

MauvilleCity_Text_RestoreLater:
	.string "{PLAYER} lowered the CROWN. The\n"
	.string "stone lay still.$"

MauvilleCity_Text_StatueMends:
	.string "{PLAYER} held the REPLICA CROWN to\n"
	.string "the break in the stone.\p"
	.string "Its light ran into the crack like\n"
	.string "rain into a dry field.\p"
	.string "The pieces ground together. The\n"
	.string "crown closed, and the statue stood\l"
	.string "whole.$"

MauvilleCity_Text_StatueWhole:
	.string "A stone king stands on the lawn,\n"
	.string "his crown whole. Wildflowers have\l"
	.string "opened around the base.$"
```

### The old man's legend (`MauvilleCity_PokemonCenter_1F`)

```
MauvilleCity_PokemonCenter_1F_Text_OldManIntro:
	.string "Trainer! You came from the GYM, did\n"
	.string "you? Then you've heard WATTSON's\l"
	.string "favorite story: the stone on the\l"
	.string "lawn.\p"
	.string "He built a whole town around a king\n"
	.string "and never learned the king's name.\p"
	.string "Sit. I'll tell you. Hardly anyone\n"
	.string "asks anymore.$"

MauvilleCity_PokemonCenter_1F_Text_OldManTale1:
	.string "Long ago, before MAUVILLE, before\n"
	.string "any road, a king ruled a land of\l"
	.string "fields.\p"
	.string "They called him the KING OF\n"
	.string "BOUNTIFUL HARVEST. Where he walked,\l"
	.string "the grain stood tall and the\l"
	.string "flowers opened.\p"
	.string "He rode a great steed, white as\n"
	.string "frost or dark as shade. No storm or\l"
	.string "army stood against the two of them.$"

MauvilleCity_PokemonCenter_1F_Text_OldManTale2:
	.string "But a king lives by being\n"
	.string "remembered. The harvests came and\l"
	.string "came, and the people forgot whom to\l"
	.string "thank.\p"
	.string "The crops still grew. The king grew\n"
	.string "faint, and faded, steed and all.\p"
	.string "The people carved his likeness in\n"
	.string "stone, to say they were sorry.\p"
	.string "That's the stone on the lawn.\n"
	.string "A crown cracks when its king is\l"
	.string "forgotten.$"

MauvilleCity_PokemonCenter_1F_Text_OldManTale3:
	.string "They say it mends the same way:\n"
	.string "when a crown is held to the break\l"
	.string "by someone who remembers.\p"
	.string "Funny. I hear you carry a crown of\n"
	.string "your own. It couldn't hurt to try.$"

MauvilleCity_PokemonCenter_1F_Text_OldManAgain:
	.string "Shall I tell the tale of the KING\n"
	.string "OF BOUNTIFUL HARVEST again?$"
```

### Calyrex appears and speaks (`MauvilleCity`)

```
MauvilleCity_Text_WindRises:
	.string "A warm wind crossed the lawn,\n"
	.string "though the air had been still.$"

MauvilleCity_Text_CalyrexAppears:
	.string "At the statue's side, where there\n"
	.string "had been nothing, a small king\l"
	.string "stood. CALYREX.$"

MauvilleCity_Text_CalyrexVoice:
	.string "A voice settled into {PLAYER}'s\n"
	.string "mind, soft and old. It had no\l"
	.string "mouth to speak it.\p"
	.string "“I felt my likeness mend. Someone\n"
	.string "remembered me, after so many\l"
	.string "seasons.”$"

MauvilleCity_Text_CalyrexCrown1:
	.string "“You carry a crown.”\p"
	.string "“No. Look closer, and it is not.”\p"
	.string "“That is no crown. It is a chain.”$"

MauvilleCity_Text_CalyrexCrown2:
	.string "“Thousands of bonds are wound into\n"
	.string "it. None were given. All were\l"
	.string "taken.\p"
	.string "“It lent its light to mend my\n"
	.string "stone, and for that I thank you.\p"
	.string "“But a crown is a weight carried\n"
	.string "for others. A chain only binds.”$"

MauvilleCity_Text_CalyrexSteed:
	.string "“I am faint. The harvest forgot me,\n"
	.string "and I forgot how to rise.\p"
	.string "“A king does not walk alone. Show\n"
	.string "me the steed you trust: the white\l"
	.string "steed of frost, or the dark steed\l"
	.string "of shade.”$"
```

"None were given. All were taken" is on purpose: the Replica Crown was charged
by the siphon, which drained the shard energy out of every chipped Pokemon
(storyline, "The Frontier siphon"). Calyrex is right about its origin and, as
the thanks line says, wrong about the hand.

### The steed check, the fight and the catch (`MauvilleCity`)

```
MauvilleCity_Text_CalyrexNoSteed:
	.string "“You have no steed with you.\n"
	.string "Without one, I cannot rise, and\l"
	.string "you cannot be measured.\p"
	.string "“The old teller of tales, in the\n"
	.string "house of healing, remembers where\l"
	.string "such steeds are kept.”$"

MauvilleCity_Text_CalyrexSees:
	.string "“A steed walks with you. I know\n"
	.string "that stride.\p"
	.string "“Then let me see how you ride, and\n"
	.string "what you do with a chain in your\l"
	.string "hand.”$"

MauvilleCity_Text_CalyrexReady:
	.string "“Are you ready to be measured?”$"

MauvilleCity_Text_CalyrexWaits:
	.string "“Then ready yourself, {PLAYER}.\n"
	.string "I am in no hurry.”$"

MauvilleCity_Text_CalyrexBagFull:
	.string "CALYREX waits, but {PLAYER}'s BAG is\n"
	.string "full.\p"
	.string "Whatever the king gives will need\n"
	.string "room. Make some first.$"

MauvilleCity_Text_CalyrexStands:
	.string "CALYREX swayed, then rose again as\n"
	.string "if the grass itself held it up.\p"
	.string "“Not yet, {PLAYER}. Come back when\n"
	.string "you are ready.”$"

MauvilleCity_Text_CalyrexRan:
	.string "“You turn from the trial. I will\n"
	.string "wait. Kings are good at it.”$"

MauvilleCity_Text_CalyrexCaught:
	.string "The ball closed on CALYREX without\n"
	.string "a struggle, calm and unhurried.\p"
	.string "It had not been bound. It had\n"
	.string "chosen.$"

MauvilleCity_Text_CalyrexThanks:
	.string "“I will ride with you, {PLAYER}.\p"
	.string "“I judged the chain. I should have\n"
	.string "judged the hand that held it.\p"
	.string "“You stood the trial, and you\n"
	.string "never asked me to bow.”$"

MauvilleCity_Text_CalyrexReins:
	.string "“Take the REINS. They bind a king\n"
	.string "to his steed in trust, not in\l"
	.string "chains.”$"

MauvilleCity_Text_CalyrexReinsHow:
	.string "“Use them on me and my steed, and\n"
	.string "we are one. Use them again, and we\l"
	.string "part.”$"

MauvilleCity_Text_StatueBlooms:
	.string "The stone king stood whole on the\n"
	.string "lawn. Around its feet, wildflowers\l"
	.string "had opened in the bare grass.$"
```

### The old man afterwards (`MauvilleCity_PokemonCenter_1F`)

```
MauvilleCity_PokemonCenter_1F_Text_OldManSteedHint:
	.string "A king without his steed is half a\n"
	.string "harvest.\p"
	.string "The steed of frost, GLASTRIER, and\n"
	.string "the steed of shade, SPECTRIER, are\l"
	.string "sold on the island, at the exchange\l"
	.string "counter.\p"
	.string "Bring either, and the king will see\n"
	.string "you.$"

MauvilleCity_PokemonCenter_1F_Text_OldManSteedGo:
	.string "Ah, there's a steed at your side.\n"
	.string "The king is waiting on the lawn.$"

MauvilleCity_PokemonCenter_1F_Text_OldManEndAsk:
	.string "Shall I tell how the tale ends?$"

MauvilleCity_PokemonCenter_1F_Text_OldManEpilogue:
	.string "So the king rides again. Not as\n"
	.string "anyone's prisoner. That's the right\l"
	.string "end for a harvest king.\p"
	.string "About those REINS: use them from\n"
	.string "your BAG on the king and his steed,\l"
	.string "and the two become one. Use them\l"
	.string "again to part them.\p"
	.string "Keep a spot free in your party,\n"
	.string "mind. The steed needs somewhere to\l"
	.string "stand.$"
```

Facts the text relies on, verified: Glastrier is wave 5 (550 FP) and Spectrier
wave 6 (1400 FP) in `src/facility_shop.c`, both free once
`FLAG_FRONTIER_SHOP_FREE` is set, so by state 15 the player can take either
from the Exchange Service Corner at no cost. Calyrex is not in the shop or in
any Hoopa ring (grep'd), so this event is its only source.

### Voice and beats, in a line each

The old man is warm, a little teasing, and the only one who knows the crown
can be mended. Calyrex is gentle and formal and sees the Crown for what it is,
but it is not cruel: it thanks the player in the same breath as the rebuke, and
by the end it admits it judged the chain and not the hand. The trial is
a measure of the hand.

---

## 6. The fusion

**The Reins of Unity** (`ITEM_REINS_OF_UNITY`, `src/data/items.h:14637`) are a
key item with `ITEM_USE_PARTY_MENU` and `ItemUseOutOfBattle_Fusion`; they are
never consumed. The Calyrex fusion table is
`sCalyrexFusionTable` (`src/data/pokemon/form_change_tables.h:2030`), wired in
`gFusionTablePointers` for Calyrex, Glastrier, Spectrier, Calyrex-Ice and
Calyrex-Shadow. `P_FUSION_FORMS` and `P_FAMILY_CALYREX/GLASTRIER/SPECTRIER` are
on. No script in this project calls it.

**How the player uses it** (read from `ItemUseCB_Fusion` and
`Task_TryItemUseFusionChange`, `src/party_menu.c` 6278-6720):

1. **Fuse.** Bag, Key Items, REINS OF UNITY, USE. The party menu opens. Pick
   **Calyrex first** (it is `targetSpecies1`), and the game asks for the
   second Pokemon ("choose second fusion mon"). Pick **Glastrier or Spectrier**.
   The steed is copied into `gPokemonStoragePtr->fusions[3]` and **removed from
   the party** (party shrinks by one), Calyrex becomes Calyrex-Ice or
   Calyrex-Shadow with recalculated stats, the mosaic animation and cry play,
   "CALYREX transformed!", and it learns **Glacial Lance** or **Astral Barrage**
   (the replace-a-move prompt if it already has four moves, which a fresh
   level-60 Calyrex always does).
2. **Unfuse.** Same item, pick the fused Calyrex only. **Needs a free party
   slot** ("Your party's full" otherwise). The steed comes back into the first
   free slot, moves the base form cannot learn are deleted (Glacial Lance or
   Astral Barrage goes), and if that leaves it with no moves it learns
   Confusion.
3. **Swapping horses** (D7): unfuse, then fuse with the other steed. Only one
   fusion can exist at a time (both table rows use storage slot 3).
4. **Wrong picks** ("won't have any effect"): the steed picked first, a non-pair
   second mon, a second fused mon.

**What must be tested** (nothing in this project has used it; the code is
upstream expansion's):

- One fusion with Glastrier and one unfusion, the species, the party size, the
  storage slot, the stats and the moves each way (harness, section 8).
- **The learn-move prompt** when Calyrex has four moves. The harness removes a
  move to take the clean path; the four-move prompt (YES, pick a move to
  forget, or NO) needs one **hand test**, as do Spectrier, a full party on unfuse,
  and a save and reload while fused.
- The Reins are reachable from the bag in this build (the Crown, another
  `ITEM_USE_PARTY_MENU` key item, already works from the same pocket).
- **Side effects of the steed leaving the party:** it cannot be sold, boxed or
  used in a gauntlet while fused. The Frontier siphon, Transfer EXP and the
  Crown's Mega limit read the party only; none of them look at fusion storage.
- Calyrex is `isFrontierBanned` and `isRestrictedLegendary` in its species data.
  After gauntlet 8 the gauntlets are not re-enterable, so this does not matter
  for the event, but the owner should know if Calyrex is meant to be usable in
  any later facility mode.

A caught Calyrex goes to the **party if there is room, else the PC**. Many
endgame parties are six full (the Crown allows six Megas), so the likely path
is "sent to the PC", and the player has to withdraw it before fusing. The
epilogue line "keep a spot free" covers unfusing only. I did not add a party
check before the fight (it would block most players until they box something);
section 9 lists it as a choice.

---

## 7. Gossip, and Wattson's lead (for the lead)

**Gossip (D9), one line, ungated by Wattson (the rubble is visible from state
15).** Suggested for the existing `GOSSIP_MAUVILLE_FREED` line of one gossip NPC
(for example appended to `OldaleTown_House2_Woman_Gossip14`, after the CHANSEY):

```
	.string "My grandson says the old stone king\n"
	.string "on MAUVILLE's lawn lies in pieces.\p"
	.string "The old man at the CENTER swears he\n"
	.string "knows the story behind it.$"
```

**Wattson's post-battle lead (workstream C's text; suggestion only so the two
line up).** What my events need from it: that Wattson built Mauville around a
stone king on the lawn by the Center, that the teams knocked it down, that
he never knew whose likeness it was, and that the old man in the Center tells
tales. A draft that fits:

```
	.string "WATTSON: Wahahahaha! Shocking!\p"
	.string "I built this town around an old\n"
	.string "stone king on the lawn by the CENTER.\l"
	.string "AQUA and MAGMA knocked him flat.\p"
	.string "I never learned whose likeness he\n"
	.string "was. The old man at the CENTER\l"
	.string "tells tales. Ask him.$"
```

The old man's intro ("you've heard WATTSON's favorite story") and the rubble
line ("someone in town might remember") both assume the player has been told
this. If C writes it differently, change those two, and nothing else.

**What C must guarantee:** the win sets `TRAINER_ENDGAME_WATTSON`'s trainer flag
(any `trainerbattle_*` does; a hand-rolled scripted battle must call the flag
setter), and the flag is never cleared (no rematch after a win, as planned).

---

## 8. The harness plan: scenario 34

File `~/decomps/headless-harness/harness-calyrex.c`, a copy of the newest
base, **`harness-lucy.c`** (scenario 32, 2026-10-07; it has 25, which `harness.c`
also has), with a `HARNESS_SCENARIO == 34` step table. Each harness copy runs in
its own scratch folder and is deleted afterward (sprint rule); `textwidth.py`
hard-codes `ROOT` to the main checkout, so in Phase 2 it must be pointed at the
worktree, or it will check the wrong tree.

`STORY_VAR` for 34 is `VAR_CALYREX_EVENT` (so `OP_MASH_UNTIL_STATE` works on
it). Runs are a New Game; the harness copy needs
the usual patches (`harness.c` notes) and no extras.

### Setup

`Setup(340)` common: `SetupCommon`, then `VAR_ENDGAME_STATE 15`,
`FLAG_ABRA_TO_RUSTBORO`, `_MAUVILLE`, `FLAG_FRONTIER_SHOP_FREE`,
`FLAG_CROWN_CHARGED`, `FLAG_FRONTIER_CHIPS_OFF`, `ITEM_REPLICA_CROWN`,
`gauntletsCompleted = 0xFF`, party **four Mewtwo** with Nature's Madness (as in
scenario 23) and **no steed**, `VAR_CALYREX_EVENT 0`, **Wattson not beaten**.

- `341`: set Wattson's flag (`FlagSet(TRAINER_FLAGS_START + TRAINER_ENDGAME_WATTSON)`).
- `342`: add a **Glastrier** (level 50) to the party (five mons), and one
  **Master Ball** as the only ball. Leave a free slot for the catch.
- `343`: drop Calyrex's fourth move (`SetMonMoveSlot(..., MOVE_NONE, 3)`) so
  the fusion takes the no-prompt path.
- Battle modes (`sBattleMode`): FIGHT (the existing mash and HP hack, a KO),
  RUN, CATCH. Foe HP stays hacked to 1 (not god mode for the player).

### Steps and checks (one planned run)

Coordinates are all verified free (section 4). Numbers are the `OP_CHECK` ids.

| Step | Do | Check |
|---|---|---|
| 1 | `Setup 340`; warp `MAUVILLE_CITY` (22, 6); wait idle | **3400**: rubble object active at (29, 6) (gfx `BREAKABLE_ROCK`); **no** statue and no Calyrex object active; `FLAG_TEMP_6` clear, `_7` and `_8` set |
| 2 | Walk DOWN 1, EAST 7 to (29, 7); face UP; A; mash | **3401**: `gStringVar4` equals `MauvilleCity_Text_RubbleBare` (the Wattson gate) and `VAR_CALYREX_EVENT` still 0. The invisible-before-Wattson path |
| 3 | Warp into the Center with Wattson **not** beaten; talk to the old man | **3402**: the vanilla man ran: `VAR_CALYREX_EVENT` 0 and the text is not `OldManIntro`; log `Script_GetCurrentMauvilleMan` for the record |
| 4 | `Setup 341`; reload the lawn; examine the rubble | **3403**: text is `RubbleCracked`; state 0; no YES/NO offered |
| 5 | Old man talk | **3404**: state 1, `OldManTale3` shown |
| 6 | Rubble, **NO** to the prompt | **3405**: text `RestoreLater`, state 1, rubble still there |
| 7 | Rubble, YES (mash); no steed | **3406**: state 3; `FLAG_MAUVILLE_STATUE_RESTORED` set; statue object at (29, 6), rubble gone, Calyrex at (28, 7); text `CalyrexNoSteed` |
| 8 | Talk to Calyrex (from (29, 7) facing LEFT), no steed | **3407**: not in battle; text `CalyrexNoSteed`; state 3 |
| 9 | Old man, no steed | **3408**: text `OldManSteedHint` |
| 10 | `Setup 342`; old man | **3409**: text `OldManSteedGo` |
| 11 | Calyrex, YES, **RUN** | **3410**: outcome `B_OUTCOME_RAN`; Calyrex object still there; state 3; `FLAG_CALYREX_CAUGHT` clear; text `CalyrexRan` |
| 12 | Calyrex, YES, **FIGHT** (KO) | **3411**: `B_OUTCOME_WON`; Calyrex still there; state 3; text `CalyrexStands` |
| 13 | Calyrex, YES, **CATCH** with the Master Ball | **3412**: `B_OUTCOME_CAUGHT`; `FLAG_CALYREX_CAUGHT` set, state 4; Calyrex object gone; `ITEM_REINS_OF_UNITY` in the bag; party has a level-60 Calyrex (slot 5, met location `MAPSEC_MAUVILLE_CITY`) |
| 14 | Clear `FLAG_FRONTIER_CHIPS_OFF` | **3413**: `IsFrontierChippedMon` is FALSE for the caught Calyrex and TRUE for a Mewtwo (the control), then set it back. Tests the `src/facility.c` line |
| 15 | Reload the lawn; examine the statue; reload the Center; old man YES | **3414**: statue object active, rubble and Calyrex not; text `StatueWhole`; the old man's text is the epilogue |
| 16 | **Fusion**: `Setup 343`; Start, Bag, Key Items, REINS, USE; pick Calyrex; pick Glastrier | **3415**: Calyrex is `SPECIES_CALYREX_ICE`; party size 5; `fusions[3]` is Glastrier (level > 0); Calyrex knows `MOVE_GLACIAL_LANCE` |
| 17 | **Unfusion**: Reins again, pick Calyrex-Ice | **3416**: `SPECIES_CALYREX` and `SPECIES_GLASTRIER` both in the party (size 6); `fusions[3].level == 0`; Glacial Lance gone |

To reach the Reins in step 16 the harness writes `gBagPosition` (key items
pocket and cursor) the way the choose-three menu writes `gSelectedOrderFromParty`,
and sets `gPartyMenu.slotId` before each A, rather than counting cursor
presses. The Start menu is opened by pressing START and moving to BAG.

### Planning notes

- **The old man wanders** along row 3 (x 1-3), so a fixed tile is a 1-in-3
  coin flip. Either freeze him in the harness (`movementType =
  MOVEMENT_TYPE_FACE_LEFT` and reset his sprite's type-function index; check by
  reading `event_object_movement.c` first), or start the script directly with
  `ScriptContext_SetupScript(MauvilleCity_PokemonCenter_1F_EventScript_OldMan)`.
  Either is deterministic; the first tests the real interaction.
- **The catch** needs the battle UI driven: in `BattleMainCB2` press RIGHT then
  A (the BAG), in the bag press A twice (first ball, USE) with `gBagPosition`
  pointing at the ball pocket and the Master Ball as the only ball, and once
  `gBattleOutcome == B_OUTCOME_CAUGHT` the nickname prompt needs DOWN then A (NO).
  The existing `Mash()` mixes DOWN pulses that would walk off a one-item bag, so
  this needs its own mode. **If the bag path misbehaves on the first run, fall
  back to forcing the outcome:** set `gBattleOutcome` and add the mon in a
  hook, which still tests every script branch after the catch, not the catch.
- **RUN** presses DOWN, RIGHT, A repeatedly (the cursor sticks on RUN). Mewtwo
  at level 100 outruns a level-60 Calyrex, so the escape is certain.
- Compare text with `gStringVar4` against the label (strings with no
  placeholders), which identifies which branch ran without parsing the log.
- Checks 3412 and 3416 are the ones to read the log for; the rest are state.

Expected log: `BOOT DONE`, a `MAP` line for each warp, `STATE` lines on
`VAR_CALYREX_EVENT` 1, 2, 3, 4, `BATTLE 1/0` three times, `EXIT 0`.

---

## 9. Open questions and risks

1. **The restoration pick is outside the plan's two options.** My reasons are
   in 1.3 (FP is a dead currency from state 15; New Mauville cannot be
   reached). If the lead wants FP regardless, the fallback is five lines. I
   would not take the stone route.
2. **The storyteller is a minority.** One New Game in five has a true
   Storyteller; the old man is a Bard-looking man in every game. The wrapper
   handles all five and keeps the vanilla man on every other path, but the
   plan's phrase "the storyteller" should read "the old man" in the owner's
   notes. The text calls him neither.
3. **Wattson's flag.** The whole event hangs on `TRAINER_ENDGAME_WATTSON` being
   set by C's win and never cleared. Confirm at integration (a test: win the
   fight, walk to the lawn).
4. **The art is stand-in.** A rock for the rubble and a gray figure for the
   statue (section 2). Cheap to replace; the owner should look at it in a real
   playthrough. Also unchecked until then: that the 32x32 Calyrex overworld
   sprite sits right on one tile (the Abra is smaller; the OW species sprites
   are the expansion's own) and that no object palette is missing (the harness
   `OP_LOGOBJS` lists active objects but cannot show a wrong colour).
5. **Calyrex into a full party goes to the PC**, which is the common case
   here, and the player then has to withdraw it before fusing. Options: leave
   it (my default), or check `getpartysize` before the fight and say "make room"
   like the bag check. I left it, because most endgame parties are full.
6. **The fusion is untested in this project** (section 6): the learn-move
   prompt, the party-full unfuse, Spectrier, and a save and reload while
   fused need a hand test. The steed disappears into the PC struct while
   fused, which is a surprise for a player who goes looking for it; the
   epilogue explains the Reins, not that.
7. **Calyrex is `isFrontierBanned` and a restricted legendary** in its
   species data; it only matters if the owner wants it usable in a facility.
8. **`dowildbattle` or the legendary start.** Plain `dowildbattle` is what
   the Island Cave's legends use, so I matched it. `special
   BattleSetup_StartLegendaryBattle` plus `waitstate` (Sky Pillar) gives the
   legend music and transition for the same fight; it is a one-line
   change if the owner wants the fanfare.
9. **A knock-out leaves Calyrex at full health next time**, as a new wild
   battle does; there is no chip damage carry-over. As D5 intended.
10. **`textwidth.py` points at the main checkout**, not the worktree. Phase 2
    must change `ROOT` (or run it from a copy) or its "over-wide: 0" proves
    nothing.
11. **Text and talk count.** The first telling of the tale is three message
    boxes with no choice; the dialogue is long. If the owner wants it shorter,
    `OldManTale1-3` are independent boxes and can be cut to two.
12. **Spawned-object count** at state 15 on the lawn is about 12 of 16. The
    harness `OP_LOGOBJS` after the restore will confirm nothing is dropped.
13. **Sequence with the other workstreams:** `facility.c` (the chip line
    above; A edits the neighbouring line), and the gossip insert at
    integration. C's Wattson text (section 7). That is all the cross-talk.

### What I verified and what I assumed

**Verified by reading the sprint branch**: the map's events and tiles (every
tile in section 4, from the `.bin`), the temp-flag use, the engine's fusion
code and table, the item, the old man's code and the five-man split,
`checkspecies`, `checktrainerflag` and `goto_if_not_defeated`, the macros I use
(`goto_if_ge`, `call_if_lt`, `giveitem`, `checkitemspace`, `playmoncry`),
local-ID generation, FP and the free-shop flag, shop waves for the steeds, the
absence of Calyrex elsewhere, the text widths, and that `ClearTempFieldEventData`
runs before `OnTransition`.

**Assumed, not run** (nothing was built or run in this phase): that the
Rock Smash rock and the Trick House statue look acceptable as rubble and a
statue; that `fadescreen` white flashes around `addobject` look right; that the
catch UI path in the harness works as described; that the Calyrex OW sprite
and its `faceplayer` work (the Abra's do); the fusion behaviour end to end;
and that `LOCALID_*` names resolve as the map-json generator describes.

**Note on the branch:** my worktree started on the upstream tip, without the
Phase 0 files. I first read them from `git archive sprint/endgame-towns`, then
(on the lead's go-ahead) fast-forwarded this branch onto
`sprint/endgame-towns` (`2ebbf4d7e3`). The design commit sits directly on top.

---

## 10. Phase 2 checklist (when approved)

1. Branch from `sprint/endgame-towns`, commit before starting.
2. `MauvilleCity/map.json`: append the three objects (section 2).
3. `MauvilleCity/scripts.inc`: the one `call` line, then the appended block and
   texts (3.1, 5).
4. `MauvilleCity_PokemonCenter_1F/map.json`: the old man's `script`;
   `scripts.inc`: the wrapper block and texts (3.2, 5).
5. `src/facility.c`: the two lines (3.3).
6. Build (`make -j$(nproc)`); the generated `LOCALID_MAUVILLE_*` names exist;
   `make check` stays at 15 known failures.
7. Widths via `textwidth.py` with `ROOT` fixed.
8. Harness scenario 34 as planned, one run, then delete the scratch folder.
9. Report: files, checks passed, anything skipped, and the hand-test list
   (the learn-move prompt, Spectrier, a full-party unfuse, save and reload
   while fused, the art on screen).
