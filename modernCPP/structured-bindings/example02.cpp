#include <iostream>
#include <tuple>

using AABB = std::tuple<float, float, float, float>;
// x, y, width, height

bool checkCollision(const AABB& a, const AABB& b) {
    // Structured binding two tuples at once
    const auto& [ax, ay, aw, ah] = a;
    const auto& [bx, by, bw, bh] = b;

    return ax < bx + bw &&
           ax + aw > bx &&
           ay < by + bh &&
           ay + ah > by;
}

int main() {
    AABB p1{ 0.f, 0.f, 2.f, 2.f };
    AABB p2{ 1.f, 1.f, 2.f, 2.f };

    std::cout << (checkCollision(p1, p2) ? "Hit!" : "No collision") << "\n";
}
