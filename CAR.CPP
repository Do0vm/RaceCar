#include "Car.h"
#include <cmath>       
#include "raymath.h"

Car::Car(Rectangle rect, float initialRotation)
{
    mPosition = { rect.x, rect.y };
    mSize = { rect.width, rect.height };
    velocity = 0;
    acceleration = 0;
    rotationSpeed = 2.5f;  // reasonable default
    maxVelocity = 5.0f;    // reasonable default
    rotation = initialRotation;
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
        velocity += 0.1f;
        if (velocity > maxVelocity) velocity = maxVelocity;
    }
    else {
        // Slow down gradually
        velocity *= 0.95f;
    }

    if (IsKeyDown(KEY_LEFT)) {
        rotation -= rotationSpeed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        rotation += rotationSpeed;
    }

    // Update position based on velocity and rotation
    mPosition.x += velocity * cosf(rotation * DEG2RAD);
    mPosition.y += velocity * sinf(rotation * DEG2RAD);
}

void Car::Draw()
{
    // Draw as a simple rectangle (placeholder for sprite)
    DrawRectanglePro(
        { mPosition.x, mPosition.y, mSize.x, mSize.y },
        { mSize.x / 2, mSize.y / 2 },
        rotation,
        RED
    );
}

void Car::Unload()
{
    // Unload resources if you loaded any
}
