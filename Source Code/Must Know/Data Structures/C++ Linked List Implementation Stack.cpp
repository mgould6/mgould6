#include "Header.h";

using namespace std;

/*
C++ Linked List Implementation Stack
*/

class Node
{
public:
    int key;
    Node* next;
};

/*
    push() in C++ — we just add `&` to the right-hand side of the head
    parameter type, and the compiler makes that parameter work by reference.
    So, this code changes the caller's memory, but no extra uses of `*` are
    necessary — we access "head" directly, and the compiler makes that
    change reference back to the caller.
*/

void push(Node*& headRef, int key)
{
    Node* node = new Node;
    node->key = key;

    //set the next pointer of the new node to point to the current
    //first node of the list 

    //no extra use of * necessary on the head the compiler 
    //takes care of it behind the scense
    node->next = headRef;

    headRef = node;
}

//function for linked list implementation from a given set of keys 
Node* constructList(vector<int> const& keys)
{
    Node* head = nullptr;

    //start from the end of the array
    for (int i = keys.size() - 1; i >= 0; i--)
    {
        //note that no extra use & necessary the compiler takes 
        //care of it here too. these calls are changing the head 

        push(head, keys[i]);
    }

    return head;
}

//helper function to print a linked list
void printList(Node* head)
{
    Node* ptr = head;
    while (ptr)
    {
        cout << ptr->key << " -> ";
        ptr = ptr->next;
    }

    cout << "nullptr";
}

int main()
{

    // input keys (in reverse order)
    vector<int> keys = { 4, 3, 2, 1 };

    // construct linked list
    Node* head = constructList(keys);

    // print linked list
    printList(head);

    return 0;
}

/*

*/