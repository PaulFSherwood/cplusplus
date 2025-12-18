#include <iostream>

// auto square(auto x) {
//    return x*x;
// }
template <typename T>
T square(T input) {
   return input * input;
}

int main() {

   std::cout << square(6) << std::endl;
   std::cout << square(5.5) << std::endl;
   std::cout << square(6.6f) << std::endl;
   return 0;
}

