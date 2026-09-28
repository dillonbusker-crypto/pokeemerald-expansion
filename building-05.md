# Building 5 — "The Main Event"

**Battle Dome.** Singles, 6v6, level 50. BST cap 600. Six battles drawn from
twelve, then the boss.

**Design intent:** teach the one-shot decision. Mega Evolution arrives here, and
a Mega is the most powerful thing on a team that can only happen once per
battle. Every CPU team has exactly one, and the building's lesson is choosing
*which* of yours to Mega Evolve, *when*, and how to play around the opponent's
before it lands. Choice items arrive alongside it — the other "commit now, live
with it" mechanic — so the whole building is about commitment.

**Structural conceit:** four groups of three. Every team carries one Mega, and
the group decides what that Mega is *for*.

| Group | Teams | Plan | What it punishes |
|---|---|---|---|
| A | 1–3 | Mega offense | No priority, no Choice Scarf, passive play |
| B | 4–6 | Setup sweepers | No phazing, no Haze, no Unaware, no Encore |
| C | 7–9 | Choice pressure & pivoting | Predictable switching, staying in on bad matchups |
| D | 10–12 | Hazards & attrition | No hazard removal, no Heavy-Duty Boots, no wallbreaker |

**Why the Dome.** Buildings 1–4 used the Battle Tower's four counters, so the
Tower is finished. The Dome is the Frontier's arena, with an audience and a
spotlight, which suits the building where Pokémon first transform mid-battle.
It's also first in the unlock-bit order (`FACILITY_DOOR_DOME`), and its lobby
already has the locked-door check waiting for that bit. Vanilla Dome tournament
rules (brackets, 3v3, team preview) are **not** used. The Dome is only the
location, and the Ten Buildings run loop runs there unchanged.

**AI:** same as buildings 3 and 4 for pool trainers — full offensive
intelligence, smart replacement choice, proactive switching, not omniscient.
Mega Evolution is automatic for any CPU Pokémon holding its stone.

---

## Unlock ceremony — end of building 4

When Timewarden Iyla falls, the building 4 attendant does three things:

1. **Gives the player the Mega Ring** (`ITEM_MEGA_RING`, a key item). Without
   it the player can't Mega Evolve at all: `CanMegaEvolve()` in
   `src/battle_util.c` refuses for the player's side unless the ring is in the
   bag. The CPU needs no ring. The Frontier battle flag only blocks *using*
   bag items in battle, not owning them, so the ring works during runs.
2. **Points to the Exchange Service Corner:** the Mega Stone counter (Keeper 3)
   is open now.
3. **Points to the Battle Dome:** building 5 is there, and its doors are open.

Draft dialogue:

> Congratulations, you've cleared the Turn Order!
>
> You've earned this: a MEGA RING. With it, a POKéMON holding its MEGA STONE
> can Mega Evolve in battle — once per battle, so choose well.
>
> The MEGA STONE counter at the Exchange Service Corner is open now.
>
> And your next challenge is waiting at the BATTLE DOME. Its doors are open
> to you.

---

## Bans

Permanent list applies: Smeargle, Wobbuffet, Shedinja, Ditto, Wishiwashi,
Palafin.

