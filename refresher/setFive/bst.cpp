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
	int closest = 2147483647;
	int one, two, three = 0;
  // keep going if you have some data
	cout << "T: (" << target << ")\n"; 
	while (tree != NULL)
	{
		if (tree        != NULL){ one     = tree->value;        } else { one     = 0; }
		if (tree->left  != NULL){ two     = tree->left->value;  } else { two     = 0; }
		if (tree->right != NULL){ three   = tree->right->value; } else { three   = 0; }
		//if (tree        != NULL){ closest = tree->value;        } else { closest = 0; }
		cout << "[" << one << "]{" << two << "}[" << three << "]=[" << closest << "]" << endl;
		
		// check for higher values
		if (target > tree->value && tree->right != NULL)
		{
			if ((abs(tree->value) - target) < (abs(tree->right->value) - target)) { closest = tree->value; }
			cout << "R-V: " << target - abs(tree->value) << " R-R: " << target - abs(tree->right->value) << " c: " << closest << endl;
			tree = tree->right;
		}
		// check for lower values
		else if (target < tree->value && tree->left != NULL)
		{
			if ((abs(tree->value) - target) < (abs(tree->left->value) - target)) { closest = tree->value; }
			cout << "L-V: " << abs(tree->value) - target << " R-L: " << abs(tree->left->value) - target << " c: " << closest << endl;
			int one = abs(tree->value - target);
			int two = abs(tree->left->value - target);
			
			if (one > two)
			{
				tree = tree->left;
			} else {
				return tree->value;
			}
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
