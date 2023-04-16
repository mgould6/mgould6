#include "Header.h";

using namespace std;

/*
Find a minimum range with at least one element from each of the given arrays
Google Translate Icon
Given three sorted arrays of variable length, efficiently compute the minimum range with at least one element from each array.

For example,

Input: 3 sorted arrays of variable length

[ 3, 6, 8, 10, 15 ]
[ 1, 5, 12 ]
[ 4, 8, 15, 16 ]

Output: Minimum range is 3–5


Input: 3 sorted arrays of variable length

[ 2, 3, 4, 8, 10, 15 ]
[ 1, 5, 12 ]
[ 7, 8, 15, 16 ]

Output: Minimum range is 4–7
Practice This Problem

A naive solution is to compute the range of every possible triplet and return the minimum of all values. The time complexity of this solution is O(n3) for an input containing n elements, as we need three nested loops to consider every triplet. This approach is demonstrated below in C++, Java, and Python:

We can quickly reduce the time complexity to linear as we don’t need to consider every triplet. The idea is to take advantage of the fact that the arrays are already sorted. In the following solution in C++, Java, and Python, we compute the range for some selected triplets and return the minimum.

The time complexity of the above solution is O(n), where n is the total number of elements in all three arrays.


*/

//function to find the minimum range with at least on eelment 
//from each of the given arrays
pair<int, int> findMinRange(vector<int>& a, vector<int>& b, vector<int>& c)
{
	//create a pair to store the result
	pair<int, int> pair;

	//stores the minimum difference
	int diff = numeric_limits<int>::max();

	// a triplet is formee by (a[i], b[j], c[k])
	int i = 0, j = 0, k = 0;

	//loop till the end of any array is reached
	while (i < a.size() && j < b.size() && k < c.size())
	{
		//find the minimum and maximum value in the current triplet
		int low = min(min(a[i], b[j]), c[k]);
		int high = max(max(a[i], b[j]), c[k]);

		//update the minimum difference if the current difference is more
		//and store the elements in a pair
		if (diff > high - low)
		{
			pair = make_pair(high, low);
			diff = high - low;
		}

		//advance index of the array with a minimum value
		if (a[i] == low)
		{
			i++;
		}
		else if (b[j] == low)
		{
			j++;
		}
		else
		{
			k++;
		}
	}
	return pair;
}

int main()
{
	vector<int> a = { 2, 3, 4, 8, 10, 15 };
	vector<int> b = { 1, 5, 12 };
	vector<int> c = { 7, 8, 15, 16 };

	auto pair = findMinRange(a, b, c);
	cout << "The minimum range is [" << pair.first << ", " << pair.second << "]";


	return 0;
}

/*

*/