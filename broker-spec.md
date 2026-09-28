# The Broker — Spec

A rebrand of vanilla Emerald's Frontier Gambler in Lounge 3. The Broker sells
the player **one piece of the next gauntlet's shop stock early** — an item
outright at a premium, or a Pokémon on loan — before that gauntlet is cleared.
It hands the player a small share of the power gap the design otherwise
reserves for bosses, at a price and with a risk.

**Built.** The Lounge 3 script is `BattleFrontier_Lounge3_EventScript_Gambler`
(the old label, kept so the map needn't change); the logic is the
`FacilityBroker*` specials at the end of `src/facility_shop.c`; loans resolve
in `FacilityCompleteGauntlet()` / `FacilityAbandonRun()` (`src/facility.c`),
and `Facility_BrokerLoanNews` (Battle Tower lobby scripts) reports the result
after every run. A loaner is identified by Original Trainer "BROKER" **plus**
the in-game-trade met location, so a player who names themselves BROKER is
safe; keeping one re-tags only the OT name and gender, so it can't change
shininess.

---

## Where

**Lounge 3**, the house on the far east edge of Outside East (door at
(65, 31), level with the Battle Arena, south of the Pyramid). The Broker is
the existing Hiker NPC in the left-middle of the room. The vanilla Gambler's
script (bets on Battle Points, gated on three Silver Symbols) is replaced.

---

## The rules

**Whose stock.** The player is about to take on gauntlet **N** (gauntlets
1 to N−1 cleared). The Broker sells from **gauntlet N's shop wave** — the
entries with `unlockBuilding == N`, which normally appear only after N is
cleared. When every gauntlet is cleared, he has nothing left to sell.

**Two shelves, one deal.** Talking to him offers two options:

- **An item** — bought outright, the player keeps it.
- **A Pokémon** — on loan.

He shows **three items and three Pokémon**, drawn at random from that wave.
The player picks **one thing, total, per gauntlet** — either an item or a
Pokémon, never both.

**The stock is fixed per gauntlet.** The random picks are derived from the
gauntlet number and the player's trainer ID, so saving, reloading or talking
to him again never rerolls them. They change when the next gauntlet's wave
becomes his stock.

**Prices.**

| | Price | Keep it? |
|---|---|---|
| Item | **1.5×** its shop price (rounded to the nearest 10 FP) | Always |
| Pokémon | **0.5×** its shop price | Only if gauntlet N is cleared |

**The loan.** A Pokémon bought from the Broker is a loaner until gauntlet N
is resolved:

- **Clear gauntlet N** (beat its boss) → the Pokémon **becomes the player's**
  for good. It's re-tagged as the player's own, and from then on it's a
  normal roster Pokémon (sellable, and so on).
- **Any run of gauntlet N ends without clearing it** (a loss or a quit) →
  the Broker's courier **collects it**. Its held item goes back to the bag
  first. It doesn't matter whether the loaner was in the party for that run.
- Either way, **the deal for gauntlet N is spent.** A collected loan doesn't
  reopen the Broker; he sells nothing more until gauntlet N is cleared and
  gauntlet N+1's stock becomes his.

**Exclusions.**

- **Mega Stones** only once the player has the Mega Ring.
- Everything else he can offer is already sold by the normal shop one
  gauntlet later, so no separate ban list is needed.
- No deals mid-run, same as the rest of the shop.

---

## Knock-on rules

**Selling Pokémon (Keeper 4).** The existing rule — you can only sell if you
own at least 7 Pokémon, so a full six always remains — stays, with two
changes:

- **Loaners don't count** toward the 7.
- **Loaners can't be sold.** "That one's not yours to sell…"

**Party size after collection.** A collected loaner can leave the party at
five. The existing "exactly six Pokémon" entry check already makes the player
pick a replacement before the next run; the sell rule above guarantees six
real Pokémon exist to pick from.

---

## Implementation outline

- **Save data:** one `u16 brokerDealsUsed` bitmask (one bit per gauntlet) in
  `struct FacilityProgress` (`include/global.h`, SaveBlock3). Nothing else —
  loaners are identified by their data, not by a saved slot.
- **Tagging a loaner:** created with Original Trainer **"BROKER"** and a
  fixed, unique trainer ID. The summary screen shows "OT: BROKER", which
  doubles as flavor. (Traded-Pokémon obedience is a non-issue: the player has
  all eight badges.)
- **Stock:** filter the existing shop tables by `unlockBuilding == N`, then
  pick three of each with a random generator seeded from `N` and the player's
  trainer ID.
- **Resolving loans:** `FacilityCompleteBuilding()` re-tags any loaner as the
  player's own; `FacilityAbandonRun()` finds and removes it (party and PC),
  returning its held item to the bag. The scripts show a message either way.
- **Menus:** reuse the shop's dynamic menu and its buy-item / buy-Pokémon
  code paths.
- **Sell-back:** `FacilityShopSellMonPrompt()` refuses loaners, and
  `CountAllOwnedMons()` stops counting them.

---

## Dialogue draft

**First meeting:**
> Psst. Over here.
>
> The EXCHANGE CORNER won't stock the good stuff until you've cleared the
> next gauntlet. Me? I know a guy on the delivery crew.
>
> One deal per gauntlet. An item, full price plus my cut… or a POKéMON, half
> price, on loan. Clear the gauntlet and it's yours. Lose, and it comes back
> to me.
>
> …And you didn't hear any of this from me.

**Deal already made this gauntlet:**
> I said one deal. Come back when the next gauntlet's open. I'll have new
> stock by then.

**Loan kept (after clearing):**
> The BROKER sent word: "Keep {STR_VAR_1}. You earned it. …Pleasure doing
> business."

**Loan collected (after losing):**
> A man in a dark coat was waiting outside. "{STR_VAR_1} goes back to the
> BROKER. Nothing personal."

**Nothing left to sell:**
> You've cleared every gauntlet? …Then there's nothing left I can get you.
> Retirement, maybe.

**Lounge 3 regulars:** the three watchers become his nervous customers —
"I bought a CHOICE SCARF off him a whole gauntlet early. I still don't know
where he gets them." Elsewhere, the Exchange Corner's Sailor warns the player
off him with vague directions — "that shady type who hangs around the houses
out past the ARENA, on the far east side." Two more NPCs spread the rumor: the
Fisherman in the Outside West plaza ("someone way over on the east side, out
past the ARENA, who'll sell you things before the shop even has them…
Sounds fishy to me") and the Cook in the house at the east edge of Outside
West ("somebody's already running a business out of one of those houses on
the far east side… whatever he's selling, it isn't food").

**Never say "Lounge" in player-facing text.** The lounges are unlabeled
houses to the player, so NPCs point toward the Broker with directions and
landmarks, not a room number. "Lounge 3" is an internal map name only.