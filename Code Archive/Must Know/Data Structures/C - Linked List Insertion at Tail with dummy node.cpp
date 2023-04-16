#include "Header.h";

using namespace std;

/*
Linked List Insertion at tail with  tail pointer and dummy head pointer

USING DUMMY NODE

The idea is to use a temporary dummy node at the head of the list during computation. The trick is that every node appears to be added after the .next field of a node with the dummy. That way, the code for the first node is the same as for the other nodes. The tail pointer plays the same role as in the previous example. It now also handles the first node (avoids making dummy a permanent part of the list).

Following is the C,


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

	printf("NULL");
}

//takes a list and a data value, creates a new link with the given data
//and pushes it onto the lists front. the head node is passed by reference
void push(struct Node** head, int data)
{
	//allocate a new node in a heap and set its data
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;

	//set the next pointer of the new node to point to the current first node of the list
	newNode->next = *head;

	//change the head pointer to point to the new node, so it is now the first node in the list
	*head = newNode;
}

// Function to implement a linked list from a given set of keys
// using a dummy node
struct Node* constructList(int keys[], int n)
{
	struct Node dummy;              // dummy node is temporarily the first node
	struct Node* tail = &dummy;     // start the tail at the dummy

	// Build the list on `dummy->next` (aka `tail->next`)
	dummy.next = NULL;

	for (int i = 0; i < n; i++)
	{
		push(&(tail->next), keys[i]);
		tail = tail->next;
	}

	// The real result list is now in `dummy.next`
	// dummy.next == {key[0], key[1], key[2], key[3]};
	return (dummy.next);
}


int main()
{
	// input keys
	int keys[] = { 1, 2, 3, 4 };
	int n = sizeof(keys) / sizeof(keys[0]);

	// points to the head node of the linked list
	struct Node* head = constructList(keys, n);

	// print linked list
	printList(head);
	return 0;
}

/*

*/