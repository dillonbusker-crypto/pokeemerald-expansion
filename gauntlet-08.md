# Gauntlet 8 — "The Summit"

**Battle Pyramid.** Doubles, 6v6, level 50. Six battles drawn from twelve,
then the boss, **Pyramid King Brandon**. The last gauntlet: clearing it
starts the endgame (`storyline.md`, "After gauntlet 8: the Crown").

> **Status: built** (see "Implementation notes" at the end). The endgame
> after it isn't.

---

## The idea: all-out doubles

Gauntlet 7 was all-out singles; this is all-out doubles. Everything from
waves 0–6 is still on sale, so the CPU teams use the whole roster, and wave 7
adds the last step up: **the legendary Megas** and the doubles-leaning stones.

**Name:** *The Summit* (chosen for the build; easy to change, see
"Implementation notes").

### Decisions this doc assumes ❓

These were open questions in `gauntlet-07.md`; the drafts below use these
answers, and are easy to change.

1. **The BST cap stays 600** on base species. No legendary over 600 is ever
   sold.
2. **Zygardite is never sold** (Mega Zygarde is 778).
3. **Floette-Eternal and Floettite are sold in wave 7**, for one Fairy Aura
   doubles team (D12).
4. **Zygardite is Brandon's.** Mega Zygarde (778) is the one Mega the player
   can't own (the boss rule); it reaches the player only in the endgame's
   free shop. Diancite stays in wave 7.
5. **Brandon breaks the cap on purpose:** his team is the strongest doubles
   team the game can field, with one box-art legendary (**Miraidon**).
   Scott's legendaries (Rayquaza, Groudon, Kyogre, Mewtwo) stay his.

---

## Wave 7: shop additions for gauntlet 8

No ability overrides: the player sets abilities with the L menu.

### Keeper 3 — Mega Stones

| Tier | FP | Stone | Mega | Why |
|---|---|---|---|---|
| Legendary | 1,200 | Darkranite | Darkrai (700, Bad Dreams) | |
| Legendary | 1,200 | Magearnite | Magearna (700, Soul-Heart) | |
| Legendary | 1,200 | Zeraorite | Zeraora (700, Volt Absorb) | Spenser's Mega, now the player's |
| Legendary | 1,200 | Heatranite | Heatran (700, Flash Fire) | |
| Legendary | 1,200 | Diancite | Diancie (700, Magic Bounce) | |
| Strong | 750 | Floettite | Floette (651, Fairy Aura) | Boosts *both* sides' Fairy moves, its ally's included |
| Strong | 750 | Ampharosite | Ampharos (610, Mold Breaker) | Trick Room special attacker |
| Strong | 750 | Aggronite | Aggron (630, Filter) | Trick Room tank |
| Strong | 750 | Steelixite | Steelix (610, Sand Force) | Trick Room and sand |
| Standard | 300 | Audinite | Audino (545, Healer) | Doubles support |
| Standard | 300 | Glalitite | Glalie (580, Refrigerate) | Ice-type Explosion and Hyper Voice |

### Keeper 4 — Pokémon

| Tier | Pokémon |
|---|---|
| Strong 1,150 | Floette-Eternal (551) |

Everything else doubles-relevant was moved into earlier gauntlets.

### Keeper 2 — Held items

| Item | FP | Why it matters in doubles |
|---|---|---|
| Wide Lens | 150 | Spread-move accuracy: Rock Slide, Blizzard, Hurricane, Electroweb |
| Ring Target | 150 | Removes the holder's immunities. Lets an ally hit it (Earthquake onto a Flying partner) or makes a Tricked foe hittable |

---

## The twelve teams

**Design intent:** the doubles finale. Every doubles tool the player has met
(spread moves, redirection, speed control, terrain, weather) at full power,
now with Ubers-grade Pokémon and legendary Megas. Each group is one way a
top doubles team wins, and the player meets at least three of four.

**Rules for the pool teams:** only Pokémon, Mega Stones and items sold by
wave 7. One Mega per team (Kangaskhanite stays Norman's gift, so no CPU Mega
Kangaskhan). Item clause compliant. No sleep-inducing moves, evasion or OHKO
moves on CPU teams. Trick Room attackers carry 0 Speed IVs.

