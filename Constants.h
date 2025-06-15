#ifndef CONSTANTS_H
#define CONSTANTS_H

// Screen Dimensions
constexpr int SCREEN_WIDTH = 750;
constexpr int SCREEN_HEIGHT = 750;

// Map Dimensions (number of tiles)
constexpr int MAP_COLS = 16;
constexpr int MAP_ROWS = 16;

// Calculated Tile Dimensions
constexpr float TILE_WIDTH = (float)SCREEN_WIDTH / MAP_COLS;
constexpr float TILE_HEIGHT = (float)SCREEN_HEIGHT / MAP_ROWS;

//// Car Physics Constants
//constexpr float MAX_VELOCITY = 900.0f;
//constexpr float MAX_REVERSE_VELOCITY = -150.0f;
//constexpr float ACCELERATION = 350.0f;
//constexpr float BRAKING_ACCELERATION = 500.0f;
//constexpr float FRICTION = 180.0f;
//
//constexpr float MAX_ANGULAR_VELOCITY = 2.0f;
//constexpr float ANGULAR_ACCELERATION = 1.3f;
//constexpr float STEERING_FRICTION = 7.0f;
//constexpr float STEERING_DRAG_FACTOR = 0.007f;



enum TileType {
    GRASS, 
    ROAD   
};

// Tile Colors
constexpr Color TILE_COLOR_EMPTY = GREEN;
constexpr Color TILE_COLOR_ROAD = GRAY;
constexpr Color TILE_COLOR_GRASS = RED;

#endif // CONSTANTS_H