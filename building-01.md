# Building 1 — "Little League"

Singles, 6v6, level 50. BST cap 420. Six battles drawn from twelve, then the
boss.

**Design intent:** teach the type chart and basic STAB discipline. The six
regular battles should be genuinely easy for anyone who builds a team with
sensible coverage. The boss is the wall.

**Item clause:** no two Pokémon on a team may hold the same item. This applies
to the player and to every CPU team. All teams below are compliant.


**Structural conceit:** each of the twelve trainers is a single-type
specialist. This makes the lesson explicit — every trainer is a type-matchup
puzzle with an obvious answer, and a player who brings six Normal-types will
notice quickly.

---

## Bans at this tier

Under the cap but excluded:

| Pokémon | BST | Reason |
|---|---|---|
| Azumarill | 420 | Huge Power — effectively 100 base Attack, dominates the tier |
| Linoone | 420 | Belly Drum + Extreme Speed, straightforward sweep |
| Medicham | 410 | Pure Power + High Jump Kick — same problem as Azumarill |
| Smeargle | 250 | Sketch grants access to anything; breaks all tiering |
| Wobbuffet | 405 | Shadow Tag trapping is miserable in 6v6 singles |
| Shedinja | 236 | Wonder Guard is binary — unkillable or free, never a fight |
| Ditto | 288 | Imposter copying the player's best mon is unfun at this tier |
| Wishiwashi | 175 | Schooling form is 620 BST; the cap doesn't measure it |

**Borderline, allowed for now:** Sableye (Prankster Will-O-Wisp + Recover is
strong but slow and passive), Parasect and Butterfree (reliable sleep). Watch
these in playtesting — if sleep with no bag items proves miserable, cut the
sleep moves rather than the Pokémon.

---

## Player pool

Curated, not exhaustive. Roughly ten to fourteen options per type gives the
player real choice without overwhelming a first building.

**Fire** — Charmeleon, Quilava, Combusken, Monferno, Braixen, Torracat, Raboot,
Crocalor, Pignite, Ponyta, Growlithe, Larvesta

**Water** — Wartortle, Croconaw, Marshtomp, Prinplup, Dewott, Frogadier,
Quaxwell, Brionne, Drizzile, Poliwhirl, Corsola, Staryu

**Grass** — Ivysaur, Bayleef, Grovyle, Grotle, Servine, Quilladin, Thwackey,
Dartrix, Floragato, Roselia, Ferroseed, Foongus

**Electric** — Flaaffy, Luxio, Plusle, Minun, Pachirisu, Chinchou, Charjabug,
Magnemite, Elekid, Joltik

**Normal** — Furret, Raticate, Dunsparce, Delcatty, Spinda, Chatot, Lickitung,
Porygon, Aipom, Teddiursa

**Bug** — Butterfree, Beedrill, Masquerain, Ariados, Dustox, Beautifly, Ledian,
Parasect, Yanma, Kricketune, Whirlipede

**Poison** — Nidorino, Nidorina, Roselia, Ariados, Koffing, Grimer, Whirlipede,
Skrelp, Mareanie, Croagunk, Stunky

**Flying** — Pidgeotto, Staravia, Tranquill, Fletchinder, Murkrow, Chatot,
Masquerain, Rufflet, Vullaby, Woobat

**Psychic** — Kadabra, Metang, Drowzee, Natu, Spoink, Kirlia, Munna, Solosis,
Espurr, Bronzor

**Fighting** — Machoke, Gurdurr, Combusken, Monferno, Scraggy, Mienfoo, Pancham,
Timburr, Croagunk, Stufful

**Rock / Ground** — Sudowoodo, Nosepass, Graveler, Pupitar, Onix, Boldore,
Gabite, Krokorok, Mudbray, Palpitoad, Marshtomp

**Dark / Ghost** — Mightyena, Murkrow, Sableye, Haunter, Lampent, Scraggy,
Pawniard, Zorua, Drifloon, Morgrem

---

## Shop — building 1 inventory

Pokémon: 100–250 FP depending on tier within the pool.

