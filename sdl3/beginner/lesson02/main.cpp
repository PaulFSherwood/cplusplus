#include <SDL3/SDL.h>
#include <iostream>

int main()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
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

  float speed = 5.0f;

  while (running)
  {
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

    const bool* keyboard = SDL_GetKeyboardState(nullptr);

    if (keyboard[SDL_SCANCODE_LEFT])
    {
      box.x -= speed;
    }
    if (keyboard[SDL_SCANCODE_RIGHT])
    {
      box.x += speed;
    }
    if (keyboard[SDL_SCANCODE_UP])
    {
      box.y -= speed;
    }
    if (keyboard[SDL_SCANCODE_DOWN])
    {
      box.y += speed;
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 200, 80, 80, 255);
    SDL_RenderFillRect(renderer, &box);

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
