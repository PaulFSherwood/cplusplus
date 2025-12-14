#include <iostream>

struct Entity {
    int x{4},y{5};
};

struct Warrior : public Entity {
    int power{10};
};

struct Goblin : public Entity {
    int power{7};
};

struct Player : public Goblin, public Warrior {
};

int main() {
    Player mike;
    std::cout << mike.Warrior::x << std::endl;
    std::cout << mike.Warrior::y << std::endl;
    
    std::cout << mike.Goblin::x << std::endl;
    std::cout << mike.Goblin::y << std::endl;
    std::cout << mike.Goblin::power << std::endl;

    return 0;

}
