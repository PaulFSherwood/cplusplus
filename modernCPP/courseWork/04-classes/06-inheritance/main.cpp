#include <iostream>

class Base {
    public:
        Base() {
            std::cout << "Base Constructor" << std::endl;
        }
        ~Base() {
            std::cout << "Base Destructor" << std::endl;
        }
    public:
        int m_base_public_member_variable;
    protected:
        int m_base_protected_member_variable;
    private:
        int m_base_private_member_variable;

};

// class Derived : private Base {       // Changes external access levels
// class Derived : protected Base {     // Changes external access levels
class Derived : public Base {
    public:
        Derived() {
            std::cout << "Derived Constructor" << std::endl;
            m_base_public_member_variable = 123;
            m_base_protected_member_variable = 333;
            // ERROR: m_base_private_memeber_variable = 444;
        }
        ~Derived() {
            std::cout << "Derived Destructor" << std::endl;
        }

};

int main() {

    Derived d;
    d.m_base_public_member_variable = 123;
    // ERROR: d.m_base_protected_member_variable = 222;
    // ERROR: d.m_base_private_member_variable = 222;

    return 0;
}
