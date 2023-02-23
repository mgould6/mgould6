#include "Header.h";

using namespace std;

/*
3–Partition Problem
Google Translate Icon
3-partition problem: Given a set S of positive integers, determine if it can be partitioned into three disjoint subsets that all have the same sum, and they cover S.

The 3–partition problem is a special case of the Partition Problem, which is related to the Subset Sum Problem (which itself is a special case of the Knapsack Problem). The goal is to partition S into two subsets with an equal sum in the partition problem. In the 3–partition problem, the goal is to partition S into 3 subsets with an equal sum.


For example,

S = { 7, 3, 2, 1, 5, 4, 8 }

We can partition S into three partitions, each having a sum of 10.

S1 = { 7, 3 }
S2 = { 5, 4, 1 }
S3 = { 8, 2 }

Note that there can be multiple solutions to a single set.

Practice This Problem

We can start by calculating the sum of all St in the set. If St is not divisible by 3, we can’t divide the array into three subsets with an equal sum. If St is divisible by 3, check if 3 subsets with the sum of elements equal to St/3 exists or not. We can find this by considering each item in the given array one by one, and for each item, there are three possibilities:

Include the current item in the first subset and recur for the remaining items with the remaining sum.
Include the current item in the second subset and recur for the remaining items with the remaining sum.
Include the current item in the third subset and recur for the remaining items with the remaining sum.
The base case of the recursion would be when no items are left. We return true when 3 subsets, each with zero-sum, are found. We can optimize our code by calling case 2 only if case 1 doesn’t result in a solution, and case 3 only if case 1 and 2 don’t result in any solution.


The algorithm can be implemented as follows in C++
*/

// Helper function to 3–partition problem.
// It returns true if there exist three subsets with a given sum
bool isSubsetExist(vector<int> const& S, int n, int a, int b, int c, vector<int>& arr)
{
    // return true if the subset is found
    if (a == 0 && b == 0 && c == 0) {
        return true;
    }

    // base case: no items left
    if (n < 0) {
        return false;
    }

    // Case 1. The current item becomes part of the first subset
    bool A = false;
    if (a - S[n] >= 0)
    {
        arr[n] = 1;        // current element goes to the first subset
        A = isSubsetExist(S, n - 1, a - S[n], b, c, arr);
    }

    // Case 2. The current item becomes part of the second subset
    bool B = false;
    if (!A && (b - S[n] >= 0))
    {
        arr[n] = 2;        // current element goes to the second subset
        B = isSubsetExist(S, n - 1, a, b - S[n], c, arr);
    }

    // Case 3. The current item becomes part of the third subset
    bool C = false;
    if ((!A && !B) && (c - S[n] >= 0))
    {
        arr[n] = 3;        // current element goes to the third subset
        C = isSubsetExist(S, n - 1, a, b, c - S[n], arr);
    }

    // return true if we get a solution
    return A || B || C;
}

// Function for solving the 3–partition problem. It prints the subset if
// the given set `S[0…n-1]` can be divided into three subsets with an equal sum
void partition(vector<int> const& S)
{
    // get the sum of all elements in the set
    int sum = accumulate(S.begin(), S.end(), 0);

    // total number of items in `S`
    int n = S.size();

    // construct an array to track the subsets
    // `arr[i] = k` represents i'th item of `S` is part of k'th subset
    vector<int> arr(n);

    // set result to true if the sum is divisible by 3 and the set `S` can
    // be divided into three subsets with an equal sum
    bool result = (n >= 3) && !(sum % 3) &&
        isSubsetExist(S, n - 1, sum / 3, sum / 3, sum / 3, arr);

    if (!result)
    {
        cout << "3-Partition of set is not possible";
        return;
    }

    // print the partitions
    for (int i = 0; i < 3; i++)
    {
        cout << "Partition " << i << " is ";
        for (int j = 0; j < n; j++)
        {
            if (arr[j] == i + 1) {
                cout << S[j] << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    // Input: a set of integers
    vector<int> S = { 7, 3, 2, 1, 5, 4, 8 };

    partition(S);

    return 0;
}

/*

*/