#pragma once
#include "../EntitySystem/EntityManager.h"
#include "../ComponentSystem/MapSystem.h"
#include "Camera.h"

#include <SDL2/SDL.h>
#include <memory>

class EntityManager; // forward declaration is OK

class Application
{
public:
    Application() = default;
    ~Application();

    bool Init();
    void Run();
    void Shutdown();

private:
    SDL_Window* m_Window{nullptr};
    SDL_Renderer* m_Renderer{nullptr};
    bool m_Running{true};
    MapSystem m_Map;
    Entity m_Player;
    Camera m_Camera;

    int m_CurrentLevel{0};
    std::unique_ptr<EntityManager> m_Entities;
    std::vector<MapSystem> m_Levels;
};

