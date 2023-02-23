#include "Header.h";

using namespace std;

/*
Water Jugs Problem
Suppose we are given n red and n blue water jugs, all of different shapes and sizes. All red jugs hold different amounts of water, as do the blue ones. Moreover, there is a blue jug for every red jug that holds the same amount of water and vice versa. The task is to efficiently group the jugs into pairs of red and blue jugs that hold the same amount of water. (Problem Source: CLRS)

A simple solution to group the jugs into pairs is to compare a red jug with each blue jug. Once we get the matching pair, group that pair, and repeat for the next red jug. This algorithm can be easily implemented, but it will perform at most n2 comparisons.


We can do better by using a randomized algorithm where the expected number of comparisons is n.log(n). The idea is analogous to the randomized Quicksort algorithm.

Randomly pick a jug from either red or blue jugs.
Partition the red jugs around the chosen jug such that it will be divided into two groups – red jugs smaller than the selected jug and those which are larger than the selected jug.
Once the red jugs have been divided, partition the blue jugs similarly – those which are smaller and those which are larger than the chosen jug.
Once the red and blue jugs are divided into two groups, repeat the process for the group of red and blue jugs that are smaller and larger than the chosen jug.
The expected number of comparisons performed by the above algorithm is the same as that of a randomized Quicksort algorithm, i.e., n.log(n) comparisons for n items. In the worst-case, the largest jug gets picked every time, which results in n2 comparisons.


Following is the implementation in C++

The time complexity of the above algorithm is the same as that of Quicksort, i.e., O(n.log(n)). The auxiliary space required by the algorithm is O(n) for the call stack.


There are several other variations of this problem which can be solved similarly:

Nuts & Bolts Problem: Given n nuts and n bolts of different shapes and sizes. The task is to match nuts with bolts, provided that a specific bolt can open each nut.
Lock & Key Problem: Given a box of n locks and n keys where each lock can be opened by only a specific key in the box. The task is to match locks with their keys.

*/

//utility function to print a vector 
void printVector(vector<int> const& A, string msg)
{
    cout << msg << ": ";
    for (int i : A) {
        cout << i << " ";
    }
    cout << endl;
}

//thie function is similar to the partition routine of the quicksort algorithm
//it partitions the specified array A[low, high] around pivot
//and returns the partition index
int partition(vector<int>& A, int low, int high, int pivot)
{
    int pIndex = low;
    for (int j = low; j < high; j++)
    {
        if (A[j] < pivot)
        {
            swap(A[pIndex], A[j]);
            pIndex++;
        }
        else if (A[j] == pivot)
        {
            swap(A[j], A[high]);
            j--;
        }
    }
    swap(A[pIndex], A[high]);
    return pIndex;
}

//group the jugs into pairs of red and blue jugs that hold the same amount of water
//this function is similar to the quicksort like routine
void findMatchingPairs(vector<int>& red, vector<int>& blue, int low, int high)
{
    //base case: if there is only one red jug and one blue jug
    //they must be of the same size
    if (low >= high)
    {
        return;
    }

    //randomly select a jug from either red or blue jugs
    int r = rand() % (high - low + 1) + low;
    int chosenJug = red[r]; //or use blue[r]

    //partition the red jugs around the chose jug
    int pivot = partition(red, low, high, chosenJug);

    //now partition the blue jugs around the chose jug
    partition(blue, low, high, chosenJug);

    //pivot now points to an index of the chosen jug in red/blue jubs

    //recur once the red and blue jugs are divided into two groups
    //around the chosen jug
    findMatchingPairs(red, blue, low, pivot - 1);
    findMatchingPairs(red, blue, pivot + 1, high);
}

int main()
{
    vector<int> red = { 6, 3, 2, 8, 7 };
    vector<int> blue = { 8, 6, 7, 2, 3 };

    int n = red.size();
    findMatchingPairs(red, blue, 0, n - 1);

    printVector(red, "Red jugs");
    printVector(blue, "Blue jugs");

    return 0;
}

/*

*/