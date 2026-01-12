#include "InputSystem.h"
#include <SDL2/SDL.h>
#include <cmath>

void InputSystem::Update(EntityManager& entities, float dt)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    for (auto e : entities.GetEntities())
    {
        if (!entities.HasTransform(e) || !entities.HasVelocity(e))
            continue;

        auto& t = entities.GetTransform(e);
        auto& v = entities.GetVelocity(e);

        // Rotate ship to face mouse
        float dx = mouseX - t.x;
        float dy = mouseY - t.y;
        t.rotation = std::atan2(dy, dx);

        // Thrust
        const float thrust = 200.0f;

        if (keys[SDL_SCANCODE_W])
        {
            if (!entities.HasGravity(e)) 
            {
                entities.AddGravity(e);
            }
            v.vx += std::cos(t.rotation) * thrust * dt;
            v.vy += std::sin(t.rotation) * thrust * dt;
        }
        if (keys[SDL_SCANCODE_S])
        {
            v.vx *= 0.98f;
            v.vy *= 0.98f;
        }
    }
}

