#include "Header.h";

using namespace std;

/*
Maximum Overlapping Intervals Problem
Google Translate Icon
Consider an event where a log register is maintained containing the guest’s arrival and departure times. Given an array of arrival and departure times from entries in the log register, find the point when there were maximum guests present in the event.

Note that if an arrival and departure event coincides, the arrival time is preferred over the departure time.


For example,

Input:

arrival = { 1, 2, 4, 7, 8, 12 }
departure = { 2, 7, 8, 12, 10, 15 }

Output: Maximum number of guests is 3, present at time 7
Maximum Overlapping Interval


Related Posts:

Find minimum platforms needed to avoid delay in the train arrival

1. Using Brute-Force (Quadratic Time Solution)
The idea is to find time t when the last guest leaves the event and create a count array of size t+2. Then fill the count array with the guest’s count using the array index to store time, i.e., for an interval [x, y], the count array is filled in a way that all values between the indices x and y are incremented by 1.

After the count array is filled with each event timings, find the maximum element’s index in the count array. This index would be the time when there were maximum guests present in the event.

The time complexity of this approach is quadratic and requires extra space for the count array. Following is the C++

// Function to find the point when the maximum number of guests are present in an event
void findMaxGuests(vector<int> const& arrival, vector<int> const& departure)
{
	// find the time when the last guest leaves the event
	int t = *max_element(departure.begin(), departure.end());

	// create a count array initialized by 0
	vector<int> count(t + 2);

	// fill the count array with guests count using the array index to store time
	for (int i = 0; i < arrival.size(); i++)
	{
		for (int j = arrival[i]; j <= departure[i]; j++)
		{
			count[j]++;
		}
	}

	// keep track of the time when there are maximum guests
	int max_event_tm = 0;

	// find the index of the maximum element in the count array
	for (int i = 0; i <= t; i++)
	{
		if (count[max_event_tm] < count[i])
		{
			max_event_tm = i;
		}
	}

	cout << "Event Time: " << max_event_tm << endl;
	cout << "The Maximum number of guests is " << count[max_event_tm] << endl;

}

2. Using Sorting (Linearithmic Time Solution)
The idea is to sort the arrival and departure times of guests and use the merge routine of the merge sort algorithm to process them together as a single sorted array of events. We maintain a counter to store the count number of guests present at the event at any point. While processing all events (arrival & departure) in sorted order,

If the next event is arrival, increase the number of guests by one and update the maximum guest’s count found so far if the current guest’s count is more.
If the next event is a departure, decrease the guest’s count by 1.
By following this process, we can keep track of the total number of guests at any time (guests that have arrived but not left). The time complexity of this approach is O(n.log(n)) and doesn’t require any extra space, where n is the total number of guests. Following is the C++

// function to find the point when the maximum number of guest are prsent in an event
void findMaxGuests(vector<int> arrival, vector<int> departure)
{
	// sort the arrival and departure arrays in increasing order
	sort(arrival.begin(), arrival.end());
	sort(departure.begin(), departure.end());

	int checked_in = 0; // keep track of the total number of guests at any time
	int max_checked_in = 0; //keep track of the maximum number of guest in the event
	int max_event_tm = 0; // keep track of the time when there are maximum guests
//	 the following code is similar to the merge routine of the merge sort

	// process all events (arrival & departure) in sorted order
for (int i = 0, j = 0; i < arrival.size() && j < departure.size();)
{
	// if the next event is arrival
	if (arrival[i] <= departure[i])
	{
		// increment number of guests
		checked_in++;

		// update the maximum count of guests if needed
		if (max_checked_in < checked_in)
		{
			max_checked_in = checked_in;
			max_event_tm = arrival[i];
		}
		// increment index of arrival array
		i++;
	}

	// if the next event is a departure
	else {
		// decrement number of guests
		checked_in--;

		// increment index of departure array
		j++;
	}
}
cout << "Event Time: " << max_event_tm << endl;
cout << "The Maximum number of guests is " << max_checked_in << endl;
}

Using Extra Space (Linear Time Solution)
We can improve solution #1 to run in linear time. The idea is to store only arrival and departure times in a count array instead of filling all values in an interval. This is done by increasing the value at the arrival time by one and decreasing the value after departure time by one.

After all guest logs are processed, perform a prefix sum computation to determine the exact guest count at each point, and get the index with maximum value. This index would be the time when there were maximum guests present in the event.

The time complexity of the above solution is O(n), but requires O(n) extra space. Following is the C++

*/

// function to find the point when the maximum number of guest are present in an event
void findMaxGuests(vector<int> const& arrival, vector<int> const& departure)
{
	// find the time when the last guest leaves the event
	int t = *max_element(departure.begin(), departure.end());

	// create a count array initialized by 0
	vector<int> count(t + 2);

	for (int i = 0; i < arrival.size(); i++)
	{
		count[arrival[i]]++;
		count[departure[i] + 1]--;
	}

	// keep track of the time when there are maximum guests
	int max_event_tm = count[0];

	// perform a prefix sum computation to determine the guest count at each point
	for (int i = 1; i <= t; i++)
	{
		count[i] += count[i - 1];
		if (count[max_event_tm] < count[i]) {
			max_event_tm = i;
		}
	}

	cout << "Event Time: " << max_event_tm << endl;
	cout << "The Maximum number of guests is " << count[max_event_tm] << endl;

}

int main()
{
	vector<int> arrival = { 1, 2, 4, 7, 8, 12 };
	vector<int> departure = { 2, 7, 8, 12, 10, 15 };

	findMaxGuests(arrival, departure);

	return 0;
}

/*

*/