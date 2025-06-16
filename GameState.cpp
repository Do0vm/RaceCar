#include "GameState.h"
#include "Constants.h"
#include "MapHandler.h"
#include "Car.h"
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

// --- Global Objects and Variables ---

// Game State
GameScreen currentGameState;

// Textures & Fonts
Texture2D grassTexture;
Texture2D roadTexture;
Font gameFont;

// Map Selection
std::vector<Texture2D> mapPreviews;
std::vector<std::string> mapFilePaths;
int selectedMapIndex = -1;

// Game Objects
Car car1;
Car car2;
MapManager g_mapManager;

// Game-specific variables
double gameStartTime = 0.0;

//nternal Logic ---
void LoadGameResources();
void UnloadGameResources();
void UpdateStartScreen();
void DrawStartScreen();
void UpdatePlayingScreen();
void DrawPlayingScreen();
void DrawTimer();

// --- Core Game Functions ---

void InitGame() {
    currentGameState = START_SCREEN;
    LoadGameResources();
    car1 = Car(Vector2{ 500, 600 }, KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE);
    car2 = Car(Vector2{ 450, 600 }, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_RIGHT_SHIFT); 

    car1.Load();
    car2.Load();

    int i = 1;
    while (true) {
        std::string path = "resources/maps/map" + std::to_string(i) + ".png";
        if (FileExists(path.c_str())) {
            mapFilePaths.push_back(path);
            mapPreviews.push_back(LoadTexture(path.c_str()));
            i++;
        }
        else {
            break;
        }
    }
}

void UnloadGame() {
    UnloadGameResources();
    car1.Unload();
    car2.Unload();
    g_mapManager.Unload();

    for (const auto& texture : mapPreviews) {
        UnloadTexture(texture);
    }
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
    case END_SCREEN:
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
    case END_SCREEN:
        break;
    }
    EndDrawing();
}


// --- Internal State-Specific Functions ---

void LoadGameResources() {
    grassTexture = LoadTexture("resources/assets/tile_grass.png");
    roadTexture = LoadTexture("resources/assets/road_straight.png");
    gameFont = GetFontDefault();
}

void UnloadGameResources() {
    UnloadTexture(grassTexture);
    UnloadTexture(roadTexture);
}

void UpdateStartScreen() {
    for (int i = 0; i < mapPreviews.size(); ++i) {
        if (IsKeyPressed(KEY_ONE + i)) {
            selectedMapIndex = i;
            g_mapManager.Load(mapFilePaths[selectedMapIndex].c_str());
            currentGameState = PLAYING;
            gameStartTime = GetTime();
            break;
        }
    }
}

void DrawStartScreen() {
    ClearBackground(BLACK);
    const char* titleText = "Retro Racer Deluxe";
    const char* promptText = "Choose your track";
    int titleFontSize = 40;
    int promptFontSize = 20;

    int titleTextWidth = MeasureText(titleText, titleFontSize);
    DrawTextEx(gameFont, titleText, { (SCREEN_WIDTH - titleTextWidth) / 2.0f, 100 }, (float)titleFontSize, 2.0f, RAYWHITE);

    int promptTextWidth = MeasureText(promptText, promptFontSize);
    DrawTextEx(gameFont, promptText, { (SCREEN_WIDTH - promptTextWidth) / 2.0f, 160 }, (float)promptFontSize, 2.0f, LIGHTGRAY);

    int numMaps = mapPreviews.size();
    float padding = 40.0f;
    float totalWidth = (numMaps * 128) + ((numMaps - 1) * padding);
    float startX = (SCREEN_WIDTH - totalWidth) / 2.0f;
    float startY = SCREEN_HEIGHT / 2.0f - 64.0f;

    for (int i = 0; i < numMaps; i++) {
        float currentX = startX + i * (128 + padding);
        DrawTextureEx(mapPreviews[i], { currentX, startY }, 0, 8.0f, WHITE);
        DrawRectangleLines(currentX - 2, startY - 2, 128 + 4, 128 + 4, RAYWHITE);

        std::string mapNumText = std::to_string(i + 1);
        int textWidth = MeasureText(mapNumText.c_str(), 40);
        DrawText(mapNumText.c_str(), currentX + 64 - (textWidth / 2.0f), startY + 140, 40, WHITE);
    }
}

void UpdatePlayingScreen() {
    car1.Update(g_mapManager);
    car2.Update(g_mapManager);

    Vector2 car1Pos = car1.GetPosition();
    int car1GridX = static_cast<int>(car1Pos.x / TILE_WIDTH);
    int car1GridY = static_cast<int>(car1Pos.y / TILE_HEIGHT);

    for (int y = car1GridY - 1; y <= car1GridY + 1; ++y) {
        for (int x = car1GridX - 1; x <= car1GridX + 1; ++x) {
            Tile* tile = g_mapManager.GetTileAt(y, x);
            if (tile && tile->GetType() == TileType::GRASS && car1.IsCollidingWithTile(*tile)) {
                car1.Bounce();
            }
        }
    }

    Vector2 car2Pos = car2.GetPosition();
    int car2GridX = static_cast<int>(car2Pos.x / TILE_WIDTH);
    int car2GridY = static_cast<int>(car2Pos.y / TILE_HEIGHT);

    for (int y = car2GridY - 1; y <= car2GridY + 1; ++y) {
        for (int x = car2GridX - 1; x <= car2GridX + 1; ++x) {
            Tile* tile = g_mapManager.GetTileAt(y, x);
            if (tile && tile->GetType() == TileType::GRASS && car2.IsCollidingWithTile(*tile)) {
                car2.Bounce();
            }
        }
    }
}

void DrawPlayingScreen() {
    ClearBackground(DARKGREEN);

    g_mapManager.Draw(grassTexture, roadTexture);


    car1.Draw();
    car2.Draw();

    DrawTimer();
    DrawFPS(10, 40);
}

void DrawTimer() {
    double elapsedTime = GetTime() - gameStartTime;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << elapsedTime;
    std::string timeString = "Time: " + stream.str();

    DrawTextEx(gameFont, timeString.c_str(), { 10.0f, 10.0f }, 20.0f, 2.0f, WHITE);
}