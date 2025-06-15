#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "raylib.h"

enum GameScreen {
    START_SCREEN,
    PLAYING,
    END_SCREEN
};

// --- Function Declarations ---

void LoadGameResources();

void UnloadGameResources();

void InitGame();

void UpdateStartScreen();

void DrawStartScreen();

void UpdatePlayingScreen();

void DrawPlayingScreen();

void DrawTimer();


void UpdateDrawFrame();

#endif // GAME_STATE_H