#include "map.h"
#include "graphics.h" // For drawing functions (to be implemented with SDL)
#include "config.h"

// 0: Wall, 1: Path
const int mapLayout[MAP_ROWS][MAP_COLS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
    {0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0},
    {0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
    {0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0},
    {0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
    {0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0},
    {0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0},
    {0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0},
    {0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0},
    {0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0},
    {0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0},
    {0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
    {0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1,0,0,1,0},
    {0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

// 1: Movable, 0: Not movable (wall or boundary)
// Note: This grid seems offset or derived from mapLayout. Let's keep it for now.
// Dimensions adjusted to MAP_ROWS-2, MAP_COLS-2 as per original code's usage.
const int movementGrid[MAP_ROWS - 2][MAP_COLS - 2] = {
    {1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1},
    {1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1},
    {1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1},
    {1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1},
    {1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1},
    {1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1},
    {1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,1,0,1,0,0,1,1,0,0,1,0,1,0,0,1},
    {1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1},
};

/**
 * @brief Draws the game map.
 *
 * Renders the walls based on the mapLayout using placeholder graphics functions.
 */
void drawMap() {
    // Set color for walls (placeholder)
    setDrawColor(0, 51, 255); // Blue walls

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (mapLayout[i][j] == 1) { // If it's a path
                // Check adjacent cells to draw walls only on the border
                // Placeholder line drawing function calls
                if (j > 0 && mapLayout[i][j - 1] == 0) {
                    drawLine(j * TILE_SIZE, i * TILE_SIZE, j * TILE_SIZE, (i + 1) * TILE_SIZE);
                }
                if (j < MAP_COLS - 1 && mapLayout[i][j + 1] == 0) {
                    drawLine((j + 1) * TILE_SIZE, i * TILE_SIZE, (j + 1) * TILE_SIZE, (i + 1) * TILE_SIZE);
                }
                if (i > 0 && mapLayout[i - 1][j] == 0) {
                    drawLine(j * TILE_SIZE, i * TILE_SIZE, (j + 1) * TILE_SIZE, i * TILE_SIZE);
                }
                if (i < MAP_ROWS - 1 && mapLayout[i + 1][j] == 0) {
                    drawLine(j * TILE_SIZE, (i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE, (i + 1) * TILE_SIZE);
                }
            }
        }
    }
} 