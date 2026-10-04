# Session handoff — 2026-10-04

Read `CLAUDE.md` first, then `storyline.md`. This file covers what the last
two sessions built, what's untested, and the tools left behind.

---

## Commits (newest first)

| Commit | What |
|---|---|
| `611920777c` | Opening: vanilla lines flavored to fit the story (small hints, no reveals) |
| `dd3ebcfa8d` | Townsfolk gossip that follows the story (`GetStoryGossipStage`) |
| `e79e71c30f` | Full dialogue pass: the player never speaks; contradictions fixed |
| `5f78b4cb0b` | Fix: tag battles overwrote party slots with the wrong Pokémon |
| `6b9bfa5124` | FP rewards scale from gauntlet 4; Second Wind, trader and psychic priced in "wins" |
| `cd43993e58` | Broker's letter: Wallace and the trip to Ever Grande (+ Wallace's back sprite) |
| `78b842b8f7` | Built "the Crown is taken", the event after gauntlet 7 |

Nothing is pushed: GitHub auth in WSL is still not set up. Local `master`
is 51 commits ahead of `origin/master`.

The owner has playtested in mGBA: the Ever Grande event (found the tag-battle
bug below) and the whole Littleroot event after gauntlet 7 ("runs clean").

---

## 1. Tag-battle bug (fixed, `5f78b4cb0b`)

The owner's slot-4 Miraidon came back from the Ever Grande tag battle as a
copy of their slot-2 Landorus.

**Cause:** the expansion's `multi_*` macros call `AreMultiPartiesFullTeams()`
before `BattleSetup_StartMultiBattle` sets the battle type, so it read the
*previous* battle's flags. Without `BATTLE_TYPE_TRAINER` it answered "full
teams": the party was never cut to the three chosen, and the write-back after
the battle copied party slots 1–3 over the chosen slots.

**Fix:** `SetMultiTrainerBattle` (`src/battle_setup.c`) now sets the battle
type the check needs. Maxie and Archie at Ever Grande are also `Multi Party:
Half` in `trainers.party`. **Any future tag battle where the player picks
three needs `Multi Party: Half` on both opponents.**

The owner's save still has the duplicate Landorus; the lost Miraidon can be
re-taken from the TEMP ferry-dock man (no one-time flag). The Devon Agents tag
battle (Littleroot, after gauntlet 5) had the same risk and is covered by the
same fix, but wasn't harness-tested.

## 2. Dialogue pass (`e79e71c30f`)

All ~18,000 words of project dialogue were read end to end.

- **The player never speaks.** No `{PLAYER}: ...` lines and no first-person
  "I should..." blockers. Narrate ("{PLAYER} asked SCOTT why...",
  "{PLAYER} decided to go home first.") or have the NPC echo it ("He dropped
  a letter? For me?"). This is the owner's standing rule (also in memory).
- Contradictions fixed: Wardens are Scott's (not Anabel's); the florist's
  Leafeon timing; Steven's gauntlet-7 call no longer says he's still tracking
  the Broker (Looker already found him in the Factory); Steven learns the
  badges are fakes because the player says their father called them that;
  Hall of Eight plaques 7–8 use gauntlet names; the FP tip; "LINK MULTI mat"
  is "the fourth mat"; Scott threatens to "squash" Norman (endgame callback).
- Flow: Steven's gauntlet-2 goodbye now comes after the player agrees to help
  (the only script-order change); the narrator says the player shows him the
  Scrambler; POKéNAV spelling; Tucker no longer says "crown".

## 3. Gossip that follows the story (`dd3ebcfa8d`)

`GetStoryGossipStage` (special, `src/facility.c`) turns the gauntlet count and
the Birch/Broker/Crown state vars into one beat, `GOSSIP_*` in
`include/constants/facility.h`:

ARRIVAL, NORMAN, STEVEN, SYSTEM_DOWN, SMUGGLER, ANABEL, LAB, AFTER_LAB, SQUAD,
ARREST, PALACE, RAID, TAKEN, STANDOFF, ALL_CLEAR.

Twenty NPCs `switch` on it and fall back to their usual line. Each gets a
`<Prefix>_GossipN` script and `<Prefix>_Text_GossipN` text right after its
own script:

