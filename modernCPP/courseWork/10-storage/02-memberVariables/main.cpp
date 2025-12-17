#include <iostream>

struct API {
   API() {}
   ~API() {}

   // Static variables in a class exists outside of the class.
   // The scope is within the class.
   static int MAJOR;
   static int MINOR;

};

int API::MAJOR = 7;

int main() {

   // API instance;
   // instance.MAJOR = 7;

   std::cout << "Major: " << API::MAJOR << std::endl;
   API::MAJOR = 9;
   std::cout << "Major: " << API::MAJOR << std::endl;
   return 0;
}
