# Endgame Teams — Proposal (2026-10-15)

**Status: proposal, not built.** The owner's new rosters for the Elite Four,
Maxie, Archie and Scott, with movesets, spreads, natures and items designed
by one agent per trainer (Sonnet 5.5, high effort) against this expansion's
own learnsets and species data. Each section has a paste-ready
`trainers.party` entry, the team plan, per-Pokémon notes, a verification table
and concerns. Nothing in `src/` has changed. When these are accepted they
replace the matching entries in `src/data/trainers.party` and the sections in
`endgame-teams.md`.

**Owner's revisions (2026-10-15), applied to the entries below; the prose in
each section predates them:**

- Sidney: Urshifu out, **Yveltal** in (Life Orb, Hasty, Oblivion Wing /
  Knock Off / Sucker Punch / Heat Wave). **Mega Sharpedo takes the Choice Band.**
  **Mega Darkrai holds Leftovers.**
- Phoebe: **Mega Chandelure holds a Choice Scarf** (Speed 190 at 53, over every
  unboosted level-50 base 130).
- Archie: **Mega Starmie holds a Choice Scarf** (Speed 298 at 65) and goes mixed
  for coverage: Liquidation / Zen Headbutt / Ice Beam / Thunderbolt, Naive,
  252 Atk / 4 SpA / 252 Spe. Rapid Spin and Recover are gone. **Mega Greninja
  takes the Life Orb.**
- Scott: **Ultra Necrozma holds a Choice Scarf** (Speed 588).

Engine notes gathered while compiling (see each section for detail):

- Species names that differ from the obvious: `Calyrex-Shadow`, `Calyrex-Ice`,
  `Urshifu-Single-Strike`, `Absol-Mega-Z`, `Garchomp-Mega-Z`, `Zygarde-Mega`,
  `Necrozma-Ultra`, `Greninja-Mega`. The two Calyrex abilities must be written
  as `ABILITY_AS_ONE_SHADOW_RIDER` / `ABILITY_AS_ONE_ICE_RIDER`, since both
  display as "As One".
- A permanent Mega has only its Mega ability (no Speed Boost on Mega Sharpedo,
  no Emergency Exit on Mega Golisopod).
