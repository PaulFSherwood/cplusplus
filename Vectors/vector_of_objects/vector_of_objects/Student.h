// Header
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
public:
	// Default Constructor
	Student();

	// Overload Constructors
	Student(string, char);

	// Deconstructor
	~Student();

	// Acessor Functions
	string getName() const;
		// getName
		// @return string - name of student
	char getGrade() const;
		// getGrade
		// @return char - grade of student

	// Mutator Functions
	void setName(string);
		// setName
		// @param string - name of student

	void setGrade(char);
		// setGrade
		// @param char - grade of student

private:
	// Member Variables
	string newName;
	char newGrade;
};

#endif