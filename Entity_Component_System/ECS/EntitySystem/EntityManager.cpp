#include "EntityManager.h"

Entity EntityManager::CreateEntity()
{
    Entity e{m_NextID++};
    m_Entities.push_back(e);
    return e;
}

void EntityManager::AddTransform(Entity e)
{
    m_Transforms[e.id] = {};
}

void EntityManager::AddVelocity(Entity e)
{
    m_Velocities[e.id] = {};
}

void EntityManager::AddRenderable(Entity e)
{
    m_Renderables[e.id] = {};
}

bool EntityManager::HasTransform(Entity e) const
{
    return m_Transforms.count(e.id) != 0;
}

bool EntityManager::HasVelocity(Entity e) const
{
    return m_Velocities.count(e.id) != 0;
}

bool EntityManager::HasRenderable(Entity e) const
{
    return m_Renderables.count(e.id) != 0;
}

TransformComponent& EntityManager::GetTransform(Entity e)
{
    return m_Transforms.at(e.id);
}

VelocityComponent& EntityManager::GetVelocity(Entity e)
{
    return m_Velocities.at(e.id);
}

Renderable& EntityManager::GetRenderable(Entity e)
{
    return m_Renderables.at(e.id);
}
void EntityManager::AddCollider(Entity e)
{
    m_Colliders[e.id] = {};
}

bool EntityManager::HasCollider(Entity e) const
{
    return m_Colliders.count(e.id) != 0;
}

ColliderComponent& EntityManager::GetCollider(Entity e)
{
    return m_Colliders.at(e.id);
}
void EntityManager::AddGravity(Entity e)
{
    m_Gravity[e.id] = {};
}

void EntityManager::RemoveGravity(Entity e)
{
    m_Gravity.erase(e.id);
}

bool EntityManager::HasGravity(Entity e) const
{
    return m_Gravity.count(e.id) != 0;
}

GravityComponent& EntityManager::GetGravity(Entity e)
{
    return m_Gravity.at(e.id);
}

