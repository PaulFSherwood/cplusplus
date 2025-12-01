#include <print>    // Improved version of printf.

int main() {
   int    a   =       4;
   double b   =     3.0;
   char c[]   = "hello";

   std::print("Hello World!\n");

   std::print("Hello World!\n{}, {}, {}, {}\n", a, b, c, "Hey Paul");

   return 0;
}