| Item | FP | Note |
|---|---|---|
| Leftovers | 150 | The only passive recovery available |
| Charcoal / Mystic Water / Miracle Seed / Magnet | 60 each | 20% type boost |
| Sharp Beak / Poison Barb / Soft Sand / Hard Stone | 60 each | |
| Silver Powder / Spell Tag / Twisted Spoon / Black Belt | 60 each | |
| Black Glasses / Silk Scarf / Never-Melt Ice / Metal Coat | 60 each | |
| Figy / Wiki / Mago / Aguav / Iapapa Berry | 80 each | Pinch recovery |
| Liechi / Petaya Berry | 100 each | Pinch stat boost |

No Choice items, no Life Orb, no Focus Sash, no Eviolite. Those arrive later.

---

## AI flags

Full offensive intelligence plus smart replacement, but no proactive switching:

- Avoid clearly bad moves
- Try to KO
- Check viability
- HP awareness
- Setup logic
- **Smart replacement choice** — picks the best answer after a faint

**Two different behaviors, two different flags.** Choosing a good replacement
after something faints is free difficulty with no downside, and should be on
from building 1. Proactively switching out a *healthy* Pokémon mid-battle is
the one to hold back — at this tier the teams are six roughly equivalent
Pokémon with no real defensive cores, so the CPU pivots for marginal gains and
the player spends turns chasing it. Turn that on around building 3, once teams
have pivots worth making.

**Not** omniscient, except the boss.

Verify exact constant names in `include/constants/battle_ai.h` — they have
changed between expansion versions.

---

## Party order

**The first Pokémon listed is the lead and is sent out first.** Every team
below has its lead chosen deliberately, with the reasoning stated above the
team. Leads fall into four patterns at this tier: status (Butterfree, Sableye),
hazards (Quilladin, Metang, Graveler), momentum (Furret, Mienfoo, Croagunk,
Hariyama), and immediate pressure (Frogadier, Fletchinder, Luxio, Combusken).

**Order the rest of the party sensibly, but don't over-think it.** With smart
replacement enabled the AI picks its best answer after a faint rather than
walking down the list, so party order past slot one is a fallback rather than
the primary mechanism.

**The boss's ace goes last.** Altaria is in slot six and should be flagged as
the ace so the AI holds it in reserve rather than leading with it. Check the
ace flag's exact name in `include/constants/battle_ai.h`.

---

## The twelve teams

All Pokémon level 50, 31 IVs across the board unless noted.

### 1. Ember — Fire

**Lead: Combusken.** Flame Charge snowballs speed; the longer it lives the harder the rest hits.

```
Combusken @ Charcoal
Ability: Blaze
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Flame Charge
- Sky Uppercut
- Bulk Up
- Rock Slide

Quilava @ Silk Scarf
Ability: Blaze
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Flamethrower
- Extrasensory
- Quick Attack
- Swift

Ponyta @ Figy Berry
Ability: Flash Fire
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Flare Blitz
- Wild Charge
- Double-Edge
- Morning Sun

Crocalor @ Leftovers
Ability: Blaze
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Incinerate
- Yawn
- Bite
- Hypnosis

Larvesta @ Never-Melt Ice
Ability: Flame Body
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Flare Blitz
- U-turn
- Wild Charge
- Take Down

Torracat @ Black Belt
Ability: Blaze
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Fire Fang
- Double Kick
- Bite
- Leech Life
```

### 2. Brook — Water

**Lead: Frogadier.** Fastest thing on the team. Applies immediate special pressure before trading.

```
Frogadier @ Mystic Water
Ability: Torrent
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Water Pulse
- Ice Beam
- Round
- Quick Attack

Marshtomp @ Leftovers
Ability: Torrent
EVs: 252 Atk / 4 Def / 252 SpD
Adamant Nature
- Earthquake
- Waterfall
- Rock Slide
- Protect

Prinplup @ Metal Coat
Ability: Torrent
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Surf
- Ice Beam
- Bubble Beam
- Metal Claw

Corsola @ Mago Berry
Ability: Natural Cure
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Recover
- Scald
- Power Gem
- Toxic

Croconaw @ Silk Scarf
Ability: Torrent
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Waterfall
- Crunch
- Ice Fang
- Dragon Dance

Staryu @ Magnet
Ability: Natural Cure
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Surf
- Thunderbolt
- Ice Beam
- Recover
```

