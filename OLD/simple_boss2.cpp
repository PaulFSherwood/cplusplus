// Simple Boss 2.0
// Demonstrates access control under inheritance

#include <iostream>
using namespace std;

class Enemy
{
public:
	Enemy(int damage = 10): m_Damage(damage)
	{}

	void Taunt() const
	{ cout << "The enemy says he will fight you.\n"; }

	void Attack() const
	{ cout << "Attack! inflicts " << m_Damage << " damage points!\n"; }

protected:
	int m_Damage;
};

class Boss : public Enemy
{
public:
	int m_DamageMultiplier;
	Boss(int damage = 30): Enemy(damage) // call base constructor with argument
	{}

	void Taunt() const
	{ cout << "The boss says he will end your pitiful existence.\n"; }

	void Attack() const
	{ 
		Enemy::Attack();
	  	cout << " and laughs heartily at you.\n"; 
	}
};

int main()
{
	cout << "Creating an enemy.\n";
	Enemy enemy1;
	enemy1.Taunt();
	enemy1.Attack();

	cout << "\n\nCreating a boss.\n";
	Boss boss1;
	boss1.Taunt();
	boss1.Attack();

	return 0;
}
