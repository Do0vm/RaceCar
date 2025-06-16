#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "Constants.h"

class Tile
{
public:
    Tile(Vector2 position, Vector2 size);
    ~Tile();

    void Update();
    void Draw(Texture2D grassTexture, Texture2D roadTexture) const;

    void SetType(TileType type);
    TileType GetType() const;
    Rectangle GetRect() const;

    void SetActive(bool active);
    bool IsActive() const;

private:
    Vector2 mPosition;
    Vector2 mSize;
    TileType mType;
    bool mIsActive;
};

#endif 