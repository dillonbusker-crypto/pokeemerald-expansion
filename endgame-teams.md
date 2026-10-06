# Endgame Teams — Brain Rematches and the Elite Four

**Status: built.** The five Brain rematches (`TRAINER_FACTORY_*`), the
Elite Four (`TRAINER_DEVON_*`), New Mauville (`TRAINER_NEW_MAUVILLE_*`) and
Scott's final teams (`TRAINER_SKY_PILLAR_SCOTT_*`) are in
`src/data/trainers.party`. Nothing is tuned by play yet. Answers `storyline.md`,
"Still to decide" #2 (the Brains' upgraded teams) and #3 (the Elite Four's
teams). Team sets are in Pokémon Showdown syntax, like the gauntlet docs.

---

## The rules these teams follow

| Rule | Applied as |
|---|---|
| Pool | **Only Pokémon and Mega Stones the player can buy by gauntlet 8** (shop waves 0–7 in `src/facility_shop.c`). No Zacian, Miraidon, Zygarde, Mewtwo, Lati or Kangaskhan. Every species was checked against the shop list |
| Priority | OU and Uber first, using Showdown's tier data as of 2026-10-05. Singles teams are judged by Gen 9 singles and National Dex tiers (National Dex is where Megas are tiered). Doubles teams are judged by doubles tiers (DOU/DUber) |
| Items | Item clause on every team. Every item is sold by the shop |
| Moves | Every move was checked against the expansion's own learnsets, including egg moves from pre-evolutions, so the player could copy any set. One exception: Rotom-Wash's Hydro Pump comes from its form change, as on Noland's built team |
| Brains | **Normal Megas** that hold their stone and Mega Evolve in battle (one per team). Level 50, since they're Scott's chipped trainers |
| Elite Four | **Two permanent Megas each.** These are listed already in Mega form, holding a real item. Real levels from 52 to 55, with the ace at 55 (`storyline.md`: "up to 55") |
| Bans | No OHKO moves, no evasion moves, no Dark Void. Sleep appears only on Lucy (Spore), as on her gauntlet team |

### Which Brains get new teams

Five Brains guard the Factory after gauntlet 8: Anabel, Tucker, Lucy, Noland
and Greta (`storyline.md`, "After gauntlet 8"). **Spenser and Brandon** rush
Wallace in the lobby and fight him off-screen. They were already at full
power, so the player never rematches them. That leaves five new teams:

| Brain | Format | Theme | Mega | Notes |
|---|---|---|---|---|
| Anabel | Doubles | Trick Room, psychic setters | Mega Heatran | Her gauntlet 4 gimmick, at full strength |
| Tucker | Singles | Setup sweepers | Mega Salamence | His signature Mega, now one sweeper among four |
| Lucy | Doubles | Status and disruption | Mega Gengar | Shadow Tag plus Perish Song |
| Noland | Singles | Machines: Paradox "Iron" Pokémon and synthetic Pokémon | Mega Magearna | The Factory Head fields what Devon could build |
| Greta | Singles | All-Fighting | Mega Blaziken | The Arena Tycoon's all-out offense |

**Format** follows each boss's gauntlet: Anabel (gauntlet 4) and Lucy (6) were
doubles, and Tucker (5) was singles. Noland and Greta fought singles at
Littleroot. That gives three singles and two doubles.

### The Elite Four

| Member | Type | Permanent Megas | Ace (Lv 55) |
|---|---|---|---|
| Sidney | Dark | Mega Absol Z, Mega Tyranitar | Mega Absol Z (his vanilla ace) |
| Phoebe | Ghost | Mega Banette (her vanilla Pokémon), Mega Chandelure | Mega Chandelure |
| Glacia | Ice | Mega Baxcalibur, Mega Froslass | Mega Baxcalibur |
| Drake | Dragon | Mega Salamence, Mega Garchomp Z | Mega Salamence (his vanilla ace) |

All singles, as in vanilla.

---

# The Brains (level 50)

AI for all five: omniscient, proactive switching, no ace flag (as on every
gauntlet boss).

## Salon Maiden Anabel — doubles, Trick Room

