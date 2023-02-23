#include "Header.h";

using namespace std;

/*
Dynamic Programming - Fibonacci Numbers With an Array

*/

//function to find nth fibonacci number
int fib(int n, int lookup[])
{
	if (n <= 1)
	{
		return n;
	}

	//if the subproblem is seen for the first time 
	if (lookup[n] == 0)
	{
		lookup[n] = fib(n - 1, lookup) + fib(n - 2, lookup);
	}

	return lookup[n];
}


int main()
{
	const int n = 8;

	int lookup[n + 1];

	memset(lookup, 0, sizeof(lookup));

	cout << fib(n, lookup);

	return 0;
}

