# Eight Gauntlets

A battle-only ROM hack of Pokémon Emerald on pokeemerald-expansion: eight
gauntlets, a shop that unlocks as you progress, and a story ending in an
endgame across Hoenn.

**Read before working:**

1. `project-guide.md`: the owner, the environment, the locked decisions,
   **the traps** (Frontier battle flag, trainer ID limit, the Experience rule,
   script gotchas) and the conventions.
2. `handoff.md`: the current state, what's tested, loose ends, the next
   step, and the headless test harness.
3. `storyline.md`: the whole story, before writing any story beat.

**Always:**

- The owner is new to git and the command line: explain commands. They're
  expert at competitive Pokémon and game design.
- Commit before starting anything. Never pull from `RHH` mid-task.
- Keep diffs small. Megas only. Don't strip the vanilla story yet.
- The player never speaks in dialogue.
- Build with `make -j$(nproc)`; `make check` has 15 known failures.
