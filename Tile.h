
#pragma once

#include "raylib.h"


enum TileType {
    GRASS = 0,
    ROAD_STRAIGHT_VERTICAL = 1,
    ROAD_STRAIGHT_HORIZONTAL = 2,
    ROAD_CORNER_NW = 3,
    ROAD_CORNER_NE = 4,
    ROAD_CORNER_SW = 5,
    ROAD_CORNER_SE = 6,
    EMPTY,
    ROAD,
    TURRET
};

class Tile
{
public:
 
    Tile(Vector2 position, Vector2 size);
    ~Tile() = default; // Default destructor is sufficient

    void Update();
    void Draw(Texture2D grass, Texture2D road, Texture2D corner) const;

    // Public modifier
    void SetType(TileType newType);

    // Getters, marked const for read-only access
    TileType GetType() const;
    Vector2 GetPosition() const;
    Vector2 GetSize() const;
    Rectangle GetRect() const;

private:
    Vector2 mPosition;
    Vector2 mSize;
    TileType mType;
    Color mColor;
};
