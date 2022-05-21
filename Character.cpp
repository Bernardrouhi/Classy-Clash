#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight, Texture2D idle_texture, Texture2D run_texture) : windowWidth(winWidth),
                                                                                                   windowHeight(winHeight)
{

    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = static_cast<float>(texture.width) / static_cast<float>(maxFrames);
    height = static_cast<float>(texture.height);
}

Vector2 Character::getScreenPos()
{
    return Vector2{static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
                   static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);
}