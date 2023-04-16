#include "Header.h";

using namespace std;

/*
Insertion Sort Algorithm – Iterative & Recursive | C

Insertion Sort Overview
Insertion sort is a stable, in-place sorting algorithm that builds the final sorted array one item at a time. It is not the very best in terms of performance but more efficient traditionally than most other simple O(n2) algorithms such as selection sort or bubble sort. Insertion sort is also used in Hybrid sort, which combines different sorting algorithms to improve performance.

It is also a well known online algorithm since it can sort a list as it receives it. In all other algorithms, we need all elements to be provided to the sorting algorithm before applying it. But an insertion sort allows us to start with a partial set of elements, sorts it (called a partially sorted set). If we want, we can insert more elements (these are the new set of elements that were not in memory when the sorting started) and sorts them. In the real world, data to be sorted is usually not static, rather dynamic. If even one additional element is inserted during the sorting process, other algorithms don’t respond easily. But only insertion sort algorithm is not interrupted and can respond well with the additional element.

How Insertion Sort works?
The idea is to divide the array into two subsets – sorted subset and unsorted subset. Initially, a sorted subset consists of only one first element at index 0. Then for each iteration, insertion sort removes the next element from the unsorted subset, finds the location it belongs within the sorted subset and inserts it there. It repeats until no input elements remain. The following example explains it all:

i = 1    [ 3  8  5  4  1  9  -2 ]
i = 2    [ 3  8  5  4  1  9  -2 ]
i = 3    [ 3  5  8  4  1  9  -2 ]
i = 4    [ 3  4  5  8  1  9  -2 ]
i = 5    [ 1  3  4  5  8  9  -2 ]
i = 6    [ 1  3  4  5  8  9  -2 ]
		 [ -2  1  3  4  5  8  9 ]


Insertion Sort Performance
The worst-case time complexity of insertion sort is O(n2), where n is the size of the input. The worst case happens when the array is reverse sorted. The best-case time complexity of insertion sort is O(n). The best case happens when the array is already sorted.

The auxiliary space used by the iterative version is O(1) and O(n) by the recursive version for the call stack.


*/





void insertionSort(int arr[], int i, int n)
{
	int value = arr[i];
	int j = i;
	while (j > 0 && arr[j - 1] > value)
	{
		arr[j] = arr[j - 1];
		j--;
	}
	arr[j] = value;
	if (i + 1 <= n) {
		insertionSort(arr, i + 1, n);
	}
}

//function to print 'n' elements of array 'arr'
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main(void)
{

	int arr[] = { 3,  8,  5,  4,  1,  9, -2 };

	int n = sizeof(arr) / sizeof(arr[0]);



	//start the recursive sort from the second element, 0 is already sorted
	insertionSort(arr, 1, n - 1);
	printArray(arr, n);


	return 0;
}

//
//void insertionSort(int arr[], int n)
//{
//	//start from the second element, the element at index 0 is already sorted
//
//	for (int i = 1; i < n; i++)
//	{
//		int value = arr[i];
//		int j = i;
//
//		//find index 'j' within the sorted subset 'arr[0... i-1]'
//		//where element 'arr[i]' belongs
//
//		while (j > 0 && arr[j - 1] > value)
//		{
//			arr[j] = arr[j - 1];
//			j--;
//		}
//		//note that the subarray 'arr[j...i-1]' is shifted to the right by one position, i.e 'arr[j+1...]'
//
//		arr[j] = value;
//	}
//}