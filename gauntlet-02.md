# Gauntlet 2 — "The Second Slot"

Doubles, 6v6, level 50. BST cap 500. Six battles drawn from twelve, then the
boss.

**Design intent:** teach doubles. The player arrives having only fought
singles, and doubles is a different game — not a harder one, a different one.
Four systems have to land: spread damage, redirection, momentum, and speed
control.

**Structural conceit:** the twelve teams are four groups of three, each group
drilling one pillar. A player who draws six random battles will almost
certainly meet at least three of the four groups, and the shop sells the
answers to all of them.

| Group | Teams | Pillar | What it punishes |
|---|---|---|---|
| A | 1–3 | Spread damage | No Protect, no Wide Guard, clustering weak Pokémon |
| B | 4–6 | Redirection | Attacking the wrong target, no Taunt, no spread moves |
| C | 7–9 | Momentum & disruption | Slow setup, no Fake Out answer, fragile leads |
| D | 10–12 | Speed control | Static speed tiers, no Tailwind or Trick Room plan |

**Item clause applies.** No duplicate held items on a team.

---

## Bans at this tier

Carried forward from gauntlet 1: **Smeargle, Wobbuffet, Shedinja, Ditto,
Wishiwashi.** These break tiering at every level and stay banned permanently.

**New ban: Palafin** (457). Zero to Hero transforms it to 650 BST mid-battle,
which the cap cannot measure.

**Unbanned at this tier: Azumarill, Linoone, Medicham.** All three were banned
from gauntlet 1 for dominating a 420 BST field. At 500 they're strong but
answerable, and Medicham in particular is a legitimate doubles threat that
teaches Fake Out pressure. Watch Azumarill — Belly Drum behind a redirector is
the combination to look out for, and if it proves oppressive, ban the move
rather than the Pokémon.

---

## Pool additions

The gauntlet 1 pool stays purchasable. New at ≤500 BST, organized by the role
they teach:

**Redirection & support** — Amoonguss, Clefairy, Togetic, Indeedee, Gastrodon,
Jellicent, Lanturn, Klefki, Whimsicott, Comfey, Oranguru

**Spread attackers** — Golem, Mudsdale, Camerupt, Salazzle, Turtonator,
Magcargo, Swanna, Exploud, Zebstrika, Frosmoth, Houndoom, Vikavolt

**Momentum & disruption** — Hitmontop, Hariyama, Scrafty, Ambipom, Medicham,
Sableye, Mimikyu, Crawdaunt

**Bulk & pivots** — Toxapex, Bronzong, Corviknight, Dusclops, Garganacl,
Copperajah, Clodsire, Bewear, Drednaw

**Speed** — Barraskewda, Manectric, Araquanid, Azumarill, Jumpluff,
Alolan Raichu, Alolan Marowak

---

## Shop — gauntlet 2 additions

**One change from the design doc:** weather rocks and terrain seeds move to
gauntlet 3 rather than arriving here. Two reasons. Weather is gauntlet 3's
theme, so the tools should arrive with the gauntlet that teaches them. And
gauntlet 2's boss runs a rain team holding a Damp Rock — which only works as a
power gap if the player can't buy one yet.

| Item | FP | Why it matters here |
|---|---|---|
| Sitrus Berry | 180 | The default doubles item. Recovery without a turn spent |
| Lum Berry | 160 | The answer to Spore, Will-O-Wisp and Thunder Wave |
| Occa / Passho / Wacan / Shuca / Yache Berry | 120 each | Resist berries — survive one hit you shouldn't |
| Chople / Kebab / Rindo / Colbur Berry | 120 each | Same, wider coverage |
| Eviolite | — | **Not yet.** Gauntlet 3 |

Resist berries are the signature gauntlet 2 item. They're the first purchase
that requires the player to predict a specific threat rather than generically
improve a Pokémon, which is the exact mental shift doubles demands.

---

## AI flags

Same as gauntlet 1, with one addition: **the doubles-awareness flag**, if your
version exposes one separately. Check `include/constants/battle_ai.h`.

- Avoid clearly bad moves, try to KO, check viability, HP awareness
- Setup logic
- Smart replacement choice
- **Still no proactive switching** — that arrives at gauntlet 3
- Omniscient on the boss only, plus proactive switching for the boss

---

## Group A — Spread Damage

