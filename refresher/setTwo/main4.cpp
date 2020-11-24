#include <iostream>
#include <string>
#include <stdlib.h> // srand and rand
#include <time.h>   // time

int main()
{
    int fighter1, fighter2, ouch, off;

    // set up the random seed
    srand(time(NULL));
    // generate fighter health 900 - 1000
    fighter1 = rand() % 100 + 900;
    fighter2 = rand() % 100 + 900;
    printf("We have two fighters\n");
    printf("In the blue corner is fighter one with %d health\n", fighter1);
    printf("In the  red corner is fighter two with %d health\n", fighter2);

    do
    {
        ouch = rand() % 9 + 10;
        fighter1 = fighter1 - ouch;
        off  = rand() % 9 + 10;
        fighter2 = fighter2 - off;

        // printf("fighter1 hit fighter2 for %d and has %d health remaining\n", ouch, fighter1);
        // printf("fighter2 hit fighter1 for %d and has %d health remaining\n", off,  fighter2);

        // if (fighter1 < 0) { fighter1 = 0; }
        // if (fighter2 < 0) { fighter2 = 0; }
    } while((fighter1 >= 0) && (fighter2 >= 0));
    
    printf("fighter1 hit fighter2 for %d and has %d health remaining\n", ouch, fighter1);
    printf("fighter2 hit fighter1 for %d and has %d health remaining\n", off,  fighter2);

    std::cout << (fighter1 > fighter2 ? "fighter1" : "fighter2") << " won the fight" << std::endl; 


    return 0;
}
