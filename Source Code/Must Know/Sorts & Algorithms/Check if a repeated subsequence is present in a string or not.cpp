#include "Header.h";

using namespace std;

/*
* Check if a repeated subsequence is present in a string or not

Given a string, check if a repeated subsequence is present in it or not. The repeated subsequence should have a length of 2 or more.

For example,

String XYBAXB has XB(XBXB) as a repeated subsequence

String XBXAXB has XX(XXX) as a repeated subsequence

String ABCA doesn’t have any repeated subsequence

String XYBYAXBY has XB(XBXB), XY(XYXY), YY(YYY), YB(YBYB), and YBY(YBYBY) as repeated subsequences.
Practice This Problem

The idea is simple. If we discard all non-repeating elements from the string (having frequency of 1), and the resulting string is non-palindrome, then the string contains a repeated subsequence. If the resulting string is a palindrome and doesn’t have any character with frequency three or more, the string cannot have a repeated subsequence.

Following is the C++

The time complexity of the above solution is O(n) and requires O(n) extra space, where n is the length of the input string.


The problem can also be solved using dynamic programming. It is nothing but a variation of the Longest Common subsequence (LCS) problem. However, the time complexity of a dynamic programming solution is O(n2).


*/

//recursive function to check if str[low...high] is a palindrome or not
bool isPalindrome(string str, int low, int high)
{
	//base case 
	if (low >= high)
	{
		return true;
	}

	return(str[low] == str[high]) && isPalindrome(str, low + 1, high - 1);
}

//function to check if repeated subsequence is present in string
bool hasRepeatedSubsequence(string str)
{
	//base case 
	if (str.length() == 0)
	{
		return false;
	}

	//map to store the frequency of each distinct character of a given string
	unordered_map<char, int> freq;

	//update map with frequency 
	for (int i = 0; i < str.length(); i++)
	{
		//if the frequency of any character becomes 3,
		//we have found the repeated subsequence
		if (++freq[str[i]] >= 3)
		{
			return true;
		}
	}

	string temp;

	//consider all repeated elements frequency 2 or more
	//and discard all non repeating elements frequency 1
	for (int i = 0; i < str.length(); i++)
	{
		if (freq[str[i]] >= 2) {
			temp += str[i];
		}
	}

	//return false if temp is palindrome
	return !isPalindrome(temp, 0, temp.length() - 1);

}

int main()
{
	string str = "XYBYAXB";        // 'XB' and 'YB' are repeated subsequences

	if (hasRepeatedSubsequence(str)) {
		cout << "Repeated subsequence is present";
	}
	else {
		cout << "No repeated subsequence is present";
	}

	return 0;
}

/*

*/