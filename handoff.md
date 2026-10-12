# Handoff — current state (2026-10-08)

Read `CLAUDE.md` and `project-guide.md` first. This file is where the work
stands: what's built, what's tested, what's loose, what's next, and the test
harness. History is in `git log`; the story is in `storyline.md`.

---

## Where things stand

- **The whole game is built**: all eight gauntlets, the shop, the run loop,
  and the story from the opening to the credits (`storyline.md`, every beat
  ✅). **None of the endgame has been played by hand**: parts 1-5 are
  headless-tested only (below). The owner's next step is a full playthrough.
- **The endgame's teams** are all in `endgame-teams.md` and
  `src/data/trainers.party`; difficulty is untuned.
- **Trainer IDs: 992 of 1000 used** (990-991 are the Gym rematches).
- **The endgame towns sprint is built** (`storyline.md`, "Rustboro after the
  liberation" and "Mauville after the liberation"): Roxanne's and Wattson's
  Gym rematches, Giratina in Rusturf Tunnel, Calyrex in Mauville. Harness
  only, **not played**.
- **Commits are local only.** Pushing from WSL isn't set up.

## Next: the owner's full playthrough, then tuning

Play from a New Game through the credits (the TEMP Miraidon on the ferry dock
is there for speed). Things to look at especially, because no one has seen
them on a screen:

- Every endgame scene's **staging** (who walks where, facing, timing).
- **Difficulty** of the Elite Four (52-55), the admins (60), Maxie and
  Archie (65, no heal between them) and Scott at 100; and the Chansey's
  single level-100 transfer.
- **Sky Pillar's 4F**: the clean layout still has three cracked tiles at
  (6-9, 4), and vanilla's bikeless route drops through one into 3F's inner
  room to reach the upper stairs. The harness walks it fine; decide whether
  that's "smooth" enough or whether 4F needs a re-tiled floor.
- **The ending** is a plain save-and-credits (`EndgameClear`,
  `src/post_battle_event_funcs.c`): no Hall of Fame screen. The continue
  after the credits lands at the Frontier's heal spot (3, 52), not at the
  Arena base.
- **Dialogue tone** in the new scenes (the Elite Four, Stone, Maxie and
  Archie, Scott's last words, Looker's arrest).

---

## Endgame parts 3-5 in brief

`VAR_ENDGAME_STATE` 11-18 (the full table is at the top of
`BattleFrontier_OutsideEast`'s endgame block).

| Piece | Where |
|---|---|
| The siphon: the Pokémon keeper's "Free the POKéMON" (state 10 with the Crown), `FLAG_CROWN_CHARGED`, `FLAG_FRONTIER_CHIPS_OFF`; state 11 | `BattleFrontier_ExchangeServiceCorner`, `src/facility_shop.c` |
| The Crown's limit: one permanent Mega from state 11, six from 14 | `GetReplicaCrownLimit`, `src/party_menu.c` |
| Steven's hub outside the Arena: every state's lines, the Mauville send-off (12, `FLAG_ABRA_TO_MAUVILLE`), the Sky Pillar send-off (16, `FLAG_ABRA_TO_SKY_PILLAR`), the post-credits lines (18) | `BattleFrontier_OutsideEast` |
| Mauville overrun; Wattson, Steven and Wallace; Wattson leads the player down (fade + warp, state 13); respawn at Mauville's Center | `MauvilleCity` |
| New Mauville: wild encounters off, the door open, exits lead back to Mauville; the four admins in order (`VAR_NEW_MAUVILLE_ADMINS`); Maxie and Archie back to back, no heal, a loss repeats both; the Crown supercharged (state 14) | `NewMauville_Entrance`, `NewMauville_Inside` |
| The teams leave; Hoopa's third ring; state 15 | `MauvilleCity` |
| Nurse Joy and the Chansey outside the Arena: `TransferExpToLevel100`, once (`FLAG_CHANSEY_TRANSFER_EXP_USED`) | `BattleFrontier_OutsideEast`, `src/facility.c` |
| Sky Pillar: the allies, the seven Brains' ambush (state 17), Joy by the door as the white-out respawn (`HEAL_LOCATION_SKY_PILLAR_OUTSIDE`), clean floors, no wild Pokémon | `SkyPillar_Outside`, `SkyPillar_1F-5F` |
| The top: the Master Ball and Rayquaza (`FLAG_SKY_PILLAR_RAYQUAZA_CAUGHT`), the Scrambler, Scott at 100 (Mega Rayquaza, both Primals, Mega Mewtwo Y, the Lati, Mega Darkrai), Looker's arrest, state 18, the credits | `SkyPillar_Top`, `EndgameClear` |
| Gossip: SIPHON, MAUVILLE, MAUVILLE_FREED, SKY_PILLAR, ENDING | `GetStoryGossipStage`, all 12 gossip NPCs |
| Vanilla gifts off in Rustboro's Cutter's house, Mauville's houses 1-2 and the Game Corner | those interiors |

Engine facts the harness confirmed: a trainer's `Groudon-Primal` /
`Kyogre-Primal` / `Rayquaza-Mega` listed directly stays in that form through
faints and switches, with Desolate Land, Primordial Sea and Delta Stream
firing; no stone or orb is needed.

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

Scott's trainer class is `FOUNDER`; his battle sprite is the owner's
`graphics/trainers/front_pics/founder_scott.png` (`Pic: Founder Scott`, all
eight `SCOTT` entries in `src/data/trainers.party`). **Not seen in battle yet.**

---

## Testing status

| What | Status |
|---|---|
| Endgame towns: the Gym rematches | Harness scenario 35 (`harness-gyms.c`), 17/17: each door sealed before its town is freed and open from then on (through 18), only the leader inside, Mauville's puzzle off, a loss and a win per leader (a loss: no white-out, still in the Gym, healed, items back, flag clear, the "come back" line; a win: flag, heal, items, lead), no Wattson outside at 15. `test/battle/ten_gauntlets_enemy_mega.c` 4/4: an enemy `Zygarde-Complete` Mega Evolves (AI too) and stays Mega. **Not played**: the teams' difficulty |
| Endgame towns: Giratina (The Tear) | Harness scenario 33 (`harness-giratina.c`), 31/31: nothing before Roxanne, the clues and Hoopa's hint, the escort, the dark walk and its three wrongnesses, a loss, a knock-out, a run, the Master Ball catch and the Core, the exits, after the credits, a full bag. **Not played**: the darkness on screen |
| Endgame towns: Calyrex (The True King) | Harness scenario 34 (`harness-calyrex.c`), 22/22: rubble only before Wattson, the old man's legend, the Crown's restoration, no steed, a run, a knock-out, the catch and the Reins, never chipped, one fusion (Glastrier) and one unfusion. **Not played**: the stand-in art, Spectrier, the learn-move prompt, save and reload while fused |
| The shop's tier menu (New arrivals, Showdown tiers, Low Tier as Competitive and Other by type; `shop-spec.md`, "The Pokémon menu") and form names (Rotom-Wash...) | Harness scenario 26 (`harness-shop.c`), 15/15: the New Game menu (Low Tier and Sell only; Competitive 1, Other 118, Flying by either type), a real walk through Low Tier (Competitive, a purchase, B; Other, no "All", a type's list, B back out level by level), every count with everything unlocked (Competitive 41, Other 223 across its types, 513 in all), gauntlet 1's 99 New arrivals, the siphon row. The old Low Tier "All" (264 rows) froze the game: a `u8` row counter, now `u16`. **Not played**: look at the wider list box beside the FP window |
| Bad Dreams: the Frontier Center's regulars asleep | Harness scenario 31 (`harness-badD.c`), 11/11: the kid and picnicker asleep in place, each dream line, the Wing's glow, Skitty, the "slept well" lines, normal lines after gauntlet 7. Scenario 29 re-run: 18/18 (one earlier run missed the Pike lobby's wandering beauty, a harness timing flake). **Not played** |
| Bad Dreams (the optional Darkrai event, gauntlet 7) | Re-run together on the merged `master`: 29 and 30 green. Scenarios 29 (`harness-badB.c`, the sleepers and Joy, 18/18), 30 (`harness-badC.c`, the Pike, Darkrai, the ball guard, a loss, the win, a gauntlet 6 regression, 9/9) and 24/28 (`harness-badA.c`, Scott's 5-Pokémon teams in both battles). **Not played** |
| The Oldale Paradox researcher (Booster Energy, one per Paradox species; the shop no longer sells it) | Harness scenario 25, 4/4: a non-Paradox refused, a new species paid, a repeat refused, a second species paid. **Not played** |
| Parts 3-5 after the merge | Scenarios 22, 23 and 24 re-run on the merged `master`: 10/10, 16/16, 14/14 |
| Endgame part 3 (the siphon, the hub, the Chansey) | Harness scenario 22 (`harness-part3.c`), 10/10: the keeper's menu, the flags, chips off, Steven's send-offs, Transfer EXP (Eggs and level 100 refused, once only), every state's cast. **Not played** |
| Endgame part 4 (Mauville, New Mauville) | Harness scenario 23 (`harness-part4.c`), 16/16: Wattson's way in, the four admins, Archie **lost on purpose** (white-out to Mauville's Center, both leaders reset), both won, the supercharge, the exit scene, three rings; Primals stayed Primal with their weather. **Not played** |
| Endgame part 5 (Sky Pillar, the ending) | Harness scenario 24 (`harness-part5.c`), 14/14: the ambush, the bikeless climb of all five floors, Scott **lost on purpose** (white-out to Joy outside, healed, items back, no re-catch), won, Looker, state 18, the credits entered with the continue warp at the Frontier; Mega Rayquaza (no stone) and both Primals kept their forms and abilities. **Not played** |
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

- **`TEMP` Miraidon** on the ferry dock is back for the owner's playthrough
  (commit "TEMP: test Miraidon back on the ferry dock"): point the dock
  man's object in `BattleFrontier_OutsideWest/map.json` back at
  `BattleFrontier_OutsideWest_EventScript_Man3` and delete the block at the
  end of its `scripts.inc` before release.
- **Unplayed endgame** (parts 1-5): see "Next" above.
- **Bad Dreams** (`storyline.md`, "During gauntlet 7"): look at the Pike
  lair's darkness on screen (`setflashlevel 2` in
  `BattleFrontier_BattlePikeRoomFinal`'s `SetUpLair`), and the Latios
  variants of Scott's Darkrai-less teams (987, 989) weren't run, only the
  Latias ones.
- **Side quests:** the Oldale Paradox researcher (`OldaleTown_House1`,
  `VAR_PARADOX_SHOWN_LO/HI`) is the first; the owner wants more of these for
  late-game items.
- **Free flags and vars:** flags 0x286-0x287, 0x289-0x28F;
  `VAR_UNUSED_0x40FB`-`0x40FF` (0x281-0x285 and 0x40F9-0x40FA are the endgame
  towns'; 0x40F7-0x40F8 are the Paradox researcher's).
- **Endgame towns, to look at in the playthrough:** the dark Rusturf Tunnel
  (light circle, Giratina's sprite, `MUS_PETALBURG_WOODS`); the Mauville
  statue's stand-in art (a Rock Smash rock as rubble, the Trick House statue)
  and the Calyrex sprite; both Gym teams' difficulty (Mega Zygarde at 60 is
  strong; the dial is Focus Blast to Protect or her level); Calyrex fused with
  Spectrier, the learn-move prompt, a full-party unfuse, save and reload while
  fused.
- **Rusturf Tunnel's warps are `MAP_DYNAMIC` for good** (all to Rustboro):
  restore or delete them at the strip.
- **Brandon's gauntlet 8 team** already has Zygarde-Complete, Miraidon and Iron
  Hands; Roxanne and Wattson repeat them (in singles, at 60-65).
- **The four admins** use grunt overworld sprites (they have none of their
  own); Looker uses the Gentleman sprite at Sky Pillar.
- **The old Battle Factory maps** and the rest of the vanilla story are still
  in the ROM (the strip is still to do; the endgame's maps must survive it:
  Rustboro, Devon Corp, Mauville, New Mauville, Sky Pillar, Island Cave).
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

- The owner's save still has the duplicate Landorus from the old tag-battle
  bug.
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

- `harness.c`: scripted-input driver; `#define HARNESS_SCENARIO n`.
  **`harness-part3.c`, `harness-part4.c`, `harness-part5.c`** are copies of
  it with scenarios 22, 23 and 24 added (endgame parts 3-5; each was written
  by a separate agent, so they live in their own files: use the file whose
  scenario you want as `src/harness.c`). **`harness-shop.c`** has scenario
  26 (the shop's tier menu); it needs one extra line appended to the copy's
  `src/field_specials.c`: `bool8 Harness_ScrollMultiOpen(void) { return
  FindTaskIdByFunc(ScrollableMultichoice_ProcessInput) != TASK_NONE; }`.
  **`harness-giratina.c` (33), `harness-calyrex.c` (34) and `harness-gyms.c`
  (35)** are copies of `harness-lucy.c` (which has 1-14, 20, 21, 25 and 32,
  not the scenarios kept in their own files). `harness-calyrex.c` needs the
  three lines in its header appended to the copy's `src/start_menu.c` and
  `src/item_menu.c`. In `harness.c` itself: 21
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
