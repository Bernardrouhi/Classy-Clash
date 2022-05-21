#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    // storing the last position
    worldPosLastFrame = worldPos;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        frame = frame % maxFrames;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    }
    Vector2Length(velocity) != 0.0 ? texture = run : texture = idle;
    velocity = {};

    // draw character
    Rectangle source{(frame * width), 0.f, (rightLeft * width), height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, (scale * width), (scale * height)};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);

}

void BaseCharacter::destroy()
{
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}