#include "Header.h";

using namespace std;

/*
Longest Palindromic Substring Problem
Google Translate Icon
Given a string, find the maximum length contiguous substring of it that is also a palindrome. For example, the longest palindromic substring of “bananas” is “anana”, and the longest palindromic substring of “abdcbcdbdcbbc” is “bdcbcdb”.

The problem differs from the problem of finding the longest palindromic subsequence. Unlike subsequences, substrings are required to occupy consecutive positions within the original string.

Note that the longest palindromic substring is not guaranteed to be unique. For example, there is no palindromic substring in a string abracadabra with a length greater than three. Still, there are two palindromic substrings with length three, namely, aca and ada. If multiple longest palindromic substring exists, return any one of them.

Practice This Problem


The time complexity of the above solution is O(n2) and requires O(n) extra space, where n is the length of the input string. Note that O(n) solution is also possible for this problem by using Manacher’s algorithm.
The dynamic programming solution for this problem takes O(n2) time and O(n2) space. This post will discuss another approach to solve this problem that doesn’t require any extra space.
The idea is simple and effective – for each character in the given string, consider it the midpoint of a palindrome and expand in both directions to find the maximum length palindrome. For an even length palindrome, consider every adjacent pair of characters as the midpoint.


Following is the C++
*/

//expand in both directions of low and hight to find the maximum length palindrom
string expand(string str, int low, int high)
{
	//run till str[low.high] is a palindrom
	while (low >= 0 & high < str.length() && (str[low] == str[high]))
	{
		low--, high++; //expand in both directions
	}

	//return palindromic substring
	return str.substr(low + 1, high - low + 1);
}

//function to find the longest palindromic substring in O(n^2) time and O(1) space
string findLongestPalindromicSubstring(string str)
{
	//base case 
	if (str.length() == 0)
	{
		return str;
	}

	//max_str stores the maximum length palindromic substring found so far
	string max_str = "", curr_str;

	int max_length = 0, curr_length;

	//consider every character of the given string as a midpoint and expand
	//in both directions to find a max length palindrom
	for (int i = 0; i < str.length(); i++)
	{
		//find the longest odd length palindrome with str[i] as a midpoint
		curr_str = expand(str, i, i);
		curr_length = curr_str.length();

		//update maximum length palindromic substring if odd length
		//palindrom has a greater length
		if (curr_length > max_length)
		{
			max_length = curr_length;
			max_str = curr_str;
		}

		//find the longest even length palindrome with str[i] and str[i+1]
		//as midpoints note that an event length palindrome has two midpoints
		curr_str = expand(str, i, i + 1);
		curr_length = curr_str.length();

		//update the maximum length palindrom substring if even length
		//palindrome has a greater length
		if (curr_length > max_length)
		{
			max_length = curr_length;
			max_str = curr_str;
		}
	}
	return max_str;
}

int main()
{
	string str = "ABDCBCDBDCBBC";

	cout << "The longest palindromic substring of " << str << " is "
		<< findLongestPalindromicSubstring(str);

	return 0;
}

/*

*/