#include "raylib.h"
#include "Constants.h"
#include "GameState.h" 

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RAYLIB RETRO RACER");
    SetTargetFPS(144);

    InitGame();

    
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    UnloadGame();
    CloseWindow();

    return 0;
}
