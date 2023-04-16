#include "Header.h";

using namespace std;

/*
Merge `M` sorted lists of variable length

*/

//data structure to store a heap node 
struct Node
{
	int val, i, index;
};

//comparison object to be used to order th min heap
struct comp
{
	bool operator()(const Node& lhs, const Node& rhs) const
	{
		return lhs.val > rhs.val;
	}
};

//function to merge m sorted lists of variable length and 
//print them in ascending order
void printSorted(vector<vector<int>> const& lists)
{
	int M = lists.size();

	//create min heap
	priority_queue<Node, vector<Node>, comp> pq;

	//push the first element of each list into the min heap'
	//along with the list number and their index in the list 
	for (int i = 0; i < M; i++)
	{
		if (lists[i].size() >= 1)
		{
			pq.push({ lists[i][0], i, 0 });
		}
	}

	//run till min heap is empty
	while (!pq.empty())
	{
		//extract the minimum node from the min heap
		Node min = pq.top();
		pq.pop();

		//print the minimum element 
		cout << min.val << " ";

		//take the next element from the same list and 
		//insert it into the min heap'
		if (min.index + 1 < lists[min.i].size())
		{
			min.index += 1;
			min.val = lists[min.i][min.index];
			pq.push(min);
		}
	}
}

int main()
{
	// `M` lists of variable size
	vector<vector<int>> lists =
	{
		{ 10, 20, 30, 40 },
		{ 15, 25, 35 },
		{ 27, 29, 37, 48, 93 },
		{ 32, 33 }
	};

	printSorted(lists);

	return 0;
}

/*
Merge `M` sorted lists of variable length

Given M sorted lists of variable length, merge them efficiently in sorted order.

For example,

Input:  4 sorted lists of variable length

[10, 20, 30, 40]
[15, 25, 35]
[27, 29, 37, 48, 93]
[32, 33]

Output:

[10, 15, 20, 25, 27, 29, 30, 32, 33, 35, 37, 40, 48, 93]
Practice This Problem

A simple solution would be to create an auxiliary array containing all lists’ elements (order doesn’t matter). Then use an efficient sorting algorithm to sort the array in ascending order and print the elements. The worst-case time complexity of this approach will be O(N.log(N)), where N is the total number of elements present in all lists. Also, this approach does not take advantage of the fact that each list is already sorted.


We can easily solve this problem in O(N.log(M)) time by using a min-heap. The idea is to construct a min-heap of size M and insert the first element of each list into it. Then pop the root element (minimum element) from the heap and insert the next element from the “same” list as the popped element. Repeat this process till the heap is exhausted. Depending upon the requirement, either print the popped element or store it in an auxiliary array.

The algorithm can be implemented as follows in C++,
*/