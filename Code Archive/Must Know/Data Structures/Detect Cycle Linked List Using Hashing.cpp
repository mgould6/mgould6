#include "Header.h";

using namespace std;

/*
Detect cycle in a linked list (Floyd’s Cycle Detection Algorithm)
For example, the following linked list has a cycle in it: 1 -> 2 -> 3 -> 4

Using Hashing
A simple solution is to use hashing. The idea is to traverse the given list and insert each encountered node into a set. If the current node already presents in the set (i.e., it is seen before), that means a cycle is present in the list.

Following is the C++


*/

//linked list node
struct Node
{
	int data;
	Node* next;
};

//helper function to create a new node with the given data and pushes it onto the lists front 

void push(struct Node*& headRef, int data)
{
	//create a new linked list node from the heap
	Node* newNode = new Node;

	newNode->data = data;
	newNode->next = headRef;
	headRef = newNode;
}

//function to detect a cycle in a linked list using hashing
bool detectCycle(Node* head)
{
	Node* curr = head;
	unordered_set<Node*> set;

	while (curr)
	{
		//return false if we already have seen this node before
		if (set.find(curr) != set.end())
		{
			return true;
		}

		//insert the current node into the set
		set.insert(curr);

		//move to the next node
		curr = curr->next;
	}

	//we reach here if the list does not contain any cycle
	return false;
}


int main()
{
	// input keys
	int keys[] = { 1, 2, 3, 4, 5 };
	int n = sizeof(keys) / sizeof(keys[0]);

	Node* head = nullptr;
	for (int i = n - 1; i >= 0; i--) {
		push(head, keys[i]);
	}

	// insert cycle
	head->next->next->next->next->next = head->next->next;

	if (detectCycle(head)) {
		cout << "Cycle Found";
	}
	else {
		cout << "No Cycle Found";
	}

	return 0;
}

/*
Detect cycle in a linked list (Floyd’s Cycle Detection Algorithm)

*/