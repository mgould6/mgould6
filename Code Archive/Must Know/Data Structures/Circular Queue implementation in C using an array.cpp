#include "Header.h";

using namespace std;

/*
Circular Queue implementation in C using an array

*/

//data structure to represent a queue
struct Queue
{
    int* items;     //array to store queue elements
    int maxSize;    //maximum capacity of the queue
    int front;      //front points to the front element in the queue (if any)
    int rear;       //rear points to the last element in the queue
    int size;       //current capacity of the queue
};


//utility function to initialize a queue
struct Queue* newQueue(int size)
{
    struct Queue* pt = NULL;
    pt = (struct Queue*)malloc(sizeof(struct Queue));

    pt->items = (int*)malloc(size * sizeof(int));
    pt->maxSize = size;
    pt->front = 0;
    pt->rear = -1;
    pt->size = 0;

    return pt;
}

//utility function to return the size of the queue
int size(struct Queue* pt)
{
    return pt->size;
}

//utility function to check if the queue is empty or not
int isEmpty(struct Queue* pt)
{
    return !size(pt);
}

int front(struct Queue* pt)
{
    if (isEmpty(pt))
    {
        printf("underflow\n program terminated\n");
        exit(EXIT_FAILURE);
    }

    return pt->items[pt->front];
}

void enqueue(struct Queue* pt, int x)
{
    if (size(pt) == pt->maxSize)
    {
        printf("overflow\n program terminated");
        exit(EXIT_FAILURE);
    }

    printf("inserting at %d\t", x);

    pt->rear = (pt->rear + 1) % pt->maxSize;    //circular queue
    pt->items[pt->rear] = x;
    pt->size++;

    printf("front = %d, rear = %d\n", pt->front, pt->rear);
}

//utility functionn to dequeue the front element 
void dequeue(struct Queue* pt)
{
    if (isEmpty(pt))    //front == rear 
    {
        printf("underflow\n program terminated\n");
        exit(EXIT_FAILURE);
    }

    printf("removing %d\t", front(pt));

    pt->front = (pt->front + 1) % pt->maxSize;  //circulare queue
    pt->size--;

    printf("front = %d, read = %d\n", pt->front, pt->rear);
}

int main()
{
    struct Queue* pt = newQueue(5);

    enqueue(pt, 1);
    enqueue(pt, 2);
    enqueue(pt, 3);
    enqueue(pt, 4);

    dequeue(pt);
    dequeue(pt);
    dequeue(pt);
    dequeue(pt);

    enqueue(pt, 5);
    enqueue(pt, 6);

    printf("size = %d\n", size(pt));

    if (isEmpty(pt)) {
        printf("The queue is empty");
    }
    else {
        printf("The queue is not empty");
    }

    return 0;
}

/*
A queue is a linear data structure that serves as a collection of elements, with three main operations.

Enqueue operation, which adds an element to the rear position in the queue.
Dequeue operation, which removes an element from the front position in the queue.
Peek or front operation, which returns the front element without dequeuing it or modifying the queue in any way.
The queue is also known as First–In, First–Out (FIFO) data structure considering the order in which elements come off a queue, i.e., the first element inserted into the queue is the first one to be removed. Following is a simple representation of a FIFO queue:


Data Queue


A queue may be implemented to have a bounded capacity. If the queue is full and does not contain enough space for enqueue operation, it will result in queue overflow. When trying to remove an element from an empty queue, queue underflow will happen.

Circular Queue Implementation using an array:

There are several efficient implementations of FIFO queues. A (bounded) queue can be easily implemented using an array using a five elements structure:

structure stack:
    item : array
    maxsize : integer
    front : integer
    rear : integer
    size : integer
Since fixed-length arrays have limited capacity, we need to convert the array into a closed circle. If n is the array’s size, then computing indices modulo n will turn the array into a circle. Now, front and rear can drift around endlessly in that circle, making it unnecessary to move items stored in the array.

Following is the C program that demonstrates it:


Output:

Inserting 1 front = 0, rear = 1
Inserting 2 front = 0, rear = 2
Inserting 3 front = 0, rear = 3
Inserting 4 front = 0, rear = 4
Removing  1 front = 1, rear = 4
Removing  2 front = 2, rear = 4
Removing  3 front = 3, rear = 4
Removing  4 front = 4, rear = 4
Inserting 5 front = 4, rear = 0
Inserting 6 front = 4, rear = 1
size = 2
The queue is not empty


The time complexity of enqueue(), dequeue(), front(), isEmpty() and size() operations is O(1).

It is possible to implement a queue that can grow or shrink as much as needed using a dynamic array. For example, using std::vector in C++ or ArrayList in Java.

Applications of a Queue:

Breadth–first search (BFS) algorithm.
Job Scheduling, to maintain a queue of processes in operating systems (FIFO order).
Queue of packets in data communication.
Data synchronization, to transfer data asynchronously between two processes.
A queue’s real-life applications would be waiting in a line at the ticket counter or call waiting for support or vehicles on a one-way lane, and many more…
*/