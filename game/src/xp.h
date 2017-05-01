/*
 * xp.h
 *
 *  Created on: May 12, 2011
 *      Author: grrwood
 */

#ifndef XP_H_
#define XP_H_
#include <iostream>
#include <cmath>
using namespace std;

class xp
{
public:
	xp(int WxptotalP, int WlvlP,  int OlvlP);
	int getxprecieved();
	int getmaxxp();
	int canlvl(int currentxp, int maxxp, int *WhpP, int *WstrP);
private:
	int currentxp;
	int Wlvl;
	int Olvl;
	int basexp;
	int xpmax;
	int xprecieved;
//
};

#endif /* XP_H_ */
