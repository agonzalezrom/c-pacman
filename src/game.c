#include "game.h"
#include "graphics.h"
#include "entities.h"
#include "map.h"
#include "input.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h> // For itoa (or snprintf)
#include <string.h> // For memset
#include <SDL.h> // For SDL_Delay (Corrected include path)

// Game state
GameState currentGameState;
int score;
int pelletsRemaining;

// Track eaten pellets (similar to original 'mem')
// 1: eaten, 0: not eaten
int pelletState[MAP_ROWS][MAP_COLS];

extern int pixelPositions[]; // From entities.c

/**
 * @brief Initializes the game state, score, pellets, etc.
 */
void initializeGame() {
    currentGameState = GAME_STATE_START_SCREEN;
    score = 0;
    pelletsRemaining = 0;
    memset(pelletState, 0, sizeof(pelletState)); // Clear pellet state

    // Count initial pellets and set state
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (mapLayout[i][j] == 1) {
                // Check if it's not the starting position of Pacman or Ghost
                if (!((j == PACMAN_START_X && i == PACMAN_START_Y) || (j == GHOST_START_X && i == GHOST_START_Y))) {
                    pelletsRemaining++;
                    pelletState[i][j] = 0; // Mark as not eaten initially
                } else {
                    pelletState[i][j] = 1; // Mark entity start positions as "eaten"
                }
            } else {
                 pelletState[i][j] = 1; // Mark walls as "eaten"
            }
        }
    }

    // Initialize Pacman and Ghost positions
    initializeEntities();
}

/**
 * @brief Updates the score display.
 *
 * Uses placeholder graphics function.
 */
void updateScoreDisplay() {
    char scoreText[10];
    // Use snprintf for safety and portability instead of itoa
    snprintf(scoreText, sizeof(scoreText), "%d", score);

    // Placeholder text drawing
    drawText("SCORE", SCREEN_WIDTH - 200, 60, 255, 255, 255);
    drawText(scoreText, SCREEN_WIDTH - 200, 90, 255, 255, 255);

    // Display win condition text
    char winText[50];
    snprintf(winText, sizeof(winText), "Pellets left: %d", pelletsRemaining);
    drawText(winText, SCREEN_WIDTH - 300, 200, 255, 255, 255);
    // drawText("to win!", SCREEN_WIDTH - 300, 230, 255, 255, 255);

}

/**
 * @brief Draws all the active pellets (dots) on the map.
 *
 * Uses placeholder graphics function.
 */
void drawPellets() {
    // Placeholder color
    setDrawColor(211, 211, 40); // Pellet color

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            // Draw pellet if it's a path and not eaten
            if (mapLayout[i][j] == 1 && pelletState[i][j] == 0) {
                int centerX = pixelPositions[j] + TILE_SIZE / 2;
                int centerY = pixelPositions[i] + TILE_SIZE / 2;
                // Placeholder circle drawing
                fillCircle(centerX, centerY, 2); // Small radius for pellet
            }
        }
    }
}

/**
 * @brief Checks if Pacman has collided with a pellet at its current location.
 *
 * If a pellet exists and hasn't been eaten, consumes it, increments score,
 * and updates the pellet state.
 * @param gridX Pacman's X grid position.
 * @param gridY Pacman's Y grid position.
 */
void checkPelletCollision(int gridX, int gridY) {
    // Check bounds just in case
    if (gridY >= 0 && gridY < MAP_ROWS && gridX >= 0 && gridX < MAP_COLS) {
         // If it's a path tile and the pellet hasn't been eaten yet
        if (mapLayout[gridY][gridX] == 1 && pelletState[gridY][gridX] == 0) {
            score += 5; // Increment score (as in original code)
            pelletsRemaining--;
            pelletState[gridY][gridX] = 1; // Mark as eaten
            // Need to visually remove the pellet too - clearing the cell might work
             clearCell(gridX, gridY);
        }
    }
}

/**
 * @brief Checks for game over conditions (collision with ghost).
 *
 * @return true if game over (collision), false otherwise.
 */
bool checkGameOverCondition() {
    return (pacman.x == ghost.x && pacman.y == ghost.y);
}

/**
 * @brief Checks for win condition (all pellets eaten).
 *
 * @return true if win condition met, false otherwise.
 */
bool checkWinCondition() {
    // Original code used score == 600, let's use pelletsRemaining for accuracy
    return (pelletsRemaining <= 0);
}

/**
 * @brief Displays the initial start screen message.
 *
 * Uses placeholder graphics function.
 */
