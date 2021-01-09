using namespace std;

string runLengthEncoding(string str) {
  // Write your code here.
	// get the first character
	char marker = str[0];
	string output = "";
	string word = "";
	int counter = 1;
	// count up to 9 
	for (int i = 0; i < str.size(); i++)
	{
		word = "";
		if (str[i] == str[i+1])
		{
			if (counter == 9)
			{
				// add output to string
				output += '9';
				output += str[i];
				
				counter = 1;
			} else {
				counter++;
			}
			// cout << counter << " " << str[i] << " ";
		}

	}
	cout << output << endl;
	// add to output string
  return output;
}