**AI:** same as gauntlet 6 for pool trainers: full offensive intelligence,
smart replacement choice, proactive switching, not omniscient.

| Group | Teams | Archetype | What it punishes |
|---|---|---|---|
| A | 1–3 | Weather wars | No weather of your own, no way to reset theirs |
| B | 4–6 | Trick Room | Fast teams with no Trick Room answer (Taunt, Imprison, your own setter) |
| C | 7–9 | Tailwind and legendary offense | No speed control, no Intimidate, no Wide Guard |
| D | 10–12 | Disruption and gimmicks | Teams that can't adapt: Perish trap, Fairy Aura, terrain |

---

## Group A — Weather wars

### A1. Sunstroke — Mega Charizard Y

**Lead: Torkoal and Venusaur.** Sun goes up, Venusaur's Chlorophyll doubles
its Speed, and Torkoal's Eruption hits both foes at full power. **Mega Charizard Y** keeps the sun if it's taken away. The lesson:
reset the weather, and Fake Out the Eruption.

```
Torkoal @ Heat Rock
Ability: Drought
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Spe
Quiet Nature
- Eruption
- Heat Wave
- Earth Power
- Protect

Venusaur @ Focus Sash
Ability: Chlorophyll
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Leaf Storm
- Earth Power
- Sludge Bomb
- Protect

Charizard @ Charizardite Y
Ability: Solar Power
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Heat Wave
- Solar Beam
- Scorching Sands
- Protect

Walking Wake @ Choice Specs
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Hydro Steam
- Draco Meteor
- Flamethrower
- Snarl

Gouging Fire @ Clear Amulet
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Flare Blitz
- Dragon Claw
- Burning Bulwark
- Howl

Incineroar @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Fake Out
- Flare Blitz
- Knock Off
- Parting Shot
```

### A2. Torrent — Mega Swampert

**Lead: Pelipper and Archaludon.** Rain makes Archaludon's Electro Shot fire
in one turn. **Mega Swampert** (Swift Swim) and Basculegion double their
Speed. The lesson: Wide Guard and a weather reset, or two sweepers outspeed
everything.

```
Pelipper @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Hurricane
- Weather Ball
- Tailwind
- Protect

Archaludon @ Assault Vest
Ability: Stamina
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Electro Shot
- Draco Meteor
- Flash Cannon
- Body Press

Swampert @ Swampertite
Ability: Torrent
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Waterfall
- High Horsepower
- Ice Punch
- Protect

Basculegion @ Choice Band
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Wave Crash
- Last Respects
- Aqua Jet
- Flip Turn

Urshifu-Rapid-Strike @ Focus Sash
Ability: Unseen Fist
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Surging Strikes
- Close Combat
- Aqua Jet
- Protect

Amoonguss @ Rocky Helmet
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Spore
- Rage Powder
- Pollen Puff
- Protect
```

*(Amoonguss's Spore is the one sleep move on a CPU team, kept because Rage
Powder plus Spore is the core of redirection. See open question 3.)*

### A3. Sandblast — Mega Tyranitar

**Lead: Mega Tyranitar and Excadrill.** Sand up, Excadrill doubles its
Speed, and Rock Slide flinches. Glimmora's Toxic Debris lays hazards when
it's hit. The lesson: Intimidate and Wide Guard blunt the spread damage;
Water and Grass break the core.

```
Tyranitar @ Tyranitarite
Ability: Sand Stream
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Rock Slide
- Knock Off
- Low Kick
- Protect

Excadrill @ Life Orb
Ability: Sand Rush
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- High Horsepower
- Iron Head
- Rock Slide
- Protect

Glimmora @ Focus Sash
Ability: Toxic Debris
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Power Gem
- Sludge Bomb
- Earth Power
- Spiky Shield

Landorus-Therian @ Choice Scarf
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Stomping Tantrum
- Rock Slide
- U-turn
- Knock Off

Gholdengo @ Covert Cloak
Ability: Good as Gold
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Make It Rain
- Shadow Ball
- Nasty Plot
- Protect

Kingambit @ Black Glasses
Ability: Defiant
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Kowtow Cleave
- Sucker Punch
- Iron Head
- Protect
```

