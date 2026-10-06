# Handoff — current state (2026-10-05)

Read `CLAUDE.md` and `project-guide.md` first. This file is where the work
stands: what's built, what's tested, what's loose, what's next, and the test
harness. History is in `git log`; the story is in `storyline.md`.

---

## Where things stand

- **All eight gauntlets, the shop and the run loop** are built.
- **The story is built through endgame part 1**: everything up to and
  including the events after gauntlet 7, then the after-gauntlet-8 Factory
  sequence and the Arena base (`storyline.md`, "After gauntlet 8: the
  Factory" ✅ and "Hoopa's rings" ✅).
- **The endgame's team plans** are in `endgame-teams.md` (five Brain
  rematches, built; the Elite Four, not yet built).
- **63 commits are local only.** Pushing from WSL isn't set up.

## Next: endgame part 2, Rustboro

`storyline.md`, "Rustboro: Devon Corporation". Part 1 ends with Steven
outside the Arena setting `FLAG_ABRA_TO_RUSTBORO` and `VAR_ENDGAME_STATE` = 7;
the ABRA in the Frontier's Pokémon Center takes the player to Rustboro.
Part 2 needs:

- The ABRA's Rustboro arrival moved to the Pokémon Center (the owner's
  choice; it's beside the town's ABRA now, `data/scripts/endgame_towns.inc`).
- Steven and Wallace outside Devon; the **Wardens' ambush** (Winona, Juan,
  Roxanne; fight off-screen).
- The **Elite Four** on Devon 1F/2F (`endgame-teams.md`, levels 52-55, two
  permanent Megas each), a loss whiting out to Rustboro's Center.
- **President Stone** and the scientist; the **Replica Crown** given
  (`ITEM_REPLICA_CROWN`, uncharged); Juan's apology outside.
- Switching off Devon Corp's vanilla events (Mr. Stone's letter, the Exp.
  Share, fossils).
- Hoopa's second ring (`GetHoopaRingsLeft`, `src/facility.c`) and a gossip beat
  after DEVON.

After that: the Frontier siphon (one permanent Mega, chips off), New Mauville
(Wattson, the admins, Archie and Maxie's Primals, six permanent Megas), the
Chansey's level 100, Sky Pillar and the final battle. Open questions are in
`storyline.md`, "Still to decide".

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

- `harness.c`: scripted-input driver; `#define HARNESS_SCENARIO n`. 20
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
- Battles: the HP hack weakens foes and keeps the player healthy. The test
  team needs a move nothing is immune to, with PP refilled (scenario 20 uses
  Nature's Madness). A battle meant to be lost holds the player at 1 HP
  instead, and the check requires `B_OUTCOME_LOST`.
- Choose-three menus: write `gSelectedOrderFromParty`, set
  `gPartyMenu.slotId = PARTY_SIZE`, press only A. Party checks need distinct
  species and an out-of-order pick.
- A log with no TICK lines means the game froze. The BTL lines (every 300
  frames in battle) show where a battle is stuck.
