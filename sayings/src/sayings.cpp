#include <iostream>
#include <string>
using namespace std;

class sayings{
	public:
	void coolSayings1()
	{
		cout << "coolSayings1 " << endl;
	}
	void coolSayings2()
	{
		cout << "coolSayings2 " << endl;
	}
	void coolSayings3()
	{
		cout << "coolSayings3 " << endl;
	}
};

int main()
{
	char num;
	sayings speakObject;
	cout << "enter the saying number\n";
	cin >> num;
	
	switch(num){
		case '1':
			speakObject.coolSayings1();
			break;
		case '2':
			speakObject.coolSayings2();
			break;
		case '3':
			speakObject.coolSayings3();
			break;
		default:
			cout << "error\n";
		}
	return 0;
}
