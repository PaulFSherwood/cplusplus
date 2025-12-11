#include <iostream>
#include <memory>

// Some User defined type
class UDT{
   public:
      // Constructor (called on creation)
      UDT() { std::cout << "UDT Created" << std::endl; }
      // Destructor (called on destruction)
      ~UDT() { std::cout << "UDT Destroyed" << std::endl; }
};

int main() {

   int x = 42;
   int *ptr = &x;

   // Output value pointed to by ptr
   std::cout << "*ptr = " << *ptr << std::endl;

   // Create a second pointer
   int *ptr2 = ptr;

   std::cout << "*ptr2 = " << *ptr2 << std::endl;

   UDT myType;

   std::unique_ptr<UDT> myUniquePtr = std::unique_ptr<UDT>(new UDT);
   std::cout << "Make 3 arrays = " << std::endl;
   std::unique_ptr<UDT[]> myArrayPtr = std::unique_ptr<UDT[]>(new UDT[3]);
   std::cout << "Make 3 arrays = " << std::endl;
   std::unique_ptr<UDT[]> myArrayPtr2 = std::make_unique<UDT[]>(3);




   return 0;
}
