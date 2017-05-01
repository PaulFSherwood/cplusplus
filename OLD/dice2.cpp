/*
  Name: Dice Game
  Author: Bleek
  Description: Game
  Date: N/A
  Copyright: N/A
*/

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
using namespace std;
void one();
void two();
void three();
void four();
void five();
void six();
//Declare Functions used
int main()
{
short unsigned int score = 0;
short unsigned int compScore = 0;
short unsigned int num = 0;
short unsigned int num2 = 0;
short unsigned int compNum = 0;
short unsigned int compNum2 = 0;
short unsigned int sum = 0;
short unsigned int compSum = 0;
char letter;
//Declare Variables
srand(time(NULL));
//Initialize random number generator
system("title Joe's Dice Game");
while (letter != 'q')
{
    cout << "Your Score: " << score << endl;
    cout << "computer's Score: " << compScore << endl << endl;
    cout << "Press r to roll or q to quit: ";
    cin >> letter;
    num = 1 + rand() % (6 - 1 + 1);
    num2 = 1 + rand() % (6 - 1 + 1);
    compNum = 1 + rand() % (6 - 1 + 1);
    compNum2 = 1 + rand() % (6 - 1 + 1);
    
    //Random numbers
    
    sum = num + num2;
    compSum = compNum + compNum2;
    
    //Calculate Sums
    
    if (letter == 'q')
        break;
    if (letter != 'r')
    {
        system("cls");
        continue;
    }
    
    switch (num)
    {
        case 1:
                one();
                break;
        case 2:
                two();
                break;
        case 3:
                three();
                break;
        case 4:
                four();
                break;
        case 5:
                five();
                break;
        case 6:
                six();
                break;
        default:
                cout << "Error...";
                break;
    } //end switch
    
    switch (num2)
    {
        case 1:
                one();
                break;
        case 2:
                two();
                break;
        case 3:
                three();
                break;
        case 4:
                four();
                break;
        case 5:
                five();
                break;
        case 6:
                six();
                break;
        default:
                cout << "Error...";
                break;
    } //end switch
        
    cout << endl << "Yours: " << num << ", " << num2 << endl;
    cout << "Computer's: " << compNum << ", " << compNum2 << "\n\n";
    
    //Display dice and numbers
    
    if (sum > compSum)
    {
        cout << "You won!!" << endl << endl;
        score++;
    }
    else
    {
        compScore++;
        cout << "you lost..." << endl << endl;
    }
    
    //Calculate score
    
    system("pause");
    system("cls");
    
    if (score == 12)
    {
        MessageBox(0, "You Won!!!", "Results:", MB_ICONEXCLAMATION);
        break;
    }
    if (compScore == 12)
    {
        MessageBox(0, "You lost...", "Results:", MB_ICONEXCLAMATION);
        break;    
    }
}
return 0;
}

void one()
{
cout << " -----" << endl;
cout << "|     |" << endl;
cout << "|  O  |" << endl;
cout << "|     |" << endl;
cout <<  " -----" << endl;
}
void two()
{
cout << " -----" << endl;
cout << "|    O|" << endl;
cout << "|     |" << endl;
cout << "|O    |" << endl;
cout <<  " -----" << endl;
}
void three()
{
cout << " -----" << endl;
cout << "|    O|" << endl;
cout << "|  O  |" << endl;
cout << "|O    |" << endl;
cout <<  " -----" << endl;
}
void four()
{
cout << " -----" << endl;
cout << "|O   O|" << endl;
cout << "|     |" << endl;
cout << "|O   O|" << endl;
cout <<  " -----" << endl;
}
void five()
{
cout << " -----" << endl;
cout << "|O   O|" << endl;
cout << "|  O  |" << endl;
cout << "|O   O|" << endl;
cout <<  " -----" << endl;
}
void six()
{
cout << " -----" << endl;
cout << "|O   O|" << endl;
cout << "|O   O|" << endl;
cout << "|O   O|" << endl;
cout <<  " -----" << endl;
}
