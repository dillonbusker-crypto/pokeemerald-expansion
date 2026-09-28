# Building 3 — "The Changing Sky"

**Battle Tower, Multi counter.** Singles, 6v6, level 50. BST cap 550. Six
battles drawn from twelve, then the boss.

**Design intent:** teach that the battlefield itself is a contested resource.
Up to now a Pokémon's ability changed its own stats. Here it changes the rules
for everyone, and the player has to learn to fight for that control rather than
play around it.

**Structural conceit:** four groups of three, one per weather condition, with
terrain folded into the fourth. A player drawing six battles meets at least
three weathers, and the shop sells the setters to fight back with.

| Group | Teams | Condition | What it punishes |
|---|---|---|---|
| A | 1–3 | Rain | No Electric answer, no way to displace weather, slow teams |
| B | 4–6 | Sun | No Fire resist, no priority against Chlorophyll |
| C | 7–9 | Sand | No Rock/Ground/Steel, no answer to chip, no phazing |
| D | 10–12 | Snow & terrain | No Ice resist, ignoring terrain damage boosts |

**Counter naming.** This is the Tower's "Multi" counter in vanilla. Attendant
dialogue needs rewriting — the player shouldn't be told "Multi" at a singles
gauntlet.

**AI change:** proactive switching turns on for regular trainers from this
building. The teams now have genuine defensive cores worth pivoting between, so
it becomes real difficulty rather than the pointless flailing it would have
been at tiers 1 and 2.

---

## Problem with the tier ladder — read this

**The 550 → 599 jump adds almost nothing.** I went looking for what building 4
unlocks over building 3 and the answer is four Pokémon: Arcanine (555),
Florges (552), Archeops (567) and Silvally (570). That's it. The band between
551 and 599 is nearly empty — almost everything strong sits either at 550 and
below or at exactly 600.

Three consequences:

1. **Building 3's boss can't get its power gap from species.** It gets it from
   **items** instead — building 4 unlocks Focus Sash, Life Orb, Assault Vest
   and Heavy-Duty Boots, which the player cannot buy yet. That's the gap, and
   it works, but it's a different mechanism than buildings 1 and 2 used.
2. **Building 4 may feel like a non-event** in terms of what the player can
   buy. Its identity has to come from the item unlocks and the format shift
   back to doubles, not from the roster.
3. **Consider merging or re-cutting the caps.** Options: make building 3 the
   ≤500–550 band and building 4 jump straight to 600 pseudos, collapsing your
   current 5 into 4; or keep the ladder and accept that building 4's draw is
   its items.

Worth deciding before I write building 4.

---

## Bans

Permanent list applies: Smeargle, Wobbuffet, Shedinja, Ditto, Wishiwashi,
Palafin. Azumarill, Medicham and Linoone are legal from building 2 and stay
legal here.

**Two shop restrictions rather than bans:**

**Blaziken is sold with Blaze, not Speed Boost.** Speed Boost Blaziken at a 550
cap is the best Pokémon in the tier by a wide margin — a free +1 Speed every
turn behind Swords Dance ends games before counterplay exists. Since the shop
controls which ability a purchased Pokémon has, this needs no ban, just a sale
restriction. Same handling for any hidden ability that outclasses its tier.

**Chansey with Eviolite is legal and will be oppressive.** 450 BST with a 1.5×
defensive multiplier on top of base 250 HP is a wall nothing at this tier
breaks cleanly. I'm leaving it in because building 7's theme is bulk and
breaking, so the player learning to hate Chansey now is useful preparation. If
it drags games past tedium in playtesting, the fix is delaying Eviolite to
building 4.

---

## Pool additions

Everything from buildings 1 and 2 stays purchasable.

**Weather setters** — Ninetales, Hippowdon, Gigalith, Vanilluxe, Ninetales-Alola,
Abomasnow *(Pelipper, Politoed and Torkoal already available from tier 2)*

