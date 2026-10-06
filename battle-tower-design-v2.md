# Eight Gauntlets — Design Document v2

Battle-only Emerald hack on pokeemerald-expansion. Eight gauntlets, permanent
purchases, escalating pools.

---

## Locked decisions

| Decision | Setting |
|---|---|
| Gimmick | **Megas only.** Tera, Z-Moves, Dynamax all disabled |
| Level | Flat (50 or 100 — see open items) |
| Customization | IVs, EVs, nature, moveset freely editable at any time |
| Roster cap | None |
| Gauntlet re-entry | **None after completion.** Forward only |
| Team lock | Locked at run start until win or loss |
| Gauntlet structure | 6 battles drawn from a pool of 12, then a fixed boss |
| Team size | All 6 brought; CPUs run full teams |
| Healing | **Full heal after every battle** |
| Bag items | **Disabled entirely** during gauntlet runs |
| Held items | Reusable — restored after each battle |
| Loss penalty | Streak lost, team kept, FP earned so far retained |

### Consequences worth holding in mind

**Full healing kills attrition.** Hazards, chip damage, PP stall and status
wear are near-worthless as CPU strategies. Every battle is a fresh sprint, so
CPU teams should be built around immediate pressure and turn-one impact, not
long games. Stealth Rock is nearly dead weight in this format — the only value
is the single switch-in it punishes mid-battle.

**No bag items raises the value of held items sharply.** With no Potions or
Revives, a Focus Sash or a Sitrus Berry is the only mid-battle recovery in
existence. Combined with reusability, these are far stronger here than in any
official format.

**No re-entry means every purchase is permanent and unrefundable.** Partial FP
awards (below) are the safety valve.

---

## Gauntlet progression

Alternating formats. BST figures are a **first-pass filter only** — each pool
is then hand-curated, with individual bans where a Pokémon is out of line for
its tier.

| # | Format | BST cap | Pool additions |
|---|---|---|---|
| 1 | Singles | 405 | Second-stage starters, basic NFEs |
| 2 | Doubles | 500 | Core support and utility mons |
| 3 | Singles | 550 | Strong fully-evolved non-legendaries |
| 4 | Doubles | 599 | The best sub-600 competitive picks |
| 5 | Singles | 600 | Pseudo-legendaries, singles-relevant Paradox/UB/Mythicals, **28 Mega Stones** (see `gauntlet-05.md`) |
| 6 | Doubles | 600 | Doubles-leaning Paradox/UB + **doubles-leaning Megas** |
| 7 | Singles | 600 | Stronger Megas, **all remaining Mega Stones** (except Kangaskhanite, never sold) + all 600 BST legendaries/Paradox/UB |
| 8 | Doubles | 680 | The finale. Box-art and Mega legendaries, full uber |

Trimmed from ten gauntlets to eight: the old 7 and 8 fold into gauntlet 7,
and the old 9 and 10 into gauntlet 8, so the last step is deliberately steep.

### Facilities and bosses — decided

Each gauntlet runs from one Battle Frontier facility. From gauntlet 4 on,
the boss is that facility's own Frontier Brain (see `frontier-dialogue.md`
for the reasoning and the lore). Gauntlets 1–3 are guarded by Anabel's Tower
lieutenants.

| # | Facility | Boss |
|---|---|---|
| 1 | Battle Tower, Singles mat | Warden Winona (Tower lieutenant) |
| 2 | Battle Tower, Doubles mat | Tidewarden Juan (Tower lieutenant) |
| 3 | Battle Tower, Multi mat | Dunewarden Roxanne (Tower lieutenant) |
| 4 | Battle Tower, Link Multi mat | Salon Maiden Anabel |
| 5 | Battle Dome | Dome Ace Tucker |
| 6 | Battle Pike | Pike Queen Lucy |
| 7 | Battle Palace | Palace Maven Spenser |
| 8 | Battle Pyramid | Pyramid King Brandon |

The Pyramid stays last as the finale. Two buildings host no gauntlet:

- **The Battle Factory is Devon's control room**: Devon's technology runs the
  island's systems, and the **Mega Pillar** stands inside. Sealed to the
  player until the endgame, which plays out there.
- **The Battle Arena is a sparring ground**: rematches against past bosses,
  and (an easter egg) mock battles against the next boss. Later it becomes
  the base for Nurse Joy and the Broker. See `frontier-dialogue.md`.

**Factory Head Noland and Arena Tycoon Greta are Scott's personal
henchmen**, not gauntlet bosses (`storyline.md`).

### Note on gauntlet 1

At 405 BST the pool is intentionally thin — second-stage starters and similar.
This is fine for the six regular battles, which should be genuinely easy. **The
risk is the boss.** Gauntlet 1's boss uses gauntlet 2's pool (up to 500 BST),
which against a 405-BST player team is a large relative gap with very little
counterplay available. Tune this boss more gently than the rule implies, or
give the player a small starting item allotment specifically to answer it.

---

## CPU team construction

