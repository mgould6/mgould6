#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

/*
Max Heap Implementation in C++
We have introduced the heap data structure in the above post and discussed heapify-up, push, heapify-down, and pop operations. In this post, the implementation of the max-heap and min-heap data structure is provided. Their implementation is somewhat similar to std::priority_queue.

Max Heap implementation in C++:
*/

//data structure to store a max heap node
struct PriorityQueue
{
private:
	//vector to store heap elements
	vector<int> A;

	//return parent of A[i]
	//dont call this function if i is already a root node
	int PARENT(int i)
	{
		return(i - 1) / 2;
	}

	//return left child of A[i]
	int LEFT(int i)
	{
		return (2 * i + 1);
	}

	//return right hcild of A[i]
	int RIGHT(int i)
	{
		return(2 * 1 + 2);
	}

	//Recursive heapify down algorithm
	//the node at index i and its two direct children
	//violoate the heap property
	void heapify_down(int i)
	{
		//get left and right child of node at index i
		int left = LEFT(i);
		int right = RIGHT(i);
		int largest = i;
		//compare A[i] with its left and right child
		//and find the largetst value 
		if (left < size() && A[left] > A[i])
		{
			largest = left;
		}

		if (right < size() && A[right] > A[largest])
		{
			largest = right;
		}

		//swap with a child having greateer value and
		//call heapify donw on the child
		if (largest != i)
		{
			swap(A[i], A[largest]);
			heapify_down(largest);
		}
	}

	//recursive heapify up algorith
	void heapify_up(int i)
	{
		//check if the node at index i and its parent violate the heap property
		if (i && A[PARENT(i)] < A[i])
		{
			//swap the two if heap property is violated
			swap(A[i], A[PARENT(i)]);

			//call heapify up on the parent
			heapify_up(PARENT(i));
		}
	}

public:
	//return size of the heap
	unsigned int size()
	{
		return A.size();
	}

	//function to check if the heap is empty or not
	bool empty()
	{
		return size() == 0;
	}

	//insert key into the heap
	void push(int key)
	{
		//insert a new element at the end of the vector
		A.push_back(key);

		//get element index and call heapify up procedure
		int index = size() - 1;
		heapify_up(index);
	}

	//function to remove an element with the highest priority (present at the root)
	void pop()
	{
		try {
			//if the heap has no elements throw and exception
			if (size() == 0)
			{
				throw out_of_range("Vector<X>::at() :"
					"index is out of range(heap underflow)");
			}

			//replace the root of the heap with the last element
			//of the vector
			A[0] = A.back();
			A.pop_back();

			//call heapify down on the root node
			heapify_down(0);
		}
		//catch and print exception
		catch (const out_of_range& oor)
		{
			cout << endl << oor.what();
		}
	}

	//funciton to return an element with the highest priority (present at the root
	//funciton to return an element with the highest priority (present at the root
	int top()
	{
		try {
			//if the heap has no elements throw and exception
			if (size() == 0)
			{
				throw out_of_range("Vector<X>::at() : "
					"index is out of range(Heap underflow)");
			}
			//otherwise return the top (first) element
			return A.at(0); //or return A[0];
		}
		//catch and print the exception
		catch (const out_of_range& oor)
		{
			cout << endl << oor.what();
		}
	}
};

// Max Heap implementation in C++
int main()
{
	PriorityQueue pq;

	// Note: The element's value decides priority

	pq.push(3);
	pq.push(2);
	pq.push(15);

	cout << "Size is " << pq.size() << endl;

	cout << pq.top() << " ";
	pq.pop();

	cout << pq.top() << " ";
	pq.pop();

	pq.push(5);
	pq.push(4);
	pq.push(45);

	cout << endl << "Size is " << pq.size() << endl;

	cout << pq.top() << " ";
	pq.pop();

	cout << pq.top() << " ";
	pq.pop();

	cout << pq.top() << " ";
	pq.pop();

	cout << pq.top() << " ";
	pq.pop();

	cout << endl << boolalpha << pq.empty();

	pq.top();	// top operation on an empty heap
	pq.pop();	// pop operation on an empty heap

	return 0;
}
/*

*/