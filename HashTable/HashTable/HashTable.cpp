#include <iostream>
#include <list>
#include <cstring>
using namespace std;

// Hashtable to implement 905, Jimmyu

class HashTable {
private:
	static const int hashGroups = 10;
	list<pair<int, string>> table[hashGroups]; // List 1, Index 0, List 2, Index 1....

public:
	bool isEmpty() const;
	int hashFunction(int key);
	void insertItem(int key, string value);
	void removeItem(int key);
	string searchTable(int key);
	void printTable();
};

bool HashTable::isEmpty() const {
	int sum{};
	for (int i{}; i < hashGroups; i++) {
		sum += table[i].size();
	}
	if (!sum) {
		return true;
	}
	return false;
}

int HashTable::hashFunction(int key) {
	return key % hashGroups;  // Key: 905, in return this function will spit out 5
}

void HashTable::insertItem(int key, string value) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;
	for (; bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr->second = value;
			cout << "[WARNING] Key exists. Value replaced." << endl;
			break;
		}
	}

	if (!keyExists) {
		cell.emplace_back(key, value);
	}
	return;
}

void HashTable::removeItem(int key) {
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;
	for (; bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr = cell.erase(bItr);
			cout << "[INFO] Pair removed." << endl;
			break;
		}
	}
	if (!keyExists) {
		cout << "[WARNING] Key not found. Pair not removed." << endl;
	}
}

void HashTable::printTable() {

}