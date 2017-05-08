#include <string>
#include <iostream>
using namespace std;

class Animal {

public:
	Animal(int health = 10, bool alive = false);

	void walking();
	void talk();
	int getHealth();
	bool getAlive();
	
protected:
	int m_Health;
	bool m_Alive;
};

Animal::Animal(int health, bool alive) {
	m_Health = health;
	m_Alive = alive;
}
void Animal::walking() {
	cout << "animal Walking" << endl;
}
void Animal::talk() {
	cout << "Animal talk" << endl;
}
int getHealth() {
	return m_Health;
}
bool getAlive() {
	return m_Alive;
}

int main() {

	Animal * bear = new Animal;
}
