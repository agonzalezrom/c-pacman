#include "input.h"
#include <SDL.h> // For SDL events (Corrected include path)
#include "game.h" // Include game state
#include "graphics.h" // For clearScreen, drawPacman, drawGhost
#include "map.h" // For drawMap
#include "entities.h" // For drawPacman, drawGhost, pacman

// Flag to track if any key was pressed, used for starting the game
static bool anyKeyPressed = false;

/**
 * @brief Processes pending SDL events (keyboard, window close).
 *
 * Uses SDL_PollEvent to check for events without blocking.
 * Updates requestedDirection and shouldQuit based on events.
 * Sets a flag if any key is pressed during the start screen state.
 * @param requestedDirection Pointer to store the requested move direction.
 * @param shouldQuit Pointer to flag if the game should quit.
 */
void processInput(Direction* requestedDirection, bool* shouldQuit) {
    SDL_Event event;
    *requestedDirection = DIR_NONE; // Default to no direction change
    anyKeyPressed = false; // Reset flag each frame

    // Poll for events
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: // User hit the window close button
                *shouldQuit = true;
                break;

            case SDL_KEYDOWN: // A key was pressed
                anyKeyPressed = true; // Signal that a key was pressed for start screen
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_w: // Allow WASD too
                        *requestedDirection = DIR_UP;
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        *requestedDirection = DIR_DOWN;
                        break;
                    case SDLK_LEFT:
                    case SDLK_a:
                        *requestedDirection = DIR_LEFT;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        *requestedDirection = DIR_RIGHT;
                        break;
                    case SDLK_ESCAPE: // Escape key to quit
                        *shouldQuit = true;
                        break;
                    default:
                        // Any other key press is noted by anyKeyPressed flag
                        break;
                }
                break;

            // We could handle SDL_KEYUP if needed, but not necessary for this movement style
        }
    }

    // Check if we are in the start screen state and any key was pressed
    if (currentGameState == GAME_STATE_START_SCREEN && anyKeyPressed) {
         currentGameState = GAME_STATE_PLAYING;
         // Perform initial draw immediately after state change
         clearScreen();
         drawMap();
         drawPellets();
         drawPacman(pacman.facing); // Draw initial pacman
         drawGhost();               // Draw initial ghost
         // Don't present here, let the main loop handle rendering
    }
} 