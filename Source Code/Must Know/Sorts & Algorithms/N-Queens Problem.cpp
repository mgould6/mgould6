#include "Header.h";

using namespace std;

/*

Print all possible solutions to N–Queens problem
Google Translate Icon
The N–queens puzzle is the problem of placing N chess queens on an N × N chessboard so that no two queens threaten each other. Thus, the solution requires that no two queens share the same row, column, or diagonal.

For example, for a standard 8 × 8 chessboard, below is one such configuration:

  Q  –  –  –  –  –  –  –
  –  –  –  –  Q  –  –  –
  –  –  –  –  –  –  –  Q
  –  –  –  –  –  Q  –  –
  –  –  Q  –  –  –  –  –
  –  –  –  –  –  –  Q  –
  –  Q  –  –  –  –  –  –
  –  –  –  Q  –  –  –  –
Note that the solution exists for all natural numbers n, except for n = 2 and n = 3.

Practice This Problem


We can solve this problem with the help of backtracking. The idea is to start from the first row and place Queen in each square of the first row and recursively explore the remaining rows to check if they lead to the solution or not. If the current configuration doesn’t result in a solution, backtrack. Before exploring any square, ignore the square if two queens threaten each other.

The algorithm can be implemented as follows in C

The time complexity of the above backtracking solution is exponential.


Optimizations: The time complexity of the above backtracking algorithm can be improved using Branch and Bound. In a backtracking solution, we backtrack on hitting a dead end, but in branch and bound, after building a partial solution, we figure out that there is no point going any deeper as we are going to hit a dead end. The N–Queen branch and bound solution is discussed here. https://developers.google.com/optimization/cp/queens


*/


//N x N chessboard
#define N 8

// Function to check if two queens threaten each other or not
int isSafe(char mat[][N], int r, int c)
{
	// return 0 if two queens share the same column
	for (int i = 0; i < r; i++)
	{
		if (mat[i][c] == 'Q') {
			return 0;
		}
	}

	// return 0 if two queens share the same `\` diagonal
	for (int i = r, j = c; i >= 0 && j >= 0; i--, j--)
	{
		if (mat[i][j] == 'Q') {
			return 0;
		}
	}

	// return 0 if two queens share the same `/` diagonal
	for (int i = r, j = c; i >= 0 && j < N; i--, j++)
	{
		if (mat[i][j] == 'Q') {
			return 0;
		}
	}

	return 1;
}

void printSolution(char mat[][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



//function to determine number of queens
void nQueen(char mat[][N], int r)
{
	//if N queens are placed successfully print the solution
	if (r == N)
	{
		printSolution(mat);
		return;
	}

	//place queen at every square in the current row r
	//and recur for each valid movement
	for (int i = 0; i < N; i++)
	{
		//if no two queens threaten eachother
		if (isSafe(mat, r, i))
		{
			//place queen on the current square
			mat[r][i] = 'Q';
			//recur for the next row
			nQueen(mat, r + 1);

			//backtrack and remove the queen from the current square
			mat[r][i] = '-';
		}
	}
}



int main()
{
	// `mat[][]` keeps track of the position of queens in the current configuration
	char mat[N][N];

	// initialize `mat[][]` by `-`
	memset(mat, '-', sizeof mat);

	nQueen(mat, 0);

	return 0;
}

/*

*/