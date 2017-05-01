#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;

int main(int nNumberofArgs, char* pszArgs[])
{
    int celsius;
    cout << "Enter the temperature in Celsius: ";
    cin >> celsius;
    
    int factor;
    factor = 212 -32;
    
    int fahrenheit;
    fahrenheit = factor * celsius/100 + 32;
    
    cout << "Fahrenheit value is: ";
    cout << fahrenheit << endl;
    cout << "PRESS c THEN ENTER TO CONTINUE" << endl;
    while(1)
    {
	if('c' == getchar())
	    break;
    }
		
    return 0;
}
