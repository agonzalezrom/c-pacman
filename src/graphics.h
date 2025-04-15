#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>

/**
 * @brief Initializes the graphics system (e.g., SDL window and renderer).
 *
 * @param title The title for the window.
 * @param width The width of the window.
 * @param height The height of the window.
 * @return true if initialization was successful, false otherwise.
 */
bool initializeGraphics(const char* title, int width, int height);

/**
 * @brief Cleans up and shuts down the graphics system.
 */
void shutdownGraphics();

/**
 * @brief Clears the entire screen to a default color (e.g., black).
 */
void clearScreen();

/**
 * @brief Updates the screen with all the drawing done since the last update.
 */
void presentScreen();

/**
 * @brief Sets the current drawing color.
 *
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
void setDrawColor(unsigned char r, unsigned char g, unsigned char b);

/**
 * @brief Draws a line between two points.
 *
 * @param x1 Starting X coordinate.
 * @param y1 Starting Y coordinate.
 * @param x2 Ending X coordinate.
 * @param y2 Ending Y coordinate.
 */
void drawLine(int x1, int y1, int x2, int y2);

/**
 * @brief Draws a filled rectangle.
 *
 * @param x Top-left X coordinate.
 * @param y Top-left Y coordinate.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
void fillRect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);

/**
 * @brief Draws a filled circle.
 *
 * @param centerX Center X coordinate.
 * @param centerY Center Y coordinate.
 * @param radius Radius of the circle.
 */
void fillCircle(int centerX, int centerY, int radius);

/**
 * @brief Draws text on the screen.
 *
 * NOTE: Text rendering is complex and will require SDL_ttf or similar.
 * This is a simplified placeholder.
 * @param text The text string to draw.
 * @param x Top-left X coordinate.
 * @param y Top-left Y coordinate.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
void drawText(const char* text, int x, int y, unsigned char r, unsigned char g, unsigned char b);


#endif // GRAPHICS_H 