**Rain abusers** — Kingdra, Kabutops, Seismitoad, Floatzel, Omastar, Poliwrath,
Gorebyss, Huntail, Toxicroak

**Sun abusers** — Venusaur, Exeggutor, Lilligant, Victreebel, Leafeon,
Tangrowth, Shiftry, Sawsbuck, Cherrim, Charizard, Magmortar, Blaziken *(Blaze
only)*

**Sand abusers** — Excadrill, Stoutland, Lycanroc, Sandaconda, Krookodile,
Rhyperior, Flygon, Mandibuzz

**Snow abusers** — Beartic, Arctozolt, Cetitan, Mamoswine, Froslass, Weavile,
Glaceon, Lapras, Walrein

**Terrain** — Rillaboom (Grassy Surge), Pincurchin (Electric Surge),
Weezing-Galar (Misty Surge), Raichu-Alola, Toxtricity

**General ≤550** — Gardevoir, Gallade, Milotic, Swampert, Sceptile, Crobat,
Scizor, Skarmory, Blissey, Snorlax, Gyarados, Aerodactyl, Starmie, Alakazam,
Machamp, Rotom formes, Ampharos, the Eeveelutions, Slowbro, Slowking, Cloyster,
Nidoking, Nidoqueen, Togekiss, Braviary, Bisharp, Honchkrow, Porygon-Z,
Magnezone, Electivire, Yanmega, Gliscor, Dusknoir, Heracross, Ferrothorn,
Haxorus, Aegislash, Noivern, Hatterene, Grimmsnarl, Annihilape, Kingambit,
Gholdengo, Volcarona

**Eviolite targets** — Chansey, Porygon2, Dusclops, Rhydon, Gligar, Scyther,
Magneton, Type: Null, Doublade, Sneasel

---

## Shop — building 3 additions

| Item | FP | Why it matters here |
|---|---|---|
| Damp Rock / Heat Rock / Smooth Rock / Icy Rock | 200 each | Extends your weather from 5 turns to 8 — the difference between a window and a gameplan |
| Electric / Grassy / Misty / Psychic Seed | 150 each | One-time stat boost on terrain entry |
| Eviolite | 350 | Turns NFE Pokémon into walls. The single most impactful item at this tier |
| Safety Goggles | 250 | Blocks weather chip and powder moves outright |

Pokémon at this tier: 300–500 FP.

**The weather rocks are the signature purchase.** They're the first item that
doesn't improve a Pokémon at all — it improves the *team*. A player who
understands why an eight-turn sandstorm beats a five-turn one has understood
the building.

---

## Group A — Rain

### A1. Downpour — rain offense

**Lead: Pelipper.** Drizzle fires on entry, so the rain is up before the player
has taken a turn. Everything behind it is built to exploit the clock.

```
Pelipper @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hurricane
- Scald
- U-turn
- Roost

Kingdra @ Mystic Water
Ability: Swift Swim
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Hydro Pump
- Draco Meteor
- Ice Beam
- Rain Dance

Barraskewda @ Sharp Beak
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Liquidation
- Close Combat
- Psychic Fangs
- Aqua Jet

Ludicolo @ Leftovers
Ability: Swift Swim
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Surf
- Giga Drain
- Ice Beam
- Rain Dance

Toxicroak @ Black Belt
Ability: Dry Skin
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Drain Punch
- Gunk Shot
- Sucker Punch
- Swords Dance

Seismitoad @ Sitrus Berry
Ability: Swift Swim
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hydro Pump
- Earth Power
- Sludge Bomb
- Stealth Rock
```

### A2. Deluge — rain attrition

**Lead: Politoed.** Sets rain, then Perish Song punishes anything that tries to
wall the team out. This is the first CPU team built to win on the clock rather
than on damage.

