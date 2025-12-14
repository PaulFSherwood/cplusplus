#include <iostream>

struct Entity {
    int x{4},y{5};
};

struct Warrior : virtual public Entity {
    int power{10};
};

struct Goblin : virtual public Entity {
    int power{7};
};

struct Player : public Goblin, public Warrior {
};

int main() {

    Player mike;
    std::cout << mike.x << std::endl;
    std::cout << mike.y << std::endl;
    
    std::cout << mike.Goblin::x << std::endl;
    std::cout << mike.Goblin::y << std::endl;
    std::cout << mike.Goblin::power << std::endl;

    return 0;
}
