#include "Header.h";

using namespace std;

/*
Find all permutations of a string in C++ (Using Backtracking and STL)
This post will find all permutations of a string containing all distinct characters in C++.

For example, the string ABC has 6 permutations, i.e., ABC, ACB, BAC, BCA, CBA, CAB.

Practice This Problem

Approach 1: (Using Backtracking)
We can in-place find all permutations of the given string by using backtracking. The idea is to swap each of the remaining characters in the string with its first character and then find all the permutations of the remaining characters using a recursive call. The base case of the recursion is when the string is left with only one unprocessed element. Following is the recursion tree for printing all permutations of the string ABC:
https://www.techiedelight.com/wp-content/uploads/Permutations.png

Approach 2: (Using STL)
We can use std::rotate to in-place rotate a string in linear time and recursively permute on the rotated string. Following is the recursion tree for printing all permutations of the string ABC:

The time complexity of the above solutions is O(n.n!) as there are n! permutations for a string of length n, and each permutation takes O(n) time.


Note that the above solution doesn’t handle strings containing duplicate characters. We have discussed how to handle duplicate characters here.
https://www.techiedelight.com/find-lexicographically-next-permutations-string-sorted-ascending-order/




*/

void permutations(string str, int i, int n)
{
	//base condition
	if (i == n - 1)
	{
		cout << str << endl;
		return;
	}
	//process each character of the remaining string
	for (int j = i; j < n; j++)
	{
		//swap character at index i with the current character
		swap(str[i], str[j]);

		//recur for substring str[i+1, n-1]
		permutations(str, i + 1, n);

		//backtrack
		swap(str[i], str[j]);
	}
}

int main()
{
	string str = "ABCD";

	permutations(str, 0, str.length());

	return 0;
}

