#include <SDL3/SDL.h>
#include <iostream>

int main()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow(
      "SDL3 Lesson 1 = Keyboard Movement",
      800,
      600,
      0
      );

  if (window == nullptr)
  {
    std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

  if (renderer == nullptr)
  {
    std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  bool running = true;

  SDL_FRect box;
  box.x = 350.0f;
  box.y = 250.0f;
  box.w = 100.0f;
  box.h = 100.0f;

  const float speed = 300.0f; // pixesl persecond

  const int targetFPS = 60;
  const Uint64 frameDelayMS = 1000 / targetFPS;

  Uint64 previousTime = SDL_GetTicks();

  while (running)
  {
    Uint64 frameStart = SDL_GetTicks();

    float deltaTime = (frameStart - previousTime) / 1000.0f;
    previousTime = frameStart;

    // Watching for events from the user.
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        running = false;
      }

      if (event.type == SDL_EVENT_KEY_DOWN)
      {
        if (event.key.key == SDLK_ESCAPE)
        {
          running = false;
        }
      }
    }

    // Movement section
    const bool* keyboard = SDL_GetKeyboardState(nullptr);

    if (keyboard[SDL_SCANCODE_LEFT])
    {
      box.x -= speed * deltaTime;
    }
    if (keyboard[SDL_SCANCODE_RIGHT])
    {
      box.x += speed * deltaTime;
    }
    if (keyboard[SDL_SCANCODE_UP])
    {
      box.y -= speed * deltaTime;
    }
    if (keyboard[SDL_SCANCODE_DOWN])
    {
      box.y += speed * deltaTime;
    }

    // Start rendering to the screen.
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 80, 180, 220, 255);
    SDL_RenderFillRect(renderer, &box);

    SDL_RenderPresent(renderer);

    Uint64 frameEnd = SDL_GetTicks();
    Uint64 frameTime = frameEnd - frameStart;

    if (frameTime < frameDelayMS)
    {
      SDL_Delay(frameDelayMS - frameTime);
    }

    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
