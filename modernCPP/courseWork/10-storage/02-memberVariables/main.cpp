#include <iostream>
#include "API.hpp"

int main() {

   // API instance;
   // instance.MAJOR = 7;

   std::cout << "Major: " << API::MAJOR << std::endl;
   // API::MAJOR = 9;
   // std::cout << "Major: " << API::MAJOR << std::endl;
   std::cout << "Major: " << API::GetMajorVersion() << std::endl;
   
   return 0;
}
