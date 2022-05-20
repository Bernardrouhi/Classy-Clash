#include "raylib.h"
#include "raymath.h"

int main()
{
    const int windowSize[2]{384, 384};

    InitWindow(windowSize[0], windowSize[1], "Classy Clash!");

    Texture2D map = LoadTexture("textures/World_24x24.png");
    Vector2 mapPos {0.0, 0.0};
    const float speed{4};

    Texture2D knight_idle = LoadTexture("textures/Knight/_Idle.png");
    Texture2D knight_run = LoadTexture("textures/Knight/_Run.png");

    Texture2D knight = LoadTexture("textures/Knight/_Idle.png");
    const float knightScale{3.0};
    Vector2 knightPos {
        (float)windowSize[0]/2.0f - knightScale * (0.5f * (float)knight.width/10.0f),
        (float)windowSize[1]/2.0f - knightScale * (0.5f * (float)knight.height)
    };

    float knightRunningTime{};
    int knightFrame{};
    const int knightMaxFrame{10};
    const float knightUpdateTime{1.f/12.f};

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;

        if(Vector2Length(direction) != 0.0)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }

        Vector2Length(direction) != 0.0 ? knight = knight_run : knight = knight_idle;

        // draw the map
        DrawTextureEx(map, mapPos, 0.f, 4.f, WHITE);

        // Update animation frame
        knightRunningTime += GetFrameTime();
        if(knightRunningTime >= knightUpdateTime)
        {
            knightFrame++;
            knightRunningTime = 0.f;
            knightFrame = knightFrame % knightMaxFrame;
        }

        // draw character
        Rectangle source {knightFrame * (float)knight.width/10.0f, 0.f, rightLeft * (float)knight.width/10.0f, (float)knight.height};
        Rectangle dest {knightPos.x, knightPos.y, knightScale * (float)knight.width/10.0f, knightScale * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(knight);
    UnloadTexture(map);
    CloseWindow();
    return 0;
}