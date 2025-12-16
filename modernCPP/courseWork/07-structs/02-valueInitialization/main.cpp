#include <iostream>
#include <string>

struct Entity {
//    Entity() : name(""), x(0), y(0), collection(nullptr){
// //       x = 0;
// //       y = 0;
// //       collection = nullptr;
//    }

//    Entity() = default;
   Entity(const std::string& _name, int _x, int _y) : x{_x}, y{_y}, collection{nullptr}, name{_name} {}
   Entity() : name{}, x{0}, y{0}, collection{nullptr} {}

//    std::string name;
//    int y;
//    int x;
//    int *collection;
   std::string name{""};
   int y{4};
   int x{5};
   int *collection{nullptr};
};

int main() {
   
   Entity e{"paul", 1, 2};
   Entity d{"mike", 7, 5};
   Entity f;
   f.name = "Sarah";
   std::cout << e.name        << std::endl;
   std::cout << e.collection  << std::endl;
   std::cout << e.x           << std::endl;
   std::cout << e.y           << std::endl;
   std::cout << "===========" << std::endl;
   std::cout << d.name        << std::endl;
   std::cout << d.collection << std::endl;
   std::cout << d.x           << std::endl;
   std::cout << d.y           << std::endl;
   std::cout << "===========" << std::endl;
   std::cout << f.name        << std::endl;
   std::cout << f.collection << std::endl;
   std::cout << f.x           << std::endl;
   std::cout << f.y           << std::endl;


   return 0;
}
