#include "Header.h";

using namespace std;

/*
Find the longest continuous sequence length with the same sum in given binary arrays
Given two binary arrays, X and Y, find the length of the longest continuous sequence that starts and ends at the same index in both arrays and have the same sum. In other words, find max(j-i+1) for every j >= i, where the sum of subarray X[i, j] is equal to the sum of subarray Y[i, j].

For example, consider the following binary arrays X and Y:


X[]: {0, 0, 1, 1, 1, 1}
Y[]: {0, 1, 1, 0, 1, 0}


The length of the longest continuous sequence with the same sum is 5 as


X[0, 4]: {0, 0, 1, 1, 1} (sum = 3)
Y[0, 4]: {0, 1, 1, 0, 1} (sum = 3)

Practice This Problem


A naive solution would be to consider every subarray [i, j], where j > i and check if the sum of X[i, j] is equal to the sum of Y[i, j] or not. If the sum is found to be equal and the length of the subarray is more than the maximum found so far, update the result. The time complexity of this solution O(n2), where n is the size of the given sequence. This assumes that the sum of each subarray is computed in constant time.


We can solve this problem in linear time. The idea is to traverse the array and maintain the sum of X[] and Y[] till the current index and calculate the difference between the two sums.

If the difference is seen for the first time, store the difference and current index in a map.
If the difference is seen before and the previous occurrence index is i, then we have found subarrays X[i+1, j] and Y[i+1, j] ending at the current index j, whose sum of elements is equal. If the subarray length is more than the maximum found so far, update the result.
How does this work?

Claim: If the difference is seen before and the index of previous occurrence is i, then X[i+1, j] = Y[i+1, j].

We can write previous difference as di = X[0, i] – Y[0, i]


Similarly, the current difference dj can be written as:

dj = X[0, j] – Y[0, j], or
dj = (X[0, i] + X[i+1, j]) – (Y[0, i] + Y[i+1, j])


If the difference is seen before, i.e., (dj = di), then

(X[0, i] + X[i+1, j]) – (Y[0, i] + Y[i+1, j]) = X[0, i] – Y[0, i]
X[i+1, j] – Y[i+1, j] = 0, or
X[i+1, j] == Y[i+1, j]
The algorithm can be implemented as follows in C++
*/

//given two binary arrays X and Y find the length of the longest
//continuous sequence that starts and ends at the same index in both 
//arrays and have the same sum
int findMaxSubarrayLength(bool X[], bool Y[], int n)
{
	//create an empty map
	unordered_map<int, int> map;
	//handle the case when the required sequence starts from index 0
	map[0] = -1;

	//stores length of the longest continuous sub sequence
	int result = 0;

	//sum_x and sum_y stores the sum of elements X[] and Y[]
	//respectively till the current index
	int sum_x = 0, sum_y = 0;

	//traverse both lists simultaneously 
	for (int i = 0; i < n; i++)
	{
		//update sum_x and sum_y
		sum_x += X[i];
		sum_y += Y[i];

		//calculate the difference between the sum of elements in two lists
		int diff = sum_x - sum_y;

		//if the difference is seen for the first time
		//store the difference and current index in a map
		if (map.find(diff) == map.end())
		{
			map[diff] = i;
		}
		//if the difference is seen before then update the result
		else
		{
			result = max(result, i - map[diff]);
		}

	}
	return result;
}

int main()
{
	bool X[] = { 0, 0, 1, 1, 1, 1 };
	bool Y[] = { 0, 1, 1, 0, 1, 0 };

	int n = sizeof(X) / sizeof(X[0]);

	cout << "The length of the longest continuous sequence with the same sum is " <<
		findMaxSubarrayLength(X, Y, n);

	return 0;
}

/*

*/