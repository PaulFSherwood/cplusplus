#include <iostream>
#include <ctime>

int main(void)
{
    using namespace std;
    
    time_t t;
    time(&t);
    srand(t);
    for (int iIndex = 0; iIndex < 10; ++iIndex) {
        cout << (rand() % 13) << "  ";
        }
        cout << endl;
        }
