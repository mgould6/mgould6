#include <Header.h>

using namespace std;

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode *next;

        SinglyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
        }
};

class SinglyLinkedList {
    public:
        SinglyLinkedListNode *head;
        SinglyLinkedListNode *tail;

        SinglyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
            }

            this->tail = node;
        }
};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    SinglyLinkedList* list = new SinglyLinkedList(); 
    
    //while parameters are not null, i
    //if head one is greater than head 2 
        //insert head 2 data into temp list and move head2 to the next position
    //else insert head 1 data into temp list and move head1 to the next position
    
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data > head2->data) {
            list->insert_node(head2->data);
            
            
            head2 = head2->next;
        } else {
            list->insert_node(head1->data);
            head1 = head1->next;
        }
    }
    
    //runs when head1 is empty
    while (head2 != nullptr) {
        list->insert_node(head2->data);
        head2 = head2->next;        
    }
    //runs when head 2 is empty
    while (head1 != nullptr) {
        list->insert_node(head1->data);
        head1 = head1->next;        
    }
    
    //return list starting at head position
    return (list->head);

}

int main()