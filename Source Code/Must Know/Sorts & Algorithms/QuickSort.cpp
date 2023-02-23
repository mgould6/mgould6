#include "Header.h";

using namespace std;

/*
Quicksort Algorithm – C++

Quicksort Overview
Quicksort is an efficient in-place sorting algorithm, which usually performs about two to three times faster than merge sort and heapsort when implemented well. Quicksort is a comparison sort, meaning that it can sort items of any type for which a less-than relation is defined. In efficient implementations, it is usually not a stable sort.

Quicksort, on average, makes O(n.log(n)) comparisons to sort n items. In the worst-case, it makes O(n2) comparisons, though this behavior is very rare.

How Quicksort Works?
Quicksort is a Divide and Conquer algorithm. Like all divide-and-conquer algorithms, it first divides a large array into two smaller subarrays and then recursively sort the subarrays. Basically, three steps are involved in the whole process:

Pivot selection: Pick an element, called a pivot, from the array (usually the leftmost or the rightmost element of the partition).
Partitioning: Reorder the array such that all elements with values less than the pivot come before the pivot. In contrast, all elements with values greater than the pivot come after it. The equal values can go either way. After this partitioning, the pivot is in its final position.
Recur: Recursively apply the above steps to the subarray of elements with smaller values than the pivot and separately to the subarray of elements with greater values than the pivot.
The base case of the recursion is arrays of size 1, which never need to be sorted. The following diagram shows how we choose the leftmost element as pivot at each step of the Quicksort algorithm, partition the array across the pivot, and recur on two subarrays we get after the partition process:


Please note that the pivot selection and partitioning steps can be made in several ways, and the choice of specific implementation schemes significantly affects the algorithm’s performance. We will discuss all that in detail later, but let’s now get to the coding part.



Quicksort Algorithm - https://www.techiedelight.com/wp-content/uploads/Quicksort.png



Quicksort Performance
The worst-case time complexity of Quicksort is O(n2), where n is the size of the input. The worst case happens when the pivot happens to be the smallest or largest element in the list or when all the array elements are equal. This will result in the most unbalanced partition as the pivot divides the array into two subarrays of sizes 0 and n-1. If this repeatedly happens in every partition (say, we have sorted array), then each recursive call processes a list of size one less than the previous list, resulting in O(n2) time.

T(n) = T(n-1) + cn = O(n²)

(Note – partition takes O(n) time that accounts for cn)


The best-case time complexity of Quicksort is O(n.log(n)). The best case happens when the pivot divides the array into two nearly equal pieces. Now each recursive call processes a list of half the size.

T(n) = 2 T(n/2) + cn = O(n.log(n))


The auxiliary space required by the Quicksort algorithm is O(n) for the call stack.

Following is the C++


*/

int partition(int arr[], int start, int end)
{
	//pick the right most element as a pivot from the array
	int pivot = arr[end];

	//elements less than will be pushed lest of pIndex
	//elements greater than will be pushed right of pIndex
	//equal elements can go either way

	int pIndex = start;

	//each time we find an element less than or equal to the pivot 
	//pIndex is incremented and that element would be placed before the pivot

	for (int i = start; i < end; i++)
	{
		if (arr[i] <= pivot)
		{
			swap(arr[i], arr[pIndex]);
			pIndex++;
		}
	}

	//swap index with pivot
	swap(arr[pIndex], arr[end]);

	//return pIndex
	return pIndex;
}

void quicksort(int arr[], int start, int end)
{
	//base condition
	if (start >= end)
	{
		return;
	}

	//rearrange elements across pivot

	int pivot = partition(arr, start, end);

	//recur on subarrays
	quicksort(arr, start, pivot - 1);
	quicksort(arr, pivot + 1, end);
}

int main()
{
	int arr[] = { 9, -3, 5, 2, 6, 8, -6, 1, 3 };
	int n = sizeof(arr) / sizeof(arr[n]);

	quicksort(arr, 0, n - 1);

	//print the sorted array

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}

