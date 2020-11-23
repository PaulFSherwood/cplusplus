// setOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cmath>
using std::cout;  // alternative to using namespace std and pulling in everthing.
using std::cin;
using std::endl;

void printVariables(char a, int b, float c, double d, bool e);  // function declaration

int main()
{
    // the solution to libraries with the same name
    // is to use differnt namespaces
    // I is like having differnet containers of code to use
    cout << "Hello World!\n";
    // cout is an object that discribes the output stream.
    // << is an operator to preform an action on to an object

    printf("hey");

    // C++ BASIC variable types 16,32, signed, short not included
    char a = 'a';
    int b = 1;
    float c = 1.1;
    double d = 2.2;
    bool e = false;
    // Signed numbers can be neg. or pos. but half the max value of Unsigned


    printVariables(a, b, c, d, e);
    for (int i = 1; i < 5; i++) {

        printVariables(a, b++, c++, d++, e);
    }
    // double result = pow(10, 3);
    // cout << result << std::endl;
}

// function defenitions
void printVariables(char a, int b, float c, double d, bool e) {
    printf("=====================\n");
    cout << "a: " << a << ", b: " << b << ", c:  " << c << ", d:  " << d << ", e: " << e << endl;
    printf("a: %c, b: %d, c: %.2f, d: %.2f, e: %s\n\n", a, b, c, d, e ? "true" : "false");
}