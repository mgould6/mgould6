#include "Header.h";

using namespace std;

/*
Longest Increasing Subsequence Problem
Google Translate Icon
The Longest Increasing Subsequence (LIS) problem is to find a subsequence of a given sequence in which the subsequence’s elements are in sorted order, lowest to highest, and in which the subsequence is as long as possible. This subsequence is not necessarily contiguous or unique.

For example, consider the following subsequence:

{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}


The longest increasing subsequence is {0, 2, 6, 9, 11, 15} having length 6; the input sequence has no 7–member increasing subsequences. The longest increasing subsequence in this example is not unique. For instance, {0, 4, 6, 9, 11, 15} and {0, 4, 6, 9, 13, 15} are other increasing subsequences of equal length in the same input sequence.

Practice This Problem


We have already discussed an O(n2) time complexity solution of LIS here, which uses dynamic programming. In this post, an O(n.log(n)) time, non-DP solution, is discussed.


Let S[i] be defined as the smallest integer that ends an increasing sequence of length i. Now iterate through every integer X of the input set and do the following:

If X is more than the last element in S, then append X at the end of S. This essentially means we have found a new largest LIS.
Otherwise, find the smallest element in S, which is more than or equal to X, and replace it with X. Because S is sorted at any time, the element can be found using binary search in log(N) time.
Let’s illustrate this with the help of an example. Following are the steps followed by the algorithm for an integer array {2, 6, 3, 4, 1, 2, 9, 5, 8}:

Initialize to an empty set S = {}
Inserting 2 —- S = {2} – New largest LIS
Inserting 6 —- S = {2, 6} – New largest LIS
Inserting 3 —- S = {2, 3} – Replaced 6 with 3
Inserting 4 —- S = {2, 3, 4} – New largest LIS
Inserting 1 —- S = {1, 3, 4} – Replaced 2 with 1
Inserting 2 —- S = {1, 2, 4} – Replaced 3 with 2
Inserting 9 —- S = {1, 2, 4, 9} – New largest LIS
Inserting 5 —- S = {1, 2, 4, 5} – Replaced 9 with 5
Inserting 8 —- S = {1, 2, 4, 5, 8} – New largest LIS

So, the length of the LIS is 5 (the size of S). Please note that here S[i] is defined as the smallest integer that ends an increasing sequence of length i. Therefore, S does not represent an actual sequence, but S’s size represents the LIS length.


The following C++ solution uses std::set, which is implemented as a red–black binary search tree with the worst-case time complexity of O(log(n)) for insertion.

The length of the LIS is 5

How to print LIS?

To make things simpler, we can keep in the set s, not the actual integers, but their indices. That is we do not keep {1, 2, 4, 5, 8}, but keep {4, 5, 3, 7, 8} since input[4] = 1, input[5] = 2, input[3] = 4, input[7] = 5, and input[8] = 8.

To reconstruct the actual LIS, we have to use a parent array. Let parent[i] be the predecessor of an element with index i in the LIS, ending at the element with index i. If we update the parent array properly, the actual LIS is:

input[s[lastElementOfS]],
input[parent[s[lastElementOfS]]],
input[parent[parent[s[lastElementOfS]]]],
………
The following C++ solution stores both actual integers and their indices in the set for easier implementation:

The time complexity of the above solution is O(n.log(n)) and requires O(n) extra space, where n is the size of the given sequence.


How to print LIS?

To make things simpler, we can keep in the set s, not the actual integers, but their indices. That is we do not keep {1, 2, 4, 5, 8}, but keep {4, 5, 3, 7, 8} since input[4] = 1, input[5] = 2, input[3] = 4, input[7] = 5, and input[8] = 8.

To reconstruct the actual LIS, we have to use a parent array. Let parent[i] be the predecessor of an element with index i in the LIS, ending at the element with index i. If we update the parent array properly, the actual LIS is:

input[s[lastElementOfS]],
input[parent[s[lastElementOfS]]],
input[parent[parent[s[lastElementOfS]]]],
………
The following C++ solution stores both actual integers and their indices in the set for easier implementation

*/

// Function to find the length of the longest increasing subsequence in a given array
int findLISLength(vector<int> const& input)
{
	// base case
	if (input.size() == 0)
	{
		return 0;
	}

	// create an empty ordered set s. the i'th element is defined as the
	// smallest integer that ends and increasing sequence of length i
	set<int> s;

	//process every element one by one
	for (int i = 0; i < input.size(); i++)
	{
		// ignore the current element if it is already present in the set
		if (s.find(input[i]) != s.end())
		{
			continue;
		}

		// insert the current element into the set
		auto ret = s.insert(input[i]);



		// get an iterator to the inserted item
		set<int>::iterator it;
		if (ret.second) {
			it = ret.first;
		}

		// if the element is not inserted at the end, then delete the next
		// greater element from the set
		if (++it != s.end()) {
			s.erase(it);
		}
	}

	//length of LIS is the total number of elements in the set
	return s.size();
}



int main()
{
	vector<int> input = { 2, 6, 3, 4, 1, 2, 9, 5, 8 };

	cout << "The length of the LIS is " << findLISLength(input);

	return 0;
}


/*

*/