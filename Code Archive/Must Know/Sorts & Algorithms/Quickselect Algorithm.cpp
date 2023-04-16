#include "Header.h";

using namespace std;

/*
Quickselect Algorithm
Quickselect is a selection algorithm to find the k'th smallest element in an unordered list. It is closely related to the Quicksort sorting algorithm. Like Quicksort, it is efficient traditionally and offers good average-case performance, but has a poor worst-case performance.


For example,

Input: [7, 4, 6, 3, 9, 1]
k = 2

Output: k’th smallest array element is 3


Input: [7, 4, 6, 3, 9, 1]
k = 1

Output: k’th smallest array element is 1
Practice This Problem

Quickselect uses the same overall approach as Quicksort, choosing one element as a pivot and partitioning the data in two based on the pivot, accordingly as less than or greater than the pivot. However, instead of recursing into both sides as in Quicksort, quickselect only recurs into one side with its searching element. Since the pivot is in its final sorted position, all those preceding it in unsorted order, and all those following it in an unsorted order. This reduces the average-case complexity from O(n.log(n)) to O(n) with a worst-case of O(n2), where n is the size of the input.

The algorithm can be implemented as follows in C,


It is worth noticing the resemblance to the Quicksort algorithm. This simple procedure has expected linear performance and, like Quicksort, has excellent performance traditionally, and beyond selecting the k'th element, it also partially sorts the data. It is also an in-place algorithm, requiring only constant memory overhead if tail-call optimization is available, or we can eliminate the tail recursion with a loop.

Time complexity:

Like Quicksort, the quickselect has good average performance but is sensitive to the chosen pivot. With good pivots, meaning ones that consistently decrease the search set by a given fraction, the search set decreases exponentially. By induction (or summing the geometric series), one sees that performance is linear, as each step is linear. The overall time is constant (depending on how quickly the search set reduces). However, if bad pivots are consistently chosen, such as decreasing by only a single element each time, then worst-case performance is quadratic: O(n2). For example, this occurs in searching for the maximum element of a set, using the first element as the pivot, and having sorted data.

Using std::nth_element:

Quickselect and its variants are the selection algorithms most often used in efficient real-world implementations. Quickselect is already provided in the C++ standard library as std::nth_element(first, nth, last) which rearranges the elements in range [first, last) so that the item at the n'th position is the element that would be in that position in a sorted sequence.

It is typically implemented using a version of quickselect called Introselect. Introselect is a hybrid of quickselect and median of medians. If quickselect takes too long (bad pivot selection), then it falls back to the slower but guaranteed linear time algorithm, thus capping its worst-case runtime before it becomes worse than linear.
*/

#define SWAP(x, y) { int temp = x; x = y; y = temp; }
#define N (sizeof(nums)/sizeof(nums[0]))


// Partition using lomuto partition scheme
int partition(int a[], int left, int right, int pIndex)
{
	// pick pIndex as a pivot from the array
	int pivot = a[pIndex];

	// move pivot to end
	SWAP(a[pIndex], a[right]);

	// elements less than the pivot will be pushed to the left of pIndex
	// elements more than the pivot will be pushed to the right of pIndex
	// equal elements can go either way
	pIndex = left;

	// each time we find an element less than or equal to the pivot, pIndex
	// is incremented and that element would be placed before the pivot
	for (int i = left; i < right; i++)
	{
		if (a[i] <= pivot)
		{
			SWAP(a[i], a[pIndex]);
			pIndex++;
		}
	}

	// move pivot to its final place 
	SWAP(a[pIndex], a[right]);

	// return pIndex - index of the pivot element
	return pIndex;
}

// Returns the k'th smallest element in the list within left..right
// the search space within the array is
// changing for each round but the list is still the same size
// thus k does not need to be updated with each round
int quickselect(int nums[], int left, int right, int k)
{
	// if the array contains only one element return that element
	if (left == right)
	{
		return nums[left];
	}

	// select pIndex between left and right
	int pIndex = left + rand() % (right - left + 1);

	pIndex = partition(nums, left, right, pIndex);

	// the pivot is in its final sorted position
	if (k == pIndex)
	{
		return nums[k];
	}

	// if k is less than the pivot index
	else if (k < pIndex)
	{
		return quickselect(nums, left, pIndex - 1, k);
	}

	// if k is more than the pivot index 
	else
	{
		return quickselect(nums, pIndex + 1, right, k);
	}
}


int main()
{
	int nums[] = { 7, 4, 6, 3, 9, 1 };
	int k = 2;

	printf("k'th smallest element is %d", quickselect(nums, 0, N - 1, k - 1));


	return 0;
}

/*

*/