#include <iostream>

template<typename T, int Size>
class Container {
    public:
        Container() {
            m_data = new T[Size];
        }
        ~Container() {
            delete[] m_data;
        }
        

        static T m_variable;

    private:
        T *m_data;
};

int main() {
    
    Container<int, 5> a;
    Container<double, 5> b;
    Container<float, 5> c;

    return 0;
}
