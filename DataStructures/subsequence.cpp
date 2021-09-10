// INPUT 
// array = [5, 1, 22, 25, 6, -1, 8, 10]
// sequence = [1, 6, -1, 10]
//
// OUTPUT
// TRUE
using namespace std;

bool isValidSubsequence(vector<int> array, vector<int> sequence) {
  // Write your code here.

    // first loop to track the first array
    for (int i = 0; i < array.size(); i++)
    {
        // second loop to track the second array
        for (int i = 0; i < sequence.size(); i++)
        {
            if (array[i] != sequence[j])
            {
                return false;
            }
            if (i = array.size() && array[i] == sequence[j])
            {
                return true;
            }
        }
    }
    

  return false;
}
