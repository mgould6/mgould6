#include "Header.h";

using namespace std;

/*
Maximum Sum Subarray Problem (Kadane’s Algorithm)
Given an integer array, find a contiguous subarray within it that has the largest sum.

For example,

Input:  {-2, 1, -3, 4, -1, 2, 1, -5, 4}

Output: Subarray with the largest sum is {4, -1, 2, 1} with sum 6.
Practice This Problem

The problem differs from the problem of finding the maximum sum subsequence. Unlike subsequences, subarrays are required to occupy consecutive positions within the original array.


We can easily solve this problem in linear time using Kadane’s algorithm. The idea is to maintain a maximum (positive-sum) subarray “ending” at each index of the given array. This subarray is either empty (in which case its sum is zero) or consists of one more element than the maximum subarray ending at the previous index.

The algorithm can be implemented as follows in C++
*/

int KadaneAlgorithm(int arr[], int n)
{

	//store the maximum subarray found so far
	int max_so_far = 0;

	//stores the maximum sum of subarray ending at the current position
	int max_ending_here = 0;

	//traverse the arry 

	for (int i = 0; i < n; i++)
	{
		//update the maximum sum of subarray ending at index i by adding the current element to the maximum sum ending at previous index
		max_ending_here = max_ending_here + arr[i];

		//if the maximum sum is negative, set it to 0
		max_ending_here = max(max_ending_here, 0);

		//update the result if the current subarray sum is found to be greater
		max_so_far = max(max_ending_here, max_so_far);
	}

	return max_so_far;
}

int main()
{
	int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "the maximum sum of a contiguous array is " << KadaneAlgorithm(arr, n);



	return 0;
}

