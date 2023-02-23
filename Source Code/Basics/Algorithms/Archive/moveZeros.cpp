#include "Header.h";

using namespace std;

/*
Move all zeros present in an array to the end
Given an integer array, move all zeros present in it to the end. The solution should maintain the relative order of items in the array and should not use constant space.

For example,

Input:  { 6, 0, 8, 2, 3, 0, 4, 0, 1 }

Output: { 6, 8, 2, 3, 4, 1, 0, 0, 0 }

The idea is simple – if the current element is non-zero, place the element at the next available position in the array. After all elements in the array are processed, fill all remaining indices by 0. This approach is demonstrated below in C, Java, and Python:



*/

void moveZeros(int arr[], int n)
{
	//stores the index of the next available position
	int k = 0;

	for (int i = 0; i < n; i++)
	{

		//if the current element is not zero put the element at the next free position in the array
		if (arr[i] != 0)
		{
			arr[k++] = arr[i];
		}
	}

	//move all zeros to the end of the array
	for (int i = k; i < n; i++)
	{
		arr[i] = 0;
	}
}


int main()
{
	int arr[] = { 6, 0, 8, 2, 3, 0, 4, 0, 1 };
	int n = sizeof(arr) / sizeof(arr[0]);

	moveZeros(arr, n);

	return 0;
}

