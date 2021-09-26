// geeksforgeeks
//
#include <iostream>
using namespace std;

// for memo  // from stackoverflow "fib memoization algo
#define N 100
const int NIL = -1;
int lookup_table[N];

void init()
{
    for (int i = 0; i < N; i++)
    {
        lookup_table[i] = NIL;
    }
}

int fib_mem(int n) {
    if(lookup_table[n] == NIL) {
        if(n <= 1)
        {
            lookup_table[n] = n;
        } else {
            lookup_table[n] = fib_mem(n-1) + fib_mem(n-2);
        }
    }
    return lookup_table[n];
}

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
    init();
    // cout << fib(9);
    // cout << fib(18);
    // cout << fib(50);
    cout << fib_mem(9) << endl;
    cout << fib_mem(18) << endl;
    cout << fib_mem(50) << endl;

    cout << endl;

    return 0;
}

