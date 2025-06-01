#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "raylib.h"
#include "Tile.h" // Needs Tile definition for the map array

// Game States
enum GameScreen {
    START_SCREEN = 0,
    PLAYING,
    // GAME_OVER // Future state
};

// Global Variables
extern GameScreen currentGameState;
extern Tile* gameMap[MAP_COLS][MAP_ROWS]; // As per user's map[x][y] structure
extern Texture2D grassTexture;
extern Texture2D roadTexture;
extern Font gameFont; // For timer and messages
extern double gameStartTime;
extern Texture2D grassTexture;
// extern Texture2D roadTexture; 
extern Texture2D roadStraightTexture;
extern Texture2D roadCornerTexture;
extern Font gameFont;

// Function Declarations
void LoadGameResources();
void UnloadGameResources();
void InitGame(); // To initialize/reset game state for PLAYING
void UpdateDrawFrame(); // Main update and draw call per frame

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