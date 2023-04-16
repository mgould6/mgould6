#include "Header.h";

using namespace std;

/*

Maximum Sum Circular Subarray
Given a circular integer array, find a subarray with the largest sum in it.

For example,

Input:  {2, 1, -5, 4, -3, 1, -3, 4, -1}

Output: Subarray with the largest sum is {4, -1, 2, 1} with sum 6.


Input:  {-3, 1, -3, 4, -1, 2, 1, -5, 4}

Output: Subarray with the largest sum is {4, -1, 2, 1} with sum 6.
Practice This Problem

The problem differs from the problem of finding the maximum sum circular subsequence. Unlike subsequences, subarrays are required to occupy consecutive positions within the original array.


The idea is to find the sequence which will have a maximum negative value. If we remove that minimum sum sequence from the input sequence, we will be left with the maximum sum circular sequence. Finally, return the maximum of the maximum-sum circular sequence (includes corner elements) and maximum-sum non-circular sequence.

For example, consider array {2, 1, -5, 4, -3, 1, -3, 4, -1}. The sequence having maximum negative value is {-5, 4, -3, 1, -3}, i.e., -6. If we remove this minimum sum sequence from the array, we will get the maximum sum circular sequence, i.e., {2, 1, 4, -1} having sum 6. Since the maximum sum circular sequence is greater than the maximum sum non-circular sequence, i.e., {4} for the given array, it is the answer.


We can find the maximum-sum non-circular sequence in linear time by using Kadane’s algorithm. We can find a maximum-sum circular sequence by inverting the sign of all array elements and then applying Kadane’s algorithm.

For example, if we invert signs of array {2, 1, -5, 4, -3, 1, -3, 4, -1}, we get {-2, -1, 5, -4, 3, -1, 3, -4, 1} which has maximum sum sequence {5, -4, 3, -1, 3} having sum 6. Now inverting the signs back, we get a minimum sum sequence {-5, 4, -3, 1, -3} having sum -6. The algorithm can be implemented as follows in C++

*/


//kadanes algorithm
int kadanesAlgo(int arr[], int n)
{
	int max_so_far = 0;
	int max_ending_here = 0;

	for (int i = 0; i < n; i++)
	{
		max_ending_here = max_ending_here + arr[i];

		max_ending_here = max(max_ending_here, 0);

		max_so_far = max(max_so_far, max_ending_here);
	}

	return max_so_far;
}

//fucntion to find the maximum sum circular subarray in a given array
int circularKadane(int arr[], int n)
{

	//empty array has a sum of 0
	if (n == 0)
	{
		return 0;
	}

	//find max element present in a given array
	int max_num = *max_element(arr, arr + n);

	//if the array contains all negative values, return the maximum element
	if (max_num < 0)
	{
		return max_num;
	}


	//negate all the array elements
	for (int i = 0; i < n; i++)
	{
		arr[i] = -arr[i];
	}

	//run kadanes algo on the modified array
	int neg_max_sum = kadanesAlgo(arr, n);

	//restore array
	for (int i = 0; i < n; i++)
	{
		arr[i] = -arr[i];
	}

	//return the maximum of the sum returned by kadanes algo on the original array or the modified array + sum of all elements

	return max(kadanesAlgo(arr, n), accumulate(arr, arr + n, 0) + neg_max_sum);
}

int main()
{

	int arr[] = { 2, 1, -5, 4, -3, 1, -3, 4, -1 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "The sum of the subarray with the largest sum is " << circularKadane(arr, n);

	return 0;
}

