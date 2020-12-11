class BST {
public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
  BST &insert(int val);
};

int findClosestValueInBst(BST *tree, int target) {
  // keep going if you have some data
	while (tree != NULL)
	{
		// std::cout << "tree->value: " << tree->value << std::endl;
		// std::cout << tree->left->value << ":" << tree->right->value << std::endl;
		// check for higher values
		// if ((target > tree->right->value || tree->right == NULL)  && (target < tree->left->value || tree->left == NULL))
		
		if (tree->right == NULL)
		{
			cout << "1" << endl;
			// right is null so just check left
			if (target < tree->left->value)
			{
				return tree->value;
			}
		} 
		if (tree->left == NULL && target > tree->right->value)
		{
			cout << "2" << endl;
			// Left is null so just check left
			if (target < tree->right->value)
			{
				return tree->value;
			}
		} 
		
		// check for higher values
		else if (target > tree->value)
		{
			tree = tree->right;
		}
		// check for lower values
		else if (target < tree->value)
		{
			tree = tree->left;
		} else {
			return tree->value;
		}
	}
  return -1;
}
