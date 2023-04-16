#include "Header.h";

using namespace std;

/*
Given two sorted arrays X[] and Y[] of size m and n each where m >= n and X[] has exactly n vacant cells, merge elements of Y[] in their correct position in array X[], i.e., merge (X, Y) by keeping the sorted order.

For example,

Input:

X[] = { 0, 2, 0, 3, 0, 5, 6, 0, 0 }
Y[] = { 1, 8, 9, 10, 15 }

The vacant cells in X[] is represented by 0

Output:

X[] = { 1, 2, 3, 5, 6, 8, 9, 10, 15 }
Practice This Problem

The idea is simple – move non-empty elements of X[] to the beginning of X[] and then merge X[] with Y[] starting from the end. The merge process is similar to the merge routine of the merge sort algorithm.

The algorithm can be implemented as follows in C
*/


void merge(int X[], int Y[], int m, int n)
{
	//set the end point of X[]
	int k = m + n + 1;

	//put th enext greatest element in the free position in X[] from the end
	while (m >= 0 && n >= 0)
	{
		if (X[m] > Y[n])
		{
			X[k--] = X[m--];
		}
		else
		{
			X[k--] = Y[n--];
		}
	}

	//copy remaining elements of Y[] to X[] if any
	while (n >= 0)
	{
		X[k--] = Y[n--];
	}

	//fill Y with zeros

	for (int i = 0; i < n; i++)
	{
		Y[i] = 0;
	}

}
//function to swap 0s to the beginning of X[]
void rearrange(int X[], int Y[], int m, int n)
{

	if (m == 0)
	{
		return;
	}
	int k = 0;

	//move non empty elements of X[] to the beginning
	for (int i = 0; i < m; i++)
	{
		if (X[i] != 0)
		{
			X[k++] = X[i];
		}
	}

	merge(X, Y, k - 1, n - 1);
}


int main()
{
	int X[] = { 0, 2, 0, 3, 0, 5, 6, 0, 0 };
	int Y[] = { 1, 8, 9, 10, 15 };

	int m = sizeof(X) / sizeof(X[0]);
	int n = sizeof(Y) / sizeof(Y[0]);

	rearrange(X, Y, m, n);

	//print the merged array


	for (int i = 0; i < m; i++)
	{
		printf("%d ", X[i]);
	}

	return 0;
}