---

## Group B — Trick Room

### B4. Grand Slam — Mega Aggron

**Lead: Indeedee and Hatterene.** Psychic Terrain blocks Fake Out on the
setter, Follow Me covers it, Trick Room goes up. Then **Mega Aggron** (Filter)
and Bloodmoon Ursaluna move first. The lesson: Taunt or Imprison the setter,
or out-damage the room.

```
Indeedee-F @ Psychic Seed
Ability: Psychic Surge
EVs: 252 HP / 252 Def / 4 SpD
IVs: 0 Spe
Relaxed Nature
- Follow Me
- Expanding Force
- Helping Hand
- Protect

Hatterene @ Sitrus Berry
Ability: Magic Bounce
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Spe
Quiet Nature
- Trick Room
- Expanding Force
- Dazzling Gleam
- Protect

Aggron @ Aggronite
Ability: Sturdy
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Heavy Slam
- Rock Slide
- Body Press
- Protect

Ursaluna-Bloodmoon @ Life Orb
Ability: Mind's Eye
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Spe
Quiet Nature
- Blood Moon
- Hyper Voice
- Earth Power
- Protect

Iron Hands @ Assault Vest
Ability: Quark Drive
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Fake Out
- Drain Punch
- Wild Charge
- Heavy Slam

Torkoal @ Charcoal
Ability: Drought
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Spe
Quiet Nature
- Eruption
- Heat Wave
- Earth Power
- Protect
```

### B5. Static Room — Mega Ampharos

**Lead: Farigiraf and Cresselia**, two Trick Room setters. Armor Tail stops
priority on the whole side. **Mega Ampharos** (Mold Breaker) and Glastrier
(30 Speed) hit hardest under the room. The lesson: two setters means one
answer isn't enough.

```
Farigiraf @ Mental Herb
Ability: Armor Tail
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Spe
Quiet Nature
- Trick Room
- Psychic Noise
- Hyper Voice
- Protect

Cresselia @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
IVs: 0 Spe
Relaxed Nature
- Trick Room
- Helping Hand
- Moonblast
- Psychic

Ampharos @ Ampharosite
Ability: Static
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Spe
Quiet Nature
- Thunderbolt
- Dragon Pulse
- Focus Blast
- Protect

Glastrier @ Choice Band
Ability: Chilling Neigh
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Icicle Crash
- High Horsepower
- Close Combat
- Heavy Slam

Ursaluna @ Flame Orb
Ability: Guts
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Facade
- Headlong Rush
- Close Combat
- Protect

Amoonguss @ Sitrus Berry
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
IVs: 0 Spe
Relaxed Nature
- Spore
- Rage Powder
- Pollen Puff
- Protect
```

### B6. Heavy Metal — Mega Steelix

**Lead: Bronzong and Hippowdon.** Trick Room and sand together: **Mega
Steelix** (Sand Force) and Copperajah (Sheer Force) swing Heavy Slam and
Rock Slide. The lesson: Fire and Water break a Steel wall; Fighting breaks
it faster.

```
Bronzong @ Mental Herb
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
IVs: 0 Spe
Relaxed Nature
- Trick Room
- Gyro Ball
- Body Press
- Imprison

Hippowdon @ Smooth Rock
Ability: Sand Stream
EVs: 252 HP / 4 Atk / 252 SpD
IVs: 0 Spe
Sassy Nature
- High Horsepower
- Slack Off
- Yawn
- Protect

Steelix @ Steelixite
Ability: Sturdy
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Heavy Slam
- Rock Slide
- High Horsepower
- Protect

Copperajah @ Life Orb
Ability: Sheer Force
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Heavy Slam
- Iron Head
- Rock Slide
- Protect

Stakataka @ Assault Vest
Ability: Beast Boost
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Gyro Ball
- Rock Slide
- High Horsepower
- Trick Room

Iron Hands @ Booster Energy
Ability: Quark Drive
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Fake Out
- Drain Punch
- Wild Charge
- Protect
```

