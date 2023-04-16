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
void reverse(struct Node* curr, struct Node* prev, struct Node** head)
{
	//base case: end of list reached
	if (curr == NULL)
	{
		//fix head pointer 
		*head = prev;
		return;
	}

	//recur for the next node and pass the current node as a previous node
	reverse(curr->next, curr, head);

	//fix current node
	curr->next = prev;
}

//reverse a given linked list. the function takes a pointer
//reference to the head pointer
void Reverse(struct Node** head)
{
	reverse(*head, NULL, head);
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

	Reverse(&head);

	printList(head);

	return 0;
}

/*
The time complexity of the above recursive solutions is O(n), where n is the length of the linked list. The solution is probably not appropriate for production code since it uses stack space proportionate to the lists’ lengths. Still, it provides good learning on how recursion works.


*/