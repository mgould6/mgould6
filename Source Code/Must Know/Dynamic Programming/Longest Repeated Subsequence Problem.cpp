#include "Header.h";

using namespace std;

/*
Longest Repeated Subsequence Problem
Google Translate Icon
The Longest Repeating Subsequence (LRS) problem is finding the longest subsequences of a string that occurs at least twice.

The problem differs from the problem of finding the longest repeating substring. Unlike substrings, subsequences are not required to occupy consecutive positions within the original string.


For example, consider the sequence ATACTCGGA.

The length of the longest repeating subsequence is 4
The longest repeating subsequence is ATCG

A T A C T C G G A
A T A C T C G G A

Note that repeated characters holds a different index in the input string.
Practice This Problem

The longest repeating subsequence problem is a classic variation of the Longest Common Subsequence (LCS) problem. The idea is to find the LCS of the given string with itself, i.e., call LCS(X, X) and exclude the cases when indexes are the same (i = j) since repeated characters hold a different index in the input string.

The LRS problem has optimal substructure. We can recursively define the problem as:

            | 0                                    (if i = 0 or j = 0)
LRS[i][j] = | LRS[i-1][j-1] + 1                    (if X[i-1] = X[j-1] & i!=j)
            | max (LRS[i-1][j], LRS[i][j-1])       (if X[i-1] != X[j-1])
The following implementation in C++, Java, and Python recursively finds the length of the longest repeated subsequence of a sequence using the optimal substructure property of the LRS problem:

// Function to find the length of the longest repeated subsequence
// of substring `X[0…m-1]` and `X[0…n-1]`
int LRSLength(string X, int m, int n, unordered_map<string, int>& lookup)
{
    // return if the end of either string is reached
    if (m == 0 || n == 0) {
        return 0;
    }

    // construct a unique map key from dynamic elements of the input
    string key = to_string(m) + "|" + to_string(n);

    // if the subproblem is seen for the first time, solve it and
    // store its result in a map
    if (lookup.find(key) == lookup.end())
    {
        // if characters at index `m` and `n` matches and the index are different
        if (X[m - 1] == X[n - 1] && m != n) {
            lookup[key] = LRSLength(X, m - 1, n - 1, lookup) + 1;
        }
        else {
            // otherwise, if characters at index `m` and `n` don't match
            lookup[key] = max(LRSLength(X, m, n - 1, lookup),
                LRSLength(X, m - 1, n, lookup));
        }
    }

    // return the subproblem solution from the map
    return lookup[key];
}

The time complexity of the above top-down solution is O(n2) and requires O(n2) extra space, where n is the length of the input string.



The above memoized version follows the top-down approach since we first break the problem into subproblems and then calculate and store values. We can also solve this problem in a bottom-up manner by calculating the smaller values of LRS(i, j) first and then building larger values from them. This is demonstrated below in C++


// Function to find the length of the longest repeated subsequence
// of substring `X[0…n-1]`
int LRSLength(string X, int n)
{
    // lookup table stores solution to already computed subproblems;
    // i.e., lookup[i][j] stores the length of LRS of substring
    // `X[0…i-1]` and `X[0…j-1]`

    //allocate the array
    int** lookup = new int* [n + 1];
    for (int i = 0; i < n + 1; i++)
        lookup[i] = new int[n + 1];


    // first column of the lookup table will be all 0
    for (int i = 0; i <= n; i++) {
        lookup[i][0] = 0;
    }

    // first row of the lookup table will be all 0
    for (int j = 0; j <= n; j++) {
        lookup[0][j] = 0;
    }

    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if characters at index `i` and `j` matches
            // and the index are different
            if (X[i - 1] == X[j - 1] && i != j) {
                lookup[i][j] = lookup[i - 1][j - 1] + 1;
            }
            // otherwise, if characters at index `i` and `j` are different
            else {
                lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1]);
            }
        }
    }

    // LRS will be the last entry in the lookup table
    return lookup[n][n];
}

The time complexity of the above bottom-up solution is O(n2) and requires O(n2) extra space, where n is the length of the input string. The space complexity of the above solution can be improved to O(n) as calculating the LRS of a row of the LRS table requires only the solutions to the current row and the previous row.

How to extend the above solution for printing the longest repeating subsequence?

The idea is very similar to printing the Longest Common Subsequence (LCS) of two strings. Refer to this post for details.

This approach is demonstrated below in C++

*/

// Function to find LRS of substrings `X[0…m-1]`, `X[0…n-1]`
string LRS(string X, int m, int n, vector<vector<int>>& lookup)
{
    // if the end of either sequence is reached,
    // return an empty string
    if (m == 0 || n == 0) {
        return string("");
    }

    // if characters at index `m` and `n` matches and the index are different
    if (X[m - 1] == X[n - 1] && m != n) {
        return LRS(X, m - 1, n - 1, lookup) + X[m - 1];
    }
    // otherwise, if characters at index `m` and `n` don't match
    else {
        if (lookup[m - 1][n] > lookup[m][n - 1]) {
            return LRS(X, m - 1, n, lookup);
        }
        else {
            return LRS(X, m, n - 1, lookup);
        }
    }
}

// Function to fill the lookup table by finding the length of LRS
// of substring `X[0…n-1]`
void LRSLength(string X, int n, vector<vector<int>>& lookup)
{
    // first row and first column of the lookup table is already 0

    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if characters at index `i` and `j` matches
            // and the index are different
            if (X[i - 1] == X[j - 1] && i != j) {
                lookup[i][j] = lookup[i - 1][j - 1] + 1;
            }
            // otherwise, if characters at index `i` and `j` are different
            else {
                lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1]);
            }
        }
    }
}

int main()
{
    string X = "ATACTCGGA";

    int n = X.length();

    // lookup[i][j] stores the length of LRS of substring `X[0…i-1]` and `X[0…j-1]`
    vector<vector<int>> lookup(n + 1, vector<int>(n + 1));

    // fill lookup table
    LRSLength(X, n, lookup);

    // find the longest repeating subsequence
    cout << "The longest repeating subsequence is " << LRS(X, n, n, lookup);

    return 0;
}

/*

*/