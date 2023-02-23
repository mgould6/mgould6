#include "Header.h";

using namespace std;

/*
Find the index of 0 to be replaced to get the maximum length sequence of continuous ones

Given a binary array, find the index of 0 to be replaced with 1 to get the maximum length sequence of continuous ones.

For example, consider the array { 0, 0, 1, 0, 1, 1, 1, 0, 1, 1 }. We need to replace index 7 to get the continuous sequence of length 6 containing all 1’s.

Practice This Problem


We can efficiently solve this problem in linear time and constant space. The idea is to traverse the given array and maintain an index of the previous zero encountered. We can then easily find out the total number of 1’s between the current zero and the last zero for each subsequent zeroes. For each element, check if the maximum sequence of continuous 1’s ending at that element (including the last zero, which is now replaced by 1) exceeds the maximum sequence found so far. If yes, update the maximum sequence to the current sequence length and index of optimal zero and index the last zero encountered.

The algorithm can be implemented as follows in C,
*/

int maxLength(int arr[], int n)
{
	int max_count = 0;
	int max_index = -1;

	int prev_zero_index = -1;
	int count = 0;

	//consider each element in the array
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == 1)
		{

			count++;
		}
		else
		{
			count = i - prev_zero_index;

			prev_zero_index = i;
		}

		if (count > max_count)
		{
			max_count = count;
			max_index = prev_zero_index;

		}
	}
	//returns the index of 0 to be replaced or -1 if the array contains all 1s
	return max_index;
}


int main()
{

	int arr[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1, 1 };
	int n = sizeof(arr) / sizeof(arr[0]);


	int index = maxLength(arr, n);

	if (index != -1)
	{
		printf("Index to be replaced is %d", index);
	}
	else
	{
		printf("Invalid input");
	}

	return 0;
}

