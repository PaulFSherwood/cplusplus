#include <iostream>
#include <memory>

struct A {
   void show() { std::cout << "Hello from A struct\n"; }
};

int main() {
   // Create a unique_ptr using make_unique (C++14+)
   std::unique_ptr<A> p1 = std::make_unique<A>();
   p1->show();

   // Transfer ownership to p2
   std::unique_ptr<A> p2 = std::move(p1);

   if (!p1) {
      std::cout << "P1 is now empty\n";
   }
   p2->show();

   return 0;
}
