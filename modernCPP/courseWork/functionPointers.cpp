#include <iostream>

typedef int (*PFnIntegerOperations)(int, int);
int add(int x, int y) {
   return x+y;
}

int multiply(int x, int y) {
   return x * y;
}

int main(){

   // function pointer for functions: int name(int, int)
   int (*op)(int, int);
   std::cout << "1 for add 2 for multiple" << std::endl;
   int n,x,y;
   std::cin >> n;
   if (n == 1) { op = add; }
   else if (n == 2) { op = multiply; }

   std::cin >> x;
   std::cin >> y;

   // op = add;
   // std::cout << "Operation: " <<      add(x, y) << std::endl;
   // std::cout << "Operation: " << multiply(x, y) << std::endl;

   // std::cout << "Operation: " <<       op(x, y) << std::endl;
   // op = multiply;
   std::cout << "Operation: " <<       op(x, y) << std::endl;

   return 0;
}
