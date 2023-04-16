#include "Header.h";

using namespace std;

/*
4–Sum Problem | Quadruplets with a given sum
4-sum problem: Given an unsorted integer array, check if it contains four elements tuple (quadruplets) having a given sum.

For example,

Input:

nums = [ 2, 7, 4, 0, 9, 5, 1, 3 ]
target = 20

Output: Quadruplet exists.

Below are quadruplets with the given sum 20

(0, 4, 7, 9)
(1, 3, 7, 9)
(2, 4, 5, 9)


Efficient solution using Hashing
The idea is to consider every pair of elements in the array one by one and insert it into a hash table. For each pair of elements (i, j), calculate the remaining sum. If the remaining sum exists in the map and elements involved in the previous occurrence doesn’t overlap with the current pair, i.e., (i, j, i, y) or (i, j, x, i) or (i, j, j, y), or (i, j, x, j), print the quadruplet and return.

Following is the C++

The time complexity of the above solution is O(n3) and requires O(n2) extra space, where n is the size of the input.

*/

typedef pair<int, int> Pair;

bool quadSumHash(int arr[], int n, int target, int count)
{
	//create an empty map
	//key -> target of a pair in the array
	//value -> vector storing an index of every pair having that sum
	unordered_map<int, vector<Pair>> map;

	//consider each element except the last element
	for (int i = 0; i < n - 1; i++)
	{
		//start from the i'th element to the last element
		for (int j = i + 1; j < n; j++)
		{
			//calculate the remaining sum
			int val = target - (arr[i] + arr[j]);

			//if the remaining sum is found on the map, we have a quad
			if (map.find(val) != map.end())
			{
				//check every pair having a sum equal to the remaining sum
				for (auto pair : map.find(val)->second)
				{
					int x = pair.first;
					int y = pair.second;

					//if quad doesn't overlap, print and return true
					if ((x != i && x != j) && (y != i && y != j))
					{
						cout << "quad found: (" << arr[i] << ", " << arr[j] << ", " << arr[x] << ", " << arr[y] << ")";
						return true;
					}
				}
			}

		}
	}

	//return false if it does not exist
	return false;
}


int main()
{
	int arr[] = { 2, 7, 4, 0, 9, 5, 1, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int target = 20;

	if (!quadSumHash(arr, n, target, 0))
	{
		cout << "quad sum does not exist";
	}


	return 0;
}

//recursive implementation

//bool quadSum(int arr[], int n, int target, int count)
//{
//
//	//if desired sum is reached with 4 elements return true
//	if (target == 0 && count == 4)
//	{
//		return true;
//	}
//
//	//return false if sum is not possible with current config
//	if (count > 4 || n == 0)
//	{
//		return false;
//	}
//
//	//recur with:
//	//1. including the current element
//	//2. excluding the current element
//
//
//	return quadSum(arr, n - 1, target - arr[n - 1], count + 1) || quadSum(arr, n - 1, target, count);
//}