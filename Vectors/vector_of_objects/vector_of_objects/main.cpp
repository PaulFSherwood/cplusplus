#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
using namespace std;

void fillVector(vector<Student>&);
// fillVector - fill in student information
// @param - vector<Student>& - students in class

void printVector(const vector<Student>&);
// printVector - print the information of all students
// @param  const vector<Student>& - students in class

int main() {

	vector<Student> myClass;

	fillVector(myClass);

	printVector(myClass);

	return 0;
}

void fillVector(vector<Student>& newMyClass) {

	string name;
	char grade;

	cout << "How many students are in your class? ";
	int classSize;
	cin >> classSize;

	for (int i = 0; i < classSize; i++) {
		cout << "\nEnter Student Name: ";
		cin >> name;
		cout << "\nEnter Student Grade: ";
		cin >> grade;
		cout << endl;

		Student newStudent(name, grade);
		newMyClass.push_back(newStudent);
		//cout << "Print new student" << name << "||" << grade << endl;
		//printVector(newMyClass);
		cout << endl;
	}
		cout << endl;
}

void printVector(const vector<Student>& newNewMyClass) {

	unsigned int size = newNewMyClass.size();

	for (unsigned int i = 0; i < size; i++) {
		cout << "Student Name: " << newNewMyClass[i].getName() << endl;
		cout << "Student Grade: " << newNewMyClass[i].getGrade() << endl;
		cout << endl;
	}
}