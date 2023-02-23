#include "Header.h";

using namespace std;

/*
Queue Implementation in C++  Using std::queue

queue is a linear data structure that serves as a container of objects that are inserted and removed according to the FIFO (First–In, First–Out) principle.

C++’s STL provides a std::queue template class which is restricted to only enqueue/dequeue operations. It also provides std::list which has push_back and pop_front operations with LIFO semantics. Java’s library contains Queue interface that specifies queue operations.
*/

// Queue implementation in C++ using `std::list`

int main()
{
	list<string> q;

	q.push_back("A");
	q.push_back("B");
	q.push_back("C");
	q.push_back("D");

	//returns the total number of elements present in the queue
	cout << "The queue size is " << q.size() << endl;

	//prints the front of the queue 
	cout << "the front element is " << q.front() << endl;

	//prints the rear of the queue
	cout << "the rear element is " << q.back() << endl;

	q.pop_front();		//removing the front element
	q.pop_front();		//removing the next front element

	cout << "the queue size is " << q.back() << endl;

	//check if the queue is empty
	if (q.empty())
	{
		cout << "the queue is empty\n";
	}
	else
	{
		cout << "the queue is not empty\n";
	}

	return 0;
}

/*

*/