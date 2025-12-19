#include <iostream>
#include <cstdarg>

template <typename T>
T Sum(T arg) {
   return arg;
}
template <typename T, typename... Args>
T Sum(T start, Args... args) {
   return start + Sum(args...);
}

int main() {

   // simple_printf("dcff", 3, 'a', 1.999, 42.5);
   std::cout << Sum<double>(1,2.2,3.56f,4) << std::endl;

   return 0;
}


// Test from cppreference.com
/*
void simple_printf(const char* fmt...) {
   va_list args;
   va_start(args, fmt);

   while (*fmt != '\0') {
      if (*fmt == 'd') {
         int i = va_arg(args, int);
      } else if (*fmt == 'c'){
         // Note automatic conversion to integral type
         int c = va_arg(args, int);
         std::cout << static_cast<char>(c) << '\n';
      } else if (*fmt == 'f') {
         double d = va_arg(args, double);
         std::cout << d << '\n';
      }
      ++fmt;
   }
   va_end(args);
}
*/
