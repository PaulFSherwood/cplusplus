using namespace std;

bool isValidSubsequence(vector<int> array, vector<int> sequence) {
	int lastNumber = 0;
  // We need to go through the array vector one set at a time.
	for (int i = 0; i < array.size(); i++)
	{
		// Next we use the second vector to test if all of those numbers are in this array
  	for (int j = 0; j < sequence.size(); j++)
		{
			// check if the number in sequence[i] is anywhere in array[n]
			if (array[i] == sequence[j] && lastNumber <= i)
			{
				lastNumber = i;
				std::cout << i << ":" << j << ": " << "s[" << sequence[i] << "] - a[" << array[j] << "] " <<  lastNumber << std::endl;
				// if we find a match remove it from the vector
				sequence.erase(sequence.begin() + j);
			}
		}
	}
	// if the vector is empty then everything must have matched
	if (sequence.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
