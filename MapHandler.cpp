// MapHandler.cpp - CORRECTED

#include "MapHandler.h"
#include "Tile.h" // You MUST include Tile.h to know about the Tile class and TileType enum
#include <iostream>

MapManager::MapManager()
// Defaulting to 15x15 to match your GameState example, change if needed
    : rows(15), cols(15), tileSizeX(50), tileSizeY(50)
{
    InitializeMap();
}

MapManager::~MapManager()
{
    Unload();
}

void MapManager::InitializeMap()
{
    // Make sure the map is clear before resizing
    Unload();
    mMap.resize(rows, std::vector<Tile*>(cols, nullptr));
}

// FIX 1: The Load function now creates a default GRASS tile.
// You will likely want to add logic here later to load from a file or array.
void MapManager::Load()
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!mMap[i][j]) {
                // We create a GRASS tile by default, providing the required 5th argument.
                mMap[i][j] = new Tile(j * tileSizeX, i * tileSizeY, tileSizeX, tileSizeY, GRASS);
            }
        }
    }
}

void MapManager::Start()
{
    std::cout << "MapManager Start\n";
}

void MapManager::Update()
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mMap[i][j]) mMap[i][j]->Update();
        }
    }
}

// FIX 2: The Draw function must accept the textures and pass them to each tile.
void MapManager::Draw(Texture2D grassTexture, Texture2D roadStraightTexture, Texture2D roadCornerTexture)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mMap[i][j]) {
                // Pass the textures along to the tile's Draw method
                mMap[i][j]->Draw(grassTexture, roadStraightTexture, roadCornerTexture);
            }
        }
    }
}

void MapManager::Unload()
{
    for (int i = 0; i < mMap.size(); ++i) { // Safer loop condition
        for (int j = 0; j < mMap[i].size(); ++j) {
            delete mMap[i][j];
            mMap[i][j] = nullptr;
        }
    }
    mMap.clear();
}

Tile* MapManager::GetTileAt(int row, int col) const
{
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return mMap[row][col];
    }
    return nullptr;
}

void MapManager::ResizeMap(int newRows, int newCols)
{
    rows = newRows;
    cols = newCols;
    InitializeMap(); // This already handles Unload and resize
    Load();
}