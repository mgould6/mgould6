#include "Header.h";

using namespace std;

/*
Implement Diff Utility
Implement your diff utility, i.e., given two similar strings, efficiently list out all differences between them.

The diff utility is a data comparison tool that calculates and displays the differences between the two texts. It tries to determine the smallest set of deletions and insertions and create one text from the other. Diff is line-oriented rather than character-oriented, unlike edit distance.


For example,

Input:

string X = XMJYAUZ
string Y = XMJAATZ

Output:

X M J -Y A -U +A +T Z

(- indicates that character is deleted from Y but it was present in X)
(+ indicates that character is inserted in Y but it was not present in X)
We can use the Longest Common Subsequence (LCS) to solve this problem. The idea is to find the longest sequence of characters present in both original sequences in the same order. From the longest common subsequence, it is only a small step to get the diff-like output:

If a character is absent in the subsequence but present in the first original sequence, it must have been deleted (indicated by the - marks).
If it is absent in the subsequence but present in the second original sequence, it must have been inserted (indicated by the + marks).
Following is the C++

The time complexity of the above solution is O(m.n) and requires O(m.n) extra space, where m is the length of the first string and n is the length of the second string.
*/

// function to display the differences between two strings
void diff(string X, string Y, int m, int n, vector<vector<int>> lookup)
{
	// if the last character of X and Y matches
	if (m > 0 && n > 0 && X[m - 1] == Y[n - 1])
	{
		diff(X, Y, m - 1, n - 1, lookup);
		cout << " " << X[m - 1];
	}

	// if the current character of y is not present in X
	else if (n > 0 && (m == 0 || lookup[m][n - 1] >= lookup[m - 1][n]))
	{
		diff(X, Y, m, n - 1, lookup);
		cout << " +" << Y[n - 1];
	}
	// if the current character of `X` is not present in `Y`
	else if (m > 0 && (n == 0 || lookup[m][n - 1] < lookup[m - 1][n]))
	{
		diff(X, Y, m - 1, n, lookup);
		cout << " -" << X[m - 1];
	}
}

// Function to fill the lookup table by finding the length of LCS of substring
vector<vector<int>> findLCS(string X, string Y, int m, int n)
{
	// lookup[i][j] stores the length of LCS of substring X[0…i-1] and Y[0…j-1]
	vector<vector<int>> lookup(m + 1, vector<int>(n + 1));

	// first column of the lookup table will be all 0
	for (int i = 0; i <= m; i++) {
		lookup[i][0] = 0;
	}

	// first row of the lookup table will be all 0
	for (int j = 0; j <= n; j++) {
		lookup[0][j] = 0;
	}

	// fill the lookup table in a bottom-up manner
	for (int i = 1; i <= m; i++)
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

	return lookup;
}

// Implement diff utility in C++

int main()
{
	string X = "ABCDFGHJQZ";
	string Y = "ABCDEFGIJKRXYZ";

	int m = X.length(), n = Y.length();

	// fill lookup table
	vector<vector<int>> lookup = findLCS(X, Y, m, n);

	// find difference by reading the lookup table in a top-down manner
	diff(X, Y, m, n, lookup);

	return 0;
}

/*

*/