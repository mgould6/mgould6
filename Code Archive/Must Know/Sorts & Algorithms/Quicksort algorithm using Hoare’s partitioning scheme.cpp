#include "Header.h";

using namespace std;

/*
Quicksort algorithm using Hoare’s partitioning scheme

Implement the Quicksort algorithm using Hoare’s Partitioning scheme.

As the Lomuto partition scheme is more compact and easy to understand, it is frequently used in the partition process of Quicksort. But this scheme degrades to O(n2) when the array is already sorted or when the array has all equal elements. In this post, a much more efficient Hoare partition scheme is discussed.

Hoare Partition Scheme
Hoare uses two indices that start at the ends of the array being partitioned, then move toward each other until they detect an inversion: a pair of elements, one greater than the pivot, one smaller, in the wrong order relative to each other. The inverted elements are then swapped. When the indices meet, the algorithm stops and returns the final index.

Hoare’s scheme is more efficient than Lomuto’s partition scheme because it does three times fewer swaps on average, and it creates efficient partitions even when all values are equal. But like Lomuto’s partition scheme, Hoare partitioning also causes Quicksort to degrade to O(n2) when the input array is already sorted; it also doesn’t produce a stable sort.

Note that in this scheme, the pivot’s final location is not necessarily at the index that was returned, and the next two segments that the main algorithm recurs on are [low…pivot] and [pivot+1…high] as opposed to [low…pivot-1] and [pivot+1…high] as in Lomuto’s scheme.

Practice This Algorithm

The algorithm can be implemented as follows in C++
*/

#define N 15

//partition using hoares partitioning scheme
int partition(int a[], int low, int high)
{
	int pivot = a[low];
	int i = low - 1;
	int j = high + 1;
	while (1)
	{
		do {
			i++;
		} while (a[i] < pivot);
		do {
			j--;
		} while (a[j] > pivot);
		if (i >= j)
		{
			return j;
		}
		swap(a[i], a[j]);
	}
}

//quicksort routine
void quicksort(int a[], int low, int high)
{
	//base condition
	if (low >= high)
	{
		return;
	}

	//rearrange elements across pivot
	int pivot = partition(a, low, high);

	//recur on subarray containing elements less than the pivot
	quicksort(a, low, pivot);

	//recur on subarray containing elements that are more than the pivot
	quicksort(a, pivot + 1, high);
}

int main()
{
	int arr[N];
	srand(time(NULL));

	//generate random input of integers
	for (int i = 0; i < N; i++)
	{
		arr[i] = (rand() % 100) - 50;
	}

	quicksort(arr, 0, N - 1);

	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}

/*

*/