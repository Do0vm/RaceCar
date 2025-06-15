#include "raylib.h"
#include "Constants.h"
#include "GameState.h"
#include "MapHandler.h"
#include "Car.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameState.h"
#include "raylib.h"
// Global objects
MapManager g_mapManager;

// Global textures
Texture2D g_grassTexture;
Texture2D g_roadTexture;

void LoadGame()
{
    // Load all your game textures
    g_grassTexture = LoadTexture("resources/assets/tile_grass.png");
    g_roadTexture = LoadTexture("resources/assets/road_straight.png");

    if (g_grassTexture.id == 0 || g_roadTexture.id == 0) {
        // Handle error, maybe draw a placeholder or exit
    }

    // Load the map from a PNG file. Create a 16x16 pixel PNG
    // where you draw with pure red (255,0,0) for roads and pure green (0,255,0) for grass.
    g_mapManager.Load("resources/maps/map1.png");

    // g_car.Load();
}

void UnloadGame()
{
    // Unload all textures
    UnloadTexture(g_grassTexture);
    UnloadTexture(g_roadTexture);

    // The map manager's destructor will handle unloading the map,
    // but calling it explicitly is also fine.
    g_mapManager.Unload();

    // g_car.Unload();
}

void UpdateGame()
{
    g_mapManager.Update();
    // g_car.Update();
    // Add other game logic here
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(DARKGREEN);

    g_mapManager.Draw(g_grassTexture, g_roadTexture);


    DrawFPS(10, 10);
    EndDrawing();
}

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Racer - Refactored");
    SetTargetFPS(60);

    LoadGame();

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();
    }

    // De-Initialization
    UnloadGame();
    CloseWindow();

    return 0;
}