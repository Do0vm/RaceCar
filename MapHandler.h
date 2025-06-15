#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "raylib.h"
#include <vector>
#include <string>
#include "Tile.h" 
class MapManager
{
public:
    MapManager();
    ~MapManager();

    void Load(const std::string& mapImagePath);
    void Unload();
    void Update();
    void Draw(Texture2D grassTexture, Texture2D roadTexture);

    Tile* GetTileAt(int row, int col) const;

    Tile* GetTileAtPixel(Vector2 pixelPosition) const;

private:
    void ClearMap();
    std::vector<std::vector<Tile*>> mMap;
    int mRows;
    int mCols;
};

#endif // MAPMANAGER_H
