#include <iostream>
#include <string>

template <typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

int main()
{
    enum class Season { summer, spring, fall, winter };
    Season now = Season::winter;

    switch (now)
    {
        case Season::summer:
            std::cout << as_integer(now) << ": It is Summer\n";
            break;
        case Season::spring:
            std::cout << as_integer(now) << ": It is Spring\n";
            break;
        case Season::fall:
            std::cout << as_integer(now) << ": It is Fall\n";
            break;
        case Season::winter:
            std::cout << as_integer(now) << ": It is Winter\n";
            break;
    }
    return 0;
}
