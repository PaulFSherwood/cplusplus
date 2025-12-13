#include <iostream>
#include "Vector3f.hpp"

std::ostream& operator<<(std::ostream& os, const Vector3f& obj) {
    os << obj.x << "," << obj.y << "," << obj.z;
    return os;
}

int main() {
    Vector3f myVector1(4,2,1);
    Vector3f myVector2;

    std::cout << myVector1 << std::endl;
    std::cout << myVector2 << std::endl;

    return 0;
}
