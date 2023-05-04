#include <QCoreApplication>

#include <iostream>
#include <Windows.h>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

const char BLOCK = '#';
const char EMPTY = ' ';

int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};

void drawBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            std::cout << (board[i][j] ? BLOCK : EMPTY) << ' ';
        }
        std::cout << '\n';
    }
}

bool isKeyPressed(int vkCode)
{
    return (0x8000 & GetAsyncKeyState(vkCode)) != 0;
}




bool canMovePiece(int** shape, int x, int y)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (shape[i][j] != 0)
            {
                int px = x + j;
                int py = y + i;
                if (px < 0 || px >= BOARD_WIDTH || py >= BOARD_HEIGHT || (py >= 0 && board[py][px] != 0))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void lockPiece(int** shape, int x, int y)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (shape[i][j] != 0)
            {
                int px = x + j;
                int py = y + i;
                board[py][px] = 1;
            }
        }
    }
}






int getRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

int** generatePiece()
{
    int type = getRandom(0, 6);
    int** piece = new int*[4];
    for (int i = 0; i < 4; ++i)
    {
        piece[i] = new int[4];
    }
    switch (type)
    {
    case 0: // I piece
        piece[0][1] = 1;
        piece[1][1] = 1;
        piece[2][1] = 1;
        piece[3][1] = 1;
        break;
    case 1: // J piece
        piece[0][2] = 1;
        piece[1][2] = 1;
        piece[2][2] = 1;
        piece[2][1] = 1;
        break;
    case 2: // L piece
        piece[0][1] = 1;
        piece[1][1] = 1;
        piece[2][1] = 1;
        piece[2][2] = 1;
        break;
    case 3: // O piece
        piece[0][1] = 1;
        piece[0][2] = 1;
        piece[1][1] = 1;
        piece[1][2] = 1;
        break;
    case 4: // S piece
        piece[0][1] = 1;
        piece[1][1] = 1;
        piece[1][2] = 1;
        piece[2][2] = 1;
        break;
    case 5: // T piece
        piece[0][1] = 1;
        piece[1][1] = 1;
        piece[2][1] = 1;
        piece[1][2] = 1;
        break;
    case 6: // Z piece
        piece[0][2] = 1;
        piece[1][1] = 1;
        piece[1][2] = 1;
        piece[2][1] = 1;
        break;
    }
    return piece;
}

void deletePiece(int** piece)
{
    for (int i = 0; i < 4; ++i)
    {
        delete[] piece[i];
    }
    delete[] piece;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);






    int currentPieceX = BOARD_WIDTH / 2;
    int currentPieceY = 0;
    int** currentPieceShape = generatePiece();

    while (true)
    {
        // Move the piece down if no key is pressed
        if (!isKeyPressed('A') && !isKeyPressed('D') && !isKeyPressed('S'))
        {
            if (canMovePiece(currentPieceShape, currentPieceX, currentPieceY + 1))
            {
                ++currentPieceY;
            }
            else
            {
                // Lock the piece in place and generate a new piece
                lockPiece(currentPieceShape, currentPieceX, currentPieceY);
                deletePiece(currentPieceShape);
                currentPieceX = BOARD_WIDTH / 2;
                currentPieceY = 0;
                currentPieceShape = generatePiece();
            }
        }

        // Move the piece left if the 'A' key is pressed
        if (isKeyPressed('A') && currentPieceX > 0 && canMovePiece(currentPieceShape, currentPieceX - 1, currentPieceY))
        {
            --currentPieceX;
        }

        // Move the piece right if the 'D' key is pressed
        if (isKeyPressed('D') && currentPieceX < BOARD_WIDTH - 1 && canMovePiece(currentPieceShape, currentPieceX + 1, currentPieceY))
        {
            ++currentPieceX;
        }

        // Move the piece down faster if the 'S' key is pressed
        if (isKeyPressed('S'))
        {
            if (canMovePiece(currentPieceShape, currentPieceX, currentPieceY + 1))
            {
                ++currentPieceY;
            }
            else
            {
                // Lock the piece in place and generate a new piece
                lockPiece(currentPieceShape, currentPieceX, currentPieceY);
                deletePiece(currentPieceShape);
                currentPieceX = BOARD_WIDTH / 2;
                currentPieceY = 0;
                currentPieceShape = generatePiece();
            }
        }

        // Update the board with the current piece
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (currentPieceShape[i][j] != 0)
                {
                    board[currentPieceY + i][currentPieceX + j] = 1;
                }
            }
        }


        // Draw the board
        system("cls"); // Clear the console
        drawBoard();

        // Reset the board
        for (int i = 0; i < BOARD_HEIGHT; ++i)
        {
            for (int j = 0; j < BOARD_WIDTH; ++j)
            {
                board[i][j] = 0;
            }
        }

        Sleep(100); // Sleep for a short time to avoid consuming too much CPU time
    }

    // Free the memory of the current piece when exiting the loop
    deletePiece(currentPieceShape);



//    return 0;

    return a.exec();
}