**Gauntlets 1–3:** fewer than 12 teams is acceptable while the pool is thin.
Build as many distinct, genuinely different teams as the pool supports rather
than padding with near-duplicates.

**Gauntlets 4–8:** four strategies per gauntlet, three team variants each,
totaling 12. Variants should differ in execution, not just species swaps — the
player should recognize the archetype and still have to read the specific team.

Each gauntlet's twelve teams should collectively teach that gauntlet's theme,
so that by the time the player reaches the boss they've seen the strategy from
several angles and have had the chance to build an answer.

---

## Boss design

Bosses draw from **next tier's pool plus current and previous tiers**. The
power jump must be present, but a boss can reach back for a supporting piece —
a weather-themed gauntlet 5 boss running Pelipper from gauntlet 2 is correct.

Three rules:

1. **Legible gimmick, not just bigger numbers.** The player should lose,
   understand exactly why, and know what to build.
2. **The counterplay must exist in the current shop.** If the boss has a Mega
   the player can't own, the answer — Encore, Taunt, priority, a status
   shutdown, Unaware — must be purchasable at the player's current tier.
3. **Unfair but beatable.** The gap is the point. Frustration comes from
   opacity, not difficulty.

---

## Economy

Currency: **FP**.

| Source | Amount |
|---|---|
| Each battle won in the current gauntlet | 10 × gauntlet number |
| Defeating the gauntlet boss | 100 × gauntlet number |

Crucially, **FP from individual wins is kept even on a failed run.** A player
who reaches battle 4 and loses keeps that FP. This is the anti-soft-lock
mechanism: a player who spends badly can always grind the current gauntlet for
incremental FP until they can afford what they need. Slow, but never dead.

Gauntlet 1 first clear yields ~160 FP; gauntlet 8, ~1300. (Superseded in the
build: 75/450 per battle/boss for gauntlets 1–2, 100/600 for 3, then +50 a
win per gauntlet from 4, the boss worth six wins: 150/900, 200/1200,
250/1500, 300/1800, 350/2100.)

### Pricing

| Pool tier | Pokémon cost |
|---|---|
| Gauntlet 1–2 | 100–250 FP |
| Gauntlet 3–4 | 300–500 FP |
| Gauntlet 5–6 | 550–850 FP |
| Gauntlet 7 | 900–1400 FP |
| Gauntlet 8 | 1500–2500 FP |

Target: clearing a gauntlet funds two to three members of the pool it unlocks.
Never a full six. The player is always choosing.

---

## Item progression

Strategic weight should climb with the gauntlets, matching the Pokémon that
unlock alongside them.

| Unlocked | Items |
|---|---|
| Gauntlet 1 | Type-boosting items, pinch berries, Leftovers |
| Gauntlet 2 | Resist berries, Sitrus, weather rocks, terrain seeds |
| Gauntlet 3 | Life Orb, Eviolite |
| Gauntlet 4 | **Focus Sash**, Assault Vest, Heavy-Duty Boots |
| Gauntlet 5 | **Choice items**, Rocky Helmet, Mental Herb, Weakness Policy, **first Mega Stones** |
| Gauntlet 6 | Covert Cloak, Clear Amulet, **doubles-leaning Mega Stones** |
| Gauntlet 7 | **All remaining Mega Stones** (Kangaskhanite is never sold). Booster Energy is never sold: the Oldale researcher pays one per Paradox species shown |

Focus Sash sits at gauntlet 4 deliberately. Under full healing, reusable items
and no bag access, a permanent guaranteed-survive in every battle is far
stronger here than in any official format.

Eviolite at gauntlet 3 rather than earlier: NFE Pokémon have artificially low
BST, so Eviolite systematically breaks the early caps.

---

## AI progression

Full offensive intelligence from gauntlet 1 — viability checking, HP awareness,
KO recognition, setup logic. No mercy, as specified.

**One exception:** hold smart switching until around gauntlet 3. With thin
early teams the CPU pivots pointlessly and battles read as tedious rather than
hard. Once teams have defensive cores worth pivoting between, turn it on.

**Omniscience is reserved for bosses only.** All eight of them.

Flag names have changed between expansion versions — check
`include/constants/battle_ai.h` in your checkout rather than copying names from
anywhere, including here.

---

## Open items

1. **Level 50 or 100.** Flat 50 is already implemented by the Frontier and is
   what VGC doubles theory is calculated against. Level 100 needs the facility's
   level-scaling changed.
2. **Doubles: 6v6, or team preview and pick 4?** Competitive doubles is pick-4.
   6v6 doubles runs long and shifts value toward bulk over positioning.
3. **Gauntlet 1 boss tuning** — see the note above.
4. **Sell-back?** Partial FP refunds would smooth mistakes further, though the
   per-battle FP award may make this unnecessary.

---

## Next step

Build gauntlet 1 as a complete vertical slice: the curated 405-BST pool, all
available CPU teams, the shop inventory, the boss, and the AI flags. One
gauntlet working end to end will surface problems no amount of planning catches.
