#include <iostream>
#include "Person.hpp"

int main() {

   Person mike("mike");
   std::cout << mike.GetAttributes() << std::endl;

   return 0;
}