---

## Group C — Tailwind and legendary offense

### C7. Gale Force — Mega Salamence

**Lead: Tornadus and Flutter Mane.** Prankster Tailwind, then Ubers-grade
attackers move twice as fast. **Mega Salamence** (Aerilate) turns Hyper
Voice into a Flying spread move. The lesson: Intimidate, Wide Guard, and
your own Tailwind or Icy Wind.

```
Tornadus @ Covert Cloak
Ability: Prankster
EVs: 252 HP / 4 SpD / 252 Spe
Timid Nature
- Tailwind
- Bleakwind Storm
- Taunt
- Protect

Flutter Mane @ Booster Energy
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Moonblast
- Shadow Ball
- Dazzling Gleam
- Protect

Chi-Yu @ Choice Specs
Ability: Beads of Ruin
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Heat Wave
- Dark Pulse
- Overheat
- Snarl

Chien-Pao @ Focus Sash
Ability: Sword of Ruin
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Icicle Crash
- Sucker Punch
- Sacred Sword
- Protect

Salamence @ Salamencite
Ability: Intimidate
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Hyper Voice
- Draco Meteor
- Flamethrower
- Protect

Urshifu @ Choice Scarf
Ability: Unseen Fist
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Wicked Blow
- Close Combat
- U-turn
- Sucker Punch
```

### C8. Live Wire — Mega Zeraora

**Lead: Tapu Koko and Regieleki.** Electric Terrain and Electroweb: the
player slows down while Electric attacks get stronger. **Mega Zeraora** (700)
cleans up with Plasma Fists. The lesson: a Ground type isn't enough on its
own (Kilowattrel and the terrain are built to punish it); bring Lightning Rod
or Volt Absorb.

```
Tapu Koko @ Choice Specs
Ability: Electric Surge
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Thunderbolt
- Dazzling Gleam
- Volt Switch
- Discharge

Regieleki @ Focus Sash
Ability: Transistor
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Electroweb
- Thunderbolt
- Volt Switch
- Protect

Zeraora @ Zeraorite
Ability: Volt Absorb
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Plasma Fists
- Close Combat
- Fake Out
- Protect

Iron Hands @ Assault Vest
Ability: Quark Drive
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Fake Out
- Drain Punch
- Wild Charge
- Heavy Slam

Kilowattrel @ Sitrus Berry
Ability: Competitive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Tailwind
- Electroweb
- Hurricane
- Protect

Gholdengo @ Life Orb
Ability: Good as Gold
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Make It Rain
- Shadow Ball
- Nasty Plot
- Protect
```

### C9. Dark Heart — Mega Darkrai

**Lead: Incineroar and Ogerpon-Hearthflame.** Fake Out and Follow Me buy
**Mega Darkrai** (700, Bad Dreams) turns to Nasty Plot. Grimmsnarl's screens
keep the frail attackers alive. The lesson: Fairy and Fighting types, and
Intimidate doesn't stop special attackers.

```
Incineroar @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Fake Out
- Flare Blitz
- Knock Off
- Parting Shot

Ogerpon-Hearthflame @ Hearthflame Mask
Ability: Mold Breaker
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Ivy Cudgel
- Horn Leech
- Follow Me
- Spiky Shield

Darkrai @ Darkranite
Ability: Bad Dreams
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Dark Pulse
- Sludge Bomb
- Nasty Plot
- Protect

Grimmsnarl @ Light Clay
Ability: Prankster
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Reflect
- Light Screen
- Spirit Break
- Thunder Wave

Roaring Moon @ Booster Energy
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Knock Off
- Acrobatics
- Protect

Hydreigon @ Choice Specs
Ability: Levitate
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Dark Pulse
- Draco Meteor
- Flamethrower
- Snarl
```

---

## Group D — Disruption and gimmicks

### D10. Bedrock — Mega Heatran

**Lead: Rillaboom and Mega Heatran.** Grassy Terrain heals and weakens the
player's Earthquakes, which is exactly what threatens Heatran. **Mega Heatran**
(700) fires Heat Wave and Earth Power from behind it. Tapu Fini's Misty
Terrain is the fallback. The lesson: two terrains, two plans.

