// full disclosure I could not figure this out after ready and going through videos
// I was stuck on the branchSums function and didn't realise you could make a 
// helper function for this to work.  also I did not know how I would pass the 
// vector around although I knew I would need a vector and a dfs.


// updated: I did this one by memory, I understand it but failed at implementation.
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
// function got return a tree/leaf values
void getBinaryTreeSum(BinaryTree *node, int runningTotal, vector<int> &totalReference);

vector<int> branchSums(BinaryTree *root) {
  // we need a vector
  vector<int> total;
  // call the function to kick off this show
  getBinaryTreeSum(root, 0, total);
  return total;
}
// function got return a tree/leaf values
void getBinaryTreeSum(BinaryTree *node, int runningTotal, vector<int> &totalReference)
{
	// see if we have nothing else to do
	if(node == NULL) { return; }
	// housekeeping increase the runningtotal
	int currentTotal = runningTotal + node->value;
	// See if we are at a leaf
	if (node->left == NULL && node->right == NULL)
	{
		// we are at a leaf add to the vector
		totalReference.push_back(currentTotal);
		return;
	}
	// we are d.u.n. done keep going.
	getBinaryTreeSum(node->left, currentTotal, totalReference);
	getBinaryTreeSum(node->right, currentTotal, totalReference);
}
