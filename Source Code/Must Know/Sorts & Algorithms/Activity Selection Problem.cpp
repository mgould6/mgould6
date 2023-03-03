#include "Header.h";

using namespace std;

/*
Activity Selection Problem
Google Translate Icon
Activity Selection Problem: Given a set of activities, along with the starting and finishing time of each activity, find the maximum number of activities performed by a single person assuming that a person can only work on a single activity at a time.

For example,

Input: Following set of activities

(1, 4), (3, 5), (0, 6), (5, 7), (3, 8), (5, 9), (6, 10), (8, 11), (8, 12), (2, 13), (12, 14)

Output:

(1, 4), (5, 7), (8, 11), (12, 14)
Practice This Problem

The activity selection problem is a problem concerning selecting non-conflicting activities to perform within a given time frame, given a set of activities each marked by a start and finish time. A classic application of this problem is scheduling a room for multiple competing events, each having its time requirements (start and end time).


Let’s assume there exist n activities each being represented by a start time si and finish time fj. Two activities i and j are said to be non-conflicting if si = fj or sj = fi.

We can solve this problem by being greedy. Using a greedy approach will always result in an optimal solution to this problem. The idea is to initially sort the activities in increasing order of their finish times and create a set S to store the selected activities and initialize it with the first activity. Then from the second activity onward, include the activity in the activities list if the activity’s start time is greater or equal to the finish time of the last selected activity. Repeat this for each activity involved.

Following is the implementation of the above algorithm in C++, Java, and Python:
*
The time complexity of the above solution is O(n.log(n)), where n is the total number of activities. The auxiliary space required by the program is constant.

Weighted Activity Selection Problem:

Weighted activity selection is a generalized version of the activity selection problem that involves selecting an optimal set of non-overlapping activities to maximize the total weight. Unlike the unweighted version, there is no greedy solution to the weighted activity selection problem.

References:

https://en.wikipedia.org/wiki/Activity_selection_problem

http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/Greedy/actSelectionGreedy.htm
*/

struct Pair
{
	// stores start and finish time of the activities 
	int start, finish;
};

// activity selection problem
void selectActivity(vector<Pair> activities)	// no ref and no const
{
	// k keeps track of the index of the last selected activity
	int k = 0;

	// set to store the selected activities index
	unordered_set<int> out;

	// select 0 as the first activity
	if (activities.size())
	{
		out.insert(0);
	}

	// sort the activities according to their finishing time
	sort(activities.begin(), activities.end(),
		[](auto const& lhs, auto const& rhs) {
			return lhs.finish < rhs.finish;
		});

	// start iterating from the second element of the
	// vector up to its last element
	for (int i = 1; i < activities.size(); i++)
	{
		// if the start time of the i'th activity is greater or equal
		// to the finish time of the last selected activity, it
		// can be included in the activities list

		if (activities[i].start >= activities[k].finish)
		{
			out.insert(i);
			k = i;            // update `i` as the last selected activity
		}
	}

	for (int i : out)
	{
		cout << "{" << activities[i].start << ", " << activities[i].finish
			<< "}" << endl;
	}

}

int main()
{
	// List of pairs with each pair storing start time
   // and finish time of the activities
	vector<Pair> activities =
	{
		{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
		{6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
	};

	selectActivity(activities);

	return 0;
}

/*

*/