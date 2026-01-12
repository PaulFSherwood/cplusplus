#pragma once

#include <SDL2/SDL.h>

// Renderable
// ----------
// Minimal visual representation.
// For now: just a colored rectangle.
//
struct Renderable
{
    int width{20};
    int height{10};
    SDL_Color color{255, 255, 255, 255};
};

