# Competitive Reference — Ten Buildings

Working reference for building CPU teams. Organized for lookup, not reading
front to back.

---

## Format notes for this ROM

Flat level 50, both formats, Megas available late. The expansion supports
Terastallization, Z-Moves, Dynamax and Gigantamax alongside Megas, all
config-toggleable.

**Recommendation: disable Tera, keep Megas.** Tera invalidates type-based
teambuilding — every defensive read becomes a coinflip, and the CPU AI handles
it poorly, which makes fights feel arbitrary rather than hard. Megas are a
cleaner endgame unlock and you've already built your progression around them.
If you keep Tera, the whole tier structure needs rethinking, because Tera
compresses the power gap between a 480 BST Pokémon and a 600 one.

---

## Problem 1: BST caps don't measure power

This is the biggest issue with the current gating plan.

BST correlates weakly with competitive viability. A sample of what sits where:

| Pokémon | BST | Competitive standing |
|---|---|---|
| Azumarill | 420 | Huge Power makes it a genuine threat |
| Pelipper | 430 | Defines rain teams via Drizzle |
| Gligar | 430 | With Eviolite, a top-tier wall |
| Amoonguss | 464 | Premier doubles support, all formats |
| Whimsicott | 480 | Prankster Tailwind — top 10 in VGC usage |
| Goodra | 600 | Pseudo-legendary, rarely viable |
| Kommo-o | 600 | Pseudo-legendary, niche at best |

Under a pure BST cap, building 5 "unlocks pseudo-legendaries" and hands the
player Goodra, which is worse than the Whimsicott they had at building 2.
Meanwhile Drizzle Pelipper at 430 BST enables an entire archetype at building 1.

**Fix:** use BST as a first-pass filter, then hand-curate every pool. Keep an
explicit allow-list per tier rather than a formula. The curation is the design
work — the number is just a sorting aid.

### Specific: building 1 at 400 BST is nearly empty

At or below 400 BST there is almost nothing competitively functional. Sableye
(380) and Mawile (380) are the notable names and both are defined by their
Megas, which you've gated to building 6+. You'd be asking players to build a
team out of scraps.

**Suggest raising building 1 to ~460.** That opens Azumarill, Pelipper,
Amoonguss, Breloom, Rotom formes, Gligar, Torkoal — enough for real
teambuilding, and still clearly "little league" against later tiers.

### Eviolite breaks BST caps

NFE Pokémon get a 1.5× defensive multiplier from Eviolite, and their BST is
artificially low because it's measured pre-evolution. Gligar (430), Dusclops
(455), Chansey (450), Porygon2 (515) and Type: Null (534) all punch far above
their tier under a cap. Gate Eviolite deliberately — it's a mid-tier item, not
an early one, despite feeling basic.

---

## Problem 2: Max AI from building 1

You want no mercy from the start, which is a defensible choice, but be aware of
what the flags actually do. Smart switching in particular makes the CPU pivot
constantly, which reads as tedious rather than difficult when the teams are
weak — the player spends six turns chasing something that keeps running.

**Suggest:** full offensive intelligence from building 1 (viability checking,
HP awareness, KO recognition, setup logic), but hold smart switching until
around building 3 when the CPU teams have defensive cores worth pivoting
between. Omniscience on bosses only, as you said, is exactly right.

---

## Singles fundamentals

### The four win conditions

Every singles team should have a plan that falls into one of these, and CPU
teams become interesting when their plan is legible but hard to stop.

1. **Setup sweep** — boost, then clean. Needs hazard support and a way past
   priority. Counters: phazing, unaware walls, priority, status.
2. **Wallbreak** — Choice-locked or Life Orb heavy hitters removing walls so a
   teammate cleans. Counters: bulky pivots, Intimidate, speed advantage.
3. **Stall / attrition** — win on PP, hazards and recovery. Counters: taunt,
   setup sweepers, breaking power, Magic Guard.
4. **Hyper offense** — hazard stack plus relentless pressure, accept trades.
   Counters: priority, hazard removal, bulky resists.

### Hazard theory

Stealth Rock is the single most valuable move in singles. Damage on entry
compounds across a long gauntlet format like yours, where the player can't heal
between battles if you follow Frontier convention.

- Setters: Landorus-T, Garchomp, Ting-Lu, Glimmora, Tyranitar
- Removal: Defog (Corviknight, Zapdos), Rapid Spin (Great Tusk, Cinccino),
  Mortal Spin (Glimmora), Court Change (Cinderace)
- Heavy-Duty Boots negate hazards entirely — a significant item, gate it
  thoughtfully

**Design note:** your buildings are gauntlets. If HP and PP carry between the
seven battles, hazard chip becomes brutally strong and the format shifts toward
attrition. If everything heals between battles, hazards are much weaker and
offense dominates. **This is an unresolved decision in your design and it
changes everything about team construction.**

### Speed tiers that matter at level 50

Base speed benchmarks worth building around. At level 50 with max investment
and a positive nature, the practical cutoffs cluster here:

