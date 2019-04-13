#include <QCoreApplication>
#include <iostream>
#include <chrono>    // g++ -std=c++0x pid_example.cpp pid.cpp -o PID
#include <thread>
#include "pid.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Setup / INIT
    //	           dt, max,  min,  Kp,   Kd,  Ki
    PID pid = PID(0.1, 100, -100, 0.4, 0.01, 0.5);
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

        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // wait for, in milliseconds
    }

    return a.exec();
}
