#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

using namespace std;

int main()
{
    //setup
    const int MAX_WRONG = 8;                         //maximum number of incorrect guesses allowed
    vector<string> words;                           //collection of possible words to guess
    
    words.push_back("AC");
    words.push_back("ACCA");
    words.push_back("ACCESS");
    words.push_back("ACCUMULATOR");
    words.push_back("ACCURACY");
    words.push_back("ACQUISITION");
    words.push_back("APPLE");
    words.push_back("BACKUP");
    words.push_back("BANDWIDTH");
    words.push_back("BASE");
    words.push_back("BASH");
    words.push_back("BIDIRECTION");
    words.push_back("BIOS");
    words.push_back("BINARY");
    words.push_back("BIT");
    words.push_back("BITRATE");
    words.push_back("BITS");
    words.push_back("BLOWFISH");
    words.push_back("BODY");
    words.push_back("BOT");
    words.push_back("BOOLEAN");
    words.push_back("BOYCE");
    words.push_back("BOYCE");
    words.push_back("BROWSER");
    words.push_back("BSD");
    words.push_back("BUCKET");
    words.push_back("BYTE");
    words.push_back("CACHE");
    words.push_back("CARRIER");
    words.push_back("CASE");
    words.push_back("CHILD");
    words.push_back("CHILDREN");
    words.push_back("CIRCULAR");
    words.push_back("CLASS");
    words.push_back("CLUSTER");
    words.push_back("CMOS");
    words.push_back("COAMS");
    words.push_back("COBOL");
    words.push_back("CODEC");
    words.push_back("COMITE");
    words.push_back("COMPLETE");
    words.push_back("COMPUTER");
    words.push_back("CONJUNCATION");
    words.push_back("CONSTRUCTOR");
    words.push_back("CONTENTION");
    words.push_back("CONVENTIONAL");
    words.push_back("COOKIE");
    words.push_back("CORBA");
    words.push_back("CPU");
    words.push_back("CRASH");
    words.push_back("EARTH");
    words.push_back("DIFFICULT");
    words.push_back("GEOMETRY");
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("MAXIMUM");
    
    srand(time(0));
    random_shuffle(words.begin(), words.end());
    const string THE_WORD = words[0];                //words to guess
    int wrong = 0;                                   //number of incorrect guesses
    string soFar(THE_WORD.size(), '-');              //word guessed so far
    string used = "";                                //letters already guessed
    
    cout << "Welcome to Hangman. Good luck!\n";
    //main loop
    while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
    {
         cout << "\n\nYou have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n";
         cout << "\nYou've used the following letters:\n" << used << endl;
         cout << "\nSo far, the word is:\n" << soFar << endl;
         
         char guess;
         cout << "\n\nEnter your guess: ";
         cin >> guess;
         guess = toupper(guess);                     //made uppercase
         while (used.find(guess) != string::npos)
         {
               cout << "\nYou've already guessed " << guess << endl;
               cout << "Enter your guess: ";
               cin >> guess;
               guess = toupper(guess);
               }
               
               used += guess;
               
               if (THE_WORD.find(guess) != string::npos)
               {
                     cout << "That's right! " << guess << " is in the word.\n";
                     
                     //update soFar to include newly guessed letter
                     for (int i = 0; i < THE_WORD.length(); ++i)
                     if (THE_WORD[i] == guess)
                     soFar[i] = guess;
               }
               else
               {
                     cout << "Sorry, " << guess << " isn't in the word.\n";
                     ++wrong;
               }
         }
                     //shut down
                     if (wrong == MAX_WRONG)
                     cout << "\nYou've been hanged!";
                     else
                     cout << "\nYou guessed it!";
                     cout << "\nThe word was " << THE_WORD << endl;
                     return 0;
}
