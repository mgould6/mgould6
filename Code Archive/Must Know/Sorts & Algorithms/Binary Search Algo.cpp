#include "Header.h";

using namespace std;

/*
Binary Search Algorithm – Iterative and Recursive Implementation
Google Translate Icon
Given a sorted array of n integers and a target value, determine if the target exists in the array in logarithmic time using the binary search algorithm. If target exists in the array, print the index of it.

For example,

Input:

nums[] = [2, 3, 5, 7, 9]
target = 7

Output: Element found at index 3


Input:

nums[] = [1, 4, 5, 8, 9]
target = 2

Output: Element not found
Practice This Problem

A simple solution would be to perform a linear search on the given array. It sequentially checks each array element for the target value until a match is found or all the elements have been searched. The worst-case time complexity of this approach is O(n) as it makes at most n comparisons, where n is the size of the input. This approach doesn’t take advantage of the fact that the input is sorted.

How to perform better?
The idea is to use binary search which is a Divide and Conquer algorithm. Like all divide-and-conquer algorithms, binary search first divides a large array into two smaller subarrays and then recursively (or iteratively) operate the subarrays. But instead of working on both subarrays, it discards one subarray and continues on the second subarray. This decision of discarding one subarray is made in just one comparison.


So binary search reduces the search space to half at each step. By search space, we mean a subarray of the given array where the target value is located (if present in the array). Initially, the search space is the entire array, and binary search redefines the search space at every step of the algorithm by using the property of the array that it is sorted. It does so by comparing the mid-value in the search space to the target value. If the target value matches the middle element, its position in the array is returned; otherwise, it discards half of the search space based on the comparison result.


Let’s track the search space by using two indexes – start and end. Initially, start = 0 and end = n-1 (as initially, the whole array is our search space). At each step, find the mid-value in the search space and compares it with the target. There are three possible cases:

If target = nums[mid], return mid.
If target < nums[mid], discard all elements in the right search space, including the middle element, i.e., nums[mid…high]. Now our new high would be mid-1.
If target > nums[mid], discard all elements in the left search space, including the middle element, i.e., nums[low…mid]. Now our new low would be mid+1.
Repeat the process until the target is found, or our search space is exhausted. Let’s understand this by taking an example. Let

nums = [2, 3, 5, 7, 8, 10, 12, 15, 18, 20]
target = 7

*/

int  binarySearchIterative(int nums[], int n, int target)
{
	//search space is nums[low...high]
	int low = 0, high = n - 1;

	//loop till the search space is exhausted
	while (low <= high)
	{
		//find the mid vale in the search space and compare it with the target
		int mid = low + (high - low) / 2;

		//target value is found
		if (target == nums[mid])
		{
			return mid;
		}

		//if the target is less than the middle element discard all elements
		//in the right search space, including the middle element
		else if (target < nums[mid])
		{
			high = mid - 1;
		}

		//if the target is more than the middle element discard all elements
		//in the left search space including the middle element
		else
		{
			low = mid + 1;
		}
	}
	//target doesn't exist in this space
	return -1;
}

int binarySearchRecursive(int nums[], int low, int high, int target)
{
	//base condition (search space is exhausted)
	if (low > high)
	{
		return -1;
	}

	//find the mid value in the search space and compare it with the target 
	int mid = low + (high - low) / 2;

	//base condition (target is found)
	if (target == nums[mid])
	{
		return mid;
	}

	//discard all elements in the right search space,
	//including the middle element
	else if (target < nums[mid])
	{
		return binarySearchRecursive(nums, low, mid - 1, target);
	}
	else if (target > nums[mid])
	{
		return binarySearchRecursive(nums, mid + 1, high, target);
	}

	//discard all elements in the left search space,
	//including the middle element
	else
	{
		return binarySearchRecursive(nums, mid + 1, high, target);
	}
}

int main()
{
	int nums[] = { 2, 5, 6, 8, 9, 10 };
	int target = 9;
	int n = sizeof(nums) / sizeof(nums[0]);
	int low = 0, high = n - 1;

	int index = binarySearchRecursive(nums, low, high, target);

	if (index != -1)
	{
		printf("element found at index %d", index);
	}
	else
	{
		printf("element not found in the array");
	}


	return 0;
}

