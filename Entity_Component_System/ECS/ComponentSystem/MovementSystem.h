#pragma once

#include "../EntitySystem/EntityManager.h"

// MovementSystem
// --------------
// Applies velocity to position.
//
class MovementSystem
{
public:
    void Update(EntityManager& entities, float dt);
};

