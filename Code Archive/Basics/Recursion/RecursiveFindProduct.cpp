#include "Header.h";

using namespace std;

/*
Replace every array element with the product of every other element without using a division operator
Given an integer array, replace each element with the product of every other element without using the division operator.

For example,

Input:  { 1, 2, 3, 4, 5 }
Output: { 120, 60, 40, 30, 24 }


Input:  { 5, 3, 4, 2, 6, 8 }
Output: { 1152, 1920, 1440, 2880, 960, 720 }
Practice This Problem

We can use recursion to solve this problem in linear time and constant space. The idea is to recursively calculate all elements’ products in the right subarray and pass the left-subarray product in function arguments. Following is the C, Java, and Python program that demonstrates it:


*/

//recursive function to replace each element of the array with the product
//of every other element without using the division operator
int findProduct(int arr[], int n, int left, int i)
{

	//base case: no elements left on the right
	if (i == n)
	{
		return 1;
	}

	//take backup of current element

	int curr = arr[i];
	//calculate the product of the right subarray
	int right = findProduct(arr, n, left * arr[i], i + 1);

	arr[i] = left * right;

	return curr * right;

}


int main()
{
	int arr[] = { 5, 3, 4, 2, 6, 8 };
	int n = sizeof(arr) / sizeof(arr[0]);

	findProduct(arr, n, 1, 0);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

