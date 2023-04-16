#include "Header.h";

using namespace std;

/*
Given a set of positive integers, check if it can be divided into two subsets with equal sum.

For example,

Consider S = {3, 1, 1, 2, 2, 1}

We can partition S into two partitions, each having a sum of 5.

S1 = {1, 1, 1, 2}
S2 = {2, 3}

Note that this solution is not unique. Here’s another solution.

S1 = {3, 1, 1}
S2 = {2, 2, 1}
Practice This Problem

The partition problem is a special case of the Subset Sum Problem, which itself is a special case of the Knapsack Problem. The idea is to calculate the sum of all elements in the set, say sum. If sum is odd, we can’t divide the array into two sets. If sum is even, check if a subset with sum/2 exists or not. Following is the algorithm to find the subset sum:

Consider each item in the given array one by one, and for each item, there are two possibilities:

Include the current item in the subset and recur for the remaining items with the remaining total.
Exclude the current item from the subset and recur for the remaining items.
Finally, return true if we get a subset by including or excluding the current item; otherwise, return false. The recursion’s base case would be when no items are left, or the sum becomes negative. We return true when the sum becomes 0, i.e., the subset is found.


The algorithm can be implemented as follows in C++
// returns true if there exists a subset of nums[] with the given sum
bool subsetSum(vector<int> const& nums, int n, int sum)
{
	// return true if the sum becomes 0
	if (sum == 0)
	{
		return true;
	}

	//base case no items left or sum becomes negative
	if (n < 0 || sum < 0)
	{
		return false;
	}

	// case 1 include the current iten nus[n] in the subset and recur
	// for remaining items n-1 with the remaining total sum-nums[n]
	bool include = subsetSum(nums, n - 1, sum - nums[n]);

	// return true if we get subset by including the current item
	if (include)
	{
		return true;
	}

	// case 2 exclude the current item nums[n] from the subset and recur for
	// remaining items n-1
	bool exclude = subsetSum(nums, n - 1, sum);

	// return true if we get subset by excluding the current item
	// falso otherwise
	return exclude;
}

// Returns true if given array nums[0...n-1]
// subsets with equal sum
bool partition(vector<int> const& nums)
{
	int sum = accumulate(nums.begin(), nums.end(), 0);

		// return true if the sum is even and the array can be divided into
		// two subsets with equal sum
		return !(sum & 1) && subsetSum(nums, nums.size() - 1, sum / 2);
}

The time complexity of the above solution is exponential and occupies space in the call stack.


The problem has an optimal substructure and also exhibits overlapping subproblems, i.e., the problem can be split into smaller subproblems, and the same subproblems will get computed again and again. We can easily prove this by drawing a recursion tree of the above code.

Dynamic programming can solve this problem by saving subproblem solutions in memory rather than computing them again and again. The idea is to solve smaller subproblems first, then solve larger subproblems from them. The following bottom-up approach computes T[i][j], for each 1 <= i <= n and 1 <= j <= sum, which is true if subset with sum j can be found using items up to first i items. It uses the value of smaller values i and j already computed. It has the same asymptotic runtime as Memoization but no recursion overhead.


Following is the C++

*/

// Returns true if there exists a subset of `array[0…n)` with the given sum
bool subsetSum(vector<int> const& nums, int sum)
{
	int n = nums.size();

	// `T[i][j]` stores true if subset with sum `j` can be attained
	// using items up to first `i` items

	//allocate the array
	bool** T = new bool* [n + 1];
	for (int i = 0; i < n + 1; i++)
		T[i] = new bool[sum + 1];
	// if 0 items in the list and the sum is non-zero
	for (int j = 1; j <= sum; j++) {
		T[0][j] = false;
	}

	// if the sum is zero
	for (int i = 0; i <= n; i++) {
		T[i][0] = true;
	}

	// do for i'th item
	for (int i = 1; i <= n; i++)
	{
		// consider all sum from 1 to sum
		for (int j = 1; j <= sum; j++)
		{
			// don't include the i'th element if `j-nums[i-1]` is negative
			if (nums[i - 1] > j) {
				T[i][j] = T[i - 1][j];
			}
			else {
				// find the subset with sum `j` by excluding or including the i'th item
				T[i][j] = T[i - 1][j] || T[i - 1][j - nums[i - 1]];
			}
		}
	}

	// return maximum value
	return T[n][sum];
}

// Partition problem – Returns true if given array `nums[0…n-1]` can
// be divided into two subsets with equal sum
bool partition(vector<int> const& nums)
{
	int sum = accumulate(nums.begin(), nums.end(), 0);

	// return true if the sum is even and the array can be divided into
	// two subsets with equal sum
	return !(sum & 1) && subsetSum(nums, sum / 2);
}


int main()
{

	// Input: a set of items
	vector<int> nums = { 7, 3, 1, 5, 4, 8 };

	if (partition(nums)) {
		cout << "Set can be partitioned";
	}
	else {
		cout << "Set cannot be partitioned";
	}

	return 0;
}

/*

*/