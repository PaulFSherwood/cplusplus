#include "MovementSystem.h"

void MovementSystem::Update(EntityManager& entities, float dt)
{
    for (auto e : entities.GetEntities())
    {
        if (!entities.HasTransform(e) || !entities.HasVelocity(e))
            continue;

        auto& t = entities.GetTransform(e);
        auto& v = entities.GetVelocity(e);

        t.x += v.vx * dt;
        t.y += v.vy * dt;
    }
}