```
Rillaboom @ Assault Vest
Ability: Grassy Surge
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Fake Out
- Grassy Glide
- Wood Hammer
- U-turn

Heatran @ Heatranite
Ability: Flash Fire
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Heat Wave
- Earth Power
- Flash Cannon
- Protect

Tapu Fini @ Leftovers
Ability: Misty Surge
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Moonblast
- Muddy Water
- Calm Mind
- Protect

Landorus-Therian @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Stomping Tantrum
- Rock Slide
- U-turn
- Protect

Urshifu-Rapid-Strike @ Focus Sash
Ability: Unseen Fist
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Surging Strikes
- Close Combat
- Aqua Jet
- Protect

Dragapult @ Choice Specs
Ability: Infiltrator
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Shadow Ball
- Flamethrower
- U-turn
```

### D11. Perish Trap — Mega Gengar

**Mega Gengar** (Shadow Tag) traps both of the player's Pokémon, then Perish
Song counts them down. Politoed sings too, and Whimsicott Encores whatever
the player tries. The lesson: **Shed Shell** and Ghost types can't be
trapped, and switching is the only way out once the count starts.

```
Gengar @ Gengarite
Ability: Cursed Body
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Perish Song
- Shadow Ball
- Sludge Bomb
- Protect

Whimsicott @ Covert Cloak
Ability: Prankster
EVs: 252 HP / 4 Def / 252 Spe
Timid Nature
- Encore
- Tailwind
- Moonblast
- Protect

Politoed @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Perish Song
- Icy Wind
- Helping Hand
- Protect

Amoonguss @ Rocky Helmet
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Rage Powder
- Pollen Puff
- Clear Smog
- Protect

Kingambit @ Black Glasses
Ability: Defiant
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Kowtow Cleave
- Sucker Punch
- Iron Head
- Protect

Archaludon @ Leftovers
Ability: Stamina
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Electro Shot
- Draco Meteor
- Flash Cannon
- Protect
```

*(Politoed's Drizzle makes Archaludon's Electro Shot instant.)*

### D12. Fairy Ring — Mega Floette

**Mega Floette** (651, Fairy Aura) boosts every Fairy move on the field,
including its partners'. Flutter Mane, Iron Valiant and Tapu Lele stack
Fairy damage on top, and Tapu Lele's Psychic Terrain blocks the player's
priority. The lesson: Steel and Poison types, and
Fairy Aura boosts the player's Fairy moves too.

```
Floette-Eternal @ Floettite
Ability: Flower Veil
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Light of Ruin
- Moonblast
- Dazzling Gleam
- Protect

Tapu Lele @ Psychic Seed
Ability: Psychic Surge
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Moonblast
- Psyshock
- Dazzling Gleam
- Protect

Flutter Mane @ Choice Specs
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Moonblast
- Dazzling Gleam
- Shadow Ball
- Power Gem

Iron Valiant @ Booster Energy
Ability: Quark Drive
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Spirit Break
- Close Combat
- Knock Off
- Protect

Incineroar @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Fake Out
- Flare Blitz
- Knock Off
- Parting Shot

Gholdengo @ Covert Cloak
Ability: Good as Gold
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Make It Rain
- Shadow Ball
- Nasty Plot
- Protect
```

---

## Boss — Pyramid King Brandon

**Pool:** everything, with no theme and no cap: **the strongest doubles team
the game can field**, as the last gate before the endgame. One box-art
legendary, **Miraidon**, and one Mega the player can't own, **Mega Zygarde**
(778, Aura Break): Zygardite is never sold during the gauntlets.

**Gimmick: everything, all at once.** Miraidon's Hadron Engine sets Electric
Terrain on entry and powers up its own Sp. Atk in it. The terrain gives Iron
Hands its Quark Drive boost for free. Chi-Yu's Beads of Ruin lowers both of
the player's Pokémon's Sp. Def, and four of Brandon's six attack from the
special side. Tornadus's Prankster Tailwind puts all of it ahead of the
player.

