//============================================================================
// Name        : tic.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class board{
public :
	void boardprint(char array[])
	{
		cout << array[0] << "|" << array[1] << "|" << array[2] << "\t0,1,2" << endl;
		cout << array[3] << "|" << array[4] << "|" << array[5] << "\t3,4,5" << endl;
		cout << array[6] << "|" << array[7] << "|" << array[8] << "\t6,7,8" << endl;
	}
};

class checkboard{
public :
	void checkwin(char array[], char player)
	{
		// Check for wins horizontal for X
		if (array[0]==player && array[1]==player && array[2]==player){
			cout << player << " wins Top row\n";
			array[9]='F';
		}
		else if (array[3]==player && array[4]==player && array[5]==player){
			cout << player << " wins Second row\n";
			array[9]='F';
		}
		else if (array[3]==player && array[4]==player && array[5]==player){
			cout << player << " wins Bottom row\n";
			array[9]='F';
		}
		// Check for wins vertical for X
		else if (array[0]==player && array[3]==player && array[6]==player){
			cout << player << " wins Left row\n";
			array[9]='F';
		}
		else if (array[1]==player && array[4]==player && array[7]==player){
			cout << player << " wins Middle row\n";
			array[9]='F';
		}
		else if (array[2]==player && array[5]==player && array[8]==player){
			cout << player << " wins Bottom row\n";
			array[9]='F';
		}
		// Check for a diagnal win for X
		else if (array[0]==player && array[4]==player && array[8]==player){
			cout << player << " wins left to right row\n";
			array[9]='F';
		}
		else if (array[2]==player && array[4]==player && array[6]==player){
			cout << player << " wins right to left row\n";
			array[9]='F';
		}
		else {
			cout << "No win found\n";
		}
	}
};

class playerinfo{
public :
	char playericon(char icon)
	{
		cout << "please pick your user character" << endl;
		cin >> icon;
		return icon;
	}
};
class whoturn{
public :
	char playerturn(char currentplayer, char playerone, char playertwo)
	{
		if (currentplayer==playerone){
			currentplayer=playertwo;
		}
		else if (currentplayer==playertwo){
			currentplayer=playerone;
		}
		else{
			cout << "error";
		}
		return currentplayer;
	}
};

int main() {
	// init
	char playerone='X';
	char playertwo='O';
	// should this be here
	int arraynum=0;
	char array[10]={'*','*','*','*','*','*','*','*','*','T'};
	board a;
	playerinfo c;
	playerone=c.playericon(playerone);
	playertwo=c.playericon(playertwo);
	char currentplayer=playerone;
	// running the game till array[9] is F
	while (array[9]=='T'){
		// get user input and place it into the array
		cin.get();
		cout << "Please select a number to put your char into" << endl;
		cin >> arraynum;
		array[arraynum]=currentplayer;

		// check the board for a win
		checkboard b;
		b.checkwin(array, currentplayer);
		a.boardprint(array);

		// update the player so the next person can play
		whoturn d;
		currentplayer=d.playerturn(currentplayer, playerone, playertwo);
	}
	return 0;
}
