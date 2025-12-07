#include <iostream>
#include <vector>
#include <tuple>

// A physics component stored as a tuple (x, y, vx, vy)
using Physics = std::tuple<float, float, float, float>;

int main() {
    std::vector<Physics> bodies = {
        { 0.f, 0.f, 1.f, 0.5f},     // x, y, vx, vy
        {10.f, 5.f, -2.f, 1.0f},
        {3.f, 8.f, 0.0f, -3.f}
    };

    float dt = 1.0f / 60.0f;

    // Recalculate x and y (edit the original x and y of bodies
    for (auto& body : bodies) {
         // Sturctured bindings make the intent 100% clear
        auto& [x, y, vx, vy] = body;

        x += vx * dt;
        y += vy * dt;
    }

    // Print out all your variables from bodies.
    for (auto& bodyz : bodies) {  // using a different variable to test we can. (bodyz)
         auto& [x, y, vx, vy] = bodyz;
         std::cout << "Pos(" << x << "," << y << ")  Vel(" << vx << "," << vy << ")\n";
    }
}

