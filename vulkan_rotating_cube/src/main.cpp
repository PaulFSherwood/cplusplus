#include "App.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    try {
        cube::App app;
        return app.run(argc, argv);
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
}
