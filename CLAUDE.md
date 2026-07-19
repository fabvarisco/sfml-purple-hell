# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

PurpleHell is a turn-based wave-survival RPG written in C++17 with SFML 2.5.1. All source code lives flat in `PurpleHell/` (no subdirectories for code). It was a college project built to exercise data structures (linked lists, stacks, queues).

## Build and Run

Linux (primary for development here):

```bash
nix-shell      # from repo root — provides gnumake + sfml_2 (SFML 3 in nixpkgs is API-incompatible)
cd PurpleHell
make          # builds ./PurpleHell using system SFML (g++ -std=c++17)
make clean
./PurpleHell  # must be run from PurpleHell/ — assets/saves use relative "res/..." paths
```

CI/releases: `.github/workflows/release.yml` builds all three OSes via the root `CMakeLists.txt`, which fetches and statically links SFML 2.6.2 from source (FetchContent). Pushing a `v*` tag creates a GitHub Release with the packaged builds.

There are no tests or linters. The `PurpleHellProject.sln` / `PurpleHell.vcxproj` are the original Windows Visual Studio build (links against the vendored `SFML-2.5.1/` directory); the Makefile links system-installed SFML instead. `PurpleHellBuild/` is a prebuilt Windows binary, not a build output directory.

## Architecture

**Scene stack.** `main.cpp` just runs `GameManager`, which owns the `sf::RenderWindow`, the delta-time clock, and a `std::stack<Scene*>`. Each frame it updates/renders only the top scene; a scene ends itself via `Scene::endScene()` and gets popped. Scenes push new scenes onto the shared stack themselves (they hold a pointer to it): `MainMenuScene` → `GameScene` (hub with shop/party management) → `WorldScene` / `BattleScene`. `Scene` is the abstract base (`updateInput`, `update`, `render` are pure virtual); it also provides shared mouse-position tracking and fade-in logic.

**Entity hierarchy.** `Entity` is the base for everything drawable/stat-bearing (texture, sprite, hp/power/special, `AnimationComponent`). `Hero` (player units, subclassed by `Mage`) and `Enemy` derive from it. `Especial` — also an `Entity` — represents attack/spell visual effects and their damage payloads; both `Hero` and `Enemy` own an `actionEffect` and a `spell`. `Buff`/`Debuff`/`Potion`/`Item` implement combat modifiers and inventory items.

**Team containers.** `Player` holds the 3-hero battle team, `Units` the 10-slot hero roster, `AI` the 5-slot enemy team for a battle. `Inventory`, `EquipedItems`, and `Shop` manage items.

**Persistence is plain text files under `PurpleHell/res/`.** Save/state data is read and written at runtime to `res/Player/*.txt` (Team, Units, Inventory, Info, equiped) and enemy definitions come from `res/AI/<n>.txt` (loaded by `AI(int i)` per battle level). Classes with `Arquivo*` methods (Portuguese for "file") do this parsing with `ifstream`/`getline`. Running the game mutates these files, so beware of dirtying `res/Player/` during testing.

**Note:** identifiers and comments mix English and Portuguese (e.g. `Especial`, `Arquivo`, `Recursao`). Follow the existing names when extending those classes.