Teaches Protect, Wide Guard, and that a spread move hitting both your Pokémon
for 75% is usually better for the opponent than one hitting one for 100%.

### A1. Fault — Earthquake core

**Lead: Golem.** Sturdy guarantees it survives to click Earthquake once, and
every partner behind it is immune or resistant to Ground.

```
Golem @ Sitrus Berry
Ability: Sturdy
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Earthquake
- Rock Slide
- Protect
- Explosion

Bronzong @ Occa Berry
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Gyro Ball
- Zen Headbutt
- Hypnosis
- Protect

Swanna @ Sharp Beak
Ability: Keen Eye
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Hurricane
- Scald
- Tailwind
- Protect

Mudsdale @ Leftovers
Ability: Stamina
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- High Horsepower
- Heavy Slam
- Rock Slide
- Protect

Hawlucha @ White Herb
Ability: Unburden
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Acrobatics
- Close Combat
- Swords Dance
- Protect

Vikavolt @ Magnet
Ability: Levitate
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Thunderbolt
- Bug Buzz
- Energy Ball
- Protect
```

### A2. Undertow — Water spread with absorbers

**Lead: Gastrodon.** Storm Drain absorbs its own partner's Muddy Water, so the
team can spam Water moves with no friendly fire at all.

```
Gastrodon @ Sitrus Berry
Ability: Storm Drain
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Muddy Water
- Earth Power
- Recover
- Protect

Jellicent @ Leftovers
Ability: Water Absorb
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Surf
- Shadow Ball
- Will-O-Wisp
- Protect

Lanturn @ Wacan Berry
Ability: Volt Absorb
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Surf
- Thunderbolt
- Ice Beam
- Protect

Araquanid @ Mystic Water
Ability: Water Bubble
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Liquidation
- Leech Life
- Wide Guard
- Protect

Clawitzer @ Rindo Berry
Ability: Mega Launcher
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Water Pulse
- Aura Sphere
- Heal Pulse
- Protect

Barraskewda @ Sharp Beak
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Liquidation
- Close Combat
- Aqua Jet
- Protect
```

### A3. Pyroclast — Heat Wave core

**Lead: Salazzle.** Fastest thing on the team and Heat Wave hits both targets
before most tier-2 Pokémon can respond.

```
Salazzle @ Charcoal
Ability: Corrosion
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Heat Wave
- Sludge Bomb
- Nasty Plot
- Protect

Camerupt @ Sitrus Berry
Ability: Solid Rock
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Heat Wave
- Earth Power
- Yawn
- Protect

Turtonator @ Occa Berry
Ability: Shell Armor
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Flamethrower
- Dragon Pulse
- Body Press
- Protect

Magcargo @ Leftovers
Ability: Flame Body
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Lava Plume
- Power Gem
- Recover
- Protect

Marowak-Alola @ Spell Tag
Ability: Lightning Rod
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Shadow Bone
- Flare Blitz
- Will-O-Wisp
- Protect

Houndoom @ Black Glasses
Ability: Flash Fire
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Heat Wave
- Dark Pulse
- Nasty Plot
- Protect
```

---

## Group B — Redirection

Teaches that the obvious target isn't always the right one. Spread moves ignore
redirection entirely, which is the lesson underneath the lesson.

### B4. Spore Cloud — Amoonguss core

**Lead: Amoonguss.** Rage Powder plus Spore is the defining support package in
doubles. Everything behind it exists because Amoonguss buys it a free turn.

```
Amoonguss @ Sitrus Berry
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Spore
- Rage Powder
- Sludge Bomb
- Protect

Azumarill @ Leftovers
Ability: Huge Power
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Aqua Jet
- Play Rough
- Superpower
- Protect

Gengar @ Spell Tag
Ability: Cursed Body
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Shadow Ball
- Sludge Bomb
- Icy Wind
- Protect

Bronzong @ Occa Berry
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Gyro Ball
- Zen Headbutt
- Light Screen
- Protect

Manectric @ Magnet
Ability: Lightning Rod
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Flamethrower
- Volt Switch
- Protect

Hitmontop @ Black Belt
Ability: Intimidate
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Fake Out
- Close Combat
- Sucker Punch
- Wide Guard
```

### B5. Sanctuary — Follow Me and terrain

