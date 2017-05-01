// hero's inventory
// demonstrates arrays

#include <iostream>
#include <string>

using namespace std;

int main()
{
    const int MAX_ITEMS = 10;
    string inventory[MAX_ITEMS];
    
    int numItems = 0;
    inventory[numItems++] = "sword";
    inventory[numItems++] = "armor";
    inventory[numItems++] = "shield";
    
    cout << "Your itmes: " << endl;
    for (int i = 0; i < numItems; ++i)
    cout << inventory[i] << endl;
    
    cout << endl << "You trade your sword for a battle axe." << endl;
    inventory [0] = "battle axe";
    cout << "Your items: " << endl;
    for (int i = 0; i < numItems; ++i)
    cout << inventory[i] << endl;
    
    cout << endl << "The item name '" << inventory[0] << "' has ";
    cout << inventory[0].size() << " letters in it. " << endl << endl;
    
    cout << "You find a healing potion." << endl;
    if (numItems < MAX_ITEMS)
    inventory[numItems++] = "healing potion";
    else cout << "You have too many items and can't carry another.";
    cout << "Your items:" << endl;
    for (int i = 0; i < numItems; ++i)
    cout << inventory[i] << endl;
    
    return 0;
}
