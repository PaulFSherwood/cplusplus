#include <iostream>
using namespace std;

const canSum(targetSum, array, size) {
    if (targetSum == 0) {
        return true;
    }

    for (int i = 0; i <= size; i++) {
        const remainder = targetSum - array[i];
        if (canSum(remainder, array, i)) {
            return true;
        }
    }
    return false;
}


int main() {

    int one[2] = {2, 3};

    cout << canSum(7, one, 2);

    return 0;
}
