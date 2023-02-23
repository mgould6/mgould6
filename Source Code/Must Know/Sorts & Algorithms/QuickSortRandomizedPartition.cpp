#include "Header.h";

using namespace std;

/*
1. Better pivot selection
In Quicksort, one of the critical operations is choosing the pivot: the element around which the list is partitioned. Quicksort normally chooses the leftmost or the rightmost element of the partition as the pivot element. This selection will cause worst-case behavior on sorted or nearly sorted input. We can easily solve the problem by choosing either a random index for the pivot (called Randomized Quicksort) or choosing the median of the first, middle, and last element of the pivot partition (called median-of-3 selection).


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
int randomizedPartition(int arr[], int start, int end)
{
	//choose a random index between start and end
	int pivotIndex = rand() % (end - start + 1) + start;

	//swap the end element with the element present at the random index
	swap(arr[pivotIndex], arr[end]);

	//call partition procedure
	return partition(arr, start, end);
}

void quicksort(int arr[], int start, int end)
{
	//base condition
	if (start >= end)
	{
		return;
	}

	//rearrange elements across pivot

	int pivot = randomizedPartition(arr, start, end);

	//recur on subarray containing elements that are less than the pivot
	quicksort(arr, start, pivot - 1);
	//recur on subarray containing elements that are more than the pivot
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

