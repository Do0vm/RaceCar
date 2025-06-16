#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"

// Screen Dimensions
constexpr int SCREEN_WIDTH = 750;
constexpr int SCREEN_HEIGHT = 750;

// Map Dimensions (number of tiles)
constexpr int MAP_COLS = 16;
constexpr int MAP_ROWS = 16;

// Calculated Tile Dimensions
constexpr float TILE_WIDTH = (float)SCREEN_WIDTH / MAP_COLS;
constexpr float TILE_HEIGHT = (float)SCREEN_HEIGHT / MAP_ROWS;

// Game Rules
const int WIN_SCORE = 5;

// Tile Types
enum TileType {
    GRASS,
    ROAD,
    CHECKPOINT
};

constexpr Color TILE_COLOR_ROAD = { 255, 0, 0, 255 }; 
constexpr Color TILE_COLOR_CHECKPOINT_DATA = { 0, 0, 255, 255 }; 
constexpr Color TILE_COLOR_CHECKPOINT_ACTIVE = { 0, 255, 0, 255 };

#endif 