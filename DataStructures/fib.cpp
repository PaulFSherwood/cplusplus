// geeksforgeeks
//
#include <iostream>
using namespace std;

// siple fib function
int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fib (n - 1) + fib (n - 2);
}

int main()
{
    cout << fib(9);
    cout << fib(18);
    cout << fib(50);
    

    cout << endl;

    return 0;
}

