#include "Header.h";

using namespace std;

/*
Young Tableau | Insert, Search, Extract-Min, Delete, Replace
Google Translate Icon
An M × N Young tableau is an M × N matrix such that the entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry. Thus, a Young tableau can be used to hold n <= M*N finite numbers.

For example, the following matrix is a Young tableau:

Young tableau


In this post, we will see how to

Extract the minimum element from an M × N Young tableau in O(M + N) time.
Extract-Min operation in Young tableau
Practice This Problem

The minimum element is present at position (0, 0) in the tableau. To remove an element (i, j) from a tableau, replace the cell value by infinity and return the element. This causes the Young tableau to become unstable, and the submatrix formed by (i, j), (i, N-1), (M-1, j), and (M-1, N-1) violates the Young tableau property (the submatrix is not row-wise sorted and column-wise sorted anymore).

A Young tableau is similar to a heap where each cell (i, j) can be considered the root node. The bottom cell (i+1, j) and right cell (i, j+1) of a cell (i, j) can be considered as the left and right child of the root node.

The idea is to perform a procedure similar to HEAPIFY-DOWN to restore the Young tableau property. If (i, j) is larger than its neighbors, swap the smallest of (i+1, j) and (i, j+1) with (i, j). This restores the tableau property for cell (i, j) but reduces the problem for cell (i+1, j) or cell (i, j+1).

The algorithm can be recursively implemented as follows in C++,

The fixTableau() routine takes an M × N matrix and breaks it into either an (M-1) × N or an M × (N-1) matrix. So, the recurrence relation is:

T(M, N) = T(M-1, N) + T(M, N-1)

So, the overall time complexity of the Extract-Min operation on a Young tableau is O(M + N).
*/

// Recursive function to fix the tableau property in an MxN young tableau
// An infinite value is initially placed at the first cell (0,0) of the tableau
// The function works by swapping the smallest of [i+1, j] and [i, j+1] with
// [i,j] and recur for the smaller value
void fixTableau(vector<vector<int>>& tableau, int i, int j)
{
	// M × N Young tableau
	int M = tableau.size();
	int N = tableau[0].size();

	// get the values present at the bottom and right cell of the current cell
	int bottom = (i + 1 < M) ? tableau[i + 1][j] : INT_MAX;
	int right = (j + 1 < N) ? tableau[i][j + 1] : INT_MAX;

	if (bottom == INT_MAX && right == INT_MAX) {
		return;
	}

	if (bottom < right)        // go down
	{
		swap(tableau[i][j], tableau[i + 1][j]);
		fixTableau(tableau, i + 1, j);
	}
	else        // go right
	{
		swap(tableau[i][j], tableau[i][j + 1]);
		fixTableau(tableau, i, j + 1);
	}
}


// Function to extract the next minimum element from the young tableau
int replaceInYoungTableau(vector<vector<int>>& tableau)
{
	// Base case
	if (tableau.size() == 0)
	{
		exit(-1);
	}

	// The first cell of the tableau stores the minimum element 
	int min = tableau[0][0];

	// make the first element as infinity
	tableau[0][0] = INT_MAX;

	// Fix the young tableau property
	fixTableau(tableau, 0, 0);
	return min;
}



int main()
{
	vector<vector<int>> tableau =
	{
		{ 10, 12, 15, 16 },
		{ 11, 18, 20, 25 },
		{ 22, 27, 30, 35 },
		{ 34, 40, 44, 45 }
	};

	// M × N Young tableau
	int M = tableau.size();
	int N = tableau[0].size();


	// repeat `M×N` times
	for (int i = 0; i < M * N; i++) {
		cout << replaceInYoungTableau(tableau) << ' ';
	}

	return 0;
}

/*

*/