#include <iostream>
#include <cmath>

template <typename T>
bool equal(T a, T b) {
   return (a==b);
}

// specialzed templated as the generated templates don't work correctly.
template<>
bool equal<float>(float a, float b) {
   std::cout << "equal<float>\n";
   return fabs(a - b) < 0.00001f;
}
template<>
bool equal<double>(double a, double b) {
   std::cout << "equal<double>\n";
   return abs(a - b) < 0.0000001;
}
int main() {
   std::cout << equal<int>(2, 2) << std::endl;
   std::cout << equal<int>(2, 3) << std::endl;
   // Calling special templates as the generated templates don't work correctly
   std::cout << equal<float>(1.0f-0.999999f, 0.000001f) << std::endl;
   std::cout << equal<double>(1.0f-0.9999999999, 0.0000000001) << std::endl;

   return 0;
}
