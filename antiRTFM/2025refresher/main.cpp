#include <iostream>
#include <random>  // For rand() and srand()
using namespace std;

// Section 4
int getInteger();

class Ogre
{
    public:
        void attack();
        void setHealth(int hp);
        void setStrength(int str);
    private:
        int health;
        int strength;        
};

int main()
{
    Ogre me;
	cout << getInteger();
    cout << endl;
    me.setHealth(10);
    me.setStrength(10);
	me.attack();

    return 0;
}

int getInteger()
{
	static mt19937 gen(random_device{}()); // Seed once
	static uniform_int_distribution<int> dist(1, 100);
	return dist(gen);
}

void Ogre::attack()
{
    cout << "Ogre attack with " << strength << endl;
};
void Ogre::setHealth(int hp)
{
    health = hp;
};
void Ogre::setStrength(int str)
{
    strength = str;
};
