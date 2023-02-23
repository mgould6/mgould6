#include "Header.h";

using namespace std;

/*
Shuffle an array using Fisher–Yates shuffle algorithm
Given an integer array, in-place shuffle it. The algorithm should produce an unbiased permutation, i.e., every permutation is equally likely.


Fisher–Yates shuffle is an algorithm to generate random permutations. It takes time proportional to the total number of items being shuffled and shuffles them in place. The algorithm swaps the element at each iteration at random among all remaining unvisited indices, including the element itself.

Here’s the complete algorithm:

— To shuffle an array ‘a’ of ‘n’ elements:
for i from n-1 down to 1 do
    j = random integer such that 0 <= j <= i
    exchange a[j] and a[i]

Following is the implementation of the above algorithm in C
*/


//function to swap A[i] and A[j] in an array
void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void shuffle(int arr[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        //generate a random number j such that 0 <= j <= i
        int j = rand() % (i + 1);

        //swap the current element with the randomly generated index
        swap(arr, i, j);

    }
}
int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // seed for random input
    srand(time(NULL));

    shuffle(arr, n);

    //print the shuffled array

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}

