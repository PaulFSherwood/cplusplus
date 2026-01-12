#pragma once

#include "../EntitySystem/EntityManager.h"
#include "../Core/Camera.h"

// InputSystem
// -----------
// Converts player input into velocity changes.
// This is where "control" lives.
//
class InputSystem
{
public:

    void Update(EntityManager& entities, float dt, const Camera& cam);

};

