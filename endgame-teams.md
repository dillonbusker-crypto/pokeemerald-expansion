# Endgame Teams — Brain Rematches and the Elite Four

**Status: built, not played.** The five Brain rematches (`TRAINER_FACTORY_*`),
the Elite Four (`TRAINER_DEVON_*`), New Mauville (`TRAINER_NEW_MAUVILLE_*`),
the Gym rematches (`TRAINER_ENDGAME_*`) and Scott's final teams
(`TRAINER_SKY_PILLAR_SCOTT_*`) are in `src/data/trainers.party`. **On
2026-10-15 the owner replaced the rosters of the Elite Four, Maxie, Archie and
Scott's Sky Pillar team**; those seven are described below as rewritten, built
only, not battle-tested. Nothing is tuned by play yet. Answers `storyline.md`,
"Still to decide" #2 (the Brains' upgraded teams) and #3 (the Elite Four's
teams). Team sets are in Pokémon Showdown syntax, like the gauntlet docs.

---

## The rules these teams follow

| Rule | Applied as |
|---|---|
| Pool | **The Brains, the Gym rematches and the four New Mauville admins:** only Pokémon and Mega Stones the player can buy by gauntlet 8 (shop waves 0–7 in `src/facility_shop.c`). No Zacian, Miraidon, Zygarde, Mewtwo, Lati or Kangaskhan, except the Gym rematches' box-art legendaries. Every species was checked against the shop list. **The Elite Four, Maxie, Archie and Scott are the owner's own rosters (2026-10-15) and no longer follow it**: legendaries, Paradox Pokémon and newer Megas |
| Priority | OU and Uber first, using Showdown's tier data as of 2026-10-05. Singles teams are judged by Gen 9 singles and National Dex tiers (National Dex is where Megas are tiered). Doubles teams are judged by doubles tiers (DOU/DUber) |
| Items | Item clause on every team. The Brains', Gym and admin items are sold by the shop. The rewritten teams use whatever fits, so Booster Energy, Spell Tag or Shuca Berry need not be sold |
| Moves | Every move was checked against the expansion's own learnsets, including egg moves from pre-evolutions, so the player could copy any set. One exception: Rotom-Wash's Hydro Pump comes from its form change, as on Noland's built team |
| Brains | **Normal Megas** that hold their stone and Mega Evolve in battle (one per team). Level 50, since they're Scott's chipped trainers |
| Elite Four | **Three to four permanent Megas each, plus legendaries.** Listed already in Mega form, holding a real item. Real levels 52/52/53/53/54/55, the ace at 55 (`storyline.md`: "up to 55") |
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

| Member | Type | Permanent Megas | Legendaries and Paradox | Ace (Lv 55) |
|---|---|---|---|---|
| Sidney | Dark | Mega Sharpedo, Absol Z, Tyranitar, Darkrai | Yveltal, Roaring Moon | Mega Darkrai |
| Phoebe | Ghost | Mega Gengar, Banette, Chandelure | Marshadow, Lunala, Calyrex-Shadow | Calyrex-Shadow |
| Glacia | Ice | Mega Froslass, Abomasnow, Crabominable, Baxcalibur | Calyrex-Ice, Kyurem-White | Kyurem-White |
| Drake | Dragon | Mega Feraligatr, Charizard X, Garchomp Z, Dragonite | Eternatus, Koraidon | Koraidon |

All singles, as in vanilla. **They are fought in pairs, back to back, at Devon
Corp:** Sidney then Phoebe on 1F, Glacia then Drake on 2F, with the rival
healing the party between the two of a pair. A loss anywhere in a pair
whites out to Rustboro's Pokémon Center and resets the pair (both are
fought again); a finished pair stays beaten. Phoebe and Drake therefore
face a party that was healed after one fight, not a fresh one.

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

# The Elite Four (levels 52–55, permanent Megas and legendaries)

**Rewritten 2026-10-15** from the owner's new rosters. The old shop-pool teams
are gone. Each team has **three to four permanent Megas** and one or two
legendaries or Paradox Pokémon. A permanent Mega is listed already in Mega
form, holding a real item (`Sharpedo-Mega @ Choice Band`), and doesn't revert
on switching or fainting. Permanent Megas **don't use up the trainer's one
Mega Evolution**, but no non-Mega member of these teams has a Mega form, so
nothing is left to evolve. Levels climb **52, 52, 53, 53, 54, 55** on every
team: the ace is at 55, the second strongest at 54. That is two to five over
the player's chipped level 50. AI: as the Brains. Every item on a team is
different. Fought in pairs, back to back, with the rival's heal between the
two of a pair (see "The Elite Four" table above); a loss resets the pair. Built,
never battle-tested or played.

## Engine notes (the seven rewritten teams)

Found while the sets were checked against this build's learnsets, abilities
and species data.

- **Species names that differ from the obvious:** `Calyrex-Shadow`,
  `Calyrex-Ice`, `Urshifu-Single-Strike`, `Absol-Mega-Z`, `Garchomp-Mega-Z`,
  `Zygarde-Mega`, `Necrozma-Ultra`, `Greninja-Mega`.
- **Calyrex's ability must be written as a constant.** "As One" is the
  display name of both As One abilities, so a name lookup is ambiguous.
  Phoebe's Calyrex uses `Ability: ABILITY_AS_ONE_SHADOW_RIDER` and Glacia's
  `Ability: ABILITY_AS_ONE_ICE_RIDER`. trainerproc accepts any text that starts
  with `ABILITY_`.
- **A permanent Mega has only its Mega ability.** Mega Sharpedo has no Speed
  Boost (only Strong Jaw), Mega Golisopod has no Emergency Exit (only Tough
  Claws). None of these sets relies on a lost ability.
- **Booster Energy works under sand.** `TryBoosterEnergy`
  (`src/battle_hold_effects.c`) only checks for sun. Under sun, Protosynthesis
  comes from the sun and the item stays unused.
