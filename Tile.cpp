#include "Tile.h"
#include "Constants.h"
// Constructor: Initializes a tile with its position and size.
// It defaults to being a GRASS tile.
Tile::Tile(Vector2 position, Vector2 size)
    : mPosition(position), mSize(size), mType(TileType::GRASS)
{
}

// Destructor: This is where you would clean up any resources the tile owns.
// In this case, it's empty because the tile doesn't allocate any memory itself.
Tile::~Tile()
{
}

// Update: Called once per frame. For now, it's empty, but you could
// add animations or other logic here.
void Tile::Update()
{
    // E.g., Animate water tiles, etc.
}

// Draw: Renders the correct texture based on the tile's type.
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
        // Draw a placeholder color if a texture is missing or type is unknown
        DrawRectangleV(mPosition, mSize, PURPLE);
        break;
    }
}

// SetType: Changes the type of the tile.
void Tile::SetType(TileType type)
{
    mType = type;
}

// GetType: Returns the current type of the tile.
TileType Tile::GetType() const
{
    return mType;
}

// GetRect: Returns the rectangular bounds of the tile, useful for collision detection.
Rectangle Tile::GetRect() const
{
    return { mPosition.x, mPosition.y, mSize.x, mSize.y };
}
