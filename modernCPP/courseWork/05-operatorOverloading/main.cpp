#include <iostream>

// A vector3 data type, storing floats
class Vector3f{
    public:
        Vector3f(){
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        Vector3f operator+(const Vector3f& rhs) const {
            Vector3f result;
            result.x = x + rhs.x;
            result.y = y + rhs.y;
            result.z = z + rhs.z;

            return result;
        }

        Vector3f operator++() {
            x = x + 1;
            y = y + 1;
            z = z + 1;
            return *this;
        }

        bool operator==(const Vector3f& rhs) {
            if (x == rhs.x && y == rhs.y && z == rhs.z) {
                return true;
            } else { 
                return false;
            }
        }
        
        float x,y,z;
};
        
std::ostream& operator<<(std::ostream& os, const Vector3f& obj) {

    os << obj.x << "," << obj.y << "," << obj.z;

    return os;
}

bool operator==(const Vector3f& lhs, const Vector3f& rhs) {
    if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z) {
        return true;
    } else { 
        return false;
    }
}
        

int main() {

    Vector3f myVector1;
    myVector1.x = 1.f;
    myVector1.y = 2.f;
    myVector1.z = 3.f;

    Vector3f myVector2;
    myVector2.x = 3.f;
    myVector2.y = 2.f;
    myVector2.z = 1.f;

    std::cout << (myVector1==myVector2) << std::endl;

    Vector3f result;
    result = myVector1 + myVector2;
    std::cout << "My vectors:\n";
    std::cout << myVector1.x << "," << myVector1.y << "," << myVector1.z << std::endl;
    std::cout << myVector2.x << "," << myVector2.y << "," << myVector2.z << std::endl;
    std::cout << "Result:\n";
    std::cout << result.x << "," << result.y << "," << result.z << std::endl;

    std::cout << "++vector:\n";
    ++myVector1;
    std::cout << myVector1.x << "," << myVector1.y << "," << myVector1.z << std::endl;

    std::cout << myVector1 << std::endl;
    myVector2.x = myVector1.x;
    myVector2.y = myVector1.y;
    myVector2.z = myVector1.z;
    std::cout << (myVector1==myVector2) << std::endl;

    return 0;
}
