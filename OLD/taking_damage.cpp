// Taking damage
// Demonstrates function inlining

#include <iostream>

double radiation(double health);
double radiasion(double helf);

using namespace std;

int main()
{
 	double health = 80;
 	double helf = 0;
 	cout << "Prior radiation exposure your health is " << health << "\n\n";
 	
 	health = radiation(health);
 	cout << "After radiation exposure your health is " << health << "\n\n";
 	
 	health = radiation(health);
 	cout << "After radiation exposure your health is " << health << "\n\n";
 	
 	health = radiation(health);
 	cout << "After radiation exposure your health is " << health << "\n\n";
 	
 	health = radiation(health);
 	cout << "After radiation exposure your health is " << health << "\n\n";
 	
 	helf = health;
 	
 	helf = radiasion(helf);
 	cout << "Out of danger, your health is rising to " << helf << "\n\n";
 	
 	helf = radiasion(helf);
 	cout << "Out of danger, your health is rising to " << helf << "\n\n";
 	
 	helf = radiasion(helf);
 	cout << "Out of danger, your health is rising to " << helf << "\n\n";
 	
 	helf = radiasion(helf);
 	cout << "Out of danger, your health is rising to " << helf << "\n\n";
 	
 	return 0;
}
inline double radiation(double health)
{
 	   return (health / 2);
}
inline double radiasion(double helf)
{
 	   return (helf * 2);
}