- Booster Energy activates under sand in this engine (it only checks for sun).
- `Necrozma-Ultra` listed directly keeps its form on fainting in a release
  build (the form-change assert's recovery returns), but a test build marks
  the test invalid and a debug build shows a crash screen. Add a one-line
  guard beside the permanent-Mega one in `CanBattlerFormChange`
  (`src/battle_util.c`) and a test, when built.
- `Zygarde-Mega` listed directly is covered by the permanent-Mega rule but has
  no test of its own yet. It is a special attacker (216 SpA, 70 Atk).
- With the Lati and Darkrai off Scott's team, his `_LATIOS` and both
  `_NO_DARKRAI_` entries become identical to the main one.

---

# Sidney — Dark (Elite Four, levels 52/52/53/53/54/55)

## 1. Entry

```
=== TRAINER_DEVON_SIDNEY ===
Name: SIDNEY
Class: Elite Four
Pic: Elite Four Sidney
Gender: Male
Music: Elite Four
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart Switching / Omniscient
Mugshot: Purple

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

Items are all distinct (Choice Band, Expert Belt, Booster Energy, Black Glasses, Weakness Policy, Life Orb). Every Pokémon is Dark-typed, so the whole team shares the same holes (Fighting, Fairy, Bug). The set choices are built around that.

## 2. Team plan

**Lead: Urshifu (52).** It is the bulkiest of the early Pokémon (182 HP, 125 Def) and has U-turn. Band Wicked Blow is a guaranteed crit and goes through Protect and Substitute (Unseen Fist), so a lead that loses the matchup can U-turn into a better one. The AI sees the player's sets, so it can pivot sensibly. Sharpedo is the follow-up.

**Win conditions.**
1. The setup trio: Roaring Moon (Dragon Dance), Absol (Swords Dance) and Mega Tyranitar (Dragon Dance). Each needs one free turn, and the earlier Pokémon exist to trade and create that turn.
2. Darkrai-Mega (ace, 55). It hits hard with no setup and nukes after one Nasty Plot. It arrives last.

**How they cover each other.**
- *Fairy and Steel:* Poison Jab (Urshifu), Iron Head (Moon) and Sludge Bomb (Darkrai). Dark attacks and Fighting attacks are resisted by Fairy, so the Dark team carries its answers as secondary moves.
- *Fighting:* Absol is immune to it (Dark/Ghost). Sharpedo's Psychic Fangs and Moon's Dragon Claw hit it, and Darkrai has Sludge Bomb and Focus Blast.
- *Ice, Dragon, Grass:* Ice Fang from Sharpedo.
- *Steel and Normal:* Close Combat on Urshifu and Absol, Earthquake on Tyranitar, Focus Blast on Darkrai.
- *Speed ladder (lv50 players with +nature max Speed: base 112 = 180, base 135 = 205):* Absol 235, Moon 180, Sharpedo 179, Urshifu 169, Darkrai 165, Tyranitar 98. Absol outspeeds everything unscarfed. The slow Pokémon (Tyranitar, Darkrai) come in after the fast ones have traded.

**Likely player answers and the price.**
- *Fairy Megas (Gardevoir, Sylveon-style walls):* Poison Jab, Iron Head and Sludge Bomb cover them. Moon is 4x weak to Fairy, so the AI should keep it away from them and send Urshifu or Darkrai.
- *Fast Fighting attackers (Mega Lucario, Lopunny):* Absol is immune to them and answers by Swords Dance and Night Slash. Tyranitar-Mega's Weakness Policy punishes a 4x Fighting hit if it survives: 222 HP and 183 Def means a non-boosted Mega Lucario Close Combat may not KO.
- *Intimidate:* it blunts Urshifu and Absol. The Choice Band lock (Urshifu) is worked around by U-turn.
- *Own-sand cost:* Sand Stream chips every non-Rock teammate, 1/16 a turn. Tyranitar should enter mid-game, and Absol (148 HP) and Sharpedo (151 HP) are the fragile ones. This is accepted as a cost. The fight is meant to feel dangerous, not clean.

## 3. Per-Pokémon notes

**Urshifu (52, Choice Band).** Lead pivot and early wallbreaker. Jolly max Speed gives 169, past a neutral base-112 mon (164). Wicked Blow is the STAB nuke (always crits, 75 BP), Close Combat hits Steel, Normal, Ice, Rock and Dark. Poison Jab is the Fairy answer, because both of Urshifu's STABs are resisted by Fairy. U-turn is the out for the Band lock. Atk is 189, 283 with Band.

**Sharpedo-Mega (52, Expert Belt).** The Mega form has only Strong Jaw, so there is no Speed Boost and no Protect-stall plan. It is a Speed 179 glass cannon with 151 HP, 93 Def, 88 SpD, so it is a pure coverage wallbreaker. Crunch (80x1.5 = 120 effective), Ice Fang (65x1.5) and Psychic Fangs (85x1.5) are all bite moves boosted by Strong Jaw. Liquidation is the Water STAB. Psychic Fangs turns Fighting and Poison walls into KOs. Expert Belt fits because the four moves are chosen to be super effective on most targets, and it avoids Life Orb recoil on a 151 HP body. Choice Band was rejected: Urshifu holds it, and a locked Sharpedo is a free read for the player.

**Roaring Moon (53, Booster Energy).** Booster Energy over "Dragon Dance plus another item" for these reasons. Protosynthesis only needs the item when sun is not up. It is not blocked by Tyranitar's sand: `TryBoosterEnergy` (src/battle_hold_effects.c:54-62) only checks that sun is absent. The item boosts Attack by 30%, the same as Life Orb with no recoil, and it cannot be Knocked Off or Tricked because the holder is Paradox (src/battle_util.c:8866). I took Adamant over Jolly on purpose. With Jolly, Atk 202 vs Spe 198 is a near tie, and an Intimidate drop at entry would shift Booster Energy to Speed (+50%) and weaken the damage. Adamant gives Atk 222 vs Spe 180, so the boost always goes to Attack, and one Dragon Dance puts Speed at 270. Dragon Claw is the Dragon STAB, Knock Off the Dark STAB (it hits Psychic and Ghost super effectively, and removes items), and Iron Head the answer to Fairy (which is immune to Dragon Claw and resists Dark) and Ice.

**Absol-Mega-Z (53, Black Glasses).** Fast cleaner. Jolly gives 235 Speed, 218 Atk, 148 HP, 85 Def. Swords Dance plus Night Slash (70x1.5 with Sharpness, high crit) is the sweep. Close Combat hits Dark, Steel and Ice, which resist or ignore the Dark STAB, and Play Rough hits Dragon and Fighting. Black Glasses was chosen over Life Orb (Darkrai has it, and recoil plus own-sand chip would kill a 148 HP body) and over Focus Sash (sand breaks it). Absol-Mega-Z is Dark/Ghost, so Fighting, Normal and Psychic do nothing to it.

**Tyranitar-Mega (54, Weakness Policy).** Second-strongest, sand setter and bulky Dragon Dance sweeper. 222 HP, 183 Def, 151 SpD (226 in sand), 255 Atk. Speed is only 98, so it needs one Dragon Dance turn. Weakness Policy turns a super-effective hit (and the many Fighting, Ground, Water, Grass, Fairy and Steel attackers the player has) into +2 Attack and +2 Sp. Atk. The four moves, Stone Edge, Knock Off and Earthquake, cover Fire, Flying, Ice, Bug, Psychic, Ghost, Steel and Electric. Kept from the current set.

**Darkrai-Mega (55, Life Orb).** Ace. Timid max SpA/Spe: 238 SpA, 165 Speed, 159 HP, 165/165 defenses. It is frail, so it is deliberately last, against a thinned team. It does about 54% to a neutral base-100 target with Dark Pulse before any boost, so Nasty Plot is a bonus rather than a requirement. Nasty Plot, Dark Pulse, Sludge Bomb (Fairy), Focus Blast (Steel, Dark, Normal, Rock, Ice). Life Orb because the coverage moves need the 1.3x too. Bad Dreams is irrelevant here (no sleep), and it is the only ability the Mega has. IVs 0 Atk blunt Foul Play.

## 4. Verification

Level-up and teachable lists use `src/data/pokemon/level_up_learnsets/gen_9.h` and `src/data/pokemon/teachable_learnsets.h`. All six forms use the base species learsets (checked in species_info: `.levelUpLearnset`/`.teachableLearnset`).

| Pokémon | Move | Where legal |
|---|---|---|
| Urshifu | Wicked Blow | level_up_learnsets/gen_9.h:19711 |
| Urshifu | Close Combat | gen_9.h:19726; teachable_learnsets.h:47734 |
| Urshifu | Poison Jab | teachable_learnsets.h:47749 |
| Urshifu | U-turn | teachable_learnsets.h:47766 |
| Sharpedo | Crunch | gen_9.h:8386 |
| Sharpedo | Liquidation | gen_9.h:8388; teachable_learnsets.h:21255 |
| Sharpedo | Ice Fang | gen_9.h:8383; teachable_learnsets.h:21253 |
| Sharpedo | Psychic Fangs | teachable_learnsets.h:21259 |
| Roaring Moon | Dragon Dance | gen_9.h:21935; teachable_learnsets.h:51595 |
| Roaring Moon | Dragon Claw | gen_9.h:21931; teachable_learnsets.h:51594 |
| Roaring Moon | Knock Off | teachable_learnsets.h:51610 |
| Roaring Moon | Iron Head | teachable_learnsets.h:51609 |
| Absol | Swords Dance | gen_9.h:9263; teachable_learnsets.h:23528 |
| Absol | Night Slash | gen_9.h:9260 |
| Absol | Play Rough | teachable_learnsets.h:23510 (also egg move) |
| Absol | Close Combat | teachable_learnsets.h:23494 |
| Tyranitar | Dragon Dance | teachable_learnsets.h:17158 |
| Tyranitar | Stone Edge | gen_9.h:6778; teachable_learnsets.h:17202 |
| Tyranitar | Knock Off | teachable_learnsets.h:17181 |
| Tyranitar | Earthquake | gen_9.h:6777; teachable_learnsets.h:17161 |
| Darkrai | Nasty Plot | gen_9.h:11404; teachable_learnsets.h:29044 |
| Darkrai | Dark Pulse | gen_9.h:11406; teachable_learnsets.h:29032 |
| Darkrai | Sludge Bomb | teachable_learnsets.h:29059 |
| Darkrai | Focus Blast | teachable_learnsets.h:29036 |

Abilities (species_info `.abilities` line):

| Form | Ability | File:line |
|---|---|---|
| Urshifu-Single-Strike | Unseen Fist | gen_8_families.h:7335 |
| Sharpedo-Mega | Strong Jaw | gen_3_families.h:6559 |
| Roaring Moon | Protosynthesis | gen_9_families.h:7129 |
| Absol-Mega-Z | Sharpness | gen_3_families.h:10564 |
| Tyranitar-Mega | Sand Stream | gen_2_families.h:8476 |
| Darkrai-Mega | Bad Dreams | gen_4_families.h:7607 |

Other checks:
- Species constants: `SPECIES_ABSOL_MEGA_Z` (include/constants/species.h:1675, the -Z form exists next to the older `SPECIES_ABSOL_MEGA`), `SPECIES_URSHIFU_SINGLE_STRIKE` (892), `SPECIES_ROARING_MOON`, `SPECIES_DARKRAI_MEGA`, `SPECIES_SHARPEDO_MEGA`, `SPECIES_TYRANITAR_MEGA`.
- Strong Jaw: Crunch, Ice Fang and Psychic Fangs are `.bitingMove = TRUE` in src/data/moves_info.h. Night Slash has `.slicingMove` for Absol's Sharpness.
- All moves are legal. Nothing needed substituting.
- Partial `IVs: 0 Atk` is accepted by trainerproc (existing example `IVs: 0 Spe` at trainers.party:21445).
- Party line `Urshifu-Single-Strike` follows the coordinator's correction. Existing lines in trainers.party use plain `Urshifu`, which resolves to the same constant (`SPECIES_URSHIFU = SPECIES_URSHIFU_SINGLE_STRIKE`).

## 5. Concerns for the owner

- **The sand premise was wrong.** The brief says Booster Energy under sand gives no boost. In this engine only sun blocks it (src/battle_hold_effects.c:54-62). Booster Energy works under Tyranitar's sand. Under the player's sun (Charizard-Y, Groudon-type Drought), Moon gets the sun boost instead, and the item stays unused until sun ends.
- **Own-sand chip.** Tyranitar-Mega's Sand Stream hurts everything else on the team (all Dark, none sand-immune except the Rock/Dark Tyranitar). Absol and Sharpedo have under 160 HP, so they lose about 9 HP a turn. It also resets every time Tyranitar re-enters. The Mega's ability is fixed, so the only mitigation is having the AI bring Tyranitar late.
- **No Speed Boost.** The Mega Sharpedo has only Strong Jaw, so it is a plain Speed 105 attacker, not a snowballing one. This set does not rely on boosting.
- **Intimidate and Booster Energy.** If a player's Intimidate drops Attack at Moon's entry and Speed becomes the highest stat, Booster Energy boosts Speed. Adamant avoids it, as explained above.
- **Shared holes.** The whole team is Dark, so Fighting, Fairy and Bug attackers are the player's correct answers. The fight is hard only for teams that bring none of them. Mega Darkrai and Tyranitar are the likeliest to be OHKO'd by a 4x/2x Fighting hit (Weakness Policy gives Tyranitar one chance to answer).
- **Engine risk:** the newer Z-A Mega Absol-Mega-Z (Sharpness) and Darkrai-Mega are already used by existing trainers (`Absol-Mega-Z` in the current Sidney entry, `Darkrai-Mega` in other entries), so no new form risk. Nothing here depends on Ultra or Primal forms.
- **Easiest dial:** Darkrai's level (55 to 53) and, if still too hard, Life Orb to Leftovers. To make it harder, raise Absol to 55 (it is the faster sweeper) and move Darkrai to 54.


---

# Phoebe (Elite Four, Ghost): L52, 52, 53, 53, 54, 55

## 1. Entry (replaces the whole current `=== TRAINER_DEVON_PHOEBE ===` block)

Two format notes, both verified against `tools/trainerproc/main.c` and `include/constants/`:

- The species constant is `SPECIES_CALYREX_SHADOW`, so the party line is `Calyrex-Shadow`. The brief's `Calyrex-Shadow-Rider` would not compile. (There is no `-Ice-Rider` either; it is `Calyrex-Ice`.)
- The parser turns the ability text into a constant by upper-casing it and replacing non-alphanumerics with `_`. "As One" is also the name of `ABILITY_AS_ONE_ICE_RIDER`, and the bracketed forms would mangle. So Calyrex's line uses the constant itself, `Ability: ABILITY_AS_ONE_SHADOW_RIDER`. `is_constant()` accepts any text starting with `ABILITY_`.

```
=== TRAINER_DEVON_PHOEBE ===
Name: PHOEBE
Class: Elite Four
Pic: Elite Four Phoebe
Gender: Female
Music: Elite Four
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart Switching / Omniscient
Mugshot: Green

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

Items are all distinct (Focus Sash, Spell Tag, Choice Band, Choice Specs, Leftovers, Life Orb). Banette and Chandelure keep their current spreads; the only change there is Banette's Life Orb becoming Spell Tag (Life Orb moves to Calyrex) and Chandelure dropping from 55 to 53 so Calyrex and Lunala sit above it.

## 2. Team plan

**Order and levels.** Gengar 52, Banette 52, Marshadow 53, Chandelure 53, Lunala 54, Calyrex 55. Levels still ascend, as in Sidney's entry. Lunala is the 54 "second-strongest" slot and Calyrex the 55 ace. Mega Gengar leads. I considered keeping it back.

**Why Gengar leads.** The AI has no deliberate Shadow Tag play: `battle_ai_util.c:466` only treats the target as trapped for `ShouldTrap` scoring, and `battle_ai_switch.c:2139` handles the AI's own switching. Whatever the AI does, a Shadow Tag mon trapping a *known* opponent is strongest when it is the opponent the player chose blind, with no team preview. That is the lead. Leading makes the player's opening pick a commitment: no pivoting out of a bad lead, no pre-positioned answer. Held back, Gengar comes in after a KO against a mon the player has already chosen to keep, and the AI picks its own replacement without regard to who gets trapped, so the trap fires at random. Gengar is also frail (60/80/95 bulk), so it will trade. Leading means its trade value (Focus Sash, then an attack or Destiny Bond) is spent at full information.

**Gengar's kit.** Focus Sash guarantees a hit from the 170 SpA lead. With Sash broken, Gengar is at 1 HP, and Destiny Bond has simple AI logic (`battle_ai_main.c:4751`): used when the AI is faster and the target can KO it. So the line is: Gengar attacks if it can KO (Try To Faint wins), otherwise Destiny Bond. Either outcome takes the player's lead down. Coverage is Ghost, Poison and Fighting. That hits every common defensive type except Fairy/Steel combos, handled below.

**Win conditions.**
1. Gengar/Banette are an attrition pair that guarantee a one-for-one or better trade each. Banette's Prankster Destiny Bond is always faster, and the AI loves that spot. Destiny Bond targets the user, so the Prankster Dark-type block (`BlocksPrankster`, `battle_util.c:9410`, `B_PRANKSTER_DARK_TYPES`) should not apply to it; Will-O-Wisp is the move Dark types shrug off. I did not trace the self-target call path, so confirm in a test if you care.
2. Marshadow punishes setup. Spectral Thief steals the player's boosts, and the shop makes Calm Mind, Dragon Dance and Swords Dance lines the common win path.
3. Chandelure (175 SpA Specs) and Calyrex (Nasty Plot, 243 Speed) are the finishers, with Lunala as a bulky Calm Mind wall-breaker that stays up through Shadow Shield and Moonlight.

**How the pieces cover each other.**
- Dark types (Tyranitar-Mega, Weavile, Darkrai) resist Ghost and are immune to Psychic, and Sucker Punch hits the Ghosts. Answers: Focus Blast (Gengar), Gunk Shot (Banette), Close Combat (Marshadow), Fire Blast and Energy Ball (Chandelure), Moonblast (Lunala), Giga Drain (Calyrex).
- Normal types are immune to Ghost. Answers: Sludge Bomb, Focus Blast, Moonblast, Giga Drain.
- Steel types resist Poison and Fairy. Answers: Focus Blast, Fire Blast, Close Combat, Stone Edge.
- Fairy types resist Fighting and Ghost-neutral. Answers: Sludge Bomb and Gunk Shot.
- Fighting and Poison mons are hit by Psychic/Psyshock.

**The player's likely answers and how they pay.**
- A Dark Mega such as Tyranitar. Phoebe has Gunk Shot, Focus Blast, Close Combat and Giga Drain for it. It also has priority Sucker Punch, so Gengar's Sash covers that first hit.
- Priority or Scarf cleaners to snipe Gengar. Sash plus Destiny Bond means the trade still happens.
- Hard Trick Room or stall. Banette's Prankster Will-O-Wisp cripples physical walls, Lunala Calm Mind outlasts them, and Spectral Thief steals defensive boosts.
- Shadow Tag escape. The player has Ghost types (immune to trapping, `B_GHOSTS_ESCAPE`), Shed Shell, and pivot moves, which is a fair counterplay window. Set mode means the player gets no free switch on a KO, so the trap matters most on the lead.

## 3. Per-Pokémon notes

**Gengar-Mega, L52, Timid, Focus Sash.** Perma Mega Shadow Tag lead. 252 Speed at L52 is 207 (base 130), outspeeding everything below base ~135 that does not hold a Scarf. 170 SpA behind Shadow Ball, Sludge Bomb and Focus Blast hits everything Ghost/Poison/Fighting can reach. Destiny Bond is the Sash follow-up the AI uses correctly. I chose Sash over Expert Belt because the lead has to survive one hit to do its job. 0 Atk IV blunts Foul Play.

**Banette-Mega, L52, Adamant, Spell Tag.** Prankster is permanent here, so Will-O-Wisp and Destiny Bond are +1 priority every turn, and Destiny Bond is always "faster" for the AI. At 252 Atk and 165 base it is a legitimate Poltergeist attacker (roughly 247 Attack; Poltergeist needs the target to hold an item, which the player's perfect sets always do). Gunk Shot covers Fairy, Grass and Dark (Dark types are immune to Prankster's burn but take Gunk Shot normally). Spell Tag replaces Life Orb because the Orb now goes to Calyrex and Banette does not need recoil on a Destiny Bond mon.

**Marshadow, L53, Jolly, Choice Band.** Technician only here, which boosts Shadow Sneak (40 to 60). Speed is 205 at L53. Spectral Thief (90 BP, steals boosts before damage) is the anti-setup piece and also hits Psychic/Ghost for neutral or better. Close Combat is the main nuke, Shadow Sneak is priority for chip finishes, and Stone Edge covers Flying, Fire and Ice. Choice Band over Life Orb because Life Orb is on Calyrex; the lock is fine for an AI that mostly wants the highest-damage attack anyway. Note that the Band lock makes the anti-setup job work best when it is *already out* as the player sets up, not when it comes in after.

**Chandelure-Mega, L53, Timid, Choice Specs.** Unchanged except 0 Atk IV and level 53 instead of 55. 175 SpA behind Specs, Infiltrator ignoring Substitute and screens. Speed is 165 (base 90), which beats base-90 and slower, not base 100 Timid. That is acceptable, because it is a cleaner behind Gengar, Banette and Marshadow, not a lead. Fire Blast over Flamethrower for the damage, since Steel/Fairy and Ice answers matter. Energy Ball hits Water/Ground/Rock; Psychic hits Poison/Fighting.

**Lunala, L54, Modest, Leftovers.** 137 HP and Shadow Shield halves the first hit, so a 252 HP spread is around 262 HP at 54 with roughly 117 Def (89 base is the weak spot; the setup is Calm Mind, which also raises SpD). Moongeist Beam is the Ghost STAB and ignores the target's ability (so it breaks Multiscale and Sturdy on the way); Moonblast hits Dark, Fighting, Dragon and covers Normal. Moonlight is the sustain the AI uses reliably. No Psychic: the two STABs plus Moonblast already reach everything except Steel/Poison corner cases. Leftovers gives long-term recovery while Shadow Shield's one-time protection does the burst.

**Calyrex-Shadow, L55, Timid, Life Orb.** Ace. As One (Unnerve and Grim Neigh): the player cannot eat berries and Calyrex gains +1 SpA after each KO. Speed 243 (base 150) outspeeds everything except Scarf users; 165 SpA with Nasty Plot hits +2 immediately. Astral Barrage (120 BP, Ghost, spread-irrelevant in singles) is the STAB, Psyshock hits physical walls (Blissey, Ting-Lu), and Giga Drain is the Dark-type answer plus sustain. I left Protect and Trick Room off: the AI uses Nasty Plot well, and Calyrex does not need more. Life Orb over Specs so the AI can set up when it is safe; Chandelure already has Specs.

## 4. Verification

Learnset tables are in `src/data/pokemon/level_up_learnsets/gen_9.h` (the GEN_LATEST set; earlier gen files hold older versions), `src/data/pokemon/teachable_learnsets.h` and `src/data/pokemon/egg_moves.h`. Mega forms point at the base species' learnset (`.levelUpLearnset = sBanetteLevelUpLearnset` etc.). Note that trainer data does not enforce learn levels, so Marshadow's high-level moves are fine.

| Species | Move | Source |
|---|---|---|
| Gengar-Mega | Shadow Ball | gen_9.h:2603 (level 48) |
| Gengar-Mega | Destiny Bond | gen_9.h:2604 (level 54) |
| Gengar-Mega | Sludge Bomb | teachable_learnsets.h:6772 |
| Gengar-Mega | Focus Blast | teachable_learnsets.h:6746 |
| Banette-Mega | Poltergeist | teachable_learnsets.h:23134 |
| Banette-Mega | Gunk Shot | teachable_learnsets.h:23126 (also Shuppet egg move, egg_moves.h list at 3245) |
| Banette-Mega | Will-O-Wisp | teachable_learnsets.h:23154 (level 16 in gen_9.h) |
| Banette-Mega | Destiny Bond | egg_moves.h:3247 (`sShuppetEggMoveLearnset`) |
| Marshadow | Spectral Thief | gen_9.h:18114 (level 72) |
| Marshadow | Close Combat | gen_9.h:18117 (level 99) |
| Marshadow | Shadow Sneak | gen_9.h:18104 |
| Marshadow | Stone Edge | teachable_learnsets.h:44495 |
| Chandelure-Mega | Shadow Ball | teachable_learnsets.h:34802 |
| Chandelure-Mega | Fire Blast | teachable_learnsets.h:34786 |
| Chandelure-Mega | Energy Ball | teachable_learnsets.h:34784 |
| Chandelure-Mega | Psychic | in the same Chandelure table (grep output, `sChandelureTeachableLearnset` at line 34781) |
| Lunala | Moongeist Beam | gen_9.h:17877 (level 0) |
| Lunala | Moonblast | gen_9.h:17889 (level 56) |
| Lunala | Moonlight | gen_9.h:17886 (level 35) |
| Lunala | Calm Mind | teachable_learnsets.h:43987 |
| Calyrex-Shadow | Nasty Plot | gen_9.h:19919 |
| Calyrex-Shadow | Astral Barrage | gen_9.h:19917 |
| Calyrex-Shadow | Giga Drain | gen_9.h:19937 (level 16) |
| Calyrex-Shadow | Psyshock | gen_9.h:19938 (level 24) and teachable_learnsets.h:48145 |

Grep used for the teachables: `bash scratchpad/tl.sh Banette Gengar ...`, a small script that prints the `s<Species>TeachableLearnset[]` block from `teachable_learnsets.h`. Level-up moves came from awk over the `s<Species>LevelUpLearnset[]` block in `gen_9.h`.

| Species | Ability | species_info line |
|---|---|---|
| Gengar-Mega | Shadow Tag | gen_1_families.h:12371 |
| Banette-Mega | Prankster | gen_3_families.h:9775 |
| Marshadow | Technician (its only ability here; no Soul Robber) | gen_7_families.h:7537 |
| Chandelure-Mega | Infiltrator | gen_5_families.h:10254 |
| Lunala | Shadow Shield | gen_7_families.h:6401 |
| Calyrex-Shadow | As One (Shadow Rider) | gen_8_families.h:8126 |

Stats used: Gengar-Mega 60/65/80/170/95/130, Banette-Mega 64/165/75/93/83/75, Chandelure-Mega 60/75/110/175/110/90, Lunala 137/113/89/137/107/97, Marshadow 90/125/80/90/90/125, Calyrex-Shadow 100/85/80/165/100/150.

## 5. Concerns for the owner

- **Species and ability strings.** Use `Calyrex-Shadow` and `Ability: ABILITY_AS_ONE_SHADOW_RIDER`, as above. Build and check the generated `trainers.h` entry for `SPECIES_CALYREX_SHADOW` and `ABILITY_AS_ONE_SHADOW_RIDER` before trusting it. I did not build, per the brief.
- **Shadow Tag on a perma Mega.** Works through the ordinary ability path. It is bypassed by Ghost types, Shed Shell, U-turn/Volt Switch/Flip Turn, Parting Shot, and Roar/Whirlwind, and cancels against another Shadow Tag (`B_SHADOW_TAG_ESCAPE`). Expect players to find the Ghost-type or pivot answer. That is the intended counterplay.
- **Poltergeist reliance on items.** Banette's Poltergeist fails against an itemless target (for instance after Knock Off or Thief). The shop's players hold items, but Gunk Shot is the backup if the AI runs into it.
- **Marshadow Choice Band lock.** Locked into Close Combat or Stone Edge when the AI wants a different move would be a weakness. If it looks bad in testing, swap to Life Orb and give Calyrex Choice Specs, then give Chandelure Wise Glasses or Expert Belt.
- **Difficulty.** This is a hard Elite Four: two uber legendaries (Lunala, Calyrex-Shadow, 680 BST) plus three Megas in a row against a player capped at level 50 and chipped. Calyrex at 243 Speed with Nasty Plot and Life Orb can sweep from a single free turn. Mitigation is already built in: the lead trap and Sash trade mean the player usually gets to Calyrex with a healthy team, and Lunala's Calm Mind is slow.
- **Easiest dial.** Calyrex's Nasty Plot slot: replace it with Protect or a second attack (Dark Pulse) to remove the sweep. Or drop Calyrex's level to 54 (then Lunala 53, and so on down). The second dial is Gengar's Focus Sash: swap it for Expert Belt to make the lead fall to one hit.


---

# Glacia, Elite Four (Ice), fought third

## 1. Entry

The species line is `Calyrex-Ice`, NOT `Calyrex-Ice-Rider`. The constant is `SPECIES_CALYREX_ICE` (include/constants/species.h:1321), and trainerproc just uppercases the name and swaps hyphens for underscores, so `Calyrex-Ice-Rider` would be `SPECIES_CALYREX_ICE_RIDER` and fail the build.

```
=== TRAINER_DEVON_GLACIA ===
Name: GLACIA
Class: Elite Four
Pic: Elite Four Glacia
Gender: Female
Music: Elite Four
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart Switching / Omniscient
Mugshot: Pink

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

The ability is written as the literal constant `ABILITY_AS_ONE_ICE_RIDER` because "As One" is the display name of both As One abilities (src/data/abilities.h:2119 and the Shadow Rider one), so a name lookup is ambiguous; trainerproc accepts an ABILITY_ constant directly (per the coordinator).

## 2. Team plan

**Order and levels.** Froslass 52, Abomasnow 52, Crabominable 53, Baxcalibur 53, Calyrex-Ice 54, Kyurem-White 55. Kyurem-White is the ace at 55 because it is the only member that can nuke from full health through a 4x-weak or neutral target in one hit. Calyrex-Ice is second (54): the bulkiest attacker, and a slow snowballer. The two snow setters sit at 52 and the two Defense-boosted bruisers at 53. Baxcalibur drops from 55 to 53 because it is no longer the ace.

**Weather and the Ice sub-theme.** Every member is part Ice, so snow gives the whole team +50% Defense (Gen 9 snow). Against physical attackers this is the main bulk plan. Both Mega setters have only Snow Warning (Froslass `gen_3_families.h:10929`, Abomasnow `gen_4_families.h:5801`).
- Froslass leads and sets snow on entry. Snow lasts 5 turns.
- Icy Rock goes on Abomasnow, not Froslass. Froslass is the lead and will likely be gone within 2-3 turns, so an 8-turn extension on her would mostly be wasted. Abomasnow comes in on turn ~3-5 and refreshes snow to 8 turns when the first snow is nearly spent, which also keeps Blizzard at 100% accuracy for the middle of the fight.
- Aurora Veil is on both setters. Froslass casts it on turn one (Sash guarantees she isn't one-shot first). Abomasnow recasts it when it enters, which is exactly when the first Veil has expired. Slush Rush is irrelevant (nobody has it). Blizzard accuracy matters for Froslass and Abomasnow only; the other four use accurate moves.

**Trick Room: no.** Reasons, in order of weight:
1. Three of six are fast (Froslass 195, Kyurem 177, Baxcalibur 161 at their spreads) and the plan is Veil + Froslass Blizzard + Kyurem nuke. A Trick Room set up by Calyrex would invert half the team.
2. The AI decides whether to set Trick Room only by comparing the active mon's speed to the player's (`ShouldSetFieldStatus`, `battle_ai_util.c:2207`; scoring in `battle_ai_main.c:2693` and `:5354`), with a "set it for the next Pokémon" bonus in singles. It does not look at its own back line. A Calyrex with Trick Room would fire it whenever slower than the player, which is almost always, and then follow it with Froslass.
3. The slow trio doesn't need it: they are the bulkiest members, and the Veil + snow Defense stack makes them hard to move.

The slow trio's plan is instead "out-bulk and out-damage". Crabominable and Calyrex use Brave with 0 Spe IV so that if the player brings their own Trick Room they move first, and Bulk Up / Swords Dance snowball while the player's team is chipped.

**Win conditions.** (1) Kyurem-White Choice Specs closing out the tail, with Fusion Flare covering Steel and Earth Power covering Fire/Steel. (2) Calyrex-Ice or Baxcalibur sweeping after one Swords Dance, with Chilling Neigh giving Calyrex +1 Atk per KO on top.

**Player's likely answers and the price.** Fire, Fighting, Steel and Rock all hit every Ice type. The coverage that punishes those answers: Fusion Flare (Steel), Earth Power (Fire, Steel, Poison), Close Combat and High Horsepower on Calyrex (Steel, Fire, Rock, Poison), Drain Punch and Knock Off on Crabominable, Earthquake on Baxcalibur, Will-O-Wisp on Froslass against physical Fighting/Steel attackers. Dragon types are the other common answer to Ice teams; Kyurem and Baxcalibur are Dragon too, and Kyurem's Draco Meteor trades with them. Fairies are the real wall: only Fusion Flare (Steel) and Earth Power (Poison/Steel) poke through. Bring a sweep-stopper or Fairy at your own risk.

## 3. Per-Pokémon notes

**Froslass-Mega (Lead, 52).** Spread: 252 SpA / 252 Spe, Timid, giving Speed 195 and SpA 199 at L52. 195 outspeeds a neutral-nature base-135 or a +Spe base-125 at L50; Choice Scarf and Booster Energy users still beat her, which is why she holds a Sash rather than Light Clay. Aurora Veil, Blizzard (110 BP, 100% in snow; roughly 85% of a 215-HP Garchomp, 377-444 on that calc), Shadow Ball for Ghost/Psychic, Will-O-Wisp to cripple physical sweepers. Spikes and Taunt are possible but the AI plays a lead Veil better than a lead hazard.

**Abomasnow-Mega (52).** 252 HP / 252 SpA, Quiet, 0 Atk and 0 Spe IV (0 Atk blunts Foul Play and confusion; it has no physical move; Speed is 32 and irrelevant unless the player runs Trick Room or Gyro Ball). Icy Rock refreshes snow for 8 turns. Blizzard (STAB), Giga Drain (STAB and recovery since it has no Leftovers), Earth Power (Fire, Steel, Poison, Rock answers), Aurora Veil. Wood Hammer would hit harder but the recoil plus Atk 0 makes no sense on this spread.

**Crabominable-Mega (53).** Bulk Up Iron Fist wallbreaker: Iron Fist boosts Ice Hammer (100 -> 120 BP, 90% acc, drops its own Speed, which is moot at 35 Spe), Drain Punch (75 -> 90, heals), and so snow Defense x1.5 plus Def 150 makes it a physical wall. Knock Off for Ghost/Psychic. Leftovers because Drain Punch plus Leftovers outheals chip. 252 HP / 252 Atk Brave, 0 Spe IV, for the Trick Room reason above. Ice Hammer does roughly 220-260% to a 198-HP Dragonite and Drain Punch roughly 100-115% to a Tyranitar (my calc, 252/31 neutral).

**Baxcalibur-Mega (53).** Unchanged from the current set: Jolly 252 Atk / 252 Spe, Swords Dance, Icicle Spear, Scale Shot, Earthquake, Loaded Dice. 161 Speed at L53 beats +Spe base-95 and below; Scale Shot's +1 Speed and Loaded Dice 4-5 hit Icicle Spear are the plan. Thermal Exchange gives burn immunity (stops Will-O-Wisp from the player) and +1 Atk if it is hit by a Fire move.

**Calyrex-Ice (54).** Brave 252 HP / 252 Atk, 0 Spe IV. SpA is dead weight (113). Swords Dance, Glacial Lance (120 BP Ice STAB, Atk-based; signature move, level-up 1), Close Combat and High Horsepower for Steel, Fire, Rock, Poison and Ground coverage that Ice cannot reach. Life Orb because Glacial Lance plus +2 doubles output and As One's Chilling Neigh feeds Atk; Calyrex's bulk is 222 HP / 183 Def / 162 SpD at this level, so Life Orb recoil is affordable. Trick Room is legal (teachable_learnsets.h:48112) and is the alternate fourth move in place of High Horsepower if the owner wants an actual TR-mode.

**Kyurem-White (Ace, 55).** Timid 252 SpA / 252 Spe, Choice Specs. 243 SpA and 177 Speed at L55; 177 beats +Spe base-105. Ice Beam (reliable even if snow is replaced), Draco Meteor, Earth Power, Fusion Flare. Specs Earth Power does roughly 96-113% to a 198-HP Heatran and Fusion Flare 4x on Ferrothorn is a clean OHKO. Choice Specs gives the AI a locked-move risk on Draco Meteor, but the AI handles Choice and Draco at -2 still hits hard. Turboblaze ignores abilities (Levitate, Multiscale, Flash Fire, Sturdy-like effects).

## 4. Verification

Species lines: `Froslass-Mega` = SPECIES_FROSLASS_MEGA (species.h:1650), `Abomasnow-Mega` = :1016, `Crabominable-Mega` = :1682, `Baxcalibur-Mega` = :1687, `Calyrex-Ice` = :1321, `Kyurem-White` = :1176. All six use their base species' learnset (see `.levelUpLearnset` / `.teachableLearnset` lines in species_info).

| Move | Species | File and line | How checked |
|---|---|---|---|
| Aurora Veil | Froslass | level_up_learnsets/gen_9.h:9331 (level 54) | grep MOVE_AURORA_VEIL |
| Aurora Veil | Abomasnow | level_up_learnsets/gen_9.h:11116 (level 1) | same |
| Blizzard | Froslass / Abomasnow | teachable_learnsets.h:23634 / :28281 | awk on `sXTeachableLearnset[]` block |
| Shadow Ball | Froslass | teachable_learnsets.h:23657 | same |
| Will-O-Wisp | Froslass | teachable_learnsets.h:23670 | same |
| Giga Drain | Abomasnow | teachable_learnsets.h:28294 | same |
| Earth Power | Abomasnow / Kyurem | teachable_learnsets.h:28288 / :36836 | same |
| Bulk Up | Crabominable | teachable_learnsets.h:41601 | same |
| Ice Hammer | Crabominable | level_up_learnsets/gen_9.h:16841 (level 37); `punchingMove = TRUE` at moves_info.h ~16781 | grep |
| Drain Punch | Crabominable | teachable_learnsets.h:41605; `punchingMove = TRUE` ~11096 | same |
| Knock Off | Crabominable | teachable_learnsets.h:41619 | same |
| Swords Dance, Icicle Spear, Scale Shot, Earthquake | Baxcalibur | teachable_learnsets.h:51380 / :51368 / :51375 / :51362 | same |
| Glacial Lance | Calyrex-Ice | level_up_learnsets/gen_9.h:19879 block (level 1, first entry) | read block |
| Swords Dance, Close Combat, High Horsepower | Calyrex-Ice | teachable_learnsets.h:48109 / :48076 / :48084 | same |
| Ice Beam, Draco Meteor | Kyurem | teachable_learnsets.h:36843 / :36830 (`sKyuremTeachableLearnset`, used by Kyurem-White at gen_5_families.h:13532) | same |
| Fusion Flare | Kyurem-White | level_up_learnsets/gen_9.h:14821 (level 48) | grep |

| Ability | Species | species_info line |
|---|---|---|
| Snow Warning (only ability) | Froslass-Mega | gen_3_families.h:10929 |
| Snow Warning (only ability) | Abomasnow-Mega | gen_4_families.h:5801 |
| Iron Fist (only ability) | Crabominable-Mega | gen_7_families.h:1524 |
| Thermal Exchange (only ability) | Baxcalibur-Mega | gen_9_families.h:6613 |
| As One (ABILITY_AS_ONE_ICE_RIDER, only ability) | Calyrex-Ice | gen_8_families.h:8058 |
| Turboblaze (only ability) | Kyurem-White | gen_5_families.h:13529 |

Items are all distinct: Focus Sash, Icy Rock, Leftovers, Loaded Dice, Life Orb, Choice Specs. Snow Warning gives snow (not hail) via `B_SNOW_WARNING = GEN_LATEST` (include/config/battle.h:335).

## 5. Concerns for the owner

- **Species and ability names:** the party line is `Calyrex-Ice` and the ability line is the literal `ABILITY_AS_ONE_ICE_RIDER`; the build should be run once to confirm trainerproc accepts both.
- **Weakness overlap:** all six are part Ice, so Fire, Fighting, Rock and Steel hit the whole team. The fix is coverage on the team (Fusion Flare, Earth Power, High Horsepower, Close Combat, Drain Punch), but a player with a Fairy plus a strong Fire or Fighting attacker will get far. Abomasnow is 4x weak to Fire.
- **Snow Defense boost:** make sure the engine's snow Defense bonus is on for all Ice types (it is Gen 9 behaviour via `B_SNOW_WARNING` / GEN_LATEST); if it is not, the slow trio loses its main bulk.
- **Ace choice:** Choice Specs Kyurem-White hits very hard; if too hard, move it to Life Orb. The new team is notably stronger offensively than the old one (Chien-Pao and Iron Bundle are gone).
- **Easiest dial:** drop Aurora Veil from Abomasnow (swap for Ice Shard or Shadow Ball) and change Kyurem's Choice Specs to Life Orb; second, shift every level down one. If too easy, put Light Clay on Froslass instead of Focus Sash and raise the AI-visible risk to the player's lead.
- **Z-A Mega engine risk:** Froslass-Mega, Crabominable-Mega and Baxcalibur-Mega are the newer Z-A Megas. Froslass-Mega and Baxcalibur-Mega are already used on the live team, so their sprites/abilities are proven; Crabominable-Mega and Abomasnow-Mega are not yet used by any trainer entry in this repo (Abomasnow-Mega is a Gen 6 Mega, not Z-A). Test Crabominable-Mega's front/back sprite and its Iron Fist boost headlessly once.


---

# Drake, Elite Four (Dragon), levels 52-55

## 1. Entry (paste over the current `=== TRAINER_DEVON_DRAKE ===` block; header unchanged)

```
=== TRAINER_DEVON_DRAKE ===
Name: DRAKE
Class: Elite Four
Pic: Elite Four Drake
Gender: Male
Music: Elite Four
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart Switching / Omniscient
Mugshot: Blue

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

(The `/* Ten Gauntlets ... */` comment after the entry stays as is.)

## 2. Team plan

**Order and levels.** Feraligatr 52, Charizard X 52, Garchomp Z 53, Dragonite 53, Eternatus 54, Koraidon 55. The rising level ladder is also a rising threat ladder: two setup sweepers first, the 151-Speed revenge killer in the middle, the Multiscale bruiser, the second boss (Eternatus), then the ace.

**Ace: Koraidon at 55, not Dragonite.** Mega Dragonite has the higher BST (700 vs 670), but its strength is Multiscale plus Dragon Dance, and both are *conditional*: Multiscale is gone after one hit, and Dragon Dance needs a free turn that a level-50 team with perfect EVs will often deny (phazing, Haze, Encore, or just a fast Mega doing 50%). Koraidon needs no turn: it enters, the sun is up, and Choice Band + Orichalcum Pulse (x1.333 Atk) gives it about 410 Atk at 55 for a 135-Speed body, with no setup the player can exploit. It also gives the fight a distinct finale instead of a sixth DD mon. Dragonite stays one level back at 53 because Multiscale already inflates its effective bulk for free.

**Speed.** Jolly Koraidon is 225 at 55, which outspeeds every unboosted, unscarfed player Pokemon up to base 151 with a Speed nature (223 at level 50, the Mega Garchomp Z benchmark). Only Scarf users and base 160+ (Deoxys-Speed, Regieleki) pass it. Garchomp Z is 235 at 53.

**Win conditions.** (1) Dragon Dance chain in the front half: Feraligatr (+1 = 202 Spe, outspeeds up to base 130 with a Speed nature), Charizard X (+1 = 235), Dragonite (+1 = 240). (2) The back half is pure frontal damage: Eternatus (SpA 212 with Recover) and Koraidon (Band + sun).

**Coverage across the six.** Dragon-only attacks are walled by Steel and are *immune* on Fairy. Answers in the team: Fairy gets Flare Blitz (Charizard, Koraidon), Sludge Bomb (Eternatus), Fire Blast (Garchomp), Extreme Speed/Earthquake (Dragonite, Feraligatr). Steel gets Earthquake (Feraligatr, Garchomp, Dragonite) and every Fire move (Flare Blitz, Flamethrower, Fire Blast). Ice and Dragon, the real Dragon weaknesses, are covered by Rock/Ground/Fire coverage and by Extreme Speed to finish at low HP. Weather ordering is deliberate: Koraidon's sun halves Water, which would hurt Feraligatr's Waterfall, so Feraligatr leads and Koraidon is last. Feraligatr's Dragonized Double-Edge is unaffected by sun anyway.

**Likely player answers and the price.** Fairy Megas and Fairy legends (Moonblast into any of the front four, since all are Dragon) are the obvious plan: Charizard X's Weakness Policy turns a super-effective Fairy hit into a +2/+2 DD Zard, and Dragonite's Boots keep Multiscale if they set Stealth Rock first. Ice Beam / Icicle Crash into Dragonite (4x) is the other plan: Multiscale only holds if Dragonite is at full HP, so use it as the 4th slot after Garchomp has chipped, not first. Steel walls (Mega Scizor, Aegislash, Ferrothorn) die to Earthquake/Fire. Phazing/Haze answers the DD trio and does nothing to Eternatus or Koraidon, which is the point of ending on two non-setup threats.

## 3. Per-Pokemon notes

**Mega Feraligatr (52, lead).** Water/Dragon, 160 Atk / 125 Def, but only 78 base Speed, so I put the full 252 into Speed rather than HP (Spe 135, +1 = 202, which beats every non-Scarf player Mega below base ~130 with nature; HP 167). Dragonize turns Normal into Dragon with the 1.2x boost, so Double-Edge is a Dragon-STAB 120 BP move (about 216 effective BP before the Attack stat), which is why it carries Double-Edge and not Outrage (it does not learn Outrage anyway). Waterfall is Water STAB for Fire/Ground/Rock, Earthquake handles Steel/Electric/Poison. Lum Berry shrugs off the Thunder Wave/Will-O-Wisp/Toxic that a level-50 player will throw at a slow setup lead. Items: Lum, unique.

**Mega Charizard X (52).** Fire/Dragon, 130 Atk, Tough Claws (x1.3 on contact). Flare Blitz + Dragon Claw are both contact, both boosted, and hit nearly everything (Fire is the answer to Steel/Fairy/Ice/Grass; Dragon Claw to everything else). Roost gives it staying power across DD turns. Adamant, 157 Speed (+1 = 235). Weakness Policy: its weaknesses are Rock/Ground/Dragon/Fairy x2, exactly the moves the player will use to answer a Dragon, and the AI cannot play around it. Replace with Leftovers if it feels too swingy.

**Mega Garchomp Z (53).** Kept from the current entry (Levitate, Dragon, 151 Speed / 141 SpA / 130 Atk). Naive Life Orb with 252 SpA / 252 Spe: Speed 235 outspeeds the whole player pool; Draco Meteor for burst, Fire Blast for Steel/Fairy/Ice, Earthquake and Stone Edge on the weaker Attack for Steel/Rock/Flying coverage. It is the cleanup piece for the chip the DD sweepers leave.

**Mega Dragonite (53).** Dragon/Flying, 91/115/125 bulk, 100 Speed (Adamant 252/252: Atk 204, Spe 160, +1 = 240). I kept it physical even though SpA is 145: it avoids stacking a fourth special attacker, it has Extreme Speed (the team's priority move, beats Scarf users and finishes after Garchomp's chip), and Hurricane is 50% accurate under Koraidon's sun. Dragon Dance / Outrage / Extreme Speed / Earthquake. Earthquake is the Steel/Fire answer; Outrage is deliberate even with its lock because with DD it is the highest-damage move (a Fairy switch-in can punish it, which is the player's reward for reading the AI). Heavy-Duty Boots because Stealth Rock does 25% to Dragon/Flying and would strip Multiscale on entry.

