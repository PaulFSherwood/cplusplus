// Static Critter
// Demonstrates static data members and functions

#include <iostream>

using namespace std;

class Critter
{
 	  public:
	  		 static int s_Total;	//static data member
	  		 						//total number of critter objects in existence
             Critter(int hunger = 0): m_Hunger(hunger)
             {
  			       cout << "A critter has been born!"  << endl;
  			       ++s_Total;
	         }
	         static int GetTotal() 	//static member function
	         {
			  		return s_Total;
             }
             private:
			 		 int m_Hunger;
			 };
			 int Critter::s_Total = 0;  // initialize static data member
			 
			 int main()
			 {
			  	 cout << "The total number of critters is: ";
			  	 cout << Critter::s_Total << "\n\n";
			  	 
			  	 Critter crit1, crit2, crit3;
			  	 
			  	 cout << "\nThe total number of critters is: ";
			  	 cout << Critter::GetTotal() << "\n";
			  	 
			  	 return 0;
			 }
