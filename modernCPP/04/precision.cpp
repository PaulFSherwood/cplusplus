#include <print>
#include <iomanip>
#include <iostream>

int main() {

  double PI = 3.1415926535;

  std::cout << PI << std::endl;

  std::cout << std::setprecision(6) << PI << std::endl;;
  std::cout << std::setprecision(11) << PI << std::endl;;

  return 0;
}
