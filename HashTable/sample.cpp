#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class HashTable {
    private:
    static const int hashGroups = 10;
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
class HashTable2 {
    private:
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups];

    public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

class HashTable3 {
    private:
    static const int HashGroups = 10;
    list <pair<int, string>> table[HashGroups];

    public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

class HashTable4 {
    private:
    static const int hashGroups = 10;
    list <pair<int, string>> table[hashGroups];

    public:
    bool isEmpty() const;
    // int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();

};

class HashTable5 {
    private:
    static const int hashGroups = 10;
    list <pair<int, string>> table[hashGroups];

    public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    // string searchTable(int key);
    void printTable();
};