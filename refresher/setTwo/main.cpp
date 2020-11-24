#include <iostream>

int main()
{
    enum season { summer, spring, fall, winter };
    season now = spring;

    switch (now)
    {
        case summer:
            std::cout << "It is Summer\n";
            break;
        case spring:
            std::cout << "It is Spring\n";
            break;
        case fall:
            std::cout << "It is Fall\n";
            break;
        case winter:
            std::cout << "It is Winter\n";
            break;
    }
    return 0;
}
