#include <iostream>
#include <random>  // For rand() and srand()
#include <unordered_map>
#include <vector>

using namespace std;
using Entity = int;

struct Health   { int hp; };
struct Attack   { int dmg; };
struct Mana     { int mp; };

std::unordered_map<Entity, Health> healths;
std::unordered_map<Entity, Attack> attacks;
std::unordered_map<Entity, Mana>   manas;


// Section 4
int getInteger();
// ECS system cont.
void DamageSystem(Entity e1, Entity e2);
void MageSystem(Entity e);

int main()
{
    Entity hero = 1;
    Entity ogre = 2;

    healths[hero] = { 50 };
    attacks[hero] = {  5 };
    manas[hero]   = { 30 };

    healths[ogre] = { 200 };
    attacks[ogre] = {  20 };

    DamageSystem(hero, ogre);
    MageSystem(hero);

    std::cout << "Ogre HP: " << healths[ogre].hp << "\n";
    std::cout << "Hero HP: " << healths[hero].hp << "\n";

    return 0;
}

int getInteger()
{
	static mt19937 gen(random_device{}()); // Seed once
	static uniform_int_distribution<int> dist(1, 100);
	return dist(gen);
}
// ECS system cont.
void DamageSystem(Entity e1, Entity e2) {
    if (attacks.count(e1) && healths.count(e2)) {
        healths[e2].hp -= attacks[e1].dmg;
        std::cout << "Entity " << e1 << " hit entity " << e2
                  << " for " << attacks[e1].dmg << " damage.\n";
    }
}

void MageSystem(Entity e) {
    if (manas.count(e) && healths.count(e)) {
        if (manas[e].mp >= 10) {
            healths[e].hp += 20;
            manas[e].mp -= 10;
            std::cout << "Entity " << e << " heals self!\n";
        }
    }
}
