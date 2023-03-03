#include "Header.h";

using namespace std;

/*
Longest Common Prefix (LCP) Problem
Google Translate Icon
Write an efficient algorithm to find the longest common prefix (LCP) between a given set of strings.

For example,

Input:  technique, technician, technology, technical
Output: The longest common prefix is techn


Input:  techie delight, tech, techie, technology, technical
Output: The longest common prefix is tech
Practice This Problem

A simple solution is to consider each string and calculate its longest common prefix with the longest common prefix of strings processed so far. The time complexity of this solution is O(N.M), where N is the total number of words and M is the maximum length of a word.

This is demonstrated below in C++

// Function to find the longest common prefix between two strings
string LCP(string X, string Y)
{
	int i = 0, j = 0;
	while (i < X.length() && Y.length())
	{
		if (X[i] != Y[i])
		{
			break;
		}

		i++, j++;
	}

	return X.substr(0, i);
}

// function to find the longest common prefix between a given set of strings
string findLCP(vector<string> const& words)
{
	string prefix = words[0];
	for (string s : words)
	{
		prefix = LCP(prefix, s);
	}

	return prefix;
}

We can also use the Divide and Conquer technique for finding the longest common prefix (LCP). Like all divide-and-conquer algorithms, the idea is to divide the strings into two smaller sets and then recursively process those sets. This is similar to the merge sort routine, except we find the LCP of the two halves instead of merging both halves.

The time complexity of the above solution is O(N.M), where N is the total number of words and M is the maximum length of a word. The auxiliary space used is O(M.log(N)) for the call stack.



*/

// Function to find the longest common prefix between two strings
string LCP(string X, string Y)
{
	int i = 0, j = 0;
	while (i < X.length() && j < Y.length()) {
		if (X[i] != Y[j])
		{
			break;
		}
		i++, j++;
	}
	return X.substr(0, i);
}

// a recursive function to find the longest common prefix between a given set of strings
string findLCP(vector<string> const& words, int low, int high)
{
	// base case: if low is more than high, return an empty string
	if (low > high)
	{
		return string("");
	}

	//base case: if low is equal to high return the current string
	if (low == high)
	{
		return words[low];
	}

	// find the mid index 
	int mid = (low + high) / 2;

	//partition the problem into subproblems and recur for each subproblem
	string X = findLCP(words, low, mid);
	string Y = findLCP(words, mid + 1, high);

	// return the longest common prefix of strings X and Y
	return LCP(X, Y);
}

int main()
{
	vector<string> words = { "techie delight", "tech", "techie",
							"technology", "technical" };

	cout << "The longest common prefix is " << findLCP(words, 0, words.size() - 1);

	return 0;

}

/*

*/