// Games should include the following
//
// Initialization
// Input handeling
// Game Logic
// Rendering
//

#include <QCoreApplication>
#include <iostream>
#include <Windows.h>


////////////////////
/// INITIALIZATION
///
const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 15;
const int GROUND_HEIGHT = 13;
const int PLAYER_WIDTH = 2;
const int PLAYER_HEIGHT = 3;

char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

// draw everything to the screen
void drawScreen() {
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            std::cout << screen[i][j];
        }
        std::cout << '\n';
    }
}

////////////////////
/// INPUT HANDLING
///
bool isKeyPressed(int vkCode) {
    return (0x8000 & GetAsyncKeyState(vkCode)) != 0;
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    int playerX = SCREEN_WIDTH / 2;
    int playerY = GROUND_HEIGHT - PLAYER_HEIGHT;

    float velocityY = 0;
    const float gravity = 0.6f;
    const float jumpForce = -2.0f;
    bool isGrounded = true;


    // main game loop
    while (true) {

        ////////////////////
        // INPUT HANDLING
        // Update player
        if (isKeyPressed('A')) {
            --playerX;
        }

        if (isKeyPressed('D')) {
            ++playerX;
        }

        if (isKeyPressed('W') && isGrounded) {
            velocityY = jumpForce;
            isGrounded = false;
        }

        ////////////////////
        /// GAME LOGIC
        ///
        playerY += static_cast<int>(velocityY);
        velocityY += gravity;

        if (playerY + PLAYER_HEIGHT > GROUND_HEIGHT) {
            playerY = GROUND_HEIGHT - PLAYER_HEIGHT;
            velocityY = 0;
            isGrounded = true;
        }


        ////////////////////
        /// RENDERING
        ///
        // Clear screen
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            for (int j = 0; j < SCREEN_WIDTH; ++j) {
                screen[i][j] = ' ';
            }
        }
        // Draw ground
        for (int i = GROUND_HEIGHT; i < SCREEN_HEIGHT; ++i) {
            for (int j = 0; j < SCREEN_WIDTH; ++j) {
                screen[i][j] = '#';
            }
        }
        // Draw player
        for (int i = 0; i < PLAYER_HEIGHT; ++i) {
            for (int j = 0; j < PLAYER_WIDTH; ++j) {
                screen[playerY + i][playerX + j] = '@';
            }
        }
        // Draw screen
        system("cls");
        drawScreen();

        Sleep(33); // Approximately 30 FPS
    }

    return a.exec();
}
