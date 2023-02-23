#include "Header.h";

using namespace std;

/*
Longest Bitonic Subarray Problem

The Longest Bitonic Subarray (LBS) problem is to find a subarray of a given sequence in which the subarray’s elements are first sorted in increasing order, then in decreasing order, and the subarray is as long as possible. Strictly ascending or descending subarrays are also accepted.

For example,

Longest bitonic subarray of the sequence { 3, 5, 8, 4, 5, 9, 10, 8, 5, 3, 4 } is { 4, 5, 9, 10, 8, 5, 3 }

For sequences sorted in increasing or decreasing order, the output is the same as the input sequence, i.e.,

[1, 2, 3, 4, 5] ——> [1, 2, 3, 4, 5]
[5, 4, 3, 2, 1] ——> [5, 4, 3, 2, 1]

We can solve this problem without using extra space. The idea is to check for the longest bitonic subarray starting at A[i]. If the longest bitonic subarray starting at A[i] ends at A[j], the trick is to skip all elements between i and j as the longest bitonic subarray starting from them will have less length. Next, check for the longest bitonic subarray starting at A[j]. We continue this process until the end of the array is reached and keep track of the longest bitonic subarray found so far.

Following is the C



*/

void findBitonicSubarray(int A[], int n)
{
    int end_index = 0, max_len = 1, i = 0;

    while (i + 1 < n)
    {
        // check for the longest bitonic subarray starting at `A[i]`

        // reset length to 1
        int len = 1;

        // run till sequence is increasing
        while (i + 1 < n && A[i] < A[i + 1]) {
            i++, len++;
        }

        // run till sequence is decreasing
        while (i + 1 < n && A[i] > A[i + 1]) {
            i++, len++;
        }

        // run till sequence is equal
        while (i + 1 < n && A[i] == A[i + 1]) {
            i++;
        }

        // update the longest bitonic subarray if required
        if (len > max_len)
        {
            max_len = len;
            end_index = i;
        }
    }

    // print the longest bitonic subarray
    printf("The length of the longest bitonic subarray is %d\n", max_len);
    printf("The longest bitonic subarray indices is [%d, %d]",
        end_index - max_len + 1, end_index);
}



int main()
{
    int arr[] = { 3, 5, 8, 4, 5, 9, 10, 8, 5, 3, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    findBitonicSubarray(arr, n);

    return 0;
}