**Eternatus (54, second-strongest).** Poison/Dragon, 140/95/95, 145 SpA, 130 Speed. Timid 252/252: Speed 215 (beats base 140 with nature, 211) and SpA 212. Poison STAB is the Fairy answer, which also makes it the one Dragon on the team that Fairies cannot wall. Dynamax Cannon (100 BP Dragon, 100% accuracy, no drawback) replaces Draco Meteor so the AI cannot spam itself to -4; Flamethrower for Steel; Recover so it lasts long enough to matter. 0 Atk IV to blunt Foul Play and confusion. Leftovers for passive recovery.

**Koraidon (55, ace).** Fighting/Dragon, 135 Atk / 135 Spe. Jolly 252/252: Atk 205 (x1.333 sun x1.5 Band = about 410), Spe 225. Collision Course (100 BP Fighting, x1.3 on super-effective, no Close Combat drop, which matters when Band-locked), Flare Blitz (x1.5 in its own sun, the Steel/Fairy/Ice answer), Dragon Claw (Dragon neutral, the Fighting-resisters), U-turn so a Band lock into a bad matchup has an exit the AI can use. Rough benchmark: Collision Course on a neutral 100/100 level-50 Mega (207 HP, 152 Def) does about 88% on average, a clean 2HKO and an OHKO when super-effective.

