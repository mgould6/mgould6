#include "Header.h";

using namespace std;

/*
Young Tableau | Insert, Search, Extract-Min, Delete, Replace
Google Translate Icon
An M × N Young tableau is an M × N matrix such that the entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry. Thus, a Young tableau can be used to hold n <= M*N finite numbers.

For example, the following matrix is a Young tableau:

Young tableau


In this post, we will see how to

Delete an element in an M × N Young tableau in O(M + N) time.
The idea is simple and inspired from the Extract-Min operation on the Young tableau. To delete an element present at cell (i, j), make it as infinity and then fix the Young tableau property of submatrix formed by (i, j), (i, N-1), (M-1, j), and (M-1, N-1).

The algorithm can be implemented as follows in C++

The time complexity of the delete operation is O(M + N), and the auxiliary space used by the program is O(M + N) for the call stack. Here, M and N are dimensions of the matrix.


*/
// Recursive function to fix the tableau property in an MxN young tableau
void fixTableau(vector<vector<int>>& tableau, int i, int j)
{
	// MxN young tableau
	int M = tableau.size();
	int N = tableau[0].size();

	// get the values present at the bottom and right cell of the current cell
	int bottom = (i + 1 < M) ? tableau[i + 1][j] : INT_MAX;
	int right = (j + 1 < N) ? tableau[i][j + 1] : INT_MAX;

	if (bottom == INT_MAX && right == INT_MAX)
	{
		return;
	}

	// go down
	if (bottom < right)
	{
		swap(tableau[i][j], tableau[i + 1][j]);
		fixTableau(tableau, i + 1, j);
	}

	// go right
	if (right < bottom)
	{
		swap(tableau[i][j], tableau[i][j + 1]);
		fixTableau(tableau, i, j + 1);
	}
}

// Function to delete a given element from the young tableau
void deletion(vector<vector<int>>& tableau, int i, int j)
{
	// base case
	if (tableau.size() == 0 || i >= tableau.size() || j >= tableau[0].size())
	{
		return;
	}

	// to delete the element at cell (i,j) make it infinity
	tableau[i][j] = INT_MAX;

	// fix the young tableau property
	fixTableau(tableau, i, j);
}

// utility function to print a young tableua
void printTableau(vector<vector<int>> const& tableau)
{
	for (int i = 0; i < tableau.size(); i++)
	{
		for (int j = 0; j < tableau[0].size(); j++)
		{
			cout << tableau[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	// M × N Young tableau
	vector<vector<int>> tableau =
	{
		{ 10, 12, 15, 16 },
		{ 11, 18, 20, 25 },
		{ 22, 27, 30, 35 },
		{ 34, 40, 44, 45 }
	};

	deletion(tableau, 1, 2);    // delete 20
	printTableau(tableau);

	return 0;
}

/*

*/