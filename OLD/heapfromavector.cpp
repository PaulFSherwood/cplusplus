/** se std::make_heap to create heap from a vector  **
 ** C++ » STL Algorithms Heap » make_heap           **
 ** http://www.java2s.com/Code/Cpp/STL-Algorithms   **
 ** -Heap/Usestdmakeheaptocreateheapfromavector.htm **/


#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
   int a[ 10 ] = { 3, 10, 52, 77, 22, 31, 1, 98, 13, 40 };
   std::vector< int > v( a, a + 10 ); // copy of a
   std::vector< int > v2;
   std::ostream_iterator< int > output( cout, " " );

   std::copy( v.begin(), v.end(), output );

   std::make_heap( v.begin(), v.end() ); // create heap from vector v
   cout << "\n\n";

   std::copy( v.begin(), v.end(), output );

   cout << endl;
   return 0;
}

 /********************************
 ** 3 10 52 77 22 31 1 98 13 40 **
 ** 98 77 52 13 40 31 1 10 3 22 **
 *********************************/  
