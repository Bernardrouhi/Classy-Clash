#include "raylib.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
    void destroy();

private:
    Texture2D texture = LoadTexture("textures/Knight/_Idle.png");
    Texture2D idle = LoadTexture("textures/Knight/_Idle.png");
    Texture2D run = LoadTexture("textures/Knight/_Run.png");
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    int maxFrames{10};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{2.0f};
};