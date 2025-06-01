#include "Tile.h"

Tile::Tile(float x, float y, float width, float height, TileType tileType)
    : type(tileType) {
    destRect = { x, y, width, height };

    // Set speed factors (car will use this later)
    switch (type) {
    case ROAD_STRAIGHT_VERTICAL:
    case ROAD_STRAIGHT_HORIZONTAL:
    case ROAD_CORNER_NW:
    case ROAD_CORNER_NE:
    case ROAD_CORNER_SW:
    case ROAD_CORNER_SE:
        speedFactor = 1.0f;
        break;
    case GRASS:
        speedFactor = 0.4f; // Car slows down on grass
        break;
    default:
        speedFactor = 1.0f;
        break;
    }
}

void Tile::Draw(Texture2D grassTex, Texture2D straightRoadTex, Texture2D cornerRoadTex) {
    // Source rectangles for drawing the entire texture
    Rectangle sourceRecGrass = { 0.0f, 0.0f, (float)grassTex.width, (float)grassTex.height };
    Rectangle sourceRecStraight = { 0.0f, 0.0f, (float)straightRoadTex.width, (float)straightRoadTex.height };
    Rectangle sourceRecCorner = { 0.0f, 0.0f, (float)cornerRoadTex.width, (float)cornerRoadTex.height };

    // --- 1. Draw Grass Layer ---
    if (grassTex.id > 0) {
        DrawTexturePro(grassTex, sourceRecGrass, destRect, { 0, 0 }, 0.0f, WHITE);
    }
    else {
        DrawRectangleRec(destRect, GREEN); // Fallback
    }

    // --- 2. Draw Road Layer (if applicable) ---
    Texture2D currentRoadTexture = { 0 }; // Default to no texture
    Rectangle sourceRecCurrentRoad = { 0,0,0,0 };
    float rotation = 0.0f;
    bool isRoad = false;

    switch (type) {
    case ROAD_STRAIGHT_VERTICAL:
        currentRoadTexture = straightRoadTex;
        sourceRecCurrentRoad = sourceRecStraight;
        rotation = 0.0f; // Assumes straightRoadTex is vertical by default
        isRoad = true;
        break;
    case ROAD_STRAIGHT_HORIZONTAL:
        currentRoadTexture = straightRoadTex;
        sourceRecCurrentRoad = sourceRecStraight;
        rotation = 90.0f; // Rotate vertical straight to horizontal
        isRoad = true;
        break;

        // Assuming roadCornerTexture connects TOP to LEFT (NW type visually)
    case ROAD_CORNER_NW: // Connects North(Top) to West(Left)
        currentRoadTexture = cornerRoadTex;
        sourceRecCurrentRoad = sourceRecCorner;
        rotation = 0.0f; // Default orientation
        isRoad = true;
        break;
    case ROAD_CORNER_NE: // Connects North(Top) to East(Right)
        currentRoadTexture = cornerRoadTex;
        sourceRecCurrentRoad = sourceRecCorner;
        rotation = 90.0f; // Rotate 90 deg clockwise
        isRoad = true;
        break;
    case ROAD_CORNER_SE: // Connects South(Bottom) to East(Right)
        currentRoadTexture = cornerRoadTex;
        sourceRecCurrentRoad = sourceRecCorner;
        rotation = 180.0f; // Rotate 180 deg
        isRoad = true;
        break;
    case ROAD_CORNER_SW: // Connects South(Bottom) to West(Left)
        currentRoadTexture = cornerRoadTex;
        sourceRecCurrentRoad = sourceRecCorner;
        rotation = 270.0f; // Rotate 270 deg clockwise
        isRoad = true;
        break;

    default:
        // GRASS or other non-road tile
        break;
    }

    if (isRoad) {
        if (currentRoadTexture.id > 0) {
            // Draw the road texture on top of the grass
            Vector2 origin = { TILE_WIDTH / 2.0f, TILE_HEIGHT / 2.0f };
            Rectangle roadDest = destRect;

            DrawTexturePro(
                currentRoadTexture,
                sourceRecCurrentRoad,
                roadDest,
                origin,
                rotation,
                WHITE
            );
        }
        else {
            DrawRectangleRec(destRect, GRAY); // Fallback color
        }
    }
}

    // Optional: Draw grid lines for debugging
    // DrawRectangleLinesEx(destRect, 1, LIGHTGRAY);