Her gauntlet 4 team, with no 600 BST cap. **Two Trick Room setters**: Hatterene
(Magic Bounce, so it can't be Taunted through Mental Herb) and Farigiraf
(Armor Tail blocks Fake Out on its partner). Four Pokémon with base Speed 67
or lower hit hard under the room. Mega Heatran (175 Sp. Atk, base Speed 67)
spreads Heat Wave. Iron Hands' Booster Energy goes to Attack, and its Fake Out
still works because there's no Psychic Terrain on this team. Indeedee was cut
for this reason: Psychic Terrain would block Kingambit's Sucker Punch and Iron
Hands' Fake Out.

Tiers: Hatterene, Kingambit, Ursaluna-Bloodmoon, Iron Hands and Farigiraf are
DOU. Heatran is National Dex OU.

```
Hatterene @ Mental Herb
Ability: Magic Bounce
EVs: 252 HP / 252 SpA / 4 SpD
Quiet Nature
IVs: 0 Spe
- Trick Room
- Dazzling Gleam
- Psychic
- Protect

Farigiraf @ Sitrus Berry
Ability: Armor Tail
EVs: 252 HP / 4 Def / 252 SpD
Sassy Nature
IVs: 0 Spe
- Trick Room
- Psychic Noise
- Hyper Voice
- Protect

Heatran @ Heatranite
Ability: Flash Fire
EVs: 252 HP / 252 SpA / 4 SpD
Quiet Nature
IVs: 0 Spe
- Heat Wave
- Earth Power
- Flash Cannon
- Protect

Ursaluna-Bloodmoon @ Assault Vest
Ability: Mind's Eye
EVs: 252 HP / 252 SpA / 4 SpD
Quiet Nature
IVs: 0 Spe
- Blood Moon
- Earth Power
- Hyper Voice
- Vacuum Wave

Kingambit @ Black Glasses
Ability: Defiant
EVs: 252 HP / 252 Atk / 4 SpD
Brave Nature
IVs: 0 Spe
- Kowtow Cleave
- Iron Head
- Sucker Punch
- Protect

Iron Hands @ Booster Energy
Ability: Quark Drive
EVs: 252 HP / 252 Atk / 4 SpD
Brave Nature
IVs: 0 Spe
- Fake Out
- Drain Punch
- Wild Charge
- Ice Punch
```

**How to beat it:** Taunt or Imprison won't work through Mental Herb and Magic
Bounce, so beat it on turns instead. Protect or stall out the room's turns,
use your own Trick Room to cancel theirs, or KO a setter before it moves. A
fast Fake Out goes first anyway, but **not into Farigiraf's partner**.

## Dome Ace Tucker — singles, setup sweepers

His gauntlet 5 team was built to land one Dragon Dance. Now **four Pokémon set
up**: Mega Salamence and Roaring Moon use Dragon Dance, and Volcarona uses
Quiver Dance. Iron Valiant and Dragapult break walls. Great Tusk lays Stealth
Rock and spins away the player's hazards. Every member is OU or Uber.

```
Great Tusk @ Rocky Helmet
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Stealth Rock
- Headlong Rush
- Rapid Spin
- Knock Off

Roaring Moon @ Booster Energy
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Acrobatics
- Knock Off
- Earthquake

Volcarona @ Heavy-Duty Boots
Ability: Flame Body
EVs: 252 HP / 4 SpA / 252 Spe
Timid Nature
- Quiver Dance
- Fiery Dance
- Giga Drain
- Morning Sun

Dragapult @ Choice Specs
Ability: Infiltrator
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Shadow Ball
- Flamethrower
- U-turn

Iron Valiant @ Life Orb
Ability: Quark Drive
EVs: 4 Atk / 252 SpA / 252 Spe
Naive Nature
- Moonblast
- Close Combat
- Knock Off
- Shadow Ball

Salamence @ Salamencite
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Double-Edge
- Earthquake
- Roost
```

**How to beat it:** Unaware (Clodsire, Skeledirge), priority, phazing, and
fast Fairies and Ice attacks. Without a counter to setup, this is the hardest
of the five.

## Pike Queen Lucy — doubles, status and disruption

Her gauntlet 6 core (Grimmsnarl, Tornadus, Amoonguss, Incineroar) is already
DOU, so it stays. Two changes:

- **Mega Gengar becomes a Perish trap.** Shadow Tag traps both of the player's
  Pokémon in doubles, and Perish Song gives them three turns. Lucy can switch
  out and the player can't.
- **Pecharunt replaces Milotic.** Poison Puppeteer confuses anything it
  poisons, and Malignant Chain often poisons. Parting Shot pivots back into
  Gengar.

```
Gengar @ Gengarite
Ability: Cursed Body
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Shadow Ball
- Sludge Bomb
- Perish Song
- Protect

Pecharunt @ Leftovers
Ability: Poison Puppeteer
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Malignant Chain
- Shadow Ball
- Parting Shot
- Protect

Amoonguss @ Rocky Helmet
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
IVs: 0 Spe
- Spore
- Rage Powder
- Sludge Bomb
- Protect

Tornadus @ Covert Cloak
Ability: Prankster
EVs: 252 HP / 4 SpD / 252 Spe
Timid Nature
- Tailwind
- Bleakwind Storm
- Taunt
- Protect

Grimmsnarl @ Light Clay
Ability: Prankster
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Reflect
- Light Screen
- Thunder Wave
- Spirit Break

Incineroar @ Sitrus Berry
Ability: Intimidate
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Fake Out
- Flare Blitz
- Knock Off
- U-turn
```

*(Amoonguss's Pollen Puff and Incineroar's Parting Shot from her gauntlet team
aren't in this expansion's learnsets. They work for a trainer, but the player
can't copy them, so they're swapped here.)*

**How to beat it:** Ghost types aren't trapped by Shadow Tag. Safety Goggles,
Grass types and Overcoat block Spore. Clear Amulet and Defiant or Competitive
punish Intimidate. Focus on Gengar early.

## Factory Head Noland — singles, machines

The Factory Head fields **what Devon could build**: future Paradox "Iron"
Pokémon, Genesect, Magearna, and an appliance Rotom. Mega Magearna (Soul-Heart,
170 Sp. Atk) gets stronger with every KO, on either side. Rotom-Wash covers
the team's shared weaknesses to Fire and Ground.

Tiers: Iron Treads, Iron Moth and Magearna are OU or Uber. Genesect is
National Dex Uber. Iron Crown and Rotom-Wash fill the gaps.

```
Iron Treads @ Rocky Helmet
Ability: Quark Drive
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Stealth Rock
- Rapid Spin
- Earthquake
- Knock Off

Iron Crown @ Booster Energy
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Tachyon Cutter
- Psyshock
- Focus Blast
- Volt Switch

Iron Moth @ Choice Specs
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Fiery Dance
- Sludge Wave
- Energy Ball
- Dazzling Gleam

Genesect @ Choice Scarf
Ability: Download
EVs: 252 Atk / 4 SpA / 252 Spe
Naive Nature
- U-turn
- Iron Head
- Flamethrower
- Ice Beam

Rotom-Wash @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Volt Switch
- Hydro Pump
- Will-O-Wisp
- Pain Split

Magearna @ Magearnite
Ability: Soul-Heart
EVs: 4 HP / 252 SpA / 252 Spe
Modest Nature
- Fleur Cannon
- Flash Cannon
- Aura Sphere
- Volt Switch
```

**How to beat it:** Fire, which hits Genesect 4× and Magearna, Iron Crown and
Iron Treads 2×. Ground hits Magearna and Iron Moth. Don't feed Magearna KOs.

## Arena Tycoon Greta — singles, all-Fighting

Six Fighting types. Each has a second type for coverage, so the team isn't one
weakness: Poison (Sneasler, against Fairies), Ghost (Annihilape, Marshadow),
Dark (Urshifu, against Psychics), Dragon (Kommo-o) and Fire (Mega Blaziken).
Mega Blaziken gets faster every turn with Speed Boost. All but Kommo-o and
base Blaziken are Uber.

```
Sneasler @ White Herb
Ability: Unburden
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Dire Claw
- Close Combat
- Rock Slide

Annihilape @ Leftovers
Ability: Defiant
EVs: 240 HP / 16 Atk / 252 SpD
Careful Nature
- Bulk Up
- Rage Fist
- Drain Punch
- Taunt

Marshadow @ Life Orb
Ability: Technician
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Spectral Thief
- Close Combat
- Shadow Sneak
- Ice Punch

Urshifu @ Choice Band
Ability: Unseen Fist
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Wicked Blow
- Close Combat
- Sucker Punch
- U-turn

Kommo-o @ Throat Spray
Ability: Soundproof
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Clangorous Soul
- Clanging Scales
- Aura Sphere
- Flamethrower

Blaziken @ Blazikenite
Ability: Speed Boost
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Swords Dance
- Flare Blitz
- Close Combat
- Protect
```

*(Sneasler's White Herb restores the Defenses that Close Combat lowers, and
using up the item triggers Unburden. Urshifu is the Single Strike form.)*

**How to beat it:** Bulky Fairies and Psychics with Flying or Poison coverage,
Intimidate, and priority. Don't hit Annihilape for free, because Rage Fist
grows with every hit it takes.

---

# The Elite Four (levels 52–55, permanent Megas)

Each team has two permanent Megas, which start the battle Mega Evolved and
hold a real item. Under the perma-Mega rule they **don't use up the trainer's
one Mega Evolution**, so a third, normal Mega is possible later (see Open
questions). Levels: 52–53 for the regulars, 54 for the second Mega, 55 for the
ace. That's two to five levels over the player's chipped level 50. AI: as the
Brains.

## Sidney — Dark

Ting-Lu lays Stealth Rock, and Vessel of Ruin lowers the player's Attack. Mega
Tyranitar's Sand Stream gives the sand-immune team free chip damage. **Mega
Absol Z** (Dark/Ghost, Sharpness, 154 Atk, **151 Speed**) cleans up behind
them. Darkrai is Uber. Weavile (UU) adds Ice coverage and Ice Shard
priority, and keeps Kingambit to Anabel's team alone.

```
Ting-Lu @ Leftovers
Ability: Vessel of Ruin
Level: 52
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Ruination
- Earthquake
- Whirlwind

Meowscarada @ Choice Band
Ability: Protean
Level: 52
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Flower Trick
- Knock Off
- Triple Axel
- U-turn

Weavile @ Black Glasses
Ability: Pressure
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Triple Axel
- Knock Off
- Ice Shard

Darkrai @ Choice Specs
Ability: Bad Dreams
Level: 53
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Dark Pulse
- Sludge Bomb
- Focus Blast
- Ice Beam

Tyranitar-Mega @ Weakness Policy
Ability: Sand Stream
Level: 54
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Dragon Dance
- Stone Edge
- Knock Off
- Earthquake

Absol-Mega-Z @ Life Orb
Ability: Sharpness
Level: 55
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Night Slash
- Shadow Claw
- Close Combat
```

*(Sharpness boosts Night Slash. Shadow Claw is the Ghost STAB, because Absol
learns no Ghost-type slicing move.)*

## Phoebe — Ghost

**Mega Banette** is her own vanilla Pokémon. Prankster gives it priority
Will-O-Wisp and Destiny Bond, though Dark types are immune to those, and 165
Attack behind Poltergeist. **Mega Chandelure** (175 Sp. Atk, Infiltrator) is
her ace and holds Choice Specs, which a normal Mega can't hold. Skeledirge's
Unaware means setup sweepers can't simply boost past her. Flutter Mane,
Ceruledge and Gholdengo are OU or Uber.

```
Gholdengo @ Air Balloon
Ability: Good as Gold
Level: 52
EVs: 252 HP / 252 SpA / 4 Spe
Modest Nature
- Nasty Plot
- Make It Rain
- Shadow Ball
- Recover

Ceruledge @ Focus Sash
Ability: Flash Fire
Level: 52
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Bitter Blade
- Poltergeist
- Shadow Sneak

Skeledirge @ Leftovers
Ability: Unaware
Level: 53
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Torch Song
- Hex
- Slack Off
- Will-O-Wisp

Flutter Mane @ Booster Energy
Ability: Protosynthesis
Level: 53
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Calm Mind
- Moonblast
- Shadow Ball
- Mystical Fire

Banette-Mega @ Life Orb
Ability: Prankster
Level: 54
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Poltergeist
- Gunk Shot
- Will-O-Wisp
- Destiny Bond

Chandelure-Mega @ Choice Specs
Ability: Infiltrator
Level: 55
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Shadow Ball
- Fire Blast
- Energy Ball
- Psychic
```

*(Mega Banette is slow at base 75 Speed, so it runs max HP rather than Speed.
Its Destiny Bond and Will-O-Wisp are the threats, not its Speed.)*

## Glacia — Ice

**A snow team.** Ninetales-Alola sets snow and Aurora Veil on turn one. Mega
Froslass (Snow Warning, Icy Rock) resets snow for eight turns, and its
Blizzard never misses in snow. Snow raises every Ice type's Defense by 50%,
which suits **Mega Baxcalibur** (175 Atk) running Swords Dance with Loaded
Dice multi-hit moves. Cloyster's Shell Smash and Chien-Pao's Sword of Ruin
finish what's left. Ice has few OU Pokémon. Chien-Pao, Iron Bundle and
Baxcalibur are Uber, and Ninetales-Alola is DOU.

```
Ninetales-Alola @ Light Clay
Ability: Snow Warning
Level: 52
EVs: 252 HP / 4 SpA / 252 Spe
Timid Nature
- Aurora Veil
- Freeze-Dry
- Moonblast
- Encore

Chien-Pao @ Choice Band
Ability: Sword of Ruin
Level: 52
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Icicle Crash
- Sucker Punch
- Sacred Sword
- Ice Shard

Cloyster @ White Herb
Ability: Skill Link
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Shell Smash
- Icicle Spear
- Rock Blast
- Ice Shard

Iron Bundle @ Booster Energy
Ability: Quark Drive
Level: 53
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Freeze-Dry
- Hydro Pump
- Taunt
- Flip Turn

Froslass-Mega @ Icy Rock
Ability: Snow Warning
Level: 54
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Blizzard
- Shadow Ball
- Spikes
- Will-O-Wisp

Baxcalibur-Mega @ Loaded Dice
Ability: Thermal Exchange
Level: 55
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Icicle Spear
- Scale Shot
- Earthquake
```

## Drake — Dragon

**Mega Salamence** is Drake's vanilla ace. The second permanent Mega is **Mega
Garchomp Z** (Levitate, 151 Speed, mixed attacker), which ties in his vanilla
Flygon. Archaludon (Stamina) lays Stealth Rock. Raging Bolt and Walking Wake
are top-tier special Dragons, and Dragonite's Choice Band Extreme Speed is the
team's priority move. Every member is OU or Uber except Garchomp (UUBL in
singles, OU in National Dex).

