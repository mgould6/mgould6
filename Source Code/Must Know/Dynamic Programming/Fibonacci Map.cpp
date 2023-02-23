#include "Header.h";

using namespace std;

/*
Dynamic Programming - Fibonacci Number With A Map
*/

/*
Now, suppose we have a simple map object, lookup, which maps each value of fib that has already been calculated to its result, and we modify our function to use it and update it. The resulting function runs in O(n) time instead of exponential time (but requires O(n) space):

Following is the dynamic programming implementation in C++
*/


//function to find the nth fibonacci number
int fib(int n, unordered_map<int, int>& lookup)
{
	if (n <= 1)
	{
		return n;
	}

	//if the subproblem is seen for the first time
	if (lookup.find(n) == lookup.end())
	{
		lookup[n] = fib(n - 1, lookup) + fib(n - 2, lookup);
	}

	return lookup[n];
}

int main()
{
	unordered_map<int, int> lookup;

	cout << fib(8, lookup);
	return 0;
}