## 4. Verification

All checked in `/home/dillo/decomps/pokeemerald-expansion`. Learnsets: `src/data/pokemon/level_up_learnsets/gen_9.h` (LU) and `src/data/pokemon/teachable_learnsets.h` (T). Mega forms point to the base species' learnsets (species_info `.levelUpLearnset`/`.teachableLearnset` lines in the table below).

| Item | Source |
|---|---|
| Species constants | `include/constants/species.h`: `SPECIES_GARCHOMP_MEGA` (947, older Mega) and `SPECIES_GARCHOMP_MEGA_Z` (1558, Z-A) both exist; I used `Garchomp-Mega-Z` as the current entry does. `SPECIES_DRAGONITE_MEGA` 1527, `SPECIES_FERALIGATR_MEGA` 1529, `SPECIES_CHARIZARD_MEGA_X` 907, `SPECIES_ETERNATUS` 890, `SPECIES_KORAIDON` 1400 |
| Learnset pointers (Mega = base) | `gen_1_families.h:20558-20559` (Dragonite-Mega), `:662-663` (Charizard-Mega-X), `gen_2_families.h:851-852` (Feraligatr-Mega), `gen_4_families.h:4586-4587` (Garchomp-Mega-Z) |
| Ability Multiscale (Dragonite-Mega) | `gen_1_families.h:20523` (`{MULTISCALE x3}`; Z-A Dragonite kept Multiscale in this repo, no new ability) |
| Ability Tough Claws (Charizard-Mega-X) | `gen_1_families.h:611` |
| Ability Dragonize (Feraligatr-Mega) | `gen_2_families.h:817`; effect in `src/battle_util.c:6642` (x1.2 boost) and `src/battle_main.c:5570` (Normal to Dragon) |
| Ability Levitate (Garchomp-Mega-Z) | `gen_4_families.h:4551` |
| Ability Pressure (Eternatus) | `gen_8_families.h:7138` |
| Ability Orichalcum Pulse (Koraidon) | `gen_9_families.h:7262`; sets sun on entry (`battle_util.c:3354`), Atk x1.3333 in sun for physical moves (`battle_util.c:7022`); sun lasts 5 turns, 8 with Heat Rock |
| Feraligatr: Dragon Dance, Waterfall, Double-Edge | T `teachable_learnsets.h:12346` (DD), `:12387` (Waterfall), `:12391` (Double-Edge) |
| Feraligatr: Earthquake | T in `sFeraligatrTeachableLearnset` (`teachable_learnsets.h:12336` block) |
| Charizard: Dragon Dance, Roost | T `:506` (DD), `:537` (Roost) |
| Charizard: Flare Blitz, Dragon Claw | LU `gen_9.h:117` (Flare Blitz lvl 62), `:109` (Dragon Claw lvl 1) |
| Garchomp: Draco Meteor, Earthquake, Fire Blast, Stone Edge | T `teachable_learnsets.h:27622`, `:27627`, `:27630`, `:27654` |
| Dragonite: Dragon Dance, Extreme Speed, Outrage | LU `gen_9.h:4634` (DD lvl 62), `:4618` (ES lvl 1), `:4631` (Outrage lvl 41) |
| Dragonite: Earthquake | T `teachable_learnsets.h:11498` |
| Eternatus: Dynamax Cannon, Flamethrower, Recover | LU `gen_9.h:19681` (lvl 56), `:19680` (lvl 48), `:19683` (lvl 72); Dynamax Cannon is a normal 100 BP Dragon special move (`src/data/moves_info.h:18327`, `EFFECT_DYNAMAX_DOUBLE_DMG`), usable without Dynamax |
| Eternatus: Sludge Bomb | T `teachable_learnsets.h:47672` |
| Koraidon: Collision Course, Flare Blitz, Dragon Claw | LU `gen_9.h:21981` (lvl 56), `:21986` (lvl 91), `:21979` (lvl 42) |
| Koraidon: U-turn | T `teachable_learnsets.h:51746` |
| Items | all exist (`include/constants/items.h`: Lum Berry 522, Weakness Policy 502, Heavy-Duty Boots 510, Choice Band 442; Life Orb, Leftovers standard). Six different items, item clause satisfied |

