// INPUT 
// array = [5, 1, 22, 25, 6, -1, 8, 10]
// sequence = [1, 6, -1, 10]
//
// OUTPUT
// TRUE
using namespace std;

bool isValidSubsequence(vector<int> array, vector<int> sequence) {
    bool isGud = false;
	int a = array.size();
	int b = sequence.size();
	cout << "a.size(" << array.size() << ")\tb.size(" << sequence.size() << ")\n";
  int counter = 0;
	
    // first loop to track the first array
    for (int j = 0; j < sequence.size(); j++)
    {
			cout << "loop(" << j << ") size: " << sequence.size() << " Counter: " << counter << endl;
				cout << endl;
			isGud = false;
        // second loop to track the second array
        for (int i = counter; i < array.size(); i++)  // .size()-1 to not run off the end of the array
        {
					  cout << "s[" << j << "] = " << sequence[j];
					  cout << "\ta["    << i << "] = " << array[i]    << endl;
					
					  if (sequence[j] == array[i]) { cout << sequence[j] << endl; }
					
						// if we finished the loop and found nothing, then everything should fail
						// this should go first in case the next test passes.
					  if (i == array.size()-1 && array[i] != sequence[j])
						{
							isGud = false;
							cout << "Fail FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n";
							return false;
						}
						// If we found what we needed
            if (array[i] == sequence[j])
            {
							cout << "GOOOOOOOOOOOOOOOOOD\n";
              isGud = true;
							counter++;
							// i=0;
							break;
            }
					counter++;
        }
    }
  return isGud;
}
