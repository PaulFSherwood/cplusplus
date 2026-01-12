#pragma once

#include "Entity.h"
#include "../Components/TransformComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/Renderable.h"
#include "../Components/GravityComponent.h"
#include "EntitySystemTypes.h"

#include <unordered_map>
#include <vector>

// EntityManager
// -------------
// Owns:
// - entity creation
// - component storage
//
// This is intentionally naïve for teaching.
//
class EntityManager
{
public:
    Entity CreateEntity();

    // Component attachment
    void AddTransform(Entity e);
    void AddVelocity(Entity e);
    void AddRenderable(Entity e);

    // Collision
    void AddCollider(Entity e);
    bool HasCollider(Entity e) const;
    ColliderComponent& GetCollider(Entity e);

    // Gravity Component
    void AddGravity(Entity e);
    void RemoveGravity(Entity e);
    bool HasGravity(Entity e) const;
    GravityComponent& GetGravity(Entity e);

    // Component queries
    bool HasTransform(Entity e) const;
    bool HasVelocity(Entity e) const;
    bool HasRenderable(Entity e) const;

    // Component access
    TransformComponent& GetTransform(Entity e);
    VelocityComponent& GetVelocity(Entity e);
    Renderable& GetRenderable(Entity e);

    const std::vector<Entity>& GetEntities() const { return m_Entities; }

private:
    EntityID m_NextID{1};
    std::vector<Entity> m_Entities;

    std::unordered_map<EntityID, TransformComponent> m_Transforms;
    std::unordered_map<EntityID, VelocityComponent> m_Velocities;
    std::unordered_map<EntityID, Renderable> m_Renderables;
    std::unordered_map<EntityID, ColliderComponent> m_Colliders;
    std::unordered_map<EntityID, GravityComponent> m_Gravity;

};

