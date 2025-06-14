#include "GameState.h"
#include "Constants.h"
#include "Tile.h"       // Make sure to include the Tile header

#include <string>
#include <iomanip>
#include <sstream>

// Define Global Variables
GameScreen currentGameState;
Tile* gameMap[MAP_COLS][MAP_ROWS];
Texture2D grassTexture;
Texture2D roadStraightTexture;
Texture2D roadCornerTexture;
Font gameFont;
double gameStartTime = 0.0;

// Tile layout definition
int typeMap[MAP_ROWS][MAP_COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void LoadGameResources() {
    grassTexture = LoadTexture("assets/tile_grass.png");
    roadStraightTexture = LoadTexture("assets/road_straight.png");
    roadCornerTexture = LoadTexture("assets/road_corner.png");
    gameFont = GetFontDefault();
}

void UnloadGameResources() {
    UnloadTexture(grassTexture);
    UnloadTexture(roadStraightTexture);
    UnloadTexture(roadCornerTexture);
    CleanupMap();
}

void InitGame() {
    currentGameState = START_SCREEN;
}

void InitMap() {
    CleanupMap(); // Clear any existing map data
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            TileType currentType = static_cast<TileType>(typeMap[row][col]);

            // --- FIX: Correctly create Tile objects ---
            // 1. Create Vector2 for position and size
            Vector2 position = { (float)col * TILE_WIDTH, (float)row * TILE_HEIGHT };
            Vector2 size = { (float)TILE_WIDTH, (float)TILE_HEIGHT };

            // 2. Construct the tile with the correct constructor
            gameMap[col][row] = new Tile(position, size);

            // 3. Set the tile's type using the separate method
            gameMap[col][row]->SetType(currentType);
        }
    }
}

void CleanupMap() {
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            if (gameMap[col][row] != nullptr) {
                delete gameMap[col][row];
                gameMap[col][row] = nullptr;
            }
        }
    }
}

void DrawMap() {
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            if (gameMap[col][row] != nullptr) {
                // --- FIX: This call now matches the intended logic ---
                // IMPORTANT: For this to compile, you MUST update your Tile class.
                // In Tile.h, change Draw() to:
                // 
                // Then, implement this new function in Tile.cpp.
                gameMap[col][row]->Draw(grassTexture, roadStraightTexture, roadCornerTexture);
            }
        }
    }
}

void UpdateStartScreen() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        currentGameState = PLAYING;
        InitMap();
        gameStartTime = GetTime();
    }
}

void DrawStartScreen() {
    ClearBackground(BLACK);
    const char* titleText = "Retro Racer Deluxe";
    const char* promptText = "Press ENTER to Start";
    int titleFontSize = 40;
    int promptFontSize = 20;

    int titleTextWidth = MeasureText(titleText, titleFontSize);
    int promptTextWidth = MeasureText(promptText, promptFontSize);

    DrawTextEx(gameFont, titleText, { (SCREEN_WIDTH - titleTextWidth) / 2.0f, SCREEN_HEIGHT / 2.0f - 50.0f }, static_cast<float>(titleFontSize), 2.0f, RAYWHITE);
    DrawTextEx(gameFont, promptText, { (SCREEN_WIDTH - promptTextWidth) / 2.0f, SCREEN_HEIGHT / 2.0f + 10.0f }, static_cast<float>(promptFontSize), 2.0f, LIGHTGRAY);
}

void UpdatePlayingScreen() {
    // Car update logic, etc., will go here
}

void DrawPlayingScreen() {
    ClearBackground(DARKGREEN);

    // --- FIX: Call the global DrawMap function to render the tiles ---
    DrawMap();

    // Other gameplay elements like the car would be drawn here

    DrawTimer();
}

void DrawTimer() {
    double elapsedTime = GetTime() - gameStartTime;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << elapsedTime;
    std::string timeString = "Time: " + stream.str();

    DrawTextEx(gameFont, timeString.c_str(), { 10.0f, 10.0f }, 20.0f, 2.0f, WHITE);
}

void UpdateDrawFrame() {
    // Update logic
    switch (currentGameState) {
    case START_SCREEN:
        UpdateStartScreen();
        break;
    case PLAYING:
        UpdatePlayingScreen();
        break;
    default:
        break;
    }

    // Drawing logic
    BeginDrawing();

    switch (currentGameState) {
    case START_SCREEN:
        DrawStartScreen();
        break;
    case PLAYING:
        DrawPlayingScreen();
        break;
    default:
        break;
    }

    EndDrawing();
}