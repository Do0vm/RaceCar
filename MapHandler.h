
#pragma once

#include "raylib.h"
#include <vector>


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

 
    void Draw(Texture2D grassTexture, Texture2D roadStraightTexture, Texture2D roadCornerTexture);

    void Unload();
    void ResizeMap(int newRows, int newCols);
    Tile* GetTileAt(int row, int col) const;

private:
    std::vector<std::vector<Tile*>> mMap;
    int rows, cols;
    int tileSizeX, tileSizeY;
};