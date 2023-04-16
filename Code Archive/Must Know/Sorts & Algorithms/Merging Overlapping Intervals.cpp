#include "Header.h";

using namespace std;

/*
Merging Overlapping Intervals
Google Translate Icon
Given a set of intervals, print all non-overlapping intervals after merging the overlapping intervals.

For example,

Input:  {1, 5}, {2, 3}, {4, 6}, {7, 8}, {8, 10}, {12, 15}

Output: Intervals after merging overlapping intervals are {1, 6}, {7, 10}, {12, 15}.
Practice This Problem

The idea is to sort the intervals in increasing order of their starting time. Then create an empty stack and for each interval,

If the stack is empty or the top interval in the stack does not overlap with the current interval, push it into the stack.
If the top interval of the stack overlaps with the current interval, merge both intervals by updating the end of the top interval at the ending of the current interval.
Finally, print all non-overlapping intervals present in the stack. The algorithm can be implemented as follows in C++,
The time complexity of the above solution O(n.log(n)) and requires O(n) extra space, where n is the total number of given intervals.
*/

// data structure to represent an interval
struct Interval
{
	int begin, end;

	bool operator<(Interval const& i)
	{
		return(begin < i.begin);
	}
};

// Function to merge overlapping intervals
void mergeIntervals(vector<Interval> intervals) // no ref no const
{
	/// sort the intervals in increasing order of their starting time
	sort(intervals.begin(), intervals.end());

	// create an empty stack
	stack<Interval> s;

	// dor for each interval
	for (const Interval& curr : intervals)
	{
		// if the stack is empty or the top interval in the stack does not overlap 
		// with the current interval, push it into the stack
		if (s.empty() || curr.begin > s.top().end)
		{
			s.push(curr);
		}

		// if the top interval of the stack overlaps with the current interval
		// merge two intervals by updating the end of the top interval
		// to the current interval
		if (s.top().end < curr.end) {
			s.top().end = curr.end;
		}
	}

	// print all non overlapping intervals
	while (!s.empty())
	{
		cout << '{' << s.top().begin << ", " << s.top().end << "}\n";
		s.pop();
	}

}

int main()
{
	vector<Interval> intervals = { { 1, 5 }, { 2, 3 }, { 4, 6 }, { 7, 8 },
							{ 8, 10 }, {12, 15} };

	mergeIntervals(intervals);

	return 0;
}

/*

*/