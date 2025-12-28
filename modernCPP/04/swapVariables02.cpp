#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    const int count = 100;
    const int max = count + 1;

    int testArray[max];

    srand(time(nullptr));

    int dup = rand() % count + 1;
    std::cout << "Dup inserted: " << dup << std::endl;

    for (int i = 0; i < count; ++i) {
        testArray[i] = i + 1;
    }

    testArray[count] = dup;

    for (int i = 0; i < max; ++i) {
        std::cout << testArray[i] << " ";
    }
    std::cout << std::endl;

    int x = 0;

    for (int i = 0; i < max; ++i) {
        x ^= testArray[i];
    }

    for (int i = 1; i <= count; ++i) {
        x ^= i;
    }

    std::cout << "Duplicate via XOR: " << x << std::endl;

    return 0;
}

