#pragma once
#include <vector>
#include "Enemy.h"
class Spawner {
private:
    std::vector<Enemy> SpawnedObjects_;

    float SpawnPer = 5.0f;

    float Timer = 0.0f;

public:
    void Spawn();;


    void Update(float delta);

    std::vector<Enemy>& GetSpawnedObjects();;

};