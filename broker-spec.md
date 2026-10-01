# The Broker — Spec

A rebrand of vanilla Emerald's Frontier Gambler in Lounge 3. The Broker sells
the player **one piece of the next gauntlet's shop stock early**, before that
gauntlet is cleared, at a markup. It hands the player a small share of the
power gap the design otherwise reserves for bosses, for a price.

**Built.** The Lounge 3 script is `BattleFrontier_Lounge3_EventScript_Gambler`
(the old label, kept so the map needn't change). The logic is the
`FacilityBroker*` specials at the end of `src/facility_shop.c`.

---

## Where

**Lounge 3**, the house on the far east edge of Outside East (door at
(65, 31), level with the Battle Arena, south of the Pyramid). The Broker is
the Hiker NPC in the left-middle of the room.

**Never say "Lounge" in player-facing text.** The lounges are unlabeled
houses to the player, so NPCs point toward the Broker with directions and
landmarks ("that shady type who hangs around the houses out past the ARENA"),
not a room number.

---

## The rules

**Whose stock.** The player is about to take on gauntlet **N** (gauntlets 1
to N−1 cleared). The Broker sells from **gauntlet N's shop wave**: the entries
with `unlockGauntlet == N`, which normally appear only after N is cleared.
When every gauntlet is cleared, he has nothing left to sell.

**Two shelves, one deal.** He offers two shelves, **an item** or **a
Pokémon**, three of each, drawn at random from that wave. The player picks
**one thing, total, per gauntlet**.

**The stock is fixed per gauntlet.** The picks are derived from the gauntlet
number and the player's trainer ID, so saving, reloading or talking to him
again never rerolls them. They change when the next gauntlet's wave becomes
his stock.

**Prices: 1.2× the shop price**, rounded to the nearest 10 FP, for items and
Pokémon alike (`BrokerPrice()`).

**Everything is the player's to keep.** There are no loans. A Pokémon he sells
is tagged Original Trainer **"BROKER"** (with the in-game-trade met location),
which shows on its summary screen as flavor. It's otherwise an ordinary roster
Pokémon: it counts toward the Exchange Corner's "keep six" sell rule and can
be sold back. For the story's Experience rule it counts as chipped, like
everything from the Frontier (`IsFrontierChippedMon()`).

**Exclusions.**

- **Mega Stones** only once the player has the Mega Ring.
- Everything else he can offer is already sold by the normal shop one
  gauntlet later, so no separate ban list is needed.
- No deals mid-run, same as the rest of the shop.

---

## The Artisan Cave quest

The Broker plays a part in the required quest (`easter-eggs-spec.md`):

- **"FLOTSAM sent you?"** Once FLOTSAM points the player to him, he reacts and
  offers an **"Illegal item"** shelf: a **MASTER BALL for 600 FP**. It doesn't
  use up the gauntlet's deal.
- **While the island's "POS is down"** (gauntlet 3 cleared, no Lati caught),
  his regular deals are off. Until FLOTSAM has sent the player, he's just
  **busy**. Once the MASTER BALL is bought, he's busy again.
- Buying the MASTER BALL (or already having one) moves the quest on: FLOTSAM
  waits at the waterfall.

---

## Implementation

- **Save data:** one `u16 brokerDealsUsed` bitmask (one bit per gauntlet) in
  `struct FacilityProgress` (`include/global.h`, SaveBlock3).
- **Stock:** the shop tables filtered by `unlockGauntlet == N`, three of each
  picked with a small generator seeded from N and the player's trainer ID.
- **Selling a Pokémon** (`FacilityBrokerSellMon()`): built like a shop
  Pokémon, then tagged. It's placed party-first, then PC, **without**
  `GiveCapturedMonToPlayer()`, which would stamp the player's name over the
  "BROKER" OT.
- **Menus:** the shop's dynamic menu and its buy code paths.

---

## Dialogue

**First meeting:**
> Psst. Over here.
>
> The EXCHANGE CORNER won't stock the good stuff until you've cleared the next
> gauntlet. Me? I know a guy on the delivery crew.
>
> One deal per gauntlet. An item or a POKéMON, yours to keep. Full price, plus
> my cut.
>
> …And you didn't hear any of this from me.

**Deal already made this gauntlet:**
> I said one deal. Come back when the next gauntlet's open. I'll have new
> stock by then.

**Nothing left to sell:**
> You've cleared every gauntlet? …Then there's nothing left I can get you.
> Retirement, maybe.

**After Steven's trade (gauntlet 4), once:** Steven borrowed a Metagross from
him, and now it's in the player's party with "BROKER" still on its papers.
They go way back: when the Broker was still known as the Gambler, Steven bet
heavily on himself beating the Battle Tower's Brain. It was the wildest gamble
the Broker ever took, Steven won, and paying up was not fun. They've been
friends ever since. (`FLAG_BROKER_STEVEN_MENTION`)

**Lounge 3 regulars** are his nervous customers: one bought a CHOICE SCARF a
whole gauntlet early; one has a POKéMON that "still says BROKER on its
papers"; one grumbles his prices are steep.
