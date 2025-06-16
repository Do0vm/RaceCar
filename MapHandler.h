#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "raylib.h"
#include <vector>
#include <string>

class Tile;

class MapManager
{
public:
    MapManager();
    ~MapManager();

    void Load(const std::string& mapImagePath);
    void Unload();
    void Update();
    void Draw(Texture2D grassTexture, Texture2D roadTexture);

    Tile* GetTileAtPixel(Vector2 pixelPosition) const;
    Tile* GetTileAt(int row, int col) const;

    // Checkpoint management
    int GetCheckpointCount() const;
    Tile* GetCheckpoint(int index) const;
    void ActivateNextCheckpoint(int& currentIndex);

private:
    void ClearMap();

    int mRows;
    int mCols;
    std::vector<std::vector<Tile*>> mMap;
    std::vector<Tile*> mCheckpoints;
};

#endif