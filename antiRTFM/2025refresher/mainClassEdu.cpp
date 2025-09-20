#include <iostream>
#include <random>  // For rand() and srand()
#include <string>
using namespace std;

// Section 4
int getInteger();

class Character {
    public:
        std::string name;
        int health{};
        int attack{};
        int defense{};

        // General Constructor
        explicit Character(const std::string& n, int h, int a, int d)
            : name(n), health(h), attack(a), defense(d) {}

        // Factory: hero
        static Character Hero(const std::string& n, int h = 50, int a = 5, int d = 5) {
            return Character(n, h, a, d);
        }
        // Factory: Monster
        static Character Monster(const std::string& n, int h = 100, int a = 10, int d = 10) {
            return Character(n, h, a, d);
        }

        // Friend for printing
        friend std::ostream& operator<<(std::ostream& os, const Character& c) {
            return os << '"' << c.name << "\", "
                      << c.health << ", "
                      << c.attack << ", "
                      << c.defense;
        }
};

int main()
{
    auto hero   = Character::Hero("Arthur");
    auto goblin = Character::Monster("Goblin", 100, 50);
    auto ogre = Character::Monster("Ogre", 200, 100);

    std::cout << hero << "\n";
    std::cout << goblin << "\n";
    std::cout << ogre << "\n";

    return 0;
}

int getInteger()
{
	static mt19937 gen(random_device{}()); // Seed once
	static uniform_int_distribution<int> dist(1, 100);
	return dist(gen);
}

