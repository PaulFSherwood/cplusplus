#include<iostream>
#include<ctime>
using namespace std;

int main(void)

{
    int iGumballs;
    int iUserguess;
    int iGuesses = 0;

    while(true)
{
	 system("clear");
	cin.clear();
	iGuesses = 0;
	
	srand(static_cast<unsigned int>(time(0)));
                iGumballs = rand()%1000+1;
		cout << "How many gumballs are in the gumball jar, you guess!"
			<< endl;
		do
		{
		    cout <<  "Enter your guess: ";
		    
		    cin >> iUserguess;
		    if(iUserguess > iGumballs)
		    {
			cout << "Too High!" << endl << endl;
		    }
		    if(iUserguess < iGumballs)
		    {
			cout << "Too Low!" << endl << endl;
		    }
		    iGuesses ++;
		}while(iUserguess > iGumballs || iUserguess < iGumballs);
		cout << "You guess the right amount" << endl << endl;
		cout << "You took " << iGuesses << " guesses " << endl << endl;
		cout << "PRESS c THEN ENTER TO CONTINUE" << endl;
		while (1)
		{
		    if ('c' == getchar())
			break;
		}
		system("pause");
	    }
    return 0;
}
