#include "Header.h";

using namespace std;

/*
Linked List Implementation in C++

3. Generic Method
Both above methods are not practical when the total number of nodes increases in the linked list. If the keys are given in any container, such as an array, vector, or set, we can easily construct a linked list by traversing the container, as shown below:


*/

//a linked list node
class Node
{
public:
	int key;	//data field
	Node* next;
};

//utility function to return new linked list node from the heap
Node* newNode(int key, Node* next)
{
	//allocate a new node in a heap and set its data
	Node* node = new Node;
	node->key = key;

	//set the .next pointer of the new node to point to the current
	//first node of the list
	node->next = next;

	return node;
}

//function for linked list implementation from a given set of keys
Node* constructList(vector<int> const& keys)
{
	Node* head = nullptr, * node = nullptr;

	//start from the end of the array
	for (int i = keys.size() - 1; i >= 0; i--)
	{
		node = newNode(keys[i], node);
		head = node;
	}

	return head;
}

//helper function to print a linked list 
void printList(Node* head)
{
	Node* ptr = head;

	while (ptr)
	{
		cout << ptr->key << " -> ";
		ptr = ptr->next;
	}

	cout << "nullptr";
}

int main()
{
	// input keys (in reverse order)
	vector<int> keys = { 4, 3, 2, 1 };

	// construct linked list
	Node* head = constructList(keys);

	// print linked list
	printList(head);

	return 0;
}

/*

*/