void showStartScreen() {
    clearScreen(); // Clear screen first
    // Placeholder text drawing
    drawText("PACMAN", (SCREEN_WIDTH / 2) - 50, SCREEN_HEIGHT / 2, 246, 255, 5);
    drawText("Press any key to start...", (SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) + 30, 255, 255, 255);
    presentScreen();

    // Waiting for input is now handled non-blockingly in processInput
}

/**
 * @brief Displays the game over (lose) message.
 *
 * Uses placeholder graphics function.
 */
void showLoseScreen() {
     clearScreen();
    // Placeholder text drawing
    drawText("GAME OVER!", (SCREEN_WIDTH / 2) - 50, SCREEN_HEIGHT / 2, 209, 10, 0);
    presentScreen();
    // Add delay or wait for input to close
    SDL_Delay(3000); // Show for 3 seconds before loop continues (and potentially exits)
}

/**
 * @brief Displays the win message.
 *
 * Uses placeholder graphics function.
 */
void showWinScreen() {
     clearScreen();
    // Placeholder text drawing
    drawText("YOU WIN!", (SCREEN_WIDTH / 2) - 50, SCREEN_HEIGHT / 2, 0, 209, 10);
    presentScreen();
     // Add delay or wait for input to close
    SDL_Delay(3000); // Show for 3 seconds before loop continues (and potentially exits)
}

/**
 * @brief Gets the current score.
 *
 * @return The current score.
 */
int getScore() {
    return score;
}

/**
 * @brief Runs the main game loop.
 *
 * Handles input processing, updating game state, and rendering based on currentGameState.
 */
void runGameLoop() {
    bool quit = false;
    Direction requestedDirection = DIR_NONE;
    Direction lastMovedDirection = DIR_NONE; // Track last successful move

    // Initial draw for start screen state handled by processInput upon transition
    if (currentGameState == GAME_STATE_START_SCREEN) {
        showStartScreen();
    }

    while (!quit) {
        Uint32 frameStart = SDL_GetTicks(); // Get time at frame start

        // 1. Handle Input (also handles state transition from START_SCREEN)
        processInput(&requestedDirection, &quit);

        if (quit) break; // Exit loop if quit requested

        // 2. Update State (only if playing)
        if (currentGameState == GAME_STATE_PLAYING) {
            lastMovedDirection = DIR_NONE;
            if (requestedDirection != DIR_NONE) {
                if (movePacman(requestedDirection)) {
                     lastMovedDirection = requestedDirection;
                     checkPelletCollision(pacman.x, pacman.y);
                     // Only move ghost if Pacman moved (original logic)
                     moveGhost(lastMovedDirection); // Basic ghost movement
                }
            }

            // Check win/lose conditions
            if (checkGameOverCondition()) {
                currentGameState = GAME_STATE_LOSE;
                showLoseScreen(); // Show lose screen immediately
                quit = true; // End game after showing lose screen
            } else if (checkWinCondition()) {
                currentGameState = GAME_STATE_WIN;
                showWinScreen(); // Show win screen immediately
                quit = true; // End game after showing win screen
            }
        }

        // 3. Render (only if playing)
        if (currentGameState == GAME_STATE_PLAYING) {
           clearScreen(); // <--- ADDED: Clear the screen at the start of rendering
           drawMap();     // <--- ADDED: Redraw map every frame for now
           drawPellets(); // <--- ADDED: Redraw pellets every frame for now

            // Pacman and Ghost drawing (includes clearing previous cell)
            if (lastMovedDirection != DIR_NONE) {
                 drawPacman(lastMovedDirection); // Draw Pacman at new location if moved
            } else {
                 // Redraw Pacman in same spot if didn't move (or handle differently)
                 // For now, drawPacman clears the *previous* cell based on last move,
                 // so if static, might not need redraw unless pellets nearby changed.
                 // Let's redraw anyway for simplicity for now.
                 drawPacman(pacman.facing); // Redraw even if static
            }
            drawGhost(); // Redraw ghost every frame (moveGhost handles its previous pos clear)

            updateScoreDisplay(); // Update score text (placeholder needs fixing)
            presentScreen(); // Show the completed frame
        }
        // If in START screen, rendering is handled by showStartScreen() and input transition

        // 4. Frame Rate Control
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        const int FRAME_DELAY = 1000 / 15; // Target ~15 FPS (adjust as needed)
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }

        /* Old delay logic:
         // Add a small delay to control frame rate (SDL_Delay)
         SDL_Delay(66); // roughly 15 FPS (original game logic might expect slower pace)
         // Placeholder delay:
        #ifdef _WIN32
            // Sleep(100); // Windows
        #else
            // usleep(100000); // Linux/macOS (100ms)
        #endif
        */
    }
    // Potentially add a final delay after win/lose before shutdownGraphics is called in main
    // SDL_Delay(2000);
} 