#include "Header.h";

using namespace std;

/*
Quicksort using Dutch National Flag Algorithm

Implement Quicksort efficiently for inputs containing many repeated elements.

Quicksort exhibits poor performance for inputs that contain many repeated elements. The problem is visible when all the input elements are equal. Then at each point in recursion, the left partition is empty (no input values are less than the pivot), and the right partition has only decreased by one element (the pivot is removed). Consequently, the algorithm takes quadratic time to sort an array of equal values.

Practice This Problem

We can use an alternative linear-time partition routine to solve this problem that separates the values into three groups:

The values less than the pivot,
The values equal to the pivot, and
The values greater than the pivot.
The values equal to the pivot are already sorted, so only the less-than and greater-than partitions need to be recursively sorted. This linear-time partition routine is similar to 3–way partitioning for the Dutch national flag problem.


The algorithm can be implemented as follows in C++

The algorithm’s best-case now occurs when all elements are equal (or are chosen from a small set of k << n elements). The modified Quicksort will perform at most two recursive calls on empty subarrays and thus finish linearly in all identical elements.


*/

//partition routine using the dutch national flag algorithm
pair<int, int> partition(vector<int>& nums, int start, int end)
{
	int mid = start;
	int pivot = nums[end];

	while (mid <= end)
	{
		if (nums[mid] < pivot)
		{
			swap(nums[start], nums[mid]);
			++start, ++mid;
		}
		else if (nums[mid] > pivot)
		{
			swap(nums[mid], nums[end]);
			--end;
		}
		else
		{
			++mid;
		}
	}

	//nums[start....mid-1] contains all occurrences of a pivot
	return make_pair(start - 1, mid);
}

//3 way quick sort routine
void quicksort(vector<int>& nums, int start, int end)
{
	//base condition for 0 or 1 elements
	if (start >= end)
	{
		return;
	}

	//rearrange elements across pivot using the dutch national flag algorithm
	pair<int, int> pivot = partition(nums, start, end);

	//recur on subarray containing elements that are less than the pivot
	quicksort(nums, start, pivot.first);

	//recur on subarray containing elements that are more than the pivot
	quicksort(nums, pivot.second, end);
}

int main()
{
	vector<int> nums = { 2, 6, 5, 2, 6, 8, 6, 1, 2, 6 };
	int n = nums.size();

	// sort list
	quicksort(nums, 0, n - 1);

	// print the sorted array
	for (int i = 0; i < n; i++) {
		cout << nums[i] << " ";
	}


	return 0;
}

/*

*/