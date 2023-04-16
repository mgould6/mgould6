#include "Header.h";

using namespace std;

/*
Linked List Implementation With InsertAtFront

The standard function adds a single node to the head end of any list. This function is called push() since we are adding the link to the head end, making a list look a bit like a stack. Alternately, it could be called InsertAtFront().


*/

struct Node
{
    int data;
    struct Node* next;
};

/*
    push(): Takes a list and a data value, creates a new link with the given
    data and pushes it onto the list's front. Its head pointer does not pass
    in the list. Instead, the list is passed in as a "reference" pointer
    to the head pointer — this allows us to modify the caller's memory.

    The parameter has the word "ref" in it as a reminder that this is a "reference".
    (struct Node**) pointer to the head pointer instead of an ordinary
    (struct Node*) copy of the head pointer.
*/

void push(struct Node** headRef, int data)
{
    //allocate a new node in a heap and set its data 
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;

    //set the .next pointer of the new node to the point to the current 
    //first node of the list
    newNode->next = *headRef;   // '*' to dereference back to real head

    //change the head pointer to point to the new node, so it is
    //now the first node in the list
    *headRef = newNode;
}

//function for linked list implementation from a given set of keys
struct Node* constructList(int keys[], int n)
{
    struct Node* head = NULL;
    //start from the end of the array
    for (int i = n - 1; i >= 0; i--)
    {
        push(&head, keys[i]);
    }

    return head;
}


//helper function to print given linked list
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

int main()
{
    //input keys
    int keys[] = { 1, 2, 3, 4 };
    int n = sizeof(keys) / sizeof(keys[0]);

    //head points to first node also called head node of linked list
    struct Node* head = constructList(keys, n);

    //print linked list 
    printList(head);

    return 0;
}

/*

*/