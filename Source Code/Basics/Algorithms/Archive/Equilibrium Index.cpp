#include "Header.h";

using namespace std;

/*
Find equilibrium index of an array
Given an integer array, find the equilibrium index in it.

For an array A consisting n elements, index i is an equilibrium index if the sum of elements of subarray A[0…i-1] is equal to the sum of elements of subarray A[i+1…n-1]. i.e.

(A[0] + A[1] + … + A[i-1]) = (A[i+1] + A[i+2] + … + A[n-1]), where 0 < i < n-1

Similarly, 0 is an equilibrium index if A[1] + A[2] + … + A[n-1] sums to 0 and n-1 is an equilibrium index if A[0] + A[1] + … + A[n-2] sums to 0.


To illustrate, consider the array {0, -3, 5, -4, -2, 3, 1, 0}. The equilibrium index is found at index 0, 3, and 7.


Optimized Solution
We can avoid using extra space. The idea is to calculate the sum of all the array elements. Then start from the last item of the array and maintain the right subarray sum. We can calculate the left subarray sum in constant time by subtracting the right subarray sum and current element from the total sum, i.e.,

Sum of left subarray A[0…i-1] = total – (A[i] + sum of right subarray A[i+1…n-1])


*/

void equilIndexFinder(int arr[], int n)
{
	int total = accumulate(arr, arr + n, 0);
	int left = 0;
	int right = 0;

	for (int i = n - 1; i >= 0; i--)
	{
		if (right == total - (arr[i] + right))
		{
			cout << "Equilibrium index at: " << i << endl;
		}

		right += arr[i];
	}


}

int main()
{
	int arr[] = { 0, -3, 5, -4, -2, 3, 1, 0 };
	int n = sizeof(arr) / sizeof(arr[0]);

	equilIndexFinder(arr, n);

	return 0;
}

