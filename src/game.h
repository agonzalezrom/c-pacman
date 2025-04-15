#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// Enum for game state
typedef enum {
    GAME_STATE_START_SCREEN,
    GAME_STATE_PLAYING,
    GAME_STATE_WIN,
    GAME_STATE_LOSE
} GameState;

// Declare global game state variable
extern GameState currentGameState;

/**
 * @brief Initializes the game state, score, pellets, etc.
 */
void initializeGame();

/**
 * @brief Runs the main game loop.
 *
 * Handles input processing, updating game state, and rendering.
 */
void runGameLoop();

/**
 * @brief Updates the score display.
 */
void updateScoreDisplay();

/**
 * @brief Draws all the pellets (dots) on the map.
 *
 * Needs to track which pellets have been eaten.
 */
void drawPellets();

/**
 * @brief Checks if Pacman has collided with a pellet at its current location.
 *
 * If a pellet exists and hasn't been eaten, consumes it, increments score,
 * and updates the pellet state.
 * @param gridX Pacman's X grid position.
 * @param gridY Pacman's Y grid position.
 */
void checkPelletCollision(int gridX, int gridY);

/**
 * @brief Checks for game over conditions (collision with ghost).
 *
 * @return true if game over (collision), false otherwise.
 */
bool checkGameOverCondition();

/**
 * @brief Checks for win condition (all pellets eaten).
 *
 * @return true if win condition met, false otherwise.
 */
bool checkWinCondition();

/**
 * @brief Displays the initial start screen message.
 */
void showStartScreen();

/**
 * @brief Displays the game over (lose) message.
 */
void showLoseScreen();

/**
 * @brief Displays the win message.
 */
void showWinScreen();

/**
 * @brief Gets the current score.
 *
 * @return The current score.
 */
int getScore();


#endif // GAME_H 