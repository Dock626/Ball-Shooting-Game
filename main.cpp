#include <iostream>
#include <vector>
#include "raylib.h"
class Spawner;

class Projectile {
public:
    Vector2 position;

    float LifeSpan = 3;

    Projectile(float x, float y) {
        position = { x, y };
    };

    void Update(float delta) {
        LifeSpan -= delta;
        position.x += 5.0f;
    };

    void Draw() {
        DrawRectangleV({ position.x, position.y }, { 10.0f, 5.0f }, RED);
    }
        
};

class CreatePlayer {
private:
    std::vector<Projectile> bullets;
    
    Vector2 ballPosition;
    
    void ShootProjectile(float x, float y) {
        bullets.push_back(Projectile(x, y));
    }
    
public:
    CreatePlayer(float x, float  y) {
        ballPosition = { (x/2) - 225, y / 2};
    };

    void Update(float delta) {
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 4.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 4.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 4.0f;
        if (IsKeyPressed(KEY_Z)) ShootProjectile(ballPosition.x, ballPosition.y);
        std::erase_if(bullets, [](Projectile p) {return p.LifeSpan <= 0;});
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].position.x += 7.5f;
        }

    };

    void Draw() {
        DrawCircleV(ballPosition, 25, BLUE);
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw();
        }
    };
        
};

class Enemy {
private:
    Vector2 Position_;

public:
    Enemy(float x) {
        float y = GetRandomValue(0, x);
        Position_ = { x, y };
    };


    void Update(float delta) {
        Position_.x -= 5.0f;
        std::cout << "testing";
    }
    void Draw() {
        DrawCircleV(Position_, 25, RED);
    }
    auto Position() {
        return Position_;
    }
};

class Spawner {
private:
    std::vector<Enemy> SpawnedObjects_;

    float SpawnPer = 5.0f;

    float Timer = 0.0f;

public:
    void Spawn() {
        SpawnedObjects_.push_back(Enemy(800));
        std::cout << "Enemy Spawned";
        std::format("Enemy Spawned2");
    };


    void Update(float delta) {
        Timer += delta;
        if (Timer >= 5.0f) {
            Timer -= 5.0f;
            Spawn();
        };
        std::erase_if(SpawnedObjects_, [](Enemy p) {return p.Position().x <= 0; });
    }

    auto& GetSpawnedObjects() {
        return SpawnedObjects_;
    };

};
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
    CreatePlayer Player{ screenWidth, screenHeight };
    Spawner spawn{};
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();

        Player.Update(delta);
        spawn.Update(delta);
        for (auto& enemy : spawn.GetSpawnedObjects())
        {
            enemy.Update(delta);
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("move the ball with arrow keys, shoot with z", 10, 10, 20, DARKGRAY);

        Player.Draw();
        for (auto& enemy : spawn.GetSpawnedObjects())
        {
            enemy.Draw();
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