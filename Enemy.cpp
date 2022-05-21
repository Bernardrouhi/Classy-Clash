#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = static_cast<float>(texture.width) / static_cast<float>(maxFrames);
    height = static_cast<float>(texture.height);
    speed = 3.5f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick(float deltaTime)
{
    // check if player alive
    if (!getAlive())
        return;
    velocity = Vector2Subtract(target->getCenterPos(), getCenterPos());
    if (Vector2Length(velocity) < radius || Vector2Length(velocity) > detect_radius) velocity = {};
    BaseCharacter::tick(deltaTime);

    // check for damaging the player
    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }

    DrawCircleLines(getCenterPos().x, getCenterPos().y, detect_radius, RED);
}

void Enemy::reset()
{
    worldPos = {0.f, 0.f};
    setAlive(true);
}