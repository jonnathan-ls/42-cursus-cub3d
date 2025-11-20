# cub3D Test Cases

Here are the relevant test cases for **cub3D**, covering mandatory requirements, edge cases, and bonus features.

## 1. Compilation & Setup

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **Basic Compilation** | Verify the project compiles without errors. | Run `make` in the root directory. | `cub3D` executable is created. No errors or warnings (especially with `-Wall -Wextra -Werror`). |
| **Re-compilation** | Verify `make re` works correctly. | Run `make re`. | Project cleans and rebuilds from scratch successfully. |
| **Clean Rules** | Verify cleanup rules. | Run `make clean` then `make fclean`. | Object files are removed, then the executable is removed. |

## 2. Argument & File Handling

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **No Arguments** | Run program without a map file. | Run `./cub3D`. | Error message printed (e.g., "Error: Usage ./cub3D <map.cub>"). Program exits cleanly. |
| **Invalid Extension** | Run with a file not ending in `.cub`. | Run `./cub3D map.txt`. | Error message printed (e.g., "Error: Invalid file extension"). Program exits cleanly. |
| **Non-existent File** | Run with a file that doesn't exist. | Run `./cub3D ghost.cub`. | Error message printed (e.g., "Error: Cannot open file"). Program exits cleanly. |
| **Directory as File** | Run with a directory path. | Run `./cub3D assets/`. | Error message printed. Program exits cleanly. |

## 3. Map Parsing (Mandatory)

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **Valid Map** | Load a compliant map. | Run `./cub3D assets/maps/mandatory.cub`. | Game launches successfully. |
| **Missing Texture** | Map file missing a texture path (e.g., NO). | Create a map with missing `NO` line and run. | Error message "Error: Missing texture identifier". Exit cleanly. |
| **Invalid Color Format** | RGB value out of range or non-numeric. | Create map with `F 255,300,0` or `C 0,0,a`. | Error message "Error: Invalid color format". Exit cleanly. |
| **Duplicate Keys** | Duplicate texture or color identifiers. | Create map with two `NO` lines. | Error message "Error: Duplicate identifier". Exit cleanly. |
| **Map Not Enclosed** | Map has a hole to the void (missing wall). | Create map with a `0` on the edge. | Error message "Error: Map is not closed/surrounded by walls". Exit cleanly. |
| **Multiple Players** | Map has more than one start position. | Create map with `N` and `S` characters. | Error message "Error: Multiple player start positions". Exit cleanly. |
| **No Player** | Map has no start position. | Create map with only `0` and `1`. | Error message "Error: No player start position". Exit cleanly. |
| **Invalid Character** | Map contains unknown char (e.g., 'X'). | Create map with `X` inside the walls. | Error message "Error: Invalid character in map". Exit cleanly. |
| **Empty Map** | File has headers but no map content. | Create file with textures but no `1` or `0`. | Error message "Error: No map found". Exit cleanly. |@@

## 4. Gameplay & Controls (Mandatory)

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **Movement** | Test WASD keys. | Press `W`, `A`, `S`, `D`. | Player moves forward, left (strafe), backward, right (strafe) relative to view. |
| **Rotation** | Test Left/Right Arrow keys. | Press `←` and `→`. | Camera view rotates left and right. |
| **Wall Collision** | Ensure player cannot walk through walls. | Walk straight into a wall. | Player stops at the wall; does not clip through or crash. |
| **Exit - ESC** | Test exit via keyboard. | Press `ESC`. | Window closes, program exits cleanly (return 0). |
| **Exit - Window X** | Test exit via window manager. | Click the window's close (X) button. | Window closes, program exits cleanly. |

## 5. Rendering (Mandatory)

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **Texture Orientation** | Verify correct texture on correct wall. | Stand in a corner and look at North vs East walls. | Different textures should be visible if defined differently in `.cub` file. |
| **Floor/Ceiling** | Verify solid colors. | Look up and down (if pitch implemented) or observe background. | Floor and Ceiling match the RGB colors defined in the `.cub` file. |

## 6. Bonus Features

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **Minimap Display** | Check if minimap exists. | Launch game. | A small map overlay is visible (usually top-left or top-right). |
| **Minimap Update** | Check if minimap updates with movement. | Move the player. | Player marker on minimap moves; map rotates or updates accordingly. |
| **Mouse Rotation** | Test mouse look. | Move mouse left/right. | Camera view rotates left/right. |
| **Door Interaction** | Open/Close doors. | Approach a door and press interaction key (e.g., `E` or `Space`). | Door texture changes or disappears (opens); player can walk through. |
| **Sprite Rendering** | Check for objects/enemies. | Find a sprite on the map. | Sprite is rendered, scales correctly with distance, and is always facing the player (billboarding). |
| **Weapon Shooting** | Test weapon firing. | Press Left Click or designated shoot key. | Weapon animation plays (fire frame); projectile logic triggers (if implemented). |

## 7. Memory & Stability

| Name | Description | Steps | Expected Result |
| :--- | :--- | :--- | :--- |
| **Valgrind - Clean Exit** | Check for leaks on normal exit. | `valgrind ./cub3D assets/maps/mandatory.cub`, then exit. | "All heap blocks were freed -- no leaks are possible". |
| **Valgrind - Error Exit** | Check for leaks on parsing error. | `valgrind ./cub3D assets/maps/invalid_map.cub`. | "All heap blocks were freed" (Parsing errors should free allocated config before exiting). |
| **Resize/Minimize** | Test window stability. | Minimize and restore the window. | Game should not crash; rendering should resume correctly. |
