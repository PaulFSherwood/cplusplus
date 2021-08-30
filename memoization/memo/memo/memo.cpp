#include <iostream>
#define N 100

using namespace std;

const int NIL = -1;
int lookup_table[N];

void init()
{
    for (int i = 0; i < N; i++)
        lookup_table[i] = NIL;
}
int fib_mem(int n) {
    if (lookup_table[n] == NIL) {
        if (n <= 1)
            lookup_table[n] = n;
        else
            lookup_table[n] = fib_mem(n - 1) + fib_mem(n - 2);
    }
    return lookup_table[n];
}
int main()
{
    init();
    cout << fib_mem(5);
    cout << endl;
    cout << fib_mem(7);
    cout << endl;
    cout << fib_mem(50);
    cout << endl;
    cout << endl;
}