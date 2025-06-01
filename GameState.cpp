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
    //       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
    /* 0*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /* 1*/ {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, // Top section
    /* 2*/ {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, // Upper curve
    /* 3*/ {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, // Right side up
    /* 4*/ {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, // Right outer
    /* 5*/ {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, // Right straight
    /* 6*/ {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, // Right down
    /* 7*/ {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0}, // Start/finish line
    /* 8*/ {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0}, // Cross section
    /* 9*/ {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0}, // After cross
    /*10*/ {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, // Left side
    /*11*/ {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, // Left straight
    /*12*/ {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, // Left curve
    /*13*/ {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, // Bottom straight
    /*14*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void LoadGameResources() {
    // GameState.cpp - in LoadGameResources()

  // Make sure you have an 'assets' folder next to your executable,
  // containing 'tile_grass.png' and 'road_straight.png' (or similar names from Kenney pack)

    grassTexture = LoadTexture("assets/tile_grass.png");
    if (grassTexture.id == 0) {
        TraceLog(LOG_WARNING, "[!] FAILED to load texture: assets/tile_grass.png");
    }
    else {
        TraceLog(LOG_INFO, "[i] Loaded texture: assets/tile_grass.png (ID: %d)", grassTexture.id);
    }

    // For now, let's assume you have 'road_straight.png' for vertical roads
    // and 'road_corner.png' for a corner piece.
    roadStraightTexture = LoadTexture("assets/road_straight.png");
    if (roadStraightTexture.id == 0) {
        TraceLog(LOG_WARNING, "[!] FAILED to load texture: assets/road_straight.png");
    }
    else {
        TraceLog(LOG_INFO, "[i] Loaded texture: assets/road_straight.png (ID: %d)", roadStraightTexture.id);
    }

    roadCornerTexture = LoadTexture("assets/road_corner.png");
    if (roadCornerTexture.id == 0) {
        TraceLog(LOG_WARNING, "[!] FAILED to load texture: assets/road_corner.png");
    }
    else {
        TraceLog(LOG_INFO, "[i] Loaded texture: assets/road_corner.png (ID: %d)", roadCornerTexture.id);
    }

    gameFont = GetFontDefault();
}

void UnloadGameResources() {
    UnloadTexture(grassTexture);
    UnloadTexture(roadStraightTexture);
    UnloadTexture(roadCornerTexture);
    CleanupMap();
    
}

void InitGame() {
    currentGameState = START_SCREEN; // Set initial state
    // Map and car initialization will happen when transitioning from START_SCREEN to PLAYING
}

void InitMap() {
    CleanupMap(); // Clear previous map if any (e.g., for restarting game)
    for (int col = 0; col < MAP_COLS; col++) {
        for (int row = 0; row < MAP_ROWS; row++) {
            // typeMap is [row][col], gameMap is [col][row] to match user's map[x][y]
            TileType currentType = static_cast<TileType>(typeMap[row][col]);
            gameMap[col][row] = new Tile(col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, currentType);
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
                // Pass the specific road textures
                gameMap[col][row]->Draw(grassTexture, roadStraightTexture, roadCornerTexture);
            }
        }
    }
}

void UpdateStartScreen() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        currentGameState = PLAYING;
        InitMap(); // Initialize the map
        gameStartTime = GetTime(); // Start the timer
        // Initialize car here in the future
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

    // In DrawStartScreen()
    DrawTextEx(gameFont, titleText, { static_cast<float>(SCREEN_WIDTH - titleTextWidth) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f - 50.0f }, titleFontSize, 2.0f, RAYWHITE); // Also made 50 and 2 float literals
    DrawTextEx(gameFont, promptText, { static_cast<float>(SCREEN_WIDTH - promptTextWidth) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f + 10.0f }, promptFontSize, 2.0f, LIGHTGRAY); 
}

void UpdatePlayingScreen() {
    // Future: Update car movement, collision detection, etc.
}

void DrawPlayingScreen() {
    ClearBackground(DARKGREEN); // A base color if map doesn't cover everything
    DrawMap();
    DrawTimer();
    // Future: DrawCar();
}

void DrawTimer() {
    double elapsedTime = GetTime() - gameStartTime;

    // Using stringstream for formatting to two decimal places
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << elapsedTime;
    std::string timeString = "Time: " + stream.str();

    // In DrawTimer()
    DrawTextEx(gameFont, timeString.c_str(), { 10.0f, 10.0f }, 20.0f, 2.0f, WHITE);
}


void UpdateDrawFrame() {
    // Update based on current game state
    switch (currentGameState) {
    case START_SCREEN:
        UpdateStartScreen();
        break;
    case PLAYING:
        UpdatePlayingScreen();
        break;
        // case GAME_OVER: UpdateGameOverScreen(); break;
    default: break;
    }

    // Draw based on current game state
    BeginDrawing();
    switch (currentGameState) {
    case START_SCREEN:
        DrawStartScreen();
        break;
    case PLAYING:
        DrawPlayingScreen();
        break;
        // case GAME_OVER: DrawGameOverScreen(); break;
    default: break;
    }
    EndDrawing();
}