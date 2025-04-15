#ifndef ENTITIES_H
#define ENTITIES_H

#include "config.h"
#include <stdbool.h>

// Enum for movement direction
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_NONE // For initial state or no movement
} Direction;

// Structure for Pacman
typedef struct {
    int x;          // X position (grid index)
    int y;          // Y position (grid index)
    Direction facing; // Current direction Pacman is facing
} Pacman;

// Structure for Ghost
typedef struct {
    int x;          // X position (grid index)
    int y;          // Y position (grid index)
    // Add other ghost properties like color, state (chase, scatter, frightened), etc. later
} Ghost;

// Declare global entities
extern Pacman pacman;
extern Ghost ghost;

/**
 * @brief Initializes the positions of Pacman and the ghost.
 */
void initializeEntities();

/**
 * @brief Draws Pacman on the screen.
 *
 * @param lastDirection The direction Pacman moved in the previous frame.
 */
void drawPacman(Direction lastDirection);

/**
 * @brief Clears the drawing from a specific grid cell.
 *
 * Used to erase the entity from its previous position before redrawing.
 * @param gridX The X coordinate of the grid cell.
 * @param gridY The Y coordinate of the grid cell.
 */
void clearCell(int gridX, int gridY);

/**
 * @brief Moves Pacman based on the input direction.
 *
 * @param direction The direction to move Pacman.
 * @return true if Pacman moved, false otherwise.
 */
bool movePacman(Direction direction);

/**
 * @brief Draws the ghost on the screen.
 */
void drawGhost();

/**
 * @brief Moves the ghost based on some logic (currently tied to Pacman's move).
 *
 * @param pacmanLastDirection The last direction Pacman moved.
 */
void moveGhost(Direction pacmanLastDirection);


#endif // ENTITIES_H 