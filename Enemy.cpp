#include "Enemy.h"

Enemy::Enemy(float x) {
    float y = GetRandomValue(0, 450);
    Position_ = { x, y };
}

float Enemy::GetRadius() const {
    return 25.0f;
}

void Enemy::Update(float delta) {
    Position_.x -= 5.0f;
}

void Enemy::Draw() {
    DrawCircleV(Position_, GetRadius(), RED);
}

Vector2 Enemy::Position() {
    return Position_;
}
