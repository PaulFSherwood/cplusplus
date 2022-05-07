#include <algorithm>    // for std::max
// https://www.youtube.com/watch?v=D2cFSDfg0So
// GOOGLE - MAXIMUM DEPTH OF BINARY TREE (LeetCode)
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


int maxDepth(BinaryTree *root) {
	if(root == NULL) { return 0; }
  // get the level of the next level and store it
  int left = maxDepth(root->left);
  int right = maxDepth(root->right);
  
  // find the maximum level and add root tree level +1
  return max(left, right) + 1;
}