```
Politoed @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Ice Beam
- Perish Song
- Protect

Toxapex @ Leftovers
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Toxic
- Recover
- Haze

Ferrothorn @ Metal Coat
Ability: Iron Barbs
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Gyro Ball
- Power Whip
- Stealth Rock
- Leech Seed

Gastrodon @ Sitrus Berry
Ability: Storm Drain
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Scald
- Earth Power
- Recover
- Toxic

Jellicent @ Spell Tag
Ability: Water Absorb
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Surf
- Shadow Ball
- Will-O-Wisp
- Recover

Poliwrath @ Black Belt
Ability: Swift Swim
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Liquidation
- Close Combat
- Bulk Up
- Ice Punch
```

### A3. Thunderhead — rain and Thunder

**Lead: Pelipper.** The point of this team is that Thunder never misses in
rain. U-turn keeps the rain up while bringing in the right Electric type.

```
Pelipper @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hurricane
- Scald
- U-turn
- Roost

Ampharos @ Magnet
Ability: Static
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Thunder
- Focus Blast
- Volt Switch
- Thunder Wave

Lanturn @ Wacan Berry
Ability: Volt Absorb
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Thunder
- Ice Beam
- Scald
- Volt Switch

Rotom-Wash @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hydro Pump
- Thunder
- Volt Switch
- Will-O-Wisp

Kabutops @ Hard Stone
Ability: Swift Swim
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Liquidation
- Stone Edge
- Aqua Jet
- Swords Dance

Toxtricity @ Black Glasses
Ability: Punk Rock
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Overdrive
- Sludge Wave
- Boomburst
- Volt Switch
```

---

## Group B — Sun

### B4. Solar Flare — Chlorophyll offense

**Lead: Ninetales.** Drought on entry, and every Grass-type behind it doubles
its Speed. Solar Beam also skips its charge turn, so the whole team hits
immediately.

```
Ninetales @ Heat Rock
Ability: Drought
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Flamethrower
- Solar Beam
- Nasty Plot
- Will-O-Wisp

Venusaur @ Miracle Seed
Ability: Chlorophyll
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Growth
- Giga Drain
- Sludge Bomb
- Weather Ball

Lilligant @ Sitrus Berry
Ability: Chlorophyll
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Quiver Dance
- Petal Dance
- Sleep Powder
- Pollen Puff

Exeggutor @ Twisted Spoon
Ability: Chlorophyll
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Psychic
- Giga Drain
- Sleep Powder
- Leaf Storm

Torkoal @ Charcoal
Ability: Drought
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Lava Plume
- Earth Power
- Stealth Rock
- Body Press

Victreebel @ Poison Barb
Ability: Chlorophyll
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Leaf Blade
- Sludge Bomb
- Sucker Punch
- Growth
```

### B5. Heat Haze — sun and fire

**Lead: Torkoal.** Bulky enough to survive setting Drought and Stealth Rock
both, and every Fire move behind it gains 50%.

```
Torkoal @ Heat Rock
Ability: Drought
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Lava Plume
- Earth Power
- Stealth Rock
- Body Press

Blaziken @ Black Belt
Ability: Blaze
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Flare Blitz
- Close Combat
- Swords Dance
- Protect

Charizard @ Charcoal
Ability: Solar Power
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Flamethrower
- Air Slash
- Solar Beam
- Roost

Magmortar @ Sitrus Berry
Ability: Flame Body
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Fire Blast
- Thunderbolt
- Focus Blast
- Taunt

Leafeon @ Miracle Seed
Ability: Chlorophyll
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Leaf Blade
- Knock Off
- Double-Edge

Tangrowth @ Leftovers
Ability: Chlorophyll
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Power Whip
- Knock Off
- Earthquake
- Synthesis
```

### B6. Scorched Earth — sun and ground

**Lead: Ninetales.** Same Drought opening, but this team wins with Eruption and
Earth Power rather than Chlorophyll speed.

