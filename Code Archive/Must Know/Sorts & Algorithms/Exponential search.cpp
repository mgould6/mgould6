#include "Header.h";

using namespace std;

/*
Exponential search
Given a sorted array of n integers and a target value, determine if the target exists in the array or not in logarithmic time. If the target exists in the array, return the index of it.

For example,

Input: A[] = [2, 3, 5, 7, 9]
target = 7

Output: Element found at index 3


Input: A[] = [1, 4, 5, 8, 9]
target = 2

Output: Element not found
Practice This Problem

Exponential search is an algorithm used for searching sorted, unbounded/infinite arrays. The idea is to determine a range that the target value resides in and perform a binary search within that range. Assuming that the array is sorted in ascending order, it looks for the first exponent, k, where the value 2k is greater than the search key. Now 2k and 2k-1 becomes the upper bound and lower bound for the binary search algorithm, respectively.

The algorithm can be implemented as follows in C
Performance
The exponential search takes O(log(i)) time, where i is the target’s position in the array when the target is in the array or position where the target should be if it isn’t in the array.

We can also use the exponential search to search in bounded arrays. It can even out-perform binary search when the target is near the beginning of the array. This is because the exponential search will run in O(log(i)) time, where i is the index of the element being searched for in the array, whereas binary search would run in O(log(n)) time, where n is the total number of elements in the array.


Exercise: Find where a strictly increasing function (f(x) > f(x-1) for all values of x) becomes positive for the first time. Consider f(x) = x2 + 2x - 400. It becomes positive for the first time for x = 20.


References: https://en.wikipedia.org/wiki/Exponential_search
*/

//utility function to find a minimum of two numbers
int min(int x, int y)
{
	return (x > y) ? x : y;
}

//binary search algorithm to return the position of the key x in subarray A[low..high]
int binarySearch(int arr[], int low, int high, int x)
{
	// base condition search space is exhausted
	if (low > high)
	{
		return -1;
	}

	// find the mid value in the search space and 
	// compares it with the key

	int mid = low + (high - low) / 2;

	//base condtion a key is found
	if (x == arr[mid])
	{
		return mid;
	}

	//discard all elements in the right search space
	// including the middle element
	else if (x < arr[mid])
	{
		return binarySearch(arr, low, mid - 1, x);
	}

	// discard all elements in the left search space
	// including the middle element
	else
	{
		return binarySearch(arr, mid + 1, high, x);
	}
}

// returns the position of key x in a given array arr of length n
int exponentialSearch(int arr[], int n, int x)
{
	// base case
	if (n == 0)
	{
		return -1;
	}

	int bound = 1;

	// find the range in which key x would reside
	while (bound < n && arr[bound] < x)
	{
		bound *= 2;	//calculate the next power of 2
	}

	// call binary search on A[bound/2 ...min(bound, n-1)]
	return binarySearch(arr, bound / 2, min(bound, n - 1), x);
}

int main()
{
	int A[] = { 2, 5, 6, 8, 9, 10 };
	int target = 9;

	int n = sizeof(A) / sizeof(A[0]);
	int index = exponentialSearch(A, n, target);

	if (index != -1) {
		printf("Element found at index %d", index);
	}
	else {
		printf("Element not found in the array");
	}

	return 0;
}

/*

*/