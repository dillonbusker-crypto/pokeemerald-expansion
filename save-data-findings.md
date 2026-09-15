# Save Data Findings — Ten Buildings

Investigation only. No code changed. All sizes below were measured directly —
either from `sizeof()` via a throwaway probe compiled with the project's own
toolchain and flags, or read straight from the struct definitions and the
`STATIC_ASSERT`s in `src/save.c` that already enforce these budgets at build
time. Nothing here is estimated.

## Verdict up front

**The working hypothesis is confirmed for the roster and currency, and the
"save space is the tightest constraint" assumption in CLAUDE.md is very
likely wrong** — at least for what this project actually needs. The PC box
system already is a persistent, save-backed, freely-editable Pokémon store.
Battle Points already is a capped save-backed currency. Flag/var space for
progression tracking is abundant before touching anything else. And the
project hasn't even flipped the switches it already has for reclaiming
save space — there's a dedicated, currently-unused config file
(`include/config/save.h`) that alone frees up ~3.9 KB the moment any of its
options are turned on.

The one real, structural constraint I found is **box count**. More on that
below.

---

## 1. The roster — PC box system

**Confirmed: this is already exactly what the design needs.**

- `TOTAL_BOXES_COUNT = 14`, `IN_BOX_COUNT = 30` (5 rows × 6 columns) —
  `include/pokemon_storage_system.h:4-7`. 14 × 30 = **420 boxed Pokémon**,
  plus the 6-Pokémon active party (`playerParty[PARTY_SIZE]`, stored in
  `SaveBlock1` at `include/global.h:1112`) = 426 total holdable at once.
- Storage is fully save-backed: `struct PokemonStorage` lives in its own
  fixed range of save sectors (below), not derived or regenerated — a
  boxed Pokémon is exactly as permanent as a partied one.
- A full management UI already exists and ships in vanilla: deposit,
  withdraw, move between boxes, rename boxes, change wallpaper. Nothing to
  build there except a game-specific entry point (a "collection" screen
  instead of the PC, if that's wanted stylistically — not a save-data
  question).

### What's lost when a Pokémon is boxed vs. partied

**Almost nothing.** `struct Pokemon` (party) is `struct BoxPokemon` (box) plus
20 extra bytes: `status`, `level`, `mail`, and the six live battle stats
(`hp`/`maxHP`/`attack`/`defense`/`speed`/`spAttack`/`spDefense`) —
`include/pokemon.h:258-299`. Species, ability, nature (derived from
personality), IVs, EVs, moves + PP, held item, OT/trainer ID, friendship,
ribbons, shininess — all of it lives in the encrypted substructs inside
`BoxPokemon` itself, identically whether the mon is in a box or the party.

Even HP loss and status condition survive boxing, just compressed:
`hpLost:14` and `compressedStatus:4` bitfields (`include/pokemon.h:272-277`),
read back out via `UncompressStatus()` (`src/pokemon.c:783`) whenever the mon
is withdrawn. The six live battle stats aren't "lost" either — they're
just not kept pre-computed while boxed; `CalculateMonStats()` rebuilds them
from the same substruct data the instant the mon re-enters the party.

Practical upshot: **"IVs, EVs, nature, moveset freely editable" needs no new
save format at all** — that's already exactly what `SetBoxMonData()` and the
existing summary-screen editing plumbing operate on. That part of the ask is
a UI/feature task, not a save-data one.

### Can the box count be expanded?

**Yes in principle, but not for free — this is the one genuine hard
constraint I found.** `PokemonStorage` is already large enough that it
barely fits in its allotted save sectors:

| | bytes |
|---|---|
| `sizeof(struct BoxPokemon)` | 80 |
| One full box (30 mons) | 2,400 |
| `sizeof(struct PokemonStorage)` (current, 14 boxes) | 34,144 |
| Sectors allotted to it (9 × 3968) | 35,712 |
| **Free space right now** | **1,568** |

One more box costs 2,400 bytes. There are only 1,568 free. **You cannot add
even a single 15th box without reclaiming space from elsewhere first** (see
§4). Beyond the raw byte budget, box count is wired into the save sector
layout itself (`SECTOR_ID_PKMN_STORAGE_START`/`_END` in `include/save.h:22-23`
hard-code "9 sectors" for storage), so growing it means either shrinking
what's allotted to `SaveBlock1`/`SaveBlock2` to hand sectors over, or
restructuring the sector map — a real engineering task, not a config flip.