**Lead: Indeedee.** Psychic Surge blocks all priority, which shuts off Fake Out
and Aqua Jet, and Follow Me keeps the partner safe while it sets up.

```
Indeedee @ Twisted Spoon
Ability: Psychic Surge
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Expanding Force
- Follow Me
- Helping Hand
- Protect

Raichu-Alola @ Magnet
Ability: Surge Surfer
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Psychic
- Nasty Plot
- Protect

Clefairy @ Sitrus Berry
Ability: Friend Guard
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Follow Me
- Helping Hand
- Moonblast
- Protect

Medicham @ Black Belt
Ability: Pure Power
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Fake Out
- High Jump Kick
- Zen Headbutt
- Protect

Bewear @ Silk Scarf
Ability: Fluffy
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Double-Edge
- Drain Punch
- Ice Punch
- Protect

Gastrodon @ Passho Berry
Ability: Storm Drain
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Muddy Water
- Earth Power
- Recover
- Protect
```

### B6. Lightning Rod — redirection by ability

**Lead: Togetic.** Follow Me plus Serene Grace Thunder Wave. The team redirects
with both moves and abilities, so the player can't simply Taunt their way out.

```
Togetic @ Sitrus Berry
Ability: Serene Grace
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Follow Me
- Dazzling Gleam
- Thunder Wave
- Protect

Kleavor @ Silver Powder
Ability: Sharpness
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Stone Axe
- X-Scissor
- Swords Dance
- Protect

Vikavolt @ Magnet
Ability: Levitate
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Thunderbolt
- Bug Buzz
- Energy Ball
- Protect

Hariyama @ Black Belt
Ability: Thick Fat
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Fake Out
- Close Combat
- Knock Off
- Wide Guard

Klefki @ Leftovers
Ability: Prankster
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Thunder Wave
- Foul Play
- Light Screen
- Reflect

Frosmoth @ Never-Melt Ice
Ability: Ice Scales
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Blizzard
- Bug Buzz
- Quiver Dance
- Protect
```

---

## Group C — Momentum & Disruption

Teaches that doubles games are decided in the first three turns, and that a
turn spent doing nothing is worse here than in singles.

### C7. Opening Act — Fake Out pressure

**Lead: Hitmontop.** Intimidate on entry plus Fake Out is two forms of damage
reduction in one slot.

```
Hitmontop @ Black Belt
Ability: Intimidate
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Fake Out
- Close Combat
- Sucker Punch
- Wide Guard

Scrafty @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Fake Out
- Drain Punch
- Knock Off
- Protect

Whimsicott @ Leftovers
Ability: Prankster
EVs: 252 HP / 4 Def / 252 Spe
Timid Nature
- Encore
- Taunt
- Moonblast
- Tailwind

Manectric @ Magnet
Ability: Lightning Rod
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Flamethrower
- Volt Switch
- Protect

Crawdaunt @ Mystic Water
Ability: Adaptability
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Crabhammer
- Knock Off
- Aqua Jet
- Protect

Muk-Alola @ Shuca Berry
Ability: Poison Touch
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Poison Jab
- Snarl
- Knock Off
- Protect
```

### C8. Interference — Prankster status

**Lead: Sableye.** Priority Will-O-Wisp and Taunt before the player moves.
Note for the player: Dark-types are immune to Prankster status, and this team
has no answer to one.

```
Sableye @ Leftovers
Ability: Prankster
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Will-O-Wisp
- Taunt
- Recover
- Foul Play

Klefki @ Sitrus Berry
Ability: Prankster
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Thunder Wave
- Foul Play
- Light Screen
- Reflect

Oranguru @ Twisted Spoon
Ability: Inner Focus
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Instruct
- Psychic
- Trick Room
- Protect

Medicham @ Black Belt
Ability: Pure Power
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Fake Out
- High Jump Kick
- Zen Headbutt
- Protect

Salazzle @ Charcoal
Ability: Corrosion
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Heat Wave
- Sludge Bomb
- Nasty Plot
- Protect

Mimikyu @ Spell Tag
Ability: Disguise
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Play Rough
- Shadow Sneak
- Swords Dance
- Protect
```

### C9. Attrition — grinding pressure

**Lead: Ambipom.** Technician Fake Out, then Double Hit breaks Sturdy, Disguise
and Focus Sash all at once.

