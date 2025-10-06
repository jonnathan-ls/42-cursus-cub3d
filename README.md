# Cub3D: Relive History with the First FPS Ever Created

![42 School Project](https://img.shields.io/badge/42-Project-blue)
![Language](https://img.shields.io/badge/language-C-blue.svg)
![Graphics](https://img.shields.io/badge/graphics-MLX42-green.svg)
![Norminette](https://img.shields.io/badge/norminette-passing-success)

A raycasting game engine inspired by the legendary **Wolfenstein 3D** (1992), the game that revolutionized the FPS genre. This project recreates the fundamental mechanics of the first-person perspective using raycasting techniques, built from scratch in C following the strict **42 School Norminette** coding standards.

---

## 📖 Table of Contents

- [Cub3D: Relive History with the First FPS Ever Created](#cub3d-relive-history-with-the-first-fps-ever-created)
	- [📖 Table of Contents](#-table-of-contents)
	- [🎮 Overview](#-overview)
	- [🛠️ Technology Stack](#️-technology-stack)
		- [Core Technologies](#core-technologies)
	- [✨ Features](#-features)
		- [Mandatory Features](#mandatory-features)
		- [Bonus Features](#bonus-features)
	- [🏗️ Project Architecture](#️-project-architecture)
		- [Key Components](#key-components)
	- [🚀 Getting Started](#-getting-started)
		- [Prerequisites](#prerequisites)
		- [Installation](#installation)
		- [Usage](#usage)
	- [🗺️ Map Format](#️-map-format)
		- [Map Elements](#map-elements)
		- [Configuration Elements](#configuration-elements)
	- [🎮 Controls](#-controls)
	- [📁 Project Structure](#-project-structure)
	- [📏 Coding Standards](#-coding-standards)
		- [Naming Conventions](#naming-conventions)
		- [Formatting Rules](#formatting-rules)
		- [Prohibited Elements](#prohibited-elements)
		- [File Organization](#file-organization)
		- [Example Function](#example-function)
	- [🔧 Development](#-development)
		- [Building](#building)
		- [Testing](#testing)
		- [Debugging](#debugging)
	- [👥 Authors](#-authors)
	- [📚 References](#-references)
	- [📜 License](#-license)

---

## 🎮 Overview

**Cub3D** is a 3D game engine that demonstrates the power of raycasting—a rendering technique that creates a pseudo-3D perspective in a 2D map. This project goes beyond the mandatory requirements by implementing:

- **Interactive doors** with smooth opening animations
- **Enemy sprites** with AI-driven movement and death states
- **Weapon system** with projectile physics and collision detection
- **Dynamic minimap** with fog of war exploration
- **Health system** with damage overlays and visual feedback
- **Multiple difficulty levels** through different map configurations
- **Texture-mapped walls** for immersive environments

The engine is built entirely in C using the **MLX42** graphics library, adhering to the rigorous **Norma** coding standards of 42 School.

---

## 🛠️ Technology Stack

| Component            | Technology     | Version                      |
| -------------------- | -------------- | ---------------------------- |
| **Language**         | C              | C99 Standard                 |
| **Graphics Library** | MLX42          | Latest                       |
| **Utility Library**  | libft (custom) | 1.0                          |
| **Build System**     | GNU Make       | 4.x                          |
| **Compiler**         | GCC/Clang      | With `-Wall -Wextra -Werror` |
| **Dependencies**     | GLFW, OpenGL   | System libraries             |

### Core Technologies

- **C Programming Language**: Pure C implementation following strict coding standards
- **MLX42**: Modern graphics library providing OpenGL-based rendering capabilities
- **libft**: Custom implementation of standard C library functions
- **Raycasting Algorithm**: Mathematical foundation for 3D rendering from 2D maps
- **DDA Algorithm**: Digital Differential Analyzer for precise ray-grid intersections

---

## ✨ Features

### Mandatory Features
✅ Raycasting engine with textured walls
✅ 4-directional wall textures (N, S, E, W)
✅ Floor and ceiling color customization
✅ Smooth player movement and rotation
✅ Map parsing with error handling
✅ Valid map validation (closed walls)
✅ Window management with proper cleanup

### Bonus Features
🎯 **Interactive Doors** - Open/close mechanics with collision
👾 **Enemy Sprites** - Animated enemies with pathfinding AI
🔫 **Weapon System** - Shooting mechanics with projectile physics
🗺️ **Dynamic Minimap** - Real-time player tracking with fog of war
❤️ **Health System** - Damage tracking and visual feedback
🎨 **Advanced Rendering** - Distance-based shading and fog effects
🖼️ **Sprite Management** - Depth sorting and billboard rendering
🎮 **Multiple Game States** - Menu system and game over screens

---

## 🏗️ Project Architecture

The project follows a modular architecture with clear separation of concerns:

```
┌─────────────────────────────────────────────┐
│           Main Engine Loop (MLX42)          │
└──────────────────┬──────────────────────────┘
                   │
        ┌──────────┴──────────┐
        │                     │
   ┌────▼─────┐         ┌─────▼───┐
   │  Parser  │         │ Engine  │
   └────┬─────┘         └────┬────┘
        │                    │
        │              ┌─────┴─────┬────────┬────────┐
        │              │           │        │        │
   ┌────▼────┐    ┌────▼───┐  ┌────▼──┐ ┌───▼──┐ ┌───▼──┐
   │  Config │    │ Render │  │ Player│ │Sprite│ │Weapon│
   └─────────┘    └───┬────┘  └───────┘ └──────┘ └──────┘
                      │
              ┌───────┼───────┐
              │       │       │
         ┌────▼──┐ ┌──▼────┐ ┌▼────┐
         │Raycast│ │Minimap│ │Shade│
         └───────┘ └───────┘ └─────┘
```

### Key Components

- **Parser**: Validates and loads `.cub` map files with texture and color configurations
- **Engine**: Core game loop, event handling, and state management
- **Raycasting**: DDA algorithm implementation for wall detection and rendering
- **Renderer**: Frame composition, texture mapping, and visual effects
- **Player**: Movement physics, collision detection, and camera control
- **Sprite System**: Enemy/collectible management with depth sorting
- **Weapon System**: Projectile physics and hit detection
- **Minimap**: 2D overview with exploration tracking

---

## 🚀 Getting Started

### Prerequisites

Before building Cub3D, ensure you have the following installed:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev libglfw3 xorg-dev

# Fedora
sudo dnf install make gcc glfw-devel libXext-devel

# macOS
brew install glfw cmake
```

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/jonnathan-ls/42-cursus-cub3d.git
   cd cub3d
   ```

2. **Build the project**
   ```bash
   make
   ```
   This will:
   - Compile the custom `libft` library
   - Build the MLX42 graphics library
   - Compile all source files
   - Link the final executable

3. **Verify the build**
   ```bash
   ./cub3d assets/maps/mandatory.cub
   ```

### Usage

Run the game with a map file:

```bash
# Standard window mode
./cub3d <path_to_map.cub>

# Windowed mode (non-fullscreen)
./cub3d <path_to_map.cub> -w
```

**Available Maps:**
- `assets/maps/mandatory.cub` - Simple test map (mandatory requirements)
- `assets/maps/level_easy.cub` - Easy difficulty with enemies
- `assets/maps/level_medium.cub` - Medium difficulty
- `assets/maps/level_hard.cub` - Challenging layout with multiple enemies

---

## 🗺️ Map Format

Maps are defined in `.cub` files with the following structure:

```
NO ./assets/textures/north.png
SO ./assets/textures/south.png
WE ./assets/textures/west.png
EA ./assets/textures/east.png

F 50,50,50
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000002000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000E10001
10000000000000001100000000001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements

| Character   | Description                              |
| ----------- | ---------------------------------------- |
| `0`         | Empty space (floor)                      |
| `1`         | Wall                                     |
| `N/S/E/W`   | Player starting position and orientation |
| `2`         | Door (bonus)                             |
| `3`         | Enemy sprite (bonus)                     |
| `C`         | Collectible coin (bonus)                 |
| ` ` (space) | Void/outside map                         |

### Configuration Elements

- **Texture Paths**: `NO`, `SO`, `WE`, `EA` followed by file path
- **Floor Color**: `F R,G,B` (RGB values 0-255)
- **Ceiling Color**: `C R,G,B` (RGB values 0-255)

---

## 🎮 Controls

| Key       | Action                            |
| --------- | --------------------------------- |
| `W`       | Move forward                      |
| `S`       | Move backward                     |
| `A`       | Strafe left                       |
| `D`       | Strafe right                      |
| `←`       | Rotate view left                  |
| `→`       | Rotate view right                 |
| `E`       | Interact (open/close doors)       |
| `Space`   | Shoot weapon                      |
| `M`       | Toggle minimap                    |
| `R`       | Toggle full map                   |
| `ESC`     | Exit game                         |
| **Mouse** | Look around (when window focused) |

---

## 📁 Project Structure

```
cub3d/
├── assets/                    # Game assets
│   ├── maps/                  # Map configuration files (.cub)
│   ├── sprites/               # Enemy and item sprites
│   └── textures/              # Wall, floor, and UI textures
│
├── configs/                   # Build configuration
│   ├── functions.mk           # Makefile helper functions
│   └── variables.mk           # Build variables and colors
│
├── includes/                  # Header files
│   ├── constants.h            # Game constants and macros
│   ├── engine.h               # Engine structure definitions
│   ├── parser.h               # Map parsing structures
│   ├── player.h               # Player state definitions
│   ├── raycast.h              # Raycasting utilities
│   ├── render.h               # Rendering functions
│   ├── shared.h               # Shared utilities
│   ├── sprite.h               # Sprite management
│   └── weapon.h               # Weapon system
│
├── libraries/                 # External libraries
│   ├── libft/                 # Custom C library
│   └── mlx42/                 # MLX42 graphics library
│
├── sources/                   # Source code
│   ├── main.c                 # Entry point
│   ├── engine/                # Core engine logic
│   │   ├── engine_init.c      # Initialization
│   │   ├── engine_loop.c      # Main game loop
│   │   ├── engine_hooks.c     # Event handlers
│   │   ├── player_update.c    # Player movement
│   │   ├── player_rotate.c    # Camera rotation
│   │   ├── ray_*.c            # Raycasting implementation
│   │   ├── doors_*.c          # Door mechanics
│   │   └── menu.c             # Menu system
│   │
│   ├── parser/                # Map parsing and validation
│   │   ├── parser_entry.c     # Main parsing logic
│   │   ├── parse_headers.c    # Config parsing
│   │   ├── parse_textures.c   # Texture loading
│   │   ├── collect_map_lines.c # Map data extraction
│   │   ├── validate_*.c       # Map validation
│   │   └── check_closed.c     # Wall closure check
│   │
│   ├── render/                # Rendering system
│   │   ├── frame.c            # Frame buffer management
│   │   ├── render_wall.c      # Wall rendering
│   │   ├── render_strip.c     # Vertical strip drawing
│   │   ├── render_shade.c     # Distance-based shading
│   │   ├── render_ceiling_floor.c # Ceiling/floor rendering
│   │   ├── render_health.c    # Health bar overlay
│   │   └── render_damage_overlay.c # Damage flash effect
│   │
│   ├── sprite/                # Sprite management
│   │   ├── sprite_init.c      # Sprite initialization
│   │   ├── sprite_update.c    # Sprite AI updates
│   │   ├── sprite_render.c    # Sprite rendering
│   │   ├── sprite_calc.c      # Distance calculations
│   │   ├── sprite_sort.c      # Depth sorting
│   │   ├── sprite_interact.c  # Collision/interaction
│   │   └── sprite_death.c     # Death animations
│   │
│   ├── weapon/                # Weapon system
│   │   ├── weapon_init.c      # Weapon initialization
│   │   ├── weapon_shoot.c     # Firing mechanics
│   │   ├── projectile_*.c     # Projectile physics
│   │   └── projectile_collision.c # Hit detection
│   │
│   ├── minimap/               # Minimap rendering
│   │   ├── minimap.c          # Main minimap logic
│   │   ├── minimap_draw.c     # Drawing functions
│   │   ├── minimap_player.c   # Player indicator
│   │   └── minimap_exploration.c # Fog of war
│   │
│   └── shared/                # Shared utilities
│       ├── memory_manager.c   # Memory allocation tracking
│       ├── math_utils.c       # Math helper functions
│       ├── map_utils.c        # Map utilities
│       └── color_utils.c      # Color manipulation
│
├── objects/                   # Compiled object files
├── Makefile                   # Build configuration
└── README.md                  # This file
```

---

## 📏 Coding Standards

This project strictly adheres to the **42 School Norminette** coding standards:

### Naming Conventions
- **Structures**: Prefix with `s_` (e.g., `s_engine`)
- **Typedefs**: Prefix with `t_` (e.g., `t_engine`)
- **Enums**: Prefix with `e_` (e.g., `e_sprite_type`)
- **Globals**: Prefix with `g_` (e.g., `g_memory_pool`)
- **All identifiers**: Use `snake_case` (lowercase with underscores)

### Formatting Rules
- **Function length**: Maximum 25 lines (excluding braces)
- **Line length**: Maximum 80 columns
- **Indentation**: 4-space tabs (ASCII 9)
- **Braces**: K&R style - opening brace on same line, closing on new line
- **Variables**: Maximum 5 per function, all declared at the top
- **Parameters**: Maximum 4 per function
- **Pointers**: Asterisk attached to variable name (`char *str`, not `char* str`)

### Prohibited Elements
❌ `for` loops (use `while` instead)
❌ `do...while` loops
❌ `switch/case` statements
❌ `goto` statements
❌ Ternary operators (`? :`)
❌ Variable Length Arrays (VLAs)
❌ Comments inside function bodies
❌ Multiple declarations per line

### File Organization
- **Headers**: Protected with include guards (`#ifndef`, `#define`, `#endif`)
- **Structs**: Only declared in header files (`.h`), not in `.c` files
- **Functions**: Maximum 5 functions per `.c` file
- **Return values**: Must be wrapped in parentheses: `return (value);`

### Example Function

```c
/**
 * Calculates Euclidean distance between two points.
 * @param x1 First point X coordinate.
 * @param y1 First point Y coordinate.
 * @param x2 Second point X coordinate.
 * @param y2 Second point Y coordinate.
 * @return The distance between the points.
 */
double	calc_euclidean_dist(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}
```

---

## 🔧 Development

### Building

```bash
# Full build
make

# Clean object files
make clean

# Clean everything (objects + executable)
make fclean

# Rebuild from scratch
make re

# Check code against Norminette
make norminette
```

### Testing

```bash
# Run with memory leak detection
make valgrind

# Test with different maps
./cub3d assets/maps/level_easy.cub
./cub3d assets/maps/level_medium.cub
./cub3d assets/maps/level_hard.cub
```

### Debugging

The project includes extensive error handling for:
- Invalid map file extensions
- Missing or incorrect texture paths
- Invalid color values (out of RGB range)
- Unclosed maps (missing walls)
- Invalid map characters
- Missing player start position
- Multiple player positions

All errors are reported with descriptive messages:
```
Error:
<specific error message>
```

---

## 👥 Authors

- **jonnathan-ls** - [@jonnathan-ls](https://github.com/jonnathan-ls)
- **peda-cos** - [@peda-cos](https://github.com/peda-cos)

*Developed as part of the 42 School curriculum.*

---

## 📚 References

- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42)
- [Raycasting Tutorial by Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)
- [42 School Norminette](https://github.com/42School/norminette)

---

## 📜 License

This project is part of the 42 School curriculum and follows their academic policies. Feel free to study and learn from the code, but please don't copy it for your own 42 projects.

---

<div align="center">

**Made with ❤️ and lots of ☕ at 42 School**

*"The best way to predict the future is to implement it."* - Alan Kay

</div>
