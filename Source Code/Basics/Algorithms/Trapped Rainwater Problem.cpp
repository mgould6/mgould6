#include "Header.h";

using namespace std;

/*
Trapping Rain Water Problem
Trapping rainwater problem: Find the maximum amount of water that can be trapped within a given set of bars where each bar’s width is 1 unit.

For example,


Input: An array containing height of bars {7, 0, 4, 2, 5, 0, 6, 4, 0, 5}

Trapping Rain Water bars

The maximum amount of water that can be trapped is 25, as shown below (blue).

Trapping Rain Water

Practice This Problem


The idea is to calculate the maximum height bar on the left and right of every bar. The amount of water stored on top of each bar is equal to the minimum among the leading’ bar to the left and right minus the current bar’s height. This approach is demonstrated below in C,

The time complexity of the above solution is O(n) and requires O(n) extra space, where n is the total number of given bars.


*/

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int min(int x, int y)
{
	return (x < y) ? x : y;
}

//function to find the amount of water that can be trapped within a given set of bars in a linear time and extra space
int trap(int bars[], int n)
{
	//base case
	if (n <= 2)
	{
		return 0;
	}

	int water = 0;

	//left[i] stores the maximum height of a bar to the left of the current bar
	int* left = new int[n - 1];
	left[0] = INT_MIN;

	//process bars from left to right
	for (int i = 1; i < n - 1; i++)
	{
		left[i] = max(left[i - 1], bars[i - 1]);
	}

	/*
	OR YOU COULD IMPLEMENT RIGHT FIRST
	int right[n];
	right[n - 1] = INT_MIN;
	for (int i = n - 2; i >= 0; i--) {
		right[i] = max(right[i+1], bars[i+1]);
	}

	for (int i = 1; i < n - 1; i++)
	{
		if (min(left[i], right[i]) > bars[i]) {
			water += min(left[i], right[i]) - bars[i];
		}
	}
	*/

	// `right` stores the maximum height of a bar to the right
	// of the current bar
	int right = INT_MIN;

	//process bars from right to left 
	for (int i = n - 2; i >= 1; i--)
	{
		right = max(right, bars[i + 1]);

		//check if it is possible to store water in the current bar
		if (min(left[i], right) > bars[i])
		{
			water += min(left[i], right) - bars[i];
		}
	}

	return water;
}

int main(void)
{
	int heights[] = { 7,0,4,2,5,0,6,4,0,5 };
	int n = sizeof(heights) / sizeof(heights[0]);

	printf("The maximum amount of water that can be trapped is %d: ", trap(heights, n));


	return 0;
}

/*

*/