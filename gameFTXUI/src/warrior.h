/*
 * warrior.h
 *
 *  Created on: May 10, 2011
 *      Author: grrwood
 */

#ifndef WARRIOR_H_
#define WARRIOR_H_
#include <iostream>
using namespace std;

class warrior
{
public:
	warrior(int starthp, int startstr, int startlvl, int xptotal, int maxxp, string startname);
	string getname(string name);
	string Nname();
	void attack();
	void heal(int amounthp);
	void beattacked();

	int gethp();
	int getstr();
	int getlvl();
	int getxptotal();
	int getmaxxp();
	void incrementP(int * ptr);

private:
	int hp;
	int str;
	int lvl;
	int xptotal;
	int maxxp;
	string name;
};


#endif /* WARRIOR_H_ */
