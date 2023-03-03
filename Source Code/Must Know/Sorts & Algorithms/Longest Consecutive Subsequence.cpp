#include "Header.h";

using namespace std;

/*
Longest Consecutive Subsequence
Google Translate Icon
Given an integer array, find the length of the longest subsequence formed by the consecutive integers. The subsequence should contain all distinct values, and the character set should be consecutive, irrespective of its order.

For example,

Input : [2, 0, 6, 1, 5, 3, 7]
Output: 4

Explanation: The longest subsequence formed by the consecutive integers is [2, 0, 1, 3]. It has distinct values and length 4.


Input : [2, 4, 6, 3, 7, 4, 8, 1]
Output: 4

Explanation: The longest subsequence formed by the consecutive integers is [2, 4, 3, 4, 1]. The distinct subsequence is [2, 4, 3, 1] having length 4.
Practice This Problem

Note that the problem differs from finding the largest subarray formed by the consecutive integers. Unlike subarrays, subsequences are not required to occupy consecutive positions within the original array.


A naive solution would be to sort the array in ascending order and compare the consecutive elements to find the maximum length subarray with consecutive integers. The time complexity of this solution would be O(n.log(n)), where n is the size of the given sequence.


We can do better using hashing. The idea is to consider each input sequence element and find the maximum length of a consecutive subsequence starting with i, i.e., for every element e, check for the presence of elements e+1, e+2, e+3, … in the input. We can optimize the code by using a set for constant-time lookups to determine if the element present in the input sequence or not. The algorithm can be implemented as below in C++

The time complexity of the above solution O(n) and requires O(n) extra space.


*/

// function to find the length of the largest subsequence formed by consecutive integers
int findMaxLenSubseq(vector<int>& input)
{
	// construct a set out of input elements 
	unordered_set<int> S(input.begin(), input.end());

	// initialize result by 0
	int max_len = 0;

	// do for each element of the input sequence
	for (int e : input)
	{
		// check if the current element e is a candidate for starting a sequence
		// the previous element e-1 doesn't exist in the set
		if (S.find(e - 1) == S.end())
		{
			// stores the length of subsquence starting with the current element 
			int len = 1;

			// check for present of elements e+1, e+2, e+3, e+len in S
			while (S.find(e + len) != S.end())
			{
				len++;
			}

			// update result with the length of current consecutive subsequence
			max_len = max(max_len, len);
		}

	}
	// return result
	return max_len;
}

int main()
{
	vector<int> input = { 2, 0, 6, 1, 5, 3, 7 };

	cout << "The length of the maximum consecutive subsequence is "
		<< findMaxLenSubseq(input);

	return 0;
}

/*

*/