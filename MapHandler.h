
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "raylib.h"
#include <vector>
#include <string>

// Forward declaration of the Tile class to avoid circular includes
class Tile;

class MapManager
{
public:
    MapManager();
    ~MapManager();

    // Loads a map from a specified PNG file.
    void Load(const std::string& mapImagePath);
    void Unload();

    void Update();

    // The Draw function now requires the textures to pass down to the tiles.
    void Draw(Texture2D grassTexture, Texture2D roadTexture);

    // A helper function to get a tile at a specific grid coordinate.
    Tile* GetTileAt(int row, int col) const;

private:
    // A 2D vector to hold pointers to all the Tile objects.
    std::vector<std::vector<Tile*>> mMap;

    // Keeps track of the map dimensions.
    int mRows;
    int mCols;

    // Clears the map and releases memory.
    void ClearMap();
};

#endif // MAP_MANAGER_H
