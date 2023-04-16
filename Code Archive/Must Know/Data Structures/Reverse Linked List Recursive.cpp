#include "Header.h";

using namespace std;

/*
Reverse linked list
We can also solve this problem by passing only reference to the head pointer to the function, as demonstrated below:
*/
// a linked list node
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

//helper function to insert a new node at the beginning of the linked list
void push(struct Node** head, int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = *head;

	*head = newNode;
}

//recusive function to reverse a linked list. it reversed the gived
//linked list by fixing the head pointer and then next pointeres
//of every node in reverse order
void reverse(struct Node** head)
{
	struct Node* first;
	struct Node* rest;

	//empty list base case
	if (*head == NULL)
	{
		return;
	}

	first = *head;		//suppose first 1,2,3
	rest = first->next;	//rest = 2, 3

	//empty rest base case

	if (rest == NULL)
	{
		return;
	}
	reverse(&rest);	//recursively reverse the smaller 2,3 case after rest = 3,2

	first->next->next = first;		//put the first item at the end of the list
	first->next = NULL;				//tricky step make a drawing
	*head = rest;					//fix the head pointer
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