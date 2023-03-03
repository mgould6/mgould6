#include "Header.h";

using namespace std;

/*
Longest Common Substring Problem
Google Translate Icon
The longest common substring problem is the problem of finding the longest string (or strings) that is a substring (or are substrings) of two strings.

The problem differs from the problem of finding the Longest Common Subsequence (LCS). Unlike subsequences, substrings are required to occupy consecutive positions within the original string.


For example, the longest common substring of strings ABABC, BABCA is the string BABC having length 4. Other common substrings are ABC, A, AB, B, BA, BC, and C.

Practice This Problem

A naive solution would be to consider all substrings of the second string and find the longest substring that is also a substring of the first string. The time complexity of this solution would be O((m + n) × m2), where m and n are the length of the strings X and Y, as it takes (m+n) time for substring search, and there are m2 substrings of the second string. We can optimize this method by considering substrings in order of their decreasing lengths and return as soon as any substring matches the first string. But the worst-case time complexity remains the same when no common characters are present.

Can we do better?

The idea is to find the longest common suffix for all pairs of prefixes of the strings using dynamic programming using the relation:

LCSuffix[i][j] = | LCSuffix[i-1][j-1] + 1       (if X[i-1] = Y[j-1])
				 | 0                            (otherwise)

where,

0 <= i – 1 < m,    where m is the length of string X
0 <= j – 1 < n,    where n is the length of string Y
For example, consider strings ABAB and BABA.

Longest Common Substring

Finally, the longest common substring length would be the maximal of these longest common suffixes of all possible prefixes.


The following solution in C++, Java, and Python finds the length of the longest repeated subsequence of sequences X and Y iteratively using the optimal substructure property of the LCS problem.

The time complexity of the above solution is O(m.n) and requires O(m.n) extra space, where m and n are the length of the strings X and Y, respectively. The space complexity of the above solution can be improved to O(n) as calculating LCS of a row of the LCS table requires only the solutions to the current row and the previous row. We can also store only non-zero values in the rows. We can do this using hash tables instead of arrays.


We can also solve this problem in O(m + n) time by using a generalized suffix tree. We will be soon discussing the suffix tree approach in a separate post.


Exercise: Write space optimized code for iterative version.


References: https://en.wikipedia.org/wiki/Longest_common_substring_problem
*/

//function to find the longest common substring of sequences
// X[0...m-1] and Y[0...n-1]
string LCS(string X, string Y, int m, int n)
{
	int maxlen = 0;			//stores the max length of LCS
	int endingIndex = m;	// stores the ending index of LCS in X

	// lookup table stores solution to already computed subproblems
	// lookup[i][j] stores the length of LCS of substring
	// X[0...i-1] and Y[0...j-1]
	//allocate the array
	int** lookup = new int* [m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		lookup[i] = new int[n + 1];

	}



	// first column of the lookup table will be all 0s
	for (int i = 0; i <= m; i++)
	{
		lookup[i][0] = 0;
	}

	// first row of the lookup table will be all 0s
	for (int j = 0; j <= n; j++)
	{
		lookup[0][j] = 0;
	}

	// fill the lookup table in a bottom up manner
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// if the current character of `X` and `Y` matches
			if (X[i - 1] == Y[j - 1])
			{
				lookup[i][j] = lookup[i - 1][j - 1] + 1;

				// update the maximum length and ending index
				if (lookup[i][j] > maxlen)
				{
					maxlen = lookup[i][j];
					endingIndex = i;
				}
			}
		}
	}
	// return longest commmon substring having length maxlen
	return X.substr(endingIndex - maxlen, maxlen);
}

int main()
{

	string X = "ABC", Y = "BABA";
	int m = X.length(), n = Y.length();

	// Find longest common substring
	cout << "The longest common substring is " << LCS(X, Y, m, n);

	return 0;
	return 0;
}

/*

*/