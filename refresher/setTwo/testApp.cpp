#include <iostream>
#include <string>
#include <stdlib.h> // srand and rand
#include <time.h>   // time
#include <ctype.h>

int distance(int groundSpeed, int time);	// 1
int groundSpeed(int distance, int time);	// 2
int time(int distance, int speed);			// 3
int fuelConsumed(int gph, int time);		// 4
int gph(int fuelConsumed, int time);		// 5
void showMenu();

int main()
{
    bool isRunning = true;
    int menuNumber = 0;
	int value1 = 0;
	int value2 = 0;
	
    while (isRunning)
    {
        // first we display the menu
        showMenu();
        // then we need to get the users choice of what to do
        std::cin >> menuNumber; // this input needs verification
		// test user input
		while (std::cin.fail()) {
			printf("Input error please try again.\n");	// show error
			std::cin.clear();							// clear input
			std::cin.ignore(256, '\n');					// clear input
			std::cin >> menuNumber;						// get input again
		}
		
		
        // now we can act on that choice
        switch (menuNumber) {
                case 1: // Find distance
					// get some values first
					printf("Enter the ground speed.\n");
					std::cin >> value1;
					printf("Enter the time.\n");
					std::cin >> value2;
					printf("Distance is: %d\n", distance(value1, value2));
					printf("===============================\n");
                    break;
                case 2: // Find distance
					// get some values first
					printf("Enter the distance.\n");
					std::cin >> value1;
					printf("Enter the time.\n");
					std::cin >> value2;
					printf("Ground speed is: %d\n", groundSpeed(value1, value2));
					printf("===============================\n");
                    break;
                case 3: // Find distance
					// get some values first
					printf("Enter the distance.\n");
					std::cin >> value1;
					printf("Enter the speed.\n");
					std::cin >> value2;
					printf("Time is: %d\n", time(value1, value2));
					printf("===============================\n");
                    break;
                case 4: // Find distance
					// get some values first
					printf("Enter the gallons per hour.\n");
					std::cin >> value1;
					printf("Enter the time.\n");
					std::cin >> value2;
					printf("Fuel consumed is: %d\n", fuelConsumed(value1, value2));
					printf("===============================\n");
                    break;
                case 5: // Find distance
					// get some values first
					printf("Enter the fuel consumed.\n");
					std::cin >> value1;
					printf("Enter the time.\n");
					std::cin >> value2;
					printf("Gallons per hour is: %d\n", gph(value1, value2));
					printf("===============================\n");
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
int distance(int groundSpeed, int time)	{ return groundSpeed  * time;  }
int groundSpeed(int distance, int time)	{ return distance     * time;  }
int time(int distance, int speed)		{ return distance     * speed; }
int fuelConsumed(int gph, int time)		{ return gph		  * time;  }
int gph(int fuelConsumed, int time)		{ return fuelConsumed * time;  }
