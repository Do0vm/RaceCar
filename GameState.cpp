#include "GameState.h"
#include "Constants.h"
#include <string> // For std::to_string
#include <iomanip> // For std::fixed and std::setprecision
#include <sstream> // For std::stringstream

// Define Global Variables
GameScreen currentGameState;
Tile* gameMap[MAP_COLS][MAP_ROWS];
Texture2D grassTexture;
Texture2D roadTexture;
Font gameFont;
double gameStartTime = 0.0;

Texture2D roadStraightTexture;
Texture2D roadCornerTexture;

// TileType Enum values for reference:
 //GRASS = 0
 //ROAD_STRAIGHT_VERTICAL = 1
 //ROAD_STRAIGHT_HORIZONTAL = 2
 //ROAD_CORNER_NW = 3 (Connects North to West)
 //ROAD_CORNER_NE = 4 (Connects North to East)
 //ROAD_CORNER_SW = 5 (Connects South to West)
 //ROAD_CORNER_SE = 6 (Connects South to East)


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

// GameState.cpp -> inside InitMap() function - CORRECTED

void InitMap() {
    CleanupMap();
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            TileType currentType = static_cast<TileType>(typeMap[row][col]);

            // FIX: Explicitly cast the calculated float positions back to int.
            // This acknowledges the conversion and removes the warning.
            int posX = static_cast<int>(col * TILE_WIDTH);
            int posY = static_cast<int>(row * TILE_HEIGHT);
            int sizeX = static_cast<int>(TILE_WIDTH);
            int sizeY = static_cast<int>(TILE_HEIGHT);

            gameMap[col][row] = new Tile(posX, posY, sizeX, sizeY, currentType);
        }
    }
}

void CleanupMap() {
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            delete gameMap[col][row];
            gameMap[col][row] = nullptr;
        }
    }
}

void DrawMap() {
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            if (gameMap[col][row] != nullptr) {
                // FIX: Pass all three required textures to the Draw function.
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
    // Future implementation
}

void DrawPlayingScreen() {
    ClearBackground(DARKGREEN);
    // DrawMap(); // You can replace the old DrawMap call with this new one
    map.Draw(grassTexture, roadStraightTexture, roadCornerTexture); // Correct call
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
    switch (currentGameState) {
    case START_SCREEN: UpdateStartScreen(); break;
    case PLAYING: UpdatePlayingScreen(); break;
    default: break;
    }

    BeginDrawing(); // You probably have Begin/End Drawing here already
    switch (currentGameState) {
    case START_SCREEN: DrawStartScreen(); break;
    case PLAYING: DrawPlayingScreen(); break; // This now correctly draws the map
    default: break;
    }
    EndDrawing(); // And here
}
