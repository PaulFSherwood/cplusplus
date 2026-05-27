#include <SDL3/SDL.h>
#include <iostream>

const int windowWidth  = 800;
const int windowHeight = 600;

struct Player
{
   SDL_FRect rect;
   float speed;
};

void handleEvents(bool& running)
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
}

void clampPlayerToWindow(Player& player)
{
   if (player.rect.x < 0)
   {
      player.rect.x = 0;
   }
   if (player.rect.y < 0)
   {
      player.rect.y = 0;
   }
   if (player.rect.x + player.rect.w > windowWidth)
   {
      player.rect.x = windowWidth - player.rect.w;
   }
   if (player.rect.y + player.rect.h > windowHeight)
   {
      player.rect.y = windowWidth - player.rect.h;
   }
}

void updatePlayer(Player& player, float deltaTime)
{
  // Movement section
  const bool* keyboard = SDL_GetKeyboardState(nullptr);

  if (keyboard[SDL_SCANCODE_LEFT])
  {
    player.rect.x -= player.speed * deltaTime;
  }
  if (keyboard[SDL_SCANCODE_RIGHT])
  {
    player.rect.x += player.speed * deltaTime;
  }
  if (keyboard[SDL_SCANCODE_UP])
  {
    player.rect.y -= player.speed * deltaTime;
  }
  if (keyboard[SDL_SCANCODE_DOWN])
  {
    player.rect.y += player.speed * deltaTime;
  }
  clampPlayerToWindow(player);
}

void drawPlayer(SDL_Renderer* renderer, const Player& player)
{
  SDL_SetRenderDrawColor(renderer, 80, 180, 220, 255);
  SDL_RenderFillRect(renderer, &player.rect);
}

void render(SDL_Renderer* renderer, const Player& player)
{
  // Start rendering to the screen.
  SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
  SDL_RenderClear(renderer);

  drawPlayer(renderer, player);
  
  SDL_RenderPresent(renderer);
}

int main()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow(
      "SDL3 Lesson 6 = Player Struct",
      windowWidth,
      windowHeight,
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

  Player player;
  player.rect.x = 350.0f;
  player.rect.y = 250.0f;
  player.rect.w = 100.0f;
  player.rect.h = 100.0f;
  player.speed  = 300.0f;

  bool running = true;

  const int targetFPS = 60;
  const Uint64 frameDelayMS = 1000 / targetFPS;

  Uint64 previousTime = SDL_GetTicks();

  while (running)
  {
    Uint64 frameStart = SDL_GetTicks();

    float deltaTime = (frameStart - previousTime) / 1000.0f;
    previousTime = frameStart;

    handleEvents(running);
    updatePlayer(player, deltaTime);
    render(renderer, player);

    Uint64 frameEnd = SDL_GetTicks();
    Uint64 frameTime = frameEnd - frameStart;

    if (frameTime < frameDelayMS)
    {
      SDL_Delay(frameDelayMS - frameTime);
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
