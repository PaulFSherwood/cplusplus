#include <iostream>
int main() {
    if (1 == 1)    
        std::cout << "in scope of if" << std::endl;
    std::cout << "out of scope of if" << std::endl;
}
