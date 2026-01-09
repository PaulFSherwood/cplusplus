#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

constexpr uint32_t g_starColours[8] =
{
   0xFFFFFFFF, 0xFFD9FFFF, 0xFFA3FFFF, 0xFFFFC8C8,
   0XFFFFCB9D, 0xFF9F9FFF, 0xFF415EFF, 0xFF28199D
};
constexpr uint32_t g_planetColours[8] =
{
   0xFFE63946,  // Deep Crimson red 
   0xFFF4A261,  // Warm Desert Orange 
   0xFF2A9D8F,  // Teal / Ocean Green
   0xFF457B9D,  // Steel Blue 
   0xFF6A4C93,  // Royal Purple
   0xFF3A86FF,  // Bright Space Blue 
   0xFF52B788,  // Lush Green 
   0xFFFFD166   // Golden Yellow 
};
constexpr uint32_t g_moonColours[4] = 
{
   0xFFD9D9D9,  // Pale Lunar Gray
   0xFFADB5BD,  // Dusty Rock Gray
   0xFF8D99AE,  // Blue-Gray Stone
   0xFF6C757d   // Dark Crater Grey
};
struct sMoon
{
   double diameter         = 0.0;
   // double orbit            = 0.0;
   olc::Pixel moonColour   = olc::WHITE;
};
struct sPlanet
{
   double distance      = 0.0;
   double diameter      = 0.0;
   double foliage       = 0.0;
   double minerals      = 0.0;
   double water         = 0.0;
   double gases         = 0.0;
   double temperature   = 0.0;
   double population    = 0.0;
   bool ring            = false;
   olc::Pixel  planetColour = olc::WHITE;
   // std::vector<double> vMoons;
   std::vector<sMoon> vMoons;
};

inline std::string fmt2(double v)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << v;
    return oss.str();
}

class cStarSystem
{
   public:
   cStarSystem(uint32_t x, uint32_t y, bool bGenerateFullSystem = false)
   {
      nLehmer = (x & 0xFFFF) << 16 | (y & 0xFFFF);

      starExists = (rndInt(0, 20) == 1);
      if (!starExists) return;

      starDiameter   = rndDouble(10.0, 40.0);
      starColour.n   = g_starColours[rndInt(0, 8)];

      if (!bGenerateFullSystem) return;
      double dDistanceFromStar = rndDouble(60.0, 200.0);
      int nPlanets = rndInt(0, 10);
      for (int i = 0; i < nPlanets; i++)
      {
         sPlanet p;
         p.distance        = dDistanceFromStar;
         dDistanceFromStar += rndDouble(20.0, 200.0);
         p.diameter        = rndDouble(4.0, 20.0);
         p.temperature     = rndDouble(-200.0, 300.0);
         p.foliage         = rndDouble(0.0, 1.0);
         p.minerals        = rndDouble(0.0, 1.0);
         p.gases           = rndDouble(0.0, 1.0);
         p.water           = rndDouble(0.0, 1.0);
         p.planetColour    = g_planetColours[rndInt(0, 8)];

         double dSum = 1.0 / (p.foliage + p.minerals + p.gases + p.water);
         p.foliage   *= dSum;
         p.minerals  *= dSum;
         p.gases     *= dSum;
         p.water     *= dSum;

         p.population = std::max(rndInt(-5000000, 20000000), 0);

         p.ring = rndInt(0, 10) == 1;

         int nMoons = std::max(rndInt(-5, 5), 0);
         for (int n = 0; n < nMoons; n++)
         { 
            // Make one sMoon
            sMoon q;
            // Set and package the moons variables
            q.diameter     = rndDouble(1.0, 5.0);
            q.moonColour   =  g_moonColours[rndInt(0, 4)];
            // push the new moon into the vMoon vector
            p.vMoons.push_back(q);
            // move onto the next moon.
         }
         vPlanets.push_back(p);
      }
   }

   public:
      bool        starExists = false;
      double      starDiameter = 0.0f;
      olc::Pixel  starColour = olc::WHITE;
      std::vector<sPlanet> vPlanets;

   private:
      uint32_t nLehmer = 0;
      uint32_t Lehmer32() 
      {
         nLehmer += 0xe120fc15;
         uint64_t tmp;
         tmp = (uint64_t)nLehmer * 0x4a39b70d;
         uint32_t m1 = (tmp >> 32) ^ tmp;
         tmp = (uint64_t)m1 * 0x12fad5c9;
         uint32_t m2 = (tmp >> 32) ^ tmp;
         return m2;
      }

      inline uint32_t Lehmer32(uint32_t& state)
      {
         state += 0xe120fc15;
         uint64_t tmp = (uint64_t)state * 0x4a39b70d;
         uint32_t x = (uint32_t)((tmp >> 32) ^ tmp);
         tmp = (uint64_t)x * 0x12fad5c9;
         return (uint32_t)((tmp >> 32) ^ tmp);
      }

