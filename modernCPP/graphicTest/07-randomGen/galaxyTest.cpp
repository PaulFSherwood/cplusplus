#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class olcGalaxy : public olc::PixelGameEngine
{
   public:
      olcGalaxy() {
         sAppName = "olcGalaxy";
      }

   public:
      bool OnUserCreate() override {
         return true;
      }

      bool OnUserUpdate(float fElapsedTime) override 
      {

         if (GetKey(olc::Key::SPACE).bReleased) 
         {
            Clear(olc::BLACK);

            auto tp1 = std::chrono::system_clock::now();
            
            for (int x = 0; x < ScreenWidth(); x++) 
            {
               for (int y = 0; y < ScreenHeight(); y++) 
               {
                  bool bIsStar = false;

                  bIsStar = rand() % 256 < 32;

                  Draw(x, y, bIsStar ? olc::WHITE : olc::BLACK);
               }
            }
            auto tp2 = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsedTime = tp2 - tp1;
            DrawString(3, 3, "Time: " + std::to_string(elapsedTime.count()), olc::RED, 2);
         }

         return true;
      }
};

int main() {
   olcGalaxy demo;
   if (demo.Construct(512, 480, 2, 2))
      demo.Start();

   return 0;
}
