using namespace std;

bool isPalindrome(string str) {
	// Duplicate the string to edit
	string Bstr = str;
	cout << str;
	
  // https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
	int n = Bstr.length();
	for (int i = 0; i < n / 2; i++) {
		swap(Bstr[i], Bstr[n - i - 1]);
		
	}
	cout << " || ";
	cout << Bstr;
	// http://www.cplusplus.com/reference/string/string/compare/
	if (str.compare(Bstr) == 0) {
		return true;
	} else {
  	return false;
	}
}
