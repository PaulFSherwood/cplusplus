#include <any>
#include <vector>

using namespace std;

// Tip: You can use el.type() == typeid(vector<any>) to check whether an item is
// a list or an integer.
// If you know an element of the array is vector<any> you can cast it using:
//     any_cast<vector<any>>(element)
// If you know an element of the array is an int you can cast it using:
//     any_cast<int>(element)
int getSum(vector<any> array, int multiplier = 1)
{
	int sum = 0;
	// first time seeing this.
	// this is 
	for (auto el : array)
	{
		if (el.type() == typeid(vector<any>))
		{
			sum += getSum(any_cast<vector<any>>(el), multiplier + 1);
		} else {
			sum += any_cast<int>(el);
		}
	}
	return sum * multiplier;
}
int productSum(vector<any> array) {
  int sum = getSum(array, 1);
  return sum;
}
// This is getting out of hand.  I have questions about these programs but no one to ask them to.
// This uses new stuff I haven't seen before and it took awhile to look them up.
// auto el : array  - This is like the pythons loop 
// https://en.cppreference.com/w/cpp/language/range-for
// el.type() == typeid(vector<any>)) - #import <any> this gives you access to .type that returns the type for variables
// https://en.cppreference.com/w/cpp/utility/any