```
Ninetales @ Heat Rock
Ability: Drought
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Flamethrower
- Solar Beam
- Nasty Plot
- Hypnosis

Camerupt @ Charcoal
Ability: Solid Rock
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Eruption
- Earth Power
- Stealth Rock
- Yawn

Shiftry @ Black Glasses
Ability: Chlorophyll
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Sucker Punch
- Leaf Blade
- Knock Off
- Swords Dance

Solrock @ Hard Stone
Ability: Levitate
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Stone Edge
- Zen Headbutt
- Will-O-Wisp
- Explosion

Flygon @ Soft Sand
Ability: Levitate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Dragon Claw
- U-turn
- Roost

Whimsicott @ Leftovers
Ability: Chlorophyll
EVs: 252 HP / 4 Def / 252 Spe
Timid Nature
- Moonblast
- Encore
- Taunt
- Leech Seed
```

---

## Group C — Sand

### C7. Duststorm — sand offense

**Lead: Hippowdon.** Sand Stream plus Stealth Rock in the same slot, and
Whirlwind punishes anything that tries to set up on its bulk.

```
Hippowdon @ Smooth Rock
Ability: Sand Stream
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Earthquake
- Stealth Rock
- Slack Off
- Whirlwind

Excadrill @ Soft Sand
Ability: Sand Rush
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Iron Head
- Rock Slide
- Swords Dance

Stoutland @ Silk Scarf
Ability: Sand Rush
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Return
- Crunch
- Superpower
- Play Rough

Gigalith @ Hard Stone
Ability: Sand Stream
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Stone Edge
- Earthquake
- Explosion
- Rock Blast

Sandaconda @ Sitrus Berry
Ability: Sand Spit
EVs: 252 HP / 252 Atk / 4 Def
Impish Nature
- Coil
- Earthquake
- Glare
- Rock Slide

Mandibuzz @ Leftovers
Ability: Overcoat
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Foul Play
- Roost
- Toxic
- Defog
```

### C8. Attrition Sands — sand stall

**Lead: Hippowdon.** This team never tries to knock anything out. It sets sand,
sets hazards, and waits. The player's own team runs out of resources first.

```
Hippowdon @ Smooth Rock
Ability: Sand Stream
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Earthquake
- Stealth Rock
- Slack Off
- Whirlwind

Skarmory @ Leftovers
Ability: Sturdy
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Brave Bird
- Spikes
- Roost
- Whirlwind

Chansey @ Eviolite
Ability: Natural Cure
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Seismic Toss
- Soft-Boiled
- Toxic
- Thunder Wave

Rhyperior @ Hard Stone
Ability: Solid Rock
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Earthquake
- Rock Blast
- Megahorn
- Swords Dance

Dusclops @ Spell Tag
Ability: Pressure
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Night Shade
- Will-O-Wisp
- Pain Split
- Haze

Toxapex @ Passho Berry
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Toxic
- Recover
- Haze
```

### C9. Grit — sand balance

**Lead: Gigalith.** Sand Stream with immediate offensive presence rather than
Hippowdon's passivity, and Explosion as a parting shot.

```
Gigalith @ Smooth Rock
Ability: Sand Stream
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Stone Edge
- Earthquake
- Stealth Rock
- Explosion

Krookodile @ Black Glasses
Ability: Moxie
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Knock Off
- Stone Edge
- Superpower

Lycanroc @ Hard Stone
Ability: Sand Rush
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Stone Edge
- Accelerock
- Crunch
- Swords Dance

Magnezone @ Magnet
Ability: Magnet Pull
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Thunderbolt
- Flash Cannon
- Volt Switch
- Body Press

Flygon @ Soft Sand
Ability: Levitate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Dragon Claw
- U-turn
- Fire Punch

Porygon2 @ Eviolite
Ability: Trace
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Tri Attack
- Ice Beam
- Thunderbolt
- Recover
```

---

## Group D — Snow & Terrain

### D10. Whiteout — snow

**Lead: Abomasnow.** Snow Warning on entry, then Aurora Veil halves incoming
damage for five turns. The hardest opening in the building to break.

