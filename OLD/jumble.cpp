#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    enum fields {WORD, HINT, NUM_FIELDS};
    const int NUM_WORDS = 5;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
          {"Wall", "Do you feel you're banging your head against something?"},
          {"glasses", "These might help you see the answer."},
          {"labored", "Going slowly, is it?"},
          {"persistent", "Keep at it."},
          {"jumble", "It;s what the game is all about."}
          };
          
          srand(time(0));
          int choice = (rand() % NUM_WORDS);
          string theWord = WORDS[choice][WORD];  // word to guess
          string theHint = WORDS[choice][HINT];  // hint for word
          
          string jumble = theWord;
          int length = jumble.size();
          int score = 0;
          int points = 0;
          for (int i = 0; i < length; ++i)
          {
              int index1 = (rand() % length);
              int index2 = (rand() % length);
              char temp = jumble[index1];
              jumble[index1] = jumble[index2];
              jumble[index2] = temp;
              }
              cout << "Welcome to Word Jumble!";
              cout << "Unscramble the letters to make a word.";
              cout << "Enter 'hint' for a hint.";
              cout << "Enter 'quit' to quit the game.";
              cout << "The jumble is " << jumble;
              
              string guess;
              cout << "Your guess: ";
              cin >> guess;
              
              while ((guess != theWord) && (guess != "guit"))
              {
                    if (guess == "hint")
                    cout << theHint;
                    else cout << "Sorry, that's not it.";
                    
                    cout << "Your guess: ";
                    cin >> guess;
                    }
                    
                    if (guess == theWord)
                    cout << "That;s it! You guessed it!";
                    
                    cout << "Thanks for playing.";
                    return 0;
                    }
