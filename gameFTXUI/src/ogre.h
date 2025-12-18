/*
 * orge.h
 *  1970 Chevelle SS Hardtop Coupe
 *  Created on: May 10, 2011
 *      Author: grrwood
 */

#ifndef OGRE_H_
#define OGRE_H_
#include <iostream>
using namespace std;

class ogre
{
public:
	ogre(int starthp, int startstr, int startlvl, string startname);
	string getname(string name);
	string Nname();
	void attack();
	void heal(int amounthp);
	void beattacked();
	int gethp();
	int getstr();
	int getlvl();
private:
	int hp;
	int str;
	int lvl;
	string name;
};

#endif /* OGRE_H_ */
