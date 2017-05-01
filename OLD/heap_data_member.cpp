// Heap Data Member
// Demonstrates an object with a dynamically allocated data member

#include <iostream>
#include <string>

using namespace std;

class Critter
{
     public:
          Critter(const string& name = "")
     {
          cout << "Constructor called\n";
          m_pName = new string(name);
     }
	         
     ~Critter()                         // destructor
     {
          cout << "destructor called\n";
          delete m_pName;
     }
     
     Critter(const Critter& c)          // copy constructor
     {
          cout << "Copy Constructor called.\n";
          m_pName = new string;
          *m_pName = c.GetName();
     }
     
     Critter& operator=(const Critter& c) // overloaded assignment operator
     {
          cout << "Overloaded asignment Operator called\n";
          
          if (this == &c)
          {
               return *this;
          }
          
          else
          {
               *m_pName = c.GetName();
               return *this;
          }
     }
     
     string GetName() const { return *m_pName; }
     void SetName(const string& name = "") { *m_pName = name; }
     void SayHi() const { cout << "Hi, my name is " << GetName() << "\n"; }
     
private:
     string* m_pName;
};

void testDestructor();
void testCopyConstructor(Critter copy);
void testAssignmentOp();

int main()
{
     testDestructor();
     cout << endl;
     
     Critter crit("Poochie");
     crit.SayHi();
     testCopyConstructor(crit);
     cout << endl;
     
     testAssignmentOp();
     
     return 0;
}

void testDestructor()
{
 	 Critter crit("Rover");
 	 crit.SayHi();
}

// passing object by value invokes its copy constructor
void testCopyConstructor(Critter copy)
{
 	 copy.SayHi();
}

void testAssignmentOp()
{
 	 Critter crit1("crit1");
 	 Critter crit2("crit2");
 	 crit1 = crit2;
 	 crit1.SayHi();
 	 crit2.SayHi();
 	 
 	 cout << "Setting name of crit1 back to 'crit1'\n";
 	 crit1.SetName("crit1");
 	 crit1.SayHi();
 	 crit2.SayHi();
 	 
 	 Critter crit("crit");
 	 crit = crit;
}
