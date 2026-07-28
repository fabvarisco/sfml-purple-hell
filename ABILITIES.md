# Abilities — Jobs and Specials (PurpleHell)

Reference for the character classes (jobs) and every special ability (specials/magics)
in the game. The values reflect the **current code**
(`Especial.cpp`, `Hero.cpp`, `BattleScene.cpp`).

## How it works

- There are **6 jobs**: `mage`, `rogue`, `knight`, `demonhunter`, `warlock`, `archer`.
- Each hero has a **`special` field (slot 1–3)** — rolled from 1 to 3 when generated in the
  shop — that defines **which** of the job's 3 abilities is active. The spell is created in
  `Hero::Hero()` (`Hero.cpp:27`) via `new Especial(special, job)`.
- The special is triggered by the **MAGIC** button in battle and is usable **once per round**
  (flag `canUseSpecial`). The normal attack has no such limit.
- `power` = the hero's attack power. The damage values below are multiples of `power`.

## Normal attack (all jobs)

- **Damage:** `power` (×1) to a single enemy.
- **Visual effect:** `slash` (`Hero::Action`, `Hero.cpp:90-97`).

## Abilities by job

### Mage
| Slot | Ability | In-game description | Damage | Effect | AOE |
|---|---|---|---|---|---|
| 1 | Thunder | Deals damage to all enemies. | `power×2` to **all** | — | **Yes** |
| 2 | Fireball | Deals damage to one enemy and burn it | `power×2` | Poison 3 turns | No |
| 3 | Waterfall | Deals extra damage to one enemy. | `power×3` | — | No |

### Rogue
| Slot | Ability | In-game description | Damage | Effect | AOE |
|---|---|---|---|---|---|
| 1 | Steal | Deals damage to one enemy and steal gold | `power×2` | **+15 gold** to the player | No |
| 2 | Poison Dagger | Deals damage to one enemy with a poison knife | `power×2` | Poison 3 turns | No |
| 3 | Kick | Stun an enemy | 0 | **Stun** (skips 1 turn) | No |

### Knight
| Slot | Ability | In-game description | Damage | Effect | AOE |
|---|---|---|---|---|---|
| 1 | Double slash | Deals double damage to one enemy. | `power×2` | — | No |
| 2 | Rage | Deals x4 more damage to one enemy. | `power×4` | — | No |
| 3 | Kick | Stun an enemy. | 0 | **Stun** (skips 1 turn) | No |

### Demonhunter
| Slot | Ability | In-game description | Damage | Effect | AOE |
|---|---|---|---|---|---|
| 1 | Scars slash | Deals x3 damage to one enemy. | `power×3` | — | No |
| 2 | Drain Blood | Deals damage to one enemy with a poison knife. | `power×2` | Heals the hero for **50% of the damage** | No |
| 3 | Punch | Deals damage to one enemy. | `power×2` | — | No |

### Warlock
| Slot | Ability | In-game description | Damage | Effect | AOE |
|---|---|---|---|---|---|
| 1 | Drain Life | Deals damage to one enemy and heal half of the damage. | `power×2` | Heals the hero for **50% of the damage** | No |
| 2 | Death Touch | Instant kill an enemy but you lost half of the life. | **Kills** (hp=0) | Hero loses **50% of own HP** | No |
| 3 | Curse | Deals curse damage to one enemy. | `power×3` | — | No |

### Archer
| Slot | Ability | In-game description | Damage | Effect | AOE |
|---|---|---|---|---|---|
| 1 | Double slash | Deals double damage to one enemy. | `power×2` | — | No |
| 2 | Poison Dagger | Deals damage to one enemy with a poison knife | `power×2` | Poison 3 turns | No |
| 3 | Kick | Stun an enemy | 0 | **Stun** (skips 1 turn) | No |

## Status effects

Applied on the enemy's turn, in `BattleScene::enemyTurn()`:

- **Poison:** `5` damage per turn, for `3` turns (`BattleScene.cpp:373-377`).
  Applied by *Fireball* and *Poison Dagger*.
- **Stun:** the enemy loses its next attack (skips 1 turn) — `BattleScene.cpp:385-386`.
  Applied by *Kick*.

## Note on enemies

Enemies (`monster01`, `monster02`, `monster03`) **have no job/special system**: they are
generic, with only `name`, `hp` and `power` (`AI::ArquivoEnemies`). Their attack deals
`power` damage, with a chance to miss.

---

### Code references
- Special definitions (name, description, animation, AOE flag): `Especial::specialInit()` — `Especial.cpp:4-128`
- Applying damage/heal/status effects: `Hero::Special()` — `Hero.cpp:57-88`
- AOE, gold steal and per-turn status: `BattleScene.cpp` (`556`, `587`, `373-386`)
- Job list: `Shop.h:100`
</content>