```
Archaludon @ Leftovers
Ability: Stamina
Level: 52
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Stealth Rock
- Draco Meteor
- Flash Cannon
- Body Press

Walking Wake @ Choice Specs
Ability: Protosynthesis
Level: 52
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Hydro Steam
- Draco Meteor
- Flamethrower
- Flip Turn

Raging Bolt @ Booster Energy
Ability: Protosynthesis
Level: 53
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Calm Mind
- Thunderclap
- Dragon Pulse
- Thunderbolt

Dragonite @ Choice Band
Ability: Multiscale
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Extreme Speed
- Outrage
- Earthquake
- Fire Punch

Garchomp-Mega-Z @ Life Orb
Ability: Levitate
Level: 54
EVs: 4 Atk / 252 SpA / 252 Spe
Naive Nature
- Draco Meteor
- Earthquake
- Fire Blast
- Stone Edge

Salamence-Mega @ Heavy-Duty Boots
Ability: Aerilate
Level: 55
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Double-Edge
- Earthquake
- Roost
```

---

# New Mauville (admins level 60, leaders level 65)

Six teams in `src/data/trainers.party` (`TRAINER_NEW_MAUVILLE_*`, 978-983),
answering `storyline.md`, "Still to decide" #4. Same rules table as above:
every species and item is sold by the shop by gauntlet 8 (checked against
`src/facility_shop.c`; the Mega Stones are Cameruptite, Houndoominite,
Sharpedonite and Swampertite), item clause per team, every move checked
against the expansion's learnsets, no OHKO, no evasion, no sleep. AI as the
Elite Four: omniscient, proactive switching. All singles. The Primals are
the one exception to the shop rule: Groudon and Kyogre aren't sold, because
Scott lent them.