**AI:** omniscient, proactive switching. No ace flag.

```
Tornadus @ Covert Cloak
Ability: Prankster
EVs: 252 HP / 4 SpD / 252 Spe
Timid Nature
- Tailwind
- Bleakwind Storm
- Taunt
- Protect

Iron Hands @ Assault Vest
Ability: Quark Drive
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Fake Out
- Drain Punch
- Wild Charge
- Heavy Slam

Miraidon @ Choice Specs
Ability: Hadron Engine
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Electro Drift
- Draco Meteor
- Volt Switch
- Dazzling Gleam

Zygarde-Complete @ Zygardite
Ability: Power Construct
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
- Core Enforcer
- Draco Meteor
- Earth Power
- Protect

Flutter Mane @ Booster Energy
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Moonblast
- Shadow Ball
- Icy Wind
- Protect

Chi-Yu @ Choice Scarf
Ability: Beads of Ruin
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Heat Wave
- Dark Pulse
- Overheat
- Snarl
```

*(**Mega Zygarde comes from the Complete Forme.** In this expansion only
`SPECIES_ZYGARDE_COMPLETE` can Mega Evolve with Zygardite, so Brandon's
Zygarde starts in Complete Forme. Verify in-game that a trainer-set Complete
Forme Mega Evolves; the fallback is Mega Diancie.)*

### The strategic dependency

**The team runs on Speed and the terrain.** Tailwind doubles Brandon's side;
Icy Wind slows the player's. Electric Terrain powers Miraidon's Electro
Drift and Iron Hands's Quark Drive; Beads of Ruin makes every special hit
land harder. Then Mega Zygarde's Core Enforcer (spread, and it suppresses
abilities) and Miraidon's Specs Draco Meteor sweep.

Take the Speed or the terrain away and the team is far less scary: Tornadus,
Flutter Mane and Chi-Yu don't take hits, and Miraidon outside Electric
Terrain loses its boost.

### Counterplay available at tier 8

- **Trick Room** flips Tailwind and Icy Wind at once
- **Your own terrain:** Rillaboom's Grassy Surge or Tapu Fini's Misty Surge
  replaces Electric Terrain, switching off Hadron Engine and Quark Drive
- **Ice for Mega Zygarde** (Dragon/Ground, 4x weak): Iron Bundle's Freeze-Dry
  and Icy Wind, Chien-Pao, Baxcalibur
- **Ground for Miraidon and Iron Hands**; Lightning Rod or Volt Absorb
  blanks Electro Drift
- **Steel for Flutter Mane and Chi-Yu's Fairy and Dark partners**: Kingambit,
  Gholdengo, Metagross
- **Snarl and Assault Vest** against a special-heavy team; Intimidate only
  touches Iron Hands
- **Fake Out the Tailwind**, or Taunt can't stop it (Prankster), so Covert
  Cloak and your own Tailwind are the answer

---

## Benchmark counter-team

Built only from gauntlet 8's pool (wave 7 and earlier), items and bans. Item
clause compliant. One Mega.

```
Rillaboom @ Assault Vest
Ability: Grassy Surge
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Fake Out
- Grassy Glide
- Wood Hammer
- U-turn

Metagross @ Metagrossite
Ability: Clear Body
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Iron Head
- Stomping Tantrum
- Zen Headbutt
- Protect

Landorus-Therian @ Choice Scarf
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Stomping Tantrum
- Rock Slide
- U-turn
- Knock Off

Iron Bundle @ Choice Specs
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Icy Wind
- Freeze-Dry
- Hydro Pump
- Flip Turn

Incineroar @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Fake Out
- Flare Blitz
- Knock Off
- Parting Shot

Tornadus @ Covert Cloak
Ability: Prankster
EVs: 252 HP / 4 SpD / 252 Spe
Timid Nature
- Tailwind
- Bleakwind Storm
- Taunt
- Protect
```

