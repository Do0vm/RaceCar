#ifndef CAR_H
#define CAR_H

#include "raylib.h"


class Tile;

class Car
{
public:
    // Constructor and Destructor
    Car(Vector2 initialPosition);
    ~Car();

    // Core Functions
    void Load();
    void Unload();
    void Update();
    void Draw() const;

    // Public Methods
    void Bounce();
    bool IsCollidingWithObject(const Tile& tile) const;
    bool IsHoveringObject(const Tile& tile) const;
    void Reset(Vector2 newPosition);

    // Getters and Setters
    void SetPosition(Vector2 pos);
    Rectangle GetBoundingBox() const;
    bool IsMovingForward() const;

private:
    // Private Helper Functions
    void HandleInput();
    void ApplyPhysics();
    void UpdateCollisionCircles();

    // Member Variables
    Vector2 mPosition;
    Vector2 mSize;
    Texture2D mTexture;

    // Physics State
    float mVelocity;
    float mRotation;
    float mRotationSpeed;
    bool mIsBouncing;
    bool mIsBraking;

    // Collision Shapes
    Vector2 mFrontCircleCenter;
    Vector2 mMiddleCircleCenter;
    Vector2 mBackCircleCenter;
};

#endif // CAR_H