#include "raylib.h"
#include "Constants.h"
#include "GameState.h" // The only header you need for the game loop

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Racer - Map Selection");
    SetTargetFPS(60);

    // Set up the game states, load resources, etc.
    InitGame();

    // Main game loop
    // UpdateDrawFrame() now handles all the logic for updating and drawing based on the current game state.
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    UnloadGame();
    CloseWindow();

    return 0;
}
