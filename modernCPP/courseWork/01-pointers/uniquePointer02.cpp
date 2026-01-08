#include <iostream>
#include <memory>

struct IntDeleter {
   void operator() (int* int_ptr) {
      std::cout << "IntDeleter called" << std::endl;
      delete int_ptr;

   }
};

int main() {

   std::unique_ptr<int> my_ptr = std::make_unique<int>();
   std::unique_ptr<int,IntDeleter> my_ptr2(new int);

   return 0;
}
