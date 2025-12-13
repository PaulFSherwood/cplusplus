#include <iostream>
#include <string>
#include <vector>
#include <tuple>

enum class EventType { Move, Fire, Quit };

// Event = type + data (dx, dy, or extra info)
using Event = std::tuple<EventType, int, int>;

int main() {
    std::vector<Event> events = {
        {EventType::Move, 1, 0},
        {EventType::Move, 0, -1},
        {EventType::Fire, 0, 0},
        {EventType::Quit, 0, 0}
    };

    for (auto& e : events) {
         // Structred binding for clarity
        auto [type, a, b] = e;

         switch (type) {
            case EventType::Move:
                std::cout << "Move: dx=" << a << ", dy=" << b << "\n";
                break;
            case EventType::Fire:
                std::cout << "Fire weapon\n";
                break;
            case EventType::Quit:
                std::cout << "Quit game\n";
                break;
         }
    }
}

