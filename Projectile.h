#pragma once
#include "raylib.h"

class Projectile {
public:
    Vector2 position;

    bool Disabled{ false };

    float LifeSpan{ 3 };

    Projectile(float x, float y);;

    Rectangle GetRect();

    void Update(float delta);;

    void Draw();

};