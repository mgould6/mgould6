#include "Header.h";

using namespace std;


/*
The time complexity of the above solution is O(n2) and requires O(n2) extra space, where n is the length of the input string.


However, both the above-discussed methods only find the longest palindromic subsequence length but does not print the longest palindromic subsequence itself.

How can we print Longest Palindromic subsequence?

The longest palindromic subsequence problem is a classic variation of the Longest Common Subsequence (LCS) problem. The idea is to find LCS of the given string with its reverse, i.e., call LCS(X, reverse(X)) and the longest common subsequence will be the longest palindromic subsequence.

Following is the C++, Java, and Python program that demonstrates it:

The time complexity of the above solution is O(n2) and requires O(n2) extra space, where n is the length of the input string.
*/


// Function to find LCS of string `X[0…m-1]` and `Y[0…n-1]`
string findLongestPalindrome(string X, string Y, int m, int n, vector<vector<int>>& lookup)
{
    // return an empty string if the end of either sequence is reached
    if (m == 0 || n == 0) {
        return string("");
    }

    // If the last character of `X` and `Y` matches
    if (X[m - 1] == Y[n - 1])
    {
        // append current character (`X[m-1]` or `Y[n-1]`) to LCS of
        // substring `X[0…m-2]` and `Y[0…n-2]`
        return findLongestPalindrome(X, Y, m - 1, n - 1, lookup) + X[m - 1];
    }

    // otherwise, if the last character of `X` and `Y` are different

    // if a top cell of the current cell has more value than the left
    // cell, then drop the current character of string `X` and find LCS
    // of substring `X[0…m-2]`, `Y[0…n-1]`

    if (lookup[m - 1][n] > lookup[m][n - 1]) {
        return findLongestPalindrome(X, Y, m - 1, n, lookup);
    }

    // if a left cell of the current cell has more value than the top
    // cell, then drop the current character of string `Y` and find LCS
    // of substring `X[0…m-1]`, `Y[0…n-2]`

    return findLongestPalindrome(X, Y, m, n - 1, lookup);
}

// Function to find the length of LCS of substring `X[0…n-1]` and `Y[0…n-1]`
int LCSLength(string X, string Y, int n, vector<vector<int>>& lookup)
{
    // first row and first column of the lookup table are already 0

    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if current character of `X` and `Y` matches
            if (X[i - 1] == Y[j - 1]) {
                lookup[i][j] = lookup[i - 1][j - 1] + 1;
            }
            // otherwise, if the current character of `X` and `Y` don't match
            else {
                lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1]);
            }
        }
    }

    return lookup[n][n];
}


int main()
{


    string X = "ABBDCACB";

    int m = X.length();

    // lookup[i][j] stores the length of LCS of substring `X[0…i-1]` and `Y[0…j-1]`
    vector<vector<int>> lookup(m + 1, vector<int>(m + 1));

    // string `Y` is a reverse of `X`
    string Y = X;
    reverse(Y.begin(), Y.end());

    // find the length of the LPS using LCS
    cout << "The length of the longest palindromic subsequence is "
        << LCSLength(X, Y, m, lookup) << endl;

    // print the LPS using a lookup table
    cout << "The longest palindromic subsequence is "
        << findLongestPalindrome(X, Y, m, m, lookup);

    return 0;
}

/*
/*
Longest Palindromic Subsequence using Dynamic Programming
Google Translate Icon
The Longest Palindromic Subsequence (LPS) problem is finding the longest subsequences of a string that is also a palindrome.

The problem differs from the problem of finding the longest palindromic substring. Unlike substrings, subsequences are not required to occupy consecutive positions within the original string.


For example, consider the sequence ABBDCACB.

The length of the longest palindromic subsequence is 5
The longest palindromic subsequence is BCACB
Practice This Problem

The idea is to use recursion to solve this problem. The idea is to compare the last character of the string X[i…j] with its first character. There are two possibilities:

If the string’s last character is the same as the first character, include the first and last characters in palindrome and recur for the remaining substring X[i+1, j-1].
If the last character of the string is different from the first character, return the maximum of the two values we get by
Removing the last character and recursing for the remaining substring X[i, j-1].
Removing the first character and recursing for the remaining substring X[i+1, j].
This yields the following recursive relation to finding the length of the longest repeated subsequence of a sequence X:

           | 1                                 (if i = j)
LPS[i…j] = | LPS[i+1…j-1] + 2                  (if X[i] = X[j])
           | max (LPS[i+1…j], LPS[i…j-1])      (if X[i] != X[j])
The algorithm can be implemented as follows in C++, Java, and Python. The solution finds the length of the longest repeated subsequence of sequence X recursively using the above relations.


// function to find the length of the longest palindromic subsequence
int findLongestPalindrome(string X, int i, int j)
{
    // base condition
    if (i > j)
    {
        return 0;
    }

    // if the string X has only one character it it a palindrom
    if (i == j)
    {
        return 1;
    }

    // if the last character of the string is the same as the first character
    if (X[i] == X[j])
    {
        // include the first and last characters in palindrom
        // and recur for the remaining substring
        return findLongestPalindrome(X, i + 1, j - 1) + 2;
    }

    // if the last character of the string is different from the first charcter
    // 1. remove the last character and recur for the remaining substring X[i, j-1]
    // 2. remove the first character and recur for the remaining substring X[i+1, j]
    // Return the maximum of the two values

    return max(findLongestPalindrome(X, i, j-1), findLongestPalindrome(X, i+1, j));
}

The worst-case time complexity of the above solution is exponential O(2n), where n is the length of the input string. The worst case happens when there is no repeated character present in X (i.e., LPS length is 1), and each recursive call will end up in two recursive calls. This also requires additional space for the call stack.



The LPS problem has an optimal substructure and also exhibits overlapping subproblems. Let’s consider the recursion tree for a sequence of length 6 having all distinct characters, say ABCDEF, whose LPS length is 1.


Longest Palindromic subsequence


As we can see, the same subproblems (highlighted in the same color) are getting computed repeatedly. We know that problems with optimal substructure and overlapping subproblems can be solved by dynamic programming, where subproblem solutions are memoized rather than computed and again. This method is demonstrated below in C++

int findLongestPalindrome(string X, int i, int j, unordered_map<string, int>& lookup)
{
    // Base condition
    if (i > j) {
        return 0;
    }

    // If the string `X` has only one character, it is a palindrome
    if (i == j) {
        return 1;
    }

    // Construct a unique map key from dynamic elements of the input
    string key = to_string(i) + "|" + to_string(j);

    // If the subproblem is seen for the first time, solve it and
    // store its result in a map
    if (lookup.find(key) == lookup.end())
    {
        //If the last character of the string is the same as the first character,
           include the first and last characters in palindrome and recur
           for the remaining substring `X[i+1, j-1]` */
           //
           //if (X[i] == X[j]) {
           //lookup[key] = findLongestPalindrome(X, i + 1, j - 1, lookup) + 2;
           //}
           //else {
           //
           ////If the last character of the string is different from the first
           ////     character
           ////   1. Remove the last character and recur for the remaining substring
           ////  `X[i, j-1]`
           //// 2. Remove the first character and recur for the remaining substring
           ////`X[i+1, j]`
           ////3. Return the maximum of the two values 
           //
           //lookup[key] = max(findLongestPalindrome(X, i, j - 1, lookup),
           //findLongestPalindrome(X, i + 1, j, lookup));
           //}
           //    }
           //
           //    // Return the subproblem solution from the map
           //    return lookup[key];
           //}
