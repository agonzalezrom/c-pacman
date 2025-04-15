#ifndef MAP_H
#define MAP_H

#include "config.h"

// Represents the layout of the map (walls, paths)
extern const int mapLayout[MAP_ROWS][MAP_COLS];

// Represents valid movement tiles
extern const int movementGrid[MAP_ROWS - 2][MAP_COLS - 2]; // Assuming movement grid is inner part

/**
 * @brief Draws the game map.
 *
 * Renders the walls based on the mapLayout.
 */
void drawMap();

#endif // MAP_H 