#include "GameState.h"
#include "Constants.h"
#include "MapHandler.h"
#include "Car.h"
#include "Tile.h"
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

// --- Global Objects and Variables ---
GameScreen currentGameState;
Texture2D grassTexture;
Texture2D roadTexture;
Font gameFont;
std::vector<Texture2D> mapPreviews;
std::vector<std::string> mapFilePaths;
int selectedMapIndex = -1;
Car car1;
Car car2;
Car* winner = nullptr;
MapManager g_mapManager;
int activeCheckpointIndex = 0;
double gameStartTime = 0.0;

// --- Internal Logic ---
void LoadGameResources();
void UnloadGameResources();
void UpdateStartScreen();
void DrawStartScreen();
void UpdatePlayingScreen();
void DrawPlayingScreen();
void UpdateEndScreen();
void DrawEndScreen();
void DrawHUD();

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
    BeginDrawing();
    ClearBackground(BLACK);

    switch (currentGameState) {
    case START_SCREEN:
        UpdateStartScreen();
        DrawStartScreen();
        break;
    case PLAYING:
        UpdatePlayingScreen();
        DrawPlayingScreen();
        break;
    case END_SCREEN:
        UpdateEndScreen();
        DrawEndScreen();
        break;
    }
    EndDrawing();
}

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
    for (size_t i = 0; i < mapPreviews.size(); ++i) {
        if (IsKeyPressed(KEY_ONE + i)) {
            selectedMapIndex = i;
            g_mapManager.Load(mapFilePaths[selectedMapIndex].c_str());

            car1.Reset({ 500, 600 }); 
            car2.Reset({ 450, 600 });
            winner = nullptr;
            activeCheckpointIndex = 0;

            currentGameState = PLAYING;
            gameStartTime = GetTime();
            break;
        }
    }
}

void DrawStartScreen() {
    const char* titleText = "RAYLIB RETRO RACER";
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

    // --- Wall Collision Logic ---
    auto handleWallCollision = [](Car& car) {
        Vector2 carPos = car.GetPosition();
        int carGridX = static_cast<int>(carPos.x / TILE_WIDTH);
        int carGridY = static_cast<int>(carPos.y / TILE_HEIGHT);

        for (int y = carGridY - 1; y <= carGridY + 1; ++y) {
            for (int x = carGridX - 1; x <= carGridX + 1; ++x) {
                Tile* tile = g_mapManager.GetTileAt(y, x);
                if (tile && tile->GetType() == TileType::GRASS && car.IsCollidingWithTile(*tile)) {
                    car.Bounce();
                }
            }
        }
        };
    handleWallCollision(car1);
    handleWallCollision(car2);

    // --- Checkpoint Logic ---
    Tile* activeCheckpoint = g_mapManager.GetCheckpoint(activeCheckpointIndex);
    if (activeCheckpoint && activeCheckpoint->IsActive()) {
        if (car1.IsCollidingWithTile(*activeCheckpoint)) {
            car1.AddPoint();
            g_mapManager.ActivateNextCheckpoint(activeCheckpointIndex);
            if (car1.GetScore() >= WIN_SCORE) {
                winner = &car1;
                currentGameState = END_SCREEN;
            }
        }
        else if (car2.IsCollidingWithTile(*activeCheckpoint)) {
            car2.AddPoint();
            g_mapManager.ActivateNextCheckpoint(activeCheckpointIndex);
            if (car2.GetScore() >= WIN_SCORE) {
                winner = &car2;
                currentGameState = END_SCREEN;
            }
        }
    }
}

void DrawPlayingScreen() {
    ClearBackground(DARKGREEN);
    g_mapManager.Draw(grassTexture, roadTexture);
    car1.Draw();
    car2.Draw();
    DrawHUD();
}

void UpdateEndScreen() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        currentGameState = START_SCREEN;
    }
}

void DrawEndScreen() {
    // Draw the final game state in the background
    DrawPlayingScreen();

    // Overlay with a semi-transparent black
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 0, 0, 0, 150 });

    std::string winText = "GAME OVER";
    if (winner == &car1) {
        winText = "PLAYER 1 WINS!";
    }
    else if (winner == &car2) {
        winText = "PLAYER 2 WINS!";
    }

    int titleFontSize = 60;
    int promptFontSize = 20;

    int titleTextWidth = MeasureText(winText.c_str(), titleFontSize);
    DrawText(winText.c_str(), (SCREEN_WIDTH - titleTextWidth) / 2, SCREEN_HEIGHT / 2 - 40, titleFontSize, GOLD);

    const char* promptText = "Press ENTER to return to the Main Menu";
    int promptTextWidth = MeasureText(promptText, promptFontSize);
    DrawText(promptText, (SCREEN_WIDTH - promptTextWidth) / 2, SCREEN_HEIGHT / 2 + 40, promptFontSize, LIGHTGRAY);
}


void DrawHUD() {
    double elapsedTime = GetTime() - gameStartTime;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << elapsedTime;
    std::string timeString = "Time: " + stream.str();

    DrawText(timeString.c_str(), 10, 10, 20, WHITE);

    car1.DrawScore(10, 40, "Player 1");
    car2.DrawScore(10, 70, "Player 2");

    DrawFPS(SCREEN_WIDTH - 100, 10);
}