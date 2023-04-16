#include "Header.h";

using namespace std;

/*
Maximum Product Subset Problem
Given an integer array, find the maximum product of its elements among all its subsets.

For example,

Input:  nums[] = { -6, 4, -5, 8, -10, 0, 8 }

Output: The maximum product of a subset is 15360

The subset with the maximum product of its elements is { -6, 4, 8, -10, 8 }



Input:  nums[] = { 4, -8, 0, 8 }

Output: The maximum product of a subset is 32

The subset with the maximum product of its elements is { 4, 8 }
Practice This Problem

1. Brute-Force Solution
A naive solution is to consider every subset and find the product of their elements. Finally, return the maximum product found among all subsets. The implementation can be seen below in C++

// Function to generate the product of all elements in a given set
// and update maximum product found so far
void findMaxProduct(vector<int> const& set, int& maximum)
{
	int product = 1;

	for (int j : set)
	{
		product = product * j;

		// if the set is not empty then update the product
		if (set.size())
		{
			maximum = max(maximum, product);
		}
	}
}

// Function to generate a power set of a given set S
void findPowerSet(vector<int> const& S, vector<int>& set, int n, int& maximum)
{
	// if we have considered all elements we have generated a subset
	if (n == 0)
	{
		// compute its product of elements and update the maximum product found so far
		findMaxProduct(set, maximum);
		return;
	}

	// consider the n'th element
	set.push_back(S[n - 1]);
	findPowerSet(S, set, n - 1, maximum);

	set.pop_back();		//backtrack
	// or dont consider the nth element
	findPowerSet(S, set, n - 1, maximum);

}

The time complexity of the above solution is exponential and requires additional space for the recursion (call stack).

2. Linear-time Solution
We can solve this problem in linear time by finding a negative element with a minimum absolute value in the set. We also count the total number of negative elements present in the set. If the count of negative elements is odd, exclude that negative element (having minimum absolute value) from the subset; otherwise, consider it (since the multiplication of two negative numbers will give a positive number as output). We need to handle one more special case because 0 will never be part of the subset if at least one positive element or two negative elements are present in the subset. Rest all elements will form part of the subset.

The algorithm can be implemented as follows in C
The time complexity of the above solution is O(n) and doesn’t require any extra space, where n is the size of the input.


*/
int min(int x, int y) {
	return (x < y) ? x : y;
}
// Function to return the maximum product of a subset of a given array
int findMaxProduct(int nums[], int n)
{
	// base case 
	if (n == 0)
	{
		return 0;
	}

	// if the array contains only one element
	if (n == 1)
	{
		return nums[0];
	}

	int product = 1;	// to store the maximum product substet

	// stores the negative elements having a minimum absolut value in the set
	int abs_min_so_far = INT_MAX;

	int negative = 0;
	int positive = 0;

	int contains_zero = 0;

	// traverse the the given  array
	for (int i = 0; i < n; i++)
	{
		// if the current element is negative
		if (nums[i] < 0)
		{
			negative++;
			abs_min_so_far = min(abs_min_so_far, abs(nums[i]));
		}
		// if the current element is positive
		else if (nums[i] > 0) {
			positive++;
		}

		// if the current element is zero
		if (nums[i] == 0) {
			contains_zero = 1;
		}
		else {
			product = product * nums[i];
		}
	}

	// if an odd number of negative elements are present, exclude the negative
	//element having a minimum absolute value from the subset
	if (negative & 1) {
		product = product / -abs_min_so_far;
	}

	// special case – set contains one negative element and one or more 0's
	if (negative == 1 && !positive && contains_zero) {
		product = 0;
	}

	// special case – set contains all 0's
	if (!negative && !positive && contains_zero) {
		product = 0;
	}

	// return maximum product
	return product;
}

int main()
{
	int nums[] = { -6, 4, -5, 8, -10, 0, 8 };
	int n = sizeof(nums) / sizeof(nums[0]);

	printf("The maximum product of a subset is %d", findMaxProduct(nums, n));

	return 0;
}

/*

*/