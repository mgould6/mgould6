#include "Header.h";

using namespace std;

/*
* Dynamic Programming
0–1 Knapsack Problem

Input:

value = [ 20, 5, 10, 40, 15, 25 ]
weight = [ 1, 2, 3, 8, 7, 4 ]
int W = 10

Output: Knapsack value is 60

value = 20 + 40 = 60
weight = 1 + 8 = 9 < W


*/

//Values stored in array 'v'
//Weights stored in array 'w'
//total number of distinct items n
//knapsack capacity 'W'
int knapsack(int v[], int w[], int n, int W, unordered_map<string, int>& lookup)
{
	//base case: negative capacity
	if (W < 0)
	{
		return INT_MIN;
	}

	//base case no items left or capacity becomes 0
	if (n < 0 || W == 0)
	{
		return 0;
	}

	//construct a unique map key from dynamic elements of the input
	string key = to_string(n) + "|" + to_string(W);

	//if the subproblem is seen for the first time, solve it 
	//and store its result in a map
	if (lookup.find(key) == lookup.end())
	{
		//case 1. include current items v[n] in the knapsack and recur for 
		//remaining items n-1 with decreased capacity W-w[n]
		int include = v[n] + knapsack(v, w, n - 1, W - w[n], lookup);

		//case 2. exclude current item v[n] from the knapsack 
		//and recur for remaining n-1 items
		int exclude = knapsack(v, w, n - 1, W, lookup);

		//assign the max value we get by including or excluding the current item
		lookup[key] = max(include, exclude);
	}
	return lookup[key];

}



//0-1 knapsack problem
int main()
{
	//input: a set of items, each with a weight and a value
	int v[] = { 20, 5, 10, 40, 15, 25 };
	int w[] = { 1, 2, 3, 8, 7, 4 };

	//knapsack capacity 
	int W = 10;

	//total number of items
	int n = sizeof(v) / sizeof(v[0]);

	//create a map to store solutions to a subproblem
	unordered_map<string, int> lookup;

	cout << "knapsack value is " << knapsack(v, w, n - 1, W, lookup);


	return 0;
}

/*
In the 0–1 Knapsack problem, we are given a set of items, each with a weight and a value, and we need to determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible.

Please note that the items are indivisible; we can either take an item or not (0-1 property). For example,

Input:

value = [ 20, 5, 10, 40, 15, 25 ]
weight = [ 1, 2, 3, 8, 7, 4 ]
int W = 10

Output: Knapsack value is 60

value = 20 + 40 = 60
weight = 1 + 8 = 9 < W
Practice This Problem

The idea is to use recursion to solve this problem. For each item, there are two possibilities:

Include the current item in the knapsack and recur for remaining items with knapsack’s decreased capacity. If the capacity becomes negative, do not recur or return -INFINITY.
Exclude the current item from the knapsack and recur for the remaining items.
Finally, return the maximum value we get by including or excluding the current item. The base case of the recursion would be when no items are left, or capacity becomes 0.


The following C++, Java, and Python implementation finds the maximum value that can be attained with weight less than or equal to W recursively using the above relations:

int knapsack(int v[], int w[], int n, int W)
{
	//base case negative capacity
	if (W < 0)
	{
		return INT_MIN;
	}

	//base case: no items left or capacity becomes 0
	if (n < 0 || W == 0)
	{
		return 0;
	}

	//case 1. include current item v[n] in the knapsack and recur for
	//remaining items n-1 with decreased capacity W-w[n]
	int include = v[n] + knapsack(v, w, n - 1, W - w[n]);

	//case 2. exclude current item v[n] from the knapsack and recur for
	//remaining items n-1
	int exclude = knapsack(v, w, n - 1, W);

	//return maximum value we get by including or excluding the current item
	return max(include, exclude);
}

The time complexity of the above solution is exponential and occupies space in the call stack.
The above solution has an optimal substructure, i.e., the optimal solution can be constructed efficiently from optimal solutions of its subproblem. It also has overlapping subproblems, i.e., the problem can be broken down into subproblems, and each subproblem is repeated several times. To reuse the subproblem solutions, we can apply dynamic programming, in which subproblem solutions are memoized rather than computed over and over again.

Following is the memoized version in C++, Java, and Python, which follows the top-down approach since we first break the problem into subproblems and then calculate and store values.

//Values stored in array 'v'
//Weights stored in array 'w'
//total number of distinct items n
//knapsack capacity 'W'
int knapsack(int v[], int w[], int n, int W, unordered_map<string, int> &lookup)
{
	//base case: negative capacity
	if (W < 0)
	{
		return INT_MIN;
	}

	//base case no items left or capacity becomes 0
	if (n < 0 || W == 0)
	{
		return 0;
	}

	//construct a unique map key from dynamic elements of the input
	string key = to_string(n) + "|" + to_string(W);

	//if the subproblem is seen for the first time, solve it
	//and store its result in a map
	if (lookup.find(key) == lookup.end())
	{
		//case 1. include current items v[n] in the knapsack and recur for
		//remaining items n-1 with decreased capacity W-w[n]
		int include = v[n] + knapsack(v, w, n - 1, W - w[n], lookup);

		//case 2. exclude current item v[n] from the knapsack
		//and recur for remaining n-1 items
		int exclude = knapsack(v, w, n - 1, W, lookup);

		//assign the max value we get by including or excluding the current item
		lookup[key] = max(include, exclude);
	}
	return lookup[key];

}

The time complexity of the above top-down solution is O(n.W) and requires O(n.W) extra space, where n is the total number of items in the input and W is the knapsack’s capacity.



We can also solve this problem in a bottom-up manner. In the bottom-up approach, we solve smaller subproblems first, then solve larger subproblems from them. The following bottom-up approach computes T[i][j], for each 1 <= i <= n and 0 <= j <= W, which is the maximum value that can be attained with weight less than or equal to j and using items up to first i items. It uses the value of smaller values i and j already computed. It has the same asymptotic runtime as Memoization but no recursion overhead.

The algorithm can be implemented as follows in C++,

int knapsack(int v[], int w[], int n, int W)
{
	// `T[i][j]` stores the maximum value that can be attained with
	// weight less than or equal to `j` using items up to first `i` items
	int T[n+1][W+1];

	for (int j = 0; j <= W; j++) {
		T[0][j] = 0;
	}

	// memset (T[0], 0, sizeof T[0]);

	// do for i'th item
	for (int i = 1; i <= n; i++)
	{
		// consider all weights from 0 to maximum capacity `W`
		for (int j = 0; j <= W; j++)
		{
			// don't include the i'th element if `j-w[i-1]` is negative
			if (w[i-1] > j) {
				T[i][j] = T[i-1][j];
			}
			else {
				// find the maximum value by excluding or including the i'th item
				T[i][j] = max(T[i-1][j], T[i-1][j-w[i-1]] + v[i-1]);
			}
		}
	}

	// return maximum value
	return T[n][W];
}

The time complexity of the above bottom-up solution is O(n.W) and requires O(n.W) extra space, where n is the total number of items in the input and W is the knapsack’s capacity.


*/