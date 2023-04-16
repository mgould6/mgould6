#include "Header.h";

using namespace std;

/*
Hybrid QuickSort Algorithm

Quicksort with Insertion Sort
When the total number of elements is below some threshold (perhaps ten elements), switch to a non-recursive sorting algorithm such as insertion sort that performs fewer swaps, comparisons, or other operations on such small arrays. This approach is discussed here.

Instead of “many small sorts” optimization, the idea is to stop when the total number of elements is less than some threshold k. Later, when the whole array has been processed, each element will be at most k positions away from its final sorted position. Now, if we perform insertion sort on it, it will take O(k.n) time to finish the sort, which is linear as k is a constant.

Following is the C++

The optimal cut-off for switching from Quicksort to Insertion sort is taken as 10 in the above program. As demonstrated by running the optimized and non-optimized Quicksort 10 times on 1 million elements (in C++ version) and taking an average of time taken by each, we can say that the optimized version is much faster than the non-optimized Quicksort.


Note if the input contains many repeated elements, Quicksort exhibits poor performance even with optimizations discussed above. We can use an alternative linear-time partition routine (sometimes called the Dutch national flag problem) to solve this problem that separates the values into three groups: values less than the pivot, values equal to the pivot, and values greater than the pivot. We have discussed this approach here.


*/

//total number of elements to be sorted
#define N 100000

//total number of sorting runs
#define NUM 10

//function to perform insertion sort on arr[]
void insertionSort(int arr[], int low, int n)
{
	//start from the second element (the element at index 0 is already sorted
	for (int i = low + 1; i <= n; i++)
	{
		int value = arr[i];
		int j = i;

		//find index j within sorted subset arr[0...i-1]
		//where element arr[i] belongs
		while (j > low && arr[j - 1] > value)
		{
			arr[j] = arr[j - 1];
			j--;
		}
		//note that subarray arr[j..i-1] is shifted to
		//the right by one position arr[j+1...i]
		arr[j] = value;
	}
}

int partition(int a[], int low, int high)
{
	//pick the rightmost element as a pivot from the array
	int pivot = a[high];

	//elements less than the pivot will be pushed to the left of pIndex
	//elements more than the pivot will be pushed to the right of pIndex
	//equal elements can go either way
	int pIndex = low;

	//each time we find an element less than or equal to the pivot, pIndex
	//is incremented and that element would be placed before the pivot
	for (int i = low; i < high; i++)
	{
		if (a[i] <= pivot)
		{
			swap(a[i], a[pIndex]);
			pIndex++;
		}
	}
	//swap pIndex with pivot
	swap(a[pIndex], a[high]);

	return pIndex;
}

void quicksort(int a[], int low, int high)
{
	//base condition
	if (low >= high)
	{
		return;
	}

	//rearrange elements across pivot
	int pivot = partition(a, low, high);

	//recur on subarray containing elements that are less than the pivot
	quicksort(a, low, pivot - 1);

	//recur on subarray containing elements that are more than the pivot
	quicksort(a, pivot + 1, high);
}

void optimizedQuicksort(int A[], int low, int high)
{
	while (low < high)
	{
		//switch to insertion sort if the size is 10 or smaller
		if (high - low < 10)
		{
			insertionSort(A, low, high);
			break;
		}
		else
		{
			int pivot = partition(A, low, high);

			//tail call optimizations - recur on the smaller subarray
			if (pivot - low < high - pivot)
			{
				optimizedQuicksort(A, low, pivot - 1);
				low = pivot + 1;
			}
			else
			{
				optimizedQuicksort(A, pivot + 1, high);
				high = pivot - 1;
			}
		}
	}
}


int main()
{
	int arr[N], dup[N];

	//seed for random input
	srand(time(NULL));

	//to measure the time taken by optimized and non optimized quicksort
	clock_t begin, end;
	double t1 = 0.0, t2 = 0.0;

	//perform quicksort NUM times and take an average
	for (int i = 0; i < NUM; i++)
	{
		//generate random input
		for (int i = 0; i < N; i++)
		{
			dup[i] = arr[i] = rand() % 100000;
		}

		//perform non optimized quicksort on the array
		begin = clock();
		quicksort(arr, 0, N - 1);
		end = clock();

		//calculate the time taken by non optimized quicksort
		t1 += (double)(end - begin) / CLOCKS_PER_SEC;

		//perform optimized quicksort on the duplicate array
		begin = clock();
		optimizedQuicksort(dup, 0, N - 1);
		end = clock();

		//calculate the time taken by optimized quicksort
		t2 += (double)(end - begin) / CLOCKS_PER_SEC;
	}

	cout << "the average time taken by non optimized quicksort: " << t1 / NUM;
	cout << "\nthe average time taken by optimized quicksort: " << t2 / NUM;

	return 0;
}

/*

*/