// #include <ctime>  // c++ <10
#include <iostream>
#include <chrono>    // g++ -std=c++0x pid_example.cpp pid.cpp -o PID
#include <thread>
//#include <stdio.h>
#include "pid.h"

// void pause(int dur) {
// 	int temp = time(NULL) + dur;
// 	while(temp > time(NULL));
// }

int main() {
	// Setup / INIT
	//	       dt, max,  min,  Kp,   Kd,  Ki
	PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);
	int setTemp = 0;
	double val = 20;
	
	// push user temperature to setTemp variable
	std::cout << "Please enter desired temp: ";
	std::cin >> setTemp;

	// loop for 300 * 300 milliseconds
	for (int i = 0; i < 300; i++) {
		// get the current change in temp requested by the PID controller
		double change = pid.calculate(setTemp, val);
		printf("[%d]\tSet: %d | Reading: %7.3f | Change: %7.3f\n", i, setTemp, val, change);
		val += change;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(30)); // wait for, in milliseconds
		// pause(1);  not used for c++ 11
	}
	return 0;
}
