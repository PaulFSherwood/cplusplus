// INPUT 
// array = [5, 1, 22, 25, 6, -1, 8, 10]
// sequence = [1, 6, -1, 10]
//
// OUTPUT
// TRUE
using namespace std;

bool isValidSubsequence(vector<int> array, vector<int> sequence) {
    bool isGud = false;

    // first loop to track the first array
    for (int j = 0; j < sequence.size(); j++)
    {
				cout << endl;
			isGud = false;
        // second loop to track the second array
        for (int i = 0; i < array.size(); i++)
        {
					  cout << "sequence[" << j << "] = " << sequence[j] << endl;
					  cout << "array["    << i << "] = " << array[i]    << endl;
					
					  if (sequence[j] == array[i]) { cout << sequence[j] << endl; }
					
						// causes one run failure
						// if (array[i] != sequence[j])
						// {
						// 		return false; 
						// }
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
							j++;
							//i=array.size();
            }
        }
    }
    

  return isGud;
}
