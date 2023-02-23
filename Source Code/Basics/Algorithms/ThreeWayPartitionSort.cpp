#include "Header.h";

using namespace std;

/*

Given an array containing only 0’s, 1’s, and 2’s, sort it in linear time and using constant space.

For example,

Input:  { 0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0 }

Output: { 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2 }

A simple solution would be to perform a counting sort. We count the total number of 0’s, 1’s, and 2’s and then put them in the array in their correct order. The time complexity of this solution is O(n), where n is the size of the input. However, this requires two traversals of the array.


We can rearrange the array in a single traversal using an alternative linear-time partition routine that separates the values into three groups:

The values less than the pivot,
The values equal to the pivot, and
The values greater than the pivot.
To solve this particular problem, consider 1 as a pivot. The following linear-time partition routine in C++,
*/


// Utility function to swap elements `arr[i]` and `arr[j]` in an array
void swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

// Linear time partition routine to sort an array containing 0, 1, and 2.

void threeWayPartition(int arr[], int end)
{
	int start = 0, mid = 0;
	int pivot = 1;

	while (mid <= end)
	{
		if (arr[mid] < pivot) //current element is 0
		{
			swap(arr, start, mid);
			++start, ++mid;
		}
		else if (arr[mid] > pivot) //current element is 2
		{
			swap(arr, mid, end);
			--end;
		}
		else //current element is 1
		{
			++mid;
		}
	}
}


int main()
{

	int arr[] = { 0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0 };
	int n = sizeof(arr) / sizeof(arr[0]);
	threeWayPartition(arr, n - 1);

	for (int i = 0; i < n; i++)
	{
		printf("%d", arr[i]);
	}

	return 0;
}

