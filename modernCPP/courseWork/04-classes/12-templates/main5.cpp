#include <iostream>

template<typename T>
T Sum(T arg) {
   return arg;
}

template<typename T, typename... Args>
T Sum(T start, Args... args) {
   return start + Sum(args...);
}

int main() {

   std::cout << Sum(1,2,3,4,5) << std::endl;
   std::cout << Sum<double, double>(1,2.7,3.5,4,5) << std::endl;

   return 0;
}
