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
    auto ship = m_Entities->CreateEntity();
    m_Entities->AddTransform(ship);
    m_Entities->AddVelocity(ship);
    m_Entities->AddRenderable(ship);
    m_Entities->AddCollider(ship);
    m_Entities->AddGravity(ship);

    float startX, startY;
    if (m_Map.FindPlayerStart(startX, startY))
    {
        auto& t = m_Entities->GetTransform(ship);
        auto& c = m_Entities->GetCollider(ship);
        // Place the ship ABOVE the landing tile
        t.x = startX;
        t.y = startY - c.height / 2.0f;
    
        // Start landed → no gravity
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

        input.Update(*m_Entities, dt);
        movement.Update(*m_Entities, dt);
        collision.Update(*m_Entities, m_Map);

        SDL_SetRenderDrawColor(m_Renderer, 15, 15, 20, 255);
        SDL_RenderClear(m_Renderer);

        m_Map.Render(m_Renderer);
        render.Render(*m_Entities, m_Renderer);

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

