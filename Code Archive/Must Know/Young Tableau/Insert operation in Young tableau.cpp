#include "Header.h";

using namespace std;

/*
Young Tableau | Insert, Search, Extract-Min, Delete, Replace
Google Translate Icon
An M × N Young tableau is an M × N matrix such that the entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry. Thus, a Young tableau can be used to hold n <= M*N finite numbers.

For example, the following matrix is a Young tableau:

Young tableau


In this post, we will see how to

Insert a new element into a non-full M × N Young tableau in O(M + N) time.
To insert an element into a non-full Young tableau, the idea is to place the element in the bottom-right corner of the tableau and then move it upwards and leftwards to its correct position within the tableau. This is demonstrated below in C++
The time complexity for the insert operation is O(M + N), while the overall time complexity to construct an M × N Young tableau from a given list of elements is O(M × N × (M + N)). The additional space used by the program is O(M + N) for the call stack.
*/

// Recursive function to insert a new element into a non-full `M × N` Young tableau
// The new element is initially placed in the bottom-right corner of the tableau.
// The function works by swapping the smallest of [i-1, j] and [i, j-1] with
// [i, j] and recur for the smaller value.

void insert(vector<vector<int>>& tableau, int i, int j)
{
    // base case
    if (i == 0 && j == 0) {
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

    if (tableau[i][j] < tableau[i - 1][j])        // go up
    {
        swap(tableau[i][j], tableau[i - 1][j]);
        insert(tableau, i - 1, j);
    }

    if (tableau[i][j] < tableau[i][j - 1])        // go left
    {
        swap(tableau[i][j], tableau[i][j - 1]);
        insert(tableau, i, j - 1);
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


// Recursive function to insert a new element into a non-full `M × N` Young tableau
vector<vector<int>> insert(vector<int>& keys)
{
    int M = ceil(sqrt(keys.size()));
    int N = M;

    // construct an `M × N` Young tableau and initialize it by infinity
    vector<vector<int>> tableau(M, vector<int>(N, INT_MAX));

    // do for each key
    for (int key : keys)
    {
        // check for overflow
        if (tableau[M - 1][N - 1] != INT_MAX) {
            cout << "Young tableau is full. Skipping key " << key << endl;
        }
        else {
            // place the key in the bottom-right corner of the tableau
            tableau[M - 1][N - 1] = key;

            // move the key to its correct position in the tableau
            insert(tableau, M - 1, N - 1);
        }
    }

    return tableau;
}

int main()
{
    // construct a Young tableau from the following keys
    vector<int> keys = { 12, 10, 20, 22, 25, 30, 34, 11,
                        44, 27, 16, 40, 35, 15, 18, 45 };

    vector<vector<int>> tableau = insert(keys);
    printTableau(tableau);

    return 0;
}

/*

*/