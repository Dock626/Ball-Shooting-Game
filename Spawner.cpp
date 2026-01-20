#include "Spawner.h"

void Spawner::Spawn() {
    SpawnedObjects_.push_back(Enemy(800));
}

void Spawner::Update(float delta) {
    Timer += delta;
    if (Timer >= 3.0f) {
        Timer -= 3.0f;
        Spawn();
    };
    std::erase_if(SpawnedObjects_, [](Enemy& p) {return p.Position().x <= 0 or !p.Alive; });
}

std::vector<Enemy>& Spawner::GetSpawnedObjects() {
    return SpawnedObjects_;
}
