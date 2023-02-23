#include "Header.h";

using namespace std;

/*
0–1 Knapsack Problem
In the 0–1 Knapsack problem, we are given a set of items, each with a weight and a value,
and we need to determine the number of each item to include in a collection so that the
total weight is less than or equal to a given limit and the total value is as large as possible.

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
*/

int knapsack(int value[], int weight[], int n, int W)
{
	//base case: negative capacity
	if (W < 0)
	{
		return INT_MIN;
	}

	//base case: no items left or capacity becomes 0
	if (n < 0 || W == 0)
	{
		return 0;
	}

	//case 1: include current item value[n] in the knapsack and recur
	//for remaining items n-1 with decreased capacity W-w[n]
	int include = value[n] + knapsack(value, weight, n - 1, W - weight[n]);

	//case 2: exclude current item value[n] from the knapsack and recur for remaining items n-1
	int exclude = knapsack(value, weight, n - 1, W);

	//return maximum value we get by including or excluding the current item
	return max(include, exclude);
}

int main()
{
	//input: a set of items, each with a weight and a value
	int value[] = { 20, 5, 10, 40, 15, 25 };
	int weight[] = { 1, 2, 3, 8, 7, 4 };

	//knapsack capacity
	int W = 10;

	int n = sizeof(value) / sizeof(value[0]);

	cout << "Knapsack value is " << knapsack(value, weight, n - 1, W);
	return 0;
}

