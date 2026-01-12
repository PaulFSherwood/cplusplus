#pragma once
#include "../EntitySystem/EntityManager.h"
#include "MapSystem.h"

class CollisionSystem
{
public:
    void Update(EntityManager& entities, MapSystem& map);
};

