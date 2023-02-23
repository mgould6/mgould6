#include "Header.h";

using namespace std;

/*
Find a triplet with the given sum in an array
Given an unsorted integer array, find a triplet with a given sum in it.

For example,

Input:

nums = [ 2, 7, 4, 0, 9, 5, 1, 3 ]
target = 6

Output: Triplet exists.

The triplets with the given sum 6 are {0, 1, 5}, {0, 2, 4}, {1, 2, 3}
Practice This Problem

The problem is a standard variation of the 3SUM problem, where instead of looking for numbers whose sum is 0, we look for numbers whose sum is any constant C.


*/

/*
3. Printing distinct triplets
The idea is to sort the given array in ascending order, and for each element nums[i] in the array, check if the triplet is formed by nums[i] and a pair from subarray nums[i+1…n). This is demonstrated below in C++

O(n^2) doesn't require extra space
*/

bool tripletSumSort(int arr[], int n, int target)
{
	//sort the array in ascending order
	sort(arr, arr + n);

	//check if the triplet is formed by arr[i] and a pair from subarray nums [i+1.... n]s

	for (int i = 0; i < n - 3; i++)
	{
		//set a variable holding the remaining sum
		int k = target - arr[i];

		//set two indices pointing to the endpoits of the subarray [i+ 1... n]
		int low = i + 1, high = n - 1;

		while (low < high)
		{
			if (arr[low] + arr[high] < k)
			{
				low++;
			}
			else if (arr[low] + arr[high] > k)
			{
				high--;
			}
			else
			{
				//print the triplet
				cout << "[" << arr[i] << " " << arr[low] << " " << arr[high] << " ]";

				//increment low and decrement high to exit the loop

				low++, high--;
			}
		}

	}
}

int main()
{
	int arr[] = { 2, 7, 4, 0, 9, 5, 1, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int target = 6;

	tripletSumSort(arr, n, target) ? cout << "Triplet Exists" : cout << "Triplet Does Not Exist";

	return 0;
}


/*
*
using hashing
The idea is to insert each array element into a hash table. Then consider all pairs present in the array and check if the remaining sum exists in the map or not. If the remaining sum is seen before and triplet doesn’t overlap with each other, i.e., (i, j, i) or (i, j, j), print the triplet and return. The algorithm can be implemented as follows in C++, Java, and Python:

The time complexity of the above solution is O(n2) and requires O(n) extra space, where n is the size of the input.



bool tripletSumHash(int arr[], int n, int target)
{
	//create map to store elements
	unordered_map<int, int> map;

	//traverse array and store elements into map
	for (int i = 0; i < n; i++)
	{
		map[arr[i]] = i;
	}

	//consider each element except the last element
	for (int i = 0; i < n - 1; i++)
	{
		//start from i'th element until the last element
		for (int j = i + 1; j < n; j++)
		{
			//remaining sum
			int val = target - (arr[i], arr[j]);

			//if the remaining sum is found, we have found a triplet
			if (map.find(val) != map.end())
			{
				//if the triplet doesn't overlap return true
				if (map[val] != i && map[val] != j)
				{
					return true;
				}

			}
		}
	}
	//return false if the triplet doesn't exist
	return false;

}


*/
//naive recursive function
//bool tripletSum(int arr[], int n, int target, int count)
//{
//	//
//	if (count == 3 && target == 0)
//	{
//		return true;
//	}
//
//	//return false if the sum is not possible with the current configuration
//	if (count == 3 || n == 0 || target < 0)
//	{
//		return false;
//	}
//	
//	//recur with including and ecluding the current element
//	return tripletSum(arr, n - 1, target - arr[n - 1], count + 1) || tripletSum(arr, n - 1, target, count);
//}


