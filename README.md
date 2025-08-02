# 🎮 cub3D - My First RayCaster with miniLibX

<div align="center">

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

*Relive History with the First FPS Ever Created* 🕹️

</div>

## 📖 About

This project is inspired by the world-famous **Wolfenstein 3D** game, developed by Id Software and published in 1992 by Apogee Software. Considered the first true "First Person Shooter" in video game history, this project challenges you to create a dynamic 3D view inside a maze using **ray-casting principles**.

### 🎯 The Challenge

Create a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective, where you must find your way through the labyrinth. This project serves as a playground to explore the practical applications of mathematics in game development.

## ✨ Features

### 🎮 Core Functionality
- **Ray-casting engine** for 3D rendering
- **First-person perspective** navigation
- **Texture mapping** on walls (North, South, East, West)
- **Customizable floor and ceiling colors**
- **Smooth window management**

### ⌨️ Controls
- **Arrow Keys** (Left/Right): Look around in the maze
- **WASD Keys**: Move through the maze
  - `W`: Move forward
  - `A`: Move left  
  - `S`: Move backward
  - `D`: Move right
- **ESC**: Exit the program
- **Red Cross**: Close window and quit

### 🎨 Bonus Features
- 🚧 **Wall collisions**
- 🗺️ **Minimap system**
- 🚪 **Interactive doors** (open/close)
- 🎭 **Animated sprites**
- 🖱️ **Mouse rotation** for point of view

## 🛠️ Technical Requirements

### 📋 Specifications
- **Language**: C
- **Graphics Library**: miniLibX
- **Compliance**: 42 Norm
- **Memory Management**: No leaks allowed
- **Error Handling**: Proper exit on misconfiguration

### 📁 File Structure
```
cub3D/
├── Makefile
├── src/
├── include/
├── textures/
├── maps/
└── libft/
```

### 🗺️ Map Format (.cub)

The program takes a scene description file with `.cub` extension containing:

#### Map Characters
- `0`: Empty space
- `1`: Wall
- `N`, `S`, `E`, `W`: Player start position and orientation

#### Configuration Elements
```
NO ./path_to_north_texture    # North wall texture
SO ./path_to_south_texture    # South wall texture  
WE ./path_to_west_texture     # West wall texture
EA ./path_to_east_texture     # East wall texture
F 220,100,0                   # Floor color (RGB)
C 225,30,0                    # Ceiling color (RGB)
```

#### Example Map
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11000000110101011100000010001
10000000000000001100000010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- make
- miniLibX library
- Math library (-lm)

### 📦 Installation

1. **Clone the repository**
```bash
git clone https://github.com/yourusername/42-cursus-cub3d.git
cd 42-cursus-cub3d
```

2. **Compile the project**
```bash
make
```

3. **Run the game**
```bash
./cub3D maps/example.cub
```

### 🔧 Makefile Rules
- `make` or `make all`: Compile the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Recompile everything
- `make bonus`: Compile with bonus features

## 🎮 Gameplay

Navigate through the maze using the WASD keys and arrow keys. Your objective is to explore the 3D environment rendered using ray-casting techniques. The game provides different wall textures depending on the direction you're facing, creating an immersive first-person experience.

## 🏆 Learning Objectives

- **Ray-casting algorithms** and 3D graphics principles
- **Event handling** and user input management
- **Texture mapping** and color management
- **Mathematical applications** in game development
- **Memory management** and error handling in C
- **Graphics programming** with miniLibX

## 🎨 Visual Examples

The project recreates the classic Wolfenstein 3D aesthetic while allowing for creative freedom in texture and design choices. Bonus implementations can include modern features like minimaps, animated sprites, and enhanced visual effects.

## 📚 Resources

- [Original Wolfenstein 3D](http://users.atw.hu/wolf3d/) - Test the original game
- [Ray-casting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Mathematical principles
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Graphics library guide

## 🤝 Contributing

This is a 42 School project. While external contributions are not accepted, feel free to fork and experiment with your own implementations!

## 📝 License

This project is part of the 42 School curriculum. Please respect the academic integrity policies of your institution.

---

<div align="center">

**Made with ❤️ at 42 School**

*"Now, it's your turn to relive History..."*

</div>
