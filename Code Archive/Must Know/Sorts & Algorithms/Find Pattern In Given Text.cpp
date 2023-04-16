#include "Header.h";

using namespace std;

/*
Given a text, find all occurrences of a given pattern in it.

For example,

1. For text T = “ABCABAABCABAC” and pattern P = “ABAA”,

The pattern occurs only once in the text, starting from index 3 (“ABCABAABCABAC”).


2. For text T = “ABCABAABCABAC” and pattern P = “CAB”,

The pattern occurs twice in the text, starting from index 2 and 8 (“ABCABAABCABAC” and “ABCABAABCABAC”).

The pattern matching is a widespread real-life problem that frequently arises in text-editing programs such as MS Word, notepad, notepad++, etc. String pattern matching algorithms are also used to search for particular patterns in DNA sequences.

The goal is to find all occurrences of pattern P[1…m] of length m in the given text T[1…n] of length n. This post will discuss the naive string-matching algorithm.


The naive algorithm finds all occurrences of a pattern by using a loop that checks the condition
P[1…m] = T[s+1…s+m] for each of the n-m+1 possible values of s. Following is the pseudocode for the algorithm:


*/

void find(string text, string pattern)
{
	int n = text.length();
	int  m = pattern.length();

	//if text is an empty string
	if (m == 0)
	{
		cout << "The pattern occurs with shift 0";
		return;
	}

	for (int i = 0; i <= n - m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (text[i + j] != pattern[j])
			{
				break;
			}
			if (j == m - 1)
			{
				cout << "the pattern occurs with shift " << i << endl;
			}
		}
	}
}

int main()
{
	string text = "ABCABAABCABAC";
	string pattern = "CAB";

	find(text, pattern);

	return 0;
}

