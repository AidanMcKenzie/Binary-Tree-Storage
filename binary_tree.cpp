#include "binary_tree.h"
#include <iostream>
#include <string>

using namespace std;

// Creates an empty binary tree
binary_tree::binary_tree(){}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value)
{
	if (tree == nullptr)
	{
		tree = new node;
		(tree)->data = value;
		(tree)->left = nullptr;
		(tree)->right = nullptr;
	}
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const vector<int> &values)
{
	for (int i = 0; i < values.size(); i++)
	{
		insert(values[i]);
	}	
}

void private_copy(struct node *&new_tree, struct node *old_tree)
{
	if(old_tree != nullptr)
	{
		// New node
		new_tree = new node;
		
		// New tree's data is the existing tree's data
		new_tree->data = old_tree->data;
		new_tree->left = nullptr;
		new_tree->right = nullptr;
		
		// New tree's left branch is existing tree's left branch
		private_copy(new_tree->left, old_tree->left);
		
		// New tree's right branch is existing tree's right branch
		private_copy(new_tree->right, old_tree->right);
	}
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{
	private_copy(tree, rhs.tree);
}

void delete_tree(node *tree)
{
	// If tree is equal to nullptr
	if (tree == nullptr)
		return;

	// Delete left branch
	delete_tree(tree->left);

	// Delete right branch
	delete_tree(tree->right);
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{
	delete_tree(tree);
}

void private_insert(node **tree, int value)
{
	// Check if nullptr. If true set new node
	if (*tree == nullptr)
	{
		// Create new node
		*tree = new node;

		// Set new value
		(*tree)->data = value;

		// Set branches to nullptr
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else
	{
		// If value is less than this node - go left
		if (value < (*tree)->data)
		{
			private_insert(&((*tree)->left), value);
		}
		// If value is greater than this node - go right
		else if (value > (*tree)->data)
		{
			private_insert(&((*tree)->right), value);
		}
	}
}

// Adds a value to the tree
void binary_tree::insert(int value)
{
	private_insert(&tree, value);
}

node* find_parent(node* tree) 
{
    static node* parent;

	// If the tree is empty, return the parent node
    if(tree == nullptr) 
	{
        return parent;
    }
	// Else the parent node becomes the tree and the right child is returned
    else 
	{
        parent = tree;
        return find_parent(tree->right);
    }
}

node* private_remove(node* tree, int value)
{
	// New node to store values
	node* storeNode;

	// If the tree is empty, return null
	if(tree == nullptr)
	{
		return NULL;
	}

	// If the current node has a value
	if(tree->data == value) 
	{
		// If there are no children
        if(tree->right == nullptr && tree->left == nullptr) 
		{
			// Delete the tree and return null
            delete(tree);
            return NULL;
		}
		// Else if one or more of the children is empty
		else if(tree->right == nullptr || tree->left == nullptr) 
		{             
			// If right child is empty
            if(tree->right == nullptr) 
			{
				// Left child is stored
                storeNode = tree->left;

				// Delete the tree
                delete(tree);

				// Return the left child
                return storeNode;
            }
            else 
			{
				// Right child is stored
                storeNode = tree->right;

				// Delete the tree
                delete(tree);

				// Return the right child
                return storeNode;
            }
        }
		else 
		{
			// Store the left child of the parent
            storeNode = find_parent(tree->left);

			// Tree's value becomes the storeNode's value
            tree->data = storeNode->data;

			// Left child is removed
            tree->left = private_remove(tree->left, tree->data);

            return tree;
        }
    }
	// Else if the current node is less than the value
    else if(tree->data < value) 
	{
		// Right child is removed
        tree->right = private_remove(tree->right, value);
    }
	// Else if the current node is greater than the value
    else if(tree->data > value) 
	{
		// Right child is removed
        tree->left = private_remove(tree->left, value);
    }
    return tree;
}

// Removes a value from the tree
void binary_tree::remove(int value)
{
	private_remove(tree, value);
}

bool private_exists(node* tree, int value)
{
	// While the tree is not empty
	while (tree != nullptr)
	{
		// If the data is equal to the value, return true
		if (tree->data == value)
		{
			return true;
		}

		// If data is lesser than value
		if (tree->data < value)
		{
			// Tree becomes the right child
			tree = tree->right;
		}
		else
		{
			// If data is greater than value
			if(tree->data > value)
			{
				// Tree becomes left child
				tree = tree->left;
			}
		}
	}

	return false;
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
	return private_exists(tree, value);
}

string private_inorder(node* tree) 
{
	if (tree != nullptr)
	{
		// Recursion - left branch
		string leftBranch = private_inorder(tree->left);

		// Print value
		string str = to_string(tree->data) + " ";

		// Recursion - right branch
		string rightBranch = private_inorder(tree->right);

		// Return the left branch, value and right branch
		return leftBranch + str + rightBranch;
	}

    return string("");
}

// Prints the tree to standard out in numerical order
string binary_tree::inorder() const
{
		// Create string buffer to store the values
		string strBuff = "";
		strBuff = private_inorder(tree);

		// Trim the last space
		size_t endpos = strBuff.find_last_not_of(" \t");

		if(string::npos != endpos)
		{
			strBuff = strBuff.substr(0, endpos + 1);
		}

		return strBuff;
}

string private_preorder(node* tree)
{
	if (tree != nullptr)
	{
		// Print value - current node
		string str = to_string(tree->data) + " ";

		// Recursion - left branch
		string leftBranch = private_preorder(tree->left);

		// Recursion - right branch
		string rightBranch = private_preorder(tree->right);

		// Return value, left branch and right branch
		return str + leftBranch + rightBranch;
	}

    return string("");
}

// Prints the tree in pre-order
string binary_tree::preorder() const
{
    // Create string buffer to store the values
	string preBuff = "";
	preBuff = private_preorder(tree);

	// Trim the last space
	size_t endpos = preBuff.find_last_not_of(" \t");

	if(string::npos != endpos)
	{
		preBuff = preBuff.substr(0, endpos + 1);
	}

	return preBuff;
}

// Prints the tree in post-order
string private_postorder(node* tree)
{
	if (tree != nullptr)
	{
		// Recursion - left branch
		string leftBranch = private_postorder(tree->left);

		// Recursion - right branch
		string rightBranch = private_postorder(tree->right);

		// Print value - current node
		string str = to_string(tree->data) + " ";

		// Return left branch, right branch and value
		return leftBranch + rightBranch + str;
	}

    return string("");
}

// Prints the tree in post-order
string binary_tree::postorder() const
{
    // Create string buffer to store the values
	string postBuff = "";
	postBuff = private_postorder(tree);

	// Trim the last space
	size_t endpos = postBuff.find_last_not_of(" \t");

	if(string::npos != endpos)
	{
		postBuff = postBuff.substr(0, endpos + 1);
	}

	return postBuff;
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{
	// Performs copy on one tree to another
    private_copy(tree, other.tree);
	return *this;
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
    return true;
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
    return true;
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
	// Inserts value and returns tree
	insert(value);
    return binary_tree();
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{
	// Removes value and returns tree
	remove(value);
    return binary_tree();
}

// Reads in values from an input stream into the tree
istream& operator>>(istream &in, binary_tree &value)
{
    return in;
}

// Writes the values, in-order, to an output stream
ostream& operator<<(ostream &out, const binary_tree &value)
{
    return out;
}