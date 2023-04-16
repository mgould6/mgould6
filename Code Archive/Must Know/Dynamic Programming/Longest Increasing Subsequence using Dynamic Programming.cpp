#include "Header.h";

using namespace std;

/*
Longest Increasing Subsequence using Dynamic Programming
Google Translate Icon
The longest increasing subsequence problem is to find a subsequence of a given sequence in which the subsequence’s elements are in sorted order, lowest to highest, and in which the subsequence is as long as possible. This subsequence is not necessarily contiguous or unique.

Please note that the problem specifically targets subsequences that need not be contiguous, i.e., subsequences are not required to occupy consecutive positions within the original sequences.

For example, the longest increasing subsequence of [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15] is [0, 2, 6, 9, 11, 15].

This subsequence has length 6; the input sequence has no 7–member increasing subsequences. The longest increasing subsequence in this example is not unique.

For instance, [0, 4, 6, 9, 11, 15] or [0, 4, 6, 9, 13, 15] are other increasing subsequences of equal length in the same input sequence.


Practice This Problem


The idea is to use recursion to solve this problem. For each item, there are two possibilities:

Include the current item in LIS if it is greater than the previous element in LIS and recur for the remaining items.
Exclude the current item from LIS and recur for the remaining items.
Finally, return the maximum value we get by including or excluding the current item. The base case of the recursion would be when no items are left. Following is the C++, Java, and Python implementation of the idea:

// Function to find the length of the longest increasing subsequence
int LIS(int arr[], int i, int n, int prev)
{
    // base case nothing is remaining
    if (i == n)
    {
        return 0;
    }

    // case 1 exclude the current element and process the remaining elements
    int excl = LIS(arr, i + 1, n, prev);

    // case 2 include the current element if it is greater
    // than the previous element in LIS
    int incl = 0;

    if (arr[i] > prev)
    {
        incl = 1 + LIS(arr, i + 1, n, arr[i]);
    }

    // return the maximum of the above two choices
    return max(incl, excl);
}

The time complexity of the above solution is O(n2) and requires O(n2) extra space, where n is the size of the given sequence.


Refer to the following post for the O(n.log(n)) solution to find the length and print longest increasing subsequence.

Longest Increasing Subsequence Problem

The time complexity of the above solution is O(n2) and requires O(n) extra space, where n is the size of the given sequence.

How to print LIS?

The above-discussed methods only print the length of LIS but do not print LIS itself. To print the LIS, we have to store the longest increasing subsequence in the lookup table instead of storing just the LIS length.

For example, consider array arr = [ 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]. The longest increasing subsequence of subarray arr[0…i] that ends with arr[i] are:

LIS[0] — 0
LIS[1] — 0 8
LIS[2] — 0 4
LIS[3] — 0 8 12
LIS[4] — 0 2
LIS[5] — 0 8 10
LIS[6] — 0 4 6
LIS[7] — 0 8 12 14
LIS[8] — 0 1
LIS[9] — 0 4 6 9
LIS[10] — 0 4 5
LIS[11] — 0 4 6 9 13
LIS[12] — 0 2 3
LIS[13] — 0 4 6 9 11
LIS[14] — 0 4 6 7
LIS[15] — 0 4 6 9 13 15
Following is the C++
The time complexity of the above solution is O(n2) and requires O(n2) extra space, where n is the size of the given sequence.


Refer to the following post for the O(n.log(n)) solution to find the length and print longest increasing subsequence.

Longest Increasing Subsequence Problem
*/

// Iterative function to find the longest increasing subsequence
// of a given array
void findLIS(vector<int> const& arr)
{
    int n = arr.size();

    // base case
    if (n == 0) {
        return;
    }

    // LIS[i] stores the longest increasing subsequence of subarray
    // `arr[0…i]` that ends with `arr[i]`
    vector<vector<int>> LIS(n, vector<int>{});

    // LIS[0] denotes the longest increasing subsequence ending at `arr[0]`
    LIS[0].push_back(arr[0]);

    // start from the second array element
    for (int i = 1; i < n; i++)
    {
        // do for each element in subarray `arr[0…i-1]`
        for (int j = 0; j < i; j++)
        {
            // find the longest increasing subsequence that ends with `arr[j]`
            // where `arr[j]` is less than the current element `arr[i]`

            if (arr[j] < arr[i] && LIS[j].size() > LIS[i].size()) {
                LIS[i] = LIS[j];
            }
        }

        // include `arr[i]` in `LIS[i]`
        LIS[i].push_back(arr[i]);
    }

    // uncomment the following code to print contents of `LIS`
    /* for (int i = 0; i < n; i++)
    {
        cout << "LIS[" << i << "] — ";
        for (int j: LIS[i]) {
            cout << j << " ";
        }
        cout << endl;
    } */

    // `j` will store the index of LIS
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (LIS[j].size() < LIS[i].size()) {
            j = i;
        }
    }

    // print LIS
    for (int i : LIS[j]) {
        cout << i << " ";
    }
}

int main()
{
    vector<int> arr = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

    findLIS(arr);
    return 0;
}

/*

*/