//============================================================================
// Name        : game.cpp
// Author      : paul
// Version     :
// Lord Macaulay said this concerning Jeremiah: “It is difficult to conceive
// any situation more painful than that of a great man, condemned to watch
// the lingering agony of an exhausted country, to tend it during the alternate
// fits of stupefaction and raving which precede its dissolution, and to see
// the symptoms of vitality disappear one by one, till nothing is left but
// COLDNESS, DARKNESS, and CORRUPTION"
//			   :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include "warrior.h"
#include "ogre.h"
#include "xp.h"
using namespace std;

void Fight_Table(int *WhpP, int *OhpP, int *WstrP, int *OstrP, int *WxptotalP, int *maxxp, int *WlvlP, int *OlvlP, const int ConstOhpP)
{
	// reseting orges hp is there a better way???
	*OhpP = ConstOhpP;
	cout << "get ready to rumble...or not\n";
	cout << "(R)un, (F)ight\n";
	char e;
	cin >> e;
	switch (e){
	case 'R':
		cout << "A RABBIT RUN AWAY!! RUN AWAY!!";
		break;
	case 'F':
		cout << "let the fight begin" << endl;
		cout << "Player: " << *WhpP << "\t" << "Ogre: " << *OhpP << endl;
		while ((*OhpP >= 1) && (*WhpP >= 1)) {
			cout << "how many times do you want to try to hit" << endl;
			int hit;
			cin >> hit;
			while ((hit >= 1) && (*OhpP >= 1) && (*WhpP >= 1)){
				cout << "hit\t" << "*WstrP\t" << "*WhpP\t" << "Tstr\t" << "Thp" << "\t\n";
				cout << hit << "\t" << *WstrP << "\t" << *WhpP << "\t" << *WstrP << "\t" << *WhpP << "\t\n\n";
				*OhpP = *OhpP - *WstrP;
				cout << "Orge HP: " << *OhpP << endl;
				*WhpP = *WhpP - *OstrP;
				cout << "Player HP: " << *WhpP << endl;
				hit = hit - 1;
			}
			if ((*OhpP) == 0){
				// pass info to do xp calculation
				xp xp1(*WxptotalP, *WlvlP, *OlvlP);
				*WxptotalP = xp1.getxprecieved();
				*maxxp = xp1.getmaxxp();
				*WlvlP = xp1.canlvl(*WxptotalP, *maxxp, WhpP, WstrP);
			}
		}
		break;
	default:
		printf ("i have detected an error and its you\n");
		break;
	}
}
int Forest(	  int *WhpP, int *WstrP, string *WnnameP, int *WlvlP
			, int *OhpP, int *OstrP, string *OnnameP, int *OlvlP
			, int *WxptotalP, int *maxxp, const int ConstOhpP)
{
	int running = 1;

	while (running == 1){
		printf("\033[2J\033[1;1H");  // ncurses breaks program this solution works.
		cout << "##Forest##" << "\t\t\t" << "##Vital Info##" << endl;
		cout << "(L)ook for a fight" << "\t\t" << "Name: " << *WnnameP << endl;
		cout << "(R)eturn to village" << "\t\t" << "Level: " << *WlvlP << endl;
		cout << "\t\t\t\t" << "Hitpoints: " << *WhpP << endl;
		cout << "\t\t\t\t" << "Turns: " << endl;// not implemented wo1.turns();
		cout << "\t\t\t\t" << "Attack: " << *WstrP << endl;
		cout << "\t\t\t\t" << "Defense: " << endl;// not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Race: " << endl; // not implemented wo1.Nname();
		cout << "\t\t\t\t" << "##Personnel Info##" << endl;
		cout << "\t\t\t\t" << "Gold: " << endl;// not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Gem: " << endl;	// not implemeneted wo1.Nname();
		cout << "\t\t\t\t" << "##Equipment##" << endl;
		cout << "\t\t\t\t" << "Weapon: " << endl; // not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Armor: " << endl; // not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Experience: " << *WxptotalP << "|" << *maxxp << endl; // not implemeneted wo1.Nname();
		char e;
		cin >> e;
		switch (e){
		case 'L':	// Look for a fight
			Fight_Table(WhpP, OhpP, WstrP, OstrP, WxptotalP, maxxp, WlvlP, OlvlP, ConstOhpP);
			cin.ignore().get();
			break;
		case 'R':	// Return to world menu
			running = 0;
			break;
		default:
			printf("i have detected an error and its you\n");
			break;
		}
		cout << endl;
	}
	return 0;
}