| Base speed | Notable | Why it matters |
|---|---|---|
| 135+ | Dragapult, Flutter Mane, Regieleki | Outspeeds nearly everything unboosted |
| 120–130 | Weavile, Zeraora, Chi-Yu | The "fast" bracket |
| 100–110 | Garchomp, Great Tusk, Kingambit (no) | Contested — small EV shifts decide |
| 80–95 | Incineroar, Urshifu, Bisharp | Scarf or Tailwind territory |
| Under 60 | Iron Hands, Torkoal, Ting-Lu | Trick Room candidates |

Base 100 is the historic benchmark. A CPU Pokémon tuned to outspeed base 100 by
one point is a common, nasty trick — worth using on bosses.

---

## Doubles fundamentals

Doubles is a different game, and this is where your alternating structure pays
off. Four pillars, in rough priority order:

### 1. Speed control (mandatory)

Doubles is decided by who moves first. Every serious team has one of:

- **Tailwind** — Whimsicott (Prankster), Tornadus, Pelipper, Talonflame
- **Trick Room** — Hatterene, Indeedee, Cresselia, Porygon2, Dusclops
- **Icy Wind / Electroweb** — spread speed drops, subtler and harder to counter
- **Choice Scarf** — on one mon, individually rather than team-wide

A CPU team with no speed control is free. A CPU team that sets Tailwind turn 1
and then hits hard is a real fight.

### 2. Redirection and protection

- **Follow Me / Rage Powder** — Amoonguss, Indeedee-F, Clefairy, Smeargle
- **Protect** — near-universal; roughly 80%+ of competitive doubles Pokémon run
  it. CPU teams without Protect feel obviously artificial
- **Wide Guard** — blocks spread moves, a hard counter to spread-based teams
- **Ally Switch** — high-risk position swapping

Amoonguss with Spore plus Rage Powder is arguably the strongest support
Pokémon in the format and should be a mid-tier unlock, not an early one.

### 3. Spread damage

Moves hitting both opponents take a 0.75× multiplier but often net more total
damage. Earthquake, Rock Slide, Heat Wave, Blizzard, Muddy Water, Dazzling
Gleam, Make It Rain. Rock Slide's 30% flinch chance across two targets is a
genuine win condition, not just chip.

### 4. Ability synergy

This is where doubles teams stop being "six good Pokémon" and become a team:

- **Intimidate** (Incineroar, Landorus-T, Arcanine) — hits both opponents
- **Prankster** (Whimsicott, Grimmsnarl, Tornadus) — priority status
- **Weather** (Pelipper, Torkoal, Tyranitar, Abomasnow) — enables partners
- **Psychic Surge** (Indeedee) — blocks all priority, shuts down Fake Out
- **Friend Guard** (Clefairy) — 25% damage reduction to the partner
- **Fake Out** users — free turn, momentum, disruption

### Lead theory

The lead pair is the most important decision in a doubles game. Standard
patterns worth giving CPU teams:

- **Redirector + setup sweeper** — Amoonguss covers a Dragon Dance
- **Fake Out + wallbreaker** — Incineroar buys a free turn
- **Weather setter + abuser** — Pelipper into Swift Swim
- **Trick Room setter + slow attacker** — Hatterene into Iron Hands

---

## Boss design

Your rule — bosses use next tier's unlocks — is the best idea in the design.
It creates a genuine power gap the player has to outplay rather than outgear.
Two guardrails:

**Give bosses a legible gimmick, not just better stats.** A boss whose team is
"the same but stronger" is frustrating. A boss built entirely around Trick Room
that the player must disrupt is a puzzle. The player should be able to lose,
understand why, and rebuild.

**Bosses should have a weakness the player's current tier can reach.** If
building 5's boss has a Mega the player can't own, the counterplay should be
something available at tier 5 — Encore, Taunt, priority, a status shutdown. The
answer must exist in the player's current shop.

---

## Item progression

Items decide more than species in a flat-level format. Rough ordering by how
much strategic weight they carry:

**Low** — type-boosting items (Charcoal, Mystic Water), pinch berries, Leftovers
**Medium** — resist berries, Sitrus, Eviolite, weather rocks, terrain seeds
**High** — Choice items, Life Orb, Assault Vest, Focus Sash, Heavy-Duty Boots
**Very high** — Covert Cloak, Clear Amulet, Safety Goggles, Rocky Helmet,
Mental Herb, Booster Energy
**Endgame** — Mega Stones

Your instinct to hold Choice items until building 3+ is right. Choice items
aren't strictly "strong" — they're a commitment mechanic that teaches
prediction, which is exactly the skill a mid-tier building should be testing.

Note on reusability: making held items reusable is the correct call for a
roguelite economy, and mechanically it's a matter of restoring consumed items
at run end. The Frontier already restores party state between attempts, so this
is a small change rather than a new system.

---

## Open decisions this document can't resolve

1. **Tera on or off** — changes everything downstream
2. **Does HP/PP carry between the seven battles?** — determines whether hazards
   and attrition matter at all
3. **Is the player's team of six locked at run start, or do they pick from a
   larger roster per battle?** — Frontier convention is pick before entering
4. **Boss Pokémon: strictly next-tier-only, or next-tier plus current?** —
   strictly next-tier may leave bosses with thin team options in early buildings
