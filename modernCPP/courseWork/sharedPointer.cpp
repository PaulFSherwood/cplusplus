#include <iostream>
#include <memory>

class UDT { // user defined type
   public:
      // Constructor (called on creation)
      UDT() { std::cout << "UDT Created" << std::endl; }
      // Destructor (called on destruction)
      ~UDT() { std::cout << "UDT Destroyed" << std::endl; }

      int num = 0;
};

int main() {

   // Create a shared pointer
   std::shared_ptr<UDT> ptr1 = std::make_shared<UDT>();
   std::cout << "Use count: " << ptr1.use_count() << std::endl;
   {
      // Then, in a new scope, share the resource from ptr1
      std::shared_ptr<UDT> ptr2 = ptr1;

      ptr1->num = 2;
      std::cout << "&ptr1: " << &ptr1 << "\t" << ptr1->num << std::endl;
      std::cout << "&ptr2: " << &ptr2 << "\t" << ptr2->num << std::endl;
      // Show the use count change
      std::cout << "Use count: " << ptr1.use_count() << std::endl;
      ptr2->num = 3;
      std::cout << "&ptr1: " << &ptr1 << "\t" << ptr1->num << std::endl;
      std::cout << "&ptr2: " << &ptr2 << "\t" << ptr2->num << std::endl;
   }  // ptr2 is released so the use count should go down.
   // Show how many pointers are pointing to the resource.
   std::cout << "Use count: " << ptr1.use_count() << std::endl;

   return 0;
}
