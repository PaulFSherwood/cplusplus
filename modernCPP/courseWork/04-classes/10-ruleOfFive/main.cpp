#include <iostream>
#include <cstring>
using namespace std;

class ResourceManager {
   private:
      char* data;
      size_t size;
   public:
      // Constructor
      ResourceManager(const char* str = "")
         : size(strlen(str)), data(new char[size + 1]) {
            strcpy(data, str);
            cout << "Constructor called\n";
         }
      // Destructor
      ~ResourceManager() {
         delete[] data;
         cout << "Destructor called\n";
      }
      // Copy Constructor
      ResourceManager(const ResourceManager& other)
         : size(other.size), data(new char[other.size + 1]) {
            strcpy(data, other.data);
            cout << "Copy Constructor called\n";
         }
      // Copy Assignment Operator
      ResourceManager& operator=(const ResourceManager& other) {
         if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            strcpy(data, other.data);
         }
         cout << "Copy Assignment Operator called\n";
         return *this;
      }
      // Move Constructor
      ResourceManager(ResourceManager&& other) noexcept
         : size(other.size), data(other.data) {
            other.data = nullptr;
            other.size = 0;
            cout << "Move Constructor called\n";
      }
      // Move Assignment Operator
      ResourceManager& operator=(ResourceManager&& other) noexcept {
         if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
         }
         cout << "Move Assignment Operator called\n";
         return *this;
      }
};

int main() {
   ResourceManager obj1("Hello");
   ResourceManager obj2 = obj1;       // Copy Constructor
   ResourceManager obj3;
   obj3 = obj1;                       // Copy Assignment Operator
   ResourceManager obj4 = move(obj1); // Move Constructor
   ResourceManager obj5;
   obj5 = move(obj2);                 // Move Assignment Operator
   return 0;
}
