#include <stdio.h>
#include "config.h"
#include "graphics.h"
#include "game.h"
#include "map.h"

int main(int argc, char* argv[]) {

    printf("Starting Pacman Clone...\n");

    // Initialize graphics system
    if (!initializeGraphics("Pacman Clone", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        fprintf(stderr, "Failed to initialize graphics!\n");
        return 1;
    }

    // Initialize game data (score, pellets, entity positions)
    initializeGame();

    // Run the main game loop
    runGameLoop();

    // Cleanup
    shutdownGraphics();

    printf("Exiting Pacman Clone.\n");

    return 0;
} 