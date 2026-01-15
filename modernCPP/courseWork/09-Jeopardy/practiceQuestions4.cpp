//Which C++ 'feature' would you use to cast a pointer to class B into a dereived class D?
  
#include <iostream>

class Base {
   virtual void someFunction() {
      std::cout << "Base::someFunction\n";
   }
};
class Derived {
   int a;
   public:
   virtual void someFunction() {
      std::cout << "Derived::someFunction\n";
   }
};

int main() {
   Base* B    = new Base;
   Derived* D = new Derived;

   if (dynamic_cast<Derived*>(B)) {
      std:: cout << "this works" << std::endl;
      dynamic_cast<Derived*>(B)->someFunction();
   }

   return 0;
}
