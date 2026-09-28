# Shop Unlock — After Building 2

What the keepers gain when Tidewarden Nerys falls. This is the biggest single
jump in the shop's life: the cap moves from 500 to 550, which is where most of
competitive Pokémon actually lives.

**Gate:** building 2 marked complete.

**Tier prices:** Standard 200 · Strong 300 · Premium 400

---

## Keeper 1 — Consumables

Nothing new. The berry shelf is complete after building 1's unlock.

---

## Keeper 2 — Held items

| Item | FP | Effect |
|---|---|---|
| Damp Rock | 200 | Rain lasts 8 turns instead of 5 |
| Heat Rock | 200 | Sun lasts 8 turns instead of 5 |
| Smooth Rock | 200 | Sandstorm lasts 8 turns instead of 5 |
| Icy Rock | 200 | Snow lasts 8 turns instead of 5 |
| Electric Seed | 150 | +1 Defense on Electric Terrain, once |
| Grassy Seed | 150 | +1 Defense on Grassy Terrain, once |
| Misty Seed | 150 | +1 Sp. Defense on Misty Terrain, once |
| Psychic Seed | 150 | +1 Sp. Defense on Psychic Terrain, once |
| Eviolite | 350 | +50% Defense and Sp. Defense to a Pokémon that can still evolve |
| Flame Orb | 200 | Burns the holder at end of turn. Guts, Facade and Flare Boost enabler |
| Toxic Orb | 200 | Badly poisons the holder at end of turn. Poison Heal and Guts enabler |
| Expert Belt | 250 | 1.2× damage on super-effective hits |
| Muscle Band | 150 | 1.1× damage on physical moves |
| Wise Glasses | 150 | 1.1× damage on special moves |

**The weather rocks are the signature purchase of this tier.** They're the first
item that doesn't improve a Pokémon at all — it improves the *team*. A player
who understands why eight turns of sand beats five has understood building 3.

**Eviolite is gated to here deliberately.** NFE Pokémon have artificially low
BST because the number measures an unevolved form, so Eviolite systematically
breaks the earlier caps. Chansey at 450 BST with a 1.5× defensive multiplier on
base 250 HP is a wall nothing below tier 3 can break.

---

## Keeper 3 — Mega Stones

Still empty. Unlocks after building 5.

---

## Keeper 4 — Pokémon (cap raised to 550)

The largest roster expansion in the game. Roughly 100 new species.

### Premium — 400 FP

The tier's genuinely format-defining picks.

Volcarona, Ferrothorn, Gholdengo, Kingambit, Hatterene, Grimmsnarl, Gliscor,
Excadrill, Skarmory, Chansey, Porygon2, Rillaboom, Milotic, Gardevoir,
Magnezone, Hippowdon, Ninetales-Alola, Weavile, Aegislash, Annihilape,
Togekiss, Kingdra, Ursaluna, Sneasler *(Unburden)*, Serperior *(Contrary)*

### Strong — 300 FP

Ninetales, Gigalith, Abomasnow, Venusaur, Tangrowth, Krookodile, Rhyperior,
Flygon, Mandibuzz, Mamoswine, Froslass, Scizor, Swampert, Gyarados, Slowbro,
Rotom-Wash, Rotom-Heat, Rotom-Mow, Alakazam, Machamp, Nidoking, Nidoqueen,
Gallade, Crobat, Haxorus, Noivern, Bisharp, Honchkrow, Porygon-Z, Electivire,
Yanmega, Dusknoir, Toxicroak, Seismitoad, Kabutops, Lycanroc,
Sandaconda, Cetitan, Arctozolt, Toxtricity, Pincurchin, Weezing-Galar,
Blissey, Snorlax, Starmie, Aerodactyl, Cloyster, Ampharos, Sylveon, Espeon,
Umbreon, Vaporeon, Jolteon, Flareon, Leafeon, Glaceon, Braviary, Tinkaton,
Lucario, Ceruledge, Hydrapple *(Regenerator)*, Golisopod, Feraligatr

### Standard — 200 FP

Vanilluxe, Floatzel, Omastar, Poliwrath, Gorebyss, Huntail, Exeggutor,
Lilligant, Victreebel, Shiftry, Sawsbuck, Cherrim, Charizard, Magmortar,
Blaziken, Beartic, Lapras, Walrein, Sceptile, Dusclops, Eelektross,
Tentacruel, Sirfetch'd, Solrock

### Eviolite targets — 300 FP

Sold alongside the item, since they only make sense together.

Chansey, Porygon2, Rhydon, Gligar, Magneton, Type: Null, Doublade,
Sneasel, Dusclops, Duraludon

Scyther and Stoutland moved to the building 2 wave (both exactly 500 BST -
see shop-unlock-b2.md). Scyther is still an Eviolite target; it just becomes
buyable a building earlier than the item.

---

## Shop restrictions

**Blaziken is sold with Blaze, not Speed Boost.** Speed Boost Blaziken at a 550
cap is the best Pokémon in the tier by a wide margin — free +1 Speed every turn
behind Swords Dance ends games before counterplay exists. The shop controls
which ability a purchased Pokémon has, so this needs no ban.

Apply the same handling to any hidden ability that outclasses its tier.

---

## Implementation note

**The Pokémon keeper is now unusable as a flat list.** Tier 1 was ~105 species,
tier 2 added ~75, and this adds ~100 more. That's roughly 280 entries.

This unlock is the point where the menu needs a real structure — a first-level
split at minimum, probably a second. The banding above (Premium / Strong /
Standard) is one candidate axis; type is the other. Whichever is chosen should
be settled before this tier ships, not after.
