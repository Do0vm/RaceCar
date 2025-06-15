#include "Tile.h"
#include "Constants.h"

Tile::Tile(Vector2 position, Vector2 size)
    : mPosition(position), mSize(size), mType(TileType::GRASS)
{
}


Tile::~Tile()
{
}


void Tile::Update()
{
}

void Tile::Draw(Texture2D grassTexture, Texture2D roadTexture) const
{
    switch (mType)
    {
    case TileType::GRASS:
        DrawTextureEx(grassTexture, mPosition, 0.0f, TILE_WIDTH / grassTexture.width, WHITE);
        break;
    case TileType::ROAD:
        DrawTextureEx(roadTexture, mPosition, 0.0f, TILE_WIDTH / roadTexture.width, WHITE);
        break;
    default:
        DrawRectangleV(mPosition, mSize, PURPLE);
        break;
    }
}

void Tile::SetType(TileType type)
{
    mType = type;
}

TileType Tile::GetType() const
{
    return mType;
}

Rectangle Tile::GetRect() const
{
    return { mPosition.x, mPosition.y, mSize.x, mSize.y };
}
