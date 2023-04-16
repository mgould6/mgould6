#include "Header.h";

using namespace std;

/*
Given a set of activities and the starting and finishing time of each activity, find the maximum number of activities that can be performed by a single person assuming that a person can only work on a single activity at a time.

This problem is called the activity selection problem, which concerns the selection of non-conflicting activities to perform within a given time frame, given a set of activities each marked by a start and finish time.

For example,

Input:

{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}

Output:

{1, 4}, {5, 7}, {8, 11}, {12, 14}
Practice This Problem

In the previous post, we have discussed a greedy approach for activity selection problem. This post will discuss a dynamic programming solution for the activity selection problem, which is nothing but a variation of the Longest Increasing Subsequence (LIS) problem.

The idea is first to sort given activities in increasing order of their start time. Let jobs[0…n-1] be the sorted array of activities. We can define an array L such that L[i] itself is an array that stores maximum non-conflicting jobs ending at i'th job. Therefore, L[i] can be recursively written as:

L[i] = jobs[i] + { max(L[j]), where j < i and jobs[j].end < jobs[i].start }
     = jobs[i], if there is no such j
For example, consider the following sorted activities:

{0, 6} {1, 4} {2, 13} {3, 5} {3, 8} {5, 7} {5, 9} {6, 10} {8, 11} {8, 12} {12, 14}
Then L[] would be:

L[0]: {0, 6}
L[1]: {1, 4}
L[2]: {2, 13}
L[3]: {3, 5}
L[4]: {3, 8}
L[5]: {1, 4} {5, 7}
L[6]: {1, 4} {5, 9}
L[7]: {1, 4} {6, 10}
L[8]: {1, 4} {5, 7} {8, 11}
L[9]: {1, 4} {5, 7} {8, 12}
L[10]: {1, 4} {5, 7} {8, 11} {12, 14}
1. Count the maximum number of non-conflicting jobs:

The algorithm can be implemented as follows in C++

The time complexity of the above solution is O(n2) and requires O(n) extra space, where n is the total number of given activities.

2. Print the maximum number of non-conflicting jobs:

The algorithm can be implemented as follows in C++,


The time complexity of the above solution is O(n2) and requires O(n2) extra space, where n is the total number of given activities.
*/

// Data structure to store the start and finish time of the jobs.
struct Job
{
    int start;
    int finish;
};

// Returns the maximum count of non-conflicting jobs that can be performed
// by a single person
int findNonConflictingJobsLength(vector<Job> jobs)        // no-ref, no-const
{
    // sort the jobs according to increasing order of their start time
    sort(jobs.begin(), jobs.end(),
        [](Job& x, Job& y) {
            return x.start < y.start;
        });

    // L[i] stores the maximum count of non-conflicting jobs ending at i'th job
    vector<int> L(jobs.size());

    for (int i = 0; i < jobs.size(); i++)
    {
        // consider each `j` less than `i`
        for (int j = 0; j < i; j++)
        {
            // L[i] = max(L[j]), where `jobs[j].finish` is less than `jobs[i].start`
            if (jobs[j].finish < jobs[i].start && L[i] < L[j]) {
                L[i] = L[j];
            }
        }

        // increment L[i] since it ends at the i'th job
        L[i]++;
    }

    // return the maximum job length in the vector
    return *max_element(L.begin(), L.end());
}

int main()
{

    // Each pair stores the start and the finish time of a job
    vector<Job> jobs =
    {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
    };

    cout << "The maximum number of non-conflicting jobs is "
        << findNonConflictingJobsLength(jobs);
    return 0;
}

/*

*/