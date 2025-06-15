#include "GameState.h"
#include "Constants.h"
#include "MapHandler.h" // You need to include this to use the map object
#include "Car.h"
#include <string>
#include <iomanip>
#include <sstream>

// --- Global Objects and Variables ---

GameScreen currentGameState;

Texture2D grassTexture;
Texture2D roadStraightTexture;
Texture2D roadCornerTexture; 
Font gameFont;

// Global Game Objects
Car car = Car(Vector2{ 500, 600 });
extern MapManager g_mapManager;

// Game-specific variables
double gameStartTime = 0.0;


// --- Functions ---

void LoadGameResources() {
    grassTexture = LoadTexture("resources/assets/tile_grass.png");
    roadStraightTexture = LoadTexture("resources/assets/road_straight.png");
     roadCornerTexture = LoadTexture("resources/assets/road_corner.png");
    gameFont = GetFontDefault();
}

void UnloadGameResources() {
    UnloadTexture(grassTexture);
    UnloadTexture(roadStraightTexture);
     UnloadTexture(roadCornerTexture);
}


void InitGame() {
    currentGameState = START_SCREEN;
    car.Load();
    
    g_mapManager.Load("resources/maps/map1.png"); 
}

void UpdateStartScreen() {
    
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        currentGameState = PLAYING;
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

    DrawTextEx(gameFont, titleText, { (SCREEN_WIDTH - titleTextWidth) / 2.0f, SCREEN_HEIGHT / 2.0f - 50.0f }, (float)titleFontSize, 2.0f, RAYWHITE);
    DrawTextEx(gameFont, promptText, { (SCREEN_WIDTH - promptTextWidth) / 2.0f, SCREEN_HEIGHT / 2.0f + 10.0f }, (float)promptFontSize, 2.0f, LIGHTGRAY);
}

void UpdatePlayingScreen() {
    g_mapManager.Update(); 
    car.Update();
}

void DrawPlayingScreen() {
    ClearBackground(DARKGREEN);

    
    g_mapManager.Draw(grassTexture, roadStraightTexture); 

    car.Draw();

    
    Rectangle carBox = car.GetBoundingBox();
    DrawRectangleLinesEx(carBox, 2, RED);

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
    // --- Update Logic ---
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

    // --- Drawing Logic ---
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
