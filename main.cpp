#include "raylib.h"
#include "Constants.h"  
#include "GameState.h"  
#include <cstdlib>      // For srand
#include <ctime>        // For time

int main() {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RaceCar Game Project"); // Using constants
    InitAudioDevice(); 
    SetTargetFPS(60);  
    
    srand(static_cast<unsigned int>(time(NULL)));
    LoadGameResources();

    
    currentGameState = START_SCREEN; 
 

// Main game loop
    while (!WindowShouldClose()) {
        UpdateDrawFrame(); 
    }

    UnloadGameResources(); 
    CloseAudioDevice();    
    CloseWindow();         

    return 0;
}