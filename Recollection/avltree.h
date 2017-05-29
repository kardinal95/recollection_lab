#pragma once

using namespace std;

/*
Structure for storing tree elements
*/
template<typename T>
struct Tree
{
	T *data;
	Tree<T> *left;
	Tree<T> *right;
	// Weight of subtree (in max)
	int weight;
};

/*
Supporting function for creating new tree node
Input:
data - pointer to data
Output:
created node
*/
template<typename T>
Tree<T> *make_node(T *data)
{
	Tree<T> *node = new Tree<T>;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	// Base weight is 0
	node->weight = 0;
	return node;
}

/*
Get pointer to subtree of given node with max weight
Input:
root - top subtree node
Output:
top node of subtree with maximum weight (NULL if none)
*/
template<typename T>
Tree<T> *get_max_subtree(Tree<T> *root)
{
	// Null by default (no subtrees)
	Tree<T> *result = NULL;
	if (root != NULL)
	{
		// Try left
		result = root->left;
		if (result == NULL)
		{
			// Switch to right if left is empty
			result = root->right;
		}
		// If both present - choose max
		else if (root->right != NULL)
		{
			if (root->right->weight > root->left->weight)
			{
				result = root->right;
			}
		}
	}
	return result;
}

/*
Get weight of current node. Depends on its subtrees
Input:
root - top subtree node
Output:
node weight
*/
template<typename T>
int get_weight(Tree<T> *root)
{
	// Base weight 0 if no subtrees
	int subweight = 0;
	// Choose subtree with maximum weight
	Tree<T> *max = get_max_subtree(root);
	if (max != NULL)
	{
		// The weight of node is maximum subtree weight + 1
		subweight = max->weight + 1;
	}
	return subweight;
}

/*
Check if the current node is balanced (difference in weights is no more than 1)
Input:
root - top subtree node
Output:
true if balanced, false if not
*/
template<typename T>
bool is_balanced(Tree<T> *root)
{
	// Empty node is always balanced
	bool balanced = true;
	if (root != NULL)
	{
		if (root->left != NULL)
		{
			if (root->right != NULL)
			{
				// If both subtrees are present - check the difference in weights
				balanced = (abs(root->left->weight - root->right->weight) <= 1);
			}
			else
			{
				// Only left subtree - check it's weight
				balanced = root->left->weight < 1;
			}
		}
		else
		{
			// Only right subtree - check it's weight
			if (root->right != NULL)
			{
				balanced = root->right->weight < 1;
			}
		}
	}
	return balanced;
}

/*
Destroy the given node (empty memory)
Input:
node - node to destroy
*/
template <typename T>
void destroy_node(Tree<T>* node)
{
	delete(node->data);
	delete(node);
}

/*
Get node of given tree with minimum parameter (leftmost)
Input:
root - top subtree node
Output:
the node found (NULL if empty tree given)
*/
template <typename T>
Tree<T> *get_minimum(Tree<T>* root)
{
	Tree<T>* minimum = root;
	// Move left till the end
	if (minimum != NULL)
	{
		while (minimum->left != NULL) minimum = minimum->left;
	}
	return minimum;
}

/*
Delete node of given tree with minimum parameter (leftmost)
Input:
root - top subtree node
Output:
tne new top node (NULL if empty)
*/
template <typename T>
Tree<T> *delete_minimum(Tree<T>* root)
{
	// If not the leftmost element
	if (root != NULL && root->left != NULL)
	{
		// Call the subsequent funtion for left subtree
		root->left = delete_minimum(root->left);
		// Recalculate weight and rearrange the tree if necessary
		if (!is_balanced(root)) root = rearrange_tree(root);
		root->weight = get_weight(root);
	}
	else
	{
		// Remove the minimum element
		root = NULL;
	}
	return root;
}

/*
Insert new node into the tree. Rearrange all the nodes accordint to AVL tree rules
Input:
root - top subtree node
node - node to add into the tree
Output:
top node of resulting tree
*/
template<typename T>
Tree<T> *insert_node(Tree<T> *root, Tree<T> *node)
{
	// If inserting into empty tree - return the node itself
	if (root == NULL)
	{
		root = node;
	}
	else if (node != NULL)
	{
		// Insert element into right/left subtree accordingly
		if (*node->data >= *root->data)
		{
			root->right = insert_node(root->right, node);
		}
		else
		{
			root->left = insert_node(root->left, node);
		}
		// Check the balance and rearrange tree if needed
		if (!is_balanced(root))	root = rearrange_tree(root);
		// Recalculate the weight of current node
		root->weight = get_weight(root);
	}
	return root;
}

