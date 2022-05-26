#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main()
{
    const int windowSize[2]{384, 384};

    InitWindow(windowSize[0], windowSize[1], "Classy Clash!");

    Texture2D map = LoadTexture("textures/World_24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.f};

    Texture2D knight_idle = LoadTexture("textures/Knight/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("textures/Knight/knight_run_spritesheet.png");
    Texture2D goblin_idle = LoadTexture("textures/Enemy/goblin_idle_spritesheet.png");
    Texture2D goblin_run = LoadTexture("textures/Enemy/goblin_run_spritesheet.png");
    Texture2D slime_idle = LoadTexture("textures/Enemy/slime_idle_spritesheet.png");
    Texture2D slime_run = LoadTexture("textures/Enemy/slime_run_spritesheet.png");

    Character knight{windowSize[0], windowSize[1], knight_idle, knight_run};
    int numEnemies {GetRandomValue(5,50)};
    Enemy *enemies[numEnemies];
    bool regCharacter{};
    for (int i = 0 ; i < numEnemies ; i++ )
    {
        if(regCharacter)
        {
            enemies[i] = new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, slime_idle, slime_run};
        }
        else
        {
            enemies[i] = new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, goblin_idle, goblin_run};
        }
        regCharacter = !regCharacter;

    }
    // {
    //     new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, slime_idle, slime_run},
    //     new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, slime_idle, slime_run},
    //     new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, goblin_idle, goblin_run},
    //     new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, goblin_idle, goblin_run},
    //     new Enemy{Vector2{static_cast<float>(32 * GetRandomValue(1,35)), static_cast<float>(32 * GetRandomValue(1,28))}, goblin_idle, goblin_run}};

    // setting target
    for (Enemy *enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

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

        knight.tick(dt);
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowSize[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowSize[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (Enemy *enemy : enemies)
            {
                if (CheckCollisionRecs(
                        enemy->getCollisionRec(),
                        knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        // Debug
        // DrawRectangleLines(knight.getCollisionRec().x, knight.getCollisionRec().y, knight.getCollisionRec().width, knight.getCollisionRec().height, RED);

        for (Prop prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // update HUD
        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth{"Health: "};
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(
                knightHealth.c_str(),
                5.f, (windowSize[1] - 20), 20, BLACK);
        }

        // draw enemy
        for (Enemy *enemy : enemies)
        {
            enemy->tick(dt);
        }

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);
    UnloadTexture(goblin_idle);
    UnloadTexture(goblin_run);
    UnloadTexture(slime_idle);
    UnloadTexture(slime_run);
    for (Prop prop : props)
    {
        prop.destroy();
    }
    delete [] enemies;
    CloseWindow();
    return 0;
}