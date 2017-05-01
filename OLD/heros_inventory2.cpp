#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> inventory;
    inventory.push_back("sword");
    inventory.push_back("armor");
    inventory.push_back("shield");
    
    cout << "You have " << inventory.size() << " items.";
    
    cout << "Your items: ";
    for (int i = 0; i < inventory.size(); ++i)
    cout << inventory[i] << endl;
    
    cout << "You trade your sword for a battle axe.";
    inventory[0] = "battle axe";
    cout << "Your items: ";
    for (int i = 0; i < inventory.size(); ++i)
    cout << inventory[i] << endl;
    
    cout << "The item name '" << inventory[0] << "' has ";
    cout << inventory[0].size() << " letters in it.";
    
    cout << "Your shield is destroyed in a fierce battle.";
    inventory.pop_back();
    cout << "Your items: ";
    for (int i = 0; i < inventory.size(); ++i)
    cout << inventory[i] << endl;
    
    cout << "You were robbed of all of your possessions by a thief.";
    inventory.clear();
    if (inventory.empty())
    cout << "You have nothing.";
    else cout << "You have atlest one itme.";
    return 0;
}
