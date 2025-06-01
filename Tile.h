#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "Constants.h" // For TileType and tile dimensions

class Tile {
public:
    Rectangle destRect; // Destination rectangle for drawing on screen
    TileType type;
    float speedFactor;  // For car interaction later

    Tile(float x, float y, float width, float height, TileType type);
    void Draw(Texture2D grassTex, Texture2D straightRoadTex, Texture2D cornerRoadTex);
};

#endif // TILE_H