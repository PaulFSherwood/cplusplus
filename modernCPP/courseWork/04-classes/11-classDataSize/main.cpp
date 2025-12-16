#include <iostream>
#include <string>

struct GameState {
//     float stateChanged;
    bool checkpoint;
    float score;
    short numberOfPlayers;
};

class GamerState {
public:
    float score;
    short numberOfPlayers;
    bool checkpoint;
};

int main() {
    GameState gs;
    GamerState gz;

    std::cout << "Align:  " << alignof(gs) << std::endl;
    std::cout << "Bool:   " << sizeof(gs.checkpoint) << std::endl;
    std::cout << "Float:  " << sizeof(gs.score) << std::endl;
    std::cout << "short:  " << sizeof(gs.numberOfPlayers) << std::endl;
    std::cout << "Struct: " << sizeof(gs) << std::endl;
    std::cout << std::endl;
    std::cout << "Align:  " << alignof(gz) << std::endl;
    std::cout << "Bool:   " << sizeof(gz.checkpoint) << std::endl;
    std::cout << "Float:  " << sizeof(gz.score) << std::endl;
    std::cout << "short:  " << sizeof(gz.numberOfPlayers) << std::endl;
    std::cout << "Struct: "<< sizeof(gz) << std::endl;

//     std::cout << sizeof(gz.GamerState

    return 0;
}
