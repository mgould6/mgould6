#include "Header.h";

using namespace std;

/*
Shortest Common Supersequence Problem
Google Translate Icon
The Shortest Common Supersequence (SCS) is finding the shortest supersequence Z of given sequences X and Y such that both X and Y are subsequences of Z.

The problem differs from the problem of finding the shortest common substring. Unlike substrings, subsequences are not required to occupy consecutive positions within the original string.

For example, consider the two following sequences, X and Y:

X: ABCBDAB
Y: BDCABA

The length of the SCS is 9
The SCS are ABCBDCABA, ABDCABDAB, and ABDCBDABA
Practice This Problem

The SCS problem has optimal substructure. That means the problem can be broken down into smaller, simple “subproblems”, which can be broken down into yet simpler subproblems, and so on, until, finally, the solution becomes trivial.

1. Let’s consider two sequences, X and Y of length m and n, respectively, that both end in the same element.

To find their SCS, shorten each sequence by removing the last element, find the SCS of the shortened sequences, and that SCS append the removed element. So, we can say that.

SCS(X[1…m], Y[1…n]) = SCS(X[1…m-1], Y[1…n-1]) + X[m]        if X[m] = Y[n]
For example,

SCS(ABCBDA, BDCABA) = SCS(ABCBD, BDCAB) + A
SCS(ABCBDAB, BDCAB) = SCS(ABCBDA, BDCA) + B
2. Now suppose that the two sequences do not end in the same element.

Then the SCS of X and Y is the shorter of the two sequences SCS(X[1…m-1], Y[1…n]) + X[m] and SCS(X[1…m], Y[1…n-1]) + Y[n]. To understand this property, let’s consider the two following sequences:

X: ABCBDAB (n elements)
Y: BDCABA (m elements)
The SCS of these two sequences either ends with B (the last element of sequence X) or A (the last element of sequence Y).

Case 1: If SCS ends with B, add B from sequence X to SCS and the problem reduces to SCS(X[1…m-1], Y[1…n]) + X[m].


Case 2: If SCS does not end with B, that means it ends with A, add A from sequence Y to SCS and the problem reduces to SCS(X[1…m], Y[1…n-1]) + Y[n].

For example,

SCS(ABCBD, BDCAB) = minimum (SCS(ABCB, BDCAB) + D, SCS(ABCBD, BDCA) + B)
The following solution in C++, Java, and Python find the shortest common supersequence of sequences X[0…m-1] and Y[0…n-1] recursively using the optimal substructure property of the SCS problem:

// Function to find the length of the shortest common supersequence of
// sequences X[0...m-1] and Y[0...n-1]
int SCSLength(string X, string Y, int m, int n)
{
    // if the end of either sequence is reached return
    // the length of another sequence
    if (m == 0 || n == 0)
    {
        return n + m;
    }

    // if the last character of X and Y matches
    if (X[m - 1] == Y[n - 1])
    {
        return SCSLength(X, Y, m - 1, n - 1) + 1;
    }
    else
    {
        // otherwise if the last character of X and Y don't match
        return min(SCSLength(X, Y, m, n - 1) + 1,
            SCSLength(X, Y, m - 1, n) + 1);
    }
}


The worst-case time complexity of the above solution is O(2(m+n)) and occupies space in the call stack where m is the length of the first string and n is the length of the second string. The worst case happens when there is no common character present in X and Y (i.e., SCS length is m+n), and each recursive call will end up in two recursive calls.




The SCS problem exhibits overlapping subproblems. Let’s consider the recursion tree for two sequences of length 6 and 8 whose SCS length is 6 + 8 = 14. As we can see, the same subproblems (highlighted in the same color) are getting computed repeatedly:

shortest common supersequence


The problems having optimal substructure and overlapping subproblems can be solved by dynamic programming, in which subproblem solutions are memoized rather than computed repeatedly. Following is a memoized version that follows the top-down approach, as we first break the problem into subproblems and then calculate and store values:


// function to find the length of the shortest common supersequence of
// sequences X[0…m-1]` and `Y[0…n-1]`
int SCSLength(string X, string Y, int m, int n, unordered_map<string, int>& lookup)
{
    // if the end of either sequence is reached return
    // the length of another sequence
    if (m == 0 || n == 0)
    {
        return n + m;
    }

    // construct a unique map key from dynamic elements of the input
    string key = to_string(m) + "|" + to_string(n);

    // if the subproblem is seen for the first time solve it
    // and store its result in a map
    if (lookup.find(key) == lookup.end())
    {
        // if the last character of X and Y matches
        if (X[m - 1] == Y[n - 1])
        {
            lookup[key] = SCSLength(X, Y, m - 1, n - 1, lookup) + 1;
        }
        else
        {
            // otherwise if the last character of X and Y dont match
            lookup[key] = min(SCSLength(X, Y, m, n - 1, lookup) + 1,
                SCSLength(X, Y, m - 1, n, lookup) + 1);
        }
    }

    // return the subproblem solution from the map
    return lookup[key];
}

The time complexity of the above solution is O(m.n) and requires O(m.n) extra space, where m is the length of the first string and n is the length of the second string.


We can also solve this problem in a bottom-up manner. In the bottom-up approach, calculate the smaller values of SCS(i, j) first, then build larger values from them.

            | j                                        (if i == 0)
            | i                                        (if j == 0)
SCS[i][j] = | SCS[i-1][j-1] + 1                        (if X[i-1] == Y[j-1])
            | min (SCS[i-1][j] + 1, SCS[i][j-1] + 1)   (if X[i-1] != Y[j-1])
The algorithm can be implemented as follows in C++

The time complexity of the above solution is O(m.n) and requires O(m.n) extra space, where m is the length of the first string and n is the length of the second string. The space complexity of the above solution can be improved to O(n) as calculating SCS of a row of the SCS table requires only the solutions to the current row and the previous row.


*/

// Function to find the length of the shortest common supersequence of 
// sequences X[0...m-1] and Y[0...n-1]
int SCSLength(string X, string Y)
{
    int m = X.length(), n = Y.length();

    // lookup table stores solution to already computed subproblems
    // i.e., `lookup[i][j]` stores the length of SCS of substring
    // `X[0…i-1]` and `Y[0…j-1]`
    //allocate the array
    int** lookup = new int* [m + 1];
    for (int i = 0; i < m + 1; i++)
        lookup[i] = new int[n + 1];
    // initialize the first column of the lookup table
    for (int i = 0; i <= m; i++) {
        lookup[i][0] = i;
    }

    // initialize the first row of the lookup table
    for (int j = 0; j <= n; j++) {
        lookup[0][j] = j;
    }

    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if the current character of `X` and `Y` matches
            if (X[i - 1] == Y[j - 1]) {
                lookup[i][j] = lookup[i - 1][j - 1] + 1;
            }
            // otherwise, if the current character of `X` and `Y` don't match
            else {
                lookup[i][j] = min(lookup[i - 1][j] + 1, lookup[i][j - 1] + 1);
            }
        }
    }

    // SCS will be the last entry in the lookup table
    return lookup[m][n];
}

int main()
{

    string X = "ABCBDAB", Y = "BDCABA";

    cout << "The length of the shortest common supersequence is "
        << SCSLength(X, Y);

    return 0;
}

/*

*/