## so_long

A small 2D top‑down game built in C with MiniLibX (X11) for the 42 "so_long" project. Guide the wizard to collect all crystals and reach the portal while navigating a forest maze.

### Demo
![so_long demo](assets/so_long_demo.gif)

If the GIF does not load, place your recording at `assets/so_long_demo.gif`.

### Features
- Smooth tile-based movement with WASD
- Collectibles and exit logic with move counter
- Map validator (shape, walls, entity counts, reachability)
- Simple, readable code structure and error handling

### Prerequisites
- Linux or WSL (Ubuntu recommended)
- Packages: `build-essential`, `libx11-dev`, `libxext-dev`, `libbsd-dev`, `libxrandr-dev`, `libxi-dev`, `libxinerama-dev`, `libxcursor-dev`

Install on Debian/Ubuntu:
```bash
sudo apt-get update -y && sudo apt-get install -y \
  build-essential libx11-dev libxext-dev libbsd-dev \
  libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev
```

### Build
```bash
make
```
The default target will first build MiniLibX in `minilibx-linux/`, then compile the game to `./so_long`.

Useful targets:
- `make` – build everything
- `make clean` – remove object files
- `make fclean` – remove objects and binary
- `make re` – full rebuild

### Run
```bash
./so_long map.ber
```
Replace `map.ber` with your map path.

Exit the game with ESC or by closing the window.

### Controls
- W / A / S / D: Move
- ESC: Quit

### Map format
The map is a rectangular grid using these characters:
- `0`: empty floor
- `1`: wall
- `P`: player start (exactly 1)
- `C`: collectible (≥ 1)
- `E`: exit (≥ 1)

All maps must be enclosed by walls and be solvable (all collectibles and an exit must be reachable from `P`).

Example (`map.ber`):
```text
1111111
1P0C0E1
1000001
1C01001
1111111
```

### Project structure
```text
assets/                 # XPM sprites (wizard, crystal, tree wall, etc.)
get_next_line/          # Line reader utility (GNL)
minilibx-linux/         # MiniLibX sources and static library
so_long.c, so_long2.c   # Core game loop and event handling
window_utils*.c         # Rendering helpers and MLX wrappers
map_*.c                 # Map loading, parsing, validation
utils.c                 # Misc utilities (errors, strings, etc.)
Makefile                # Build rules (builds MLX then the game)
```

### Troubleshooting
- Linker error `cannot find -lmlx`:
  - Ensure `make` builds `minilibx-linux/libmlx.a` successfully.
  - On WSL, run inside Ubuntu with X server (e.g. VcXsrv/X410) and `DISPLAY` set.
- Window does not open on WSL:
  - Start an X server on Windows and export `DISPLAY` in your shell, e.g.:
    ```bash
    export DISPLAY=$(grep -m1 nameserver /etc/resolv.conf | awk '{print $2}'):0
    ```

### Recording a demo GIF (optional)
Using `ffmpeg` and `ffmpeg`-based `gif` generation:
```bash
sudo apt-get install -y ffmpeg
ffmpeg -video_size 800x600 -framerate 30 -f x11grab -i $DISPLAY \
  -t 10 /tmp/so_long.mp4
ffmpeg -i /tmp/so_long.mp4 -vf "fps=12,scale=640:-1:flags=lanczos" \
  -loop 0 assets/so_long_demo.gif
```

### License
This repository is for educational purposes in the context of 42 School projects. Asset files are included for convenience; review their licenses before reuse.

### Acknowledgements
- MiniLibX by 42
- X11 libraries and community docs