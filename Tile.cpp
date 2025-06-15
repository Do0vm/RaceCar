#include "Tile.h"
#include "Constants.h" // Include for TILE_COLOR constants

Tile::Tile(Vector2 position, Vector2 size)
    : mPosition(position),
    mSize(size),
    mType(TileType::EMPTY),
    mColor(TILE_COLOR_EMPTY)
{
}



void Tile::Update()
{
}

void Tile::Draw(Texture2D grass, Texture2D road, Texture2D corner) const
{
    DrawRectangleV(mPosition, mSize, mColor);

}

void Tile::SetType(TileType newType)
{
    mType = newType;

    // A switch statement is cleaner and often more efficient for enums
    switch (mType)
    {
    case TileType::EMPTY:
        mColor = TILE_COLOR_EMPTY;
        break;
    case TileType::ROAD:
        mColor = TILE_COLOR_ROAD;
        break;

    }
}

TileType Tile::GetType() const
{
    return mType;
}

Vector2 Tile::GetPosition() const
{
    return mPosition;
}

Vector2 Tile::GetSize() const
{
    return mSize;
}

Rectangle Tile::GetRect() const
{
    return { mPosition.x, mPosition.y, mSize.x, mSize.y };
}