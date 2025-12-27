#include <iostream>
#include <vector>

template<typename first, typename second>
struct Entry {
    Entry(first key, second value) {
        m_key = key;
        m_value = value;
    }
    first m_key;
    second m_value;
};

int main() {
    // Original
    // Entry<int, int> entry(5, 100);

    // Class Template Argument Deduction (CTAD)
    Entry entry(5, 100.1f);

    std::cout << entry.m_key << std::endl;
    std::cout << entry.m_value << std::endl;

    // std::vector<int> v1{1,2,3,4,5};
    std::vector v1{1,2,3,4,5};
    // std::vector v2{1,2.0f,3,4,5};  // will cause issues as it is not sure what the types should be
    std::vector v2{1.0f,2.0f,3.0f,4.0f,5.0f};   // all are the same type so it is good to go.

    return 0;

}
