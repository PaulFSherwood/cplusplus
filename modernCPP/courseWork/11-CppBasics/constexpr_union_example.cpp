#include <cstdint>
#include <iostream>

union Color32
{
   // Value -> packed integer
   uint32_t value;
   struct 
   {
      // r,g,b,a -> Individual channels
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
   };
};

// Constexpr factory funciton, runs at compile time
constexpr Color32 MakeColor(
      uint8_t r,
      uint8_t g,
      uint8_t b,
      uint8_t a = 255
      )
{
   return Color32 {
      .r = r,
      .g = g,
      .b = b,
      .a = a
   };
}

// compile-time constant
// constexpr requires compile-time evalutation
constexpr Color32 SkyBlue = MakeColor(135, 206, 235);
constexpr Color32 NotSkyBlue = MakeColor(134, 206, 235);
constexpr Color32 SkyBlue1 = MakeColor(135, 205, 235);
constexpr Color32 SkyBlue2 = MakeColor(135, 204, 235);
constexpr Color32 SkyBlue3 = MakeColor(135, 203, 235);
constexpr Color32 SkyBlue4 = MakeColor(135, 206, 234);
constexpr Color32 SkyBlue5 = MakeColor(135, 206, 233);
constexpr Color32 SkyBlue6 = MakeColor(135, 206, 232);

int main()
{
   // Runtime usage
   std::cout << "Packed value: 0x"
             << std::hex << SkyBlue.value << std::dec << "\n";

   std::cout << "R: " << static_cast<int>(SkyBlue.r) << "\n";
   std::cout << "G: " << static_cast<int>(SkyBlue.g) << "\n";
   std::cout << "B: " << static_cast<int>(SkyBlue.b) << "\n";
   std::cout << "A: " << static_cast<int>(SkyBlue.a) << "\n";

   // Runtime usage
   std::cout << "Packed value: 0x"
             << std::hex << NotSkyBlue.value << std::dec << "\n";

   std::cout << "R: " << static_cast<int>(NotSkyBlue.r) << "\n";
   std::cout << "G: " << static_cast<int>(NotSkyBlue.g) << "\n";
   std::cout << "B: " << static_cast<int>(NotSkyBlue.b) << "\n";
   std::cout << "A: " << static_cast<int>(NotSkyBlue.a) << "\n";

   std::cout << "Packed value1: 0x" << std::hex << SkyBlue1.value << std::dec << "\n";
   std::cout << "Packed value2: 0x" << std::hex << SkyBlue2.value << std::dec << "\n";
   std::cout << "Packed value3: 0x" << std::hex << SkyBlue3.value << std::dec << "\n";
   std::cout << "Packed value4: 0x" << std::hex << SkyBlue4.value << std::dec << "\n";
   std::cout << "Packed value5: 0x" << std::hex << SkyBlue5.value << std::dec << "\n";
   std::cout << "Packed value6: 0x" << std::hex << SkyBlue6.value << std::dec << "\n";

   std::cout << "Packed value1: 0x" << std::hex << SkyBlue1.value << std::dec << "\n";
   std::cout << "Packed value3: 0x" << std::hex << SkyBlue3.value << std::dec << "\n";
   return 0;
}
