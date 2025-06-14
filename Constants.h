#ifndef CONSTANTS_H
#define CONSTANTS_H

// Screen Dimensions
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 600;

// Map Dimensions (number of tiles)
constexpr int MAP_COLS = 15;
constexpr int MAP_ROWS = 15;

// Calculated Tile Dimensions
constexpr float TILE_WIDTH = (float)SCREEN_WIDTH / MAP_COLS;
constexpr float TILE_HEIGHT = (float)SCREEN_HEIGHT / MAP_ROWS;

// Car Physics Constants
constexpr float MAX_VELOCITY = 400.0f;
constexpr float MAX_REVERSE_VELOCITY = -150.0f;
constexpr float ACCELERATION = 350.0f;
constexpr float BRAKING_ACCELERATION = 500.0f;
constexpr float FRICTION = 180.0f;

constexpr float MAX_ANGULAR_VELOCITY = 2.0f;
constexpr float ANGULAR_ACCELERATION = 2.5f;
constexpr float STEERING_FRICTION = 5.0f;
constexpr float STEERING_DRAG_FACTOR = 0.004f;

constexpr float COLLISION_BOUNCE_FACTOR = -0.8f;
constexpr float COLLISION_RADIUS = 15.0f;

// Tile Colors
constexpr Color TILE_COLOR_EMPTY = GREEN;
constexpr Color TILE_COLOR_ROAD = GRAY;
constexpr Color TILE_COLOR_TURRET = RED;

#endif // CONSTANTS_H