#include <iostream>
#include <memory>

/*
	Pointer type	Owns Object	can use -> ?	Must lock()?
	shared_ptr	   yes		   yes		   no
	unique_ptr	   yes		   yes		   no
	weak_ptr	    no		    no		  yes
 */
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
      std::weak_ptr<UDT> ptr2 = ptr1; // weak pointers do not update the reference counter

      // ptr1->num = 2;
      if (auto sp = ptr2.lock()) {
	      sp->num = 2;
	      std::cout << "&ptr1: " << &ptr1 << "\tptr1->num: " << ptr1->num << std::endl;
      	      std::cout << "&ptr2: " << &ptr2 << "\tptr2.lock()->num: " << sp->num << std::endl;
      } else {}
      // Show the use count change
      std::cout << "Use count: " << ptr1.use_count() << std::endl;
      // ptr2->num = 3;
      std::cout << "&ptr1: " << &ptr1 << std::endl; //"\t" << ptr1->num << std::endl;
      std::cout << "&ptr2: " << &ptr2 << std::endl; //"\t" << ptr2->num << std::endl;
   }  // ptr2 is released so the use count should go down.
   // Show how many pointers are pointing to the resource.
   std::cout << "Use count: " << ptr1.use_count() << std::endl;

   return 0;
}
