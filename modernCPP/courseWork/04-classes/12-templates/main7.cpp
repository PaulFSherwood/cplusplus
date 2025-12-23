#include <iostream>

template<typename T, int Size>
class Container {
    public:
        Container(int N) {
            m_data = new T[N];
        }
        Container() {
            m_data = new T[Size];
        }
        ~Container() {
            delete[] m_data;
        }

    private:
        T *m_data;
};

int main() {

    //Container <int>c(10);
    Container<int,5>    c;// (10);
    Container<int,7>    d;// (10);
    Container<double,5> e;// (10);

    return 0;
}
