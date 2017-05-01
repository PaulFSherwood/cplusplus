// Critter Farm
// Demonstrates object containment

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Critter
{
 	  public:
	  		 Critter(const string& name = ""): m_Name(name) {}
	  		 string GetName() const { return m_Name; }
      private:
  		     string m_Name;
      };
      
      class Farm
      {
	   		public:
				   Farm(int spaces = 1) { m_Critters.reserve(spaces); }
				   void Add(const Critter& aCritter) { m_Critters.push_back(aCritter); }
				   void RollCall() const
      {
	        for (vector<Critter>::const_iterator iter = m_Critters.begin();
	        iter != m_Critters.end(); ++iter)
	        cout << iter->GetName() << " here.\n";
      }
      private:
	  		  vector<Critter> m_Critters;
      };
	  
	  int main()
	  {
	   	  Critter crit("Poochie");
			 cout << "My critter's name is " << crit.GetName() << endl;
			 
			 cout << "\nCreating critter farm.\n";
			 Farm myFarm(3);
			 
			 cout << "\nAdding three critters to the farm.\n";
			 myFarm.Add(Critter("Moe"));
			 myFarm.Add(Critter("Larry"));
			 myFarm.Add(Critter("Curly"));
			 
			 cout << "\nCalling Roll...\n";
			 myFarm.RollCall();
			 
			 return 0;
			 }
			 
			 