**Against Brandon:** Rillaboom's Grassy Surge replaces Electric Terrain and
shuts off Hadron Engine and Quark Drive; Tornadus contests Tailwind; Iron
Bundle's Freeze-Dry hits Mega Zygarde for 4x and Icy Wind undoes Brandon's;
Mega Metagross's Iron Head handles Flutter Mane; Landorus is immune to
Electro Drift and Wild Charge; Incineroar's Snarl and Fake Out blunt the
special attackers. **Against the pool:** Rillaboom and Landorus handle the rain
and sand teams, Tornadus and Iron Bundle fight the Tailwind teams for Speed,
and Taunt stops a Trick Room setter.

---

## Open for playtesting

1. **The finale's difficulty.** Legendary Megas on three pool teams (C8, C9,
   D10) and an uncapped boss with Miraidon and Mega Zygarde is a big step up
   from gauntlet 7. That's the intent for Brandon; if the pool teams are too
   much, swap one or two for non-legendary Megas.
7. **Mega Zygarde from a trainer-set Complete Forme** (boss). Check it Mega
   Evolves; if not, give Brandon Mega Diancie instead.
2. **Perish trap (D11).** The AI has to time Perish Song with Shadow Tag;
   check it actually does, or the team is just Gengar.
3. **Spore (A2, B5).** Amoonguss's Spore breaks the "no sleep moves" rule
   on purpose, since redirection with Spore is a doubles staple. Swap it for
   Clear Smog if sleep feels cheap.
4. **Trick Room teams' 0 Speed IVs.** Check they really move first under
   the room against the player's usual answers.
5. **Fairy Aura cuts both ways (D12).** It boosts the player's Fairy moves
   too, which is the counterplay; check the AI doesn't get punished harder
   than it should.
6. **Repeated Pokémon.** Incineroar, Iron Hands, Amoonguss, Gholdengo and
   Kingambit each appear on two or three teams. Swap some if it feels
   repetitive.

---

## Implementation notes

What was built, and where. Keep the sets above in sync with
`src/data/trainers.party`; the trainer entries were generated from this doc,
and every move was checked against `all_learnables.json`.

- **Trainers:** `TRAINER_FACILITY_B8_*` (IDs 948–960; `TRAINERS_COUNT` is now
  961, under the 1000 limit), all doubles. Classes: Kindler (A1), Sailor (A2),
  Ruin Maniac (A3), Black Belt (B4), Psychic (B5), Hiker (B6), Bird Keeper
  (C7), Guitarist (C8), Ninja Boy (C9), Pokémon Ranger (D10), Hex Maniac
  (D11), Lady (D12); Brandon is the Pyramid King with his own pic. Trick Room
  attackers have 0 Speed IVs.
- **Run loop:** `FACILITY_GAUNTLET_8` and `sGauntlet8Pool` in `src/facility.c`;
  the Tower lobby's shared dispatch routes gauntlet 8 to `Facility_DoBattle_B8`
  and `Facility_Battle_Boss_B8`, in the Pyramid lobby's script.
- **The Pyramid** opens when gauntlet 7 is cleared (`IsBattlePyramidUnlocked`).
  Its attendant runs the gauntlet; new plaque, rules board, and three lobby
  NPCs (the hint-giver hints at Brandon's Miraidon). Clearing gauntlet 7 now
  points to the Pyramid; clearing gauntlet 8 has a placeholder message until
  the endgame is built.
- **Shop wave 7** (`unlockGauntlet` 7): the legendary Mega Stones (Diancite
  included), the doubles-leaning stones, Floette-Eternal, Wide Lens and Ring
  Target. Zygardite is never sold.
- **Elsewhere:** Brandon is on the Arena's sparring list (and the mock battle
  covers gauntlet 8); the Pyramid sign, the Reception guide, Scott's progress
  line and the Lounge 2 news desk all know about gauntlet 8.
- **Renaming the gauntlet:** "THE SUMMIT" appears in the Pyramid lobby's texts,
  `Facility_B8_Text_GauntletComplete`, the Pyramid sign and the Reception
  guide.

---

## Next steps

1. Playtest gauntlet 8, especially Brandon's Mega Zygarde (open for
   playtesting, 7).
2. Build the endgame's start: what happens when Brandon falls
   (`storyline.md`, "After gauntlet 8: the Crown").
