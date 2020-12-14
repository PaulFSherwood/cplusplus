#include <vector>
using namespace std;

// Do not edit the class below except
// for the depthFirstSearch method.
// Feel free to add new properties
// and methods to the class.
class Node {
public:
  string name;
  vector<Node *> children;

  Node(string str) { name = str; }

  vector<string> depthFirstSearch(vector<string> *array) {
		// this array size must be packed before it is used.
		// std::cout << this->children.size() << ":" << this->name << std::endl;
		
    array->push_back(this->name); // add node name to the vector
		// go through vector
		for(int i = 0; i < this->children.size(); i++)
		{
			std::cout << "Size: " << this->children.size() << "|| Name:" << this->name << "|| " << "children[" << i << "]" << std::endl;
			// never seen this before but using the index of the vector
			// node to pull out all the data.
			children[i]->depthFirstSearch(array);
		}
		cout << "=========================" << endl;
    return *array;
  }

  Node *addChild(string name) {
    Node *child = new Node(name);
    children.push_back(child);
    return this;
  }
};

