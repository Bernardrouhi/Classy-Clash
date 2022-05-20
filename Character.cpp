#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = (float)texture.width / (float)maxFrames;
    height = (float)texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - scale * (0.5f * width),
        (float)winHeight / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    }

    Vector2Length(direction) != 0.0 ? texture = run : texture = idle;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        frame = frame % maxFrames;
    }

    // draw character
    Rectangle source{(frame * width), 0.f, (rightLeft * width), height};
    Rectangle dest{screenPos.x, screenPos.y, (scale * width), (scale * height)};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::destroy()
{
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}
