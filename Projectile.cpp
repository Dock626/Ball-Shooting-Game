#include "Projectile.h"

Projectile::Projectile(float x, float y) {
    position = { x, y };
}

Rectangle Projectile::GetRect() {
    return{ position.x, position.y, 10.0f, 5.0f };
}

void Projectile::Update(float delta) {
    LifeSpan -= delta;
    position.x += 5.0f;
}

void Projectile::Draw() {
    DrawRectangleRec(this->GetRect(), RED);
}

