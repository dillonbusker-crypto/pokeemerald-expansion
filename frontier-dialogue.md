# Battle Frontier — Dialogue Inventory & Rewrite Proposals

A pass over every NPC and sign the player can actually reach in the Battle
Frontier, what they say today, and what they could say instead so the whole
place feels like it belongs to the Ten Gauntlets. **Built** — see "Build
notes" at the end for where the build differs from this spec.

Line breaks in the proposals are loose. Final text gets reflowed to the
GBA's ~36-characters-per-line boxes when it's implemented.

---

## The problem, in one paragraph

Almost every NPC outside the six gauntlets we've rewritten still lives in
vanilla Emerald's Frontier: they talk about Battle Points, win streaks,
Frontier Brains, rental Pokémon, tournaments, Symbols, the FRONTIER PASS,
"seven TRAINERS in a row", and facilities that run completely different
rules. Meanwhile the attendants and shopkeepers talk about FP, locked teams,
Wardens and Mega Stones. The player walks between two games. The fix is a
shared **world bible** plus a rewrite of every reachable line against it.

---

## Part 1 — World bible

The facts every NPC should agree on. Most already exist in the design docs;
this just makes them the Frontier's shared reality.

**What the Frontier is now.** SCOTT's Battle Frontier has been rebuilt as
**the Ten Gauntlets**: ten gauntlets, each tougher than the last. The Battle
Tower's four mats are gauntlets 1–4; the other six facilities each host one
gauntlet after that.

**Facility-to-gauntlet map — decided.** Follows the existing door order in
`src/facility.c` (Dome, Factory, Pike, Arena, Palace, Pyramid) and puts the
Pyramid — the Frontier's "golden pinnacle" — last. Each facility's boss is
that facility's own Frontier Brain:

| Gauntlet | Facility | Format | Name | Boss |
|---|---|---|---|---|
| 1 | Tower, Singles mat | Singles | Little League | Warden Helis *(Tower lieutenant)* |
| 2 | Tower, Doubles mat | Doubles | The Second Slot | Tidewarden Nerys *(Tower lieutenant)* |
| 3 | Tower, Multi mat | Singles | The Changing Sky | Dunewarden Kasra *(Tower lieutenant)* |
| 4 | Tower, Link Multi mat | Doubles | The Turn Order | **Salon Maiden Anabel** |
| 5 | Battle Dome | Singles | The Main Event | **Dome Ace Tucker** |
| 6 | Battle Factory | Doubles | The Assembly Line | **Factory Head Noland** |
| 7 | Battle Pike | Singles | *TBD* | **Pike Queen Lucy** |
| 8 | Battle Arena | Doubles | *TBD* | **Arena Tycoon Greta** |
| 9 | Battle Palace | Singles | *TBD* | **Palace Maven Spenser** |
| 10 | Battle Pyramid | Doubles | *TBD* | **Pyramid King Brandon** |

Why each pairing fits: Anabel is the Tower's own Brain, so she guards the end
of the Tower. Tucker's vanilla ace is Salamence, and gauntlet 5's boss already
uses Mega Salamence. Noland's Factory builds teams to spec — "The Assembly
Line". Lucy's Seviper, Milotic and Shuckle suit a status/disruption gauntlet.
Greta is an aggressive fighter, suited to raw-power doubles. Spenser's vanilla
team includes Suicune, and gauntlet 9 is where box-art legendaries arrive.
Brandon's vanilla team is the Legendary Birds and the Regis — the strongest
Brain, in the final gauntlet.

**The bosses are the Frontier Brains** (gauntlet 4 onward). SCOTT rebuilt
the Frontier around them: seven Brains, now the last line of ten gauntlets.
They're the island's celebrities — NPCs gossip about them, fear them, and
are fans of them. The vanilla Dome fans' "DOME ACE" lines already work
almost as-is, now pointing at the gauntlet 5 boss.

**Gauntlets 1–3** are guarded by the **Tower lieutenants** — Helis, Nerys
and Kasra, the Warden-titled trainers Anabel keeps between new challengers
and herself. "Warden" becomes their rank.

**Implementation direction (not built yet):** the Brains' battle sprites
(`TRAINER_PIC_SALON_MAIDEN_ANABEL` and the rest), trainer classes and
overworld sprites (`OBJ_EVENT_GFX_ANABEL` and the rest) all already exist in
this build. Converting a boss is a change to its `Class`, `Pic` and `Name`
lines in `src/data/trainers.party` plus its intro/defeat text; each Brain
could also stand in their facility's lobby. Existing team designs stay
unless a Brain's signature Pokémon is worth folding in (e.g. Anabel's
Alakazam / Snorlax, Noland's rentals-as-a-theme).

