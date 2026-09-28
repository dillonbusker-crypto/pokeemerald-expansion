# Project Handoff — Ten Buildings

Context document for an agent picking up this project. Read this first, then
`battle-tower-design-v2.md` and `building-01.md`.

---

## What this project is

A battle-only ROM hack of Pokémon Emerald built on pokeemerald-expansion.
There is no story, no overworld progression, no gyms. The player fights through
ten escalating battle facilities, earns points, and permanently buys Pokémon and
items from pools that unlock as they progress.

The vanilla Emerald story and maps are **not being used** and will eventually be
stripped, but nothing has been removed yet.

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
| Format | Alternating singles and doubles by building |
| Team size | Full 6v6, both sides, no team preview |
| Healing | Full heal between every battle |
| Bag items | Disabled during runs |
| Held items | Reusable — restored after each battle |
| Item clause | No duplicate held items on a team, player and CPU alike |
| Building structure | 6 battles drawn from a pool of 12, then a fixed boss |
| Re-entry | None after completing a building |
| Loss | Streak lost, team kept, FP earned so far retained |
| Roster cap | None. Sell back at 50% |

Building 1 is capped at 420 BST with a ban list. Later buildings escalate to
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

## ⚠️ Temporary test-only patch — currently ON, must be reverted before shipping

One engine behavior is still hard-disabled so the building 1 boss test
harness gives a clean read. No existing on/off switch for it anywhere else in
the codebase, so it's a small, clearly-marked direct patch rather than a
config flip:

| | |
|---|---|
| Switch | `include/config/battle.h`, near the top: `TESTING_DISABLE_EXP_GAIN`, `TRUE` |
| Exp gain | `BattleTypeAllowsExp()` in `src/battle_script_commands.c` — returns `FALSE` unconditionally when the flag is on, so no Pokémon can level up mid-fight and skew the test |

**To revert:** flip the define to `FALSE`, or delete the config block and the
one guarded `if` at the top of `BattleTypeAllowsExp()`. Additive, so removal
is a clean, small diff.

**Do not carry this into the real facility** without deciding on purpose
whether the shipped game wants exp gain on or off — it was switched off
purely so the boss tuning test isn't contaminated by mid-battle level-ups,
not as a design decision for the shipped game.

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

Copy these into the repo folder so they're readable:

- `battle-tower-design-v2.md` — full ten-building structure, economy, item and
  AI progression
- `building-01.md` — the complete vertical slice: curated pool, ban list, shop,
  twelve CPU teams, the boss, and the benchmark counter-team
- `competitive-reference.md` — competitive fundamentals for singles and doubles,
  tailored to this format
- `give-counter-team.c` — ready-to-paste function that gives the player the
  benchmark counter-team

Team sets are written in Pokémon Showdown syntax.

---

## Immediate task

Get the building 1 boss fight playable so the owner can test whether it's
tuned correctly. This is a throwaway test harness, not the real facility.

1. **Determine the trainer data format.** Check whether `src/data/` contains
   `trainers.party` (expansion 1.10+ Competitive Format) or only `trainers.h`
   (older C struct format). This decides how the teams get entered.
2. **Replace a sacrificial early trainer** — Youngster Calvin on Route 102 is
   the suggestion, since he's reachable within two minutes of a new game and
   is a single battle — with Warden Helis's six from `building-01.md`. All at
   level 50, with the specified natures, EVs, IVs, abilities, items and moves.
3. **Set the boss AI flags:** full offensive intelligence, smart replacement
   choice, and omniscient. Altaria in slot six flagged as the ace so the AI
   holds it in reserve.
4. **Add the counter-team function** from `give-counter-team.c` to
   `src/new_game.c`, with the call at the end of `NewGameInitData()`.
5. **Disable exp gain and obedience checks** for the duration of this test —
   see "Temporary test-only patches" below. Both would otherwise contaminate
   the tuning read (mid-battle level-ups, random disobedience at level 50
   with zero badges).
6. **Build and fix errors.**

---

## Things to verify rather than assume

These were written without access to the repo and need checking against the
actual headers:

- **AI flag constant names** — in `include/constants/battle_ai.h`. They have
  changed between expansion versions, so don't trust any name written in the
  design docs.
- **Ability numbers.** Sableye must get Prankster and Parasect must get Dry
  Skin. Both are set via `abilityNum` and the numbering should be confirmed
  against the species data.
- **Species, move and item constants** — particularly `SPECIES_FERROSEED`,
  `MOVE_FOUL_PLAY`, `ITEM_BLACK_GLASSES`, `ITEM_MYSTIC_WATER`.
- **Pokémon API signatures** — `CreateMonWithNature`, `SetMonMoveSlot`,
  `CalculateMonStats` and the `MON_DATA_*` enum names.

---

## Conventions

- **Commit before starting anything.** The owner is new to git; a clean
  checkpoint is how they recover from a bad change.
- **Don't pull from `RHH` mid-task.** Updating the expansion version mid-work
  will produce merge conflicts they aren't equipped to resolve yet.
- **Don't refactor or clean up unrelated code.** Keep diffs small and readable.
- **Don't strip the vanilla story yet.** That's a later, deliberate step.
- **Don't enable Tera, Z-Moves or Dynamax.** Megas only is a locked decision.

---

## What comes after

Once the boss is playable and tuned, the gate for moving on is the owner
beating Helis using only building 1's pool. Then buildings 2 through 10 get
designed, and separately the real facility gets built — the point economy, the
shop, the purchase and roster UI, and the save data to hold a permanently owned
collection.

Save block space is expected to be the tightest technical constraint in the
whole project and has not been investigated yet.
