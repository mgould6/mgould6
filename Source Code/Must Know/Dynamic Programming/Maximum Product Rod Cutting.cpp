#include "Header.h";

using namespace std;

/*
Maximum Product Rod Cutting
Given a rod of length n, find the optimal way to cut the rod into smaller rods to maximize the product of each of the smaller rod’s price. Assume that each rod of length i has price i.

For example, consider the following rod of length 4:


Best: Cut the rod into two pieces of length 2 each to gain revenue of 2×2 = 4

Cut            Profit
4                4
1, 3            (1 × 3) = 3
2, 2            (2 × 2) = 4
3, 1            (3 × 1) = 3
1, 1, 2         (1 × 1 × 2) = 2
1, 2, 1         (1 × 2 × 1) = 2
2, 1, 1         (2 × 1 × 1) = 2
1, 1, 1, 1      (1 × 1 × 1 × 1) = 1


Similarly, for n = 6, (3 × 3) = 9
For n = 8, (2 × 3 × 3) = 18
For n = 15, (3 × 3 × 3 × 3 × 3) = 243
Practice This Problem

The idea is simple. First, partition the given rod of length n into two parts of length i and n-i for each 1 <= i <= n. Then recur for the rod of length n-i but don’t divide rod of length i any further. Finally, take a maximum of all values. This yields the following recursive relation:

rodcut(n) = max { n, i * rodcut(n – i) } where 1 <= i <= n
The algorithm can be implemented as follows in C++

// Function to find the best way to cut a rod of length `n`
// where the rod of length `i` has price `i`
int findMaxProfit(int n)
{
    // base case
    if (n <= 1) {
        return n;
    }

    // rod of length `n` has at least cost of `n`
    int maxValue = n;

    // one by one, partition the given rod of length `n` into two parts of
    // length (1, n-1), (2, n-2), … (n-1 , 1), (n, 0) and take maximum
    for (int i = 1; i <= n; i++) {
        maxValue = max(maxValue, i * findMaxProfit(n - i));
    }

    return maxValue;
}

The time complexity of the above solution is O(nn) and occupies space in the call stack, where n is the rod length.



We have seen that the problem can be broken down into smaller subproblems, which can further be broken down into yet smaller subproblems, and so on. So, the problem has optimal substructure. Let’s consider a recursion tree for the rod of length 4.

Rod cutting problem

As we can see, the same subproblems (highlighted in the same color) are getting computed repeatedly. So, the problem also exhibits overlapping subproblems. We know that problems with optimal substructure and overlapping subproblems can be solved by dynamic programming, where subproblem solutions are memoized rather than computed and again.

We will solve this problem in a bottom-up manner. In the bottom-up approach, we solve smaller subproblems first, then solve larger subproblems from them. The following bottom-up approach computes T[i], which stores the maximum profit achieved from the rod of length i for each 1 <= i <= n. It uses the value of smaller values i already computed.

Following is the C++
*/

int findMaxProfit(int n)
{
    // `T[i]` stores the maximum profit achieved from the rod of length `i`.
    int* T{ new int[n + 1] {} };
    // A rod of length `i` has at least cost `i`
    for (int i = 0; i <= n; i++) {
        T[i] = i;
    }

    // consider rod of length `i`
    for (int i = 2; i <= n; i++)
    {
        // divide the rod of length `i` into two rods of length `j`
        // and `i-j` each and take maximum
        for (int j = 1; j <= i; j++) {
            T[i] = max(T[i], j * T[i - j]);
        }
    }

    // `T[n]` stores the maximum profit achieved from the rod of length `n`
    return T[n];
}

int main()
{
    // rod length
    int n = 15;

    cout << "The maximum profit is " << findMaxProfit(n);

    return 0;
}


/*

*/