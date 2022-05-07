class BST {
public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
  BST &insert(int val);
};

int findClosestValueInBst(BST *tree, int target) {
 	int bestValue = 987654321;
	while (tree != NULL) {
		// cout << "tree:" << tree->value << "L:" << tree->left->value << "R:" << tree->right->value << endl;
		// test and save the best value
		if (abs(target - tree->value) < abs( target - bestValue)) { bestValue = tree->value; 
		cout << "Target: " << target << " abs(tree->value): " << abs(tree->value) << " BestValue: " << bestValue << endl;
																							 }
		// we need to move left or right based on leafs
		// also make sure the node isn't empty so we dont crash
		if (target < tree->value && tree->left != NULL)
		{
			// cout << "Target: " << target << " tree->value: " << tree->value << " tree->left: " << tree->left->value << endl;
			tree = tree->left;
		}
		else if (target > tree->value && tree->right != NULL)
		{
			// cout << "Target: " << target << " tree->value: " << tree->value << " tree->right: " << tree->right->value << endl;
			tree = tree->right;
		}
		// test the first node and see if it is right
		else if (target == tree->value) { return bestValue; }
		else
		{
			return bestValue;
		}
	}
	
  return -1;
}
