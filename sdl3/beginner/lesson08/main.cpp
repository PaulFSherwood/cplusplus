#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

const int windowWidth  = 800;
const int windowHeight = 600;

struct Player
{
   SDL_FRect rect;
   float speed;
};

struct Wall
{
   SDL_FRect rect;
};

bool checkCollision(const SDL_FRect& a, const SDL_FRect& b)
{
   if (a.x + a.w <= b.x)
   {
      return false;
   }
   if (a.x >= b.x + b.w)
   {
      return false;
   }
   if (a.y + a.h <= b.y)
   {
      return false;
   }
   if (a.y >= b.y + b.h)
   {
      return false;
   }
   return true;
}

bool playerHitsAnyWall(const Player& player, const std::vector<Wall>& walls)
{
   for (const Wall& wall : walls)
   {
      if (checkCollision(player.rect, wall.rect))
      {
         return true;
      }
   }

   return false;
}

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
      player.rect.y = windowHeight - player.rect.h;
   }
}

void updatePlayer(Player& player, const std::vector<Wall>& walls, float deltaTime)
{
   // Movement section
   const bool* keyboard = SDL_GetKeyboardState(nullptr);

   float oldX = player.rect.x;
   float oldY = player.rect.y;

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

   if (playerHitsAnyWall(player, walls))
   {
      player.rect.x = oldX;
      player.rect.y = oldY;
   }
}

void drawPlayer(SDL_Renderer* renderer, const Player& player)
{
   SDL_SetRenderDrawColor(renderer, 80, 180, 220, 255);
   SDL_RenderFillRect(renderer, &player.rect);
}

void drawWall(SDL_Renderer* renderer, const Wall& wall)
{
   SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
   SDL_RenderFillRect(renderer, &wall.rect);
}

void render(SDL_Renderer* renderer, const Player& player, const std::vector<Wall>& walls)
{
   // Start rendering to the screen.
   SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
   SDL_RenderClear(renderer);
 
   for (const Wall& wall : walls)
   {
      drawWall(renderer, wall);
   }

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
   player.rect.x =  50.0f;
   player.rect.y =  50.0f;
   player.rect.w =  50.0f;
   player.rect.h =  50.0f;
   player.speed  = 300.0f;

   std::vector<Wall> walls;

   Wall wall1;
   wall1.rect.x = 200.0f;
   wall1.rect.y = 150.0f;
   wall1.rect.w = 300.0f;
   wall1.rect.h =  40.0f;
   walls.push_back(wall1);

   Wall wall2;
   wall2.rect.x = 100.0f;
   wall2.rect.y = 350.0f;
   wall2.rect.w = 500.0f;
   wall2.rect.h =  40.0f;
   walls.push_back(wall2);

   Wall wall3;
   wall3.rect.x = 600.0f;
   wall3.rect.y = 100.0f;
   wall3.rect.w =  40.0f;
   wall3.rect.h = 350.0f;
   walls.push_back(wall3);
 
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
      updatePlayer(player, walls, deltaTime);
      render(renderer, player, walls);
 
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
