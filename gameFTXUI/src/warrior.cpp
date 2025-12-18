/*
 * warrior.cpp
 *
 *  Created on: May 10, 2011
 *      Author: grrwood
 */
#include <iostream>
#include "warrior.h"
using namespace std;

warrior::warrior(int starthp, int startstr, int startlvl, int startxptotal, int startmaxxp, string startname)
: hp(starthp), str(startstr), lvl(startlvl), xptotal(startxptotal), maxxp(startmaxxp), name(startname)
{}

string warrior::getname(string name)
{
	return name;
}
string warrior::Nname()
{
	return name;
}

void warrior::attack()
{
	cout << "\n attacking with " << str << " strength\n";
}
void warrior::heal(int amounthp)
{
	hp += amounthp;
}
void warrior::beattacked()
{
	cout << "\narrrrgh\n";
	hp -= 1;
}
int warrior::gethp()
{
	return hp;
}
int warrior::getstr()
{
	return str;
}
int warrior::getlvl()
{
	return lvl;
}
int warrior::getxptotal()
{
	return xptotal;
}
int warrior::getmaxxp()
{
	return maxxp;
}
void warrior::incrementP(int * x)
{
	(*x)++;
}
