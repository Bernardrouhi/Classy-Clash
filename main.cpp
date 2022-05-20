#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int windowSize[2]{384, 384};

    InitWindow(windowSize[0], windowSize[1], "Classy Clash!");

    Texture2D map = LoadTexture("textures/World_24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.f};

    Character knight{windowSize[0], windowSize[1]};
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("textures/Props/rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("textures/Props/log.png")}};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        const float dt{GetFrameTime()};

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);
        for (Prop prop : props)
        {
            prop.Render(knight.getWorldPos());
        }
        // rock.Render(knight.getWorldPos());
        knight.tick(dt);
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowSize[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowSize[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Debug
        DrawRectangle(knight.getCollisionRec().x, knight.getCollisionRec().y, knight.getCollisionRec().width, knight.getCollisionRec().height, RED);

        for (Prop prop : props)
        {
            // Debug
            DrawRectangle(
                    prop.getCollisionRec(knight.getWorldPos()).x, 
                    prop.getCollisionRec(knight.getWorldPos()).y,
                    prop.getCollisionRec(knight.getWorldPos()).width, 
                    prop.getCollisionRec(knight.getWorldPos()).height, RED);
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }
    for (Prop prop : props)
    {
        prop.destroy();
    }
    knight.destroy();
    UnloadTexture(map);
    CloseWindow();
    return 0;
}