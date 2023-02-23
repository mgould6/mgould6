#include "Header.h";

using namespace std;

/*
Insertion in a BST – Iterative and Recursive Solution

A Binary Search Tree (BST) is a rooted binary tree, whose nodes each store a key (and optionally, an associated value), and each has two distinguished subtrees, commonly denoted left and right. The tree should satisfy the BST property, which states that each node’s key must be greater than all keys stored in the left subtree and not greater than all keys in the right subtree. Ideally, unique values should be present in the tree.

BST

Binary search trees are a fundamental data structure used to construct more abstract data structures such as sets, multisets, and associative arrays (maps, multimaps, etc.).

Practice This Problem

Recursive Version
When looking for a place to insert a new key, traverse the tree from root-to-leaf, making comparisons to keys stored in the tree’s nodes and deciding based on the comparison to continue searching in the left or right subtrees. In other words, we examine the root and recursively insert the new node to the left subtree if its key is less than that of the root or the right subtree if its key is greater than or equal to the root.

Insertion in the BST
https://www.techiedelight.com/wp-content/uploads/Insert-into-BST.png

Following is the implementation of the above approach in C++
*/
struct Node
{
	int data;
	Node* left, * right;

	Node(int data)
	{
		this->data = data;
		this->left = this->right = nullptr;
	}

};

//function to perform inorder traversal on the tree
void inorder(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

//recursive function to insert a key into a BST
Node* insert(Node* root, int key)
{
	//if the root is null, create a new node and return it
	if (root == nullptr)
	{
		return new Node(key);
	}

	//if the given key is less than the root node, recur for the left subtree 
	if (key < root->data)
	{
		root->left = insert(root->left, key);
	}
	//if the given key is more than the root node, recur for the right subtree
	else
	{
		root->right = insert(root->right, key);
	}
	return root;
}

//function to construct a BST from given keys
Node* constructBST(vector<int> const& keys)
{
	Node* root = nullptr;
	for (int key : keys)
	{
		root = insert(root, key);
	}
	return root;
}





int main()
{
	vector<int> keys = { 15, 10, 20, 8, 12, 16, 25 };

	Node* root = constructBST(keys);
	inorder(root);


	return 0;
}


/*

Iterative Version
Another way to explain the insertion is to insert a new node into the tree. Initially, the key is compared with that of the root. If its key is less than the root’s, it is then compared with the root’s left child’s key. If its key is greater, it is compared with the root’s right child. This process continues until the new node is compared with a leaf node, and then it is added as this node’s right or left child, depending on its key: if the key is less than the leaf’s key, then it is inserted as the leaf’s left child; otherwise, as to the leaf’s right child.

The iterative version is demonstrated below in C++, Java, and Python:

The time complexity of the above solution is O(h), where h is the BST height. The BST height in the worst-case is as much as the total number of keys in the BST. The worst case happens when given keys are sorted in ascending or descending order, and we get a skewed tree (all the nodes except the leaf have one and only one child).

For height-balanced BSTs, with each comparison, skip about half of the tree so that each insertion operation takes time proportional to the logarithm of the total number of items n stored in the tree, i.e., log2n. This is much better than the linear time required to find items by key in an (unsorted) array but slower than the corresponding operations on hash tables.


The space used by the recursive routine is also proportional to the tree’s height, whereas the iterative version doesn’t

struct Node
{
	int data;
	Node* left, * right = nullptr;

	Node(int data)
	{
		this->data = data;
		this->left = this->right = nullptr;
	}
};

//function to perform an inorder traversal
void inorder(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

//iterative function to insert a key into a BST.
//root is passd by reference to the function
void insertIterative(Node*& root, int key)
{
	//start with the root node
	Node* curr = root;

	//pointer to store the parent of the current node
	Node* parent = nullptr;

	//if the tree is empty, create a new node and set it as root
	if (root == nullptr)
	{
		root = new Node(key);
		return;
	}

	//traverse the tree and find the parent node of the given key
	while (curr != nullptr)
	{
		//update the parent to the current node
		parent = curr;

		//if the given key is less than the current node go to the
		//left subtree; otherwise, go to the right subtree.

		if (key < curr->data)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}

	//construct a node and assign it to the appropriate parent pointer
	if (key < parent->data)
	{
		parent->left = new Node(key);
	}
	else
	{
		parent->right= new Node(key);
	}
}

//function to construct a BST from given keys
Node* constructBST(vector<int> const& keys)
{
	Node* root = nullptr;
	for (int key : keys)
	{
		insertIterative(root, key);
	}
	return root;
}
*/