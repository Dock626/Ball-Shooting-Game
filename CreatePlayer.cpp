#include "CreatePlayer.h"

void CreatePlayer::ShootProjectile(float x, float y) {
    bullets.push_back(Projectile(x, y));
}

CreatePlayer::CreatePlayer(float x, float y, int z) {

    ballPosition = { x, y };
    ballRadius = { z };
    ballStartPosition = ballPosition;
    ballStartRadius = ballRadius;
}

std::vector<Projectile>& CreatePlayer::GetBullets() {
    return bullets;
}

void CreatePlayer::Update(float delta) {

    if (Alive == false and IsKeyPressed(KEY_R)) { Reset(); }
    if (Alive == false) { return; }
    if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 4.0f;
    if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 4.0f;
    if (IsKeyDown(KEY_UP)) ballPosition.y -= 4.0f;
    if (IsKeyDown(KEY_DOWN)) ballPosition.y += 4.0f;
    if (IsKeyPressed(KEY_Z)) ShootProjectile(ballPosition.x, ballPosition.y);
    std::erase_if(bullets, [](Projectile& p) {return p.LifeSpan <= 0 or p.Disabled; });
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].position.x += 7.5f;
    }

}

void CreatePlayer::Reset() {
    Alive = true;
    Score = 0;
    ballPosition = ballStartPosition;
    ballRadius = ballStartRadius;
}

void CreatePlayer::Draw() {
    if (Alive == false) { return; };
    DrawCircleV(ballPosition, ballRadius, BLUE);
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }
}

int CreatePlayer::GetRadius() {
    return ballRadius;
}

bool CreatePlayer::Status() {
    return Alive;
}
