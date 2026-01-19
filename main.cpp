#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
class Spawner;
class Enemy;

class Projectile {
public:
    Vector2 position;

    bool Disabled { false };

    float LifeSpan{ 3 };

    Projectile(float x, float y) {
        position = { x, y };
    };

    Rectangle GetRect() {
        return{ position.x, position.y, 10.0f, 5.0f };
    }
    
    void Update(float delta) {
        LifeSpan -= delta;
        position.x += 5.0f;
    };

    void Draw() {
        DrawRectangleRec(this->GetRect(), RED);
    }
        
};

class CreatePlayer {
private:

    bool Alive = true;

    std::vector<Projectile> bullets;
    
    Vector2 ballPosition;
    int ballRadius;
    
    Vector2 ballStartPosition;
    float ballStartRadius;

    void ShootProjectile(float x, float y) {
        bullets.push_back(Projectile(x, y));
    }
    
public:

    int Score = 0;

    CreatePlayer(float x, float  y, int z) {
        
        ballPosition = { x, y };
        ballRadius = { z };
        ballStartPosition = ballPosition;
        ballStartRadius = ballRadius;
    }

    auto& GetBullets() {
        return bullets;
    }

    void Update(float delta) {

        if (Alive == false and IsKeyPressed(KEY_R)) { Reset(); }
        if (Alive == false) { return; }
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 4.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 4.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 4.0f;
        if (IsKeyPressed(KEY_Z)) ShootProjectile(ballPosition.x, ballPosition.y);
        std::erase_if(bullets, [](Projectile& p) {return p.LifeSpan <= 0 or p.Disabled;});
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].position.x += 7.5f;
        }

    };

    void Reset() {
        Alive = true;
        Score = 0;
        ballPosition = ballStartPosition;
        ballRadius = ballStartRadius;
    }

    void Draw() {
        if (Alive == false) { return; };
        DrawCircleV(ballPosition, ballRadius, BLUE);
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw();
        }
    };
    
    auto GetRadius() {
        return ballRadius;
    }

    auto GetPosition() {
        return ballPosition;
    }

    auto Status() {
        return Alive;
    }
    void Die(){
        Alive = false;
    }

};

class Enemy {
private:
    Vector2 Position_;

public:

    bool Alive{ true };

    Enemy(float x) {
        float y = GetRandomValue(0, 450);
        Position_ = { x, y };
    };

    float GetRadius() const {
        return 25.0f;
    }

    void Update(float delta) {
        Position_.x -= 5.0f;
    }
    void Draw() {
        DrawCircleV(Position_, GetRadius(), RED);
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
    };


    void Update(float delta) {
        Timer += delta;
        if (Timer >= 3.0f) {
            Timer -= 3.0f;
            Spawn();
        };
        std::erase_if(SpawnedObjects_, [](Enemy& p) {return p.Position().x <= 0 or !p.Alive; });
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
    CreatePlayer Player{ (screenWidth / 2) - 225, screenHeight / 2, 25 };
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
