#include "Header.h";

using namespace std;

/*
In-place merge two sorted arrays

Given two sorted arrays, X[] and Y[] of size m and n each, merge elements of X[] with elements of array Y[] by maintaining the sorted order, i.e., fill X[] with the first m smallest elements and fill Y[] with remaining elements.

Do the conversion in-place and without using any other data structure.


For example,

Input:

X[] = { 1, 4, 7, 8, 10 }
Y[] = { 2, 3, 9 }

Output:

X[] = { 1, 2, 3, 4, 7 }
Y[] = { 8, 9, 10 }


The idea is simple. Consider each array element X[] and ignore it if it is already in the correct order (i.e., the element smallest among all remaining elements); otherwise, swap it with the smallest element, which happens to be the first element of Y[]. After swapping, move the element (now present at Y[0]) to its correct position in Y[] to maintain the sorted order.


Following is the implementation in C++,The merge process is almost similar to the merge routine of the merge sort algorithm. The only difference is that we are not using an auxiliary array for merging.
*/

void printArray(int arr[], int n)
{
	cout << "[";

	for (int i = 0; i < n; i++)
	{
		cout << " " << arr[i] << ", ";
	}

	cout << "]" << endl;

}

void merge(int X[], int Y[], int m, int n)
{
	for (int i = 0; i < m; i++)
	{

		if (X[i] > Y[0])
		{
			swap(X[i], Y[0]);

			int first = Y[0];
			int k;
			for (k = 1; k < n && Y[k] < first; k++)
			{
				Y[k - 1] = Y[k];
			}
			Y[k - 1] = first;
		}
	}
}

int main()
{
	int X[] = { 1, 4, 7, 8, 10 };
	int Y[] = { 2, 3, 9 };

	int m = sizeof(X) / sizeof(X[0]);
	int n = sizeof(Y) / sizeof(Y[0]);


	merge(X, Y, m, n);
	printArray(X, m);
	printArray(Y, n);

	return 0;
}

