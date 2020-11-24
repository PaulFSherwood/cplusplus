#include <iostream>
#include <string>

int main()
{
    int password = 400;
    int guess = 0;
    do 
    {
        guess++;
    } while (guess != password);

    std::cout << "Guess[" << guess << "] is now equal to the password[" << password << "]\n";

    return 0;
}
