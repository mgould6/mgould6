#include "Header.h";

using namespace std;

/*
C - Linked List Insertion at Tail with Local References
A tricky way to unifying all the node cases without using a dummy node is to use a local “reference pointer”, which always points to the last pointer in the list instead of the last node. All additions to the list are made by following the reference pointer. The reference pointer starts by pointing to the head pointer. Later, it points to the .next field inside the last node in the list.


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

/*
	Takes a list and a data value, creates a new link with the given data and
	pushes it onto the list's front. The head node is passed by reference.
*/
void push(struct Node** head, int data)
{
	//allocate a new node in a heap and set its data
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;

	//set the next pointer of the new node to point to the current first node in the list
	newNode->next = *head;

	//change the head pointer to point to the new node so it is now the first node in the list 
	*head = newNode;
}

//function to implement a linked list from a given set of keys
//using local references 
struct Node* constructList(int keys[], int n)
{
	struct Node* head = NULL;

	//lastPtrRef points to the last pointer (next field inside the last node in the list)
	//initially it points to the head pointer itself
	struct Node** lastPtrRef = &head;

	for (int i = 0; i < n; i++)
	{
		//adds a new node at the last pointer the new node becomes the last node in the list
		push(lastPtrRef, keys[i]);

		//advance lastPtrRef to now point to the next field insied
		lastPtrRef = &((*lastPtrRef)->next);
	}

	// head == {key[0], key[1], key[2], key[3]};
	return head;
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