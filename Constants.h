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


#endif // CONSTANTS_H