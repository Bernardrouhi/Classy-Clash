#include "raylib.h"

class Character
{
public:
    Character();
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void destroy();

private:
    Texture2D texture = LoadTexture("textures/Knight/_Idle.png");
    Texture2D idle = LoadTexture("textures/Knight/_Idle.png");
    Texture2D run = LoadTexture("textures/Knight/_Run.png");
    Vector2 screenPos{};
    Vector2 worldPos{};

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    int maxFrames{10};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float scale{3.f};
    float width{};
    float height{};
};