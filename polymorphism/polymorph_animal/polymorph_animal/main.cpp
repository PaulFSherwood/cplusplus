#include <iostream>

using namespace std;

class Animal {
	public:
		virtual void talk() = 0;
};

class Dog : Animal {
	public:
		virtual void talk() {
			cout << "Bow wow!" << endl;
		}
};
class Cat : Animal {
	public:
		virtual void talk() {
			cout << " Meow!" << endl;
		}
};


int main() {
	Dog fido;
	Cat kitty;

	fido.talk();
	kitty.talk();

	return 0;
}