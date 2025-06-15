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
Car car = Car(Vector2{ 500, 600 });
MapManager g_mapManager; 

// Game-specific variables
double gameStartTime = 0.0;

// --- Function Prototypes for Internal Logic ---
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
    car.Load();

    
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
    car.Unload();
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

    // Calculate layout for map previews
    int numMaps = mapPreviews.size();
    float padding = 40.0f;
    float totalWidth = (numMaps * 128) + ((numMaps - 1) * padding);
    float startX = (SCREEN_WIDTH - totalWidth) / 2.0f;
    float startY = SCREEN_HEIGHT / 2.0f - 64.0f;

    for (int i = 0; i < numMaps; i++) {
        float currentX = startX + i * (128 + padding);
        DrawTextureEx(mapPreviews[i], { currentX, startY }, 0, 8.0f, WHITE); // Draw map preview scaled up
        DrawRectangleLines(currentX - 2, startY - 2, 128 + 4, 128 + 4, RAYWHITE); // Add a border

        std::string mapNumText = std::to_string(i + 1);
        int textWidth = MeasureText(mapNumText.c_str(), 40);
        DrawText(mapNumText.c_str(), currentX + 64 - (textWidth / 2.0f), startY + 140, 40, WHITE);
    }
}


void UpdatePlayingScreen() {
    
    car.Update(g_mapManager);

    
    Vector2 carPos = car.GetPosition();
    int carGridX = static_cast<int>(carPos.x / TILE_WIDTH);
    int carGridY = static_cast<int>(carPos.y / TILE_HEIGHT);

    
    for (int y = carGridY - 1; y <= carGridY + 1; ++y) {
        for (int x = carGridX - 1; x <= carGridX + 1; ++x) {
            Tile* tile = g_mapManager.GetTileAt(y, x);
            // If the tile is grass and the car is touching it, trigger the bounce effect.
            if (tile && tile->GetType() == TileType::GRASS && car.IsCollidingWithTile(*tile)) {
                car.Bounce();
            }
        }
    }
}


void DrawPlayingScreen() {
    ClearBackground(DARKGREEN);

    g_mapManager.Draw(grassTexture, roadTexture);
    car.Update(g_mapManager);
    car.Draw();
    Rectangle carBox = car.GetBoundingBox();
    DrawRectangleLinesEx(carBox, 2, RED);

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
