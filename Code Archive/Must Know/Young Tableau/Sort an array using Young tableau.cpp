#include "Header.h";

using namespace std;

/*
Sort an array using Young tableau
Google Translate Icon
In this post, we will see how to sort N2 numbers in increasing order using an N × N Young tableau in O(N3) time.

An N × N Young tableau is an N × N matrix such that entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry. Thus, a Young tableau can be used to hold n <= N2 finite numbers.


Refer the following article on Young tableau as a prerequisite of this post:

Young Tableau | Insert, Search, Extract-Min, Delete, Replace

Practice This Problem


To sort an array using Young tableau, insert each of its values into an empty Young tableau, one at a time. Afterward, repeatedly call the Extract-Min routine on the Young tableau until the tableau is empty and put the returned values back to the original array.

Following is the C++
Constructing an O(N × N) Young tableau from O(N2) keys takes O(N3) time. Also, the extractMin() routine is called O(N × N) times, which runs in linear time. So, the overall time complexity of the proposed solution is O(N3) for O(N2) keys. The additional space used by the program is O(N2) for constructing an N × N Young tableau.

In order words, the sorting procedure runs in O(n1.5) time and O(n) space, where n is the size of the input.
*/

class YoungTableau
{
    // Recursive function to fix the tableau property in an NxN young tableau
    // an infinite value is initially placed at the firs cell (0,0) of the tableau
    // the function works by swapping the smallest of [i+1, j] and [i, j+1] with
    // [i,j] and recur for the smaller value
    void fixTableau(vector<vector<int>>& tableau, int i, int j)
    {
        int N = tableau.size();

        // get the values present at the bottom and right cell of the current cell
        int bottom = (i + 1 < N) ? tableau[i + 1][j] : INT_MAX;
        int right = (j + 1 < N) ? tableau[i][j + 1] : INT_MAX;

        //base case
        if (bottom == INT_MAX && right == INT_MAX) {
            return;
        }

        if (bottom < right)        // go down
        {
            swap(tableau[i][j], tableau[i + 1][j]);
            fixTableau(tableau, i + 1, j);
        }
        else                    // go right
        {
            swap(tableau[i][j], tableau[i][j + 1]);
            fixTableau(tableau, i, j + 1);
        }
    }

    // recursive function to insert a new element into a non-full NxN young tableau
    // the new element is initially placed at the bottom right corner of the tableau
    // the functiont  works by swapping the smallest of [i-1, j] and [i, j-1] with
    // [i,j] and recur for the smaller value
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

public:
    // Function construct an `N × N` Young tableau from the given keys
    vector<vector<int>> construct(vector<int>& keys)
    {
        // initialize the Young tableau by infinity
        int N = (int)ceil(sqrt(keys.size()));
        vector<vector<int>> tableau(N, vector<int>(N, INT_MAX));

        // do for each key
        for (int key : keys)
        {
            // check for overflow
            if (tableau[N - 1][N - 1] != INT_MAX) {
                break;
            }

            // place the key at the bottom-right corner of the tableau
            tableau[N - 1][N - 1] = key;

            // move the key to its correct position in the tableau
            insert(tableau, N - 1, N - 1);
        }

        return tableau;
    }
    // Function to extract the next minimum element from the Young tableau
    int extractMin(vector<vector<int>>& tableau)
    {
        // the first cell of the tableau stores the minimum element
        int min = tableau[0][0];

        // make the first element as infinity
        tableau[0][0] = INT_MAX;

        // fix the Young tableau property
        fixTableau(tableau, 0, 0);

        return min;
    }


};

void sort(vector<int>& keys)
{
    if (keys.size() == 0) {
        return;
    }

    // construct a Young tableau from the above keys
    YoungTableau s;
    vector<vector<int>> tableau = s.construct(keys);

    // repeatedly call `extractMin()` and fill `keys[]` with the returned values
    for (int i = 0; i < keys.size(); i++) {
        keys[i] = s.extractMin(tableau);
    }
}

int main()
{
    // unsorted input
    vector<int> keys{ 6, 4, 8, 7, 2, 3, 1, 5 };

    // sort the input keys
    sort(keys);

    // print the sorted input
    for (int i : keys) {
        cout << i << ' ';
    }

    return 0;
}

/*

*/