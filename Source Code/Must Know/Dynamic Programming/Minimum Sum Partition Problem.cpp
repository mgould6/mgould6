#include "Header.h";

using namespace std;

/*
Minimum Sum Partition Problem
Given a set of positive integers S, partition set S into two subsets, S1 and S2, such that the difference between the sum of elements in S1 and S2 is minimized. The solution should return the minimum absolute difference between the sum of elements of two partitions.

For example, consider S = {10, 20, 15, 5, 25}.


We can partition S into two partitions where the minimum absolute difference between the sum of elements is 5.

S1 = {10, 20, 5}
S2 = {15, 25}

Note that this solution is not unique. The following is another solution:

S1 = {10, 25}
S2 = {20, 15, 5}

Practice This Problem

This problem is an optimization version of the partition problem. The idea is to consider each item in the given set S one by one, and for each item, there are two possibilities:

Include the current item in subset S1 and recur for the remaining items.
Include the current item from the subset S2 and recur for the remaining items.
Finally, return the minimum difference we get by including the current item in S1 and S2. When there are no items left in the set, return the absolute difference between elements of S1 and S2.


Following is the C++

// partition set S into two subsets S1 and S2 such that the
// difference between the sum of elements in S1 and the sum
// of elements in S2 is minimized
int findMinAbsDiff(vector<int> const& S, int n, int S1, int S2)
{
    // base case if the list becomes empty return the absolute difference between both sets
    if (n < 0)
    {
        return abs(S1 - S2);
    }

    // case 1 include the current item in subset S1 and recur for the remaining items n-1
    int inc = findMinAbsDiff(S, n - 1, S1 + S[n], S2);

    // case 2 exclude the current item from subset S1 and recur for
    // the remaining items n-1
    int exc = findMinAbsDiff(S, n - 1, S1, S2 + S[n]);

    return min(inc, exc);
}
The time complexity of the above solution is exponential and occupies space in the call stack.


The problem has optimal substructure. That means the problem can be broken down into smaller, simple “subproblems”, which can further be divided into yet simpler, smaller subproblems until the solution becomes trivial. The above solution also exhibits overlapping subproblems. If we draw the solution’s recursion tree, we can see that the same subproblems are getting computed repeatedly.

We know that problems with optimal substructure and overlapping subproblems can be solved using dynamic programming, in which subproblem solutions are memoized rather than computed again and again.

Following is the memoized version in C++, Java, and Python that follows the top-down approach since we first break the problem into subproblems and then calculate and store values.





*/

// partitiion set S into two subsets S1 and S2 such that the
// difference between the sum of elements in S1 and the sum
// of elements in S2 is minimized
int findMinAbsDiff(vector<int> const& S, int n, int S1, int S2, unordered_map<string, int>& lookup)
{
    // base case if the list becomes empty return the absolut difference between both sets
    if (n < 0)
    {
        return abs(S1 - S2);
    }

    // construct a unique map key from dynamic elements of the input
    // note that we can uniquely indentify the subproblem with n and S1 only
    // as S2 is nothin but S-S1 where S is the sum of all elements
    string key = to_string(n) + "|" + to_string(S1);

    // if the subproblem is seen for the first time solve it and
    // store its result in a map
    if (lookup.find(key) == lookup.end())
    {
        // case 1 include the current item in subset S1 and recur for the reemaining items n-1
        int inc = findMinAbsDiff(S, n - 1, S1 + S[n], S2, lookup);

        // case 2 exclude the current item from subset S1 and recur for the remaining n-1 items
        int exc = findMinAbsDiff(S, n - 1, S1, S2 + S[n], lookup);

        lookup[key] = min(inc, exc);
    }
    return lookup[key];
}


int main()
{

    // Input: a set of items
    vector<int> S = { 10, 20, 15, 5, 25 };

    // total number of items
    int n = S.size();

    // create a map to store solutions to subproblems
    unordered_map<string, int> lookup;

    cout << "The minimum difference is " << findMinAbsDiff(S, n - 1, 0, 0, lookup);

    return 0;
}

/*

*/