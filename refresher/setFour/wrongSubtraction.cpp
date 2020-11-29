#include <iostream>
#include <cmath>

int wrongSubtraction(int inputNumber, int turns)
{
    std::cout << "Num: " << inputNumber <<  " -> ";
    
    for(int i = 0; i < turns; i++)
    {
        if((inputNumber % 10) == 0)
        {
            inputNumber = inputNumber / 10;
        } else {
            inputNumber--;
        }
        std::cout << inputNumber << " -> ";
    }
        return inputNumber;
}

int main() 
{
    
    wrongSubtraction(512, 4);
    std::cout << std::endl;

    return 0;
}
