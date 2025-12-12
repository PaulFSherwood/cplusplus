#include <iostream>
#include "Array.hpp"

Array::Array(){
	std::cout << "Constructor" << std::endl;
	data = new int[10];
	for (int i = 0; i < 10; i++) {
		data[i] = i * i;
	}
}

Array::~Array(){
	delete[] data;
}
// Copy Constructor
// Array myNewArray = someExistingArray
Array::Array(const Array& rhs) {
	std::cout << "Copy Constructor" << std::endl;
	data = new int[10];
	for (int i = 0; i < 10; i++) {
		data[i] = rhs.data[i];
	}
}
// Copy Assignment operator
Array& Array::operator=(const Array& rhs) {
	std::cout << "Copy assignment operator" << std::endl;
	if (&rhs == this) {
		return *this;
	}
	delete[] data;
	data = new int[10];
	for (int i = 0; i < 10; i++) {
		data[i] = rhs.data[i];
	}
	return *this;
}
void Array::PrintingData() {
	for (int i = 0; i < 10; i++) {
		std::cout << data[i] << std::endl;
	}
}

void Array::SetData(int index, int value) {
   data[index] = value;
}
