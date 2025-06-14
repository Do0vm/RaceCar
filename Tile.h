// Tile.h - CORRECTED

#pragma once

#include "raylib.h"


enum TileType {
    GRASS = 0,
    ROAD_STRAIGHT_VERTICAL = 1,
    ROAD_STRAIGHT_HORIZONTAL = 2,
    ROAD_CORNER_NW = 3,
    ROAD_CORNER_NE = 4,
    ROAD_CORNER_SW = 5,
    ROAD_CORNER_SE = 6
};

class Tile
{
public:
    // DECLARATION: Matches the definition in Tile.cpp (5 arguments)
    Tile(int posX, int posY, int sizeX, int sizeY, TileType type);
    ~Tile();

    void Load();
    // DECLARATION: Matches the definition in Tile.cpp (3 arguments)
    void Draw(Texture2D grassTexture, Texture2D roadStraightTexture, Texture2D roadCornerTexture);
    void Update();
    void Unload();
    void ChangeType(TileType type);

private:
    int mPosX;
    int mPosY;
    int mSizeX;
    int mSizeY;
    Color mColor;
    TileType mType;
};