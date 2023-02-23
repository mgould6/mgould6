#include "Header.h";

using namespace std;

/*
Queue Implementation in C++ using an array

queue is a linear data structure that serves as a container of objects that are inserted and removed according to the FIFO (First–In, First–Out) principle.


Queue has three main operations: enqueue, dequeue, and peek. We have already covered these operations and C implementation of queue data structure using an array and linked list. In this post, we will cover queue implementation in C++ using class and STL.


The following queue implementation in C++ covers the following operations:

Enqueue: Inserts a new element at the rear of the queue.
Dequeue: Removes the front element of the queue and returns it.
Peek: Returns the front element present in the queue without dequeuing it.
IsEmpty: Checks if the queue is empty.
IsFull: Checks if the queue is full.
Size: Returns the total number of elements present in the queue.


The time complexity of all the above queue operations is O(1).


*/

#define SIZE 1000

//a class to store a queue
class Queue
{
	int* arr;		//array to store queue elements
	int capacity;	//maximum capacity of the queue
	int front;		//front points to the front element in the queue
	int rear;		//rear points to the last element in the queue
	int count;		//current size of the queue

public:

	Queue(int size = SIZE);		//constructor
	~Queue();

	int dequeue();
	void enqueue(int x);
	int peek();
	int size();
	bool isEmpty();
	bool isFull();
};

Queue::Queue(int size)
{
	arr = new int[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
}

//Destructor to free memory allocated to the queue
Queue::~Queue()
{
	delete[] arr;
}

//utility function to dequeue the front element
int Queue::dequeue()
{
	//check for queue underflow
	if (isEmpty())
	{
		cout << "underflow\n program terminated\n";
		exit(EXIT_FAILURE);
	}

	int x = arr[front];
	cout << "Removing " << x << endl;

	front = (front + 1) % capacity;
	count--;

	return x;
}

//utility function to add an item to the queue
void Queue::enqueue(int item)
{
	//check for queue overflow 
	if (isFull())
	{
		cout << "overflow\n program terminated\n";
		exit(EXIT_FAILURE);
	}

	cout << "inserting " << item << endl;
	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
}

//utility function to return the front element of the queue
int Queue::peek()
{
	if (isEmpty())
	{
		cout << "underflow\n program terminated\n";
		exit(EXIT_FAILURE);
	}
	return arr[front];
}

//utility function to return the size of the queue
int Queue::size()
{
	return count;
}

//utility function to check if the queue is empty
bool Queue::isEmpty()
{
	return (size() == 0);
}

//utility function to check if the queue is full or not
bool Queue::isFull()
{
	return(size() == capacity);
}


int main()
{
	// create a queue of capacity 5
	Queue q(5);

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);

	cout << "The front element is " << q.peek() << endl;
	q.dequeue();

	q.enqueue(4);

	cout << "The queue size is " << q.size() << endl;

	q.dequeue();
	q.dequeue();
	q.dequeue();

	if (q.isEmpty()) {
		cout << "The queue is empty\n";
	}
	else {
		cout << "The queue is not empty\n";
	}

	return 0;
}

/*

*/