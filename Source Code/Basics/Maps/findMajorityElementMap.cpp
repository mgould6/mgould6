#include "Header.h";

using namespace std;

/*
Find majority element (Boyer–Moore Majority Vote Algorithm)
Given an integer array containing duplicates, return the majority element if present. A majority element appears more than n/2 times, where n is the array size.

For example, the majority element is 2 in array {2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2}.
*/

int findMajorityElement(int arr[], int n)
{
	//create empty map
	unordered_map<int, int> map;

	//iterate through array and store element frequency in a map
	for (int i = 0; i < n; i++)
	{
		map[arr[i]]++;
	}

	//return the element if the count is more than n/2

	for (auto pair : map)
	{
		if (pair.second > n / 2)
		{
			return pair.first;
		}
	}

	//return -1 if no majority element is present
	return -1;
}


int main()
{

	int arr[] = { 2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int result = findMajorityElement(arr, n);

	if (result != -1)
	{
		cout << "Majority Element is: " << result;
	}
	else
	{
		cout << "The majority element doesn't exist";
	}

	return 0;
}


