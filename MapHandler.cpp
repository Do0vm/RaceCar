#include "MapHandler.h"
#include "Tile.h"
#include "Constants.h"
#include <iostream>

// Constructor: Initializes the map dimensions.
MapManager::MapManager() : mRows(MAP_ROWS), mCols(MAP_COLS)
{
    // Initialize the map grid with null pointers
    mMap.resize(mRows, std::vector<Tile*>(mCols, nullptr));
}

// Destructor: Ensures the map is unloaded properly to prevent memory leaks.
MapManager::~MapManager()
{
    Unload();
}

// Load: Reads a PNG image and builds the map based on its pixel colors.
void MapManager::Load(const std::string& mapImagePath)
{
    // Ensure any previous map is cleared before loading a new one.
    ClearMap();

    Image mapImage = LoadImage(mapImagePath.c_str());
    if (mapImage.data == nullptr)
    {
        std::cerr << "Error: Failed to load map image at " << mapImagePath << std::endl;
        return;
    }

    // Check if the image dimensions match the expected map dimensions.
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

            // Create a new tile
            mMap[row][col] = new Tile(position, size);

            // Get the color of the pixel at the current position
            Color pixelColor = colors[row * mapImage.width + col];

            // --- THIS IS THE CORE LOGIC ---
            // Set the tile type based on the pixel color.
            // Pure Red for Road, Pure Green for Grass.
            if (pixelColor.r == 255 && pixelColor.g == 0 && pixelColor.b == 0)
            {
                mMap[row][col]->SetType(TileType::ROAD);
            }
            else // Default to GRASS for any other color
            {
                mMap[row][col]->SetType(TileType::GRASS);
            }
            // You can add more rules here, e.g., for blue water tiles:
            // else if (pixelColor.b == 255 && pixelColor.r == 0 && pixelColor.g == 0) { ... }
        }
    }

    // Clean up the loaded image data from CPU memory.
    UnloadImageColors(colors);
    UnloadImage(mapImage);
}

// Unload: Calls ClearMap to free all resources.
void MapManager::Unload()
{
    ClearMap();
}

// Update: Calls the Update function for every tile on the map.
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

// Draw: Calls the Draw function for every tile, passing the necessary textures.
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

// GetTileAt: A safe way to get a tile from the map.
// Returns nullptr if the coordinates are out of bounds.
Tile* MapManager::GetTileAt(int row, int col) const
{
    if (row >= 0 && row < mRows && col >= 0 && col < mCols)
    {
        return mMap[row][col];
    }
    return nullptr;
}

// ClearMap: A private helper function to delete all tile objects and clear the vector.
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