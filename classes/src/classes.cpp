//============================================================================
// Name        : classes.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;

class Ogre{
	public:
		string name;
		int health;
		int strength;
		void attack()		// how do i actualy get to use this latter on. like in the fight_table
		{					// can this function be passed through main into another class
			cout << "Ogre Attack!!\n";
		}
};

class Player{
	public:
		string name;
		int health;
		int strength;
		void attack()
		{
			cout << "Player attack 1\n";
		}
};

int eat(int a)
{
    cout << "eating some yum yums";
    a = 80;
    return a;
}

void Fight_Table(int Php, int Thp, int Pstr, int Tstr)
{
	cout << "get ready to rumble... or not\n";
		cout << "(R)un, (F)ight\n";
		char e;
		cin >> e;
		switch (e){
			case 'R':
				cout << "A RABBIT RUN AWAY! RUN AWAY!";
				break;
			case 'F':
				cout << "let the fight begin" << endl;
				cout << "Player: " << Php << "\t"<< "Ogre: " << Thp << endl;
				while ((Thp >= 1) && (Php >=1)){
					cout << "how many times do you want to try to hit" << endl;
					int hit;
					cin >> hit;
					cout << "hit\t" <<    "Pstr\t" <<     "Php\t" <<     "Tstr\t" <<     "Thp" << "\t\n";
					cout << hit << "\t" << Pstr << "\t" << Php << "\t" << Tstr << "\t" << Thp << "\t\n\n";
					Thp = Thp - (hit * Pstr);
						cout << "Orge HP: " << Thp << endl;
					Php = Php - (hit * Tstr);
						cout << "Player HP: " << Php << endl;
				}
				break;
			default:
				printf("i have detected an error and its you\n");
				break;
		}
}

int main() {
	int running = 1;

	Ogre t;
	t.name="Orge_01";
	t.health = 70;
	t.strength= 3;
	cout << "I am " << t.name << endl;
	printf("my health = %d\n", t.health);
	printf("my strength = %d\n", t.strength);
	t.attack();

	cout << endl;

	Player p;
	p.name="Knight";
	p.health=50;
	p.strength=8;
	cout << "I am " << p.name << endl;
	printf("my health = %d\n", p.health);
	printf("my strength = %d\n", p.strength);
	p.attack();

	while (running ==1){

		cout << "what would you like to do\n";
		cout << "(E)xplore, (e)at, or...tbc\n";
		char e;
		cin >> e;
		switch (e){
			case 'E':
				Fight_Table(p.health, t.health, p.strength, t.strength);
				break;
			case 'e':
				cout << eat(p.health) << endl;

				cout << endl << p.health << endl;
				break;
			default:
				printf("i have detected an error and its you\n");
				break;
		}
		cout << endl << "==============================" << endl;
		cout << "\nkeep going (1)yes (0)no";
		cin >> running;
		cout << endl;
	}
	return 0;
}
