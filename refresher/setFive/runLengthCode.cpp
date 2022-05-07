using namespace std;

string runLengthEncoding(string str) {
	cout << str << endl;
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
			// show output for 9 characters
			if (counter == 9)
			{
				// add output to string
				output += '9';
				output += str[i];
				// reset count
				counter = 1;
			} else {
				// not ready to output increase counter
				counter++;
			}
			// cout << counter << " " << str[i] << " ";
			// show output that is less than 9 characters
		} else {
			// cout << counter << " " << str[i] << " ";
			// add output to string
			output += std::to_string(counter);
			output += str[i];
			// reset count
			counter = 1;
			// cout << output << endl;
		}
	}
	cout << output << endl;
	// return what we have.
  return output;
}
