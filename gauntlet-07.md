# Gauntlet 7 — "The Open Court"

**Battle Palace.** Singles, 6v6, level 50. Six battles drawn from twelve,
then the boss, **Palace Maven Spenser**.

> **Status: gauntlet 7 is built** (see "Implementation notes" at the end).
> Wave 7 and gauntlet 8 are still a plan. Open questions 1, 2 and 5 only
> affect wave 7; the rest were settled with the defaults noted there.

---

## The idea: two all-out gauntlets

Gauntlets 7 and 8 are the finale, and they're **all-out**: gauntlet 7 is
all-out singles, gauntlet 8 all-out doubles. Everything competitively
relevant that we've held back so far comes in:

- **Every Pokémon at or under 600 BST** is fair game, including the
  Ubers-grade ones gauntlets 5 and 6 held back.
- **Every Mega Stone** goes on sale, whatever the Mega's BST, apart from the
  story-locked ones (below).
- **Every competitively relevant item** we haven't added yet.

**Phased by format:**

- **Wave 6** (unlocks clearing gauntlet 6, bought *for* gauntlet 7): the
  singles-relevant additions.
- **Wave 7** (unlocks clearing gauntlet 7, bought *for* gauntlet 8): the
  doubles-relevant leftovers, plus the **700-BST legendary Megas** as the
  finale's last step up.

Everything from wave 6 stays on sale in gauntlet 8, so the doubles gauntlet
gets the whole roster.

**Name:** *The Open Court* (chosen for the build; easy to change, see
"Implementation notes").

---

## Cap and rules

**The BST cap stays 600 for both gauntlets**, on the base species. Megas may
go above it; that's the point of "every stone". The design doc's old plan
(680 BST box-art legendaries in gauntlet 8) is superseded: **legendaries over
600 are never sold**. They're Scott's endgame (Mewtwo, Rayquaza, Groudon,
Kyogre), and the rest (Zacian, Kyurem, Calyrex and co.) simply stay out.
❓ Confirm.

### Bans

**Permanent list stands:** Smeargle, Wobbuffet, Shedinja, Ditto,
Wishiwashi, Palafin.

**The form-change rule, updated:** Mega Evolution is now allowed at **any**
BST. Other form changes that escape the cap stay out:

- **Zygarde** is sold as Zygarde-50% with **Aura Break only**. Power
  Construct (Complete Forme, 708) stays banned.
- **Greninja**: Protean only. Battle Bond stays banned.
- **Hoopa** stays Confined. The Prison Bottle is never sold (Unbound is 680).
- **Galarian Darmanitan's Zen Mode is allowed**: Zen is 540, under the cap.

**Blaziken gets Speed Boost back.** It's been Blaze-only since gauntlet 5
because Blazikenite wasn't sold; now it is.

**Items that stay out** (luck, or no legal holder):

| Item | Why |
|---|---|
| King's Rock, Razor Fang | Flinch on any hit. Banned in Smogon singles |
| Quick Claw, Focus Band | Pure luck |
| Bright Powder, Lax Incense | Evasion. Banned in Smogon singles |
| Berserk Gene | Confusion every time. Luck |
| Lucky Punch, Metal Powder, Quick Powder | No worthwhile legal holder (Ditto is banned) |
| Luck Incense, Pure Incense | No battle effect |
| Odd, Rock, Sea, Wave and Rose Incense | Duplicates of the type boosters and Plates. ❓ See open questions |

### Story locks (never sold)

| What | Why |
|---|---|
| Latias, Latios, Latiasite, Latiosite, Soul Dew | The Artisan Cave quest. Steven returns the player's Lati **with its Mega Stone** before gauntlet 8 (`storyline.md`) |
| Kangaskhanite | Norman's gift, the only one (`storyline.md`) |
| Mewtwo, Mewtwonite X/Y | Over 600, and on Scott's team |
| Red Orb, Blue Orb, the Origin orbs | Scott's endgame; their holders are over 600 |
| Prison Bottle | Hoopa-Unbound is 680 |

---

## Wave 6: shop additions for gauntlet 7 (singles)

**Price tiers:** the design doc's 900–1,400 band for gauntlet 7, with
cheaper catch-up tiers for the plain OU leftovers and Mega bases.

### Keeper 4 — Pokémon

Everything gauntlets 5 and 6 held "until gauntlet 7", plus the leftovers.

| Tier | Pokémon |
|---|---|
| **Premium 1,400** | Flutter Mane, Roaring Moon, Chi-Yu, Chien-Pao, Darkrai, Deoxys-Attack, Deoxys-Speed, Shaymin-Sky, Magearna, Marshadow, Zygarde-50%, Spectrier, Urshifu Single Strike |
| **Strong 1,150** | Walking Wake, Gouging Fire, Iron Bundle, Kartana, Pheromosa, Naganadel, Genesect, Galarian Zapdos, Landorus Incarnate, Enamorus Incarnate, Deoxys-Normal, Necrozma, Diancie, Houndstone, Galarian Darmanitan |
| **Standard 900** | Espathra |

