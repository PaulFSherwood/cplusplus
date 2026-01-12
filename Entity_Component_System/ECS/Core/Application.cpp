#include "Application.h"
#include "../EntitySystem/EntityManager.h"
#include "../ComponentSystem/InputSystem.h"
#include "../ComponentSystem/MovementSystem.h"
#include "../ComponentSystem/RenderSystem.h"
#include "../ComponentSystem/MapSystem.h"
#include "../ComponentSystem/CollisionSystem.h"

Application::~Application() = default;

bool Application::Init()
{
    SDL_Init(SDL_INIT_VIDEO);

    m_Window = SDL_CreateWindow(
        "Sub-Terrania Flight Demo (Phase 1)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    m_Entities = std::make_unique<EntityManager>();

    // Create player ship
    m_Player = m_Entities->CreateEntity();
    auto ship = m_Player;
    m_Entities->AddTransform(ship);
    m_Entities->AddVelocity(ship);
    m_Entities->AddRenderable(ship);
    m_Entities->AddCollider(ship);
    m_Entities->AddGravity(ship);

    m_Levels.emplace_back(); // Level 0
    m_Levels.emplace_back(); // Level 1 (later different map)

    m_Map = m_Levels[m_CurrentLevel];

    float startX, startY;
    if (m_Map.FindPlayerStart(startX, startY))
    {
        auto& t = m_Entities->GetTransform(ship);
        // auto& c = m_Entities->GetCollider(ship);
    
        // Place ship ABOVE the landing tile
        t.x = startX;
        t.y = startY;// - c.height / 2.0f;
    
        // Start landed
        m_Entities->RemoveGravity(ship);
    }

    return true;
}

void Application::Run()
{
    InputSystem input;
    MovementSystem movement;
    RenderSystem render;
    CollisionSystem collision;

    const float dt = 1.0f / 60.0f;

    while (m_Running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                m_Running = false;
        }

        input.Update(*m_Entities, dt, m_Camera);
        movement.Update(*m_Entities, dt);
        collision.Update(*m_Entities, m_Map);

        auto& t = m_Entities->GetTransform(m_Player);
        m_Camera.x = t.x - 400; // half of 800
        m_Camera.y = t.y - 300; // half of 600

        // if (!m_Entities->HasGravity(m_Player))
        // {
        //     m_CurrentLevel = (m_CurrentLevel + 1) % m_Levels.size();
        //     m_Map = m_Levels[m_CurrentLevel];
        // 
        //     float sx, sy;
        //     if (m_Map.FindPlayerStart(sx, sy))
        //     {
        //         auto& t = m_Entities->GetTransform(m_Player);
        //         auto& c = m_Entities->GetCollider(m_Player);
        //         auto& v = m_Entities->GetVelocity(m_Player);
        // 
        //         t.x = sx;
        //         t.y = sy - c.height / 2.0f;
        // 
        //         v.vx = v.vy = 0.0f;
        //     }
        // }
        int tile = m_Map.GetTileAt(t.x, t.y);

        if (m_Entities->HasGravity(m_Player))
        {
            auto& g = m_Entities->GetGravity(m_Player);
        
            switch (tile)
            {
                case 3: // water (blue)
                    g.strength = -40.0f;
                    break;
        
                case 0: // normal space / air
                case 2: // green
                case 4: // start
                    g.strength = 120.0f;
                    break;
        
                default:
                    g.strength = 120.0f;
                    break;
            }
        }


        SDL_SetRenderDrawColor(m_Renderer, 15, 15, 20, 255);
        SDL_RenderClear(m_Renderer);

        m_Map.Render(m_Renderer, m_Camera);
        render.Render(*m_Entities, m_Renderer, m_Camera);

        SDL_RenderPresent(m_Renderer);
        SDL_Delay(16);
    }
}

void Application::Shutdown()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

