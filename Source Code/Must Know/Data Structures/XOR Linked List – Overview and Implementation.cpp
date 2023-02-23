#include "Header.h";

using namespace std;

/*
XOR Linked List – Overview and Implementation in C/C++

This post will discuss the XOR linked list, which is used to reduce memory requirements of doubly-linked lists using a bitwise XOR operator.

We know that each node of a doubly-linked list requires two pointer fields to store its previous and next node’s addresses. On the other hand, each node of the XOR linked list requires only a single pointer field, which doesn’t store the actual memory addresses but stores the bitwise XOR of address for its previous and next node.

To illustrate, let’s consider the following doubly linked list:


Doubly Linked List


Here the link field for an equivalent XOR linked list stores the following values:

link(A) = NULL ^ addr(B)        // bitwise XOR of NULL with address of node B
link(B) = addr(A) ^ addr(C)     // bitwise XOR between the address of node A and C
link(C) = addr(B) ^ addr(D)     // bitwise XOR between the address of node B and D
link(D) = addr(C) ^ NULL        // bitwise XOR of the address of node A with NULL
How this helps?

We know that XOR has the following properties:

X^X = 0
X^0 = X
X^Y = Y^X
We can easily traverse the XOR linked list in either direction using the above properties:

1. Traversing the list from left to right:

Since we are traversing the list from left to right, say we store the previous node’s address in some variable. As the previous node information is available, we can get the next node’s address by XORing the value in the link field with the previous node’s address.


For example, suppose we are at node C, we can get the address of node D, as shown below.

addr(B) ^ link(C)
= addr(B) ^ (addr(B) ^ addr(D))
= 0 ^ addr(D)
= addr(D)
The XOR operation cancels addr(B) appearing twice in the equation, and all we are left with is the addr(D). Similarly, to get the address of the first node A in the list, we can XOR the value in the link field with NULL.

NULL ^ link(A)
= NULL ^ (NULL ^ addr(B))
= 0 ^ addr(B)
= addr(B)
2. Traversing the list from right to left:

Following a similar logic, to get the address of the last node D in the list, XOR the D's link field value with NULL:

NULL ^ link(D)
= NULL ^ (addr(C) ^ NULL)
= 0 ^ addr(C)
= addr(C)
For any middle node, say node C, we can get the address of the previous node B as follows.

addr(D) ^ link(C)
= addr(D) ^ (addr(B) ^ addr(D))
= 0 ^ addr(B)
= addr(B)
Consider the following program, which constructs an XOR linked list and traverses it in a forward direction using bitwise XOR operator properties. To traverse the complete list, maintain three-pointers prev, curr, and next to store the current node address, the previous node address, and the next node address, respectively. Each iteration of the loop moves these pointers one position forward or backward depending upon which direction we are traversing the list.

The implementation can be seen below in C and C++:



Drawbacks of XOR linked list:

An XOR linked list is similar to a doubly-linked list but not completely equivalent to a doubly-linked list. There are several disadvantages of an XOR linked list over a doubly-linked list, which is discussed below:

A doubly-linked list is easy to code and maintain, but it is a little complex for an XOR linked list.
XOR linked list is not supported by several languages such as Java, where conversion between pointers and integers is undefined.
If a pointer to an existing middle node in an XOR linked list is provided, we can’t delete that node from the list or insert a new node before or after it. On the other hand, this can be done easily with a doubly-linked list.
*/

//data structure to store linked list node
struct Node
{
	int data;
	struct Node* link;
};

//helper function to return xor of x and y
struct Node* XOR(struct Node* x, struct Node* y)
{
	return (struct Node*)((uintptr_t)(x) ^ (uintptr_t)(y));
}

//helper function to traverse the list in a forward direction
void traverse(struct Node* head)
{
	struct Node* curr = head;
	struct Node* prev = NULL;
	struct Node* next;

	while (curr != NULL)
	{
		printf("%d -> ", curr->data);

		//next node would be xor of the address of the previous node
		//and current node link
		next = XOR(prev, curr->link);

		//update prev and curr pointers for the next iteration of the loop
		prev = curr;
		curr = next;
	}

	printf("NULL");
}

//helper function to insert a node at the beginning of the xor linked list
void push(struct Node** head, int data)
{
	//allocate a new list node and set its data
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;

	//the link field of the new node is xor of the current head and NULL
	//since a new node is being inserted at the beginning
	newNode->link = XOR(*head, NULL);

	//update link value of the current head node if the linked list is not empty
	if (*head)
	{
		//*(head)->link is XOR of NULL and address of the next node
		//to get the address of the next node XOR it with NULL
		(*head)->link = XOR(newNode, XOR((*head)->link, NULL));
	}

	//update the head pointer 
	*head = newNode;
}

int main()
{
	// input keys
	int keys[] = { 1, 2, 3, 4, 5 };
	int n = sizeof(keys) / sizeof(keys[0]);

	struct Node* head = NULL;
	for (int i = n - 1; i >= 0; i--) {
		push(&head, keys[i]);
	}

	traverse(head);

	return 0;
}

/*

*/