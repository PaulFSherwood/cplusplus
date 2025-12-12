#include <iostream>
#include "Array.hpp"

Array::Array(){
	std::cout << "Constructor" << std::endl;
	for (int i = 0; i < 1; i++) {
		data.push_back(i);
	}
}

Array::~Array(){
}
// Copy Constructor
// Array myNewArray = someExistingArray
Array::Array(const Array& rhs) {
	std::cout << "Copy Constructor" << std::endl;
	for (int i = 0; i < rhs.data.size(); i++) {
		data.push_back(rhs.data[i]);
	}
}
// Copy Assignment operator
Array& Array::operator=(const Array& rhs) {
	std::cout << "Copy assignment operator" << std::endl;
	if (&rhs == this) {
		return *this;
	}
	data.clear();
	for (int i = 0; i < rhs.data.size(); i++) {
		data.push_back(rhs.data[i]);
	}
	return *this;
}
void Array::PrintingData() {
	std::cout << "{";
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i];
	}
	std::cout << "}" << std::endl;
}

void Array::SetData(int index, int value) {
    if (index >= data.size()) {
        data.resize(index + 1);
    }
    data[index] = value;
}
