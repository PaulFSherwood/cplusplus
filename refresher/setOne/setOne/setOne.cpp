// setOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using std::cout;  // alternative to using namespace std and pulling in everthing.

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

    cout << "a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << ", e: " << e << std::endl;
}