**Levels.** The four admins are level 60, five over the top of the Elite
Four (52-55): the player has had the siphon and (perhaps) another Hoopa
legend since, and gains Experience now that the chips are off. The leaders
are level 65, five over the admins, and their five teammates match their
Primal. The player has at most one permanent Mega here (the Crown holds six
only after these fights are won).

**Megas.** Each admin has **one normal Mega**, holding its stone and Mega
Evolving in battle (like the Brains). Maxie and Archie have **no Mega**: each
has a permanent Primal, listed directly in Primal form (`Groudon-Primal`,
`Kyogre-Primal`) holding Leftovers, so it doesn't revert on switching or
fainting and Desolate Land or Primordial Sea starts the battle.

| Trainer | Theme | Mega | Level |
|---|---|---|---|
| Tabitha | Magma: Fire, Ground, Rock | Mega Camerupt | 60 |
| Courtney | Magma: Fire, Rock, Ground, Dark | Mega Houndoom | 60 |
| Matt | Aqua: Water, Dark, Ice | Mega Sharpedo | 60 |
| Shelly | Aqua: Water, Dark, Ground | Mega Swampert | 60 |
| Maxie | Sun, built around Primal Groudon | none | 65 |
| Archie | Rain, built around Primal Kyogre | none | 65 |