      int rndInt(int min, int max)
      {
         // bIsStar = Lehmer32() % 256 < 32;
         // bIsStar = (Lehmer32(state) & 0xFF) < 32;
         return (Lehmer32() % (max - min)) + min;
      }

      double rndDouble(double min, double max)
      {
         return ((double)Lehmer32() / (double)(0x7FFFFFFF)) * (max - min) + min;
      }
};

class olcGalaxy : public olc::PixelGameEngine
{
   public:
      olcGalaxy() {
         sAppName = "olcGalaxy";
      }

      olc::vf2d vGalaxyOffset = { 0, 0 };
      bool bStarSelected = false;
      olc::vi2d vStarSelected = { 0, 0};

   public:
      bool OnUserCreate() override {
         return true;
      }

      bool OnUserUpdate(float fElapsedTime) override 
      {
         if (GetKey(olc::Key::W).bHeld) vGalaxyOffset.y -= 50.0f * fElapsedTime;
         if (GetKey(olc::Key::S).bHeld) vGalaxyOffset.y += 50.0f * fElapsedTime;
         if (GetKey(olc::Key::A).bHeld) vGalaxyOffset.x -= 50.0f * fElapsedTime;
         if (GetKey(olc::Key::D).bHeld) vGalaxyOffset.x += 50.0f * fElapsedTime;


         Clear(olc::BLACK);

         int nSectorsX = ScreenWidth() / 16;
         int nSectorsY = ScreenHeight() / 16;

         olc::vi2d mouse = { GetMouseX() / 16, GetMouseY() / 16 };
         olc::vi2d galaxy_mouse = mouse + vGalaxyOffset;
         olc::vi2d screen_sector = { 0,0 };

         for (screen_sector.x = 0; screen_sector.x < nSectorsX; screen_sector.x++)
            for (screen_sector.y = 0; screen_sector.y < nSectorsY; screen_sector.y++)
            {
               cStarSystem star(
                  screen_sector.x + (uint32_t)vGalaxyOffset.x, 
                  screen_sector.y + (uint32_t)vGalaxyOffset.y
               );

               if (star.starExists)
               {
                  FillCircle(
                     screen_sector.x * 16 + 8, 
                     screen_sector.y * 16 + 8,
                     (int)star.starDiameter / 8, 
                     star.starColour
                  );

                  if (mouse.x == screen_sector.x && mouse.y == screen_sector.y)
                  {
                     DrawCircle(screen_sector.x * 16 + 8, screen_sector.y * 16 + 8, 12, olc::YELLOW);
                  }
               }
            }
         // === Handle left mouse button ===
         if (GetMouse(0).bPressed)
         {
            cStarSystem star(galaxy_mouse.x, galaxy_mouse.y);
            if (star.starExists)
            {
               bStarSelected = true;
               vStarSelected = galaxy_mouse;
            }
            else
               bStarSelected = false;
         }
         // === Draw system ===
         if (bStarSelected)
         {
            cStarSystem star(vStarSelected.x, vStarSelected.y, true);

            // Draw Window
            FillRect(8, 240, 496, 232, olc::DARK_BLUE);
            DrawRect(8, 240, 496, 232, olc::WHITE);

            // Draw Star
            olc::vi2d vBody = { 14, 356 };
            vBody.x += star.starDiameter * 1.375;
            FillCircle(vBody, (int)(star.starDiameter * 1.375), star.starColour);
            vBody.x += (star.starDiameter * 1.375) + 8;

            // Draw Planets
            int line = 2;
            for (auto& planet : star.vPlanets)
            {
               if (vBody.x + planet.diameter >= 496) break;

               vBody.x += planet.diameter;
               FillCircle(vBody, (int)(planet.diameter * 1.0), planet.planetColour);

               olc::vi2d vMoon = vBody;
               vMoon.y += planet.diameter + 10;

               // Draw Moons
               for (auto& moon : planet.vMoons)
               {
                  vMoon.y += moon.diameter;
                  FillCircle(vMoon, (int)(moon.diameter * 1.0), moon.moonColour);
                  vMoon.y += moon.diameter + 10;
               }

               vBody.x += planet.diameter + 8;

               DrawString(150, line, 
                  
                     "Diameter: " + fmt2(planet.diameter) + "\n" 
                     "Temperature: " + fmt2(planet.temperature),
                     olc::YELLOW
               );
               line += 20;
            }
         }
         // === HUD ===
         DrawString(2, 2,
            "X: " + std::to_string((int)vGalaxyOffset.x) +
            " Y: " + std::to_string((int)vGalaxyOffset.y),
            olc::YELLOW
         );
         return true;
      }
};

int main() {
   olcGalaxy demo;
   if (demo.Construct(512, 480, 2, 2))
      demo.Start();

   return 0;
}
