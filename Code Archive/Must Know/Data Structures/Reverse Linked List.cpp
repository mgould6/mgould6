#include "Header.h";

using namespace std;

/*
Reverse a linked List – Iterative Solution | C


For example,

Input:  1 —> 2 —> 3 —> 4 —> 5 —> 6 —> null

Output: 6 —> 5 —> 4 —> 3 —> 2 —> 1 —> null
Practice This Problem

The idea is to use three-pointers: next, current, previous and move them down the list. Here, current is the main pointer running down the list, next leads it, and previous trails it. For each step, reverse the current pointer and then advance all three to get the next node.

This previous-current-next strategy can be implemented as follows in C,

The time complexity of the solution is O(n), where n is the total number of nodes in the linked list, and doesn’t require any extra space.
*/

struct Node
{
	int data;
	struct Node* next;
};

//helper function to print a given linked list
void printList(struct Node* head)
{
	struct Node* ptr = head;
	while (ptr)
	{
		printf("%d -> ", ptr->data);
		ptr = ptr->next;
	}

	printf("NULL\n");
}

//helper function to insert a new node at the beginning of the linked list 
void push(struct Node** head, int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}


//reverses a given linked list by changing its next pointers 
//and its head pointer. takes a pointer reference to the head pointer
void reverse(struct Node** head)
{
	struct Node* previous = NULL; // the previous pointer
	struct Node* current = *head; //the main pointer 

	//traverse the list
	while (current != NULL)
	{
		//tricky note the next node
		struct Node* next = current->next;

		current->next = previous; //fix the current node

		//advance the two pointers 
		previous = current;
		current = next;
	}

	*head = previous;
}

int main()
{
	// input keys
	int keys[] = { 1, 2, 3, 4, 5, 6 };
	int n = sizeof(keys) / sizeof(keys[0]);

	struct Node* head = NULL;
	for (int i = n - 1; i >= 0; i--) {
		push(&head, keys[i]);
	}

	reverse(&head);

	printList(head);


	return 0;
}

/*

*/