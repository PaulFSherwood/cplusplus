#include <iostream>
#include <typeinfo>

template <typename T1, typename T2>
void foo(T1 input1, T2 input2) {
   std::cout << typeid(input1).name() << " " << input1 << std::endl;
   std::cout << typeid(input2).name() << " " << input2 << std::endl;
}

int main() {

   // Pass in a integer and a float 
   foo<int, float>(5, 3.14f);
   
   return 0;
}