/*
Remove node with given data from given tree.
Returns the same tree if the element cannot be found
Input:
root - top subtree node
data - value in node to delete
Output:
top node of resulting tree
*/
template <typename T>
Tree<T> *remove_node(Tree<T> *root, T* data)
{
	// Base new root is current
	Tree<T>* newroot = root;
	// Skip if empty
	if (root != NULL)
	{
		// If node found
		if (*data == *root->data)
		{
			// If right subtree is empty - connect left subtree
			if (root->right == NULL) newroot = root->left;
			// If right subtree is not empty
			else
			{
				// Find minimum element in right subtree (new root)
				newroot = get_minimum(root->right);
				// Find resulting subtree (without minimum element)
				Tree<T>* rightroot = delete_minimum(root->right);
				// Make necessary connections
				newroot->left = root->left;
				newroot->right = rightroot;
			}
			// Destroy the node to delete
			destroy_node(root);
		}
		// If not found - call subsequent function on according subtree
		else if (*data > *root->data) root->right = remove_node(root->right, data);
		else if (*data < *root->data) root->left = remove_node(root->left, data);

		// Recalculate weight and rearrange the subtree if necessary
		if (!is_balanced(newroot)) newroot = rearrange_tree(newroot);
		if (newroot != NULL) newroot->weight = get_weight(newroot);
	}
	return newroot;
}

/*
Perform left rotation of tree
Input:
root, child, grandchild - key nodes
*/
template<typename T>
void left_rotate(Tree<T> *root, Tree<T> *child, Tree<T> *grandchild)
{
	Tree<T> *top = child;
	root->right = child->left;
	child->left = root;
	// If used in LeftRight
	if (grandchild->left == root)
	{
		grandchild->left = child;
		top = grandchild;
	}

	// Recalculate weights
	if (top->left != NULL) top->left->weight = get_weight(top->left);
	if (top->right != NULL) top->right->weight = get_weight(top->right);
	top->weight = get_weight(top);
}

/*
Perform left rotation of tree
Input:
root, child, grandchild - key nodes
*/
template<typename T>
void right_rotate(Tree<T> *root, Tree<T> *child, Tree<T> *grandchild)
{
	Tree<T> *top = child;
	root->left = child->right;
	child->right = root;
	// If used in Rightleft
	if (grandchild->right == root)
	{
		grandchild->right = child;
		top = grandchild;
	}

	// Recalculate weights
	if (top->left != NULL) top->left->weight = get_weight(top->left);
	if (top->right != NULL) top->right->weight = get_weight(top->right);
	top->weight = get_weight(top);
}

/*
Rearrange the unbalanced tree (AVL type)
Input:
root - top subtree node
Output:
rearranged tree top node
*/
template<typename T>
Tree<T> *rearrange_tree(Tree<T> *root)
{
	// Determines rotate selection
	int rotate = 0;
	Tree<T> *newroot = NULL;
	// Get the supporting elements (subnodes with max weight)
	Tree<T> *child = get_max_subtree(root);
	Tree<T> *grandchild = get_max_subtree(child);
	// Choose rotation
	if (root->right == child) rotate += 10;
	if (child->right == grandchild) rotate += 1;
	// Perform necessary rotation(s) and choose new top element
	switch (rotate)
	{
		// LeftLeft
	case 00:
	{
		right_rotate(root, child, grandchild);
		newroot = child;
		break;
	}
	// LeftRight
	case 01:
	{
		left_rotate(child, grandchild, root);
		right_rotate(root, grandchild, child);
		newroot = grandchild;
		break;
	}
	// RightLeft
	case 10:
	{
		right_rotate(grandchild, child, root);
		left_rotate(root, child, grandchild);
		newroot = grandchild;
		break;
	}
	// RightRight
	case 11:
	{
		left_rotate(root, child, grandchild);
		newroot = child;
		break;
	}
	default:
		// Do nothing
		break;
	}
	return newroot;
}