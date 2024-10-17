#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    int WindowSize[2]{384, 384};
    InitWindow(WindowSize[0], WindowSize[1], "2D Battle");
    SetTargetFPS(60);

    Character Knight{WindowSize[0], WindowSize[1]};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy Goblin{
        Vector2{600.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy Slime{
        Vector2{800.f, 400.f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* Enemies[]{
        &Goblin,
        &Slime
    };
    for (auto enemy : Enemies)
    {
        enemy->SetTarget(&Knight);
    }

    Texture2D Map = LoadTexture("nature_tileset/map.png");
    Vector2 MapPos{0.f, 0.f};

    const float MapScale = 4.f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        MapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);
        DrawTextureEx(Map, MapPos, 0.f, MapScale, WHITE);
        // Draw Props
        for (auto prop : props)
        {
            prop.Render(Knight.GetWorldPos());
            if (CheckCollisionRecs(prop.getCollisionRec(Knight.GetWorldPos()), Knight.GetCollision()))
            {
                Knight.UndoMovement();
            }
        }
        if (!Knight.GetAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string KnightHealth = "Health: ";
            KnightHealth.append(std::to_string(Knight.GetHealth()), 0, 5);
            DrawText(KnightHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        for (auto enemy : Enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : Enemies)
            {
                if (CheckCollisionRecs(Knight.GetWeaponCollisionRec(), enemy->GetCollision()))
                {
                    enemy->SetAlive(false);
                }
            }
        }
        //Check Map Bounds
        Knight.Tick(GetFrameTime());
        if( Knight.GetWorldPos().x < 0.f ||
            Knight.GetWorldPos().y < 0.f ||
            Knight.GetWorldPos().x + WindowSize[0] > Map.width * MapScale ||
            Knight.GetWorldPos().y + WindowSize[1] > Map.height * MapScale)
        {
            Knight.UndoMovement();
        }

        EndDrawing();
    }
    UnloadTexture(Map);
    CloseWindow();
}