- **Mega Starmie is a Huge Power physical attacker** (the Mega's only ability).
  **Mega Zygarde is a special attacker** (216 SpA, 70 Atk).
- **Pokémon listed directly in a late form:** `Necrozma-Ultra` keeps its form
  through a faint in a release build, but a test build marks the test invalid
  and a debug build crashes (a form-change assert). A guard beside the
  permanent-Mega one in `CanBattlerFormChange` (`src/battle_util.c`) is being
  added. `Zygarde-Mega` is covered by the permanent-Mega rule but no test lists
  it directly.
- Partial IV lines (`IVs: 0 Atk`) are accepted by trainerproc.

## Sidney: Dark

**Lead: Yveltal** (Life Orb, Hasty, Dark Aura). Dark Aura raises every Dark
move on the field, the player's too, while it's out. Mega Sharpedo (Choice
Band) follows. Roaring Moon, Mega Absol Z and Mega Tyranitar are the setup
trio, and **Mega Darkrai** (Leftovers) closes at 55. The whole team is Dark,
so it shares one set of holes (Fighting, Fairy, Bug), and the moves are
chosen to cover them.

```
Yveltal @ Life Orb
Ability: Dark Aura
Level: 52
EVs: 4 Atk / 252 SpA / 252 Spe
Hasty Nature
- Oblivion Wing
- Knock Off
- Sucker Punch
- Heat Wave

Sharpedo-Mega @ Choice Band
Ability: Strong Jaw
Level: 52
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Crunch
- Liquidation
- Ice Fang
- Psychic Fangs

Roaring Moon @ Booster Energy
Ability: Protosynthesis
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Dragon Claw
- Knock Off
- Iron Head

Absol-Mega-Z @ Black Glasses
Ability: Sharpness
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Night Slash
- Play Rough
- Close Combat

Tyranitar-Mega @ Weakness Policy
Ability: Sand Stream
Level: 54
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Dragon Dance
- Stone Edge
- Knock Off
- Earthquake

Darkrai-Mega @ Leftovers
Ability: Bad Dreams
Level: 55
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Nasty Plot
- Dark Pulse
- Sludge Bomb
- Focus Blast
```

**Win conditions.** (1) The setup trio: Roaring Moon and Mega Tyranitar with
Dragon Dance, Absol with Swords Dance. Each needs one free turn, and the
Pokémon before them exist to trade and make it. (2) Mega Darkrai: it hits hard
with no setup and nukes after one Nasty Plot. It is frail, so it comes in last
against a thinned team.

- **Yveltal** (252 SpA / 252 Spe, Hasty, Speed 171): special lead. Oblivion
  Wing heals, Knock Off and Sucker Punch are the Dark STAB and priority, Heat
  Wave covers Steel, Grass and Ice.
- **Mega Sharpedo** (Jolly, Speed 179): a glass cannon with Strong Jaw bite
  moves (Crunch, Ice Fang, Psychic Fangs) plus Liquidation, all boosted by the
  Band. Psychic Fangs turns Fighting and Poison walls into KOs. The Band lock
  is its weakness: each of the four moves hits a different set of targets.
- **Roaring Moon** (Booster Energy, Adamant): Adamant on purpose. If an
  Intimidate drops its Attack on entry and Speed becomes the highest stat,
  Booster Energy would boost Speed instead. Adamant keeps it on Attack (222
  Atk, 180 Spe, 270 after one Dragon Dance). Iron Head is the Fairy answer.
- **Mega Absol Z** (Black Glasses, Jolly, Speed 235): the fast cleaner. Dark/
  Ghost, so Fighting, Normal and Psychic do nothing to it. Play Rough and
  Close Combat cover the Dragons, Fighting and Steel that the Dark STAB can't
  reach. Black Glasses, not Life Orb: recoil plus its own team's sand would
  wear down a 148 HP body.
- **Mega Tyranitar** (Weakness Policy, Dragon Dance): sets sand and sweeps. A
  super-effective hit from the player's many Fighting, Ground, Fairy and Water
  attackers becomes +2 Attack and +2 Sp. Atk. Speed is only 98, so it needs
  a Dragon Dance turn.
- **Mega Darkrai** (Leftovers, Timid, 0 Atk IV): Nasty Plot, Dark Pulse, Sludge
  Bomb for Fairy, Focus Blast for Steel, Normal and Ice. Bad Dreams is its only
  ability and does nothing here (no sleep).

**Own-sand cost.** Tyranitar's Sand Stream chips every other member, 1/16 a
turn. Absol and Sharpedo have under 160 HP and are the fragile ones. The Mega's
ability is fixed, so the only mitigation is that Tyranitar comes in mid-game.

**How to beat it:** Fighting, Fairy and Bug attackers. Absol is immune to
Fighting, so go through the others. A hard Fairy Mega is covered by Iron Head,
Play Rough, Sludge Bomb and Heat Wave, but Roaring Moon is 4x weak to Fairy.
Weakness Policy gives Tyranitar one answer to a super-effective hit if it
survives. Under the player's sun, Moon gets its boost from the sun instead.

**Easiest dial:** Mega Darkrai's level (55 to 53). Harder: put Life Orb back
on Darkrai.

## Phoebe: Ghost

**Lead: Mega Gengar** (Focus Sash, Shadow Tag). Leading makes the player's
blind opening pick a commitment, with no pivoting out. Mega Banette (her
vanilla Pokémon), Marshadow, **Mega Chandelure** (Choice Scarf), Lunala and
**Calyrex-Shadow** (the ace, 55) follow. Three permanent Megas, three
legendaries.

```
Gengar-Mega @ Focus Sash
Ability: Shadow Tag
Level: 52
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Shadow Ball
- Sludge Bomb
- Focus Blast
- Destiny Bond

Banette-Mega @ Spell Tag
Ability: Prankster
Level: 52
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Poltergeist
- Gunk Shot
- Will-O-Wisp
- Destiny Bond

Marshadow @ Choice Band
Ability: Technician
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Spectral Thief
- Close Combat
- Shadow Sneak
- Stone Edge

Chandelure-Mega @ Choice Scarf
Ability: Infiltrator
Level: 53
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Shadow Ball
- Fire Blast
- Energy Ball
- Psychic

Lunala @ Leftovers
Ability: Shadow Shield
Level: 54
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Atk
Modest Nature
- Calm Mind
- Moongeist Beam
- Moonblast
- Moonlight

Calyrex-Shadow @ Life Orb
Ability: ABILITY_AS_ONE_SHADOW_RIDER
Level: 55
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Nasty Plot
- Astral Barrage
- Psyshock
- Giga Drain
```

**Win conditions.** (1) Gengar and Banette are an attrition pair: Sash, then an
attack or Destiny Bond, so each trades one for one or better. (2) Marshadow
punishes setup: Spectral Thief steals the player's boosts. (3) Chandelure,
Lunala and Calyrex finish: Calyrex's Nasty Plot at 243 Speed can sweep from
one free turn.

- **Mega Gengar** (Sash, Timid, 0 Atk IV, Speed 207): 170 SpA behind Shadow
  Ball, Sludge Bomb and Focus Blast. Shadow Tag stops the player's switches.
  Ghost types, Shed Shell and pivot moves escape it, which is the intended
  counterplay.
- **Mega Banette** (Spell Tag, Adamant, 252 HP / 252 Atk): Prankster makes
  Will-O-Wisp and Destiny Bond priority. Poltergeist needs the target to hold
  an item. Gunk Shot is the backup and the Fairy answer.
- **Marshadow** (Choice Band, Jolly, Speed 205): Technician boosts Shadow Sneak.
  Spectral Thief, Close Combat, Shadow Sneak, Stone Edge. The Band lock works
  best when it is already out as the player sets up.
- **Mega Chandelure** (Choice Scarf, Timid, 0 Atk IV): 175 SpA, Infiltrator
  ignores Substitute and screens. At level 53, Speed is 165, and 247 with the
  Scarf, past nearly every unboosted level-50 Pokémon. The Scarf locks it into
  one attack.
- **Lunala** (Leftovers, Modest, 252 HP / 252 SpA): Shadow Shield halves the
  first hit. Calm Mind, Moongeist Beam (ignores abilities), Moonblast,
  Moonlight.
- **Calyrex-Shadow** (Life Orb, Timid, 0 Atk IV): As One (Unnerve and Grim
  Neigh) stops berries and gives +1 SpA per KO. Nasty Plot, Astral Barrage,
  Psyshock for physical walls, Giga Drain for Dark types.

**Coverage.** Dark types (resist Ghost, immune to Psychic): Focus Blast, Gunk
Shot, Close Combat, Fire Blast, Energy Ball, Moonblast, Giga Drain. Normal
types: Sludge Bomb, Focus Blast, Moonblast. Steel: Focus Blast, Fire Blast,
Close Combat, Stone Edge. Fairy: Sludge Bomb and Gunk Shot.

**To check when played.** Destiny Bond is a self-target move, so Dark types
should not block it with Prankster, but that call path wasn't traced. The AI
has no deliberate Shadow Tag play: the trap is strongest on the lead.

**How to beat it:** Ghost types (immune to the trap), Shed Shell, U-turn or
Volt Switch. Priority or a Scarf on the Sash lead still loses the Destiny Bond
trade. Dark Megas face Gunk Shot, Focus Blast and Close Combat. Hard Trick
Room or stall faces a burning Banette and Lunala's Calm Mind.

**Easiest dial:** Calyrex's Nasty Plot slot (Protect or Dark Pulse), or drop
it to 54 and shift the others down one. Second: Gengar's Sash to Expert Belt.

## Glacia: Ice

**Lead: Mega Froslass** (Focus Sash, Snow Warning) sets snow and Aurora Veil.
Mega Abomasnow (Icy Rock) refreshes snow to eight turns and recasts the Veil
as the first one expires. Every member is part Ice, so snow raises the whole
team's Defense by 50%. Mega Crabominable and Mega Baxcalibur are the Defense-
boosted bruisers, **Calyrex-Ice** is second (54) and **Kyurem-White** is the
ace (55). Four permanent Megas, two legendaries.

```
Froslass-Mega @ Focus Sash
Ability: Snow Warning
Level: 52
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Aurora Veil
- Blizzard
- Shadow Ball
- Will-O-Wisp

Abomasnow-Mega @ Icy Rock
Ability: Snow Warning
Level: 52
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Atk / 0 Spe
Quiet Nature
- Aurora Veil
- Blizzard
- Giga Drain
- Earth Power

Crabominable-Mega @ Leftovers
Ability: Iron Fist
Level: 53
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Bulk Up
- Ice Hammer
- Drain Punch
- Knock Off

Baxcalibur-Mega @ Loaded Dice
Ability: Thermal Exchange
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Icicle Spear
- Scale Shot
- Earthquake

Calyrex-Ice @ Life Orb
Ability: ABILITY_AS_ONE_ICE_RIDER
Level: 54
EVs: 252 HP / 252 Atk / 4 SpD
IVs: 0 Spe
Brave Nature
- Swords Dance
- Glacial Lance
- Close Combat
- High Horsepower

Kyurem-White @ Choice Specs
Ability: Turboblaze
Level: 55
EVs: 252 SpA / 4 SpD / 252 Spe
Timid Nature
- Ice Beam
- Draco Meteor
- Earth Power
- Fusion Flare
```

**Win conditions.** (1) Kyurem-White's Choice Specs close out the tail:
Fusion Flare for Steel, Earth Power for Fire and Steel, and Turboblaze ignores
abilities. (2) Calyrex-Ice or Baxcalibur sweep after one Swords Dance, with
Chilling Neigh giving Calyrex +1 Attack per KO.

- **Mega Froslass** (Sash, Timid, Speed 195): Aurora Veil on turn one, Blizzard
  (never misses in snow), Shadow Ball, Will-O-Wisp against physical attackers.
- **Mega Abomasnow** (Icy Rock, Quiet, 252 HP / 252 SpA, 0 Atk and 0 Spe IV):
  Icy Rock is on Abomasnow, not Froslass, because the lead is gone in two or
  three turns. Blizzard, Giga Drain (no Leftovers, so it heals itself), Earth
  Power, Aurora Veil. 4x weak to Fire.
- **Mega Crabominable** (Leftovers, Brave, 252 HP / 252 Atk, 0 Spe IV): Bulk
  Up, with Iron Fist on Ice Hammer and Drain Punch, and snow Defense. Knock
  Off for Ghost and Psychic.
- **Mega Baxcalibur** (Loaded Dice, Jolly, Speed 161): Swords Dance, Icicle
  Spear and Scale Shot (4 to 5 hits), Earthquake. Thermal Exchange stops burns.
- **Calyrex-Ice** (Life Orb, Brave, 252 HP / 252 Atk, 0 Spe IV): As One
  (Chilling Neigh). Swords Dance, Glacial Lance, Close Combat and High
  Horsepower for Steel, Fire, Rock and Poison.
- **Kyurem-White** (Choice Specs, Timid, Speed 177): Ice Beam, Draco Meteor,
  Earth Power, Fusion Flare.

**No Trick Room.** Three of the six are fast, and the AI sets Trick Room whenever
it is slower than the player, which would fire for Calyrex and invert half the
team. The slow ones run Brave and 0 Spe IV, so if the *player* sets Trick Room
they move first.

**How to beat it:** Fire, Fighting, Rock and Steel hit every Ice type, and
Abomasnow takes 4x Fire. The coverage moves (Fusion Flare, Earth Power, Close Combat, Drain Punch)
punish the usual answers. Fairies are the real wall: only Fusion Flare and
Earth Power get through. Dragons trade with Kyurem and Baxcalibur, which are
Dragon too.

**To check when played.** Snow's +50% Defense for Ice types is Gen 9
behaviour (`B_SNOW_WARNING = GEN_LATEST`); if it's off, the slow trio loses
its bulk plan.

**Easiest dial:** drop Aurora Veil from Abomasnow and put Kyurem's Specs on
Life Orb, then shift every level down one. Harder: Light Clay on Froslass in
place of the Sash.

## Drake: Dragon

**Lead: Mega Feraligatr** (Lum Berry, Dragonize). The first two are Dragon
Dance setup leads (Feraligatr and Mega Charizard X), then Mega Garchomp Z (the
fast cleaner), Mega Dragonite (Multiscale), **Eternatus** (54) and **Koraidon**
(the ace, 55). Four permanent Megas, two legendaries.

```
Feraligatr-Mega @ Lum Berry
Ability: Dragonize
Level: 52
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Double-Edge
- Waterfall
- Earthquake

Charizard-Mega-X @ Weakness Policy
Ability: Tough Claws
Level: 52
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Flare Blitz
- Dragon Claw
- Roost

Garchomp-Mega-Z @ Life Orb
Ability: Levitate
Level: 53
EVs: 4 Atk / 252 SpA / 252 Spe
Naive Nature
- Draco Meteor
- Earthquake
- Fire Blast
- Stone Edge

Dragonite-Mega @ Heavy-Duty Boots
Ability: Multiscale
Level: 53
EVs: 252 Atk / 4 Def / 252 Spe
Adamant Nature
- Dragon Dance
- Outrage
- Extreme Speed
- Earthquake

Eternatus @ Leftovers
Ability: Pressure
Level: 54
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Dynamax Cannon
- Sludge Bomb
- Flamethrower
- Recover

Koraidon @ Choice Band
Ability: Orichalcum Pulse
Level: 55
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Collision Course
- Flare Blitz
- Dragon Claw
- U-turn
```

**Why Koraidon is the ace and not Dragonite.** Dragonite's strength
(Multiscale and Dragon Dance) is conditional on one hit and one free turn.
Koraidon needs neither: Orichalcum Pulse brings the sun and boosts its Attack,
and with a Band it hits for about 410 Attack at 55.

**Win conditions.** (1) A Dragon Dance chain in the front half (Feraligatr,
Charizard X, Dragonite). (2) The back half is pure frontal damage: Eternatus
and Koraidon, which a Haze or Roar doesn't answer.

- **Mega Feraligatr** (Lum Berry, Adamant, Speed 135): Dragonize turns Double-
  Edge into a Dragon STAB. Waterfall and Earthquake for Fire, Ground, Steel.
  Lum Berry for the status a slow setup lead draws. It leads because
  Koraidon's sun halves Water.
- **Mega Charizard X** (Weakness Policy, Adamant): Tough Claws boosts Flare
  Blitz and Dragon Claw (both contact). A Rock, Ground or Fairy hit turns
  into +2/+2. The swingiest item here: Leftovers is the safe swap.
- **Mega Garchomp Z** (Life Orb, Naive, 252 SpA, Speed 235): Draco Meteor, Fire
  Blast, Earthquake and Stone Edge.
- **Mega Dragonite** (Heavy-Duty Boots, Adamant): Dragon Dance, Outrage, Extreme
  Speed (the team's priority), Earthquake. Boots keep Multiscale through
  Stealth Rock.
- **Eternatus** (Leftovers, Timid, 0 Atk IV, Speed 215): Dynamax Cannon (a plain
  100 BP Dragon move here), Sludge Bomb for Fairy, Flamethrower, Recover.
- **Koraidon** (Choice Band, Jolly, Speed 225): Collision Course, Flare Blitz,
  Dragon Claw, U-turn as the exit from the Band lock.

**Coverage.** Dragon moves are walled by Steel and immune on Fairy. Fairy: Flare
Blitz (Charizard, Koraidon), Sludge Bomb (Eternatus), Fire Blast (Garchomp).
Steel: Earthquake (three Pokémon) and every Fire move. Ice and Dragon, the real
Dragon weaknesses, are covered by Rock, Ground and Fire coverage and Extreme
Speed.

**How to beat it:** Fairies and Ice into the front four (Charizard X's Policy
turns a Fairy hit into +2/+2). Ice into Dragonite only works while Multiscale
is down. Haze, Roar, Whirlwind and Unaware answer the three Dragon Dance
users and do nothing to Eternatus or Koraidon, which is the point.

**Easiest dial:** Koraidon's Choice Band to Sitrus Berry, or its level (55 to
54). Alternatively give Charizard Leftovers in place of the Policy.

---

# New Mauville (admins level 60, leaders level 65)

Six teams in `src/data/trainers.party` (`TRAINER_NEW_MAUVILLE_*`, 978-983),
answering `storyline.md`, "Still to decide" #4. Same rules table as above
for the four admins: every species and item is sold by the shop by gauntlet 8
(checked against `src/facility_shop.c`; the Mega Stones are Cameruptite,
Houndoominite, Sharpedonite and Swampertite), item clause per team, every move
checked against the expansion's learnsets, no OHKO, no evasion, no sleep. AI as
the Elite Four: omniscient, proactive switching. All singles. **Maxie and
Archie were rewritten on 2026-10-15** and, like the Elite Four, no longer
follow the shop rule: each has a permanent Primal (which Scott lent), three or
four permanent Megas and a legendary.

**Levels.** The four admins are level 60, five over the top of the Elite
Four (52-55): the siphon lifted every chipped Pokémon to 60 (the level of
Hoopa's legendaries) and the shop sells at 60 from then on, so the player's
whole party is at least 60 here and gains Experience now that the chips are
off. The leaders are level 65, five over the admins, and their five teammates
match their Primal. The player has at most one permanent Mega here (the Crown
holds six only after these fights are won).

**Order (changed 2026-10-15).** The four admins are the gates, in order
Tabitha, Courtney, Matt, Shelly, with a charging-coil heal after each. Then
**Maxie and Archie stand together at the generator and are fought back to
back**: Maxie first, then the rival (who has run in behind the player) heals
the party, then Archie. A loss to either whites out to Mauville's Pokémon
Center and **both are fought again**. This reverses the 2026-10-13 order (each
leader at the end of his own team's wing, with a full heal after every fight),
which was made because twelve Pokémon at 65 straight after four admins at 60
was a cliff. The rival's heal between the leaders and the siphon's level 60
party are what make the pair fair now.

**Megas.** Each admin has **one normal Mega**, holding its stone and Mega
Evolving in battle (like the Brains). Maxie and Archie have **permanent
Megas** instead, listed already in Mega form holding a real item (Maxie three,
Archie four), plus a permanent Primal, listed directly in Primal form
(`Groudon-Primal`, `Kyogre-Primal`) holding Leftovers, so it doesn't revert on
switching or fainting and Desolate Land or Primordial Sea starts the battle.

| Trainer | Theme | Mega | Level |
|---|---|---|---|
| Tabitha | Magma: Fire, Ground, Rock | Mega Camerupt | 60 |
| Courtney | Magma: Fire, Rock, Ground, Dark | Mega Houndoom | 60 |
| Matt | Aqua: Water, Dark, Ice | Mega Sharpedo | 60 |
| Shelly | Aqua: Water, Dark, Ground | Mega Swampert | 60 |
| Maxie | Sun, built around Primal Groudon | Permanent: Charizard Y, Heatran, Blaziken | 65 |
| Archie | Rain, built around Primal Kyogre | Permanent: Golisopod, Swampert, Starmie, Greninja | 65 |

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

**Rewritten 2026-10-15** (the owner's roster; no shop-pool rule). Maxie
stands at the generator beside Archie and is fought first, after all four
admins; the rival heals the party after him. **Primal Groudon leads.** Desolate Land makes
harsh sunlight and Water moves fail outright. Three **permanent Megas**: Mega
Charizard Y (Drought, the sun backup), Mega Heatran (Air Balloon) and Mega
Blaziken (Focus Sash, Speed Boost). Reshiram and Ho-Oh are the legendaries.
Groudon holds Leftovers, not the Red Orb, because it's listed directly as
`Groudon-Primal`.

```
Groudon-Primal @ Leftovers
Ability: Desolate Land
Level: 65
EVs: 252 HP / 252 Atk / 4 SpD
Brave Nature
IVs: 0 Spe
- Swords Dance
- Earthquake
- Fire Punch
- Stone Edge

Charizard-Mega-Y @ Life Orb
Ability: Drought
Level: 65
EVs: 4 Def / 252 SpA / 252 Spe
Timid Nature
- Fire Blast
- Solar Beam
- Focus Blast
- Roost

Heatran-Mega @ Air Balloon
Ability: Flash Fire
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Magma Storm
- Earth Power
- Flash Cannon
- Dark Pulse

Reshiram @ Assault Vest
Ability: Turboblaze
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Blue Flare
- Draco Meteor
- Earth Power
- Solar Beam

Blaziken-Mega @ Focus Sash
Ability: Speed Boost
Level: 65
EVs: 4 HP / 252 Atk / 252 Spe
Jolly Nature
- Swords Dance
- Flare Blitz
- Close Combat
- Thunder Punch

Ho-Oh @ Heavy-Duty Boots
Ability: Regenerator
Level: 65
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- Sacred Fire
- Brave Bird
- Earthquake
- Recover
```

**The weather war.** The player knows Maxie leads Groudon, so the obvious
answer is to lead their own Primal Kyogre. Switch-in abilities resolve
fastest-first, so the slowest Primal on the field keeps the weather.
Groudon is built **slow** on purpose: Brave and a 0 Spe IV with no Speed EVs
make Speed 109 at level 65, below any plausible level-60 Kyogre-Primal. Its
Desolate Land lands last and Kyogre's Water moves fail from turn one. Groudon
wins on bulk (266 HP, 274 Def, Leftovers). **Untested**: a headless lead
against a lead is one run.

**Win conditions.** (1) Groudon under Desolate Land: Swords Dance (330 Atk),
then Earthquake, Stone Edge and Fire Punch. Its 4x Water weakness is hidden
while the sun holds. (2) After Groudon falls, Charizard Y's Drought sets
ordinary sun, but only on switch-in, so if the AI sends Heatran or Blaziken
first there is no weather until Charizard comes in. Charizard is slot 2.
Everyone else works without weather.

- **Mega Charizard Y** (Life Orb, Timid, 272 SpA, Speed 196): Fire Blast,
  Solar Beam (instant in sun), Focus Blast, Roost. No Choice item, because a
  locked Fire Blast would be wasted under Primordial Sea.
- **Mega Heatran** (Air Balloon, Modest, 322 SpA, Speed 112): Magma Storm
  traps. The Balloon covers its 4x Ground weakness until it pops. Earth Power,
  Flash Cannon and Dark Pulse for Psychic and Ghost.
- **Reshiram** (Assault Vest, Modest): Blue Flare, Draco Meteor (the Rayquaza
  and Latios answer), Earth Power, Solar Beam. All four are attacks.
- **Mega Blaziken** (Focus Sash, Jolly): Speed Boost is permanent, so 215 Speed
  is 322 after one turn. Swords Dance, Flare Blitz, Close Combat, Thunder
  Punch for Water and Flying.
- **Ho-Oh** (Heavy-Duty Boots, Adamant, Regenerator): Sacred Fire, Brave Bird,
  Earthquake, Recover.

**Counterplay.** *Holding the player's Primal Kyogre* and switching it in
after Groudon is the real answer: Primordial Sea makes every Fire move fail,
and Groudon takes 4x Water. The team still has non-Fire damage everywhere
except Charizard, which has only Focus Blast. *Mega Rayquaza* (Delta Stream)
lifts the Water ban and exposes Groudon too. Reshiram's Draco Meteor is the
check. *Cloud Nine or Air Lock* (the player picks abilities) turns both
Desolate Land's Water block and the sun off: the hardest counter, and no
moveset fixes it. *Stealth Rock* hits Charizard and Ho-Oh 4x, so Ho-Oh holds
Boots.

**How to beat it:** Desolate Land makes Water fail, so use Grass, Ice and
Steel, or bring Kyogre-Primal in late. Take Groudon out before Swords Dance.
Expect the first four turns to be hard and the fight to ease once Groudon
falls without Drought.

**Easiest dial:** Groudon's Speed. Adamant with the IV at 31 (Speed 142) lets a
low-Speed Kyogre land its weather last, and the fight gets much easier. The
finer dial is Swords Dance (swap for Rock Polish or Fire Blast).

## Archie: rain, Primal Kyogre at level 65

**Rewritten 2026-10-15.** The mirror of Maxie, fought second at the
generator after the rival's heal, with Maxie already beaten (a loss repeats
both). **Primal Kyogre leads**, and Primordial Sea makes heavy
rain (Fire moves fail outright). Four **permanent Megas**: Golisopod (Assault
Vest), Swampert (Choice Band, Swift Swim), Starmie (Choice Scarf) and Greninja
(Life Orb). Lugia (Multiscale, Boots) is the anchor.

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

Golisopod-Mega @ Assault Vest
Ability: Tough Claws
Level: 65
EVs: 252 HP / 252 Atk / 4 Def
Adamant Nature
- First Impression
- Liquidation
- Leech Life
- Knock Off

Swampert-Mega @ Choice Band
Ability: Swift Swim
Level: 65
EVs: 4 HP / 252 Atk / 252 Spe
Adamant Nature
- Waterfall
- Earthquake
- Ice Punch
- Knock Off

Starmie-Mega @ Choice Scarf
Ability: Huge Power
Level: 65
EVs: 252 Atk / 4 SpA / 252 Spe
Naive Nature
- Liquidation
- Zen Headbutt
- Ice Beam
- Thunderbolt

Greninja-Mega @ Life Orb
Ability: Protean
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
- Surf
- Dark Pulse
- Ice Beam
- Grass Knot

Lugia @ Heavy-Duty Boots
Ability: Multiscale
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Aeroblast
- Psychic
- Calm Mind
- Roost
```

**Win conditions.** (1) The rain snowball: Kyogre's Calm Mind, then Swampert at
314 Speed in rain. (2) Two weather-proof stat checks: Mega Starmie and Mega
Greninja outspeed nearly everything and need no rain.

- **Kyogre-Primal** (Leftovers, Modest, 266 HP, 330 SpA, Speed 142): a bulk
  piece, not a speed piece. Origin Pulse, Thunder (never misses in rain), Ice
  Beam, Calm Mind.
- **Mega Golisopod** (Assault Vest, Adamant): Tough Claws boosts every attack.
  First Impression (priority), Liquidation, Leech Life, Knock Off. Only the
  Vest protects it, and it is 4x weak to Fire, safe while Primordial Sea holds.
- **Mega Swampert** (Choice Band, Adamant, 157 Speed, 314 in rain): Waterfall,
  Earthquake, Ice Punch, Knock Off. Without rain it is merely decent, which
  is deliberate.
- **Mega Starmie** (Choice Scarf, Naive, 252 Atk / 4 SpA / 252 Spe): **Huge
  Power makes it a physical attacker** (392 Atk, Speed 244, 366 with the
  Scarf). It is mixed for coverage: Liquidation and Zen Headbutt are the
  STABs, Ice Beam and Thunderbolt hit Grass, Dragon, Flying and Water on the
  special side.
- **Mega Greninja** (Life Orb, Timid, Speed 275): Surf, Dark Pulse, Ice Beam,
  Grass Knot. Protean works once per battle in this repo and Greninja is
  already Water/Dark, so the single use goes to Ice Beam or Grass Knot. Grass
  Knot is also a non-Water answer through Desolate Land.
- **Lugia** (Heavy-Duty Boots, Modest): Multiscale halves the first hit, then
  Roost. Aeroblast, Psychic, Calm Mind, Roost.

**After Kyogre falls.** The weather is gone (there's no second setter) and Swift
Swim switches off, so Swampert drops to 157 Speed. Starmie, Greninja, Lugia and
Golisopod lose only the 1.5x on Water moves.

**Counterplay.** *Primal Groudon* (Desolate Land) shuts down all the Water
moves, leaves Kyogre only Ice Beam, and exposes Golisopod to Fire. Everyone in
the back five has a live non-Water move. *A Fire Mega* once the rain is gone
(Charizard, Blaziken) one-shots Golisopod. *Mega Rayquaza* lifts the rain boost
but changes little else.

**How to beat it:** Electric and Grass hit the Water types, and Primordial Sea
blanks Fire. Pressure Kyogre before it stacks Calm Mind. Starmie's 392 Attack
is the highest raw physical number on the field at 65.

**Easiest dial:** Kyogre's Calm Mind slot (Surf instead stops the snowball).
Second: Swampert's Band to Sitrus Berry, or take the Scarf off Starmie.

---

## Open questions for review

1. **Repeats across opponents.** The Elite Four, Maxie, Archie and Scott no
   longer follow the shop pool, so repeats are the owner's picks. Repeats
   that remain:
   - **Normal Mega for one trainer, permanent for another:** Mega Gengar
     (Lucy, Phoebe), Mega Heatran (Anabel, Maxie), Mega Blaziken (Greta,
     Maxie), Mega Swampert (Shelly, Archie), Mega Sharpedo (Matt, Sidney).
   - **Same Pokémon, different Mega or no Mega:** Marshadow (Greta, Phoebe),
     Roaring Moon (Tucker, Sidney), Greninja (Matt, Archie's Mega), Garchomp
     (Tabitha, Drake's Mega).
   - **By design:** the Primals (Maxie's and Archie's, which Scott takes back),
     Mega Darkrai (Sidney's ace, Scott's Factory team), Mega Zygarde
     (Roxanne, Scott).
   - Gone: Mega Salamence is Tucker's alone now (Drake no longer has it), and
     Kingambit is still Anabel's alone.
   - **Against Spenser's and Brandon's gauntlet teams:** Great Tusk (Tucker),
     Iron Hands (Anabel) and Tornadus (Lucy) each also appear on one of those
     two teams. The new rosters add none. The player doesn't fight Spenser or
     Brandon again, so these only repeat against gauntlets 7 and 8.
2. **A normal Mega on top?** Resolved as moot for the Elite Four: permanent
   Megas don't use up the battle's one Mega Evolution, but every non-Mega
   member (Yveltal, Roaring Moon, Marshadow, Lunala, Calyrex, Kyurem-White,
   Eternatus, Koraidon) has no Mega form, and the teams already carry three to
   four permanent Megas.
3. **Difficulty.** These are full-strength teams with no handicaps, and
   harder than the old ones: each Elite Four team has two Uber legendaries
   or a legendary and a Paradox, and Scott's back half is now three tanks and
   an Ultra, where it was frail. The Elite Four comes before the siphon, so
   the player has no permanent Megas yet; their only edge is a level 60
   legendary from Hoopa, if they caught one. Levels stay at 52–55 for
   playtesting (your call), and each section lists its own easiest dial. The
   Elite Four's hardest threats: Calyrex-Shadow's Nasty Plot (Phoebe), Kyurem-
   White (Glacia), Koraidon (Drake), Mega Darkrai (Sidney).
4. **Engine checks when played:**
   - **Necrozma-Ultra and Zygarde-Mega listed directly** (Scott). Ultra
     needs the form-change guard (in progress) and a test; Zygarde-Mega is
     covered by the permanent-Mega rule but untested directly.
   - **Megas untested in a trainer team:** Mega Starmie, Golisopod,
     Greninja, Crabominable, Abomasnow, Feraligatr, Dragonite and Heatran.
     Check that each transforms, shows its sprite and that its ability works
     in a quick battle. Mega Magearna, Absol Z, Garchomp Z, Baxcalibur,
     Froslass and Chandelure are newer Megas (Legends: Z-A and later) that
     the old teams used, and they were never run either.
   - **The Calyrex abilities** as `ABILITY_AS_ONE_*` constants: confirm the
     generated `trainers.h` has them.
   - **Three to four permanent Megas on one team:** the engine tests cover a
     single permanent Mega at a time.
   - **Maxie's weather war** (a slow Groudon-Primal landing Desolate Land
     last) and Phoebe's Prankster Destiny Bond against a Dark type.
5. **Trainer IDs:** five new Brain teams plus four Elite Four members makes
   nine, already counted in `storyline.md`'s budget (984 of 1000 with the
   whole endgame).
6. **Scott's four Sky Pillar entries are identical now** (see "The final
   battle"). The script still branches on `FLAG_STEVEN_HAS_LATIOS` and
   `FLAG_DARKRAI_FREED`; the "one short" Darkrai line was rewritten to fit.
   The owner decides whether to collapse the three copies.

---

# The Gym rematches (Roxanne 60, Wattson 65)

Two teams in `src/data/trainers.party` (`TRAINER_ENDGAME_ROXANNE` 990,
`TRAINER_ENDGAME_WATTSON` 991), for the endgame towns sprint
(`sprint-endgame-towns.md`, D1 and D2; the Gyms themselves are in
`sprint-c-gyms.md`). Both singles, class Leader with their own pics, the
Elite Four's and New Mauville's AI (omniscient, proactive switching).

| Rule | Applied as |
|---|---|
| Pool | Every species, item and Mega Stone is sold by the endgame shop (`src/facility_shop.c`, waves 0-7), **except the box-art legendary** (Zygarde-Complete with Zygardite, Miraidon), which is the owner's pick, as the Primals were |
| Megas | **One each, Mega Evolving in battle:** Roxanne's is her box-art legendary (Mega Zygarde); Wattson's is a normal Mega from the shop (Mega Zeraora, the owner's pick) |
| Items | Item clause on both teams |
| Moves | Every move checked against this build's learnsets (level-up, teachable and egg) |
| Levels | Roxanne 60 (the admins), Wattson 65 (Maxie and Archie) |

## Roxanne: sand and stone, Mega Zygarde at level 60

Glimmora leads with Stealth Rock and Mortal Spin (it clears the player's
hazards) behind a Focus Sash, and Toxic Debris lays Toxic Spikes when it's hit
physically. Tyranitar's Sand Stream gives every Rock type +50% Sp. Def, and
its Thunder Wave is the team's speed control alongside Mega Zygarde's Glare.
Garganacl walls physical attackers, and Salt Cure does double damage to Water
and Steel, Rock's two worst matchups. Terrakion (Swords Dance) and a Choice
Scarf Iron Boulder are the breaker and the revenge killer, both hitting Steel
with Close Combat. **Mega Zygarde** (216 HP, 216 Sp. Atk, Aura Break) closes:
Focus Blast is for the Ice types that otherwise check it 4x.

```
Glimmora @ Focus Sash
Ability: Toxic Debris
Level: 60
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
IVs: 0 Atk
- Stealth Rock
- Mortal Spin
- Power Gem
- Earth Power

Tyranitar @ Smooth Rock
Ability: Sand Stream
Level: 60
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Stone Edge
- Knock Off
- Earthquake
- Thunder Wave

Garganacl @ Leftovers
Ability: Purifying Salt
Level: 60
EVs: 252 HP / 252 Def / 4 SpD
Impish Nature
- Salt Cure
- Recover
- Iron Defense
- Body Press

Terrakion @ Life Orb
Ability: Justified
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Swords Dance
- Close Combat
- Stone Edge
- Earthquake

Iron Boulder @ Choice Scarf
Ability: Quark Drive
Level: 60
EVs: 252 Atk / 4 Def / 252 Spe
Jolly Nature
- Mighty Cleave
- Psycho Cut
- Close Combat
- Earthquake

Zygarde-Complete @ Zygardite
Ability: Power Construct
Level: 60
EVs: 4 HP / 252 SpA / 252 Spe
Modest Nature
IVs: 0 Atk
- Earth Power
- Dragon Pulse
- Focus Blast
- Glare
```

| Pokémon | Role |
|---|---|
| Glimmora | Hazard lead: Stealth Rock, Toxic Debris, Mortal Spin removal; Sash guarantees a turn |
| Tyranitar | Sand setter (Smooth Rock, 8 turns), Thunder Wave speed control, Knock Off |
| Garganacl | Physical wall; Salt Cure punishes Water and Steel; Iron Defense + Body Press |
| Terrakion | Swords Dance breaker; Close Combat for Steel, Earthquake for the rest |
| Iron Boulder | Choice Scarf revenge killer; Mighty Cleave goes through Protect |
| Zygarde-Complete | **Mega Zygarde**, the ace: special attacker, Glare cripples faster threats |

**How to beat it:** Water hits five of six super-effectively and Grass four
(not Glimmora or Zygarde). Ice is 4x on Zygarde, but mind Focus Blast. Sand
chips everything that isn't Rock, Ground or Steel, so Steel types do well
here, until Salt Cure.

*(Brandon's gauntlet 8 team also has Zygarde-Complete @ Zygardite; this is a
singles set at 60 against his doubles set at 50.)*

## Wattson: Electric Terrain, Miraidon at level 65

Miraidon leads: Hadron Engine sets Electric Terrain on entry, which boosts
every grounded Electric move by 30%, powers Iron Hands's Quark Drive (Attack)
and Miraidon's own Sp. Atk. Tapu Koko's Electric Surge resets it. The speed
control is Prankster Thunder Wave (Thundurus) and a fast core (Miraidon, Koko,
Mega Zeraora at 130-153). Volt Switch and U-turn keep the momentum; Grass Knot
and Ice Punch hit the Ground types an Electric team otherwise can't touch.
**Magnezone** is his Emerald line (Magneton was in his Gym team), and **Mega
Zeraora** is his one normal Mega (the owner's pick over Mega Manectric).

```
Miraidon @ Choice Specs
Ability: Hadron Engine
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
IVs: 0 Atk
- Electro Drift
- Draco Meteor
- Volt Switch
- Overheat

Tapu Koko @ Heavy-Duty Boots
Ability: Electric Surge
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
IVs: 0 Atk
- Thunderbolt
- Dazzling Gleam
- U-turn
- Roost

Iron Hands @ Assault Vest
Ability: Quark Drive
Level: 65
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Drain Punch
- Supercell Slam
- Ice Punch
- Volt Switch

Thundurus @ Life Orb
Ability: Prankster
Level: 65
EVs: 4 HP / 252 SpA / 252 Spe
Timid Nature
IVs: 0 Atk
- Thunder Wave
- Nasty Plot
- Thunderbolt
- Grass Knot

Magnezone @ Air Balloon
Ability: Magnet Pull
Level: 65
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
IVs: 0 Atk
- Thunderbolt
- Flash Cannon
- Volt Switch
- Mirror Coat

Zeraora @ Zeraorite
Ability: Volt Absorb
Level: 65
EVs: 252 Atk / 4 SpA / 252 Spe
Naive Nature
- Plasma Fists
- Close Combat
- Knock Off
- Grass Knot
```

| Pokémon | Role |
|---|---|
| Miraidon | **Box-art legendary.** Lead, sets Electric Terrain; Choice Specs wallbreaker, Volt Switch pivot |
| Tapu Koko | Second terrain setter; fast pivot (U-turn); Dazzling Gleam for Dragons |
| Iron Hands | Bulky physical attacker, Quark Drive in terrain; Ice Punch for Ground and Dragon; Assault Vest |
| Thundurus | Prankster Thunder Wave speed control; Ground immune; Nasty Plot, Grass Knot for Ground types |
| Magnezone | His Emerald line. Magnet Pull traps and removes Steel types; Air Balloon covers the 4x Ground weakness until popped; Mirror Coat punishes special attackers |
| Zeraora | **Mega Zeraora** (157 Atk, 147 SpA, 153 Speed, Volt Absorb): the ace. Terrain-boosted Plasma Fists, Close Combat for Steel, Knock Off, Grass Knot for heavy Ground types |

**How to beat it:** a Ground type is immune to the Electric moves, and five
of the six are weak to Ground (Thundurus flies; Magnezone's Balloon holds
until it's hit); watch for Ice Punch, Grass Knot and Overheat.
Paralysis from Thundurus is the real threat: carry a Lum Berry or an
Electric type. A Dragon or Fairy takes on Miraidon. Steel types: beware Magnezone's trap.

*(Brandon's gauntlet 8 team also has Miraidon and Iron Hands, at 50 in doubles.)*

---

# The final battle

**Built** (`TRAINER_SKY_PILLAR_SCOTT_LATIAS` / `_LATIOS` and
`_NO_DARKRAI_LATIAS` / `_LATIOS`, `src/data/trainers.party`), **rewritten
2026-10-15** from the owner's new roster. Never battle-tested or played.
Answers `storyline.md`, "Still to decide" #5 (Scott's movesets, EVs and items).
Scott at the top of Sky Pillar: **level 100, every Pokémon listed directly in
its permanent form** (Mega Rayquaza, Mega Mewtwo Y and Mega Zygarde keep no
stone, the Primals and Ultra Necrozma no orb or crystal), **every one holding
a different item** (item clause), four attacks each, max EVs in the attacking
stat and Speed (or HP in place of Speed on the three slow Pokémon), and **no
balance at all.**

| Rule | Applied as |
|---|---|
| Pool | None. This is Scott's own team, so the shop's pool doesn't apply: legendaries, Primals, Mega Rayquaza, Mega Zygarde, Ultra Necrozma |
| Variants | **All four Sky Pillar entries are now the same six Pokémon.** The Latias and Latios entries and the two Bad Dreams entries no longer differ. The Lati and Mega Darkrai live only on the Factory teams (below) |
| Order | Rayquaza leads, then Kyogre, Groudon, Mewtwo, Zygarde, Necrozma |
| AI | `Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Omniscient` (no Smart Switching), `Music: Intense`, class `Founder`, `Pic: Founder Scott` |
| Whiteout | A normal white-out: the player wakes up beside Nurse Joy outside the tower, and the held items come back |

## Scott at Sky Pillar

```
Rayquaza-Mega @ Focus Sash
Ability: Delta Stream
Level: 100
EVs: 252 Atk / 4 SpD / 252 Spe
Jolly Nature
- Dragon Dance
- Dragon Ascent
- Extreme Speed
- Earthquake

Kyogre-Primal @ Assault Vest
Ability: Primordial Sea
Level: 100
EVs: 252 HP / 252 SpA / 4 SpD
IVs: 0 Atk
Modest Nature
- Water Spout
- Origin Pulse
- Ice Beam
- Thunder

Groudon-Primal @ Shuca Berry
Ability: Desolate Land
Level: 100
EVs: 252 HP / 252 Atk / 4 SpD
Adamant Nature
- Precipice Blades
- Heat Crash
- Stone Edge
- Swords Dance

Mewtwo-Mega-Y @ Life Orb
Ability: Insomnia
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Psystrike
- Aura Sphere
- Ice Beam
- Thunderbolt

Zygarde-Mega @ Leftovers
Ability: Aura Break
Level: 100
EVs: 252 HP / 252 SpA / 4 SpD
Modest Nature
- Core Enforcer
- Earth Power
- Sludge Wave
- Focus Blast

Necrozma-Ultra @ Choice Scarf
Ability: Neuroforce
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
IVs: 0 Atk
Timid Nature
- Photon Geyser
- Dark Pulse
- Flash Cannon
- Earth Power
```

Items are six different: Focus Sash, Assault Vest, Shuca Berry, Life Orb,
Leftovers, Choice Scarf.

**The slow three absorb, the fast three kill.** Rayquaza (361 Speed), Mewtwo
(416) and Necrozma (588 with the Scarf) outspeed almost everything a player
can field. Kyogre, Groudon and Zygarde (216, 216, 236 Speed, uninvested) are
the stat-check wall: 404, 404 and 636 HP, behind an Assault Vest, a Shuca Berry
and Leftovers. "No balance" means no pivoting, no hazards, no status, no
screens, no Pokémon whose job is to be a wall.

**The weathers are a relay, not a clash.** Scott has no Smart Switching, so a
Primal or Delta Stream Pokémon is always gone before the next one arrives:
Delta Stream, then rain, then sun, each ending when its holder faints. Two
weather Pokémon are never out together in singles. (An earlier draft of this
doc claimed the weathers cancel each other. They only do if the player
switches.)

**Win conditions.** (1) The Primals: Kyogre's Water Spout in its own rain does
about twice an average level-80 bulky Mega's HP, and Groudon's Heat Crash
about 1.6 times. Each Primal also shuts down a type: Primordial Sea erases the
player's Fire moves, Desolate Land their Water moves. (2) The fast trio
finishes the damaged remainder. Every one of the 18 types is hit super
effectively by at least one move on the team.

- **Mega Rayquaza** (Focus Sash, Jolly, 252 Atk / 4 SpD / 252 Spe, Speed 361):
  Dragon Dance, Dragon Ascent, Extreme Speed, Earthquake. The Sash guarantees
  a move. It isn't Choice-locked, because Scott has no Smart Switching. Dragon
  Dance (541 Speed after one) is the one setup move the AI uses well.
- **Kyogre-Primal** (Assault Vest, Modest, 0 Atk IV): Water Spout, Origin
  Pulse (takes over below about 75% HP), Ice Beam, Thunder. No Fire Blast: it
  fails in Primordial Sea. Atk IV 0 against Foul Play.
- **Groudon-Primal** (Shuca Berry, Adamant): Precipice Blades, Heat Crash (120
  BP only under about 200 kg), Stone Edge, Swords Dance. The Shuca Berry takes
  the first Ground hit, so in the sun it has no real weakness.
- **Mewtwo-Mega-Y** (Life Orb, Timid, 0 Atk IV, Speed 416, SpA 535): Psystrike
  (hits Defense), Aura Sphere (never misses), Ice Beam, Thunderbolt for the
  Water types that shrug off the rest.
- **Zygarde-Mega** (Leftovers, Modest, 636 HP, SpA 584): **a special attacker**
  (216 SpA, 70 Atk), so Thousand Arrows isn't worth a slot. Core Enforcer, Earth
  Power, Sludge Wave (Fairy and Grass), Focus Blast (its own Ice problem).
- **Necrozma-Ultra** (Choice Scarf, Timid, 0 Atk IV, Speed 588, SpA 433):
  Neuroforce (x1.25 on super-effective hits) with four super-effective angles.
  Photon Geyser is special here (it uses the higher of Atk and SpA) and hits
  Special Defense, while Psystrike hits Defense. Dark Pulse for the Psychic
  and Ghost mirrors, Flash Cannon for Fairy, Earth Power for Steel. The Scarf
  makes it outspeed even a Dragon-Danced Rayquaza and locks it into one move,
  which a no-switching AI will feel.

**How to beat it:** Scarf or priority on the Sash lead. A Ground-STAB hit into
Groudon (the Shuca Berry takes the first). An Ice Beam into Zygarde (4x, but
636 HP survives it, so it trades once). Dark, Bug or Ghost hitters into
Mewtwo and Necrozma (70 and 97 base Defense). **How it makes them pay:** no
free turn to set up a stall or a Perish Song, and the bulky trio punishes a
Pokémon brought to answer one of them.

**Easiest dial:** take the three bulk items off the slow trio (Kyogre's
Assault Vest to Mystic Water, Groudon's Shuca Berry to Soft Sand, Zygarde's
Leftovers to Wise Glasses): a stat check becomes a glass-cannon race.
Harder: Necrozma's Scarf to Life Orb or Expert Belt (it has the lowest
damage on the team).

**To check when played** (engine): Necrozma-Ultra staying Ultra through a
faint (a one-line guard is being added to `CanBattlerFormChange`, and a test
is needed), and Zygarde-Mega listed directly (no test lists it yet).

## The variants (a script question for the owner)

With the Lati and Mega Darkrai gone from the Sky Pillar team, **all four
Sky Pillar entries are identical.** The Sky Pillar script still branches on
them: `FLAG_STEVEN_HAS_LATIOS` picks the Latias or Latios entry, and
`FLAG_DARKRAI_FREED` picks the Bad Dreams one, which is harmless. Scott's
"one short" line there (`SkyPillar_Top_EventScript_ScottOneShort`) was
rewritten on 2026-10-15 to fit the new roster: a freed Darkrai only cost him a
spare, and he doesn't carry spares anymore. Deleting three entries and
pointing everything at one would free three trainer IDs; the owner's call.

## The Factory teams (unchanged)

Scott's Pillar Chamber teams after gauntlet 8 are **not rewritten**
(`TRAINER_FACTORY_SCOTT_LATIAS` / `_LATIOS` and `_NO_DARKRAI_*`): Mega Mewtwo
Y, Mega Latias or Latios (by `FLAG_STEVEN_HAS_LATIOS`), Mega Darkrai, Mega
Gengar, Mega Salamence and Mega Mawile. A player who freed Darkrai in Bad
Dreams (`FLAG_DARKRAI_FREED`) fights a Scott with **Mega Magearna standing in**
for Darkrai, in Darkrai's slot, and nothing else changed:

```
Magearna-Mega @ Wise Glasses
Ability: Soul-Heart
Level: 100
EVs: 252 SpA / 4 SpD / 252 Spe
Modest Nature
- Fleur Cannon
- Flash Cannon
- Aura Sphere
- Thunderbolt
```

Darkrai hit harder on the Dark side; Magearna trades that for a Steel/Fairy
body and Soul-Heart snowballing off every faint. Scott acknowledges the
missing Darkrai before the Factory battle.
