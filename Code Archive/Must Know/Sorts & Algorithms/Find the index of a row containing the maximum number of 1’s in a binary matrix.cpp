#include "Header.h";

using namespace std;

/*
Find the index of a row containing the maximum number of 1’s in a binary matrix
Given a binary M × N row-wise sorted matrix, find a row that contains the maximum number of 1's in linear time.

For example,

Input:

[ 0  0  0  1  1 ]
[ 0  0  1  1  1 ]
[ 0  0  0  0  0 ]
[ 0  1  1  1  1 ]
[ 0  0  0  0  1 ]

Output: The maximum 1’s are present in row 4
Practice This Problem

The idea is to start from the top-right corner of the matrix and do the following:

If the current cell has value 1, continue moving left till we encounter 0, or all columns are processed;
If the current cell has value 0, continue moving down till we encounter 1, or all rows are processed.
Finally, return the row index of the last cell in which we have seen 1. The algorithm can be implemented as follows in C++
The time complexity of the proposed solution is O(M + N) for an M × N matrix and doesn’t require any extra space.



*/
int findRowIndex(vector<vector<int>> const& mat)
{
    //base case 
    if (mat.size() == 0)
    {
        return 0;
    }

    // M x N matrix
    int M = mat.size();
    int N = mat[0].size();

    //(i,j) stores the current row and column index 
    int i, j;

    //stores row number with maximum index
    int row = -1;

    //start from the top right most cell of the matrix
    i = 0, j = N - 1;

    while (i <= M - 1 && j >= 0)
    {
        //move left if the current cell has value 1
        if (mat[i][j])
        {
            j--, row = i; //update row number 
        }
        else
        {
            i++;
        }
    }
    return row + 1;
}

int main()
{
    vector<vector<int>> mat =
    {
        { 0, 0, 0, 1, 1 },
        { 0, 0, 1, 1, 1 },
        { 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 1 }
    };

    int rowIndex = findRowIndex(mat);

    // rowIndex = 0 means no 1's are present in the matrix
    if (rowIndex) {
        cout << "The Maximum 1's are present in the row " << rowIndex;
    }

    return 0;
}

/*

*/