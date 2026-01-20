#pragma once
#include "raylib.h"
#include <vector>
#include "Projectile.h"

class CreatePlayer {
private:

    bool Alive = true;

    std::vector<Projectile> bullets;

    Vector2 ballPosition;
    int ballRadius;

    Vector2 ballStartPosition;
    float ballStartRadius;

    void ShootProjectile(float x, float y);

public:

    int Score = 0;

    CreatePlayer(float x, float  y, int z);

    std::vector<Projectile>& GetBullets();

    void Update(float delta);;

    void Reset();

    void Draw();;

    int GetRadius();

    auto GetPosition() {
        return ballPosition;
    }

    bool Status();
    void Die() {
        Alive = false;
    }

};