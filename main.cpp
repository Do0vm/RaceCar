#include "raylib.h"
#include "Constants.h"
#include "GameState.h"
#include "MapHandler.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

MapManager map;

// Function declarations
void Load();
void Start();
void Update();
void Draw();
void Unload();

int main() {
    Load();
    Start();

    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    Unload();
    return 0;
}

void Load() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Racer Deluxe");
    InitAudioDevice();
    SetTargetFPS(60);

    srand(static_cast<unsigned int>(time(NULL)));

    LoadGameResources();
    InitGame();

    map.Load();
}

void Start() {
    currentGameState = START_SCREEN;
    cout << "[i] Game started. Initial state: START_SCREEN" << endl;
}

void Update() {
    UpdateDrawFrame();
    map.Update(); // Optional: add conditional if needed for certain states
}

void Draw() {
    BeginDrawing();

    switch (currentGameState) {
    case START_SCREEN:
        DrawStartScreen();
        break;
    case PLAYING:
        DrawPlayingScreen();
        break;
    default:
        ClearBackground(RAYWHITE);
        DrawText("Unknown State", 10, 10, 20, RED);
        break;
    }

    EndDrawing();
}

void Unload() {
    UnloadGameResources();
    CloseAudioDevice();
    CloseWindow();
}