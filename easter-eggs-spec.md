# Battle Frontier — Easter Eggs & the Artisan Cave Side Quest

Decided with the owner. **Built** (see "As built" at the end for where
everything lives and the two places the build departs from the design). Follows the world bible in `frontier-dialogue.md`
(including: no internal map names like "Lounge 3" in dialogue).

| # | Easter egg | Status |
|---|---|---|
| 1 | The Artisan Cave side quest (replaces the odd-tree idea) | Built |
| 2 | Hints toward an end-game battle with SCOTT | Hints built; the battle itself comes after gauntlet 10 |
| 3 | ~~The Hall of Ten's eleventh plaque~~ | Removed (eight gauntlets: the Mega Pillar is in the Factory now; the plaque is the Hall of Eight's header) |
| 4 | A Ditto disguised as an NPC | Built |
| 5 | The banned Pokémon support group | Built |
| 8 | The Frontier Brains loitering before their battles | Built |
| 9 | A strategist who hints at the current gauntlet's counterplay | Built |

(#6 was dropped; #7 is replaced by #1.)

---

## 1. The Artisan Cave side quest

**Unlocks once gauntlet 4 is unlocked** — that is, after the third boss
(DUNEWARDEN ROXANNE) falls. A small crime story told across the
Frontier, ending with the player choosing between **Latios and Latias** —
they keep one, and the other is gone for good.

### The map, as it actually is

Checked against the map data:

- **Artisan Cave has two entrances.** The **East** one (Outside East, (28, 7))
  is at the top of a narrow corridor beside the Hall of Ten. It is
  **exit-only**: a one-way ledge (row 9) drops the player into the corridor,
  and nothing climbs back up. The **West** one (Outside West, (39, 55))
  is on a small landing reachable **only by water**.
- **The odd tree (the Sudowoodo, Outside East (54, 62)) is a real gate.** It
  stands on the only land tile that touches a pool below the plaza. That pool
  drains down a **waterfall** into the southern sea — and that sea is the
  only way to the West entrance. (The pool in the plaza itself is enclosed.)
- **Riding down the waterfall needs only Surf** (the current pushes the
  player down). **Climbing back up needs Waterfall.**
- **Wild Smeargle** (a permanently banned Pokémon) live in the cave today.

### The route the quest uses

1. Clear the Sudowoodo.
2. **Surf** into the pool behind it and ride down the waterfall.
3. Surf west to the landing and enter the **West** entrance.
4. Latios and Latias wait just inside.
5. Back out, and climb the waterfall with **Waterfall** to return to the
   plaza.

To make that the only route:

- **Block the East entrance from the plaza side.** A construction worker
  stands in the corridor's one-tile-wide stretch (Outside East (28, 16)):
  "Rockslide in the cave. Nobody goes in this way." After the legendary is
  caught he lets the player through from inside — "…I didn't see anything."
- **Stop the player stranding themselves.** Stepping onto the launch point
  behind the Sudowoodo checks the party for Waterfall. Without it: "The
  current only runs one way. Without a POKéMON that knows WATERFALL, you'd
  never get back up." — and the player stays put. (The HMs are already in
  the bag; teaching them uses the L-button menu's Teach TM tool.)
- **Disable wild encounters in Artisan Cave** — removes the Smeargle
  loophole for good.

### The characters

**FLOTSAM** — the quest-giver. A washed-up ex-TEAM AQUA grunt (sprite:
`OBJ_EVENT_GFX_AQUA_MEMBER_M`). TEAM AQUA disbanded after the events of
Emerald; he drifted to the Frontier and into small-time smuggling. He used to
run crates for the Broker by boat until the Broker cut him loose for talking
too much. Jittery, greedy, and a coward. He knows the southern sea better
than anyone — which is how he spotted Latios and Latias nesting in a cave he
can't reach. The WAILMER PAIL is an old AQUA prop he never gave back.

**LOOKER** — the detective who replaces him at the end. The International
Police detective from the main series, as a cameo: there's no LOOKER sprite
in this build, so he uses `OBJ_EVENT_GFX_POLICEMAN`, with his name and his
trademark over-dramatic delivery.

**The Broker** — gets one extra line tying him to FLOTSAM (step 4).

### The story, step by step

| Step | Where / who | What happens |
|---|---|---|
| 0 | Before gauntlet 4 is unlocked | FLOTSAM is there but won't deal: "You? Nobody's heard of you. Come back once you've taken down three of the FRONTIER's bosses — then maybe we'll talk." |
| 1 | **FLOTSAM** — hidden at the end of the quiet dead-end path that leads down to the odd tree (Outside East, the path north of (55, 62)). The player has to find him. | "Psst. There's a cave out west you can only reach by sea. Two rare POKéMON are nesting in there — a red one and a blue one. I'd grab 'em myself, but… there's this tree. And I can't swim. Long story.<br><br>That tree's no tree. It's standing on the only way down to the water. Here — water it. You didn't get this from me." Gives a **WAILMER PAIL**. |
| 2 | The odd tree | With the pail: "{PLAYER} watered the odd tree. It shrieked — it was a SUDOWOODO! — and fled." The tree is gone for good. No battle; it just runs (decided). |
| 3 | FLOTSAM | Now scared: "You actually did it? People SAW you! If anyone asks, I don't know you. …Look, I'm out. But there's a guy who's been doing this a lot longer than me. I used to run crates for him. Tell him FLOTSAM sent you. …Actually, don't." This points the player at the Broker (no map names). |
| 4 | **The Broker** | First, a reaction: "FLOTSAM sent you? That kid never could keep his mouth shut." Then a new line in his shop: **"Illegal item"** — a **MASTER BALL** for **1,000 FP**. Doesn't use up that gauntlet's deal. "Where'd I get it? Where do you think?" |
| 5 | FLOTSAM | "I said I'm DONE helping. You've got that fancy trainer menu, don't you? Figure it out yourself." (A nudge toward teaching Surf and Waterfall with the L menu.) |
| 6 | **Artisan Cave, just inside the West entrance** | **Latios and Latias**, side by side as idle overworld sprites. Talking to either one starts a **wild battle at level 50** with that one. Once it's caught, the other takes flight: "LATIAS let out a cry and flew off deep into the cave…" — and is gone for good. The player keeps the one they caught. |
| 7 | Where FLOTSAM stood | He's gone. **LOOKER** is there instead: "I am LOOKER, of the International Police! We have been tracking this FLOTSAM for weeks. Illegal sales… tampering with protected POKéMON… We took him in this very morning.<br><br>…You would not happen to know anything about that, would you? …No? Hmm. Very well. Carry on." |

**Edge cases:**

- **If the chosen one faints** instead of being caught, both stay (it
  reappears the next time the player enters the cave). The other only flies
  off once one of them is actually caught.
- **If the player loses the Master Ball** somewhere else (e.g. throws it at a
  wild Pokémon off-island) and hasn't caught the legendary, the Broker sells
  another. Otherwise it's a one-time purchase.
- **Soft-lock safety:** the Waterfall check at the launch point, plus the
  worker letting the player out through the East entrance after the catch.

### Rumors — how an exploring player finds it

Four NPCs, spread across the Frontier, each point at a different piece of the
quest. None names a map, and together they lead an explorer to it:

| NPC | Where | Rumor |
|---|---|---|
| **Old Woman** (the odd-tree hinter) | Outside East, south-east, near the odd tree | Keeps her "odd tree" line, and once gauntlet 4 is unlocked adds: "…And lately there's been a shifty-looking man skulking down the path to it. Up to no good, I'd wager." |
| **Camper** (the "sticky Pokémon" one) | Outside East, north, by the corridor beside the Hall of Ten | "That corridor up there leads to a cave, but they closed it after a rockslide. …I swear I heard something singing in there, though. Two voices." |
| **Pokéfan F** (the paintbrush-Pokémon hunter) | Outside West plaza | Her Smeargle hunt gains a clue: "They say the paintbrush POKéMON used to live in a cave on the west side — the one you can only reach by water. But they're all gone now. Something else moved in." |
| **School Kid** | Pokémon Center | "I saw two POKéMON flying low over the southern sea — a red one and a blue one, fast as jets! Where do you think they were going?" |

The two sighting rumors (Camper, School Kid) are available from the start,
as foreshadowing; the Old Woman's "shifty man" line only appears once the
quest has unlocked, so it points straight at FLOTSAM.

### The prize — Latios or Latias (decided)

Both are **600 BST**. That's **one point over gauntlet 4's 599 cap** — on
purpose: the quest opens as gauntlet 4 does, and a player who finds it gets a
genuine edge a gauntlet early. From gauntlet 5 on they're within the cap. The
pair
makes a real choice: **Latios** is the special attacker (130 SpA, 110 Spe),
**Latias** the bulkier support (130 SpD, Recover, Tailwind-style utility).
Both have Levitate.

**Knock-on changes:**

- **Remove Latios and Latias from gauntlet 6's shop wave.** They're
  currently sold there (Strong, 700 FP — `src/facility_shop.c`). Left in, the
  one the player passes up would be just 700 FP away, and the choice would
  mean nothing. The cave becomes the only source of either.
- **Their Mega Stones (Latiosite, Latiasite) stay unsold.** Mega Latios and
  Mega Latias are 700 BST; they belong with the Mega legendaries the design
  doc saves for gauntlet 10.
- No CPU trainer uses either, so nothing else changes.

### Implementation notes

- **New save state:** one variable for the quest's step (0–7), plus flags for
  "Latios/Latias caught" and "Master Ball bought". FLOTSAM, LOOKER, the
  worker, and Latios and Latias are object events whose visibility follows
  those.
- **The odd tree** stays at (54, 62); its script checks for the Wailmer Pail
  and the quest step. Its "fled" state reuses its existing hide flag,
  `FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO`.
- **The Waterfall check** is a coordinate trigger on the launch tile, using
  the scripting system's party-move check.
- **Latios and Latias** use `OBJ_EVENT_GFX_SPECIES(LATIOS)` /
  `OBJ_EVENT_GFX_SPECIES(LATIAS)` — every species has an overworld sprite in
  this build (`OW_POKEMON_OBJECT_EVENTS`). Each triggers its own wild
  battle; a successful catch hides both objects and sets the caught flag.
- **Artisan Cave's wild encounters** are removed from
  `src/data/wild_encounters.json`.
- **The Broker's "Illegal item"** option appears once the quest reaches
  step 4.

---

## 2 & 3. Hinting at a battle with SCOTT

SCOTT will be fought after gauntlet 10. For now, the game only hints.

**Already in the game:** two NPCs who've "never once seen him battle", and
SCOTT's own line after gauntlet 10 ("There's something after the tenth that
I haven't told anyone about").

**New hints:**

- ~~**The Hall of Ten's eleventh plaque** (#3).~~ Removed with the trim to
  eight gauntlets; the plaque now reads "THE HALL OF EIGHT".
- **Six Poké Balls in SCOTT's house.** A shelf behind his desk: "Six POKé
  BALLS, polished to a shine. Not a single scratch on any of them." After
  gauntlet 10: "…One of them twitches."
- **The Frontier Brains know something.** Once beaten, a Brain's loitering
  line (see #8) can include a sideways remark — e.g. ANABEL: "Has SCOTT ever
  told you who taught all of us?"

---

## 4. A Ditto in disguise

An ordinary-looking NPC in the Outside West plaza whose line is slightly
*off* — it repeats what the last NPC the player spoke to said, word for word.
Talk to it a second time and it gives itself away: "…Ditto!" It turns into
a Ditto and bounces off the map. One line afterwards from a nearby NPC:
"Banned from every gauntlet. …Can't imagine why."

Implementation: an NPC object and a hidden Ditto object
(`OBJ_EVENT_GFX_SPECIES(DITTO)`); the second talk hides the NPC, shows the
Ditto, moves it off-screen and sets a flag so it never returns. The "repeat
the last line" trick can be a fixed line instead if tracking the last NPC is
awkward — e.g. it recites the ferry attendant's greeting.

---

## 5. The banned Pokémon support group

The empty house on the Outside East side (Lounge 9 — currently one silent
NPC) becomes a support group of trainers whose Pokémon are banned:

- **Wobbuffet's trainer:** "Shadow Tag, Encore, Counter… He only ever wanted
  to help. And they call HIM the problem?"
- **Shedinja's trainer:** "One HP! One! How is that fair to anyone? …They
  said something about Wonder Guard."
- **Palafin's trainer:** "It was only 457 BST when I walked in!"
- **Wishiwashi's trainer:** "It's small. It's so small. Until it isn't."
- **The group leader:** "Welcome. We're all friends here. Nobody judges.
  …Did you bring a SMEARGLE? We're still waiting on our SMEARGLE member."

---

## 8. The Frontier Brains, before their battles

Each Frontier Brain loiters outside their own facility until the player
beats them, then changes their line:

| Brain | Where | Before | After |
|---|---|---|---|
| ANABEL | Outside the Battle Tower | "The last mat is mine. Take your time on the first three — I'll know when you're ready." | "You've got the TOWER. Now let's see what the rest of them make of you." (+ the SCOTT remark from #2) |
| TUCKER | Outside the Battle Dome | Practicing bows. "Audience of one? I'll take it. See you in the main event!" | "Encore, encore! …No? Fair enough. You earned the crown." |
| LUCY | Outside the Battle Pike (45, 29), once gauntlet 5 is cleared | Staring at the door. "Every team in there takes one of four roads. Read yours early." | "...You beat me. SCOTT asked about you afterwards. More than once." |
| SPENSER, BRANDON | Outside their sealed facilities | Shown only once their gauntlet exists. SPENSER is the "important-looking old man" the Outside East girl mentions. | — |

NOLAND and GRETA aren't gauntlet bosses any more: they're SCOTT's henchmen,
first met in Artisan Cave (storyline.md).

A Brain only appears once the player has reached their gauntlet's facility
(e.g. TUCKER once gauntlet 4 is cleared), so they don't give the future away.
Their overworld sprites already exist (`OBJ_EVENT_GFX_ANABEL` and the rest).

---

## 9. The strategist

The Man in the house on the east edge of Outside West (Lounge 4) already
talks about "plotting strategy and combos". He becomes the Frontier's
unofficial coach: one hint for the player's **current** gauntlet, drawn from
its design doc's "Counterplay" section, framed as overheard wisdom rather than
the answer.

| Gauntlets cleared | Hint |
|---|---|
| 0 | "A Dragon Dance sweeper only needs one free turn. Don't give it one." |
| 1 | "In Doubles, the move that hits both sides is worth more than the one that hits hardest." |
| 2 | "The best answer to a weather team isn't to resist it. It's to take the weather away." |
| 3 | "Speed isn't something you have. It's something you set." |
| 4 | "A setup sweeper is only as good as its setup turn. Take the turn away, or be faster than it." |
| 5 | "Every one of those teams is a chain. Break the link it can't replace." |
| 6+ | "I'm out of advice. You've gone further than I ever did." |

---

## Decisions

1. **The prize is a choice between Latios and Latias** — the player keeps one;
   the other flies off for good.
2. **The odd tree just flees** — no battle.
3. **SCOTT's team** will be an Ubers-grade, deliberately broken team in the
   same spirit as gauntlet 10's boss. It gets designed with gauntlet 10; only
   the hints (#2 and #3) are built before then.

---

## As built

**Two design pieces were dropped** after checking the map data: the East
entrance's ledge is one-way, so the cave can't be entered from the plaza,
and walking out through it always gets the player home.

- **No construction worker.** The ledge already blocks the East entrance
  from outside, which was his whole job.
- **No Waterfall check.** Its purpose was soft-lock safety, and the cave's
  exit already provides that. The quest needs only **Surf**: ride down the
  waterfall, surf to the landing, go through the cave, walk out East and hop
  the ledge. The Camper's rumor now describes the ledge rather than a
  rockslide.

**Save state:** `VAR_ARTISAN_QUEST_STEP` (was `VAR_UNUSED_0x404E`; 0 none,
1 pail given, 2 tree fled, 3 FLOTSAM named the Broker, 4 Broker reacted,
7 caught), `FLAG_ARTISAN_LATI_CAUGHT` (0x20), `FLAG_FRONTIER_DITTO_REVEALED`
(0x21). No "Master Ball bought" flag was needed: the Broker offers it while
the quest is at step 4+, nothing is caught, and there's no Master Ball in the
bag or PC.

| Piece | Where |
|---|---|
| FLOTSAM / LOOKER | Outside East (54, 59), the dead-end nub off the path down to the tree. Swapped by temp flags in `BattleFrontier_OutsideEast_OnTransition` |
| Odd tree | `BattleFrontier_OutsideEast_EventScript_Sudowoodo` (talk, with the pail) and `_WaterSudowoodo` (also run by the bag's WAILMER PAIL, `src/item_use.c`). It jumps away; no battle |
| Broker | `BattleFrontier_Lounge3_EventScript_Gambler`: FLOTSAM reaction, "Illegal item" shelf, MASTER BALL for 1,000 FP |
| Latios / Latias | Artisan Cave B1F (16, 46) / (17, 46), just inside the West entrance. L50 wild battles; temp hide flags, so a fainted one returns on re-entry |
| Shop | Latios and Latias removed from gauntlet 6's wave (`src/facility_shop.c`) |
| Wild Smeargle | Both Artisan Cave encounter tables deleted from `src/data/wild_encounters.json` |
| Rumors | Old Woman (Outside East), Camper (Outside East corridor), Pokéfan F (Outside West), School Kid (Pokémon Center) |
| Brains | ANABEL (19, 14) beside the Tower door, always; TUCKER (21, 17) beside the Dome once gauntlet 4 is cleared; LUCY (45, 29) at the Pike once gauntlet 5 is cleared. Each changes lines once beaten, with a SCOTT remark. SPENSER and BRANDON get added with their gauntlets |
| Ditto | Outside West (42, 41), a WOMAN_1 who recites the ferry attendant's greeting; the second talk reveals it, and it bounces away from the player. The wandering woman at (33, 41) comments until the player leaves the area |
| Support group | Lounge 9, in a circle around SMEARGLE's empty seat |
| Strategist | Lounge 4's Man, one hint per gauntlets-cleared count |
| SCOTT hints | Master Ball on a plaque in SCOTT's house (4, 2) (the eleventh plaque is gone) |

---

## Revision: the florist, the betrayal, and no HMs (built)

Supersedes the step table above where they differ.

**SCOTT bans HMs.** None are given with the starting team, older saves lose
them on entering the Frontier's outdoor maps (`RemoveFrontierHMs`), and the
starting Chinchou runs Scald instead of Surf. Surf now comes only from
level-up learnsets via the L-menu's Move Relearner: Slowbro and Slowking (Lv
30), Milotic (40), Tentacruel (46), all sold by gauntlet 2. ("Teach TM" only
covers `FOREACH_TM`, which has no HM moves.)

| Step | What happens |
|---|---|
| 0 | FLOTSAM, before 3 bosses: "None of your business... beat a few bosses and maybe I'll loop you in." After 3: the pitch (cave down the waterfall, the tree, the florist who won't talk to him). No pail. |
| 1 | **The florist** (replaces the Rich Boy above the Battle Palace, (45, 47)): before 3 bosses she hints and cuts herself off; after, she asks for a LEAFEON (yes/no, party pick, yes/no) and trades it for the WAILMER PAIL (`FLAG_FRONTIER_FLORIST_TRADED`). |
| 2 | The tree flees when watered (unchanged). |
| 3 | FLOTSAM is paranoid, quits, and points to the BROKER - but doesn't know where he is now. |
| 4 | The BROKER reacts ("FLOTSAM sent you?") and offers the MASTER BALL (800 FP). |
| 5 | Buying it (or already having one) puts FLOTSAM on the tree's old tile - the only way down to the water. He betrays the player: a singles battle, Frontier rules, heal-and-retry on a loss (`TRAINER_FRONTIER_FLOTSAM`: Crobat, Alolan Muk, Crawdaunt, Kingdra, Weavile, **Mega Sharpedo** - the player's first Mega encounter, before they have the Mega Ring). |
| 6 | Beaten, he sneers that SCOTT bans HMs so the player can't Surf, clocks the L menu, and bolts - dropping 300 FP. Latios and Latias only appear from this step on. |
| 7 | Caught. LOOKER: FLOTSAM was caught leaving the Frontier with every POKéMON wiped out - who beat him? |

---

## Revision: the quest is required, and the shop is down (built)

**Gauntlet 4 stays locked until a Latias or Latios is caught.** While the
quest is required and unfinished (gauntlet 3 cleared, `FLAG_ARTISAN_LATI_CAUGHT`
unset), `IsFrontierPOSDown()` is TRUE: the island's "POS system is down".

- **The economy is protected, with room to spare.** Clearing gauntlet 3 pays
  1,200 FP (six pool wins at 100, plus 600 for the boss). The quest costs 900:
  a LEAFEON (300) and the Broker's MASTER BALL (**600**). Every other FP sink
  is shut until the Lati is caught, so the player can't spend themselves into
  a soft lock, and the spare 300 simply carries over:
  - **Exchange Corner:** every keeper says the POS is down. The Pokémon keeper
    mentions one LEAFEON that "keeps showing up" (you probably don't want
    it), and sells it for 300 FP once the florist has asked for one
    (`FLAG_FRONTIER_FLORIST_ASKED`).
  - **The Broker:** regular deals are off; only the MASTER BALL "under the
    counter".
  - **Lounge 7 move tutors:** closed ("the FP registers are down").
  - **Gauntlet 4's attendant:** the mat is closed, with a hint toward the
    PALACE, where the Old Woman's rumor leads to FLOTSAM.
- **Surf can't soft-lock either.** Once FLOTSAM is beaten (step 6) the Pokémon
  keeper's system is "partly back up" and sells only the four level-up SURF
  learners: Slowbro and Slowking (150), Tentacruel (200), Milotic (400).
  FLOTSAM's dropped 300 FP covers the cheaper three.
- **FLOTSAM is gauntlet 3 strength:** every species and item buyable by then
  (Crawdaunt's Life Orb became a Muscle Band), with Mega Sharpedo as the one
  deliberate exception.
- **The system comes back on once the player collects the SCRAMBLER from
  LOOKER** (who appears after the catch), not at the catch itself, so the
  player can't skip him. Until then, gauntlet 4's attendant points to "a
  detective from the International Police… out past the PALACE".
- **Scott's men.** After the catch, Scott stops the player at the Battle Tower
  door to mention a ruckus in the cave and that he's sending men in. That
  nudges the player back toward the cave and LOOKER. With the SCRAMBLER in hand,
  two men in suits are waiting in B1F (a one-time scene, then "Scram, kid").
  They leave once gauntlet 4 is cleared, and the cave closes for good:
  "FRONTIER staff has closed the cave."
- **Metagross is never offered on gauntlet 4**, by the Broker or his cousin.
  Steven hands one over right after it. The normal shop still sells it from
  gauntlet 5 on.