```
Ambipom @ Silk Scarf
Ability: Technician
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Fake Out
- Double Hit
- Knock Off
- Protect

Hariyama @ Black Belt
Ability: Thick Fat
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Fake Out
- Close Combat
- Knock Off
- Wide Guard

Toxapex @ Passho Berry
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Toxic
- Recover
- Haze

Corviknight @ Leftovers
Ability: Mirror Armor
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Brave Bird
- Bulk Up
- Roost
- Protect

Zebstrika @ Magnet
Ability: Sap Sipper
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Overheat
- Volt Switch
- Protect

Drednaw @ Hard Stone
Ability: Strong Jaw
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Liquidation
- Crunch
- Rock Slide
- Protect
```

---

## Group D — Speed Control

Teaches the single most important fact about doubles: whoever moves first
usually wins, and speed is something you set rather than something you have.

### D10. Slipstream — Tailwind offense

**Lead: Whimsicott.** Prankster Tailwind goes up before anything else can act,
and Encore locks a Protect user into uselessness for three turns.

```
Whimsicott @ Sitrus Berry
Ability: Prankster
EVs: 252 HP / 4 Def / 252 Spe
Timid Nature
- Tailwind
- Encore
- Taunt
- Moonblast

Swanna @ Sharp Beak
Ability: Keen Eye
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Tailwind
- Hurricane
- Scald
- Protect

Barraskewda @ Mystic Water
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Liquidation
- Close Combat
- Aqua Jet
- Protect

Salazzle @ Charcoal
Ability: Corrosion
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Heat Wave
- Sludge Bomb
- Nasty Plot
- Protect

Manectric @ Magnet
Ability: Lightning Rod
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Flamethrower
- Volt Switch
- Protect

Mimikyu @ Spell Tag
Ability: Disguise
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Play Rough
- Shadow Sneak
- Swords Dance
- Protect
```

### D11. Inversion — Trick Room

**Lead: Bronzong.** Levitate and enormous bulk mean it survives to set Trick
Room, and Gyro Ball gets stronger the slower it is.

```
Bronzong @ Sitrus Berry
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Trick Room
- Gyro Ball
- Zen Headbutt
- Protect

Dusclops @ Leftovers
Ability: Pressure
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Trick Room
- Night Shade
- Will-O-Wisp
- Protect

Mudsdale @ Passho Berry
Ability: Stamina
EVs: 252 HP / 252 Atk / 4 Def
Brave Nature
- High Horsepower
- Heavy Slam
- Rock Slide
- Protect

Camerupt @ Charcoal
Ability: Solid Rock
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Heat Wave
- Earth Power
- Yawn
- Protect

Wailord @ Mystic Water
Ability: Pressure
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Water Spout
- Ice Beam
- Hydro Pump
- Protect

Bewear @ Silk Scarf
Ability: Fluffy
EVs: 252 HP / 252 Atk / 4 Def
Brave Nature
- Double-Edge
- Drain Punch
- Ice Punch
- Protect
```

### D12. Tempo — Trick Room with Instruct

**Lead: Oranguru.** Sets Trick Room, then Instruct makes the partner attack a
second time in the same turn. Two slow heavy hitters moving twice each is the
fastest clock in the gauntlet.

```
Oranguru @ Twisted Spoon
Ability: Inner Focus
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Trick Room
- Instruct
- Psychic
- Protect

Garganacl @ Sitrus Berry
Ability: Purifying Salt
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Salt Cure
- Body Press
- Recover
- Protect

Copperajah @ Hard Stone
Ability: Sheer Force
EVs: 252 HP / 252 Atk / 4 Def
Brave Nature
- Heavy Slam
- High Horsepower
- Iron Head
- Protect

Amoonguss @ Passho Berry
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Spore
- Rage Powder
- Sludge Bomb
- Protect

Marowak-Alola @ Spell Tag
Ability: Lightning Rod
EVs: 252 HP / 252 Atk / 4 Def
Brave Nature
- Shadow Bone
- Flare Blitz
- Will-O-Wisp
- Protect

Frosmoth @ Never-Melt Ice
Ability: Ice Scales
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Blizzard
- Bug Buzz
- Quiver Dance
- Protect
```

---

## Boss — Tidewarden Juan

**Pool:** gauntlet 3 (≤550 BST) plus everything prior.

