#include "Header.h";

using namespace std;

/*
Linked List Implementation in C
Generic Method
The above-discussed methods will become a pain if the total number of nodes required is huge in the linked list. We can construct a linked list easily using iteration if the keys are given in the form of an array or any other data structure (using its iterator). Following is the implementation of the idea:


*/

//data structure to store linked list node
struct Node {
	int data;
	struct Node* next;
};

//helper function to return new linked list node from tehs heap
struct Node* newNode(int data, struct Node* nextNode)
{
	//allocate a new node in a heap and set its data
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;

	//set the .next pointer of the new node to point to the current 
	//first node of the list
	node->next = nextNode;

	return node;
}

//function for linked list implementation from a given set of keys
struct Node* constructList(int keys[], int n)
{
	struct Node* head = NULL, * node = NULL;

	//start from the end of the array
	for (int i = n - 1; i >= 0; i--)
	{
		node = newNode(keys[i], node);
		head = node;
	}

	return head;
}

//helper function to print a linked list
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

int main(void)
{
	int keys[] = { 1, 2, 3, 4 };
	int n = sizeof(keys) / sizeof(keys[0]);

	//head points to the first node (also known as a head node) of a linked lit
	struct Node* head = constructList(keys, n);

	//print linked list
	printList(head);

	return 0;
}

/*

*/