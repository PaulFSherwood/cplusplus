#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));  // seed random number generator based on current time
    
    int randomNumber = rand();  // generate random number
    int point = 0;
    
    int die1 = (randomNumber % 6) + 1;  // get a number between 1 and 6
    cout << "You rolled a " << die1 << " on your first die." << endl;
    int die2 = (randomNumber % 6) + 1;
    cout << "You rolled a " << die2 << " on your second die." << endl;
    int score = (die1 + die2);
    
    
    		do
		{
		    cout <<  "Total roll is " << score << endl;
		    
		    if(score == 7 || score == 11)
		    {
			cout << "YOUR " << score << " WINS" << endl;
		    }
		    if(score == 2 || score == 3 || score == 12)
		    {
			cout << "YOU LOST WITH " << score << endl;
		    }
		}while(score == 4 || score == 5 || score == 6 || score == 8 || score == 9 || score == 10);
		score == point;
		cout << "Your point is " << point << endl;
		cout << "Roll again" << endl;
		while (1)
		{
		    if ('c' == getchar())
			break;
		}
		system("pause");
    return 0;
}
    
    
    
    
/**    if(score == '2') 
    {
	    cout << "YOUR " << score << " WINS" << endl;
	    if(score == '7')
	    {
		cout << "YOU LOST WITH " << score << endl;
	    }
	    
	}
    return 0;
}**/
//else
//	    {
//        score == point;
//       
//        }||11||3||12