Given that, and that the design says "Roster cap: none," worth flagging: at
current box math, **420 is the practical ceiling** unless sector space is
deliberately reallocated. Whether that's actually a problem depends on how
large the full ten-building purchasable pool ends up being across all ten
buildings, and how aggressively players are expected to sell back rather
than hoard — I didn't try to estimate total pool size across the whole
design doc, since buildings 3–10 aren't designed yet.

---

## 2. The currency — Battle Points

**Confirmed usable, with one caveat.**

`gSaveBlock2Ptr->frontier.battlePoints` is a `u16` (`include/global.h:529`),
capped by `#define MAX_BATTLE_FRONTIER_POINTS 9999`
(`include/constants/battle_frontier.h:51`). The storage itself (2 bytes)
supports up to 65,535 — the 9999 ceiling is a plain `#define`, not a save
format limit, so if 9999 genuinely isn't enough for the target economy it's
a one-line change, no save impact.

**The caveat:** this is the *actual* vanilla Battle Frontier's currency
field, inside its actual live struct (`struct BattleFrontier`, still fully
present and functional, since nothing's been stripped yet — see CLAUDE.md).
Reusing it directly means FP and real Battle Frontier BP become the same
pool. If vanilla Battle Frontier is going to stay reachable at all before
the story strip happens, that's two unrelated economies sharing one
counter, which is probably not intended. A dedicated FP field, entirely
separate from `frontier.battlePoints`, costs 2–4 bytes and there's ample
room for it (§4) — I'd recommend that over reusing the Frontier field
outright, unless the plan is specifically to gut vanilla Battle Frontier and
repurpose its struct wholesale (see the note on `struct BattleFrontier`'s
size in §4 — it's the single largest reclaimable block in the whole save,
and shaped remarkably close to what this project needs).

---

## 3. Progression state — buildings, tiers, streak

**Confirmed abundant, no new space needed even before touching anything
else.**

- `VARS_COUNT = 256` (`include/constants/vars.h:280`), each a `u16`, living
  in `SaveBlock1` (`vars[VARS_COUNT]` at `include/global.h:1134`). Of the
  256, **29 are currently defined as literally unused**
  (`VAR_UNUSED_0x****`), free to rename and use today with zero size cost.
- `FLAGS_COUNT = 2,400` single bits (`include/constants/flags.h:1642`,
  packed into `flags[NUM_FLAG_BYTES]` in `SaveBlock1`,
  `include/global.h:1133`). **381 are currently defined as unused.**

What ten-building progression actually needs is small: one flag per building
completed (10), one var for current streak within a run (0–7), one var (or
even derivable from the completion flags) for highest unlocked tier, and
some small encoding for which 6 of 12 pool trainers were drawn this run if
that needs to persist across a save/quit (worst case, a 12-bit mask per
building fits in one var each — 10 more vars). That's on the order of
**~15–25 vars and ~15–25 flags**, comfortably inside the 29 + 381 already
sitting unused, without needing to grow either array (which would eat into
the already-tight `SaveBlock1` budget — see §4). This isn't close to a
constraint.

Once the vanilla story is actually stripped (a separate, later step per
CLAUDE.md), most of the other ~2,019 currently-"used" flags and ~227
currently-"used" vars tied to story/map events become free too — this
number only gets more comfortable over time, not less.

---

## 4. Free space — the actual numbers, and why the constraint is softer than assumed

All four figures below are exact (`sizeof()` via a compiled probe using the
project's real compiler flags, cross-checked against the `STATIC_ASSERT`s in
`src/save.c:80-83` and the debug menu's own size-checker in `src/debug.c`,
which computes free space with the identical formula).

| Block | Sectors allotted | Capacity | Currently used | **Free right now** |
|---|---|---|---|---|
| `SaveBlock1` | 4 | 15,872 B | 15,568 B | **304 B** |
| `SaveBlock2` | 1 | 3,968 B | 3,884 B | **84 B** |
| `SaveBlock3` | 14 (116 B/sector) | 1,624 B | 4 B | **1,620 B** |
| `PokemonStorage` | 9 | 35,712 B | 34,144 B | **1,568 B** |

Taken at face value, `SaveBlock2`'s 84 bytes free looks like it justifies
CLAUDE.md's worry. But two things change that picture substantially:

**`SaveBlock3` is essentially empty.** It's a 1,624-byte block whose real
content right now is one active byte (`dexNavChain`) — everything else in
its struct (fake RTC, NPC follower data, item description flags, DexNav
search levels, apricorn trees) is compiled out in this config. This is by
far the easiest place to put new small state (progression flags/vars if you
ever need more than the spare `SaveBlock1` ones, an FP counter, anything
compact) — 1,620 free bytes with zero reclamation work.

**There's a dedicated, unused space-reclaiming config file already in the
codebase: `include/config/save.h`.** Every option in it is currently
`FALSE` — meaning all of this legacy data is being allocated for features
this project almost certainly doesn't use (Mystery Gift, Union Room Chat,
E-Reader, record-mixing Hall of Fame records, Trainer Hill, VS Seeker/match
call, link battle records):

