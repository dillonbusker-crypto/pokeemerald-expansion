# Eight Gauntlets — Project Guide

The standing reference: the project, the owner, the environment, the locked
decisions, the traps, and the conventions. `CLAUDE.md` points here; the
current state of the work is in `handoff.md`.

---

## What this project is

A battle-only ROM hack of Pokémon Emerald built on pokeemerald-expansion. The
player fights through eight escalating gauntlets (trimmed from ten: see
`storyline.md`, "Trimming to eight gauntlets"), earns points (FP), and
permanently buys Pokémon and items from pools that unlock as they progress. A
story runs alongside it (`storyline.md`), ending in an endgame after gauntlet
8 across the Frontier, Rustboro, Mauville and Sky Pillar.

The vanilla Emerald story is **not used** and will eventually be stripped, but
nothing has been removed yet. Maps the story reuses must survive the strip
(`storyline.md`, "Technical notes").

## Who you're working with

The owner is new to git and the command line (the repo was set up from no WSL
and no toolchain). Explain what commands do rather than just running them.
They are deeply fluent in competitive Pokémon and game design, so design
reasoning needs no simplification.

## Environment

| | |
|---|---|
| Host | Windows, building inside WSL 2 (Ubuntu) |
| Repo | `~/decomps/pokeemerald-expansion` |
| Upstream | Fork of `rh-hideout/pokeemerald-expansion`, remote named `RHH` |
| Toolchain | devkitARM at `/opt/devkitpro`, env vars in `~/.bashrc` |
| Build | `make -j$(nproc)` produces `pokeemerald.gba` |
| Tests | `make check`: **15 known failures** (deliberate project changes); more is new |
| Testing | mGBA on Windows (ROM over `\\wsl$`), or the headless harness (`handoff.md`) |
| GitHub | Pushing from WSL isn't set up; everything is local commits |

Don't re-run environment setup.

## Locked design decisions

| Decision | Setting |
|---|---|
| Battle gimmick | **Megas only.** Tera, Z-Moves, Dynamax disabled |
| Level | Flat 50 in the gauntlets |
| Customization | IVs, EVs, nature, moveset (and ability, via the L menu) freely editable |
| Format | Alternating singles and doubles by gauntlet |
| Team size | Full 6v6, both sides, no team preview |
| Healing | Full heal between every gauntlet battle |
| Bag items | Disabled during runs |
| Held items | Reusable: restored after each battle |
| Item clause | No duplicate held items on a team, player and CPU alike |
| Gauntlet structure | 6 battles drawn from a pool of 12, then a fixed boss |
| Re-entry | None after completing a gauntlet |
| Loss | Streak lost, team kept, FP earned so far retained |
| Roster cap | None. Sell back at 50% |

Gauntlet 1 is capped at 420 BST with a ban list; later gauntlets escalate to
legendaries and Megas (`battle-tower-design-v2.md`, `gauntlet-0N.md`).

---

## Traps

### Set/Shift protection depends on `BATTLE_TYPE_FRONTIER`

Shift's free "switch too?" prompt is skipped only because of one vanilla line,
`data/battle_scripts_1.s` (`jumpifbattletype BATTLE_TYPE_FRONTIER, ...`).
Facility battles must keep `BATTLE_TYPE_FRONTIER`; under a custom flag the
protection disappears silently. (Held items consumed in battle come back via
`SaveFacilityHeldItems()`/`RestoreFacilityHeldItems()`, `src/frontier_util.c`,
which doesn't depend on any flag.)

### Trainer IDs must stay below `MAX_TRAINERS_COUNT` (1000)

Each trainer's "defeated" flag is `TRAINER_FLAGS_START + id`. Past the limit
it silently shares a **system flag** and is read as a battle partner, so the
wrong team loads. A `STATIC_ASSERT` in `src/facility.c` guards it. **986 used.**
Don't raise the limit: it shifts every flag and SaveBlock1 field after it and
breaks existing saves (the last raise already needed a New Game).

### Experience is a story rule

`FrontierStoryAllowsExp()` and `IsFrontierChippedMon()` (`src/facility.c`):
Experience flows only with **real badges** (`FLAG_REAL_BADGES`: Steven after
gauntlet 4, Scott swaps them back after 7, Wallace after 8) and only for
**unchipped** Pokémon (met in Artisan Cave or, through Hoopa's rings, Island
Cave). The Frontier siphon (endgame part 2+) is to lift the chip rule.
Facility battles never give Experience. Obedience is real: the player holds
`FLAG_BADGE08_GET` from the starter on, which makes everything obey.

### Silent script traps

- `checktrainerflag` sets the comparison result, not `VAR_RESULT`: follow it
  with `goto_if TRUE/FALSE` or `call_if TRUE`.
- In a `dynmultistack` menu, an item whose id equals `initialSelected` becomes
  the starting cursor: give CANCEL `MULTI_B_PRESSED` (127), never 0.
- Temp flags `FLAG_TEMP_9/A/B/E/10+` double as engine flags: never hide
  objects with them.

---

## Files

All in the repo root. Team sets use Pokémon Showdown syntax.

| File | What |
|---|---|
| `handoff.md` | Current state, testing status, loose ends, the next step, the harness |
| `storyline.md` | The whole story: built (✅) and planned (📝), technical notes, open questions |
| `endgame-teams.md` | Brain rematches and Elite Four teams |
| `battle-tower-design-v2.md` | Gauntlet structure, economy, item and AI progression |
| `gauntlet-01.md` … `gauntlet-08.md` | Each gauntlet's pool, bans, CPU teams, boss |
| `shop-spec.md`, `shop-unlock-b*.md` | The shop and its unlock waves |
| `run-loop-spec.md` | How a gauntlet run works |
| `save-data-findings.md` | Save block budget (SaveBlock1/2 tight, SaveBlock3 roomy) |
| `frontier-dialogue.md`, `broker-spec.md`, `easter-eggs-spec.md` | World bible, the Broker, the Artisan Cave quest |
| `competitive-reference.md` | Competitive fundamentals for this format |

When docs disagree with the code, trust the headers: names change between
expansion versions.

## Conventions

- **Commit before starting anything**, so the owner always has a clean
  checkpoint.
- **Don't pull from `RHH` mid-task**: merge conflicts the owner can't resolve yet.
- **Keep diffs small.** Don't refactor or clean up unrelated code.
- **Don't strip the vanilla story yet**, and **don't enable Tera, Z-Moves or Dynamax.**
- **The player never speaks.** Narrate ("{PLAYER} asked...") or have NPCs echo.
- **Read `storyline.md` before writing any story beat.** World-building is in
  `frontier-dialogue.md` and `broker-spec.md`.
- **Gossip follows the story** (`GetStoryGossipStage`, beats in
  `include/constants/facility.h`): give every new story event a beat.
- **Every trainer gets a real class and pic** that fits its team. Wardens
  (gauntlets 1-3) use class `Warden` and their Leader pic; gauntlets 4-8 are
  the Frontier Brains with their own. Anything battled under Frontier rules
  must be covered by `IsFacilityBattleTrainer()`, or its pic comes from the
  legacy Frontier table.
- **Pool trainers hold only items the shop already sells** by their
  gauntlet; bosses are exempt.
- **Say "gauntlet", not "building"** (some code still says building until the
  rename in `frontier-dialogue.md`, Part 5).
- **Check new dialogue widths** with `~/decomps/headless-harness/textwidth.py`
  (~208 px per line).