- **Frontier, east:** TriathleteM (the Scott-watcher, pays off "I've never
  once seen him battle"), Gentleman, RichBoy (the busybody).
- **Frontier, elsewhere:** OutsideWest Man1 and Man2, Lounge 4 Cook, the
  Pokémon Center School Kid (now tells the "crying in the cave... then
  nothing" rumor; marked ✅ in `storyline.md`).
- **Oldale:** House 2 grandmother (her grandson calls from the Frontier, so
  Oldale hears Frontier news), Girl, Mart Employee, Footprints Man.
- **Littleroot:** Boy, Twin, Fat Man (only between arcs; they stay indoors
  during each), and Birch's wife indoors (`RivalsHouse_1F_EventScript_RivalMom`).

**When a new story event is built, give it a beat and update the gossip.**
The endgame after gauntlet 8 currently maps to ALL_CLEAR, which shares the
STANDOFF lines.

## 4. The opening (`611920777c`)

Light hints only, nothing about chips, the harvest or the Crown. Birch's intro
speech mentions bond research; the TV report says the Gyms went quiet since the
gauntlets opened; Mom says Birch works day and night and knows the POKéNAV is
Devon's; the rival does Birch's fieldwork because he never leaves the lab;
Birch on Route 101 was coming back from a meeting (matches the aide); Oldale's
mart has little stock; a Route 103 NPC points at the ferry dock.

---

## Testing status

| What | Status |
|---|---|
| Tag-battle fix | Harness: Ever Grande win and loss paths with six different species picked 1,4,3; party intact. Reproduced the bug without the fix |
| Dialogue pass, gossip, opening | Built, widths checked against the font. **Not played** |
| Gossip stage logic | Code-read only. Worth checking a few NPCs at different story points |
| Broker's-letter event as a whole | Never hand-tested (Ever Grande part now played) |
| Crown event visuals | Littleroot part hand-tested by the owner; the Factory standoff (Dialga sprite, shake, flash) not yet confirmed |
| Price changes (wins) | Built and code-read, not run |

---

## Tools: `~/decomps/headless-harness/`

- `harness.c`: scripted-input driver. `#define HARNESS_SCENARIO n` (1 Palace
  exit, 2 Littleroot win path, 3 Noland/Greta loss, 4 Scott's house + Factory
  + Lati, 5 girl's house, 6 Ever Grande win, 7 Ever Grande loss, 8 League Abra
  home). Scenarios 6 and 7 now use six different species and pick slots 1,4,3,
  and log the party before and after (`LogParty`).
- `main.c.patch`, `script.c.additions`, `text.c.additions`: apply to a
  **copy** of the repo, never the real one.
- `render_map.py`, `textwidth.py` (checks added `.string` lines in `git diff`
  against real font widths, limit ~208 px).

How to run: rsync the repo to the scratchpad **excluding `build/`** but **not**
`*.gba` (`data/mb_*.gba` are build inputs). `touch .histignore`, `patch -p0 <
main.c.patch` from the copy's root. The two `.additions` files start with
their source file's original last lines: append only from the `Harness_`
functions on. Drop in `harness.c` as `src/harness.c`, `make`, then
`tools/mgba/mgba-rom-test -S 3 -R r0 -l 15 pokeemerald.gba`, piped through
`grep --line-buffered "GBA Debug"`. Runs take a few minutes.

Gotchas: runs are always a New Game (never the owner's save); watch the right
story var (`STORY_VAR`); text speed fast, battle style Set; in the choose-three
menu write `gSelectedOrderFromParty`, set `gPartyMenu.slotId = PARTY_SIZE`,
press only A; use `gMain.inBattle` for in-battle menus; a silent log with no
TICK lines means the game froze. **Party checks need distinct species and an
out-of-order pick**, or a wrong write-back looks identical.

---

## Loose ends

- **`TEMP` Miraidon** on the ferry dock (commit `ad68c3ceb0`): revert before
  release.
- **Open pricing questions:** should the Arena's 100 FP mock battle be priced
  in wins too? Should early service prices have a floor (Second Wind is 150
  FP in gauntlets 1–2)?
- The Factory lobby still has gauntlet-6 "Assembly Line" text, but the door
  never unlocks (`FACILITY_DOOR_FACTORY` is never set), so it's unreachable.
- `~/decomps/wallace-backsprite-for-artist/` can be deleted.
- Trainer IDs: 967 used of 1000. Don't raise `MAX_TRAINERS_COUNT`.

## Permanent Megas (built after this handoff was written)

The engine rule and the Replica Crown item are built and tested
(`storyline.md`, "Permanent Megas"). The Crown works only once
`FLAG_CROWN_CHARGED` is set, which the planned Frontier siphon scene must do.
Not yet hand-tested in mGBA (no scene gives the item yet).

## The Devon Factory (built after this handoff was written)

The Battle Factory's interior is rebuilt as Devon's facility, four new maps
(`storyline.md`, "The Devon Factory"). Harness scenario 10 walks it: locked
door and hidden Joy, then unlocked, every staircase, the sealed Pillar
stairs, Scott. **Not hand-played**; use the debug menu (R + START, warp).
The maps come from `~/decomps/headless-harness/factory/` (ASCII plans + an
auto-tiler + stamps cut from vanilla maps); its `render_lib.py` also fixes
`render_map.py`'s gTileset_General and FRLG rendering.

**`make check` baseline:** 15 known failures, all from deliberate project
changes (Experience off, save layout grown, one vanilla item description).
Any count above 15 is new.

## Next

The endgame after gauntlet 8. Open design questions first (`storyline.md`,
"Still to decide"): the Brains' upgraded teams, the Elite Four's teams,
Scott's Kangaskhan replacement, Steven's PokéNav, how the Broker gets out of
the Factory. (The permanent-Mega question is answered: built, see above.)
