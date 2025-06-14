#include "Car.h"
#include <cmath>       
#include "raymath.h"

Car::Car(Rectangle rect, float initialRotation)
{
    mPosition = { rect.x, rect.y };
    mSize = { rect.width, rect.height };
    mVelocity = 0;
    mAcceleration = 0;
    mRotationSpeed = 2.5f;  // reasonable default
    mMaxVelocity = 5.0f;    // reasonable default
    mRotation = initialRotation;
}

Car::~Car()
{
    // Nothing to cleanup yet
}

void Car::Load()
{
    // Load resources like textures if needed
}

void Car::Start()
{
    // Initialize values if necessary
}

void Car::Update()
{
    // Basic controls (Arrow keys)
    if (IsKeyDown(KEY_UP)) {
        mVelocity += 0.1f;
        if (mVelocity > mMaxVelocity) mVelocity = mMaxVelocity;
    }
    else {
        // Slow down gradually
        mVelocity *= 0.95f;
    }

    if (IsKeyDown(KEY_LEFT)) {
        mRotation -= mRotationSpeed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        mRotation += mRotationSpeed;
    }

    // Update position based on velocity and rotation
    mPosition.x += mVelocity * cosf(mRotation * DEG2RAD);
    mPosition.y += mVelocity * sinf(mRotation * DEG2RAD);
}

void Car::Draw()
{
    // Draw as a simple rectangle (placeholder for sprite)
    DrawRectanglePro(
        { mPosition.x, mPosition.y, mSize.x, mSize.y },
        { mSize.x / 2, mSize.y / 2 },
        mRotation,
        RED
    );
}

void Car::Unload()
{
    // Unload resources if you loaded any
}
