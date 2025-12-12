#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string>

class Student {  // Student our new user defined type
	public:
		// Actions - Constructor
		Student();
		Student(std::string name);
		// Action - Destructor
		~Student();

		void printName();

		std::string m_name;
};
#endif
