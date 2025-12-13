#include <iostream>

struct PlayerState {
    float x;
    float y;
    float health;
    int ammo;
};

void restore(PlayerState *dst, const PlayerState *src) {
    *dst = *src;        // raw memory copy
}

int main() {
    PlayerState current = {10.0f, 5.0f, 100.0f, 30};
    PlayerState checkpoint = current;

    std::cout << "HP: " << current.health << std::endl;
    current.health = 20.0f;     // took damage

    std::cout << "HP: " << current.health << std::endl;
    restore(&current, &checkpoint);     // rollback
    std::cout << "HP: " << current.health << std::endl;
}
