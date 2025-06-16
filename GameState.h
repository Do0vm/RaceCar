#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "raylib.h"

enum GameScreen {
    START_SCREEN,
    PLAYING,
    END_SCREEN
};

void InitGame();
void UnloadGame();
void UpdateDrawFrame();

#endif // GAME_STATE_H