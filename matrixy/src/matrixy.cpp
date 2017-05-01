//============================================================================
// Name        : matrixy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<unistd.h>
#include<math.h>
#include<string>
#include<iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
//#include <conio.h>

using namespace std;

int main(int argc, char *argv[])
{
	int a;
	string array [42] = ("A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"," "," ","?","!","#","*");
//	system("TITLE The Matrix");
//	system("color CA");
	while(1)
	{
		sleep(1);
		for (int i = 0; i < 21; i++)
		{
			a = rand()%2;
			cout << " " << array[a]; // 1 BLANK
			cout << " "; // 2 blank
			}
			cout << endl;
		}
		getchar();
	return 0;
}
