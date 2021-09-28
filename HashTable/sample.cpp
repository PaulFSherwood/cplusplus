#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class HashTable {
    private:
    static const int hashGroup = 10;
    list <pair<int, string>> table[hashGroups];

    public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};



// testing
class sHashTable {
    private:
    static const int hashGroups = 10;
    list <pair <int, string>> table[hashGroups];

    public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};