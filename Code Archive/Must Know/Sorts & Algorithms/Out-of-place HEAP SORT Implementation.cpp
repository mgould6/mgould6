#include "Header.h";

using namespace std;

/*
Out-of-place Heapsort Implementation
*/

//a class to store min heap
class PriorityQueue
{
	//array to store heap elements 
	int* A;

	//stores current size of the heap
	unsigned size;

	//return left child of A[i]
	int LEFT(int i)
	{
		return (2 * i + 1);
	}

	//return the right child
	int RIGHT(int i)
	{
		return (2 * i + 2);
	}

	//recursive heapify down algorithm
	//the node at index i and its two direct children
	//violate the heap property
	void heapify(int i)
	{
		//get left and right child of node at i
		int left = LEFT(i);
		int right = RIGHT(i);

		int smallest = i;

		//compare A[i] with its left and right child 
		//and find the smallest value
		if (left < size && A[left] < A[i])
		{
			smallest = left;
		}
		if (right < size && A[right] < A[smallest])
		{
			smallest = right;
		}

		//swap with a hild having lesser value and 
		//call heapify down on the child
		if (smallest != i)
		{
			swap(A[i], A[smallest]);
			heapify(smallest);
		}
	}

public:

	//constructor / build heap
	PriorityQueue(vector<int>& arr, int n)
	{
		//allocate memory to the heap and initialize it by the given array
		A = new int[n];
		for (int i = 0; i < n; i++)
		{
			A[i] = arr[i];
		}

		// set heap capacity equal to the array size
		size = n;

		//call heapify starting from the last internal node all
		//way up to the root node
		int i = (n - 2) / 2;
		while (i >= 0)
		{
			heapify(i--);
		}
	}

	//destructor 
	~PriorityQueue()
	{
		//free the memory used by heap nodes
		delete[] A;
	}

	//function to check if the heap is empty or not 
	int empty()
	{
		return size == 0;
	}

	//function to remove an element with the highest priority (present at the root)
	int pop()
	{
		// if the heap has no elements 
		if (size <= 0)
		{
			return -1;
		}

		int top = A[0];

		//replace the root of the heap with the last element
		//of the array
		A[0] = A[size - 1];

		//decrease heap size by 1
		size--;

		//call heapify down on the root node
		heapify(0);

		return top;
	}
};

//function to perform heapsort on array A of size n
void heapsort(vector<int>& A, int n)
{
	//build a priority queue and initialize it by the given array
	PriorityQueue pq(A, n);

	int i = 0;

	//repeatedly pop form the heap till it becomes empty 
	while (!pq.empty())
	{
		A[i++] = pq.pop();
	}
}

//heapsort algorithm implementation in c++

int main()
{
	vector<int> A = { 6, 4, 7, 1, 9, -2 };
	int n = A.size();

	//perform heapsort on the array
	heapsort(A, n);

	//print the sorted array
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << " ";
	}

	return 0;
}

/*

*/