### 3. Fern — Grass

**Lead: Quilladin.** Spikes lead. Bulky enough to get a layer down against most openers.

```
Quilladin @ Silk Scarf
Ability: Overgrow
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Seed Bomb
- Body Slam
- Spikes
- Synthesis

Grovyle @ Miracle Seed
Ability: Overgrow
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Leaf Blade
- Rock Slide
- X-Scissor
- Quick Attack

Roselia @ Leftovers
Ability: Natural Cure
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Giga Drain
- Sludge Bomb
- Sleep Powder
- Synthesis

Ivysaur @ Poison Barb
Ability: Overgrow
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Giga Drain
- Sludge Bomb
- Leech Seed
- Synthesis

Dartrix @ Sharp Beak
Ability: Overgrow
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Leaf Blade
- Pluck
- Synthesis
- Foul Play

Ferroseed @ Metal Coat
Ability: Iron Barbs
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Seed Bomb
- Gyro Ball
- Spikes
- Protect
```

### 4. Volt — Electric

**Lead: Luxio.** Intimidate on entry blunts the player's physical lead for free.

```
Luxio @ Magnet
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Spark
- Crunch
- Ice Fang
- Fire Fang

Flaaffy @ Leftovers
Ability: Static
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Thunderbolt
- Thunder Wave
- Cotton Guard
- Power Gem

Chinchou @ Mystic Water
Ability: Volt Absorb
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Surf
- Thunderbolt
- Ice Beam
- Confuse Ray

Charjabug @ Silver Powder
Ability: Battery
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Discharge
- X-Scissor
- Sticky Web
- Iron Defense

Plusle @ Petaya Berry
Ability: Plus
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Nasty Plot
- Grass Knot
- Encore

Magnemite @ Metal Coat
Ability: Magnet Pull
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Thunderbolt
- Flash Cannon
- Volt Switch
- Thunder Wave
```

### 5. Marlo — Normal

**Lead: Furret.** U-turn pivot. Scouts the player's lead and hands the matchup to the right teammate.

```
Furret @ Silk Scarf
Ability: Frisk
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Double-Edge
- Coil
- Knock Off
- U-turn

Raticate @ Black Glasses
Ability: Guts
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Facade
- Crunch
- Sucker Punch
- Swords Dance

Dunsparce @ Leftovers
Ability: Serene Grace
EVs: 252 HP / 252 Def / 4 SpD
Careful Nature
- Headbutt
- Glare
- Coil
- Roost

Porygon @ Never-Melt Ice
Ability: Download
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Tri Attack
- Ice Beam
- Thunderbolt
- Recover

Lickitung @ Figy Berry
Ability: Own Tempo
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Body Slam
- Knock Off
- Wish
- Protect

Chatot @ Sharp Beak
Ability: Tangled Feet
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Boomburst
- Heat Wave
- Nasty Plot
- Chatter
```

### 6. Mira — Bug

**Lead: Butterfree.** Compound Eyes Sleep Powder at 98% accuracy. Removes one player Pokémon turn one.

```
Butterfree @ Silver Powder
Ability: Compound Eyes
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Sleep Powder
- Bug Buzz
- Air Slash
- Quiver Dance

Masquerain @ Leftovers
Ability: Intimidate
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Air Slash
- Bug Buzz
- Quiver Dance
- Sticky Web

Beedrill @ Poison Barb
Ability: Swarm
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Poison Jab
- X-Scissor
- Drill Run
- Swords Dance

Parasect @ Miracle Seed
Ability: Dry Skin
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Spore
- Seed Bomb
- X-Scissor
- Leech Life

Ariados @ Black Glasses
Ability: Insomnia
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Megahorn
- Poison Jab
- Sticky Web
- Sucker Punch

Yanma @ Sharp Beak
Ability: Speed Boost
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Bug Buzz
- Air Slash
- Ancient Power
- Protect
```

