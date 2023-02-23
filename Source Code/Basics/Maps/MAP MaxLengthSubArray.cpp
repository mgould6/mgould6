#include "Header.h";
using namespace std;

/*

Given an integer array, find the maximum length subarray having a given sum.

For example, consider the following array:

nums[] = { 5, 6, -5, 5, 3, 5, 3, -2, 0 }
target = 8


Subarrays with sum 8 are

{ -5, 5, 3, 5 }
{ 3, 5 }
{ 5, 3 }

The longest subarray is { -5, 5, 3, 5 } having length 4


*/

void findMaxLenSubarray(int nums[], int n, int S)
{
    unordered_map<int, int> map;

    //initialize first map value with <0,-1> to account for the target sum being 0
    map[0] = -1;

    int target_sum = 0;

    //stores the maximum length of subarray with sum 'S'
    int length = 0;

    //store the ending index of the maximum length subarray having sum S
    int ending_index = -1;
    for (int i = 0; i < n; i++)
    {
        //sum of elements so far
        target_sum += nums[i];


        //if the sum is found for the first time insert the sum with iterator value into map

        if (map.find(target_sum) == map.end())
        {
            map[target_sum] = i;
        }

        //update length and index of the max length 
        if (map.find(target_sum - S) != map.end() && length < i - map[target_sum - S])
        {
            length = i - map[target_sum - S];
            ending_index = i;
        }
    }
    //print the subarray

    cout << "[" << (ending_index - length + 1) << "," << ending_index << "]";

}

int main()
{
    int nums[] = { 5, 6, -5, 5, 3, 5, 3, -2, 0 };
    int target = 11;

    int n = sizeof(nums) / sizeof(nums[0]);

    findMaxLenSubarray(nums, n, target);

    return 0;
}


