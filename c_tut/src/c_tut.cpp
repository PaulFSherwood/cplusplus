//============================================================================
// Name        : c_tut.cpp
// Author      : paul
// Version     : 0.01
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int numcheck (int i)
{
    while ( ! (cin >> i))
    {
        cout << "Error please try again: ";
        cin.clear ();
        cin.ignore (1000, '\n');
    }
     return i;
}

int randomNumber(int a,int b){
	srand(time(0));
	int theNumber = rand() % (b - a + 1) + a;
	return theNumber;
}

int guessCheck(int randomNum){
	int guesses = 0;
	int guess;

	while (guess != randomNum){
		cout << "guess a number: " << endl;
		cin >> guess;

		if (guess < randomNum){
			cout << "too low" << endl;
		}
		else if (guess > randomNum){
			cout << "too high" << endl;
		}
		else if (guess == randomNum){
			cout << "OMG HAX...\nyou guessed it!!!" << endl;
		}
		else{
			cout << "something bad happened";
			guess = 0;
		}
		cout << endl;
		guesses = guesses + 1;
		cout << "total guesses is " << guesses << endl;
	}
	return 0;
}

int main() {
	int lownum=0;
	int highnum=100;
	int usernum=0;
	int count=0;
	int compguess=50;
	int currentguess=0;
	int randomNum=0;
	char whoguess=0;

	cout << "who is going to guess 1)User 2)PC" << endl;
	cin >> whoguess;
	switch (whoguess){
	case '1':
		cout << "pick your low and high number" << endl;
		cout << "Enter low number: ";
		lownum = numcheck(lownum);
		cout << "Enter high number: ";
		highnum = numcheck(highnum);

		printf("low number is: %d and high number is: %d\n",lownum, highnum);
		randomNum = randomNumber(lownum,highnum);
		guessCheck(randomNum);
		break;
	case '2':
		cout << "please pick a number for the computer to guess at 0-100: ";
		cin >> usernum;
		while (count == 0){
			if (compguess == usernum){
				cout << "pc wins" << endl;
				count = count + 1;
				break;
			}
			else if (compguess < usernum){
				cout << "The computer guessed " << compguess << " and it was too low" << endl;
				lownum = compguess;
				compguess = (((highnum-lownum)/2)+lownum);
			}
			else if (compguess > usernum){
				cout << "The computer guessed " << compguess << " and it was too high" << endl;
				highnum = compguess;
				compguess = (((highnum-lownum)/2)+lownum);
			}
			else{
				cout << "there was an error!" << endl;
				break;
			}
		}
		break;
	}
	return 0;
}
