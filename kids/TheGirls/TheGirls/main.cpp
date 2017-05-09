#include <iostream>
#include <sstream>

using namespace std;

class child {
	private:
		int age;
		string name;

	public:
		int getAge() {
			return age;
		}
		void setAge(int tempAge) {
			age = tempAge;
		}
		string getName() {
			return name;	
		}
		void setName(string tempName) {
			name = tempName;
		}
	
		void printClass(child *kiddo) {
			cout << kiddo->getAge() << endl;
			cout << kiddo->getName() << endl;
		}


};


int main() {

	child lilly;
	lilly.setAge(15);
	lilly.setName("Lillian");

	child lauren;
	lauren.setAge(13);
	lauren.setName("Lauren");

	lilly.printClass(&lilly);
	lauren.printClass(&lauren);
	
	return 0;
}