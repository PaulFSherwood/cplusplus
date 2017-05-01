// Abstract Creature
// Demonstrates abstract classses

#include <iostream>
using namespace std;

class Creature		// abstract class
{
public:
	Creature(int health = 100): m_Health(health)
	{}

	virtual void Greet() const = 0;  // a pure virtual memeber function

	virtual void Displayhealth() const
	{ cout << "Health: " << m_Health << endl; }

protected:
	int m_Health;
};

class Orc : public Creature
{
public:
	Orc(int health = 120): Creature(health)
	{}

	virtual void Greet() const
	{ cout << "The orc grunts hello.\n"; }
};

int main()
{
	Creature* pCreature = new Orc();
	pCreature->Greet();
	pCreature->Displayhealth();

	return 0;
}