### 7. Sable — Poison

**Lead: Croagunk.** Fake Out for free chip and guaranteed momentum.

```
Croagunk @ Black Belt
Ability: Dry Skin
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Poison Jab
- Drain Punch
- Sucker Punch
- Fake Out

Nidorino @ Poison Barb
Ability: Poison Point
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Poison Jab
- Horn Attack
- Double Kick
- Sucker Punch

Koffing @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Sludge Bomb
- Will-O-Wisp
- Pain Split
- Clear Smog

Whirlipede @ Iapapa Berry
Ability: Poison Point
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Venoshock
- Toxic
- Iron Defense
- Protect

Mareanie @ Mystic Water
Ability: Merciless
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Toxic
- Recover
- Venoshock

Skrelp @ Wiki Berry
Ability: Poison Point
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Sludge Bomb
- Scald
- Toxic
- Protect
```

### 8. Gale — Flying

**Lead: Fletchinder.** Gale Wings priority Acrobatics. Punishes slow or weakened leads instantly.

```
Fletchinder @ Sharp Beak
Ability: Gale Wings
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Acrobatics
- Flame Charge
- Swords Dance
- Roost

Staravia @ Silk Scarf
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Brave Bird
- Double-Edge
- Close Combat
- U-turn

Murkrow @ Black Glasses
Ability: Prankster
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Brave Bird
- Sucker Punch
- Thunder Wave
- Taunt

Vullaby @ Leftovers
Ability: Overcoat
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Foul Play
- Roost
- Toxic
- Whirlwind

Woobat @ Twisted Spoon
Ability: Simple
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Calm Mind
- Air Slash
- Stored Power
- Roost

Pidgeotto @ Figy Berry
Ability: Keen Eye
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Wing Attack
- Quick Attack
- U-turn
- Roost
```

### 9. Cass — Psychic

**Lead: Metang.** Stealth Rock lead. Clear Body means Intimidate leads can't soften it.

```
Metang @ Metal Coat
Ability: Clear Body
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Meteor Mash
- Zen Headbutt
- Bullet Punch
- Stealth Rock

Kadabra @ Twisted Spoon
Ability: Synchronize
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Psychic
- Shadow Ball
- Dazzling Gleam
- Calm Mind

Drowzee @ Leftovers
Ability: Insomnia
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Psychic
- Hypnosis
- Seismic Toss
- Protect

Natu @ Wiki Berry
Ability: Magic Bounce
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Psychic
- Night Shade
- Roost
- Thunder Wave

Solosis @ Petaya Berry
Ability: Magic Guard
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Psychic
- Shadow Ball
- Calm Mind
- Recover

Espurr @ Spell Tag
Ability: Own Tempo
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Psychic
- Shadow Ball
- Charge Beam
- Yawn
```

### 10. Dex — Fighting

**Lead: Mienfoo.** Fake Out plus Regenerator U-turn. Free damage, free scout, free switch.

```
Mienfoo @ Silk Scarf
Ability: Regenerator
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- High Jump Kick
- U-turn
- Knock Off
- Fake Out

Machoke @ Black Belt
Ability: No Guard
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dynamic Punch
- Knock Off
- Ice Punch
- Bullet Punch

Gurdurr @ Leftovers
Ability: Guts
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Drain Punch
- Mach Punch
- Knock Off
- Bulk Up

Scraggy @ Black Glasses
Ability: Shed Skin
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Drain Punch
- Knock Off
- Dragon Dance
- Zen Headbutt

Monferno @ Charcoal
Ability: Blaze
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Close Combat
- Flare Blitz
- Mach Punch
- Swords Dance

Pancham @ Figy Berry
Ability: Iron Fist
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Drain Punch
- Body Slam
- Crunch
- Bullet Punch
```

### 11. Quarry — Rock / Ground