## Tabitha: Magma, Fire and Ground

Torkoal sets sun with Stealth Rock, and Rapid Spin to clear the player's
hazards. Heatran, Excadrill and Rhyperior hit the player's Steel and Rock
answers from the Ground side, Garchomp's Choice Scarf cleans up, and **Mega
Camerupt** (Sheer Force, 145 Sp. Atk) is the ace.

```
Torkoal @ Heat Rock
Ability: Drought
Level: 60
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
IVs: 0 Atk
- Stealth Rock
- Lava Plume
- Earth Power
- Rapid Spin

Rhyperior @ Choice Band
Ability: Solid Rock
Level: 60
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Earthquake
- Stone Edge
- Megahorn
- Ice Punch

Heatran @ Leftovers
Ability: Flash Fire
Level: 60
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Magma Storm
- Earth Power
- Flash Cannon
- Taunt

Excadrill @ Life Orb
Ability: Mold Breaker
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Earthquake
- Iron Head
- Rock Slide

Garchomp @ Choice Scarf
Ability: Rough Skin
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Outrage
- Stone Edge
- Fire Fang

Camerupt-Mega @ Cameruptite
Ability: Sheer Force
Level: 60
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Lava Plume
- Earth Power
- Flash Cannon
- Rock Slide
```

**How to beat it:** Water, Grass and Ice hit most of the team. Torkoal's sun
doubles the Fire moves, so take it out early or set your own weather.

