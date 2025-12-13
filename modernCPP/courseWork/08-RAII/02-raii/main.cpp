#include <cstddef>
#include <iostream>
#include <iterator>

class Collection {
    public:
        Collection() {
            data = new int[10];
            try {
                throw 20;
            } catch (int e) {
                std::cout << "Error message" << std::endl;
            }
        }
        ~Collection() {
            std::cout << "Destructor" << std::endl;
            delete[] data;
        }
        int& operator[](std::size_t idx) {
            return data[idx];
        }
        const int& operator[](std::size_t idx) const {
            return data[idx];
        }
    private:
        int *data;
};

int main() {
    Collection myCollection; 

    myCollection[0] = 7;
    myCollection[1] = 7;
    myCollection[2] = 7;
    std::cout << myCollection[0] << std::endl;

    return 0;

}
