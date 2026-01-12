#pragma once

#include "../EntitySystem/EntityManager.h"

// InputSystem
// -----------
// Converts player input into velocity changes.
// This is where "control" lives.
//
class InputSystem
{
public:
    void Update(EntityManager& entities, float dt);
};

