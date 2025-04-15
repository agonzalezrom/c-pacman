# C Pacman Clone (SDL2 Version)

A simple Pacman clone written in C using the SDL2 library for cross-platform graphics and input.
This project is a refactoring of an older Windows-specific version (using `winbgim.h`).

## Current Status

*   Basic game logic implemented (movement, pellet collection, collision detection).
*   Uses SDL2 for window creation, basic shape rendering (lines, rectangles), and input handling.
*   Map layout loaded from code.
*   Basic game loop with start, playing, win, and lose states.
*   **Limitations:**
    *   Text rendering (score, messages) currently prints to console, not the game window (requires SDL_ttf).
    *   Pacman, Ghost, and Pellets are rendered as simple shapes (circles/rectangles).
    *   Ghost AI is very basic and predictable.
    *   No sound effects or music.
    *   Only one level and one ghost type.

## Dependencies

*   A C compiler (like `gcc` or `clang`)
*   `make`
*   **SDL2 Development Library:**
    *   Debian/Ubuntu: `sudo apt update && sudo apt install libsdl2-dev`
    *   macOS (Homebrew): `brew install sdl2`
    *   Fedora: `sudo dnf install SDL2-devel`
    *   Windows (MSYS2/MinGW): Follow SDL2 setup instructions for MinGW.

## Compilation

Navigate to the project's root directory in your terminal and run:

```bash
make
```

This will compile the source files and create the executable in the `build/` directory.

To clean the build files, run:
```bash
make clean
```

## Running the Game

After successful compilation, run the executable:

```bash
./build/pacman_clone
```

**Controls:**
*   Arrow Keys or WASD: Move Pacman
*   ESC: Quit the game
*   Any key on the start screen: Start the game
