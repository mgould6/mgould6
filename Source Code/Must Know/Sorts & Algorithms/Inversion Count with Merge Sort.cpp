#include "Header.h";

using namespace std;

/*
Inversion count of an array

Using Merge Sort
This is a classic problem that can be solved by merge sort algorithm. Basically, for each array element, count all elements more than it to its left and add the count to the output. This whole magic happens inside the merge function of merge sort.

Let’s consider two subarrays involved in the merge process:

Inversion Count – Step 1
Inversion Count – Step 2
Inversion Count – Step 3
Inversion Count – Step 4
Inversion Count – Step 5
Inversion Count – Step 6


The implementation can be seen below in C
The time complexity of the above solution is O(n.log(n)) (same as that of merge sort algorithm), and the auxiliary space used by the program is O(n).



*/

int Merge(int arr[], int aux[], int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;
	int inversionCount = 0;

	//while there are elements in the left and right runs
	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
		{
			aux[k++] = arr[i++];
		}
		else
		{
			aux[k++] = arr[j++];
			inversionCount += (mid - i + 1);
		}
	}

	//copy remaining elements
	while (i <= mid)
	{
		aux[k++] = arr[i++];
	}

	/*
	no need to copy the second half since the remaining items are already in their correct position in the temporary array
	*/

	//copy back to the original array to reflect sorted order
	for (int i = low; i <= high; i++)
	{
		arr[i] = aux[i];
	}

	return inversionCount;
}

//sort array arr[low...high] using auxiliary array aux

int MergeSort(int arr[], int aux[], int low, int high)
{
	//base case
	if (high <= low)
	{
		return 0;
	}

	//find midpoint 
	int mid = (low + ((high - low) >> 1));
	int inversionCount = 0;

	//recursively split runs into two halves until runsize <= 1
	//then merges them and return up the call chain
	//split/merge left half
	inversionCount += MergeSort(arr, aux, mid + 1, high);

	//merge the two half runs
	inversionCount += Merge(arr, aux, low, mid, high);

	return inversionCount;

}

int main()
{
	int arr[] = { 1, 9, 6, 4, 5 };

	int N = sizeof(arr) / sizeof(arr[0]);

	int* aux = new int[N];
	for (int i = 0; i < N; i++) {
		aux[i] = arr[i];
	}

	// get the inversion count by performing merge sort on arr
	printf("The inversion count is %d", MergeSort(arr, aux, 0, N - 1));

	return 0;
}

/*

*/