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

//define the default capacity of the stack
#define SIZE 10

//a class to represent a stack
class Stack
{
	int* arr;
	int top;
	int capacity;

public:
	Stack(int size = SIZE); //constructor
	~Stack();				//destructor

	void push(int);
	int pop();
	int peek();

	int size();
	bool isEmpty();
	bool isFull();
};

//constructor to initialize the stack
Stack::Stack(int size)
{
	arr = new int[size];
	capacity = size;
	top = -1;
}

//destructor to free the stack
Stack::~Stack()
{
	delete[] arr;
}

//utility function to add an element x to the stack

void Stack::push(int x)
{
	if (isFull())
	{
		cout << "overflow\n program terminated\n";
		exit(EXIT_FAILURE);
	}
	cout << "inserting " << x << endl;
	arr[++top] = x;
}

int Stack::pop()
{
	//check for stack underflow
	if (isEmpty())
	{
		cout << "underflow\n program terminated\n";
		exit(EXIT_FAILURE);
	}

	cout << "removing " << peek() << endl;

	//decrease stack size by 1 and optionally return the popped element
	return arr[top--];
}

//utility function to return the top element of the stack
int Stack::peek()
{
	if (!isEmpty())
	{
		return arr[top];
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

//utility function to return the size of the stack
int Stack::size()
{
	return top + 1;
}


//utility function to check if the stack is empty or not
bool Stack::isEmpty()
{
	return top == -1;
}

//utility function to check if the stack is full or not
bool Stack::isFull()
{
	return top == capacity - 1;
}

int main()
{
	Stack pt(3);

	pt.push(1);
	pt.push(2);

	pt.pop();
	pt.pop();

	pt.push(3);

	cout << "the top element is " << pt.peek() << endl;
	cout << "the stack size is " << pt.size() << endl;

	pt.pop();

	if (pt.isEmpty())
	{
		cout << "the stack is empty\n";
	}
	else
	{
		cout << "the stack is not empty\n";
	}


	return 0;
}

