#include "Header.h";

using namespace std;

/*
Right rotate an array `k` times

In this post, we will see how to right-rotate an array

by specified positions. For example, right rotating

array { 1, 2, 3, 4, 5, 6, 7 } three times will result in array { 5, 6, 7, 1, 2, 3, 4 }.

By reversing array
We can even solve this problem in O(n) time and O(1) extra space. The idea is to reverse the last k elements of the input array and then reverse the remaining n-k elements. Finally, get the right-rotated array by reversing the complete array.


*/


//function to reverse a given subarray
void reverse(int arr[], int low, int high)
{

	for (int i = low, j = high; i < j; i++, j--)
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

//function to right rotate an array by k positions
void rightRotate(int arr[], int k, int n)
{

	// base case: invalid input
	if (k < 0 || k >= n) {
		return;
	}

	//reverse the last 'k' elements
	reverse(arr, n - k, n - 1);

	//reverse the first 'n-k' elements
	reverse(arr, 0, n - k - 1);

	//reverse the whole array
	reverse(arr, 0, n - 1);


}


int main()
{

	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int k = 1;

	if (k >= n)
	{
		cout << "Please restart program and choose a # of rotations < n";
		return 0;
	}
	rightRotate(arr, k, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}





/*

The idea is to right-rotate all array elements by one position k times, where k is the given rotation count. This approach is demonstrated below in C

The time complexity of the above solution is O(n.k), where n is the size of the input and k is the rotation count.

*/



//void rightRotateByOne(int arr[], int n)
//{
//
//	int end = arr[n - 1];
//	int start = arr[0];
//
//	for (int i = n - 2; i >= 0; i--)
//	{
//		//rotate the array to the right the number of times 
//		//specified in the rotations parameter
//		arr[i + 1] = arr[i];
//	}
//
//	arr[0] = end;
//
//}
//
//void rightRotate(int arr[], int k, int n)
//{
//
//	//base case: invalid input
//	if (k < 0 || k >= n)
//	{
//		return;
//	}
//
//	for (int i = 0; i < k; i++)
//	{
//		rightRotateByOne(arr, n);
//	}
//
//}