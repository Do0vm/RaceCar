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
                // Use the existing Tile(Vector2 position, Vector2 size) ctor:
                Vector2 pos = { j * static_cast<float>(tileSizeX), i * static_cast<float>(tileSizeY) };
                Vector2 sz = { static_cast<float>(tileSizeX), static_cast<float>(tileSizeY) };
                Tile* tile = new Tile(pos, sz);
                // Set type to GRASS (so color, etc., get set)
                tile->SetType(TileType::EMPTY); // if you want EMPTY by default; or skip
                tile->SetType(TileType::ROAD);  // example: if default should be ROAD
                // But per original intent: default GRASS. 
                // Assuming you have a TileType::GRASS or similar:
                tile->SetType(TileType::GRASS);
                mMap[i][j] = tile;
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
            if (mMap[i][j]) {
                // Call Update only if Tile has it; we will add an empty stub in Tile.
                mMap[i][j]->Update();
            }
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