## Courtney: Magma, Fire, Rock and Dark

Volcarona, Landorus-Therian and Ting-Lu are the setup and hazard core; Coalossal
spins. Tyranitar's Sand Stream adds sand chip damage, and **Mega
Houndoom** (Solar Power, 140 Sp. Atk) with Nasty Plot is the ace.

```
Volcarona @ Heavy-Duty Boots
Ability: Flame Body
Level: 60
EVs: 252 HP / 4 SpA / 252 Spe
Timid Nature
- Quiver Dance
- Fiery Dance
- Bug Buzz
- Morning Sun

Landorus-Therian @ Rocky Helmet
Ability: Intimidate
Level: 60
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Stealth Rock
- Earthquake
- U-turn
- Knock Off

Coalossal @ Leftovers
Ability: Flash Fire
Level: 60
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Rapid Spin
- Flamethrower
- Stone Edge
- Will-O-Wisp

Ting-Lu @ Sitrus Berry
Ability: Vessel of Ruin
Level: 60
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Ruination
- Earthquake
- Spikes
- Whirlwind

Tyranitar @ Assault Vest
Ability: Sand Stream
Level: 60
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Knock Off
- Stone Edge
- Earthquake
- Fire Punch

Houndoom-Mega @ Houndoominite
Ability: Solar Power
Level: 60
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Nasty Plot
- Fire Blast
- Dark Pulse
- Sludge Bomb
```

**How to beat it:** Fighting, Water and Ground. Quiver Dance Volcarona is the
sweep to stop; Ting-Lu's Whirlwind and Spikes make it hard to stall.

## Matt: Aqua, Water and Dark

Pelipper sets rain. Crawdaunt (Adaptability), Greninja and Weavile are the
Dark attackers; Toxapex stalls with Baneful Bunker and Haze. **Mega Sharpedo**
(Strong Jaw, 140 Attack) runs Crunch and Ice Fang.

```
Pelipper @ Damp Rock
Ability: Drizzle
Level: 60
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Hurricane
- Scald
- U-turn
- Roost

Crawdaunt @ Life Orb
Ability: Adaptability
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Crabhammer
- Knock Off
- Aqua Jet

Toxapex @ Black Sludge
Ability: Regenerator
Level: 60
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
IVs: 0 Atk
- Baneful Bunker
- Scald
- Recover
- Haze

Greninja @ Choice Specs
Ability: Protean
Level: 60
EVs: 4 Def / 252 SpA / 252 Spe
Timid Nature
- Hydro Pump
- Dark Pulse
- Ice Beam
- U-turn

Weavile @ Black Glasses
Ability: Pressure
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Triple Axel
- Knock Off
- Ice Shard

Sharpedo-Mega @ Sharpedonite
Ability: Strong Jaw
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Protect
- Crunch
- Waterfall
- Ice Fang
```

**How to beat it:** Grass, Electric and Fighting. Toxapex wants Poison-proof
or Steel attackers; Weavile and Greninja are frail.

## Shelly: Aqua, Water, Dark and Ground

Politoed sets rain for Kingdra and **Mega Swampert** (Swift Swim, 150 Attack),
which is the ace. Gyarados and Krookodile Intimidate, Mandibuzz is the
defensive pivot.

```
Politoed @ Damp Rock
Ability: Drizzle
Level: 60
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Scald
- Ice Beam
- Encore
- Haze

Kingdra @ Choice Specs
Ability: Swift Swim
Level: 60
EVs: 4 HP / 252 SpA / 252 Spe
Modest Nature
- Hydro Pump
- Draco Meteor
- Ice Beam
- Flip Turn

Gyarados @ Lum Berry
Ability: Intimidate
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Waterfall
- Earthquake
- Stone Edge

Mandibuzz @ Rocky Helmet
Ability: Overcoat
Level: 60
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Foul Play
- Roost
- Defog
- U-turn

Krookodile @ Life Orb
Ability: Intimidate
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Bulk Up
- Earthquake
- Knock Off
- Stone Edge

Swampert-Mega @ Swampertite
Ability: Swift Swim
Level: 60
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Waterfall
- Earthquake
- Ice Punch
- Stealth Rock
```

**How to beat it:** Grass, and Electric into the Flying and Water types. The
rain boosts Water and halves Fire, so remove Politoed before it sets up.

## Maxie: sun, Primal Groudon at level 65

Maxie is the first of the generator pair (the Scrambler: no heal between him
and Archie). **Primal Groudon leads.**
Desolate Land makes harsh sunlight, and when Groudon leaves or faints, Torkoal's
Drought resumes ordinary sun. Venusaur and Charizard are the sun sweepers,
Volcarona and Heatran the Fire attackers. No Mega: Groudon-Primal is the ace.

