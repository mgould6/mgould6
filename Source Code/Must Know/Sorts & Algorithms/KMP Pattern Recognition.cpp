#include "Header.h";

using namespace std;

/*
KMP Algorithm

We have seen that the naive algorithm for pattern matching runs in O(n.m) time, where n is the length of the text and m is the length of the pattern. This is because the algorithm doesn’t remember any information about the past matched characters. It basically matches a character with a different pattern character over and over again.


The KMP Algorithm (or Knuth, Morris, and Pratt string searching algorithm) cleverly uses the previous comparison data. It can search for a pattern in O(n) time as it never re-compares a text symbol that has matched a pattern symbol. However, it uses a partial match table to analyze the pattern structure. Construction of a partial match table takes O(m) time. Therefore, the overall time complexity of the KMP algorithm is O(m + n).


Please refer to the following link for a detailed explanation of the KMP algorithm, one of the best explanations available on the web:

http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/

*/
int* pre_kmp(string pattern)
{
	int size = pattern.size();
	int* pie = new int[size];
	pie[0] = 0;
	int k = 0;
	for (int i = 1; i < size; i++)
	{
		while (k > 0 && pattern[k] != pattern[i])
		{
			k = pie[k - 1];
		}
		if (pattern[k] == pattern[i])
		{
			k = k + 1;
		}
		pie[i] = k;
	}

	return pie;
}

void kmp(string text, string pattern)
{
	int* pie = pre_kmp(pattern);
	int matched_pos = 0;
	for (int current = 0; current < text.length(); current++)
	{
		while (matched_pos > 0 && pattern[matched_pos] != text[current])
			matched_pos = pie[matched_pos - 1];

		if (pattern[matched_pos] == text[current])
			matched_pos = matched_pos + 1;

		if (matched_pos == (pattern.length()))
		{
			cout << "Pattern occurs with shift " << current - (pattern.length() - 1);
			matched_pos = pie[matched_pos - 1];
		}
	}
}
int main()
{
	string text, pattern;
	cout << "enter text:";
	cin >> text;
	cout << "enter pattern:";
	cin >> pattern;

	kmp(text, pattern);

	return 0;
}