| Toggle | Frees | Block |
|---|---|---|
| `FREE_MYSTERY_GIFT` | 876 B | SaveBlock1 |
| `FREE_MYSTERY_EVENT_BUFFERS` | 1,104 B | SaveBlock1 |
| `FREE_RECORD_MIXING_HALL_RECORDS` | 1,032 B | SaveBlock2 |
| `FREE_UNION_ROOM_CHAT` | 212 B | SaveBlock1 |
| `FREE_BATTLE_TOWER_E_READER` | 188 B | SaveBlock2 |
| `FREE_EXTRA_SEEN_FLAGS_SAVEBLOCK2` | 108 B | SaveBlock2 |
| `FREE_MATCH_CALL` | 104 B | SaveBlock1 |
| `FREE_LINK_BATTLE_RECORDS` | 88 B | SaveBlock1 |
| `FREE_EXTRA_SEEN_FLAGS_SAVEBLOCK1` | 52 B | SaveBlock1 |
| `FREE_ENIGMA_BERRY` | 52 B | SaveBlock1 |
| `FREE_TRAINER_HILL` | 28 B | SaveBlock1 |
| `FREE_TRAINER_TOWER` | 0 B (FRLG-only, doesn't apply to Emerald) | — |

Flipping just the ones that gate genuinely-unused vanilla systems here would
take `SaveBlock1` from 304 B free to roughly **2,820 B free**, and
`SaveBlock2` from 84 B free to roughly **1,428 B free** — before writing a
single line of new-feature code, and before stripping anything else.

**The single biggest number in the whole save file, though, is
`struct BattleFrontier` itself: 2,272 bytes**, almost 60% of all of
`SaveBlock2` (`include/global.h:456-541`, confirmed via the same probe).
That's the live Battle Tower/Dome/Palace/Arena/Factory/Pike/Pyramid state —
win streaks, records, rental trainer pools, the works. This project's
real facility is conceptually a direct descendant of exactly this system
(win streaks through a facility, records, rentals), and if the plan is ever
to gut vanilla Battle Frontier rather than run alongside it, this struct is
both the natural home for the ten-buildings save state and, on its own,
larger than everything else in `SaveBlock2` combined. I'm not making that
call for you — it's a real design decision (keep vanilla Frontier reachable
vs. replace it outright) — but it's worth knowing it's sitting right there.

### The one real constraint

Restated from §1: **PC box count.** `PokemonStorage` has only 1,568 free
bytes against a 2,400-byte cost per additional box, and the 9-sector
allotment is hard-coded in `include/save.h`. This is the one place where
"just add a field" doesn't work — expanding past 420 boxed Pokémon needs
sector reallocation, which is a real (if bounded) engineering task.

---

## Summary

**Get for free, no new save data:**
- The entire roster system — permanent storage, 420 box slots + 6 party,
  full IV/EV/nature/moveset persistence, a working management UI.
- A capped, save-backed currency field (Battle Points), if reused directly
  — see the caveat about entangling it with vanilla Battle Frontier.
- All the flags/vars progression tracking needs (~15–25 of each, against
  381 unused flags and 29 unused vars already sitting free).

**Genuinely needs new save data, and how much:**
- **A dedicated FP counter**, separate from vanilla Battle Points, if you
  want the two economies distinct: 2–4 bytes. Fits trivially in the ~1,620
  free bytes already sitting in `SaveBlock3`.
- **Ten-building progression state** (per-building completion, current
  streak, unlocked tier, which pool trainers were drawn if that must
  persist): well under 100 bytes total. Also fits in `SaveBlock3` alongside
  the FP counter with room to spare, no reclamation needed.
- **Box count beyond 420**, if the design ultimately needs it: this is the
  only item on this list that isn't cheap. It needs sector reallocation in
  `include/save.h`/`src/save.c`, not just a new field, because
  `PokemonStorage` is already within 1,568 bytes of its 9-sector ceiling
  and one extra box costs 2,400.

**Net assessment:** CLAUDE.md's assumption that save space is the tightest
constraint in the project does not hold up for the roster, the currency, or
progression tracking — all three fit inside space that already exists,
some of it (`SaveBlock3`) barely touched. The box-count ceiling is the one
place the assumption holds, and only if 420 turns out not to be enough.
