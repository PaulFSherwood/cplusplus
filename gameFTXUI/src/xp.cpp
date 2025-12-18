/*
 * xp.cpp
 *
 *  Created on: May 12, 2011
 *      Author: grrwood
 */

#include <iostream>
#include <cmath>
#include "xp.h"
using namespace std;

xp::xp(int WxptotalP, int WlvlP,  int OlvlP)
{
	currentxp = WxptotalP;
	Wlvl = WlvlP;
	Olvl = OlvlP;
}


int  xp::getxprecieved()
{

	int basexp = 0;
	int xpmax = 0;
	int xprecieved = 0;

	basexp = (((Wlvl*5)+45)*(2));
	xpmax = ((10)*(pow(2, Wlvl)));
	xprecieved = (((Wlvl*5)+45)*(2+(Olvl-Wlvl)));

	if (Olvl >= Wlvl){
		currentxp = currentxp + xprecieved;
	}
	else if (Olvl < Wlvl){
		xprecieved = (basexp - (10*(Wlvl)));
		currentxp = currentxp + xprecieved;
	}
	return currentxp;
}

int xp::getmaxxp()
{
	int xpmax = 0;
	xpmax = ((10)*(pow(2, Wlvl)));

	return xpmax;
}

int xp::canlvl(int currentxp, int maxxp, int *WhpP, int *WstrP)
{
	if (currentxp > maxxp){
		Wlvl += 1;
		double tempHP = 0;
		tempHP = (*WhpP * .1);
		*WhpP += (tempHP + 10);
		*WstrP += 5;

	}
	else {
		return 0;
	}
	return Wlvl;
}
