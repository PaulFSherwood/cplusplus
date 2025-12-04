#include <iostream>

int main() {

  const int a = 12;
  
  std::cout << "A: " << a << std::endl;

  const int& x = a;

  int* p = const_cast<int*>(&a);
  *p = 70;

  std::cout << "P: " << p << std::endl;
  std::cout << "A: " << a << std::endl;
  std::cout << "X: " << x << std::endl;

  return 0;
}
