#include <iostream>
#include <iomanip>
#include <bitset>

int main() {

   std::cout << std::fixed;
   std::cout << std::setprecision(6);
   std::cout << (float)7/5 << std::endl;

   int result = 50000;
   short c = result;
   std::cout << c << "\n size: " << sizeof(result) << std::endl;
   std::cout << " size: " << sizeof(c) << std::endl;

   result = 5;
   char d = result;
   std::cout << "INT: [" << result << "]  ASCII: [" << d << "]" << std::endl; 

   result = 53;
   d = result;
   std::cout << "INT: [" << result << "] ASCII: [" << d << "]" << std::endl; 


   int result2 = 65;
   unsigned char e = result2;
   std::cout << (int)e << std::endl;

   // use -Wall to give all warnings to see this is a bad comparison.
   int i = -2;
   unsigned int u = 1;
   if (i > u)
   {
      std::cout << "huh?" << std::endl;
   }

   // Print binary representation using bitset
   std::bitset<4> bits(i);
   std::bitset<4> bitz(u);
   std::cout << "Binary representation BITS: " << bits << "\n";
   std::cout << "Binary representation BITZ: " << bitz << "\n";
   std::cout << "is i > u : [" << std::cmp_greater(i, u) << "]" << std::endl;
   
   return 0;
}
