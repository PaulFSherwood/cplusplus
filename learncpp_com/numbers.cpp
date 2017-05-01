#include <iostream>
using namespace std;

char showLetters(char letters[], int length)
{
	int i = 0;
	while (i < length)
	{
		if (i == 25)
		{
			cout << letters[i] << endl;
			i++;
		}
		else
		{
			cout << letters[i] << ", ";
			i++;
		}
	}
}

char showNumbers(char letters[], int length)
{
	int i = 0;
	while (i < length)
	{
		if (i == 25)
		{
			int iLetter = static_cast<int>(letters[i]);
			cout << iLetter << endl;
			i++;

		}
		else
		{
			int iLetter = static_cast<int>(letters[i]);
			cout << iLetter << ", ";
			i++;
		}
	}
}


int main()
{
	char letters[26] = {	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
				'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
				'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	showLetters(letters, 26);
	showNumbers(letters, 26);
}
