// Diffie-Helman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Practical programming -Pt 8.2: Diffie Helman c++
// https://www.youtube.com/watch?v=-iR-XTiZk6c
#include <iostream>
using namespace std;

// Defining DH constants
int g = 5;

// n is essentially useless
int n = 19301;

void randomReset() {
	int thing = rand() + time(NULL);
	srand(thing);
}

void singleProgram() {
	randomReset();
	int a = rand() % 5;
	int ga = pow(g, a);

	randomReset();
	int b = rand() % 5;
	int gb = pow(g, b);

	long long gba = pow(gb, a);
	long long gab = pow(ga, b);

	cout << "a is " << a << "\nb is " << b << "\n" << gab << " " << gba << "\n\n\n\n";
}

void programA() {
	randomReset();
	int a = rand() % 5;
	int ga = pow(g, a);

	cout << "ga is " << ga << endl;
	int gb;
	cout << "Input gb from the other client: ";
	cin >> gb;
	cout << "\n";

	int sharedSecret = pow(gb, a);
	cout << "Shared secret is " << sharedSecret << "\n\n\n\n\n\n";
}

void programB() {
	randomReset();
	int b = rand() % 5;
	int gb = pow(g, b);

	cout << "gb is " << gb << endl;
	int ga;
	cout << "Input ga from the other client: ";
	cin >> ga;
	cout << "\n";

	int sharedSecret = pow(ga, b);
	cout << "Shared secret is " << sharedSecret << "\n\n\n\n\n\n";

}

int main() {
	bool isRunning = true;
	while (isRunning) {
		cout << "booger\nWhat program do you want to execute?\n1 - Single Program\n2 - Program A\n3 - Program B" << endl;

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			system("cls");
			singleProgram();
			break;
		case 2:
			system("cls");
			programA();
			break;
		case 3:
			system("cls");
			programB();
			break;
		default:
			cout << "Not a valid option\nExiting the program\n";
			isRunning = false;
			break;
		}
	}
	return 0;
}