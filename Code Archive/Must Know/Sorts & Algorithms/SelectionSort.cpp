#include "Header.h";

using namespace std;

/*
Selection Sort Algorithm – Iterative & Recursive | C

Selection Sort Overview
Selection sort is an unstable, in-place sorting algorithm known for its simplicity. It has performance advantages over more complicated algorithms in certain situations, particularly where the auxiliary memory is limited. It can be implemented as a stable sort and requires O(n2) time to sort n items, making it inefficient to use on large lists. Among simple average-case O(n2) algorithms, selection sort almost always outperforms bubble sort and generally performs worse than the insertion sort.

The biggest advantage of using a selection sort is that it does a maximum of n swaps (memory write). The insertion sort, on the other hand, does O(n2) number of writes. This can be critical if memory-write operation is significantly more expensive than memory-read operation, such as flash memory, where every write lessens the memory’s lifespan.

How Selection Sort works?
The idea is to divide the array into two subsets – sorted subset and unsorted subset. Initially, the sorted subset is empty, and the unsorted subset is the entire input list. The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element in the unsorted subset, swapping it with the leftmost unsorted element (putting it in sorted order), and moving the subset boundaries one element to the right. The following example explains it all:

			3  5  8  4  1  9 -2
i = 0      -2  5  8  4  1  9  3
i = 1      -2  1  8  4  5  9  3
i = 2      -2  1  3  4  5  9  8
i = 3      -2  1  3  4  5  9  8
i = 4      -2  1  3  4  5  9  8
i = 5      -2  1  3  4  5  8  9

Both the worst-case and best-case time complexity of selection sort is O(n2), where n is the input size, and it doesn’t require any extra space.

auxiliary space used by the recursive version is O(n) for the

*/



////function to perform the selection sort iteratively
//void selectionSort(int arr[], int n)
//{
//	//run n-1 times
//	for (int i = 0; i < n - 1; i++)
//	{
//		//find the min element in the unsorted array [i ... n - 1]
//		int min = i;
//
//		for (int j = i + 1; j < n; j++)
//		{
//			//if arr[j] is less then it is the new minimum
//			if (arr[j] < arr[min])
//			{
//				min = j; //update th eindex of the minimum element
//			}
//		}
//
//		//swap the minimum elememtn in the subarray
//		swap(arr, min, i);
//	}
//
//


//}
//utility function to swap values at two indices in an array
void swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

//recursive function to perform selection sort 
void selectionSort(int arr[], int i, int n)
{
	int min = i;
	for (int j = i + 1; j < n; j++)
	{
		if (arr[j] < arr[min])
		{
			min = j; //update the indices of the min element
		}
	}

	swap(arr, min, i);
}

//function to print 'n' elements of array 'arr' 
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{

	int arr[] = { 3, 5, 8, 4, 1, 9, -2 };
	int n = sizeof(arr) / sizeof(arr[0]);

	selectionSort(arr, 0, n);
	printArray(arr, n);


	return 0;
}

