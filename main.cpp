#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int windowSize[2]{384, 384};

    InitWindow(windowSize[0], windowSize[1], "Classy Clash!");

    Texture2D map = LoadTexture("textures/World_24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowSize[0],windowSize[1]);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        const float dt {GetFrameTime()};

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.f, 4.f, WHITE);
        knight.tick(dt);

        EndDrawing();
    }

    knight.destroy();
    UnloadTexture(map);
    CloseWindow();
    return 0;
}