The plain leftovers (starters, Mega bases, doubles staples) go into earlier
gauntlets instead: see "Pulled into earlier gauntlets" below.

Notes:

- **Necrozma** is base form only. Its fusion items aren't sold, and Dusk
  Mane, Dawn Wings and Ultra are all over 600.
- **Genesect** comes with its four Drives (Keeper 2).
- **Espathra stays here** despite its 481 BST: Speed Boost with Stored
  Power is Ubers-grade in singles. Galarian Darmanitan (Gorilla Tactics) and
  Houndstone (Last Respects) stay for the same reason.

### Keeper 3 — Mega Stones

Every remaining stone except the wave 7 group and the story locks.

| Tier | FP | Stones (Mega BST, ability) |
|---|---|---|
| **Premium** | 1,000 | Garchompite (700, Sand Force), Garchompite Z (700, Levitate), Salamencite (700, Aerilate), Metagrossite (700, Tough Claws), Tyranitarite (700, Sand Stream), Dragoninite (700, Multiscale), Baxcalibrite (700, Thermal Exchange), **Gengarite** (600, Shadow Tag), **Blazikenite** (630, Speed Boost) |
| **Strong** | 750 | Charizardite X (634, Tough Claws), Charizardite Y (634, Drought), Gyaradosite (640, Mold Breaker), Swampertite (635, Swift Swim), Blastoisinite (630, Mega Launcher), Sceptilite (630, Lightning Rod), Greninjite (630, Protean), Golisopite (630, Tough Claws), Chesnaughtite (630, Bulletproof), Feraligite (630, Dragonize), Delphoxite (634, Levitate), Emboarite (628, Mold Breaker), Lucarionite (625, Adaptability), Lucarionite Z (625, Aura Guard), Glimmoranite (625, Adaptability), Venusaurite (625, Thick Fat), Meganiumite (625, Mega Sol), Starminite (620, Huge Power), Chandelurite (620, Infiltrator), Gardevoirite (618, Pixilate), Galladite (618, Inner Focus), Aerodactylite (615, Tough Claws), Eelektrossite (615, Eelevate), Excadrite (608, Piercing Drill), Pyroarite (607, Fire Mane) |
| **Standard** | 300 | Banettite (555, Prankster), Scolipite (585, Shell Armor), Falinksite (570, Battle Armor) |

- **Gengarite at wave 6 keeps Lucy's gauntlet 6 team valid.** Mega Gengar is
  the "one Mega the player can't own yet" during gauntlet 6
  (`gauntlet-06.md`).
- **Mega Banette, Scolipede and Falinks** were "cut as outclassed" in
  gauntlet 5. With every stone on sale they come back cheap, for
  completeness.

### Keeper 2 — Held items

| Item | FP | Why |
|---|---|---|
| **Booster Energy** | 400 | Paradox abilities without sun or Electric Terrain. Held since gauntlet 5 for this moment |
| Air Balloon | 250 | Ground immunity until hit. Heatran, Gholdengo, Magnezone |
| Power Herb | 250 | One-turn Meteor Beam, Electro Shot, Solar Beam |
| Protective Pads | 200 | Ignore contact effects: Rocky Helmet, Iron Barbs, Rough Skin |
| Blunder Policy | 200 | +2 Speed on a miss. Focus Blast, Hurricane |
| Shed Shell | 200 | Always able to switch, which answers Mega Gengar's Shadow Tag |
| Scope Lens, Razor Claw | 200 each | +1 crit stage. Two copies, two holders |
| Metronome | 200 | Repeated-move power boost |
| Masks: Wellspring, Cornerstone | 600 each | Ogerpon's forms (Ogerpon is sold from wave 5) |
| Hearthflame Mask | 800 | Hearthflame Ogerpon is Ubers-grade |
| Plates (all 17) | 250 each | 20% type boosts, a second copy of each type item under the item clause |
| Gems (all 18) | 150 each | One 30% boost per battle; reusable here, since held items come back |
| Pinch berries: Salac, Ganlon, Apicot, Lansat, Starf, Micle, Custap | 200 each | Endure-and-sweep sets, Custap priority |
| Reactive berries: Kee, Maranga, Jaboca, Rowap, Enigma | 150 each | |
| Chilan Berry | 150 | The Normal resist berry, the last one missing |
| Status berries: Cheri, Chesto, Pecha, Rawst, Aspear, Persim; Leppa, Oran, Berry Juice | 50–100 | Chesto for Rest sets; mostly completeness |
| Shell Bell, Big Root | 150 each | Drain and recovery support |
| Binding Band, Grip Claw | 150 each | Trapping sets |
| Zoom Lens | 150 | Moving last boosts accuracy |
| Destiny Knot | 150 | Attract both ways |
| Absorb Bulb, Cell Battery, Luminous Moss, Snowball | 150 each | Reactive stat boosts |
| Iron Ball, Lagging Tail, Full Incense, Sticky Barb | 100 each | Trick and Fling tools |
| Float Stone | 100 | Halves weight |
| Drives (4), Memories (17) | 100 each | Genesect's Techno Blast and Silvally's type |
| Thick Club, Light Ball, Leek | 150 each | Signature items, if their holders are in the pool |

