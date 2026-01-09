/**********************************************************
 * Platformer Beat-'Em-Up Example
 * Engine: Raylib
 * ECS: flecs
 *
 * This example intentionally favors clarity over performace
 *********************************************************/


/**********************************************************
 * COMPILE:
 * g++ main.cpp -o program -std=c++17 -lraylib -lflecs -lm -lpthread -ldl -ltr -lX11
 *********************************************************/
#include <raylib.h>
#include <flecs.h>
#include <cmath>


/**********************************************************
 * COMPONENT DEFINITIONS
 *********************************************************/

// Position in world space
struct Position {
   float x;
   float y;
};

// Velocity for movement & gravity
struct Velocity {
   float x;
   float y;
};

// Rectangle size for collision & drawing
struct Size {
   float w;
   float h;
};

// Marks an entity as affect by gravity
struct Gravity {};

// Marks entity as player-controlled
struct Player {};

// Marks entity as an enemy
struct Enemy {};

// Health component for combat
struct Health {
   int hp;
};

// Simple attack state
struct Attack {
   bool active;
   float timer;
};

// Static Platform 
struct Platform {};

/**********************************************************
 * CONSTANTS
 *********************************************************/

constexpr float GRAVITY_FORCE = 1200.0f;
constexpr float MOVE_SPEED  = 300.0f;
constexpr float JUMP_FORCE = 500.0f;
constexpr float ATTACK_TIME = 0.15f;

/**********************************************************
 * HEALPER FUNCTIONS
 *********************************************************/

static bool RectsOverlap(
      float ax, float ay, float aw, float ah,
      float bx, float by, float bw, float bh)
{
   return ax < bx + bw &&
          ax + aw > bx &&
          ay < by + bh &&
          ay + ah > by;
}

/**********************************************************
 * MAIN
 *********************************************************/

int main() 
{
   /**********************************************************
    * RAYLIB INIT
    *********************************************************/
   InitWindow(1000, 600, "flecs + Raylib Beat 'Em Up");
   SetTargetFPS(60);

   /**********************************************************
    * ECS WORLD
    *********************************************************/
   flecs::world ecs;

   /**********************************************************
    * SYSTEM: GRAVITY 
    *********************************************************/
   ecs.system<Velocity, Gravity>()
      .each([](Velocity& v) {
            v.y += GRAVITY_FORCE * GetFrameTime();
      });

   /**********************************************************
    * SYSTEM: PLAYER INPUT
    *********************************************************/
   ecs.system<Velocity, Attack, const Player>()
      .each([](Velocity& v, Attack& atk, const Player&) {
            v.x = 0;

            if (IsKeyDown(KEY_A)) v.x = -MOVE_SPEED;
            if (IsKeyDown(KEY_D)) v.x = MOVE_SPEED;
               
            if (IsKeyPressed(KEY_SPACE)) {
               v.y = -JUMP_FORCE;
            }

            if (IsKeyPressed(KEY_J)) {
               atk.active = true;
               atk.timer = ATTACK_TIME;
            }
      });

   /**********************************************************
    * SYSTEM: ATTACK TIMER
    *********************************************************/
   ecs.system<Attack>()
      .each([](Attack& atk) {
            if (!atk.active) return;
            atk.timer -= GetFrameTime();
            if (atk.timer <= 0) atk.active = false;
      });

   /**********************************************************
    * SYSTEM: MOVEMENT 
    *********************************************************/
   ecs.system<Position, Velocity>()
      .each([](Position& p, Velocity& v) {
            p.x += v.x * GetFrameTime();
            p.y += v.y * GetFrameTime();
      });

   /**********************************************************
    * SYSTEM: PLATFORM COLLISION
    *********************************************************/ 
   ecs.system<Position, Velocity, Size>()
      .with<Platform>()
      .each([](Position& p, Velocity& v, Size& s) {
            if (p.y + s.h > 520) {
            p.y = 520 - s.h;
            v.y = 0;
            }
      });

   /**********************************************************
    * SYSTEM: COMBAT (PLAYER -> ENEMY)
    *********************************************************/ 
   ecs.system<Position, Size, Attack, const Player>()
         .each([&](Position& p, Size& s, Attack& atk, const Player&) {
            if (!atk.active) return;

            ecs.each<Position, Size, Health, Enemy>(
                  [&](Position& ep, Size& es, Health& hp, Enemy&) {
                  if (RectsOverlap(
                           p.x + s.w, p.y + 10, 30, s.h - 20,
                           ep.x, ep.y, es.w, es.h))
                  {
                     hp.hp -= 1;
                     ep.x += 40; // Knockback
                  }
            });
         });

   /**********************************************************
    * SYSTEM: DRAWING
    *********************************************************/ 
   ecs.system<Position, Size>()
      .each([](Position& p, Size& s) {
         DrawRectangle(p.x, p.y, s.w, s.h, BLUE);
      });

   ecs.system<Position, Size, Enemy>()
      .each([](Position& p, Size& s, Enemy&) {
            DrawRectangle(p.x, p.y, s.w, s.h, RED);
      });
 
   ecs.system<Position, Size, Platform>()
      .each([](Position& p, Size& s, Plaform&) {
            DrawRectangle(p.x, p.y, s.w, s.h, DARKGRAY);
      });

   /**********************************************************
    * ENTITY CREATION 
    *********************************************************/ 

   // Player
   ecs.entity("Player")
      .add<Player>()
      .add<Gravity>()
      .add<Position>({100, 300})
      .add<Velocity>({0, 0})
      .add<Size>({40, 80})
      .add<Attack>({false, 0})
      .add<Health>({10});

   // Enemy
   ecs.entity("Enemy")
      .add<Enemy>()
      .add<Gravity>()
      .add<Position>({500, 300})
      .add<Velocity>({0, 0})
      .add<Size>({40, 80})
      .add<Health>({5});

   // Platform
   ecs.entity("Ground")
      .add<Ground>()
      .add<Position>({0, 520})
      .set<Size>({1000, 80});

   /**********************************************************
    * GAME LOOP
    *********************************************************/ 
   while (!WindowShouldClose())
   {
      BegineDrawing();
      ClearBackground(RAYWHITE);

      ecs.progress(GetFrameTime());

      DrawText("A/D = Move SPACE = Jump  J = Attack",
            20, 20, 20, DARKGRAY);
      EndDrawing();
   }
   CloseWindow();
   
   return 0;
}
