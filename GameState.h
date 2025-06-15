#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "raylib.h"
#include "Tile.h"
#include "Constants.h" 

#include "MapHandler.h"


// Game States
enum GameScreen {
    START_SCREEN = 0,
    PLAYING
};

// Global Variables
extern GameScreen currentGameState;
extern Tile* gameMap[MAP_COLS][MAP_ROWS];
extern Texture2D grassTexture;
extern Texture2D roadTexture;
extern Texture2D roadStraightTexture;
extern Texture2D roadCornerTexture;
extern Font gameFont;
extern double gameStartTime;
extern MapManager map;

// Function Declarations
void LoadGameResources();
void UnloadGameResources();
void InitGame();
void UpdateDrawFrame();

// Specific screen functions
void UpdateStartScreen();
void DrawStartScreen();

void UpdatePlayingScreen();
void DrawPlayingScreen();
void InitMap();
void DrawMap();
void CleanupMap();
void DrawTimer();

#endif // GAMESTATE_H
