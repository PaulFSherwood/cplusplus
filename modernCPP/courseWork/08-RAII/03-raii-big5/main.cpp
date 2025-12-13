#include <string>
#include <vector>
#include "intArray.hpp"

IntArray foo() {
    IntArray result("foo() created array");
    return result;
}

int main() {
    // IntArray array1("array1");
    // Copy made
    // IntArray array2 = array1;
    //IntArray array2 = foo();
    std::vector<IntArray> myArrays;
    myArrays.reserve(10);   // reserving memory ahead of time. Not needed. 35 vs 13 allocs 
    for (int i = 0; i < 10; i++) {
        IntArray temp(std::to_string(i));
        myArrays.push_back(std::move(temp));
    }

    return 0;
}
