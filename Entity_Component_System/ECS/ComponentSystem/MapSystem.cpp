#include "MapSystem.h"
#include <string>

MapSystem::MapSystem()
{
    const char* raw[] = {
        "11111111111111111111111111111111111111111111111111",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "10000000000000000000024200000000000000000000000001",
        "10000000000000000000211120000000000000000000000001",
        "10000000022222222222211122220000000000000000000001",
        "11111111111111111111111111111111111111111111111111"
    };

    for (auto& row : raw)
    {
        std::vector<int> line;
        for (char c : std::string(row))
            line.push_back(c - '0');
        m_Map.push_back(line);
    }
}

void MapSystem::Render(SDL_Renderer* renderer)
{
    for (int y = 0; y < (int)m_Map.size(); ++y)
    {
        for (int x = 0; x < (int)m_Map[y].size(); ++x)
        {
            int tile = m_Map[y][x];
            if (tile == 0) continue;

            SDL_Rect r{
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

            if (tile == 1)
                SDL_SetRenderDrawColor(renderer, 120, 80, 40, 255); // wall
            else if (tile == 2 || tile == 4)
                SDL_SetRenderDrawColor(renderer, 50, 180, 50, 255); // landing

            SDL_RenderFillRect(renderer, &r);
        }
    }
}

bool MapSystem::IsSolidAt(float x, float y) const
{
    int tx = x / TILE_SIZE;
    int ty = y / TILE_SIZE;

    if (ty < 0 || ty >= (int)m_Map.size()) return true;
    if (tx < 0 || tx >= (int)m_Map[0].size()) return true;

    return m_Map[ty][tx] == 1;
}

bool MapSystem::IsLandingAt(float x, float y) const
{
    int tx = x / TILE_SIZE;
    int ty = y / TILE_SIZE;

    if (ty < 0 || ty >= (int)m_Map.size()) return false;
    if (tx < 0 || tx >= (int)m_Map[0].size()) return false;

    return m_Map[ty][tx] == 2 || m_Map[ty][tx] == 4;
}

bool MapSystem::FindPlayerStart(float& outX, float& outY) const
{
    for (int y = 0; y < (int)m_Map.size(); ++y)
    {
        for (int x = 0; x < (int)m_Map[y].size(); ++x)
        {
            if (m_Map[y][x] == 4)
            {
                outX = x * TILE_SIZE + TILE_SIZE / 2.0f;
                outY = y * TILE_SIZE + TILE_SIZE / 2.0f;
                return true;
            }
        }
    }
    return false;
}

