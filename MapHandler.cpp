#include "MapHandler.h"
#include "Tile.h"
#include "Constants.h"
#include <iostream>

MapManager::MapManager() : mRows(MAP_ROWS), mCols(MAP_COLS)
{
    mMap.resize(mRows, std::vector<Tile*>(mCols, nullptr));
}

MapManager::~MapManager()
{
    Unload();
}

void MapManager::Load(const std::string& mapImagePath)
{
    ClearMap();

    Image mapImage = LoadImage(mapImagePath.c_str());
    if (mapImage.data == nullptr)
    {
        std::cerr << "Error: Failed to load map image at " << mapImagePath << std::endl;
        return;
    }

    if (mapImage.width != mCols || mapImage.height != mRows)
    {
        std::cerr << "Warning: Map image dimensions (" << mapImage.width << "x" << mapImage.height
            << ") do not match MAP_COLS/MAP_ROWS (" << mCols << "x" << mRows << ")." << std::endl;
    }

    Color* colors = LoadImageColors(mapImage);

    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
            Vector2 position = { col * TILE_WIDTH, row * TILE_HEIGHT };
            Vector2 size = { TILE_WIDTH, TILE_HEIGHT };

            mMap[row][col] = new Tile(position, size);

            Color pixelColor = colors[row * mapImage.width + col];

            
            if (pixelColor.r == 255 && pixelColor.g == 0 && pixelColor.b == 0)
            {
                mMap[row][col]->SetType(TileType::ROAD);
            }
            else 
            {
                mMap[row][col]->SetType(TileType::GRASS);
            }
            
        }
    }

    
    UnloadImageColors(colors);
    UnloadImage(mapImage);
}


void MapManager::Unload()
{
    ClearMap();
}

void MapManager::Update()
{
    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
            if (mMap[row][col])
            {
                mMap[row][col]->Update();
            }
        }
    }
}

void MapManager::Draw(Texture2D grassTexture, Texture2D roadTexture)
{
    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
            if (mMap[row][col])
            {
                mMap[row][col]->Draw(grassTexture, roadTexture);
            }
        }
    }
}


Tile* MapManager::GetTileAtPixel(Vector2 pixelPosition) const
{
    if (pixelPosition.x < 0 || pixelPosition.y < 0 ||
        pixelPosition.x >= mCols * TILE_WIDTH ||
        pixelPosition.y >= mRows * TILE_HEIGHT)
    {
        return nullptr;
    }

    int col = static_cast<int>(pixelPosition.x / TILE_WIDTH);
    int row = static_cast<int>(pixelPosition.y / TILE_HEIGHT);

    return GetTileAt(row, col);
}


Tile* MapManager::GetTileAt(int row, int col) const
{
    if (row >= 0 && row < mRows && col >= 0 && col < mCols)
    {
        return mMap[row][col];
    }
    return nullptr;
}

void MapManager::ClearMap()
{
    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
            if (mMap[row][col])
            {
                delete mMap[row][col];
                mMap[row][col] = nullptr;
            }
        }
    }
}