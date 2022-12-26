#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

class dog
{
	private:
		int numberOfDogs;
		int numberOflegs;
	public:
		string getDogName(string name) {
			return name;
		}
};

class people
{
	private:
		int numberOfPeoples;
		int numberOfLegs;
	public:
		string getPersonName(string name){
			return name;
		}
};

int main() {
	people p;
	cout << "I am " << p.getPersonName("Baul") << endl;
}
// dog::dog()
// {

