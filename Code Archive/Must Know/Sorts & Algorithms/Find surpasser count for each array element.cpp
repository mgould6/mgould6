#include "Header.h";

using namespace std;

/*
Find surpasser count for each array element
Google Translate Icon
Given an integer array having distinct elements, find the surpasser count for each element in it. In other words, for each array element, find the total number of elements to its right, which are greater than it.

For example,

Input:  { 4, 6, 3, 9, 7, 10 }

Output: { 4, 3, 3, 1, 1, 0 }
Practice This Problem

A simple solution would be for each array element, count all elements greater than it to its right. The implementation of this approach can be seen here. It runs in O(n2) time, where n is the size of the input.


We can reduce the time complexity to O(n.log(n)) by using merge sort algorithm. The problem is similar to finding the inversion count of an array. Since surpasser is just the opposite of inversion, sort the array in descending order and maintain a map to store the surpasser count for each distinct array element.

The algorithm can be implemented as follows in C++, Java, and Python:


*/

//function to merge two sorted subarrays arr[low..mid]
// and arr[mid+1...high]
void merge(int arr[], int aux[], int low, int mid, int high, unordered_map<int, int>& surpasser_count)
{
	int k = low, i = low, j = mid + 1;
	int count = 0;

	//run if there are elements in the left and right runs
	while (i <= mid && j <= high)
	{
		if (arr[i] > arr[j])
		{
			//update surpasser count of arr[i]
			surpasser_count[arr[i]] += count;

			aux[k++] = arr[j++];
		}
		else
		{
			aux[k++] = arr[j++];
			count++;
		}
	}

	//copy remaining elements 
	while (i <= mid)
	{
		surpasser_count[arr[i]] += count;
		aux[k++] = arr[i++];
	}

	// no need to copy the second half (since remaining items
	// are already in their correct position in the temporary array

	//copy back to the original array to reflect sorted order
	for (int i = low; i <= high; i++)
	{
		arr[i] = aux[i];
	}
}

//function to sort array arr[low..high] in descending order
void merge_sort(int arr[], int aux[], int low, int high, unordered_map<int, int>& surpasser_count)
{
	//base case run size is less than or equal to 1
	if (high <= low)
	{
		return;
	}

	//find midpoint
	int mid = (low + ((high - low) >> 1));

	//recursively split runs into two halves until run size == 1
	//merge them and return up the call chain
	merge_sort(arr, aux, low, mid, surpasser_count);
	merge_sort(arr, aux, mid + 1, high, surpasser_count);

	merge(arr, aux, low, mid, high, surpasser_count);
}



//function to find the surpasser count for each array element
unordered_map<int, int> surpasserCount(int const A[], int n)
{

	unordered_map<int, int> surpasser_count;

	//create two copies of the original array
	int* arr{ new int[n] {} }, * aux{ new int[n] {} };

	memcpy(aux, A, n * sizeof(A[0]));
	memcpy(arr, A, n * sizeof(A[0]));

	//sort array arr[] in descending order using auxiliary array aux[]
	merge_sort(arr, aux, 0, n - 1, surpasser_count);

	return surpasser_count;
}

int main()
{

	int arr[] = { 4, 6, 3, 9, 7, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// find the surpasser count for array elements
	unordered_map<int, int> surpasser_count = surpasserCount(arr, n);
	for (int i = 0; i < n; i++) {
		cout << surpasser_count[arr[i]] << " ";
	}
	return 0;
}

/*

*/