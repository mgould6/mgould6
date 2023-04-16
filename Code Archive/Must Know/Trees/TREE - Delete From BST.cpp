#include "Header.h";

using namespace std;

/*
Deletion from BST (Binary Search Tree)
Given a BST, write an efficient function to delete a given key in it.

Practice This Problem

There are three possible cases to consider deleting a node from BST:


Case 1: Deleting a node with no children: remove the node from the tree.
https://www.techiedelight.com/wp-content/uploads/Deletion-in-BST-Case-1.png
Deletion from BST – Case 1

Case 2: Deleting a node with two children: call the node to be deleted N. Do not delete N. Instead, choose either its inorder successor node or its inorder predecessor node, R. Copy the value of R to N, then recursively call delete on R until reaching one of the first two cases. If we choose the inorder successor of a node, as the right subtree is not NULL (our present case is a node with 2 children), then its inorder successor is a node with the least value in its right subtree, which will have at a maximum of 1 subtree, so deleting it would fall in one of the first 2 cases.
https://www.techiedelight.com/wp-content/uploads/Deletion-in-BST-Case-2-1.png
Deletion from BST – Case 2

Case 3: Deleting a node with one child: remove the node and replace it with its child.
https://www.techiedelight.com/wp-content/uploads/Deletion-in-BST-Case-3.png
Deletion from BST – Case 3

Broadly speaking, nodes with children are harder to delete. As with all binary trees, a node’s inorder successor is its right subtree’s leftmost child, and a node’s inorder predecessor is the left subtree’s rightmost child. In either case, this node will have zero or one child. Delete it according to one of the two simpler cases above.

The algorithm can be implemented as follows in C++
*/
#include <iostream>
using namespace std;

// Data structure to store a BST node
struct Node
{
	int data;
	Node* left = nullptr, * right = nullptr;

	Node() {}
	Node(int data) : data(data) {}
};

// Function to perform inorder traversal on the BST
void inorder(Node* root)
{
	if (root == nullptr) {
		return;
	}

	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

// Helper function to find minimum value node in the subtree rooted at `curr`
Node* getMinimumKey(Node* curr)
{
	while (curr->left != nullptr) {
		curr = curr->left;
	}
	return curr;
}

// Recursive function to insert a key into a BST
Node* insert(Node* root, int key)
{
	// if the root is null, create a new node and return it
	if (root == nullptr) {
		return new Node(key);
	}

	// if the given key is less than the root node, recur for the left subtree
	if (key < root->data) {
		root->left = insert(root->left, key);
	}

	// if the given key is more than the root node, recur for the right subtree
	else {
		root->right = insert(root->right, key);
	}

	return root;
}

// Iterative function to search in the subtree rooted at `curr` and set its parent.
// Note that `curr` and `parent` is passed by reference to the function.
void searchKey(Node*& curr, int key, Node*& parent)
{
	// traverse the tree and search for the key
	while (curr != nullptr && curr->data != key)
	{
		// update the parent to the current node
		parent = curr;

		// if the given key is less than the current node, go to the left subtree;
		// otherwise, go to the right subtree
		if (key < curr->data) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
}

// Function to delete a node from a BST
void deleteNode(Node*& root, int key)
{
	// pointer to store the parent of the current node
	Node* parent = nullptr;

	// start with the root node
	Node* curr = root;

	// search key in the BST and set its parent pointer
	searchKey(curr, key, parent);

	// return if the key is not found in the tree
	if (curr == nullptr) {
		return;
	}

	// Case 1: node to be deleted has no children, i.e., it is a leaf node
	if (curr->left == nullptr && curr->right == nullptr)
	{
		// if the node to be deleted is not a root node, then set its
		// parent left/right child to null
		if (curr != root)
		{
			if (parent->left == curr) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		// if the tree has only a root node, set it to null
		else {
			root = nullptr;
		}

		// deallocate the memory
		free(curr);		// or delete curr;
	}

	// Case 2: node to be deleted has two children
	else if (curr->left && curr->right)
	{
		// find its inorder successor node
		Node* successor = getMinimumKey(curr->right);

		// store successor value
		int val = successor->data;

		// recursively delete the successor. Note that the successor
		// will have at most one child (right child)
		deleteNode(root, successor->data);

		// copy value of the successor to the current node
		curr->data = val;
	}

	// Case 3: node to be deleted has only one child
	else {
		// choose a child node
		Node* child = (curr->left) ? curr->left : curr->right;

		// if the node to be deleted is not a root node, set its parent
		// to its child
		if (curr != root)
		{
			if (curr == parent->left) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}

		// if the node to be deleted is a root node, then set the root to the child
		else {
			root = child;
		}

		// deallocate the memory
		free(curr);
	}
}

int main()
{
	int keys[] = { 15, 10, 20, 8, 12, 16 };

	Node* root = nullptr;
	for (int key : keys) {
		root = insert(root, key);
	}

	deleteNode(root, 12);
	inorder(root);

	return 0;
}

