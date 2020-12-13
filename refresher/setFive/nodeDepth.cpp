#include <algorithm>    // std::max
using namespace std;

class BinaryTree {
public:
  int value;
  BinaryTree *left;
  BinaryTree *right;

  BinaryTree(int value) {
    this->value = value;
    left = NULL;
    right = NULL;
  }
};

// struct Level {
// 	BinaryTree *root;
// 	int depth;
// };
int getDepth(BinaryTree *root, int depth);
int nodeDepths(BinaryTree *root) {
	return getDepth(root, 0);
// 	// storage
// 	int sumOfDepths = 0;
// 	vector<Level> stack = {{root, 0}};
	
// 	while(stack.size() > 0) {
		
// 		BinaryTree *node = stack.back().root;
// 		int depth        = stack.back().depth;
		
// 		stack.pop_back(); // remove the last container
		
// 		if(node == NULL) { continue; }
		
// 		sumOfDepths += depth;
		
// 		stack.push_back(Level{node->left,  depth + 1});
// 		stack.push_back(Level{node->right, depth + 1});
// 	}
// 	return sumOfDepths;
}
// The point of this is not to count the values of the nodes,
// but to count the depths of the trees. 
int getDepth(BinaryTree *root, int depth)
{
	// if we are at the root exit
	if (root == NULL) { return 0; }
	cout << depth << endl;
	// pass the next depth L&R add +1 to depth add everything to depth and return
	return depth + getDepth(root->left, depth+1) + getDepth(root->right, depth+1);
}