int main() {
	// all this information should be pulled from a file later on!!!!!!
	// also how should the ogre's stats be worked out? based on players stats?
	ogre oo1(900, 100, 2, "Orge_01");	// INITIAL STATS
	warrior wo1(	900, 	150, 	2,  	  0, 	100,	"Wario");	// INITIAL STATS
				// 	hp, 	str,  lvl,  xptotal,  maxxp,	name

	int running = 1;
	// variables for warrior
	int WhpP_ref = wo1.gethp();
	int WstrP_ref = wo1.getstr();
	int WxptotalP_ref = wo1.getxptotal();	// character currnt xp
	int maxxp_ref = wo1.getmaxxp();			// character maximum xp
	string WnnameP_ref = wo1.Nname();
	int WlvlP_ref = wo1.getlvl();
	// this is dumb i have to do this round da bout stuff to get to the address
	int *WhpP = &WhpP_ref;
	int *WstrP = &WstrP_ref;
	int *WxptotalP = &WxptotalP_ref;	// character currnt xp
	int *maxxp = &maxxp_ref;			// characer maximum xp
	string *WnnameP = &WnnameP_ref;
	int *WlvlP = &WlvlP_ref;

	// variables for orge
	int OhpP_ref = oo1.gethp();
	int OstrP_ref = oo1.getstr();
	string OnnameP_ref = wo1.Nname();
	int OlvlP_ref = oo1.getlvl();

	int *OhpP = &OhpP_ref;
	const int ConstOhpP = *OhpP;// this is probably a bad solution but i need a const var for
	const int ConstWhpP = *WhpP;// the hp, and i couldnt get it to work in the class files
	int *OstrP = &OstrP_ref;
	string *OnnameP = &OnnameP_ref;
	int *OlvlP = &OlvlP_ref;

	while (running == 1){
		// this section is the menu setup... its probably going to be ugly sorry.
		printf("\033[2J\033[1;1H");  // ncurses breaks program this solution works.
		cout << "##Village Gate##" << "\t\t" << "##Vital Info##" << endl;
		cout << "(F)orest" << "\t\t\t" << "Name: " << *WnnameP << endl;
		cout << "(Q)uit to the fields" << "\t\t" << "Level: " << *WlvlP << endl;
		cout << "(W)arrior training" << "\t\t" << "Hitpoints: " << *WhpP << endl;
		cout << "##Market Street##" << "\t\t" << "Turns: " << endl;// not implemented wo1.turns();
		cout << "MightE's (W)eaponry" << "\t\t" << "Attack: " << *WstrP << endl;
		cout << "Pegasus (A)rmor" << "\t\t\t" << "Defense: " << endl;// not implemented wo1.Nname();
		cout << "Ye Old (B)ank" << "\t\t\t" << "Race: " << endl; // not implemented wo1.Nname();
		cout << "(H)eal your self\t\t" << "##Personnel Info##" << endl;
		cout << "\t\t\t\t" << "Gold: " << endl;// not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Gem: " << endl;	// not implemeneted wo1.Nname();
		cout << "\t\t\t\t" << "##Equipment##" << endl;
		cout << "\t\t\t\t" << "Weapon: " << endl; // not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Armor: " << endl; // not implemented wo1.Nname();
		cout << "\t\t\t\t" << "Experience: " << *WxptotalP << "|" << *maxxp << endl;
		//<< "|....|....|" << endl; // not implemeneted wo1.Nname();
		char e;
		cin >> e;
		switch (e){
		case 'F':	// Forest
			Forest(WhpP, WstrP, WnnameP, WlvlP, OhpP, OstrP, OnnameP, OlvlP, WxptotalP, maxxp, ConstOhpP);
			break;
		case 'Q':	// Quit to the fields
			running = 0;
			break;
		case 'T':	// Warrior Training
					// this should be used to level your character after you ahve enoguh exp.
	//		Warrior_Training();
			break;
		case 'W':	// MightE's Weaponry
					// this should be used to multiply your dmg
	//		Weapon_Shop();
			break;
		case 'A':	// Pegasus Armor
					// this should be used to alter how much dmg take or i guess reduction in dmg
	//		Pegasus_Armor();
			break;
		case 'B':	// ye old bank
					// have to implemement getting money off of each kill
	//		Bank();
			break;
		case 'H':	// easy heal bot
			*WhpP = ConstWhpP;
			cout << "With a wave of the wand your are not so much deader" << endl;
			cin.ignore().get();
			break;
		default:
			printf("i have detected an error and its you\n");
			break;
		}
	}
	return 0;
}
