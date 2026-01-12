#include "MovementSystem.h"

// void MovementSystem::Update(EntityManager& entities, float dt)
// {
//     const float GRAVITY = 120.0f; // pixels/sec² (tweakable)
// 
//     for (auto e : entities.GetEntities())
//     {
//         if (!entities.HasTransform(e) || !entities.HasVelocity(e))
//             continue;
// 
//         auto& t = entities.GetTransform(e);
//         auto& v = entities.GetVelocity(e);
// 
//         // gravity pulls down
//         v.vy += GRAVITY * dt;
// 
//         t.x += v.vx * dt;
//         t.y += v.vy * dt;
//     }
// }

void MovementSystem::Update(EntityManager& entities, float dt)
{
    for (auto e : entities.GetEntities())
    {
        if (!entities.HasTransform(e) || !entities.HasVelocity(e))
            continue;

        auto& t = entities.GetTransform(e);
        auto& v = entities.GetVelocity(e);

        // Apply gravity only if entity has GravityComponent
        if (entities.HasGravity(e))
        {
            auto& g = entities.GetGravity(e);
            v.vy += g.strength * dt;
        }

        t.x += v.vx * dt;
        t.y += v.vy * dt;
    }
}