**The Palafin rule, restated for this tier:** anything that changes form
mid-battle to escape the cap stays out. Mega Evolution is the one sanctioned
exception, and only for Megas at or below 600 *after* evolving. Also out:
Zygarde (Power Construct), Greninja-Bond, Hoopa-Unbound (the Prison Bottle
isn't sold, so Hoopa stays Confined), and Diancie's and Latios's stones
(their Megas are 700).

**Blaziken remains Blaze-only.** Blazikenite isn't sold either — Mega Blaziken
is 630.

**Which Megas are sold.** Gen 6 Megas, plus the *Legends: Z-A* Megas that
play best in singles. All are at or under 600 after evolving.

- **Doubles-leaning Megas are held for building 6:** Mega Camerupt, plus the
  Z-A Scrafty, Golurk, Crabominable, Scovillain, Tatsugiri, Chimecho, Meowstic,
  Drampa and Raichu X. Building 6 is doubles, and the design doc already gives
  it a limited Mega pool.
- **Cut entirely, as outclassed:**
  - Mega Audino — Mega Clefable does its job better.
  - Mega Banette — Mega Absol Z is the better physical Ghost.
  - Mega Glalie — Mega Altaria and Mega Froslass do its jobs better.
  - Mega Scolipede — Mega Evolving drops its Speed from 112 to 62.
  - Mega Falinks — five better Fighting Megas are already sold.

**Mega Gengar and Mega Kangaskhan are held until building 7.** Both were
banned to Ubers in Gen 6: Shadow Tag traps the player's switch-ins, and
Parental Bond makes every attack hit twice. Their stones aren't sold here.

---

## Pool additions

Everything prior stays purchasable. Three sources of new Pokémon.

### 1. The 600-BST non-legendaries

Garchomp, Dragapult, Dragonite, Tyranitar, Metagross, Salamence, Hydreigon,
Baxcalibur, Kommo-o, Archaludon, Goodra, Goodra-Hisui.

That's the eleven pseudo-legendaries plus **Archaludon**, which is 600 and
non-legendary and was missing from the earlier "eleven" count.

### 2. Singles-relevant Paradox, Ultra Beasts and Mythicals

The ones that matter in singles **and aren't Ubers-grade** there.

| Group | Pokémon |
|---|---|
| Paradox | Great Tusk, Iron Valiant, Iron Treads, Iron Moth, Iron Boulder, Iron Crown, Iron Leaves, Raging Bolt, Slither Wing, Sandy Shocks, Scream Tail, Brute Bonnet, Iron Thorns |
| Ultra Beasts | Buzzwole, Celesteela, Blacephalon, Nihilego, Xurkitree, Guzzlord |
| Mythicals | Mew, Jirachi, Celebi, Victini, Keldeo, Meloetta, Volcanion, Zeraora, Melmetal, Zarude, Manaphy, Pecharunt, Shaymin (Land), Deoxys-Defense, Hoopa (Confined) |

**Booster Energy is still not sold** (building 7, per the design doc). Paradox
abilities only switch on under sun or Electric Terrain, which rewards what
building 3 taught.

**Held for building 6 (doubles-focused):** Iron Hands, Iron Jugulis, Stakataka.

**Held for building 7+ (Ubers-grade in singles):** Flutter Mane, Roaring Moon,
Walking Wake, Gouging Fire, Iron Bundle, Kartana, Pheromosa, Naganadel,
Darkrai, Deoxys (Normal / Attack / Speed), Shaymin-Sky, Magearna, Marshadow,
Genesect.

Not covered by this pass: the sub-legendaries held back at building 4
(Tornadus, the Tapus, the Ruin quartet, the Loyal Three, Cresselia and the
rest), plus the 600-BST sub-legendaries (Heatran, Latios, Latias, Landorus).
They're neither Paradox, Ultra Beast nor Mythical. Building 6 or 7 is their
natural home.

### 3. Mega bases

Every Mega sold at this building (see Bans) needs its base Pokémon, and **nine
of them aren't sold yet.** Those arrive now, priced for what they are without
a stone — the stone carries the premium.

Pidgeot, Sharpedo, Altaria, Absol, Lopunny, Raichu, Staraptor, Malamar,
Dragalge.

**Clefable** also arrives here as a regular Pokémon. It's never been sold, and
building 5's CPU teams and boss use it.

---

## Shop — building 5 additions

**Tier prices:** Standard 550 · Strong 700 · Premium 850 (the design doc's
550–850 band for buildings 5–6).

### Keeper 2 — Held items

| Item | FP | Why it matters here |
|---|---|---|
| Choice Scarf | 450 | +50% Speed, locked into one move. The singles speed-control item |
| Choice Band | 400 | +50% Attack, locked into one move |
| Choice Specs | 400 | +50% Sp. Attack, locked into one move |
| Weakness Policy | 350 | +2 Atk and Sp. Atk when hit super-effectively. Setup without a setup turn |
| Rocky Helmet | 300 | Contact attackers lose 1/6 HP. Pairs with Rough Skin and Iron Barbs |
| Mental Herb | 200 | Cures Taunt, Encore, Torment, Disable and Heal Block once |

**Choice Scarf is the signature purchase.** It's the singles answer to every
fast Mega in the building, and the benchmark counter-team depends on it.

**Clear Amulet moves to building 6.** `shop-spec.md` had it here and the
design doc at building 6. Its main job is blanking Intimidate, which is a
doubles problem, so building 6 is where it teaches something.

### Keeper 3 — Mega Stones (opens now)

Priced by what the Mega does, not its BST. Buying a Mega means buying the base
*and* the stone, so a Premium Mega's real cost is about 1,000–1,450 FP.

**Premium — 600 FP**

| Stone | Mega | Why |
|---|---|---|
| Alakazite | Alakazam (600) | 175 SpA, 150 Speed, Trace |
| Scizorite | Scizor (600) | Technician Bullet Punch, excellent bulk |
| Heracronite | Heracross (600) | 185 Atk, Skill Link Rock Blast / Pin Missile |
| Pinsirite | Pinsir (600) | Aerilate Return, Swords Dance |
| Mawilite | Mawile (480) | Huge Power; the BST badly understates it |
| Medichamite | Medicham (510) | Pure Power; same story |
| Altarianite | Altaria (590) | Pixilate Dragon Dance sweeper |
| Lopunnite | Lopunny (580) | Scrappy Fake Out, 135 Speed |
| Sablenite | Sableye (480) | Magic Bounce wall; the BST understates it |
| Clefablite | Clefable (583) | Magic Bounce plus 135 SpA Calm Mind; becomes Fairy/Flying |
| Hawluchanite | Hawlucha (600) | No Guard: High Jump Kick and Stone Edge never miss |
| Raichunite Y | Raichu (585) | No Guard Thunder and Focus Blast at 160 SpA, 130 Speed |
| Absolite Z | Absol (565) | Sharpness slicing moves, 154 Atk, 151 Speed, Dark/Ghost |
| Staraptite | Staraptor (585) | Contrary Close Combat raises its defenses; becomes Fighting/Flying |

**Strong — 450 FP**

| Stone | Mega | Why |
|---|---|---|
| Manectite | Manectric (575) | Intimidate pivot, 135 Speed |
| Slowbronite | Slowbro (590) | 180 Def, Iron Defense / Calm Mind wall |
| Houndoominite | Houndoom (600) | Nasty Plot, 140 SpA |
| Sharpedonite | Sharpedo (560) | Strong Jaw, 140 Atk |
| Pidgeotite | Pidgeot (579) | No Guard Hurricane |
| Absolite | Absol (565) | Magic Bounce, 150 Atk |
| Abomasite | Abomasnow (594) | Snow setter with 132/132 mixed offense |
| Barbaracite | Barbaracle (600) | Shell Smash with Tough Claws; becomes Rock/Fighting |
| Malamarite | Malamar (582) | Contrary Superpower raises its Attack and Defense |
| Skarmorite | Skarmory (565) | 140 Atk Swords Dance attacker that keeps Spikes and Whirlwind |
| Froslassite | Froslass (580) | Sets its own snow; never-miss Blizzard, 120 Speed |
| Dragalgite | Dragalge (594) | 163 SpD Regenerator pivot |

**Standard — 300 FP**

| Stone | Mega | Why |
|---|---|---|
| Beedrillite | Beedrill (495) | Adaptability, 145 Speed. Frail, but fast |
| Victreebelite | Victreebel (590) | Strength Sap, mixed offense, Innards Out |

That's 28 stones. Gengar and Kangaskhan are held until building 7, and ten
doubles-leaning Megas until building 6 (see Bans).

**Z-A Megas have no Smogon history.** Their tiers come from stats, abilities
and movepools. Expect to move some after playtesting.

### Keeper 4 — Pokémon

| Tier | Pokémon |
|---|---|
| Premium 850 | Garchomp, Dragapult, Dragonite, Tyranitar, Metagross, Great Tusk, Iron Valiant, Iron Treads, Iron Moth, Raging Bolt, Iron Boulder, Iron Crown, Keldeo, Volcanion, Pecharunt, Mew, Jirachi, Celesteela, Blacephalon, Buzzwole |
| Strong 700 | Salamence, Hydreigon, Baxcalibur, Archaludon, Kommo-o, Iron Leaves, Slither Wing, Sandy Shocks, Nihilego, Xurkitree, Victini, Celebi, Meloetta, Zeraora, Melmetal, Zarude, Manaphy, Deoxys-Defense, Shaymin, Hoopa |
| Standard 550 | Goodra, Goodra-Hisui, Scream Tail, Brute Bonnet, Iron Thorns, Guzzlord |
| Mega bases 375 | Lopunny, Altaria, Absol, Clefable, Staraptor, Raichu |
| Mega bases 250 | Pidgeot, Sharpedo, Malamar, Dragalge |

**Ability overrides** (the shop otherwise sells slot 0):

- **Garchomp:** Rough Skin, not Sand Veil.
- **Dragonite:** Multiscale, not Inner Focus.

---

## Group A — Mega offense

The Mega *is* the win condition. Each team clears a path and brings it in.

### A1. Headliner — Mega Lopunny

**Lead: Garchomp** sets Stealth Rock behind Focus Sash, then everything else
is fast. Lopunny's Scrappy Fake Out and Return hit Ghosts, so there's no safe
switch-in to its STAB.

```
Garchomp @ Focus Sash
Ability: Rough Skin
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Stealth Rock
- Earthquake
- Scale Shot
- Swords Dance

Lopunny @ Lopunnite
Ability: Limber
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Fake Out
- High Jump Kick
- Return
- Ice Punch

Dragapult @ Life Orb
Ability: Infiltrator
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Shadow Ball
- Flamethrower
- U-turn

Iron Moth @ Heavy-Duty Boots
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Fiery Dance
- Sludge Wave
- Dazzling Gleam
- Energy Ball

Weavile @ Muscle Band
Ability: Pressure
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Triple Axel
- Knock Off
- Ice Shard
- Swords Dance

Zeraora @ Expert Belt
Ability: Volt Absorb
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Plasma Fists
- Close Combat
- Knock Off
- Volt Switch
```

### A2. Spotlight — Mega Alakazam

Special hyper offense. Nothing on this team wants to be touched, and nothing
on it has to be — Alakazam at 150 Speed and Xurkitree behind a Sash both end
games fast.

```
Alakazam @ Alakazite
Ability: Magic Guard
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Psyshock
- Focus Blast
- Shadow Ball
- Nasty Plot

Hydreigon @ Life Orb
Ability: Levitate
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Dark Pulse
- Flamethrower
- U-turn

Raging Bolt @ Leftovers
Ability: Protosynthesis
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Thunderclap
- Draco Meteor
- Thunderbolt
- Calm Mind

Volcanion @ Heavy-Duty Boots
Ability: Water Absorb
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Steam Eruption
- Flamethrower
- Earth Power
- Sludge Bomb

Iron Crown @ Expert Belt
Ability: Quark Drive
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Tachyon Cutter
- Psyshock
- Focus Blast
- Volt Switch

Xurkitree @ Focus Sash
Ability: Beast Boost
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Tail Glow
- Thunderbolt
- Energy Ball
- Dazzling Gleam
```

### A3. Quickdraw — Mega Medicham and priority

Every member has priority or a way to fake it. The team punishes a player
who thinks a faster Pokémon is a safe answer.

```
Medicham @ Medichamite
Ability: Pure Power
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- High Jump Kick
- Zen Headbutt
- Ice Punch
- Bullet Punch

Kingambit @ Black Glasses
Ability: Supreme Overlord
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Sucker Punch
- Kowtow Cleave
- Iron Head
- Swords Dance

Azumarill @ Sitrus Berry
Ability: Huge Power
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Belly Drum
- Aqua Jet
- Play Rough
- Knock Off

Dragonite @ Weakness Policy
Ability: Multiscale
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Extreme Speed
- Earthquake
- Fire Punch

Mamoswine @ Never-Melt Ice
Ability: Thick Fat
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Icicle Crash
- Earthquake
- Ice Shard
- Stealth Rock

Lucario @ Life Orb
Ability: Inner Focus
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Close Combat
- Meteor Mash
- Extreme Speed
```

---

## Group B — Setup sweepers

One free turn is the whole game. Every team has at least three Pokémon that
win from +1 or +2, and a Mega that does it best.

### B4. Ascension — Dragon Dance

**Mega Altaria** is the headline: Pixilate Return off a Dragon Dance. Behind it,
four more Dragon Dance or Clangorous Soul users. A player without phazing,
Haze, Unaware or priority faces the same problem six times.

```
Altaria @ Altarianite
Ability: Natural Cure
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Return
- Earthquake
- Roost

Salamence @ Heavy-Duty Boots
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Dual Wingbeat
- Earthquake
- Roost

Tyranitar @ Weakness Policy
Ability: Sand Stream
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Stone Edge
- Crunch
- Earthquake

Baxcalibur @ Never-Melt Ice
Ability: Thermal Exchange
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Icicle Crash
- Glaive Rush
- Earthquake

Gyarados @ Leftovers
Ability: Moxie
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Dragon Dance
- Waterfall
- Earthquake
- Taunt

Kommo-o @ Sitrus Berry
Ability: Bulletproof
EVs: 252 HP / 252 SpA / 4 Spe
Modest Nature
- Clangorous Soul
- Clanging Scales
- Aura Sphere
- Flamethrower
```

### B5. Crescendo — special setup

**Mega Clefable's** Magic Bounce bounces back the Taunt or Toxic a player would
use to stop it. Behind it, every special setup move in the building: Nasty
Plot, Quiver Dance, Calm Mind, and Contrary Leaf Storm.

```
Clefable @ Clefablite
Ability: Magic Guard
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Calm Mind
- Moonblast
- Fire Blast
- Moonlight

Hydreigon @ Life Orb
Ability: Levitate
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Nasty Plot
- Draco Meteor
- Dark Pulse
- Flamethrower

Volcarona @ Heavy-Duty Boots
Ability: Flame Body
EVs: 252 HP / 252 SpA / 4 Spe
Modest Nature
- Quiver Dance
- Fiery Dance
- Giga Drain
- Morning Sun

Raging Bolt @ Leftovers
Ability: Protosynthesis
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Calm Mind
- Thunderclap
- Draco Meteor
- Thunderbolt

Keldeo @ Expert Belt
Ability: Justified
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Calm Mind
- Secret Sword
- Scald
- Air Slash

Serperior @ Miracle Seed
Ability: Contrary
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Leaf Storm
- Glare
- Dragon Pulse
- Synthesis
```

### B6. Bulwark — defensive setup

The slow version: Iron Defense, Bulk Up and Salt Cure. **Mega Slowbro** is 180
base Defense before it boosts. Mental Herb makes its answer — Taunt — fail
once on Garganacl.

```
Slowbro @ Slowbronite
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Iron Defense
- Body Press
- Scald
- Slack Off

Corviknight @ Leftovers
Ability: Pressure
EVs: 252 HP / 4 Def / 252 SpD
Careful Nature
- Bulk Up
- Body Press
- Brave Bird
- Roost

Buzzwole @ Rocky Helmet
Ability: Beast Boost
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Bulk Up
- Drain Punch
- Ice Punch
- Roost

Archaludon @ Weakness Policy
Ability: Stamina
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Iron Defense
- Body Press
- Flash Cannon
- Dragon Pulse

Celesteela @ Sitrus Berry
Ability: Beast Boost
EVs: 252 HP / 4 Def / 252 SpD
Careful Nature
- Leech Seed
- Heavy Slam
- Protect
- Flamethrower

Garganacl @ Mental Herb
Ability: Purifying Salt
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Salt Cure
- Iron Defense
- Body Press
- Recover
```

---

## Group C — Choice pressure & pivoting

Choice items arrive this building and these teams are built around them. The
lesson runs in both directions: punish a locked opponent, and don't get locked
into the wrong move yourself.

### C7. Locked In — the Choice trio

Scarf Garchomp, Band Dragonite and Specs Hydreigon, with **Mega Manectric**
pivoting between them on Volt Switch. The switch-ins it's fishing for are the
player's own.

```
Garchomp @ Choice Scarf
Ability: Rough Skin
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Earthquake
- Outrage
- Stone Edge
- Fire Fang

Dragonite @ Choice Band
Ability: Multiscale
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Extreme Speed
- Outrage
- Earthquake
- Fire Punch

Hydreigon @ Choice Specs
Ability: Levitate
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Dark Pulse
- Flash Cannon
- U-turn

Manectric @ Manectite
Ability: Lightning Rod
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Volt Switch
- Thunderbolt
- Overheat
- Snarl

Rotom-Wash @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Hydro Pump
- Volt Switch
- Will-O-Wisp
- Pain Split

Tyranitar @ Chople Berry
Ability: Sand Stream
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Stone Edge
- Crunch
- Thunder Wave
```

### C8. Momentum — U-turn and Volt Switch

**Mega Scizor** is the pivot. Six Pokémon, five pivoting moves: the player is
always facing the Pokémon the AI wanted in.

```
Scizor @ Scizorite
Ability: Technician
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Bullet Punch
- U-turn
- Knock Off
- Roost

Dragapult @ Choice Specs
Ability: Infiltrator
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Shadow Ball
- Flamethrower
- U-turn

Zeraora @ Choice Band
Ability: Volt Absorb
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Plasma Fists
- Close Combat
- Knock Off
- Volt Switch

Rotom-Wash @ Leftovers
Ability: Levitate
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Volt Switch
- Hydro Pump
- Will-O-Wisp
- Pain Split

Corviknight @ Rocky Helmet
Ability: Pressure
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Brave Bird
- U-turn
- Roost
- Defog

Metagross @ Choice Scarf
Ability: Clear Body
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Meteor Mash
- Zen Headbutt
- Earthquake
- Trick
```

### C9. Sleight of Hand — Trick

Trick and Switcheroo turn a Choice item into a weapon: a Choice Scarf on the
player's wall means it's locked into Recover. **Mega Absol's** Magic Bounce
reflects hazards and status while the rest work.

```
Absol @ Absolite
Ability: Justified
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Knock Off
- Sucker Punch
- Play Rough

Jirachi @ Choice Scarf
Ability: Serene Grace
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Iron Head
- U-turn
- Trick
- Healing Wish

Hoopa @ Choice Specs
Ability: Magician
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Psyshock
- Shadow Ball
- Focus Blast
- Trick

Victini @ Choice Band
Ability: Victory Star
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- V-create
- Zen Headbutt
- U-turn
- Trick

Iron Treads @ Leftovers
Ability: Quark Drive
EVs: 252 HP / 4 Atk / 252 Spe
Jolly Nature
- Stealth Rock
- Rapid Spin
- Earthquake
- Iron Head

Pecharunt @ Rocky Helmet
Ability: Poison Puppeteer
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Malignant Chain
- Shadow Ball
- Parting Shot
- Recover
```

---

## Group D — Hazards & attrition

The slow teams. Each wins by chip, not by knockouts, and each has a Mega that
makes the chip hard to stop.

### D10. Minefield — hazard stack

Stealth Rock, Spikes and Toxic Spikes, with Whirlwind to force switches into
them. **Mega Skarmory** sets Spikes and phazes, and hits with 140 Attack when
it has to.
A player with no removal and no Heavy-Duty Boots loses a quarter of each
Pokémon's HP just switching in.

```
Skarmory @ Skarmorite
Ability: Sturdy
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Spikes
- Brave Bird
- Roost
- Whirlwind

Garchomp @ Rocky Helmet
Ability: Rough Skin
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Stealth Rock
- Earthquake
- Dragon Tail
- Fire Blast

Glimmora @ Focus Sash
Ability: Toxic Debris
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Mortal Spin
- Power Gem
- Earth Power
- Sludge Wave

Hippowdon @ Leftovers
Ability: Sand Stream
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Earthquake
- Slack Off
- Whirlwind
- Stone Edge

Toxapex @ Black Sludge
Ability: Regenerator
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Toxic Spikes
- Scald
- Recover
- Haze

Mandibuzz @ Heavy-Duty Boots
Ability: Overcoat
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Foul Play
- Roost
- U-turn
- Toxic
```

### D11. Iron Wall — stall

**Mega Sableye** bounces back Toxic, Will-O-Wisp, Taunt and hazards alike. The
rest recover every hit. A player without a wallbreaker or setup sweeper runs
out of PP before this team runs out of HP.

```
Sableye @ Sablenite
Ability: Prankster
EVs: 252 HP / 4 Def / 252 SpD
Careful Nature
- Will-O-Wisp
- Knock Off
- Recover
- Foul Play

Clefable @ Leftovers
Ability: Magic Guard
EVs: 252 HP / 252 Def / 4 SpD
Bold Nature
- Moonblast
- Soft-Boiled
- Stealth Rock
- Knock Off

Corviknight @ Rocky Helmet
Ability: Pressure
EVs: 252 HP / 252 Def / 4 SpD
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
- Toxic
- Recover
- Haze

Clodsire @ Sitrus Berry
Ability: Unaware
EVs: 252 HP / 4 Def / 252 SpD
Careful Nature
- Earthquake
- Toxic
- Recover
- Stealth Rock

Pecharunt @ Heavy-Duty Boots
Ability: Poison Puppeteer
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Malignant Chain
- Parting Shot
- Recover
- Shadow Ball
```

### D12. Pressure Point — balance

Hazards up, hazards off, a spinblocker, and **Mega Heracross** to punish the
player for playing slowly back. The most "normal" team in the building, and
the one closest to what a real singles team looks like.

```
Heracross @ Heracronite
Ability: Guts
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Pin Missile
- Rock Blast
- Close Combat
- Swords Dance

Great Tusk @ Rocky Helmet
Ability: Protosynthesis
EVs: 252 HP / 4 Atk / 252 Spe
Jolly Nature
- Rapid Spin
- Headlong Rush
- Ice Spinner
- Knock Off

Tyranitar @ Leftovers
Ability: Sand Stream
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Knock Off
- Stone Edge
- Thunder Wave

Gholdengo @ Expert Belt
Ability: Good as Gold
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Make It Rain
- Shadow Ball
- Nasty Plot
- Recover

Zapdos @ Heavy-Duty Boots
Ability: Static
EVs: 252 HP / 252 Def / 4 SpA
Bold Nature
- Volt Switch
- Hurricane
- Heat Wave
- Roost

Slowking @ Sitrus Berry
Ability: Regenerator
EVs: 252 HP / 252 SpD / 4 Def
Calm Nature
- Scald
- Future Sight
- Slack Off
- Chilly Reception
```

---

## Boss — Crownwarden Solen

**Pool:** building 6 (≤600, limited Megas) plus everything prior, and one Mega
the player can never own.

**Gimmick:** **Mega Salamence** (700 BST — well above the cap). Aerilate
Double-Edge off a Dragon Dance. Everything else on the team exists to get it
one clean turn. That's the power gap: a Mega the player can't buy, plus
**Booster Energy** on Great Tusk, which the player can't buy until building 7.
Every set is fully optimized.

**AI:** omniscient, proactive switching. **No ace flag** — the same call made
for Helis: forcing Salamence to wait until it's the last Pokémon left would
hand the player free turns to prepare for it. The AI brings it in when the
path is clear.

```
Tyranitar @ Leftovers
Ability: Sand Stream
EVs: 252 HP / 4 Atk / 252 SpD
Careful Nature
- Stealth Rock
- Knock Off
- Stone Edge
- Thunder Wave

Great Tusk @ Booster Energy
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Rapid Spin
- Headlong Rush
- Close Combat
- Ice Spinner

Dragapult @ Choice Specs
Ability: Infiltrator
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Draco Meteor
- Shadow Ball
- Flamethrower
- U-turn

Clefable @ Life Orb
Ability: Magic Guard
EVs: 252 HP / 252 SpA / 4 Def
Modest Nature
- Calm Mind
- Moonblast
- Fire Blast
- Soft-Boiled

Corviknight @ Rocky Helmet
Ability: Pressure
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Brave Bird
- Body Press
- U-turn
- Roost

Salamence @ Salamencite
Ability: Intimidate
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Double-Edge
- Earthquake
- Roost
```

### The strategic dependency

**The team is built to land one Dragon Dance.** Tyranitar sets rocks and
cripples a check with Thunder Wave. Great Tusk spins away the player's
hazards and threatens the Steel and Ice types that would stop a Salamence.
Dragapult and Clefable force switches, and Corviknight's U-turn brings
Salamence in safely.

Mega Salamence at +1 is the fastest and strongest thing in the building.
At +0 it's merely very good.

**Adamant, not Jolly, is deliberate — and it's the crack.** At +1 an Adamant
Mega Salamence is just slower than a **Jolly Choice Scarf Garchomp**, a
Pokémon and item the player can buy this building. That's the intended
answer, sitting in the same shop that just unlocked. A fully optimized boss
could run Jolly; this one leaves one door open on purpose, the same way
Kasra's team depended on sand.

### Counterplay available at tier 5

- **Jolly Choice Scarf Garchomp** outspeeds +1 Adamant Mega Salamence.
  Stone Edge or Outrage
- **Ice priority:** Weavile's Ice Shard, Mamoswine's Ice Shard
- **Unaware** ignores the boosts: Clodsire, Dondozo
- **Phazing and Haze:** Skarmory's Whirlwind, Toxapex's Haze, Hippowdon's
  Whirlwind
- **Encore** locks it into Dragon Dance: Whimsicott, Grimmsnarl
- **Intimidate** undoes the boost: Incineroar, Arcanine, Salamence
- **Fairy and Steel** resist its Dragon moves; **Rocky Helmet** punishes
  Double-Edge contact on top of its recoil
- **Your own Mega Scizor or Mega Mawile** to handle Clefable and Tyranitar

---

## Benchmark counter-team

Built only from building 5's pool, items and bans. Item clause compliant. One
Mega.

```
Garchomp @ Choice Scarf
Ability: Rough Skin
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Earthquake
- Outrage
- Stone Edge
- Fire Fang

Weavile @ Focus Sash
Ability: Pressure
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Triple Axel
- Ice Shard
- Knock Off
- Swords Dance

Clodsire @ Black Sludge
Ability: Unaware
EVs: 252 HP / 4 Def / 252 SpD
Careful Nature
- Earthquake
- Toxic
- Recover
- Stealth Rock

Scizor @ Scizorite
Ability: Technician
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Bullet Punch
- U-turn
- Knock Off
- Swords Dance

Skarmory @ Rocky Helmet
Ability: Sturdy
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Brave Bird
- Spikes
- Roost
- Whirlwind

Great Tusk @ Leftovers
Ability: Protosynthesis
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Headlong Rush
- Close Combat
- Rapid Spin
- Ice Spinner
```

**Game plan.** Skarmory and Clodsire make Salamence's setup worthless: one
phazes it, the other ignores the boost. Great Tusk spins off Tyranitar's rocks
and hits Salamence with Ice Spinner on the way in. Mega Scizor's Bullet Punch
handles Clefable, and U-turn keeps the player on the right side of
Dragapult's Choice lock. If Salamence does get its +1, the Scarf Garchomp
outspeeds it and Weavile's Ice Shard finishes it through Multiscale-free
damage.

**The lesson:** a setup sweeper is only as good as its setup turn. Take the
turn away, or be faster than the turn.

---

## Open for playtesting

1. **Mega Mawile and Mega Medicham.** Huge Power and Pure Power double their
   Attack, so their 480 and 510 BST badly understate them — both were top-tier
   in Gen 6 singles. Priced Premium for that reason; watch whether 600 FP is
   enough.
2. **Choice Scarf with reusable items.** A Scarf that restores every battle is
   exactly how it works in official play, so this is fine — but it's the
   first item that lets a player lock the speed tier building 4 taught them to
   fight over. Watch whether every team becomes Scarf Garchomp plus five.
3. **Mega Raichu Y and Mega Absol Z.** The two likeliest to be too strong:
   both are faster than almost everything in the building, and No Guard and
   Sharpness remove their usual weaknesses. They're comparable to Mega
   Alakazam, so not out of line for the tier, but they're the first two to
   hold back if the building plays too fast.
4. **Hazard stack in D10.** Three hazards plus Whirlwind against a player who
   hasn't bought Heavy-Duty Boots is very punishing. That may be the lesson,
   or it may just feel unfair. Watch the win rate.
5. **The Mega Ring handoff.** It's a key item given from a script that
   usually only gives FP. If a save is ever wiped or migrated, the player
   needs another way to get it back.

---

## Implementation notes

Not code — a checklist for when this gets built.

- **Building 4 completion** (`Facility_AfterBossBattle`,
  `data/maps/BattleFrontier_BattleTowerLobby/scripts.inc`): add a building 4
  branch, like the existing building 1 one. It gives `ITEM_MEGA_RING`, sets
  the `FACILITY_DOOR_DOME` bit in `unlockedFacilityDoors`, and shows the
  dialogue above. Nothing sets any door bit yet (see the comment above
  `FACILITY_DOOR_DOME` in `src/facility.c`).
- **The run loop only exists in the Tower lobby.** Building 5 is the first
  building elsewhere, so the Dome lobby needs the same entry, battle and
  post-battle script flow. This is the biggest single piece of work here.
- **Keeper 3** (`BattleFrontier_ExchangeServiceCorner_EventScript_MegaStoneKeeper`)
  is a "coming later" placeholder. It needs a real stock list and menu, the
  same shape as Keeper 2's.
- **New data:** `FACILITY_BUILDING_5`, 13 trainer constants (12 pool plus the
  boss), the `sBuilding5Pool` table, and the shop entries above at
  `unlockBuilding 4`.
- **Update the docs:**
  - `battle-tower-design-v2.md`'s progression table: building 5 now adds
    Megas, Paradoxes, Ultra Beasts and Mythicals, not "pseudo-legendaries
    only".
  - Its item table: Clear Amulet moves to building 6.
  - `shop-spec.md`: the Mega Stone keeper now opens after building 4, not
    building 5.
- **To verify before building:** that the CPU Mega Evolves automatically from
  trainer data, that `Chilly Reception`, `Mortal Spin`, `Glaive Rush`,
  `Malignant Chain` and `Tachyon Cutter` all behave correctly, and that the AI
  knows to Trick a Choice item rather than using Trick as a wasted turn.
