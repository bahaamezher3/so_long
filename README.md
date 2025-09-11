# so_long

A simple 2D top-down collectible game built with the MiniLibX (X11) graphics library. You control the player, collect all crystals, and reach the portal to win. This project follows the 42 school specifications for the so_long project.

## Showcase

![Gameplay](gif/game.gif)

## Features
- 2D tile-based rendering with MiniLibX
- Map loading from a `.ber` file
- Map validation (rectangular, walled, element counts, path reachability)
- Keyboard controls (W/A/S/D or arrows, ESC to quit)
- Move counter and win condition when all collectibles are gathered

## Requirements
- Linux environment
- `gcc` and `make`
- X11 dependencies for MiniLibX:
  - `libx11-dev`
  - `libxext-dev`
  - `libbsd-dev` (often required)
  - `zlib1g-dev` (often required)
  - `libxrandr-dev` (for some environments)

On Debian/Ubuntu, install with:
```bash
sudo apt update && sudo apt install -y build-essential libx11-dev libxext-dev libbsd-dev zlib1g-dev libxrandr-dev
```

## Build
The repository includes MiniLibX as a subdirectory and a Makefile to build everything.
```bash
make
```
This will:
- Build `minilibx-linux` and produce `libmlx.a`
- Compile project sources and link with X11/MiniLibX
- Produce the executable `so_long`

Clean artifacts:
```bash
make clean   # remove object files
make fclean  # remove objects and executable
make re      # full rebuild
```

## Run
Provide a valid `.ber` map file:
```bash
./so_long map.ber
```

### Controls
- W / Up Arrow: move up
- A / Left Arrow: move left
- S / Down Arrow: move down
- D / Right Arrow: move right
- ESC: quit the game

### Objective
- Collect all `C` (crystals)
- Reach the exit `E`
- You cannot pass through walls `1`
- Floor tiles `0` are walkable

## Map Format
Maps are plain text rectangular grids using the following characters:
- `1`: Wall
- `0`: Floor (empty space)
- `C`: Collectible
- `E`: Exit
- `P`: Player start (exactly one)

Validation rules enforced by the game:
- The map must be rectangular (all rows have the same length)
- The map must be fully enclosed by walls (`1`) on the outer boundary
- Exactly 1 player `P` and exactly 1 exit `E`
- At least 1 collectible `C`
- All collectibles must be reachable from the player
- The exit must be reachable from the player

Example (`map.ber` in this repo):
```text
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
```

## Project Structure
```
so_long/
├─ assets/                  # XPM sprites (player, wall, floor, crystal, exit)
│  ├─ crystal.xpm
│  ├─ forest_floor.xpm
│  ├─ portal.xpm
│  ├─ tree_wall.xpm
│  └─ wizard.xpm
├─ get_next_line/           # Line-by-line file reader used by the map loader
│  ├─ get_next_line.c
│  ├─ get_next_line_utils.c
│  ├─ get_next_line.h
│  └─ README.md
├─ minilibx-linux/          # MiniLibX library (X11)
├─ so_long.h                # Shared types, constants, prototypes
├─ so_long.c                # File checks, helpers, and utility functions
├─ so_long2.c               # Map dimensioning, loader entry, main()
├─ so_long3.c               # Dimension scanning helpers
├─ so_long4.c               # Loader helpers and error handling
├─ map_utils.c              # DFS helpers and map copy utilities
├─ map_utils2.c             # Map duplication and DFS runners from player
├─ map_validator.c          # Boundary and element checks, reachability checks
├─ map_validator2.c         # Validation orchestration and error reporting
├─ map_validator3.c         # Element count updates and validation
├─ window_utils.c           # MLX/window init, game state init
├─ window_utils2.c          # Image loading, player scan, collectible count
├─ window_utils3.c          # Draw tile/map, redraw moves, win updates
├─ window_utils4.c          # Input handling, moves, close
├─ window_utils5.c          # Image data validation and error path
├─ utils.c                  # I/O helpers, length, error exits, cleanup
├─ Makefile                 # Build rules (links MiniLibX and X11)
└─ map.ber                  # Sample map
```

## Technical Notes
- Rendering is tile-based with `TILE_SIZE = 32`
- Input keycodes support both WASD and X11 arrow keys
- Map loading uses `get_next_line()`; trailing whitespace/newlines are trimmed
- Robust error paths: descriptive messages and cleanup before exiting
- MiniLibX usage: `mlx_init`, `mlx_new_window`, `mlx_xpm_file_to_image`, `mlx_put_image_to_window`

## Troubleshooting
- Missing X11 headers/libraries: install packages listed in Requirements
- Wayland-only environments: ensure X11 compatibility packages are present
- If sprites do not load, verify `.xpm` files exist in `assets/` and paths match

## License / Attribution
- MiniLibX: see `minilibx-linux/README.md` and `LICENSE`
- This is an educational 42 project implementation by @bmezher
