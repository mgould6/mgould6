#include "Header.h";

using namespace std;

/*
Find maximum profit earned by buying and selling shares any number of times
Given a list containing future prediction of share prices, find the maximum profit earned by buying and selling shares any number of times with the constraint, a new transaction can only start after the previous transaction is complete, i.e., we can only hold at most one share at a time.

For example,

Stock Prices: {1, 5, 2, 3, 7, 6, 4, 5}

Total profit earned is 10

Buy on day 1 and sell on day 2
Buy on day 3 and sell on day 5
Buy on day 7 and sell on day 8


Stock Prices: {10, 8, 6, 5, 4, 2}

Total profit earned is 0
Practice This Problem

There are several variations to the above problem:

If we are allowed to stock only once, we can find the maximum difference between two elements in the array, where the smaller element appears before the larger element.
If we are allowed to stock shares at most twice, we can follow the approach discussed here.
If we are allowed to stock shares at most k times, we can follow the approach discussed here.

The current problem allows us to make unlimited stock transactions. The idea is to traverse the given list of prices and find a local minimum of every increasing sequence. For example, the increasing sequences of length 2 or more in the array {1, 5, 2, 3, 7, 6, 4, 5} are {1, 5}, {2, 3, 7}, and {4, 5}. The local minimum of each sequence is 1, 2 and 4, respectively. We can gain maximum profit if we buy the shares at the starting of every increasing sequence (local minimum) and sell them at the end of the increasing sequence (local maximum).

Following is the C
*/
int findMaxProfit(int price[], int n)
{
	int profit = 0;

	//initialize local minimum to the first elements index
	int j = 0;

	//traverse the array starting from the second element
	for (int i = 1; i < n; i++)
	{

		//update the local minimum if a decreasing sequence is found
		if (price[i - 1] > price[i])
		{
			j = i;
		}

		//sell shares if the current element is the peak
		//i.e. previous <= current > next
		if (price[i - 1] <= price[i] && i + 1 == n || price[i] > price[i + 1])
		{
			profit += (price[i] - price[j]);
			printf("buy on day %d and sell on day %d\n", j + 1, i + 1);
		}

	}
	return profit;

}

int main()
{
	int price[] = { 1, 5, 2, 3, 7, 6, 4, 5 };
	int n = sizeof(price) / sizeof(price[0]);

	printf("\nTotal profit earned is %d", findMaxProfit(price, n));

	return 0;
}

