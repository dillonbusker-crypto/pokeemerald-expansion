# Project Handoff — Eight Gauntlets

Context document for an agent picking up this project. Read this first, then
`handoff.md` (the latest session's state, testing status and loose ends) and
`storyline.md`.

---

## What this project is

A battle-only ROM hack of Pokémon Emerald built on pokeemerald-expansion.
The player fights through eight escalating gauntlets (trimmed from ten: see
`storyline.md`, "Trimming to eight gauntlets"), earns points, and permanently
buys Pokémon and items from pools that unlock as they progress. A story runs
alongside it (`storyline.md`).

The vanilla Emerald story is **not being used** and will eventually be
stripped, but nothing has been removed yet. Some vanilla maps are reused by
the story (Littleroot, Oldale, Ever Grande, and later Rustboro, Mauville,
Sky Pillar...); those must survive the strip (`storyline.md`, "Technical
notes").

---

## Who you're working with

The project owner is new to git and the command line — this repo was set up
over the course of one session, starting from no WSL and no toolchain. Explain
what commands do rather than just running them. They are, however, deeply
fluent in competitive Pokémon and game design, so design reasoning needs no
simplification.

---

## Environment

| | |
|---|---|
| Host | Windows, building inside WSL 2 (Ubuntu) |
| Repo | `~/decomps/pokeemerald-expansion` |
| Upstream | Fork of `rh-hideout/pokeemerald-expansion`, remote named `RHH` |
| Toolchain | devkitARM at `/opt/devkitpro`, installed via the apt repo |
| Env vars | `DEVKITPRO`, `DEVKITARM`, and `$DEVKITARM/bin` on PATH, all in `~/.bashrc` |
| Build | `make -j$(nproc)` — confirmed working, produces `pokeemerald.gba` |
| Testing | mGBA on Windows, reading the ROM over `\\wsl$` |

The build is clean and the ROM boots. Do not re-run environment setup.

---

## Locked design decisions

| Decision | Setting |
|---|---|
| Battle gimmick | **Megas only.** Tera, Z-Moves, Dynamax all disabled |
| Level | Flat 50 |
| Customization | IVs, EVs, nature, moveset freely editable by the player |
| Format | Alternating singles and doubles by gauntlet |
| Team size | Full 6v6, both sides, no team preview |
| Healing | Full heal between every battle |
| Bag items | Disabled during runs |
| Held items | Reusable — restored after each battle |
| Item clause | No duplicate held items on a team, player and CPU alike |
| Gauntlet structure | 6 battles drawn from a pool of 12, then a fixed boss |
| Re-entry | None after completing a gauntlet |
| Loss | Streak lost, team kept, FP earned so far retained |
| Roster cap | None. Sell back at 50% |

Gauntlet 1 is capped at 420 BST with a ban list. Later gauntlets escalate to
680 BST with legendaries and Megas. Full progression is in the design doc.

---

## ⚠️ Set vs. Shift protection is tied to one specific flag — a trap

Facility battles must not let the player's Options menu Battle Style setting
(Set/Shift) affect difficulty — Shift's free "opponent is about to switch,
want to switch too?" prompt is a real competitive advantage and shouldn't
depend on a menu toggle. Investigated whether this needed a hard override
and found the good news and the trap in the same place:

**The good news:** it's already handled, for free, with zero code of ours.
The Shift-only prompt is gated by this exact line in the vanilla battle
scripts:

```
data/battle_scripts_1.s:2748
jumpifbattletype BATTLE_TYPE_FRONTIER, BattleScript_FaintedMonSendOutNew
```

Any battle carrying `BATTLE_TYPE_FRONTIER` skips the prompt unconditionally,
*regardless* of what `gSaveBlock2Ptr->optionsBattleStyle` says — the raw
option is never overridden (checked every reference to it; there's no
Frontier-specific write), but the one place it's actually read for gameplay
(this same script, checking `sBATTLE_STYLE`) is never reached in a
Frontier-flagged battle, because the line above jumps past it first.

**The trap:** this protection is *only* that one hardcoded
`BATTLE_TYPE_FRONTIER` check. It is not "any facility battle" or "any battle
this project considers a facility fight" — it's that literal flag, checked
by name, in vanilla script data we didn't write and won't be revisiting
line-by-line. **If facility battles are ever run under a different/custom
battle type flag instead of reusing `BATTLE_TYPE_FRONTIER`, this protection
disappears silently** — no build error, no obvious symptom, just a player
with Shift selected quietly getting free information and a free switch that
Set-style players don't. Whoever wires up the real facility's battles needs
to either keep `BATTLE_TYPE_FRONTIER` set on them, or explicitly re-check
this before shipping if a custom flag is used instead.

(Separately investigated in the same pass: between-round healing is a full
heal, not a party snapshot, and does not restore held items consumed in
battle — `SaveFacilityHeldItems()`/`RestoreFacilityHeldItems()`
(`src/frontier_util.c`) now exist to handle that, registered as specials,
ready for the facility's pre-/post-battle scripts to call. Unlike the Set/
Shift protection above, this one is explicit and ours - it doesn't depend on
`BATTLE_TYPE_FRONTIER` or any other flag, so it isn't subject to the same
trap.)

---

## ⚠️ Trainer IDs must stay below MAX_TRAINERS_COUNT — and raising it breaks saves

Every trainer's "defeated" flag is `TRAINER_FLAGS_START + id`, and the trainer
flag range ends at `MAX_TRAINERS_COUNT` (`include/constants/opponents.h`).
An ID past it silently shares its flag with a **system flag** (Pokédex,
badges, ...) and is also read as a **battle partner** (`IsPartnerTrainerId()`
in `include/data.h`), so the game loads the wrong team. This happened to
gauntlet 4 while the limit was 890.

It's now 1000, sized when the plan was ten gauntlets (13 trainers each);
with eight, everything planned fits with room to spare. A
`STATIC_ASSERT` in `src/facility.c` fails the build if `TRAINERS_COUNT` ever
exceeds it. **Don't raise it again casually:** it moves every flag after the
trainer range and every SaveBlock1 field after `flags[]`, so existing saves
stop loading correctly. The raise to 1000 already required a New Game.

---

## Experience is a story rule, not a config switch

The old `TESTING_DISABLE_EXP_GAIN` test patch is gone. Experience now follows
the story (`storyline.md`), in `FrontierStoryAllowsExp()` and
`IsFrontierChippedMon()` (`src/facility.c`), called from
`BattleTypeAllowsExp()` and the per-Pokémon step of the exp code
(`src/battle_script_commands.c`):

- **No Experience at all** until Steven swaps the counterfeit badges for real
  ones after gauntlet 4 (`FLAG_REAL_BADGES`).
- **Even then, "chipped" Pokémon never gain any.** A Pokémon counts as chipped
  unless its met location is Artisan Cave, so only the wild-caught Latias or
  Latios can grow. The New Mauville overclock (planned) lifts the chip rule.
- Facility battles never give Experience anyway (vanilla excludes
  `BATTLE_TYPE_FRONTIER`).

**Obedience is no longer test-patched — this is now real, not a shim.**
`TESTING_DISABLE_OBEDIENCE` has been removed entirely (was `GetAttackerObedienceForAction()`
in `src/battle_util.c` unconditionally returning `OBEYS`). The player now
receives all 8 badges at starter receipt (`CB2_GiveStarter()` in
`src/battle_setup.c`), so real obedience checks already pass at level 50 —
`FLAG_BADGE08_GET` alone makes obedience unconditional regardless of level,
per vanilla's own Rain Badge behavior. Facility battles were already exempt
either way (`BATTLE_TYPE_FRONTIER` always obeys, vanilla behavior, untouched).
No further action needed here; noted in case a future save-data wipe or
alternate game-start path ever bypasses `CB2_GiveStarter()` and needs its own
way to grant badges.

---

## Files

All in the repo root. Team sets are written in Pokémon Showdown syntax.

| File | What |
|---|---|
| `handoff.md` | Latest session: commits, testing status, tools, loose ends, next step |
| `storyline.md` | The whole story, what's built (✅) and planned (📝), open questions |
| `battle-tower-design-v2.md` | Gauntlet structure, economy, item and AI progression (written for ten; trimmed to eight per `storyline.md`) |
| `gauntlet-01.md` … `gauntlet-08.md` | Each gauntlet's pool, ban list, CPU teams and boss |
| `shop-spec.md`, `shop-unlock-b*.md` | The shop and its unlock waves |
| `run-loop-spec.md` | How a gauntlet run works |
| `save-data-findings.md` | Save block budget (SaveBlock3 is nearly empty; SaveBlock1/2 are tight) |
| `frontier-dialogue.md`, `broker-spec.md`, `easter-eggs-spec.md` | World bible, the Broker, the Artisan Cave quest |
| `competitive-reference.md` | Competitive fundamentals for this format |
| `give-counter-team.c` | Historical: the gauntlet 1 benchmark counter-team |

When docs disagree with the code, verify constant names and API signatures
against the headers; they change between expansion versions.

---

## Current state

All eight gauntlets, the shop and the run loop are built, and the story is
built through the event after gauntlet 7 ("the Crown is taken"). Next is the
endgame after gauntlet 8 (`storyline.md`, "After gauntlet 8" onward, and
"Still to decide"). See `handoff.md` for what's untested.

Testing is either the owner in mGBA, or the headless harness in
`~/decomps/headless-harness/` (run on a **copy** of the repo, always a New
Game; how-to in `handoff.md`).

---

## Conventions

- **Commit before starting anything.** The owner is new to git; a clean
  checkpoint is how they recover from a bad change.
- **Don't pull from `RHH` mid-task.** Updating the expansion version mid-work
  will produce merge conflicts they aren't equipped to resolve yet.
- **Don't refactor or clean up unrelated code.** Keep diffs small and readable.
- **Don't strip the vanilla story yet.** That's a later, deliberate step.
- **Don't enable Tera, Z-Moves or Dynamax.** Megas only is a locked decision.
- **The whole story lives in `storyline.md`** (the receptor, Scott, the ending,
  what's built vs planned). Read it before writing any story beat.
- **World-building lives in `frontier-dialogue.md` and `broker-spec.md`.**
  Frontier NPCs react to progress through the `GetGauntletsClearedCount`
  special; keep new lines consistent with the world bible there (Part 1).
- **Every facility trainer gets a real Class and Pic.** In `src/data/trainers.party`,
  pick a class/pic that fits the team's theme (Hiker for an Earthquake team,
  Sailor for rain, Kindler for sun...) - never leave the placeholder
  Youngster. Bosses: gauntlets 1-3 are Gym Leaders turned Wardens (class
  `Warden`, their Leader pic: WINONA, JUAN, ROXANNE); gauntlets 4-8 are the
  Frontier Brains with their own class and pic (Anabel, Tucker, Lucy,
  Spenser, Brandon). Noland and Greta are Scott's henchmen, not bosses. Our trainers only show their
  own pic because `OpponentGetTrainerPicId()` (`src/battle_controller_opponent.c`)
  skips the legacy Frontier lookup for `IsFacilityBattleTrainer()` IDs - any
  new trainer battled under Frontier rules must be covered by that function.
- **Say "gauntlet", not "building".** The eight sets of battles are gauntlets
  (the project is the Eight Gauntlets; the Ranking Hall is the Hall of Eight). "Building" means only the physical
  Frontier structures. Some code names still say "building"
  (`FACILITY_BUILDING_N`, `buildingsCompleted`, ...) until the planned rename
  in `frontier-dialogue.md`, Part 5.

