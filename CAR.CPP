#include "Car.h"
#include "Constants.h"
#include <cmath>
#include "Tile.h"


#include "raylib.h"

Car::Car(Vector2 initialPosition)
    : mPosition(initialPosition),
    mSize({ 0, 0 }),
    mVelocity(0.0f),
    mRotation(0.0f),
    mRotationSpeed(0.0f),
    mTexture({ 0 }),
    mIsBouncing(false),
    mIsBraking(false)
{
}

Car::~Car()
{
    if (mTexture.id > 0)
    {
        Unload();
    }
}

void Car::Load()
{
    mTexture = LoadTexture("resources/sprites/car.png");
    mSize = { (float)mTexture.width, (float)mTexture.height };
    UpdateCollisionCircles();
}

void Car::Unload()
{
    UnloadTexture(mTexture);
}

void Car::Update()
{
    HandleInput();
    ApplyPhysics();
    UpdateCollisionCircles();
}

void Car::Draw() const
{
    Rectangle source = { 0.0f, 0.0f, mSize.x, mSize.y };
    Rectangle dest = { mPosition.x, mPosition.y, mSize.x, mSize.y };
    Vector2 origin = { mSize.x / 2.0f, mSize.y / 2.0f };
    DrawTexturePro(mTexture, source, dest, origin, mRotation + 90.0f, WHITE);
}

void Car::HandleInput()
{
    float accelerationInput = 0.0f;
    if (IsKeyDown(KEY_W)) accelerationInput = 9.0f;
    if (IsKeyDown(KEY_S)) accelerationInput = -9.0f;

    float turnInput = 0.0f;
    if (IsKeyDown(KEY_A)) turnInput = -1.0f;
    if (IsKeyDown(KEY_D)) turnInput = 1.0f;

    mIsBraking = IsKeyDown(KEY_SPACE);

    if (accelerationInput != 0.0f && !mIsBouncing)
    {
        mVelocity += ACCELERATION * accelerationInput * GetFrameTime();
    }

    if (std::abs(mVelocity) > 1.0f && !mIsBouncing)
    {
        float turnEffect = turnInput * (mVelocity * STEERING_DRAG_FACTOR);
        mRotationSpeed += ANGULAR_ACCELERATION * turnEffect * GetFrameTime();
    }
}

void Car::ApplyPhysics()
{
    if (mIsBouncing)
    {
        mVelocity += FRICTION * (mVelocity > 0 ? -1.0f : 1.0f) * GetFrameTime();
        if (std::abs(mVelocity) < 10.0f)
        {
            mVelocity = 0.0f;
            mIsBouncing = false;
        }
    }
    else if (mIsBraking)
    {
        if (std::abs(mVelocity) > 0.0f)
        {
            mVelocity -= BRAKING_ACCELERATION * (mVelocity > 0 ? 1.0f : -1.0f) * GetFrameTime();
        }
        if (std::abs(mVelocity) < 1.0f) mVelocity = 0.0f;
    }
    else
    {
        if (std::abs(mVelocity) > 0.0f)
        {
            mVelocity -= FRICTION * (mVelocity > 0 ? 1.0f : -1.0f) * GetFrameTime();
            if (std::abs(mVelocity) < 1.0f) mVelocity = 0.0f;
        }
    }

    if (std::abs(mRotationSpeed) > 0.0f)
    {
        mRotationSpeed -= STEERING_FRICTION * (mRotationSpeed > 0 ? 1.0f : -1.0f) * GetFrameTime();
        if (std::abs(mRotationSpeed) < 0.01f) mRotationSpeed = 0.0f;
    }

    if (mVelocity > MAX_VELOCITY) mVelocity = MAX_VELOCITY;
    if (mVelocity < MAX_REVERSE_VELOCITY) mVelocity = MAX_REVERSE_VELOCITY;
    if (mRotationSpeed > MAX_ANGULAR_VELOCITY) mRotationSpeed = MAX_ANGULAR_VELOCITY;
    if (mRotationSpeed < -MAX_ANGULAR_VELOCITY) mRotationSpeed = -MAX_ANGULAR_VELOCITY;

    float angleInRadians = mRotation * DEG2RAD;
    mPosition.x += mVelocity * cos(angleInRadians) * GetFrameTime();
    mPosition.y += mVelocity * sin(angleInRadians) * GetFrameTime();
    mRotation += mRotationSpeed * mVelocity * GetFrameTime();

    if (mRotation >= 360.0f) mRotation -= 360.0f;
    if (mRotation < 0.0f) mRotation += 360.0f;
}

void Car::UpdateCollisionCircles()
{
    float angleInRadians = mRotation * DEG2RAD;
    float cosA = cos(angleInRadians);
    float sinA = sin(angleInRadians);
    float frontDistance = mSize.y / 2.0f - COLLISION_RADIUS;
    float backDistance = mSize.y / 2.0f - COLLISION_RADIUS;

    mFrontCircleCenter.x = mPosition.x + cosA * frontDistance;
    mFrontCircleCenter.y = mPosition.y + sinA * frontDistance;

    mBackCircleCenter.x = mPosition.x - cosA * backDistance;
    mBackCircleCenter.y = mPosition.y - sinA * backDistance;

    mMiddleCircleCenter = mPosition;
}

void Car::Bounce()
{
    if (!mIsBouncing)
    {
        mVelocity *= COLLISION_BOUNCE_FACTOR;
        mRotationSpeed = 0;
        mIsBouncing = true;
    }
}

bool Car::IsCollidingWithObject(const Tile& tile) const
{
    // Get the collision rectangle directly from the tile.
    const Rectangle tileRect = tile.GetRect();

    // Check collision for the front of the car if moving forward.
    if (mVelocity > 0 && CheckCollisionCircleRec(mFrontCircleCenter, COLLISION_RADIUS, tileRect))
    {
        return true;
    }

    // Check collision for the back of the car if moving backward.
    if (mVelocity < 0 && CheckCollisionCircleRec(mBackCircleCenter, COLLISION_RADIUS, tileRect))
    {
        return true;
    }

    // No collision detected.
    return false;
}

bool Car::IsHoveringObject(const Tile& tile) const
{
    // Get the collision rectangle and check for collision with the car's center.
    const Rectangle tileRect = tile.GetRect();
    return CheckCollisionCircleRec(mMiddleCircleCenter, COLLISION_RADIUS, tileRect);
}

void Car::Reset(Vector2 newPosition)
{
    mPosition = newPosition;
    mVelocity = 0.0f;
    mRotation = 0.0f;
    mRotationSpeed = 0.0f;
    mIsBouncing = false;
    mIsBraking = false;
}

void Car::SetPosition(Vector2 pos)
{
    mPosition = pos;
    UpdateCollisionCircles();
}

Rectangle Car::GetBoundingBox() const
{
    return { mPosition.x - mSize.x / 2.0f, mPosition.y - mSize.y / 2.0f, mSize.x, mSize.y };
}

bool Car::IsMovingForward() const
{
    return mVelocity > 0;
}