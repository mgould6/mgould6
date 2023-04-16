#include "Header.h";

using namespace std;

/*
Young Tableau | Insert, Search, Extract-Min, Delete, Replace
Google Translate Icon
An M × N Young tableau is an M × N matrix such that the entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry. Thus, a Young tableau can be used to hold n <= M*N finite numbers.

For example, the following matrix is a Young tableau:

Young tableau


In this post, we will see how to

Replace an element in an M × N Young tableau in O(M + N) time.
To replace an element x with an element y in a Young tableau:

Start by searching x's position (i, j) in the tableau.
Replace the element at cell (i, j) by infinity and fix the Young tableau property.
Place the element y in the tableau’s bottom-right corner and move the key to its correct position in the tableau.
The algorithm can be implemented as follows in C++

The time complexity of the replace operation is O(M + N), and the auxiliary space used by the program is O(M + N) for the call stack. Here, M and N are dimensions of the matrix.


Exercise: Determine if a given matrix is Young tableau or not, i.e., check if the matrix is row-wise and column-wise sorted.


*/

// Recursive function to fix the tableau property in an MxN young tableau
void fixTableau(vector<vector<int>>& tableau, int i, int j)
{
	// M x N young tableau
	int M = tableau.size();
	int N = tableau[0].size();

	// get the values present at the bottom and right cell of the current cell
	int bottom = (i + 1 < M) ? tableau[i + 1][j] : INT_MAX;
	int right = (j + 1 < M) ? tableau[i][j + 1] : INT_MAX;

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
	if (right < bottom)
	{
		swap(tableau[i][j], tableau[i][j + 1]);
		fixTableau(tableau, i, j + 1);
	}
}

// Recursive function to insert a new element into a non full MxN young tableau
void insert(vector<vector<int>>& tableau, int i, int j)
{
	// base case 
	if (i == 0 && j == 0)
	{
		return;
	}

	// handle separately for the first row
	if (i == 0)
	{
		if (tableau[i][j] < tableau[i][j - 1])
		{
			swap(tableau[i][j], tableau[i][j - 1]);
			insert(tableau, i, j - 1);
		}
		return;
	}
	// handle separately for the first column
	if (j == 0)
	{
		if (tableau[i][j] < tableau[i - 1][j])
		{
			swap(tableau[i][j], tableau[i - 1][j]);
			insert(tableau, i - 1, j);
		}
		return;
	}

	//go up
	if (tableau[i][j] < tableau[i - 1][j])
	{
		swap(tableau[i][j], tableau[i - 1][j]);
		insert(tableau, i - 1, j);
	}

	// go left
	if (tableau[i][j] < tableau[i][j - 1])
	{
		swap(tableau[i][j], tableau[i][j - 1]);
		insert(tableau, i, j - 1);
	}

}

// Function to replace a given element in a Young tableau
void replace(vector<vector<int>>& tableau, int i, int j, int key)
{
	// delete the element at cell `(i, j)`
	tableau[i][j] = INT_MAX;

	// fix the Young tableau property
	fixTableau(tableau, i, j);

	// M × N Young tableau
	int M = tableau.size();
	int N = tableau[0].size();

	// place the given key in the bottom-right corner of the tableau
	tableau[M - 1][N - 1] = key;

	// move the key to its correct position in the tableau
	insert(tableau, M - 1, N - 1);
}

// Utility function to search an element in a Young tableau
void search(vector<vector<int>>& tableau, int key, int value)
{
	// base case
	if (tableau.size() == 0) {
		return;
	}

	// M × N Young tableau
	int M = tableau.size();
	int N = tableau[0].size();

	// start from the top-rightmost cell of the tableau, i.e., (0, N-1) cell
	int i = 0, j = N - 1;

	// run till tableau boundary is reached
	while (i < M && j >= 0)
	{
		// if the current element is less than the key, increment the row index
		if (tableau[i][j] < key) {
			i++;
		}

		// if the current element is more than the key, decrement the column index
		else if (tableau[i][j] > key) {
			j--;
		}

		// if the current element is equal to the key
		else {
			replace(tableau, i, j, value);
			return;
		}
	}
}

// Utility function to print a Young tableau
void printTableau(vector<vector<int>> const& tableau)
{
	for (int i = 0; i < tableau.size(); i++)
	{
		for (int j = 0; j < tableau[0].size(); j++) {
			cout << tableau[i][j] << ' ';
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

	search(tableau, 20, 14);    // replace 20 by 14
	printTableau(tableau);

	return 0;
}

/*

*/