# Handoff — current state (2026-10-15)

Read `CLAUDE.md` and `project-guide.md` first. This file is where the work
stands: what's built, what's tested, what's loose, what's next, and the test
harness. History is in `git log`; the story is in `storyline.md`.

---

## Where things stand

- **The whole game is built**: all eight gauntlets, the shop, the run loop,
  and the story from the opening to the credits (`storyline.md`, every beat
  ✅). **None of the endgame has been played by hand**: parts 1-5 are
  headless-tested only (below). The owner's next step is a full playthrough.
- **The endgame's teams** are all in `endgame-teams.md` and
  `src/data/trainers.party`; difficulty is untuned. On 2026-10-15 the owner
  replaced the rosters of the Elite Four, Maxie, Archie and Scott's Sky Pillar
  team (built only, see "Testing status").
- **Trainer IDs: 992 of 1000 used** (990-991 are the Gym rematches).
- **The endgame towns sprint is built** (`storyline.md`, "Rustboro after the
  liberation" and "Mauville after the liberation"): Roxanne's and Wattson's
  Gym rematches, Giratina in Rusturf Tunnel, Calyrex in Mauville. Harness
  only, **not played**.
- **The towns' people are written (2026-10-23)**: every vanilla townsperson
  in Rustboro and Mauville, outdoors and in every open building, now follows
  the story (`GetStoryGossipStage`: under the Elite Four / overrun, freed,
  after the credits), and **six hidden helpers** each raise one party
  Pokémon once: three in Rustboro to 55 (the Devon engineer outdoors, the
  night nurse in Flat 2's 3F, the School teacher), three in Mauville to 65
  (the ex-Rollout tutor outdoors, the Game Corner cook, Rydel's assistant).
  One hint per town (Rustboro: Flat 2 1F's old woman; Mauville: the Mart
  man). `RaiseMonToLevel` (`src/facility.c`), `FLAG_RUSTBORO_RAISE_1-3`,
  `FLAG_MAUVILLE_RAISE_1-3`. Vanilla extras switched off with them: the
  Seedot trade, Walda's wallpaper, the Rollout tutor, Rydel's bike, the Game
  Corner doll and coins. **Built and width-checked only, not run.**
- **Commits are local only.** Pushing from WSL isn't set up.

## Next: the owner's full playthrough, then tuning

Play from a New Game through the credits (the TEMP Miraidon on the ferry dock
is there for speed). Things to look at especially, because no one has seen
them on a screen:

- Every endgame scene's **staging** (who walks where, facing, timing).
- **Difficulty** of the Elite Four (52-55, in pairs with the rival's heal
  between the two), the admins (60), Maxie and Archie (65, **doubles since 2026-10-15**, back to back at
  the generator after all four admins, the rival's heal between them) and
  Scott at 100; and the Chansey's level-100 transfers (unlimited since 2026-10-23). The Elite Four, Maxie,
  Archie and Scott were rewritten on 2026-10-15 and are the hardest teams
  in the game on paper: three to four permanent Megas plus legendaries
  each, Calyrex-Shadow with Nasty Plot, Kyurem-White, Koraidon, and a Scott
  of three tanks and Ultra Necrozma. Nobody has fought them, and
  `endgame-teams.md` gives each team's easiest dial. The siphon now lifts
  every chipped Pokémon to 60 and the shop sells at 60 after it
  (2026-10-13): check the party's levels after "Free the POKéMON".
- **The pair scenes' staging** (rewritten 2026-10-15, never seen on a
  screen). Devon 1F and 2F: during the fade after the first member leaves,
  the player and the rival are placed on fixed tiles (1F: player (14,6),
  rival walks (11,6) to (13,6), Phoebe walks (14,2) to (14,5); 2F: player
  (9,2), rival (12,2) to (10,2), Drake (2,2) to (8,2)). Check it from every
  side the player can talk to the first member from, and that a loss in the
  second fight resets the pair. New Mauville: the rival runs in from off
  screen at (20,5), through the lowered x=21 barrier and along row 5, then
  steps to the player's row on each of the five x=29 trigger rows (y 4-8);
  on the talk path (the player beside either leader) the rival runs the
  same way and stops at (31,5). Check the heal between Maxie and Archie,
  that both fights are doubles, and that a loss to either repeats both.
- **Sky Pillar's 4F**: the clean layout still has three cracked tiles at
  (6-9, 4), and vanilla's bikeless route drops through one into 3F's inner
  room to reach the upper stairs. The harness walks it fine; decide whether
  that's "smooth" enough or whether 4F needs a re-tiled floor.
- **The ending** is a plain save-and-credits (`EndgameClear`,
  `src/post_battle_event_funcs.c`): no Hall of Fame screen. The continue
  after the credits lands at the Frontier's heal spot (3, 52), not at the
  Arena base.
- **Dialogue tone** in the new scenes (the Elite Four, Stone, Maxie and
  Archie, Scott's last words, Looker's arrest).

---

## Endgame parts 3-5 in brief

`VAR_ENDGAME_STATE` 11-18 (the full table is at the top of
`BattleFrontier_OutsideEast`'s endgame block).

| Piece | Where |
|---|---|
| The siphon: the Pokémon keeper's "Free the POKéMON" (state 10 with the Crown), every chipped Pokémon below 60 lifted to 60 (`SiphonLiftChippedLevels`, party, boxes, Day Care), the shop at 60 from then on, `FLAG_CROWN_CHARGED`, `FLAG_FRONTIER_CHIPS_OFF`; state 11 | `BattleFrontier_ExchangeServiceCorner`, `src/facility.c`, `src/facility_shop.c` |
| The Crown's limit: one permanent Mega from state 11, six from 14 | `GetReplicaCrownLimit`, `src/party_menu.c` |
| Steven's hub outside the Arena: every state's lines, the Mauville send-off (12, `FLAG_ABRA_TO_MAUVILLE`), the Sky Pillar send-off (16, `FLAG_ABRA_TO_SKY_PILLAR`), the post-credits lines (18) | `BattleFrontier_OutsideEast` |
| Mauville overrun; Wattson, Steven and Wallace; Wattson leads the player down (fade + warp, state 13); respawn at Mauville's Center | `MauvilleCity` |
| New Mauville: wild encounters off, the door open, exits lead back to Mauville; the four admin gates in order, Tabitha, Courtney, Matt, Shelly (`VAR_NEW_MAUVILLE_ADMINS`, 0-4, **renumbered 2026-10-15**), a coil heal after each; then Maxie and Archie together at the generator (33,5) and (34,5), fought back to back (the x=29 trigger or a talk starts it, **the rival runs in behind the player**, Maxie, the rival's heal, Archie), a loss to either repeats both (`OnTransition` clears Maxie's flag in state 13); **Maxie and Archie are 6v6 doubles now (2026-10-15)**, the four admins stay singles; the Crown supercharged (state 14), the Primals taken back, both leave and the rival too. Rewritten 2026-10-15, **built only** | `NewMauville_Entrance`, `NewMauville_Inside` |
| The teams leave; Hoopa's third ring; state 15 | `MauvilleCity` |
| Nurse Joy and the Chansey outside the Arena: `TransferExpToLevel100`, repeatable (unlimited since 2026-10-23); the first use sets `FLAG_CHANSEY_TRANSFER_EXP_USED`, which lifts Roxanne's and Wattson's rematches to level 100 (`LiftOptionalEndgameTrainerParty`, hooked in `DoTrainerBattle`) | `BattleFrontier_OutsideEast`, `src/facility.c` |
| Sky Pillar: the allies, the seven Brains' ambush (state 17), Joy by the door as the white-out respawn (`HEAL_LOCATION_SKY_PILLAR_OUTSIDE`), clean floors, no wild Pokémon | `SkyPillar_Outside`, `SkyPillar_1F-5F` |
| The top: the Master Ball and Rayquaza (`FLAG_SKY_PILLAR_RAYQUAZA_CAUGHT`), the Scrambler, Scott at 100 (Mega Rayquaza, both Primals, Mega Mewtwo Y, Mega Zygarde, Ultra Necrozma; rewritten 2026-10-15), Looker's arrest, state 18, the credits | `SkyPillar_Top`, `EndgameClear` |
| Gossip: SIPHON, MAUVILLE, MAUVILLE_FREED, SKY_PILLAR, ENDING | `GetStoryGossipStage`, all 12 gossip NPCs |
| Vanilla gifts off in Rustboro's Cutter's house, Mauville's houses 1-2 and the Game Corner; since 2026-10-23 also the Seedot trade, Walda's wallpaper, the Rollout tutor, Rydel's bike, the Game Corner doll and coins | those interiors |

Engine facts the harness confirmed: a trainer's `Groudon-Primal` /
`Kyogre-Primal` / `Rayquaza-Mega` listed directly stays in that form through
faints and switches, with Desolate Land, Primordial Sea and Delta Stream
firing; no stone or orb is needed. Not yet confirmed: `Necrozma-Ultra`
and `Zygarde-Mega` listed directly (Scott's new team).

---

## Endgame part 2 in brief

Rustboro, tracked by `VAR_ENDGAME_STATE` 7-10 (listed in `RustboroCity`'s
scripts).

| Piece | Where |
|---|---|
| The ABRA lands in Rustboro's Pokémon Center, beside the town's ABRA | `RustboroCity_PokemonCenter_1F`, `endgame_towns.inc` |
| Steven and Wallace block Devon's door; talking starts the Wardens' ambush (off-screen) | `RustboroCity` (state 7 → 8) |
| Elite Four in **pairs, back to back** (rewritten 2026-10-15, built only): Sidney then Phoebe on 1F, Glacia then Drake on 2F. The rival heals between the two (in the lobby and the 2F hall, `OBJ_EVENT_GFX_VAR_0`, `FLAG_TEMP_4`, only in state 8 while the pair is unfinished) and leaves after each pair. The second member walks over and fights at once; the player and rival are placed on fixed tiles during the fade. A loss anywhere whites out to the Center and resets the pair (`OnTransition` clears the first member's flag while the second is unbeaten). The rival is not on 3F | Devon 1F (Sidney, Phoebe), 2F (Glacia, Drake) |
| Stone's confession, the scientist, `ITEM_REPLICA_CROWN` | Devon 3F (state 8 → 9) |
| Juan's apology as the player comes out; Hoopa's second ring | `RustboroCity` (state 9 → 10), `GetHoopaRingsLeft` |
| Devon's staff hidden; the letter, PokéNav, Exp. Share and fossils off | Devon 1F-3F |
| Gossip: `GOSSIP_DEVON_FREED` (state 10 on) | `GetStoryGossipStage`, four new lines |

The Elite Four (`TRAINER_DEVON_*`, 974-977) are plain trainer battles, not
Frontier battles: their real levels, and held items restored afterwards
like every story fight.

---

## Endgame part 1 in brief

Tracked by `VAR_ENDGAME_STATE` (states listed in `BattleFrontier_OutsideEast`'s
scripts: 1 gauntlet 8 cleared ... 7 sent to Rustboro).

| Piece | Where |
|---|---|
| Harsh sunlight (drought, outdoor Frontier maps, states 1-4) | Outside East/West `SetupEndgame` |
| Wallace at the Pyramid swaps the badges back to real | Outside East |
| Palkia blasts the Factory door (`SetBattleFactoryUnlocked`); Joy's post | Outside West |
| Spenser and Brandon take Wallace on; five guards (`TRAINER_FACTORY_*`), key pieces, five lights | `BattleFrontier_DevonFactory_*` |
| Cells free Mom, Dad, the Broker, Hoopa | Factory B1F |
| Scott's no-white-out battle (`B_FLAG_NO_WHITEOUT`), level 100, Mega Darkrai | Factory B3F |
| The Arena base: free shop (`FLAG_FRONTIER_SHOP_FREE`), 99 Ultra Balls, Steven | Outside East, Exchange Service Corner |
| Hoopa's rings: eleven box-art legendaries (Miraidon removed 2026-10-16), Island Cave, level 60, unchipped | Arena lobby, Island Cave |
| Gossip: SIEGE, AFTERMATH, DEVON beats | `GetStoryGossipStage` |
| The Frontier's ABRA, now in the Pokémon Center | Pokémon Center 1F |

Scott's trainer class is `FOUNDER`; his battle sprite is the owner's
`graphics/trainers/front_pics/founder_scott.png` (`Pic: Founder Scott`, all
eight `SCOTT` entries in `src/data/trainers.party`). **Not seen in battle yet.**

---

## Testing status

| What | Status |
|---|---|
| The seven rewritten teams (2026-10-15): Sidney, Phoebe, Glacia, Drake, Maxie, Archie and Scott's Sky Pillar team | Written from `endgame-teams.md` into `src/data/trainers.party`; **built only, not battle-tested and not played**. Engine risks to check when played: `Necrozma-Ultra` staying Ultra after a faint (a one-line guard in `CanBattlerFormChange` is in, with no test yet; without it a test or debug build tripped the form-change assert); `Zygarde-Mega` listed directly (no test lists it); the newer Megas' abilities, sprites and cries (Starmie, Golisopod, Greninja, Crabominable, Abomasnow, Feraligatr, Dragonite, Heatran have never run in a trainer team); the Calyrex abilities as `ABILITY_AS_ONE_*` constants in the generated data; three to four permanent Megas on one team (tests cover one at a time); the Primals entering from slot 6 with no ace flag (Maxie and Archie were rewritten again 2026-10-16: Charizard Y and Mega Heatran lead Maxie with Volcarona, Reshiram, Ho-Oh; Politoed and Mega Swampert lead Archie with Indeedee-F, Lugia, Mega Starmie; Indeedee-F's Psychic Surge and an Assault Vest Kyogre answer the owner's Miraidon); Phoebe's Prankster Destiny Bond against a Dark type |
| The pair flows (2026-10-15): the Elite Four in pairs at Devon, Maxie and Archie back to back at New Mauville, both with the rival's heal | Rewritten in `RustboroCity_DevonCorp_1F/2F` and `NewMauville_Inside` (scripts, `map.json`, `VAR_NEW_MAUVILLE_ADMINS` 0-4); **built only, not battle-tested, not played**. **Harness scenarios 21 and 23 now test the OLD flows (single fights, Maxie in the corridor, Archie alone) and must be rewritten before they are trusted.** To cover: a pair's staging on the fixed tiles, the rival's heal, the second member fighting at once, a loss in the second fight resetting both, held items restored after each win and a white-out, the rival gone after each pair and absent from 3F; at New Mauville the four admins, the rival added only at the generator scene (all five trigger rows and the talk path), the heal between, a loss to either repeating both, the unchanged supercharge, the rival gone |
| The towns' people and the six helpers (2026-10-23) | **Built only**: `make` clean, `textwidth.py` 0 over-wide. Not run, not played. To check when played: each helper's pick, Egg and "too strong" loops, the flag after a success, the "used" lines per beat, the hint lines vanishing (Mauville) once all three are spent; the Rustboro raise refusing a party already at 60 after the siphon; every NPC's beat switch at states 7/8/10/11/13/15/18 |
| Endgame towns: the Gym rematches | Harness scenario 35 (`harness-gyms.c`), 17/17: each door sealed before its town is freed and open from then on (through 18), only the leader inside, Mauville's puzzle off, a loss and a win per leader (a loss: no white-out, still in the Gym, healed, items back, flag clear, the "come back" line; a win: flag, heal, items, lead), no Wattson outside at 15. **Predates 2026-10-23**: with `FLAG_CHANSEY_TRANSFER_EXP_USED` set both leaders are at level 100; scenario 35 never sets it, so it still tests 60 and 65. `test/battle/ten_gauntlets_enemy_mega.c` 4/4: an enemy `Zygarde-Complete` Mega Evolves (AI too) and stays Mega. **Not played**: the teams' difficulty |
| Endgame towns: Giratina (The Tear) | Harness scenario 33 (`harness-giratina.c`), 31/31: nothing before Roxanne, the clues and Hoopa's hint, the escort, the dark walk and its three wrongnesses, a loss, a knock-out, a run, the Master Ball catch and the Core, the exits, after the credits, a full bag. **Not played**: the darkness on screen |
| Endgame towns: Calyrex (The True King) | Harness scenario 34 (`harness-calyrex.c`), 22/22: rubble only before Wattson, the old man's legend, the Crown's restoration, no steed, a run, a knock-out, the catch and the Reins, never chipped, one fusion (Glastrier) and one unfusion. **Not played**: the stand-in art, Spectrier, the learn-move prompt, save and reload while fused |
| The shop's tier menu (New arrivals, Showdown tiers, Low Tier as Competitive and Other by type; `shop-spec.md`, "The Pokémon menu") and form names (Rotom-Wash...) | Harness scenario 26 (`harness-shop.c`), 15/15: the New Game menu (Low Tier and Sell only; Competitive 1, Other 118, Flying by either type), a real walk through Low Tier (Competitive, a purchase, B; Other, no "All", a type's list, B back out level by level), every count with everything unlocked (Competitive 41, Other 223 across its types, 513 in all), gauntlet 1's 99 New arrivals, the siphon row. The old Low Tier "All" (264 rows) froze the game: a `u8` row counter, now `u16`. **Not played**: look at the wider list box beside the FP window |
| Bad Dreams: the Frontier Center's regulars asleep | Harness scenario 31 (`harness-badD.c`), 11/11: the kid and picnicker asleep in place, each dream line, the Wing's glow, Skitty, the "slept well" lines, normal lines after gauntlet 7. Scenario 29 re-run: 18/18 (one earlier run missed the Pike lobby's wandering beauty, a harness timing flake). **Not played** |
| Bad Dreams (the optional Darkrai event, gauntlet 7) | Re-run together on the merged `master`: 29 and 30 green. Scenarios 29 (`harness-badB.c`, the sleepers and Joy, 18/18), 30 (`harness-badC.c`, the Pike, Darkrai, the ball guard, a loss, the win, a gauntlet 6 regression, 9/9) and 24/28 (`harness-badA.c`, Scott's 5-Pokémon teams in both battles). **Not played** |
| The Oldale Paradox researcher (Booster Energy, one per Paradox species; the shop no longer sells it) | Harness scenario 25, 4/4: a non-Paradox refused, a new species paid, a repeat refused, a second species paid. **Not played** |
| Parts 3-5 after the merge | Scenarios 22, 23 and 24 re-run on the merged `master`: 10/10, 16/16, 14/14 (scenario 23 predates the 2026-10-15 New Mauville rewrite) |
| Endgame part 3 (the siphon, the hub, the Chansey) | Harness scenario 22 (`harness-part3.c`), re-run 2026-10-13, 10/10: the keeper's menu, the flags, chips off, the level catch-up (chipped 50s in the party, box 0 and the Day Care to 60 with full HP; an Island Cave 50, a 70 and an Egg untouched), Steven's send-offs, Transfer EXP (Eggs and level 100 refused, once only), every state's cast. **Not played**. **Predates 2026-10-23**: Transfer EXP is unlimited now, so its checks 305-307 expect a second use refused; rewrite them: after a success Joy asks "Another one?" (YES picks again, NO ends), and the flag now means "used at least once" |
| Endgame part 4 (Mauville, New Mauville) | Harness scenario 23 (`harness-part4.c`), re-run 2026-10-13 after the split, 18/18; **predates the 2026-10-15 rewrite (it tests the old order, with Maxie in the corridor, and fails or passes for the wrong reasons)**: Wattson's way in, the five guards in order (Tabitha, Courtney, Maxie, Matt, Shelly), Maxie gone from the corridor and shown at the generator after his win and after a reload, Archie **lost on purpose** (white-out to Mauville's Center, Maxie stays beaten, only Archie reset), Archie won (Maxie fought once, Archie twice), the supercharge, the exit scene, three rings; Primals stayed Primal with their weather. **Not played** |
| Endgame part 5 (Sky Pillar, the ending) | Harness scenario 24 (`harness-part5.c`), 14/14: the ambush, the bikeless climb of all five floors, Scott **lost on purpose** (white-out to Joy outside, healed, items back, no re-catch), won, Looker, state 18, the credits entered with the continue warp at the Frontier; Mega Rayquaza (no stone) and both Primals kept their forms and abilities. **Not played** |
| Endgame part 2 (Rustboro) | Harness scenario 21, **19/19 green** before the 2026-10-15 pair rewrite (it **predates the change**: single Elite Four fights, no rival): the ABRA in and out of the Centers, the ambush, the Elite Four in order (out-of-order talks refused), a loss to Glacia whiting out to Rustboro's Center (healed, items back, beaten members stay gone), Stone's scene and the Crown, vanilla 3F events off, Juan, two Hoopa rings, the new gossip beat. **Not played** |
| Endgame part 1 | Harness scenario 20, **18/18 green**: Pyramid to Rustboro, every Brain fight, the cells, Scott's battle **lost on purpose** (outcome checked, no white-out, team healed, items back), the base, the Broker, a Hoopa trip, the ABRA. **Not played** |
| Hoopa catching a legendary | Not run (the knock-out path was). Since the owner's playthrough: after a catch Hoopa rests until `VAR_ENDGAME_STATE` goes up (`VAR_HOOPA_REST_STATE`, no rest after the credits); built, not run |
| Endgame gossip beats | Built, widths checked; code-read only |
| Endgame towns | Harness scenario 11, 14/14. **Not played** |
| Wallace hiding | Harness scenario 14, 7/7 (incl. an old save). **Not played** |
| Tag-battle party fix | Harness: Ever Grande win and loss, distinct species picked 1,4,3 |
| Devon Factory maps | Harness scenario 10. **Not played** |
| Permanent Megas, Replica Crown | Engine tests in `test/battle/ten_gauntlets_perma_mega.c`. The one-charge Crown (states 11-13) now counts permanent Megas in the PC boxes and Day Care too (`IsReplicaCrownFull`; boxing one used to free the charge); built, not run |
| Crown event (after gauntlet 7) | Littleroot part played by the owner; the Factory standoff visuals not confirmed |
| Broker's-letter event | Ever Grande part played; the rest not hand-tested |
| Dialogue pass, opening, gossip | Built, widths checked. **Not played** |
| Prices in wins | Built and code-read, not run |
| `make check` | 15 known failures (the baseline) |

---

## Loose ends

- **`TEMP` Miraidon** on the ferry dock is back for the owner's playthrough
  (commit "TEMP: test Miraidon back on the ferry dock"): point the dock
  man's object in `BattleFrontier_OutsideWest/map.json` back at
  `BattleFrontier_OutsideWest_EventScript_Man3` and delete the block at the
  end of its `scripts.inc` before release.
- **Unplayed endgame** (parts 1-5): see "Next" above.
- **The rival's New Mauville parting line** (`NewMauville_Inside_Text_RivalAfter`)
  says they head up first to tell Wattson, but the rival is not in the
  Mauville street scene afterwards (Wattson, Steven and Wallace only). Fine
  as it is, or add the rival there: the owner's call.
- **`VAR_NEW_MAUVILLE_ADMINS` was renumbered on 2026-10-15** (0-5 became 0-4:
  Maxie's step left the corridor). A save made in the middle of New Mauville
  before that day would be off by one (a count of 2 would now mean Courtney
  is beaten and Matt is next, where it used to mean Maxie was next). New
  Games are unaffected; the owner's playthrough should start fresh.
- **Scott's Sky Pillar teams are identical now.** All four entries
  (`_LATIAS`, `_LATIOS`, `_NO_DARKRAI_LATIAS`, `_NO_DARKRAI_LATIOS`) hold the
  same six (Mega Rayquaza, Kyogre-Primal, Groudon-Primal, Mega Mewtwo Y, Mega
  Zygarde, Ultra Necrozma), so the Bad Dreams reward and the Lati choice no
  longer change the final battle (they still change the Factory fight).
  The Sky Pillar script still branches on `FLAG_STEVEN_HAS_LATIOS` and
  `FLAG_DARKRAI_FREED` (harmless: the four entries are the same team). The
  "one short" Darkrai line (`SkyPillar_Top_EventScript_ScottOneShort`) was
  rewritten to fit on 2026-10-15: Scott shrugs it off as a spare he no longer
  carries. Collapsing the four entries to one would free three trainer IDs;
  the owner's call.
- **Bad Dreams** (`storyline.md`, "During gauntlet 7"): look at the Pike
  lair's darkness on screen (`setflashlevel 2` in
  `BattleFrontier_BattlePikeRoomFinal`'s `SetUpLair`), and the Latios
  variants of Scott's Darkrai-less teams (987, 989) weren't run, only the
  Latias ones.
- **Side quests:** the Oldale Paradox researcher (`OldaleTown_House1`,
  `VAR_PARADOX_SHOWN_LO/HI`) is the first; the owner wants more of these for
  late-game items.
- **Free flags and vars:** flags 0x286-0x287, 0x28F (0x289-0x28E are the towns' helpers);
  `VAR_UNUSED_0x40FC`-`0x40FF` (0x281-0x285 and 0x40F9-0x40FA are the endgame
  towns'; 0x40F7-0x40F8 are the Paradox researcher's; 0x40FB is
  `VAR_HOOPA_REST_STATE`).
- **Endgame towns, to look at in the playthrough:** the dark Rusturf Tunnel
  (light circle, Giratina's sprite, `MUS_PETALBURG_WOODS`); the Mauville
  statue's stand-in art (a Rock Smash rock as rubble, the Trick House statue)
  and the Calyrex sprite; both Gym teams' difficulty (Mega Zygarde at 60 is
  strong; the dial is Focus Blast to Protect or her level); Calyrex fused with
  Spectrier, the learn-move prompt, a full-party unfuse, save and reload while
  fused.
- **Rusturf Tunnel's warps are `MAP_DYNAMIC` for good** (all to Rustboro):
  restore or delete them at the strip.
- **Brandon's gauntlet 8 team** already has Zygarde-Complete, Miraidon and Iron
  Hands; Roxanne and Wattson repeat them (in singles, at 60-65).
- **The four admins** use grunt overworld sprites (they have none of their
  own); Looker uses the Gentleman sprite at Sky Pillar.
- **The old Battle Factory maps** and the rest of the vanilla story are still
  in the ROM (the strip is still to do; the endgame's maps must survive it:
  Rustboro, Devon Corp, Mauville, New Mauville, Sky Pillar, Island Cave).
- **The ABRA arrivals were a dead end** (fixed in part 2): in the Pokémon
  Center layout, (13, 6) below the ABRA is boxed in by the table, so anyone
  arriving at the Frontier by ABRA could only teleport away. Arrivals are now
  (12, 5) in both Centers. Mauville and Sky Pillar's ABRAs are outdoors and
  unaffected.
- **A parallel build once corrupted `src/data/heal_locations.json`**
  (a missing comma, then a JSON parse error). `git checkout
  src/data/heal_locations.json` and building again fixed it. If a build
  fails with `JSONPROC_ERROR` there, that's the fix.
- **The Elite Four's lines** are first drafts in their vanilla voices; tune
  them after a playthrough, along with the teams' difficulty
  (`endgame-teams.md`, Open question 3).

- The owner's save still has the duplicate Landorus from the old tag-battle
  bug.
- **Tag battles** where the player picks three need `Multi Party: Half` on both
  opponents (`trainers.party`).
- **Pricing questions:** should the Arena's 100 FP mock battle be priced in
  wins? Should early services have a floor (Second Wind is 150 FP in
  gauntlets 1-2)?
- **Endgame towns:** the vanilla gifts and services inside open buildings
  are all off now (2026-10-23; the Mart purchases and the nurses stay).
  **Glass doors** (Devon Corp, the Game Corner) warp through
  `TryStartWarpEventScript`, so sealing one would need a check there. Sky
  Pillar still has its cracked floors; the owner wants the climb smooth (no
  bike, and Rydel no longer hands one out).
- **The Factory generator** (`~/decomps/headless-harness/factory/`) still makes
  seven B2F lights; regenerating B2F would undo the five-light edit.
- The old Battle Factory maps (gauntlet-6 "Assembly Line" text) are unused:
  the Factory door leads to the Devon Factory. Strip them with the vanilla
  story.
- Champion's Room and Hall of Fame Wallaces have no hide flag; give them one
  if the endgame opens those rooms.
- `~/decomps/wallace-backsprite-for-artist/` can be deleted.

---

## The headless harness: `~/decomps/headless-harness/`

- `harness.c`: scripted-input driver; `#define HARNESS_SCENARIO n`.
  **`harness-part3.c`, `harness-part4.c`, `harness-part5.c`** are copies of
  it with scenarios 22, 23 and 24 added (endgame parts 3-5; each was written
  by a separate agent, so they live in their own files: use the file whose
  scenario you want as `src/harness.c`). **`harness-shop.c`** has scenario
  26 (the shop's tier menu); it needs one extra line appended to the copy's
  `src/field_specials.c`: `bool8 Harness_ScrollMultiOpen(void) { return
  FindTaskIdByFunc(ScrollableMultichoice_ProcessInput) != TASK_NONE; }`.
  **`harness-giratina.c` (33), `harness-calyrex.c` (34) and `harness-gyms.c`
  (35)** are copies of `harness-lucy.c` (which has 1-14, 20, 21, 25 and 32,
  not the scenarios kept in their own files). `harness-calyrex.c` needs the
  three lines in its header appended to the copy's `src/start_menu.c` and
  `src/item_menu.c`. In `harness.c` itself: 21
  endgame part 2 (Rustboro, loses to Glacia once on purpose); 20
  endgame part 1 (Pyramid to Rustboro, loses Scott on purpose); 14 Wallace
  hidden/shown; 12-13 Wallace probes; 11 endgame towns; 10 Devon Factory; 9
  Broker control; 8 League Abra home; 6/7 Ever Grande win/loss; 5 girl's house;
  4 Scott's house, Factory, Lati; 3 Noland/Greta loss; 2 Littleroot win; 1
  Palace exit. `harness.c.pre-*` are older copies.
- `main.c.patch`, `script.c.additions`, `text.c.additions`: apply to a
  **copy** of the repo, never the real one.
- `textwidth.py` checks new `.string` lines in `git diff` against the font
  (~208 px). `factory/render_lib.py` renders maps (plain `render_map.py`
  garbles gTileset_General and FRLG maps).

**How to run:** rsync the repo to the scratchpad excluding `build/`, `.git/`
and `pokeemerald*.gba` (but not `data/mb_*.gba`, a build input). In the copy:
`touch .histignore`, `patch -p0 < main.c.patch`, append each `.additions` file
from its first `Harness_` line on, copy `harness.c` to `src/harness.c`,
`make`, then `tools/mgba/mgba-rom-test -S 3 -R r0 -l 15 pokeemerald.gba |
grep --line-buffered "GBA Debug"`. A run takes a few minutes.

**Gotchas:**
- Runs are always a **New Game**, never the owner's save.
- Watch the right story var (`STORY_VAR`). Fast text, battle style Set.
- **Plan the path first** (collision, bounds, triggers, door types, timing)
  so one run is enough.
- Don't press B in the overworld when mashing through YES/NO prompts.
- Leaving a building means stepping **off** the door mat: walk one tile past
  the warp tile.
- Objects more than about seven tiles from the player aren't loaded yet, so
  check a far object's position only once the player is near it.
- Battles: the HP hack weakens foes and keeps the player healthy. The test
  team needs a move nothing is immune to, with PP refilled (scenario 20 uses
  Nature's Madness). A battle meant to be lost holds the player at 1 HP
  instead, and the check requires `B_OUTCOME_LOST`.
- Choose-three menus: write `gSelectedOrderFromParty`, set
  `gPartyMenu.slotId = PARTY_SIZE`, press only A. Party checks need distinct
  species and an out-of-order pick.
- A log with no TICK lines means the game froze. The BTL lines (every 300
  frames in battle) show where a battle is stuck.
