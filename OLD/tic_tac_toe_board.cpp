#include <iostream>

using namespace std;

int main()

{
    const int ROWS = 3;
    const int COLUMS = 3;
    char board[ROWS][COLUMS] = { {'O', 'X', 'O'},
                                 {' ', 'X', 'X'},
                                 {'X', 'X', 'O'} };
                                 
    cout << "Here's the tic-tac-toe board: ";
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMS; ++j)
        cout << board[i][j];
        cout << endl;
        }
        
        cout << " 'X' moves to the empty location. ";
        board[1][0] = 'X';
         
         cout << "Now the tic-tac-toe board is: ";
         for (int i = 0; i < ROWS; ++i)
         {
         for (int j = 0; j < COLUMS; ++j)
         cout << board[i][j];
         cout << endl;
         }
         
         cout << "'X' wins!";
         return 0;
         }    
