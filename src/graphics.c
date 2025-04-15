#include "graphics.h"
#include <SDL.h> // Main SDL header (Corrected include path)
#include <stdio.h> 

// SDL globals (file scope)
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

/**
 * @brief Initializes the graphics system using SDL.
 *
 * Creates an SDL window and renderer.
 * @param title The title for the window.
 * @param width The width of the window.
 * @param height The height of the window.
 * @return true if initialization was successful, false otherwise.
 */
bool initializeGraphics(const char* title, int width, int height) {
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    printf("SDL Graphics Initialized Successfully.\n");
    return true;
}

/**
 * @brief Cleans up and shuts down the SDL graphics system.
 */
void shutdownGraphics() {
    printf("Shutting down SDL graphics...\n");
    // Destroy renderer and window
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    // Quit SDL subsystems
    SDL_Quit();
}

/**
 * @brief Clears the entire screen to black using SDL.
 */
void clearScreen() {
    if (!renderer) return;
    // Set draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // R, G, B, Alpha
    // Clear the entire rendering target with the drawing color
    SDL_RenderClear(renderer);
}

/**
 * @brief Updates the screen with all the drawing done since the last update.
 */
void presentScreen() {
     if (!renderer) return;
    // Update the screen with rendering performed.
    SDL_RenderPresent(renderer);
}

/**
 * @brief Sets the current drawing color for the SDL renderer.
 *
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
void setDrawColor(unsigned char r, unsigned char g, unsigned char b) {
    if (!renderer) return;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); // Use full opacity (255)
}

/**
 * @brief Draws a line between two points using SDL.
 *
 * @param x1 Starting X coordinate.
 * @param y1 Starting Y coordinate.
 * @param x2 Ending X coordinate.
 * @param y2 Ending Y coordinate.
 */
void drawLine(int x1, int y1, int x2, int y2) {
    if (!renderer) return;
    // Note: Assumes color is already set via setDrawColor
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

/**
 * @brief Draws a filled rectangle using SDL.
 *
 * @param x Top-left X coordinate.
 * @param y Top-left Y coordinate.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
void fillRect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b) {
    if (!renderer) return;
    SDL_Rect fillRect = { x, y, w, h };
    // Set the color for this rectangle
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    // Render the rectangle
    SDL_RenderFillRect(renderer, &fillRect);
}

/**
 * @brief Draws a filled circle (Placeholder).
 *
 * NOTE: SDL does not have a built-in function for circles.
 * Requires custom drawing algorithm (like Midpoint) or SDL_gfx library.
 * This placeholder draws a small square.
 * @param centerX Center X coordinate.
 * @param centerY Center Y coordinate.
 * @param radius Radius of the circle.
 */
void fillCircle(int centerX, int centerY, int radius) {
    if (!renderer) return;
    // Placeholder: Draw a square using fillRect
    // A real implementation would calculate points on the circumference and fill.
    int diameter = radius * 2;
    fillRect(centerX - radius, centerY - radius, diameter, diameter, 255, 255, 0); // Yellow square
    // For pellets, maybe just a small rectangle is fine?
    // fillRect(centerX - 1, centerY - 1, 3, 3, 211, 211, 40); // Tiny yellow square for pellet
}

/**
 * @brief Draws text on the screen (Placeholder).
 *
 * NOTE: Requires SDL_ttf library for proper text rendering.
 * @param text The text string to draw.
 * @param x Top-left X coordinate.
 * @param y Top-left Y coordinate.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
void drawText(const char* text, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    // This requires SDL_ttf: Load font, RenderText_Solid, CreateTextureFromSurface, RenderCopy, Destroy resources
    // For now, just print to console as a placeholder.
    printf("SDL Graphics Placeholder: Draw text '%s' at (%d,%d) color (%d,%d,%d)\n", text, x, y, r, g, b);
    // Example of how it *might* look with SDL_ttf (pseudo-code):
    /*
    if (!font) return; // Need to load TTF_Font*
    SDL_Color color = { r, g, b, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    */
} 