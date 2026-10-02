# PKMN Kanto Re:Flux

> **Author:** [Miguel Zafra (@mzafram2001)](https://github.com/mzafram2001)

An enhanced and modernized decompilation of **Pokémon FireRed** based on [pret/pokefirered](https://github.com/pret/pokefirered). This project integrates essential modern Quality-of-Life (QoL) improvements, battle mechanics up to Gen 6 standards, full RTC day/night cycles, no-trade evolutions, dynamic badge-based level caps, modern shiny rates, and improved trainer AI while preserving the classic Kanto adventure.

---

## 🌟 Key Features & Changes

### 🏃 Quality of Life & Exploration
* **Running Shoes from the Start:** Unlocked right from the beginning of your journey—no need to wait for Mom or Professor Oak's aide.
* **Indoor Running:** Full sprint capability inside houses, Pokémon Centers, Marts, and all indoor facilities.
* **Auto-Run Toggle:** Press the **L button** on the overworld to toggle between walking and running automatically without having to hold **B**.
* **Catch Experience:** Capturing wild Pokémon awards experience points to your party, following Gen 6+ mechanics.
* **Reusable TMs:** Technical Machines (TMs) are infinite and will not be consumed upon teaching.
* **Forgettable HMs:** Hidden Machines (HMs) can be freely forgotten and overwritten when learning new moves without visiting the Move Deleter.
* **Help Menu Disabled:** Removed the intrusive L/R help system menu to prevent accidental gameplay interruptions; default LR mode is activated.
* **Auto-Repel Prompt (B2W2 Style):** When a Repel wears off in the field, a prompt asks if you want to use another one without opening your bag.
* **Overworld Poison Survival (Gen 4+):** Pokémon survive at 1 HP from poison outside of battle; the poison fades away instead of causing the Pokémon to faint.

---

### ⚔️ Battle Mechanics & Typing
* **Physical / Special / Status Split:**
  * Moves are categorized individually as **Physical**, **Special**, or **Status** regardless of their elemental type (Gen 4+ battle mechanics).
  * Category text labels are displayed directly in the move info panel within the Pokémon summary screen with clear color-coding (Physical in orange-red, Special in blue, and Status in dark grey).
* **Fairy-Type Integration (Gen 6+):**
  * Full Gen 6 type matchup table implemented (weaknesses, resistances, and immunities).
  * Existing Pokémon retroactively updated to Fairy or dual Fairy-type (e.g., Clefairy line, Jigglypuff line, Mr. Mime, Togepi line, Marill line, Snubbull line, Ralts/Kirlia/Gardevoir, etc.).
  * Fairy-type moves included and integrated via level-up learnsets and TMs (**TM09 Disarming Voice**, **TM48 Draining Kiss**, and **TM49 Dazzling Gleam**).
  * Custom pastel-pink Fairy badge icon seamlessly integrated into battle menus and summary screens.
* **Modern Shiny Rate (1/4096):**
  * Upgraded base shiny encounter probability from the classic 1/8192 to the modern Gen 6+ standard of **1/4096** (`SHINY_ODDS = 16/65536`) for wild encounters, gifts, and breeding.
* **Battle Healthbox Type Icons (CFRU-Style):**
  * Displays dynamic type badges directly above each active Pokémon's health box (showing Primary & Secondary types for dual-type species, or a single centered badge for pure types).
  * Smoothly synchronized with healthbox entry/exit slide animations and visibility during move attacks.
  * Real-time dynamic updates if a Pokémon changes typing mid-battle (Conversion, Color Change, Transform, etc.).

---

### 📊 Pokémon Summary Screen & UI
* **Nature Stat Colors:** Stat displays highlight the effect of the Pokémon's Nature (+10% boosted stat in **Red**, -10% hindered stat in **Blue**).
* **IVs & EVs Visualizer:**
  * In the Pokémon summary screen (Stats page), press the toggle button to cycle between:
    1. **Base Calculated Stats**
    2. **Individual Values (IVs: 0–31)**
    3. **Effort Values (EVs: 0–255)**
  * Clean UI formatting with EXP bar preserved and color palettes properly tuned.

---

### ⏰ Real-Time Clock (RTC) & Day/Night System
* **Hardware RTC Integration:** S-3511A real-time clock protocol support compatible with both flashcarts and modern GBA emulators (mGBA, VBA, etc.).
* **Dynamic Overworld Tinting:** Progressive ambient tinting across all outdoor routes and towns reflecting the time of day:
  * **Morning:** Gentle warm sunrise tint.
  * **Day:** Standard natural daylight.
  * **Sunset / Evening:** Rich amber sunset glow.
  * **Night:** Deep twilight night tint.
* **Time-Based Evolutions:** Eevee evolves into **Espeon** during the day/morning and **Umbreon** during the night via high Friendship.

---

### 🔄 Evolutions & Pokédex Freedom
* **National Dex Restriction Removed:** Pokémon with evolutions introduced in Generation 2 (Crobat, Steelix, Scizor, Blissey, Kingdra, etc.) can now evolve freely in Kanto prior to obtaining the National Pokédex.
* **Trade Evolutions Removed (Playable 100% Solo):**
  * **By Level Up:**
    * Kadabra ➔ Alakazam *(Level 38)*
    * Machoke ➔ Machamp *(Level 36)*
    * Graveler ➔ Golem *(Level 36)*
    * Haunter ➔ Gengar *(Level 38)*
  * **By Level Up holding item:**
    * Poliwhirl ➔ Politoed *(Level up holding King's Rock)*
    * Slowpoke ➔ Slowking *(Level up holding King's Rock)*
    * Onix ➔ Steelix *(Level up holding Metal Coat)*
    * Scyther ➔ Scizor *(Level up holding Metal Coat)*
    * Seadra ➔ Kingdra *(Level up holding Dragon Scale)*
    * Porygon ➔ Porygon2 *(Level up holding Up-Grade)*
    * Clamperl ➔ Huntail *(Level up holding Deep Sea Tooth)*
    * Clamperl ➔ Gorebyss *(Level up holding Deep Sea Scale)*
    * Feebas ➔ Milotic *(Level up holding Heart Scale)*
* **All Evolutionary Items Available:** Celadon Department Store (4F) now stocks all evolutionary stones, trade hold items, Heart Scales, and baby incenses (Moon Stone, Sun Stone, King's Rock, Metal Coat, Dragon Scale, Up-Grade, Deep Sea Tooth, Deep Sea Scale, Heart Scale, Sea & Lax Incense) for full solo Pokédex completion.
* **Complete TM Accessibility (50/50) & Fairy TMs:**
  * Added **TM10 (Hidden Power)**, **TM48 (Draining Kiss)**, and **TM49 (Dazzling Gleam)** to the Celadon Department Store (2F) TM counter.
  * **TM09 (Disarming Voice)** is obtained early in Mt. Moon (1F) and as a gift from the Vermilion City Pokémon Fan Club.
  * Resolves the classic vanilla oversight where TM10 was exclusively locked behind low-probability Pickup ability grinding.
* **Full Competitive & Type-Boosting Item Availability:** Celadon Department Store (5F) now stocks all competitive battle items (Choice Band, Leftovers, Scope Lens, Focus Band, BrightPowder, Shell Bell, White Herb, Mental Herb, Lucky Egg, Soothe Bell, Light Ball, Thick Club, Stick) and all elemental type boosters (Magnet, Charcoal, Mystic Water, Miracle Seed, etc.).
* **Specialty Poké Balls Available:** Celadon Department Store (2F) now stocks all specialty Poké Balls (Ultra Ball, Net Ball, Nest Ball, Repeat Ball, Timer Ball, Luxury Ball).

---

### 🧠 Trainer AI & Difficulty Enhancements
* **Dynamic Badge-Based Level Caps:**
  * To prevent unintentional overleveling and maintain competitive boss encounters, a dynamic level cap system is enforced based on badge progress.
  * Pokémon at or above the current cap receive **0 EXP** (cleanly bypassing repetitive level-up messages) while still earning **EVs**.
  * Leveling up in battle will clamp exactly at the cap level, and Rare Candies / Daycare will not exceed the cap.
  
| Badges / Milestone | Target Boss | Level Cap |
| :--- | :--- | :---: |
| **0 Badges** *(Game Start)* | Gym 1: Brock *(Onix)* | **14** |
| **1 Badge** *(Boulder Badge)* | Gym 2: Misty *(Starmie)* | **21** |
| **2 Badges** *(Cascade Badge)* | Gym 3: Lt. Surge *(Raichu)* | **24** |
| **3 Badges** *(Thunder Badge)* | Gym 4: Erika *(Vileplume)* | **29** |
| **4–5 Badges** *(Rainbow / Soul / Marsh)* | Gym 5 & 6: Koga & Sabrina *(Weezing / Alakazam)* | **43** |
| **6 Badges** *(Both Koga & Sabrina defeated)* | Gym 7: Blaine *(Arcanine)* | **47** |
| **7 Badges** *(Volcano Badge)* | Gym 8: Giovanni *(Rhydon)* | **50** |
| **8 Badges** *(Earth Badge)* | Elite Four 1: Lorelei | **54** |
| **Lorelei Defeated** | Elite Four 2: Bruno | **56** |
| **Bruno Defeated** | Elite Four 3: Agatha | **58** |
| **Agatha Defeated** | Elite Four 4: Lance | **60** |
| **Lance Defeated** | Champion Rival | **63** |
| **Champion Defeated** *(Hall of Fame)* | Post-Game Freedom | **100** |

* **Competitive Boss Trainers:** Gym Leaders, Elite Four, Champion, and Rival feature progressively scaled competitive IV spreads (up to 31) and optimized EV yields, accompanied by competitive held items.
* **Upgraded Battle AI:** Important trainers utilize full-suite AI decision-making (damage calculation awareness, kill-range recognition, avoiding useless moves).
* **Smart Switching Logic:** Skilled trainers will actively switch out when facing critical type disadvantages or perilous matchups.

---

## 🎮 Controls Quick Guide

| Button / Combination | Context | Effect |
| :--- | :--- | :--- |
| **L** | Overworld | Toggle Auto-Run on / off |
| **B** *(Hold)* | Overworld | Manual sprint (if Auto-Run is off) |
| **A / SELECT** | Summary Screen (Stats Page) | Cycle between Stats, IVs, and EVs |

---

## 🛠️ Building the ROM

### Prerequisites
Follow the instructions in [INSTALL.md](INSTALL.md) to set up devkitARM and project dependencies.

### Build Commands
```bash
# Build Pokémon FireRed (English)
make -j$(nproc)
```

The resulting ROM will be output as:
* `pokefirered.gba`

---

## 👤 Author

* **Miguel Zafra** — [@mzafram2001](https://github.com/mzafram2001)

---

## 🙏 Credits & Acknowledgements

* **[pret/pokefirered](https://github.com/pret/pokefirered):** The incredible reverse engineering base project.
* **Pokémon Community:** Contributors, guides, and research on GBA decompilation.
* **Game Freak / Nintendo:** Creators of Pokémon FireRed and the Pokémon franchise.