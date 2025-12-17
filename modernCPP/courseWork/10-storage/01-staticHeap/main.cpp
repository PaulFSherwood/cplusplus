#include <iostream>

void foo() {
   int s_variable = 0;
   std::cout << s_variable << std::endl;
   std::cout << &s_variable << std::endl;
}

int main() {

   int x = 0;         // x is a local variable

   int *p = new int;  // p is a local variable
                      // p, points to a memory
                      //    allocated on the heap
                      //    The memory on the 
                      //    heap leaves until 
                      //    we say so.
   delete p;

   for (int i = 0; i < 10; i++) {
      foo();
      if (i >= 5){ int y = i; }
   }
   double t = 10.0f;
   for (int i = 0; i < 10; i++) {
      foo();
      if (i >= 5){ int y = i; }
   }

   return 0;
}
