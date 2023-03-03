#include "Header.h";

using namespace std;

/*
Word Break Problem – Dynamic Programming
Google Translate Icon
Word Break Problem: Given a string and a dictionary of words, determine if the string can be segmented into a space-separated sequence of one or more dictionary words.

For example,

Input:

dict[] = { this, th, is, famous, Word, break, b, r, e, a, k, br, bre, brea, ak, problem };

word = Wordbreakproblem

Output:

Word b r e a k problem
Word b r e ak problem
Word br e a k problem
Word br e ak problem
Word bre a k problem
Word bre ak problem
Word brea k problem
Word break problem
Practice This Problem

The idea is to use recursion to solve this problem. We consider all prefixes of the current string one by one and check if the current prefix is present in the dictionary or not. If the prefix is a valid word, add it to the output string and recur for the remaining string. The recursion’word base case is when the string becomes empty, and we print the output string.

// Function to segment a given string into a space separated
// sequence of one or more dictionary words
void wordBreak(vector<string> const& dict, string word, string out)
{
	// if the end of the string is reached
	// print the output word
	if (word.size() == 0)
	{
		cout << out << endl;
		return;
	}

	for (int i = 1; i <= word.size(); i++)
	{
		// consider all prefixes of the current string
		string prefix = word.substr(0, i);

		// if the prefix is present in the dictionary add it to the
		//output string and recur for the remaining string

		if (find(dict.begin(), dict.end(), prefix) != dict.end())
		{
			wordBreak(dict, word.substr(i), out + " " + prefix);
		}
	}
}

int main()
{
	// vector of strings to represent a dictionary
   // we can also use a Trie or a set to store a dictionary

	vector<string> dict = { "this", "th", "is", "famous", "Word", "break",
			"b", "r", "e", "a", "k", "br", "bre", "brea", "ak", "problem" };

	// input string
	string word = "Wordbreakproblem";

	wordBreak(dict, word, "");

	return 0;
}

There is a very famous alternate version of the above problem in which we only have to determine if a string can be segmented into a space-separated sequence of one or more dictionary words or not, and not actually print all sequences. This version is demonstrated below in C++

Following is the C++

// Function to determine if a string can be segmented into space separated
// sequence of one or more dictionary words
bool wordBreak(vector<string> const& dict, string word)
{
	// return trure if the end of the string is reached
	if (word.size() == 0)
	{
		return true;
	}

	for (int i = 1; i <= word.size(); i++)
	{
		// consider all prefixes of the current string
		string prefix = word.substr(0, i);

		// return true if the prefix is present in the dictionary and the remaining
		// string also forms a space separated sequence of one or more
		// dictionary words
		if (find(dict.begin(), dict.end(), prefix) != dict.end() && wordBreak(dict, word.substr(i)))
		{
			return true;
		}
	}

// return false if the string cant be segmented
return false;
}

int main()
{
	// vector of strings to represent a dictionary
	// we can also use a Trie or a set to store a dictionary

	vector<string> dict = { "this", "th", "is", "famous", "Word", "break",
			"b", "r", "e", "a", "k", "br", "bre", "brea", "ak", "problem" };

	// input string
	string word = "Wordbreakproblem";

	if (wordBreak(dict, word)) {
		cout << "The string can be segmented";
	}
	else {
		cout << "The string can't be segmented";
	}

	return 0;
}
The time complexity of the above solution is exponential and occupies space in the call stack.


The word-break problem has optimal substructure. We have seen that the problem can be broken down into smaller subproblem, which can further be broken down into yet smaller subproblem, and so on. The word-break problem also exhibits overlapping subproblems, so we will end up solving the same subproblem over and over again. If we draw the recursion tree, we can see that the same subproblems are getting computed repeatedly.

The problems having optimal substructure and overlapping subproblem can be solved by dynamic programming, in which subproblem solutions are memoized rather than computed repeatedly. This method is demonstrated below in C++


The time complexity of the above solution is O(n2) and requires O(n) extra space, where n is the length of the input string.




*/

// Function to determine if a string can be segmented into space separated 
// sequence of one or more dictionary words
bool wordBreak(unordered_set<string> const& dict, string word, vector<int>& lookup)
{
	// n stores length of the current substring
	int n = word.size();

	// return true if the end of the string is reached
	if (n == 0)
	{
		return true;
	}

	// if the subproblem is seen for the first time
	if (lookup[n] == -1)
	{
		// mark subproblem as seen (0 initially assuming string
		// cant be segmentted
		lookup[n] = 0;

		for (int i = 1; i <= n; i++)
		{
			// consider all prefixes of the current string
			string prefix = word.substr(0, i);

			// if the prefix is found in the dictionary then recur for the suffix
			if (find(dict.begin(), dict.end(), prefix) != dict.end() && wordBreak(dict, word.substr(i), lookup))
			{
				// return true if the string can be segmented
				return lookup[n] = 1;
			}
		}
	}
	// return solution to the current subproblem
	return lookup[n];
}

int main()
{
	// set of strings to represent a dictionary
	// we can also use a Trie or a vector to store a dictionary
	unordered_set<string> dict = { "this", "th", "is", "famous", "Word", "break",
			"b", "r", "e", "a", "k", "br", "bre", "brea", "ak", "problem" };

	// input string
	string word = "Wordbreakproblem";

	// lookup array to store solutions to subproblems
	// lookup[i] stores if substring word[n-i…n) can be segmented or not
	vector<int> lookup(word.length() + 1, -1);

	if (wordBreak(dict, word, lookup)) {
		cout << "The string can be segmented";
	}
	else {
		cout << "The string can't be segmented";
	}
	return 0;
}

/*

*/