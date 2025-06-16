#include "Car.h"
#include "Constants.h"
#include <cmath> 
#include "Tile.h" 

Car::Car()
    : mPosition({ 0, 0 }), mSize({ 0, 0 }), mVelocity(0.0f), mRotation(0.0f),
    mAccelerationInput(0.0f), mRotationInput(0.0f), mIsBraking(false),
    mTexture({ 0 }), mIsBouncing(false), mKeyUp(0), mKeyDown(0), mKeyLeft(0),
    mKeyRight(0), mKeyBrake(0)
{
}

Car::Car(Vector2 initialPosition, int keyUp, int keyDown, int keyLeft, int keyRight, int keyBrake)
    : mPosition(initialPosition),
    mSize({ 0, 0 }),
    mVelocity(0.0f),
    mRotation(0.0f),
    mAccelerationInput(0.0f),
    mRotationInput(0.0f),
    mIsBraking(false),
    mTexture({ 0 }),
    mIsBouncing(false),
    mKeyUp(keyUp),
    mKeyDown(keyDown),
    mKeyLeft(keyLeft),
    mKeyRight(keyRight),
    mKeyBrake(keyBrake)
{
}


Car::~Car()
{
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

void Car::Update(const MapManager& mapManager)
{

    HandleInput();

    //if (!mIsBouncing)
    //{
    //    HandleInput();
    //}
    ApplyPhysics(mapManager);
    UpdateCollisionCircles();
}

void Car::Draw() const
{
    Rectangle source = { 0.0f, 0.0f, mSize.x, mSize.y };
    Rectangle dest = { mPosition.x, mPosition.y, mSize.x * CAR_VISUAL_SCALE, mSize.y * CAR_VISUAL_SCALE };
    Vector2 origin = { (mSize.x * CAR_VISUAL_SCALE) / 2.0f, (mSize.y * CAR_VISUAL_SCALE) / 2.0f };
    DrawTexturePro(mTexture, source, dest, origin, mRotation + 90.0f, WHITE);
}

void Car::HandleInput()
{
    mAccelerationInput = 0.0f;
    if (IsKeyDown(mKeyUp)) mAccelerationInput = 1.0f;    
    if (IsKeyDown(mKeyDown)) mAccelerationInput = -1.0f; 

    mIsBraking = IsKeyDown(mKeyBrake); 

    mRotationInput = 0.0f;
    if (IsKeyDown(mKeyLeft)) mRotationInput = -1.0f;   
    if (IsKeyDown(mKeyRight)) mRotationInput = 1.0f;  
}


void Car::ApplyPhysics(const MapManager& mapManager)
{
    // --- Determine Surface Properties ---
    Tile* currentTile = mapManager.GetTileAtPixel(mPosition);
    bool onGrass = (currentTile && currentTile->GetType() == TileType::GRASS);

    float currentMaxSpeed = onGrass ? GRASS_MAX_SPEED : ROAD_MAX_SPEED;
    float currentAcceleration = onGrass ? GRASS_ACCELERATION : ROAD_ACCELERATION;
    float currentFriction = onGrass ? GRASS_FRICTION : ROAD_FRICTION;
    float currentSteering = onGrass ? GRASS_STEERING : ROAD_STEERING;

    // --- Apply Acceleration & Braking ---
    if (mIsBraking)
    {
        mVelocity -= BRAKING_FORCE * (mVelocity > 0 ? 1.0f : -1.0f) * GetFrameTime();
    }
    else
    {
        mVelocity += currentAcceleration * mAccelerationInput * GetFrameTime();
    }

    // --- Apply Friction ---
    if (std::abs(mAccelerationInput) < 0.1f && std::abs(mVelocity) > 0)
    {
        mVelocity -= currentFriction * (mVelocity > 0 ? 1.0f : -1.0f) * GetFrameTime();
        if (std::abs(mVelocity) < 1.0f)
        {
            mVelocity = 0;
        }
    }

    // --- Clamp Velocity ---
    if (mVelocity > currentMaxSpeed) mVelocity = currentMaxSpeed;
    if (mVelocity < REVERSE_SPEED) mVelocity = REVERSE_SPEED;

    // --- Apply Rotation ---
    if (std::abs(mVelocity) > 1.0f)
    {
        float speedFactor = std::min(std::abs(mVelocity) / 200.0f, 1.0f);
        mRotation += mRotationInput * currentSteering * speedFactor * (mVelocity > 0 ? 1.0f : -1.0f) * 100.0f * GetFrameTime();
    }

    // --- Update Position ---
    float angleInRadians = mRotation * DEG2RAD;
    mPosition.x += mVelocity * cos(angleInRadians) * GetFrameTime();
    mPosition.y += mVelocity * sin(angleInRadians) * GetFrameTime();

    // --- Handle Bouncing State ---
    if (mIsBouncing && std::abs(mVelocity) < 20.0f) {
        mIsBouncing = false;
    }
}


void Car::UpdateCollisionCircles()
{
    float angleInRadians = mRotation * DEG2RAD;
    float cosA = cos(angleInRadians);
    float sinA = sin(angleInRadians);

    float frontDistance = (mSize.y * CAR_VISUAL_SCALE) / 2.0f - COLLISION_RADIUS;

    mFrontCircleCenter.x = mPosition.x + cosA * frontDistance;
    mFrontCircleCenter.y = mPosition.y + sinA * frontDistance;

    mBackCircleCenter.x = mPosition.x - cosA * frontDistance;
    mBackCircleCenter.y = mPosition.y - sinA * frontDistance;
}

void Car::Bounce()
{
    if (!mIsBouncing)
    {
        mVelocity *= COLLISION_BOUNCE_FACTOR;
        mIsBouncing = true;
    }
}

bool Car::IsCollidingWithTile(const Tile& tile) const
{
    const Rectangle tileRect = tile.GetRect();

    if (CheckCollisionCircleRec(mFrontCircleCenter, COLLISION_RADIUS, tileRect) ||
        CheckCollisionCircleRec(mBackCircleCenter, COLLISION_RADIUS, tileRect))
    {
        return true;
    }
    return false;
}

void Car::Reset(Vector2 newPosition)
{
    mPosition = newPosition;
    mVelocity = 0.0f;
    mRotation = 0.0f;
    mAccelerationInput = 0.0f;
    mRotationInput = 0.0f;
    mIsBouncing = false;
}

void Car::SetPosition(Vector2 pos)
{
    mPosition = pos;
    UpdateCollisionCircles();
}

Rectangle Car::GetBoundingBox() const
{
    return {
        mPosition.x - (mSize.x * CAR_VISUAL_SCALE) / 2.0f,
        mPosition.y - (mSize.y * CAR_VISUAL_SCALE) / 2.0f,
        mSize.x * CAR_VISUAL_SCALE,
        mSize.y * CAR_VISUAL_SCALE
    };
}
