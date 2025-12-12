#include "classesPart1.hpp"

int main() {
	Student mike;
	mike.m_name = "Mike";
	Student *paul = new Student;
	paul->m_name = "Paul";

	Student sue("Sue");

	delete paul;

	return 0;
}
