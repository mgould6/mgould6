#include "Header.h";

using namespace std;

/*
Merge Sort Algorithm – C++

Merge sort Overview
Merge sort is an efficient sorting algorithm that produces a stable sort, which means that if two elements have the same value, they hold the same relative position in the sorted sequence as they did in the input. In other words, the relative order of elements with equal values is preserved in the sorted sequence. Merge sort is a comparison sort, which means that it can sort any input for which a less-than relation is defined.

How Merge sort works?
Merge sort is a Divide and Conquer algorithm. Like all divide-and-conquer algorithms, merge sort divides a large array into two smaller subarrays and then recursively sort the subarrays. Basically, two steps are involved in the whole process:

Divide the unsorted array into n subarrays, each of size 1 (an array of size 1 is considered sorted).
Repeatedly merge subarrays to produce new sorted subarrays until only 1 subarray is left, which would be our sorted array.
The following diagram represents a top-down view of the recursive merge sort algorithm used to sort an 7-element integer array:

Merge Sort Algorithm - https://www.techiedelight.com/wp-content/uploads/Merge-Sort-Steps.png

Merge Sort Performance
The worst-case time complexity of merge sort is O(n.log(n)), where n is the size of the input. The recurrence relation is:

T(n) = 2T(n/2) + cn = O(n.log(n))

The recurrence basically summarizes the merge sort algorithm – Sort two lists of half the original list’s size and add the n steps taken to merge the resulting two lists.

The auxiliary space required by the merge sort algorithm is O(n) for the call stack.


*/
#define N 15



//merge two sorted subarrays

void Merge(int arr[], int aux[], int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;

	//while there are elements in the left and the right
	while (i <= mid && j <= high)
	{
		if (arr[i] < arr[j])
		{
			aux[k++] = arr[i++];
		}
		else
		{
			aux[k++] = arr[j++];
		}
	}

	//copy remaining elements

	while (i <= mid)
	{
		aux[k++] = arr[i++];
	}

	//no need to copy the second half since the remaining items
	//are already in their correct position in the aux array

	//copy back to the original array to reflect sorted order
	for (int i = low; i <= high; i++)
	{
		arr[i] = aux[i];
	}

}

//sort array 'arr[low...high]'using auxiliary array 'aux'

void mergeSort(int arr[], int aux[], int low, int high)
{
	//base case
	if (high <= low) //if runsize <= 1
	{
		return;
	}


	//find midpoint
	int mid = (low + ((high - low) >> 1));

	//recursively split runs into two halves until run size <= 1,
	//then merge them and return up the call chain

	mergeSort(arr, aux, low, mid);				//split/merge left half
	mergeSort(arr, aux, mid + 1, high);			//split/merge right half

	Merge(arr, aux, low, mid, high);
}


//function to check if arr is sorted in ascending order or not
int isSorted(int arr[])
{
	int prev = arr[0];

	for (int i = 1; i < N; i++)
	{
		if (prev > arr[i])
		{
			printf("Merge Sort Failed");
		}
		prev = arr[i];
	}

	return 1;
}

int main(void)
{
	int arr[N], aux[N];
	srand(time(NULL));

	//generate random input of integers

	for (int i = 0; i < N; i++)
	{
		aux[i] = arr[i] = (rand() % 100) - 50;
	}

	//sort array 'arr' using auxiliary array 'aux'

	mergeSort(arr, aux, 0, N - 1);

	if (isSorted(arr))
	{
		for (int i = 0; i < N; i++)
		{
			printf("%d ", arr[i]);
		}
	}

	return 0;
}

