#include <iostream>
#include <typeinfo>
#include <string>

int main()
{
   auto value1 = 72;
   std::cout << typeid(value1).name() << ":" << value1 << std::endl;

   auto value2 = 72.04f;
   std::cout << typeid(value2).name() << ":" << value2 << std::endl;

   auto value3 = "bob";
   std::cout << typeid(value3).name() << ":" << value3 << std::endl;
   std::cout << "Could not deduce type intent\nP is the encoding for \"pointer\", K refers to \"const\", and c means \"char\"." << std::endl;

   std::string value4 = "bob";
   std::cout << typeid(value4).name() << ":" << value4 << std::endl;

   auto value5 = 'c';
   std::cout << typeid(value5).name() << ":" << value5 << std::endl;

   return 0;
}
