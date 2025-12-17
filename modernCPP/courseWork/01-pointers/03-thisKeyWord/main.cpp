#include <iostream>

class Person {
	public:
		Person(int age) {
         this->age = age;
      }
      int GetAge() const {
         return age;
      }
      Person* GetThisAddress() {
         return this;
      }

   private:
      int age;
};

int main() {
   Person mike(500);

   std::cout << "Mike's age:   " << mike.GetAge() << std::endl;
   std::cout << "Mike address: " << mike.GetThisAddress() << std::endl;
   std::cout << "Mike age:     " << &mike << std::endl;

   Person *bob = new Person(700);
   std::cout << "Bob's age:   " << bob->GetAge() << std::endl;
   std::cout << "Bob address: " << bob->GetThisAddress() << std::endl;
   std::cout << "Bob pointer: " << bob << std::endl;

   delete bob;

   return 0;
}

