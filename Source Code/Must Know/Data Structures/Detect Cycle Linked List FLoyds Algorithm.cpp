#include "Header.h";

using namespace std;

/*
Detect cycle in a linked list (Floyd’s Cycle Detection Algorithm)
2. Floyd’s Cycle Detection Algorithm


Floyd’s cycle detection algorithm is a pointer algorithm that uses only two pointers, which move through the sequence at different speeds. The idea is to move the fast pointer twice as quickly as the slow pointer, and the distance between them increases by one at each step. If we both meet at some point, we have found a cycle in the list; otherwise, no cycle is present if the end of the list is reached. It is also called the “tortoise and the hare algorithm”.

The algorithm can be implemented as follows in C++

The time complexity of the  solution is O(n), where n is the total number of nodes in the linked list, and doesn’t require any extra space.


*/


//linked list node
struct Node
{
	int data;
	Node* next;
};

//helper function to create a new node with the given data and pushes it onto the lists front
void push(Node*& headRef, int data)
{
	//create a new linked list node
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = headRef;
	headRef = newNode;
}

//function to detect a cycle in a linked list using floydds cycle detection algorithm
bool detectCycle(Node* head)
{
	//take two pointers slow and fast
	Node* slow = head, * fast = head;

	while (fast && fast->next)
	{
		//move slow by one pointer
		slow = slow->next;

		//move fast by two pointers
		fast = fast->next->next;

		//if they meet at any node the linked list contains a cycle
		if (slow == fast)
		{
			return true;
		}
	}

	//we reach here if the slow and fast do not meet
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

*/