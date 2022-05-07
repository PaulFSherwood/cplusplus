using namespace std;

int getNthFib(int n) {
	cout << "n: " << n << endl;
	int n0 = 0, n1 = 1, out = 0;
	for (int i = 0; i < n-2; i++)
	{
		out = n0 + n1;
		n0 = n1;
		n1 = out;
		cout << "n0: " << n0 << " n1: " << n1 << " out: " << out << endl;
	}
	     if (n == 0) { return 0; } 
	else if (n == 1) { return 0; } 
	else if (n == 2) { return 1; }
	cout << out;
  return out;
}
