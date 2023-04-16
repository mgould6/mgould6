#include "Header.h";

using namespace std;

/*
Rearrange an array with alternate high and low elements
Given an integer array, rearrange it such that every second element becomes greater than its left and right elements. Assume no duplicate elements are present in the array.

For example,

Input:  {1, 2, 3, 4, 5, 6, 7}
Output: {1, 3, 2, 5, 4, 7, 6}

Input:  {9, 6, 8, 3, 7}
Output: {6, 9, 3, 8, 7}

Input:  {6, 9, 2, 5, 1, 4}
Output: {6, 9, 2, 5, 1, 4}
Practice This Problem

A simple solution would be to sort the array in ascending order first. Then take another auxiliary array and fill it with elements starting from the sorted array’s two endpoints in alternate order. Following is the complete algorithm:

RearrangeArray(arr[], n)

Sort the array in ascending order.
Take two index variables i and j to that point to two endpoints of the array (i.e., i = 0 and j = n-1).
Create an auxiliary array A[] and initialize an index k with 0.
Do while (i < j)
    A[k++] = arr[i++]
    A[k++] = arr[j–]
Print A[].

The time complexity of this solution is O(n.log(n)) and doesn’t require any extra space, where n is the size of the input.


An efficient solution doesn’t involve sorting the array or the use of extra space. The idea is to start from the second array element and increment the index by 2 for each loop’s iteration. If the last element is greater than the current element, swap the elements. Similarly, if the next element is greater than the current element, swap both elements. At the end of the loop, we will get the desired array that satisfies given constraints.

Following is the implementation in C
*/
// Utility function to swap elements `arr[i]` and `arr[j]` in an array

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

}

void sortArray(int arr[], int n)
{
    for (int i = 1; i < n; i += 2)
    {
        //if the previous element is greater than the current element swap the elements
        if (arr[i - 1] > arr[i])
        {
            swap(arr, i - 1, i);
        }

        //if the next element is greater than the current element 
        //swap elements
        if (arr[i + 1] > arr[i])
        {
            swap(arr, i + 1, i);
        }
    }
}

int main()
{

    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    sortArray(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}

