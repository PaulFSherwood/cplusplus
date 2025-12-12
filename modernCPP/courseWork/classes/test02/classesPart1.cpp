#include "classesPart1.hpp"
#include <iostream>

// Action - Constructor
Student::Student() {
	std::cout << "Constructor" << std::endl;
}
Student::Student(std::string name) {
   m_name = name;
	std::cout << "Constructor with name: " << m_name << std::endl;
}
// Action - Destructor
Student::~Student() {
	std::cout << "Destructor: " << m_name <<  std::endl;
}
// Print students names 
void Student::printName() {
	std::cout << "Student name: " << m_name << std::endl;
}

