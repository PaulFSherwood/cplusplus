//============================================================================
// Name        : 10.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime> 	// for time()
#include <cstdlib>	// for srand and rand()
using namespace std;

int MyFunction(){
	cout << "type in a number from 0 - 100: ";
	int playerGuess;
	cin >> playerGuess;
	return playerGuess;
}
int randomNumber(){
	srand(time(0));
	int theNumber = (rand() % 100) +1;
	return theNumber;
}

int main()
{
	int theNumber = randomNumber();
	int returnedplayerGuess;
	int guesses=0;

	cout << "lets play guess a number! \n";

	while (returnedplayerGuess != theNumber){
		returnedplayerGuess = MyFunction();
	//	cin >> playerGuess;

		if (returnedplayerGuess < theNumber){
			cout << "too low" << endl;
		}
		else if (returnedplayerGuess > theNumber){
			cout << "too high" << endl;
		}
		else if (returnedplayerGuess == theNumber){
			cout << "you guessed it!!!" << endl;
		}
		else{
			cout << "something bad happened";
			returnedplayerGuess = 0;
		}
		cout << endl;
		guesses = guesses + 1;
		cout << "total guesses is " << guesses << endl;
	}
	/*
	int x = 0;
	switch (x)
	{
	case 1: cout << "ONe";
	case 0: cout << "Zero";
	case 3: cout << "Hello World";
	}
	*/
	return 0;
}




