#include "Header.h";

using namespace std;

/*
Print a spiral square matrix without using any extra space
Google Translate Icon
Given a positive number N, print an N × N spiral matrix containing numbers from 1 to N × N in a counterclockwise direction and without extra space.

For example,

Input: N = 5

Output:

25  24  23  22  21
10   9   8   7  20
11   2   1   6  19
12   3   4   5  18
13  14  15  16  17
Practice This Problem

If we are allowed to use extra space, allocate storage for an N × N matrix, and start filling out the matrix in spiral order for each element starting from N × N till 1. To maintain the spiral order, use four loops, each for the top, right, bottom, and left corner of the matrix.


Here’s how we can do it with constant space:

25  24  23  22  21
10  9   8   7   20
11  2   1   6   19
12  3   4   5   18
13  14  15  16  17
An N × N matrix has ceil(N/2) square cycles. A cycle is formed by i'th row, j'th column, j'th row and i'th column, where i varies from 1 to ceil(N/2) and j = (n-i+1).

The first cycle is formed by elements of its first row, last column, last row, and first column (marked by black). The first cycle consists of elements from N × N to (N-2) × (N-2) + 1, i.e., from 25 to 10 for N = 5.
The second cycle is formed by elements of the second row, second last column, second last row, and second column (marked by red). The second cycle consists of elements from (N-2) × (N-2) to (N-4) × (N-4) + 1, i.e., from 9 to 2 for N = 5.
The third cycle is formed by the third row, third-last column, third-last row, and third column (marked by blue). The third cycle consists of elements from (N-4) × (N-4) to 1, i.e., only element 1 for N = 5.
The idea is for each square cycle, associate a marker to it. The marker will have the value 0 for the outer cycle, for the second cycle will have value 1, and it has value 2 for the third cycle. In general, for an N × N matrix, the i'th cycle will have a marker value of i-1.

 25  24  23  22  21
 10  9   8   7   20
 11  2   1   6   19
 12  3   4   5   18
 13  14  15  16  17
If we divide the matrix into two parts – upper right triangle (marked by red) and lower left triangle (marked by blue), as shown above, then using marker x we can easily calculate the value that will be present at index (i, j) in any N × N spiral matrix with the following formula:

For upper right half, M[i][j] = (N-2x) × (N-2x)-(i-x)-(j-x).
For lower left half, M[i][j] = (N-2x-2) × (N-2x-2) + (i-x) + (j-x).
Following is the implementation in C++
*/

// function to prints an N x N spiral without using any extra space
// the matrix contains numbers from 1 to N x N
void printSpiralMatrix(int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; i < N; j++)
		{
			// x stores the layer in which (i, j) element lies
			int x;

			// find a minimum of four inputs
			x = min(min(i, j), min(N - 1 - i, N - 1 - j));

			// print upper right half
			if (i <= j)
			{
				cout << (N - 2 * x) * (N - 2 * x) - (i - x) - (j - x);
			}
			else {
				cout << (N - 2 * x - 2) * (N - 2 * x - 2) + (i - x) + (j - x);
			}

			cout << '\t';
		}
		cout << endl;
	}
}

int main()
{
	int N = 5;

	printSpiralMatrix(N);

	return 0;
}

/*

*/