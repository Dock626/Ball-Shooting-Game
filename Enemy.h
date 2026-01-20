#pragma once
#include "raylib.h"


class Enemy {
private:
    Vector2 Position_;

public:

    bool Alive{ true };

    Enemy(float x);;

    float GetRadius() const;

    void Update(float delta);
    void Draw();
    Vector2 Position();
};
