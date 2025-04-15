# Basic Makefile for C Pacman Clone

# Compiler
CC = gcc

# Executable name
TARGET = pacman_clone

# Source directory
SRC_DIR = src

# Build directory
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Find all .c files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Generate object file names in the build directory
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Get SDL2 flags using sdl2-config
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)

# Compiler flags
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -g: Add debugging information
# -std=c11: Use C11 standard
# -Isrc: Add src directory to include paths
CFLAGS = -Wall -Wextra -g -std=c11 -I$(SRC_DIR) $(SDL_CFLAGS)

# Linker flags
# -lm: Link math library
# NOTE: You need SDL2 development libraries installed!
# (e.g., on Debian/Ubuntu: sudo apt install libsdl2-dev)
# (e.g., on macOS with Homebrew: brew install sdl2)
LDFLAGS = -lm
# SDL flags are now in SDL_LDFLAGS from sdl2-config
# SDL_LDFLAGS += -lSDL2_ttf # Add this if/when implementing text rendering

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Rule to link the executable
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $@ $(CFLAGS) $(LDFLAGS) $(SDL_LDFLAGS)
	@echo "Linking complete: $@"

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $< -> $@"

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Created directory: $@"

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory."

# Phony targets
.PHONY: all clean 