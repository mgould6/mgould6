#include "Header.h";

using namespace std;

/*
Stack Implementation in C++ LIFO

Following is the stack implementation in C++ which covers the following operations:

push: Inserts a new element at the top of the stack, above its current top element.
pop: Removes the top element on the stack, thereby decrementing its size by one.
isEmpty: Returns true if the stack is empty, i.e., its size is zero; otherwise, it returns false.
isFull: Returns true if the stack is full, i.e., its size has reached maximum allocated capacity; otherwise, it returns false.
peek: Returns the top element present in the stack without modifying the stack.
size: Returns the count of elements present in the stack.

Stack Implementation using an array:


*/


int main()
{
    list<string> s;

    s.push_front("A");        // Insert `A` into the stack
    s.push_front("B");        // Insert `B` into the stack
    s.push_front("C");        // Insert `C` into the stack
    s.push_front("D");        // Insert `D` into the stack

    // returns the total number of elements present in the stack
    cout << "The stack size is " << s.size() << endl;

    // prints the top of the stack (`D`)
    cout << "The top element is " << s.front() << endl;

    s.pop_front();          // removing the top element (`D`)
    s.pop_front();          // removing the next top (`C`)

    cout << "The stack size is " << s.size() << endl;

    // check if the stack is empty
    if (s.empty()) {
        cout << "The stack is empty\n";
    }
    else {
        cout << "The stack is not empty\n";
    }

    return 0;

}