**The rules, as NPCs understand them:**

- Six Pokémon, all level 50, all enter. The team is locked once a run starts.
- Full heal between every battle. Held items come back after every battle;
  bag items can't be used.
- One of each held item per team — the item clause applies to Wardens too.
- Lose and the run ends, but you keep your team and every FP you earned.
- A cleared gauntlet can't be re-entered. Only forward.
- **FP (Frontier Points)** is the only currency. Battle Points don't exist
  anymore.
- The Exchange Service Corner sells Pokémon outright and buys them back at
  half price. There are no rentals.
- Mega Evolution arrives with gauntlet 5, via the Mega Ring.

**No internal map names in dialogue.** The lounges are unlabeled houses to
the player, so NPCs refer to them by landmarks and directions ("the houses
out past the ARENA"), never "LOUNGE 3".

**Tone.** The Frontier is a proving ground people *travel* to — by the Route
103 ferry — and most of them are stuck somewhere in the middle. NPCs should
feel like other challengers at other points on the same ladder: someone who
just lost to Helis's Altaria, someone saving FP for a Choice Scarf, someone
who has only ever *heard* about the Pyramid.

---

## Part 2 — Big structural suggestions

These change *how* dialogue works, not just what it says.

**1. Progress-reactive dialogue — approved.** The best way to make the Frontier feel
alive is for NPCs to notice where the player is. Many NPCs get two or three
versions keyed to how many gauntlets are cleared: early (0–1), middle (2–4),
late (5+). A single special (e.g. `GetBuildingsClearedCount`) reading
`buildingsCompleted` is all the scripts need. Marked **🔄** below.

**2. NPCs as the tutorial layer.** The design docs have a "counterplay"
section for every gauntlet. The NPCs outside each facility can hand those
out as overheard advice before the player walks in — without ever saying
"here's the answer." Marked **💡** below.

**3. Repurpose the vanilla boards.** The rules boards, results monitors and
Ranking Hall plaques all read vanilla data (streaks, tournament trees) that
no longer means anything. They should become:

- **Rules boards** → the Ten Gauntlets rules for that facility's gauntlet.
- **Results monitors** → a plaque naming the gauntlet, its format and its
  Warden (and "Cleared" once the player beats it).
- **Ranking Hall** → the **Hall of Ten**: one plaque per gauntlet's boss,
  revealed as the player beats them.

**4. Leave the unreachable rooms alone.** Battle rooms, corridors, the
Tower elevator, the Pyramid floors and the Pike rooms are never entered —
every battle happens at the attendant. Their ~120 NPCs can stay vanilla.

**5. Sealed facilities keep their current "not open yet" warp-out** until
their gauntlet is designed. Their lobby NPCs (listed at the end) get
rewritten when that gauntlet is.

---

## Part 2.5 — The opening sequence (decided)

**Today:** the ferry drops the player in Outside West, and the moment that
map loads, `GiveFrontierStartingGrants()` (`src/new_game.c`, called from
`BattleFrontier_OutsideWest_OnTransition`) silently puts five Pokémon in the
party, adds 300 FP and the HMs. The Reception Gate's Scott scene then ends
with an offhand "feel free to visit my quarters."

**New flow:**

1. **Ferry → Outside West.** Nothing is granted on arrival.
2. **Reception Gate — Scott's welcome** (existing scene). His last line
   changes from the offhand invitation to a clear errand:
   > Before you go anywhere near the TOWER, come by my house. It's at the
   > north end of the plaza, past the BATTLE PIKE. One POKéMON won't get you
   > through the door of gauntlet one — I've got something for you.
3. **Scott's House — the team.** First visit only:
   > SCOTT: There you are! Every challenger needs six to enter a gauntlet,
   > and you've only brought one. So I put together a few of my own
   > favorites to round you out.
   >
   > They're no champions, but they're honest workers. Look after them —
   > and when you can afford better, the EXCHANGE CORNER will take them off
   > your hands.

   Then each Pokémon is handed over with the usual "{PLAYER} received
   FURRET!" fanfare — **Furret, Chinchou, Graveler, Murkrow, Roselia**, the
   same five as today. Scott adds the starting 300 FP ("a little something
   to spend") and the HMs, and closes with:
   > Now you've got six. The BATTLE TOWER is waiting. Go show me I was
   > right about you!
4. **If the player goes to the Tower first:** the attendants' "you need six
   Pokémon" line gets a first-time variant — "Hm, only one POKéMON? MR.
   SCOTT said he had something for new arrivals. You might pay him a visit
   first." Uses the same `startingGrantsGiven` flag, so no new save data.

**Implementation notes:**

- Move the `special GiveFrontierStartingGrants` call from
  `BattleFrontier_OutsideWest_OnTransition` into Scott's House, and split the
  function so each Pokémon can get its own "received" message (or have the
  script give them one at a time). `startingGrantsGiven` still guards it, so
  it can never happen twice.
- The player only has their starter at this point, so all five fit in the
  party. As a safety net, anything that doesn't fit goes to the PC like any
  gift Pokémon.
- Scott's House already runs a first-visit script (vanilla's welcome plus a
  Battle Points gift). That gets replaced by this scene; his later lines
  follow the progress-reactive plan in Part 3.
- Existing saves that already received the five are unaffected — the flag
  is already set.
- Birch's lab currently foreshadows "receiving POKéMON" at the Frontier;
  tweak it to name SCOTT as the one who'll set the player up.

---

## Part 3 — Map by map

"Now" is a short summary of the current line; "Proposed" is the rewrite.

### Reception Gate — the front door

| NPC | Now | Proposed |
|---|---|---|
| Greeter | "Welcome to the BATTLE FRONTIER!" | "Welcome to the BATTLE FRONTIER — home of the Ten Gauntlets! Ten gauntlets, ten Wardens, and only one way through: forward." |
| Facility guide | Menu explaining each vanilla facility | **Gauntlet guide.** Same menu shape, one entry per *open* gauntlet: format, name, and where it is. Sealed ones read "Not yet open — clear the gauntlet before it." 🔄 |
| Rules guide | Menu on vanilla rules (level mode, banned mons, 3 Pokémon) | **The Ten Gauntlets rules**, one topic each: Six Pokémon · Level 50 · Locked teams · Full heal · Held items · The item clause · Losing · No going back |
| FRONTIER PASS guide | Explains the Pass, Symbols, BP | **FP & your roster guide**: how FP is earned (every win, big payout per clear), that Pokémon are bought and kept forever, sell-back at half, and the L-button tools for tuning a team. |

### Outside West

| NPC | Now | Proposed |
|---|---|---|
| Boy (26,38) | "Best of all my friends, useless here" | "Back home I never lost. Here? Warden Helis's ALTARIA swept my whole team. I didn't even know you *could* do that." |
| Ferry attendant | Ferry, needs TICKET | Keep the function, point it home: "The ferry sails back to ROUTE 103. Your team, your FP — all of it will be waiting when you return." |
| Expert M (26,20) | "Is this the Dome? I won't let GENTLEMEN beat me" | "So this is the BATTLE DOME… They say every trainer inside can Mega Evolve. Hmph. So can I, once I find that Mega Ring." 🔄 (Late: "I found the Ring. Then I found out what Mega Lopunny does. Ahem.") |
| Man (27,30) | Only tough trainers are brought here | "Nobody stumbles onto this island. SCOTT invites you, you take the ferry, and then the Ten Gauntlets decide how good you really were." |
| Woman (33,41) | Arrived, will grab attention | "I just arrived! I'm going to clear all ten gauntlets with my looks and ability alone!" 🔄 (Later: "…Gauntlet 2 has doubles. Nobody told me about doubles.") |
| Fat Man (28,43) | Munch, square full of tough people | Keep — the joke works. "Munch, munch… Every one of these people has a locked team of six… Munch… I just have snacks…" |
| Gentleman (17,20) | Luck at the Dome | "Off to the DOME? In there, one Pokémon on each team changes form mid-battle. Deciding *which* of yours does is the whole art." 💡 |
| Maniac pair (13–14,44) | "Can we challenge without POKéMON? The big scary guy lends POKéMON!" | "Bro, do we even have six POKéMON?" / "The lady at the EXCHANGE CORNER *sells* them, bro. For FP. We have… zero FP." / "We're gonna need a bigger plan, bro." |
| Man (23,47) | Nothing here long ago | "There used to be seven facilities here, run by the FRONTIER BRAINS. Now it's ten gauntlets and ten Wardens. SCOTT really doesn't do anything halfway." |
| Girl (38,27) | Scared of the Pike's SEVIPER | "The BATTLE PIKE is still sealed… but I heard its Warden keeps a SEVIPER. I'm s-scared already, and I haven't even cleared gauntlet 3!" |
| Woman (45,18) | Rock-paper-scissors for the Pike | Keep the minigame: win → "I'll go take on gauntlet 2 today!"; lose → "Not lucky today. Doubles can wait until tomorrow." |
| Camper (9,47) | Who's raising the rental POKéMON? | "That's the BATTLE FACTORY. It used to rent Pokémon out. Now it's a doubles gauntlet where every team is built to a plan. I wonder who designs them all?" |
| Lass (35,5) | Battling until she gets a Symbol | "I'm going to keep battling until I clear a gauntlet. Just one! Then the next… then the next…" |
| Man (11,66) | Long dreamed of a place like this | Keep, lightly: "Ten gauntlets of nothing but battling… I've dreamed of a place like this my whole life." |
| Fisherman (31,31) | Only one who chooses fishing | Keep — pure flavor. |
| Fisherman (42,48) | Seasick on the way | "I wanted to start gauntlet 1 the moment I got off the ferry from ROUTE 103… Urrrp… Maybe after I lie down." |
| Fat Man (38,22) | Scary girl at the Pike | "Crunch… I tried snacking in the TOWER lobby and an attendant told me the item rule applies to *me* too. Crunch…" |
| Dome fans (11–12,9–10) | Squabbling over the DOME ACE | Same scene, new idol: fans of **Dome Ace Tucker**. "When TUCKER's SALAMENCE Mega Evolved, our eyes met!" / "That was *me* it looked at!" / "Fair-weather fans! Go cheer for some Tower Warden!" 🔄 |
| Man (8,5) | Those fans were once famous trainers | "Those three were famous trainers once. Then DOME ACE TUCKER beat them so thoroughly they became fans instead." |
| Pokéfan F (4,26) | Long-tailed Pokémon rumor | Easter egg about the ban list: "I heard there's a Pokémon with a paintbrush tail that's *banned* from every gauntlet! Why would they ban something so cute?" (SMEARGLE) |
| Signs: Dome / Pike / Factory | Vanilla facility slogans | "BATTLE DOME — Gauntlet 5: THE MAIN EVENT. Crowned by DOME ACE TUCKER." · "BATTLE FACTORY — Gauntlet 6: THE ASSEMBLY LINE." · "BATTLE PIKE — Sealed. Opens for those who clear gauntlet 6." 🔄 |
| Mart signs | Mart slogan | Keep. |

### Outside East

| NPC | Now | Proposed |
|---|---|---|
| Ninja Boy (20,17) | The Tower feels special | "The BATTLE TOWER holds four whole gauntlets, one mat each! Everyone starts there." |
| Man (42,15) | Conquer Frontier and League, ask MIMI | "My dream: clear all ten gauntlets. And then… I'll ask MIMI from the Lounge to be friends with me!" (keep the joke) |
| Hiker (53,6) | Pyramid too harsh, climb outside | "The PYRAMID's sealed tight. They say it's the tenth gauntlet — the last one. I'm going to be waiting right here when it opens." |
| Hex Maniac (54,16) | Thrives in darkness, Pyramid | Keep the voice, foreshadow the finale: "The PYRAMID KING waits in the dark of the tenth gauntlet… Few have seen him. Yet everyone who reaches gauntlet 9 dreams of him…" |
| Black Belt (37,32) | Ultimate team, storming the Arena | "I didn't sleep for a week and built the ultimate team! …The ARENA's still sealed, so I'm starting at gauntlet 1 like everyone else." |
| Cook (41,56) | Cheering for ZIGG | Keep — pure flavor. |
| Expert F (8,46) | Once beat a Gym Leader | "I once beat a GYM LEADER, you know. There's no LEAGUE here, though — only Wardens. And they don't give badges." |
| Triathlete M (34,41) | Did SCOTT bring you here too? | Keep, lightly: "Did SCOTT invite you too? He can spot talent, but I've never once seen him battle." |
| Rich Boy (45,47) | Busybody, can't watch at the Palace | "Your hat's crooked! And your lead's wrong! And you haven't bought a resist berry! …Sorry, I can't help myself." 💡 |
| Triathlete F (59,35) | Fast on bike and battle | "Speed is everything! …At least until gauntlet 4, where everyone learned to *change* the speed order. I'm still upset about it." 💡 |
| Twin + Man (17–18,40) | Kid better than daddy | Keep the pair: "Daddy bought me a MEGA STONE!" / "Go rack up some wins for Daddy, sweetie!" 🔄 (stone line late only) |
| Zigzagoon | Looks vacant | Keep. |
| Maniac (42,34) | Came for a pretty girl at the Arena | Keep — the payoff still works once the Arena opens. |
| Girl (51,53) | Important old man with awesome POKéMON | "An important-looking old man goes into the PALACE sometimes, even though it's sealed. His POKéMON look… legendary." (foreshadows gauntlet 9) |
| Psychic M (62,18) | Made-up Pyramid legend | Keep the gag, retarget: "The legend of the PYRAMID! When a trainer clears nine gauntlets, the PYRAMID KING shall appear! …I just made that up. Or did I?" |
| Man + Woman (10–11,21) | He lost badly at the Tower | "He'd never lost once. Then he met Warden HELIS." / "It was one ALTARIA! ONE!" 💡 (Early only; later: "…He's on gauntlet 3 now. Don't mention sandstorms.") 🔄 |
| Woman (16,30) | Enough BP for a plush doll | "I finally saved up enough FP! Choice Scarf or a new POKéMON… Choice Scarf or a new POKéMON…" 🔄 |
| Black Belt (33,14) | Wants his name in the Ranking Hall | "So this is the HALL OF TEN! Beat a gauntlet's boss and your name goes up on its plaque. I'm going to be the reason one of those changes!" |
| Couple (54,31–32) | Multi Battle Room, power of love | Retarget to doubles: "Doubles is *made* for us, darling! You Fake Out, I Protect!" / "…That's not how it works, but I love you." 💡 |
| Old Woman (58,55) | Odd tree past here | Keep (Sudowoodo easter egg) if the encounter still exists; otherwise cut. |
| Gentleman (48,41) | SCOTT's bigger objective | "Ten gauntlets, ten Wardens… SCOTT never does anything without a reason. What's waiting after the tenth, I wonder?" |
| Camper (29,14) | Sticky long-tailed POKéMON under a boulder | Keep if the Sudowoodo event exists; else cut. |
| Signs: Tower / Palace / Arena / Pyramid | Vanilla slogans | "BATTLE TOWER — Gauntlets 1 to 4. Every challenger starts here." · Sealed ones: "BATTLE ARENA — Sealed. Opens for those who clear gauntlet 7." 🔄 |
| Exchange Corner sign | "BATTLE POINT EXCHANGE SERVICE CORNER" | "FRONTIER POINT EXCHANGE SERVICE CORNER — Pokémon, items and Mega Stones for FP." |
| Ranking Hall sign | "Set your sights on new records!" | "THE HALL OF TEN — Ten gauntlets. Ten bosses. And the trainers who beat them." |

### Battle Tower lobby

| NPC | Now | Proposed |
|---|---|---|
| Four attendants | Already rewritten | Tweak only: name the number — "Welcome to gauntlet 1, Little League!" |
| Feelings Man | Easy Chat interview | Keep the mechanic; reword: "How do you feel before facing a Warden?" |
| Woman (17,8) | Win streaks are recorded | "Lose a battle and the run's over — but you keep every FP you earned. Losing still pays, a little." |
| Boy (15,9) | Can't leave until you lose or win seven | "Once a run starts, your six are locked until you win or lose. Choose them *before* you talk to the attendant." 💡 |
| Reporter | Interviews about the Tower | Keep; she interviews about "your last gauntlet". |
| Apprentice | Vanilla Apprentice feature | **Hidden (decided).** It's a vanilla Tower / record-mixing system that can't work here. |
| Rules board | Vanilla Tower rules | Ten Gauntlets rules, with a Tower page: "Four mats, four gauntlets. Singles, Doubles, Singles, Doubles." |
| Four result signs | Vanilla streak records | Gauntlet plaques: "Mat 3 — THE CHANGING SKY. Warden: DUNEWARDEN KASRA. Status: Cleared." 🔄 |

### Battle Dome lobby (gauntlet 5)

| NPC | Now | Proposed |
|---|---|---|
| Attendant | Rewritten | Keep. |
| Man (1,11) | Should've held a Pokémon in reserve | "I Mega Evolved my first Pokémon on turn one. Then the *real* threat came out, and I had nothing left." 💡 |
| Lass (14,14) | Tournament winners become stars | "Clear the MAIN EVENT and people will know your name. DOME ACE TUCKER made it the most famous gauntlet on the island." |
| Fat Man (18,14) | Met a favorite in round one | "My first opponent led with LOPUNNY. It Mega Evolved and Fake Outed me before I'd even blinked." |
| Maniac (8,14) | Watch the last tournament's results | "Did you hear? TUCKER's ace Mega Evolves into something that isn't even *sold* here. Word is you need a scarf and nerves of steel." 💡 |
| Doubles attendant | Rewritten ("not running") | Keep. |
| Tourney tree / result monitors | Vanilla tournament data | Gauntlet 5 plaque + a "Mega Evolution rules" board: one per battle, needs the Mega Ring, the stone must match. |

### Battle Factory lobby (gauntlet 6)

| NPC | Now | Proposed |
|---|---|---|
| Attendants | Rewritten | Keep. |
| Woman (3,11) | No raised team needed, but knowledge matters | "Every team in here is built around one plan — weather, terrain, TRICK ROOM or raw power. Spot it on turn one, and you're halfway there." 💡 |
| Camper (14,11) | Swapped for a weak Pokémon | "I brought my singles team to a doubles gauntlet. Spread moves hit *both* of my POKéMON. Every turn." |
| Picnicker (13,11) | Check the opponent's Pokémon | "Their PELIPPER set rain, and I just kept attacking… I should've taken the weather away first." 💡 |
| Fat Man (6,10) | Can't figure out staff hints | "The Warden here runs on sunshine, I hear. …I'm going to go stand in the rain for a while." 💡 |
| Rules board | Battle Swap rules | Gauntlet 6 rules, plus a page on the four archetypes. |

### Exchange Service Corner

Mostly rewritten already. Small tweaks:

| NPC | Now | Proposed |
|---|---|---|
| Rich Boy | "Don't know how much FP I've spent" | Keep. |
| Pokéfan F | "Leave it to your mommy!" | Keep. |
| Sailor | Items make his Pokémon tougher | "Leftovers, a resist berry, a Choice Scarf… the right item is worth more than a new POKéMON sometimes." 💡 |
| Man | Used to be dolls and cushions | Keep — it already tells the "what changed" story. |
| Girl | FP explanation | Keep. |

### Pokémon Mart

| NPC | Now | Proposed |
|---|---|---|
| Clerk | Standard | Keep. |
| Old Woman | "PRO…TE…IN? Sounds delicious" | Keep, it's funny. |
| Old Man | Souvenirs for grandson | Keep. |
| Boy | Many facilities ban items | "Bag items don't work during a run — only what your POKéMON is holding. So why am I buying POTIONS? …Habit." |

### Pokémon Center

| NPC | Now | Proposed |
|---|---|---|
| Nurse | GOLD CARD / Frontier Symbol lines | Drop the card lines; keep the heal. |
| School Kid | Unknown Pokémon | "Someone was using a POKéMON from a region I've never even heard of! The EXCHANGE CORNER sells Pokémon from *everywhere*." |
| Man | Next stop the Arena | "Next stop, gauntlet 3! I'd better check my six before I lock them in." |
| Picnicker | Every challenge with just this baby | "Giggle… I'm going through every gauntlet with just this baby! …What do you mean, six?" |
| 2F link attendants | Wireless Club | Keep; the link features are vanilla. |

### Ranking Hall → the Hall of Ten

| NPC | Now | Proposed |
|---|---|---|
| Attendant | Recognizes record-setting trainers | "Welcome to the HALL OF TEN. One plaque for each gauntlet's boss — and, once they've fallen, the name of the trainer who beat them." |
| Ninja Boy | "Is your name on this list?" | "Is your name on one of these plaques? …Wow! Which boss did you beat?" 🔄 |
| Boy (44,11) | His name's not up there | "No plaques with my name yet. I'm still on gauntlet 1…" |
| 10 record signs | Vanilla facility records | One plaque per gauntlet, in the same spots the vanilla records use (four Tower plaques, then one per facility): "GAUNTLET 5 — THE MAIN EVENT. DOME ACE TUCKER. Defeated by {PLAYER}." Unbeaten bosses read "— Undefeated —". 🔄 |

### Scott's House

| Now | Proposed |
|---|---|
| Welcomes the player to *his* Frontier, gives Battle Points, explains BP. | **First visit:** hands over the starting team, 300 FP and the HMs — see Part 2.5. **Afterwards:** recast as the host of the Ten Gauntlets. He explains *why* he rebuilt the Frontier around the Frontier Brains ("Seven facilities tested seven skills. I wanted one ladder that tests all of them, in order.") and hints there's something after gauntlet 10. He gets a new line after every gauntlet cleared. 🔄 |

### Lounges

| Lounge | NPC | Now | Proposed |
|---|---|---|---|
| 1 | Breeder | Judges a Pokémon's IVs | Keep the mechanic; reframe: "IVs? With the Frontier's tools anyone can tune those. Let me tell you what I *really* see…" Could judge nature fit or BST tier instead. |
| 1 | Two boys | "He said my Pokémon is outstanding" | Keep. |
| 2 | Frontier Maniac + apprentices | Reports the "hottest" facility | Becomes the Frontier's news desk, keyed to progress: "Word is gauntlet 3's Warden lives and dies by sandstorms." Always one gauntlet ahead of the player. 🔄💡 |
| 2 | Triathlete F | "What is this place?" | Keep. |
| 3 | Gambler → **the Broker** | Bets the player's BP on another trainer | **Decided:** rebranded as the Broker, who sells one piece of the next gauntlet's stock early. Full design in `broker-spec.md`. |
| 3 | Watchers | Commentary on the Dome's bettors | His nervous customers — see `broker-spec.md`. |
| 4 | Woman, Cook, Man | Interviews / restaurant / strategy break | Keep; small FP/Warden touches. |
| 5 | Nature Girl | Reads a Pokémon's nature | Keep — natures still matter. Give her one Mega line: "This one wants to change shape so badly!" |
| 5 | Gentleman, Black Belt, Little Boy | React to her | Keep. |
| 6 | Trader (SKITTY trade) | In-game trade | Keep. |
| 7 | Two move-tutor ladies | Teach moves for BP | Convert to FP. The L-button menu already covers level-up moves, egg moves and TMs, so these two become the Frontier's **tutor-only move** teachers — the moves the L menu can't reach. |
| 7 | Sailor, Gentleman | React to the tutors | Keep. |
| 8 | Ninja Boy | Talent vs. liking something | Keep. |
| 8 | Man | Has everything except POKéMON | "I have knowledge, strategy, luck, guts, spirit and bravery! …Six POKéMON? At level 50? Hm." |
| 8 | Woman | Explains the FRONTIER BRAINS | Explains the **Wardens**, and that they replaced the Frontier Brains. This is the natural place to canonize the lore. |

---

## Part 4 — Sealed facilities (rewrite with their gauntlet)

Their lobbies are only ever seen for one frame before the "not open yet"
warp-out, so they can wait until gauntlets 7–10 are designed. Direction:

- **Pike lobby** (gauntlet 7): the SEVIPER-fearing girl's rumor pays off
  here. The Hiker and Twin currently talk about status conditions and luck,
  which could fit a gauntlet themed on status or disruption.
- **Arena lobby** (gauntlet 8): its three NPCs talk about judging and
  aggression — a natural fit for a raw-power doubles gauntlet.
- **Palace lobby** (gauntlet 9): nature and Pokémon's hearts — the "important
  old man" from Outside East could be its Warden.
- **Pyramid lobby** (gauntlet 10): the Hex Maniac hint-giver becomes the
  voice of the finale. The legend from Outside East pays off.

---

## Part 5 — Decisions

**Decided:**

1. **Facility order for 7–10:** Pike, Arena, Palace, Pyramid (see Part 1).
2. **The Frontier Brains are the bosses** from gauntlet 4 on; gauntlets 1–3
   keep their Tower lieutenants (see Part 1). Every boss-name reference in
   the proposals above (Helis's Altaria, Tucker's fans, "the Warden of the
   Dome"...) follows the new names when implemented — e.g. the Outside West
   fans idolize the DOME ACE, TUCKER, as in vanilla.
3. **Progress-reactive dialogue:** approved.
4. **The Gambler becomes the Broker** — sells one piece of the next
   gauntlet's stock early. See `broker-spec.md`.

5. **The Ranking Hall becomes the Hall of Ten**, with live plaques. The
   ten record plaques map one-to-one onto the ten gauntlets, "beaten" is
   already in `buildingsCompleted`, and no new save data is needed. The
   plaques stop opening the vanilla records screen, which only shows data
   this game never produces. The name works whether a gauntlet's boss is a
   Frontier Brain or a Tower lieutenant.
6. **The Apprentice is hidden.** A vanilla Tower / record-mixing feature
   that can't work here. Hiding it is one line in the Tower lobby's
   on-transition script (always set `FLAG_HIDE_APPRENTICE`); its save data
   (`playerApprentice` and `apprentices[]` in SaveBlock2) could be reclaimed
   later if save space gets tight.

7. **"Gauntlet", not "building".** The ten sets of battles are **gauntlets**
   (the project is the **Ten Gauntlets**). "Building" now means only the
   physical Frontier structures — the Tower *building* holds gauntlets 1–4.
   The design docs are already converted (the `building-0N.md` files are now
   `gauntlet-0N.md`). The patch converts the rest:
   - **In-game text:** every player-facing line that means the challenge —
     Scott's welcome, the Exchange Corner, the completion messages. The
     Reception Gate's facility guide keeps "building" where it describes the
     structures ("The BATTLE PALACE is the red building…").
   - **Code names** (recommended, since they're read by whoever maintains
     this): `FACILITY_BUILDING_N` → `FACILITY_GAUNTLET_N`,
     `buildingsCompleted` → `gauntletsCompleted`, `unlockBuilding` →
     `unlockGauntlet`, `FacilityCompleteBuilding` →
     `FacilityCompleteGauntlet`, the `sBuildingNPool` tables, the
     `Facility_BN_BuildingComplete` script labels, and the "Ten Buildings:"
     comment tags. A rename only — the save layout doesn't change.

Nothing is left open. Everything above is decided and waiting to be built
alongside `broker-spec.md`.

---

## Easter eggs

Designed in `easter-eggs-spec.md`: the Artisan Cave side quest (FLOTSAM, an
ex-TEAM AQUA smuggler; the odd tree; the Broker's Master Ball; LOOKER; and a
choice between Latios and Latias), hints toward an
end-game battle with SCOTT, the Hall of Ten's eleventh plaque, a disguised
Ditto, a support group for banned Pokémon, the Frontier Brains loitering
before their battles, and a strategist who hints at each gauntlet's
counterplay.

---

## Build notes

Everything in Parts 1–5 is built, with these differences:

- **Progress special:** `GetGauntletsClearedCount` (`src/facility.c`) —
  gauntlets clear strictly in order, so it's also "the highest cleared".
  Every 🔄 line branches on it; no new save data.
- **Reception Gate guides** talk the player through their topic instead of
  showing the old menus. The gauntlet guide names the player's *next*
  gauntlet and where it is.
- **Lounge 7 move tutors** now charge FP (the vanilla Battle Point prices ×
  10), but **still teach vanilla's move lists**. Switching them to
  tutor-only moves is left for later: their teaching path uses the
  summary-screen move swap that the Teach TM tool's notes link to earlier
  heap corruption (`data/scripts/debug.inc`), so it deserves its own careful
  pass.
- **Lounge 2's Frontier Maniac** is a progress-reactive news desk, always one
  gauntlet ahead of the player.
- **Kept as-is:** the Old Woman and Camper's "odd tree" hints (the Sudowoodo
  still shakes when spoken to), the Pokémon Center nurse's vanilla trainer-
  card lines (shared code, and they only trigger on a vanilla card rank), the
  Wireless Club attendants, and the sealed facilities' lobby NPCs (Part 4).
- **Dead vanilla text:** the replaced scripts (old menus, the Gambler's bets,
  Scott's Battle Points gift) are left in their files but unreferenced, the
  same way the vanilla Tower and Dome attendants were. That's where the
  remaining "Battle Points" strings live; none can appear in-game.
- **Dome extras:** the old tournament-tree board is a poster of TUCKER that
  gets defaced ("{PLAYER} WAS HERE") once he's beaten.


---

## The rival's rematch (built)

The Route 103 battle is a sham: the player's level 50 starter against the
rival's level 5 one. Once SCOTT has handed over the starting team, the rival
(MAY for a male player, BRENDAN for a female one) stands in front of the
Battle Tower door and won't move until the player accepts a fair rematch.

- **Script:** `BattleFrontier_OutsideEast_EventScript_Rival`. Visibility is set up
  in `BattleFrontier_OutsideEast_EventScript_SetupRival` (needs
  `HasReceivedFrontierStartingGrants`, hidden once
  `FLAG_FRONTIER_RIVAL_REMATCH_DONE` is set).
- **Loss:** `trainerbattle_earlyrival` with `RIVAL_BATTLE_HEAL_AFTER`, so there's
  no whiteout. The team is healed and the rival stays for another try.
- **Win:** the rival storms off, the party is healed, and the Tower opens.
- **Teams:** `TRAINER_FRONTIER_RIVAL_{MAY,BRENDAN}_{FIRE,WATER,GRASS}` in
  `src/data/trainers.party`. Level 50, 31 IVs, no held items, gauntlet 1 pool
  species. Mightyena, Masquerain, Corsola, Kirlia, Plusle, then the rival's
  starter at its middle stage, picked to beat the player's starter (Combusken
  vs Quilladin, Marshtomp vs Combusken, Grovyle vs Frogadier).