---

## Wave 7 preview: shop additions for gauntlet 8 (doubles)

Designed with gauntlet 8, listed here so the split is visible.

**Pokémon:** only Floette-Eternal (551, for Floettite), if it's sold at all
(open question 5). The other doubles staples go into earlier gauntlets: see
"Pulled into earlier gauntlets".

**Mega Stones:**

- **The legendary Megas, 700 BST:** Darkranite, Magearnite, Zeraorite,
  Heatranite, Diancite. The finale's last step up, arriving alongside the
  player's own Lati and its stone (Steven, before gauntlet 8).
- **Doubles-leaning stones:** Ampharosite (610, Mold Breaker), Aggronite
  (630, Filter), Steelixite (610, Sand Force), Audinite (545, Healer),
  Glalitite (580, Refrigerate), Floettite (651, Fairy Aura).
- ❓ **Zygardite (Mega Zygarde, 778).** Mewtwo-tier from a 600 base. My
  recommendation is never selling it, which keeps the finale's Megas at 700
  and under.

**Items:** Wide Lens (spread-move accuracy: Rock Slide, Blizzard, Hurricane),
Ring Target.

---

## Moved into earlier gauntlets (built)

The never-sold leftovers that aren't Ubers-grade are now in earlier
gauntlets' shops: gauntlet 2 (Kilowattrel, Banette, Glalie, Audino, Falinks),
gauntlet 3 (the starter finals, Galarian Slowking, Hisuian Zoroark, Overqwil
and the Mega bases), gauntlet 4 (Cinderace, Greninja, Meowscarada and the
doubles staples) and gauntlet 6 (Ursaluna-Bloodmoon). See each gauntlet's doc,
"Later shop additions", for prices, abilities and suggested CPU swaps.

---

## Economy

The tiers above follow the design doc, but income hasn't kept pace: from
gauntlet 4 on, a clear pays 150 × 6 + 900 = **1,800 FP**. That buys about one
Premium Pokémon per gauntlet.

❓ **Proposal:** raise gauntlets 7–8 to **200 per battle, 1,200 for the
boss** (2,400 per clear), so a full clear buys one Premium Pokémon plus its
stone or item. The endgame's free shop (`storyline.md`) means this money
only matters for two gauntlets.

