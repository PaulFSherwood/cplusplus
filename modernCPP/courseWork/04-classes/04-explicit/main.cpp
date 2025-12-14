#include <iostream>
#include <string>

class udt {
    public:
        explicit udt(int);
        //explicit udt(float);

    private:
        int m_varaible;
        //float m_varaible;
};

udt::udt(int i) {
//udt::udt(float i) {
    m_varaible = i;

    std::cout << "m_variable: "
              << m_varaible
              << std::endl;
}

int main() {

    udt u1{500};
    //udt u1{500.04f};

    return 0;
}
