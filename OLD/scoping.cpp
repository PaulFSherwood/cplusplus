// Scoping
// Demonstrates scopes
#include <iostream>

using namespace std;

void func();

int main()
{
    int var = 5;  // local variable in main()
    cout << "12 In main() var is: " << var << "\n\n";
    
    func();
    
    cout << "16 Back in main () var is: " << var << "\n\n";
	{
         cout << "19 In main() in a new scope var is: " << var << "\n\n";
         
         cout << "21 Creating new var in new scope.\n";
         int var = 10; // bariable in new scope, hides other variable named var
         cout << "23 In main() in a new scope var is: " << var << "\n";
	}
         
         cout << "26 At end of main() var created in new scope no longer exists.\n";
         cout << "27 At end of main() var is: " << var << "\n";
         
         return 0;
         
}
         
         void func()
		 {
              int var =-5;  // local variable in func()
              cout << "36 In func() var is: " << var << "\n\n";
		 }
