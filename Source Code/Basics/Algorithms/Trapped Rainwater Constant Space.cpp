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

The time complexity of the above solution is O(n) and doesn’t require any extra space.


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
int trap(int heights[], int n)
{
	//maintain two pointers left and right, pointing to the leftmost 
	//and rightmost index of the input array

	int left = 0, right = n - 1, water = 0;

	int maxLeft = heights[left];
	int maxRight = heights[right];

	while (left < right)
	{
		if (heights[left] <= -heights[right])
		{
			left++;
			maxLeft = max(maxLeft, heights[left]);
			water += (maxLeft - heights[left]);
		}
		else {
			right--;
			maxRight = max(maxRight, heights[right]);
			water += (maxRight - heights[right]);
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