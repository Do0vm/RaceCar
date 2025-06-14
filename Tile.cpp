#include "Tile.h"

// Updated constructor to include TileType parameter
Tile::Tile(int posX, int posY, int sizeX, int sizeY, TileType type)
    : mPosX(posX), mPosY(posY), mSizeX(sizeX), mSizeY(sizeY), mType(type)
{
    // Set color based on tile type (optional, can be removed if not used)
    switch (mType) {
    case GRASS: mColor = GREEN; break;
    case ROAD_STRAIGHT_VERTICAL:
    case ROAD_STRAIGHT_HORIZONTAL:
    case ROAD_CORNER_NW:
    case ROAD_CORNER_NE:
    case ROAD_CORNER_SW:
    case ROAD_CORNER_SE:
        mColor = GRAY; break;
    default:
        mColor = GREEN; break;
    }
}

Tile::~Tile()
{
}

void Tile::Load()
{
}

void Tile::Draw(Texture2D grassTexture, Texture2D roadStraightTexture, Texture2D roadCornerTexture)
{
    // Draw appropriate texture based on tile type
    Rectangle destRect = { static_cast<float>(mPosX), static_cast<float>(mPosY),
                          static_cast<float>(mSizeX), static_cast<float>(mSizeY) };
    Rectangle sourceRect = { 0, 0, (float)grassTexture.width, (float)grassTexture.height };

    switch (mType) {
    case GRASS:
        DrawTexturePro(grassTexture, sourceRect, destRect, { 0,0 }, 0.0f, WHITE);
        break;

    case ROAD_STRAIGHT_VERTICAL:
    case ROAD_STRAIGHT_HORIZONTAL:
        DrawTexturePro(roadStraightTexture, sourceRect, destRect, { 0,0 }, 0.0f, WHITE);
        break;

    case ROAD_CORNER_NW:
    case ROAD_CORNER_NE:
    case ROAD_CORNER_SW:
    case ROAD_CORNER_SE:
        DrawTexturePro(roadCornerTexture, sourceRect, destRect, { 0,0 }, 0.0f, WHITE);
        break;

    default:
        // Fallback to just drawing a colored rectangle
        DrawRectangle(mPosX, mPosY, mSizeX, mSizeY, mColor);
        break;
    }
}

void Tile::Update()
{
}

void Tile::Unload()
{
}

void Tile::ChangeType(TileType type)
{
    mType = type;
    // Update color or any other property if needed
    switch (mType) {
    case GRASS:
        mColor = GREEN;
        break;
    case ROAD_STRAIGHT_VERTICAL:
    case ROAD_STRAIGHT_HORIZONTAL:
    case ROAD_CORNER_NW:
    case ROAD_CORNER_NE:
    case ROAD_CORNER_SW:
    case ROAD_CORNER_SE:
        mColor = GRAY;
        break;
    default:
        mColor = GREEN;
        break;
    }
}
