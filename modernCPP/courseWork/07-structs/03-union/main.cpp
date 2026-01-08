#include <iostream>
#include <variant>    // C++17 and beyond

union U {
    int i;
    short s;
};

int main() {

   std::variant<int, float> data;
   std::cout << "U   : " << sizeof(U) << std::endl;
   std::cout << "data: " << sizeof(data) << std::endl;
   data = 7.0f;
   if (auto attempt = std::get_if<float>(&data)) {
      std::cout << "We found a float" << std::endl;
   }
   std::cout << get<float>(data) << std::endl;

   return 0;
}
