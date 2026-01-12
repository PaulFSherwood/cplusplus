#pragma once
#include "../Core/Camera.h"

#include <vector>
#include <SDL2/SDL.h>

class MapSystem
{
public:
    static constexpr int TILE_SIZE = 32;
    void Render(SDL_Renderer* renderer, const Camera& cam);

    MapSystem();

    bool IsSolidAt(float x, float y) const;
    bool IsLandingAt(float x, float y) const;
    bool FindPlayerStart(float& outX, float& outY) const;

    int GetTileAt(float x, float y) const;

private:
    std::vector<std::vector<int>> m_Map;
};

