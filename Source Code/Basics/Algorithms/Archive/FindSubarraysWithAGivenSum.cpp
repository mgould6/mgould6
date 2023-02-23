#include "Header.h";

using namespace std;

/*
Find subarrays with a given sum in an array
Given an integer array, find subarrays with a given sum in it.

For example,

Input:

nums[] = { 3, 4, -7, 1, 3, 3, 1, -4 }
target = 7

Output:

Subarrays with the given sum are

{ 3, 4 }
{ 3, 4, -7, 1, 3, 3 }
{ 1, 3, 3 }
{ 3, 3, 1 }
Practice This Problem

Please note that the problem specifically targets subarrays that are contiguous (i.e., occupy consecutive positions) and inherently maintains the order of elements.

We can also use hashing to find subarrays with the given sum in an array by using a map of lists or a multimap for storing the end index of all subarrays having a given sum. The idea is to traverse the given array and maintain the sum of elements seen so far. At any index, i, let k be the difference between the sum of elements seen so far and the given sum. If key k is present on the map, at least one subarray has the given sum ending at the current index i, and we print all such subarrays.

Following is the implementation of the above algorithm in C++
*/


void printSubarray(int arr[], int i, vector<int>& input)
{
	for (int j : input)
	{
		cout << "[" << (j + 1) << "..." << i << "] --- { ";
		copy(arr + j + 1, arr + i + 1, ostream_iterator<int>(cout, " "));
		cout << "}\n";
	}
}

void findSubarraysHash(int arr[], int n, int target)
{
	//create an empty map
	unordered_map<int, vector<int>> map;

	//handle the case where the subarray with the given sum starts from the 0th index

	map[0].push_back(-1);

	int sum_so_far = 0;

	//traverse the array
	//sum of elements so far
	for (int i = 0; i < n; i++)
	{
		sum_so_far += arr[i];

		//check if at least one subarray exists with the given sum 
		auto itr = map.find(sum_so_far - target);
		if (itr != map.end())
		{
			//print all subarrays with the given sum
			printSubarray(arr, i, map[itr->first]);
		}


		//insert (target so far, current index) pair into the map of vectors
		map[sum_so_far].push_back(i);

	}




}


int main()
{
	int arr[] = { 3, 4, -7, 1, 3, 3, 1, -4 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int target = 7;


	findSubarraysHash(arr, n, target);

	return 0;
}


//a simple solution is to consider all subarraysand calculate the sum of their elements.If the sum of the subarray is equal to the given sum, print it.This approach is demonstrated below in C,
//
//void print(int arr[], int i, int j)
//{
//	printf("[%d...%d] ---- { ", i, j);
//	for (int k = i; k <= j; k++)
//	{
//		printf("%d ", arr[k]);
//	}
//	printf("}\n");
//}
//
//void findSubarrays(int arr[], int n, int target)
//{
//	for (int i = 0; i < n; i++)
//	{
//		int sum_so_far = 0;
//
//		//consider all subarrays starting from i and ending j
//
//		for (int j = i; j < n; j++)
//		{
//			sum_so_far += arr[j];
//
//			//if the sum so far is equal to the given sum
//			if (sum_so_far == target)
//			{
//				print(arr, i, j);
//			}
//
//		}
//
//
//	}
// }