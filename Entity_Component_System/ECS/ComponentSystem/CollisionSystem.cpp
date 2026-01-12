#include "CollisionSystem.h"
#include <cmath>

// void CollisionSystem::Update(EntityManager& entities, MapSystem& map)
// {
//     for (auto e : entities.GetEntities())
//     {
//         if (!entities.HasTransform(e) || !entities.HasCollider(e))
//             continue;
// 
//         auto& t = entities.GetTransform(e);
// 
//         if (map.IsSolidAt(t.x, t.y))
//         {
//             // Crash → reset
//             t.x = 400;
//             t.y = 300;
// 
//             if (entities.HasVelocity(e))
//             {
//                 auto& v = entities.GetVelocity(e);
//                 v.vx = v.vy = 0.0f;
//             }
//         }
//     }
// }


void CollisionSystem::Update(EntityManager& entities, MapSystem& map)
{
    const float MAX_LANDING_SPEED = 60.0f; // safe vertical speed

    for (auto e : entities.GetEntities())
    {
        if (!entities.HasTransform(e) || !entities.HasCollider(e))
            continue;

        auto& t = entities.GetTransform(e);

        // solid wall = crash
        if (map.IsSolidAt(t.x, t.y))
        {
            t.x = 400;
            t.y = 300;

            if (entities.HasVelocity(e))
            {
                auto& v = entities.GetVelocity(e);
                v.vx = 0.0f;
                v.vy = 0.0f;
            }
            continue;
        }

        // landing zone
        if (map.IsLandingAt(t.x, t.y) && entities.HasVelocity(e))
        {
            auto& v = entities.GetVelocity(e);
            auto& c = entities.GetCollider(e);
        
            // bottom of ship
            float shipBottom = t.y + c.height / 2.0f;
        
            // top of tile
            float tileTop =
                (int(t.y / MapSystem::TILE_SIZE)) * MapSystem::TILE_SIZE;
        
            // Safe landing
            if (std::abs(v.vy) <= MAX_LANDING_SPEED)
            {
                // Snap ship on top of the tile (no overlap)
                t.y = tileTop - c.height / 2.0f;
        
                v.vx = 0.0f;
                v.vy = 0.0f;
        
                entities.RemoveGravity(e);
            }
            else
            {
                // Too fast → crash
                t.x = 400;
                t.y = 300;
                v.vx = 0.0f;
                v.vy = 0.0f;
            }
        }

    }
}