```
Abomasnow @ Icy Rock
Ability: Snow Warning
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Blizzard
- Wood Hammer
- Ice Shard
- Aurora Veil

Ninetales-Alola @ Never-Melt Ice
Ability: Snow Warning
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Blizzard
- Moonblast
- Aurora Veil
- Freeze-Dry

Beartic @ Sitrus Berry
Ability: Slush Rush
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Icicle Crash
- Superpower
- Aqua Jet
- Swords Dance

Arctozolt @ Magnet
Ability: Slush Rush
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Bolt Beak
- Icicle Crash
- Low Kick
- Substitute

Mamoswine @ Soft Sand
Ability: Thick Fat
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Icicle Crash
- Ice Shard
- Stealth Rock

Froslass @ Spell Tag
Ability: Cursed Body
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Shadow Ball
- Ice Beam
- Destiny Bond
- Spikes
```

### D11. Overgrowth — Grassy Terrain

**Lead: Rillaboom.** Grassy Surge makes Grassy Glide a priority move, which is
the single nastiest thing available at this tier. Everything else heals on the
terrain while the player doesn't.

```
Rillaboom @ Miracle Seed
Ability: Grassy Surge
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Grassy Glide
- Knock Off
- Swords Dance
- U-turn

Tangrowth @ Leftovers
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpA
Relaxed Nature
- Giga Drain
- Knock Off
- Sleep Powder
- Synthesis

Appletun @ Sitrus Berry
Ability: Thick Fat
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Apple Acid
- Dragon Pulse
- Recover
- Leech Seed

Gligar @ Eviolite
Ability: Immunity
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Earthquake
- Knock Off
- Roost
- Stealth Rock

Sylveon @ Silk Scarf
Ability: Pixilate
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hyper Voice
- Calm Mind
- Psyshock
- Wish

Heracross @ Black Belt
Ability: Guts
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Close Combat
- Megahorn
- Rock Blast
- Swords Dance
```

### D12. Static Field — Electric Terrain

**Lead: Pincurchin.** Electric Surge doubles Rising Voltage's power and blocks
sleep outright, which shuts off every Spore and Sleep Powder in the building.

```
Pincurchin @ Magnet
Ability: Electric Surge
EVs: 252 HP / 252 SpA / 4 Def
Quiet Nature
- Rising Voltage
- Sucker Punch
- Spikes
- Recover

Raichu-Alola @ Twisted Spoon
Ability: Surge Surfer
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Thunderbolt
- Psychic
- Nasty Plot
- Focus Blast

Toxtricity @ Black Glasses
Ability: Punk Rock
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Overdrive
- Sludge Wave
- Boomburst
- Volt Switch

Magnezone @ Metal Coat
Ability: Magnet Pull
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Thunderbolt
- Flash Cannon
- Volt Switch
- Body Press

Electivire @ Sitrus Berry
Ability: Motor Drive
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Wild Charge
- Ice Punch
- Earthquake
- Cross Chop

Rotom-Wash @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hydro Pump
- Thunderbolt
- Volt Switch
- Will-O-Wisp
```

---

## Boss — Dunewarden Kasra

**Pool:** building 4 (≤599) plus everything prior.

**Gimmick:** eight-turn sand, Excadrill sweeping at doubled Speed under it, and
**four held items the player cannot buy yet.** Life Orb, Heavy-Duty Boots,
Focus Sash and Assault Vest all unlock at building 4. That's the power gap —
not bigger Pokémon, better equipment. Every set here is fully optimized; the
boss is not handicapped in any way.

**AI:** omniscient, proactive switching, no ace flag.

```
Hippowdon @ Smooth Rock
Ability: Sand Stream
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Earthquake
- Stealth Rock
- Slack Off
- Whirlwind

Excadrill @ Life Orb
Ability: Sand Rush
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Earthquake
- Iron Head
- Rock Slide
- Swords Dance

Arcanine @ Heavy-Duty Boots
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Flare Blitz
- Extreme Speed
- Wild Charge
- Morning Sun

Kingambit @ Leftovers
Ability: Supreme Overlord
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Sucker Punch
- Iron Head
- Kowtow Cleave
- Swords Dance

Tangrowth @ Assault Vest
Ability: Regenerator
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Power Whip
- Knock Off
- Earthquake
- Giga Drain

Gholdengo @ Focus Sash
Ability: Good as Gold
EVs: 252 SpA / 4 Def / 252 Spe
Timid Nature
- Make It Rain
- Shadow Ball
- Nasty Plot
- Thunder Wave
```

