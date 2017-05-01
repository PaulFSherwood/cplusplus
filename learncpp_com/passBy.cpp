#include <iostream>
using namespace std;

int nFive = 5;
int nSix = 6;

void SetToSix(int *pTempPtr);

int main()
{
	// First we set pPtr to the address of nFive
	// Which means *pPtr = 5
	int *pPtr = &nFive;

	// This will pritn 5
	cout << "This will print 5: " << *pPtr << endl;

	// Now we call SetToSix (see function below)
	// pTempPtr receives a copy of the address of pPtr
	SetToSix(pPtr);

	// pPtr is still set to the address of nFive!
	// This will print 5
	cout << "This will pritn 5: " << *pPtr << endl;

}

// pTempPtr copies the value of pPtr!
void SetToSix(int *pTempPtr)
{

	// This only changes pTempPtr, no pPtr!
	pTempPtr = &nSix;

	// This will print 6
	cout << "This will print 6: " << *pTempPtr << endl;
	
}
