#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "Spawner.h"
#include "CreatePlayer.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    CreatePlayer Player{ (screenWidth / 2) - 225, screenHeight / 2, 25 };
    Spawner spawn{};
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();

        Player.Update(delta);
        if (Player.Status() == true) {
            spawn.Update(delta);
        }
        
        for (auto& enemy : spawn.GetSpawnedObjects())
        {
            enemy.Update(delta);
        }

        for (auto& enemy : spawn.GetSpawnedObjects()) {
            if (not enemy.Alive) { continue; }
            if (CheckCollisionCircles(Player.GetPosition(), Player.GetRadius(), enemy.Position(), enemy.GetRadius())) {
                Player.Die();
                enemy.Alive = false;
                break;
            };

                for (auto& bullet : Player.GetBullets()) {
                    if (not bullet.Disabled and CheckCollisionCircleRec(enemy.Position(), enemy.GetRadius(), bullet.GetRect())) {
                        bullet.Disabled = true;
                        enemy.Alive = false;
                        Player.Score += 1;
                    }
                }
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (Player.Status() == false) {
            DrawText("You died! Press R to start over.", 10, 10, 20, RED);
            DrawText(TextFormat("Your score: %d", Player.Score), screenWidth / 2 - 175, screenHeight / 2 - 50, 50, DARKGRAY);
        }
        else {
            DrawText("move the ball with arrow keys, shoot with z", 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Your score: %d", Player.Score), 10, 30, 20, DARKBLUE);
        }
        

        Player.Draw();
        for (auto& enemy : spawn.GetSpawnedObjects())
        {
            if (Player.Status() == true) { enemy.Draw(); }
        }
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}
