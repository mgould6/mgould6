#include "Header.h";

using namespace std;

/*
Maximum Product Subarray Problem
Given an integer array, find the subarray that has the maximum product of its elements. The solution should return the maximum product of elements among all possible subarrays.

For example,

Input:  { -6, 4, -5, 8, -10, 0, 8 }
Output: 1600
Explanation: The maximum product subarray is {4, -5, 8, -10} having product 1600


Input:  { 40, 0, -20, -10 }
Output: 200
Explanation: The maximum product subarray is {-20, -10} having product 200
Practice This Problem

The problem differs from the problem of finding the maximum product subsequence. Unlike subsequences, subarrays are required to occupy consecutive positions within the original array.


A naive solution would be to consider every subarray and find the product of their elements. Finally, return the maximum product found among all subarrays. The implementation can be seen here. The time complexity of this solution is O(n2), where n is the size of the input.


A better solution will be to maintain two variables to store the maximum and minimum product ending in the current position. Then traverse the array once, and for every index i in the array, update the maximum and minimum product ending at A[i]. Update the result if the maximum product ending at any index is more than the maximum product found so far.

Following is the C,
*/

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int max(int x, int y)
{
    return (x > y) ? x : y;
}

int findMaxProduct(int arr[], int n)
{
    if (n == 0)
    {
        return 0;
    }

    //maintain two variables to store the maximum and minimum product ending at the current index
    int max_ending = arr[0], min_ending = arr[0];

    //store the maximum product subarray so far
    int max_so_far = arr[0];

    //traverse array
    for (int i = 1; i < n; i++)
    {
        int temp = max_ending;

        //update the maximum product ending at the current inddex
        max_ending = max(arr[i], max(arr[i] * max_ending, arr[i] * min_ending));

        //update the minimum product ending at the current index
        min_ending = min(arr[i], min(arr[i] * temp, arr[i] * min_ending));

        max_so_far = max(max_so_far, max_ending);

    }

    //return maximum product

    return max_so_far;
}


int main()
{

    int arr[] = { -6, 4, -5, 8, -10, 0, 8 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("The maximum product of a subarray is %d",
        findMaxProduct(arr, n));


    return 0;
}

