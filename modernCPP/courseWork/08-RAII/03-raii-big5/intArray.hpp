#include <iostream>

class IntArray {
    public:
        // The Big 3
        // (1) Constructor
        IntArray(std::string name);
        // (2) Destructor
        ~IntArray();
        // (3) Copy constructor policy
        IntArray(const IntArray &rhs);
        // Copy assignment operator policy
        IntArray &operator=(const IntArray &rhs);

        // The other 2 (in total, making 'The Big 5')
        // Move constructor policy
        IntArray(IntArray &&source);
        // Move assignment operator policy
        IntArray & operator=(IntArray &&source);
    private:
    std::string m_name;
    int *m_data;
};
