#include "Header.h";

using namespace std;

/*
Find the maximum absolute difference between the sum of two non-overlapping subarrays
Google Translate Icon
Given an array, find the maximum absolute difference between the sum of elements of two non-overlapping subarrays in linear time.

Please note that the problem specifically targets subarrays that are contiguous (i.e., occupy consecutive positions) and inherently maintains the order of elements.


For example,

Input:  A[] = { -3, -2, 6, -3, 5, -9, 3, 4, -1, -8, 2 }

Output: The maximum absolute difference is 19.

The two subarrays are { 6, -3, 5 }, { -9, 3, 4, -1, -8 } whose sum of elements are 8 and -11, respectively. So, abs(8-(-11)) or abs(-11-8) = 19.
Practice This Problem

The idea is to calculate the maximum and minimum sum of subarrays ending and starting at any index i in the array. Then for each index i, consider the maximum absolute value of the following:

Maximum subarray sum in subarray ending at index i – Minimum subarray sum in subarray starting at index i+1
Minimum subarray sum in subarray ending at index i – Maximum subarray sum in subarray starting at index i+1
If Kadane’s algorithm is used, the time complexity of this solution is O(n2), where n is the size of the input.


We can solve this problem in O(n) by using extra space. The idea is to create four auxiliary arrays, left_min[i], left_max[], right_min[], right_min[], such that:

left_max[i] stores the maximum sum of subarray in A(0, i)
right_max[i] stores the maximum sum of subarray in A(i, n-1)
left_min[i] stores the minimum sum of subarray in A(0, i)
right_min[i] stores the minimum sum of subarray in A(i, n-1)
To fill left_max[] and right_max[] arrays in linear time, we can use the standard Kadane’s algorithm for finding the maximum sum of a subarray.

To fill left_min[] and right_min[] arrays, we can still use Kadane’s algorithm by transforming the array so that each element’s sign is reversed. Then find the maximum sum of subarray for each index and invert its sign to get the minimum subarray sum.


The algorithm can be implemented as follows in C++
*/


//diff->counter for loop from i to j in A[] diff can b +1 or -1
//if the diff is 1 fill aux[k] with the maximum sum of subarray A[0,k]
//if the diff is -1 fill aux[k] with the maximum sum of subarray A[k, n-1]
//usig kadanes algoritm

void findMaxSumSubarray(int A[], int aux[], int i, int j, int diff)
{
	int max_so_far = A[i];
	int max_ending_here = A[i];
	aux[i] = A[i];

	for (int k = i + diff; k != j; k += diff)
	{
		//update the maximum sum of subarray ending or starting at index k
		max_ending_here = max(A[k], max_ending_here + A[k]);

		//update the result if the current subarray sum is found to be greater
		max_so_far = max(max_so_far, max_ending_here);
		aux[k] = max_so_far;
	}
}

void fillArrays(int A[], int left_max[], int right_max[], int left_min[], int right_min[], int n)
{
	findMaxSumSubarray(A, left_max, 0, n - 1, 1);
	findMaxSumSubarray(A, right_max, n - 1, 0, -1);

	///negate A[] for finding the minimum sum of subarrays using
	//the same logic for finding the maximum sum of subarrays
	transform(A, A + n, A, negate<int>());

	findMaxSumSubarray(A, left_min, 0, n - 1, 1);
	findMaxSumSubarray(A, right_min, n - 1, 0, -1);

	//negate left_min[] and right_min[] to get the minimum sum of subarrays
	transform(left_min, left_min + n, left_min, negate<int>());
	transform(right_min, right_min + n, right_min, negate<int>());

	//restore the sign of A[]
	transform(A, A + n, A, negate<int>());
}

//find the maximum absolute difference betweent the sum of elements of
//two non overlapping subarrays in a given arrayh
int findMaxAbsDiff(int A[], int n)
{

	//base case
	if (n == 0)
	{
		return 0;
	}

	//base case 
	if (n == 1)
	{
		return A[0];
	}

	//left_max[i] stores the maximum sum subarray in A(0,1)
	//right_max[i] stores the maximum sum subarray in A(i, n-1)
	//right_max[i] stores the maximum sum subarray in A(i, n-1)
	//left_min[i] stores the minimum sum of subarray in A(0,i)
	//right_min[i] stores the minimum sum of subarray in A(i, n-1)
	int* left_max{ new int[n] {} }, * right_max{ new int[n] {} }, * left_min{ new int[n] {} }, * right_min{ new int[n] {} };
	fillArrays(A, left_max, right_max, left_min, right_min, n);

	//storese the maximum absolute differnce
	int max_abs_diff = INT_MIN;

	//do for each index i in the array
	for (int i = 0; i < n - 1; i++)
	{
		max_abs_diff = max(max_abs_diff, max(abs(left_max[i] - right_min[i + 1]),
			abs(left_min[i] - right_max[i + 1])));
	}

	return max_abs_diff;
}

int main()
{
	int A[] = { -3, -2, 6, -3, 5, -9, 3, 4, -1, -8, 2 };
	int n = sizeof(A) / sizeof(A[0]);

	cout << "The maximum absolute difference is " << findMaxAbsDiff(A, n);


	return 0;
}

/*

*/