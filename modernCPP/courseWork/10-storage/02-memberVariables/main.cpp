#include <iostream>

struct API {
   API() {}
   ~API() {}

   static int MAJOR;
   static int MINOR;

};

int main() {

   API instance;
   instance.MAJOR = 7;

   return 0;
}
