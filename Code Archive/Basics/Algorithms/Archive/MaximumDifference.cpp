#include "Header.h";

using namespace std;

/*
Find the maximum difference between two array elements that satisfies the given constraints
Given an integer array, find the maximum difference between two elements in it such that the smaller element appears before the larger element.

For example,

Input:  { 2, 7, 9, 5, 1, 3, 5 }

Output: The maximum difference is 7.

The pair is (2, 9)

We can solve this problem in linear time. The idea is to traverse the array from the right and keep track of the maximum difference found so far. If the current element is less than the maximum element found so far and their difference is more than the maximum difference found so far, update the maximum difference with the current difference.

The algorithm can be implemented as follows in C

*/

//helper functiont to determine if difference is larger
int max(int x, int y)
{
	return (x > y) ? x : y;
}

int maximumDifference(int arr[], int n)
{
	//declare a diff variable and initialize to INT_MIN
	int diff = INT_MIN;

	//if an array of size 0? return the INT_MIN diff
	if (n == 0)
	{
		return diff;
	}

	//create int to store the current max at the end of the array
	
	int max_so_far = arr[n - 1];

	//iterate through array in reverse from the second to last position
	for (int i = n - 2; i >= 0; i--)
	{

		//if element is greater than max so far update the max so far element
		if (arr[i] >= max_so_far)
		{
			max_so_far = arr[i];
		}
		//compare the  difference with the  max so far minus the current element 
		else
		{
			diff = max(diff, max_so_far - arr[i]);
		}
	}
	return diff;
}


int main()
{
	int arr[] = { 2, 7, 9, 5, 1, 3, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);

	//store the result of maximum difference
	int result = maximumDifference(arr, n);

	//once result no longer == INT_MIN print the result and exit program
	if (result != INT_MIN)
	{
		printf("the maximum difference is %d", result);
	}
	return 0;
}

