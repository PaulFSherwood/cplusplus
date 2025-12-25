#include <iostream>

template<typename T, int Size>
class Container {
    public:
        Container() {
            m_data = new T[Size];  // 5 heap allocated <T's> not really an array.
        }
        ~Container() {
            delete[] m_data;
        }
       void getM() {
           std::cout << "m_var:" << m_variable << std::endl;
       }

        static T m_variable;    // static members belong to the class type, {{not to an object}}

    private:
        T *m_data;
};
// define storage for a static member variable.
template<typename T, int Size> T Container<T, Size>::m_variable;

int main() {
    
    Container<int,    5> a;
    Container<double, 5> b;
    Container<float,  5> c;
    Container<int,   5>::m_variable = 7;    // One int
    Container<float, 5>::m_variable = 8;    // One float

    std::cout << Container<int,   5>::m_variable << std::endl;  // 7 <int,5> defined type
    std::cout << Container<float, 5>::m_variable << std::endl;  // 8 <float,5> defined type
    std::cout << Container<int,   4>::m_variable << std::endl;  // 0 <int,4> new type
    std::cout << Container<int,   6>::m_variable << std::endl;  // 7 <int,6> new type

    a.getM();

    return 0;
}