```
Groudon-Primal @ Leftovers
Ability: Desolate Land
Level: 65
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Swords Dance
- Precipice Blades
- Fire Punch
- Stone Edge

Torkoal @ Heat Rock
Ability: Drought
Level: 65
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
IVs: 0 Atk
- Stealth Rock
- Lava Plume
- Earth Power
- Rapid Spin

Venusaur @ Black Sludge
Ability: Chlorophyll
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
- Growth
- Giga Drain
- Sludge Bomb
- Earth Power

Volcarona @ Heavy-Duty Boots
Ability: Flame Body
Level: 65
EVs: 252 HP / 4 SpA / 252 Spe
Timid Nature
- Quiver Dance
- Fiery Dance
- Bug Buzz
- Morning Sun

Heatran @ Air Balloon
Ability: Flash Fire
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Magma Storm
- Earth Power
- Flash Cannon
- Taunt

Charizard @ Choice Specs
Ability: Solar Power
Level: 65
EVs: 4 Def / 252 SpA / 252 Spe
Timid Nature
- Fire Blast
- Air Slash
- Focus Blast
- Solar Beam
```

*(Primal Groudon holds Leftovers, not the Red Orb, because the Red Orb isn't
sold. Listed as Groudon-Primal, it needs no orb to be Primal.)*

**How to beat it:** Desolate Land makes Water moves fail outright, so use
Grass, Ice and Steel. Take Groudon out before it sets up Swords Dance.
Once it's gone, Torkoal's Drought keeps the sun going and Venusaur
Chlorophyll sweeps.

## Archie: rain, Primal Kyogre at level 65

The mirror of Maxie. **Primal Kyogre leads**, and Primordial Sea makes heavy
rain (Fire moves fail outright). Pelipper's Drizzle takes over once Kyogre is
gone. Kingdra, Barraskewda and Ludicolo all have Swift Swim; Zapdos's Thunder
never misses in rain. No Mega.

```
Kyogre-Primal @ Leftovers
Ability: Primordial Sea
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Origin Pulse
- Thunder
- Ice Beam
- Calm Mind

Pelipper @ Damp Rock
Ability: Drizzle
Level: 65
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Hurricane
- Scald
- U-turn
- Roost

Kingdra @ Choice Specs
Ability: Swift Swim
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Modest Nature
- Hydro Pump
- Draco Meteor
- Ice Beam
- Flip Turn

Barraskewda @ Choice Band
Ability: Swift Swim
Level: 65
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Liquidation
- Close Combat
- Flip Turn
- Psychic Fangs

Ludicolo @ Life Orb
Ability: Swift Swim
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Modest Nature
- Hydro Pump
- Giga Drain
- Ice Beam
- Focus Blast

Zapdos @ Heavy-Duty Boots
Ability: Pressure
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Thunder
- Hurricane
- Heat Wave
- Roost
```

**How to beat it:** Electric and Grass hit the Water types, and Primordial Sea
blanks Fire. Kyogre's Calm Mind makes it a wall, so pressure it before it
stacks.

---

## Open questions for review

1. **Repeats across opponents.** There are only about 30 OU and Uber Pokémon
   in the pool, so some show up twice. Phoebe now uses Mega Banette and
   Skeledirge, so Mega Gengar is Lucy's alone. Sidney now uses Weavile, so
   Kingambit is Anabel's alone. Repeats that remain:
   - **Mega Salamence:** a normal Mega for Tucker, permanent for Drake.
     It's the signature Pokémon of both. If you want it on only one, Tucker
     can take Mega Metagross (National Dex Uber) instead.
   - **Against Spenser's and Brandon's gauntlet teams:** Chien-Pao (Glacia),
     Flutter Mane (Phoebe), Great Tusk (Tucker), Iron Hands (Anabel) and
     Tornadus (Lucy) each also appear on one of those two teams. The player
     doesn't fight Spenser or Brandon again, so these only repeat against
     gauntlets 7 and 8.
2. **A third Mega for the Elite Four?** Permanent Megas don't use up the
   battle's one Mega Evolution, so each Elite Four member *could* also Mega
   Evolve a normal Mega mid-battle. These teams don't, to keep to "two per
   team." It's an easy way to raise the difficulty later.
3. **Difficulty.** These are full-strength teams with no handicaps. The Elite
   Four comes before the siphon, so the player has no permanent Megas yet;
   their only edge is a level 60 legendary from Hoopa, if they caught one.
   The levels stay at 52–55 for playtesting (your call). They're the
   simplest dial to turn.
