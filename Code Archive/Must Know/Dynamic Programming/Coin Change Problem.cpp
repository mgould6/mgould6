#include "Header.h";

using namespace std;

/*
Coin Change Problem
Given an unlimited supply of coins of given denominations, find the total number of distinct ways to get the desired change.

For example,

Input: S = { 1, 3, 5, 7 }, target = 8

The total number of ways is 6

{ 1, 7 }
{ 3, 5 }
{ 1, 1, 3, 3 }
{ 1, 1, 1, 5 }
{ 1, 1, 1, 1, 1, 3 }
{ 1, 1, 1, 1, 1, 1, 1, 1 }


Input: S = { 1, 2, 3 }, target = 4

The total number of ways is 4

{ 1, 3 }
{ 2, 2 }
{ 1, 1, 2 }
{ 1, 1, 1, 1 }

The problem has an optimal substructure as the problem can be broken down into smaller subproblems, which can further be broken down into yet smaller subproblems, and so on. The problem also clearly exhibits overlapping subproblems, so we will end up solving the same subproblem over and over again. The repeated subproblems can be seen by drawing a recursion tree for higher values of the desired change. We know that problems with optimal substructure and overlapping subproblems can be solved using dynamic programming where the subproblem solutions are memoized rather than computed and again.

Following is the C++
The time complexity of the above top-down solution is O(n.target), where n is the total number of coins and target is the total change required. The auxiliary space required by the program is O(n.target).



*/

//function to find the total number of distinct ways to get a change of target 
//from an unlimited supply of coins in set S
int count(vector<int> const& S, int n, int target, unordered_map<string, int>& lookup)
{
	//if the total is 0 return 1 (solution found)
	if (target == 0)
	{
		return 1;
	}

	//return 0 if total becomes negative or no elements are left 
	//(solution does not exist
	if (target < 0 || n < 0)
	{
		return 0;
	}

	//construct a unique map key from dynamic elements of the input 
	string key = to_string(n) + "|" + to_string(target);

	//if the subproblem is seen for the first time solve it and store its result in a map
	if (lookup.find(key) == lookup.end())
	{
		//case 1. include current coin S[n] in solution and recur 
		//with remaining change target - S[n] with the same number of coins 
		int include = count(S, n, target - S[n], lookup);

		//case 3 exclude current coin S[n] from solution and recur for remaining coins n-1

		int exclude = count(S, n - 1, target, lookup);

		//assign total ways by including or excluding current coin
		lookup[key] = include + exclude;

	}

	//return solution to current sub problem
	return lookup[key];
}



int main()
{
	//n coins of given denominations
	vector<int> S = { 1, 2, 3 };
	int n = S.size();

	//total change required
	int target = 4;


	// create a map to store solutions to subproblems
	unordered_map<string, int> lookup;

	cout << "the total number of ways to get the desired change is " << count(S, n - 1, target, lookup);

	return 0;
}

/*
The idea is to use recursion to solve this problem. We recur to see if the total can be reached by choosing the coin or not for each coin of given denominations. If choosing the current coin results in the solution, update the total number of ways.

Following is the C++

//functio nto find the total number of ways to get a change of target
//from an unlimited supply of coins in set S
int count(vector<int> const& S, int target)
{
	//if the total is = 0 return 1
	if (target == 0)
	{
		return 1;
	}

	//return 0 if total becomes negative
	if (target < 0)
	{
		return 0;
	}

	//initialize the total number of ways to 0
	int result = 0;

	//do for each coin
	for (int c : S)
	{
		//recur to see if the total can be reached by including current coin c
		result += count(S, target - c);
	}

	//return the total number of ways
	return result;
}


The time complexity of the above solution is exponential since each recursive call is making n recursive calls. It also requires additional space for the call stack.

There is an issue with the above solution. The above solution doesn’t always return distinct sets. For example, for set {1, 2, 3}, it returns 7 as some ways are permutations of each other, as shown below:

How can we get distinct ways?

The idea is somewhat similar to the Knapsack problem. We can recursively define the problem as:

count(S, n, total) = count(S, n, total-S[n]) + count(S, n-1, total);
That is, for each coin.

Include current coin S[n] in solution and recur with remaining change total-S[n] with the same number of coins.
Exclude current coin S[n] from solution and recur for remaining coins n-1.
Finally, return the total ways by including or excluding the current coin. The recursion’s base case is when a solution is found (i.e., change becomes 0) or the solution doesn’t exist (when no coins are left, or total becomes negative). Following is the C++


//function to find the total number of distinct ways to get a change of target
//from an unlimited supply of coins in set S
int count(vector<int> const& S, int n, int target)
{
	//if the total is 0, return 1
	if (target == 0)
	{
		return 1;
	}

	//return 0 if total becomes negative (solution does not exist
	//no elements are left
	if (target < 0 || n < 0)
	{
		return 0;
	}

	//case 1. include current coin S[n] in solution and recur
	//with remaining change 'target - s[n]' with the same number of coins
	int include = count(S, n, target - S[n]);

	//case 2. exclude current coin S[n] from the solution and recur
	int exclude = count(S, n - 1, target);
	//return total ways by including or excluding current coint
	return include + exclude;
}
The time complexity of the above solution is still exponential and requires auxiliary space for the call stack.







#include <stdio.h>

// Function to find the total number of distinct ways to get
// a change of `target` from an unlimited supply of coins in set `S`
int count(int S[], int n, int target)
{
	int T[target+1];

	for (int i = 0; i <= target; i++) {
		T[i] = 0;
	}

	T[0] = 1;

	for (int i = 0; i < n; i++)
	{
		for (int j = S[i]; j <= target; j++) {
			T[j] += T[j - S[i]];
		}
	}

	return T[target];
}

int main(void)
{
	// `n` coins of given denominations
	int S[] = { 1, 2, 3 };
	int n = sizeof(S) / sizeof(S[0]);

	// total change required
	int target = 4;

	printf("The total number of ways to get the desired change is %d", count(S, n, target));

	return 0;
}



The time complexity of the above top-down solution is O(n.target), where n is the total number of coins and target is the total change required. The auxiliary space required by the program is O(n.target).


We can even write a bottom-up version of the above memoized solution. The following code shows how to implement this in C
The time and space complexity of the above bottom-up solution remains the same as the memoized recursive solution. However, the space complexity can be reduced to O(target) using the simplified algorithm below:

#include <stdio.h>

// Function to find the total number of distinct ways to get
// a change of `target` from an unlimited supply of coins in set `S`
int count(int S[], int n, int target)
{
	int T[target+1];

	for (int i = 0; i <= target; i++) {
		T[i] = 0;
	}

	T[0] = 1;

	for (int i = 0; i < n; i++)
	{
		for (int j = S[i]; j <= target; j++) {
			T[j] += T[j - S[i]];
		}
	}

	return T[target];
}

int main(void)
{
	// `n` coins of given denominations
	int S[] = { 1, 2, 3 };
	int n = sizeof(S) / sizeof(S[0]);

	// total change required
	int target = 4;

	printf("The total number of ways to get the desired change is %d", count(S, n, target));

	return 0;
}
*/