using namespace std;

bool isValidSubsequence(vector<int> array, vector<int> sequence) {
  // using the sequence number search throught the array for matches
	int counter = 0;
	// 1 2 3 4
	// ^      
	//   ^
	// go throught the sequence set one at a time.
	for (int i = 0; i < sequence.size(); i++)
	{
		// look for a match startinf from the beginning
		for (int j = i; j < array.size(); j++)
		{
			std::cout << "s[" << i << "]" << sequence[i] << ":" << "a[" << j << "]" << array[j] << std::endl;
			if (sequence[i] == array[j])
			{
				i++;  // move the test case to the next in sequence 
				counter++;  // for testing pass / fail
			}
		}
		
	}
	// if the good tests equal the size of the sequnce then reutnr true.
	if (counter == sequence.size())
	{
		return true;
	} else {
	return false;
	}
}
