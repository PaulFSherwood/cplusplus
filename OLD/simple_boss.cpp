// Simple Boss
// Demonstrates inheritance

#include <iostream>

using namespace std;

class Enemy
{
public:
	int m_Damage;
	Enemy(): m_Damage(10) {}
	void Attack() const
	{ cout << "Attack inflicts " << m_Damage << " damage points!\n"; }
};

class Boss : public Enemy
{
public:
	int m_DamageMultiplier;
	Boss(): m_DamageMultiplier(3) {}
	void SpecialAttack() const
	{ cout << "Special Attack inflicts " << (m_DamageMultiplier * m_Damage);
	cout << " damage points!\n"; }
};

class Superboss : public Boss
{
public:
	int m_smDamageMultiplier;
	Superboss(): m_smDamageMultiplier(20) {}
	void smSpecialAttack() const
	{ cout << "SuperSpecial Attack inflicts " << (m_smDamageMultiplier * m_Damage);
	cout << " damage points!\n"; }
};

int main()
{

	cout << "Creating an enemy.\n";
	Enemy enemy1;
	enemy1.Attack();

	cout << "\nCreating a boss.\n";
	Boss boss1;
	boss1.Attack();
	boss1.SpecialAttack();

	cout << "\nCreating a superboss.\n";
	Superboss superboss1;
	superboss1.Attack();
	superboss1.SpecialAttack();
	superboss1.smSpecialAttack();

	return 0;
}
