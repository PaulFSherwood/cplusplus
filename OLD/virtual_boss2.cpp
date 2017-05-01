// Virtual Boss
// Demonstrates virtual functions

#include <iostream>

using namespace std;

class Enemy
{
public:
	Enemy(int damage = 10)
	{ m_pDamage = new int(damage); }

	virtual ~Enemy()
	{
		cout << "m_pDamage deleted\n";
		delete m_pDamage;
	}
	
	void Taunt() const
	{ cout << "The enemy says he will fight you.\n"; }

	void virtual VTaunt() const
	{ cout << "The enemy says he will fight you.\n"; }

protected:
	int* m_pDamage;
};

class Boss : public Enemy
{
public:
	Boss(int multiplier = 3)
	{ m_pDamageMultiplier = new int(multiplier); }

	virtual ~Boss()
	{
		cout << "m_pdamageMultiplier deleted\n";
		delete m_pDamageMultiplier;
	}

	void Taunt() const
	{ cout << "The boss says he will end your pitifull existence.\n"; }

	void virtual VTaunt() const
	{ cout << "The boss says he will end your pitifull existence.\n"; }

protected:
	int* m_pDamageMultiplier;
};

int main()
{

	cout << "Pointer to Enemy that points to a Boss object:\n";
	Enemy* pBadGuy = new Boss();
	pBadGuy->Taunt();
	pBadGuy->VTaunt();

	cout << "\nDeleting pointer to Enemy:\n";
	delete pBadGuy;
	pBadGuy = 0;

	return 0;
}
