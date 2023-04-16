#include "Header.h";

using namespace std;

/*
Find minimum sum subarray of size `k`
Given an integer array, find the minimum sum subarray of size k, where k is a positive integer.

For example,

Input:  {10, 4, 2, 5, 6, 3, 8, 1}, k = 3

Output: Minimum sum subarray of size 3 is (1, 3)
Practice This Problem

The problem differs from the problem of finding the minimum sum subsequence of size k. Unlike subsequences, subarrays are required to occupy consecutive positions within the original array.


We can solve this problem by using the sliding window technique. The idea is to maintain a window of size k. For every array element, include it in the window and remove the window’s leftmost element if the window size is more than k. Also maintain the sum of elements in the current window. If the sum of the current window is less than the minimum found so far, update the minimum sum to the current window sum and store the window’s endpoints.

The algorithm can be implemented as follows in C

The time complexity of the above solution is O(n) and doesn’t require any extra space, where n is the size of the input.


*/

void findSubarray(int arr[], int n, int k)
{
    // base case 
    if (n == 0 || n <= k)
    {
        return;
    }

    // stores the sum of elements in the current window
    int window_sum = 0;

    // stores the sum of minimum sum subarray found so far
    int min_window = INT_MAX;

    // stores ending index of the minimum sum subarrray found so far
    int last = 0;

    for (int i = 0; i < n; i++)
    {
        // add the current element to the window
        window_sum += arr[i];

        // if the window size is more than equal to k 
        if (i + 1 >= k)
        {
            //update the minimum sum window
            if (min_window > window_sum)
            {
                min_window = window_sum;
                last = i;
            }
            // remove a leftmost element from the window
            window_sum -= arr[i + 1 - k];
        }
    }
    printf("The minimum subarray is (%d, %d)", last - k + 1, last);
}

int main()
{
    int arr[] = { 10, 4, 2, 5, 6, 3, 8, 1 };
    int k = 3;

    int n = sizeof(arr) / sizeof(arr[0]);

    findSubarray(arr, n, k);

    return 0;
}

/*

*/