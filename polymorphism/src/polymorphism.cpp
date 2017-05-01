//============================================================================
// Name        : polymorphism.cpp
// Author      : paul
// Version     :
// Copyright   : no copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Enemy{
public:
	virtual void attack(){

	}
//protected:
//	int attackPower;
//public:
//	void setAttackPower(int a){
//		attackPower=a;
//	}
};
class Ninja: public Enemy{
public:
	void attack(){
		cout << "ninja attack -" << endl;
	}

//public:
//	void attack(){
//		cout << "im an ninja, ninja chop! -" << attackPower << endl;
//	}
};
class Monster: public Enemy{
public:
	void attack(){
		cout << "monster attack -" << endl;
	}
//public:
//	void attack(){
//		cout << "monster must eat you!!! -" << attackPower << endl;
//	}
};

int main() {
	Ninja n;
	Monster m;

	Enemy *enemy1 = &n;
	Monster *enemy2 = &m;
	enemy1->attack();
	enemy2->attack();
	return 0;

//	Ninja n;
//	Monster m;

//	Enemy *enemy1 = &n;			// because ninja is of type enemy, this is valid
//	Enemy *enemy2 = &m;			// anthink that an enemy can do , monster can do
//	enemy1->setAttackPower(29);	// ninja is just a more specific type of enemy
//	enemy2->setAttackPower(99);	// every enemy has setAttackPower
//	n.attack();					// cant use enem1 becuase its type enemy
//	m.attack();					// Enemy class does not have attack
//	return 0;					// vitual members make this even easier.
}
