// full disclosure I could not figure this out after ready and going through videos
// I was stuck on the branchSums function and didn't realise you could make a 
// helper function for this to work.  also I did not know how I would pass the 
// vector around although I knew I would need a vector and a dfs.

using namespace std;

// This is the class of the input root. Do not edit it.
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
// helper function to run recursion on
void calculateBranchSums(BinaryTree *node, int runningSum, vector<int> &sums);

vector<int> branchSums(BinaryTree *root) {
  // a quick glance you could store everying in a vector
	vector<int> sums;
	// run recusion to find the sum and store in the vector
	calculateBranchSums(root, 0, sums);
  return sums;
}

void calculateBranchSums(BinaryTree *node, int runningSum, vector<int> &sums) {
	if (node == NULL) { return; }
	// get the current value and combine it with the running sum
	int newRunningSum = runningSum + node->value;
	// if you are at a leaf then add the total to the vector (no index required)
	if(node->left == NULL && node->right == NULL) {
		sums.push_back(newRunningSum);
		return;
	}
	// we are not at a leaf keep pushing the sum along the node branches
	calculateBranchSums(node->left, newRunningSum, sums);
	calculateBranchSums(node->right, newRunningSum, sums);
}