Stat numbers above come from the level-50-formula calculator I ran with 31 IVs and the listed EVs/natures (Fer Spe 135, Char Spe 157, Garchomp Spe 235, Dragonite Spe 160, Eternatus Spe 215, Koraidon Spe 225); the player Speed benchmarks use 252 EV, 31 IV at level 50 (base 130 = 182/200, base 135 = 187/205, base 151 = 203/223).

## 5. Concerns for the owner

- **Brief correction.** Sun does not "help Charizard X not at all": it boosts Flare Blitz 1.5x. It is moot here because Koraidon is slot 6 and Charizard is slot 2; only relevant if you reorder. The real sun interaction is that Koraidon's sun halves *Water*, which is why Feraligatr leads.
- **Koraidon difficulty.** Band + sun + 135 Speed against level-50 Pokemon is a lot of damage; expect it to remove one Pokemon per turn. If it is too hard: change Choice Band to Sitrus Berry (the single easiest dial), or drop it to level 54.
- **Three Dragon Dance users** (Feraligatr, Charizard, Dragonite). Haze/Roar/Whirlwind/Unaware answers all three. If that feels repetitive, swap Charizard's Dragon Dance for Swords Dance/Earthquake, or give Dragonite the special set (Hurricane / Draco Meteor / Fire Blast / Roost).
- **AI.** Outrage can lock Dragonite into a Fairy, and Choice Band can lock Koraidon; I included U-turn on Koraidon as an exit and left Outrage as a possible win for the player. Weakness Policy and Lum Berry are triggered passively. Nothing here relies on prediction.
- **Engine.** Every ability and move is already implemented in this expansion (checked above). Z-A Mega Dragonite's ability is plain Multiscale here, no engine risk. The 4-Mega species need their Mega sprites and cries, which exist (`gMonFrontPic_DragoniteMega` etc.); I did not build.
- **Weakness Policy** on Charizard X is the swingiest item; Leftovers is the safe replacement.


---

# Maxie, New Mauville: sun, Primal Groudon at level 65

## 1. Entry (paste over the current `TRAINER_NEW_MAUVILLE_MAXIE` block)

