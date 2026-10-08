# Sprint: endgame towns (Giratina, Calyrex, the Gym rematches)

Project plan, 2026-10-08. Owner-approved scope: an optional **Giratina** event
in Rustboro, an optional **Calyrex** event in Mauville, and **Roxanne's and
Wattson's Gym rematches at full power**. Goal: the endgame towns have
endgame content of their own, not just story stops.

Read `CLAUDE.md`, `project-guide.md`, `handoff.md` and `storyline.md`
(Rustboro, Mauville, Hoopa's rings) before working on any of it.

---

## 1. Decisions

### Locked by the owner

- Both legendary events and both Gym rematches are in.
- Giratina's only source is the Rustboro event (it is in no Hoopa ring, the
  shop or any gift today).
- The Gym leaders fight "at full power".

### Set by the lead (the owner can veto any of these before kickoff)

| # | Question | Default | Why |
|---|---|---|---|
| D1 | What "full power" means | Six Pokémon, no gauntlet caps (any species and item the endgame shop sells), **one normal Mega** each, omniscient AI, proactive switching | Same standard as the Brains; the Elite Four's two permanent Megas stay their signature |
| D2 | Gym leader levels | **Roxanne 60, Wattson 65** | Matches the admins (60) and Maxie and Archie (65), the fights each town's liberation sits next to |
| D3 | Legendary levels | **65** for both | A step over Hoopa's legends (60): optional bosses, not free gifts |
| D4 | When each opens | Giratina and Roxanne from Rustboro's liberation (`VAR_ENDGAME_STATE` 10); Calyrex and Wattson from Mauville's (15). **Stays open after the credits** | Optional content shouldn't be missable; the post-credits save keeps a reason to travel |
| D5 | Catching | Both are catchable wild battles, **never chipped** (Rusturf Tunnel and Mauville join `IsFrontierChippedMon`'s exceptions). A knock-out or a run leaves them there to retry, as with Darkrai | No permanent misses in optional content |
| D6 | Giratina's form | The **Griseous Core** is given after the catch; holding it makes Origin Forme (Gen 9 rule, already in the engine) | The signature form is the reward |
| D7 | Calyrex's form | The **Reins of Unity** are given with Calyrex. The player fuses with whichever horse they own and can swap later (canon) | The shop's Glastrier (wave 5) and Spectrier (wave 6) finally get a payoff |
| D8 | Gym rewards | One never-sold item each, picked in Phase 1 from items the shop doesn't sell (Roxanne: a Rock-themed pick; Wattson: an Electric one) | A reason to fight beyond the fight |
| D9 | Gossip | One line per event in the existing gossip NPCs, added by the lead at integration, not a new story beat (these are optional) | Keeps `GetStoryGossipStage` untouched |

---

## 2. The three workstreams

Each runs in its own **git worktree** (a separate copy of the repo on its own
branch, so three agents can build at once without touching each other's
files). The lead merges them at the end.

### A. Giratina in Rustboro: "The Tear"

**Story.** Palkia's blast at the Factory and Hoopa's rings keep tearing
space. Giratina, ruler of the space between places, has come through in
**Rusturf Tunnel**.

1. **The clue (state 10+).** A Devon scientist on 3F reads spatial
   distortion that grows with every ring Hoopa opens. Two Rustboro
   NPCs (one in the Trainers' School) mention wrong shadows and a tunnel that
   "goes upward".
2. **The way in.** Rustboro's exits stay sealed. The scientist offers to take
   the player (YES/NO), then a fade, narration and a warp into Rusturf Tunnel,
   the same pattern as Wattson and New Mauville. In the endgame every tunnel
   exit leads back to Rustboro, never Route 116 or Verdanturf.
3. **The tunnel.** Vanilla events off in the endgame (Wanda, her boyfriend,
   the Aqua grunt, Peeko, Briney, Mike, both Rock Smash rocks hidden). Dark
   (`setflashlevel`, as in the Pike lair), with two or three small
   "wrongnesses" (an object that's back where it started, a line said
   backwards). Giratina (Altered) at the far end.
4. **The battle.** `setwildbattle SPECIES_GIRATINA, 65`. Caught: the object
   goes, the Griseous Core is given, the flag is set. Anything else: it stays.
5. **Hoopa's hint (optional, small).** In Hoopa's ring menu, a one-time line
   that one ring "won't open: something on the other side is angry", from
   state 10 until Giratina is caught.
6. **Chips.** Add `MAPSEC_RUSTURF_TUNNEL` to `IsFrontierChippedMon`'s
   never-chipped list (`src/facility.c`), so it gains Experience before the
   siphon.

**Owns:** `data/maps/RusturfTunnel/*`, `data/maps/RustboroCity_DevonCorp_3F/*`,
the clue NPCs' maps, Hoopa's ring script (hint only), the chip function in
`src/facility.c`.

### B. Calyrex in Mauville: "The True King"

**Story.** The teams proclaimed Scott Hoenn's new king. Calyrex is a real
one, and it can tell the Replica Crown is a counterfeit.

1. **The statue (state 15+).** A toppled statue of a crowned Pokémon in
   Mauville's plaza, knocked down during the occupation. Examining it: "A
   statue lies in pieces. Its crown is cracked."
2. **The legend.** The storyteller (the old man in Mauville's Pokémon
   Center) tells the King of Bountiful Harvest's story: a king who rode a
   great steed and faded when he was forgotten.
3. **The restoration.** Phase 1 picks one: pay FP, or bring a stone from New
   Mauville's generator room. Restored, the statue shows Calyrex.
4. **Calyrex appears**, weak, speaking by telepathy. It senses the Crown:
   "That is no crown. It is a chain." It asks to see the steed the player
   trusts: a **Glastrier or Spectrier** in the party. Without one: the
   storyteller's hint that "the steeds of frost and shade are sold on the
   island".
5. **The battle.** `setwildbattle SPECIES_CALYREX, 65`. Caught: it joins, the
   Reins of Unity are given (D7), the statue stays restored.
6. **Chips.** Add `MAPSEC_MAUVILLE_CITY` to the never-chipped list (harmless:
   chips are off from state 11 anyway, but it keeps the rule honest).

**Owns:** `data/maps/MauvilleCity/*` (the statue and its object only; the
endgame scenes there are untouched), `data/maps/MauvilleCity_PokemonCenter_1F/*`,
the New Mauville item if chosen, the chip function's one line (coordinate
with A at merge: same list).

### C. The Gym rematches: Roxanne and Wattson

1. **The doors.** Remove each Gym from the endgame sealed-door table
   (`src/facility.c`) once its town is freed (Rustboro Gym from state 10,
   Mauville Gym from 15). Before that, still sealed.
2. **The interiors.** In the endgame, every Gym trainer hidden, the leader at
   the back. **Mauville Gym's electric barriers** must leave a clear path
   (its switch puzzle: check every barrier state). Rustboro Gym's maze needs
   only the trainers gone.
3. **The leaders.** Talk: an endgame line (Roxanne was gauntlet 3's boss and
   knows the player; Wattson was at their side in Mauville), then the battle.
   Lose: white-out to the town's Center as usual; retry any time. Win: the
   reward (D8) once, then a post-battle line. No rematch after a win.
4. **The teams.** `TRAINER_ENDGAME_ROXANNE` (990) and `TRAINER_ENDGAME_WATTSON`
   (991), real class and pic (Leader). Six each, per D1/D2, written in
   Showdown syntax into a new `endgame-teams.md` section first, legal moves
   checked against the expansion's learnsets, item clause, everything sold by
   the endgame shop.

**Owns:** `data/maps/RustboroCity_Gym/*`, `data/maps/MauvilleCity_Gym/*`,
the sealed-door table in `src/facility.c`, `include/constants/opponents.h`,
`src/data/trainers.party`, `endgame-teams.md`.

---

## 3. Phases

| Phase | Who | What | Gate |
|---|---|---|---|
| 0 | Lead | This plan approved; the **reservations commit** on `master` (below) | Owner says go |
| 1 | A, B, C in parallel | **Design only, no build.** Each writes its section in its own doc: dialogue drafts, map changes (with coordinates checked against `map.bin` collision), state and flag use, teams (C), the D8 reward (C) and the B3 restoration choice (B). Then stops and reports | **Owner review** of all three designs |
| 2 | A, B, C in parallel | Build, harness test, commit on their branch | Each branch builds clean, its harness scenario is green, text widths pass |
| 3 | Lead | Merge, integrate, regression test, docs | `master` builds, `make check` at 15, regressions green |

The Phase 1 gate exists because dialogue and teams are the owner's taste; a
review before building costs minutes, rework after costs a sprint.

### Phase 0: the reservations commit (lead, before any agent starts)

Every agent reads its numbers from here, so no two branches touch the same
line of a shared header:

| Kind | A (Giratina) | B (Calyrex) | C (Gyms) |
|---|---|---|---|
| Flags | 0x281 `FLAG_GIRATINA_CAUGHT`, 0x282 `FLAG_HOOPA_TEAR_HINTED` | 0x283 `FLAG_CALYREX_CAUGHT`, 0x284 `FLAG_MAUVILLE_STATUE_RESTORED` | 0x285 `FLAG_ENDGAME_ROXANNE_REWARD`, 0x286 `FLAG_ENDGAME_WATTSON_REWARD` |
| Vars | 0x40F9 `VAR_GIRATINA_EVENT` | 0x40FA `VAR_CALYREX_EVENT` | none (trainer flags) |
| Trainer IDs | none | none | 990, 991 (`TRAINERS_COUNT_EMERALD` to 992) |
| Harness scenario | 33 (`harness-giratina.c`) | 34 (`harness-calyrex.c`) | 35 (`harness-gyms.c`) |
| Design doc | `sprint-a-giratina.md` | `sprint-b-calyrex.md` | `sprint-c-gyms.md` + `endgame-teams.md` |

Spare for surprises: flags 0x287, 0x289-0x28F; vars 0x40FB-0x40FF. An agent
that needs one asks the lead instead of taking it.

The commit renames those `FLAG_UNUSED_*` / `VAR_UNUSED_*` lines to the names
above and fixes `handoff.md`'s stale "free vars" line.

### Phase 3: integration (lead)

1. Merge **C, then A, then B** (C touches the most shared files; A and B
   share only the chip list, a one-line conflict at most).
2. Build; `make check` (15 known failures, no new ones).
3. Re-run the endgame scenarios that walk these towns: 21 (Rustboro), 23
   (Mauville), plus 33-35. The Gym door change must not open a Gym early.
4. Gossip lines (D9), widths checked.
5. Fold the three design docs into `storyline.md` (Rustboro and Mauville
   sections), update `handoff.md` (testing table, loose ends, reservations),
   delete the per-workstream docs.
6. One commit per merged workstream, then a docs commit.

---

## 4. Guidelines for every agent

- **Read first:** `CLAUDE.md`, `project-guide.md` (the traps), `handoff.md`
  (the harness), `storyline.md`, and this plan.
- **Stay in your lane:** edit only the files your workstream owns. Need
  something else (a flag, a shared header, another map)? Ask the lead.
- **Story rules:** the player never speaks (narrate, or the NPC echoes);
  Calyrex and Giratina speak only through narration or telepathy lines. New
  dialogue goes through `~/decomps/headless-harness/textwidth.py`
  (about 208 px a line).
- **Script traps** (`project-guide.md`): `checktrainerflag` sets the
  comparison result; never hide objects with `FLAG_TEMP_9/A/B/E/10+`; a
  dynamic menu's CANCEL is `MULTI_B_PRESSED`.
- **Vanilla maps:** don't strip the vanilla story. Gate endgame changes on
  `VAR_ENDGAME_STATE` where that's cheap; where a vanilla event must go,
  hide it in the endgame only.
- **Trainers (C):** real class and pic, item clause, legal moves (check the
  learnset files; Incineroar can't learn Parting Shot here, for example),
  everything sold by the endgame shop. Don't harness-battle a team: build it
  and check the generated `src/data/trainers.h` entry.
- **Harness (A, B, C):** one planned run per scenario. Check collision and
  events for every tile first. Runs are a New Game: set the endgame state in
  `Setup`. Test the failure paths too (no horse for Calyrex; a sealed Gym
  before liberation; running from Giratina).
- **Commits:** small, one per step, on your branch. Never pull from `RHH`.
- **Report back** with: what changed (files), what was tested (scenario,
  checks passed), anything skipped, and open questions. No silent scope
  changes.

---

## 5. Agents

Three worktree agents, one per workstream, started together after Phase 0.
Each gets this plan, its workstream letter and the Phase 1 instruction (design
only, then stop). After the owner's review, the lead sends each its approved
design and the go for Phase 2. The lead reviews every diff before merging.

Worktrees fit because the three touch different maps and different parts of
`src/facility.c`, and the shared numbers are reserved up front. If an agent
goes off track, the lead stops it; its branch is thrown away without touching
`master`.

---

## 6. Risks

| Risk | Plan |
|---|---|
| Mauville Gym's barrier puzzle leaves no path | C maps every barrier state in Phase 1, before building |
| Rusturf's vanilla events fire in the endgame | A hides all of them with endgame-only checks; harness walks the whole tunnel |
| A Gym opens before its town is freed | C's harness checks the door at state 9 and 14 (sealed) and 10 and 15 (open) |
| The post-credits continue (Frontier) can't reach the towns | Phase 1 (A) confirms the ABRA network still runs after state 18; if not, the lead decides |
| Calyrex's fusion menu misbehaves | B tests one fusion and one unfusion in the harness: it's engine code this project hasn't used yet |
| Agents collide on a shared file | The reservations commit; "ask the lead" rule; merge order C, A, B |
