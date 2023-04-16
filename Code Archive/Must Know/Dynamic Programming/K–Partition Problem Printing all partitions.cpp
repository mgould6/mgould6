#include "Header.h";

using namespace std;

/*

In the k–partition problem, we need to partition an array of positive integers into k disjoint subsets that all have an equal sum, and they completely cover the set.

For example, consider set S = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 }.


1. S can be partitioned into two partitions, each having a sum of 30.

S1 = { 5, 3, 8, 4, 6, 4 }
S2 = { 7, 3, 5, 12, 2, 1 }

2. S can be partitioned into three partitions, each having a sum of 20.

S1 = { 2, 1, 3, 4, 6, 4 }
S2 = { 7, 5, 8 }
S3 = { 3, 5, 12 }

3. S can be partitioned into four partitions, each having a sum of 15.

S1 = { 1, 4, 6, 4 }
S2 = { 2, 5, 8 }
S3 = { 12, 3 }
S4 = { 7, 3, 5 }

4. S can be partitioned into five partitions, each having a sum of 12.

S1 = { 2, 6, 4 }
S2 = { 8, 4 }
S3 = { 3, 1, 5, 3 }
S4 = { 12 }
S5 = { 7, 5 }



Practice This Problem


k-partition problem is a special case of Partition Problem, where the goal is to partition S into two subsets with equal sum. This post will extend the 3-partition solution to find and print k–partitions.

We can start by calculating the sum of all elements in the set. If the sum is not divisible by k, we can’t divide the array into k subsets with an equal sum. If the sum is divisible by k, check if k subsets with the sum of elements equal to sum/k exists or not. We can find this by considering each item in the given array one by one, and for each item, include it in the i'th subset & recur for the remaining items with the remaining sum. We backtrack if the solution is not found by including a current item in the i'th subset and try for the (i+i)'th subset.

The solution should return true and print the subsets when k subsets each with zero-sum are found. For printing the partitions, maintain a separate array A[] to keep track of subsets elements. If the value of A[i] is k, then it means that the i'th item of S is part of the k'th subset.


The algorithm can be implemented as follows in C++
The time complexity of the above solution is exponential and requires additional space for the recursion (call stack).

The time complexity of the above solution is exponential and requires additional space for the recursion (call stack).


*/

// Function to check if all subsets are filled or not
bool checkSum(int sumLeft[], int k)
{
	int r = true;
	for (int i = 0; i < k; i++)
	{
		if (sumLeft[i] != 0)
		{
			r = false;
		}
	}
	return r;
}

// Helper function for solving k partition problem
// It returns true if there exist k subsets with the given sum
bool subsetSum(int S[], int n, int sumLeft[], int A[], int k)
{
	// return true if a subset is found
	if (checkSum(sumLeft, k))
	{
		return true;
	}

	// base case no items left
	if (n < 0)
	{
		return false;
	}

	bool result = false;

	// consider current item S[n] and explore all possibilities
	// using backtracking
	for (int i = 0; i < k; i++)
	{
		if (!result && (sumLeft[i] - S[n] >= 0))
		{
			// mark the current element subset
			A[n] = i + 1;

			// add the current item to the i'th subset
			sumLeft[i] = sumLeft[i] - S[n];

			//recur for remaining items
			result = subsetSum(S, n - 1, sumLeft, A, k);

			//backtracking remove the current item from the ith subset
			sumLeft[i] = sumLeft[i] + S[n];
		}
	}

	//return true if we get a solution
	return result;
}

// function for solving k partition problem. it prints the subsets if
// set S[0...n-1] can be divided into k subsets with equal sum
void partition(int S[], int n, int k)
{

	//base case
	if (n < k)
	{
		cout << "k-partition of set S is not possible";
		return;
	}

	// bet the sum of all elements in the set
	int sum = accumulate(S, S + n, 0);

	int* A{ new int[n] {} };
	int* sumLeft{ new int[k] {} };


	// create an array of size k for each subset and initialize it
	// by their expected sum "sum/k"
	for (int i = 0; i < k; i++)
	{
		sumLeft[i] = sum / k;
	}

	// return true if the sum is divisible by k and set S can 
	// be divided into k subsets with equal sum
	bool result = !(sum % k) && subsetSum(S, n - 1, sumLeft, A, k);

	if (!result)
	{
		cout << "k partition of set S is not possible";
		return;
	}

	// print all k partitions 
	for (int i = 0; i < k; i++)
	{
		cout << "partition " << i << " is ";
		for (int j = 0; j < n; j++)
		{
			if (A[j] == i + 1)
			{
				cout << S[j] << " ";
			}
		}
		cout << endl;
	}
}

int main()
{
	// Input: a set of integers
	int S[] = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };

	// total number of items in `S`
	int n = sizeof(S) / sizeof(S[0]);
	int k = 5;

	partition(S, n, k);

	return 0;
}

/*

*/