**Pool trainers** in gauntlet 7 hold only what's buyable by wave 6, as always
(gauntlet N's pool trainers hold only items unlocked by N−1). **Bosses are
exempt.**

---

## Open questions ❓

1. **The BST cap:** 600 for both gauntlets, with no legendary over 600 ever
   sold? (Recommended; it keeps the box-art legendaries Scott's.)
2. **Zygardite:** never sold, or wave 7 at the top price?
3. **Gauntlet 7–8 FP:** raise to 200 / 1,200? *(Built unchanged at 150 / 900
   for now.)*
4. **Incenses:** Plates already give a second copy of each type boost. Do we
   want a third (Sea/Wave/Odd/Rock/Rose Incense), or skip them? *(Built
   without them.)*
5. **Floette-Eternal:** sell it (wave 7) so Floettite has a holder, or drop
   both?
6. **Smogon clauses** (evasion moves, OHKO moves, Moody, Sleep Clause): the
   L menu lets the player teach anything legal. Do the all-out gauntlets
   need any of these enforced, or do CPU teams just avoid them?
7. ~~The name of gauntlet 7.~~ *The Open Court.*

---

## The twelve teams

**Design intent:** the singles finale. Every tool a competitive player knows
is on the table at once: Ubers-grade attackers, Megas over 600, weather at
full power, and the defensive answers that hold it all back. Each group is
one way a top-tier singles team wins, and the player meets at least three of
the four in six battles.

**Rules for the pool teams:** only Pokémon, Mega Stones and items sold by
wave 6 (the wave the player shops from for this gauntlet). One Mega per team.
Item clause compliant. No evasion moves, OHKO moves, Moody or sleep-inducing
moves on CPU teams (see open question 6).

**AI:** same as gauntlets 5 and 6 for pool trainers: full offensive
intelligence, smart replacement choice, proactive switching, not omniscient.
Mega Evolution is automatic for any CPU Pokémon holding its stone.

| Group | Teams | Archetype | What it punishes |
|---|---|---|---|
| A | 1–3 | Weather at full power | No way to contest the weather, no answer to boosted speed |
| B | 4–6 | Ubers-grade offense | Slow, passive teams; no priority, no Scarf, no Focus Sash |
| C | 7–9 | Bulky offense and balance | Teams that can't break a defensive core or keep up with pivoting |
| D | 10–12 | Trap and disrupt | Over-reliance on switching, setup, or priority |

---

## Group A — Weather at full power

Gauntlet 3 taught weather with 550-BST Pokémon. This is the same lesson with
Megas and Paradoxes behind it.

### A1. Sandstorm — Mega Tyranitar

**Lead: Garchomp** sets Stealth Rock behind Rough Skin and Rocky Helmet.
**Mega Tyranitar** (700) sets sand and Dragon Dances; Excadrill outspeeds
everything in sand behind an Air Balloon. The lesson: the weather setter is
also the win condition.

```
Garchomp @ Rocky Helmet
Ability: Rough Skin
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Stealth Rock
- Earthquake
- Dragon Tail
- Spikes

Tyranitar @ Tyranitarite
Ability: Sand Stream
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Stone Edge
- Crunch
- Earthquake

Excadrill @ Air Balloon
Ability: Sand Rush
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Swords Dance
- Earthquake
- Iron Head
- Rapid Spin

Landorus @ Life Orb
Ability: Sheer Force
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Earth Power
- Sludge Wave
- Focus Blast
- Grass Knot

Gholdengo @ Choice Scarf
Ability: Good as Gold
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Make It Rain
- Shadow Ball
- Focus Blast
- Trick

Zapdos-Galar @ Choice Band
Ability: Defiant
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Thunderous Kick
- Brave Bird
- Close Combat
- U-turn
```

### A2. Drought — Mega Charizard Y

**Lead: Torkoal** sets sun and Stealth Rock. **Mega Charizard Y** keeps it
up with Drought and 159 SpA; Walking Wake's Hydro Steam gets *stronger* in
sun, and both Paradoxes get Protosynthesis for free. The lesson: take the sun
away and half this team stops working.

```
Torkoal @ Heat Rock
Ability: Drought
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Stealth Rock
- Lava Plume
- Rapid Spin
- Yawn

Charizard @ Charizardite Y
Ability: Solar Power
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Fire Blast
- Solar Beam
- Focus Blast
- Roost

Walking Wake @ Choice Specs
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Hydro Steam
- Draco Meteor
- Flamethrower
- Flip Turn

Gouging Fire @ Heavy-Duty Boots
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Flare Blitz
- Outrage
- Earthquake

Venusaur @ Life Orb
Ability: Chlorophyll
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Growth
- Giga Drain
- Sludge Bomb
- Weather Ball

Great Tusk @ Assault Vest
Ability: Protosynthesis
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Headlong Rush
- Close Combat
- Knock Off
- Rapid Spin
```

### A3. Downpour — Mega Swampert

**Lead: Pelipper** sets rain and pivots. **Mega Swampert** (635) gets Swift
Swim on Mega Evolving: 150 Attack, doubled Speed. Raging Bolt's Thunder never
misses in rain, and Booster Energy switches its Protosynthesis on without
sun. The lesson: two Swift Swim sweepers, one rain setter — kill Pelipper.

```
Pelipper @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Hurricane
- Surf
- U-turn
- Roost

Swampert @ Swampertite
Ability: Torrent
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Waterfall
- Earthquake
- Ice Punch
- Rain Dance

Barraskewda @ Choice Band
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Liquidation
- Close Combat
- Flip Turn
- Psychic Fangs

Kingdra @ Life Orb
Ability: Swift Swim
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Hydro Pump
- Draco Meteor
- Hurricane
- Ice Beam

Raging Bolt @ Booster Energy
Ability: Protosynthesis
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Thunderclap
- Thunder
- Draco Meteor
- Calm Mind

Ferrothorn @ Leftovers
Ability: Iron Barbs
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Leech Seed
- Power Whip
- Knock Off
```

---

## Group B — Ubers-grade offense

The Pokémon gauntlets 5 and 6 held back, all at once. Fast, frail, and
built to end games before a defensive player can stabilize.

### B4. Ruin — the four Treasures of Ruin

All four Treasures of Ruin, and every Pokémon on the team is part Dark. Each
Ruin ability lowers one of the player's stats while it's on the field.
**Mega Gyarados** (Water/Dark, Mold Breaker) is the win condition. The
lesson: a team this one-note has one answer, Fighting and Fairy coverage,
and it has to come from more than one Pokémon.

```
Ting-Lu @ Leftovers
Ability: Vessel of Ruin
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Ruination
- Earthquake
- Whirlwind

Wo-Chien @ Rocky Helmet
Ability: Tablets of Ruin
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Leech Seed
- Giga Drain
- Foul Play
- Protect

Chien-Pao @ Focus Sash
Ability: Sword of Ruin
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Icicle Crash
- Sucker Punch
- Sacred Sword

Chi-Yu @ Choice Scarf
Ability: Beads of Ruin
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Overheat
- Dark Pulse
- Flamethrower
- Psychic

Gyarados @ Gyaradosite
Ability: Moxie
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Waterfall
- Crunch
- Earthquake

Kingambit @ Black Glasses
Ability: Supreme Overlord
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Swords Dance
- Kowtow Cleave
- Sucker Punch
- Iron Head
```

### B5. Paradox — the future and the past

Paradoxes everywhere, and only one Booster Energy (the item clause): Flutter
Mane gets it, the rest win on raw stats. **Mega Lucario** (Adaptability)
adds priority. The lesson: these hit hard but don't take hits; Focus Sash
and priority of your own swing the trade.

```
Iron Treads @ Leftovers
Ability: Quark Drive
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Stealth Rock
- Rapid Spin
- Earthquake
- Knock Off

Flutter Mane @ Booster Energy
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Moonblast
- Shadow Ball
- Mystical Fire
- Calm Mind

Roaring Moon @ Life Orb
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Knock Off
- Outrage
- Earthquake

Iron Bundle @ Choice Specs
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Freeze-Dry
- Hydro Pump
- Ice Beam
- Flip Turn

Iron Valiant @ Focus Sash
Ability: Quark Drive
EVs: 4 Atk / 252 SpA / 252 Spe
Naive Nature
- Moonblast
- Close Combat
- Knock Off
- Thunderbolt

Lucario @ Lucarionite
Ability: Justified
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Close Combat
- Meteor Mash
- Extreme Speed
```

### B6. No Brakes — Mega Blaziken and Speed Boost

Everything is fast, and gets faster. **Deoxys-Speed** sets hazards and
Taunts; **Mega Blaziken** gains Speed every turn; Pheromosa's Beast Boost and
a Choice Scarf cover the rest. The lesson: a team built on Speed loses to
priority, Scarf users, and anything that survives the first hit.

```
Deoxys-Speed @ Focus Sash
Ability: Pressure
EVs: 252 HP / 4 SpA / 252 Spe
Timid Nature
- Stealth Rock
- Spikes
- Taunt
- Psycho Boost

Blaziken @ Blazikenite
Ability: Speed Boost
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Swords Dance
- Flare Blitz
- Close Combat
- Protect

Shaymin-Sky @ Life Orb
Ability: Serene Grace
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Seed Flare
- Air Slash
- Earth Power
- Healing Wish

Pheromosa @ Choice Scarf
Ability: Beast Boost
EVs: 252 Atk / 4 SpA / 252 Spe
Naive Nature
- U-turn
- Close Combat
- Ice Beam
- Poison Jab

Kartana @ Choice Band
Ability: Beast Boost
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Leaf Blade
- Sacred Sword
- Smart Strike
- Knock Off

Cinderace @ Heavy-Duty Boots
Ability: Libero
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Pyro Ball
- High Jump Kick
- U-turn
- Court Change
```

---

## Group C — Bulky offense and balance

No single sweeper: a defensive core that absorbs the player's best hits, and
attackers that punish every switch.

### C7. Steel Heart — Mega Metagross and Magearna

**Mega Metagross** (700, Tough Claws) and Magearna (Soul-Heart) lead a
Steel-heavy balance team; Corviknight and Toxapex wall, Heatran traps with
Magma Storm. The lesson: Fire and Ground coverage, and a plan for hazards
(Toxic Spikes, then Defog for the player's own).

```
Metagross @ Metagrossite
Ability: Clear Body
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Meteor Mash
- Zen Headbutt
- Earthquake
- Bullet Punch

Magearna @ Leftovers
Ability: Soul-Heart
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Calm Mind
- Fleur Cannon
- Flash Cannon
- Volt Switch

Zygarde @ Lum Berry
Ability: Aura Break
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Thousand Arrows
- Outrage
- Iron Head

Heatran @ Air Balloon
Ability: Flash Fire
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Magma Storm
- Earth Power
- Flash Cannon
- Taunt

Corviknight @ Rocky Helmet
Ability: Mirror Armor
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Brave Bird
- Roost
- Defog
- U-turn

Toxapex @ Black Sludge
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Recover
- Toxic Spikes
- Haze
```

*(Zygarde is the 50% Forme with Aura Break, per the bans.)*

### C8. Momentum — the pivot loop

U-turn, Volt Switch and Knock Off on almost everything. **Mega Scizor**'s
Technician U-turn and Bullet Punch keep the loop going. The lesson: every
switch costs HP; slow pivots of your own, or a sturdy Assault Vest wall,
break the loop.

```
Landorus-Therian @ Rocky Helmet
Ability: Intimidate
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Stealth Rock
- Earthquake
- U-turn
- Knock Off

Urshifu @ Choice Band
Ability: Unseen Fist
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Wicked Blow
- Close Combat
- U-turn
- Sucker Punch

Zapdos @ Heavy-Duty Boots
Ability: Static
EVs: 252 HP / 4 SpA / 252 Spe
Timid Nature
- Volt Switch
- Hurricane
- Heat Wave
- Roost

Scizor @ Scizorite
Ability: Technician
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- U-turn
- Bullet Punch
- Knock Off
- Swords Dance

Ogerpon-Wellspring @ Wellspring Mask
Ability: Water Absorb
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Ivy Cudgel
- Horn Leech
- U-turn
- Swords Dance

Meowscarada @ Choice Scarf
Ability: Protean
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Flower Trick
- Knock Off
- U-turn
- Triple Axel
```

*(Urshifu is the Single Strike Style.)*

### C9. Dragonfire — Mega Salamence and the Dragon core

Six Dragons or Dragon-adjacent attackers. **Mega Salamence** (700,
Aerilate) turns Double-Edge into a Flying STAB nuke. Archaludon fires Electro
Shot in one turn with Power Herb. The lesson: Fairy and Ice answers, and a
Steel type that can take a Draco Meteor.

```
Archaludon @ Power Herb
Ability: Stamina
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Electro Shot
- Draco Meteor
- Flash Cannon
- Stealth Rock

Salamence @ Salamencite
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Double-Edge
- Earthquake
- Roost

Dragapult @ Choice Specs
Ability: Infiltrator
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Shadow Ball
- Flamethrower
- U-turn

Kommo-o @ Throat Spray
Ability: Overcoat
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Clangorous Soul
- Clanging Scales
- Aura Sphere
- Flamethrower

Naganadel @ Life Orb
Ability: Beast Boost
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Nasty Plot
- Sludge Wave
- Draco Meteor
- Fire Blast

Baxcalibur @ Loaded Dice
Ability: Thermal Exchange
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Icicle Spear
- Scale Shot
- Earthquake
```

---

## Group D — Trap and disrupt

Teams that take the player's options away: switching, setup, priority.

### D10. No Exit — Mega Gengar and Shadow Tag

**Mega Gengar** (Shadow Tag) traps whatever it faces; Heatran's Magma Storm
traps too. Darkrai and Marshadow clean up what's left. The lesson: **Shed
Shell** (sold this wave) and Ghost types can't be trapped; plan for it, or
a Pokémon you can't switch out goes down with the ship.

```
Grimmsnarl @ Light Clay
Ability: Prankster
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Reflect
- Light Screen
- Thunder Wave
- Spirit Break

Gengar @ Gengarite
Ability: Cursed Body
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Shadow Ball
- Sludge Wave
- Focus Blast
- Destiny Bond

Darkrai @ Life Orb
Ability: Bad Dreams
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Nasty Plot
- Dark Pulse
- Sludge Bomb
- Focus Blast

Marshadow @ Expert Belt
Ability: Technician
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Spectral Thief
- Close Combat
- Shadow Sneak
- Ice Punch

Deoxys-Attack @ Focus Sash
Ability: Pressure
EVs: 4 Atk / 252 SpA / 252 Spe
Naive Nature
- Psycho Boost
- Superpower
- Knock Off
- Extreme Speed

Heatran @ Leftovers
Ability: Flash Fire
EVs: 252 HP / 4 SpA / 252 SpD
Calm Nature
- Magma Storm
- Earth Power
- Taunt
- Protect
```

### D11. Stonewall — Unaware stall

Two Unaware walls (Skeledirge, Dondozo) make the player's stat boosts
worthless; Toxapex, Gliscor and Blissey grind with poison and hazards. **Mega
Venusaur** (Thick Fat) checks the Fire and Ice moves meant for the Grass and
Water walls. The lesson: setup does nothing here. Taunt, Knock Off, and raw
power do.

```
Gliscor @ Toxic Orb
Ability: Poison Heal
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Earthquake
- Knock Off
- Spikes
- Protect

Skeledirge @ Heavy-Duty Boots
Ability: Unaware
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Torch Song
- Slack Off
- Will-O-Wisp
- Hex

Blissey @ Leftovers
Ability: Natural Cure
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Seismic Toss
- Soft-Boiled
- Stealth Rock
- Heal Bell

Toxapex @ Black Sludge
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Recover
- Toxic Spikes
- Haze

Venusaur @ Venusaurite
Ability: Chlorophyll
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Giga Drain
- Sludge Bomb
- Synthesis
- Leech Seed

Dondozo @ Rocky Helmet
Ability: Unaware
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Wave Crash
- Rest
- Sleep Talk
- Curse
```

### D12. Mind Games — Psychic Terrain

**Tapu Lele** sets Psychic Terrain, which blocks the player's priority moves
and boosts every Psychic attack. Espathra climbs with Speed Boost and Stored
Power; **Mega Gardevoir** (Pixilate) hits with boosted Fairy-type Hyper
Voice. The lesson: Sucker Punch and Extreme Speed won't save you here; Dark
types and Steel types will.

```
Azelf @ Focus Sash
Ability: Levitate
EVs: 252 Atk / 4 SpA / 252 Spe
Naive Nature
- Stealth Rock
- Taunt
- Psychic
- Explosion

Tapu Lele @ Choice Specs
Ability: Psychic Surge
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Psyshock
- Moonblast
- Focus Blast
- Psychic

Espathra @ Leftovers
Ability: Speed Boost
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Calm Mind
- Stored Power
- Dazzling Gleam
- Protect

Necrozma @ Weakness Policy
Ability: Prism Armor
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Swords Dance
- Photon Geyser
- Earthquake
- Knock Off

Gardevoir @ Gardevoirite
Ability: Trace
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Hyper Voice
- Psyshock
- Calm Mind
- Focus Blast

Slowking-Galar @ Heavy-Duty Boots
Ability: Regenerator
EVs: 252 HP / 4 SpA / 252 SpD
Sassy Nature
- Future Sight
- Sludge Bomb
- Chilly Reception
- Slack Off
```

---

## Boss — Palace Maven Spenser

**Pool:** everything, with no theme and no cap: **the strongest singles team
the game can field**. One box-art legendary, **Zacian** (Crowned, with the
Rusted Sword), and one Mega the player can't own yet, **Mega Zeraora** (700,
153 Speed): Zeraorite arrives in wave 7, after Spenser falls. Scott's
legendaries (Rayquaza, Groudon, Kyogre, Mewtwo) stay his.

**Gimmick: everything, all at once.** Ting-Lu lays Stealth Rock and Spikes.
Crowned Zacian (Intrepid Sword, +1 Attack on entry) Swords Dances and sweeps
with Behemoth Blade. Mega Zeraora outspeeds almost anything. Chien-Pao's
Sword of Ruin lowers the player's Defense for every physical hit. Great Tusk
clears the player's hazards; Choice Specs Flutter Mane breaks special walls.

**AI:** omniscient, proactive switching. No ace flag.

```
Ting-Lu @ Leftovers
Ability: Vessel of Ruin
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Ruination
- Whirlwind
- Spikes

Zacian @ Rusted Sword
Ability: Intrepid Sword
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Iron Head
- Play Rough
- Close Combat

Zeraora @ Zeraorite
Ability: Volt Absorb
EVs: 252 Atk / 4 SpA / 252 Spe
Jolly Nature
- Plasma Fists
- Close Combat
- Knock Off
- Volt Switch

Flutter Mane @ Choice Specs
Ability: Protosynthesis
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Moonblast
- Shadow Ball
- Mystical Fire
- Thunderbolt

Great Tusk @ Booster Energy
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Rapid Spin
- Headlong Rush
- Ice Spinner
- Close Combat

Chien-Pao @ Focus Sash
Ability: Sword of Ruin
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Icicle Crash
- Sucker Punch
- Sacred Sword
```

*(Zacian holds the Rusted Sword, so it becomes Crowned Zacian at the start of
battle, and Iron Head becomes Behemoth Blade.)*

### The strategic dependency

**Hazards in, then a sweep.** Ting-Lu's rocks and Spikes chip every switch;
Great Tusk spins away the player's. Then Zacian, Mega Zeraora or Chien-Pao
sets up or cleans, each faster or stronger than anything the player can
normally field. Sword of Ruin makes every physical hit land harder.

The fix is to **stop the setup** (Taunt, phazing, Unaware, priority on the
Focus Sash) and keep hazards off your side.

### Counterplay available at tier 7

- **Fire and Ground for Zacian** (Fairy/Steel): Heatran (Air Balloon),
  Gouging Fire, Great Tusk, Landorus. Unaware walls (Skeledirge, Dondozo)
  ignore its Swords Dance
- **Ground for Mega Zeraora**; it's frail (75/80 defences), so priority and
  Scarf users finish it
- **Fighting, Fire, Steel and Fairy for Chien-Pao**; Focus Sash breaks to
  hazards or a multi-hit move
- **Steel for Flutter Mane**: Gholdengo, Kingambit, Heatran
- **Water, Grass and Ice for Ting-Lu**; Defog or Rapid Spin for its hazards.
  **Ghost types** (Gholdengo, Dragapult, Flutter Mane) block Great Tusk's
  Rapid Spin, so the player's own hazards stay up
- **Taunt** stops Ting-Lu's hazards and Zacian's and Chien-Pao's Swords Dance

---

## Benchmark counter-team

Built only from gauntlet 7's pool (wave 6 and earlier), items and bans. Item
clause compliant. One Mega.

```
Heatran @ Air Balloon
Ability: Flash Fire
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Magma Storm
- Earth Power
- Flash Cannon
- Taunt

Urshifu @ Choice Band
Ability: Unseen Fist
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Wicked Blow
- Close Combat
- U-turn
- Sucker Punch

Iron Bundle @ Choice Specs
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Freeze-Dry
- Hydro Pump
- Ice Beam
- Flip Turn

Raging Bolt @ Booster Energy
Ability: Protosynthesis
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Thunderclap
- Thunderbolt
- Draco Meteor
- Calm Mind

Lucario @ Lucarionite
Ability: Justified
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Close Combat
- Meteor Mash
- Extreme Speed

Corviknight @ Leftovers
Ability: Pressure
EVs: 252 HP / 4 Atk / 252 Def
Impish Nature
- Brave Bird
- Roost
- Defog
- U-turn
```

**Against Spenser:** Heatran (Air Balloon) walls Zacian and Flutter Mane and
breaks Zacian with Earth Power and Magma Storm; Urshifu's Close Combat and
Wicked Blow remove Chien-Pao and Ting-Lu; Iron Bundle's Hydro Pump and
Freeze-Dry handle Great Tusk and Ting-Lu; Mega Lucario's Extreme Speed
finishes Mega Zeraora and breaks Chien-Pao's Focus Sash with Close Combat;
Corviknight Defogs Ting-Lu's hazards. **Against the pool:** Corviknight
answers B4's Ruin team and Group A's ground attackers, Lucario's Extreme
Speed picks off B6's frail speed demons, and Heatran traps D11's stall walls.

---

## Open for playtesting

1. **Treasures of Ruin (B4).** In singles only the active Pokémon's Ruin
   ability applies, so it's one stat drop at a time. Check it still feels
   oppressive rather than gimmicky.
2. **Shadow Tag (D10).** Mega Gengar plus Destiny Bond can feel unfair. Shed
   Shell is sold this wave; make sure the player has reason to know it.
3. **Two Unaware walls (D11).** Stall against the AI can drag. If battles run
   too long, swap Dondozo for an attacker.
4. **The uncapped boss.** Crowned Zacian and Mega Zeraora are a deliberate
   jump above the pool. Check it's beatable with wave 6 and earlier; the
   counter-team above is the benchmark.
5. **Booster Energy on pool teams (A3, B5).** The shop doesn't sell it any
   more: the researcher in Oldale's first house pays one per Paradox species
   shown, reachable by ferry from gauntlet 5 (the first Paradox wave), so
   pool teams may carry it. Check the AI uses Raging Bolt and Flutter Mane's boosts
   sensibly.
6. **Repeated Pokémon.** Heatran, Toxapex, Corviknight and Venusaur each
   appear on two teams. Swap some if it feels repetitive.

---

## Implementation notes

What was built, and where. Keep the sets above in sync with
`src/data/trainers.party`; the trainer entries were generated from this doc,
and every move was checked against `all_learnables.json`.

- **Trainers:** `TRAINER_FACILITY_B7_*` (IDs 935–947; `TRAINERS_COUNT` is now
  948, still under the 1000 limit) in `include/constants/opponents.h` and
  `src/data/trainers.party`, all singles. Classes: Ruin Maniac (A1), Kindler
  (A2), Swimmer (A3), PokéManiac (B4), Expert (B5, D11), Triathlete (B6, C8),
  Cooltrainer (C7), Dragon Tamer (C9), Hex Maniac (D10), Psychic (D12);
  Spenser is the Palace Maven with his own pic. Spenser's AI adds Omniscient
  and Ace Pokemon (Magearna is last in the party).
- **Run loop:** `FACILITY_GAUNTLET_7` (`include/constants/facility.h`) and
  `sGauntlet7Pool` in `src/facility.c`. The shared dispatch in the Tower
  lobby script routes gauntlet 7 to `Facility_DoBattle_B7` and
  `Facility_Battle_Boss_B7`, in the Palace lobby's script.
- **The Palace** opens when gauntlet 6 is cleared (`IsBattlePalaceUnlocked`).
  Its Singles attendant runs the gauntlet; the Doubles attendant is closed.
  New plaque, rules board and four lobby NPCs. Clearing gauntlet 6 and 7 have
  their own completion messages (the Pyramid "still being prepared").
- **Shop wave 6** (`unlockGauntlet` 6 in `src/facility_shop.c`): the Pokémon,
  Mega Stones and items above. Ability overrides for Landorus (Sheer Force),
  Enamorus (Contrary), Espathra (Speed Boost) and Houndstone (Fluffy).
  **Blaziken** gets Speed Boost only once gauntlet 6 is cleared (before that
  it's sold with Blaze), in `GetShopMonAbilityNum()`.
- **Elsewhere:** Spenser is on the Arena's sparring list (and the mock
  battle covers gauntlet 7); the Palace sign, the Reception guide, Scott's
  progress line and the Lounge 2 news desk all know about gauntlet 7.
- **Renaming the gauntlet:** "THE OPEN COURT" appears in the Palace lobby's
  texts, `Facility_B6_Text_GauntletComplete` / `Facility_B7_Text_GauntletComplete`,
  the Palace sign and the Reception guide.

---

## Next steps

1. Playtest gauntlet 7 (see "Open for playtesting").
2. Settle open questions 1, 2 and 5, then design gauntlet 8 (doubles, the
   Battle Pyramid, Pyramid King Brandon) and wave 7.
3. Update Lucy (`gauntlet-06.md`) only if Gengarite's wave changes.
