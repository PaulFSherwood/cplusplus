#pragma once

#include "../EntitySystem/EntityManager.h"
#include "../Core/Camera.h"
#include <SDL2/SDL.h>

class RenderSystem
{
public:

    void Render(EntityManager& entities, SDL_Renderer* renderer, const Camera& cam);

};

