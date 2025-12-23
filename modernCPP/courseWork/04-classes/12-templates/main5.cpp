#include <iostream>

template<typename T>
T Sum(T arg) {
   return arg;
}

template<typename T, typename... Args>
T Sum(T start, Args... args) {
    std::cout << "Args left: " << sizeof...(Args) << "\n";
   return start + Sum(args...);
}

template<typename T>
T Multiply(T num) {
    return num;
}

template<typename T, typename... Args>
T Multiply(T start, Args... args) {
    return start * Multiply(args...);
}

int main() {

   std::cout << Sum(1,2,3,4,5) << std::endl;
   std::cout << Sum<double, double>(1,2.7,3.5,4,5) << std::endl;
   std::cout << Multiply<double, double>(2,2.7) << std::endl;

   return 0;
}
