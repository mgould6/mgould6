#include "Header.h";

using namespace std;

/*
Print continuous subarray with maximum sum
Given an integer array, find and print a contiguous subarray with the maximum sum in it.

For example,

Input:  {-2, 1, -3, 4, -1, 2, 1, -5, 4}

Output: The contiguous subarray with the largest sum is {4, -1, 2, 1}


Input:  {8, -7, -3, 5, 6, -2, 3, -4, 2}

Output: The contiguous subarray with the largest sum is {5, 6, -2, 3}

We can easily solve this problem in linear time by maintaining the maximum subarray sum ending at each array index. Then,

The subarray is either empty in which case its sum is zero, or
It consists of one more element than the maximum subarray ending at the previous index.
We have already discussed this approach using Kadane’s algorithm, but that only output the sum
of contiguous subarray having the largest sum but do not print the subarray itself. We can easily
modify the algorithm to keep track of the maximum subarray’s starting and ending indices.

Following is the C++, Java, and Python program that demonstrates it:


*/

void maxSub(int arr[], int n)
{
	//variables for maintaining the maximum subarray sum at each array index
	int max_ending_here = 0;
	int max_so_far = 0;
	int begin = 0, start = 0, end = 0;

	for (int i = 0; i < n; i++)
	{
		//store the max current element sum
		max_ending_here = max_ending_here + arr[i];

		//if max at element is less than current element 
		if (max_ending_here < arr[i])
		{
			//set max here to current element and record the beginning index of the continuous subarray
			max_ending_here = arr[i];
			begin = i;
		}

		//if max so far is less than current max here
		if (max_so_far < max_ending_here)
		{
			//max so far == max ending here, set the starting index == begin, and set the ending index = i;
			max_so_far = max_ending_here;
			start = begin;
			end = i;
		}
	}

	cout << "the contiguous subarray with the largest sum is: ";

	for (int i = start; i <= end; i++)
	{
		cout << arr[i] << " ";
	}

}


int main()
{

	int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	int n = sizeof(arr) / sizeof(arr[0]);

	maxSub(arr, n);

	return 0;
}