**Lead: Graveler.** Sturdy guarantees Stealth Rock goes up no matter what it faces.

```
Graveler @ Leftovers
Ability: Sturdy
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Earthquake
- Rock Blast
- Stealth Rock
- Explosion

Gabite @ Soft Sand
Ability: Rough Skin
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Dragon Claw
- Rock Slide
- Swords Dance

Sudowoodo @ Hard Stone
Ability: Rock Head
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Head Smash
- Wood Hammer
- Earthquake
- Sucker Punch

Pupitar @ Liechi Berry
Ability: Shed Skin
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Rock Slide
- Earthquake
- Crunch
- Dragon Dance

Krokorok @ Black Glasses
Ability: Moxie
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Crunch
- Rock Slide
- Pursuit

Nosepass @ Iapapa Berry
Ability: Sturdy
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Stealth Rock
- Rock Slide
- Thunder Wave
- Rest
```

### 12. Nyx — Dark / Ghost

**Lead: Sableye.** Prankster Will-O-Wisp or Taunt before the player moves. Shuts down physical and setup leads alike.

```
Sableye @ Leftovers
Ability: Prankster
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Will-O-Wisp
- Recover
- Foul Play
- Taunt

Haunter @ Spell Tag
Ability: Levitate
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Shadow Ball
- Sludge Bomb
- Hypnosis
- Destiny Bond

Mightyena @ Black Glasses
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Crunch
- Play Rough
- Sucker Punch
- Howl

Lampent @ Charcoal
Ability: Flash Fire
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Shadow Ball
- Flamethrower
- Energy Ball
- Pain Split

Pawniard @ Metal Coat
Ability: Defiant
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Knock Off
- Iron Head
- Sucker Punch
- Swords Dance

Drifloon @ Wiki Berry
Ability: Unburden
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Shadow Ball
- Hex
- Will-O-Wisp
- Calm Mind
```

---

## Boss — Warden Helis

**Pool:** building 2 (≤500 BST) plus everything from building 1.

**Gimmick:** a Dragon Dance sweeper protected by a team that removes its
checks. Altaria is the win condition; everything else exists to clear the way
for it.

**Why this is the right first boss:** it's the simplest complete strategy in
competitive Pokémon, it's legible after one loss, and the answers all exist in
the building 1 shop.

**AI:** omniscient. Altaria held in reserve as the ace.

**Lead: Hariyama.** Fake Out opens every game. Free chip, free momentum, and Thick Fat means Fire and Ice leads don't punish it.

```
Hariyama @ Black Belt
Ability: Thick Fat
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Fake Out
- Close Combat
- Knock Off
- Bullet Punch

Manectric @ Magnet
Ability: Lightning Rod
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Flamethrower
- Volt Switch
- Hidden Power Ice

Jumpluff (no item)
Ability: Infiltrator
EVs: 252 HP / 4 Def / 252 Spe
Jolly Nature
- Sleep Powder
- Leech Seed
- Acrobatics
- U-turn

Crawdaunt @ Mystic Water
Ability: Adaptability
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Crabhammer
- Knock Off
- Aqua Jet
- Swords Dance

Claydol @ Iapapa Berry
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Earth Power
- Ice Beam
- Stealth Rock
- Rapid Spin

Altaria @ Leftovers
Ability: Natural Cure
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Dragon Claw
- Earthquake
- Roost
```

### Counterplay available at tier 1

The player must be able to find these in their own shop, or the boss is unfair
rather than hard:

- **Sableye** — Prankster Will-O-Wisp halves Altaria's Attack through a Dragon
  Dance, and Taunt shuts down Roost
- **Mightyena / Pawniard / Croagunk** — Sucker Punch ignores the speed boost
- **Flaaffy / Magnemite** — Thunder Wave before the sweep starts
- **Ice coverage** — Ice Beam or Ice Fang from the Water pool hits Altaria for
  four times damage
- **Ferroseed / Quilladin** — Iron Barbs and bulk blunt the physical sweep

