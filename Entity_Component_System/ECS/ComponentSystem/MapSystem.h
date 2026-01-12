#pragma once
#include <vector>
#include <SDL2/SDL.h>

class MapSystem
{
public:
    static constexpr int TILE_SIZE = 32;

    MapSystem();

    void Render(SDL_Renderer* renderer);
    bool IsSolidAt(float x, float y) const;
    bool IsLandingAt(float x, float y) const;
    bool FindPlayerStart(float& outX, float& outY) const;

private:
    std::vector<std::vector<int>> m_Map;
};

