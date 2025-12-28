#include <iostream>
#include <stdlib.h>
#include <time.h>

// int xs[] = {
//     7,62,2,46,73,43,26,82,5,95,
//     57,56,44,21,40,79,13,6,9,8,
//     72,59,65,81,60,78,13,85,87,58,
//     48,25,32,47,67,4,31,19,33,1,
//     92,14,53,89,84,54,29,10,17,3,
//     77,70,45,97,34,23,86,55,15,64,
//     68,83,76,41,18,39,94,22,74,11,
//     69,49,12,35,20,90,100,98,36,63,
//     91,38,66,93,50,96,61,71,75,37,
//     52,88,30,28,99,27,42,51,80,24,16};
// size_t n = sizeof(testArray)/sizeof(testArray[0]) - 1;
// x = y...

void printArray(int array[], int num) {
    // Print the array
    for (int i = 0; i <= num; i++) {
        if (i == num) {
            printf("testArray[%d]=%d\n", i, array[num]);
        } else {
            printf("testArray[%d]=%d, ", i, array[i]);
        }
    }
}

int main() {

    int a = 63;
    int b = 401;

    std::cout << "Before: " << "a: " << a << " || b: " << b << std::endl;
    a ^= b;
    std::cout << "a ^= b: " << "a: " << a << " || b: " << b << std::endl;
    b ^= a;
    std::cout << "b ^= a: " << "a: " << a << " || b: " << b << std::endl;
    a ^= b;
    std::cout << "a ^= b: " << "a: " << a << " || b: " << b << std::endl;

    // create a duplicate number out of 100
    int count = 100;
    int max = count + 1;

    int testArray[max];
    srand(time(0));
    int dup = rand() % max;
    std::cout << "dup: " << dup << std::endl;

    // Populate the max array size + 1 to get the duplicate in.
    for (int i = 0; i < count; i++) {
        testArray[i] = i + 1;
    }
    testArray[count] = dup;

    // Shuffle array Fisher-Yates Shuffle
    for (int i = max - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(testArray[i], testArray[j]);
    }

    // printArray(testArray, count);
    
    // Use xor to find duplicate
    int x = 0;

    // XOR expected values
    for (int i = 1; i <= 100; ++i) {
        x ^= i;
    }
    printf("x: %d\n", x);

    for (int i = 0; i < max; ++i) {
        // nuke each element to end up with one element.
        x ^= testArray[i];
    }
    printf("Dup: %d\n", x);

    // a^b^b == a


    return 0;
}
