# LifeStructure

LifeStructure is a personal self-improvement app, currently built as a C++ terminal application. The long-term goal is to bring together tools like journaling, goal tracking, task management, and planning into a single app that helps organize daily life — starting terminal-first, with a GUI planned down the road.

## Current Status

The project is in early development. The core architecture is in place:

- **`Feature`** — an abstract base class that any feature of the app (Journal, Goals, etc.) inherits from. It defines a shared `menu()` interface, so the terminal UI can display and hand off control to any feature without needing to know its specific type.
- **`Entry`** — a base class representing a single logged item (an id, timestamp, and content), meant to be extended by feature-specific entry types.
- **`JournalEntry`** — extends `Entry` with a mood tag (Happy / Neutral / Sad).
- **`JournalContainer`** — the first feature built on top of `Feature`. Lets a user write journal entries and page through past entries.
- **`TermUI`** — the terminal-based interface. Holds a collection of features (`vector<unique_ptr<Feature>>`) and drives the top-level menu loop, dispatching to whichever feature the user selects.
- **`inputUtils`** — a reusable helper (`getValidatedInt`) for validating terminal input, so bad input (letters instead of numbers, out-of-range choices) doesn't crash the app or hang it. Meant to be reused across future projects, not just this one.

**Known limitation:** entries currently only live in memory — nothing is saved to disk yet, so all journal entries are lost when the program closes. Persistence is the top priority next step (see TODO below).

## Project Structure

```
LifeStructure/
├── CMakeLists.txt
└── src/
    ├── Core/           # Entry and Feature base classes
    ├── JournalEntry/   # JournalEntry
    ├── Containers/      # JournalContainer
    ├── TerminalUI/      # TermUI
    ├── Utils/           # inputUtils
    └── main.cpp
```

## Building

The project uses CMake:

```bash
mkdir build && cd build
cmake ..
make
./LifeStructure
```

## TODO (Near-Term)

Concrete next steps for the current codebase, roughly in priority order:

- [ ] **Data persistence** — save and load journal entries to/from disk, so entries survive between runs (currently everything is lost on exit)
- [ ] Journal entry ID search — let users look up a specific entry by its ID instead of only paging through sequentially
- [ ] Better entry typing system — support structured or multi-part entries instead of a single free-text blob per entry

## Future Features (Longer-Term)

Bigger additions planned once the core app is solid:

- [ ] Non-military (12-hour) time display, with time zone support
- [ ] Goals feature — goal tracking with goal entries, similar in spirit to the Journal feature
- [ ] Tasks feature — simple to-do style task tracking
- [ ] Weekly planner — a higher-level view tying journal, goals, and tasks together across a week
- [ ] GUI — move beyond the terminal interface once features are proven out (likely with Dear ImGui, given the existing `Feature` abstraction already separates data/logic from display)
