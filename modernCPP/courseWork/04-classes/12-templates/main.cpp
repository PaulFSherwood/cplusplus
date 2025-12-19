/*
#include <functional>  // for function
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
*/
#include <iostream>

template <typename T>
T square(T input, auto output) {
   std::cout << "T+T: " << output + output << std::endl;
   return input * input;
}
auto returnNumbers(auto x, auto y, auto z) {
   return x * y * z;
}
// float square(float input) {
//    return input * input;
// }

int main() {

   std::cout << square(2, 2.05f) << std::endl;
   std::cout << returnNumbers(2, 2.4, 2.005f) << std::endl;

   return 0;
}


/*
 * template and auto seem to create the same code.
ORIGINAL
template <typename T>
T square(T input) {
  return input * input;
} 
PRODUCED
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int square<int>(int input)
{
  return input * input;
}
#endif

ORIGINAL
auto square(auto input) {
  return input * input;
}
PRODUCED
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int square<int>(int input)
{
  return input * input;
}
#endif

*/
