#include "RenderSystem.h"
#include <cmath>

void RenderSystem::Render(EntityManager& entities, SDL_Renderer* renderer, const Camera& cam)
{
    for (auto e : entities.GetEntities())
    {
        if (!entities.HasTransform(e) || !entities.HasRenderable(e))
            continue;

        auto& t = entities.GetTransform(e);
        auto& r = entities.GetRenderable(e);

        SDL_Rect rect{
            (int)(t.x - r.width / 2 - cam.x),
            (int)(t.y - r.height / 2 - cam.y),
            r.width,
            r.height
        };

        SDL_SetRenderDrawColor(renderer, r.color.r, r.color.g, r.color.b, r.color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

