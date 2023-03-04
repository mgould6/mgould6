#include "Header.h";

using namespace std;

/*
Longest Alternating Subsequence Problem
Google Translate Icon
The longest alternating subsequence is a problem of finding a subsequence of a given sequence in which the elements are in alternating order and in which the sequence is as long as possible. In order words, we need to find the length of the longest subsequence with alternate low and high elements.

For example, consider array A[] = [8, 9, 6, 4, 5, 7, 3, 2, 4]. The longest alternating subsequence length is 6, and the subsequence is [8, 9, 6, 7, 3, 4] as (8 < 9 > 6 < 7 > 3 < 4).

Note that the longest alternating subsequence is not unique. Following are a few more subsequences of length 6:

(8, 9, 6, 7, 2, 4)
(8, 9, 4, 7, 3, 4)
(8, 9, 4, 7, 2, 4)
…
…
And many more…
Practice This Problem

The problem differs from the problem of finding the Longest Alternating Subarray. Unlike subarrays, subsequences are not required to occupy consecutive positions within the original array.


We can use recursion to solve this problem. The idea is to maintain a flag to indicate if the next element in the sequence should be smaller or greater than the previous element. Then for any element A[i] at index i, we have two choices:

Include the element in the subsequence.
If the flag is true and A[i-1] < A[i], include A[i] as next high in the subsequence.
If the flag is false and A[i-1] > A[i], include A[i] as next low in the subsequence.
Then recur for the next element by flipping the flag. If we get the longest subsequence by including the element in the subsequence, update the result.

Exclude the element from subsequence.

Exclude the current element and recur for next element (flag remains same). If we get the longest subsequence by excluding the element from the subsequence, update the result.
The algorithm can be implemented as follows in C++

 vector<int> A = { 8, 9, 6, 4, 5, 7, 3, 2, 4 };

    // Find the longest alternating subsequence
    cout << "The length of the longest alternating subsequence is "
         << findLongestSequence(A);

         The time complexity of the above solution is exponential and occupies space in the call stack.


The LAS problem has an optimal substructure and also exhibits overlapping subproblems. We know that problems with optimal substructure and overlapping subproblems can be solved by dynamic programming, in which subproblem solutions are saved rather than computed repeatedly. This method is demonstrated below in C++, Java, and Python, which follows a top-down approach using Memoization

// Utility function to find the length of the longest alternating subsequence.
// If the `flag` is true, the next element should be greater.
// If the `flag` is false, the next element should be smaller.
int findLongestSequence(vector<int> const& A, int start, int end, bool flag,
    vector<vector<int>>& lookup)
{
    // if the subproblem is seen for the first time, solve it and
    // store its result in the lookup table
    if (lookup[start][flag] == 0)
    {
        int result = 0;
        for (int i = start; i <= end; i++)
        {
            // include `A[i]` as next high in subsequence and flip `flag`
            // for next subsequence
            if (flag && A[i - 1] < A[i]) {
                result = max(result, 1 + findLongestSequence(A, i + 1, end,
                    !flag, lookup));
            }

            // include `A[i]` as next low in subsequence and flip `flag`
            // for next subsequence
            else if (!flag && A[i - 1] > A[i]) {
                result = max(result, 1 + findLongestSequence(A, i + 1, end,
                    !flag, lookup));
            }

            // don't include `A[i]` in subsequence
            else {
                result = max(result, findLongestSequence(A, i + 1, end, flag, lookup));
            }
        }

        lookup[start][flag] = result;
    }

    // return solution to the current subproblem
    return lookup[start][flag];
}

// Function to find the length of the longest subsequence with alternate
// low and high elements. It calls the `findLongestSequence()` method.
int longestSequence(vector<int> const& A)
{
    int n = A.size();

    // base case
    if (n == 0) {
        return 0;
    }

    // Fix the first element and recur for the remaining elements.
    // There are two possibilities:

    // lookup table to store solutions to a subproblem
    // `max(lookup[i][0], lookup[i][1])` stores the longest sequence till `A[0…i]`
    vector<vector<int>> lookup(n + 1, vector<int>(2));

    // 1. The next element is greater (pass true)
    // 2. The next element is smaller (pass false)
    return 1 + max(findLongestSequence(A, 1, n - 1, true, lookup),
        findLongestSequence(A, 1, n - 1, false, lookup));
}


The time complexity of the above top-down solution is O(n2) and requires O(n) extra space, where n is the size of the given sequence. We can even write a bottom-up version of the above memoized solution. The following code shows how to implement it in C:

The time complexity of the above bottom-up solution is O(n2) and requires O(n) extra space, where n is the size of the given sequence.


*/


int max(int x, int y) {
    return (x > y) ? x : y;
}

// Function to find the length of the longest subsequence with alternate
// low and high elements.
int findLongestSequence(int A[], int n)
{
    // base case
    if (n <= 1) {
        return n;
    }

    // lookup table to store solutions to subproblems
    int** T = new int* [n];
    for (int i = 0; i < n; i++)
        T[i] = new int[2];
    /*
        `T[i][0]` stores the longest alternating subsequence till `A[0…i]`
        where `A[i]` is greater than `A[i-1]`

        `T[i][1]` stores the longest alternating subsequence till `A[0…i]`
        where `A[i]` is smaller than `A[i-1]`
    */

    // initialize matrix
    for (int i = 1; i < n; i++) {
        T[i][0] = T[i][1] = 0;
    }

    // base case: the first element will always be part of LAS
    T[0][0] = T[0][1] = 1;

    // stores result
    int result = 1;

    // fill the lookup table in a bottom-up manner
    for (int i = 1; i < n; i++)
    {
        // do for each element `A[j]` before `A[i]`
        for (int j = 0; j < i; j++)
        {
            // If `A[i]` is greater than `A[j]`, update `T[i][0]`
            if (A[i] > A[j]) {
                T[i][0] = max(T[i][0], T[j][1] + 1);
            }

            // If `A[i]` is smaller than `A[j]`, update `T[i][1]`
            if (A[i] < A[j]) {
                T[i][1] = max(T[i][1], T[j][0] + 1);
            }
        }

        // update result by taking a maximum of both values
        if (result < max(T[i][0], T[i][1])) {
            result = max(T[i][0], T[i][1]);
        }
    }

    // return result
    return result;
}

int main(void)
{
    int A[] = { 8, 9, 6, 4, 5, 7, 3, 2, 4 };
    int n = sizeof(A) / sizeof(A[0]);

    printf("The length of the longest alternating subsequence is %d",
        findLongestSequence(A, n));

    return 0;
}

/*

*/