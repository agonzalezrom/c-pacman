#include "entities.h"
#include "map.h"
#include "graphics.h" // For drawing functions (to be implemented with SDL)
#include "config.h"

// Define global entities
Pacman pacman;
Ghost ghost;

// Array for converting grid index to pixel position (like original 'pos')
// Initialized in initializeEntities
int pixelPositions[MAP_COLS > MAP_ROWS ? MAP_COLS : MAP_ROWS];

/**
 * @brief Initializes the positions of Pacman and the ghost.
 */
void initializeEntities() {
    pacman.x = PACMAN_START_X;
    pacman.y = PACMAN_START_Y;
    pacman.facing = DIR_RIGHT; // Initial facing direction

    ghost.x = GHOST_START_X;
    ghost.y = GHOST_START_Y;

    // Initialize pixel position lookup table
    for (int i = 0; i < (MAP_COLS > MAP_ROWS ? MAP_COLS : MAP_ROWS); ++i) {
        pixelPositions[i] = i * TILE_SIZE;
    }
}

/**
 * @brief Clears the drawing from a specific grid cell.
 *
 * Uses a placeholder graphics function.
 * @param gridX The X coordinate of the grid cell.
 * @param gridY The Y coordinate of the grid cell.
 */
void clearCell(int gridX, int gridY) {
    int screenX = pixelPositions[gridX];
    int screenY = pixelPositions[gridY];
    // Placeholder clear rectangle function
    fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, 0, 0, 0); // Fill with black
}

/**
 * @brief Draws Pacman on the screen.
 *
 * Uses placeholder graphics functions.
 * @param lastDirection The direction Pacman moved in the previous frame.
 */
void drawPacman(Direction lastDirection) {
    int centerX = pixelPositions[pacman.x] + TILE_SIZE / 2;
    int centerY = pixelPositions[pacman.y] + TILE_SIZE / 2;
    int radius = TILE_SIZE / 2 - 1; // Slightly smaller than the tile

    // Placeholder color setting
    setDrawColor(255, 252, 2); // Yellow

    // Placeholder drawing logic (e.g., draw a circle)
    // The original code used pieslice for the mouth effect, which needs SDL equivalent
    // For now, just draw a circle
    fillCircle(centerX, centerY, radius);

    // Clear the previous position based on the *opposite* of the last move direction
    switch (lastDirection) {
        case DIR_UP:    clearCell(pacman.x, pacman.y + 1); break;
        case DIR_DOWN:  clearCell(pacman.x, pacman.y - 1); break;
        case DIR_LEFT:  clearCell(pacman.x + 1, pacman.y); break;
        case DIR_RIGHT: clearCell(pacman.x - 1, pacman.y); break;
        case DIR_NONE:  break; // No previous move to clear
    }
}

/**
 * @brief Moves Pacman based on the input direction.
 *
 * Checks the movementGrid for validity.
 * @param direction The direction to move Pacman.
 * @return true if Pacman moved, false otherwise.
 */
bool movePacman(Direction direction) {
    int nextX = pacman.x;
    int nextY = pacman.y;
    bool moved = false;

    switch (direction) {
        case DIR_UP:
            nextY--;
            break;
        case DIR_DOWN:
            nextY++;
            break;
        case DIR_LEFT:
            nextX--;
            break;
        case DIR_RIGHT:
            nextX++;
            break;
        case DIR_NONE:
            return false; // No movement requested
    }

    // Check boundaries and movement grid
    // Note: The original movementGrid access needs careful index checking
    // Assuming movementGrid indices correspond to mapLayout indices [1..18][1..18]
    if (nextY >= 1 && nextY < MAP_ROWS - 1 && nextX >= 1 && nextX < MAP_COLS - 1 &&
        movementGrid[nextY - 1][nextX - 1] == 1) // Adjust indices for movementGrid
    {
        pacman.x = nextX;
        pacman.y = nextY;
        pacman.facing = direction;
        moved = true;
    }

    return moved;
}

/**
 * @brief Draws the ghost on the screen.
 *
 * Uses placeholder graphics functions.
 */
void drawGhost() {
    int screenX = pixelPositions[ghost.x];
    int screenY = pixelPositions[ghost.y];

    // Placeholder drawing logic (e.g., draw a colored rectangle)
    // Original used multiple bars, needs SDL equivalent
    setDrawColor(230, 230, 230); // White-ish
    fillRect(screenX + TILE_SIZE / 4, screenY + TILE_SIZE / 4,
             TILE_SIZE / 2, TILE_SIZE / 2, 230, 230, 230);
}

/**
 * @brief Moves the ghost based on some logic (currently tied to Pacman's move).
 *
 * This logic is very basic and needs significant improvement (e.g., A* pathfinding).
 * Uses placeholder graphics functions for clearing.
 * @param pacmanLastDirection The last direction Pacman moved.
 */
void moveGhost(Direction pacmanLastDirection) {
    // Original logic was simplistic: try to move opposite to pacman's last move.
    // This needs a proper AI implementation later.
    // For now, keep a similar (but flawed) logic for structure.

    int prevX = ghost.x;
    int prevY = ghost.y;
    int nextX = ghost.x;
    int nextY = ghost.y;
    bool moved = false;

    // Simplified: try moving based on Pacman's last direction (needs reversal/better logic)
    // Check boundaries and movement grid
    switch (pacmanLastDirection) {
        case DIR_UP: // Pacman moved up, try moving ghost up?
            nextY--;
            break;
        case DIR_DOWN: // Pacman moved down, try moving ghost down?
            nextY++;
            break;
        case DIR_LEFT: // Pacman moved left, try moving ghost left?
            nextX--;
            break;
        case DIR_RIGHT:// Pacman moved right, try moving ghost right?
            nextX++;
            break;
        case DIR_NONE:
            return; // No trigger to move
    }

    // Basic validity check (needs improvement)
    if (nextY >= 1 && nextY < MAP_ROWS - 1 && nextX >= 1 && nextX < MAP_COLS - 1 &&
        movementGrid[nextY - 1][nextX - 1] == 1) {
        ghost.x = nextX;
        ghost.y = nextY;
        moved = true;
    }

    if (moved) {
        drawGhost();
        clearCell(prevX, prevY);
    }
} 