4. **Engine checks when built:**
   - Mega Heatran, Mega Magearna, Mega Absol Z, Mega Garchomp Z, Mega
     Baxcalibur, Mega Froslass and Mega Chandelure are newer Megas (Legends:
     Z-A and later). Check that each one transforms and that its ability
     works in a quick battle.
   - Enemy permanent Megas are tested, but no team has run two yet.
5. **Trainer IDs:** five new Brain teams plus four Elite Four members makes
   nine, already counted in `storyline.md`'s budget (984 of 1000 with the
   whole endgame).

---

# The final battle

**Built** (`TRAINER_SKY_PILLAR_SCOTT_LATIAS` / `_LATIOS`, 984-985,
`src/data/trainers.party`). Answers `storyline.md`, "Still to decide" #5
(Scott's movesets, EVs and items). Scott at the top of Sky Pillar: **level
100, every Pokémon listed directly in its permanent form** (Mega Rayquaza
keeps no stone, the Primals hold their orbs), **every one holding a different
item** (item clause), four attacks each, max EVs in their attacking stat and
Speed, and **no balance at all.**

| Rule | Applied as |
|---|---|
| Pool | None. This is Scott's own team, so the shop's pool doesn't apply: legendaries, Primals and Mega Rayquaza |
| Which Lati | Same logic as the Factory: `FLAG_STEVEN_HAS_LATIOS` set (the player's is a Latios) means Scott has **Latias**, otherwise Latios |
| Overlap with the Factory | Mewtwo-Mega-Y, the Lati and Darkrai-Mega are the Factory sets unchanged. Gengar, Salamence and Mawile make way for the three legendaries |
| Order | Rayquaza leads, then Kyogre, Groudon, Mewtwo, the Lati, Darkrai |
| AI | As the Factory teams (`Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Omniscient`), `Music: Intense`, class `Founder`, `Gentleman` standing in for his missing sprite |
| Whiteout | A normal white-out: the player wakes up beside Nurse Joy outside the tower, and the held items come back |

**The weathers fight each other on purpose.** Mega Rayquaza (Delta Stream)
leads. Kyogre (Primordial Sea) and Groudon (Desolate Land) each overwrite the
last when they come in, and a Primal's weather also cancels Rayquaza's. His
own weather cancels his teammates' advantage. It's "raw power, no balance"
made literal. A balanced team with pivots and speed control beats it.

## Scott: the Latias team (a Latios player)

```
Rayquaza-Mega @ Choice Band
Ability: Delta Stream
Level: 100
EVs: 252 Atk / 4 SpD / 252 Spe
Adamant Nature
- Dragon Ascent
- Extreme Speed
- Earthquake
- Stone Edge

Kyogre-Primal @ Blue Orb
Ability: Primordial Sea
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Water Spout
- Origin Pulse
- Ice Beam
- Thunder

Groudon-Primal @ Red Orb
Ability: Desolate Land
Level: 100
EVs: 252 Atk / 4 SpD / 252 Spe
Adamant Nature
- Precipice Blades
- Fire Punch
- Stone Edge
- Thunder Punch

Mewtwo-Mega-Y @ Life Orb
Ability: Insomnia
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Psystrike
- Aura Sphere
- Ice Beam
- Fire Blast

Latias-Mega @ Choice Specs
Ability: Levitate
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Mist Ball
- Thunderbolt
- Ice Beam

Darkrai-Mega @ Black Glasses
Ability: Bad Dreams
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Dark Pulse
- Sludge Bomb
- Focus Blast
- Ice Beam
```

## Scott: the Latios team (a Latias player)

The same team, with **Latios-Mega** in the fifth slot: Draco Meteor,
**Psyshock** (instead of Mist Ball), Thunderbolt, Ice Beam, still Choice
Specs and Timid, as on his Factory team.

## Scott without Darkrai (Bad Dreams)

A player who freed Darkrai in the optional Bad Dreams event
(`FLAG_DARKRAI_FREED`, see storyline.md) fights a Scott who has lost it.
Both level-100 battles then use **five-Pokémon** variants that are the teams
above with the Mega Darkrai entry removed and nothing else changed:
`TRAINER_FACTORY_SCOTT_NO_DARKRAI_LATIAS` / `_LATIOS` in the Pillar Chamber
(Mewtwo, Lati@s, Gengar, Salamence, Mawile) and
`TRAINER_SKY_PILLAR_SCOTT_NO_DARKRAI_LATIAS` / `_LATIOS` at the top of Sky
Pillar (Rayquaza, Kyogre, Groudon, Mewtwo, Lati@s). The Latias/Latios choice
still follows `FLAG_STEVEN_HAS_LATIOS`, and the rematch after a loss uses the
same variant. Scott acknowledges it before the Factory battle and in the Sky
Pillar scene.