**Playtest checkpoint:** if a competent tier-1 team loses to Altaria with no
recourse, the boss is too strong and the fix is dropping Roost, not lowering
its stats. A sweeper without recovery is still a puzzle; a sweeper the player
can't interact with is a wall.

---

## Optimal counter-team for the boss

Built only from building 1's pool, items and bans. Item clause compliant. This
is the benchmark: if this team can't beat Helis reliably, the boss needs
tuning.

```
Sableye @ Leftovers
Ability: Prankster
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Will-O-Wisp
- Taunt
- Recover
- Foul Play

Ferroseed @ Metal Coat
Ability: Iron Barbs
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Gyro Ball
- Seed Bomb
- Protect
- Curse

Chinchou @ Mystic Water
Ability: Volt Absorb
EVs: 252 HP / 4 Def / 252 SpA
Modest Nature
- Surf
- Ice Beam
- Thunderbolt
- Confuse Ray

Pawniard @ Black Glasses
Ability: Defiant
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Sucker Punch
- Knock Off
- Iron Head
- Swords Dance

Marshtomp @ Soft Sand
Ability: Torrent
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Earthquake
- Waterfall
- Rock Slide
- Protect

Parasect @ Miracle Seed
Ability: Dry Skin
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Spore
- Seed Bomb
- X-Scissor
- Leech Life
```

### Why each slot

**Sableye** is the linchpin. Prankster Will-O-Wisp halves the Attack of
Hariyama, Crawdaunt and Altaria regardless of speed, and priority Taunt shuts
down Roost and Leech Seed. Foul Play uses Altaria's own Dragon Dance boosts
against it.

**Ferroseed** resists Water, Grass, Dragon and Flying, which walls Crawdaunt
and Altaria simultaneously. Nothing on Helis's team carries a Fire move, so its
main weakness is unexploited. Gyro Ball off minimum speed hits a +1 Altaria
hard.

**Chinchou** blanks Manectric completely — Volt Absorb turns Thunderbolt into
healing, and Manectric's Lightning Rod is irrelevant because Chinchou isn't
relying on Electric moves. Ice Beam hits Altaria, Jumpluff and Claydol.

**Pawniard** is the revenge killer. Sucker Punch ignores a Dragon Dance speed
boost entirely, which is the single most important interaction in the fight.
Knock Off strips Leftovers from Altaria and Claydol.

**Marshtomp** is immune to Electric, so it's a second hard switch-in to
Manectric, and Rock Slide punishes Altaria on the way in.

**Parasect** hard-counters Crawdaunt: Dry Skin heals from Crabhammer and Aqua
Jet, and Grass resists Water. Spore is the emergency button on anything that
sets up. Keep it away from Claydol's Ice Beam and Jumpluff's Acrobatics.

### Game plan

1. Lead Sableye. Burn whatever comes in. Taunt anything that tries to set up.
2. Bring Parasect in on Crawdaunt. Spore whatever replaces it.
3. Keep Pawniard at full health and in reserve — it exists solely to Sucker
   Punch Altaria.
4. Don't let Ferroseed take a Close Combat. Hariyama is its only real threat.
5. Altaria comes last as the ace. Ideally it arrives burned, paralyzed by
   nothing, and facing a healthy Pawniard.

### If this team loses consistently

The boss is over-tuned. In order of preference: remove Roost from Altaria, then
drop Claydol's Ice Beam, then cut the Dragon Dance. Lowering stats is the last
resort — a sweeper the player can interact with is a puzzle, and a sweeper
that's simply weaker is just a worse fight.

---

## Open for playtesting

1. **Sleep** — Parasect, Butterfree, Roselia, Haunter and Drowzee all carry
   it. With no bag items and no Sleep Talk at this level, repeated sleep may
   feel oppressive. Cut moves rather than Pokémon if so.
2. **Sturdy** — Graveler and Nosepass both survive anything once. At a tier
   with no multi-hit moves, this is more annoying than it looks.
3. **Boss difficulty** — the largest unknown. Building 1's player pool is the
   weakest in the game and the boss gap is the widest relative jump.
