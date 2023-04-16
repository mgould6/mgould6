#include "Header.h";

using namespace std;

/*
Dynamic Programming - Fibonacci

In the bottom-up approach, we calculate the smaller values of fib first, then build larger values from them. This method also uses O(n) time since it contains a loop that repeats n-1 times, but it only takes constant O(1) space, in contrast to the top-down approach, which requires O(n) space to store the map.

Following is the C++
*/

//function to find the nth fibonacci number
int fib(int n)
{
	if (n <= 1)
	{
		return n;
	}

	int previousFib = 0, currentFib = 1;
	for (int i = 0; i < n - 1; i++)
	{
		int newFib = previousFib + currentFib;
		previousFib = currentFib;
		currentFib = newFib;
	}

	return currentFib;
}


int main()
{
	cout << fib(8);

	return 0;
}