```
=== TRAINER_NEW_MAUVILLE_MAXIE ===
Name: MAXIE
Class: Magma Leader
Pic: Magma Leader Maxie
Gender: Male
Music: Magma
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart Switching / Omniscient

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

Items: Leftovers, Life Orb, Air Balloon, Assault Vest, Focus Sash, Heavy-Duty Boots. No repeats.

## 2. Team plan

**Lead and the weather war.** Groudon-Primal leads. The new point is the lead turn. Switch-in abilities resolve fastest-first (`DoSwitchInEvents` sorts `gBattlersBySpeed`, src/battle_switch_in.c), so the SLOWEST Primal or Delta Stream on the field resolves last and keeps the weather. The player knows Maxie leads Groudon, so the obvious answer is to lead their own Primal Kyogre. Groudon is therefore built SLOW: Brave nature and 0 Spe IV with no Speed EVs give Speed 109 at level 65. A level-60 base-90 Kyogre-Primal is at least 131 with a neutral nature and no EVs, or 117 with a Speed-minus nature, so Groudon's Desolate Land lands last and Kyogre's Water moves fail from turn one. The cost is that Groudon moves second against nearly everything. It has 266 HP, 274 Def and Leftovers, so that is affordable. Desolate Land also forbids Kyogre's Origin Pulse and Surf, which is most of its offense.

**Win condition 1: Groudon under Desolate Land.** Swords Dance (+2 Atk, 330 Atk with Brave) then Earthquake, Stone Edge and Fire Punch (STAB, sun-boosted). Water moves fail while it lives, so its 4x Water weakness is hidden. It is the only member that wins by staying in.

**Win condition 2: sun after Groudon falls.** Groudon's Desolate Land clears when it leaves or faints (`BS_TryToClearPrimalWeather`, battle_script_commands.c:11809). Charizard-Mega-Y's Drought then sets ordinary sun when it comes in. Charizard is slot 2 so it is also the fallback if the AI follows party order. Drought only fires on switch-in, so if the AI sends Heatran or Blaziken after Groudon there is no weather until Charizard enters. Every other member is built to be fine in no weather:
- Reshiram, Heatran and Ho-Oh are bulky and hit hard without sun.
- Blaziken needs no weather, because Speed Boost is its engine.

**How the pieces cover each other.**
- Rock and Ground: Charizard's Solar Beam and Reshiram's Solar Beam and Earth Power hit what resists Fire. Ground attackers are blanked by Heatran's Balloon, and Ho-Oh's Earthquake handles Rock and Steel.
- Water: Solar Beam (two members) and Blaziken's Thunder Punch (2x on Kyogre and Gyarados).
- Dragon and Rayquaza: Reshiram's Draco Meteor.
- Psychic and Ghost: Heatran's Dark Pulse.
- Flying: Groudon's Stone Edge, plus Reshiram and Heatran as neutral hitters.
- Bulk is spread across the team. Groudon is the physical tank, Heatran and Reshiram (Vest) are the special tanks, and Ho-Oh is the Regenerator pivot.

**Counterplay and how the team makes it pay.**
- *Primal Kyogre.* Leading it loses the weather war, as above. The real answer is to hold it and switch it in later, since a Kyogre switching in AFTER Groudon replaces Desolate Land with Primordial Sea. All Fire moves then fail, and Groudon takes 4x Water in rain, which usually OHKOs it. The team still functions under Primordial Sea, because everyone has non-Fire damage:
  - Groudon has Earthquake and Stone Edge.
  - Heatran has Earth Power, Flash Cannon and Dark Pulse.
  - Reshiram has Draco Meteor and Earth Power.
  - Blaziken has Close Combat and Thunder Punch.
  - Ho-Oh has Brave Bird and Earthquake.
  - Charizard is the weakest here (Focus Blast is its only live attack), and Drought cannot return while Primordial Sea holds.
- *Mega Rayquaza.* The mega is a normal Mega Evolution, so it happens mid-battle and Delta Stream replaces Desolate Land. The Water ban lifts and Groudon's 4x weakness is exposed. Reshiram's Draco Meteor (Dragon is 2x on Rayquaza) is the dedicated check, with Heatran's Flash Cannon neutral and fast enough to matter at 322 SpA. Delta Stream also removes Flying's Rock weakness, so Charizard and Ho-Oh take 2x from Rock instead of 4x. This is a small gift worth noting.
- *Cloud Nine (any mon, since the player picks abilities).* `HasWeatherEffect()` returns FALSE with Cloud Nine or Air Lock on the field, so both Desolate Land's Water-failure check (`CancelerWeatherPrimal`) and sun's Fire boost switch off. Water moves hit Groudon at 4x with no weather protection, and Solar Beam needs a charge turn. This is the hardest counter and cannot be fixed with a moveset. The AI is Omniscient and Smart Switching, so it should pull Groudon out. Everything else on the team is a normal-damage Pokemon with real bulk, so the fight becomes a stat check the team can still win.
- *Stealth Rock.* Charizard and Ho-Oh are 4x weak to Rock. Ho-Oh holds Boots because it pivots (Regenerator) and re-enters repeatedly. Charizard enters once, usually on a faint.

## 3. Per-Pokemon notes

**Groudon-Primal (lead, Leftovers, Brave 252 HP / 252 Atk / 4 SpD, 0 Spe IV).** Role: weather setter and Swords Dance sweeper. Speed 109 is intentionally below every plausible player Kyogre-Primal (see the weather war above), and Groudon wins the lead on bulk (266 HP / 274 Def) rather than speed. Earthquake replaced Precipice Blades (85% accuracy) for reliability: expected damage is equal and a boss fight should not turn on a miss. Stone Edge is for Flying and Rayquaza and Fire Punch is for Grass and Steel. Under Desolate Land Fire Punch is STAB x sun. If Primordial Sea ever overrides, the AI sees Fire Punch as dead and Check Bad Move will skip it.

**Charizard-Mega-Y (Life Orb, Timid 252 SpA / 252 Spe).** Role: the sun sweeper and the Drought backup. 272 SpA and 196 Speed are above most level-60 players without a Scarf. Fire Blast is sun-boosted, Solar Beam is instant in sun and hits Water, Rock and Ground, and Focus Blast covers the Rock and Steel that resist Fire. Roost keeps a 237 HP Pokemon in the fight so it can reset. I avoided a Choice item deliberately: a locked Fire Blast under Primordial Sea would waste the turn. Life Orb recoil is an acceptable price, and Roost offsets it.

**Heatran-Mega (Air Balloon, Modest 252 HP / 252 SpA / 4 SpD).** Role: special tank and Steel-hitter, 322 SpA. Base Speed 67 gives only 112, so it moves last and is Balloon-protected from the Ground 4x weakness that is its only real liability. Magma Storm (sun-boosted, traps) removes the player's switch-out, Earth Power and Flash Cannon (Ice, Fairy, Rock) are the coverage, and Dark Pulse is the answer to Psychic and Ghost, the standard Heatran walls. Taunt is gone (this is a stat-check boss, not a stall team). Flash Fire gives immunity to Fire, which matters if the player has Fire coverage of its own.

**Reshiram (Assault Vest, Modest 252 HP / 252 SpA / 4 SpD).** Role: the Dragon check and bulky special wall. 333 SpD with the Vest and 266 HP means a level-60 Primal Kyogre's boosted Origin Pulse does roughly 100 to 120 damage, and Reshiram still threatens. Blue Flare (130 BP) is sun-boosted. Draco Meteor handles Rayquaza and Latios. The Vest rules out Roost (which Reshiram does learn); I chose passive bulk over recovery so all four slots are attacks. Turboblaze ignores abilities such as Water Absorb, Levitate and Thick Fat.

**Blaziken-Mega (Focus Sash, Jolly 252 Atk / 252 Spe).** Role: late-game Speed Boost cleaner. Speed Boost is permanent from turn one, so 215 at +0 becomes 322 after the first turn and 430 after the second, outrunning all but Scarf users after one turn. Focus Sash guarantees at least one Speed Boost turn when it enters on a faint with full HP. Swords Dance gives it a second gear, Flare Blitz (sun-boosted) and Close Combat are the STABs, and Thunder Punch is for Water and Flying walls (2x on Kyogre and Gyarados). Knock Off is the fallback if Thunder Punch feels unneeded.

**Ho-Oh (Heavy-Duty Boots, Adamant 252 HP / 252 Atk / 4 Def, Regenerator).** Role: Regenerator pivot and endgame tank, 273 HP and 266 SpD. Sacred Fire (100 BP, 95% accuracy, 50% burn, sun-boosted) and Brave Bird are the STABs, Earthquake hits Rock, Steel and Electric, and Recover keeps the loop going. Boots because Ho-Oh is 4x weak to Rock and re-enters often. Sunny Day (level-up 72) was considered as a sun backup but there is no free slot.

## 4. Verification

Abilities, all in `src/data/pokemon/species_info/`:

| Species | Ability used | Line |
|---|---|---|
| Groudon-Primal | Desolate Land | gen_3_families.h:12996 |
| Charizard-Mega-Y | Drought | gen_1_families.h:685 |
| Heatran-Mega | Flash Fire (slot 1; hidden slot is Flame Body) | gen_4_families.h:6983 |
| Reshiram | Turboblaze | gen_5_families.h:13145 |
| Blaziken-Mega | Speed Boost (all three slots) | gen_3_families.h:573 |
| Ho-Oh | Regenerator (hidden slot) | gen_2_families.h:8648 |

Moves, level-up (gen_9, which `P_LVL_UP_LEARNSETS` selects in pokemon.c:748) and teachable (src/data/pokemon/teachable_learnsets.h). The Mega and Primal forms point at the base species' learnsets (species_info lines: Groudon-Primal gen_3:12979+, Charizard-Mega-Y gen_1:737, Heatran-Mega gen_4:7019, Blaziken-Mega gen_3).

| Species | Move | Where |
|---|---|---|
| Groudon | Swords Dance, Earthquake, Fire Punch, Stone Edge | teachable_learnsets.h:24725, 24687, 24692, 24721 (Earthquake also level-up, gen_9.h:9741) |
| Charizard | Fire Blast, Solar Beam, Focus Blast, Roost | teachable_learnsets.h:512, 543, 519, 537 |
| Heatran | Magma Storm | level-up, gen_9.h:11293 (L72) |
| Heatran | Earth Power, Flash Cannon, Dark Pulse | teachable_learnsets.h:28718, 28726, 28714 |
| Reshiram | Blue Flare | level-up, gen_9.h:14741 (L88) |
| Reshiram | Draco Meteor, Earth Power, Solar Beam | teachable_learnsets.h:36640, 36646, 36678 |
| Blaziken | Swords Dance, Flare Blitz, Close Combat, Thunder Punch | teachable_learnsets.h:17778, 17750, 17739, 17781 |
| Ho-Oh | Sacred Fire, Recover | level-up, gen_9.h:6819, 6818 |
| Ho-Oh | Brave Bird, Earthquake | teachable_learnsets.h:17312, 17318 |

The grep used for teachable lines: find `static const u16 s<Species>TeachableLearnset`, then the first `MOVE_X,` after it.

Engine checks done: `CancelerWeatherPrimal` (battle_move_resolution.c:1095) fails Water under sun-primal and Fire under rain-primal only for moves with power above 0 and only if `HasWeatherEffect()` (battle_util.c:10072, false with Cloud Nine or Air Lock). `TryChangeBattleWeather` (battle_util.c:2061) lets any of the three strong-weather abilities override another, and blocks all ordinary weather while a strong weather is up.

## 5. Concerns for the owner

- **Weather-war speed trick is untested.** It relies on `SortBattlersBySpeed` being fastest-first and the slowest Primal's weather landing last. A headless test with Kyogre-Primal vs Groudon-Primal at the lead would confirm it in one run. If the owner does not like how it plays, see the dial below.
- **Drought is not a guaranteed backup.** It fires only when Charizard-Mega-Y switches in after Groudon is gone. The order of mons is the soft control (Charizard is slot 2) but Smart Mon Choices may pick otherwise. Check in a test that Charizard replacing a fainted Groudon actually sets sun (the clear script runs before the switch-in abilities, so it should).
- **Heatran-Mega's ability.** The repo lists Flash Fire (slot 1) and Flame Body (hidden). I used Flash Fire. If the Z-A data is wrong in this repo, the line to check is gen_4_families.h:6983.
- **Z-A and newer Megas.** Confirm that the trainer parser accepts `Heatran-Mega`, `Charizard-Mega-Y` and `Blaziken-Mega`. The existing trainers.party has `Camerupt-Mega`, `Gengar-Mega` etc., so the naming pattern is established.
- **Cloud Nine is the hard counter and cannot be fixed by moveset.** Water attackers with Cloud Nine hit Groudon at 4x. This is accepted design, and the AI should switch Groudon out (Omniscient sees the set).
- **Difficulty.** The team is heavy on Fire; the Primal Kyogre switch-in is the strongest plan against it and the player must find it. Expect the fight to be hard in the first four turns and easier once Groudon falls without Drought.
- **Easiest dial:** Groudon's Speed. The 0 Spe IV Brave Groudon is the harder version: it wins the lead weather war against any Kyogre-Primal. Switching to Adamant with the IV at 31 (Speed 142) makes it faster than a low-Speed Kyogre, so Kyogre's Primordial Sea would land last on a lead-vs-lead start and the fight gets much easier. The finer dial is Swords Dance: swap it for Rock Polish or Fire Blast to remove the setup threat.


---

# Archie, New Mauville: rain, Primal Kyogre, level 65

## 1. Entry (replaces the current `=== TRAINER_NEW_MAUVILLE_ARCHIE ===` block; header lines unchanged)

```
=== TRAINER_NEW_MAUVILLE_ARCHIE ===
Name: ARCHIE
Class: Aqua Leader
Pic: Aqua Leader Archie
Gender: Male
Music: Aqua
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Smart Switching / Omniscient

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

Items are all distinct (Leftovers, Assault Vest, Choice Band, Life Orb, Choice Specs, Heavy-Duty Boots). No IVs line anywhere: nothing wants less than 31. Knock Off appears on two mons; that is a move, not an item, so the clause does not apply.

## 2. Team plan

