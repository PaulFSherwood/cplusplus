#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>

const int MATRIX_WIDTH = 40;
const int MATRIX_HEIGHT = 10;

std::string colorArray[7] = {
    "\033[1;31m",  // Red
    "\033[1;32m",  // Green
    "\033[1;33m",  // Yellow
    "\033[1;34m",  // Blue
    "\033[1;35m",  // Magenta
    "\033[1;36m",  // Cyan
    "\033[1;37m"   // White
};

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";  // Clear the screen
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            std::cout << colorArray[col] << "█";
        }
        std::cout << "\033[0m" << std::endl;  // Reset color before moving to the next row
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    clearScreen();

    std::vector<std::vector<int>> matrix(MATRIX_HEIGHT, std::vector<int>(MATRIX_WIDTH, 0));

    // Print the initial matrix
    printMatrix(matrix);

    while (true) {
        // Shift matrix rows downwards
        for (int row = MATRIX_HEIGHT - 1; row >= 1; row--) {
            matrix[row] = matrix[row - 1];
        }

        // Generate new random values for the first row
        for (int col = 0; col < MATRIX_WIDTH; col++) {
            matrix[0][col] = rand() % 7;  // Select a random color from 0 to 6
        }

        // Update only the changed rows
        for (int row = 0; row < MATRIX_HEIGHT; row++) {
            std::cout << "\033[" << row + 1 << ";1H";  // Move the cursor to the row position
            for (int col = 0; col < MATRIX_WIDTH; col++) {
                if (col % 2 == 0) { std::cout << colorArray[matrix[row][col]] << "█"; }
                else { std::cout << colorArray[matrix[row][col]] << "╚"; }
            }
            std::cout << "\033[0m";  // Reset color before moving to the next row
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Delay between frames (100ms)
    }

    return 0;
}
