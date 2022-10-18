#include <iostream>
int main() {
    int num[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int min = num[0];
    for (int i = 0; i < 10; i++)
        if (num[i] < min)   // this if belongs to the for above
            min = num[i];   // this line belongs to the 'if' above
                            // so this line also belong to the 'for'
                            // as the 'for' own the 'if'
}