### The strategic dependency

A boss should have a dependency the player can attack, not a handicap that
weakens it. Kasra is fully optimized — every set here is one a competitive
player would actually run. What it has instead is a **load-bearing condition**:

**The team is built on sand.** Excadrill without Sand Rush is a 88-base-Speed
Pokémon instead of a 176 one, and the sand chip that grinds down the player's
team stops. Hippowdon is the linchpin, and Smooth Rock makes its weather last
eight turns rather than five.

That's not a weakness in the sense of being weaker — it's a pressure point. The
player who identifies it wins; the player who tries to out-damage a Life Orb
Excadrill under sand does not.

### Counterplay available at tier 3

- **Your own weather setter.** Pelipper, Politoed, Ninetales, Abomasnow —
  all cheap, all available, all switch Excadrill off
- **Levitate or Flying** blanks Excadrill's Earthquake. Rotom-Wash, Skarmory,
  Flygon, Mandibuzz
- **Rain** halves Arcanine's Flare Blitz and Torkoal-style Fire pressure
- **Whirlwind or Roar** phazes a Swords-Danced Excadrill out
- **Safety Goggles** ignores sand chip entirely
- **Multi-hit moves** break Gholdengo's Focus Sash
- **Fighting or Ground coverage** for Kingambit, whose Sucker Punch fails
  against status moves

---

## Benchmark counter-team

Built only from building 3's pool, items and bans. Item clause compliant.

```
Pelipper @ Damp Rock
Ability: Drizzle
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Scald
- Hurricane
- U-turn
- Roost

Rotom-Wash @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Hydro Pump
- Thunder
- Volt Switch
- Will-O-Wisp

Skarmory @ Sitrus Berry
Ability: Sturdy
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Brave Bird
- Spikes
- Roost
- Whirlwind

Ferrothorn @ Metal Coat
Ability: Iron Barbs
EVs: 252 HP / 252 Def / 4 SpD
Relaxed Nature
- Gyro Ball
- Power Whip
- Stealth Rock
- Leech Seed

Toxapex @ Passho Berry
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Scald
- Toxic
- Recover
- Haze

Kingdra @ Mystic Water
Ability: Swift Swim
EVs: 252 SpA / 4 Def / 252 Spe
Modest Nature
- Hydro Pump
- Draco Meteor
- Ice Beam
- Rain Dance
```

**Game plan.** Lead Pelipper and overwrite the sand immediately — that single
switch turns off Excadrill's Sand Rush, halves Arcanine's Fire damage, and
makes Kingdra the fastest thing on the field. Rotom-Wash and Skarmory both
blank Excadrill's Earthquake, so even if the weather war is lost the sweeper
has no clean target. Whirlwind phazes anything that sets up. Kingdra closes
under Swift Swim.

**The lesson:** the answer to a weather team isn't resisting its damage, it's
taking the weather away.

---

## Open for playtesting

1. **Chansey with Eviolite.** Flagged above. Likely to be the most
   frustrating thing in the building. If games drag, delay Eviolite to
   building 4.
2. **Aurora Veil in D10.** Halving all damage for five turns on top of snow is
   a strong opening. Watch whether it's a fight or a wall.
3. **Weather wars generally.** With four groups all running setters, a player
   who buys their own setter may find the whole building trivial — every team's
   gimmick switches off. That might be the correct lesson, or it might make six
   of twelve matchups identical. This is the single biggest unknown here.
4. **Grassy Glide priority.** Rillaboom's priority Grass STAB is genuinely
   strong at this tier. Watch it.
