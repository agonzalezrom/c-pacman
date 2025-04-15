#ifndef INPUT_H
#define INPUT_H

#include "entities.h" // For Direction enum
#include <stdbool.h>

/**
 * @brief Processes any pending input events (keyboard, window close, etc.).
 *
 * Updates the game state based on input, e.g., sets requested Pacman direction
 * or flags the game to quit.
 * @param requestedDirection Pointer to a Direction variable to store the requested move.
 * @param shouldQuit Pointer to a bool variable to indicate if the game should quit.
 */
void processInput(Direction* requestedDirection, bool* shouldQuit);


#endif // INPUT_H 