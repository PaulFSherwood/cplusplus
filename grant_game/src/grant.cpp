/*
 * grant.cpp
 *
 *  Created on: May 18, 2011
 *      Author: sherwood
 */

#include <iostream>
#include "grant.h"
using namespace std;

grant::grant()
{}
// Setters
void grant::setHunger(int h)
{
	Hunger = h;
}
void grant::setSmarts(int s)
{
	Smarts = s;
}
void grant::setFun(int f)
{
	Fun = f;
}
void grant::setMoney(int m)
{
	Money = m;
}
void grant::setHappy(int hap)
{
	Happy = hap;
}

// Getters
int grant::getHunger()
{
	return Hunger;
}
int grant::getSmarts()
{
	return Smarts;
}
int grant::getFun()
{
	return Fun;
}
int grant::getMoney()
{
	return Money;
}
int grant::getHappy()
{
	return Happy;
}
