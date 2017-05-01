#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Stack {
	private:
		T datastore[100];
		int top;
	public:
		Stack() {
			top = -1;
		}

		// template <typename T>
		// void push(T num) {
		void push (int num) {
			++top;
			datastore[top] = num;
		}
		T pop() {
			int val = datastore[top];
			datastore[top] = 0;
			--top;
			return val;
		}
		T peek() {
			return datastore[top];
		}
};

template<>
class Stack<string> {
	private:
		string datastore[100];
		int top;
	public:
		Stack() {
			top = -1;
		}

		void push(string value) {
			++top;
			datastore[top] = value;
		}
		string pop() {
			string val = datastore[top];
			datastore[top] = "";
			--top;
			return val;
		}
		string peek() {
			return datastore[top];
		}
};


int main() {

	Stack<int> numbers;
	numbers.push(12);
	numbers.push(22);
	cout << numbers.peek() << endl;
	int value = numbers.pop();
	 cout << numbers.peek() << endl;
	

	/*Stack<string> names;
	names.push("bob");
	names.push("Ann");
	cout << names.peek() << endl;
	string tempString = names.pop();
	cout << names.peek() << endl;*/
	
	/*Stack<char> characters;
	characters.push('A');
	characters.push('B');
	cout << characters.peek() << endl;
	char tempChar = characters.pop();
	cout << characters.peek() << endl;*/

	Stack<string> names;
	names.push("Mary");
	names.push("Joe");
	cout << names.peek() << endl;
	string name = names.pop();
	cout << names.peek() << endl;
	string tempChar = names.pop();


	return 0;
}