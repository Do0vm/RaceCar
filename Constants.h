#ifndef CONSTANTS_H
#define CONSTANTS_H

// Screen Dimensions
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

// Map Dimensions (number of tiles)
const int MAP_COLS = 15; // Number of columns (X-axis)
const int MAP_ROWS = 15; // Number of rows (Y-axis)

// Calculated Tile Dimensions
const float TILE_WIDTH =  (float)SCREEN_WIDTH / MAP_COLS;
const float TILE_HEIGHT = (float)SCREEN_HEIGHT / MAP_ROWS;

// Tile Types Enum
enum TileType {
    GRASS = 0,
    ROAD_STRAIGHT_VERTICAL,     // Tile where road goes from Top to Bottom
    ROAD_STRAIGHT_HORIZONTAL,   // Tile where road goes from Left to Right
    ROAD_CORNER_NW,             // Corner connecting North (top) and West (left) road segments
    ROAD_CORNER_NE,             // Corner connecting North (top) and East (right)
    ROAD_CORNER_SW,             // Corner connecting South (bottom) and West (left)
    ROAD_CORNER_SE              // Corner connecting South (bottom) and East (right)
};

#endif // CONSTANTS_H