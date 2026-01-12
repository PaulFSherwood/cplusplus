#include "InputSystem.h"
#include "../Core/Camera.h"
#include <SDL2/SDL.h>
#include <cmath>

void InputSystem::Update(EntityManager& entities, float dt, const Camera& cam)
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

        // Convert mouse to WORLD space
        float worldMouseX = mouseX + cam.x;
        float worldMouseY = mouseY + cam.y;

        // Rotate ship to face mouse
        float dx = worldMouseX - t.x;
        float dy = worldMouseY - t.y;
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

