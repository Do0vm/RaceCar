// MapHandler.h - CORRECTED

#pragma once

#include "raylib.h"
#include <vector>

// Forward declare Tile so the header knows it exists.
// This is often better than including the full Tile.h in another header.
class Tile;

class MapManager
{
public:
    MapManager();
    ~MapManager();

    void InitializeMap();
    void Load();
    void Start();
    void Update();

    // FIX: The declaration for Draw() must be updated to accept the three textures.
    // This now matches the definition in MapHandler.cpp.
    void Draw(Texture2D grassTexture, Texture2D roadStraightTexture, Texture2D roadCornerTexture);

    void Unload();
    void ResizeMap(int newRows, int newCols);
    Tile* GetTileAt(int row, int col) const;

private:
    std::vector<std::vector<Tile*>> mMap;
    int rows, cols;
    int tileSizeX, tileSizeY;
};