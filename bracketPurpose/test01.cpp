#include <iostream>
int main() {
    for (int i = 0; i < 10; i++)
        std::cout << "in scope of for" << std::endl;
    std::cout << "out of scope of for" << std::endl;
}
