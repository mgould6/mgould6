#include "Header.h";

using namespace std;

/*
Print all combinations of positive integers in increasing order that sums to a given number
Google Translate Icon
Write code to print all combinations of positive integers in increasing order that sum to a given positive number.

For example,

Input:  N = 3

1 1 1
1 2
3

Input:  N = 4

1 1 1 1
1 1 2
1 3
2 2
4

Input:  N = 5

1 1 1 1 1
1 1 1 2
1 1 3
1 2 2
1 4
2 3
5
Practice This Problem

We can easily solve the problem using recursion by taking the help of an auxiliary array to store combinations. This approach is demonstrated below in C
*/

void printArray(int nums[], int n)
{
	for (int i = 0; i <= n; i++)
	{
		printf("%d", nums[i]);
	}
	printf("\n");
}

//recursive function to print all combinations of positive integers
//in increasing order that sum to a given number
void printCombinations(int nums[], int i, int sum, int sum_left)
{
	//to maintaim the increasing order, start the loop from 
	//previous number stored in nums[]
	int prev_num = (i > 0) ? nums[i - 1] : 1;
	for (int k = prev_num; k <= sum; k++)
	{
		//set the next array element to k
		nums[i] = k;

		//recur with the sum left and the next location in the array
		if (sum_left > k)
		{
			printCombinations(nums, i + 1, sum, sum_left - k);
		}

		//if the sum is found
		if (sum_left == k)
		{
			printArray(nums, i);
		}
	}
}

//wrapper over printcombinations() function
void findCombinations(int sum)
{
	//create a temporary array for storing the combinations
	int* nums{ new int[sum] {} };

	//recur for all combinations
	int starting_index = 0;
	printCombinations(nums, starting_index, sum, sum);


}

int main()
{
	int sum = 5;
	findCombinations(sum);


	return 0;
}

/*

*/