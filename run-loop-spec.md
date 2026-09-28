# Facility Run Loop — Design Spec

The state machine for entering, running and completing a building. Written
before implementation so the edge cases get decided rather than discovered.

---

## The happy path

1. Player talks to the building's attendant NPC
2. Eligibility check — does the player have exactly six eligible Pokémon?
3. Team selection: choose six from the roster
4. Confirm. **The run begins and the team is locked**
5. Battles 1–6: a random CPU team drawn from that building's pool of twelve,
   no repeats within a run
6. Between each battle: full heal, held items restored, FP awarded
7. Battle 7: the building's boss, always the same team
8. On boss defeat: building marked complete, completion FP awarded, next
   building and its shop tier unlock
9. Player exits with their team intact

---

## State to track

| State | Scope | Persists across power-off? |
|---|---|---|
| Current building | Run | Yes |
| Battle number (1–7) | Run | Yes |
| Which pool teams already faced this run | Run | Yes |
| Locked team (which six) | Run | Yes |
| FP balance | Permanent | Yes |
| Buildings completed (10 flags) | Permanent | Yes |
| Shop tiers unlocked | Derived from above | — |

Run state must survive a power-off, because it's a handheld game and people
turn them off. See "Save and quit" below.

---

## Decisions to make

### Save and quit mid-run — DECIDED: supported

**Supported, Frontier-style.** The vanilla Battle Tower lets
you save and quit between battles, and resuming drops you back into the run at
the same battle number with the same team. This is expected behavior on the
platform and its absence reads as a bug.

The alternative — a run must be completed in one sitting — punishes people for
having lives, and on a seven-battle gauntlet of 6v6 doubles that could be an
hour.

**Implication:** run state goes in the save block, not scratch RAM.

### Losing

On a loss at battle N:

- Streak ends, run over
- **FP from battles 1 through N-1 is kept** — this is the anti-soft-lock
  mechanism
- Building is not marked complete
- Team returns intact
- Player may immediately re-enter and try again

### Mid-run access restrictions

The team is locked at run start, which means anything that could change the
team must be blocked for the duration:

| Thing | Mid-run | Reason |
|---|---|---|
| L-menu QoL tools | **Blocked** | Re-tuning EVs and movesets against the team you're about to fight isn't a locked team |
| PC / box access | **Blocked** | Would allow swapping the six outright |
| Shop | **Blocked** | Buying a counter mid-run defeats the point |
| Bag during battle | **Blocked** | Already handled by the Frontier battle flag |

Each needs a check against "is a run active." Worth implementing that check as
a single shared function rather than four separate conditions.

### Eligibility at entry

**Require exactly six.** Fewer than six against full CPU teams is a losing
position the player didn't understand they were choosing, and allowing it
invites confusion rather than expressing a challenge.

If the player has fewer than six eligible Pokémon, the attendant should say so
plainly and not start the run.

### Quitting deliberately mid-run — DECIDED: allowed

**Allowed, on the same terms as a loss.** FP earned is kept, streak ends. Keep FP earned, lose
the streak. There's no exploit — abandoning is strictly worse than continuing,
since continuing could earn more. And forcing someone to deliberately lose a
battle to escape a run they've realized is unwinnable is just tedium.

### Re-entry after completion

Locked, per the design. A completed building cannot be re-entered.

**The consequence to keep in view:** once building N is complete, the only FP
source is building N+1. A player who has completed building 5 and cannot beat
building 6 can only grind partial runs of building 6 itself. That works — the
per-battle FP award means progress is always possible — but it's slow, and if
playtesting shows it's *too* slow, the fix is raising the per-battle award for
the current building rather than reopening old ones.

---

## Random team selection

Six teams drawn from twelve, no repeats within a run. The boss is always
battle seven and is not part of the pool.

**Watch for:** the draw should be re-rolled per run, not per battle from a
fixed seed, or players will learn the sequence. Shuffle the twelve at run
start and take the first six.

---

## Order of implementation

A vertical slice on one building, not all ten at once.

1. **Run state and the save block field.** Everything else depends on it
2. **The "is a run active" check**, and wire the four restrictions to it
3. **Entry flow** — NPC, eligibility, team selection, confirm, lock
4. **Battle loop** — draw a team, fight, heal, restore items, award FP,
   increment, repeat
5. **Boss at battle seven**
6. **Completion** — set the flag, award completion FP, unlock the next tier
7. **Loss and abandon paths**
8. **Save and quit / resume**

Steps 1 and 2 are the foundation. Steps 3 through 6 are the loop. Steps 7 and 8
are the edge cases that make it feel finished.

Once one building works end to end, the other nine are data: a pool of twelve
teams, a boss, a BST cap, a shop tier.

---

## Opponent preview — DECIDED

**No pre-run pool viewing.** The player does not see the twelve teams before
committing. Team selection is made blind, on the building's stated tier and
format alone.

**Between battles, a "view next opponent" option is available.** The team is
already locked, so this informs lead choice and in-battle planning rather than
teambuilding.

### Code references

Two existing screens do roughly this and either could be adapted:

- **Battle Dome** — the bracket lets the player inspect upcoming trainers'
  Pokémon. The more featured of the two.
- **Battle Factory** — shows the opponent's team ahead of the swap phase.

### How much to show

**Species only.** Competitive team preview shows what's coming, not its set.
Battle Dome's screen displays movesets, which is far more generous — if that
code is used as the base, the move display should be stripped.

Showing items is a judgment call. Real team preview doesn't. Leaving items
hidden preserves the read on Choice items and Focus Sash, which matters more in
later buildings than early ones.

### Party reordering between battles

**Allowed.** Reordering isn't swapping the team — it's choosing leads, which is
the whole point of having preview information. Without it the preview only
affects in-battle decisions and loses most of its value.

Team *composition* stays locked. Only the order changes.

---

## Still open

1. **Does the player see the building's tier and format at the entrance?** Some
   indication of the BST cap and singles/doubles seems necessary — otherwise a
   player brings a singles team to a doubles building and loses to a rules
   misunderstanding rather than a skill one.
2. **Is the boss previewable at battle seven?** Same rules would suggest yes,
   which makes the boss a puzzle you get one look at before committing.