**Lead.** Primal Kyogre, as fixed. Primordial Sea makes every Fire move fail outright (the player's Fire Megas lose their STAB and their coverage) and boosts all five Water attackers behind it. Kyogre itself is the stall-and-snowball piece: 100/90/160 bulk with Leftovers, one Calm Mind turns it into something the player's level-60 party cannot break without a Primal or a Fire/Electric-neutral answer. Origin Pulse and Thunder (never misses in rain) are the real damage; Ice Beam is the Grass/Dragon cover.

**Win conditions.** (1) Rain snowball: Kyogre Calm Mind, then Swampert at 314 Speed in rain (Choice Band Waterfall flinch lock plus Earthquake) and Starmie with its doubled Attack. (2) Raw stat checks that do not care about weather: Mega Starmie (Huge Power, ~390-430 Attack) and Mega Greninja (275 Speed, ~358 Specs SpA) both outspeed nearly everything at level 60-70 and neither needs rain.

**Cover.** Kyogre is Water only (weak to Electric and Grass); Lugia (Flying/Psychic) takes those hits and resets with Multiscale. Golisopod (Bug/Steel, 4x weak to Fire only) is the physical wall that is entirely safe while Primordial Sea is up and turns into a liability the moment it ends, so it is placed second to be live while rain lasts. Starmie covers Fighting/Poison, Greninja's Dark Pulse covers Psychic/Ghost, Swampert's Ice Punch/Knock Off cover Flying/Grass/Dragon/Ghost.

**What happens after Kyogre falls.** The weather is simply gone (Primordial Sea ends with its holder; there is no second weather setter and I deliberately did not spend a slot on Lugia's Rain Dance, which also fails against Desolate Land and Delta Stream). Swift Swim switches off, so Swampert drops to 157 Speed: it is still a Mega Swampert (150 Atk / 110 / 110 bulk) with Choice Band, but it is no longer first. Starmie, Greninja, Lugia and Golisopod lose almost nothing; their Water moves just lose the 1.5x. That is intentional: the back five do not depend on rain, only Swampert does.

**Against the player's weather answers.**
- Primal Groudon (Desolate Land replaces rain): every Water move on the team fails while it is on the field, and Fire hits 1.5x, so Golisopod's 4x weakness is the exposed one. Each of the back five has a live non-Water move: Swampert Earthquake/Ice Punch/Knock Off, Starmie Zen Headbutt/Rapid Spin, Greninja Dark Pulse/Ice Beam/Grass Knot, Golisopod First Impression/Leech Life/Knock Off, Lugia Aeroblast/Psychic. Kyogre is the one that suffers (Thunder cannot touch Ground, only Ice Beam works); that is the mirror-match price and the thematic one.
- Mega Rayquaza (Delta Stream): Water is no longer boosted or the failure removed, but Lugia loses its Rock/Electric/Ice weaknesses, and Greninja/Starmie do not care. Fine.
- Player's own Kyogre-Primal is just the same weather; no change.

## 3. Per-Pokemon notes

**Kyogre-Primal @ Leftovers, Modest 252 HP / 252 SpA / 4 SpD.** Lead and Calm Mind sweeper. Stats at 65: 266 HP, 330 SpA (Modest), 233 SpD, 142 Speed (slower than a level-60 base-100 neutral, which is why it is a bulk piece, not a speed piece). Origin Pulse (110 BP, 85%) over Surf is the owner's original call; Thunder is perfect-accuracy in rain; Ice Beam is Grass/Dragon coverage; Leftovers kept as asked.

**Golisopod-Mega @ Assault Vest, Adamant 252 HP / 252 Atk / 4 Def.** Mega Golisopod has only Tough Claws, no Emergency Exit, so it is built as a tank, not a Wimp Out pivot. Def 253 and SpD 271 with the Vest (176 base x1.5), HP 233, Atk 287. Every attack is contact and gets 1.3x: First Impression (priority, fires every switch-in, covers its 40 base Speed), Liquidation (1.5x in rain), Leech Life (the only recovery; the Vest rules out Swords Dance and similar status moves), Knock Off for Psychic/Ghost and item removal. Assault Vest over Rocky Helmet: the player's team is mostly special attackers, and a Vest tank with Leech Life is the stickiest thing I can build with no status moves.

**Swampert-Mega @ Choice Band, Adamant 4 HP / 252 Atk / 252 Spe.** Rain sweeper: 157 Speed becomes 314 under Swift Swim, outspeeding any level-65 base-150 neutral (287 at best). Attack 287, 430 under Band. Waterfall (flinch, with the rain Speed advantage it lock-flinches slower targets), Earthquake and Ice Punch for Electric/Steel and Flying/Grass/Dragon, Knock Off for Ghost/Psychic. Hits harder than any other piece when rain is up, and is deliberately the piece that is merely decent when rain is not. Stealth Rock and Superpower were left out to keep the 4-move set simple for the AI.

**Starmie-Mega @ Life Orb, Jolly 4 HP / 252 Atk / 252 Spe.** Huge Power with 100 base Attack: 196 raw (Jolly does not touch Attack) becomes 392, and Speed 244, past a neutral level-65 base-130 (235). Liquidation and Zen Headbutt are its two STABs and almost all its pressure; Recover keeps Life Orb bearable; Rapid Spin is the AI-friendly utility slot (removes Stealth Rock, now also +1 Speed per hit in this repo) and doubles as a chip move at 392 Attack. Fragile (HP 173), so the AI tends to bring it as revenge killer, not lead.

**Greninja-Mega @ Choice Specs, Timid 4 HP / 252 SpA / 252 Spe.** Speed 275 (base 142), SpA 239 raw, 358 with Specs. Protean is once per battle in this repo (B_PROTEAN_LIBERO is GEN_LATEST, include/config/battle.h:211), so I built around it: Greninja is already Water/Dark, so Surf and Dark Pulse are STAB regardless, and the single Protean use goes to Ice Beam or Grass Knot. Grass Knot (weight based) kills legendary-heavy targets: 120 BP into Primal Groudon/Kyogre-class weights, Water/Ground/Rock walls, and it is a non-Water answer through Desolate Land. Not Nasty Plot, because Choice Specs has no lock problem here (Surf is the only move that fails to Groudon, and the AI's Check Bad Move will not select it into a failing weather).

**Lugia @ Heavy-Duty Boots, Modest 252 HP / 252 SpA / 4 SpD.** Last piece and the anchor. Stats at 65: HP 273, Def 194, SpD 225 (+1 Calm Mind is 337), SpA 201. Multiscale halves the first hit, Roost resets it, Aeroblast (100 BP, high crit, Flying STAB) is the main attack and Psychic is the coverage. Boots because Stealth Rock does 25% to Lugia on every switch-in and the AI will happily switch it in repeatedly.

## 4. Verification

Active learnset gen for level-up is gen_9.h (`P_LVL_UP_LEARNSETS GEN_LATEST`, include/config/pokemon.h:14; compiled in src/pokemon.c:748). Mega/Primal forms point at their base species' learnsets (`.levelUpLearnset`/`.teachableLearnset` in each species_info block).

| Species | Move | Source (file:line) |
|---|---|---|
| Kyogre-Primal | Origin Pulse | level_up_learnsets/gen_9.h:9718 (lvl 1) |
| Kyogre-Primal | Calm Mind | gen_9.h:9713 block, lvl 18 |
| Kyogre-Primal | Ice Beam | gen_9.h block lvl 36; also teachable_learnsets.h:24638 |
| Kyogre-Primal | Thunder | teachable_learnsets.h:24655 |
| Golisopod-Mega | First Impression | gen_9.h:17402-17403 (lvl 0/1) |
| Golisopod-Mega | Liquidation | gen_9.h lvl 44; teachable_learnsets.h:42920 |
| Golisopod-Mega | Leech Life | teachable_learnsets.h:42919 |
| Golisopod-Mega | Knock Off | teachable_learnsets.h:42918 |
| Swampert-Mega | Earthquake | gen_9.h:7024 (lvl 1) |
| Swampert-Mega | Waterfall | teachable_learnsets.h:17953 |
| Swampert-Mega | Ice Punch | teachable_learnsets.h:17925 |
| Swampert-Mega | Knock Off | teachable_learnsets.h:17928 |
| Starmie-Mega | Liquidation | teachable_learnsets.h:8933 |
| Starmie-Mega | Zen Headbutt | teachable_learnsets.h:8956 |
| Starmie-Mega | Rapid Spin, Recover | gen_9.h:3456 block (lvl 1 both) |
| Greninja-Mega | Surf | teachable_learnsets.h:37558 |
| Greninja-Mega | Dark Pulse | teachable_learnsets.h:37526 |
| Greninja-Mega | Ice Beam | teachable_learnsets.h:37535 |
| Greninja-Mega | Grass Knot | teachable_learnsets.h:37531 |
| Lugia | Aeroblast | gen_9.h:6788 block, lvl 54 |
| Lugia | Calm Mind | gen_9.h block, lvl 27 |
| Lugia | Psychic | teachable_learnsets.h:17266 |
| Lugia | Roost | teachable_learnsets.h:17275 |

Abilities (src/data/pokemon/species_info/):

| Species | Ability | Line |
|---|---|---|
| Kyogre-Primal | Primordial Sea | gen_3_families.h:12841 |
| Golisopod-Mega | Tough Claws (only) | gen_7_families.h:4284 |
| Swampert-Mega | Swift Swim (only) | gen_3_families.h:871 |
| Starmie-Mega | Huge Power (only) | gen_1_families.h:15960 |
| Greninja-Mega | Protean (only) | gen_6_families.h:905 |
| Lugia | Multiscale (slot 3) | gen_2_families.h:8557 |

Species constants exist: `SPECIES_GOLISOPOD_MEGA`, `SPECIES_SWAMPERT_MEGA`, `SPECIES_STARMIE_MEGA`, `SPECIES_GRENINJA_MEGA`, `SPECIES_KYOGRE_PRIMAL`, `SPECIES_LUGIA` (include/constants/species.h:996, 1021, 1645, 1659, 1683, 260). Mega Greninja stats: 72/125/77/133/81/142, Water/Dark. No egg moves used.

## 5. Concerns for the owner

- **Golisopod and Fire.** It is 4x weak to Fire and has only the Vest for protection. Fire fails in Primordial Sea, so it is safe while Kyogre lives, but it is a one-hit KO to a Fire Mega (Charizard X/Y, Blaziken) once rain is gone or Primal Groudon takes over. If the fight feels cheap in the Groudon case, this is why.
- **Primal Groudon / Desolate Land** shuts down all five Water attackers at once and leaves Kyogre only Ice Beam. The back five all keep non-Water moves, but Greninja is locked into Specs: the AI's Check Bad Move should avoid a failing Surf, but I have not run it headless.
- **Newer Z-A Megas.** Mega Starmie (Huge Power), Mega Golisopod (Tough Claws) and Mega Greninja (Protean) are the repo's `P_GEN_9_MEGA_EVOLUTIONS` forms and each has a single-ability line, so there is nothing to select; I could not verify the engine's Protean behavior for the Z-A form beyond the config (once per battle). Mega Greninja's signature Z-A Water Shuriken was not used.
- **Difficulty.** This is deliberately harder than Maxie (alone at the generator, rain Swampert at 314 Speed under Choice Band, two ~390+ attackers). Starmie's 392 Attack is the highest raw physical number on the field at 65; if it one-shots too much, swap Life Orb for Sitrus Berry.
- **Easiest dial:** Kyogre's Calm Mind slot. Replace it with Surf and the lead stops snowballing, which is where the fight is won or lost. The second dial is Swampert's Choice Band to Sitrus Berry.


---

# Scott, the final battle (Sky Pillar, level 100)

## 1. Entry

```
=== TRAINER_SKY_PILLAR_SCOTT_LATIAS ===
Name: SCOTT
Class: Founder
Pic: Founder Scott
Gender: Male
Music: Intense
Double Battle: No
AI: Check Bad Move / Try To Faint / Check Viability / HP Aware / Smart Mon Choices / Omniscient

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

Items are six different: Focus Sash, Assault Vest, Shuca Berry, Life Orb, Leftovers, Expert Belt.

## 2. Team plan

**Philosophy: the slow three absorb, the fast three kill.** Rayquaza (361 Speed), Mewtwo (416) and Necrozma (392) outspeed almost everything a level 70-80s player can field, and they hold the kill and insurance items (Sash, Life Orb, Expert Belt). Kyogre, Groudon and Zygarde (216, 216, 236 Speed, uninvested) are the stat-check wall: 404, 404 and 636 HP, with an Assault Vest, a Shuca Berry and Leftovers. "No balance" is read as: no pivoting, no hazards, no status, no recovery moves, no screens, no sleep-adjacent tricks, and no Pokémon whose job is to be a wall. The only defensive things on the team are items on the three Pokémon whose job is to take one hit and delete you, and a Sash on the lead.

**Order:** Rayquaza, Kyogre, Groudon, Mewtwo, Zygarde, Necrozma. The three weather setters come in back to back (Delta Stream, Primordial Sea, Desolate Land), then the three non-weather hitters, with Ultra Necrozma as the closer.

- **Lead, Rayquaza.** Jolly Mega Rayquaza at 361 Speed outruns a max-Speed Jolly level-85 base-130 mon (335) and base-142 (358). Focus Sash means it always gets one move even if a Scarf Fairy special hitter (Pixilate Hyper Voice does roughly its whole 351 HP at the top roll) or a Sash/Sturdy lead tries to trade. It is deliberately not Choice-locked: Scott has no Smart Switching, so a locked Dragon Ascent into a Steel or a locked Extreme Speed into a Ghost would be a dead mon. Dragon Dance is its fourth slot because it is the one setup move the AI uses well, takes it to 541 Speed (outruns every Scarf), and turns a blocked turn into a threat.
- **Win condition 1 (the Primals).** Kyogre's Water Spout in Primordial Sea is 150 x 1.5 x 1.5 STAB with 504 SpA: a calc against an average level-80 bulky Mega (293 HP, 240 Def) is about 598 damage, 2x its HP. Groudon's Heat Crash in Desolate Land against the same target is about 478. Each Primal also shuts down half of what a "Mega-heavy" team brings: Primordial Sea erases the player's Fire moves, Desolate Land erases their Water moves entirely.
- **Win condition 2 (the fast trio, finishing).** After the Primals have eaten the player's good Pokémon, Mewtwo (OHKOs the same average target with Life Orb, about 367 damage), Zygarde (about 309 with no item) and Necrozma finish the damaged remainder. Mewtwo and Necrozma are outsped only by Scarf users above roughly base 105 at level 80.
- **Coverage.** Every one of the 18 types is hit super effectively by at least one move on the team: Normal/Ice/Dark/Steel/Rock by Aura Sphere, Fire/Grass/Ice/Steel/Bug by Heat Crash, Ground/Water by Water Spout (and Ice Beam), Flying/Fighting/Bug/Grass by Dragon Ascent, Poison/Fairy by Sludge Wave, Fairy/Ice/Rock by Flash Cannon, Psychic/Ghost by Dark Pulse (Necrozma), Dragon by Core Enforcer and Ice Beam, Water/Flying by Thunder and Thunderbolt, Electric/Poison/Rock/Steel by the Ground moves, Fighting/Poison by Psystrike and Photon Geyser.
- **Two Psychic hitters, split by defensive stat.** Psystrike hits Defense; Photon Geyser is special on Necrozma (Timid, Atk IV 0, so SpA > Atk) and hits Special Defense. Psychic resisters and Dark immunes are covered by Aura Sphere (Mewtwo), Dark Pulse and Earth Power (Necrozma), Earth Power and Focus Blast (Zygarde).
- **Physical/special split is 2 physical (Rayquaza, Groudon) vs 4 special**: Will-O-Wisp mostly eats Rayquaza, and Groudon (Ground/Fire) cannot be burned. Necrozma's Atk IV is 0 so Foul Play is dull.

**How the player can beat it:** Scarf or priority on the Sash lead; a Ground-STAB attacker into Groudon (Shuca Berry takes the first hit, then a second Ground hit still does 2x); an Ice Beam into Zygarde (4x, but 636 HP survives a strong level-80 STAB Ice Beam at around 576 max roll, then Leftovers and a Core Enforcer reply, so it will usually trade once); Dark/Bug/Ghost hitters into Mewtwo and Necrozma (their Defense is the soft spot, 70 and 97 base). **How it makes them pay:** there is no free turn to set up a stall or a Perish Song, and the bulky trio punishes a mon that was brought to answer one of them.

## 3. Per-Pokémon notes

**Rayquaza-Mega @ Focus Sash (Jolly, 252 Atk / 4 SpD / 252 Spe).** Stats at level 100: Atk 459, Spe 361, HP 351. Jolly rather than Adamant because the 10 percent damage (504 vs 459) matters far less than clearing the 335-345 max-Speed band (Adamant sits at 329). Dragon Ascent is the Flying-type STAB (so Fairy and Steel walls are not an issue for it), Extreme Speed is the revenge-kill and the answer to Scarf/Ice Shard, Earthquake is the Steel/Rock/Fire/Electric answer, Dragon Dance is the setup. No Stone Edge or Outrage: Dragon Ascent already covers what they would, and Ground STAB is already on three other Pokémon.

**Kyogre-Primal @ Assault Vest (Modest, 252 HP / 252 SpA / 4 SpD, Atk IV 0).** HP 404, SpA 504, SpD 357 x 1.5 = 535 with the Vest; Def is only 216, so the Vest makes it a special wall that physical Ground/Grass/Electric hitters can crack. No Calm Mind or Recover because the Vest bans status moves anyway and "no balance" bans them on principle. Water Spout is 150 BP at full HP and 100 percent accuracy; Origin Pulse (110, 85 percent) takes over when it is chipped (they cross at about 75 percent HP, and the AI's damage calc picks correctly). Ice Beam covers Dragon, Grass, Flying and Ground; Thunder is 100 percent accurate in its own rain and hits the Water types that resist Spout. No Fire Blast: it fails in Primordial Sea. Atk IV 0 against Foul Play (base 150 Atk would otherwise be a real weapon against it).

**Groudon-Primal @ Shuca Berry (Adamant, 252 HP / 252 Atk / 4 SpD).** HP 404, Atk 504, Def 356; Speed is left at 216 because nothing in the Groudon matchup needs it, but it does mean everyone moves first. Its weaknesses are Water (4x, void under its own Desolate Land) and Ground (2x); the Shuca Berry covers the second, so while the sun is up it has no real weakness. Precipice Blades is the Ground STAB (120 BP, 85 percent), Heat Crash the Fire STAB (120 BP at 100 percent against anything under 200 kg; 60 BP against a Mega Aggron-class 400 kg target and 40 against Metagross/Steelix, where Precipice Blades and Stone Edge take over), Stone Edge for Flying/Ice/Bug, and Swords Dance because it is a bulky mon that the AI reliably uses it with when no KO is on.

**Mewtwo-Mega-Y @ Life Orb (Timid, 252 SpA / 4 SpD / 252 Spe, Atk IV 0).** Spe 416 (fastest on the team), SpA 535. It is the only one that keeps the Life Orb because it is the one that needs the 1.3x to OHKO neutral targets (about 367 of 293 with it, 283 without). Psystrike for Defense, Aura Sphere (never misses) for Dark/Steel/Normal/Ice/Rock, Ice Beam for Dragons and Flyers it outspeeds, Thunderbolt for the Water types that shrug off Psystrike and Ice Beam (it outspeeds nearly all of them, and 90 BP at 100 percent beats Thunder's 70 percent outside rain). Dark Pulse is left to Necrozma so the two Psychic hitters do not share their answer to Psychic resists. Atk IV 0: its base 150 Atk would make Foul Play hit it very hard.

**Zygarde-Mega @ Leftovers (Modest, 252 HP / 252 SpA / 4 SpD).** HP 636, SpA 584 (the highest special stat on the team), Spe 236. It is Mega Zygarde, a special attacker (216 SpA, 70 Atk), so none of Thousand Arrows or Thousand Waves are worth a slot: Thousand Arrows' main value is hitting airborne targets, and Core Enforcer already hits Flying and levitating Pokémon, and at 70 Atk an Arrows hit would do roughly a third of Earth Power's damage. Core Enforcer (100 BP Dragon, 100 percent) is the STAB, Earth Power the Ground STAB, Sludge Wave is the Fairy/Grass answer (Zygarde is weak to Fairy, so it needs one), Focus Blast hits the Ice that is its own 4x problem plus Steel, Normal and Dark. Its 636 HP is why it can take a 4x Ice Beam and respond, which is why it gets Leftovers not damage.

**Necrozma-Ultra @ Expert Belt (Timid, 252 SpA / 4 SpD / 252 Spe, Atk IV 0).** Spe 392, SpA 433, HP 398, bulk only 97s. Neuroforce (1.25x on super effective hits) multiplies with Expert Belt (1.2x), so its super effective hits are 1.5x: the set is built entirely from super-effective angles. Photon Geyser (it uses whichever of Atk and SpA is higher; Atk is 0 IV and Timid, so it is special and hits Special Defense, while Mewtwo's Psystrike hits Defense), Dark Pulse for the Psychic and Ghost mirrors common in a legendary-heavy shop (Photon Geyser is resisted by Psychic and Steel and bounces off Dark), Flash Cannon for Fairy (the type most threatening to Necrozma and Mega Dragon users), Earth Power for the Steel types that wall everything else here. Dragon Pulse and Power Gem were left off because Photon Geyser and Core Enforcer/Ice Beam already cover Dragon and Flying.

## 4. Verification

All level-up learnset lines are `src/data/pokemon/level_up_learnsets/gen_9.h` (the active set: `P_LVL_UP_LEARNSETS = GEN_LATEST`, `include/config/pokemon.h:14`); all teachable lines are `src/data/pokemon/teachable_learnsets.h`.

| Move | Species learnset used | Where |
|---|---|---|
| Dragon Dance | Rayquaza (Mega uses it, `gen_3_families.h`) | gen_9.h:9760 (level 18) |
| Dragon Ascent | Rayquaza | gen_9.h:9758 (level 1) |
| Extreme Speed | Rayquaza | gen_9.h:9761 (level 27) |
| Earthquake | Rayquaza | teachable_learnsets.h:24769 |
| Water Spout | Kyogre (Primal uses it) | gen_9.h:9727 (level 90) |
| Origin Pulse | Kyogre | gen_9.h:9718 (level 1) |
| Ice Beam | Kyogre | gen_9.h:9722 (level 36) |
| Thunder | Kyogre | teachable_learnsets.h:24655 |
| Precipice Blades | Groudon | gen_9.h:9738 (level 1) |
| Heat Crash | Groudon | teachable_learnsets.h:24696 |
| Stone Edge | Groudon | teachable_learnsets.h:24721 |
| Swords Dance | Groudon | teachable_learnsets.h:24725 |
| Psystrike | Mewtwo | gen_9.h:4655 (level 72) |
| Aura Sphere | Mewtwo | gen_9.h:4650 (level 40) |
| Ice Beam | Mewtwo | teachable_learnsets.h:11597 |
| Thunderbolt | Mewtwo | teachable_learnsets.h:11633 |
| Dark Pulse | Necrozma | teachable_learnsets.h:44353 |
| Core Enforcer | Zygarde (`sZygardeLevelUpLearnset`, shared by all Zygarde forms incl. Mega, `gen_6_families.h:7141`) | gen_9.h:16354 (level 1) |
| Earth Power | Zygarde | teachable_learnsets.h:40473 |
| Sludge Wave | Zygarde | teachable_learnsets.h:40492 |
| Focus Blast | Zygarde | teachable_learnsets.h:40475 |
| Photon Geyser | Necrozma (Ultra uses `sNecrozmaLevelUpLearnset`, `gen_7_families.h`) | gen_9.h:18068 (level 72) |
| Flash Cannon | Necrozma | teachable_learnsets.h:44360 |
| Earth Power | Necrozma | teachable_learnsets.h:44357 |

Note: Zygarde-Mega's `.levelUpLearnset`/`.teachableLearnset` are the plain `sZygarde*` ones, not a separate Complete table (there is only one Zygarde learnset). The two Complete-form "extra" moves exist: Thousand Arrows and Thousand Waves are level 1 in the same table (gen_9.h:16352-16353). Mega Rayquaza keeps no stone: Dragon Ascent is level 1 in Rayquaza's list, so it is legal as a plain move.

Ability check (`src/data/pokemon/species_info/`):

| Species | Ability | Line |
|---|---|---|
| Rayquaza-Mega | Delta Stream | gen_3_families.h:13155 |
| Kyogre-Primal | Primordial Sea | gen_3_families.h:12841 |
| Groudon-Primal | Desolate Land | gen_3_families.h:12996 |
| Mewtwo-Mega-Y | Insomnia | gen_1_families.h:20741 |
| Zygarde-Mega | Aura Break (only slot) | gen_6_families.h:7104 |
| Necrozma-Ultra | Neuroforce (only slot) | gen_7_families.h:7198 |

Base stats read from the same blocks: Zygarde-Mega 216/70/91/216/85/100 (HP/Atk/Def/SpA/SpD/Spe), Necrozma-Ultra 97/167/97/167/97/129, Mewtwo-Y 106/150/70/194/120/140.

Items all exist in `include/constants/items.h`: `ITEM_FOCUS_SASH`, `ITEM_ASSAULT_VEST`, `ITEM_SHUCA_BERRY`, `ITEM_EXPERT_BELT`, plus Life Orb and Leftovers (used elsewhere in `trainers.party`).

## 5. Concerns for the owner

1. **The weather overrides never actually happen.** Scott never switches voluntarily (no Smart Switching), so a Primal or Delta Stream mon is always gone before the next one arrives. Each weather ends when its Pokémon faints and the next comes in to a clear sky. The sequence is still visible (Delta Stream, rain, sun, one after another), but it is a relay, not a clash. That is an engine truth, not a team-building one: two weather mons are never out together in singles.
2. **Necrozma-Ultra as a permanent form needs an engine fix and a test.** `CanBattlerFormChange` (src/battle_util.c, the `FORM_CHANGE_END_BATTLE`/`FORM_CHANGE_FAINT` case) already returns FALSE for a Mega that began the battle as one (the Replica Crown patch), but for Ultra it takes the `IsBattlerUltraBursted` path. `sNecrozmaUltraFormChangeTable` (form_change_tables.h:1670) is `{FORM_CHANGE_FAINT}, {FORM_CHANGE_END_BATTLE}` with no target species, and a Necrozma that was never Ultra Bursted this battle has `changedSpecies == SPECIES_NONE`, so `TryBattleFormChange` hits the `assertf(targetSpecies != SPECIES_NONE)`. In a release build that returns FALSE (the Necrozma stays Ultra, which is what we want); in test/debug builds the assert fires. A one-line guard mirroring the Mega one (`isUltraBurst && changedSpecies == SPECIES_NONE` returns FALSE) plus a test (enemy `SPECIES_NECROZMA_ULTRA` stays Ultra after switch-out, after a faint, and keeps Neuroforce) would be needed. I did not check the player-side `TryFormChange` in pokemon.c; it has the same `FORM_CHANGE_FAINT` table.
3. **Zygarde-Mega** is already covered by `test/battle/ten_gauntlets_enemy_mega.c` for Zygarde-Complete evolving; listing `Zygarde-Mega` directly is `isMegaEvolution = TRUE` so the existing permanence patch applies, but no test lists it directly. Worth one test.
4. **Variants collapse.** With the Lati and Darkrai gone, `_LATIOS`, `_NO_DARKRAI_LATIAS` and `_NO_DARKRAI_LATIOS` would all be identical to this entry. The owner can delete the three and point everything at one entry, or keep them as copies; I designed one team only.
5. **Heat Crash weight dependence.** 120 BP only against targets under about 200 kg; Steel Megas (Aggron, Steelix, Metagross) get 40-60. That is on purpose (Precipice Blades covers them) but the AI will see a low Heat Crash number and prefer the Ground move there, which is correct.
6. **Difficulty worries.** Honest read: this is very hard, probably harder than the old Latias/Darkrai team because the old back half (Lati, Darkrai) was frail and the new one is three tanks and an Ultra. The Sash lead and Zygarde's bulk mean a player cannot trade evenly early. The main real counterplay is Scarf/priority on the lead, Ground into Groudon, Ice into Zygarde, and Dark/Bug/Ghost physical hitters into Mewtwo/Necrozma. Foul Play is dulled (Atk IV 0 on Kyogre, Mewtwo and Necrozma).
7. **Easiest dial.** Take the three bulk items off the slow trio: swap Kyogre's Assault Vest to Mystic Water, Groudon's Shuca Berry to a Life Orb or Soft Sand, and Zygarde's Leftovers to Wise Glasses. That is the "balance" in the team: removing it turns a stat-check into a glass-cannon race. For making it harder instead, swap Necrozma's Expert Belt for Life Orb and Mewtwo's Life Orb for Wise Glasses (Necrozma is the lowest raw damage on the team by design: Photon Geyser does about 229 to the same 293 HP target the others clear in one hit).


---

