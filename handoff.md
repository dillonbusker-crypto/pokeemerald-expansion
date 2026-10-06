# Handoff — current state (2026-10-05)

Read `CLAUDE.md` and `project-guide.md` first. This file is where the work
stands: what's built, what's tested, what's loose, what's next, and the test
harness. History is in `git log`; the story is in `storyline.md`.

---

## Where things stand

- **All eight gauntlets, the shop and the run loop** are built.
- **The story is built through endgame part 2**: everything up to and
  including the events after gauntlet 7, the after-gauntlet-8 Factory
  sequence and the Arena base, and Rustboro (`storyline.md`, "After gauntlet
  8: the Factory" ✅, "Hoopa's rings" ✅, "Rustboro: Devon Corporation" ✅).
- **The endgame's teams** in `endgame-teams.md` are built: the five Brain
  rematches and the Elite Four.
- **64 commits are local only.** Pushing from WSL isn't set up.

## Next: endgame part 3, the Frontier siphon

`storyline.md`, "Back to the Frontier: the siphon". Part 2 ends with Juan's
apology outside Devon: `VAR_ENDGAME_STATE` = 10, the player holds the
uncharged `ITEM_REPLICA_CROWN`, and Hoopa's second ring is open. Steven and
Wallace are nowhere at the Frontier yet (the base allies stay hidden from
state 7 on, and Steven is on Devon 3F only at state 9). Part 3 needs:

- Steven and Wallace back outside the Arena (or wherever the siphon scene
  wants them) from state 10.
- The Pokémon keeper's **"Free the POKéMON"** option in the Exchange Service
  Corner: the flash, `FLAG_CROWN_CHARGED`, and **the chips off** (a flag
  `IsFrontierChippedMon()`, `src/facility.c`, checks first).
- **The Crown's limit:** one permanent Mega after the siphon, six after New
  Mauville (a story var `ITEM_REPLICA_CROWN`'s use checks; see
  `storyline.md`, Technical notes, "Permanent Megas").
- Steven, Wallace and Nurse Joy's lines; Steven starting Mauville and
  `FLAG_ABRA_TO_MAUVILLE`.
- A gossip beat after `GOSSIP_DEVON_FREED`.

After that: New Mauville (Wattson, the admins, Archie and Maxie's Primals,
six permanent Megas), the Chansey's level 100, Sky Pillar and the final
battle. Open questions are in `storyline.md`, "Still to decide".

---

## Endgame part 2 in brief

Rustboro, tracked by `VAR_ENDGAME_STATE` 7-10 (listed in `RustboroCity`'s
scripts).

| Piece | Where |
|---|---|
| The ABRA lands in Rustboro's Pokémon Center, beside the town's ABRA | `RustboroCity_PokemonCenter_1F`, `endgame_towns.inc` |
| Steven and Wallace block Devon's door; talking starts the Wardens' ambush (off-screen) | `RustboroCity` (state 7 → 8) |
| Elite Four, in order, each leaves when beaten; a loss whites out to the Center | Devon 1F (Sidney, Phoebe), 2F (Glacia, Drake) |
| Stone's confession, the scientist, `ITEM_REPLICA_CROWN` | Devon 3F (state 8 → 9) |
| Juan's apology as the player comes out; Hoopa's second ring | `RustboroCity` (state 9 → 10), `GetHoopaRingsLeft` |
| Devon's staff hidden; the letter, PokéNav, Exp. Share and fossils off | Devon 1F-3F |
| Gossip: `GOSSIP_DEVON_FREED` (state 10 on) | `GetStoryGossipStage`, four new lines |

The Elite Four (`TRAINER_DEVON_*`, 974-977) are plain trainer battles, not
Frontier battles: their real levels, and held items restored afterwards
like every story fight.

---

## Endgame part 1 in brief

Tracked by `VAR_ENDGAME_STATE` (states listed in `BattleFrontier_OutsideEast`'s
scripts: 1 gauntlet 8 cleared ... 7 sent to Rustboro).

| Piece | Where |
|---|---|
| Harsh sunlight (drought, outdoor Frontier maps, states 1-4) | Outside East/West `SetupEndgame` |
| Wallace at the Pyramid swaps the badges back to real | Outside East |
| Palkia blasts the Factory door (`SetBattleFactoryUnlocked`); Joy's post | Outside West |
| Spenser and Brandon take Wallace on; five guards (`TRAINER_FACTORY_*`), key pieces, five lights | `BattleFrontier_DevonFactory_*` |
| Cells free Mom, Dad, the Broker, Hoopa | Factory B1F |
| Scott's no-white-out battle (`B_FLAG_NO_WHITEOUT`), level 100, Mega Darkrai | Factory B3F |
| The Arena base: free shop (`FLAG_FRONTIER_SHOP_FREE`), 99 Ultra Balls, Steven | Outside East, Exchange Service Corner |
| Hoopa's rings: twelve box-art legendaries, Island Cave, level 60, unchipped | Arena lobby, Island Cave |
| Gossip: SIEGE, AFTERMATH, DEVON beats | `GetStoryGossipStage` |
| The Frontier's ABRA, now in the Pokémon Center | Pokémon Center 1F |

Scott's trainer class is `FOUNDER`. **He has no battle sprite yet: the owner
is making one** (`Pic:` on both `TRAINER_FACTORY_SCOTT_*` in
`src/data/trainers.party`; Gentleman stands in).

---

## Testing status

| What | Status |
|---|---|
| Endgame part 2 (Rustboro) | Harness scenario 21, **19/19 green**: the ABRA in and out of the Centers, the ambush, the Elite Four in order (out-of-order talks refused), a loss to Glacia whiting out to Rustboro's Center (healed, items back, beaten members stay gone), Stone's scene and the Crown, vanilla 3F events off, Juan, two Hoopa rings, the new gossip beat. **Not played** |
| Endgame part 1 | Harness scenario 20, **18/18 green**: Pyramid to Rustboro, every Brain fight, the cells, Scott's battle **lost on purpose** (outcome checked, no white-out, team healed, items back), the base, the Broker, a Hoopa trip, the ABRA. **Not played** |
| Hoopa catching a legendary | Not run (the knock-out path was) |
| Endgame gossip beats | Built, widths checked; code-read only |
| Endgame towns | Harness scenario 11, 14/14. **Not played** |
| Wallace hiding | Harness scenario 14, 7/7 (incl. an old save). **Not played** |
| Tag-battle party fix | Harness: Ever Grande win and loss, distinct species picked 1,4,3 |
| Devon Factory maps | Harness scenario 10. **Not played** |
| Permanent Megas, Replica Crown | Engine tests in `test/battle/ten_gauntlets_perma_mega.c`. No scene gives the Crown yet |
| Crown event (after gauntlet 7) | Littleroot part played by the owner; the Factory standoff visuals not confirmed |
| Broker's-letter event | Ever Grande part played; the rest not hand-tested |
| Dialogue pass, opening, gossip | Built, widths checked. **Not played** |
| Prices in wins | Built and code-read, not run |
| `make check` | 15 known failures (the baseline) |

---

## Loose ends

- **The ABRA arrivals were a dead end** (fixed in part 2): in the Pokémon
  Center layout, (13, 6) below the ABRA is boxed in by the table, so anyone
  arriving at the Frontier by ABRA could only teleport away. Arrivals are now
  (12, 5) in both Centers. Mauville and Sky Pillar's ABRAs are outdoors and
  unaffected.
- **A parallel build once corrupted `src/data/heal_locations.json`**
  (a missing comma, then a JSON parse error). `git checkout
  src/data/heal_locations.json` and building again fixed it. If a build
  fails with `JSONPROC_ERROR` there, that's the fix.
- **The Elite Four's lines** are first drafts in their vanilla voices; tune
  them after a playthrough, along with the teams' difficulty
  (`endgame-teams.md`, Open questions 2 and 3).

- **`TEMP` Miraidon** on the ferry dock (commit `ad68c3ceb0`): revert before
  release. The owner's save also still has the duplicate Landorus from the
  old tag-battle bug.
- **Scott's battle sprite** (above).
- **Tag battles** where the player picks three need `Multi Party: Half` on both
  opponents (`trainers.party`).
- **Pricing questions:** should the Arena's 100 FP mock battle be priced in
  wins? Should early services have a floor (Second Wind is 150 FP in
  gauntlets 1-2)?
- **Endgame towns:** the vanilla gifts inside open buildings are still
  reachable (Cutter's house HM Cut, Mauville house 1 HM Rock Smash, house 2
  Coin Case, the Game Corner), and **glass doors** (Devon Corp, the Game
  Corner) warp through `TryStartWarpEventScript`, so sealing one needs a
  check there. Sky Pillar still has its cracked floors; the owner wants the
  climb smooth (no bike). New Mauville needs Wattson's way in.
- **The Factory generator** (`~/decomps/headless-harness/factory/`) still makes
  seven B2F lights; regenerating B2F would undo the five-light edit.
- The old Battle Factory maps (gauntlet-6 "Assembly Line" text) are unused:
  the Factory door leads to the Devon Factory. Strip them with the vanilla
  story.
- Champion's Room and Hall of Fame Wallaces have no hide flag; give them one
  if the endgame opens those rooms.
- `~/decomps/wallace-backsprite-for-artist/` can be deleted.

---

## The headless harness: `~/decomps/headless-harness/`

- `harness.c`: scripted-input driver; `#define HARNESS_SCENARIO n`. 21
  endgame part 2 (Rustboro, loses to Glacia once on purpose); 20
  endgame part 1 (Pyramid to Rustboro, loses Scott on purpose); 14 Wallace
  hidden/shown; 12-13 Wallace probes; 11 endgame towns; 10 Devon Factory; 9
  Broker control; 8 League Abra home; 6/7 Ever Grande win/loss; 5 girl's house;
  4 Scott's house, Factory, Lati; 3 Noland/Greta loss; 2 Littleroot win; 1
  Palace exit. `harness.c.pre-*` are older copies.
- `main.c.patch`, `script.c.additions`, `text.c.additions`: apply to a
  **copy** of the repo, never the real one.
- `textwidth.py` checks new `.string` lines in `git diff` against the font
  (~208 px). `factory/render_lib.py` renders maps (plain `render_map.py`
  garbles gTileset_General and FRLG maps).

**How to run:** rsync the repo to the scratchpad excluding `build/`, `.git/`
and `pokeemerald*.gba` (but not `data/mb_*.gba`, a build input). In the copy:
`touch .histignore`, `patch -p0 < main.c.patch`, append each `.additions` file
from its first `Harness_` line on, copy `harness.c` to `src/harness.c`,
`make`, then `tools/mgba/mgba-rom-test -S 3 -R r0 -l 15 pokeemerald.gba |
grep --line-buffered "GBA Debug"`. A run takes a few minutes.

**Gotchas:**
- Runs are always a **New Game**, never the owner's save.
- Watch the right story var (`STORY_VAR`). Fast text, battle style Set.
- **Plan the path first** (collision, bounds, triggers, door types, timing)
  so one run is enough.
- Don't press B in the overworld when mashing through YES/NO prompts.
- Leaving a building means stepping **off** the door mat: walk one tile past
  the warp tile.
- Objects more than about seven tiles from the player aren't loaded yet, so
  check a far object's position only once the player is near it.
- Battles: the HP hack weakens foes and keeps the player healthy. The test
  team needs a move nothing is immune to, with PP refilled (scenario 20 uses
  Nature's Madness). A battle meant to be lost holds the player at 1 HP
  instead, and the check requires `B_OUTCOME_LOST`.
- Choose-three menus: write `gSelectedOrderFromParty`, set
  `gPartyMenu.slotId = PARTY_SIZE`, press only A. Party checks need distinct
  species and an out-of-order pick.
- A log with no TICK lines means the game froze. The BTL lines (every 300
  frames in battle) show where a battle is stuck.