**Gimmick:** permanent rain. Pelipper's Drizzle sets it on entry, and four
teammates have Swift Swim or Dry Skin. Under rain the entire team doubles its
Speed and every Water move hits 50% harder.

**The power gap:** Damp Rock is a gauntlet 3 item. The player cannot buy one,
so they cannot field a rain team of their own — they have to beat it from the
outside.

**AI:** omniscient, proactive switching enabled, no ace flag.

```
Pelipper @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hurricane
- Scald
- Tailwind
- Protect

Kingdra @ Mystic Water
Ability: Swift Swim
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Muddy Water
- Draco Meteor
- Ice Beam
- Protect

Kabutops @ Hard Stone
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Liquidation
- Stone Edge
- Aqua Jet
- Protect

Seismitoad @ Sitrus Berry
Ability: Swift Swim
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Muddy Water
- Earth Power
- Sludge Bomb
- Protect

Ludicolo @ Leftovers
Ability: Swift Swim
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Surf
- Giga Drain
- Ice Beam
- Fake Out

Toxicroak @ Black Belt
Ability: Dry Skin
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Drain Punch
- Gunk Shot
- Fake Out
- Protect
```

### Counterplay available at tier 2

Deliberately multiple routes, so this isn't a lock-and-key:

- **Trick Room** inverts the entire gimmick. Swift Swim doubling their Speed
  becomes a liability. Bronzong, Dusclops and Oranguru all set it, and all
  three are in the tier 2 shop.
- **Storm Drain Gastrodon** absorbs every Water move on the team, including the
  spread ones, and gets a Special Attack boost for it.
- **Water Absorb Jellicent** and **Volt Absorb Lanturn** do similar work.
- **Electric types** punish rain — Thunder never misses in it, and Water is
  weak to Electric. Vikavolt, Manectric, Zebstrika, Lanturn.
- **Amoonguss** Spore doesn't care how fast anything is.
- **Whimsicott** Prankster Taunt shuts off Pelipper's Tailwind, and Encore
  traps a Protect.

### Benchmark counter-team

Built only from gauntlet 2's pool, items and bans. Item clause compliant.

```
Bronzong @ Sitrus Berry
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Trick Room
- Gyro Ball
- Zen Headbutt
- Protect

Gastrodon @ Passho Berry
Ability: Storm Drain
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Muddy Water
- Earth Power
- Recover
- Protect

Lanturn @ Wacan Berry
Ability: Volt Absorb
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Thunder
- Ice Beam
- Surf
- Protect

Amoonguss @ Leftovers
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Spore
- Rage Powder
- Sludge Bomb
- Protect

Vikavolt @ Magnet
Ability: Levitate
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Thunder
- Bug Buzz
- Energy Ball
- Protect

Mudsdale @ Mystic Water
Ability: Stamina
EVs: 252 HP / 252 Atk / 4 Def
Brave Nature
- High Horsepower
- Heavy Slam
- Rock Slide
- Protect
```

**Game plan.** Lead Bronzong and Amoonguss. Set Trick Room turn one while
Amoonguss redirects with Rage Powder or removes a threat with Spore. Under
Trick Room the whole boss team moves last, and Thunder from Lanturn and
Vikavolt never misses in their own rain. Gastrodon is the safety valve — it
absorbs Muddy Water, Surf and Scald, so bringing it in on a predicted spread
move gains a free turn and a Special Attack boost.

**Note on the Brave and Quiet natures.** Nearly every Pokémon here wants
minimum Speed, because Trick Room rewards being slow. This is the first
gauntlet where the optimal spread isn't "max the attacking stat and max
Speed," which is a genuine conceptual step for the player.

---

## Open for playtesting

1. **Is rain too much for a second boss?** It's a coherent, well-supported
   archetype and the counterplay is real, but the speed swing under Drizzle is
   large. Watch whether a player without Trick Room has any path at all.
2. **Redirection frequency.** Three teams in group B lean on Follow Me or Rage
   Powder. If it reads as repetitive rather than instructive, vary B6 toward
   ability-based redirection only.
3. **Azumarill.** Newly unbanned. Watch for Belly Drum behind a redirector.
4. **Protect on almost everything.** This is correct for doubles and matches
   real play, but it lengthens games. If matches drag, trim Protect from the
   bulkiest Pokémon rather than the frail ones.
