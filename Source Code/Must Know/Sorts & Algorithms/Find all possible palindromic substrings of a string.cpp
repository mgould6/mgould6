#include "Header.h";

using namespace std;

/*
Find all possible palindromic substrings of a string
Google Translate Icon
Given a string, find all possible palindromic substrings in it.

The problem differs from the problem of finding the possible palindromic subsequence. Unlike subsequences, substrings are required to occupy consecutive positions within the original string.


For example,

Input:  str = google

Output: e l g o oo goog
Practice This Problem

A simple solution would be to generate all substrings of the given string and print substrings that are palindromes. The time complexity of this solution would be O(n3), where n is the length of the input string.


We can solve this problem in O(n2) time and O(1) space. The idea is inspired by the Longest Palindromic Substring problem. For each character in the given string, consider it as the midpoint of a palindrome and expand in both directions to find all palindromes that have it as midpoint. For an even length palindrome, consider every adjacent pair of characters as the midpoint. We use a set to store all unique palindromic substrings.

Following is the C++
*/

//expand in both directions  of low and high to find all palindromes
void expand(string str, int low, int high, unordered_set<string>& set)
{
	//run till str[low.high] is not a palindrome
	while (low >= 0 && high < str.length() && str[low] == str[high])
	{
		//push all palindromes into a set
		set.insert(str.substr(low, high - low + 1));

		//expand in both directions
		low--, high++;
	}
}

//function to find all unique palindromic substrings of a given string
void findPalindromicSubstrings(string str)
{
	//create an empty set to store all unique palindromic substrings
	unordered_set<string> set;

	for (int i = 0; i < str.length(); i++)
	{
		//find all odd length palindrome with str[i] as a midpoint
		expand(str, i, i, set);

		//find all even length palindrome with str[i] and str[i+1] as 
		//its midpoint
		expand(str, i, i + 1, set);
	}

	//print all unique palindromic substrings
	for (auto i : set)
	{
		cout << i << " ";
	}
}


int main()
{
	string str = "google";

	findPalindromicSubstrings(str);

	return 0;
}

/*

*/