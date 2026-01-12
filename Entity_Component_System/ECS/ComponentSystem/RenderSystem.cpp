#include "RenderSystem.h"
#include <cmath>

void RenderSystem::Render(EntityManager& entities, SDL_Renderer* renderer)
{
    for (auto e : entities.GetEntities())
    {
        if (!entities.HasTransform(e) || !entities.HasRenderable(e))
            continue;

        auto& t = entities.GetTransform(e);
        auto& r = entities.GetRenderable(e);

        SDL_Rect rect{
            static_cast<int>(t.x - r.width / 2),
            static_cast<int>(t.y - r.height / 2),
            r.width,
            r.height
        };

        SDL_SetRenderDrawColor(renderer, r.color.r, r.color.g, r.color.b, r.color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

