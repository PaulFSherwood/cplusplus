class BST {
public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
  BST &insert(int val);
};

int findClosestValueInBst(BST *tree, int target) {
	int counter = 0;
  // keep going if you have some data
	while (tree != NULL)
	{
		
		//std::cout << ": " << std::abs (tree->value) << std::endl;
				
		// check for higher values
		if (target > tree->value && tree->right != NULL)
		{
			std::cout << "[" << target << "]:[" << tree->value;
			tree = tree->right;
			std::cout  << "]:Right: " << std::endl;
			std::cout  << tree->value << std::endl;
		}
		// check for lower values
		else if (target < tree->value && tree->left != NULL)
		{
			std::cout << "[" << target << "]:[" << tree->value;
			tree = tree->left;
			std::cout  << "]:Left: " << std::endl;
			std::cout << tree->value << std::endl;
		} else {
			std::cout << "Retrun: ";
			std::cout << tree->value << std::endl;
			return tree->value;
		}
	}
  return -1;
}
