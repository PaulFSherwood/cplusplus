#include <cmath> 

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
	int one, two, three = 0;
  // keep going if you have some data
	cout << "T: (" << target << ")\n"; 
	while (tree != NULL)
	{
		if (tree        != NULL){ one   = tree->value;        } else { one   = 0; }
		if (tree->left  != NULL){ two   = tree->left->value;  } else { two   = 0; }
		if (tree->right != NULL){ three = tree->right->value; } else { three = 0; }
		cout << "[" << one << "]{" << two << "}[" << three << "]" << endl;
		
		// check for higher values
		if (target > tree->value && tree->right != NULL)
		{
			// if the current spot is smaller than the right
			if (tree->right != NULL) {
				if ((abs(tree->value) - target) < (abs(tree->right->value)-target))
				{
					cout << "Good R: " << tree->value << endl;
				}
			}
			//std::cout << "[" << target << "]:Right: [" << tree->value;
			tree = tree->right;
			//std::cout  << "]:[" << tree->value <<  "]" << std::endl;
			
			// if ((abs(tree->right->value - target)) < (abs(tree->value - target)))
			// {
			// 	cout << "found a low match" << endl;
			// }
		}
		// check for lower values
		else if (target < tree->value && tree->left != NULL)
		{
			int one = abs(tree->value - target);
			int two = abs(tree->left->value - target);
			if (tree->left != NULL) {
				if ((abs(tree->value) - target) > (abs(tree->left->value) - target))
				{
					cout << "Good L: " << tree->value << endl;
				}
			}
			if (one > two)
			{
				tree = tree->left;
			} else {
				return tree->value;
			}
			//std::cout << "[" << target << "]:Left: [" << tree->value;
			//tree = tree->left;
			//std::cout  << "]:[" << tree->value << "]" << std::endl;
		} else {
			std::cout << "Retrun: ";
			std::cout << tree->value << std::endl;
			// should probably test here as i am about to output
			// is this value clo
			return tree->value;
		}
	}
  return -1;
}
