/*
 * ogre.cpp
 *
 *  Created on: May 10, 2011
 *      Author: grrwood
 */

#include <iostream>
#include "ogre.h"
using namespace std;

ogre::ogre(int starthp, int startstr, int startlvl, string startname)
: hp(starthp), str(startstr), lvl(startlvl), name(startname)
{}

string ogre::getname(string name)
{
	return name;
}
string ogre::Nname()
{
	return name;
}
void ogre::attack()
{
	cout << "\n Ogre attacking with " << str << " strength\n";
}
void ogre::heal(int amounthp)
{
	hp += amounthp;
}
void ogre::beattacked()
{
	cout << "\narrrrgh\n";
	hp -= 1;
}
int ogre::gethp()
{
	return hp;
}
int ogre::getstr()
{
	return str;
}
int ogre::getlvl()
{
	return lvl;
}
