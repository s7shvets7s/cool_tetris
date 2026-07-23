<div align="center">

# 🧱 Cool Tetris

### A playable C++ and Qt 6 desktop Tetris client with a new Java server under development

[![C++](https://img.shields.io/badge/C++-Desktop%20Client-00599C?style=flat-square\&logo=c%2B%2B\&logoColor=white)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6.5%2B-41CD52?style=flat-square\&logo=qt\&logoColor=white)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/Build-CMake-064F8C?style=flat-square\&logo=cmake\&logoColor=white)](https://cmake.org/)
[![Widgets](https://img.shields.io/badge/UI-Qt%20Widgets-41CD52?style=flat-square)](https://doc.qt.io/qt-6/qtwidgets-index.html)
[![Network](https://img.shields.io/badge/Networking-Qt%20Network-blue?style=flat-square)](https://doc.qt.io/qt-6/qtnetwork-index.html)
[![Client](https://img.shields.io/badge/Client-Playable-success?style=flat-square)](#client-status)
[![Server](https://img.shields.io/badge/Java%20Server-In%20Development-orange?style=flat-square)](#java-server-development)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)](LICENSE)

</div>

---

## Screenshots

<!--
Create the following directory in the repository:

docs/images/

Save the main-menu screenshot as:

docs/images/main-menu.png

Save the gameplay screenshot as:

docs/images/gameplay.png
-->

<div align="center">

<image src="https://github.com/user-attachments/assets/63f8a865-c8e1-438e-b6d8-15f112b17200"  alt="Cool Tetris main menu" width="46%">

<image src="https://github.com/user-attachments/assets/6c210944-6aa1-4a34-9920-376ec6964e29" alt="Cool Tetris gameplay" width="46%">
 

</div>

---

## About the Project

**Cool Tetris** is a desktop Tetris application built in C++ with Qt 6.

The repository currently contains a playable graphical client with the complete core single-player gameplay loop:

* tetromino generation;
* movement and rotation;
* collision detection;
* line clearing;
* score calculation;
* increasing levels and game speed;
* next-piece previews;
* a hold-piece slot;
* pause and game-over overlays;
* locally saved player statistics.

The client also contains early integration points for player accounts, authentication and remote score submission.

A new server is currently being developed in **Java**. It is intended to replace the older experimental C++/Qt server included in this repository and become the primary backend for the project's online functionality.

> [!IMPORTANT]
> The local C++/Qt client is playable. The new Java server and the complete online account system are still under development.

---

## Client Status

| Component                   | Status                  |
| --------------------------- | ----------------------- |
| Core Tetris gameplay        | ✅ Implemented           |
| Graphical Qt interface      | ✅ Implemented           |
| Score and level progression | ✅ Implemented           |
| Next-piece preview          | ✅ Implemented           |
| Hold-piece mechanic         | ✅ Implemented           |
| Pause and game-over screens | ✅ Implemented           |
| Local statistics            | ✅ Implemented           |
| Local settings persistence  | ✅ Implemented           |
| Windows deployment script   | ✅ Implemented           |
| Account interface           | 🧪 Experimental         |
| Remote score submission     | 🧪 Integration scaffold |
| Control-remapping interface | 🚧 Not completed        |
| New Java server             | 🚧 In development       |
| Stable online services      | 🚧 Not available yet    |

---

## 🎮 Implemented Gameplay

### Standard Playing Field

The client uses a classic:

```text
10 × 20
```

Tetris playing field.

The board stores both frozen tetrominoes and the currently falling piece. The game checks boundaries and occupied cells before allowing movement or rotation.

### Seven Tetromino Types

All seven standard tetrominoes are implemented:

* `I`
* `J`
* `L`
* `O`
* `S`
* `T`
* `Z`

Each piece has:

* an individual shape;
* its own color;
* rotation logic;
* coordinate conversion for rendering and collision detection.

The square `O` piece does not rotate.

### Piece Movement

The player can:

* move the active piece left;
* move it right;
* move it down manually;
* rotate it;
* perform a hard drop;
* move a piece into the hold slot;
* restart the current game;
* pause the game.

Movement is processed through a repeating input timer, allowing held movement keys to be handled continuously.

### Collision Detection

Before applying movement, the game checks whether the tetromino would:

* leave the left side of the board;
* leave the right side of the board;
* move below the playing field;
* overlap an already frozen block.

When a piece can no longer move down, it is frozen into the board and the next tetromino is spawned.

### Line Clearing

After every placed tetromino, the game searches for completed rows.

Completed rows are removed, and all rows above them are shifted downward.

The client supports clearing:

* one line;
* two lines;
* three lines;
* four lines at once.

A four-line clear is tracked separately as a **Tetris**.

### Score System

The current score calculation uses the number of simultaneously cleared lines and the current level.

Base rewards are:

| Lines | Base score |
| ----: | ---------: |
|     1 |        100 |
|     2 |        300 |
|     3 |        500 |
|     4 |       1200 |

The base reward is multiplied by:

```text
current level + 1
```

The game also contains separate scoring logic for manually dropping pieces.

### Level Progression

The player begins at level `0`.

The level increases after every ten cleared lines:

```text
10 lines → next level
```

Each new level reduces the automatic falling interval, causing pieces to move faster.

The interval is calculated dynamically and has a lower limit to prevent the timer from becoming unusably fast.

### Next-Piece Queue

The game maintains a queue of four upcoming pieces.

The interface displays the first three pieces, allowing the player to plan future placements.

Whenever a new piece is spawned:

1. the first piece is removed from the queue;
2. it becomes the active tetromino;
3. a new random tetromino is appended to the queue;
4. the preview widget is updated.

### Hold Piece

The client contains a hold, or pocket, mechanic.

The player can:

* store the current piece;
* retrieve a previously stored piece;
* exchange the active piece with the stored one.

The hold action can only be performed once for each newly spawned tetromino. It becomes available again after the current piece is frozen and another piece is created.

---

## 🖥️ User Interface

The client interface is built entirely with **Qt Widgets**.

### Main Menu

The main menu contains:

* the `QT TETRIS` title;
* the current player nickname;
* the best local score;
* the total number of cleared lines;
* a Play button;
* an Exit button;
* navigation buttons for the user page, settings and statistics.

The menu uses a custom background image and SVG icons stored in the Qt resource system.

### Gameplay Screen

The gameplay screen is divided into three main areas:

```text
┌──────────────┬──────────────────────┬──────────────┐
│ Hold piece   │ Score and game field │ Next pieces  │
└──────────────┴──────────────────────┴──────────────┘
```

The central area contains:

* the current score;
* the 10 × 20 game board;
* the active tetromino;
* already placed blocks.

The side panels display:

* the held tetromino;
* the next three tetrominoes.

### Rendering

The playing field and tetrominoes are rendered with `QPainter`.

The renderer draws:

* the board grid;
* frozen blocks;
* block outlines;
* the active piece;
* individual colors for every tetromino type.

### Pause Overlay

Opening the pause menu stops both:

* automatic piece movement;
* the client's input-processing timer.

The pause overlay provides:

* Continue;
* Play Again;
* Exit to Main Menu.

### Game-Over Overlay

The game ends when a newly spawned tetromino immediately collides with occupied cells.

The game-over overlay displays:

* the final score;
* a Play Again button;
* an Exit to Main Menu button.

At the end of a game, the client updates and saves the player's local statistics.

---

## ⌨️ Controls

| Key      | Action                        |
| -------- | ----------------------------- |
| `←`      | Move left                     |
| `→`      | Move right                    |
| `↓`      | Soft drop                     |
| `↑`      | Rotate                        |
| `Space`  | Hard drop                     |
| `Shift`  | Hold or swap the active piece |
| `R`      | Restart the game              |
| `Escape` | Open the pause menu           |

> [!NOTE]
> The project already contains data structures for configurable controls, but the visible control-remapping interface and its connection to gameplay input are not finished yet.

---

## 📊 Local Statistics

Player statistics are stored locally through `QSettings`.

The client currently tracks:

* player nickname;
* best score;
* total number of games played;
* cumulative cleared lines;
* total number of four-line Tetris clears;
* total number of placed tetrominoes;
* total game time;
* an average-score value displayed by the statistics screen.

The statistics screen uses a scrollable Qt interface and updates after completed games.

Local data is saved under the application identifiers:

```text
Organization: s7shvets7s
Application: cool_tetris
```

This allows the statistics to remain available between application launches.

---

## 🌐 Network Integration

The client contains two experimental networking components.

### Score Submission

At the end of a game, the client can create a TCP connection and send a compact JSON message containing:

```json
{
  "type": "score",
  "nickname": "Player",
  "score": 1000,
  "lines": 12
}
```

The current default development address is:

```text
127.0.0.1:5000
```

This integration requires a compatible server and should currently be treated as development scaffolding rather than a stable online leaderboard.

### Account Authentication

The client also contains:

* registration and login forms;
* a user section in the main menu;
* JSON-based login requests;
* token-response handling;
* login-success and login-error signals.

The current login prototype targets a local HTTPS development endpoint.

Registration is not fully implemented, and the account flow depends on server-side work that is still in progress.

---

## ☕ Java Server Development

> [!IMPORTANT]
> The active server direction for Cool Tetris is now Java.

A new Java backend is currently being developed to replace the old experimental C++ server.

The Qt client already contains integration points for:

* account login;
* authentication tokens;
* player identity;
* score submission;
* remote player statistics.

These client-side integration points will be updated as the Java server API becomes stable.

The Java server is not yet part of the stable project build, so the current release should primarily be evaluated as a **playable C++/Qt desktop client**.

### Legacy Server

The `TetrisServer/` directory currently contains an older C++ and Qt server prototype.

That prototype experiments with:

* Qt Network;
* Qt HTTP Server;
* PostgreSQL;
* Redis;
* Docker;
* authentication endpoints;
* score processing.

It remains in the repository for historical and educational reference, but it is no longer the primary backend direction.

---

## 🏗️ Client Architecture

```text
TetrisClient/
├── assets/
│   ├── backgrounds/              # Menu backgrounds
│   └── icons/                    # SVG and application icons
│
├── src/
│   ├── core/
│   │   ├── game_logic.h
│   │   ├── game_logic.cpp        # Board, movement, scoring and levels
│   │   ├── tetromino.h
│   │   └── tetromino.cpp         # Tetromino shapes, rotation and colors
│   │
│   ├── network/
│   │   ├── network_manager.h
│   │   ├── network_manager.cpp   # TCP score submission
│   │   ├── network_managerv2.h
│   │   └── network_managerv2.cpp # HTTP authentication prototype
│   │
│   ├── settings/
│   │   ├── setting_manager.h
│   │   └── setting_manager.cpp   # QSettings and local statistics
│   │
│   ├── ui/
│   │   ├── mainwindow.h
│   │   ├── mainwindow.cpp        # Main menu/game navigation
│   │   │
│   │   ├── ingame/
│   │   │   ├── fild_widget.*     # Board rendering and keyboard input
│   │   │   ├── game_widget.*     # Gameplay-screen composition
│   │   │   ├── score_widget.*    # Current score
│   │   │   ├── next_pieces_widget.*
│   │   │   ├── poket_piece_widget.*
│   │   │   ├── pause_widget.*
│   │   │   ├── game_over_widget.*
│   │   │   └── overlay_widget.*
│   │   │
│   │   └── menus/
│   │       ├── menu_widget.*
│   │       ├── setting_widget.*
│   │       ├── statistic_widget.*
│   │       └── Authorization/
│   │           ├── login_form.*
│   │           ├── registrate_form.*
│   │           └── user_widget.*
│   │
│   └── main.cpp
│
├── CMakeLists.txt
├── resources.qrc
└── build_static.bat
```

---

## 🛠️ Technology Stack

| Technology     | Purpose                                     |
| -------------- | ------------------------------------------- |
| **C++**        | Client gameplay and application logic       |
| **Qt 6**       | Desktop application framework               |
| **Qt Widgets** | Main menu, game screen and overlays         |
| **Qt GUI**     | Painting, colors, icons and keyboard input  |
| **Qt Network** | TCP and HTTP client integration             |
| **Qt SVG**     | SVG menu icons                              |
| **QSettings**  | Persistent local statistics and preferences |
| **CMake**      | Build configuration                         |
| **Ninja**      | Optional Windows build tool                 |
| **Java**       | New server currently under development      |

---

## 🚀 Building the Client

### Requirements

* CMake 3.19 or newer
* Qt 6.5 or newer
* A C++ compiler supported by Qt
* Qt components:

  * Core
  * GUI
  * Widgets
  * Network
  * SVG

### Clone the Repository

```bash
git clone https://github.com/s7shvets7s/cool_tetris.git
cd cool_tetris
```

### Configure Only the Client

Because the root project also references the legacy C++ server, configure the client directory directly:

```bash
cmake -S TetrisClient -B build/client
```

When CMake cannot locate Qt automatically, specify the Qt installation path:

```bash
cmake -S TetrisClient -B build/client \
  -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x/compiler"
```

Example for a Windows MinGW installation:

```powershell
cmake -S TetrisClient -B build/client `
  -DCMAKE_PREFIX_PATH="C:/Qt/6.10.2/mingw_64"
```

### Build

```bash
cmake --build build/client --config Release
```

The exact executable location depends on the selected CMake generator and operating system.

Possible locations include:

```text
build/client/TetrisClient
build/client/TetrisClient.exe
build/client/Release/TetrisClient.exe
```

---

## 📦 Windows Deployment

The client directory contains:

```text
TetrisClient/build_static.bat
```

The script performs the following operations:

1. removes previous build and deployment directories;
2. configures the project with CMake and Ninja;
3. creates a Release build;
4. copies the executable;
5. runs `windeployqt`;
6. prepares a deployable folder containing the required Qt libraries.

The script contains machine-specific paths for:

* Qt;
* CMake;
* Ninja;
* Enigma Virtual Box.

Update those variables before running it on another computer.

> [!NOTE]
> Despite its filename, the script primarily creates a deployed Windows build with the required Qt DLLs. It does not perform a conventional fully static Qt link by itself.

---

## 🚧 Current Limitations

The current client has several known unfinished areas:

* the settings page does not yet expose actual gameplay settings;
* saved control mappings are not yet connected to the hard-coded gameplay controls;
* registration is represented by an early interface and client-side scaffold;
* login depends on a local development backend;
* remote score submission requires a compatible running server;
* the Java server is still under development;
* the repository does not currently contain automated client tests;
* the old C++ server and the new Java backend direction have not yet been fully separated;
* some source-file and class names contain historical spelling mistakes such as `fild` and `poket`.

These limitations do not prevent the local single-player client from being played.

---

## 🗺️ Development Direction

The next major stage of the project is the Java backend.

Current development priorities are:

* completing the Java server;
* defining a stable protocol between the Qt client and Java backend;
* connecting account registration and login;
* replacing temporary localhost endpoints;
* moving remote score storage to the new server;
* completing the settings interface;
* connecting configurable controls to the input system;
* separating or removing the legacy C++ server;
* adding automated tests for the gameplay core.

---

## 📄 License

This project is distributed under the **MIT License**.

See the [LICENSE](LICENSE) file for the complete license text.

---

<div align="center">

### Playable Qt client. Java backend in progress.

**A desktop game project combining C++, Qt and an evolving client-server architecture.**

</div>
