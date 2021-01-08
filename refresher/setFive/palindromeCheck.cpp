using namespace std;

bool isPalindrome(string str) {
	string Bstr = str;
	cout << str;
  // setup
	int n = Bstr.length();
	
	for (int i = 0; i < n / 2; i++) {
		swap(Bstr[i], Bstr[n - i - 1]);
		
	}
	cout << " || ";
	cout << Bstr;
	
	if (str.compare(Bstr) == 0) {
		return true;
	} else {
  	return false;
	}
}
