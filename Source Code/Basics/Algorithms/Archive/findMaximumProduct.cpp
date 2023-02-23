#include "Header.h";

using namespace std;

void findmaximumProduct(int nums[], int n)
{

	//For storing the 2 largest and 2 smallest elements in the array
	int max1 = nums[0], max2 = INT_MIN;
	int min1 = nums[0], min2 = INT_MAX;

	/*
	We can solve this problem in linear time as we need the only maximum, second maximum, minimum, and second minimum elements to solve this problem. We can compute all these in only a single traversal of the array, which accounts for O(n) time complexity.
		*/

	for (int i = 1; i < n; i++)
	{
		//if the current element is more than the max update the max and the second max

		if (nums[i] > max1)
		{
			max2 = max1;
			max1 = nums[i];
		}
		else if (nums[i] > max2)
		{
			max2 = nums[i];
		}

		if (nums[i] < min1)
		{
			min2 = min1;
			min1 = nums[i];
		}
		//if the current element is 
		else if (nums[i] < min2)
		{
			min2 = nums[i];
		}
	}

	// choose the maximum of the following :
	// 1. Product of the maximum and second maximum element or
	// 2. Product of the minimum and second minimum element+

	if (max1 * max2 > min1 * min2)
	{
		printf("Pair is (%d, %d)", max1, max2);
	}
	else
	{
		printf("Pair is (%d, %d)", min1, min2);
	}
}


/*
Given an integer array, find the maximum product of two integers in it.

For example, consider array {-10, -3, 5, 6, -2}. The maximum product is the (-10, -3) or (5, 6) pair.
*/


int main()
{
	int nums[] = { -10, -3, 5, 6, -2 };
	int n = sizeof(nums) / sizeof(nums[0]);

	findmaximumProduct(nums, n);

	return 0;
}

