#include <iostream>
#include <string>
#include <stdlib.h> // srand and rand
#include <time.h>   // time
#include <ctype.h>

void showMenu();
int verifyInput(int value);
void distance();		// 1
void groundSpeed();		// 2
void time();			// 3
void fuelConsumed();	// 4
void gph();				// 5

int main()
{
    bool isRunning = true;
    int menuNumber = 0;
	
    while (isRunning)
    {
        // first we display the menu
        showMenu();
        // then we need to get the users choice of what to do
        menuNumber = verifyInput(menuNumber);
		
        // now we can act on that choice
        switch (menuNumber) {
                case 1: // Find distance
					distance();
                    break;
                case 2: // Find Ground speed
					groundSpeed();
                    break;
                case 3: // Find Time
					time();
                    break;
                case 4: // Find Fuel consumed
					fuelConsumed();
                    break;
                case 5: // Find Gallons per hour
					gph();
                    break;
				case 6: // exit the program
                    isRunning = false;
					break;
                default:  // exit on anything else
					break; // something went wrong loop back around
        }
    }
    return 0;
}
void showMenu()
{
    printf("Please select a Aviation Function\n");
    printf("1) Distance = Grd Spd(mpg) * Time(min)\n");
    printf("2) Ground Speed = Distance(miles) * Time(min)\n");
    printf("3) Time = Distance(miles) * Speed\n");
    printf("4) Fuel consumed = GPH * Time(min)\n");
    printf("5) GPH = Fuel Consumed / Time(min)\n");
    printf("6) Exit\n");
}
int verifyInput(int value)
{
	std::cin >> value; // this input needs verification
	// test user input
	while (std::cin.fail()) {
		printf("Input error please try again.\n");	// show error
		std::cin.clear();							// clear input
		std::cin.ignore(256, '\n');					// clear input
		std::cin >> value;						// get input again
	}
	return value;
}
void distance() 
{
	printf("Enter the ground speed. ");
	int value1 = verifyInput(value1);
	printf("Enter the time. ");
	int value2 = verifyInput(value2);
	printf("Distance is: %d\n", value1 * value2);
	printf("===============================\n");
}
void groundSpeed() 
{
	printf("Enter the distance. ");
	int value1 = verifyInput(value1);
	printf("Enter the time. ");
	int value2 = verifyInput(value2);
	printf("Ground speed is: %d\n", value1 * value2);
	printf("===============================\n");
}
void time() 
{ 
	printf("Enter the distance. ");
	int value1 = verifyInput(value1);
	printf("Enter the speed. ");
	int value2 = verifyInput(value2);
	printf("Time is: %d\n", value1 * value2);
	printf("===============================\n");
}
void fuelConsumed()
{ 
	// get some values first
	printf("Enter the gallons per hour. ");
	int value1 = verifyInput(value1);
	printf("Enter the time. ");
	int value2 = verifyInput(value2);
	printf("Fuel consumed is: %d\n", value1 * value2);
	printf("===============================\n");
}
void gph()
{ 
	// get some values first
	printf("Enter the fuel consumed. ");
	int value1 = verifyInput(value1);
	printf("Enter the time. ");
	int value2 = verifyInput(value2);
	printf("Gallons per hour is: %d\n", value1 * value2);
	printf("===============================\n");
}
