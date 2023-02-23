#include "Header.h";

using namespace std;

/*
Find the area of the largest rectangle of 1’s in a binary matrix
Google Translate Icon
Given a rectangular binary matrix, calculate the area of the largest rectangle of 1's in it. Assume that a rectangle can be formed by swapping any number of columns with each other.

For example,

Input:

[0, 1, 0, 1, 1]
[1, 1, 0, 0, 1]
[1, 1, 0, 1, 1]
[1, 1, 1, 1, 1]

Output: The area of the largest rectangle of 1’s is 9

Explanation: The largest rectangle of 1’s can be formed by swapping column 3 with column 5.

[0, 1, 1, 1, 0]
[1, 1, 1, 0, 0]
[1, 1, 1, 1, 0]
[1, 1, 1, 1, 1]


Input:

[0, 1, 1, 0]
[1, 0, 0, 1]
[1, 1, 0, 1]
[1, 1, 1, 1]

Output: The area of the largest rectangle of 1’s is 6

Explanation: The largest rectangle of 1’s can be formed by swapping column 2 with column 4 or swapping column 3 with column 4.

[0, 0, 1, 1]
[1, 1, 0, 0]
[1, 1, 0, 1]
[1, 1, 1, 1]

OR

[0, 1, 0, 1]
[1, 0, 1, 0]
[1, 1, 1, 0]
[1, 1, 1, 1]
Practice This Problem

1. The idea is to create an auxiliary matrix aux of the same size as the input matrix and fill it with the count of consecutive 1's present in each column of the input matrix. For example, consider the following input matrix:

[0, 1, 0, 1, 1]
[1, 1, 0, 0, 1]
[1, 1, 0, 1, 1]
[1, 1, 1, 1, 1]

Here’s how the auxiliary matrix would look like after this step.

[0, 4, 0, 1, 4]
[3, 3, 0, 0, 3]
[2, 2, 0, 2, 2]
[1, 1, 1, 1, 1]


2. Next, create a count matrix count initialized with 0's and update it using elements of the auxiliary matrix aux as an index, i.e., for each cell (i, j) of the count matrix, do count[i][aux[i][j]] += 1. Here’s how the count matrix would look after this step:

[0, 1, 0, 0, 2]
[0, 0, 0, 3, 0]
[0, 0, 4, 0, 0]
[0, 5, 0, 0, 0]


3. Since the auxiliary matrix contains “count” of consecutive 1's in each column and the count matrix stores information about the total number of times that “count” appeared in each row, the maximum area of each cell (i, j) can be calculated by taking the product of each element aux[i][j] in the auxiliary matrix with its corresponding value count[i][aux[i][j]] in the count matrix. Here’s how the matrix would look like after this step.

[0, 8, 0, 1, 8]
[9, 9, 0, 0, 9]
[8, 8, 0, 8, 8]
[5, 5, 5, 5, 5]

The largest rectangle area of 1's is 9, which would be the largest value in the above matrix.


Following is the implementation of the above algorithm in C, Java, and Python. The solution is highly optimized to save space. For instance, instead of building an auxiliary array, the input matrix is updated with the count of consecutive 1's. Instead of using the count matrix, a count array is used for each row.

The time complexity of the proposed solution is O(M × N), where M is the total number of rows and N is the total number of columns in the input matrix. The auxiliary space required by the program is O(M).


*/

#define M 4
#define N 5

// Utility function to replace all non zero values in a matrix by 1
void resetMatrix(int mat[][N])
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] != 0) {
                mat[i][j] = 1;
            }
        }
    }
}

// Utility function to find the maximum of two numbers
int max(int x, int y)
{
    return (x > y) ? x : y;
}

// Function to calculate the area of the largest rectangle of 1's where swapping of 
// columns is allowed
int findMaxRectArea(int mat[][N])
{
    // update the matrix to store the counts of consecutive 1's present in each column
    for (int j = 0; j < N; j++)
    {
        // process each column from bottom to top
        for (int i = M - 2; i >= 0; i--)
        {
            if (mat[i][j] == 1)
            {
                mat[i][j] = mat[i + 1][j] + 1;
            }
        }
    }

    // keep track of the largest rectangle of 1's found so far
    int maxArea = 0;

    // traverse each row in the modified matrix to find the maximum area
    for (int i = 0; i < M; i++)
    {
        //create a count array for each row 'i'
        int count[M + 1] = { 0 };
        // process row i
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] > 0)
            {
                // increment value in the count array using the current element
                // as an index
                count[mat[i][j]] += 1;

                // the area can be calculated by multiplying the current 
                // element mat[i][j] with the corresponding value
                // in the count array count[mat[i][j]]
                maxArea = max(maxArea, mat[i][j] * count[mat[i][j]]);

            }
        }
    }

    //reset matrix before returning
    resetMatrix(mat);

    return maxArea;
}

int main()
{
    int mat[M][N] =
    {
        { 0, 1, 0, 1, 1 },
        { 1, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 1 },
        { 1, 1, 1, 1, 1 }
    };

    printf("The area of the largest rectangle of 1's is %d", findMaxRectArea(mat));

    return 0;
}

/*

*/