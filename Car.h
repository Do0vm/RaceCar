#ifndef CAR_H
#define CAR_H

#include "raylib.h"
#include "MapHandler.h" 

// --- Tunable Physics Constants ---
const float CAR_VISUAL_SCALE = 0.15f;           
const float COLLISION_RADIUS = 5.0f;          
// --- Road Physics ---
const float ROAD_ACCELERATION = 200.0f;        
const float ROAD_MAX_SPEED = 200.0f;           
const float ROAD_FRICTION = 300.0f;            
const float ROAD_STEERING = 5.0f;              

// --- Grass Physics ---
const float GRASS_ACCELERATION = 400.0f;       
const float GRASS_MAX_SPEED = 150.0f;          
const float GRASS_FRICTION = 1000.0f;         
const float GRASS_STEERING = 1.0f;            

// --- General Physics ---
const float BRAKING_FORCE = 800.0f;            
const float REVERSE_SPEED = -80.0f;           
const float COLLISION_BOUNCE_FACTOR = -0.5f;  

class Car
{
public:
    Car(Vector2 initialPosition, int keyUp, int keyDown, int keyLeft, int keyRight, int keyBrake);
    ~Car();   
    Car();

    void Load();
    void Unload();
    void Update(const MapManager& mapManager);
    void Draw() const;

    void Bounce();
    bool IsCollidingWithTile(const Tile& tile) const;

    // Resets the car to a starting state.
    void Reset(Vector2 newPosition);
    void SetPosition(Vector2 pos);

    // Getters
    Rectangle GetBoundingBox() const;
    Vector2 GetPosition() const { return mPosition; }

private:
    // Helper methods for internal logic
    void HandleInput();
    void ApplyPhysics(const MapManager& mapManager);
    void UpdateCollisionCircles();

    // Car State
    Vector2 mPosition;
    Vector2 mSize;
    float mVelocity;
    float mRotation;

    // Input state
    float mAccelerationInput;
    float mRotationInput;
    bool mIsBraking;

    bool mIsBouncing;

    // Collision detection
    Vector2 mFrontCircleCenter;
    Vector2 mBackCircleCenter;

    // Resources
    Texture2D mTexture;


    //Keys
    int mKeyUp;
    int mKeyDown;
    int mKeyLeft;
    int mKeyRight;
    int mKeyBrake;
};

#endif //CAR_H