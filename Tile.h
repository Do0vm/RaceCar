
#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "Constants.h"

class Tile
{
public:
    // Constructor uses Vector2 for modern C++ game dev
    Tile(Vector2 position, Vector2 size);
    ~Tile(); // Destructor

    void Update();

    // The Draw function now takes the textures it needs to render itself
    void Draw(Texture2D grassTexture, Texture2D roadTexture) const;

    // Sets the tile's type (e.g., GRASS, ROAD)
    void SetType(TileType type);
    TileType GetType() const;

    // Gets the tile's bounding box for collisions
    Rectangle GetRect() const;

private:
    Vector2 mPosition;
    Vector2 mSize;
    TileType mType;
};

#endif // TILE_H
